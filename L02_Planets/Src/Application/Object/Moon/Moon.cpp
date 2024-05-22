#include "Moon.h"

#include "../../main.h"

void Moon::Update()
{
	// 移動行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0.0f, 0.0f, -2.0f);

	// 自転
	static float deg = 0.0f;
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(deg));
	deg += 1.0f;

	// 公転
	static float revDeg = 1.0f;
	Math::Matrix revMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(revDeg));
	revDeg += 0.5f;

	Math::Matrix sunMat;
	for (std::shared_ptr<KdGameObject> obj : Application::Instance().GetObjList())
	{
		if (obj->GetObjType() == ObjType::Earth)sunMat = obj->GetMatrix();
	}

	m_mWorld = (rotY * transMat) * revMat * sunMat;
}

void Moon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_pModel, m_mWorld);
}

void Moon::Init()
{
	m_objType = ObjType::Moon;
	m_pModel = std::make_shared<KdModelData>();
	m_pModel->Load("Asset/Data/LessonData/Planets/Moon.gltf");
}
