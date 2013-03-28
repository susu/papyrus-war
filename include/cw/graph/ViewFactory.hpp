#ifndef CW_GRAPH_VIEW_FACTORY_HPP_INC
#define CW_GRAPH_VIEW_FACTORY_HPP_INC

#ifdef VIEW_MAPPING
#error VIEW_MAPPING already defined!
#else
#define VIEW_MAPPING(group,model,view)\
  template<> struct group<model> { typedef view view_type; }
#endif

#include <cw/graph/Types.hpp>

namespace cw
{
  namespace graph
  {
    template<class Policy>
    class ViewFactory
    {
      public:
        template<class Model, typename... CtorArgs>
        Ref< typename Policy::template Mapping<Model>::view_type >
        createViewFor(CtorArgs&&... args)
        {
          return
            Ref< typename Policy::template Mapping<Model>::view_type>
            ( new typename Policy::template Mapping<Model>::view_type
              ( std::forward<CtorArgs>(args)... ) );
        }
    };
  }
}

#endif
