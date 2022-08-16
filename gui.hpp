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
      std::cout << "main_thread: Please enter your command.\n";

      std::cout << "> ";
      std::getline(std::cin, line);

      std::cout << "\n";

      if (line == "quit") {
         quit = true;
         Event event(EventType::Quit, "");
         event_queue.push(event);
         continue;
      }

      auto [command, argument] = split_input(line);

      if (command == "login") {
        std::cout << "GUI pushing to login with arguments -> " << argument << std::endl;
        Event event(EventType::Login, std::move(argument));
        event_queue.push(event);
      }

      if (command == "register") {
        std::cout << "GUI pushing to register with arguments -> " << argument << std::endl;
        Event event(EventType::Login, std::move(argument));
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
