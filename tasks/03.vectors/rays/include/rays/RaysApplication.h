#ifndef RAYS_RAYSAPPLICATION_H_
#define RAYS_RAYSAPPLICATION_H_

// System headers

// Other libraries headers
#include "utils/file/PpmFileWritter.h"
#include "utils/ErrorCode.h"

// Own components headers
#include "rays/config/RaysConfig.h"
#include "rays/scene/RaysScene.h"

// Forward declarations

class RaysApplication {
public:
  ErrorCode run(const RaysConfig &cfg);

private:
  ErrorCode saveOutput(const ImageConfig &cfg,
                       const std::vector<Color24> &pixels);

  RaysScene _scene;
  PpmFileWritter _writter;
};

#endif /* RAYS_RAYSAPPLICATION_H_ */
