// Corresponding header
#include "utils/file/PpmFileWritter.h"

// System headers
#include <cerrno>
#include <cstring>
#include <iostream>

// Other libraries headers
#include "utils/data_type/EnumClassUtils.h"

// Own components headers

ErrorCode PpmFileWritter::writeFile(const std::string &file,
                                    const PpmHeader &header,
                                    const std::vector<Color24> &pixels) {
  auto err = validate(file, header, pixels);
  if (ErrorCode::SUCCESS != err) {
    std::cerr << "PpmFileWritter::validate() failed" << std::endl;
    return err;
  }

  err = openStream(file);
  if (ErrorCode::SUCCESS != err) {
    std::cerr << "PpmFileWritter::openStream() failed" << std::endl;
    return err;
  }

  doWrite(header, pixels);
  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileWritter::validate(const std::string &file,
                                   const PpmHeader &header,
                                   const std::vector<Color24> &pixels) const {
  const auto idx = file.rfind(".ppm");
  if (std::string::npos == idx) {
    std::cerr << "Error, file: [" << file << "] must end with .ppm extension"
              << std::endl;
    return ErrorCode::FAILURE;
  }

  if (PpmVersion::P3 != header.version) {
    std::cerr << "Error, received unsupported PpmVersion: "
              << getEnumValue(header.version)
              << ". Currently only P3 version is supported" << std::endl;
    return ErrorCode::FAILURE;
  }

  const size_t expectedPixelsCtn = header.imageWidth * header.imageHeight;
  const size_t providedPixelsCtn = pixels.size();
  if (expectedPixelsCtn != providedPixelsCtn) {
    std::cerr << "Error, expectedPixelsCtn/providedPixelsCtn mismatch. "
              << expectedPixelsCtn << " vs " << providedPixelsCtn << std::endl;
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileWritter::openStream(const std::string &file) {
  //RAII dtor will close the stream when finished
  _fileStream.open(file.c_str(), std::ios::out | std::ios::binary);
  if (!_fileStream) {
    std::cerr << "Error, file: [" << file << "] could not be created. Reason: "
              << strerror(errno) << std::endl;
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

void PpmFileWritter::doWrite(const PpmHeader &header,
                             [[maybe_unused]]const std::vector<Color24> &pixels) {
  _fileStream << "P3\n" << header.imageWidth << ' ' << header.imageHeight
              << '\n' << header.maxColorComponent << '\n';

  int32_t pixelId = 0;
  for (int32_t row = 0; row < header.imageHeight; ++row) {
    for (int32_t col = 0; col < header.imageWidth; ++col) {
      _fileStream << pixels[pixelId];
      ++pixelId;
    }
    _fileStream << '\n';
  }
}

