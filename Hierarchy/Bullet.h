#ifndef BULLET_H
#define BULLET_H


#include "Application.h"
#include "NodeT.h"
__declspec(align(16)) class Bullet
{
public:
	Bullet(NodeT* spawner, XMVECTOR m_vInheritedVelocity);
	~Bullet();

	void Draw();
	static void LoadResources(void);
	static void ReleaseResources(void);
	void Update();
	bool DestroyTime();
	void UpdateMatrices(void);
	
private:
	//---- Functions ----//
	void MoveForward();
	void SetWorldPosition();



	//---- Variables ----//
	float fLifeTime = 5;
	float fcurLifeTime = 0.0f;

	static CommonMesh* s_pBulletMesh;
	static bool s_bResourcesReady;
	bool positioned = false;
	const XMVECTOR forward = XMVectorSet(0, 0, 1, 0);
	XMMATRIX m_mBulletWorldMatrix;	
	XMVECTOR m_vForwardVector;  
	XMVECTOR m_vInheritedVelocity;
	float fBulletSpeed;			
	NodeT* spawnParent;
	XMFLOAT4 m_v4Rot; // Euler rotation angles
	XMFLOAT4 m_v4Pos; // World position
};

#endif

