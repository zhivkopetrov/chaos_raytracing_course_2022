// Corresponding header
#include "crt/config/CrtConfigLoader.h"

// System headers

// Other libraries headers
#include "utils/file/IniFileParser.h"
#include "utils/log/Log.h"

// Own components headers
#include "crt/defines/CrtDefines.h"

namespace {
constexpr auto CONFIG_FILE_NAME = "config.ini";

//config keys
constexpr auto IMAGE_SECTION_NAME = "image";
constexpr auto IMAGE_NAME = "name";
constexpr auto IMAGE_WIDTH = "width";
constexpr auto IMAGE_HEIGHT = "height";

constexpr auto PIXEL_REGION_SECTION_NAME = "pixel_regions";
constexpr auto PIXEL_REGION_ROWS = "rows";
constexpr auto PIXEL_REGIONS_PER_ROW = "regions_per_row";

constexpr auto STRATEGY_SECTION_NAME = "strategy";
constexpr auto STRATEGY_IDENTIFIER = "identifier";
constexpr auto WORKER_THREADS_HINT = "worker_threads_hint";

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

ErrorCode populatePexielRegionSection(const IniFileData &data,
                                      PixelRegionConfig &outCfg) {
  auto it = data.find(PIXEL_REGION_SECTION_NAME);
  if (it == data.end()) {
    LOGERR("Error, section name: '%s' not found in '%s'",
        PIXEL_REGION_SECTION_NAME, CONFIG_FILE_NAME);
    return ErrorCode::FAILURE;
  }
  const auto &section = it->second;

  bool success = IniFileParser::getKeyValueInt(section, PIXEL_REGION_ROWS,
      outCfg.pixelRegionsRows);
  if (!success)
    return ErrorCode::FAILURE;

  success = IniFileParser::getKeyValueInt(section, PIXEL_REGIONS_PER_ROW,
      outCfg.pixelRegionsPerRow);
  if (!success)
    return ErrorCode::FAILURE;

  return ErrorCode::SUCCESS;
}

ErrorCode populateStrategySection(const IniFileData &data,
                                  StrategyConfig &outCfg) {
  auto it = data.find(STRATEGY_SECTION_NAME);
  if (it == data.end()) {
    LOGERR("Error, section name: '%s' not found in '%s'", STRATEGY_SECTION_NAME,
        CONFIG_FILE_NAME);
    return ErrorCode::FAILURE;
  }
  const auto &section = it->second;

  std::string strategyStr;
  bool success = IniFileParser::getKeyValueString(section, STRATEGY_IDENTIFIER,
      strategyStr);
  if (!success)
    return ErrorCode::FAILURE;
  outCfg.strategy = parseStrategy(strategyStr);

  success = IniFileParser::getKeyValueInt(section, WORKER_THREADS_HINT,
      outCfg.workerThreadsHint);
  if (!success)
    return ErrorCode::FAILURE;

  return ErrorCode::SUCCESS;
}
} //end anonymous namespace

ErrorCode CrtConfigLoader::loadConfig(CrtConfig &outCfg) {
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

  err = populatePexielRegionSection(fileData, outCfg.pixelRegionCfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("Error, populatePexielRegionSection() failed");
    return ErrorCode::FAILURE;
  }

  err = populateStrategySection(fileData, outCfg.strategyCfg);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("Error, populatePexielRegionSection() failed");
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}
