#ifndef CPP_11_HACKS_HPP_INC
#define CPP_11_HACKS_HPP_INC

// not supported keywords

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
#define constexpr const
#define noexcept throw()
#define __PRETTY_FUNCTION__ __FUNCDNAME__
#endif

#endif
