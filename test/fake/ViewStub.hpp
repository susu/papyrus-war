#ifndef FAKE_VIEW_STUB_HPP_INC
#define FAKE_VIEW_STUB_HPP_INC

#include <cw/graph/View.hpp>

namespace fake
{
  class ViewStub : public cw::graph::View
  {
    public:
      ViewStub( UnitStubRef unit )
        : m_unit(unit)
      {}

      UnitStubRef getUnit()
      {
        return m_unit;
      }
      virtual void show() override {}

      UnitStubRef m_unit;
  };
}

#endif
