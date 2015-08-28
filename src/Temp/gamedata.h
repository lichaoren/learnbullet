#ifndef GAMEDATA__H
#define GAMEDATA__H
#include <string>
#include <map>

#include "tinyxml.h"
#include "vector2f.h"


class Gamedata {
public:
  static Gamedata& getInstance();
  ~Gamedata();
  void printData() const;

  TiXmlElement* getElem(const std::string&) const;
  template<typename T>
  T getAttr(const std::string& elem, const std::string& attr) const {
    T v;
    if ( TIXML_SUCCESS != getElem(elem)->QueryValueAttribute<T>(attr, &v)) {
      std::cerr << "can't find attribute '" << attr << "' in " << elem << std::endl;
      exit(0);
    }
    return v;
  }
//  int getValue(const std::string&, const std::string&) const;
//  float getFloat(const std::string&, const std::string&) const;
//  const std::string& getStr(const std::string&, const std::string&) const;

  float getRandInRange(int min, int max) const;
  float getRandFloat(float min, float max) const;

private:
  std::string fname;
  TiXmlDocument doc;

  Gamedata(const std::string& fn = "xmlSpec/game.xml");
  Gamedata(const Gamedata&);
  Gamedata& operator=(const Gamedata&);
};

#endif
