#include "Bullet.h"

// Initialise static class variables.
CommonMesh* Bullet::s_pBulletMesh = NULL;
bool Bullet::s_bResourcesReady = false;

//---- Public ----//
Bullet::Bullet(NodeT* spawner, XMVECTOR inheritedVelocity)
{
	m_mBulletWorldMatrix = XMMatrixIdentity();
	spawnParent = spawner;
	m_vInheritedVelocity = inheritedVelocity;
	m_v4Pos = XMFLOAT4(0,0,0,0);
	m_v4Rot = XMFLOAT4(0,0,0,0);

	SetWorldPosition();
	LoadResources();

	fBulletSpeed = 5.0f;

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


	XMVECTOR vCurPos = XMLoadFloat4(&m_v4Pos);
	vCurPos += m_vForwardVector * fBulletSpeed;

	//Need to find a way to Inverse X axis?

	vCurPos += m_vInheritedVelocity;

	XMStoreFloat4(&m_v4Pos, vCurPos);
}

void Bullet::SetWorldPosition()
{

	m_vInheritedVelocity = XMVector3Cross(spawnParent->parent->GetNodeWorldMatrix().r[0], spawnParent->parent->GetNodeWorldMatrix().r[1]);
	//TODO:: Fix Local Rotation


	XMStoreFloat4(&m_v4Pos, spawnParent->GetNodeWorldMatrix().r[3]);
	XMStoreFloat4(&m_v4Rot, spawnParent->GetNodeWorldRotation(XMLoadFloat4(&m_v4Rot)));
}

void Bullet::UpdateMatrices(void)
{
	XMMATRIX mRotX, mRotY, mRotZ, mTrans, scale;
	// Calculate m_mWorldMatrix for plane based on Euler rotation angles and position data.
	mRotX = XMMatrixRotationX(XMConvertToRadians(m_v4Rot.x));
	mRotY = XMMatrixRotationY(XMConvertToRadians(m_v4Rot.y));
	mRotZ = XMMatrixRotationZ(XMConvertToRadians(m_v4Rot.z));
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Pos));
	scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);

	// Then concatenate the matrices to calculate m_mBulletWorldMatrix
	m_mBulletWorldMatrix = scale * mRotX *  mRotZ * mRotY *  mTrans;

	m_vForwardVector = XMVector3Cross(m_mBulletWorldMatrix.r[0], m_mBulletWorldMatrix.r[1]);

}

