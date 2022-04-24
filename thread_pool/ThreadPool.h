#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool {
  public:
    using Task = std::function<void()>;

    explicit ThreadPool(int max_size);
    ~ThreadPool();

    void AddTask(Task task);
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
      -> std::future<typename std::result_of<F(Args...)>::type>;
  private:

    std::queue<Task> tasks_;
    std::vector<std::thread> work_threads_;

    std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_;
};

ThreadPool::ThreadPool(int max_size) : stop_(false) {
  for (int i = 0; i < max_size; ++i) {
    work_threads_.emplace_back(
      [this]() {
        while (!stop_) {
          Task task;
          {
            std::unique_lock<std::mutex> lock(mutex_);
            this->cv_.wait(lock, [this]{ return this->stop_ || !this->tasks_.empty();});
            if (this->stop_ && this->tasks_.empty()) {
              return;
            }
            task = std::move(this->tasks_.front());
            this->tasks_.pop();
          }
          if (task != nullptr) {
            task();
          }
        }
      }
    );
  }
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(mutex_);
    stop_ = true;
  }
  cv_.notify_all();
  for (auto& thread : work_threads_) {
    thread.join();
  }
}

void ThreadPool::AddTask(Task task) {
  std::unique_lock<std::mutex> lock(mutex_);
  tasks_.emplace(std::move(task));
  cv_.notify_one();
}

template <typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
  -> std::future<typename std::result_of<F(Args...)>::type> {
   using return_type = typename std::result_of<F(Args...)>::type;
   auto task = std::make_shared<std::packaged_task<return_type()>>(
     std::bind(std::forward<F>(f), std::forward<Args>(args)...)
   ); 
   std::future<return_type> res = task->get_future();
   {
     std::unique_lock<std::mutex> lock(mutex_);
     if (stop_) {
       throw std::runtime_error("enqueue on stopped ThreadPool");
     }
     tasks_.emplace([task]() { (*task)(); });
   }
   cv_.notify_one();
   return res;
}

