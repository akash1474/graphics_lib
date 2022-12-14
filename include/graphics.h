#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <ostream>
#include <string.h>
#include "math.h"
#include "iostream"
#include "chrono"
#include "thread"
#include "string"

struct Vec2i{
    int x;
    int y;
    Vec2i(){};
    Vec2i(int a,int b):x(a),y(b){}
    friend std::ostream& operator<<(std::ostream& out,const Vec2i& x);
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
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    unsigned int counter = 0;
    void init();
    void framebuffer_size_callback(GLFWwindow* window, int w, int h);
public:
    static int frameRates;
    static void frameRate(int x);

    void setSize(Vec2i& v);
    GLFWwindow* getglfwWindow();

    Window()=default;
    Window(int _w,int _h,const char* _t);
    void showFps();

    bool isOpen();
    void swapBuffers();

    void clear();
    void clear(int x);
    void clear(float r,float g,float b, float a=1.0f);

    void destroy();
};

namespace color{
    const Color spring_green=Color(0,255,127);
    const Color light_teal=Color(0,180,190);
    const Color cyan=Color(0,238,238);
    const Color golden=Color(255,193,37);
    const Color red=Color(255,64,64);
    const Color light_red=Color(255,106,106);
    const Color blue3=Color(28,134,238);
    const Color blue2=Color(100,149,237);
    const Color blue1=Color(65,105,225);
    const Color light_purple=Color(131,111,255);
    const Color purple=Color(155,48,255);
    const Color deep_pink=Color(255,52,179);
    const Color yellow=Color(255,255,0);

}

namespace glx{
    static double mx=0;
    static double my=0;
    static bool fillEnabled=true;
    static bool strokeEnabled=true;
    static bool clickLeft=false;
    static bool clickRight=false;
    static bool draggingEnabled=false;


    void event(GLFWwindow* w);
    void mouseEventHandler(GLFWwindow*, int, int, int);
    bool mouseClicked(int x=0);
    Vec2i mousePos();
    void enableDragging();
    void reset();

    float constrain(float n,float low,float high);
    float map(float n,float start1,float stop1,float start2,float stop2);

    void enableFill();
    void enableStroke();
    inline static void stroke(int x){glColor3ub(x,x,x); }
    void stroke(int r,int g,int b,int a=255);
    inline static void fill(int x){glColor3ub(x,x,x); }
    void fill(int r,int g,int b,int a=255);
    void fill(const Color& color);
    // void color(int r,int g,int b,int a=255);
    void strokeWidth(int x=1);


    void ellipse(GLfloat cx, GLfloat cy, GLfloat rx,GLfloat ry);
    bool circle(float cx, float cy, float r, int num_segments=25);

    void quad(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
    void quad(Vec2i& p1,Vec2i& p2,Vec2i& p3,Vec2i& p4);

    void rect(int x1,int y1,int x2,int y2);
    void rect(Vec2i& p1,Vec2i& p2);

    void square(int x1,int y1,int s);
    void square(Vec2i& p,int x);

    bool line(int x1,int y1,int x2,int y2);
    bool line(const Vec2f& p1,const Vec2f& p2);
    bool line(const Vec2i& p1,const Vec2i& p2);


    void putpixel(int x1,int y1,const Color& col);


    bool point(int x,int y,float strokeWidth=2);
    bool point(Vec2i a,float strokeWidth=2);

    float lerp(int x,int y,float t);
    Vec2i lerp(Vec2i& x,Vec2i& y,float t);

    void beginShape(GLenum a=GL_LINE_STRIP);
    void endShape();
    void vertex(int x,int y);
    void vertex(Vec2i a);

    double dist(float x1,float y1, float x2,float y2);
};



#endif