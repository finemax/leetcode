#include<iostream>
#include<mutex>

struct ReadWriteLock {
public:
    ReadWriteLock() : r_cnt_(0) {}
    void ReadLock() {
        r_mutex_.lock();
        r_cnt_++;
        if (r_cnt_ == 1) {
            w_mutex_.lock(); 
        }
        r_mutex_.unlock();
    }
    void ReadUnlock() {
        r_mutex_.lock();
        r_cnt_--;
        if (r_cnt_ == 0) {
            w_mutex_.unlock(); 
        }
        r_mutex_.unlock();
    }
    void WriteLock() {
        w_mutex_.lock();
    }
    void WriteUnlock() {
        w_mutex_.unlock();
    }
private:
    std::mutext r_mutex_;
    std::mutext w_mutex_;
    int r_cnt_;
};
