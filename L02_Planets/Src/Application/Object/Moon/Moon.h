#pragma once

class Moon :public KdGameObject
{
public:

	Moon() { Init(); }
	~Moon()override {}

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:

	std::shared_ptr<KdModelData> m_pModel = nullptr;
};