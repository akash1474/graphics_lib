#include "graphics.h"


std::ostream& operator<< (std::ostream& out,const Vec2i& v){
    out << "Vec2f(" <<v.x << "," << v.y << ")\n";
    return out;
}

void glx::mouseEventHandler(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) clickLeft=true;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) clickLeft=false;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) clickRight=true;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) clickRight=false;
}

bool glx::mouseClicked(int x){
    return x==0 ? clickLeft : clickRight;
}

void glx::event(GLFWwindow* w){
    glfwGetCursorPos(w, &glx::mx, &glx::my);
    glfwSetMouseButtonCallback(w, glx::mouseEventHandler);
}

Vec2i glx::mousePos(){
    return Vec2i(glx::mx,glx::my);
}

void glx::enableDragging(){
   draggingEnabled=true; 
}


float glx::constrain(float n,float low,float high){
    return std::max(std::min(n, high), low);
}

float glx::map(float n,float start1,float stop1,float start2,float stop2){
    float newval= (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
    if (start2 < stop2) {
        return constrain(newval, start2, stop2);
    } else {
        return constrain(newval, stop2, start2);
    }
}


void glx::enableFill(){
    glx::strokeEnabled=true;
}

void glx::enableStroke(){
    glx::strokeEnabled=false;
}

void glx::reset(){
    if(!draggingEnabled){
        clickLeft=0;
        clickRight=0;
    }
    glx::strokeEnabled=true;
}

void glx::stroke(int r,int g,int b,int a){
    glColor4ub(r,g,b,a);
}

void glx::fill(int r,int g,int b,int a){
    glColor4ub(r,g,b,a);
}

void glx::fill(const Color& c){
    glColor4ub(c.r,c.g,c.b,c.a);
}


// void glx::color(int r,int g,int b,int a){
//     glColor4ub(r,g,b,a);
// }

bool glx::line(int x1,int y1,int x2,int y2){
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
    int dx=x2-x1;
    int dy=y2-y1;
    double num=abs((dy*glx::mx)-(dx*glx::my)+(x2*y1)-(y2*x1));
    double deno=sqrt(pow(dy,2)+pow(dx,2));
    return num/deno < 3;
}

bool glx::line(const Vec2f& p1,const Vec2f& p2){
    return glx::line(p1.x,p1.y,p2.x,p2.y);
}

bool glx::line(const Vec2i& p1,const Vec2i& p2){
    return glx::line(p1.x,p1.y,p2.x,p2.y);
}

void glx::strokeWidth(int x){
    glLineWidth(x);
}


void glx::ellipse(GLfloat cx, GLfloat cy, GLfloat rx,GLfloat ry) {
    int i;
    int amt = 20;
    GLfloat twicePi = 2.0f * 3.141;
    glBegin(glx::strokeEnabled ? GL_LINE_LOOP:GL_POLYGON);
    for (i = 0; i <= amt; i++) {
        glVertex2f(
            cx + ((rx+1)* cos(i * twicePi / amt)),
            cy + ((ry-1)* sin(i * twicePi / amt))
        );
    }
    glEnd();
}

bool glx::circle(float cx, float cy, float r, int num_segments) {
    glBegin(glx::strokeEnabled ? GL_LINE_LOOP : GL_POLYGON);

    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta); 
        glVertex2f(x + cx, y + cy); 
    }
    glEnd();
    return sqrt((glx::mx - cx)*(glx::mx - cx) + (glx::my - cy)*(glx::my - cy)) <= r;
}

void glx::quad(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4){
    glBegin(glx::strokeEnabled ? GL_LINE_LOOP : GL_POLYGON);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glVertex2i(x3,y3);
    glVertex2i(x4,y4);
    glEnd();
}

void glx::quad(Vec2i& p1,Vec2i& p2,Vec2i& p3,Vec2i& p4){
    glx::quad(p1.x,p1.y,p2.x,p2.y,p3.x,p3.y,p4.x,p4.y);
}

void glx::rect(int x1,int y1,int x2,int y2){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    glBegin(glx::strokeEnabled ? GL_LINE_LOOP : GL_POLYGON);
    glVertex2i(x1,y1);
    glVertex2i(x1+dx,y1);
    glVertex2i(x1+dx,y1+dy);
    glVertex2i(x1,y1+dy);
    glEnd();
}

void glx::rect(Vec2i& p1,Vec2i& p2){
   glx::rect(p1.x,p1.y,p2.x,p2.y);
}

void glx::square(int x1,int y1,int s){
    glBegin(glx::strokeEnabled ? GL_LINE_LOOP : GL_POLYGON);
    glVertex2i(x1,y1);
    glVertex2i(x1+s,y1);
    glVertex2i(x1+s,y1+s);
    glVertex2i(x1,y1+s);
    glEnd();
}

void glx::square(Vec2i& p,int x){
    glx::square(p.x,p.y,x);
}


void glx::putpixel(int x1,int y1,const Color& c){
    glColor4ub(c.r,c.b,c.g,c.a);
    glBegin(GL_POINTS);
    glVertex2i(x1,y1);
    glEnd();
    glColor4ub(255,255,255,255);
}


bool glx::point(int x,int y,float strokeWidth){
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
    return sqrt((glx::mx - cx)*(glx::mx - cx) + (glx::my - cy)*(glx::my - cy)) <= (r+2);
}

bool glx::point(Vec2i a,float strokeWidth){
    return glx::point(a.x,a.y,strokeWidth);
}

float glx::lerp(int x,int y,float t){
    return x+(y-x)*t;
}

Vec2i lerp(Vec2i& x,Vec2i& y,float t){
    return Vec2i(x.x + (y.x-x.x)*t,x.y + (y.y-x.y)*t);
}

void glx::beginShape(GLenum a){
    glBegin(a);
}

void glx::endShape(){
    glEnd();        
}

void glx::vertex(int x,int y){
    glVertex2i(x,y);
}

void glx::vertex(Vec2i a){
    glx::vertex(a.x,a.y);
}


double glx::dist(float x1,float y1, float x2,float y2){
    return std::sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}