#ifndef GEOMETRY3_HH
#define GEOMETRY3_HH

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <regex>

#include "auxiliary.hh"

using namespace std;

struct coord3d {
  double x[3];

//  coord3d(const vector <double> vec) { x[0] = vec[0]; x[1] = vec[1]; x[2] = vec[2]; }
  coord3d(const double y[3]) { x[0] = y[0]; x[1] = y[1]; x[2] = y[2]; }
  coord3d(const double x_, const double y, const double z) { x[0] = x_; x[1] = y; x[2] = z; }
  coord3d() { x[0] = 0; x[1] = 0; x[2] = 0; }
  coord3d(const double theta, const double phi) { x[0] = sin(theta)*cos(phi); x[1] = sin(theta)*sin(phi); x[2] = cos(theta); } // and r=0

  coord3d operator/(const double d)   const { return coord3d(*this) /= d; }
  coord3d& operator/=(const double d){ x[0] /= d; x[1] /= d; x[2] /= d; return *this; }
  coord3d operator*(const double d)   const { return coord3d(*this) *= d; }
  friend coord3d operator*(const double d, const coord3d& c3d) { return c3d * d; }
  friend coord3d operator*(const int i, const coord3d& c3d) { return c3d * i; }
  coord3d& operator*=(const double d){ x[0] *= d; x[1] *= d; x[2] *= d; return *this; }
  coord3d operator+(const coord3d& y) const { return coord3d(*this) += y; }
  coord3d& operator+=(const coord3d& y){ x[0] += y[0]; x[1] += y[1]; x[2] += y[2]; return *this; }
  coord3d operator-(const coord3d& y) const { return coord3d(*this) -= y; }
  coord3d& operator-=(const coord3d& y){ x[0] -= y[0]; x[1] -= y[1]; x[2] -= y[2]; return *this; }
  coord3d operator-() const {coord3d y(-x[0],-x[1],-x[2]); return y;}

  coord3d cross(const coord3d& y) const {
    return coord3d(x[1]*y[2]-x[2]*y[1], x[2]*y[0]-x[0]*y[2], x[0]*y[1]-x[1]*y[0]);
  }
  double dot(const coord3d& y) const { return x[0]*y[0]+x[1]*y[1]+x[2]*y[2]; }
  double norm() const { return sqrt(dot(*this)); }
  //double norm() const { return sqrt(abs(dot(*this))); }

  coord3d normalised() const {
    const double normi = norm();
    if (normi==0) {return coord3d(0,0,0);}
    else {return *this/norm();}
  }

  double& operator[](const unsigned int i){ return x[i]; }
  double  operator[](const unsigned int i) const { return x[i]; }

  //vector<double>::iterator begin(){return &x[0];}
  //vector<double>::iterator end(){return &x[3];}



  static double dist(const coord3d& x, const coord3d& y){ return (x-y).norm(); }
  // d/dx_i ||x|| = x_i/||x||.
  static coord3d dnorm(const coord3d& x){ return x/x.norm(); }
  // d^2/(dx_i dx_j) ||x|| = -x_i x_j/||x||^3 + [i==j]/||x||
  static void ddnorm(const coord3d& x, vector<double> &H) {
    const double n = 1.0/x.norm(), n3 = n*n*n;
    for(int i=0;i<3;i++)
      for(int j=0;j<3;j++)
        H[i*3+j] = -x[i]*x[j]*n3 + (i==j? n : 0);
  }

  void scale(const double f);

  // calculation of the angle beta at b(0,0,0)
  static double angle(const coord3d& a, const coord3d& c);
  // calculation of the derivative of angle beta at b(0,0,0) according to coordinates a and c with fixed b
  static void dangle(const coord3d& a, const coord3d& c, coord3d& da, coord3d& dc);
  // calculation of the dihedral angle theta at a(0,0,0), b, c and d,  the result is an angle between -\pi and +\pi (in radians)
  static double dihedral(const coord3d& b, const coord3d& c, const coord3d& d);
  // calculation of the derivative of dihedral angle theta at a(0,0,0), b, c and d according to coordinates b, c and d with fixed a
  static void ddihedral(const coord3d& b, const coord3d& c, const coord3d& d, coord3d& db, coord3d& dc, coord3d& dd);

  // coordinates of d-a in the dihedral abcd, where c2=b-a and c3=c-a
  // so the call is coord = foo(b-a, c-a, ...) + a
  static coord3d internal2cart(const coord3d& c2, const coord3d& c3, const double r, const double a, const double d);


  friend vector<coord3d> &operator-=(vector<coord3d>& xs, const coord3d& y) {
    for(size_t i=0;i<xs.size();i++) xs[i] -= y;
    return xs;
  }

  friend vector<coord3d> &operator*=(vector<coord3d>& xs, const double& y) {
    for(size_t i=0;i<xs.size();i++) xs[i] *= y;
    return xs;
  }

//  friend ostream& operator<<(ostream &s, const coord3d& c3d){ s << fixed << "{" << c3d[0] << "," << c3d[1] << "," << c3d[2]<< "}"; return s; }
  friend ostream& operator<<(ostream &s, const coord3d& c3d){ s << scientific << "{" << c3d[0] << "," << c3d[1] << "," << c3d[2]<< "}"; return s; }

/* Use this for writing to the .vti file.
  friend ostream& operator<<(ostream &s, const coord3d& c3d){ 
    regex lowercasee("e");
    stringstream stream;
    string xstring;
    stream << c3d[0];
    xstring = stream.str();
    s << "  " << regex_replace(xstring, lowercasee, "E");
    stream.str("");
    xstring = "";
    stream << c3d[1];
    xstring = stream.str();
    s << "  " << regex_replace(xstring, lowercasee, "E");
    stream.str("");
    xstring = "";
    stream << c3d[2];
    xstring = stream.str();
    s << "  " << regex_replace(xstring, lowercasee, "E");
    return s; 
  }
*/ 


};



#endif

