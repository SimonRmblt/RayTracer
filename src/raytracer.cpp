/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** raytracer.cpp
*/

#include "raytracer.hpp"

RayTracer::Raytracer::Raytracer() {
    this->_cam = std::make_unique<RayTracer::Camera>();
    this->_objects = std::make_unique<std::vector<std::unique_ptr<RayTracer::IObject>>>();
    this->_lights = std::vector<std::unique_ptr<RayTracer::ILight>>();
    this->texture = std::make_unique<sf::Texture>();
    this->sprite = std::make_unique<sf::Sprite>();
    this->_closestPoint = std::make_unique<math::Point3D>();
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1080, 1080), "Ray Tracing");
    this->_image = std::make_unique<sf::Image>();
    this->_image->create(1080, 1080, sf::Color::Black);
    this->_config = new libconfig::Config();
    this->_configFile = "";
    this->_event = std::make_unique<sf::Event>();
    this->_bgColor = sf::Color(10, 10, 30);
}

RayTracer::Raytracer::Raytracer(
        std::unique_ptr<RayTracer::FileParsing> &parser) {
    this->_cam = std::make_unique<RayTracer::Camera>();
    this->_cam->_origin = parser->getCamPos();
    this->_cam->_videoMode = parser->getVideoMode();
    this->_cam->_aspectRatio = _cam->_videoMode.width / static_cast<double>(_cam->_videoMode.height);
    math::Point3D bottomRightPoint = math::Point3D(static_cast<double>(this->_cam->_videoMode.width) / this->_cam->_videoMode.height, 0, 0);
    math::Point3D topLeftPoint = math::Point3D(0, static_cast<double>(this->_cam->_videoMode.height) / this->_cam->_videoMode.height, 0);
    this->_cam->_screen = Rectangle3D(this->_cam->_screen._origin, bottomRightPoint, topLeftPoint);
    this->_dirIntensity = parser->getDirIntensity();
    this->_ambientLight = parser->getAmbient();
    this->_objects = std::move(parser->getShapes());
    this->_lights = std::move(parser->getLights());
    this->texture = std::make_unique<sf::Texture>();
    this->sprite = std::make_unique<sf::Sprite>();
    this->_closestPoint = std::make_unique<math::Point3D>();
    this->_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(this->_cam->_videoMode.width, this->_cam->_videoMode.height), "Ray Tracing");
    this->_image = std::make_unique<sf::Image>();
    this->_image->create(this->_cam->_videoMode.width, this->_cam->_videoMode.height, sf::Color::Black);
    this->_config = new libconfig::Config();
    this->_configFile = parser->getFile();
    this->_event = std::make_unique<sf::Event>();
    this->_bgColor = parser->getBgColor();
}

std::unique_ptr<sf::RenderWindow> &RayTracer::Raytracer::getWindow() {
    return this->_window;
}

std::unique_ptr<sf::Image> &RayTracer::Raytracer::getImage() {
    return _image;
}

void RayTracer::Raytracer::setCamera(RayTracer::Camera &cam) {
    this->_cam = std::make_unique<RayTracer::Camera>(cam);
}

std::unique_ptr<RayTracer::Camera> &RayTracer::Raytracer::getCamera() {
    return this->_cam;
}

void RayTracer::Raytracer::setObjects(std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &obj) {
    this->_objects = std::move(obj);
}

std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &RayTracer::Raytracer::getObjects() {
    return this->_objects;
}

void RayTracer::Raytracer::setLights(std::vector<std::unique_ptr<RayTracer::ILight>> &lights) {
    this->_lights = std::move(lights);
}

std::vector<std::unique_ptr<RayTracer::ILight>> &RayTracer::Raytracer::getLights() {
    return this->_lights;
}

void RayTracer::Raytracer::addLight(std::unique_ptr<RayTracer::ILight> light) {
    this->getLights().push_back(std::move(light));
}

void RayTracer::Raytracer::addObject(std::unique_ptr<RayTracer::IObject> obj) {
    this->_objects->push_back(std::move(obj));
}

void RayTracer::Raytracer::bubbleSort(std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &obj) {
    this->setDistFromCam(obj);
    size_t n = obj->size();
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (size_t i = 1; i < n; i++) {
            if (obj->at(i - 1)->getDistFromCam() < obj->at(i)->getDistFromCam()) {
                std::swap(obj->at(i - 1), obj->at(i));
                swapped = true;
            }
        }
        n--;
    }
}

void RayTracer::Raytracer::setDistFromCam(
        std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &objects) {
    for (auto &obj : *objects) {
        obj->setDistFromCam(math::Vector3D{this->_cam->_origin.x - obj->getHitPoint().x,
                                           this->_cam->_origin.y - obj->getHitPoint().y,
                                           this->_cam->_origin.z - obj->getHitPoint().z}.length());
    }
}

void RayTracer::Raytracer::renderScene() {
    for (int i = 0 ; i < static_cast<int>(this->_cam->_videoMode.width); i++) {
        for (int j = 0 ; j < static_cast<int>(this->_cam->_videoMode.height); j++) {
            this->hitCompute(i, j);
        }
    }
}

void RayTracer::Raytracer::hitCompute(int i, int j) {
    double u = i / static_cast<double>(this->_cam->_videoMode.width);
    double v = j / static_cast<double>(this->_cam->_videoMode.height);
    std::unique_ptr<RayTracer::Ray> r = std::make_unique<RayTracer::Ray>(this->getCamera()->ray(u, v));
    r->_direction = r->normal(r->_direction);
    this->getImage()->setPixel(i, j, this->_bgColor);
    for (auto &it : *this->getObjects()) {
        if (it && it->hit(*r)) {
            auto closestObject = r->getClosestPoint<RayTracer::IObject>(this->getObjects(), it, *r);
            if (it->isReflective()) {
                sf::Color color = this->getColorAverage(*r->_closestPoint, closestObject ? closestObject : it, this->getObjects());
                sf::Color color2 = this->getReflectionAverage(*r->_closestPoint, closestObject ? closestObject : it, this->getObjects(), *r);
                this->getImage()->setPixel(i, j, {static_cast<sf::Uint8>( (color.r + color2.r) / 2),
                                                  static_cast<sf::Uint8>( (color.g + color2.g) / 2),
                                                  static_cast<sf::Uint8>( (color.b + color2.b) / 2)});
            } else
                this->getImage()->setPixel(i, j, this->getColorAverage(*r->_closestPoint, closestObject ? closestObject : it, this->getObjects()));
        }
    }
}

void RayTracer::Raytracer::display() {
    while (this->getWindow() && this->getWindow()->isOpen()) {;
        while (this->getWindow()->pollEvent(*this->_event)) {
            if (this->_event->type == sf::Event::Closed || this->_event->key.code == sf::Keyboard::Escape)
                this->getWindow()->close();
            if (this->_event->type == sf::Event::KeyReleased) {
                if (this->_event->key.code == sf::Keyboard::A) {
                    sf::Image image = texture->copyToImage();
                    image.saveToFile("image.png");
                    std::cout << "Image saved to image.png" << std::endl;
                }
                if (this->_event->key.code == sf::Keyboard::Space)
                    this->restart();
                this->inputCheck();
            }
        }
        texture->loadFromImage(*this->getImage());
        this->sprite->setTexture(*this->texture);
        this->getWindow()->clear();
        this->getWindow()->draw(*sprite);
        this->getWindow()->display();
    }
}

void RayTracer::Raytracer::inputCheck() {
    if (this->_event->key.code == sf::Keyboard::Left) {
        this->_cam->_screen._origin.x -= 0.8;
        this->_cam->_origin.x -= 0.8;
        this->_cam->_screen._bottomRightPoint.x -= 0.8;
        this->_cam->_screen._topLeftPoint.x -= 0.8;
        _window->clear(sf::Color::Black);
        this->renderScene();
    }
    if (this->_event->key.code == sf::Keyboard::Right) {
        this->_cam->_screen._origin.x += 0.8;
        this->_cam->_origin.x += 0.8;
        this->_cam->_screen._bottomRightPoint.x += 0.8;
        this->_cam->_screen._topLeftPoint.x += 0.8;
        _window->clear(sf::Color::Black);
        this->renderScene();
    }
    if (this->_event->key.code == sf::Keyboard::Z) {
        this->_cam->_screen._origin.z += 0.8;
        this->_cam->_origin.z += 0.8;
        this->_cam->_screen._bottomRightPoint.z += 0.8;
        this->_cam->_screen._topLeftPoint.z += 0.8;
        _window->clear(sf::Color::Black);
        this->renderScene();
    }
    if (this->_event->key.code == sf::Keyboard::S) {
        this->_cam->_screen._origin.z -= 0.8;
        this->_cam->_origin.z -= 0.8;
        this->_cam->_screen._bottomRightPoint.z -= 0.8;
        this->_cam->_screen._topLeftPoint.z -= 0.8;
        _window->clear(sf::Color::Black);
        this->renderScene();
    }
    if (this->_event->key.code == sf::Keyboard::Down) {
        this->_cam->_screen._origin.y += 0.8;
        this->_cam->_origin.y += 0.8;
        this->_cam->_screen._bottomRightPoint.y += 0.8;
        this->_cam->_screen._topLeftPoint.y += 0.8;
        _window->clear(sf::Color::Black);
        this->renderScene();
    }
    if (this->_event->key.code == sf::Keyboard::Up) {
        this->_cam->_screen._origin.y -= 0.8;
        this->_cam->_origin.y -= 0.8;
        this->_cam->_screen._bottomRightPoint.y -= 0.8;
        this->_cam->_screen._topLeftPoint.y -= 0.8;
        _window->clear(sf::Color::Black);
        this->renderScene();
    }
}

sf::Color RayTracer::Raytracer::getColorAverage(math::Point3D &point,
                                                std::unique_ptr<RayTracer::IObject> &obj,
                                                std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &objs) {
    std::vector<sf::Color> colors;
    for (auto &dl : this->getLights()) {
        colors.push_back(dl->castShadow(point, obj, objs));
    }
    double r = obj->getColor().r * this->_ambientLight, g = obj->getColor().g * this->_ambientLight, b = obj->getColor().b * this->_ambientLight;
    if (!colors.empty()) {
        r = 0, g = 0, b = 0;
    }
    for (auto &color : colors) {
        r += color.r;
        g += color.g;
        b += color.b;
    }
    r > 255 ? r = 255 : r;
    g > 255 ? g = 255 : g;
    b > 255 ? b = 255 : b;
    return {static_cast<sf::Uint8>(r * this->_dirIntensity),
            static_cast<sf::Uint8>(g * this->_dirIntensity),
            static_cast<sf::Uint8>(b * this->_dirIntensity)};
}

void RayTracer::Raytracer::restart() {
    this->getWindow()->close();
    auto start_time = std::chrono::high_resolution_clock::now();
    std::unique_ptr<RayTracer::FileParsing> parse = std::make_unique<RayTracer::FileParsing>();
    try {
        parse->parseFile(this->_configFile);
        std::unique_ptr<RayTracer::Raytracer> rtx = std::make_unique<RayTracer::Raytracer>(parse);
        rtx->bubbleSort(rtx->getObjects());
        rtx->renderScene();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        long seconds = duration.count() / 1000;
        long milliseconds = duration.count() % 1000;
        std::cout << "Time taken to compute reload: " << seconds << "." << milliseconds << std::endl;
        rtx->display();
    } catch (const std::exception &e) {
        throw std::runtime_error(e.what());
    }
}

sf::Color RayTracer::Raytracer::getReflectionAverage(math::Point3D &point,
                                                     std::unique_ptr<RayTracer::IObject> &obj,
                                                     std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &objs,
                                                     RayTracer::Ray &ray) {
    std::vector<sf::Color> colors;
    for (auto &dl : this->getLights()) {
        colors.push_back(dl->reflectLight(point, obj, objs, ray));
    }
    double r = obj->getColor().r * this->_ambientLight, g = obj->getColor().g * this->_ambientLight, b = obj->getColor().b * this->_ambientLight;
    if (!colors.empty()) {
        r = 0, g = 0, b = 0;
    }
    for (auto &color : colors) {
        r += color.r;
        g += color.g;
        b += color.b;
    }
    r > 255 ? r = 255 : r;
    g > 255 ? g = 255 : g;
    b > 255 ? b = 255 : b;
    return {static_cast<sf::Uint8>(r * this->_dirIntensity),
            static_cast<sf::Uint8>(g * this->_dirIntensity),
            static_cast<sf::Uint8>(b * this->_dirIntensity)};
}
