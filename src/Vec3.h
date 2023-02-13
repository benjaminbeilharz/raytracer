#ifndef __VEC3_H__
#define __VEC3_H__
#include "Common.h"
#include <cmath>
#include <memory>
#include <ostream>
#include <vector>

template<class T, class A = std::allocator<T>>
class Vec3
{
private:
	std::vector<T, A> data;

public:
	Vec3()
	{
		T fillValue = static_cast<T>(0.);
		data = { fillValue, fillValue, fillValue };
	}
	Vec3(const T x, const T y, const T z)
			:data{ x, y, z }
	{
	};
	Vec3(const T v)
			:data{ v, v, v }
	{
	};

	inline static Vec3 Random()
	{
		return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
	}

	inline static Vec3 Random(double min, double max)
	{
		return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
	}

	T GetX() const
	{
		return data[0];
	}
	T GetY() const
	{
		return data[1];
	}
	T GetZ() const
	{
		return data[2];
	}

	T& GetX()
	{
		return data[0];
	}
	T& GetY()
	{
		return data[1];
	}
	T& GetZ()
	{
		return data[2];
	}

	Vec3 operatordouble() const
	{
		Vec3<double> result;
		result.GetX() = static_cast<double>(GetX());
		result.GetY() = static_cast<double>(GetY());
		result.GetZ() = static_cast<double>(GetZ());
		return result;
	}

	Vec3 operatorint() const
	{
		Vec3<int> result;
		result.GetX() = static_cast<int>(GetX());
		result.GetY() = static_cast<int>(GetY());
		result.GetZ() = static_cast<int>(GetZ());
		return result;
	}

	T operator[](const unsigned int i) const
	{
		return data[i];
	}
	T& operator[](const unsigned int i)
	{
		return data[i];
	}

	Vec3& operator+=(const Vec3& v)
	{
		for (unsigned int i = 0; i < data.size(); i++)
		{
			data[i] += v[i];
		}
		return *this;
	}

	Vec3& operator-=(const Vec3& v)
	{
		for (unsigned int i = 0; i < data.size(); i++)
		{
			data[i] -= v[i];
		}
		return *this;
	}

	Vec3& operator*=(const Vec3& v)
	{
		for (unsigned int i = 0; i < data.size(); i++)
		{
			data[i] *= v[i];
		}
		return *this;
	}

	Vec3& operator/=(const Vec3& v)
	{
		for (unsigned int i = 0; i < data.size(); i++)
		{
			data[i] /= v[i];
		}
		return *this;
	}

	friend Vec3 operator+(Vec3 v, const Vec3 other)
	{
		v += other;
		return v;
	}

	friend Vec3 operator-(Vec3 v, const Vec3 other)
	{
		v -= other;
		return v;
	}

	Vec3 operator-() const
	{
		Vec3 result;
		for (int i = 0; i < data.size(); i++)
		{
			result[i] = -data[i];
		}

		return result;
	}

	T operator*(const Vec3& v) const
	{
		return GetX() * v.GetX() + GetY() * v.GetY() + GetZ() * v.GetZ();
	}

	friend Vec3 operator*(Vec3 v, const T f)
	{
		v *= f;
		return v;
	}

	friend Vec3 operator*(const T f, Vec3 v)
	{
		return v * f;
	}

	friend Vec3 operator/(Vec3 v, const T f)
	{
		v /= f;
		return v;
	}

	friend std::ostream& operator<<(std::ostream& os, Vec3 const& v)
	{
		os << "[" << v.GetX() << ", " << v.GetY() << ", " << v.GetZ() << "]";
		return os;
	}

	T Length() const
	{
		T sum{};
		for (auto i : data)
		{
			sum += i * i;
		}

		return std::sqrt(sum);
	}

	T SquaredLength() const
	{
		T sum{};
		for (auto i : data)
		{
			sum += i * i;
		}

		return sum;
	}

	T Dot(const Vec3& other)
	{
		T result = {};
		for (int i = 0; i < data.size(); i++)
		{
			result += data[i] * other[i];
		}
		return result;
	}

	T Distance(const Vec3& v) const
	{
		return (v - *this).Length();
	}

	[[nodiscard]] bool NearZero() const
	{
		const double s = 1e-8;
		return (fabs(data[0]) < s) && (fabs(data[1]) < s) && (fabs(data[2]) < s);
	}
};
template<typename T>
T Dot(const Vec3<T>& v1, const Vec3<T>& v2)
{
	T result = {};
	for (int i = 0; i < 3; i++)
	{
		result += v1[i] * v2[i];
	}
	return result;
}

template<typename T>
Vec3<T> Cross(const Vec3<T>& v1, const Vec3<T>& v2)
{
	T x = v1.GetY() * v2.GetZ() - v1.GetZ() * v2.GetY();
	T y = v1.GetZ() * v2.GetX() - v1.GetX() * v1.GetZ();
	T z = v1.GetX() * v2.GetY() - v1.GetY() * v1.GetX();

	Vec3<T> result{ x, y, z };
	return result;
}

template<typename T>
inline Vec3<T> UnitVector(const Vec3<T> v)
{
	return v / v.Length();
}

template<typename T>
Vec3<T> RandomInUnitSphere()
{
	while (true)
	{
		Vec3<T> p = Vec3<T>::Random(-1, 1);
		if (p.SquaredLength() >= 1)
		{
			continue;
		}
		return p;
	}
}

template<typename T>
Vec3<T> RandomUnitVector()
{
	return UnitVector(RandomInUnitSphere<T>());
}

template<typename T>
Vec3<T> RandomInHemisphere(const Vec3<T>& normal)
{
	Vec3<T> in_unit_sphere = RandomInUnitSphere<T>();
	if (Dot(in_unit_sphere, normal) > .0)
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

template<typename T = double>
Vec3<T> Reflect(const Vec3<T>& v, const Vec3<T>& n)
{
	return v - 2 * Dot(v, n) * n;
}

using vec3 = Vec3<double>;
using vec3i = Vec3<int>;
using point3 = vec3;
using color = vec3;

#endif // __VEC3_H__