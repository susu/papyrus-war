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
    template<class Factory>
    class UnitFactory
    {
      public:
        typedef std::function< void(core::UnitRef) > UnitCreatedCallback;
        typedef std::function< void( Ref<View> ) > ViewCreatedCallback;

        template<typename... FactoryCtorArgs>
        UnitFactory( UnitCreatedCallback unitCallback,
                     ViewCreatedCallback viewCallback,
                     FactoryCtorArgs&&... args )
          : m_unitCallback( unitCallback )
          , m_viewCallback( viewCallback )
          , m_viewFactory( std::forward<FactoryCtorArgs>(args)... )
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
        Factory m_viewFactory;
    };
  }
}

#endif
