#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include <cw/graph/ViewFactory.hpp>

using namespace igloo;

template<class T>
struct DummyMapping;

struct One {};
struct ViewForOne {};

// in mapping-group called 'DummyMapping':
//  OneType => ViewForOneType
//  meaning: with ViewFactory<DummyPolicy> will create ViewForOneType for OneType
VIEW_MAPPING(DummyMapping, One, ViewForOne);

struct DummyPolicy
{
  template<class T>
  using Mapping = DummyMapping<T>;
};

Describe(the_ViewFactory)
{
  cw::graph::ViewFactory<DummyPolicy> factory;

  It(can_be_construccted_with_a_mapping_policy)
  {}

  It(should_create_an_instance_of_ViewForOne_for_One)
  {
    Ref<ViewForOne> view = factory.createViewFor<One>();
  }
};
