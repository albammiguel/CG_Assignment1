#include <iostream>
#include <ogl/glew.h>
#include <ogl/freeglut.h>

#include "Shaders.h"
#include "Model.h"

#define I glm::mat4(1.0)

#define opacity 0.75

void funInit();
void funReshape(int w, int h);
void funDisplay();


void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawSuelo(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAspa(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHelice(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBrazo(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBrazoHelice(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBrazos(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawEsfera(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawEstructuraSuperior(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTronco(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawPlataforma(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawEstucturaInferior(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTiovivo(glm::mat4 P, glm::mat4 V, glm::mat4 M);


// Shaders
Shaders shaders;

// Modelos
Model plane;
Model cylinder;
Model sphere;
Model cone;

// Viewport
int w = 600;
int h = 600;

// Transformaciones
float desYCone = -2.75455951691;
float desYCylinder = -1;
float DesXHelice = 1;
float desZCylinder = -1;
float desYPlataforma = 1;
float desYTronco = 2.1;
float desYEstructuraSuperior = 1.3;
float rotX = 90.0;
float rotY90 = 90.0;
float rotZ90 = 90.0;
float rotY45 = 45.0;
float rotY72 = 72.0;

int main(int argc, char** argv) {

    // Inicializamos GLUT
    glutInit(&argc, argv);
    glutInitContextVersion(3,3);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(w,h);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Practica 1");

    // Inicializamos GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return 0;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    std::cout <<"This system supports OpenGL Version: " << oglVersion << std::endl;

    // Inicializaciones específicas
    funInit();

    // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);

    // Bucle principal
    glutMainLoop();

    return 0;
}

void funInit() {

    // Test de profundidad
    glEnable(GL_DEPTH_TEST);
    glPolygonOffset(1.0,1.0);

    // Shaders
    shaders.initShaders("resources/shaders/vshader.glsl","resources/shaders/fshader.glsl");

    // Modelos
    plane.initModel("resources/models/plane.obj");
    cylinder.initModel("resources/models/cylinder.obj");
    sphere.initModel("resources/models/sphere.obj");
    cone.initModel("resources/models/cone.obj");


}

void funReshape(int wnew, int hnew) {

    // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

    // Actualización de w y h
    w = wnew;
    h = hnew;

}

void funDisplay() {

    // Borramos el buffer de color
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Indicamos los shaders a utilizar
    shaders.useShaders();

    // Matriz P
    float fovy   = 30.0;
    float nplane =  0.1;
    float fplane = 25.0;
    float aspect = (float)w/(float)h;
    glm::mat4 P  = glm::perspective(glm::radians(fovy), aspect, nplane, fplane);

    // Matriz V
    glm::vec3 pos   (4.0, 4.0, 4.0);
    glm::vec3 eye(0.0, 0.0, 0.0);
    glm::vec3 up    (0.0, 1.0,  0.0);
    glm::mat4 V = glm::lookAt(pos, eye, up);

    // Dibujamos la escena
    drawSuelo(P,V,I);
    drawTiovivo(P,V,I);

    //EJERCICIO 4
    //M1 (comentado para que al ejecutar salga solo posición inicial tiovivo)
//    glm::mat4 T = glm::translate(I, glm::vec3(2.0, 0.0, 2.0));
//    glm::mat4 R = glm::rotate(I, glm::radians(18.0f), glm::vec3(0, 1, 0));
//    glm::mat4 M1 = T*R;
//    drawTiovivo(P,V,M1);

    //M2 (comentado para que al ejecutar salga solo posición inicial tiovivo)
//    glm::mat4 T2 = glm::translate(I, glm::vec3(1.0, 0.0, 1.0));
//    glm::mat4 RZ = glm::rotate(I, glm::radians(30.0f), glm::vec3(0, 0, 1));
//    glm::mat4 RX = glm::rotate(I, glm::radians(30.0f), glm::vec3(-1, 0, 0));
//    glm::mat4 RY = glm::rotate(I, glm::radians(40.0f), glm::vec3(0, 1, 0));
//    glm::mat4 M2 = T2*RX*RZ*RY;
//    drawTiovivo(P,V,M2);


    // Intercambiamos los buffers
    glutSwapBuffers();

}

void drawObject(Model model, glm::vec3 color, glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    shaders.setMat4("uPVM",P*V*M);

    glEnable(GL_POLYGON_OFFSET_FILL);
    shaders.setVec3("uColor",color);
    model.renderModel(GL_FILL);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glm::vec3 colorNew = color.operator*=(opacity);
    shaders.setVec3("uColor",colorNew);
    model.renderModel(GL_LINE);

}

void drawSuelo(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(2.0, 1.0, 2.0));
    drawObject(plane,glm::vec3(0.552941 , 0.552941 , 0.552941),P,V,M*S);

}

void drawAspa(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 S = glm::scale(I, glm::vec3(0.037, 0.06,  0.011 ));
    glm::mat4 R = glm::rotate   (I, glm::radians(rotX), glm::vec3(1, 0, 0));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, desYCone, 0.0));
    drawObject(cone,glm::vec3(1.0, 0.0, 0.0),P,V,M*R*S*T);

}

void drawHelice(glm::mat4 P, glm::mat4 V, glm::mat4 M) {

    glm::mat4 RY90 = glm::rotate(I, glm::radians(rotY90), glm::vec3(0, 1, 0));
    drawAspa(P,V,M);
    drawAspa(P,V,M*RY90);
    drawAspa(P,V,M*RY90*RY90);
    drawAspa(P,V,M*RY90*RY90*RY90);

}

void drawBrazo(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(I, glm::vec3(0.05, 0.5,  0.05));
    glm::mat4 R = glm::rotate   (I, glm::radians(rotX), glm::vec3(1, 0, 0));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, desYCylinder, desZCylinder));
    drawObject(cylinder,glm::vec3(0.0, 0.0, 1.0),P,V,M*R*S*T);
}

void drawBrazoHelice(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 RY45 = glm::rotate(I, glm::radians(rotY45), glm::vec3(0, 1, 0));
    glm::mat4 T = glm::translate(I, glm::vec3(DesXHelice, 0.0,0.0));
    drawHelice(P,V,M*T*RY45);
    glm::mat4 RY90 = glm::rotate(I, glm::radians(rotY90), glm::vec3(0, -1, 0));
    glm::mat4 RY902 = glm::rotate(I, glm::radians(rotZ90), glm::vec3(0, 0, 1));
    glm::mat4 T2 = glm::translate(I, glm::vec3(0.0, -0.05,0.0));
    drawBrazo(P,V,M*RY90*RY902*T2);

}

void drawBrazos(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 RY72 = glm::rotate(I, glm::radians(rotY72), glm::vec3(0, 1, 0));
    drawBrazoHelice(P,V,M);
    drawBrazoHelice(P,V,M*RY72);
    drawBrazoHelice(P,V,M*RY72*RY72);
    drawBrazoHelice(P,V,M*RY72*RY72*RY72);
    drawBrazoHelice(P,V,M*RY72*RY72*RY72*RY72);

}

void drawEsfera(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.3, 0.3,  0.3 ));
    drawObject(sphere,glm::vec3(0.0, 1.0, 0.0),P,V,M*S);
}

void drawEstructuraSuperior(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawBrazos(P,V,M);
    drawEsfera(P,V,M);

}

void drawTronco(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.093,0.268,0.093));
    //Lo desplazamos para ponerlo apoyado justo en el suelo.
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, desYTronco,0.0));
    drawObject(cone,glm::vec3(1.0, 0.5, 0.0),P,V,M*S*T);
}

void drawPlataforma(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.6,0.05,0.6));
    //Lo desplazamos para ponerlo apoyado justo en el suelo.
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, desYPlataforma,0.0));
    drawObject(cylinder,glm::vec3(1.0, 1.0, 0.0),P,V,M*S*T);
}

void drawEstucturaInferior(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawTronco(P,V,M);
    drawPlataforma(P,V,M);
}

void drawTiovivo(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    drawEstucturaInferior(P,V,M);
    glm::mat4 T = glm::translate(I, glm::vec3(0.0, desYEstructuraSuperior, 0.0));
    drawEstructuraSuperior(P,V,M*T);
}



