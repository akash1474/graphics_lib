#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <string.h>
#include "math.h"
#include "iostream"

struct Vec2i{
    int x;
    int y;
    Vec2i(){};
    Vec2i(int a,int b):x(a),y(b){}
};

struct Vec2f{
    float x;
    float y;
    Vec2f(){};
    Vec2f(float a,float b):x(a),y(b){}
};

struct Color{
    int r=255,g=255,b=255,a=255;
    Color(){};
    Color(int x):r(x),g(x),b(x),a(255){}
    Color(int _r,int _g,int _b,int _a=255):r(_r),g(_g),b(_b){}
};

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
    void init();
public:
    void setSize(Vec2i& v);
    GLFWwindow* getglfwWindow();
    Window()=default;
    Window(int _w,int _h,const char* _t);
    bool isOpen();
    void swapBuffers();
    void clear();
    void clear(int x);
    void clear(float r,float g,float b, float a=1.0f);
    void destroy();
};

namespace glx{
    static double mx=0,my=0;
    static bool fillEnabled=true;
    static bool strokeEnabled=true;

    void enableFill();
    void enableStroke();
    void reset();
    inline static void stroke(int x){glColor3ub(x,x,x); }
    void stroke(int r,int g,int b,int a=255);
    inline static void fill(int x){glColor3ub(x,x,x); }
    void fill(int r,int g,int b,int a=255);
    void event(GLFWwindow* w);
    Vec2i mousePos();
    void Color(int r,int g,int b,int a=255);
    bool line(int x1,int y1,int x2,int y2);
    void strokeWidth(int x=1);


    void ellipse(GLfloat cx, GLfloat cy, GLfloat rx,GLfloat ry);
    bool circle(float cx, float cy, float r, int num_segments=25);

    void quad(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
    void quad(Vec2i& p1,Vec2i& p2,Vec2i& p3,Vec2i& p4);

    void rect(int x1,int y1,int x2,int y2);
    void rect(Vec2i& p1,Vec2i& p2);

    void square(int x1,int y1,int s);
    void square(Vec2i& p,int x);

    void line(const Vec2f& p1,const Vec2f& p2);
    void line(const Vec2i& p1,const Vec2i& p2);


    void putpixel(float x1,float y1);


    bool point(int x,int y,float strokeWidth=2);
    void point(Vec2i a);

    float lerp(int x,int y,float t);
    Vec2i lerp(Vec2i& x,Vec2i& y,float t);

    void beginShape(GLenum a=GL_LINE_STRIP);
    void endShape();
    void vertex(int x,int y);
    void vertex(Vec2i a);
};



#endif