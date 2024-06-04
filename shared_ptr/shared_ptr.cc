#include <iostream>
#include <mutex>
#include <thread>

template<class T>
class shared_ptr {
    public:
        shared_ptr(T* ptr = nullptr) : ptr_(ptr),
                                       ref_count_(new int(1),
                                       mtx_(new mutex)) {}
        ~shared_ptr() { Release(); }

        shared_ptr(const shared_ptr<T>& sp) : ptr_(sp.ptr_),
                                              ref_count(sp.refcount_),
                                              mtx_(sp.mtx_) { AddRefCount(); };
        shared_ptr<T>& operator= (const shared_ptr<T>& sp) {
            if (ptr_ != sp.ptr_) {
                Release();
                ptr_ = sp.ptr_;
                ref_count_ = sp.ref_count_;
                mtx_ = sp.mtx_;
                AddRefCount();
            }
            return *this;
        }
        T& operator *() { return *ptr_; }
        T* operator->() { return ptr_; }
        T* Get() { return ptr_; }
        int UseCount() { return *ref_count; }

        void AddRefCount() {
            mtx_->lock();
            ++(*ref_count_);
            mtx_->unlock;
        }
    private:
        void Release() {
            bool flag = false;
            mtx_->lock();
            if (--(*ref_count_) == 0) {
                delete ref_count_;
                delete ptr_;
                flag = true;
            }
            mtx_->unlock();
            if (flag == true) {
                delete mtx_;
            }
        }
        int* ref_count_;
        T* ptr_;
        std::mutex* mtx_;
};
