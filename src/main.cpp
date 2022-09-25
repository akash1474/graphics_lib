#include "iostream"
#include "graphics.h"

#define WIDTH 480
#define HEIGHT 480

bool isClicked=false;
int grid_size=10;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) isClicked=true;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) isClicked=false;
}

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
    float delta=0.01;
    bool done=false;
    int j=1;
    bool isHovered=false;
    glfwSetMouseButtonCallback(win.getglfwWindow(), mouse_button_callback);
    while (win.isOpen()){
        win.clear(30);
        glx::event(win.getglfwWindow());
        p3=glx::mousePos();
        if(!done && isClicked){
            isClicked=false;
            switch(j){
                case 1:
                   p1.x=p3.x; 
                   p1.y=p3.y;
                   j++;
                   break;
                case 2:
                   p2.x=p3.x; 
                   p2.y=p3.y;
                   j++;
                   break;
                case 3:
                   p3.x=p3.x; 
                   p3.y=p3.y;
                   done=true;
                   break;
            }
        }
        glx::quad(10,10,100,10,50,200,120,252);
        glx::rect(10,10,100,120);
        
        glx::square(150,150,100);
        if(done){
            glx::beginShape();
            for(float t=0;t<=1.0f;t+=delta){
                int x1=glx::lerp(p1.x,p3.x,t);
                int y1=glx::lerp(p1.y,p3.y,t);
                int x2=glx::lerp(p3.x,p2.x,t);
                int y2=glx::lerp(p3.y,p2.y,t);
                int x=glx::lerp(x1,x2,t);
                int y=glx::lerp(y1,y2,t);
                glx::vertex(x,y);
                // glx::line(x1,y1,x2,y2);
            }
            glx::endShape();
        }
        draw_grid();

        win.swapBuffers();
    }
    win.destroy();
    return 0;
}