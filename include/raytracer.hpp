/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** raytracer.hpp
*/

#ifndef RAYTRACER_RAYTRACER_HPP
    #define RAYTRACER_RAYTRACER_HPP

    #include <libconfig.h++>
    #include "iostream"
    #include "vector"
    #include "string"
    #include "SFML/Graphics.hpp"
    #include "rectangle.hpp"
    #include "camera.hpp"
    #include "sphere.hpp"
    #include "directionalLight.hpp"
    #include "fstream"
    #include "fileParsing.hpp"
    #include "rectangle.hpp"
    #include "plane.hpp"
    #include "cone.hpp"
    #include "cylinder.hpp"
    #include "pointLight.hpp"
    #include <algorithm>
    #include <chrono>

namespace RayTracer {
    class Raytracer {
        public:
            Raytracer();
            explicit Raytracer(std::unique_ptr<RayTracer::FileParsing> &parser);
            std::unique_ptr<sf::RenderWindow> &getWindow();
            std::unique_ptr<sf::Image> &getImage();
            void setCamera(RayTracer::Camera &cam);
            std::unique_ptr<RayTracer::Camera> &getCamera();
            void setObjects(std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &obj);
            std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &getObjects();
            void setLights(std::vector<std::unique_ptr<RayTracer::ILight>> &lights);
            std::vector<std::unique_ptr<RayTracer::ILight>> &getLights();
            void setDistFromCam(std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &obj);
            void bubbleSort(std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &obj);
            void renderScene();
            void display();
            void hitCompute(int i, int j);
            void addObject(std::unique_ptr<RayTracer::IObject> obj);
            void addLight(std::unique_ptr<RayTracer::ILight> dirLight);
            sf::Color getColorAverage(math::Point3D &point, std::unique_ptr<RayTracer::IObject> &obj, std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &objs);
            sf::Color getReflectionAverage(math::Point3D &point, std::unique_ptr<RayTracer::IObject> &obj, std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &objs, RayTracer::Ray &ray);
            void restart();
            void inputCheck();

            ~Raytracer() = default;
        private:
            std::unique_ptr<sf::RenderWindow> _window;
            libconfig::Config *_config;
            std::unique_ptr<sf::Image> _image;
            std::unique_ptr<RayTracer::Camera> _cam;
            std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> _objects;
            std::vector<std::unique_ptr<RayTracer::ILight>> _lights;
            std::unique_ptr<sf::Texture> texture;
            std::unique_ptr<sf::Sprite> sprite;
            std::unique_ptr<math::Point3D> _closestPoint;
            double _ambientLight;
            double _dirIntensity;
            std::string _configFile;
            std::unique_ptr<sf::Event> _event;
            sf::Color _bgColor;
    };
}

#endif //RAYTRACER_RAYTRACER_HPP
