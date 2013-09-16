#ifndef CW_MEASURE_UNITS_HPP_INC
#define CW_MEASURE_UNITS_HPP_INC

#include <cstdint>

namespace cw
{
  typedef uint64_t ByteType;
  // exchange numbers to 1 BYTE
  const ByteType ONE_KILO_BYTE = 1024;
  const ByteType ONE_MEGA_BYTE = 1024 * ONE_KILO_BYTE;

  ByteType MegaByte(ByteType mb)
  {
    return mb * ONE_MEGA_BYTE;
  }

  ByteType KiloByte(ByteType kb)
  {
    return kb * ONE_KILO_BYTE;
  }
}

#endif
