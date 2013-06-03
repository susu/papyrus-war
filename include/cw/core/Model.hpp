#ifndef CW_CORE_MODEL_HPP_INC
#define CW_CORE_MODEL_HPP_INC

#include <cw/core/HasCallbackRegistrar.hpp>

namespace cw
{
  namespace core
  {
    class Model : public HasCallbackRegistrar
    {
      public:
        virtual void tick(double diffTime) = 0;
    };
  }
}

#endif
