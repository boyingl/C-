#ifndef _MAKEFILE_
#define _MAKEFILE_
#include <string>
#include <iostream>
#include "target.h"

const int maxTargets = 20;

struct Makefile {   
  std::ostream &out; 
  int numTargets;
  Target* files[maxTargets];
  int time;

  Makefile(std::ostream &out = std::cout);
  ~Makefile();
  
  //return index of target, maxTargets if not exist
  int exist(const std::string &t);

  //add target if not exist and return its index
  //simply return index if exist
  int addFile(const std::string &t);

  void addDepend(const std::string &t, const std::string &d);

  void changeTarget(const std::string &t);

  void rebuild(const std::string &t);

};

#endif


#ifndef _TARGET_H_
#define _TARGET_H_
#include <iostream>
#include <string>

const int maxDepends = 10;

struct Target {  
  std::ostream &out; 
  std::string name;
  bool leaf;
  int updateTime;
  int numDepends;
  Target* depends[maxDepends];
  //if the target is rebuilt after build command
  bool isBuilt;


  Target(const std::string &name, std::ostream &out = std::cout);
  ~Target();

  bool isLeaf() const;
  void addDepend(Target *d);
  void update(int time);
  int lastUpdated() const;
  //update time stamp of all non-leaf node rooting at calling object
  void updateAll(const int time);
  void build();

};

#endif

