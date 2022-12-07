#pragma once
#include <glm/gtx/norm.hpp>
#include <glm/glm.hpp>
#include <cstdlib>
#include <algorithm>

inline float random01()
{
	return rand() / (float)RAND_MAX;
}

inline float random(float min, float max)
{
	if (min > max) std::swap(min, max);

	return min + (max - min) * random01();
}

inline glm::vec3 randomInUnitSphere()
{
    glm::vec3 point;
    do
    {
        point = glm::vec3{ random(-1, 1), random(-1, 1), random(-1, 1) };

    } while (glm::length2(point) >= 1);

    return point;
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


inline glm::vec3 reflect(glm::vec3 v, glm::vec3 n)
{
    return v - (n * dot(n, v)) * 2.0f;
}

template <typename T>
inline T lerp(T a, T b, float t)
{
	return (a * (1.0f - t)) + (b * t);
}