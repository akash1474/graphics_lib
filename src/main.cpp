#include "iostream"
#include "graphics.h"
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




    while (win.isOpen()){
        win.showFps();
        win.clear(30);
        glx::event(win.getglfwWindow());
        draw_grid();

        glx::reset();
        win.swapBuffers();
    }
    win.destroy();
    return 0;
}