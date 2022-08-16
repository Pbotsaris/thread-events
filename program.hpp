#ifndef PROGRAM_H
#define PROGRAM_H
#include "threadsafe_queue.hpp"
#include "events.hpp"
#include "gui.hpp"
#include "event_loop.hpp"
#include <string>
#include <unistd.h>

// Program could hold all the application logic though this could live in the main.cpp too.

class Program {
  public:
  void run() {
      
      ThreadSafeQueue<Event> event_queue; // create a queue that will receive eventw

      // launch GUI on a thread
     std::thread gui_thread([&event_queue, this] { m_gui.main_loop(event_queue); }); 

      // launch EventLoop on another thread on a thread
     std::thread event_thread([&event_queue, this] { m_event_loop.loop(event_queue); });

     gui_thread.join();
     event_thread.join();
  }

  private:
  SkypeGUI m_gui;
  EventLoop m_event_loop;
};

#endif // !PROGRAM_H
