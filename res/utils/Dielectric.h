#pragma once

#include "Material.h"

class Dielectric : public Material {

public:
	Dielectric(double ri) : m_RefIdx(ri) {}

	bool scatter(const Ray& inRay, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override {
		attenuation = Vec3(1.0f, 1.0f, 1.0f);

		double etaiOverEtat = 0.0f;
		if (rec.frontFace)
			etaiOverEtat = 1.0f / m_RefIdx;
		else
			etaiOverEtat = m_RefIdx;

		Vec3 unitDirection = inRay.getDirection().unitVector();
		double cosTheta = ffmin((-unitDirection).dot(rec.normal), 1.0f);
		double sinTheta = sqrt(1.0f - cosTheta * cosTheta);
		if (etaiOverEtat * sinTheta > 1.0f) {
			Vec3 reflected = reflect(unitDirection, rec.normal);
			scattered = Ray(rec.position, reflected);

			return true;
		}
		double reflectProb = schlick(cosTheta, etaiOverEtat);
		if (randDouble() < reflectProb) {
			Vec3 reflected = reflect(unitDirection, rec.normal);
			scattered = Ray(rec.position, reflected);

			return true;
		}

		Vec3 refracted = refract(unitDirection, rec.normal, etaiOverEtat);
		scattered = Ray(rec.position, refracted);

		return true;
	}

private:
	double m_RefIdx;

};