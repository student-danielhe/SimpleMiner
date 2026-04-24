#pragma once
#include "TileHeatMap.hpp"

class SignedDistanceField : public TileHeatMap {
    public:

	std::vector<bool> m_negativeField;
	std::vector<IntVec2> m_borderTiles;

	std::vector<bool> m_visited;

	SignedDistanceField(IntVec2 const& dimensions, float initialValue=0.f);

	void SpreadHeat();

	std::vector<IntVec2> SpreadHeatDriver(std::vector<IntVec2> positions, int currentVal);

	bool IsPositionValid(IntVec2 pos);

	void AddVertsForHeatMap(std::vector<Vertex_PCU>&verts, AABB2 size);

	Rgba8 GetColorFromHeat(int heat, int maxColorThreshold);
};