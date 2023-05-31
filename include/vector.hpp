/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** vector.hpp
*/

#include <cmath>

#ifndef BOOTSTRAP_RAYTRACING_MAIN_HPP
    #define BOOTSTRAP_RAYTRACING_MAIN_HPP

#include "point.hpp"

namespace math {
    class Point3D;

    class Vector3D {
        public:
            Vector3D();
            Vector3D(double x, double y, double z);
            Vector3D(Vector3D &other);
            Vector3D(Vector3D &&other) noexcept ;
            ~Vector3D();
            double length() const;
            double dotProduct(Vector3D other);
            double dotProduct(math::Point3D other);
            void normal();

            bool operator==(const math::Vector3D &other) const;
            Vector3D &operator=(const Vector3D &other);
            Vector3D operator+(const Vector3D &other);
            Vector3D &operator+=(const Vector3D &other);
            Vector3D operator-(const Vector3D &other);
            Vector3D &operator-=(const Vector3D &other);
            Vector3D operator*(const Vector3D &other);
            Vector3D &operator*=(const Vector3D &other);
            Vector3D operator/(const Vector3D &other);
            Vector3D &operator/=(const Vector3D &other);
            Vector3D operator*(double nbr);
            Vector3D &operator*=(double nbr);
            Vector3D operator/(double nbr);
            Vector3D &operator/=(double nbr);


            double x;
            double y;
            double z;
    };
}

#endif //BOOTSTRAP_RAYTRACING_MAIN_HPP
