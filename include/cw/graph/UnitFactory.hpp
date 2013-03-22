//
// TODO - UnitFactory
//  - create the unit
//  - store in UnitContainer (call unitcreated callback)
//  - register at InputDistributor
//  - create the xView (TODO needs an AbstractFactory)
//  - store in ViewContainer (call viewcreated callback)
//

#ifndef CW_GRAPH_UNIT_FACTORY_HPP_INC
#define CW_GRAPH_UNIT_FACTORY_HPP_INC

#include <cw/core/Types.hpp>
#include <cw/graph/Types.hpp>

namespace cw
{
  namespace graph
  {
    class UnitFactory
    {
      public:
        typedef std::function< void(core::UnitRef) > UnitCreatedCallback;
        typedef std::function< void( Ref<View> ) > ViewCreatedCallback;
        UnitFactory( UnitCreatedCallback unitCallback, ViewCreatedCallback viewCallback )
        {}
    };
  }
}

#endif
