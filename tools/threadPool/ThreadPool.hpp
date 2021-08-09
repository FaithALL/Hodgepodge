/**
 * 固定数目的线程池，当线程池销毁时会等待所有线程执行完毕，单例设计模式
 * 向线程池添加任务时，会忽略可执行对象的返回值，如果想从执行任务中获取信息，应该自己实现(例如在参数中传std::promise)
 * 参考https://github.com/progschj/ThreadPool/blob/master/ThreadPool.h
 */

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>

class ThreadPool {
public:

    static ThreadPool &getInstance() {
        static ThreadPool threadPool;
        return threadPool;
    }

    //向线程池增加任务，当F的参数为引用时，需要std::ref实参
    template<typename F, typename ... Args>
    void append(F &&, Args &&...);

    //销毁线程池，销毁所有线程
    inline ~ThreadPool();

    //禁止拷贝、移动线程池
    ThreadPool(const ThreadPool &) = delete;

    ThreadPool(ThreadPool &&) = delete;

    ThreadPool &operator=(const ThreadPool &) = delete;

    ThreadPool &operator=(ThreadPool &&) = delete;

private:
    bool mStop = false;
    std::vector<std::thread> mThreads;
    std::condition_variable mCondition;
    std::mutex mMutexLock;
    std::queue<std::function<void()>> mTaskQueue;

    //创建固定线程数的线程池
    inline explicit ThreadPool(unsigned = std::thread::hardware_concurrency());
};

ThreadPool::ThreadPool(unsigned threadCount) {
    for (unsigned i = 0; i < threadCount; ++i) {
        mThreads.emplace_back([this]() {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> uniqueLock(this->mMutexLock);
                    mCondition.wait(uniqueLock, [this]() {
                        return this->mStop || !this->mTaskQueue.empty();
                    });
                    if (this->mStop && this->mTaskQueue.empty()) return;
                    task = std::move(this->mTaskQueue.front());
                    this->mTaskQueue.pop();
                }
                task();
            }
        });
    }
}

template<typename F, typename ... Args>
void ThreadPool::append(F &&func, Args &&... args) {
    {
        std::lock_guard<std::mutex> lockGuard(mMutexLock);
        auto task = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
        mTaskQueue.push([task]() { task(); });
    }
    mCondition.notify_one();
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lockGuard(mMutexLock);
        mStop = true;
    }
    mCondition.notify_all();
    for (auto &t : mThreads) t.join();
}

#endif //THREADPOOL_HPP