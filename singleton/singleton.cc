#include <iostream>

// Meyer's Singleton
template <typename T>
class Singleton {
    public:
        static T& GetInstance() {
            static T instance;
            return instance;
        }
        Singleton(T&&) = delete;
        Singleton(const T&) = delete;
        void operator= (const T&) = delete;
    private:
        Singleton() = default;
        virtual ~Singleton() = default;
};

// Lazy Singleton
template <typename T, bool is_thread_safe = true>
class LazySingleton {
    public:
        static T& GetInstance() {
            if (is_thread_safe == false) {
                if (t_ == nullptr) {
                    t_ = std::unique_ptr<T>(new T);
                    return *t_;
                }
            }
            if (t_ == nullptr) {
                std::unique_lock<std::mutex> lk(mtx_);
                if (t_ == nullptr) {
                    t_ = std::unique_ptr<T>(new T);
                }
                return *t_;
            } else {
                return *t_;
            };
        }

        LazySingleton(T&&) = delete;
        LazySingleton(const T&) = delete;
        void operator= (const T&) = delete;
    private:
        static std::unique_ptr<T> t_;
        static mutex mtx_;
};

template<typename T, bool is_thread_safe>
std::unique_ptr<T> LazySingleton<T, is_thread_safe>::t_;

template<typename T, bool is_thread_safe>
std::mutex LazySingleton<T, is_thread_safe>::mtx_;

// EagerSingleton
template<typename T>
class EagerSingleton {

public:
    static T& GetInstance() {
        return *t_;
    }

    EagerSingleton(T&&) = delete;
    EagerSingleton(const T&) = delete;
    void operator= (const T&) = delete;

private:
    EagerSingleton() = default;
    virtual ~EagerSingleton() = default;

    static T* t_;
};

template<typename T>
T* EagerSingleton<T>::t_ = new (std::nothrow) T;


