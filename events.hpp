#ifndef EVENTS_H
#define EVENTS_H
#include <string>
#include "threadsafe_queue.hpp"

  enum EventType {Login, Register, Quit};

   // this is an Event struct. It is used to pass event information between threads.
   //  We could potentially create a virtual class so we can have many types of events for example
   // UserEvents
   // AudioEvents
   // etc
   
  struct Event { 

    private:
     EventType m_type;
     std::string m_argument;

    public:
     Event(EventType type, std::string &&argument) : m_type(type), m_argument(argument) {};
     Event(EventType type, const char *argument) : m_type(type), m_argument(argument) {};

     EventType type() { return m_type; }
     const std::string& data() { return m_argument; } // returns a const reference it is not possible to be modified outside Event
  };

  typedef std::shared_ptr<Event> EventSharedPointer;

#endif // !GLOBAL_H
