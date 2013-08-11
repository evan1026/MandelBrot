#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "Logger.hpp"

using namespace std;

int main(int argc, char *argv[]){
    
    sf::Window window(sf::VideoMode(800, 600), "My window");
    window.setVerticalSyncEnabled(true);
    Logger::log("Initialized window.");
    
    bool running = true;
    while (running){
        
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                running = false;
            }
            else if (event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.display();
    }

    window.close();
    Logger::log("Window closed.");
    
    Logger::log("Exiting...");
    return 0;
}

