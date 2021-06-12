#pragma once

#include "Material.h"

class Lambertian : public Material {

public:
	Lambertian(const Vec3& a) : m_Albedo(a) {}

	bool scatter(const Ray& inRay, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override {
		Vec3 scatter_direction = rec.normal + Vec3::randUVector();
		scattered = Ray(rec.position, scatter_direction);
		attenuation = m_Albedo;
		return true;

		//always scatters, but attenuates....can also be never attenuate, but scatter only a fraction of the incident rays
	}

private:
	Vec3 m_Albedo;
};