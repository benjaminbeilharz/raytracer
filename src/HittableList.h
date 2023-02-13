#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__

#include "Hittable.h"
#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable
{
public:
	HittableList()
	{
	}
	explicit HittableList(shared_ptr<Hittable> object)
	{
		add(object);
	}

	void clear()
	{
		objects.clear();
	}
	void add(shared_ptr<Hittable> object)
	{
		objects.push_back(object);
	}

	virtual bool Hit(const ray& r, double tMin, double tMax, HitRecord& rec) const override;
	std::vector<shared_ptr<Hittable>> objects;
};

inline bool HittableList::Hit(const ray& r, double tMin, double tMax, HitRecord& rec) const
{
	HitRecord tmpRec;
	bool hitAnything = false;
	double clostestSoFar = tMax;

	for (const auto& object : objects)
	{
		if (object->Hit(r, tMin, clostestSoFar, tmpRec))
		{
			hitAnything = true;
			clostestSoFar = tmpRec.t;
			rec = tmpRec;
		}
	}
	return hitAnything;
}
#endif // __HITTABLE_LIST_H__