#ifndef UTILS_INIFILEPARSER_H_
#define UTILS_INIFILEPARSER_H_

// System headers
#include <string>
#include <string_view>
#include <unordered_map>

// Other libraries headers

// Own components headers
#include "utils/ErrorCode.h"

// Forward declarations

#include <iostream>
#include <cctype>

using IniFileSection = std::unordered_map<std::string, std::string>;
using IniFileData = std::unordered_map<std::string, IniFileSection>;

class IniFileParser {
public:
  IniFileParser() = delete;

  ErrorCode parseFile(std::string_view file, IniFileData& outData);
};

#endif /* UTILS_INIFILEPARSER_H_ */
