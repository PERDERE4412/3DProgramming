#pragma once

class BaseCamera;

class Character : public KdGameObject
{
public:
	Character() {}
	virtual ~Character()	override {}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

	void SetCamera(std::shared_ptr<BaseCamera> _camera)
	{
		m_camera = _camera;
	}

private:
	std::shared_ptr<KdSquarePolygon>	m_spPoly	= nullptr;
	std::weak_ptr<BaseCamera> m_camera;

};