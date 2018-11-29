//*********************************************************************************************
// File:			Aeroplane.cpp
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include "Aeroplane.h"

// Initialise static class variables.
CommonMesh* Aeroplane::s_pPlaneMesh = NULL;


bool Aeroplane::s_bResourcesReady = false;
float temp = 0;

Aeroplane::Aeroplane(float fX, float fY, float fZ, float fRotY)
{
	 m_pBullet = NULL;
	m_mWorldMatrix = XMMatrixIdentity();

	m_mBulletSpawnMatrix = XMMatrixIdentity();
	m_mCamWorldMatrix = XMMatrixIdentity();

	//Plane Rot & Pos
	m_v4Pos = XMFLOAT4(fX, fY, fZ, 0.0f);
	m_v4Rot = XMFLOAT4(0.0f, fRotY, 0.0f, 0.0f);
	//Propeller Rot & Pos
	pProp = new NodeT(0.0f, 0.0f, 1.9f, 0.0f, "Resources/Plane/prop.x");
	//Turret Rot & Pos
	pTurret = new NodeT(0.0f, 1.05f, -1.3f, 0.0f, "Resources/Plane/turret.x");
	//Gun Rot & Pos
	pGun = new NodeT(0.0f, 0.5f, 0.0f, 0.0f, "Resources/Plane/gun.x");

	m_v4CamOff = XMFLOAT4(0.0f, 4.5f, -15.0f, 0.0f);
	m_v4CamRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_vCamWorldPos = XMVectorZero();
	m_vForwardVector = XMVectorZero();

	m_fSpeed = 0.0f;

	m_bGunCam = false;
}

Aeroplane::~Aeroplane(void)
{
}

void Aeroplane::SetWorldPosition(float fX, float fY, float fZ)
{
	m_v4Pos = XMFLOAT4(fX, fY, fZ, 0.0f);
	UpdateMatrices();
}

void Aeroplane::UpdateMatrices(void)
{	
	//Plane Variables
	XMMATRIX mRotX, mRotY, mRotZ, mTrans, mLocalGun, mLocalTurret;
	XMMATRIX mPlaneCameraRot, mForwardMatrix;
	XMVECTOR mInverseWorld;

	// Calculate m_mWorldMatrix for plane based on Euler rotation angles and position data.
	mRotX = XMMatrixRotationX(m_v4Rot.x);
	mRotY = XMMatrixRotationY(m_v4Rot.y);
	mRotZ = XMMatrixRotationZ(m_v4Rot.z);
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Pos));
	m_mWorldMatrix = mRotZ * mRotX * mRotY * mTrans;
	mPlaneCameraRot = mRotY * mTrans;

	// [Skip this step first time through] Get the forward vector out of the world matrix and put it in m_vForwardVector	
	m_vForwardVector = XMVector3Cross(m_mWorldMatrix.r[0], m_mWorldMatrix.r[1]);		//[0] = Up [1] = Right


	//Prop
	pProp->UpdateMatrices(m_mWorldMatrix);
	//Turret
	pTurret->UpdateMatrices(m_mWorldMatrix);
	//Gun
	pGun->UpdateMatrices(pTurret->GetNodeWorldMatrix());

	m_mBulletSpawnMatrix = mRotX * mRotY * mTrans * pTurret->GetNodeWorldMatrix();


	// Calculate m_mCameraWorldMatrix for camera based on Euler rotation angles and position data.
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4CamRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4CamRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4CamRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4CamOff));

	m_mCamWorldMatrix = mRotX * mRotY * mRotZ * mTrans;


	if (!m_bGunCam)		//Parent to Plane Hull
		m_mCamWorldMatrix *= mPlaneCameraRot;
	else				//Parent to Gun
		m_mCamWorldMatrix *= pGun->GetNodeWorldMatrix();

	m_vCamWorldPos = m_mCamWorldMatrix.r[3];

}

void Aeroplane::Update(bool bPlayerControl)
{
	//---- Player Controls ----//
	if(bPlayerControl)
	{	
		if (GetAsyncKeyState('R') && 0x8000)
		{
			m_pBullet = new Bullet(pGun->GetNodeWorldMatrix());			
			//bullets.push_back(m_pBullet);
		}
		//----------- ALTITUDE -----------//
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			if (XMConvertToDegrees(m_v4Rot.x) < 60)
				m_v4Rot.x += XMConvertToRadians(1);
		}
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			if (XMConvertToDegrees(m_v4Rot.x) > -60)
				m_v4Rot.x -= XMConvertToRadians(1);
		}
		else if(XMConvertToDegrees(m_v4Rot.x) != 0)			// If no input on "Q" or "A" slowly return to 0
		{
			if(XMConvertToDegrees(m_v4Rot.x) < 0)
			{
				if (XMConvertToDegrees(m_v4Rot.x) < -0.5)
					m_v4Rot.x += XMConvertToRadians(0.5);
				else
					m_v4Rot.x = XMConvertToRadians(0);
			}
			else if (XMConvertToDegrees(m_v4Rot.x) > 0)
			{
				if(XMConvertToDegrees(m_v4Rot.x) > 0.5)
					m_v4Rot.x -= XMConvertToRadians(0.5);
				else
					m_v4Rot.x = XMConvertToRadians(0);
			}
		}

		//----------- ROLLING -----------//
		if (GetAsyncKeyState('P') & 0x8000)				// Step 3: Make the plane yaw and roll left when you press "P" and return to level when released [Max Roll = 20deg]
		{
			if (XMConvertToDegrees(m_v4Rot.z) > -20)
				m_v4Rot.z -= XMConvertToRadians(1);

			m_v4Rot.y += XMConvertToRadians(1);

		}
		else if (GetAsyncKeyState('O') & 0x8000)			// Step 4: Make the plane yaw and roll right when you press "O" and return to level when released [Min Roll = -20deg]
		{			
			if (XMConvertToDegrees(m_v4Rot.z) < 20)
				m_v4Rot.z += XMConvertToRadians(1);

			m_v4Rot.y -= XMConvertToRadians(1);
		}
		else if(XMConvertToDegrees(m_v4Rot.z != 0))			// If no input on "O" or "P" slowly return to 0
		{
			if (XMConvertToDegrees(m_v4Rot.z) < 0)
			{
				if (XMConvertToDegrees(m_v4Rot.z) < -0.5)
					m_v4Rot.z += XMConvertToRadians(0.5);
				else
					m_v4Rot.z = XMConvertToRadians(0);
			}
			else if (XMConvertToDegrees(m_v4Rot.z) > 0)
			{
				if (XMConvertToDegrees(m_v4Rot.z) > 0.5)
					m_v4Rot.z -= XMConvertToRadians(0.5);
				else
					m_v4Rot.z = XMConvertToRadians(0);
			}
		}

	} // End of if player control

	
	// Forward Momentum
	m_fSpeed += 0.001f;

	if(m_fSpeed > 1)
		m_fSpeed = 1;

	// Rotate propeller and turret
	pProp->m_v4Rot.z += 100 * m_fSpeed;
	pTurret->m_v4Rot.y += 0.1f;

	// Tilt gun up and down as turret rotates
	pGun->m_v4Rot.x = (sin((float)XMConvertToRadians(pTurret->m_v4Rot.y * 4.0f)) * 10.0f) - 10.0f;


	UpdateMatrices();

	// Move Forward
	XMVECTOR vCurrPos = DirectX::XMLoadFloat4(&m_v4Pos);
	vCurrPos += m_vForwardVector * m_fSpeed;
	XMStoreFloat4(&m_v4Pos, vCurrPos);
	
	UpdateBullets();
}

void Aeroplane::UpdateBullets()
{
	if (m_pBullet != NULL)
		m_pBullet->Update();
}

void Aeroplane::LoadResources(void)
{
	s_pPlaneMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Plane/plane.x");
}

void Aeroplane::ReleaseResources(void)
{
	delete s_pPlaneMesh;
}

void Aeroplane::Draw(void)
{
	Application::s_pApp->SetWorldMatrix(m_mWorldMatrix);
	s_pPlaneMesh->Draw();

	//Nodes
	pTurret->Draw();
	pGun->Draw();
	pProp->Draw();

	if(m_pBullet != NULL)
		m_pBullet->Draw();
}
