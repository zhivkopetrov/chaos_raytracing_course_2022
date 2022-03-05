#ifndef SHAPE_SHAPEAPPLICATION_H_
#define SHAPE_SHAPEAPPLICATION_H_

// System headers

// Other libraries headers
#include "utils/file/PpmFileWritter.h"
#include "utils/ErrorCode.h"

// Own components headers
#include "shape/config/ShapeConfig.h"

// Forward declarations

class ShapeApplication {
public:
  ErrorCode run(const ShapeConfig &cfg);

private:
  ErrorCode saveOutput(const ImageConfig &cfg,
                       const std::vector<Color24> &pixels);

  PpmFileWritter _writter;
};

#endif /* SHAPE_SHAPEAPPLICATION_H_ */
