
#include "Plane.h"

bool Plane::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
    float t;
    if (!Raycast(ray, m_transform.position, m_transform.GetUp(), minDistance, maxDistance, t)) {
        return false;
    }

    raycastHit.distance = t;
    raycastHit.normal = glm::normalize(m_transform.GetUp());
    raycastHit.point = ray.At(t);
    raycastHit.material = GetMaterial();

    return true;
}

bool Plane::Raycast(const ray_t& ray, const glm::vec3& point, const glm::vec3& normal, float minDistance, float maxDistance, float& t)
{
    float denominator = dot(ray.direction, normal);
    if (approx(denominator, 0)) {
        return false;
    }
    t = dot(point - ray.origin, normal);
    if (t < 0) {
        return false;
    }
    if (t <= minDistance || t >= maxDistance) return false;
    return true;
}
