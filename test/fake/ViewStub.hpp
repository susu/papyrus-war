#ifndef FAKE_VIEW_STUB_HPP_INC
#define FAKE_VIEW_STUB_HPP_INC

#include <cw/graph/View.hpp>

namespace fake
{
  class ViewStub : public cw::graph::View
  {
    public:
      ViewStub( Ref<ModelStub> model )
        : m_model(model)
      {}

      Ref<ModelStub> getModel()
      {
        return m_model;
      }
      virtual void show() override {}

      Ref<ModelStub> m_model;
  };
}

#endif
