#include "Character.h"
#include "../../main.h"

void Character::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Data/LessonData/Character/Hamu.png");
		m_spPoly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	}

	m_tex.Load("Asset/Textures/name.png");
}

void Character::Update()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		// ①マウス座標を取得する
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(Application::Instance().GetWindowHandle(), &mousePos);

		if (!m_wpCam.expired())
		{
			Math::Vector3 camPos = m_wpCam.lock()->GetCameraMatrix().Translation();
			Math::Vector3 rayDir = Math::Vector3::Zero;
			float rayRange = 1000.0f;
			// ②レイの発射方向を求める(rayDir)
			m_wpCam.lock()->GenerateRayInfoFromClientPos(mousePos, camPos, rayDir, rayRange);

			// ③実際にレイを飛ばして衝突位置を求める
			const std::shared_ptr<KdGameObject> _terrain = m_wpTerrain.lock();
			if (_terrain)
			{
				Math::Vector3 _endRayPos = camPos + (rayDir * rayRange);
				KdCollider::RayInfo _rayInfo(KdCollider::TypeGround, camPos, _endRayPos);

				// 実際の当たり判定の処理
				std::list<KdCollider::CollisionResult> _results;
				_terrain->Intersects(_rayInfo, &_results);

				// 結果が一つでも返って来ていたら
				if (!_results.empty())
				{
					for (KdCollider::CollisionResult result : _results)
					{
						m_TargetPos = result.m_hitPos;
					}
				}
			}
		}
	}

	// キャラクターの移動速度(真似しちゃダメですよ)
	float moveSpd = 0.05f;

	Math::Vector3 nowPos = GetPos();

	Math::Vector3 moveVec = Math::Vector3::Zero;
	moveVec = m_TargetPos - nowPos;
	
	if (moveVec.LengthSquared() < moveSpd)moveSpd = moveVec.Length();
	
	moveVec.Normalize();
	moveVec *= moveSpd;
	nowPos += moveVec;
	
	// キャラクターのワールド行列を創る処理
	m_mWorld = Math::Matrix::CreateTranslation(nowPos);
}

void Character::DrawLit()
{
	if (!m_spPoly) return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void Character::DrawSprite()
{
	// ↓この赤い点が常にハムスターの原点(足元)に追従するように！
	// ①ハムスターの3D座標を2D座標に変換する
	Math::Vector3 pos = Math::Vector3::Zero;
	if (!m_wpCam.expired())
	{
		m_wpCam.lock()->ConvertWorldToScreenDetail(GetPos(), pos);
		pos.y += 100.0f;
	}
	Math::Rectangle rect = { 0,0,(int)m_tex.GetWidth(),(int)m_tex.GetHeight() };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, pos.x, pos.y, m_tex.GetWidth(), m_tex.GetHeight(), &rect);

	// 2D座標を3D座標に変換

}
