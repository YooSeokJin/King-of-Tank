module;
#include "Object.h"	

export module CollisionChecker;
namespace CollisionChecker {
	namespace {
		const float M_epsilon_ = 0.1f;
		void M_checkPoint(std::shared_ptr<Object> obj, float target, float wall, char type);
		void M_checkMesh(std::shared_ptr<Object> obj, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Mesh>& wall);
		bool M_isFalling(std::shared_ptr<Object> obj, float target, float wall);
	}
	export void M_checkCollide(std::shared_ptr<Object> obj, std::shared_ptr<Static_Object> wall);
}

namespace CollisionChecker {
	namespace {
		void M_checkPoint(std::shared_ptr<Object> obj, float target, float wall, char type)
		{
			if (std::abs(target - wall) <= M_epsilon_) {
				obj->setObjectState(type);
			}
			obj->deleteObjectState(type);
		}
		void M_checkMesh(std::shared_ptr<Object> obj, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Mesh>& wall) {
			std::vector<float> aabb = mesh->getAabb();
			std::vector<float> aabb_ = wall->getAabb();

			// Falling üũ: �޽ð� �� ���� �ִ��� Ȯ��
			if (aabb[2] >= aabb_[3]) { // y_min > wall�� y_max -> Falling ����
				obj->setObjectState('F'); // Falling ���� ����
				return; // ������ �浹 �˻� ����
			}

			// Falling ���°� �ƴϸ� �ٸ� ��(x, X, z, Z, Y) �浹 �˻�
			M_checkPoint(obj, aabb[0], aabb_[0], 'x'); // x_min
			M_checkPoint(obj, aabb[1], aabb_[1], 'X'); // x_max
			M_checkPoint(obj, aabb[4], aabb_[4], 'z'); // z_min
			M_checkPoint(obj, aabb[5], aabb_[5], 'Z'); // z_max
			M_checkPoint(obj, aabb[3], aabb_[2], 'Y'); // y_max�� y_min ��
		}

		bool M_isFalling(std::shared_ptr<Object> obj, float target, float wall)
		{
		}

	}
	export void M_checkCollide(std::shared_ptr<Object> obj, std::shared_ptr<Static_Object> wall) {
		for (auto& mesh : obj->getMeshes()) {
			for (auto& staticMesh : wall->getMeshes()) {
				M_checkMesh(obj, mesh, staticMesh);
			}
		}
	}
}