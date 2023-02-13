//
// Created by Ben on 29.01.23.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "Common.h"
#include "Hittable.h"
#include "Ray.h"
#include "Vec3.h"

class Material
{
public:
	virtual bool Scatter(const ray& rIn, const HitRecord& record,
			color& attenuation, ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	color albedo;
	explicit Lambertian(const color& a)
			:albedo(a)
	{
	};
	bool Scatter(const ray& rIn, const HitRecord& record,
			color& attenuation, ray& scattered) const override
	{
		vec3 scatterDirection = record.normal + RandomUnitVector<double>();

		if (scatterDirection.NearZero())
			scatterDirection = record.normal;

		scattered = ray(record.p, scatterDirection);
		attenuation = albedo;
		return true;
	}
};

class Metal : public Material
{
public:
	color albedo;
	Metal(const color& a)
			:albedo(a)
	{
	}

	bool Scatter(const ray& rIn, const HitRecord& record, color& attenuation,
			ray& scattered) const override
	{
		vec3 reflected = Reflect(UnitVector(rIn.GetDirection()), record.normal);
		scattered = ray(record.p, reflected);
		attenuation = albedo;
		return (Dot(scattered.GetDirection(), record.normal) > 0);
	}
};

#endif // RAYTRACING_MATERIAL_H
