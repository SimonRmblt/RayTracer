/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** directionalLight.hpp
*/

#ifndef BOOTSTRAP_RAYTRACING_DIR_LIGHT_HPP
    #define BOOTSTRAP_RAYTRACING_DIR_LIGHT_HPP

#include "sphere.hpp"
#include "ILight.hpp"

namespace RayTracer {
    class DirectionalLight : public ILight {
        public:
            DirectionalLight();
            DirectionalLight(math::Vector3D dir, double ambientLight);

            sf::Color getColorByLight(math::Point3D point, std::unique_ptr<RayTracer::Sphere> &s) override;
            sf::Color castShadow(math::Point3D point, std::unique_ptr<RayTracer::IObject> &s, std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2) override;
            sf::Color reflectLight(math::Point3D point, std::unique_ptr<RayTracer::IObject> &s, std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &s2, RayTracer::Ray ray) override;

            math::Vector3D getDir() override;
            double getIntensity() override;
            RayTracer::IObject &getBulb() override { return *new RayTracer::Sphere();};

            ~DirectionalLight();

        private:
            math::Vector3D _dir;
            double _ambientLight;
    };
}

#endif //BOOTSTRAP_RAYTRACING_DIR_LIGHT_HPP
