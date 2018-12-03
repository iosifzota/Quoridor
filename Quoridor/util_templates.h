#pragma once

template<typename T>
struct ignore_deduction {
	using type = T;
};

template<typename T>
using ignore_deduction_t = typename ignore_deduction<T>::type;