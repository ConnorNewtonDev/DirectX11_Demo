#include "Bullet.h"

// Initialise static class variables.
CommonMesh* Bullet::s_pBulletMesh = NULL;
bool Bullet::s_bResourcesReady = false;

//---- Public ----//
Bullet::Bullet(XMMATRIX m_mGunWorldMatrix)
{
	LoadResources();
	SetWorldPosition(m_mGunWorldMatrix);
	fBulletSpeed = 0.5f;

	//m_v4Pos = XMFLOAT4(0.0f, 2.0f, 0.0f, 0.0f);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	//MoveForward();
	UpdateMatrices();
	Draw();
}

void Bullet::Draw(void)
{
	Application::s_pApp->SetWorldMatrix(m_mBulletWorldMatrix);
	s_pBulletMesh->Draw();
}

void Bullet::LoadResources(void)
{
	s_pBulletMesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Plane/gun.x");
}

void Bullet::ReleaseResources(void)
{
	delete s_pBulletMesh;
}

//---- Private ----//

void Bullet::MoveForward()
{
	XMVECTOR vCurPos = XMLoadFloat4(&m_v4Pos);
	vCurPos = m_vForwardVector * fBulletSpeed;
	XMStoreFloat4(&m_v4Pos, vCurPos);
}

void Bullet::SetWorldPosition(XMMATRIX m_mGunWorldMatrix)
{
	XMVECTOR mScale, mRot, mTrans;
	XMMatrixDecompose(&mScale ,&mRot, &mTrans, m_mGunWorldMatrix);

	XMStoreFloat4(&m_v4Pos, mTrans);
	XMStoreFloat4(&m_v4Rot, mRot);


	UpdateMatrices();
}

void Bullet::UpdateMatrices(void)
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans;
	// Calculate m_mWorldMatrix for plane based on Euler rotation angles and position data.
	mRotX = XMMatrixRotationX(m_v4Rot.x);
	mRotY = XMMatrixRotationY(m_v4Rot.y);
	mRotZ = XMMatrixRotationZ(m_v4Rot.z);
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Pos));
	// Then concatenate the matrices to calculate m_mBulletWorldMatrix
	m_mBulletWorldMatrix = mRotZ * mRotX * mRotY * mTrans;

	m_vForwardVector = XMVector3Cross(m_mBulletWorldMatrix.r[0], m_mBulletWorldMatrix.r[1]);
}

