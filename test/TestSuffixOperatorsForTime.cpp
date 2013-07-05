#include <cw/core/Timer.hpp>

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

using namespace igloo;

// TODO enable when VC support user defined literals
// Describe(suffix_operators)
// {
//   const double DELTA = 1e-12;
//   Spec(ns)
//   {
//     double t = 1_nanosec;
//     double u = 945_nanosec;
//     AssertThat( t, EqualsWithDelta( 1e-9, DELTA ) );
//     AssertThat( u, EqualsWithDelta( 945 * 1e-9, DELTA ) );
//   }
// 
//   Spec(us)
//   {
//     double t  = 1_microsec;
//     double u = 546_microsec;
//     AssertThat( t, EqualsWithDelta( 1e-6, DELTA ) );
//     AssertThat( u, EqualsWithDelta( 546 * 1e-6, DELTA ) );
//   }
// 
//   Spec(ms)
//   {
//     double t = 1_millisec;
//     double u = 127_millisec;
//     AssertThat( t, EqualsWithDelta( 1e-3, DELTA ) );
//     AssertThat( u, EqualsWithDelta( 127 * 1e-3, DELTA ) );
//   }
// 
//   Spec(sec)
//   {
//     double t = 1_sec;
//     double u = 14_sec;
//     AssertThat( t, EqualsWithDelta( 1, DELTA ) );
//     AssertThat( u, EqualsWithDelta( 14, DELTA ) );
//   }
// 
//   Spec(mixed)
//   {
//     AssertThat( 1000000000_nanosec, EqualsWithDelta( 1_sec, DELTA ) );
//     AssertThat( 1000000000_nanosec, EqualsWithDelta( 1000_millisec, DELTA ) );
//     AssertThat( 1000000000_nanosec, EqualsWithDelta( 1000000_microsec, DELTA ) );
// 
//     AssertThat( 1000000_nanosec, EqualsWithDelta( 1_millisec, DELTA ) );
//     AssertThat( 1000000_nanosec, EqualsWithDelta( 1000_microsec, DELTA ) );
// 
//     AssertThat( 1000_nanosec, EqualsWithDelta( 1_microsec, DELTA ) );
//   }
// };
