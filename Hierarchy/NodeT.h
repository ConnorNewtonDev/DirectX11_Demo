#ifndef NODET_H
#define NODET_H

#include "Application.h"
class NodeT
{
public:
	NodeT(float fX, float fY, float fZ, float fRotY, std::string filePath);
	NodeT();
	~NodeT();
	void LoadResources(std::string filePath);
	void ReleaseResources();
	void Draw(void);

	void UpdateMatrices(XMMATRIX m_mParentWorldMatrix);
private:

	XMMATRIX m_mNodeWorldMatrix;

public:
	XMFLOAT4 m_v4Rot; // Euler rotation angles
	XMFLOAT4 m_v4Pos; // World position
	CommonMesh* s_pNodeMesh = NULL;
	XMMATRIX GetNodeWorldMatrix() { return m_mNodeWorldMatrix; }
};

#endif
