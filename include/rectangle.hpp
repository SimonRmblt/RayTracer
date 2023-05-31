/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** rectangle.hpp
*/

#ifndef BOOTSTRAP_RAYTRACING_RECTANGLE_HPP
    #define BOOTSTRAP_RAYTRACING_RECTANGLE_HPP

#include "sphere.hpp"

class Rectangle3D {
    public:
        Rectangle3D();
        Rectangle3D(math::Point3D origin, math::Point3D bottomRightPoint, math::Point3D topLeftPoint);
        Rectangle3D(math::Point3D origin, math::Point3D bottomRightPoint, math::Point3D topLeftPoint, double ratio);
        ~Rectangle3D() = default;
        math::Point3D pointAt(double u, double v);


        math::Point3D _origin;
        math::Point3D _bottomRightPoint;
        math::Point3D _topLeftPoint;
};

#endif //BOOTSTRAP_RAYTRACING_RECTANGLE_HPP
