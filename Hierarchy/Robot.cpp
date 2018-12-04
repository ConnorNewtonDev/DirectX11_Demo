#include "Robot.h"

Robot::Robot(float fX, float fY, float fZ, float fRotY)
{
	m_mWorldMatrix = XMMatrixIdentity();
	LoadNodes(fX, fY, fZ, fRotY);
}

Robot::~Robot()
{
}

//Step through the vector of robotNodes and release.
void Robot::ReleaseResources()
{
	for (int i = 0; i < robotNodes.size(); i++)
	{
		robotNodes[i]->ReleaseResources();
	}
}
//Adds robot components to the robotNodes vector.
//NodeT takes in (xPos, yPos, zPos, YRot, Filepath, parent<NodeT>).
void Robot::LoadNodes(float fX, float fY, float fZ, float fRotY)
{
	//Root 0
	robotNodes.push_back(new NodeT(fX, fY, fZ, fRotY, "", NULL));
	//Pelvis 1
	robotNodes.push_back(new NodeT(-0.250011f / 10, 15.25000f / 10, -0.000005f / 10, 0.0f, "Resources/Robot/pelvis.x", robotNodes[0]));
	//Body 2
	robotNodes.push_back(new NodeT(0.500099f / 10, 43.749992f / 10, 0.000003f / 10, 0.0f, "Resources/Robot/body.x", robotNodes[1]));
	//Left Shoulder 3
	robotNodes.push_back(new NodeT(46.000000f / 10, 0.000000f / 10, -0.009992f / 10, 0.0f, "Resources/Robot/left_shoulder.x", robotNodes[2]));
	//Left Elbow 4
	robotNodes.push_back(new NodeT(34.250019f / 10, -0.499817f / 10, -0.004262f / 10, 0.0f, "Resources/Robot/left_elbow.x", robotNodes[3]));
	//Left Wrist 5
	robotNodes.push_back(new NodeT(55.250008f / 10, -0.999710f / 10, 0.003968f / 10, 0.0f, "Resources/Robot/left_wrist.x", robotNodes[4]));
	//Right Shoulder 6
	robotNodes.push_back(new NodeT(-44.500023f / 10, 0.500000f / 10, -0.000021f / 10, 0.0f, "Resources/Robot/right_shoulder.x", robotNodes[2]));
	//Right Elbow 7
	robotNodes.push_back(new NodeT(-33.999996f / 10, 0.250229f / 10, -0.000194f / 10, 0.0f, "Resources/Robot/right_elbow.x", robotNodes[6]));
	//Right Wrist 8
	robotNodes.push_back(new NodeT(-60.000381f / 10, -1.750183f / 10, 0.007156 / 10, 0.0f, "Resources/Robot/right_wrist.x", robotNodes[7]));
	//Neck 9
	robotNodes.push_back(new NodeT(0.249983 / 10, 36.625015 / 10, 25.999998 / 10, 0.0f, "Resources/Robot/neck.x", robotNodes[2]));
	//Left Hip 10
	robotNodes.push_back(new NodeT(19.500000f / 10, -7.724991f / 10, 0.000000f / 10, 0.0f, "Resources/Robot/left_hip.x", robotNodes[0]));
	//Left Knee 11
	robotNodes.push_back(new NodeT(0.000006f / 10, -22.200001f / 10, 0.000000f / 10, 0.0f, "Resources/Robot/left_knee.x", robotNodes[10]));
	//Left Ankle 12
	robotNodes.push_back(new NodeT(-0.800152f / 10, -36.399994f / 10, -0.000098f / 10, 0.0f, "Resources/Robot/left_ankle.x", robotNodes[11]));
	//Right Hip 13
	robotNodes.push_back(new NodeT(-19.500000f / 10, -7.724991f / 10, 0.000000f / 10, 0.0f, "Resources/Robot/right_hip.x", robotNodes[0]));
	//Right Knee 14
	robotNodes.push_back(new NodeT(0.000006f / 10, -22.200001f / 10, 0.000000f / 10, 0.0f, "Resources/Robot/right_knee.x", robotNodes[13]));
	//Right Ankle 15
	robotNodes.push_back(new NodeT(-0.199911f / 10, -36.799995f / 10, 0.000039f / 10, 0.0f, "Resources/Robot/right_ankle.x", robotNodes[14]));
}

//Step through the vector of robotNodes and call their draw.
void Robot::Draw(void)
{
	for (int i = 0; i < robotNodes.size(); i++)
	{
		robotNodes[i]->Draw();
	}
}

void Robot::Update()
{
	UpdateMatrices();
}

//Step through the vector of robotNodes and update their matricies.
void Robot::UpdateMatrices()
{
	for (int i = 0; i < robotNodes.size(); i++)
	{
		robotNodes[i]->UpdateMatrices();
	}
}