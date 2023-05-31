/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** sphere.cpp
*/

#include "../include/cylinder.hpp"

RayTracer::Cylinder::Cylinder() {
    this->_center = math::Point3D();
    this->_radius = 2;
    this->_color = sf::Color::White;
    this->_hitPoint = math::Point3D();
    this->_distFromCamera = 0;
    this->_type = ObjectType::CYLINDER;
    this->_axis = math::Vector3D(0, 1, 0);
}

bool RayTracer::Cylinder::operator==(const RayTracer::Cylinder &other) const {
    return this->_center == other._center && this->_radius == other._radius && this->_axis == other._axis;
}

bool RayTracer::Cylinder::hit(RayTracer::Ray ray) {
    ray._direction.normal();
    const double epsilon = std::numeric_limits<double>::epsilon();
    math::Vector3D oc = math::Vector3D(ray._origin.x - _center.x, ray._origin.y - _center.y, ray._origin.z - _center.z);
    double a = ray._direction.dotProduct(ray._direction) - pow(ray._direction.dotProduct(_axis), 2);
    double b = 2.0 * (oc.dotProduct(ray._direction) - oc.dotProduct(_axis) * ray._direction.dotProduct(_axis));
    double c = oc.dotProduct(oc) - pow(oc.dotProduct(_axis), 2) - _radius * _radius;
    double discriminant = b * b - 4.0f * a * c;
    if (discriminant < epsilon)
        return false;
    double t1 = (-b + sqrt(discriminant)) / (2.0f * a);
    double t2 = (-b - sqrt(discriminant)) / (2.0f * a);
    if (t1 < 0 && t2 < 0)
        return false;
    _hitPoint = math::Point3D{ray._origin.x + ray._direction.x * std::min(t1, t2),
                              ray._origin.y + ray._direction.y * std::min(t1, t2),
                              ray._origin.z + ray._direction.z * std::min(t1, t2)};
    return true;
}

RayTracer::Cylinder::Cylinder(math::Point3D center, double radius, sf::Color color, math::Vector3D axis) {
    this->_center = center;
    this->_radius = radius;
    this->_color = color;
    this->_hitPoint = math::Point3D();
    this->_distFromCamera = 0;
    this->_type = ObjectType::CYLINDER;
    axis.normal();
    this->_axis = axis;
}

double RayTracer::Cylinder::getDistFromCam() {
    return this->_distFromCamera;
}

RayTracer::Cylinder::Cylinder(RayTracer::Cylinder&& other) {
    this->_center = other._center;
    this->_radius = other._radius;
    this->_color = other._color;
    this->_hitPoint = other._hitPoint;
    this->_distFromCamera = other._distFromCamera;
    this->_type = other._type;
    this->_axis = other._axis;
}

RayTracer::Cylinder::Cylinder(RayTracer::IObject &&other) {
    this->_center = other.getCenter();
    this->_radius = other.getRadius();
    this->_color = other.getColor();
    this->_hitPoint = other.getHitPoint();
    this->_distFromCamera = other.getDistFromCam();
    this->_type = other.getType();
    this->_axis = other.getNormal();
}

void RayTracer::Cylinder::setDistFromCam(double distance) {
    this->_distFromCamera = distance;
}

double RayTracer::Cylinder::getRadius() {
    return _radius;
}

void RayTracer::Cylinder::setRadius(double radius) {
    this->_radius = radius;
}

math::Point3D RayTracer::Cylinder::getCenter() {
    return this->_center;
}

void RayTracer::Cylinder::setCenter(math::Point3D &point) {
    this->_center = point;
}

sf::Color RayTracer::Cylinder::getColor() {
    return this->_color;
}

void RayTracer::Cylinder::setColor(sf::Color &color) {
    this->_color = color;
}

math::Point3D RayTracer::Cylinder::getHitPoint() {
    return this->_hitPoint;
}

void RayTracer::Cylinder::setHitPoint(math::Point3D &hitPoint) {
    this->_hitPoint = hitPoint;
}

RayTracer::ObjectType RayTracer::Cylinder::getType() {
    return this->_type;
}

void RayTracer::Cylinder::setType(RayTracer::ObjectType type) {
    this->_type = type;
}

void RayTracer::Cylinder::setNormal(math::Vector3D &normal) {
    _axis = normal;
}

math::Vector3D RayTracer::Cylinder::getNormal() {
    return _axis;
}

double RayTracer::Cylinder::getHeight() {
    return 0;
}

void RayTracer::Cylinder::setHeight([[maybe_unused]] double height) {
}

math::Point3D RayTracer::Cylinder::getBasePoint() {
    return {};
}

void RayTracer::Cylinder::setBasePoint([[maybe_unused]] math::Point3D &base) {}

math::Point3D RayTracer::Cylinder::getTopPoint() {
    return {};
}

void RayTracer::Cylinder::setTopPoint([[maybe_unused]] math::Point3D &top) {}

math::Vector3D RayTracer::Cylinder::getNormalAt(math::Point3D &point) {
    math::Vector3D fromCenter = math::Vector3D(point.x - this->getCenter().x, point.y - this->getCenter().y, point.z - this->getCenter().z);
    math::Vector3D onAxis = this->getNormal() * fromCenter.dotProduct(this->getNormal());
    math::Vector3D onPlane = fromCenter - onAxis;
    onPlane.normal();
    math::Vector3D normal = onPlane;
    normal.normal();
    return normal;
}

std::unique_ptr<RayTracer::IObject> RayTracer::Cylinder::clone() {
    return std::make_unique<Cylinder>(*this);
}

RayTracer::Cylinder::Cylinder(RayTracer::Cylinder &other) {
    this->_center = other._center;
    this->_radius = other._radius;
    this->_color = other._color;
    this->_hitPoint = other._hitPoint;
    this->_distFromCamera = other._distFromCamera;
    this->_type = other._type;
    this->_axis = other._axis;
}

RayTracer::Cylinder::~Cylinder() = default;
