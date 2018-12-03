#include "NodeT.h"
#include "Application.h"

NodeT::NodeT(float fX, float fY, float fZ, float fRotY, std::string filePath, NodeT* nParent)
{
	name = filePath;
	if (filePath != "")
		LoadResources(filePath);



	parent = nParent;
	m_v4Rot = XMFLOAT4(0.0f, fRotY, 0.0f, 0.0f);
	m_v4Pos = XMFLOAT4(fX, fY, fZ, 0.0f);
}


NodeT::~NodeT()
{
}

void NodeT::LoadResources(std::string filePath)
{

	const char* path = filePath.c_str();
	s_pNodeMesh = CommonMesh::LoadFromXFile(Application::s_pApp, path);
}

void NodeT::ReleaseResources()
{
	delete s_pNodeMesh;
}

void NodeT::Draw(void)
{
	Application::s_pApp->SetWorldMatrix(m_mNodeWorldMatrix);
	if(s_pNodeMesh != NULL)
		s_pNodeMesh->Draw();
}

XMVECTOR NodeT::GetNodeWorldPosition(XMVECTOR& parentMatrix)
{	
	if (parent != NULL)
	{
		XMVECTOR temp = parent->GetNodeWorldPosition(XMLoadFloat4(&m_v4Pos));
		return parentMatrix + temp;
	}
	return  XMLoadFloat4(&m_v4Pos) + parentMatrix;
	
}

XMVECTOR NodeT::GetNodeWorldRotation(XMVECTOR& parentMatrix)
{
	if (parent != NULL)
	{
		XMVECTOR temp = parent->GetNodeWorldRotation(XMLoadFloat4(&m_v4Rot));
		return parentMatrix + temp;
	}
	return  XMLoadFloat4(&m_v4Rot) + parentMatrix;
}

void NodeT::UpdateMatrices()
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;
	// Calculate m_mWorldMatrix for plane based on Euler rotation angles and position data.
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Rot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Rot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Rot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Pos));

	// Then concatenate the matrices and parent
	if (parent != NULL)
	{
		m_mNodeWorldMatrix = mRotX * mRotY * mRotZ * mTrans * parent->GetNodeWorldMatrix();
	}
	else if(parent == NULL)
	{	
		m_mNodeWorldMatrix = mRotZ * mRotX * mRotY * mTrans;
	}
}
