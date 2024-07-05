#include "FpsCamera.h"

void FpsCamera::Update()
{
	// ターゲットの行列
	Math::Matrix targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> target = m_target.lock();
	if (target)
	{
		targetMat = Math::Matrix::CreateTranslation(target->GetPos());
	}

	// カメラの回転
	UpdateRotateByMouse();
	m_rotation = GetRotationMatrix();
	m_mWorld = m_rotation * m_localPos * targetMat;

	BaseCamera::Update();
}

void FpsCamera::Init()
{
	// 親クラスの初期化呼び出し
	BaseCamera::Init();

	// 基準点(ターゲット)からどれだけ離れているか
	m_localPos = Math::Matrix::CreateTranslation(0.0f, 1.5f, 0.0f);

	SetCursorPos(m_fixMousePos.x,m_fixMousePos.y);
}
