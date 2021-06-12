#pragma once

#include "Ray.h"
#include "Hittable.h"

class Material {

public:
	virtual bool scatter(const Ray& inRay, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;

protected:
	inline Vec3 reflect(const Vec3& v, const Vec3& normal) const {
		return v - (2.0f * v.dot(normal) * normal);
	}

	Vec3 refract(const Vec3& uv, const Vec3& normal, double etaiOveretat) const {
		double cosTheta = (-uv).dot(normal);
		Vec3 outParallel = etaiOveretat * (uv + cosTheta * normal);
		Vec3 outPerp = -(sqrt(1.0f - outParallel.lengthSq()) * normal);
		return outParallel + outPerp;
	}

	double schlick(double cosine, double refIdx) const {
		double r0 = (1.0f - refIdx) / (1.0f + refIdx);
		r0 = r0 * r0;
		return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
	}
};