#pragma once

#include<chrono>
#include<memory>
#include<numeric>
#include "ThreadPool.h"


class Process : public std::enable_shared_from_this<Process> {
public:
    ~Process() = default;
    static std::shared_ptr<Process> Create(std::shared_ptr<ThreadPool> exector) {
        return std::shared_ptr<Process> (new Process(exector));
    }
    void SetContext(std::unique_ptr<std::vector<int>>&& data) {
        context_data_ = std::move(data);
        if (exector_ == nullptr) return;
        future_ret_ = exector_->enqueue([_this = shared_from_this()](){
            //using namespace std::literals::chrono_literals;
            //std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
            return std::accumulate(_this->context_data_->cbegin(),
                    _this->context_data_->cend(),0);
        });
    }
    int GetValue() const { return future_ret_.get(); }
private:
    Process() = default;
    Process(std::shared_ptr<ThreadPool> exector) : exector_(exector) {}
    std::unique_ptr<std::vector<int>> context_data_;
    mutable std::future<int> future_ret_;
    std::shared_ptr<ThreadPool> exector_;
};
