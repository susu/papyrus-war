#include <cw/core/CommandDispatcher.hpp>


namespace cw
{
  namespace core
  {

CommandDispatcher::CommandDispatcher(ModelContainer & models, const PickingInterface&)
  : m_models(models)
{}

void CommandDispatcher::onClick(ClickEvent click)
{
  m_models.each( [this,click](Ref<Model>::R model)
  {
    if (model->isOver(click.pos))
    {
      model->setFocus(true);
    }
    else
    {
      model->setFocus(false);
    }
  });
}

  }
}
