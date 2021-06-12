#pragma once

#include "Hittable.h"

class Sphere : public Hittable {

public:
	Sphere() = default;
	Sphere(Vec3 center, double radius, std::shared_ptr<Material> material);

public:
	bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const override;

private:
	Vec3 m_Center;
	double m_Radius;

	std::shared_ptr<Material> m_Material;
};