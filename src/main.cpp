#include "iostream"
#include "graphics.h"
#include "matrix.h"
#include "chrono"
#include "thread"


#define WIDTH 480
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

    std::vector<Vec2i> v;
    std::cout << glx::map(40,20,185,0,1) << std::endl;

    while (win.isOpen()){
        win.clear(30);
        glx::event(win.getglfwWindow());
     
        if(glx::mouseClicked(0)) v.push_back(glx::mousePos());
        if(glx::mouseClicked(1)) v.clear();

        for(Vec2i& el: v) glx::point(el,10.f);

        draw_grid();
        // std::this_thread::sleep_for(std::chrono::milliseconds(16));
        glx::reset();
        win.swapBuffers();
    }
    win.destroy();
    return 0;
}