/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** sphere.cpp
*/

#include "../include/sphere.hpp"

RayTracer::Sphere::Sphere() {
    this->_center = math::Point3D();
    this->_radius = 4;
    this->_color = sf::Color::Black;
    this->_hitPoint = math::Point3D();
    this->_distFromCamera = 0;
    this->_type = ObjectType::SPHERE;
    this->_isReflective = true;
}

bool RayTracer::Sphere::operator==(const RayTracer::Sphere &other) const {
    return this->_center == other._center && this->_radius == other._radius;
}

bool RayTracer::Sphere::hit(RayTracer::Ray ray) {
    ray._direction.normal();
    const double epsilon = std::numeric_limits<double>::epsilon();
    double a = ray._direction.dotProduct(ray._direction);
    math::Vector3D oc = math::Vector3D(ray._origin.x - _center.x, ray._origin.y - _center.y, ray._origin.z - _center.z);
    double b = 2.0 * oc.dotProduct(ray._direction);
    double c = oc.dotProduct(oc) - _radius * _radius;
    double discriminant = b * b - 4.0f * a * c;
    if (discriminant < epsilon)
        return false;
    double t1 = (-b + sqrt(discriminant)) / (2.0f * a);
    double t2 = (-b - sqrt(discriminant)) / (2.0f * a);
    if (t1 < epsilon && t2 < epsilon)
        return false;
    _hitPoint = math::Point3D{ray._origin.x + ray._direction.x * std::min(t1, t2),
                                    ray._origin.y + ray._direction.y * std::min(t1, t2),
                                    ray._origin.z + ray._direction.z * std::min(t1, t2)};
    return true;
}

RayTracer::Sphere::Sphere(math::Point3D center, double radius, sf::Color color) {
    this->_center = center;
    this->_radius = radius;
    this->_color = color;
    this->_hitPoint = math::Point3D();
    this->_distFromCamera = 0;
    this->_type = ObjectType::SPHERE;
    this->_isReflective = true;
}

double RayTracer::Sphere::getDistFromCam() {
    return this->_distFromCamera;
}

RayTracer::Sphere::Sphere(RayTracer::Sphere&& other) {
    this->_center = other._center;
    this->_radius = other._radius;
    this->_color = other._color;
    this->_hitPoint = other._hitPoint;
    this->_distFromCamera = other._distFromCamera;
    this->_type = other._type;
    this->_isReflective = other._isReflective;
}

RayTracer::Sphere::Sphere(RayTracer::IObject &&other) {
    this->_center = other.getCenter();
    this->_radius = other.getRadius();
    this->_color = other.getColor();
    this->_hitPoint = other.getHitPoint();
    this->_distFromCamera = other.getDistFromCam();
    this->_type = other.getType();
    this->_isReflective = other.isReflective();
}

void RayTracer::Sphere::setDistFromCam(double distance) {
    this->_distFromCamera = distance;
}

double RayTracer::Sphere::getRadius() {
    return _radius;
}

void RayTracer::Sphere::setRadius(double radius) {
    this->_radius = radius;
}

math::Point3D RayTracer::Sphere::getCenter() {
    return this->_center;
}

void RayTracer::Sphere::setCenter(math::Point3D &point) {
    this->_center = point;
}

sf::Color RayTracer::Sphere::getColor() {
    return this->_color;
}

void RayTracer::Sphere::setColor(sf::Color &color) {
    this->_color = color;
}

math::Point3D RayTracer::Sphere::getHitPoint() {
    return this->_hitPoint;
}

void RayTracer::Sphere::setHitPoint(math::Point3D &hitPoint) {
    this->_hitPoint = hitPoint;
}

RayTracer::ObjectType RayTracer::Sphere::getType() {
    return this->_type;
}

void RayTracer::Sphere::setType(RayTracer::ObjectType type) {
    this->_type = type;
}

void RayTracer::Sphere::setNormal([[maybe_unused]] math::Vector3D &normal) {}

math::Vector3D RayTracer::Sphere::getNormal() {
    return {};
}

math::Vector3D RayTracer::Sphere::getNormalAt(math::Point3D &point) {
    math::Vector3D normal = math::Vector3D(point.x - _center.x, point.y - _center.y, point.z - _center.z);
    normal.normal();
    return normal;
}

std::unique_ptr<RayTracer::IObject> RayTracer::Sphere::clone() {
    return std::make_unique<RayTracer::Sphere>(*this);
}

RayTracer::Sphere::Sphere(RayTracer::Sphere &other) {
    this->_center = other._center;
    this->_radius = other._radius;
    this->_color = other._color;
    this->_hitPoint = other._hitPoint;
    this->_distFromCamera = other._distFromCamera;
    this->_type = other._type;
    this->_isReflective = other._isReflective;

}

RayTracer::Sphere::~Sphere() = default;
