// Corresponding header
#include "shape/config/ShapeConfigLoader.h"

// System headers

// Other libraries headers

// Own components headers

namespace {
//TODO read values from a file
constexpr auto FILE_NAME = "batman.ppm";
constexpr auto IMAGE_WIDTH = 1920;
constexpr auto IMAGE_HEIGHT = 1080;
constexpr auto BATMAN_ORIGIN_X = IMAGE_WIDTH / 2;
constexpr auto BATMAN_ORIGIN_Y = IMAGE_HEIGHT / 2;
constexpr auto BATMAN_SCALE = 120.0;
constexpr auto BATMAN_OVAL_RADIUS_X = IMAGE_WIDTH / 2;
constexpr auto BATMAN_OVAL_RADIUS_Y = BATMAN_OVAL_RADIUS_X / 2;
}

ShapeConfig ShapeConfigLoader::loadConfig() {
  ShapeConfig cfg;

  auto& imageCfg = cfg.imageCfg;
  imageCfg.name = FILE_NAME;
  imageCfg.width = IMAGE_WIDTH;
  imageCfg.height = IMAGE_HEIGHT;

  auto& batmanCfg = cfg.batmanShapeCfg;
  batmanCfg.origin = Point2f(BATMAN_ORIGIN_X, BATMAN_ORIGIN_Y);
  batmanCfg.ovalRadius = Point2f(BATMAN_OVAL_RADIUS_X, BATMAN_OVAL_RADIUS_Y);;
  batmanCfg.scale = BATMAN_SCALE;

  return cfg;
}
