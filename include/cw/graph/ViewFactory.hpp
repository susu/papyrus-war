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
        typename Ref< typename Policy::template Mapping<Model>::type::view_type >::R
        createViewFor(CtorArgs&&... args)
        {
          return
            typename Ref< typename Policy::template Mapping<Model>::type::view_type>::R
            ( new typename Policy::template Mapping<Model>::type::view_type
              ( std::forward<CtorArgs>(args)... ) );
        }
    };
  }
}

#endif
