#include "Node.h"

Node::Node(Node* parent, std::string filePath, float offX, float offY, float offZ, std::string _name)
{
	//TEMP
	name = _name;
	//
	nodeParent = parent;
	LoadResources(filePath);

	m_mNodeWorldMatrix = XMMatrixIdentity();

	SetWorldPosition(offX, offY, offZ);

}

Node::Node(float offX, float offY, float offZ, std::string _name)		//Root Node
{
	name = _name;
	nodeParent = NULL;
	SetWorldPosition(offX, offY, offZ);
}
Node::~Node()
{

}

void Node::LoadResources(std::string filePath)
{
	const char* path = filePath.c_str();
	s_pNodeMesh = CommonMesh::LoadFromXFile(Application::s_pApp, path);
}

void Node::ReleaseResources()
{	//Depth first search through child nodes to release
	if (children.size() != 0)
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->ReleaseResources();
		}
	}
	
	delete s_pNodeMesh;
}

void Node::Update()
{
	UpdateMatrices(nodeParent->m_mNodeWorldMatrix);

	////Depth first search through child nodes to update
	//if (children.size() != 0)
	//{
	//	for (int i = 0; i < children.size(); i++)
	//	{
	//		children[i]->Update();
	//	}
	//}
}

void Node::Draw()
{	//Depth first search through child nodes to draw
	if (children.size() != 0)
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Draw();
		}
	}

	Application::s_pApp->SetWorldMatrix(m_mNodeWorldMatrix);
	s_pNodeMesh->Draw();
}

void Node::UpdateMatrices(XMMATRIX m_mParentWorldMatrix)
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;
	// Calculate m_mWorldMatrix for plane based on Euler rotation angles and position data.
	mRotX = XMMatrixRotationX(m_v4Rot.x);
	mRotY = XMMatrixRotationY(m_v4Rot.y);
	mRotZ = XMMatrixRotationZ(m_v4Rot.z);
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Pos));
	// Then concatenate the matrices and parent
		m_mNodeWorldMatrix = mRotX * mRotY * mRotZ * mTrans * m_mParentWorldMatrix;


	if (children.size() != 0)
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->UpdateMatrices(m_mNodeWorldMatrix);
		}
	}

}


void Node::SetWorldPosition(float offX, float offY, float offZ)
{

}