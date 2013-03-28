#ifndef TEST_MODEL_FACTORY_HPP_INC
#define TEST_MODEL_FACTORY_HPP_INC

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
  using Mapping = FakeMapping<T>;
};

typedef cw::graph::ViewFactory<FakePolicy> FakeViewFactory;

Describe(the_ModelFactory)
{
  Ref< cw::core::Model > createdModel;
  Ref< cw::graph::View > createdView;
  cw::graph::ModelFactory<FakeViewFactory> factory;

  the_ModelFactory() : factory(
        [this]( Ref<cw::core::Model> u ) { createdModel = u; },
        [this]( Ref<cw::graph::View> v ) { createdView = v; } )
  {}

  It(can_be_instantiated)
  {
    LOG(DEBUG) << &factory;
  }

  It(should_call_callbacks_with_the_created_elements)
  {
    factory.create<fake::ModelStub>();

    auto viewStub = std::dynamic_pointer_cast<fake::ViewStub>(createdView);

    AssertThat( createdModel, Is().Not().EqualTo( Ref<cw::core::Model>() ) );
    AssertThat( createdView, Is().Not().EqualTo( Ref<cw::graph::View>() ) );

    AssertThat( createdModel, Equals( viewStub->getModel() ) );
  }
};

#endif
