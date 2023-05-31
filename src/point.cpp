/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** point.cpp
*/

#include "../include/point.hpp"

math::Point3D::Point3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

math::Point3D::Point3D(math::Point3D &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

math::Point3D::Point3D(math::Point3D &&other) noexcept {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    other.x = 0.0;
    other.y = 0.0;
    other.z = 0.0;
}

math::Point3D::Point3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

math::Point3D math::Point3D::operator+(const math::Vector3D &other) {
    return Point3D(x + other.x, y + other.y, z + other.z);
}

math::Point3D math::Point3D::operator-(const math::Vector3D &other) const {
    return Point3D(x - other.x, y - other.y, z - other.z);
}

math::Point3D &math::Point3D::operator+=(const math::Vector3D &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

math::Point3D &math::Point3D::operator=(const math::Point3D &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

bool math::Point3D::operator==(const math::Point3D &other) const {
    return (x == other.x && y == other.y && z == other.z);
}

math::Point3D::~Point3D() = default;
