/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** ray.hpp
*/

#ifndef BOOTSTRAP_RAYTRACING_RAY_HPP
    #define BOOTSTRAP_RAYTRACING_RAY_HPP

#include "vector.hpp"
#include "point.hpp"
#include "memory"
#include "IObject.hpp"
#include "vector"

namespace RayTracer {

    class Ray {
        public:
            Ray();
            Ray(math::Point3D origin, math::Vector3D direction);
            Ray(Ray &other);
            Ray(Ray &&other) noexcept;
            template<typename T>
            std::unique_ptr<RayTracer::IObject> getClosestPoint(std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &objs, std::unique_ptr<RayTracer::IObject> &obj, RayTracer::Ray r) {
                math::Point3D p = obj->getHitPoint();
                std::unique_ptr<T> closest = nullptr;
                for (auto &it: *objs) {
                    if (it && it != obj && it->hit(r)) {
                        math::Vector3D vec1 = {it->getHitPoint().x - r._origin.x, it->getHitPoint().y - r._origin.y, it->getHitPoint().z - r._origin.z};
                        math::Vector3D vec2 = {p.x - r._origin.x, p.y - r._origin.y, p.z - r._origin.z};
                        if (vec1.length() < vec2.length()) {
                            p = it->getHitPoint();
                            closest = std::unique_ptr<T>(dynamic_cast<T*>(it->clone().release()));
                        }
                    }
                }
                this->_closestPoint = std::make_unique<math::Point3D>(p);
                if (closest) {
                    return closest;
                } else {
                    return nullptr;
                }
            }

            math::Vector3D normal(math::Vector3D vec);

            ~Ray();

            math::Point3D _origin;
            math::Vector3D _direction;
            std::unique_ptr<math::Point3D> _closestPoint;
    };
}

#endif //BOOTSTRAP_RAYTRACING_RAY_HPP
