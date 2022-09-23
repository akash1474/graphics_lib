#include "iostream"
#include "graphics.h"

int main(void)
{
    Window win(480,480,"Test");
    while (win.isOpen()){
        win.clear();


        line(10,10,150,120);



        win.swapBuffers();
    }
    win.destroy();
    return 0;
}