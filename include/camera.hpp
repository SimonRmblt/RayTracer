/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** camera.hpp
*/

#ifndef BOOTSTRAP_RAYTRACING_CAMERA_HPP
    #define BOOTSTRAP_RAYTRACING_CAMERA_HPP

#include "rectangle.hpp"

namespace RayTracer {
    class Camera {
        public:
            Camera();
            Camera(math::Point3D origin, Rectangle3D screen);
            ~Camera();
            Ray ray(double u, double v);

            math::Point3D _origin;
            Rectangle3D _screen;
            sf::VideoMode _videoMode;
            double _fov;
            double _aspectRatio;

    };
}

#endif //BOOTSTRAP_RAYTRACING_CAMERA_HPP
