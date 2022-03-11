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

  if (PpmVersion::P3 == header.version) {
    doWriteP3Format(header, pixels);
  } else {
    doWriteP6Format(header, pixels);
  }

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

  if ((PpmVersion::P3 != header.version) &&
      (PpmVersion::P6 != header.version)) {
    LOGERR("Error, received unsupported PpmVersion: %d. Currently only "
           "P3 and P6 versions are supported", getEnumValue(header.version));
    return ErrorCode::FAILURE;
  }

  const size_t expectedPixelsCtn =
      static_cast<size_t>(header.imageWidth) * header.imageHeight;
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

  _fileStream << std::nounitbuf;

  return ErrorCode::SUCCESS;
}

void PpmFileWritter::doWriteP3Format(const PpmHeader &header,
                                     const std::vector<Color24> &pixels) {

  _fileStream << "P3\n" << header.imageWidth << ' ' << header.imageHeight
              << '\n' << header.maxColorComponent << '\n';

  int32_t pixelId = 0;
  for (int32_t row = 0; row < header.imageHeight; ++row) {
    for (int32_t col = 0; col < header.imageWidth; ++col) {
      pixels[pixelId].writeInt32SpacedData(_fileStream);
      _fileStream << '\t';
      ++pixelId;
    }
    _fileStream << '\n';
  }
}

void PpmFileWritter::doWriteP6Format(const PpmHeader &header,
                                     const std::vector<Color24> &pixels) {

  _fileStream << "P6\n" << header.imageWidth << ' ' << header.imageHeight
              << '\n' << header.maxColorComponent << '\n';

  int32_t pixelId = 0;
  for (int32_t row = 0; row < header.imageHeight; ++row) {
    for (int32_t col = 0; col < header.imageWidth; ++col) {
      pixels[pixelId].writeCharData(_fileStream);
      ++pixelId;
    }
  }
}

