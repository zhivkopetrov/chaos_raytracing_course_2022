// Corresponding header
#include "single_triangle/config/SingleTriangleConfigLoader.h"

// System headers

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
} //end anonymous namespace

ErrorCode SingleTriangleConfigLoader::loadConfig(SingleTriangleConfig &outCfg) {
  std::string filePath = PROJECT_ROOT_DIR;
  filePath.append("/").append(CONFIG_FILE_NAME);
  IniFileData fileData;
  auto err = IniFileParser::parseFile(filePath, fileData);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("IniFileParser::parseFile() failed");
    return ErrorCode::FAILURE;
  }

  err = populateImageSection(fileData, outCfg.imageCfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("Error, populateImageSection() failed");
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}
