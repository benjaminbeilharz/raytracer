#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Common.h"
#include "Ray.h"
#include "Vec3.h"

class Camera
{
public:
	Camera()
	{
		double aspectRatio = 16. / 9.;
		double viewportHeight = 2.;
		double viewportWidth = aspectRatio * viewportHeight;
		double focalLength = 1.;

		origin = point3(0, 0, 0);
		horizontal = vec3(viewportWidth, 0., 0.);
		vertical = vec3(0., viewportHeight, 0.);
		lowerLeftCorner = origin - horizontal / 2. - vertical / 2. - vec3(0., 0., focalLength);
	}

	Ray<double> GetRay(double u, double v) const
	{
		return Ray<double>(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

private:
	point3 origin;
	point3 lowerLeftCorner;
	vec3 horizontal;
	vec3 vertical;
};
#endif // __CAMERA_H__