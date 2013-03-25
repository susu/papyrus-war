#ifndef CW_GRAPH_UNIT_FACTORY_HPP_INC
#define CW_GRAPH_UNIT_FACTORY_HPP_INC

#include <cw/core/Types.hpp>

#include <cw/graph/Types.hpp>
#include <cw/graph/ViewFactory.hpp>

namespace cw
{
  namespace graph
  {
    //  UnitFactory - TODO register at InputDistributor
    template<class ViewPolicy>
    class UnitFactory
    {
      public:
        typedef std::function< void(core::UnitRef) > UnitCreatedCallback;
        typedef std::function< void( Ref<View> ) > ViewCreatedCallback;
        UnitFactory( UnitCreatedCallback unitCallback, ViewCreatedCallback viewCallback )
          : m_unitCallback( unitCallback )
          , m_viewCallback( viewCallback )
        {
        }

        template<class T, typename... Args>
        void createUnit(Args&&... args)
        {
          Ref<T> unit( new T( std::forward<Args>(args)... ) );
          m_unitCallback(unit);

          auto view = m_viewFactory.template createViewFor<T>( unit );
          m_viewCallback(view);
        }
      private:
        UnitCreatedCallback m_unitCallback;
        ViewCreatedCallback m_viewCallback;
        ViewFactory<ViewPolicy> m_viewFactory;
    };
  }
}

#endif
