#ifndef AEROPLANE_H
#define AEROPLANE_H

//*********************************************************************************************
// File:			Aeroplane.h
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include "Application.h"
#include "Bullet.h"
#include "NodeT.h"
#include <iostream>
#include <ctime>

__declspec(align(16)) class Aeroplane
{
  public:
	Aeroplane(float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f, float fRotY = 0.0f);
	~Aeroplane(void);

	void ReleaseResources(void); // Only free the resources once for all instances
	void Update(bool bPlayerControl); // Player only has control of plane when flag is set
	void UpdateBullets();
	void Draw(void);


  private:
	void UpdateMatrices(void);
	void UpdateCamera();


	XMVECTOR m_vForwardVector; // Forward Vector for Plane
	float m_fSpeed; // Forward speed

	XMMATRIX m_mWorldTrans; // World translation matrix
	XMMATRIX m_mWorldMatrix; // World transformation matrix
	
	XMFLOAT4 m_v4CamRot; // Local rotation angles
	XMFLOAT4 m_v4CamOff; // Local offset

	XMVECTOR m_vCamWorldPos; // World position
	XMMATRIX m_mCamWorldMatrix; // Camera's world transformation matrix

	bool m_bGunCam;

	std::vector<Bullet*> bullets;
	std::vector<NodeT*> components;

  public:
	float GetXPosition(void) { return components[0]->m_v4Pos.x; }
	float GetYPosition(void) { return components[0]->m_v4Pos.y; }
	float GetZPosition(void) { return components[0]->m_v4Pos.z; }
	float GetForwardSpeed()  { return m_fSpeed;  }
	XMFLOAT4 GetFocusPosition(void) { return GetPosition(); }
	XMFLOAT4 GetCameraPosition(void)
	{
		XMFLOAT4 v4Pos;
		DirectX::XMStoreFloat4(&v4Pos, m_vCamWorldPos);
		return v4Pos;
	}
	XMFLOAT4 GetPosition(void) { return components[0]->m_v4Pos; }
	void SetGunCamera(bool value) { m_bGunCam = value; }

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