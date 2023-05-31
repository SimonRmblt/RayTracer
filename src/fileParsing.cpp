/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** fileParsing.cpp
*/

#include "fileParsing.hpp"

RayTracer::FileParsing::FileParsing() {
    this->_config = new libconfig::Config();
    this->_shapes = std::make_unique<std::vector<std::unique_ptr<RayTracer::IObject>>>();
    this->_lights = std::vector<std::unique_ptr<RayTracer::ILight>>();
    this->_ambient = 0;
}

RayTracer::FileParsing::~FileParsing() = default;


void RayTracer::FileParsing::parseFile(std::string file) {
    try {
        this->_config->readFile(file);
    } catch (libconfig::FileIOException &e) {
        throw std::runtime_error(
                std::string("FileIOException occurred. Could not read \"") +
                file + "\"!");
    } catch (libconfig::ParseException &e) {
        throw std::runtime_error(
                std::string("Parse error at ") + e.getFile() + ":" +
                std::to_string(e.getLine()) +
                " - " + e.getError());
    }
    this->_file = file;
    this->parseCam();
    this->parseShapes();
    this->parseLights();
}

void RayTracer::FileParsing::parseShapes() {
    libconfig::Setting& primitives = this->_config->lookup("primitives");
    if (primitives.exists("spheres")) {
        libconfig::Setting& spheres = primitives.lookup("spheres");
        int sphereCount = spheres.getLength();
        for (int i = 0; i < sphereCount; ++i) {
            libconfig::Setting& sphere = spheres[i];
            double x = 0, y = 0, z = 0, radius = 0;
            unsigned int r = 0, g = 0, b = 0;
            bool reflective = false;
            sphere.lookupValue("x", x);
            sphere.lookupValue("y", y);
            sphere.lookupValue("z", z);
            sphere.lookupValue("r", radius);
            libconfig::Setting& color = sphere.lookup("color");
            color.lookupValue("r", r);
            color.lookupValue("g", g);
            color.lookupValue("b", b);
            sphere.lookupValue("reflective", reflective);
            auto s = createShapes("sphere");
            math::Point3D p{x, y, z};
            sf::Color c(r, g, b);
            s->setCenter(p);
            s->setRadius(radius);
            s->setColor(c);
            s->setReflection(reflective);
            this->addObject(std::move(s));
        }
    }
    if (primitives.exists("planes")) {
        libconfig::Setting& planes = primitives.lookup("planes");
        int planeCount = planes.getLength();
        for (int i = 0; i < planeCount; ++i) {
            libconfig::Setting& plane = planes[i];
            double ax = 0, ay = 0, az = 0;
            double px = 0, py = 0, pz = 0;
            unsigned int r = 0, g = 0, b = 0;
            bool reflective = false;
            libconfig::Setting& axis = plane.lookup("axis");
            axis.lookupValue("x", ax);
            axis.lookupValue("y", ay);
            axis.lookupValue("z", az);
            libconfig::Setting& pos = plane.lookup("position");
            pos.lookupValue("x", px);
            pos.lookupValue("y", py);
            pos.lookupValue("z", pz);
            libconfig::Setting& color = plane.lookup("color");
            color.lookupValue("r", r);
            color.lookupValue("g", g);
            color.lookupValue("b", b);
            plane.lookupValue("reflective", reflective);
            auto p = createShapes("plane");
            math::Point3D point{px, py, pz};
            sf::Color c(r, g, b);
            math::Vector3D v(ax, ay, az);
            p->setCenter(point);
            p->setColor(c);
            p->setNormal(v);
            p->setReflection(reflective);
            this->addObject(std::move(p));
        }
    }
    if (primitives.exists("cylinders")) {
        libconfig::Setting& cylinders = primitives.lookup("cylinders");
        int cylindersCount = cylinders.getLength();
        for (int i = 0; i < cylindersCount; ++i) {
            libconfig::Setting& cylinder = cylinders[i];
            double x = 0, y = 0, z = 0, radius = 0;
            unsigned int r = 0, g = 0, b = 0;
            double ax = 0, ay = 0, az = 0;
            bool reflective = false;
            cylinder.lookupValue("x", x);
            cylinder.lookupValue("y", y);
            cylinder.lookupValue("z", z);
            libconfig::Setting& axis = cylinder.lookup("axis");
            axis.lookupValue("x", ax);
            axis.lookupValue("y", ay);
            axis.lookupValue("z", az);
            libconfig::Setting& color = cylinder.lookup("color");
            color.lookupValue("r", r);
            color.lookupValue("g", g);
            color.lookupValue("b", b);
            cylinder.lookupValue("radius", radius);
            cylinder.lookupValue("reflective", reflective);
            sf::Color cylColor = {static_cast<sf::Uint8>(r),
                      static_cast<sf::Uint8>(g),
                      static_cast<sf::Uint8>(b)};
            auto c = createShapes("cylinder");
            math::Point3D p{x, y, z};
            math::Vector3D v{ax, ay, az};
            c->setCenter(p);
            c->setColor(cylColor);
            c->setNormal(v);
            c->setRadius(radius);
            c->setReflection(reflective);
            this->addObject(std::move(c));
        }
    }
}

void RayTracer::FileParsing::parseCam() {
    libconfig::Setting& cam = this->_config->lookup("camera");
    if (cam.exists("resolution") && cam.exists("position")) {
        int width = 0, height = 0;
        double x = 0, y = 0, z = 0;
        unsigned int r = 0, g = 0, b = 0;
        double fov = 0;
        sf::Color bgColor;
        libconfig::Setting& res = cam.lookup("resolution");
        res.lookupValue("width", width);
        res.lookupValue("height", height);
        this->_videoMode = {static_cast<unsigned int>(width), static_cast<unsigned int>(height), 32};
        libconfig::Setting& pos = cam.lookup("position");
        pos.lookupValue("x", x);
        pos.lookupValue("y", y);
        pos.lookupValue("z", z);
        libconfig::Setting& color = cam.lookup("background");
        color.lookupValue("r", r);
        color.lookupValue("g", g);
        color.lookupValue("b", b);
        bgColor = {static_cast<sf::Uint8>(r),
                   static_cast<sf::Uint8>(g),
                   static_cast<sf::Uint8>(b)};
        this->_camPos = math::Point3D{x, y, z};
        this->_fov = fov;
        this->_bgColor = bgColor;
    }
}

void RayTracer::FileParsing::parseLights() {
    libconfig::Setting& lights = this->_config->lookup("lights");
    if (lights.exists("directionalIntensity")) {
        double a = 0;
        lights.lookupValue("directionalIntensity", a);
        if (a >= 0 && a <= 1)
            this->_dirIntensity = a;
        else if (a < 0)
            this->_dirIntensity = 0;
        else
            this->_dirIntensity = 1;
    }
    if (lights.exists("ambient")) {
        double a = 0;
        lights.lookupValue("ambient", a);
        if (a >= 0 && a <= 1)
            this->_ambient = a;
        else if (a < 0)
            this->_ambient = 0;
        else
            this->_ambient = 1;
    }
    if (lights.exists("directional")) {
        libconfig::Setting& dirLights = lights.lookup("directional");
        int dirLightCount = dirLights.getLength();
        for (int i = 0; i < dirLightCount; ++i) {
            libconfig::Setting& dirLight = dirLights[i];
            double x = 0, y = 0, z = 0;
            dirLight.lookupValue("x", x);
            dirLight.lookupValue("y", y);
            dirLight.lookupValue("z", z);
            math::Vector3D vec{x, y, z};
            vec.normal();
            auto light = DirectionalLightBuilder()
                    .setDirection(vec)
                    .setAmbientLight(this->_dirIntensity)
                    .build();
            this->addLight(std::move(light));
        }
    }
}

void RayTracer::FileParsing::addLight(std::unique_ptr<RayTracer::ILight> dirLight) {
    this->_lights.push_back(std::move(dirLight));
}

void RayTracer::FileParsing::addObject(std::unique_ptr<RayTracer::IObject> obj) {
    this->_shapes->push_back(std::move(obj));
}

std::unique_ptr<std::vector<std::unique_ptr<RayTracer::IObject>>> &
RayTracer::FileParsing::getShapes() {
    return this->_shapes;
}

std::vector<std::unique_ptr<RayTracer::ILight>> &
RayTracer::FileParsing::getLights() {
    return this->_lights;
}

sf::VideoMode &RayTracer::FileParsing::getVideoMode() {
    return this->_videoMode;
}

math::Point3D &RayTracer::FileParsing::getCamPos() {
    return this->_camPos;
}

math::Vector3D &RayTracer::FileParsing::getCamDir() {
    return this->_camDir;
}

double &RayTracer::FileParsing::getFov() {
    return this->_fov;
}

double &RayTracer::FileParsing::getDirIntensity() {
    return this->_dirIntensity;
}

std::string &RayTracer::FileParsing::getFile() {
    return this->_file;
}

sf::Color &RayTracer::FileParsing::getBgColor() {
    return this->_bgColor;
}

double &RayTracer::FileParsing::getAmbient() {
    return this->_ambient;
}
