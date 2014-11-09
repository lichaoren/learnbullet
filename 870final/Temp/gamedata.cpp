#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <limits>
#include <cmath>
#include <ctime>

#include "utils.h"
#include "gamedata.h"

Gamedata& Gamedata::getInstance() {
  static Gamedata gamedata;
  return gamedata;
}

Gamedata::~Gamedata( ) { }

Gamedata::Gamedata(const std::string& fn ) :
  fname(fn),
  doc(fname.c_str())
{
  if (!doc.LoadFile(fname.c_str())) {
    std::cerr << doc.ErrorDesc() << std::endl;
    exit(0);
  }

  TiXmlElement* root = doc.FirstChildElement();
  if(root == NULL)
  {
      std::cerr << "Failed to load file: No root element." << std::endl;
      doc.Clear();
      exit(0);
  }
}

void Gamedata::printData() const {
  dump_to_stdout(fname.c_str());
}

TiXmlElement* Gamedata::getElem(const std::string& name) const {
  TiXmlElement* root = const_cast<TiXmlElement*>(doc.FirstChildElement());
  for( TiXmlElement* pChild = root->FirstChildElement(); pChild != 0; pChild = pChild->NextSiblingElement() ) {
    if ( !std::string(pChild->Value()).compare(name) )
      return pChild;
  }
  std::cerr << "can't find element " << name << std::endl;
  exit(0);
}

float Gamedata::getRandInRange(int min, int max) const {
  return min + (rand()/(std::numeric_limits<int>::max()+1.0f))*(max-min);
}

float Gamedata::getRandFloat(float min, float max) const {
  return min + (rand() / (RAND_MAX + 1.0f)) * (max - min);
}


//
//bool Gamedata::getXmlBool(const std::string& tag) const {
//  std::map<std::string, std::string>::const_iterator ptr = gameData.find(tag);
//  if ( ptr == gameData.end() )
//    throw std::string("Game: Didn't find boolean tag ")+tag+std::string(" in xml");
//  else {
//    if ( ptr->second == "true" ) return true;
//    else return false;
//  }
//}
//
//int Gamedata::getXmlInt(const std::string& tag) const {
//  std::map<std::string, std::string>::const_iterator ptr = gameData.find(tag);
//  if ( ptr == gameData.end() )
//    throw std::string("Game: Didn't find integer tag ")+tag+std::string(" in xml");
//  else {
//    std::stringstream strm;
//    strm << ptr->second;
//    int data;
//    strm >> data;
//    return data;
//  }
//}
//
//float Gamedata::getXmlFloat(const std::string& tag) const {
//  std::map<std::string, std::string>::const_iterator ptr = gameData.find(tag);
//  if ( ptr == gameData.end() )
//    throw std::string("Game: Didn't find float tag ")+tag+std::string(" in xml");
//  else {
//    std::stringstream strm;
//    strm << ptr->second;
//    float data;
//    strm >> data;
//    return data;
//  }
//}
//
//const std::string& Gamedata::getXmlStr(const std::string& tag) const {
//  std::map<std::string, std::string>::const_iterator ptr = gameData.find(tag);
//  if ( ptr == gameData.end() )
//    throw std::string("Game: Didn't find std::string tag ")+tag+std::string(" in xml");
//  else return ptr->second;
//}
//


