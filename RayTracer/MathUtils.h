#pragma once

#include <cmath>
#include <limits>
#include <glm/glm.hpp>

inline bool approximately(float value1, float value2, float epsilon = std::numeric_limits<float>::epsilon()) {
	return std::fabs(value1 - value2) < epsilon;
}

inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2) {
	return glm::cross(v1, v2);
}

template <typename T>
inline T lerp(const T& a, const T& b, float t) {
	return (1.0f - t) * a + t * b;
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2) {
	return glm::dot(v1, v2);
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
	return glm::reflect(v, n);
}

inline bool refract(const glm::vec3& v, const glm::vec3& n, float index, glm::vec3& refracted) {
	glm::vec3 nv = glm::normalize(v);
	float dt = glm::dot(nv, n);
	float discriminant = 1.0f - index * index * (1.0f - dt * dt);

	if (discriminant > 0.0f) {
		refracted = index * (nv - n * dt) - n * glm::sqrt(discriminant);
		return true;
	}

	return false;
}

inline float schlick(float cosine, float index) {
	float r0 = (1.0f - index) / (1.0f + index);
	r0 = r0 * r0;
	return r0 + (1.0f - r0) * static_cast<float>(std::pow(1.0 - cosine, 5));
}
