#include "HittableList.h"

HittableList::HittableList(std::shared_ptr<Hittable> obj) { add(obj); }

bool HittableList::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
	HitRecord temp;
	bool anyHit = false;
	double currClosest = t_max;

	for (const auto& obj : m_Objects) {
		if (obj->hit(ray, t_min, currClosest, temp)) {
			anyHit = true;
			currClosest = temp.t;
			rec = temp;
		}
	}

	return anyHit;
}