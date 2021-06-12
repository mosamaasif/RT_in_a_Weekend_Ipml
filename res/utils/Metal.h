#pragma once

#include "Material.h"

class Metal : public Material {

public:
	Metal(const Vec3& a, double fuzz) : m_Albedo(a), m_Fuzz(fuzz < 1.0f ? 0.0f : 1.0f) {}

	bool scatter(const Ray& inRay, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override {
		Vec3 reflected = reflect(inRay.getDirection().unitVector(), rec.normal);
		scattered = Ray(rec.position, reflected + m_Fuzz * Vec3::randInUSphere());
		attenuation = m_Albedo;
		return scattered.getDirection().dot(rec.normal) > 0.0f;
	}

private:
	Vec3 m_Albedo;
	double m_Fuzz;
};