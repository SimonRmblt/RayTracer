/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** rectangle.cpp
*/

#include "../include/rectangle.hpp"

Rectangle3D::Rectangle3D() {
    _origin = math::Point3D();
    _bottomRightPoint = math::Point3D(1, 0, 0);
    _topLeftPoint = math::Point3D(0, 1, 0);
}

Rectangle3D::Rectangle3D(math::Point3D origin, math::Point3D bottomRightPoint, math::Point3D topLeftPoint) {
    this->_origin = origin;
    this->_bottomRightPoint = bottomRightPoint;
    this->_topLeftPoint = topLeftPoint;
}

math::Point3D Rectangle3D::pointAt(double u, double v) {
    return {_origin.x + u * (_bottomRightPoint.x - _origin.x) + v * (_topLeftPoint.x - _origin.x),
            _origin.y + u * (_bottomRightPoint.y - _origin.y) + v * (_topLeftPoint.y - _origin.y),
            _origin.z + u * (_bottomRightPoint.z - _origin.z) + v * (_topLeftPoint.z - _origin.z)};
}

Rectangle3D::Rectangle3D(math::Point3D origin, math::Point3D bottomRightPoint,
                         math::Point3D topLeftPoint, double ratio) {
    double currentWidth = bottomRightPoint.x - origin.x;
    double currentHeight = topLeftPoint.y - origin.y;
    double desiredWidth = currentHeight * ratio;
    double desiredHeight = currentWidth / ratio;
    if (currentWidth > desiredWidth) {
        double diff = (currentWidth - desiredWidth) / 2.0f;
        bottomRightPoint.x -= diff;
        topLeftPoint.x += diff;
    } else {
        double diff = (currentHeight - desiredHeight) / 2.0f;
        bottomRightPoint.y += diff;
        topLeftPoint.y -= diff;
    }
    _origin = origin;
    _bottomRightPoint = bottomRightPoint;
    _topLeftPoint = topLeftPoint;
}
