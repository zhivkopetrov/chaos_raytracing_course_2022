#ifndef RAYS_RAYSCONFIG_H_
#define RAYS_RAYSCONFIG_H_

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

struct RaysConfig {
  ImageConfig imageCfg;
};

#endif /* RAYS_RAYSCONFIG_H_ */
