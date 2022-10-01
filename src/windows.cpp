#include "graphics.h"


void Window::framebuffer_size_callback(GLFWwindow* win, int w, int h)
{
    glViewport(0, 0, w, h);
}

void Window::init(){
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
    // glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    if (glewInit() != GLEW_OK) throw Graphics::glew_init_failed();
    glGetString(GL_VERSION);
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LINE_SMOOTH);
    glViewport(0, 0, this->width, this->height);
    glOrtho(0, this->width, this->height, 0, 0,1);
    win=window;
}



void Window::setSize(Vec2i& v){
    this->width=v.x;
    this->height=v.y;
}

GLFWwindow* Window::getglfwWindow(){
    return this->win;
}

Window::Window(int _w,int _h,const char* _t){
    if(_w <=0 || _h <= 0) throw Graphics::invalid_window_dimensions();
    if(strlen(_t)==0) throw Graphics::invalid_argument();
    this->width=_w;
    this->height=_h;
    this->title=_t;
    this->init();
}

bool Window::isOpen(){
    return !glfwWindowShouldClose(this->win);
}

void Window::swapBuffers(){
    glfwSwapBuffers(this->win);
    glfwPollEvents();
}


int Window::frameRates=0;
void Window::frameRate(int x){
    Window::frameRates=1000/x;
}

void Window::clear(){
    if(frameRates>0) std::this_thread::sleep_for(std::chrono::milliseconds(frameRates));
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::clear(int x){
    if(frameRates>0) std::this_thread::sleep_for(std::chrono::milliseconds(frameRates));
    glClearColor((float)x/255.0f,(float)x/255.0f,(float)x/255.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::clear(float r,float g,float b, float a){
    if(frameRates>0) std::this_thread::sleep_for(std::chrono::milliseconds(frameRates));
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::destroy(){
    glfwDestroyWindow(this->win);
    glfwTerminate();
}
