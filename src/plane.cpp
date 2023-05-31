/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** plane.cpp
*/

#include "plane.hpp"

RayTracer::Plane::Plane()
{
    _point = math::Point3D();
    _normal = math::Vector3D();
    _color = sf::Color::Blue;
    _hitPoint = math::Point3D();
    _distFromCamera = 0;
    _type = ObjectType::PLANE;
    _isReflective = true;
}

RayTracer::Plane::Plane(math::Point3D point, math::Vector3D normal,
                        sf::Color color) {
    _point = point;
    normal.normal();
    _normal = normal;
    _color = color;
    _hitPoint = math::Point3D();
    _distFromCamera = 0;
    _type = ObjectType::PLANE;
}

bool RayTracer::Plane::hit(RayTracer::Ray ray) {
    ray._direction.normal();
    double denominator = _normal.dotProduct(ray._direction);
    const double epsilon = std::numeric_limits<double>::epsilon();
    if (std::abs(denominator) > epsilon) {
        math::Point3D p = math::Point3D(_point.x - ray._origin.x, _point.y - ray._origin.y, _point.z - ray._origin.z);
        double t = _normal.dotProduct(p) / (denominator == 0 ? 1 : denominator);
        if (t > 0) {
            _hitPoint = math::Point3D{ray._origin.x + ray._direction.x * t,
                                      ray._origin.y + ray._direction.y * t,
                                      ray._origin.z + ray._direction.z * t};
            return true;
        }
    }
    return false;
}

bool RayTracer::Plane::operator==(const RayTracer::Plane &other) const {
    return this->_point == other._point && this->_normal == other._normal;
}

double RayTracer::Plane::getDistFromCam() {
    return _distFromCamera;
}

void RayTracer::Plane::setDistFromCam(double distance) {
    this->_distFromCamera = distance;
}

double RayTracer::Plane::getRadius() {
    return 0;
}

void RayTracer::Plane::setRadius([[maybe_unused]] double radius) {}

math::Point3D RayTracer::Plane::getCenter() {
    return _point;
}

void RayTracer::Plane::setCenter(math::Point3D &point) {
    this->_point = point;
}

sf::Color RayTracer::Plane::getColor() {
    return _color;
}

void RayTracer::Plane::setColor(sf::Color &color) {
    this->_color = color;
}

math::Point3D RayTracer::Plane::getHitPoint() {
    return _hitPoint;
}

void RayTracer::Plane::setHitPoint(math::Point3D &hitPoint) {
    this->_hitPoint = hitPoint;
}

RayTracer::ObjectType RayTracer::Plane::getType() {
    return _type;
}

void RayTracer::Plane::setType(RayTracer::ObjectType type) {
    this->_type = type;
}

void RayTracer::Plane::setNormal(math::Vector3D &normal) {
    this->_normal = normal;
}

math::Vector3D RayTracer::Plane::getNormal() {
    return _normal;
}

math::Vector3D RayTracer::Plane::getNormalAt([[maybe_unused]] math::Point3D &point) {
    _normal.normal();
    return _normal;
}

std::unique_ptr<RayTracer::IObject> RayTracer::Plane::clone() {
    return std::make_unique<RayTracer::Plane>(*this);
}

RayTracer::Plane::~Plane() = default;
