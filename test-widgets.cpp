
#include <iostream>
#include <cmath>

#include <vector>


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "node.h"
#include "camera.h"

#include "shader.h"
#include "buffer.h"
#include "texture.h"

#include "font.h"

#include "render.h"

#include "resource_manager.h"

#include "ui.h"

#include "popup_menu.h"


// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 768;


// void error ( int error, const char * description )
// {
//     fputs ( description, stderr );
// }

void key_callback ( GLFWwindow * window, int key, int scancode, int action, int mods )
{
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose ( window, GL_TRUE );
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // std::cout << "xpos " << xpos << "ypos " << ypos << std::endl;
        
        ui::Event e;

        e._name = "mouse_button_right_down";
        e.x = xpos;
        e.y = HEIGHT - ypos;       

        ui::instance()->mouse_click_event_up(&e);

    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // std::cout << "xpos " << xpos << "ypos " << ypos << std::endl;

        ui::Event e;

        e._name = "mouse_button_right_up";
        e.x = xpos;
        e.y = HEIGHT - ypos;       

        ui::instance()->mouse_click_event_up(&e);


    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
        // std::cout << "xpos " << xpos << "ypos " << ypos << std::endl;
        
        ui::Event e;

        e._name = "mouse_move";
        e.x = xpos;
        e.y = HEIGHT - ypos;       

        ui::instance()->mouse_move_event_up(&e);

}


int main()
{

    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "widgets", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    Render* render = new Render();
    render->load_resources_all();

    ui::PopupMenu menu;

    menu.add_line("ПУНКТ1\n");
    menu.add_line("ПУНКТ2\n");
    menu.add_line("ПУНКТ3\n");

    menu.set_rect(200.0, 250, 200, 200);

    ui::instance()->add_widget(&menu);

    ui::instance()->set_window(WIDTH, HEIGHT);

    while ( glfwWindowShouldClose ( window ) != true)
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


        ui::instance()->draw(render);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    delete render;

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
