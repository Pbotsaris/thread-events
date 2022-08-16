#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "events.hpp"
#include <iostream>
#include <tuple>

// we cvan have different classes for event handlers instead of just one for everything for example
//
// UserEventHandlers
// AudioEventHandles
// VideoEventHandlers

class EventHandlers {

  public:
  typedef std::tuple<std::string, std::string> StringTuple;

  static void login(EventSharedPointer event) {

    const std::string &data = event.get()->data();
    auto [user, password] = split_user_password(data);

    std::cout << "EventLoopThread >> logging in user: '" << user << "'  with password: '" << password << "'" << std::endl;
  }

  static void registration(EventSharedPointer event) {
    const std::string &data = event.get()->data();
    auto [user, password] = split_user_password(data);

    std::cout << "EventLoopThread >> registering in user: '" << user << "' with password: '" << password << "'" << std::endl;
  }


  // FUNCTION BELOW IS JUST TO HELP PARSE THE INPUT. IT IS NOT IMPORTANT
  
private:
 static StringTuple split_user_password(const std::string &s, const std::string &delim = " ") {

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

#endif // !USER_HANDLERS_H
