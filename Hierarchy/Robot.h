#ifndef ROBOT_H
#define ROBOT_H

#include "Application.h"


__declspec(align(16)) class Robot
{
public:
	Robot(float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f, float fRotY = 0.0f);
	~Robot(void);

	static void LoadResources(void); // Only load the resources once for all instances
	static void ReleaseResources(void); // Only free the resources once for all instances
	void Update(); // Player only has control of plane when flag is set
	void Draw(void);

	void SetWorldPosition(float fX, float fY, float fZ);
private:
	void UpdateMatrices(void);

	static CommonMesh* s_pPlaneMesh; // Only one plane mesh for all instances
	static CommonMesh* s_pPropMesh; // Only one propellor mesh for all instances
	static CommonMesh* s_pTurretMesh; // Only one turret mesh for all instances
	static CommonMesh* s_pGunMesh; // Only one gun mesh for all instances

	
public:
	
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