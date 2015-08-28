
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Utility.h"

#include <math.h>
#include <iostream>

using namespace std;

class Vector2d;
class Vector3d;

class Vector2d {
public:
  double x, y;

  Vector2d(double vx = 0, double vy = 0);
  Vector2d(const Vector2d &v);

  const double& operator[](int i) const;

  double magnitude() const;      // magnitude of vector
  double magnitudeSqr() const;   // magnitude squared
  Vector2d normalize() const;   // normalize

  void set(double vx = 0, double vy = 0); // set assuming y = 0
  void set(const Vector2d &v);

  /* Vector2d operator prototypes */
  friend Vector2d operator-(const Vector2d& v1); // unary negation of vector
  friend Vector2d operator+(const Vector2d& v1, const Vector2d& v2);//addition
  friend Vector2d operator-(const Vector2d& v1, const Vector2d& v2);//subtract
  friend Vector2d operator*(const Vector2d& v, double s); // scalar mult
  friend Vector2d operator*(double s, const Vector2d& v);
  friend double   operator*(const Vector2d& v1, const Vector2d& v2); // dot
  friend Vector3d operator%(const Vector2d& v1, const Vector2d& v2); // cross
  friend Vector2d operator/(const Vector2d& v, double s); // division by scalar
  friend short    operator==(const Vector2d& one, const Vector2d& two); // eq
  friend ostream& operator<< (ostream& os, const Vector2d& v);
};


class Vector3d {
public:
  double x, y, z;

  Vector3d(double vx = 0, double vy = 0, double vz = 0);
  Vector3d(const Vector3d &v);

  const double& operator[](int i) const;

  double magnitude() const;      // magnitude of vector
  double magnitudeSqr() const;   // magnitude squared
  Vector3d normalize() const;   // normalize

  void set(double vx = 0, double vy = 0, double vz = 0); // set
  void set(const Vector3d &v);

  /* Vector3d operator prototypes */
  friend Vector3d operator-(const Vector3d& v1);  // unary negation
  Vector3d operator+(const Vector3d& v2) const; // vector addition
  friend Vector3d operator-(const Vector3d& v1, const Vector3d& v2); // subtract
  friend Vector3d operator*(const Vector3d& v, double s);      // multiply
  friend Vector3d operator*(double s, const Vector3d& v);
  friend double   operator*(const Vector3d& v1, const Vector3d& v2); // dot
  friend Vector3d operator%(const Vector3d& v1, const Vector3d& v2); // cross
  friend Vector3d operator/(const Vector3d& v, double s); // division by scalar
  friend short    operator==(const Vector3d& one, const Vector3d& two); // equ
  friend ostream& operator<< (ostream& os, const Vector3d& v);
};

class Vector
{
  public:

   Vector(){ xyz[0] = xyz[1] = xyz[2] = 0; }

   Vector(const Vector& v)
   {
      xyz[0] = v.xyz[0];
      xyz[1] = v.xyz[1];
      xyz[2] = v.xyz[2];
   }

   Vector(const double a, const double b, const double c)
   {
      xyz[0] = a;
      xyz[1] = b;
      xyz[2] = c;
   }

   ~Vector(){}

   //!  Set all three components
   void set( const float vx, const float vy, const float vz )
   {
      xyz[0] = vx;
      xyz[1] = vy;
      xyz[2] = vz;
   }

   //! Add two vectors together
   const Vector operator+        (const Vector& v) const
   {
      return Vector(xyz[0]+v.xyz[0], xyz[1]+v.xyz[1], xyz[2]+v.xyz[2]);
   }

   //! Subtract one vector from another
   const Vector operator-        (const Vector& v) const
   {
      return Vector(xyz[0]-v.xyz[0], xyz[1]-v.xyz[1], xyz[2]-v.xyz[2]);
   }

   //! Unary minus
   friend const Vector operator- (const Vector& v)
   { return Vector(-v.xyz[0],-v.xyz[1],-v.xyz[2]); }

   //! Multiplication of a constant with a vector
   friend const Vector operator* (const double w, const Vector& v)
   { return v*w; }

   //! Multiplication of a vector with a constant
   const Vector operator*        (const double v) const
   { return Vector(xyz[0]*v, xyz[1]*v, xyz[2]*v); }

   const Vector operator/        (const double v) const
   { return Vector(xyz[0]/v, xyz[1]/v, xyz[2]/v); }

   friend const Vector operator/       (const double v, const Vector& w)
   { return Vector(v/w.xyz[0], v/w.xyz[1], v/w.xyz[2]); }

   //! Inner product
   const double operator*        (const Vector& v) const
   { return (xyz[0]*v.xyz[0] + xyz[1]*v.xyz[1] + xyz[2]*v.xyz[2]); }

   //! cross product
   const Vector operator%        (const Vector& v) const
   { return Vector(  xyz[1]*v.xyz[2] - xyz[2]*v.xyz[1],
                     xyz[2]*v.xyz[0] - xyz[0]*v.xyz[2],
                     xyz[0]*v.xyz[1] - xyz[1]*v.xyz[0]  ); }

   Vector& operator=       (const Vector& v)
   { xyz[0] = v.xyz[0]; xyz[1] = v.xyz[1]; xyz[2] = v.xyz[2]; return *this; }

   Vector& operator+=      (const Vector& v)
   { xyz[0] += v.xyz[0]; xyz[1] += v.xyz[1]; xyz[2] += v.xyz[2]; return *this; }

   Vector& operator-=      (const Vector& v)
   { xyz[0] -= v.xyz[0]; xyz[1] -= v.xyz[1]; xyz[2] -= v.xyz[2]; return *this; }

   Vector& operator*=      (const double v)
   { xyz[0] *= v; xyz[1] *= v; xyz[2] *= v; return *this; }

   Vector& operator/=      (const double v)
   { xyz[0] /= v; xyz[1] /= v; xyz[2] /= v; return *this; }


   const double& operator[] (const int v) const { return xyz[v]; }
         double& operator[] (const int v)       { return xyz[v]; }
   const double& operator() (const int v) const { return xyz[v]; }

   const double X() const { return xyz[0]; }
   const double Y() const { return xyz[1]; }
   const double Z() const { return xyz[2]; }

   const double magnitude() const
   { return sqrt( xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2] ); }

   const Vector unitvector() const { return *this/magnitude(); }

   void normalize()
   { double mag = magnitude(); xyz[0] /= mag; xyz[1] /= mag; xyz[2] /= mag; }

//  Comparisons

   const bool operator==         (const Vector& v) const
       { return ( xyz[0]==v.xyz[0] && xyz[1]==v.xyz[1] && xyz[2]==v.xyz[2] ); }

   const bool operator!=         (const Vector& v) const
       { return ( xyz[0]!=v.xyz[0] || xyz[1]!=v.xyz[1] || xyz[2]!=v.xyz[2] ); }

   const bool operator<          (const Vector& v) const
       { return ( magnitude() < v.magnitude() ); }

   const bool operator<=         (const Vector& v) const
       { return ( magnitude() <= v.magnitude() ); }

   const bool operator>          (const Vector& v) const
       { return ( magnitude() > v.magnitude() ); }

   const bool operator>=         (const Vector& v) const
       { return ( magnitude() >= v.magnitude() ); }

   // Test for parallel
   const bool operator||         (const Vector& v) const
       { return (  fabs((*this)*v) == v.magnitude()*((*this).magnitude()) ); }

   friend std::ostream& operator<< (std::ostream& stream, const Vector& v) {
     stream <<"[ " << v.xyz[0]  <<", " << v.xyz[1] <<", " << v.xyz[2] <<" ]";
     return stream;
  }

private:
  double xyz[3];
};


#endif
