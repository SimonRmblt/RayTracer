/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** point.hpp
*/

#ifndef BOOTSTRAP_RAYTRACING_POINT_HPP
    #define BOOTSTRAP_RAYTRACING_POINT_HPP

#include "vector.hpp"

namespace math {
    class Vector3D;

    class Point3D {
        public:
            Point3D();
            Point3D(double x, double y, double z);
            Point3D(Point3D &other);
            Point3D(Point3D &&other) noexcept;
            ~Point3D();

            bool operator==(const math::Point3D &other) const;
            Point3D &operator=(const math::Point3D &other);
            Point3D operator+(const math::Vector3D &other);
            Point3D operator-(const math::Vector3D &other) const;
            Point3D &operator+=(const math::Vector3D &other);

            double x;
            double y;
            double z;
    };
}

#endif //BOOTSTRAP_RAYTRACING_POINT_HPP
