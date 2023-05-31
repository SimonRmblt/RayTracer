/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** vector.cpp
*/

#include "../include/vector.hpp"

math::Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

math::Vector3D::Vector3D(math::Vector3D &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

math::Vector3D::Vector3D(math::Vector3D &&other)  noexcept {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    other.x = 0.0;
    other.y = 0.0;
    other.z = 0.0;
}

math::Vector3D::Vector3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

math::Vector3D &math::Vector3D::operator=(const math::Vector3D &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator+(const math::Vector3D &other) {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

math::Vector3D &math::Vector3D::operator+=(const math::Vector3D &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator-(const math::Vector3D &other) {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

math::Vector3D &math::Vector3D::operator-=(const math::Vector3D &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator*(const math::Vector3D &other) {
    return Vector3D(x * other.x, y * other.y, z * other.z);
}

math::Vector3D &math::Vector3D::operator*=(const math::Vector3D &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator/(const math::Vector3D &other) {
    return Vector3D(x / other.x, y / other.y, z / other.z);
}

math::Vector3D &math::Vector3D::operator/=(const math::Vector3D &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

math::Vector3D math::Vector3D::operator*(double nbr) {
    return Vector3D(x * nbr, y * nbr, z * nbr);
}

math::Vector3D &math::Vector3D::operator*=(double nbr) {
    x *= nbr;
    y *= nbr;
    z *= nbr;
    return *this;
}

math::Vector3D math::Vector3D::operator/(double nbr) {
    return Vector3D(x / nbr, y / nbr, z / nbr);
}

math::Vector3D &math::Vector3D::operator/=(double nbr) {
    x /= nbr;
    y /= nbr;
    z /= nbr;
    return *this;
}

double math::Vector3D::length() const {
    return std::sqrt(x*x + y*y + z*z);
}

double math::Vector3D::dotProduct(Vector3D other) {
    return ((x * other.x) + (y * other.y) + (z * other.z));
}

double math::Vector3D::dotProduct(math::Point3D other) {
    return ((x * other.x) + (y * other.y) + (z * other.z));
}

void math::Vector3D::normal() {
    double len = length();
    x /= len;
    y /= len;
    z /= len;
}

bool math::Vector3D::operator==(const math::Vector3D &other) const {
    return (x == other.x && y == other.y && z == other.z);
}

math::Vector3D::~Vector3D() = default;
