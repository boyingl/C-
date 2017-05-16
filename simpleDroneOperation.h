#ifndef __DRONE_H__
#define __DRONE_H__
struct Position {
  int ew, ns;
  Position( int ew = 0, int ns = 0 );
};

struct Drone {
  Drone();
  ~Drone();
  void forward(); 
  void backward(); 
  void left();
  void right();
  Position current() const;
  int totalDistance() const;
  int manhattanDistance() const;
  bool repeated() const;
  
  Position visited[50];
  int numVisited;
  Position cur;
  enum direction{ north = 0, east, south, west};
  direction face;
  int distance;

};
#endif
