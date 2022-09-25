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
        // glEnable(GL_LINE_SMOOTH);
        glViewport(0, 0, this->width, this->height);
        glOrtho(0, this->width, this->height, 0, 0,1);
        win=window;
    }
public:
    void setSize(Vec2i& v){
        this->width=v.x;
        this->height=v.y;
    }

    GLFWwindow* getglfwWindow(){
        return this->win;
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

    void clear(int x){
        glClearColor((float)x/255.0f,(float)x/255.0f,(float)x/255.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void clear(float r,float g,float b, float a=1.0f){
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void destroy(){
        glfwDestroyWindow(this->win);
        glfwTerminate();
    }
};

namespace glx{
    static double mx=0,my=0;
    static bool doStroke=true;

    void enableFill(){
        doStroke=true;
    }

    void enableStroke(){
        doStroke=false;
    }

    void reset(){
        doStroke=true;
    }

    inline static void stroke(int x){
        glColor3ub(x,x,x);
    }

    void stroke(int r,int g,int b,int a=255){
        glColor4ub(r,g,b,a);
    }

    inline static void fill(int x){
        glColor3ub(x,x,x);
    }

    void fill(int r,int g,int b,int a=255){
        glColor4ub(r,g,b,a);
    }

    void event(GLFWwindow* w){
        glfwGetCursorPos(w, &mx, &my);
    }

    Vec2i mousePos(){
        return Vec2i(mx,my);
    }

    void Color(int r,int g,int b,int a=255){
        glColor4ub(r,g,b,a);
    }

    bool line(int x1,int y1,int x2,int y2){
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glEnd();
        int dx=x2-x1;
        int dy=y2-y1;
        double num=abs((dy*mx)-(dx*my)+(x2*y1)-(y2*x1));
        double deno=sqrt(pow(dy,2)+pow(dx,2));
        return num/deno < 3;
    }

    void strokeWidth(int x=1){
        glLineWidth(x);
    }


    void ellipse(GLfloat cx, GLfloat cy, GLfloat rx,GLfloat ry) {
        int i;
        int amt = 20;
        GLfloat twicePi = 2.0f * 3.141;

        glBegin(doStroke ? GL_LINE_LOOP:GL_POLYGON);
        for (i = 0; i <= amt; i++) {
            glVertex2f(
                cx + ((rx+1)* cos(i * twicePi / amt)),
                cy + ((ry-1)* sin(i * twicePi / amt))
            );
        }
        glEnd();
    }

    bool circle(float cx, float cy, float r, int num_segments=25) {
        glBegin(doStroke ? GL_LINE_LOOP : GL_POLYGON);

        for (int ii = 0; ii < num_segments; ii++)   {
            float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
            float x = r * cosf(theta);
            float y = r * sinf(theta); 
            glVertex2f(x + cx, y + cy); 
        }
        glEnd();
        return sqrt((mx - cx)*(mx - cx) + (my - cy)*(my - cy)) <= r;
    }

    void quad(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
        glBegin(doStroke ? GL_LINE_LOOP : GL_POLYGON);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
        glVertex2i(x3,y3);
        glVertex2i(x4,y4);
        glEnd();
    }

    void quad(Vec2i& p1,Vec2i& p2,Vec2i& p3,Vec2i& p4){
        quad(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y);
    }

    void rect(int x1,int y1,int x2,int y2){
        int dx=abs(x2-x1);
        int dy=abs(y2-y1);
        glBegin(doStroke ? GL_LINE_LOOP : GL_POLYGON);
        glVertex2i(x1,y1);
        glVertex2i(x1+dx,y1);
        glVertex2i(x1+dx,y1+dy);
        glVertex2i(x1,y1+dy);
        glEnd();
    }

    void rect(Vec2i& p1,Vec2i& p2){
       rect(p1.x,p1.y,p2.x,p2.y);
    }

    void square(int x1,int y1,int s){
        glBegin(doStroke ? GL_LINE_LOOP : GL_POLYGON);
        glVertex2i(x1,y1);
        glVertex2i(x1+s,y1);
        glVertex2i(x1+s,y1+s);
        glVertex2i(x1,y1+s);
        glEnd();
    }

    void square(Vec2i& p,int x){
        square(p.x,p.y,x);
    }

    void line(const Vec2f& p1,const Vec2f& p2){
        line(p1.x,p1.y,p2.x,p2.y);
    }

    void line(const Vec2i& p1,const Vec2i& p2){
        line(p1.x,p1.y,p2.x,p2.y);
    }

    void putpixel(float x1,float y1){
        glBegin(GL_POINTS);
        glVertex2f(x1,y1);
        glEnd();
    }


    bool point(int x,int y,float strokeWidth=2){
        glBegin(GL_POLYGON);
        double r = strokeWidth;
        double cx = x;
        double cy = y;
        for (int i = 0; i <= 300; i++) {
            double angle = 2 * 3.141 * i / 300;
            double x = cos(angle) * r;
            double y = sin(angle) * r;
            glVertex2d(cx + x, cy + y);
        }
        glEnd();
        return sqrt((mx - cx)*(mx - cx) + (my - cy)*(my - cy)) <= r;
    }





    void point(Vec2i a){
        point(a.x,a.y);
    }

    float lerp(int x,int y,float t){
        return x+(y-x)*t;
    }

    Vec2i lerp(Vec2i& x,Vec2i& y,float t){
        return Vec2i(x.x + (y.x-x.x)*t,x.y + (y.y-x.y)*t);
    }

    void beginShape(GLenum a=GL_LINE_STRIP){
        glBegin(a);
    }

    void endShape(){
        glEnd();        
    }

    void vertex(int x,int y){
        glVertex2i(x,y);
    }

    void vertex(Vec2i a){
        vertex(a.x,a.y);
    }
};



#endif