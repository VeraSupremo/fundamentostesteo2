//#include "glad/glad.h"
#include <GLFW/glfw3.h> // Para la ventana y el manejo de eventos (GLFW)
#include <cmath>
#include <iostream>
#include <math.h>
#include <random>

float circleRadius = 50.0f; // Radio base
float RC(){// Random Color
    std::random_device rd;
    std::uniform_real_distribution<float> random(0.0,1.0);
    return random(rd);   
}

class Color{
    public:
    float RED;
    float GREEN;
    float BLUE;
    Color(){
        RED=1.0;
        GREEN=1.0;
        BLUE=1.0;
    }
    Color(float r,float g,float b){
        RED = r;
        GREEN = g;
        BLUE = b;
    }
};
Color color(RC(),RC(),RC());
class Dibujo {
public:
    static void drawCircle(float radius) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); // punto centro del circulo
        glColor3f(color.RED,color.GREEN,color.BLUE);
        for (int i = 0; i <= 360; i++) {
            float angle = 3.14159f * i / 180.0f; //Convierte a radianes
            glVertex2f(radius * cos(angle), radius * sin(angle));
        }
        glEnd();
    }
};

class Pantalla {
public:
    static void display(GLFWwindow* window) {
        glClear(GL_COLOR_BUFFER_BIT); // Limpia la pantalla
        int width, height;
        
        glfwGetFramebufferSize(window, &width, &height); // Obtiene el tamaño del frame
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION); // Selecciona la matriz
        glLoadIdentity(); // Reinicia la matriz
        glOrtho(0.0, width, 0.0, height, -1.0, 1.0); // Establece la proyección
        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); // Reinicia la matriz 
        glTranslatef(width / 2, height / 2, 0.0f); // Mueve al centro del circulo
        Dibujo::drawCircle(circleRadius); //dibuja
        glfwSwapBuffers(window); 
    }
};


void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_A:
                circleRadius += 10.0f; // aumenta el radio
                break;
            case GLFW_KEY_B:
                circleRadius -= 10.0f; // Disminuye el radio
                if (circleRadius < 0.0f) //no permite radio negativo
                    circleRadius = 0.0f;
                break;
            case GLFW_KEY_1:
                color.RED += 0.2;
                if(color.RED>=1.0) color.RED=1.0;
                break;
            case GLFW_KEY_4:
                color.RED -=0.2;
                if(color.RED<=0.0) color.RED=0.0;
                break;
        }
    }
}

int main() {
    
    // Inicializa GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Crea una ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "Círculo en OpenGL con GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
                                              //ventana como actual
    glfwMakeContextCurrent(window);
                                             // Configura el callback de teclado
    glfwSetKeyCallback(window, keyboard);

    while (!glfwWindowShouldClose(window)) {
        // Renderiza la pantalla
        Pantalla::display(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
