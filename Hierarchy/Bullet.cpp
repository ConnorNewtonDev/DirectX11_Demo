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

	m_vForwardVector = XMVectorZero();
	SetWorldPosition();
	LoadResources();
	UpdateMatrices();
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


	XMVECTOR vCurPos = XMLoadFloat4(&m_v4Pos);
	vCurPos += m_vForwardVector * fBulletSpeed;

	//Need to find a way to Inverse X axis?

	vCurPos += m_vInheritedVelocity;

	XMStoreFloat4(&m_v4Pos, vCurPos);
	UpdateMatrices();
}

void Bullet::SetWorldPosition()
{

	XMStoreFloat4(&m_v4Pos, spawnParent->GetNodeWorldMatrix().r[3]);

	XMVECTOR scale, rot, trans;
	XMMatrixDecompose(&scale, &rot, &trans, spawnParent->GetNodeWorldMatrix());

	XMStoreFloat4(&m_v4Rot, rot);

}

void Bullet::UpdateMatrices(void)
{
	XMMATRIX mTrans, scale, mRot;

	// Calculate m_mWorldMatrix for plane based on Euler rotation angles and position data.
	mTrans = XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4Pos));
	scale = XMMatrixScaling(0.1f, 0.1f, 0.1f);
	mRot = XMMatrixRotationQuaternion(XMLoadFloat4(&m_v4Rot));
	m_mBulletWorldMatrix = scale * mRot *  mTrans;

	
	m_vForwardVector = XMVector3TransformNormal(forward, m_mBulletWorldMatrix);
}

