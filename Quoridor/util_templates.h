#pragma once

template<typename T>
struct ignore_deduction {
	using type = T;
};

template<typename T>
using ignore_deduction_t = typename ignore_deduction<T>::type;

template <typename T>
struct Err {
	Err(const T& value) :
		m_value{ value }
	{}

	T& value() { return m_value; }
	T m_value;
};