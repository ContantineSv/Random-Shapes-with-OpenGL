#include "GLFW/glfw3.h"
#include "shapes.h"
#include <iostream>
#include <vector>
#include<random>
#include <math.h>
#include <memory>

using namespace std;


int WINDOW_WIDTH = 1200;
int WINDOW_HEIGHT = 800;

int STEP = 10;

unique_ptr<Shape> RandomShape()
{   
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> type_dis(0,2);

    uniform_real_distribution<>x_dis(- float(WINDOW_WIDTH) / float(STEP),
                                                float(WINDOW_WIDTH) / float(STEP));
    uniform_real_distribution<>y_dis(- float(WINDOW_HEIGHT) / float(STEP),
                                                float(WINDOW_HEIGHT) / float(STEP));
    uniform_real_distribution<>r_dis(-float(min(WINDOW_HEIGHT, WINDOW_WIDTH)) / float(STEP) / 2.0,
                                                float(min(WINDOW_HEIGHT, WINDOW_WIDTH)) / float(STEP) / 2.0);                                     

    Type type = static_cast<Type> (type_dis(gen));
    
    unique_ptr<Shape> shape = nullptr;

    switch (type){
        case (Type::triangle):
            shape = make_unique<Triangle>(Point(x_dis(gen), y_dis(gen)),
                                Point(x_dis(gen), y_dis(gen)),
                                Point(x_dis(gen), y_dis(gen)));
            break;
        case (Type::rectangle):
            shape = make_unique<Rectangle>(Point(x_dis(gen), y_dis(gen)),
                                Point(x_dis(gen), y_dis(gen)));
            break;
        case (Type::circle):
            shape = make_unique<Circle>(Point(x_dis(gen), y_dis(gen)),
                                r_dis(gen));
    }
    return shape;
}

vector<unique_ptr<Shape>> GetShapes(int n)
{
    vector<unique_ptr<Shape>> shapes;
    for (int i = 0; i < n; ++i)
    {
        shapes.push_back(RandomShape());
    }
    return shapes;
}



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shapes", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    vector<unique_ptr<Shape>> shapes = GetShapes(10);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);
        for (const auto& shape: shapes)
        {
            if (shape != nullptr)
            {
                shape->Draw(WINDOW_WIDTH, WINDOW_HEIGHT, STEP);
            }
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}