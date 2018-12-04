#include "Bullet.h"

// Initialise static class variables.
CommonMesh* Bullet::s_pBulletMesh = NULL;
bool Bullet::s_bResourcesReady = false;

//---- Public ----//
Bullet::Bullet(NodeT* spawner, XMVECTOR inheritedVelocity)
{
	//Initialise values.
	m_mBulletWorldMatrix = XMMatrixIdentity();
	m_v4Pos = XMFLOAT4(0, 0, 0, 0);
	m_v4Rot = XMFLOAT4(0, 0, 0, 0);
	m_vForwardVector = XMVectorZero();
	spawnParent = spawner;
	m_vInheritedVelocity = inheritedVelocity;
	
	//Set the bullet to it's spawn position.
	SetWorldPosition();
	LoadResources();
	fBulletSpeed = 2.5f;

}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	MoveForward();
	
}

void Bullet::Draw(void)
{
	Application::s_pApp->SetWorldMatrix(m_mBulletWorldMatrix);
	s_pBulletMesh->Draw();
}

void Bullet::LoadResources(void)
{
	s_pBulletMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Bullet/bullet.x");
}

void Bullet::ReleaseResources(void)
{
	delete s_pBulletMesh;
}

void Bullet::MoveForward()
{
	//Increment the current position forward.
	XMVECTOR vCurPos = XMLoadFloat4(&m_v4Pos);
	vCurPos += m_vForwardVector * fBulletSpeed;
	//Add the inherited velocity from the plane.
	vCurPos += m_vInheritedVelocity;
	//Store the new value & update.
	XMStoreFloat4(&m_v4Pos, vCurPos);
	UpdateMatrices();
}

// Used only to set the initial position by decomposing the parent's world matrix.
// These values will then be set as the bullet's position & rotation.
void Bullet::SetWorldPosition()
{
	XMVECTOR scale, rot, trans;
	// Decompose will save having to step through each parent.
	XMMatrixDecompose(&scale, &rot, &trans, spawnParent->GetNodeWorldMatrix());

	XMStoreFloat4(&m_v4Rot, rot);
	XMStoreFloat4(&m_v4Pos, trans);

}

// Check if the time the bullet has been alive, then return true if it has exceeded its max life time.
bool Bullet::DestroyTime()
{
	if (fTimeAlive < fLifeTime)
	{
		fTimeAlive += 0.05f;
		return false;
	}
	else
	{
		return true;
	}
}

// Updates the world matrix by taking scaling / translation / rotation from stored values that have been changed through update.
void Bullet::UpdateMatrices(void)
{
	XMMATRIX mTrans, scale, mRot;

	// Calculate WorldMatrix for plane based on Euler rotation angles and position data.
	scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Pos));
	mRot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_v4Rot));
	m_mBulletWorldMatrix = scale * mRot *  mTrans;

	
	m_vForwardVector = XMVector3TransformNormal(forward, m_mBulletWorldMatrix);
}

