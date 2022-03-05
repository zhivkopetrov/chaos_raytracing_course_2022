#ifndef CRT_CRTAPPLICATION_H_
#define CRT_CRTAPPLICATION_H_

// System headers

// Other libraries headers
#include "utils/file/PpmFileWritter.h"
#include "utils/ErrorCode.h"

// Own components headers
#include "crt/config/CrtConfig.h"

// Forward declarations

class CrtApplication {
public:
  ErrorCode run(const CrtConfig &cfg);

private:
  ErrorCode saveOutput(const ImageConfig &cfg,
                       const std::vector<Color24> &pixels);

  PpmFileWritter _writter;
};

#endif /* CRT_CRTAPPLICATION_H_ */
