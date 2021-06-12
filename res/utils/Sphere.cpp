#include "Sphere.h"

Sphere::Sphere(Vec3 center, double radius, std::shared_ptr<Material> material): m_Center(center), m_Radius(radius), m_Material(material) {}

bool Sphere::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
	//a = r.origin . r.origin,  b = 2 * r.origin . r.direction,  c = r.direction . r.direction
	Vec3 acDiff = ray.getOrigin() - m_Center;
	double a = ray.getDirection().lengthSq();

	double h_b = acDiff.dot(ray.getDirection());
	double c = acDiff.lengthSq() - (m_Radius * m_Radius);
	double disc = (h_b * h_b) - (a * c);

	if (disc > 0.0f) {
		double t = (-h_b - sqrt(disc)) / a;
		if (t > t_min && t < t_max) {
			rec.t = t;
			rec.position = ray.at(t);
			rec.material = m_Material;
			Vec3 out_norm = (rec.position - m_Center) / m_Radius;
			rec.setFaceNorm(ray, out_norm);

			return true;
		}

		t = (-h_b + sqrt(disc)) / a;
		if (t > t_min && t < t_max) {
			rec.t = t;
			rec.position = ray.at(t);
			rec.material = m_Material;
			Vec3 out_norm = (rec.position - m_Center) / m_Radius;
			rec.setFaceNorm(ray, out_norm);

			return true;
		}
	}
	return false;
}