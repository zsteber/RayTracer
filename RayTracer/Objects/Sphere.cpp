#include "Sphere.h"

bool Sphere::Hit(const Ray& r, float tMin, float tMax, RaycastHit& hit)
{
    glm::vec3 oc = r.origin - m_center;
    float a = glm::dot(r.direction, r.direction);
    float b = 2 * glm::dot(r.direction, oc);
    float c = glm::dot(oc, oc) - (m_radius * m_radius);

    float discriminant = (b * b) - (4 * a * c);

    return discriminant >= 0;
}