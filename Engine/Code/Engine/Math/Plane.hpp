#pragma once
#include "Engine/Math/Vec3.hpp"
#include"Engine/Math/Vec2.hpp"
//altitude of point p = p*n - d

struct Plane2 {
	Vec2 m_normal;
	float m_dist;
};

struct Plane3 {
	Vec3 m_normal;
	float m_dist;
};