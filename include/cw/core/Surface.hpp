#ifndef CW_CORE_SURFACE_HPP_INC
#define CW_CORE_SURFACE_HPP_INC

#include <cw/core/Model.hpp>

namespace cw
{
  namespace core
  {
    class Surface : public Model
    {
      public:
        Surface();
        virtual ~Surface();

        virtual void tick() override;
    };

  }
}

#endif
