#include "Camera.h"

using namespace std;

void
Camera::report () const {
    cout << "\n *** Camera Details ***\n";
    cout << "    Location: " << _location << " Aim: " << _aim << endl;
    cout << "          Up: " << _up << " Right: " << _right << endl;
    cout << "  Near Plane: " << _near << " Far Plane: " << _far << endl;
    cout << " Plane Width: " << _w << " Height: " << _h << "  AspRratio: "
            << _asp_ratio << endl;
    cout << "     Htanhov: " << _htanfov << " Vtanhov: " << _vtanfov << endl;
    cout << " ****************************************************" << endl
            << endl;
    ;
}

Camera::Camera (const int w, const int h) {
    if (w <= 1 || h <= 1) {
        std::cout << "image size of Camera incorrect!\n";
        exit (0);
    }
    _w = w, _h = h;
    updateAspectRatio (double (w), double (h));
    setEyeViewUp (Vector (0, 0, 1), Vector (0, 0, -1), Vector (0, 1, 0));
    setFov (60.0);
    setNearPlane (0.0);
    setFarPlane (1.0e6);
    updateDOF ();
}

void
Camera::setEyeViewUp (const Vector& loc, const Vector& tar, const Vector& up) {
    _location = loc;
    _target = tar;
    _up = up;
    _aim = (_target - _location).unitvector ();
    _right = (_aim % _up).unitvector ();
    _up = -(_aim % _right).unitvector ();
}

void
Camera::setFovhv (const double htanfov) {
    _htanfov = htanfov;
    _vtanfov = _htanfov;
}

void
Camera::setFov (const double fov) {
    _fov = fov;
    _htanfov = tan (_fov / 360.0 * M_PI);
    _vtanfov = _htanfov / _asp_ratio;
}

void
Camera::rotateAround (const Vector& axis, const double& degree) {
    Vector newloc = rotation (axis, -degree) * _location;
    setEyeViewUp (newloc, _target, _up);
}

// view direction of a pixel at the fractional _location x,y.
// Nominally 0 <= x <= 1 and 0 <= y <= 1 for the primary fov,
// but the values can extend beyond that
const Vector
Camera::eyeRay (const int ww, const int hh) const {
    double xx = (2.0 * (double (ww) / _w) - 1.0) * _htanfov;
    double yy = (2.0 * (double (hh) / _h) - 1.0) * _vtanfov;
    return (_up * yy + _right * xx + _aim).unitvector ();
}

