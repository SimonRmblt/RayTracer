/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** pointLight.cpp
*/

#include "pointLight.hpp"

RayTracer::pointLight::pointLight() {
    _bulb = std::make_unique<RayTracer::Sphere>(math::Point3D(0, 0, 0), 0, sf::Color::White);
    _intensity = 0.5;
}

RayTracer::pointLight::pointLight([[maybe_unused]] RayTracer::Sphere &sphere, [[maybe_unused]] double intensity) {
    this->_bulb = std::make_unique<RayTracer::Sphere>(sphere.getCenter(), sphere.getRadius(), sphere.getColor());
    this->_intensity = intensity;
}

sf::Color RayTracer::pointLight::getColorByLight([[maybe_unused]] math::Point3D point, [[maybe_unused]] std::unique_ptr<RayTracer::Sphere> &s) {
//    const float bias = 1e-13;
//    math::Vector3D normal(point.x - s->getCenter().x, point.y - s->getCenter().y, point.z - s->getCenter().z);
//    normal.normal();
//    math::Point3D newPoint(point.x + (bias * (normal.x)), point.y + (bias * normal.y), point.z + (bias * normal.z));
//    RayTracer::Ray ray = RayTracer::Ray(newPoint, math::Vector3D(normal));
//    double hitColor = std::max(0.0, normal.dotProduct(ray.normal(ray._direction)));
//    return {static_cast<sf::Uint8>(s->getColor().r * hitColor),
//            static_cast<sf::Uint8>(s->getColor().g * hitColor),
//            static_cast<sf::Uint8>(s->getColor().b * hitColor)};
    return sf::Color::White;
}

sf::Color RayTracer::pointLight::castShadow(math::Point3D point,
                                                       std::unique_ptr<RayTracer::IObject> &s,
                                                       std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2) {
    const float bias = 1e-13;
    math::Vector3D normal = s->getNormalAt(point);
    normal.normal();
    math::Point3D newPoint(point.x + (bias * (normal.x)), point.y + (bias * normal.y), point.z + (bias * normal.z));
    RayTracer::Ray ray = RayTracer::Ray(newPoint, math::Vector3D(normal));
    double hitColor = std::max(0.0, normal.dotProduct(ray.normal(ray._direction)));
    for (auto &i : *s2) {
        if (i && i != s && i->hit(ray) && this->_bulb->hit(ray)) {
            return {static_cast<sf::Uint8>((this->_intensity * s->getColor().r * hitColor)),
                    static_cast<sf::Uint8>((this->_intensity * s->getColor().g * hitColor)),
                    static_cast<sf::Uint8>((this->_intensity * s->getColor().b * hitColor))};
        }
    }
    return {static_cast<sf::Uint8>(s->getColor().r * hitColor),
            static_cast<sf::Uint8>(s->getColor().g * hitColor),
            static_cast<sf::Uint8>(s->getColor().b * hitColor)};
}

double RayTracer::pointLight::getIntensity() {
    return _intensity;
}

RayTracer::IObject &RayTracer::pointLight::getBulb() {
    return *_bulb;
}

sf::Color RayTracer::pointLight::reflectLight([[maybe_unused]] math::Point3D point,
                                              [[maybe_unused]] std::unique_ptr<RayTracer::IObject> &s,
                                              [[maybe_unused]] std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2,
                                              [[maybe_unused]] RayTracer::Ray ray) {
    return sf::Color::White;
}

RayTracer::pointLight::~pointLight() = default;
