#include "Collision.h"

Collision::Collision()
{
}
void Collision::setAabb(const std::vector<float>& aabb)
{
    aabb_ = aabb;
}

std::vector<float> Collision::getAabb() const
{
    return aabb_;
}
