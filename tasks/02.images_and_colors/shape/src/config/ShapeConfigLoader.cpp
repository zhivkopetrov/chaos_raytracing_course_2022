// Corresponding header
#include "shape/config/ShapeConfigLoader.h"

// System headers
#include <array>

// Other libraries headers
#include "utils/file/IniFileParser.h"
#include "utils/log/Log.h"

// Own components headers

namespace {
constexpr auto CONFIG_FILE_NAME = "config.ini";

//config keys
constexpr auto IMAGE_SECTION_NAME = "image";
constexpr auto IMAGE_NAME = "name";
constexpr auto IMAGE_WIDTH = "width";
constexpr auto IMAGE_HEIGHT = "height";

constexpr auto GEOMETRY_SECTION_NAME = "geometry";
constexpr auto GEOMETRY_ORIGIN_X = "origin_x";
constexpr auto GEOMETRY_ORIGIN_Y = "origin_y";
constexpr auto GEOMETRY_SHAPE_SCALE = "shape_scale";
constexpr auto GEOMETRY_OVAL_RADIUS_X = "ovar_radius_x";
constexpr auto GEOMETRY_OVAL_RADIUS_Y = "ovar_radius_y";

ErrorCode populateImageSection(const IniFileData &data, ImageConfig &outCfg) {
  auto it = data.find(IMAGE_SECTION_NAME);
  if (it == data.end()) {
    LOGERR("Error, section name: '%s' not found in '%s'", IMAGE_SECTION_NAME,
        CONFIG_FILE_NAME);
    return ErrorCode::FAILURE;
  }
  const auto &section = it->second;

  bool success = IniFileParser::getKeyValueString(section, IMAGE_NAME,
      outCfg.name);
  if (!success)
    return ErrorCode::FAILURE;

  success = IniFileParser::getKeyValueInt(section, IMAGE_WIDTH, outCfg.width);
  if (!success)
    return ErrorCode::FAILURE;

  success = IniFileParser::getKeyValueInt(section, IMAGE_HEIGHT, outCfg.height);
  if (!success)
    return ErrorCode::FAILURE;

  return ErrorCode::SUCCESS;
}

ErrorCode populateGeometrySection(const IniFileData &data,
                                  BatmanShapeConfig &outCfg) {
  auto it = data.find(GEOMETRY_SECTION_NAME);
  if (it == data.end()) {
    LOGERR("Error, section name: '%s' not found in '%s'", GEOMETRY_SECTION_NAME,
        CONFIG_FILE_NAME);
    return ErrorCode::FAILURE;
  }
  const auto &section = it->second;

  constexpr auto valuesCount = 5;
  constexpr std::array<const char*, valuesCount> valueNames { GEOMETRY_ORIGIN_X,
      GEOMETRY_ORIGIN_Y, GEOMETRY_SHAPE_SCALE, GEOMETRY_OVAL_RADIUS_X,
      GEOMETRY_OVAL_RADIUS_Y };
  std::array<float*, valuesCount> values { &outCfg.origin.x, &outCfg.origin.y,
      &outCfg.scale, &outCfg.ovalRadius.x, &outCfg.ovalRadius.y };

  for (auto i = 0; i < valuesCount; ++i) {
    const bool success = IniFileParser::getKeyValueFloat(section, valueNames[i],
        *values[i]);
    if (!success)
      return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}
} //end anonymous namespace

ErrorCode ShapeConfigLoader::loadConfig(ShapeConfig &outCfg) {
  std::string filePath = PROJECT_ROOT_DIR;
  filePath.append("/").append(CONFIG_FILE_NAME);
  IniFileData fileData;
  const auto err = IniFileParser::parseFile(filePath, fileData);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("IniFileParser::parseFile() failed");
    return ErrorCode::FAILURE;
  }

  populateImageSection(fileData, outCfg.imageCfg);
  populateGeometrySection(fileData, outCfg.batmanShapeCfg);

  return ErrorCode::SUCCESS;
}
