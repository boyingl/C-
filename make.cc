#include "makefile.h"
#include <iostream>
#include <string>
using namespace std;

Makefile::Makefile(ostream &out) : 
out{out}, numTargets{0}, time{0} {}


Makefile::~Makefile() {
  for(int i = 0; i < numTargets; i++) delete files[i];
}


//return index if exist, return maxTargets if not
int Makefile::exist(const string &t){
  for(int i = 0; i < numTargets; i++){
    if(files[i]->name == t) return i;
  }
  return maxTargets;
}


//add to target if not exist, and return the index of the target
int Makefile::addFile(const std::string &t){

  //do nothing if target exists
  int index = exist(t);
  if(index != maxTargets) return index;
  
  //output error to stdout if exceed maxTargets
  if(numTargets >= maxTargets){
    out << "Max targets exceeded" << endl;
    return maxTargets;
  }

  //add new target
  files[numTargets] = new Target(t, out);
  numTargets ++;
  return (numTargets - 1);
}


void Makefile::addDepend(const string &t, const string &d) {
  int master = addFile(t);
  int depen = addFile(d);

  //exit if cannot add mentioned files
  if(master == maxTargets || depen == maxTargets) return;
  files[master]->addDepend(files[depen]);
  return;
}


void Makefile::changeTarget(const string &t) {
  int index = exist(t);
  time ++;
  //if target does not exist
  if(index == maxTargets) return;
  Target* cur = files[index];
  //is leaf, update target
  if(cur->isLeaf()){
    cur->update(time);
    out << cur->name << " updated at time " << time << endl;
  }  
  else out << "Cannot update non-leaf object" << endl; 
  return;
}

void Makefile::rebuild(const string &t) {
  int index = exist(t);

  //if targets does not exist, return
  if(index == maxTargets)  return;
  Target* cur = files[index];
  cur->build();

  //if rebuit was done
  if(cur->isBuilt){
    //update updateTime of the target & its non-leaf dependencies
    cur->updateAll(time);
  }
  return;
}


#include "target.h"
#include <string>
using namespace std;

Target::Target(const string &name, ostream &out) : 
out{out}, name{name}, leaf{true}, updateTime{0}, numDepends{0}, isBuilt{false} {}


Target::~Target(){}


bool Target::isLeaf() const {
  return leaf;
}


void Target::addDepend(Target *d) {
   
  bool exist = false;
  string depName = d->name;
  for(int i = 0; i < numDepends; i++){
    if(depName == depends[i]->name){ 
      exist = true;
      break;
    }   	
  }

  //do nothing if dependency already exist
  if(exist) return;

  //print error message if max dependencies exceeded
  if(numDepends >= maxDepends){
    out << "Max dependencies exceeded" << endl;
    return;
  }
 
  //not exist and max not exceeded add new dependency
  depends[numDepends] = d;
  numDepends ++;
  leaf = false;
  return;
}


//update modified time
void Target::update(int time) {
  updateTime = time;
  return;
}


//return last updated time
int Target::lastUpdated() const {
  return updateTime;
}


//update time stamp of all non-leaf in the subtree rooting calling target
void Target::updateAll(const int time){
  for(int i = 0; i < numDepends; i++){
    Target* cur = depends[i];
    if(! cur->isLeaf())  cur->updateAll(time);
  }
  update(time);
  return;
}


void Target::build() {
  isBuilt = false;
  //leaf target, do nothing
  if(leaf)  return;

  bool needRebuild = false;

  //check each dependency
  for(int i = 0; i < numDepends; i++){
    Target* dep = depends[i];
    //leaf dependency, see if it was updated before
    if(dep->isLeaf()){
      needRebuild = (dep->lastUpdated() > updateTime)? true : needRebuild;
    }

    //nonleaf dependency, build it
    else{
      dep->build();
      if(dep->isBuilt) needRebuild = true;
    } 
  }
  if(needRebuild){
    out << "Building " << name << endl;
    isBuilt = true;
  }
  return;	
}


