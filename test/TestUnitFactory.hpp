#ifndef TEST_UNIT_FACTORY_HPP_INC
#define TEST_UNIT_FACTORY_HPP_INC

#include <cw/graph/UnitFactory.hpp>
#include <cw/graph/ViewFactory.hpp>

#include "fake/ViewStub.hpp"
#include "fake/UnitStub.hpp"

using namespace igloo;

template<class T>
struct FakeMapping;

VIEW_MAPPING(FakeMapping, fake::UnitStub, fake::ViewStub);

struct FakePolicy
{
  template<class T>
  using Mapping = FakeMapping<T>;
};

typedef cw::graph::ViewFactory<FakePolicy> FakeViewFactory;

Describe(the_UnitFactory)
{
  cw::core::UnitRef createdUnit;
  Ref< cw::graph::View > createdView;
  cw::graph::UnitFactory<FakeViewFactory> factory;

  the_UnitFactory() : factory(
        [this]( cw::core::UnitRef u ) { createdUnit = u; },
        [this]( Ref<cw::graph::View> v ) { createdView = v; } )
  {}

  It(can_be_instantiated)
  {
    LOG(DEBUG) << &factory;
  }

  It(should_call_callbacks_with_the_created_elements)
  {
    factory.createUnit<fake::UnitStub>();

    auto viewStub = std::dynamic_pointer_cast<fake::ViewStub>(createdView);

    AssertThat( createdUnit, Is().Not().EqualTo( cw::core::UnitRef() ) );
    AssertThat( createdView, Is().Not().EqualTo( Ref<cw::graph::View>() ) );

    AssertThat( createdUnit, Equals( viewStub->getUnit() ) );
  }
};

#endif
