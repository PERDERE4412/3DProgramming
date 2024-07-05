#include "BaseCamera.h"

void BaseCamera::Update()
{
	if (!m_camera) return;

	m_camera->SetCameraMatrix(m_mWorld);
}

void BaseCamera::PreDraw()
{
	if (!m_camera)return;

	m_camera->SetToShader();
}

void BaseCamera::Init()
{
	if (!m_camera)
	{
		m_camera = std::make_shared<KdCamera>();
	}

	// ↓画面中央
	m_fixMousePos.x = 640;
	m_fixMousePos.y = 320;
}

void BaseCamera::UpdateRotateByMouse()
{
	POINT nowPos;
	GetCursorPos(&nowPos);

	// マウスカーソルの差分を求める
	POINT mouseMove;
	mouseMove.x = nowPos.x - m_fixMousePos.x;
	mouseMove.y = nowPos.y - m_fixMousePos.y;

	// マウスカーソルを再度画面中央へ固定
	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);

	// 上の差分を基に回転角度を求める
	m_degAng.x += mouseMove.y * 0.15f;
	m_degAng.y += mouseMove.x * 0.15f;
}