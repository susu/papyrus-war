#ifndef TEST_UNIT_FACTORY_HPP_INC
#define TEST_UNIT_FACTORY_HPP_INC

#include <cw/graph/UnitFactory.hpp>

using namespace igloo;

template<class T>
struct XCreatedCallback
{
  void operator()( T x )
  {
    lastElement = x;
  }
  T lastElement;
};

Describe(the_UnitFactory)
{
  XCreatedCallback< cw::core::UnitRef > unitCallbacks;
  XCreatedCallback< Ref<cw::graph::View> > viewCallbacks;

  It(can_be_instantiated)
  {
    cw::graph::UnitFactory factory( unitCallbacks, viewCallbacks );
    LOG(DEBUG) << &factory;
  }
};

#endif
