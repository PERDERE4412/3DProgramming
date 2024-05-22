#pragma once

class Terrain :public KdGameObject
{
public:

	Terrain() {}
	~Terrain() {}

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:

	// モデルデータ
	std::shared_ptr<KdModelData> m_spModel = nullptr;
};