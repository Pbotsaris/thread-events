#ifndef GUI
#define GUI

#include "events.hpp"
#include "threadsafe_queue.hpp"
#include <iostream>
#include <string>
#include <tuple>

typedef std::tuple<std::string, std::string> StringTuple;

class SkypeGUI {
  std::string line;
  bool quit = false;

public:

  void main_loop(ThreadSafeQueue<Event> &event_queue) {
    while (!quit) {
      std::cout << "GUI thread >> Please enter your command.\n";

      std::getline(std::cin, line);

      if (line == "quit") {
         quit = true;
         Event event(EventType::Quit, "");
         event_queue.push(event);
         continue;
      }

      auto [command, argument] = split_input(line);

      // GUI can send events by pushing an event to the queue
      if (command == "login") { 
        std::cout << "GUI Thread >> pushing to login with arguments -> " << argument << std::endl;
        Event event(EventType::Login, std::move(argument));
        event_queue.push(event);
      }

      // GUI puishing a register command
      if (command == "register") {
        std::cout << "GUIT hread >> pushing to register with arguments -> " << argument << std::endl;
        Event event(EventType::Register, std::move(argument));
        event_queue.push(event);
      }
    }
  }

private:
  static StringTuple split_input(const std::string &s,
                                 const std::string &delim = " ") {

    if (s.empty()) {
      return StringTuple{"", ""};
    }

    int start = 0;
    int end = s.find(delim);
    StringTuple result;

    std::string first = (s.substr(start, end - start));
    start = end + delim.size();
    end = s.size();

    std::string second = (s.substr(start, end - start));

    return StringTuple{first, second};
  }
};

#endif // !GUI
