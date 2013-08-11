#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "Logger.hpp"
#include "main.hpp"
#include <sstream>

#define WIDTH 100
#define HEIGHT 100

using namespace std;

bool running = true;

int main(int argc, char *argv[]){
    
    sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "My window");
    window.setVerticalSyncEnabled(true);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);

    Logger::log("Initialized window.");
    
    int pixX = 0;
    int pixY = 1;

    glClear(GL_COLOR_BUFFER_BIT);

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
        if (pixY != HEIGHT + 1){
            render(pixX, pixY, window);
            pixX = (pixX + 1) % WIDTH;
            if (pixX == 0) pixY++;
        }
        //if (pixY == HEIGHT + 1) running = false;

        window.display();
    }

    window.close();
    Logger::log("Window closed.");
    
    Logger::log("Exiting...");
    return 0;
}

void render(int pixX, int pixY, sf::Window& window){
    glBegin(GL_POINTS);
    //Logger::log(intToString(pixX) + " " + intToString(pixY));

    sf::Vector2u size = window.getSize();
    double x0 = (double) pixX / (double) size.x * 3.5 - 2.5;
    double y0 = (double) pixY / (double) size.y * 2.0 - 1.0;
    //Logger::log(floatToString(x0) + " " + floatToString(y0));
    int iteration = 0;
    int max_iteration = 1000;

    double x = 0;
    double y = 0;

    while ((x*x) + (y*y) < 4 && iteration < max_iteration){
        double xtemp = x*x - y*y + x0;
        y = 2 * x * y + y0;
        
        x = xtemp;
        
        iteration++;
        //Logger::log(intToString(x) + " " + intToString(y) + " " + intToString(iteration));
    }

    if (iteration >= max_iteration){
        glColor3f(0, 0, 0);
    }
    else{
        long temp = iteration * (16777216 / max_iteration);
        float red = 0, green = 0, blue = 0;
        red = temp / 65025;
        temp -= red * 65025;
        green = temp / 255;
        temp -= green * 255;
        blue = temp;
        //Logger::log(intToString(pixX) + " " + intToString(pixY) + " " + intToString(red) + " " + intToString(green) + " " + intToString(blue));
        glColor3f(red / 255, green / 255, blue / 255);
    }

    glVertex2i(pixX, pixY);
    glEnd();
}

string intToString(long long int val){
    stringstream ss;
    ss << val;
    return  ss.str();
}

string floatToString(float val){
    stringstream ss;
    ss << val;
    return ss.str();
}
