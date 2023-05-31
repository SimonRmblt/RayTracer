/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** ILight.hpp
*/

#ifndef RAYTRACER_ILIGHT_HPP
    #define RAYTRACER_ILIGHT_HPP

    #include "sphere.hpp"

namespace RayTracer {
    class ILight {
        public:
            virtual sf::Color getColorByLight(math::Point3D point, std::unique_ptr<RayTracer::Sphere> &s) = 0;
            virtual sf::Color castShadow(math::Point3D point, std::unique_ptr<RayTracer::IObject> &s, std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2) = 0;
            virtual sf::Color reflectLight(math::Point3D point, std::unique_ptr<RayTracer::IObject> &s, std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2, RayTracer::Ray ray) = 0;

            virtual math::Vector3D getDir() = 0;
            virtual double getIntensity() = 0;
            virtual RayTracer::IObject &getBulb() = 0;

            virtual ~ILight() = default;
    };
}

#endif //RAYTRACER_ILIGHT_HPP
