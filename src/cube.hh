#ifndef CUBE_HH
#define CUBE_HH

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include "geometry3.hh"

using namespace std;

/*void printcoords(vector<coord3d> coords){
  cout << "Printing coords:\n";
  int i = 0;
  for (coord3d vec : coords) {
    ++i;
    cout << vec <<"\n";
  }
  cout << "There are " << i << " coord3d's inside the vector.\n";
}*/
  
class Cube {
  vector<coord3d> field;
  int xrange;
  int yrange;
  int zrange;


  public:
  vector<double> origin;
  vector<double> spacing;
  void testfunc();
  Cube(string filename);
  vector<vector<int>> gettropplaneZ(double zcoord) const;
  vector<vector<int>> gettropplane(string filename, int bfielddir, int fixeddir, double fixedcoord) const;
  void splitgrid(string gridfile, string weightfile, int bfielddir) const;
  void writetropplane(string filename, vector<vector<int>> tropicities) const;
  void writecube(const string& filename) const;
  coord3d getvector(coord3d position) const;
  coord3d getvector3(coord3d position) const;
  bool outofbounds (coord3d position) const; 
};

#endif
