#include "Earth.h"

#include "../../main.h"

void Earth::Update()
{
	// 移動行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0.0f, 0.0f, -10.0f);
	
	// 自転
	static float deg = 0.0f;
	Math::Matrix rotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(deg));
	deg += 1.0f;

	// 公転
	static float revDeg=1.0f;
	Math::Matrix revMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(revDeg));
	revDeg += 0.5f;

	Math::Matrix sunMat;
	for (std::shared_ptr<KdGameObject> obj : Application::Instance().GetObjList())
	{
		if (obj->GetObjType() == ObjType::Sun)sunMat = obj->GetMatrix();
	}

	m_mWorld = (rotY*transMat)*revMat*sunMat;
}

void Earth::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_pModel,m_mWorld);
}

void Earth::Init()
{
	m_objType = ObjType::Earth;
	m_pModel = std::make_shared<KdModelData>();
	m_pModel->Load("Asset/Data/LessonData/Planets/earth.gltf");
}
