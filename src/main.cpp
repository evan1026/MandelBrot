#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "Logger.hpp"
#include "main.hpp"
#include <sstream>
#include <iostream>

#define WIDTH 1275
#define HEIGHT 740

using namespace std;

bool running = true;

sf::Vector3<float> colors[WIDTH][HEIGHT + 1];

int main(int argc, char *argv[]){

    sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");    

    int pixX = 0;
    int pixY = 1;

    glClear(GL_COLOR_BUFFER_BIT);
    
    Logger::log("Starting rendering...");
    cout << "00% complete";
    
    int doneAt = WIDTH * HEIGHT;
    int at = 0;

    bool finished = false;
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
            render(pixX, pixY);
            at++;
            int percent = (float)at / doneAt * 100;
            if (percent < 10) cout << "\b\b\b\b\b\b\b\b\b\b\b\b0" << percent << "% complete";
            else cout << "\b\b\b\b\b\b\b\b\b\b\b\b" << percent << "% complete";
            pixX = (pixX + 1) % WIDTH;
            if (pixX == 0) pixY++;
        }
        else if (!finished){
            finished = true;
            cout << endl;
            Logger::log("Finished rendering!");
            
            window.setVerticalSyncEnabled(true);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, WIDTH, HEIGHT, 0, 0, 1); 
            glMatrixMode(GL_MODELVIEW);
            glDisable(GL_DEPTH_TEST);
        
            Logger::log("Initialized window.");

        }
        else{
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);    
            for (int i = 0; i < WIDTH; i++){
                for (int j = 1; j < HEIGHT + 1; j++){
                    glColor3f(colors[i][j].x, colors[i][j].y, colors[i][j].z);
                    glVertex2i(i, j);
                }
            }
            glEnd();
            window.display();
        }

        //window.display();
    }

    window.close();
    Logger::log("Window closed.");
    
    Logger::log("Exiting...");
    return 0;
}

void render(int pixX, int pixY){
    //glBegin(GL_POINTS);
    //Logger::log(intToString(pixX) + " " + intToString(pixY));

    double x0 = (double) pixX / (double) WIDTH * 3.5 - 2.5;
    double y0 = (double) pixY / (double) HEIGHT * 2.0 - 1.0;
    //Logger::log(floatToString(x0) + " " + floatToString(y0));
    int iteration = 0;
    int max_iteration = 10000;

    double x = 0;
    double y = 0;

    while ((x*x) + (y*y) < 4 && iteration < max_iteration){
        double xtemp = x*x - y*y + x0;
        y = 2 * x * y + y0;
        
        x = xtemp;
        
        iteration++;
        //Logger::log(intToString(x) + " " + intToString(y) + " " + intToString(iteration));
    }
    double red=0, green=0, blue=0;
    if (iteration >= max_iteration){
        //glColor3f(0, 0, 0);
    }
    else{
        long temp = iteration * 0b1000000000000000000000000 / max_iteration;
        red = temp & 0b111111110000000000000000;
        green = temp & 0b1111111100000000;
        blue = temp & 0b11111111;
        //Logger::log(intToString(pixX) + " " + intToString(pixY) + " " + intToString(red) + " " + intToString(green) + " " + intToString(blue));
        //glColor3f(red / 0b1000000000000000000000000, green / 0b10000000000000000, blue / 0b100000000);
    }
    colors[pixX][pixY] = sf::Vector3<float>(red / 0b1000000000000000000000000, green / 0b10000000000000000, blue / 0b100000000);
    //glVertex2i(pixX, pixY);
    //glEnd();
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
