/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** cone.hpp
*/

#ifndef RAYTRACER_CONE_HPP
#define RAYTRACER_CONE_HPP

#include "SFML/Graphics.hpp"
#include "IObject.hpp"
#include "iostream"

namespace RayTracer {
    class Cone : public IObject {
        public:
            Cone();
            explicit Cone(RayTracer::IObject &other);
            Cone(RayTracer::Cone &other);
            Cone(math::Point3D base, math::Vector3D axis, sf::Color color, double radius, double height, double angle);
            bool hit(RayTracer::Ray ray) override;
            bool operator==(const RayTracer::Cone &other) const;
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
            double getHeight() override;
            void setHeight(double height) override;
            double getAngle() override;
            void setAngle(double angle) override;
            math::Point3D getBasePoint() override {return {};}
            void setBasePoint([[maybe_unused]] math::Point3D &base) override {};
            math::Point3D getTopPoint() override {return {};}
            void setTopPoint([[maybe_unused]] math::Point3D &top) override {}
            bool isReflective() override {return _isReflective;}
            math::Vector3D getNormalAt(math::Point3D &point) override;
            std::unique_ptr<IObject> clone() override;
            void setReflection(bool reflective) override {_isReflective = reflective;}

            ~Cone() override;
        private:
            math::Point3D _base;
            math::Vector3D _axis;
            sf::Color _color;
            double _height;
            double _radius;
            math::Point3D _hitPoint;
            double _distFromCamera;
            ObjectType _type;
            double _angle;
            bool _isReflective;
    };
}

#endif //RAYTRACER_CONE_HPP
