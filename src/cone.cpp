/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** cone.cpp
*/

#include "cone.hpp"

RayTracer::Cone::Cone()
{
    _base = math::Point3D(0, 10, 30);
    _axis = math::Vector3D(0, 1, 0);
    _radius = 2;
    _height = 8;
    _color = sf::Color::Blue;
    _hitPoint = math::Point3D();
    _distFromCamera = 0;
    _type = ObjectType::CONE;
    _angle = 30;
    _isReflective = true;
}

RayTracer::Cone::Cone(math::Point3D base, math::Vector3D axis,
                        sf::Color color, double radius, double height, double angle) {
    _base = base;
    _axis = axis;
    _color = color;
    _hitPoint = math::Point3D();
    _distFromCamera = 0;
    _type = ObjectType::CONE;
    _radius = radius;
    _height = height;
    _angle = angle;
}

bool RayTracer::Cone::hit(RayTracer::Ray ray) {
    ray._direction.normal();
    const double epsilon = std::numeric_limits<double>::epsilon();
    math::Vector3D oc = math::Vector3D(ray._origin.x - _base.x, ray._origin.y - _base.y, ray._origin.z - _base.z);
    double cos2 = pow(_angle, 2);
    double sin2 = 1.0 - cos2;
    double a = ray._direction.dotProduct(ray._direction) - cos2 * pow(ray._direction.dotProduct(_axis), 2) - sin2;
    double b = 2.0 * (oc.dotProduct(ray._direction) - cos2 * oc.dotProduct(_axis) * ray._direction.dotProduct(_axis)
                      - sin2 * oc.dotProduct(_axis));
    double c = oc.dotProduct(oc) - cos2 * pow(oc.dotProduct(_axis), 2) - sin2 * oc.dotProduct(oc);
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant < epsilon)
        return false;
    double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b - sqrt(discriminant)) / (2.0 * a);
    if (t1 < 0 && t2 < 0)
        return false;
    _hitPoint = math::Point3D{ray._origin.x + ray._direction.x * std::min(t1, t2),
                              ray._origin.y + ray._direction.y * std::min(t1, t2),
                              ray._origin.z + ray._direction.z * std::min(t1, t2)};
    return true;
}



bool RayTracer::Cone::operator==(const RayTracer::Cone &other) const {
    return this->_base == other._base && this->_axis == other._axis;
}

double RayTracer::Cone::getDistFromCam() {
    return _distFromCamera;
}

void RayTracer::Cone::setDistFromCam(double distance) {
    this->_distFromCamera = distance;
}

double RayTracer::Cone::getRadius() {
    return 0;
}

void RayTracer::Cone::setRadius([[maybe_unused]] double radius) {}

math::Point3D RayTracer::Cone::getCenter() {
    return _base;
}

void RayTracer::Cone::setCenter(math::Point3D &point) {
    this->_base = point;
}

sf::Color RayTracer::Cone::getColor() {
    return _color;
}

void RayTracer::Cone::setColor(sf::Color &color) {
    this->_color = color;
}

math::Point3D RayTracer::Cone::getHitPoint() {
    return _hitPoint;
}

void RayTracer::Cone::setHitPoint(math::Point3D &hitPoint) {
    this->_hitPoint = hitPoint;
}

RayTracer::ObjectType RayTracer::Cone::getType() {
    return _type;
}

void RayTracer::Cone::setType(RayTracer::ObjectType type) {
    this->_type = type;
}

void RayTracer::Cone::setNormal(math::Vector3D &normal) {
    this->_axis = normal;
}

math::Vector3D RayTracer::Cone::getNormal() {
    return _axis;
}

double RayTracer::Cone::getHeight() {
    return _height;
}

void RayTracer::Cone::setHeight(double height) {
    this->_height = height;
}

double RayTracer::Cone::getAngle() {
    return _angle;
}

void RayTracer::Cone::setAngle(double angle) {
    this->_angle = angle;
}

RayTracer::Cone::Cone(RayTracer::IObject &other) {
    this->_base = other.getCenter();
    this->_axis = other.getNormal();
    this->_color = other.getColor();
    this->_hitPoint = other.getHitPoint();
    this->_distFromCamera = other.getDistFromCam();
    this->_type = other.getType();
    this->_radius = other.getRadius();
    this->_height = other.getHeight();
    this->_angle = other.getAngle();
}

math::Vector3D RayTracer::Cone::getNormalAt(math::Point3D &point) {
    math::Vector3D p_c = math::Vector3D(point.x - _base.x, point.y - _base.y, point.z - _base.z);
    double cos2 = pow(_angle, 2);
    double sin2 = 1.0 - cos2;
    double k = 1.0 / sqrt(cos2 * pow(p_c.dotProduct(_axis), 2) + sin2 * p_c.dotProduct(p_c));
    math::Vector3D normal = math::Vector3D(p_c.x - k * cos2 * p_c.dotProduct(_axis) * _axis.x,
                                           p_c.y - k * cos2 * p_c.dotProduct(_axis) * _axis.y,
                                           p_c.z - k * cos2 * p_c.dotProduct(_axis) * _axis.z);
    normal.normal();
    return normal;
}

RayTracer::Cone::Cone(RayTracer::Cone &other) {
    this->_base = other._base;
    this->_axis = other._axis;
    this->_color = other._color;
    this->_hitPoint = other._hitPoint;
    this->_distFromCamera = other._distFromCamera;
    this->_type = other._type;
    this->_radius = other._radius;
    this->_height = other._height;
    this->_angle = other._angle;
}

std::unique_ptr<RayTracer::IObject> RayTracer::Cone::clone() {
    return std::make_unique<Cone>(*this);
}


RayTracer::Cone::~Cone() = default;
