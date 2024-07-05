#pragma once

class BaseCamera : public KdGameObject
{
public:

	BaseCamera() {}
	~BaseCamera()override {}

	void Update()override;
	void PreDraw()override;
	void Init()override;

	// カメラのターゲットとしたいオブジェクト情報の設定
	void SetTarget(std::shared_ptr<KdGameObject> _target) { m_target = _target; }

	const Math::Matrix GetRotationMatrix() const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_degAng.y),
			DirectX::XMConvertToRadians(m_degAng.x),
			DirectX::XMConvertToRadians(m_degAng.z)
		);
	};

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY
		(
			DirectX::XMConvertToRadians(m_degAng.y)
		);
	}

	void RegistHitObject(const std::shared_ptr<KdGameObject>& _obj)
	{
		m_wpHitObjectList.push_back(_obj);
	}

protected:

	void UpdateRotateByMouse();

	std::shared_ptr<KdCamera> m_camera = nullptr;
	std::weak_ptr<KdGameObject> m_target;
	std::vector<std::weak_ptr<KdGameObject>> m_wpHitObjectList;

	Math::Matrix m_localPos;
	Math::Matrix m_rotation;

	POINT m_fixMousePos;

	// カメラ回転用角度
	Math::Vector3 m_degAng;
};