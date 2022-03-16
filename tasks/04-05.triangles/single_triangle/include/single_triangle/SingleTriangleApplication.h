#ifndef SINGLE_TRIANGLE_SINGLETRIANGLEAPPLICATION_H_
#define SINGLE_TRIANGLE_SINGLETRIANGLEAPPLICATION_H_

// System headers

// Other libraries headers
#include "utils/file/PpmFileWritter.h"
#include "utils/ErrorCode.h"

// Own components headers
#include "single_triangle/config/SingleTriangleConfig.h"
#include "single_triangle/scene/SingleTriangleScene.h"

// Forward declarations

class SingleTriangleApplication {
public:
  ErrorCode run(const SingleTriangleConfig &cfg);

private:
  ErrorCode saveOutput(const ImageConfig &cfg,
                       const std::vector<Color24> &pixels);

  SingleTriangleSceneConfig generateSceneConfig(
      const SingleTriangleConfig &cfg) const;

  SingleTriangleScene _scene;
  PpmFileWritter _writter;
};

#endif /* SINGLE_TRIANGLE_SINGLETRIANGLEAPPLICATION_H_ */
