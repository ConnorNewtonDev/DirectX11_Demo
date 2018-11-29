#include "Robot.h"

Robot::Robot(float fX, float fY, float fZ, float fRotY)
{
	m_mWorldMatrix = XMMatrixIdentity();
	LoadNodes(fX, fY, fZ, fRotY);
}

Robot::~Robot()
{
}

void Robot::LoadResources()
{
}

void Robot::ReleaseResources()
{
	//robotNodes[0]->ReleaseResources();
	pelvis->ReleaseResources();
}

void Robot::LoadNodes(float fX, float fY, float fZ, float fRotY)
{
	//Pelvis
	pelvis = new NodeT(fX, fY, fZ, fRotY, "Resources/Robot/pelvis.x");
	robotNodes.push_back(pelvis);

}

void Robot::Draw(void)
{
	if(pelvis != NULL)
		pelvis->Draw();
	/*if (!robotNodes.empty())
	{
		for (int i = 0; i < robotNodes.size(); i++)
		{
			robotNodes[i]->Draw();
		}
	}*/


}

void Robot::SetWorldPosition(float fX, float fY, float fZ)
{

}

void Robot::Update()
{
	UpdateMatrices();
}

void Robot::UpdateMatrices()
{

	pelvis->UpdateMatrices(m_mWorldMatrix);
	/*if (!robotNodes.empty())
	{
		for (int i = 0; i < robotNodes.size(); i++)
		{
			robotNodes[i]->UpdateMatrices(m_mWorldMatrix);
		}
	}	*/
}