#ifndef THREADSAFE_QUEUE_H
#define THREADSAFE_QUEUE_H
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

// This is threadsafe Qeue. Because multiple threads will be pushing and poping to this queue for events
//  we need to make it threadsafe and lock it.
//  You can access the data by either getting calling pop_try() which will return a shared pointer or nulptr
//  you by passing an Event object as argument to retrieve the data.

template <typename T> class ThreadSafeQueue {

  mutable std::mutex m_mutex;
  std::queue<std::shared_ptr<T>> m_queue;
  std::condition_variable m_datacond;

  public:

  ThreadSafeQueue(){};
  void push(T t_item) {

    std::shared_ptr<T> item(std::make_shared<T>(std::move(t_item)));

    std::lock_guard<std::mutex> lock_guard(m_mutex);
    m_queue.push(item);
    m_datacond.notify_one();
  }

  bool pop_try(T &t_item) {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    if (m_queue.empty()) {
      return false;
    }

    t_item = std::move(*m_queue.front()); 
    m_queue.pop();

    return true;
  }

  std::shared_ptr<T> pop_try() {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    if (m_queue.empty()) {
      return std::shared_ptr<T>(); // returns nullptr
    }

    std::shared_ptr<T> res = m_queue.front();
    m_queue.pop();
    return res;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lock_guard(m_mutex);
    return m_queue.empty();
  }
};


#endif // !THREADSAFE_QUEUE_H
