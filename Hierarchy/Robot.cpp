#include "Robot.h"

Robot::Robot(float fX, float fY, float fZ, float fRotY)
{
	LoadNodes();
}

Robot::~Robot()
{
}

void Robot::LoadResources()
{
}

void Robot::ReleaseResources()
{

}

void Robot::LoadNodes()
{
	//Root
	Node activeNode = Node(1.027778, 75.644722,0.00, "Root");
	robotNodes.push_back(activeNode);
	//Pelvis
	activeNode = Node(&robotNodes[0], "Resources/Robot/pelvis.x", -0.250011f, 15.250000f, -0.000005f, "Pelvis");
	robotNodes.push_back(activeNode);
	robotNodes[0].children.push_back(&activeNode);
}

void Robot::Draw()
{
	robotNodes[0].Draw();
}

void Robot::SetWorldPosition(float fX, float fY, float fZ)
{

}

void Robot::Update()
{
	robotNodes[0].Update();
}

void Robot::UpdateMatrices()
{

}