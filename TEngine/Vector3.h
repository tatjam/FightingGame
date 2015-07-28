#pragma once

template<class T>
class Vector3
{
public:
	T x;
	T y;
	T z;

	T getX(){ return x; };
	T getY(){ return y; };
	T getZ(){ return z; };

	void setVector(Vector3<T> v){ x = v.x; y = v.y; z = v.z; };

	Vector3()
	{
	};

	Vector3(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};
};

