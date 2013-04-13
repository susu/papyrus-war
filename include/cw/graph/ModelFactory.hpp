#ifndef CW_GRAPH_MODEL_FACTORY_HPP_INC
#define CW_GRAPH_MODEL_FACTORY_HPP_INC

#include <cw/core/Types.hpp>

#include <cw/graph/Types.hpp>
#include <cw/graph/ViewFactory.hpp>

namespace cw
{
  namespace graph
  {
    //  TODO register at InputDistributor
    template<class Factory>
    class ModelFactory
    {
      public:
        typedef std::function< void( Ref<core::Model> ) > ModelCreatedCallback;
        typedef std::function< void( Ref<View> ) > ViewCreatedCallback;

        template<typename... FactoryCtorArgs>
        ModelFactory( ModelCreatedCallback modelCallback,
                     ViewCreatedCallback viewCallback,
                     FactoryCtorArgs&&... args )
          : m_modelCallback( modelCallback )
          , m_viewCallback( viewCallback )
          , m_viewFactory( std::forward<FactoryCtorArgs>(args)... )
        {
        }

        template<class T, typename... Args>
        Ref<T> create(Args&&... args)
        {
          Ref<T> model( new T( std::forward<Args>(args)... ) );
          m_modelCallback(model);

          auto view = m_viewFactory.template createViewFor<T>( model );
          m_viewCallback(view);
          return model;
        }
      private:
        ModelCreatedCallback m_modelCallback;
        ViewCreatedCallback m_viewCallback;
        Factory m_viewFactory;
    };
  }
}

#endif
