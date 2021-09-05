#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    {

        float positions[] = {
            -0.5f, -0.5f,   // 0
             0.5f, -0.5f,   // 1
             0.5f,  0.5f,   // 2
            -0.5f,  0.5f,   // 3

        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        
        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUnform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Undind();

        Renderer renderer;
   
        float r = 0.0f, g = 0.0f, b = 0.0f;
        float r_inc = 0.05f;
        float g_inc = 0.05f;
        float b_inc = 0.05f;



        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            shader.Bind();
            shader.SetUnform4f("u_Color", r, g, b, 1.0f);
            
            renderer.Draw(va, ib, shader);
            
            if (r > 1.0f)
                r_inc = -0.05f;
            else if (r < 0.0f)
                r_inc = 0.05f;

            if (g > 1.0f)
                g_inc = -0.05f / 3;
            else if (g < 0.0f)
                g_inc = 0.05f / 2;
            if (b > 1.0f)
                b_inc = -0.05f / 2;
            else if (b < 0.0f)
                b_inc = 0.05f / 3;

            r += r_inc;
            g += g_inc;
            b += b_inc;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}