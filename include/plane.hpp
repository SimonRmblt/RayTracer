/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** plane.hpp
*/

#ifndef RAYTRACER_PLANE_HPP
#define RAYTRACER_PLANE_HPP

#include "SFML/Graphics.hpp"
#include "IObject.hpp"
#include "iostream"

namespace RayTracer {
    class Plane : public IObject {
        public:
            Plane();
            Plane(math::Point3D point, math::Vector3D normal, sf::Color color);
            bool hit(RayTracer::Ray ray) override;
            bool operator==(const RayTracer::Plane &other) const;
            double getDistFromCam() override;
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
            void setTopPoint([[maybe_unused]] math::Point3D &top) override {}
            bool isReflective() override {return _isReflective;}
            math::Vector3D getNormalAt(math::Point3D &point) override;
            std::unique_ptr<RayTracer::IObject> clone() override;
            void setReflection(bool reflective) override {_isReflective = reflective;}

            ~Plane() override;
        private:
            math::Point3D _point;
            math::Vector3D _normal;
            sf::Color _color;
            math::Point3D _hitPoint;
            double _distFromCamera;
            ObjectType _type;
            bool _isReflective;
    };
}

#endif //RAYTRACER_PLANE_HPP
