#include "Camera.h"
#include "Common.h"
#include "Color.h"
#include "HittableList.h"
#include "Material.h"
#include "Sphere.h"
#include "Vec3.h"
#include <iostream>

using std::cerr;
using std::cout;

int main()
{
	// image
	const double aspectRatio = 16. / 9.;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
	const int samplesPerPixel = 100;
	const int maxDepth = 50;

	// world
	HittableList world;

	auto materialGround = make_shared<Lambertian>(color(.8, .8, .0));
	auto materialCenter = make_shared<Lambertian>(color(.7, .3, .3));
	auto materialLeft = make_shared<Metal>(color(.8));
	auto materialRight = make_shared<Metal>(color(.8, .6, .2));

	world.add(make_shared<Sphere>(point3(0, -100.5, -1.0), 100., materialGround));
	world.add(make_shared<Sphere>(point3(0, .0, -1.), .5, materialCenter));
	world.add(make_shared<Sphere>(point3(-1.0, .0, -1.0), .5, materialLeft));
	world.add(make_shared<Sphere>(point3(1.0, .0, -1.0), .5, materialRight));

	// camera
	Camera camera;

	// render

	cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

	for (int j = imageHeight - 1; j >= 0; --j)
	{
		cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < imageWidth; ++i)
		{
			color pixelColor(0.);
			for (int s = 0; s < samplesPerPixel; s++)
			{
				double u = (i + RandomDouble()) / (imageWidth - 1);
				double v = (j + RandomDouble()) / (imageHeight - 1);
				ray r = camera.GetRay(u, v);
				pixelColor += RayColor(r, world, maxDepth);
			}
			WriteColor(std::cout, pixelColor, samplesPerPixel);
		}
	}

	cerr << "\nDone.\n";
}