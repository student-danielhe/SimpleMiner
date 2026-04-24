#include "Engine/Math/ConvexShape.hpp"
#include "Engine/Math/RandomNumberGenerator.hpp"
#include "Engine/Math/MathUtils.hpp"
void ConvexShape::Move(Vec2 displacement)
{
    m_globalCoords +=displacement;
    UpdateLocation();
}

void ConvexShape::Rotate(float degree)
{
    m_rotation+=degree;
    UpdateLocation();
}

void ConvexShape::UpdateLocation()
{

    m_intersections.clear();
    for (int i = 0; i < m_localIntersections.size(); i++) {
        Vec2 intersection = m_localIntersections[i];
        intersection.RotateDegrees(m_rotation);
        intersection += m_globalCoords;
        m_intersections.push_back(intersection);
    }



    m_planes.clear();

    for (int i = 0; i < m_intersections.size(); i++) {
        
        Vec2 planeFrom = m_intersections[i];
        Vec2 planeTo;

        if (i + 1 == m_intersections.size()) {
            planeTo = m_intersections[0];
        }
        else {
            planeTo = m_intersections[i+1];
        }

        Plane2 plane;
        
        plane.m_normal = planeTo-planeFrom;
        plane.m_normal.Rotate90Degrees();
        plane.m_normal.Normalize();
        plane.m_dist = GetProjectedLength2D(planeFrom, plane.m_normal);

        m_planes.push_back(plane);

    }
}

ConvexShape* ConvexShape::CreateRandom(int minSides, int maxSides, float minRadius, float maxRadius, AABB2 bounds)
{
    RandomNumberGenerator* rng = new RandomNumberGenerator();
    int totalSides = rng->RollRandomIntInRange(minSides, maxSides);
    float radius = rng->RollRandomFloatInRange(minRadius, maxRadius);
    
    float degreeMoved = 0.f;

    ConvexShape* result = new ConvexShape();
    result->m_boundingDiscRadius = radius;
    result->m_rotation = 0.f;

    for (int i = 0; i < totalSides; i++) {
        
        float degreeSkipped = 0;
        if (i + 1 == totalSides) {
            degreeSkipped = rng->RollRandomFloatInRange(0, 359.f-degreeMoved);
        }
        else {
			float remainingDegree = 360.f - degreeMoved;
			int remainingSides = totalSides - i;
			float averageSkip = remainingDegree / (float)remainingSides;
            degreeSkipped = rng->RollRandomFloatInRange(0, 2.f * averageSkip);
        }

        degreeMoved+=degreeSkipped;

        Vec2 newIntersection(radius, 0.f);

        newIntersection.RotateDegrees(degreeMoved);

        result->m_localIntersections.push_back(newIntersection);
        
    }

    float globalX = rng->RollRandomFloatInRange(bounds.m_mins.x+radius, bounds.m_maxs.x-radius);

    float globalY = rng->RollRandomFloatInRange(bounds.m_mins.y+radius, bounds.m_maxs.y-radius);

    result->m_globalCoords = Vec2(globalX, globalY);

    result->UpdateLocation();

    return result;
}

