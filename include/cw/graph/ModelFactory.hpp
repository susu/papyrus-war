#ifndef CW_GRAPH_MODEL_FACTORY_HPP_INC
#define CW_GRAPH_MODEL_FACTORY_HPP_INC

#include <cw/core/Types.hpp>
#include <cw/core/HasCallbackRegistrar.hpp>

#include <cw/graph/Types.hpp>
#include <cw/graph/ViewFactory.hpp>

namespace cw
{
  namespace graph
  {
    /**
     * Responsible to create XyModel, and corresponding XyView
     * Template parameter: the factory which decides the corresponding type of View
     */
    template<class Factory>
    class ModelFactory : public core::HasCallbackRegistrar
    {
      public:
        typedef std::function< void( Ref<core::Model>::R ) > ModelCreatedCallback;
        typedef std::function< void( Ref<View>::R ) > ViewCreatedCallback;

        /**
         * modelCallback, viewCalback: these functions are called if
         *   a model/view is created. Useful to store models/views in a common place
         * args: arguments forwarded to viewFactory
         */
        template<typename... FactoryCtorArgs>
        ModelFactory( ModelCreatedCallback modelCallback,
                     ViewCreatedCallback viewCallback,
                     FactoryCtorArgs&&... args )
          : m_modelCallback( modelCallback )
          , m_viewCallback( viewCallback )
          , m_viewFactory( std::forward<FactoryCtorArgs>(args)... )
        {
        }

        /**
         * Template parameter T: the type of the model
         * args: parameters for ctor of T
         *
         *  returns the created model
         */
        template<class T, typename... Args>
        typename Ref<T>::R create(Args&&... args)
        {
          typename Ref<T>::R model( new T( std::forward<Args>(args)... ) );
          m_modelCallback(model);

          auto view = m_viewFactory.template createViewFor<T>( model );
          m_viewCallback(view);


          if ( hasRegistrars() )
          {
            model->setCallbackRegistrar( getRegistrars() );
            view->setCallbackRegistrar( getRegistrars() );
          }

          return model;
        }

        using HasCallbackRegistrar::setCallbackRegistrar;

      private:
        ModelFactory(ModelFactory&);
        ModelFactory& operator=(ModelFactory);

        ModelCreatedCallback m_modelCallback;
        ViewCreatedCallback m_viewCallback;
        Factory m_viewFactory;
    };
  }
}

#endif
