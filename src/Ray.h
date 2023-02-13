#ifndef __RAY_H__
#define __RAY_H__

#include "Vec3.h"
#include <ostream>

template<class T>
class Ray
{
private:
	Vec3<T> origin_;
	Vec3<T> direction_;

public:
	Ray()
	{
		Vec3 origin_ = Vec3<T>();
		Vec3 direction_ = Vec3<T>();
	};

	Ray(const Vec3<T>& origin, const Vec3<T>& direction)
			:origin_(origin), direction_(direction)
	{
	};
	Vec3<T> GetOrigin() const
	{
		return origin_;
	};
	Vec3<T> GetDirection() const
	{
		return direction_;
	};

	Vec3<T> At(const double& t) const
	{
		return origin_ + t * direction_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Ray& r)
	{
		os << "Origin: " << r.GetOrigin() << "\n"
		   << "Direction: " << r.GetDirection();
		return os;
	}
};

using ray = Ray<double>;
using i_ray = Ray<int>;

#endif // __RAY_H__