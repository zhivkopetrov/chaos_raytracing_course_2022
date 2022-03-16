#ifndef SINGLE_TRIANGLE_SINGLETRIANGLECONFIG_H_
#define SINGLE_TRIANGLE_SINGLETRIANGLECONFIG_H_

// System headers
#include <cstdint>
#include <string>

// Other libraries headers

// Own components headers

// Forward declarations

struct ImageConfig {
  std::string name;
  int32_t width{};
  int32_t height{};
};

struct SingleTriangleConfig {
  ImageConfig imageCfg;
};

#endif /* SINGLE_TRIANGLE_SINGLETRIANGLECONFIG_H_ */
