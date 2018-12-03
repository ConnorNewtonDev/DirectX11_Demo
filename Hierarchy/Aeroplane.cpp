//*********************************************************************************************
// File:			Aeroplane.cpp
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include "Aeroplane.h"

Aeroplane::Aeroplane(float fX, float fY, float fZ, float fRotY)
{
	m_mWorldMatrix = XMMatrixIdentity();

	m_mCamWorldMatrix = XMMatrixIdentity();

	//Root
	components.push_back(new NodeT(fX, fY, fZ, fRotY, "Resources/Plane/plane.x", NULL));
	//Propeller Rot & Pos
	components.push_back(new NodeT(0.0f, 0.0f, 1.9f, 0.0f, "Resources/Plane/prop.x", components[0]));
	//Turret Rot & Pos
	components.push_back(new NodeT(0.0f, 1.05f, -1.3f, 0.0f, "Resources/Plane/turret.x", components[0]));
	//Gun Rot & Pos
	components.push_back(new NodeT(0.0f, 0.5f, 0.0f, 0.0f, "Resources/Plane/gun.x", components[2]));


	m_v4CamOff = XMFLOAT4(0.0f, 4.5f, -15.0f, 0.0f);
	m_v4CamRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	m_vCamWorldPos = XMVectorZero();
	m_vForwardVector = XMVectorZero();

	m_fSpeed = 0.0f;

	m_bGunCam = false;;
}

Aeroplane::~Aeroplane(void)
{
}

void Aeroplane::UpdateMatrices(void)
{	
	m_vForwardVector = XMVector3Cross(components[0]->GetNodeWorldMatrix().r[0], components[0]->GetNodeWorldMatrix().r[1]);	//[0] = Up [1] = Right

	//Bullets
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->UpdateMatrices();
	}
	//Bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->UpdateMatrices();
	}

	UpdateCamera();
	
}

void Aeroplane::UpdateCamera()
{
	//Plane Variables
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;
	XMMATRIX mPlaneCameraRot;

	// Calculate m_mWorldMatrix for plane based on Euler rotation angles and position data.
	mRotX = XMMatrixRotationX(XMConvertToRadians(components[0]->m_v4Rot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(components[0]->m_v4Rot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(components[0]->m_v4Rot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&components[0]->m_v4Pos));
	//m_mWorldMatrix = mRotZ * mRotX * mRotY * mTrans;
	mPlaneCameraRot = mRotY * mTrans;


	// Calculate m_mCameraWorldMatrix for camera based on Euler rotation angles and position data.
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4CamRot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4CamRot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4CamRot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4CamOff));

	m_mCamWorldMatrix = mRotX * mRotY * mRotZ * mTrans;


	if (!m_bGunCam)		//Parent to Plane Hull
		m_mCamWorldMatrix *= mPlaneCameraRot;
	else				//Parent to Gun
		m_mCamWorldMatrix *= components[3]->GetNodeWorldMatrix();

	m_vCamWorldPos = m_mCamWorldMatrix.r[3];
}

void Aeroplane::Update(bool bPlayerControl)
{
	if (bEngineOn)
	{
		//---- Player Controls ----//
		if (bPlayerControl)
		{
			if (GetAsyncKeyState('R') && 0x8000)
			{
				AttemptFire();
			}
			//----------- ALTITUDE -----------//
			if (GetAsyncKeyState('Q') & 0x8000)
			{
				if ((components[0]->m_v4Rot.x) < 60)
					components[0]->m_v4Rot.x += 1;
			}
			else if (GetAsyncKeyState('A') & 0x8000)
			{
				if ((components[0]->m_v4Rot.x) > -60)
					components[0]->m_v4Rot.x -= (1);
			}
			else if ((components[0]->m_v4Rot.x) != 0)			// If no input on "Q" or "A" slowly return to 0
			{
				if ((components[0]->m_v4Rot.x) < 0)
				{
					if ((components[0]->m_v4Rot.x) < -0.5)
						components[0]->m_v4Rot.x += (0.5);
					else
						components[0]->m_v4Rot.x = (0);
				}
				else if ((components[0]->m_v4Rot.x) > 0)
				{
					if ((components[0]->m_v4Rot.x) > 0.5)
						components[0]->m_v4Rot.x -= (0.5);
					else
						components[0]->m_v4Rot.x = (0);
				}
			}

			//----------- ROLLING -----------//
			if (GetAsyncKeyState('P') & 0x8000)				// Step 3: Make the plane yaw and roll left when you press "P" and return to level when released [Max Roll = 20deg]
			{
				if ((components[0]->m_v4Rot.z) > -20)
					components[0]->m_v4Rot.z -= (1);

				components[0]->m_v4Rot.y += (1);

			}
			else if (GetAsyncKeyState('O') & 0x8000)			// Step 4: Make the plane yaw and roll right when you press "O" and return to level when released [Min Roll = -20deg]
			{
				if ((components[0]->m_v4Rot.z) < 20)
					components[0]->m_v4Rot.z += (1);

				components[0]->m_v4Rot.y -= (1);
			}
			else if ((components[0]->m_v4Rot.z != 0))			// If no input on "O" or "P" slowly return to 0
			{
				if ((components[0]->m_v4Rot.z) < 0)
				{
					if ((components[0]->m_v4Rot.z) < -0.5)
						components[0]->m_v4Rot.z += (0.5);
					else
						components[0]->m_v4Rot.z = (0);
				}
				else if ((components[0]->m_v4Rot.z) > 0)
				{
					if ((components[0]->m_v4Rot.z) > 0.5)
						components[0]->m_v4Rot.z -= (0.5);
					else
						components[0]->m_v4Rot.z = (0);
				}
			}

		} // End of if player control


		  // Forward Momentum
		m_fSpeed += 0.001f;

		if (m_fSpeed > 1)
			m_fSpeed = 1;

		// Rotate propeller and turret
		components[1]->m_v4Rot.z += 100 * m_fSpeed;
		components[2]->m_v4Rot.y += 0.1f;

		// Tilt gun up and down as turret rotates
	}
	components[3]->m_v4Rot.x = (sin((float)XMConvertToRadians(components[2]->m_v4Rot.y * 4.0f)) * 10.0f) - 10.0f;


	UpdateMatrices();

	// Move Forward
	XMVECTOR vCurrPos = DirectX::XMLoadFloat4(&components[0]->m_v4Pos);
	vCurrPos += m_vForwardVector * m_fSpeed;
	XMStoreFloat4(&components[0]->m_v4Pos, vCurrPos);
	
	

	UpdateBullets();


}

void Aeroplane::AttemptFire()
{
	if (fCurTimer <= 0.0f)
	{
		bullets.push_back(new Bullet(components[3], m_vForwardVector));
		fCurTimer = fBulletCD;
	}

}

void Aeroplane::UpdateBullets()
{
	//Timer
	if (fCurTimer > 0.0f)
		fCurTimer -= 0.05f;

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update();
	}

}

void Aeroplane::ReleaseResources(void)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->ReleaseResources();
	}
}

void Aeroplane::Draw(void)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Draw();
	}


	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Draw();
	}
}
