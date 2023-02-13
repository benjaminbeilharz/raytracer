#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "Ray.h"
#include "Vec3.h"
#include <memory>

class Material;

struct HitRecord
{
    point3 p;
    vec3 normal;
    std::shared_ptr<Material> p_Material;
    double t;
    bool frontFace;

    inline void setFaceNormal(const ray &r, const vec3 &outwardNormal)
    {
        frontFace = r.GetDirection().Dot(outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
  public:
    virtual bool Hit(const ray &r, double tMin, double tMax, HitRecord &rec) const = 0;
};

#endif // __HITTABLE_H__