#ifndef BULLET_H
#define BULLET_H


#include "Application.h"
__declspec(align(16)) class Bullet
{
public:
	Bullet(XMMATRIX m_mGunWorldMatrix);
	~Bullet();

	void Draw();
	static void LoadResources(void);
	static void ReleaseResources(void);
	void Update();

	
private:
	//---- Functions ----//
	void MoveForward();
	void SetWorldPosition(XMMATRIX m_mGunWorldMatrix);
	void UpdateMatrices(void);


	//---- Variables ----//
	static CommonMesh* s_pBulletMesh;
	static bool s_bResourcesReady;

	XMMATRIX m_mBulletWorldMatrix;	

	XMVECTOR m_vForwardVector;  
	float fBulletSpeed;			
	
	XMFLOAT4 m_v4Rot; // Euler rotation angles
	XMFLOAT4 m_v4Pos; // World position
	

public:


};

#endif

