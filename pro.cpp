#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <random>
//#include <GL/glut.h>
const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=600;

const char *vertexShaderSource ="#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform float scale;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos*scale, 1.0);\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 410 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = ourColor;\n"
    "}\n\0";
unsigned int shaderProgram;
GLuint uniID, ourColorID;
GLfloat escala = 1.0f, aumento = 0.1f;
float greenValue;
int vertexColorLocation;

class Circulo{
    public:    
        double X,Y,A,H;//cordenada X, Coordenada Y, Alto, Ancho.
        float Radio;
        float Red,Blue,Green,Alpha;//Valores de los Colores RGB.
    
        Circulo();
        Circulo(double Size,float _red,float _green, float _blue);
        void change_Color(float c_Red,float c_Green,float c_Blue);
        void change_Size(double cambio,double width,double height,int opcion);
        ~Circulo();
};
class Ventana{
    public:
    float width;
    float height;
    Ventana();
    Ventana(float _width,float _height);
};


Circulo::Circulo(){
    X=0.0;
    Y=0.0;
    A=0.0;
    H=0.0;
    Red=0.0f;
    Green=0.0f;
    Blue=0.0f;
}
Circulo:: Circulo(double Size,float _red,float _green, float _blue){
    A=Size;
    H=Size;
    X=0.0;
    Y=0.0;
    Radio=sqrt(pow(H-X,2)+pow(A-Y,2));
    Red=_red;
    Green=_green;
    Blue=_blue;
}
void Circulo :: change_Color(float c_Red, float c_Green, float c_Blue){

    if(Red+c_Red>=2.0f) Red=2.0f;
    else if(Red+c_Red>=0.0f) Red=0.0f;
    else Red +=c_Red;
    if(Green+c_Green>=2.0f)Green=2.0f;
    else if(Green+c_Green<=0)Green=0.0f;
    else Green += c_Green;
    if(Blue==2.0f&&c_Blue>0)Blue=2.0f;
    else if(Blue==0.0f&&c_Blue<0)Blue=0.0f;
    else Blue+=c_Blue;
    
}
void Circulo :: change_Size(double cambio,double width,double height,int opcion){
    double new_Addwidth = A +(A*cambio);
    double new_Addheight = H + (H*cambio);
    double new_Restwidth = A - (A*cambio);
    double new_Restheight = H - (H*cambio);
    switch(opcion){
        case 1: 
                if(new_Addwidth>=width||new_Addheight>=height){
                A = width;
                H = height;
                }
                else{
                    A=new_Addwidth;
                    H=new_Addwidth;
                }
                break;
        case 2:
            if(new_Restwidth<=0||new_Restwidth<=0) {
                A=0.0f;
                H=0.0f;
            }
            else{
                A=new_Restwidth;
                H=new_Restheight;
            }
            break;
    };
}

Circulo::~Circulo(){}

Ventana::Ventana(){
    width=300.0f;
    height=250.0f;
}
Ventana::Ventana(float _width, float _height){
    width=_width;
    height=_height;
}



void processInput(GLFWwindow *windows, Circulo circulo,Ventana ventana)
{
    
    if(glfwGetKey(windows, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(windows, true);
    if(glfwGetKey(windows, GLFW_KEY_1) == GLFW_PRESS)circulo.change_Color(0.2f,0,0);
    if(glfwGetKey(windows, GLFW_KEY_2) == GLFW_PRESS)circulo.change_Color(0,0.2f,0);
    if(glfwGetKey(windows, GLFW_KEY_3) == GLFW_PRESS)circulo.change_Color(0,0,0.2f);
    if(glfwGetKey(windows, GLFW_KEY_4) == GLFW_PRESS)circulo.change_Color(-0.2f,0,0);
    if(glfwGetKey(windows, GLFW_KEY_5) == GLFW_PRESS)circulo.change_Color(0,-0.2f,0);
    if(glfwGetKey(windows, GLFW_KEY_6) == GLFW_PRESS)circulo.change_Color(0,0,-0.2f);
    if(glfwGetKey(windows, GLFW_KEY_A) == GLFW_PRESS)circulo.change_Size(0.2f,ventana.width,ventana.height,1);
    if(glfwGetKey(windows, GLFW_KEY_B) == GLFW_PRESS)circulo.change_Size(0.2f,ventana.width,ventana.height,2);
}

void framebuffer_size_callback(GLFWwindow* windows, int width, int height)
{   
    glViewport(0, 0,width,height);
}
float RC(){
    std::random_device rd;
    std::uniform_real_distribution<float> random(0.0,2.0);
    return random(rd);   
}
void Paint_Pixel(int x,int y,float red,float green,float blue){
    glPointSize(3);
    glColor3f(red,green,blue);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}
void Pintar_Circulo(Circulo circulo){
    double cirx,ciry;
    cirx= circulo.X;
    while(cirx<circulo.Radio){
        ciry= sqrt(pow(circulo.Radio,2)-pow(cirx,2));

        Paint_Pixel(cirx+circulo.A,ciry+circulo.H,circulo.Red,circulo.Green,circulo.Blue);
        Paint_Pixel(cirx+circulo.A,ciry+circulo.H,circulo.Red,circulo.Green,circulo.Blue);

        Paint_Pixel(-cirx+circulo.A,ciry+circulo.H,circulo.Red,circulo.Green,circulo.Blue);
        Paint_Pixel(-cirx+circulo.A,ciry+circulo.H,circulo.Red,circulo.Green,circulo.Blue);

        Paint_Pixel(cirx+circulo.A,-ciry+circulo.H,circulo.Red,circulo.Green,circulo.Blue);
        Paint_Pixel(cirx+circulo.A,-ciry+circulo.H,circulo.Red,circulo.Green,circulo.Blue);

        Paint_Pixel(-cirx+circulo.A,-ciry+circulo.H,circulo.Red,circulo.Green,circulo.Blue);
        Paint_Pixel(-cirx+circulo.A,-ciry+circulo.H,circulo.Red,circulo.Green,circulo.Blue);
        cirx++;
    }
    
}

int main(){

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Ventana ventana{float(SCR_WIDTH),float(SCR_HEIGHT)};
    Circulo circulo(300.0,RC(),RC(),RC());
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(ventana.width,ventana.height,"LearnOpenGL",NULL,NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window,circulo,ventana);

        // renderizado del circulo
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        Pintar_Circulo(circulo);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
