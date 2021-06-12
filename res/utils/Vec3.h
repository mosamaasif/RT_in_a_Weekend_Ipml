#pragma once

#include <fstream>
#include <iostream>

#include "Helper.h"

class Vec3 {

public:
	Vec3() : m_Data{ 0.0f, 0.0f, 0.0f } {}
	Vec3(double a, double b, double c) {
		m_Data[0] = a;
		m_Data[1] = b;
		m_Data[2] = c;
	}

public:
	inline friend Vec3 operator+(const Vec3& a, const Vec3& b) { return Vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]); }
	inline friend Vec3 operator-(const Vec3& a, const Vec3& b) { return Vec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]); }

	inline Vec3 operator-() const { return Vec3(-m_Data[0], -m_Data[1], -m_Data[2]); }
	inline friend Vec3 operator*(const Vec3& a, const Vec3& b) { return Vec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]); }
	inline friend Vec3 operator*(double num, const Vec3& v) { return Vec3(num * v[0], num * v[1], num * v[2]); }

	inline friend Vec3 operator*(const Vec3& v, double num) { return num * v; }
	inline friend Vec3 operator/(const Vec3& v, double num) { return (1 / num) * v; }

	Vec3& operator+=(const Vec3& other) {
		m_Data[0] += other[0];
		m_Data[1] += other[1];
		m_Data[2] += other[2];

		return *this;
	}
	Vec3& operator-=(const Vec3& other) {
		m_Data[0] -= other[0];
		m_Data[1] -= other[1];
		m_Data[2] -= other[2];

		return *this;
	}
	Vec3& operator*=(const Vec3& other) {
		m_Data[0] *= other[0];
		m_Data[1] *= other[1];
		m_Data[2] *= other[2];

		return *this;
	}
	Vec3& operator/=(const Vec3& other) {
		m_Data[0] /= other[0];
		m_Data[1] /= other[1];
		m_Data[2] /= other[2];

		return *this;
	}

	double operator[](int i) const { return m_Data[i]; }
	double& operator[](int i) { return m_Data[i]; }

	inline double length() const { return sqrt(lengthSq()); }
	inline double lengthSq() const { return (m_Data[0] * m_Data[0]) + (m_Data[1] * m_Data[1]) + (m_Data[2] * m_Data[2]); }

	inline double dot(const Vec3& b) const {
		return (m_Data[0] * b[0]) + (m_Data[1] * b[1]) + (m_Data[2] * b[2]);
	}
	inline Vec3 cross(const Vec3& b) {
		return Vec3(m_Data[1] * b[2] - m_Data[2] * b[1],
			m_Data[2] * b[0] - m_Data[0] * b[2],
			m_Data[0] * b[1] - m_Data[1] * b[0]
		);
	}
	inline Vec3 unitVector() { return *this / this->length(); }

	inline static Vec3 random() { return Vec3(randDouble(), randDouble(), randDouble()); }
	inline static Vec3 random(double min, double max) { return Vec3(randDouble(min, max), randDouble(min, max), randDouble(min, max)); }

	inline static Vec3 randInUSphere() {
		while (true) {
			Vec3 point = Vec3::random(-1.0f, 1.0f);
			if (point.lengthSq() >= 1.0f)
				continue;
			return point;
		}
	}

	inline static Vec3 randUVector() {
		double a = randDouble(0.0f, 2.0f * pi);
		double z = randDouble(-1.0f, 1.0f);
		double r = sqrt(1.0f - z * z);

		return Vec3(r * cos(a), r * sin(a), z);
	}

	inline static Vec3 randInHemisphere(const Vec3& normal) {
		Vec3 inUSphere = randInUSphere();
		if (inUSphere.dot(normal) > 0.0f)
			return inUSphere;
		else
			return -inUSphere;
	}

	inline static Vec3 randInDisc() {
		while (true) {
			Vec3 rand(randDouble(-1.0, 1.0), randDouble(-1.0, 1.0), 0.0);
			if (rand.lengthSq() >= 1.0)
				continue;
			return rand;
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const Vec3& obj) {
		out << 255.999 * obj[0] << " " << 255.999 * obj[1] << " " << 255.999 * obj[2] << "\n";
		return out;
	}
	friend std::ofstream& operator<<(std::ofstream& out, const Vec3& obj) {
		out << 255.999 * obj[0] << " " << 255.999 * obj[1] << " " << 255.999 * obj[2] << "\n";
		return out;
	}

private:
	double m_Data[3];

};