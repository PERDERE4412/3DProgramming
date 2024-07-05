#include "TrackingCamera.h"

void TrackingCamera::Update()
{
	// ターゲットの行列
	Math::Matrix targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> target=m_target.lock();
	if (target)
	{
		targetMat = Math::Matrix::CreateTranslation(target->GetPos());
	}

	m_mWorld = m_rotation * m_localPos*targetMat;

	BaseCamera::Update();
}

void TrackingCamera::Init()
{
	// 基準点(ターゲット)からどれだけ離れているか
	m_localPos = Math::Matrix::CreateTranslation(0.0f, 6.0f, -5.0f);

	// どれだけ傾いているか
	m_rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));

	BaseCamera::Init();
}
