#include "SignedDistanceField.hpp"
#include "Engine/Core/VertexUtils.hpp"

SignedDistanceField::SignedDistanceField(IntVec2 const& dimensions, float initialValue/*=0.f*/): TileHeatMap(dimensions, initialValue)
{

}

void SignedDistanceField::SpreadHeat()
{
    m_visited.clear();
	
    for (int i = 0; i < m_dimensions.x * m_dimensions.y; i++) {
		m_visited.push_back(false);
	}

    std::vector<IntVec2> openList = m_borderTiles;

    int currentVal = 0;

    for (IntVec2 pos : m_borderTiles) {
        m_visited[pos.x + pos.y * m_dimensions.x] = true;
    }

    while (!openList.empty()) {

        openList = SpreadHeatDriver(openList, currentVal);
        currentVal++;

    }
}

std::vector<IntVec2> SignedDistanceField::SpreadHeatDriver(std::vector<IntVec2> positions, int currentVal)
{
    std::vector<IntVec2> newOpenList;

	for (IntVec2 pos : positions) {
		
        if (m_negativeField[pos.x + pos.y * m_dimensions.x]) {
            SetHeat(pos, -currentVal);
        }
        else {
			SetHeat(pos, currentVal);
        }
		
        
        if (IsPositionValid(pos + IntVec2(0, 1))) {
            newOpenList.push_back(pos + IntVec2(0, 1));
        }

		if (IsPositionValid(pos + IntVec2(0, -1))) {
			newOpenList.push_back(pos + IntVec2(0, -1));
		}

		if (IsPositionValid(pos + IntVec2(1, 0))) {
			newOpenList.push_back(pos + IntVec2(1, 0));
		}

		if (IsPositionValid(pos + IntVec2(-1, 0))) {
			newOpenList.push_back(pos + IntVec2(-1, 0));
		}

	}

    return newOpenList;
}

bool SignedDistanceField::IsPositionValid(IntVec2 pos)
{
    if (pos.x < 0 || pos.y < 0 || pos.x >= m_dimensions.x || pos.y >= m_dimensions.y) {
        return false;
    }

    if (m_visited[pos.x + pos.y * m_dimensions.x]) {
        return false;
    }

    m_visited[pos.x + pos.y * m_dimensions.x] = true;
    return true;
}


void SignedDistanceField::AddVertsForHeatMap(std::vector<Vertex_PCU>&verts, AABB2 size)
{
    Vec2 totalDimension = size.GetDimensions();
    Vec2 tileDimension(totalDimension.x/(float)m_dimensions.x, totalDimension.y/(float)m_dimensions.y);

    for (int y = 0; y < m_dimensions.y; y++) {

        for (int x = 0; x < m_dimensions.x; x++) {

            int index = x + y * m_dimensions.x;

            Vec2 mins = size.m_mins + Vec2(tileDimension.x * (float)x, tileDimension.y * (float)y);
            
            AABB2 currentSquare(mins, mins + tileDimension);

            AddVertsForRect(verts, currentSquare, GetColorFromHeat( (int)GetHeat( IntVec2(x, y) ), 25 ));

        }

    }

}

Rgba8 SignedDistanceField::GetColorFromHeat(int heat, int maxColorThreshold)
{
    Rgba8 negative(0,0,255);
    Rgba8 netural(0, 255, 0);
    Rgba8 positive(255, 0,0);

    if (heat < -maxColorThreshold) {
        return negative;
    }

    if (heat < 0) {
        float fraction = (-(float)heat / (float)maxColorThreshold);
        return Rgba8(0, (int)(255.f * (1.f - fraction)), (int)(255.f * fraction));
    }

    if (heat == 0) {
        return netural;
    }

    if (heat > maxColorThreshold) {
        return positive;
    }

	float fraction = ((float)heat / (float)maxColorThreshold);
    return Rgba8((int)(255.f * fraction), (int)(255.f*(1.f - fraction)), 0);
}
