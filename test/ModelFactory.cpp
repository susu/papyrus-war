#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/core/Model.hpp>

#include <cw/graph/ModelFactory.hpp>
#include <cw/graph/ViewFactory.hpp>

#include "fake/ViewStub.hpp"
#include "fake/ModelStub.hpp"

using namespace igloo;

template<class T>
struct FakeMapping;

VIEW_MAPPING(FakeMapping, fake::ModelStub, fake::ViewStub);

struct FakePolicy
{
  template<class T>
  struct Mapping
  {
    typedef FakeMapping<T> type;
  };
};

typedef cw::graph::ViewFactory<FakePolicy> FakeViewFactory;

Describe(the_ModelFactory)
{
  Ref< cw::core::Model >::R createdModel;
  Ref< cw::graph::View >::R createdView;
  cw::graph::ModelFactory<FakeViewFactory> factory;

  the_ModelFactory() : factory(
        [this]( Ref<cw::core::Model>::R u ) { createdModel = u; },
        [this]( Ref<cw::graph::View>::R v ) { createdView = v; } )
  {}

  It(should_call_callbacks_with_the_created_elements)
  {
    factory.create<fake::ModelStub>();

    auto viewStub = std::dynamic_pointer_cast<fake::ViewStub>(createdView);

    AssertThat( createdModel, Is().Not().EqualTo( Ref<cw::core::Model>::R() ) );
    AssertThat( createdView, Is().Not().EqualTo( Ref<cw::graph::View>::R() ) );

    AssertThat( createdModel, Equals( viewStub->getModel() ) );
  }
};
