#include "Sun.h"

void Sun::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_pModel);
}

void Sun::Init()
{
	m_objType = ObjType::Sun;
	m_pModel = std::make_shared<KdModelData>();
	m_pModel->Load("Asset/Data/LessonData/Planets/sun.gltf");
}
