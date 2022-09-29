#include "glm/fwd.hpp"
#include "iostream"
#include "graphics.h"
#include "matrix.h"
#include "chrono"
#include "thread"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

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
    float angle=0.0;

    Matrix cube(4,8,{
        {50,50,-50,-50,50,50,-50,-50},
        {50,-50,50,-50,50,-50,50,-50},
        {50,50,50,50,-50,-50,-50,-50},
        {  1, 1, 1, 1, 1,  1,  1,  1}
    });

    double dis= 0.8;
    Matrix proj(4,4,{
        {dis,0,0,0},
        {0,dis,0,0},
        {0,0,dis,0},
        {0,0,0  ,1},
    });
    

    while (win.isOpen()){
        win.clear(30);
        glx::event(win.getglfwWindow());
      
        Matrix rotate=Matrix::rotate(cube,angle,{1.0f,1.0f,1.0f});
        Matrix scale=Matrix::scale(rotate,{1.5f,1.5f,1.5f});
        Matrix translate=Matrix::translate(scale,{50.0f,50.0f,1.0f});
        Matrix projected=Matrix::dot(proj,translate); //2x8
        projected+200;
        for(int i=0;i<projected.cols;i++){
            glx::point(projected.data[0][i],projected.data[1][i]);
        }

        for(int i=0;i<7;i++){
            if(i%2==0) glx::line(projected.data[0][i],projected.data[1][i],projected.data[0][i+1],projected.data[1][i+1]);
            if(i < 4) glx::line(projected.data[0][i],projected.data[1][i],projected.data[0][i+4],projected.data[1][i+4]);
            if(i==0 ||i==1 || i==4 || i==5) glx::line(projected.data[0][i],projected.data[1][i],projected.data[0][i+2],projected.data[1][i+2]);
        }


        angle+=0.05;
        draw_grid();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        glx::reset();
        win.swapBuffers();
    }
    win.destroy();
    return 0;
}