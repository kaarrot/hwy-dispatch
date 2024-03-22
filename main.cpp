#include <hwy/highway.h>
#include <hwy/print.h>

#include <vector>
#include <iostream>
#include <numeric>

namespace hn = hwy::HWY_NAMESPACE;

using T = float;

void MulAddLoop(const T* HWY_RESTRICT mul_array,
                const T* HWY_RESTRICT add_array,
                const size_t size, T* HWY_RESTRICT x_array) {
    const hn::ScalableTag<T> d;

    for (size_t i = 0; i < size; i += hn::Lanes(d)) {
        const auto mul = hn::Load(d, mul_array + i);
        const auto add = hn::Load(d, add_array + i);

        hwy::PrintArray(x_array, size);
        
        auto x = hn::Load(d, x_array + i);
        x = hn::Add(mul, add);
        hn::Store(x, d, x_array + i);
  }
}

int main(){
    using namespace std;
    std::vector<float> v_mult(16, 2.0);
    std::vector<float> v_add(16, 1.0);
    std::iota(v_add.begin(), v_add.end(), 1);
    std::vector<float> x_arr(16, 3.0);

    // for(auto i : v_mult) cout << i  << ' ';

    MulAddLoop(&v_mult[0], &v_add[0], x_arr.size(), &x_arr[0]);

    for(auto i : x_arr) cout << i  << ' ';

    std::cout << "DONE" << std::endl;
}
