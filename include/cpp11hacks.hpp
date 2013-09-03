#ifndef CPP_11_HACKS_HPP_INC
#define CPP_11_HACKS_HPP_INC

// not supported keywords

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
#define constexpr const
#define noexcept throw()
#endif

#include <memory>

// C++14 hacks
namespace std
{
  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args&&>(args)...));
  }
}

#endif
