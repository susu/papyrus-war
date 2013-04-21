#ifndef CW_CORE_MODEL_HPP_INC
#define CW_CORE_MODEL_HPP_INC

#include <cw/core/EntityContainer.hpp>

namespace cw
{
  namespace core
  {
    class Model
    {
      public:
        virtual void tick() = 0;
    };
    typedef EntityContainer<Model, &Model::tick> ModelContainer;
  }
}

#endif
