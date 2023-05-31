/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** sphere.hpp
*/

#ifndef BOOTSTRAP_RAYTRACING_SPHERE_HPP
    #define BOOTSTRAP_RAYTRACING_SPHERE_HPP

#include "vector.hpp"
#include "point.hpp"
#include "memory"
#include "iostream"
#include "SFML/Graphics.hpp"
#include "IObject.hpp"

namespace RayTracer {
    class Sphere : public IObject {
        public:
            Sphere();
            Sphere(Sphere &&other);
            Sphere(Sphere &other);
            Sphere(RayTracer::IObject &&other);
            Sphere(math::Point3D center, double radius, sf::Color color);
            bool operator==(const RayTracer::Sphere &other) const;
            bool hit(RayTracer::Ray ray) override;
            double getDistFromCam() override;
            ~Sphere();

            void setDistFromCam(double distance) override;
            double getRadius() override;
            void setRadius(double radius) override;
            math::Point3D getCenter() override;
            void setCenter(math::Point3D &point) override;
            sf::Color getColor() override;
            void setColor(sf::Color &color) override;
            math::Point3D getHitPoint() override;
            void setHitPoint(math::Point3D &hitPoint) override;
            ObjectType getType() override;
            void setType(ObjectType type) override;
            void setNormal(math::Vector3D &normal) override;
            math::Vector3D getNormal() override;
            double getHeight() override {return 0;}
            void setHeight([[maybe_unused]] double height) override {}
            double getAngle() override {return 0;}
            void setAngle([[maybe_unused]] double angle) override {}
            math::Point3D getBasePoint() override {return {};}
            void setBasePoint([[maybe_unused]] math::Point3D &base) override {};
            math::Point3D getTopPoint() override {return {};}
            void setTopPoint([[maybe_unused]]math::Point3D &top) override {}
            bool isReflective() override {return _isReflective;}
            math::Vector3D getNormalAt(math::Point3D &point) override;
            std::unique_ptr<RayTracer::IObject> clone() override;
            void setReflection(bool reflective) override {_isReflective = reflective;}

        private:
            math::Point3D _center;
            double _radius;
            sf::Color _color;
            math::Point3D _hitPoint;
            double _distFromCamera;
            ObjectType _type;
            bool _isReflective;
    };
}

#endif //BOOTSTRAP_RAYTRACING_SPHERE_HPP
