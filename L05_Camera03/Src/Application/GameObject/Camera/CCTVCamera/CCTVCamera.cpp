#include "CCTVCamera.h"

#include "../../../main.h"

void CCTVCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 6.0f, -10.0f);

	m_mWorld = m_mLocalPos;
}

void CCTVCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	UpdateLookAtRotate(_targetMat.Translation());
}

void CCTVCamera::UpdateLookAtRotate(const Math::Vector3& _targetPos)
{
	Math::Matrix shadowVP= DirectX::XMMatrixLookAtLH(GetPos(),_targetPos,Math::Vector3::Up);
	m_mWorld = shadowVP.Invert();
}