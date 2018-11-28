#ifndef NODE_H
#define NODE_H

#include "Application.h"
#include <string>
#include <vector>
__declspec(align(16)) class Node
{
public:
	Node(Node* parent, std::string filePath, float offX, float offY, float offZ, std::string name);
	Node(float offX, float offY, float offZ, std::string name);
	~Node();
	CommonMesh* s_pNodeMesh; // Only one mesh for all instances
	void LoadResources(std::string filePath); // Only load the resources once for all instances
	void ReleaseResources(void); // Only free the resources once for all instances
	void Update(); // Player only has control of plane when flag is set
	void Draw(void);
private:
	void UpdateMatrices(XMMATRIX m_mNodeParetnMatrix);
	void SetWorldPosition(float offX, float offY, float offZ);

public:
	std::string name;
	Node* nodeParent;
	Node* thisNode;
	XMFLOAT4 m_v4Rot; // Euler rotation angles
	XMFLOAT4 m_v4Pos; // World position

	XMMATRIX m_mNodeWorldMatrix;

	std::vector<Node*> children;
};
#endif