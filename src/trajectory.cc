
#include <cassert>
#include <iostream>
#include <vector>

#include "auxiliary.hh"
#include "geometry3.hh"
#include "trajectory.hh"

using namespace std;


void trajectory::extend_euler(const Cube& cube){  //Euler
  coord3d nextposition(positions[positions.size()-1]+directions[directions.size()-1].normalised()*step_length);
  if (cube.outofbounds(nextposition)) {return;}
  append(nextposition,cube.getvector(nextposition));  
  }



// the numbers in extend-rungekutta are not magic numbers. (see wikipedia article for runge-kutta method).
// any other numbers (like "10000" or "0.05" are probably magic numbers.
// beware
void trajectory::extend_rungekutta(const Cube& cube){ 
  coord3d c1 = positions[positions.size()-1];
  coord3d k1 = cube.getvector(c1);
  k1 = k1.normalised()*step_length;
  coord3d c2 = positions[positions.size()-1]+k1*0.5;
  coord3d v1 = cube.getvector(c2);
  coord3d k2 = v1.normalised()*step_length;
  coord3d c3 = positions[positions.size()-1]+k2*0.5;
  coord3d v2 = cube.getvector(c3);
  coord3d k3 = v2.normalised()*step_length;
  coord3d c4 = positions[positions.size()-1]+k3;
  coord3d v3 = cube.getvector(c4);
  coord3d k4 = v3.normalised()*step_length;
  coord3d nextposition(positions[positions.size()-1]+(k1+k2*2.0+k3*2.0+k4)/6.0);
  coord3d c5 = cube.getvector(nextposition);
  append(nextposition,c5);  
}

void trajectory::printstatus(const Cube& cube){

} 

void trajectory::complete(const Cube& cube){
  //const double threshold = 1e-2;
  //if (directions[0].norm() < threshold) {oob=true; return;} //if the intensity is vero low, don't bother completing. classify as "oob"
  //the above is commented out because i didn't figure out what would be a good value for this threshold
  //if someone does, this would probably save some computational time
  step_length=cube.spacing[0]*0.05;

  int step = 0;
  double dist2farthest = -1; //if this is set at 0 at declaration, the following while loop will never run

  while ((positions[positions.size()-1]-positions[0]).norm()>0.2*dist2farthest){ //if we get to a point that is less than SOME WELL-GUESSED FRACTION (1/5) of the longest distance in the trajectory
    extend_rungekutta(cube);							//(looking back on this this cant be very effective... maybe the next summer worker can come up with a computationally cheaper alternative)
    step++;
    if (cube.outofbounds(positions[positions.size()-1]+directions[directions.size()-1].normalised()*step_length)){
      oob = true;
      return;
    }
  
    if ((positions[positions.size()-1]-positions[0]).norm()>dist2farthest) {
      dist2farthest=(positions[positions.size()-1]-positions[0]).norm();
    }

    if (step>10000){ //a single trajectory must not be more than this WELL-GUESSED NUMBER 10 000 OF steps
      step=0;
      step_length+=2;
      int size = positions.size();
      for (int a=0;a<size-1;a++){ //also this can't be very effective, there must be a way to wipe the positions and directions lists and create new blanks ones that is cheaper than this
        positions.pop_back();     
        directions.pop_back();
      }
      dist2farthest = -1;
    }
  }
}
      


int trajectory::classify(const Cube& cube, int bfielddir) const { 
  coord3d bfield;
  switch(bfielddir) {
    case 0:
      {
      bfield = coord3d(1,0,0);
      break;
      }
    case 1:
      {
      bfield = coord3d(-1,0,0);
      break;
      }
    case 2:
      {
      bfield = coord3d(0,1,0);
      break;
      }
    case 3:
      {
      bfield = coord3d(0,-1,0);
      break;
      }
    case 4:
      {
      bfield = coord3d(0,0,1);
      break;
      }
    case 5:
      {
      bfield = coord3d(0,0,-1);
      break;
      }
    default:
      {
      cout<<"bfielddir value wasn't 0-5.\n";
      return 7;
      }
  }
  
  coord3d crossum(0,0,0);

  if (oob==true) {return 0;}

  for (int i = 1; i<directions.size(); i++){
    crossum+=positions[i-1].cross(positions[i]);
  }
  crossum+=positions[positions.size()-1].cross(positions[0]);

  if (bfield.dot(crossum) < 0) { //counter-clockwise (paratropic) 
    return -1;
  }
  else if (bfield.dot(crossum) > 0) { //clockwise (diatropic)
    return 1;
  }
  else {                         //neither. something happened  // lnw: I suppose that never happens? // jaakko: i would also suppose that never happens, but in an _arbitrary_ vector field such a trajectory could exist.
    return 2;
  }

}

void trajectory::write2mathematicalist(string filename) {
  ofstream outputfile;
  outputfile.open(filename);
  outputfile<<"traj = {{";
  for (int i = 0; i<positions.size();i++) {    
    outputfile<<"{"<<positions[i][0]<<","<<positions[i][1]<<","<<positions[i][2]<<"}";
    if(i<positions.size()-1) {outputfile<<",";}
  }
  outputfile<<"}}";
}

bool trajectory::to_mathematica(const trajectory &t, FILE *file){
  ostringstream s;
  s << "traj = {{" << fixed << positions << "}};" << endl;
  s << "Graphics3D[{Arrow@#} & /@ data]" << endl;
  fputs(s.str().c_str(),file);

  return ferror(file) == 0;
}

