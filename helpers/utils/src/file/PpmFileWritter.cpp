// Corresponding header
#include "utils/file/PpmFileWritter.h"

// System headers

// Other libraries headers

// Own components headers
#include "utils/data_type/EnumClassUtils.h"
#include "utils/log/Log.h"

ErrorCode PpmFileWritter::writeFile(const std::string &file,
                                    const PpmHeader &header,
                                    const std::vector<Color24> &pixels) {
  auto err = validate(file, header, pixels);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("validate() failed");
    return err;
  }

  err = openStream(file);
  if (ErrorCode::SUCCESS != err) {
    LOGERR("openStream() failed");
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
    LOGERR("Error, file: [%s] must end with .ppm extension", file.c_str());
    return ErrorCode::FAILURE;
  }

  if (PpmVersion::P3 != header.version) {
    LOGERR("Error, received unsupported PpmVersion: %d. Currently only "
           "P3 version is supported",
        getEnumValue(header.version));
    return ErrorCode::FAILURE;
  }

  const size_t expectedPixelsCtn = header.imageWidth * header.imageHeight;
  const size_t providedPixelsCtn = pixels.size();
  if (expectedPixelsCtn != providedPixelsCtn) {
    LOGERR("Error, expectedPixelsCtn/providedPixelsCtn mismatch. %zu vs %zu",
        expectedPixelsCtn, providedPixelsCtn);
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

ErrorCode PpmFileWritter::openStream(const std::string &file) {
  //RAII dtor will close the stream when finished
  _fileStream.open(file.c_str(), std::ios::out | std::ios::binary);
  if (!_fileStream) {
    LOGERR("Error, file: [%s] could not be created", file.c_str());
    return ErrorCode::FAILURE;
  }

  return ErrorCode::SUCCESS;
}

void PpmFileWritter::doWrite(const PpmHeader &header,
                             const std::vector<Color24> &pixels) {
  _fileStream << std::nounitbuf; //don't flush after insertion

  _fileStream << "P3\n" << header.imageWidth << ' ' << header.imageHeight
              << '\n' << header.maxColorComponent << '\n';

  int32_t pixelId = 0;
  for (int32_t row = 0; row < header.imageHeight; ++row) {
    for (int32_t col = 0; col < header.imageWidth; ++col) {
      pixels[pixelId].writeInt32DataToStream(_fileStream);
      _fileStream << '\t';
      ++pixelId;
    }
    _fileStream << '\n';
  }
}

