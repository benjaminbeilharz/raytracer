//
// Created by Ben on 01.02.23.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "Hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "Ray.h"
#include <ostream>

color RayColor(const ray& r, const Hittable& world, int depth)
{
	HitRecord record;

	if (depth <= 0)
		return color(0.);

	if (world.Hit(r, 0.001, infinity, record))
	{
		ray scattered;
		color attenuation;
		if (record.p_Material->Scatter(r, record, attenuation, scattered))
			return attenuation * RayColor(scattered, world, depth - 1);

		return color(0.);
	}

	vec3 unitDirection = UnitVector(r.GetDirection());
	double t = .5 * (unitDirection.GetY() + 1.);
	return (1. - t) * color(1.) + t * color(.5, .7, .1);
}

inline void WriteColor(std::ostream& out, color pixelColor, int samplesPerPixel)
{
	double r = pixelColor.GetX();
	double g = pixelColor.GetY();
	double b = pixelColor.GetZ();

	double scale = 1. / samplesPerPixel;
	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);

	out << static_cast<int>(256 * Clamp(r, .0, .999)) << ' ' << static_cast<int>(256 * Clamp(g, .0, .999)) << ' '
		<< static_cast<int>(256 * Clamp(b, .0, .999)) << '\n';
}

#endif //RAYTRACING_COLOR_H
