#ifndef PROFILE_EXCEPTION_H
#define PROFILE_EXCEPTION_H

#include <exception>

using namespace std;

struct profile_exception : std::exception
{
  const string message;

  profile_exception(const string message) : message(message)
  {
  }

  const char* what() const throw() override
  {
    return message.c_str();
  }
};

#endif // PROFILE_EXCEPTION_H
