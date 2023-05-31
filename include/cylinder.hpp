/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** cylinder.hpp
*/

#ifndef BOOTSTRAP_RAYTRACING_CYLINDER_HPP
    #define BOOTSTRAP_RAYTRACING_CYLINDER_HPP

#include "vector.hpp"
#include "point.hpp"
#include "memory"
#include "iostream"
#include "SFML/Graphics.hpp"
#include "IObject.hpp"

namespace RayTracer {
    class Cylinder : public IObject {
        public:
            Cylinder();
            Cylinder(Cylinder &&other);
            Cylinder(Cylinder &other);
            Cylinder(RayTracer::IObject &&other);
            Cylinder(math::Point3D center, double radius, sf::Color color, math::Vector3D axis);
            bool operator==(const RayTracer::Cylinder &other) const;
            bool hit(RayTracer::Ray ray) override;
            double getDistFromCam() override;
            ~Cylinder();

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
            math::Point3D getBasePoint() override;
            void setBasePoint(math::Point3D &base) override;
            math::Point3D getTopPoint() override;
            void setTopPoint(math::Point3D &top) override;
            double getAngle() override {return 0;}
            void setAngle([[maybe_unused]] double angle) override {}
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
            math::Vector3D _axis;
            bool _isReflective;
    };
}

#endif //BOOTSTRAP_RAYTRACING_CYLINDER_HPP
