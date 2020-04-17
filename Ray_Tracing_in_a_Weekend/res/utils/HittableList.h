#pragma once

#include "Hittable.h"

#include <vector>
#include <memory>

class HittableList : public Hittable {

public:
	HittableList() = default;
	HittableList(std::shared_ptr<Hittable> obj);

public:
	inline void add(std::shared_ptr<Hittable> obj) { m_Objects.push_back(obj); }
	inline void clear() { m_Objects.clear(); }

	bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;


private:
	std::vector<std::shared_ptr<Hittable>> m_Objects;
};
