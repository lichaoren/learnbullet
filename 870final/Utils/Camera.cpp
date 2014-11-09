/*
 * camera.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: chaorel
 */

#include "Camera.h"

#include <cmath>

void Camera::update() {

}

const glm::vec3 Camera::ray(const int w, const int h) const {
    if (_projectMode == ORTHO) {
        glm::vec3 extents(_ratio*1.0f, 1.0f, 0);
        extents *= (_location - _target).length();
        glm::vec3 lower = _target - extents;
        glm::vec3 upper = _target + extents;
        float u = w / _width;
        float v = (_height - h) / _height;
        glm::vec3 p((1.0f - u) * lower.x + u * upper.x,
                    (1.0f - v) * lower.y + v * upper.y,
                    _location.z);
        return p;
    }
    float x = (2.0f * float(w) / _width - 1.0f) * _htanfov;
    float y = (2.0f * float(h) / _height - 1.0f) * _vtanfov;
    glm::vec3 rt(_up * y + _right * x + _aim);
    return glm::normalize(rt);
}

void Camera::rotate(const float d) {

    glm::quat tmp(glm::angleAxis(d, _up));
    _target = _location + tmp * (_target - _location);
    refine();
}

void Camera::refine() {
    _aim = glm::normalize(_target - _location);
    _right = glm::normalize(glm::cross (_aim, _up));
    _up = glm::normalize (-(glm::cross (_aim, _right)));
}

void Camera::setFov(const float f) {
    _fov = f;
    _htanfov = tan(_fov / 360.0f * M_PI);
    _vtanfov = _htanfov / _ratio;
}


Camera::Camera () :
        _width(720), _height(480), _near(0.1f), _far(1000.0f),
        _fov(45.0f), _ratio(_width / _height),
        _htanfov(tan(_fov / 360.0f * M_PI)),
        _vtanfov(_htanfov / _ratio), _location(glm::vec3(0, 0, 0)),
        _target(glm::vec3(0, 0, -1)), _aim(0, 0, -1), _up(0, 1, 0),
        _right(1, 0, 0) {
    // TODO Auto-generated constructor stub

}

