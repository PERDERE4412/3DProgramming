#include "TpsCamera.h"

void TpsCamera::Update()
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
	m_mWorld = m_localPos * m_rotation * targetMat;

	// ↓めり込み防止の為の座標補正計算
	// ①当たり判定(レイ判定)用の情報作成
	KdCollider::RayInfo rayInfo;
	// レイの発射位置を設定
	rayInfo.m_pos = GetPos();
	// レイの発射方向を設定
	rayInfo.m_dir = Math::Vector3::Down;
	// レイの長さ
	rayInfo.m_range = 1000.0f;
	// 当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;
	if (target)
	{
		Math::Vector3 targetPos = target->GetPos();
		targetPos.y += 0.1f;
		rayInfo.m_dir = targetPos - GetPos();
		rayInfo.m_range = rayInfo.m_dir.Length();
		rayInfo.m_dir.Normalize();
	}

	// ②HIT対象オブジェクトに総当たり
	for (std::weak_ptr<KdGameObject> wpObj : m_wpHitObjList)
	{
		std::shared_ptr<KdGameObject> spObj = wpObj.lock();
		if (spObj)
		{
			std::list<KdCollider::CollisionResult> retRayList;
			spObj->Intersects(rayInfo, &retRayList);

			// ③結果を使って座標を補完する
			// レイに当たったリストから一番近いオブジェクトを検出
			float maxOverLap = 0;
			Math::Vector3 hitPos = {};
			bool hit = false;
			for (auto& ret : retRayList)
			{
				// レイを遮断し、オーバーした長さが一番長いものを探す
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					hit = true;
				}
			}

			if (hit)
			{
				Math::Vector3 _hitPos = hitPos;
				_hitPos += rayInfo.m_dir * 0.4f;
				SetPos(_hitPos);
			}
		}
	}

	BaseCamera::Update();
}

void TpsCamera::Init()
{
	// 基準点(ターゲット)からどれだけ離れているか
	m_localPos = Math::Matrix::CreateTranslation(0.0f, 1.5f, -10.0f);

	// ↓画面中央
	m_fixMousePos.x = 640;
	m_fixMousePos.y = 320;

	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);

	BaseCamera::Init();
}
