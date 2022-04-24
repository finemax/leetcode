#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue {
  public:
    BlockingQueue() = default;
    BlockingQueue(int capacity) : capacity_(capacity) {}
    int push(const T& e) {
      std::unique_lock<mutex> lock(mutex_);
      while(queue_.size() >= capacity_) {
        not_full_.wait(mutex_);
      }
      if (queue_.size() >= capacity_) {
        return -1;
      }
      queue_.push(e);
      not_empty_.notify_one();
      return 0;
    } 

    int get(T& e) {
      std::unique_lock<mutex> lock(mutex_);
      while(queue_.empty()) {
        not_empty_.wait(mutex_);
      }
      if (queue_.empty()) {
        return -1;
      }
      e = queue_.front();
      queue_.pop()
      not_full_.notify_one();
      return 0;
    }
  private:
    queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    int capacity_ = INT_MAX;
};