#ifndef CW_CORE_HAS_CALLBACK_REGISTRAR_HPP_INC
#define CW_CORE_HAS_CALLBACK_REGISTRAR_HPP_INC

#include <cw/Enforce.hpp>
#include <cw/core/CallbackRegistrars.hpp>

namespace cw
{
  namespace graph
  {
    template<typename F>
    class ModelFactory;
  }
  namespace core
  {
    class HasCallbackRegistrar
    {
      protected:
        HasCallbackRegistrar()
          : m_callbackRegistrars(nullptr)
        {}

        CallbackRegistrars & getRegistrars()
        {
          ENFORCE( hasRegistrars(), "CallbackRegistrars not set!" );
          return *m_callbackRegistrars;
        }

        bool hasRegistrars() const
        {
          return nullptr != m_callbackRegistrars;
        }

        virtual void registerCallbacks() {}

      private:
        template<typename F>
        friend class graph::ModelFactory;

        void setCallbackRegistrar( CallbackRegistrars & cbReg )
        {
          m_callbackRegistrars = &cbReg;
          registerCallbacks();
        }

        CallbackRegistrars * m_callbackRegistrars;
    };
  }
}

#endif
