#pragma once

#include "../../Systems/Physics.h"
#include "PhysicsBody.h"
#include "Shape.h"
#include "../Transform.h"
#include "../../GameObject.h"
class CollisionTest {
public:
	struct Corners2D {
		glm::vec3 TopRight;
		glm::vec3 BottomRight;
		glm::vec3 BottomLeft;
		glm::vec3 TopLeft;

		Corners2D(glm::vec3 center, glm::mat4 rotationMatrix, glm::vec2 offset);
		Corners2D(glm::vec3 tr, glm::vec3 br, glm::vec3 bl, glm::vec3 tl) 
			: TopRight(tr), BottomRight(br), BottomLeft(bl), TopLeft(tl) {};

	};
	struct Corners3D {
		glm::vec3 TopRightFront;
		glm::vec3 TopLeftFront;
		glm::vec3 BottomRightFront;
		glm::vec3 BottomLeftFront;
		glm::vec3 TopRightBack;
		glm::vec3 TopLeftBack;
		glm::vec3 BottomRightBack;
		glm::vec3 BottomLeftBack;

		Corners3D(glm::vec3 center, glm::mat4 rotationMatrix, glm::vec3 offset);
	};
	static bool Test(PhysicsBody* body1, PhysicsBody* body2, glm::vec3* normal, float* depth);

private:
	static void GetMinMax(Corners2D c, glm::vec3 axis, float& min, float& max);
	static void GetMinMax(Corners3D c, glm::vec3 axis, float& min, float& max);

	static bool PointInBounds2D(Corners2D c, glm::vec3 point);
	static bool PointInBounds3D(Corners3D c, glm::vec3 point);

	static bool OBB_OBB_Test(PhysicsBody* body1, PhysicsBody* body2, glm::vec3* normal, float* depth);
	static bool OBC2AA_OBC2AA_Test(PhysicsBody* body1, PhysicsBody* body2);
	static bool OBC_OBC_Test_Internal(PhysicsBody* body1, PhysicsBody* body2);
	static bool OBC_OBC_Test(PhysicsBody* body1, PhysicsBody* body2);
	static bool OBC_OBB_Test(PhysicsBody* body1, PhysicsBody* body2);
	static bool OBB_Circle_Test(PhysicsBody* body1, PhysicsBody* body2);


	static bool CylinderAA_CylinderAA_Test(PhysicsBody* body1, PhysicsBody* body2, glm::vec3* normal, float* depth);
	static bool CylinderAA_Sphere_Test(PhysicsBody* body1, PhysicsBody* body2);
	static bool Sphere_Sphere_Test(PhysicsBody* body1, PhysicsBody* body2);

public:
	static bool PointInOBB(glm::vec3 point, PhysicsBody* body);
};