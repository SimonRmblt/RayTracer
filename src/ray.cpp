/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ray.cpp
*/

#include "../include/ray.hpp"

RayTracer::Ray::Ray() {
    _origin = math::Point3D();
    _direction = math::Vector3D();
    _closestPoint = std::make_unique<math::Point3D>();
}

RayTracer::Ray::Ray(math::Point3D origin, math::Vector3D direction) {
    this->_origin = origin;
    this->_direction = direction;
    this->_direction.normal();
}

RayTracer::Ray::Ray(Ray &other) {
    this->_origin = other._origin;
    this->_direction = other._direction;
}

math::Vector3D RayTracer::Ray::normal(math::Vector3D vec) {
    return {vec.x / vec.length(), vec.y / vec.length(), vec.z / vec.length()};
}

RayTracer::Ray::Ray(Ray &&other) noexcept {
    this->_origin = other._origin;
    this->_direction = other._direction;
    other._origin = math::Point3D();
    other._direction = math::Vector3D();
}

RayTracer::Ray::~Ray() = default;
