/*
 * Camera.h
 *
 *  Created on: Sep 17, 2014
 *      Author: chaorel
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO 1. Lock aim to an object using observer pattern
// TODO 2. abstract camera then derive to Pers and Orth

enum PROJECTION {ORTHO, PERSP};

class Camera
{
public:
    explicit Camera();
    virtual ~Camera() {
    }
    void update();

    const glm::mat4 getViewMatrix() const {
        return glm::lookAt(_location, _target, _up);
    }
    const glm::mat4 getProjectMatrix() const {
        return glm::perspective(_fov, _ratio, _near, _far);
    }

//    return a direction at w, h from the camera
    const glm::vec3 ray(const int, const int) const;
//    rotate $1 around current up
    void rotate(const float);
//    rotate $1 degrees around axis $2
    void rotate(const glm::vec3&, const glm::vec3&);

    void refine();

    float getWidth() const {
        return _width;
    }
    float getHeight() const {
        return _height;
    }
    float getFov() const {
        return _fov;
    }
    float getRatio() const {
        return _ratio;
    }
    float getNear() const {
        return _near;
    }
    float getFar() const {
        return _far;
    }
    const glm::vec3& getLocation() const {
        return _location;
    }
    const glm::vec3& getTarget() const {
        return _target;
    }
    const glm::vec3& getAim() const {
        return _aim;
    }
    const glm::vec3& getUp() const {
        return _up;
    }
    const glm::vec3& getRight() const {
        return _right;
    }

    void setWidth(const float w) {
        _width = w;
    }
    void setHeight(const float h) {
        _height = h;
    }
    void setFov(const float);
    void setRatio(const float r) {
        _ratio = r;
    }
    void setNear(const float n) {
        _near = n;
    }
    void setFar(const float f) {
        _far = f;
    }
    void setLocation(const glm::vec3& v) {
        _location = v;
    }
    void setLocation(const float x, const float y, const float z) {
        _location[0] = x;
        _location[1] = y;
        _location[2] = z;
    }
    void setTarget(const glm::vec3& v) {
        _target = v;
    }
    void setTarget(const float x, const float y, const float z) {
        _target[0] = x;
        _target[1] = y;
        _target[2] = z;
    }
    void setAim(const glm::vec3& v) {
        _aim = v;
    }
    void setAim(const float x, const float y, const float z) {
        _aim[0] = x;
        _aim[1] = y;
        _aim[2] = z;
    }
    void setUp(const glm::vec3& v) {
        _up = v;
    }
    void setUp(const float x, const float y, const float z) {
        _up[0] = x;
        _up[1] = y;
        _up[2] = z;
    }
    void setRight(const glm::vec3& v) {
        _right = v;
    }
    void setRight(const float x, const float y, const float z) {
        _right[0] = x;
        _right[1] = y;
        _right[2] = z;
    }

    void projectionMode(PROJECTION p) {
        _projectMode = p;
    }
    int projectionMode() const {
        return _projectMode;
    }

private:
    float _width, _height, _near, _far;
    float _fov, _ratio, _htanfov, _vtanfov;
    glm::vec3 _location, _target, _aim, _up, _right;
    PROJECTION _projectMode;

    Camera(Camera&);
    Camera(const Camera&);
    Camera& operator=(const Camera&);
};

#endif /* CAMERA_H_ */
