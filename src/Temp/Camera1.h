
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "PolyMath.h"
#include "LinearAlgebra.h"

#include <iostream>
#include <stdlib.h>

class Camera
{
public:

    Camera () {
    }
    Camera (const int w, const int h);
    ~Camera () {
    }

    void
    report () const;

    void
    setEyeViewUp (const Vector& loc, const Vector& tar, const Vector& up);
    const Vector&
    camLoc () const {
        return _location;
    }
    const Vector&
    camAim () const {
        return _aim;
    }
    const Vector&
    camRight () const {
        return _right;
    }
    const Vector&
    camUp () const {
        return _up;
    }
    const double&
    width () const {
        return _w;
    }
    const double&
    height () const {
        return _h;
    }
    const double&
    hfov () const {
        return _htanfov;
    }
    const double&
    vfov () const {
        return _vtanfov;
    }

    void
    rotateAround (const Vector& axis, const double& degree);

    void
    setNearPlane (const double n) {
        _near = n;
    }
    const double&
    nearPlane () const {
        return _near;
    }

    void
    setFarPlane (const double n) {
        _far = n;
    }
    const double&
    farPlane () const {
        return _far;
    }

    void
    updateDOF () {
        _dof = _far - _near;
    }
    const double&
    dof () const {
        return _dof;
    }

    void
    setWidth (const double w) {
        _w = w;
    }
    void
    setHeight (const double h) {
        _h = h;
    }

    void
    updateAspectRatio (const double& w, const double& h) {
        _asp_ratio = w / h;
    }
    const double&
    aspectRatio () const {
        return _asp_ratio;
    }

    void
    setFovhv (const double htanfov);

    void
    setFov (const double fov);

    // view direction of a pixel at the fractional _location x,y.
    // Nominally 0 <= x <= 1 and 0 <= y <= 1 for the primary fov,
    // but the values can extend beyond that
    const Vector
    eyeRay (const int ww, const int hh) const;

protected:
    double _w, _h, _asp_ratio;
    double _fov, _htanfov, _vtanfov;
    double _near, _far, _dof;

    Vector _location, _target, _aim, _up, _right;
};

#endif

