#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mtx; // mutable to allow locking in const member functions
    std::condition_variable cv;

public:
    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mtx); // Use std::lock_guard to lock the mutex
        queue.push(item);
        cv.notify_one(); // Notify one waiting thread
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx); // Use std::unique_lock to wait on condition variable
        cv.wait(lock, [this]() { return !queue.empty(); });
        T item = queue.front();
        queue.pop();
        return item;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx); // Use std::lock_guard to lock the mutex
        return queue.empty();
    }
};