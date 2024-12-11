module;
#include "Object.h"	
#include "algorithm"
#include "Enemy.h"
export module CollisionChecker;
namespace CollisionChecker {
    namespace {
        const float M_epsilon_ = 0.1f;
        const float M_bulletEpsion = 0.3f;
    }
	export void M_checkCollide(std::shared_ptr<Object> obj, 
        const std::vector<std::shared_ptr<Static_Object>>& walls,
        const std::vector<std::shared_ptr<Object>>& enermy);

    export void M_checkFalling(std::shared_ptr<Object> obj, 
        const std::vector<std::shared_ptr<Static_Object>>& walls);

    export void M_checkBullet(std::shared_ptr<Object> bullet, 
        const std::vector<std::shared_ptr<Static_Object>>& walls, 
        const std::vector<std::shared_ptr<Object>>& enermy);
}

namespace CollisionChecker {
	namespace {

	}
    export void M_checkCollide(std::shared_ptr<Object> obj, 
        const std::vector<std::shared_ptr<Static_Object>>& walls,
        const std::vector<std::shared_ptr<Object>>& enermy) {
        if (!obj->isOnGround()) return;
        bool isColliding = false;
        for (auto& mesh : obj->getMeshes()) {
            std::vector<float> meshAabb = mesh->getAabb();
            for (auto& wall : walls) {
                for (auto& staticMesh : wall->getMeshes()) {
                    std::vector<float> staticAabb = staticMesh->getAabb();
                    bool yOverlap = !(staticAabb[3] < meshAabb[2] || meshAabb[3] < staticAabb[2]);
                    if (!yOverlap) continue;
                    bool xOverlap = !(staticAabb[1] < meshAabb[0] || meshAabb[1] < staticAabb[0]);
                    if (!xOverlap) continue;
                    bool zOverlap = !(staticAabb[5] < meshAabb[4] || meshAabb[5] < staticAabb[4]);
                    
                    if (zOverlap) {
                        isColliding = true;
                        bool x = staticAabb[0] <= meshAabb[0] && meshAabb[0] <= staticAabb[1];
                        bool X = staticAabb[0] <= meshAabb[1] && meshAabb[1] <= staticAabb[1];
                        if (x)
                            obj->setObjectState('x');
                        if (X)
                            obj->setObjectState('X');

                        bool z = staticAabb[4] <= meshAabb[4] && meshAabb[4] <= staticAabb[5];
                        bool Z = staticAabb[4] <= meshAabb[5] && meshAabb[5] <= staticAabb[5];
                        if (z)
                            obj->setObjectState('z');
                        if (Z)
                            obj->setObjectState('Z');
                        return;
                        }
                    }
                }
            }
        obj->deleteObjectState('x');
        obj->deleteObjectState('X');
        obj->deleteObjectState('z');
        obj->deleteObjectState('Z');
    }
    export void M_checkFalling(std::shared_ptr<Object> obj, const std::vector<std::shared_ptr<Static_Object>>& walls) {
        std::vector<float> minys;
        for (auto& mesh : obj->getMeshes()) {
            std::vector<float> aabb = mesh->getAabb();
            minys.push_back(aabb[2]);
        }
        bool isOnGround = false;
        std::sort(minys.begin(), minys.end());
        glm::vec3 location = obj->getPosition();
        for (auto& wall : walls) {
            for (auto& mesh : wall->getMeshes()) {
                std::vector<float> aabb_ = mesh->getAabb();
                if (location.x < aabb_[0]) continue;
                if (aabb_[1] < location.x) continue;
                if (location.z < aabb_[4]) continue;
                if (aabb_[5] < location.z) continue;

                if (aabb_[2] + M_epsilon_ <= minys[0] && minys[0] <= aabb_[3] + M_epsilon_) {
                    isOnGround = true;
                }
            }
        }
        if (isOnGround) {
            obj->setObjectState('O');
            obj->deleteObjectState('F');
        }
        else {
            obj->setObjectState('F');
            obj->deleteObjectState('O');
        }
    }
    void M_checkBullet(std::shared_ptr<Object> bullet, 
        const std::vector<std::shared_ptr<Static_Object>>& walls,
        const std::vector<std::shared_ptr<Object>>& enermy)
    {
        glm::vec3 location = bullet->getPosition();
        std::vector<float> bulletAabb = bullet->getMeshes()[0]->getAabb();
        for (auto& obj : enermy) {
            if (bullet->hasState('b')) break;
            bool overlap = false;
            int index = -1;
            if (obj->tag == 'P') continue;
            for (auto& mesh : obj->getMeshes()) {
                ++index;
                std::vector<float> aabb = mesh->getAabb();

                if (aabb[3] < bulletAabb[2] || bulletAabb[3] < aabb[2]) continue;
                if (aabb[1] < bulletAabb[0] || bulletAabb[1] < aabb[0]) continue;
                if (aabb[5] < bulletAabb[4] || bulletAabb[5] < aabb[4]) continue;

                overlap = true;
                break;
            }
            if (overlap) {
                auto enemy = std::dynamic_pointer_cast<Enemy>(obj);
                obj->setObjectState('B');
                bullet->setObjectState('b');
                break;
            }
        }
        for (auto& wall : walls) {
            for (auto& mesh : wall->getMeshes()) {
                std::vector<float> aabb = mesh->getAabb();
                if (aabb[0] - M_bulletEpsion > location.x) continue;
                if (aabb[1] + M_bulletEpsion < location.x) continue;
                if (aabb[2] - M_bulletEpsion > location.y) continue;
                if (aabb[3] + M_bulletEpsion < location.y) continue;
                if (aabb[4] - M_bulletEpsion > location.z) continue;
                if (aabb[5] + M_bulletEpsion < location.z) continue;

                bullet->setObjectState('O');
                return;
            }
        }
    }
}