#include <igloo/igloo_alt.h>

#include <cw/core/CommandDispatcher.hpp>
#include <cw/core/InputDistributor.hpp>

#include "fake/ModelStub.hpp"
#include "fake/PickingStub.hpp"

using namespace igloo;
using namespace cw;

Describe(ACommandDispatcher)
{
  core::CommandDispatcher::ModelContainer m_models;
  fake::PickingStub m_pickingStub;
  core::CommandDispatcher dispatcher;

  ACommandDispatcher()
    : dispatcher(m_models, m_pickingStub)
  {}

  It(should_set_focus_on_unit_if_clicked)
  {
    // Arrange
    auto model = std::make_shared<fake::ModelStub>();
    model->over() = true;
    m_models.add(model);

    // Act
    dispatcher.onClick( core::ClickEvent{ core::Pos(0,0) } );

    // Assert
    AssertThat( model->hasFocus(), Equals(true) );
  }

  It(should_not_set_focus_if_position_not_matches)
  {
    // Arrange
    auto model = std::make_shared<fake::ModelStub>();
    m_models.add(model);

    // Act
    dispatcher.onClick( core::ClickEvent{ core::Pos(0,0) } );

    // Assert
    AssertThat( model->hasFocus(), Equals(false) );
  }

  It(should_remove_focus_if_pos_not_match)
  {
    // Arrange
    auto model = std::make_shared<fake::ModelStub>();
    m_models.add(model);
    model->over() = false;
    model->setFocus(true);

    // Act
    dispatcher.onClick( core::ClickEvent{ core::Pos(0,0) } );

    // Assert
    AssertThat( model->hasFocus(), Equals(false) );
  }
};
