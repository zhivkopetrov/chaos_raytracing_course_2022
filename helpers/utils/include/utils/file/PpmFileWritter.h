#ifndef UTILS_PPMFILEWRITTER_H_
#define UTILS_PPMFILEWRITTER_H_

// System headers
#include <string>
#include <vector>
#include <fstream>

// Other libraries headers
#include "utils/geometry/Vec3f.h"

// Own components headers
#include "utils/ErrorCode.h"

// Forward declarations

enum class PpmVersion {
  P3, P6
};

struct PpmHeader {
  PpmVersion version = PpmVersion::P3;
  int32_t imageWidth { };
  int32_t imageHeight { };
  int32_t maxColorComponent = 255;
};

class PpmFileWritter {
public:
  ErrorCode writeFile(const std::string &file, const PpmHeader &header,
                      const std::vector<Color24> &pixels);

private:
  ErrorCode validate(const std::string &file, const PpmHeader &header,
                     const std::vector<Color24> &pixels) const;

  ErrorCode openStream(const std::string &file);

  void doWrite(const PpmHeader &header, const std::vector<Color24> &pixels);

  std::ofstream _fileStream;
};

#endif /* UTILS_PPMFILEWRITTER_H_ */
