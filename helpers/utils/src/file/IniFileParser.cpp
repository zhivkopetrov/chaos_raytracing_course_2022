// Corresponding header
#include "utils/file/IniFileParser.h"

// System headers
#include <fstream>

// Other libraries headers

// Own components headers
#include "utils/log/Log.h"

namespace {
ErrorCode validate(std::string_view file, std::ifstream &outStream) {
  if (std::string_view::npos == file.rfind(".ini")) {
    LOGERR("Error, file: [%s] is missing .ini extension", file.data());
    return ErrorCode::FAILURE;
  }

  outStream.open(file.data(), std::ios_base::in | std::ios_base::binary);
  if (!outStream) {
    LOGERR("Error, file: [%s] could not be opened", file.data());
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

std::string_view trim(const std::string &line) {
  const size_t size = line.size();
  // trim leading spaces
  size_t startIdx = 0;
  for (; startIdx < size; ++startIdx) {
    if (!isspace(line[startIdx])) {
      break;
    }
  }

  // empty line
  if (startIdx == size) {
    return std::string_view { };
  }

  // trim trailing spaces
  size_t endIdx = size - 1;
  for (; endIdx < size; --endIdx) {
    if (!isspace(line[endIdx])) {
      break;
    }
  }

  return std::string_view(line.c_str() + startIdx, endIdx - startIdx + 1);
}
} //end anonymous namespace

ErrorCode IniFileParser::parseFile(std::string_view file,
                                   IniFileData &outData) {
  std::ifstream fileStream;
  const auto err = validate(file, fileStream);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("Error, validate failed for file: [%s]", file.data());
    return ErrorCode::FAILURE;
  }

  std::string rawLine;
  int32_t lineNumber = 0;
  IniFileSection currSection;
  std::string_view currSectionName;
  while (!fileStream.eof()) {
    ++lineNumber;
    getline(fileStream, rawLine);

    const std::string_view line = trim(rawLine);
    if (line.empty()) {
      continue;
    }

    const char front = line.front();
    // handle comments
    if ( (';' == front) || ('#' == front)) {
      continue;
    }

    // handle section
    if ('[' == front) {
      const auto closeIdx = line.find(']');
      if (std::string_view::npos == closeIdx) {
        LOGERR("Error, section is missing closing ']' on line: %d", lineNumber);
        return ErrorCode::FAILURE;
      }

      const auto sectionName = line.substr(1, closeIdx - 1);
      // finish previous section
      if (!currSectionName.empty()) {
        outData[std::string(currSectionName)] = std::move(currSection);
        currSection.clear();
        currSectionName = sectionName;
      }
      continue;
    }

    // handle value
    const auto eqIdx = line.find('=');
    if (std::string_view::npos == eqIdx) {
      LOGERR("key missing '=' on line: %d", lineNumber);
      return ErrorCode::FAILURE;
    }

    currSection.insert(
        std::make_pair(line.substr(0, eqIdx), line.substr(eqIdx + 1)));
  }

  if (!currSectionName.empty()) {
    outData[std::string(currSectionName)] = std::move(currSection);
  }
  return ErrorCode::SUCCESS;
}
