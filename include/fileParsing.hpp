/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** FileParsing.hpp
*/

#ifndef RAYTRACER_FILEPARSING_HPP
    #define RAYTRACER_FILEPARSING_HPP

#include "iostream"
#include "fstream"
#include "SFML/Graphics.hpp"
#include "vector.hpp"
#include "point.hpp"
#include "memory"
#include "IObject.hpp"
#include "directionalLight.hpp"
#include "libconfig.h++"
#include "cone.hpp"
#include "cylinder.hpp"
#include <unordered_map>
#include <functional>
#include "plane.hpp"
#include "pointLight.hpp"

namespace RayTracer {

    class ILightBuilder {
        public:
            virtual std::unique_ptr<ILight> build() = 0;
            virtual ~ILightBuilder() = default;
    };

    class DirectionalLightBuilder : public ILightBuilder {
        public:
            DirectionalLightBuilder& setDirection(const math::Vector3D& direction) {
                _direction = direction;
                return *this;
            }
            DirectionalLightBuilder& setAmbientLight(double ambientLight) {
                _ambientLight = ambientLight;
                return *this;
            }
            std::unique_ptr<ILight> build() override {
                return std::make_unique<DirectionalLight>(_direction, _ambientLight);
            }
        private:
            math::Vector3D _direction;
            double _ambientLight;
    };

    class PointLightBuilder : public ILightBuilder {
        public:
            PointLightBuilder& setAmbientLight(double ambientLight) {
                _ambientLight = ambientLight;
                return *this;
            }
            PointLightBuilder& setSphere(std::unique_ptr<RayTracer::Sphere> sphere) {
                _sphere = std::move(sphere);
                return *this;
            }
            std::unique_ptr<ILight> build() override {
                return std::make_unique<pointLight>(*_sphere, _ambientLight);
            }
        private:
            std::unique_ptr<RayTracer::Sphere> _sphere;
            double _ambientLight;
    };

    class FileParsing {
        public:
            FileParsing();
            ~FileParsing();

            void parseFile(std::string file);
            void parseShapes();
            void parseCam();
            void parseLights();

            void addObject(std::unique_ptr<RayTracer::IObject> obj);
            void addLight(std::unique_ptr<RayTracer::ILight> dirLight);

            std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &getShapes();
            std::vector<std::unique_ptr<RayTracer::ILight>> &getLights();
            sf::VideoMode &getVideoMode();
            math::Point3D &getCamPos();
            math::Vector3D &getCamDir();
            double &getFov();
            double &getDirIntensity();
            double &getAmbient();
            std::string &getFile();
            sf::Color &getBgColor();
            static std::unique_ptr<IObject>
            createShapes(const std::string &type)
            {
                static const std::unordered_map<std::string, std::function<std::unique_ptr<IObject>()>> objectFactories {
                        {"sphere", [](){ return std::make_unique<RayTracer::Sphere>(); }},
                        {"plane", [](){ return std::make_unique<RayTracer::Plane>(); }},
                        {"cylinder", [](){ return std::make_unique<RayTracer::Cylinder>(); }},
                };
                auto it = objectFactories.find(type);
                if (it == objectFactories.end()) {
                    std::cerr << "Invalid object type: " + type << std::endl;
                    return nullptr;
                }
                return it->second();
            }
        private:
            libconfig::Config *_config;
            std::string _file;
            sf::VideoMode _videoMode;
            math::Point3D _camPos;
            math::Vector3D _camDir;
            double _fov;
            double _dirIntensity;
            double _ambient;
            std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> _shapes;
            std::vector<std::unique_ptr<RayTracer::ILight>> _lights;
            sf::Color _bgColor;
    };
}

#endif //RAYTRACER_FILEPARSING_HPP
