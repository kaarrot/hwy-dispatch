#ifndef DYNAMIC_DIPATCH_H_
#define DYNAMIC_DIPATCH_H_

#include "hwy/base.h"  // HWY_RESTRICT

namespace EXAMPLE_DYNAMIC {
using T = float;
HWY_DLLEXPORT void CallMulAddLoop(const T* HWY_RESTRICT mul_array,
                                  const T* HWY_RESTRICT add_array,
                                  const size_t size, T* HWY_RESTRICT x_array);
}  // namespace EXAMPLE_DYNAMIC

#endif  // DYNAMIC_DIPATCH_H_