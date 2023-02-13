#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Common.h"
#include "Hittable.h"
#include "Ray.h"
class Sphere : public Hittable {
public:
  Sphere() {}
  Sphere(point3 center, double radius, shared_ptr<Material> m)
      : center(center), radius(radius), p_Mat(m) {}

  virtual bool Hit(const ray &r, double tMin, double tMax,
                   HitRecord &rec) const override;

  point3 center;
  double radius;
  shared_ptr<Material> p_Mat;
};
#endif // __SPHERE_H__

inline bool Sphere::Hit(const ray &r, double tMin, double tMax,
                        HitRecord &rec) const {
  vec3 oc = r.GetOrigin() - center;
  double a = r.GetDirection().SquaredLength();
  double halfB = oc.Dot(r.GetDirection());
  double c = oc.SquaredLength() - radius * radius;

  double discriminant = halfB * halfB - a * c;
  if (discriminant < 0) {
    return false;
  }
  double sqrtd = sqrt(discriminant);

  // find nearest in range
  double root = (-halfB - sqrtd) / a;
  if (root < tMin || tMax < root) {
    root = (-halfB + sqrtd) / a;
    if (root < tMin || tMax < root) {
      return false;
    }
  }

  rec.t = root;
  rec.p = r.At(rec.t);
  vec3 outwardNormal = (rec.p - center) / radius;
  rec.setFaceNormal(r, outwardNormal);
  rec.p_Material = p_Mat;
  return true;
}
