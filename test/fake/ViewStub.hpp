#ifndef FAKE_VIEW_STUB_HPP_INC
#define FAKE_VIEW_STUB_HPP_INC

#include <cw/graph/View.hpp>

#include "ModelStub.hpp"

namespace fake
{
  class ViewStub : public cw::graph::View
  {
    public:
      ViewStub( Ref<ModelStub>::R model )
        : m_model(model)
      {}

      Ref<ModelStub>::R getModel()
      {
        return m_model;
      }
      virtual void show() override {}

      Ref<ModelStub>::R m_model;
  };
}

#endif
