#pragma once

class Earth :public KdGameObject
{
public:

	Earth() { Init(); }
	~Earth()override {}

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:

	std::shared_ptr<KdModelData> m_pModel = nullptr;
};