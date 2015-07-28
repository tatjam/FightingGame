#pragma once
template <class T>
class Vector2
{
public:
	T x;
	T y;

	void setVector(T newV){x = newV.x; y = newV.y;};
	Vector2();
	Vector2(T x, T y);
};

