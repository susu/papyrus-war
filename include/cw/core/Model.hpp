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
        virtual bool hasFocus() const = 0;
        virtual void setFocus(bool focus) = 0;
        virtual bool isOver(double x, double y) const = 0;
        virtual void moveTo(double x, double y) = 0;

        virtual void tick() = 0;
    };
    typedef EntityContainer<Model, &Model::tick> ModelContainer;
  }
}

#endif
