#ifndef UTILS_TIME_H_
#define UTILS_TIME_H_

// System headers
#include <cstdint>
#include <chrono>

// Other libraries headers

// Own components headers

class Time {
public:
  Time& getElapsed();

  size_t toSeconds() const;
  size_t toMilliseconds() const;
  size_t toMicroseconds() const;
  size_t toNanoseconds() const;

private:
  std::chrono::time_point<std::chrono::steady_clock> _now =
      std::chrono::steady_clock::now();
  std::chrono::time_point<std::chrono::steady_clock> _elapsedLastCall;
};

#endif /* UTILS_TIME_H_ */
