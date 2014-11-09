
#include "Vector.h"

using namespace std;

Vector2d::Vector2d(double vx, double vy){
  set(vx, vy);
}

Vector2d::Vector2d(const Vector2d &v){
  set(v);
}

Vector3d::Vector3d(double vx, double vy, double vz){
  set(vx, vy, vz);
}

Vector3d::Vector3d(const Vector3d &v){
  set(v);
}


const double& Vector2d::operator[](int i) const
{
  if(i < 0 || i > 1){
    cerr << "2D vector index bounds error" << endl;
    exit(1);
  }

  switch(i){
  case 0:
    return x;
  default:
    return y;
  }
}

const double& Vector3d::operator[](int i) const
{
  if(i < 0 || i > 2){
    cerr << "3D vector index bounds error" << endl;
    exit(1);
  }

  switch(i){
  case 0:
    return x;
  case 1:
    return y;
  default:
    return z;
  }
}

Vector2d Vector2d::normalize() const
{
  double mag;
  Vector2d newv;
  mag = magnitude();
  if (abs(x) > mag * HUGENUMBER ||
      abs(y) > mag * HUGENUMBER ){
    cerr << "Attempting to take the norm of a zero 2D vector." << endl;
  }
  newv.x = x / mag;
  newv.y = y / mag;
  return newv;
}

Vector3d Vector3d::normalize() const
{
  double mag;
  Vector3d newv;
  mag = magnitude();
  if (abs(x) > mag * HUGENUMBER ||
      abs(y) > mag * HUGENUMBER ||
      abs(z) > mag * HUGENUMBER ){
    cerr << "Attempting to take the norm of a zero 3D vector." << endl;
  }
  newv.x = x / mag;
  newv.y = y / mag;
  newv.z = z / mag;
  return newv;
}

void Vector2d::set(double vx, double vy)
{
  x = vx;
  y = vy;
}

void Vector2d::set(const Vector2d &v)
{
  x = v.x;
  y = v.y;
}

void Vector3d::set(double vx, double vy, double vz)
{
  x = vx;
  y = vy;
  z = vz;
}

void Vector3d::set(const Vector3d &v)
{
  x = v.x;
  y = v.y;
  z = v.z;
}

double Vector2d::magnitudeSqr() const
{
  return x*x + y*y;
}

double Vector3d::magnitudeSqr() const
{
  return x*x + y*y + z*z;
}



double Vector2d::magnitude() const
{
  return sqrt(magnitudeSqr());
}

double Vector3d::magnitude() const
{
  return sqrt(magnitudeSqr());
}

Vector2d operator-(const Vector2d& v1){
  Vector2d r(-v1.x, -v1.y);
  return r;
}
Vector3d operator-(const Vector3d& v1){
  Vector3d r(-v1.x, -v1.y, -v1.z);
  return r;
}

Vector2d operator+(const Vector2d& v1, const Vector2d& v2)
{
  Vector2d r;
  r.x = v1.x + v2.x;
  r.y = v1.y + v2.y;
  return r;
}

Vector3d Vector3d::operator+(const Vector3d& v2) const
{
  Vector3d r;
  r.x = x + v2.x;
  r.y = y + v2.y;
  r.z = z + v2.z;
  return r;
}

Vector2d operator-(const Vector2d& v1, const Vector2d& v2)
{
  Vector2d r;
  r.x = v1.x - v2.x;
  r.y = v1.y - v2.y;
  return r;
}
Vector3d operator-(const Vector3d& v1, const Vector3d& v2)
{
  Vector3d r;
  r.x = v1.x - v2.x;
  r.y = v1.y - v2.y;
  r.z = v1.z - v2.z;
  return r;
}

Vector2d operator*(const Vector2d& v, double s)
{
  Vector2d r;

  r.x = v.x * s;
  r.y = v.y * s;
  return r;
}
Vector2d operator*(double s, const Vector2d& v)
{
  Vector2d r;

  r.x = v.x * s;
  r.y = v.y * s;
  return r;
}
Vector3d operator*(const Vector3d& v, double s)
{
  Vector3d r;

  r.x = v.x * s;
  r.y = v.y * s;
  r.z = v.z * s;
  return r;
}
Vector3d operator*(double s, const Vector3d& v)
{
  Vector3d r;

  r.x = v.x * s;
  r.y = v.y * s;
  r.z = v.z * s;
  return r;
}

double operator*(const Vector2d& v1, const Vector2d& v2)
{
  return(v1.x * v2.x +
   v1.y * v2.y);
}
double operator*(const Vector3d& v1, const Vector3d& v2)
{
  return(v1.x * v2.x +
   v1.y * v2.y +
   v1.z * v2.z);
}

// Cross product of two Vectors
Vector3d operator%(const Vector2d& v1, const Vector2d& v2)
{
  Vector3d cp;
  cp.x = 0;
  cp.y = 0;
  cp.z = v1.x * v2.y - v1.y * v2.x;
  return (cp);
}
Vector3d operator%(const Vector3d& v1, const Vector3d& v2)
{
  Vector3d cp;
  cp.x = v1.y * v2.z - v1.z * v2.y;
  cp.y = v1.z * v2.x - v1.x * v2.z;
  cp.z = v1.x * v2.y - v1.y * v2.x;
  return (cp);
}

Vector2d operator/(const Vector2d& v, double s)
{
  Vector2d r;
  r.x = v.x / s;
  r.y = v.y / s;
  return(r);
}
Vector3d operator/(const Vector3d& v, double s)
{
  Vector3d r;
  r.x = v.x / s;
  r.y = v.y / s;
  r.z = v.z / s;
  return(r);
}

short operator==(const Vector2d& one, const Vector2d& two)
{
  return((one.x == two.x) && (one.y == two.y));
}
short operator==(const Vector3d& one, const Vector3d& two)
{
  return((one.x == two.x) && (one.y == two.y) && (one.z == two.z));
}

ostream& operator<< (ostream& os, const Vector2d& v){
  os << "[" << v.x << " " << v.y << "]";
  return os;
}

ostream& operator<< (ostream& os, const Vector3d& v){
  os << "[" << v.x << " " << v.y << " " << v.z << "]";
  return os;
}

