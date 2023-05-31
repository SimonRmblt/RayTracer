/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** camera.cpp
*/

#include "camera.hpp"

RayTracer::Camera::Camera() {
    _origin = math::Point3D(0.5, 0.5, -1);
    _screen = Rectangle3D();
    _videoMode = sf::VideoMode(1920, 1080);
    _fov = 90;
    _aspectRatio = _videoMode.width / static_cast<double>(_videoMode.height);
}

RayTracer::Camera::Camera(math::Point3D origin, Rectangle3D screen) {
    this->_origin = origin;
    this->_screen = screen;
}

RayTracer::Ray RayTracer::Camera::ray(double u, double v) {
    return {_origin,
            math::Vector3D(_screen.pointAt(u, v).x - _origin.x,
                           _screen.pointAt(u, v).y - _origin.y,
                           _screen.pointAt(u, v).z - _origin.z)};
}

RayTracer::Camera::~Camera() = default;
