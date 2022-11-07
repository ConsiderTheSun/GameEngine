#include "CollisionTest.h"

bool CollisionTest::Test(PhysicsBody* body1, PhysicsBody* body2, glm::vec3* normal, float* depth) {
	// checks if layers interact
	int layer1 = body1->gameObject->GetLayer();
	int layer2 = body2->gameObject->GetLayer();
	if (!Physics::GetInstance()->LayerInteraction(layer1, layer2)) {
		return false;
	}

	
	// body 1 is OBB 
	if (body1->GetShapeType() == Shape::ShapeType::OBB && body2->GetShapeType() == Shape::ShapeType::OBB) {
		return OBB_OBB_Test(body1, body2, normal, depth);
	}
	if (body1->GetShapeType() == Shape::ShapeType::OBB && body2->GetShapeType() == Shape::ShapeType::OBC) {
		return OBC_OBB_Test(body2, body1);
	}
	if (body1->GetShapeType() == Shape::ShapeType::OBB && body2->GetShapeType() == Shape::ShapeType::OBC2AA) {
		return OBC_OBB_Test(body2, body1);
	}
	if (body1->GetShapeType() == Shape::ShapeType::OBB && body2->GetShapeType() == Shape::ShapeType::Circle) {
		return OBB_Circle_Test(body1, body2);
	}

	// body 1 is OBC 
	if (body1->GetShapeType() == Shape::ShapeType::OBC && body2->GetShapeType() == Shape::ShapeType::OBB) {
		return OBC_OBB_Test(body1, body2);
	}
	if (body1->GetShapeType() == Shape::ShapeType::OBC && body2->GetShapeType() == Shape::ShapeType::OBC) {
		return OBC_OBC_Test(body1, body2);
	}
	if (body1->GetShapeType() == Shape::ShapeType::OBC && body2->GetShapeType() == Shape::ShapeType::OBC2AA) {
		return OBC_OBC_Test(body1, body2);
	}


	// body 1 is OBC2AA 
	if (body1->GetShapeType() == Shape::ShapeType::OBC2AA && body2->GetShapeType() == Shape::ShapeType::OBB) {
		return OBC_OBB_Test(body1, body2);
	}
	if (body1->GetShapeType() == Shape::ShapeType::OBC2AA && body2->GetShapeType() == Shape::ShapeType::OBC) {
		return OBC_OBC_Test(body1, body2);
	}
	if (body1->GetShapeType() == Shape::ShapeType::OBC2AA && body2->GetShapeType() == Shape::ShapeType::OBC2AA) {
		return OBC2AA_OBC2AA_Test(body1, body2);
	}

	
	

	return false;
}



void CollisionTest::GetMinMax(Corners2D c, glm::vec3 axis, float& min, float& max) {
	min = glm::dot(c.TopRight, axis);
	max = min;


	glm::vec3 otherCorners[] = { c.BottomRight,c.BottomLeft,c.TopLeft };
	for (auto corner : otherCorners) {
		float cornerValue = glm::dot(corner, axis);
		if (cornerValue < min) min = cornerValue;
		if (cornerValue > max) max = cornerValue;
	}
}

void CollisionTest::GetMinMax(Corners3D c, glm::vec3 axis, float& min, float& max) {
	min = glm::dot(c.TopRightFront, axis);
	max = min;


	glm::vec3 otherCorners[] = { c.TopLeftFront, c.BottomRightFront,
		c.BottomLeftFront,c.TopRightBack,c.TopLeftBack,
		c.BottomRightBack,c.BottomLeftBack };

	for (auto corner : otherCorners) {
		float cornerValue = glm::dot(corner, axis);
		if (cornerValue < min) min = cornerValue;
		if (cornerValue > max) max = cornerValue;
	}
}

bool CollisionTest::PointInBounds2D(Corners2D c, glm::vec3 point) {

	glm::vec3 axes[2] = {
		c.TopLeft - c.TopRight,
		c.TopLeft - c.BottomLeft
	};
	for (glm::vec3 axis : axes) {
		float min = 0.0;
		float max = 0.0;
		GetMinMax(c, axis, min, max);
		float pointPos = glm::dot(point, axis);
		if (pointPos < min || pointPos > max) {
			return false;
		}
	}

	return true;
}

bool CollisionTest::PointInBounds3D(Corners3D c, glm::vec3 point) {
	//glm::vec3 center1 = t1->GetWorldPosition();
	//glm::vec3 center2 = t2->GetWorldPosition();

	glm::vec3 ax = glm::normalize(c.TopLeftFront - c.TopRightFront);
	glm::vec3 ay = glm::normalize(c.TopLeftFront - c.BottomLeftFront);
	glm::vec3 az = glm::normalize(c.TopLeftFront - c.TopLeftBack);

	for (glm::vec3 axis : { ax, ay, az }) {
		float min1 = 0.0;
		float max1 = 0.0;
		GetMinMax(c, axis, min1, max1);

		float centerProjection = glm::dot(point, axis);

		if (max1 < centerProjection || centerProjection < min1)
			return false;
	}
	return true;
}


bool CollisionTest::OBB_OBB_Test(PhysicsBody* body1, PhysicsBody* body2, glm::vec3* normal, float* depth) {

	*depth = FLT_MAX;

	Transform* t1 = body1->gameObject->GetComponent<Transform>();
	Transform* t2 = body2->gameObject->GetComponent<Transform>();

	glm::vec2 sideLength1 = 0.5f * t1->GetWorldScale();
	glm::vec2 sideLength2 = 0.5f * t2->GetWorldScale();

	Corners2D corners1(t1->GetWorldPosition(), t1->GetRotationMatrix(), sideLength1);
	Corners2D corners2(t2->GetWorldPosition(), t2->GetRotationMatrix(), sideLength2);

	glm::vec3 a1x = glm::normalize(corners1.TopLeft - corners1.TopRight);
	glm::vec3 a1y = glm::normalize(corners1.TopLeft - corners1.BottomLeft);
	glm::vec3 a2x = glm::normalize(corners2.TopLeft - corners2.TopRight);
	glm::vec3 a2y = glm::normalize(corners2.TopLeft - corners2.BottomLeft);

	glm::vec3 axes[] = { a1x, a1y, a2x, a2y };

	for (glm::vec3 axis : axes) {
		float min1 = 0.0;
		float max1 = 0.0;
		GetMinMax(corners1, axis, min1, max1);

		float min2 = 0.0;
		float max2 = 0.0;
		GetMinMax(corners2, axis, min2, max2);
		if (max1 <= min2 || max2 <= min1)
			return false;


		float axisDepth = std::min(max2-min1, max1-min2);
		if (axisDepth < *depth) {
			*depth = axisDepth;
			*normal = axis;
		}
	}


	*depth /= normal->length();
	*normal = glm::normalize(*normal);
	if (glm::dot(*normal, t2->GetPosition() - t1->GetPosition()) < 0) {
		*normal = -*normal;
	}

	return true;

	/*
	// AABB
	glm::vec2 min1 = t1->GetWorldPosition() - glm::vec3(sideLenght1, 0);
	glm::vec2 max1 = t1->GetWorldPosition() + glm::vec3(sideLenght1, 0);
	glm::vec2 min2 = t2->GetWorldPosition() - glm::vec3(sideLenght2, 0);
	glm::vec2 max2 = t2->GetWorldPosition() + glm::vec3(sideLenght2, 0);
	if (min1.x < max2.x && max1.x > min2.x && min1.y < max2.y && max1.y > min2.y)
		return true;
	return false;
	*/
}

bool CollisionTest::OBC2AA_OBC2AA_Test(PhysicsBody* body1, PhysicsBody* body2) {
	
	Transform* t1 = body1->gameObject->GetComponent<Transform>();
	Transform* t2 = body2->gameObject->GetComponent<Transform>();

	glm::vec3 sideLenght1 = 0.5f * t1->GetWorldScale();
	glm::vec3 sideLenght2 = 0.5f * t2->GetWorldScale();

	Corners3D corners1(t1->GetWorldPosition(), t1->GetRotationMatrix(), sideLenght1);
	Corners3D corners2(t2->GetWorldPosition(), t2->GetRotationMatrix(), sideLenght2);

	glm::vec3 a1x = glm::normalize(corners1.TopLeftFront - corners1.TopRightFront);
	glm::vec3 a1y = glm::normalize(corners1.TopLeftFront - corners1.BottomLeftFront);
	glm::vec3 a1z = glm::normalize(corners1.TopLeftFront - corners1.TopLeftBack);

	glm::vec3 a2x = glm::normalize(corners2.TopLeftFront - corners2.TopRightFront);
	glm::vec3 a2y = glm::normalize(corners2.TopLeftFront - corners2.BottomLeftFront);
	glm::vec3 a2z = glm::normalize(corners2.TopLeftFront - corners2.TopLeftBack);

	glm::vec3 axes[] = { a1x, a1y, a1z, a2x, a2y, a2z };

	for (glm::vec3 axis : axes) {
		float min1 = 0.0;
		float max1 = 0.0;
		GetMinMax(corners1, axis, min1, max1);

		float min2 = 0.0;
		float max2 = 0.0;
		GetMinMax(corners2, axis, min2, max2);
		if (max1 < min2 || max2 < min1)
			return false;
	}
	return true;
}

bool CollisionTest::OBC_OBC_Test_Internal(PhysicsBody* body1, PhysicsBody* body2) {
	
	Transform* t1 = body1->gameObject->GetComponent<Transform>();
	Transform* t2 = body2->gameObject->GetComponent<Transform>();

	glm::vec3 sideLenght1 = 0.5f * t1->GetWorldScale();
	glm::vec3 sideLenght2 = 0.5f * t2->GetWorldScale();

	Corners3D corners1(t1->GetWorldPosition(), t1->GetRotationMatrix(), sideLenght1);
	Corners3D corners2(t2->GetWorldPosition(), t2->GetRotationMatrix(), sideLenght2);

	std::pair<glm::vec3, glm::vec3> edges[12] = {
		{corners1.TopLeftFront, corners1.TopRightFront}, // Top Front
		{corners1.TopLeftFront, corners1.BottomLeftFront}, // Left Front
		{corners1.TopLeftFront, corners1.TopLeftBack}, // Top Left
		{corners1.BottomLeftBack, corners1.BottomLeftFront}, // Bottom Left
		{corners1.BottomLeftBack, corners1.BottomRightBack}, // Bottom Back
		{corners1.BottomLeftBack, corners1.TopLeftBack}, // Left Back
		{corners1.TopRightBack, corners1.TopRightFront}, // Top Right
		{corners1.TopRightBack, corners1.TopLeftBack}, // Top Back
		{corners1.TopRightBack, corners1.BottomRightBack}, // Right Back
		{corners1.BottomRightFront, corners1.BottomRightBack}, // Bottom Right
		{corners1.BottomRightFront, corners1.BottomLeftFront}, // Bottom Front
		{corners1.BottomRightFront, corners1.TopRightFront} // Right Front
	};


	Corners2D planes[6]= {
		Corners2D(corners2.TopRightFront, corners2.BottomRightFront,
				  corners2.BottomLeftFront, corners2.TopLeftFront), //Front

		Corners2D(corners2.TopRightFront, corners2.TopLeftFront,
				  corners2.TopLeftBack, corners2.TopRightBack), // Top

		Corners2D(corners2.TopRightFront, corners2.TopRightBack,
				  corners2.BottomRightBack, corners2.BottomRightFront), // Right

		Corners2D(corners2.BottomLeftBack, corners2.BottomRightBack,
				  corners2.TopRightBack, corners2.TopLeftBack), // Back

		Corners2D(corners2.BottomLeftBack, corners2.BottomLeftFront,
				  corners2.BottomRightFront, corners2.BottomRightBack), //Bottom

		Corners2D(corners2.BottomLeftBack, corners2.TopLeftBack,
				  corners2.TopLeftFront, corners2.BottomLeftFront) //Left
	};

	glm::vec3 planeNormals[6] = { 
		corners2.TopRightBack - corners2.TopRightFront, // Front
		corners2.BottomRightFront - corners2.TopRightFront, // Top
		corners2.TopLeftFront - corners2.TopRightFront, // Right
		corners2.BottomLeftFront - corners2.BottomLeftBack, // Back
		corners2.TopLeftBack - corners2.BottomLeftBack, // Bottom
		corners2.BottomRightBack - corners2.BottomLeftBack, // Left
	};

	for(const std::pair< glm::vec3, glm::vec3>& edgePoints: edges) {
		for (int i = 0; i < 6; ++i) {
			// if there in no intersection, continue
			if (abs(glm::dot(edgePoints.second - edgePoints.first, planeNormals[i])) < 0.0000001f) continue;

			float d = glm::dot(planes[i].TopRight - edgePoints.first, planeNormals[i]) / glm::dot(edgePoints.second - edgePoints.first, planeNormals[i]);

			// checks if the intersection point is between the two corners
			if (d >= 0 && d <= 1) {
				glm::vec3 intersectionPoint = edgePoints.first + (edgePoints.second - edgePoints.first) * d;
				if (PointInBounds2D(planes[i], intersectionPoint)) {					
					return true;
				}
			}
		}
	}

	// test for full encapsulation
	if (PointInBounds3D(corners1, t2->GetWorldPosition())) {
		return true;
	}
	return false;
}

// This seems really intensive, imma prob use OBC2AA whenever possible
// (which is prob almost always)
bool CollisionTest::OBC_OBC_Test(PhysicsBody* body1, PhysicsBody* body2) {
	if (OBC_OBC_Test_Internal(body1, body2) || OBC_OBC_Test_Internal(body2, body1)) {
		return true;
	}
	return false;
}

bool CollisionTest::OBC_OBB_Test(PhysicsBody* body1, PhysicsBody* body2) {
	Transform* t1 = body1->gameObject->GetComponent<Transform>();
	Transform* t2 = body2->gameObject->GetComponent<Transform>();

	glm::vec3 sideLenght1 = 0.5f * t1->GetWorldScale();
	glm::vec2 sideLenght2 = 0.5f * t2->GetWorldScale();

	Corners3D corners3d(t1->GetWorldPosition(), t1->GetRotationMatrix(), sideLenght1);
	Corners2D corners2d(t2->GetWorldPosition(), t2->GetRotationMatrix(), sideLenght2);

	std::pair<glm::vec3, glm::vec3> edges[12] = {
		{corners3d.TopLeftFront, corners3d.TopRightFront}, // Top Front
		{corners3d.TopLeftFront, corners3d.BottomLeftFront}, // Left Front
		{corners3d.TopLeftFront, corners3d.TopLeftBack}, // Top Left
		{corners3d.BottomLeftBack, corners3d.BottomLeftFront}, // Bottom Left
		{corners3d.BottomLeftBack, corners3d.BottomRightBack}, // Bottom Back
		{corners3d.BottomLeftBack, corners3d.TopLeftBack}, // Left Back
		{corners3d.TopRightBack, corners3d.TopRightFront}, // Top Right
		{corners3d.TopRightBack, corners3d.TopLeftBack}, // Top Back
		{corners3d.TopRightBack, corners3d.BottomRightBack}, // Right Back
		{corners3d.BottomRightFront, corners3d.BottomRightBack}, // Bottom Right
		{corners3d.BottomRightFront, corners3d.BottomLeftFront}, // Bottom Front
		{corners3d.BottomRightFront, corners3d.TopRightFront} // Right Front
	};
	glm::vec3 planeNormal = glm::cross(corners2d.TopLeft - corners2d.TopRight, corners2d.BottomRight - corners2d.TopRight);
	for (const std::pair< glm::vec3, glm::vec3>& edgePoints : edges) {
		for (int i = 0; i < 6; ++i) {
			// if there in no intersection, continue
			if (abs(glm::dot(edgePoints.second - edgePoints.first, planeNormal)) < 0.0000001f) continue;

			float d = glm::dot(corners2d.TopRight - edgePoints.first, planeNormal) / glm::dot(edgePoints.second - edgePoints.first, planeNormal);

			// checks if the intersection point is between the two corners
			if (d >= 0 && d <= 1) {
				glm::vec3 intersectionPoint = edgePoints.first + (edgePoints.second - edgePoints.first) * d;
				if (PointInBounds2D(corners2d, intersectionPoint)) {
					return true;
				}
			}
		}
	}
	return false;
}

CollisionTest::Corners2D::Corners2D(glm::vec3 center, glm::mat4 rotationMatrix, glm::vec2 offset) {
	glm::vec3 rotatedOffset = rotationMatrix * glm::vec4(offset, 0, 1);
	TopRight = center + rotatedOffset;
	BottomLeft = center - rotatedOffset;

	rotatedOffset = rotationMatrix * glm::vec4(-offset.x, offset.y, 0, 1);
	TopLeft = center + rotatedOffset;
	BottomRight = center - rotatedOffset;
}

CollisionTest::Corners3D::Corners3D(glm::vec3 center, glm::mat4 rotationMatrix, glm::vec3 offset) {
	glm::vec3 rotatedOffset = rotationMatrix * glm::vec4(offset, 1);
	TopRightFront = center + rotatedOffset;
	BottomLeftBack = center - rotatedOffset;

	rotatedOffset = rotationMatrix * glm::vec4(-offset.x, offset.y, offset.z, 1);
	TopLeftFront = center + rotatedOffset;
	BottomRightBack = center - rotatedOffset;

	rotatedOffset = rotationMatrix * glm::vec4(offset.x, -offset.y, offset.z, 1);
	BottomRightFront = center + rotatedOffset;
	TopLeftBack = center - rotatedOffset;

	rotatedOffset = rotationMatrix * glm::vec4(offset.x, offset.y, -offset.z, 1);
	TopRightBack = center + rotatedOffset;
	BottomLeftFront = center - rotatedOffset;
}



bool CollisionTest::OBB_Circle_Test(PhysicsBody* body1, PhysicsBody* body2) {

	//TODO: this

	return false;
	Transform* t1 = body1->gameObject->GetComponent<Transform>();
	Transform* t2 = body2->gameObject->GetComponent<Transform>();

	glm::vec2 sideLength1 = 0.5f * t1->GetWorldScale();
	//glm::vec2 sideLength2 = 0.5f * t2->GetWorldScale();
	float circleRadius = 0.5f * t2->GetWorldScale().x;

	Corners2D corners1(t1->GetWorldPosition(), t1->GetRotationMatrix(), sideLength1);

	glm::vec3 a1x = glm::normalize(corners1.TopLeft - corners1.TopRight);
	glm::vec3 a1y = glm::normalize(corners1.TopLeft - corners1.BottomLeft);

	glm::vec3 axes[] = { a1x, a1y };

	for (glm::vec3 axis : axes) {
		float min1 = 0.0;
		float max1 = 0.0;
		GetMinMax(corners1, axis, min1, max1);

		float min2 = 0.0;
		float max2 = 0.0;
		max2 = glm::dot(t2->GetPosition() + circleRadius, axis);
		min2 = glm::dot(t2->GetPosition() - circleRadius, axis);

		max2 = glm::dot(t2->GetPosition() + circleRadius * axis, axis);
		min2 = glm::dot(t2->GetPosition() - circleRadius * axis, axis);

		//GetMinMax(corners2, axis, min2, max2);
		if (max1 <= min2 || max2 <= min1)
			return false;
	}

	return true;
}