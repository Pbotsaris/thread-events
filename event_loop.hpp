#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "events.hpp"
#include "threadsafe_queue.hpp"
#include "event_handlers.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <unordered_map>

class EventLoop {

public:
  EventLoop()
      : m_handlers({
            {EventType::Login, EventHandlers::login},
            {EventType::Register, EventHandlers::registration},
        }) {}

  typedef std::unordered_map< EventType, std::function<void(const EventSharedPointer)>> Handlers;

  Handlers m_handlers;
  std::thread m_thread;

  void loop(ThreadSafeQueue<Event> &event_queue) {
    while (true) {
      if (!event_queue.empty()) { // check if queue is empty before
                                
        EventSharedPointer event = event_queue.pop_try(); // Grab latest event from queue
        
        if(event == nullptr){ // if queue is mutex locked and will nullprt
            continue;
        }

        EventType event_type = event.get()->type(); // get event type
        if (event_type == EventType::Quit) { // if event is quit break the event loop
          break;
        }

        m_handlers[event_type](event); // call the handler for a certain EventType

        // Throtelling the wile loop just so this thread don't run like crazy
        // later we can have our own throtteling logic here
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
      }
    }
  }
};

#endif // !EVENT_HANDLER_H
