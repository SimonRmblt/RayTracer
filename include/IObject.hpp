/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** IObject.hpp
*/

#ifndef RAYTRACER_IOBJECT_HPP
    #define RAYTRACER_IOBJECT_HPP

#include "memory"
#include "SFML/Graphics.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace RayTracer {
    enum class ObjectType {
        SPHERE,
        PLANE,
        CONE,
        CYLINDER,
    };
    class Ray;
    class IObject {
        public:
            virtual std::unique_ptr<IObject> clone() = 0;
            virtual bool hit(RayTracer::Ray ray) = 0;
            virtual double getDistFromCam() = 0;
            virtual void setDistFromCam(double distance) = 0;
            virtual double getRadius() = 0;
            virtual void setRadius(double radius) = 0;
            virtual math::Point3D getCenter() = 0;
            virtual void setCenter(math::Point3D &point) = 0;
            virtual sf::Color getColor() = 0;
            virtual void setColor(sf::Color &color) = 0;
            virtual math::Point3D getHitPoint() = 0;
            virtual void setHitPoint(math::Point3D &hitPoint) = 0;
            virtual ObjectType getType() = 0;
            virtual void setType(ObjectType type) = 0;
            virtual void setNormal(math::Vector3D &normal) = 0;
            virtual math::Vector3D getNormal() = 0;
            virtual double getHeight() = 0;
            virtual void setHeight(double height) = 0;
            virtual double getAngle() = 0;
            virtual void setAngle(double angle) = 0;
            virtual math::Point3D getBasePoint() = 0;
            virtual void setBasePoint(math::Point3D &base) = 0;
            virtual math::Point3D getTopPoint() = 0;
            virtual void setTopPoint(math::Point3D &top) = 0;
            virtual bool isReflective() = 0;
            virtual void setReflection(bool r) = 0;
            virtual math::Vector3D getNormalAt(math::Point3D &point) = 0;

            virtual ~IObject() = default;
    };
}



#include "ray.hpp"

#endif //RAYTRACER_IOBJECT_HPP
