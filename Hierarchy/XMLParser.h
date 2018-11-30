#ifndef  XMLPARSER_H
#define XMLPARSER_H

#include "../tinyxml2/tinyxml2.h"
#include <iostream>

class XMLParser
{
public:
	
	XMLParser();
	~XMLParser();
	void Init(std::string filePath);
	void GetNode(std::string root);
private:


public:
	tinyxml2::XMLDocument xml;

};
#endif
