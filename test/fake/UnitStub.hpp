#ifndef FAKE_UNIT_STUB_HPP_INC
#define FAKE_UNIT_STUB_HPP_INC

#include <cw/core/Unit.hpp>
#include <cw/core/Pos.hpp>

namespace fake
{
  class UnitStub : public cw::core::Unit
  {
    public:
      UnitStub()
        : m_focused(false)
        , m_moveTarget(-1,-1)
      {}
      void setPos( double x, double y )
      {
        m_pos = {x,y};
      }

      void setSize( double x, double y )
      {
        m_size = {x,y};
      }

      cw::core::Pos getMoveTarget() const
      {
        return m_moveTarget;
      }

      virtual bool hasFocus() const override
      {
        return m_focused;
      }

      virtual void setFocus(bool f) override
      {
        m_focused = f;
      }

      virtual bool isOver(double x, double y) const override
      {
        LOG(DEBUG) << "x=" << x << " y=" << y;
        return ( m_pos.x < x && x < m_pos.x + m_size.x ) &&
               ( m_pos.y < y && y < m_pos.y + m_size.y );
      }

      virtual void moveTo(double x, double y) override
      {
        m_moveTarget = {x,y};
      }

      virtual void tick() override
      {}

    private:
      struct Coord
      {
        double x,y;
      };
      Coord m_pos;
      Coord m_size;
      bool m_focused;
      cw::core::Pos m_moveTarget;
  };
  typedef std::shared_ptr<UnitStub> UnitStubRef;
}

#endif
