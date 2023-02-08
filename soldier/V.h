#pragma once

template <typename T>
struct V2 {
	T x;
	T y;

	V2() : x(), y() {}
	V2(T m, T n) : x(m), y(n) {}
};

using V2i = V2<int>;
using V2u = V2<unsigned int>;
using V2f = V2<float>;


template <typename T>
struct V3 {
	T x;
	T y;
	T z;

	V3() : x(), y(), z() {}
	V3(T a, T b, T c) : x(a), y(b), z(c) {}
};

using V3i = V3<int>;
using V3u = V3<unsigned int>;
using V3f = V3<float>;