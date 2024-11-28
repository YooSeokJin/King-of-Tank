module;
#include "Object.h"	

export module CollisionChecker;
namespace CollisionChecker {
	namespace {
		const float epsilon = 0.1f;
		void check_point(std::shared_ptr<Object> obj, float target, float wall, char type);
		void check_mesh(std::shared_ptr<Object> obj, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Mesh>& wall);
	}
	export void isCollid_Static(std::shared_ptr<Object> obj, std::shared_ptr<Static_Object> wall);
}

namespace CollisionChecker {
	namespace {
		void check_point(std::shared_ptr<Object> obj, float target, float wall, char type)
		{
			if (std::abs(target - wall) <= epsilon) {
				obj->set_Collision_State(type);
			}
			obj->reset_Collision_State(type);
		}
		void check_mesh(std::shared_ptr<Object> obj, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Mesh>& wall) {
			std::vector<float> aabb = mesh->get_aabb();
			std::vector<float> aabb_ = wall->get_aabb();
			check_point(obj, aabb[0], aabb_[0], 'x');
			check_point(obj, aabb[1], aabb_[1], 'X');
			check_point(obj, aabb[2], aabb_[2], 'y');
			check_point(obj, aabb[3], aabb_[3], 'Y');
			check_point(obj, aabb[4], aabb_[4], 'z');
			check_point(obj, aabb[5], aabb_[5], 'Z');
		}
	}
	export void isCollid_Static(std::shared_ptr<Object> obj, std::shared_ptr<Static_Object> wall) {
		for (auto& mesh : obj->getMeshes()) {
			check_mesh(obj, mesh, wall->getMeshes()[0]);
		}
	}
}