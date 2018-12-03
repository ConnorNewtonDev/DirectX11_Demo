#ifndef ROBOT_H
#define ROBOT_H

#include "Application.h"
#include "NodeT.h"
#include "XMLParser.h"

#include <list>
#include <vector>
#include <iostream>

__declspec(align(16)) class Robot
{
public:
	Robot(float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f, float fRotY = 0.0f);
	~Robot(void);

	void ReleaseResources(void); // Only free the resources once for all instances
	void LoadNodes(float fX, float fY, float fZ, float fRotY);
	void Draw(void);
	void Update(); // Player only has control of plane when flag is set
private:
	void UpdateMatrices(void);

	static CommonMesh* s_pPlaneMesh; // Only one plane mesh for all instances
	static CommonMesh* s_pPropMesh; // Only one propellor mesh for all instances
	static CommonMesh* s_pTurretMesh; // Only one turret mesh for all instances
	static CommonMesh* s_pGunMesh; // Only one gun mesh for all instances

	
public:
	XMLParser* parser = NULL;
	XMFLOAT4 m_v4Rot; // Euler rotation angles
	XMFLOAT4 m_v4Pos; // World position
	XMVECTOR m_vForwardVector; // Forward Vector for Plane
	XMMATRIX m_mWorldMatrix; // World transformation matrix

	std::vector<NodeT*> robotNodes;
	std::string nodeFilePath;




	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}

};

#endif