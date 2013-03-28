#include <algorithm>

#include <cw/core/Logger.hpp>
#include <cw/core/InputDistributor.hpp>
#include <cw/core/Model.hpp>

namespace
{
  cw::core::Logger logger("core");
}

namespace cw
{
  namespace core
  {

InputDistributor::InputDistributor()
{}

InputDistributor::~InputDistributor()
{}

void InputDistributor::registerModel(Ref<Model> model)
{
  m_models.insert(model);
}

void InputDistributor::clickedAt(int x, int y)
{
  for ( const Ref<Model> & model : m_models )
  {
    if ( !model->hasFocus() )
    {
      if ( model->isOver(x,y) )
      {
        model->setFocus(true);
      }
    }
    else
    {
      model->moveTo(x,y);
    }
  }
}

void InputDistributor::zoom(ZoomDir dir)
{}

void InputDistributor::startScroll(ScrollDir dir)
{}

void InputDistributor::stopScroll()
{}

  }
}
