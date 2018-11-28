#ifndef NODET_H
#define NODET_H

#include "Application.h"
class NodeT
{
public:
	NodeT(float fX, float fY, float fZ, float fRotY, std::string filePath);
	~NodeT();
	void LoadResources(std::string filePath);
	void ReleaseResources();

	CommonMesh* s_pNodeMesh;

private:
	void UpdateMatrices(XMMATRIX m_mParentWorldMatrix);
	XMMATRIX m_mNodeWorldMatrix;

public:
	XMFLOAT4 m_v4Rot; // Euler rotation angles
	XMFLOAT4 m_v4Pos; // World position

	XMMATRIX GetNodeWorldMatrix() { return m_mNodeWorldMatrix; }
};

#endif
