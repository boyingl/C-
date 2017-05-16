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

