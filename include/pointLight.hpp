/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** pointLight.hpp
*/

#ifndef BOOTSTRAP_RAYTRACING_POINT_LIGHT_HPP
    #define BOOTSTRAP_RAYTRACING_POINT_LIGHT_HPP

#include "sphere.hpp"
#include "ILight.hpp"

namespace RayTracer {
    class pointLight : public ILight {
        public:
            pointLight();
            pointLight(RayTracer::Sphere &sphere, double intensity);

            sf::Color getColorByLight(math::Point3D point, std::unique_ptr<RayTracer::Sphere> &s) override;
            sf::Color castShadow(math::Point3D point, std::unique_ptr<RayTracer::IObject> &s, std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2) override;
            sf::Color reflectLight(math::Point3D point, std::unique_ptr<RayTracer::IObject> &s, std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2, RayTracer::Ray ray) override;

            math::Vector3D getDir() override { return {0, 0, 0};};
            double getIntensity() override;
            RayTracer::IObject &getBulb() override;

            ~pointLight();

        private:
            std::unique_ptr<RayTracer::Sphere> _bulb;
            double _intensity;
    };
}

#endif //BOOTSTRAP_RAYTRACING_POINT_LIGHT_HPP
