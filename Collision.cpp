#include "Collision.h"

Collision::Collision()
{
}
void Collision::set_aabb(const std::vector<float>& aabb_)
{
    aabb = aabb_;
}

const std::vector<float>& Collision::get_aabb()
{
    return aabb;
}
