#pragma once

class HamuTaro :public KdGameObject
{
public:

	HamuTaro() {}
	~HamuTaro()override {}

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:

	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;
};