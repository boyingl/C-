#include "drone.h"
#include <iostream>
using namespace std;

Position::Position(int ew, int ns):ew{ew}, ns{ns}{}

Drone::Drone():numVisited{0},
cur{Position(0,0)}, face{north}, distance{0}{}

Drone:: ~Drone(){}

void Drone::forward(){
  bool repeat = repeated();
  //if field visted reached 50 
  //and a new place is being visited
  //violate assumption
  if(numVisited == 50 && (!repeat)){
    cerr << "visited more than 50 places";
    return;
  }
  //if location is new, document it
  if(!repeat) {
    visited[numVisited] = Position(cur.ew, cur.ns);
    numVisited ++;
  }

  distance ++;
  //depending on where the drone faces, forward has different effect on location coordinate
  int deltax = (2-face)%2;
  int deltay = (1-face)%2;
  cur.ew += deltax;
  cur.ns += deltay;
  return;
}
 
void Drone::backward(){
  face = static_cast<direction>((face +2)%4);
  forward();
  face = static_cast<direction>((face +2)%4);
  return;
} 

void Drone::left(){
  face = static_cast<direction>((face -1 +4)%4); 
  return;
}

void Drone::right(){
  face = static_cast<direction>((face +1)%4);
  return;
}

Position Drone::current() const{
  return cur;
}

int Drone::totalDistance() const{
  return distance;
}

int Drone::manhattanDistance() const{
  int mdx = (cur.ew > 0)? cur.ew : (-cur.ew);
  int mdy = (cur.ns > 0)? cur.ns : (-cur.ns);
  return (mdx + mdy);
}

bool Drone::repeated() const{
  for(int i = 0; i < numVisited; i++){
    if(visited[i].ew == cur.ew && visited[i].ns == cur.ns) return true;
  }
  return false;
}
  
  


