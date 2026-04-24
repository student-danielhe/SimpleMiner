#pragma once
#include "Engine/Math/Plane.hpp"
#include "Engine/Math/Vec2.hpp"
#include <vector>
#include "Engine/Math/AABB2.hpp"
class ConvexShape {
	public:
	Vec2 m_globalCoords;
	float m_rotation;
	float m_boundingDiscRadius;

	std::vector<Plane2> m_planes;

	//must be in CCW
	std::vector<Vec2> m_intersections;

	void Move(Vec2 displacement);
	void Rotate(float degree);

	void UpdateLocation();

	static ConvexShape* CreateRandom(int minSides, int maxSides, float minRadius, float maxRadius, AABB2 bounds);

	private:
	std::vector<Vec2> m_localIntersections;
};