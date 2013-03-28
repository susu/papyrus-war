#ifndef CW_CORE_RECTANGLE_UNIT_HPP_INC
#define CW_CORE_RECTANGLE_UNIT_HPP_INC

#include <cw/core/Model.hpp>
#include <cw/core/Pos.hpp>

namespace cw
{
  namespace core
  {
    class RectangleUnit : public Model
    {
      public:
        RectangleUnit( Pos pos, Pos size );
        ~RectangleUnit() = default;
        virtual bool hasFocus() const override;
        virtual void setFocus(bool) override;
        virtual bool isOver(double x, double y) const override;

        Pos getPos() const;
      protected:
        Pos m_pos;
      private:
        bool m_focus;
        Pos m_size;
    };
  }
}

#endif
