#pragma once

#include "Vec3.h"

class Ray {

public:
	Ray() = default;
	Ray(Vec3 origin, Vec3 direction) : m_Origin(origin), m_Direction(direction) {}

	inline Vec3 getOrigin() const { return m_Origin; }
	inline Vec3 getDirection() const { return m_Direction; }

	inline Vec3 at(double t) const { return (m_Origin + (t * m_Direction)); }

private:
	Vec3 m_Origin, m_Direction;

};