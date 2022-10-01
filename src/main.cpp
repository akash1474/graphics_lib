#include "iostream"
#include "graphics.h"
#include "string"
#include "matrix.h"


#define WIDTH 620
#define HEIGHT 480

bool isClicked=false;
int grid_size=10;


void draw_grid(){
    int c=WIDTH/grid_size;
    glx::fill(40);
    for(int i=0;i<c;i++){
        glx::line(i*grid_size,0,i*grid_size,HEIGHT);
    }
    for(int j=0;j<c;j++){
       glx::line(0,j*grid_size,WIDTH,j*grid_size) ;
    }
    glx::fill(255);
}


int main(void){
    Window win(WIDTH,HEIGHT,"Test");
    Vec2i p1(10,100);
    Vec2i p2(WIDTH,100);
    Vec2i p3(150,20);
    Window::frameRate(120);

    std::vector<Vec2i> v;

    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    unsigned int counter = 0;

    glx::enableDragging();
    while (win.isOpen()){
        crntTime = glfwGetTime();
        timeDiff = crntTime - prevTime;
        counter++;

        if (timeDiff >= 1.0 / 30.0)
        {
            std::string FPS = std::to_string((1.0 / timeDiff) * counter);
            std::string ms = std::to_string((timeDiff / counter) * 1000);
            std::string newTitle = "Graphics Lib - " + FPS + "FPS / " + ms + "ms " + std::to_string(v.size());
            glfwSetWindowTitle(win.getglfwWindow(), newTitle.c_str());

            prevTime = crntTime;
            counter = 0;
        }
        win.clear(30);
        glx::event(win.getglfwWindow());
        draw_grid();
     
        Vec2i mPos=glx::mousePos();
        if(glx::mouseClicked(0)) v.push_back(mPos);
        if(glx::mouseClicked(1)) v.clear();

        glx::fill(100);
        int offset=10;
        glx::line(0,mPos.y,mPos.x-offset,mPos.y);
        glx::line(mPos.x+offset,mPos.y,WIDTH,mPos.y);
        glx::line(mPos.x,0,mPos.x,mPos.y-offset);
        glx::line(mPos.x,mPos.y+offset,mPos.x,HEIGHT);
        // glx::circle(mPos.x,mPos.y,10);
        glx::color(0,200,255);
        glx::quad(mPos.x-offset,mPos.y,mPos.x,mPos.y-offset,mPos.x+offset,mPos.y,mPos.x,mPos.y+offset);
        glx::fill(255);

        for(Vec2i el: v) {
            if(glx::point(el)){
                glx::color(255,0,149);
                glx::point(el);
                glx::circle(el.x,el.y,5);
                glx::fill(255);
            }
            glx::fill(100);
            glx::line(mPos.x,mPos.y,el.x,el.y);
            glx::fill(255);
        }
        glx::color(0,190,200);
        glx::beginShape();
        for(int i=0;i< v.size();i++){
            glx::vertex(v[i].x,v[i].y);
        }
        glx::endShape();

        glx::reset();
        win.swapBuffers();
    }
    win.destroy();
    return 0;
}