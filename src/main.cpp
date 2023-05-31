/*
** EPITECH PROJECT, 2023
** Raytracer
** File description:
** main.cpp
*/

#include "raytracer.hpp"
#include "cstring"

int main([[maybe_unused]] int ac, char **av)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::unique_ptr<RayTracer::FileParsing> parse = std::make_unique<RayTracer::FileParsing>();
    try {
        parse->parseFile(av[1]);
        std::unique_ptr<RayTracer::Raytracer> rtx = std::make_unique<RayTracer::Raytracer>(parse);
        rtx->bubbleSort(rtx->getObjects());
        rtx->renderScene();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        long seconds = duration.count() / 1000;
        long milliseconds = duration.count() % 1000;
        std::cout << "Time taken to compute: " << seconds << "." << milliseconds << std::endl;
        rtx->display();
    } catch (const std::exception &e) {
        if (ac == 1)
            std::cerr << "Error: No file given" << std::endl;
        else if (strcmp(av[1], "-h") == 0) {
            std::cout << "USAGE:\n\t./raytracer [config file]" << std::endl;
            std::cout << "KEYS" << std::endl;
            std::cout << "\tA\t\tScreenshot" << std::endl;
            std::cout << "\tZ\t\tForward" << std::endl;
            std::cout << "\tS\t\tBackward" << std::endl;
            std::cout << "\tUP\t\tUp" << std::endl;
            std::cout << "\tDOWN\t\tDown" << std::endl;
            std::cout << "\tLEFT\t\tLeft" << std::endl;
            std::cout << "\tRIGHT\t\tRight" << std::endl;
            std::cout << "\tSPACEBAR\tReload scene" << std::endl;
        } else
            std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
