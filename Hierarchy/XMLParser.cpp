#include "XMLParser.h"

void XMLParser::Init(std::string filePath)
{
	const char* path = filePath.c_str();
	xml.LoadFile(path);

	//GetNode("root");
}

XMLParser::XMLParser()
{
}

XMLParser::~XMLParser()
{
}

void XMLParser::GetNode(std::string name)
{
	tinyxml2::XMLElement *root;
	tinyxml2::XMLElement *child;

	root = xml.RootElement()->FirstChildElement()->NextSiblingElement();
	child = root->FirstChildElement("library_animations");
	
	while(child != NULL)
	{
		if (child->Name() == name)
		{

		}

		//Iterate
		child = child->NextSiblingElement();
	}

	

}

struct AnimationFrame
{

};
