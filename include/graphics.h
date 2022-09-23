#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string.h>

struct Vec2i{
    int x;
    int y;
};

struct Vec2f{
    float x;
    float y;
    Vec2f(){};
    Vec2f(float a,float b):x(a),y(b){}
};

void line(const Vec2f& p1,const Vec2f& p2){
    glBegin(GL_LINES);
    glVertex2f(p1.x,p1.y);
    glVertex2f(p2.x,p2.y);
    glEnd();
}

void line(int x1,int y1,int x2,int y2){
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

void putpixel(float x1,float y1){
    glBegin(GL_POINTS);
    glVertex2f(x1,y1);
    glEnd();
}


class Graphics{
public:
    class invalid_window_dimensions{};
    class glfw_init_failed{};
    class glew_init_failed{};
    class invalid_argument{};
};


class Window{
    int width;
    int height;
    const char* title;
    GLFWwindow* win;
    void init(){
        GLFWwindow* window;

        if (!glfwInit()) throw Graphics::glfw_init_failed();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

        window = glfwCreateWindow(this->width, this->height,this->title, NULL, NULL);
        if (!window){
            glfwTerminate();
            throw Graphics::glfw_init_failed();
        }

        glfwMakeContextCurrent(window);
        if (glewInit() != GLEW_OK) throw Graphics::glew_init_failed();
        glGetString(GL_VERSION);
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, this->width, this->height);
        glOrtho(0, this->width, this->height, 0, 0,1);
        win=window;
    }
public:
    void setSize(Vec2i& v){
        this->width=v.x;
        this->height=v.y;
    }

    Window()=default;
    Window(int _w,int _h,const char* _t){
        if(_w <=0 || _h <= 0) throw Graphics::invalid_window_dimensions();
        if(strlen(_t)==0) throw Graphics::invalid_argument();
        this->width=_w;
        this->height=_h;
        this->title=_t;
        this->init();
    }

    bool isOpen(){
        return !glfwWindowShouldClose(this->win);
    }

    void swapBuffers(){
        glfwSwapBuffers(this->win);
        glfwPollEvents();
    }

    void clear(){
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void clear(float r,float g,float b, float a){
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void destroy(){
        glfwDestroyWindow(this->win);
        glfwTerminate();
    }
};



#endif