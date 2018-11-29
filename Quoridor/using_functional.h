#pragma once

#include <functional>

using std::function;

template <typename T>
using ref_wrapper = std::reference_wrapper<T>;