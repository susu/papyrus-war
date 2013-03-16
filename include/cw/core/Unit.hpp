#ifndef CW_CORE_UNIT_HPP_INC
#define CW_CORE_UNIT_HPP_INC

namespace cw
{
  namespace core
  {
    class Unit
    {
      public:
        virtual bool hasFocus() const = 0;
        virtual void setFocus(bool focus) = 0;
        virtual bool isOver(double x, double y) const = 0;
        virtual void moveTo(double x, double y) = 0;
    };
  }
}

#endif
