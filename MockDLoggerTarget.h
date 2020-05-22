#include <gmock/gmock.h>
#include "DLoggerTarget.h"

class MockDLoggerTarget : public DLoggerTarget {
 public:
  MOCK_METHOD2(Write,
      void(Level level, const std::string& message));
};
