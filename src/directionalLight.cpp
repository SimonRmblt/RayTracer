/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** directionalLight.cpp
*/

#include "directionalLight.hpp"

RayTracer::DirectionalLight::DirectionalLight() {
    _dir = math::Vector3D(0, 0, 1);
}

RayTracer::DirectionalLight::DirectionalLight(math::Vector3D dir, double ambient) {
    this->_dir = dir;
    this->_ambientLight = ambient;
}

sf::Color RayTracer::DirectionalLight::getColorByLight(math::Point3D point, std::unique_ptr<RayTracer::Sphere> &s) {
    const float bias = 1e-13;
    math::Vector3D normal(point.x - s->getCenter().x, point.y - s->getCenter().y, point.z - s->getCenter().z);
    normal.normal();
    math::Point3D newPoint(point.x + (bias * (normal.x)), point.y + (bias * normal.y), point.z + (bias * normal.z));
    RayTracer::Ray ray = RayTracer::Ray(newPoint, math::Vector3D(-this->_dir.x, -this->_dir.y, -this->_dir.z));
    double hitColor = std::max(0.0, normal.dotProduct(ray.normal(ray._direction)));
    return {static_cast<sf::Uint8>(s->getColor().r * hitColor),
            static_cast<sf::Uint8>(s->getColor().g * hitColor),
            static_cast<sf::Uint8>(s->getColor().b * hitColor)};
}

sf::Color RayTracer::DirectionalLight::castShadow(math::Point3D point,
                                                       std::unique_ptr<RayTracer::IObject> &s,
                                                       std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2) {
    const float bias = 0.01;
    math::Vector3D normal = s->getNormalAt(point);
    normal.normal();
    math::Point3D newPoint(point.x + (bias * (normal.x)), point.y + (bias * normal.y), point.z + (bias * normal.z));
    RayTracer::Ray ray = RayTracer::Ray(newPoint, math::Vector3D(-this->_dir.x, -this->_dir.y, -this->_dir.z));
    double hitColor = std::max(0.0, normal.dotProduct(ray.normal(ray._direction)));
    for (auto &i : *s2) {
        if (i && i != s && i->hit(ray)) {
            return {static_cast<sf::Uint8>((this->_ambientLight * s->getColor().r * hitColor)),
                    static_cast<sf::Uint8>((this->_ambientLight * s->getColor().g * hitColor)),
                    static_cast<sf::Uint8>((this->_ambientLight * s->getColor().b * hitColor))};
        }
    }
    return {static_cast<sf::Uint8>(s->getColor().r * hitColor),
            static_cast<sf::Uint8>(s->getColor().g * hitColor),
            static_cast<sf::Uint8>(s->getColor().b * hitColor)};
}

double RayTracer::DirectionalLight::getIntensity() {
    return this->_ambientLight;
}

math::Vector3D RayTracer::DirectionalLight::getDir() {
    return this->_dir;
}

sf::Color RayTracer::DirectionalLight::reflectLight(math::Point3D point,
                                                    std::unique_ptr<RayTracer::IObject> &hitObject,
                                                    std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &sceneObjects,
                                                    RayTracer::Ray ray) {
    const float bias = 0.0001;
    math::Vector3D normal = hitObject->getNormalAt(point);
    normal.normal();
    math::Point3D newPoint(point.x - (bias * normal.x), point.y - (bias * normal.y), point.z - (bias * normal.z));
    math::Vector3D reflection = {
            ray._direction.x - 2 * normal.dotProduct(ray._direction) * normal.x,
            ray._direction.y - 2 * normal.dotProduct(ray._direction) * normal.y,
            ray._direction.z - 2 * normal.dotProduct(ray._direction) * normal.z};
    RayTracer::Ray reflectedRay = RayTracer::Ray(newPoint, reflection);
    sf::Color reflectedColor = {0, 0, 0};
    double reflectionIntensity = 0.7;
    if (reflectionIntensity > 0) {
        for (auto& obj : *sceneObjects) {
            if (obj && obj != hitObject && obj->hit(reflectedRay)) {
                reflectedColor = {static_cast<sf::Uint8>(obj->getColor().r * reflectionIntensity),
                                  static_cast<sf::Uint8>(obj->getColor().g * reflectionIntensity),
                                  static_cast<sf::Uint8>(obj->getColor().b * reflectionIntensity)};
            }
        }
        reflectedColor.r = std::min(static_cast<int>(reflectedColor.r), 255);
        reflectedColor.g = std::min(static_cast<int>(reflectedColor.g), 255);
        reflectedColor.b = std::min(static_cast<int>(reflectedColor.b), 255);
    }
    return reflectedColor;
}

RayTracer::DirectionalLight::~DirectionalLight() = default;
