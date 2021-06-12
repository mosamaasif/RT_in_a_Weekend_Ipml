#pragma once

#include "Helper.h"

class Camera {

public:
	Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 vUp, double vFov, double aspectRatio, double apurture, double focusDist) :m_Origin(lookFrom) {

		m_LensRad = apurture / 2.0;

		double halfHeight = tan(degToRad(vFov) / 2.0f);
		double halfWidth = aspectRatio * halfHeight;

		m_W = (lookFrom - lookAt).unitVector();
		m_U = vUp.cross(m_W).unitVector();
		m_V = m_W.cross(m_U);

		m_LowerLeft = m_Origin - (halfWidth * focusDist * m_U) - (halfHeight * focusDist * m_V) - (focusDist * m_W);
		m_Horizontal = 2.0f * halfWidth * focusDist * m_U;
		m_Vertical = 2.0f * halfHeight * focusDist * m_V;
	}

	inline Ray getRay(double s, double t) const { 
		Vec3 rand = m_LensRad * Vec3::randInDisc();
		Vec3 off = m_U * rand[0] + m_V * rand[1];
		return  Ray(m_Origin + off, m_LowerLeft + (s * m_Horizontal) + (t * m_Vertical) - m_Origin - off); 
	}

private:
	Vec3 m_Origin, m_LowerLeft, m_Horizontal, m_Vertical;
	Vec3 m_U, m_V, m_W;
	double m_LensRad;
};