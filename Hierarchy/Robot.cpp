#include "Robot.h"

Robot::Robot(float fX, float fY, float fZ, float fRotY)
{
	parser = new XMLParser();
	parser->Init("Resources/Maya Files/RobotIdleAnim.dae");
	m_mWorldMatrix = XMMatrixIdentity();
	//	m_mWorldMatrix *= XMMatrixScaling(0.25f, 0.25f, 0.f);
	LoadNodes(fX, fY, fZ, fRotY);

	parser->GetNode("root.rotateX");
}

Robot::~Robot()
{
}

void Robot::LoadResources()
{
}

void Robot::ReleaseResources()
{
	pelvis->ReleaseResources();
	for (int i = 0; i < robotNodes.size(); i++)
	{
		robotNodes[i]->ReleaseResources();
	}
}

void Robot::LoadNodes(float fX, float fY, float fZ, float fRotY)
{
	//Root
	root = new NodeT(fX, fY, fZ, fRotY, "");
	robotNodes.push_back(root);
	//Pelvis
	pelvis = new NodeT(-0.250011f / 10, 15.25000f / 10, -0.000005f / 10, 0.0f, "Resources/Robot/pelvis.x");
	robotNodes.push_back(pelvis);
	//Body
	body = new NodeT(0.500099f / 10, 43.749992f / 10, 0.000003f / 10, 0.0f, "Resources/Robot/body.x");
	robotNodes.push_back(body);
	//Left Shoulder
	left_shoulder = new NodeT(46.000000f / 10, 0.000000f / 10, -0.009992f / 10, 0.0f, "Resources/Robot/left_shoulder.x");
	robotNodes.push_back(left_shoulder);
	//Left Elbow
	left_elbow = new NodeT(34.250019f / 10, -0.499817f / 10, -0.004262f / 10, 0.0f, "Resources/Robot/left_elbow.x");
	robotNodes.push_back(left_elbow);
	//Left Wrist
	left_wrist = new NodeT(55.250008f / 10, -0.999710f / 10, 0.003968f / 10, 0.0f, "Resources/Robot/left_wrist.x");
	robotNodes.push_back(left_wrist);
	//Right Shoulder
	right_shoulder = new NodeT(-44.500023f / 10, 0.500000f / 10, -0.000021f / 10, 0.0f, "Resources/Robot/right_shoulder.x");
	robotNodes.push_back(right_shoulder);
	//Right Elbow
	right_elbow = new NodeT(-33.999996f / 10, 0.250229f / 10, -0.000194f / 10, 0.0f, "Resources/Robot/right_elbow.x");
	robotNodes.push_back(right_elbow);
	//Right Wrist
	right_wrist = new NodeT(-60.000381f / 10, -1.750183f / 10, 0.007156 / 10, 0.0f, "Resources/Robot/right_wrist.x");
	robotNodes.push_back(right_wrist);
	//Neck
	neck = new NodeT(0.249983/ 10, 36.625015 / 10, 25.999998 / 10, 0.0f, "Resources/Robot/neck.x");
	robotNodes.push_back(neck);
	//Left Hip
	left_hip = new NodeT(19.500000f / 10, -7.724991f / 10, 0.000000f / 10, 0.0f, "Resources/Robot/left_hip.x");
	robotNodes.push_back(left_hip);
	//Left Knee
	left_knee = new NodeT(0.000006f / 10, -22.200001f / 10, 0.000000f / 10, 0.0f, "Resources/Robot/left_knee.x");
	robotNodes.push_back(left_knee);
	//Left Ankle
	left_ankle = new NodeT(-0.800152f / 10, -36.399994f / 10, -0.000098f / 10, 0.0f, "Resources/Robot/left_ankle.x");
	robotNodes.push_back(left_ankle);
	//Right Hip
	right_hip = new NodeT(-19.500000f / 10, -7.724991f / 10, 0.000000f / 10, 0.0f, "Resources/Robot/right_hip.x");
	robotNodes.push_back(right_hip);
	//Right Knee
	right_knee = new NodeT(0.000006f / 10, -22.200001f / 10, 0.000000f / 10, 0.0f, "Resources/Robot/right_knee.x");
	robotNodes.push_back(right_knee);
	//Right Ankle
	right_ankle = new NodeT(-0.199911f/ 10, -36.799995f/ 10, 0.000039f / 10, 0.0f, "Resources/Robot/right_ankle.x");
	robotNodes.push_back(right_ankle);
}

void Robot::Draw(void)
{
	
	pelvis->Draw();
	body->Draw();
	left_shoulder->Draw();
	left_elbow->Draw();
	left_wrist->Draw();
	right_shoulder->Draw();
	right_elbow->Draw();
	right_wrist->Draw();
	neck->Draw();
	left_hip->Draw();
	left_knee->Draw();
	left_ankle->Draw();
	right_hip->Draw();
	right_knee->Draw();
	right_ankle->Draw();


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
	root->UpdateMatrices(m_mWorldMatrix);
	pelvis->UpdateMatrices(root->GetNodeWorldMatrix());
	body->UpdateMatrices(pelvis->GetNodeWorldMatrix());
	left_shoulder->UpdateMatrices(body->GetNodeWorldMatrix());
	left_elbow->UpdateMatrices(left_shoulder->GetNodeWorldMatrix());
	left_wrist->UpdateMatrices(left_elbow->GetNodeWorldMatrix());
	right_shoulder->UpdateMatrices(body->GetNodeWorldMatrix());
	right_elbow->UpdateMatrices(right_shoulder->GetNodeWorldMatrix());
	right_wrist->UpdateMatrices(right_elbow->GetNodeWorldMatrix());
	neck->UpdateMatrices(body->GetNodeWorldMatrix());
	left_hip->UpdateMatrices(root->GetNodeWorldMatrix());	//pelvis->GetNodeWorldMatrix()
	left_knee->UpdateMatrices(left_hip->GetNodeWorldMatrix());
	left_ankle->UpdateMatrices(left_knee->GetNodeWorldMatrix());
	right_hip->UpdateMatrices(root->GetNodeWorldMatrix());//pelvis->GetNodeWorldMatrix()
	right_knee->UpdateMatrices(right_hip->GetNodeWorldMatrix());
	right_ankle->UpdateMatrices(right_knee->GetNodeWorldMatrix());
	/*if (!robotNodes.empty())
	{
		for (int i = 0; i < robotNodes.size(); i++)
		{
			robotNodes[i]->UpdateMatrices(m_mWorldMatrix);
		}
	}	*/
}