#ifndef CW_CORE_CALLBACKREGISTRARS_HPP_INC
#define CW_CORE_CALLBACKREGISTRARS_HPP_INC

#include <cw/core/InputDistributor.hpp>
#include <cw/core/Timer.hpp>

namespace cw
{
  namespace core
  {
    /**
     *  Stores all the callback sources for Models and Views
     *  Automatically passed as argument
     */
    class CallbackRegistrars
    {
      public:
        CallbackRegistrars(InputDistributor & inputDistr, Timer & timer)
          : m_inputDistributor(inputDistr)
          , m_timer(timer)
        {}

        InputDistributor & getInputDistributor()
        {
          return m_inputDistributor;
        }

        Timer & getTimer()
        {
          return m_timer;
        }
      private:
        InputDistributor & m_inputDistributor;
        Timer & m_timer;
    };
  }
}

#endif
