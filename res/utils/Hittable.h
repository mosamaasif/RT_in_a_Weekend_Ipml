#pragma once

#include "Ray.h"

class Material;

struct HitRecord {
	Vec3 position;
	Vec3 normal;
	double t;
	std::shared_ptr<Material> material;
	bool frontFace;

	inline void setFaceNorm(const Ray& ray, const Vec3& out_norm) {
		//greater, inside ray, else outside
		frontFace = ray.getDirection().dot(out_norm) < 0.0f;
		normal = frontFace ? out_norm : -out_norm;
	}

};

class Hittable {

public:
	virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const = 0;
};