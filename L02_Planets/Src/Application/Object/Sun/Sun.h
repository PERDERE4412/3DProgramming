#pragma once

class Sun :public KdGameObject
{
public:

	Sun() { Init(); }
	~Sun()override {}

	void DrawLit()override;
	void Init()override;

private:

	std::shared_ptr<KdModelData> m_pModel=nullptr;
};