#ifndef TEST_GRAPH_VIEW_FACTORY_HPP_INC
#define TEST_GRAPH_VIEW_FACTORY_HPP_INC

#include <cw/graph/ViewFactory.hpp>

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

#endif
