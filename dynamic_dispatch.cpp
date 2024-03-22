// #include "dynamic_dispatch.h"

#undef HWY_TARGET_INCLUDE             // prevents error when re-including
// TODO with gcc using relative file path errors with file not found
//      changing to absolute path compiles but crash on AVX2_simd
#define HWY_TARGET_INCLUDE "dynamic_dispatch.cpp"  // add file relative to root, dont use __FILE__

// Generates code for each enabled target by re-including this source file.
#include <hwy/foreach_target.h>  // IWYU pragma: keep

// END of dynamic dispatch

#include <hwy/highway.h>
#include <hwy/print.h>

// HWY_BEFORE_NAMESPACE();  // or use: HWY_ATTR void MulAddLoop() ...

namespace EXAMPLE_DYNAMIC {
namespace HWY_NAMESPACE {

namespace hn = hwy::HWY_NAMESPACE;  // necessary to avoid ADL error

using T = float;

HWY_ATTR void MulAddLoop(const T* HWY_RESTRICT mul_array,
                const T* HWY_RESTRICT add_array,
                const size_t size, T* HWY_RESTRICT x_array) {
    const hn::ScalableTag<T> d;

    for (size_t i = 0; i < size; i += hn::Lanes(d)) {
        const auto mul = hn::Load(d, mul_array + i);
        const auto add = hn::Load(d, add_array + i);

        // hwy::PrintArray(x_array, size);
        
        auto x = hn::Load(d, x_array + i);
        x = hn::Add(mul, add);
        hn::Store(x, d, x_array + i);
    }
}

} // namespace HWY_NAMESPACE
} // namespace EXAMPLE_DYNAMIC
// HWY_AFTER_NAMESPACE();


// The table of pointers to the various implementations in HWY_NAMESPACE must
// be compiled only once (foreach_target #includes this file multiple times).
// HWY_ONCE is true for only one of these 'compilation passes'.
#if HWY_ONCE

namespace EXAMPLE_DYNAMIC {
HWY_EXPORT(MulAddLoop);

using T = float;

HWY_DLLEXPORT void CallMulAddLoop(const T* HWY_RESTRICT mul_array,
                   const T* HWY_RESTRICT add_array,
                   const size_t size, T* HWY_RESTRICT x_array){

    // This must reside outside of HWY_NAMESPACE because it references (calls the
    // appropriate one from) the per-target implementations there.
    // For static dispatch, use HWY_STATIC_DISPATCH.
    return HWY_DYNAMIC_DISPATCH(MulAddLoop)(mul_array, add_array, size, x_array);
}
} // namespace EXAMPLE_DYNAMIC

#endif  // HWY_ONCE
