/* 
* main.c
*/

#include "scop.h"
#include "parser.h"
#include "materials.h"
#include "config.h"

static void initGlad(t_data *data)
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        secureExit(data, "Failed to initialize GLAD");
}

static void initOpenGL(t_data *data, t_config *config)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    data->window = glfwCreateWindow(config->winWidth, config->winHeight, "Scop", NULL, NULL);
    if (!data->window)
        secureExit(data, "Failed to create GLFW window");

    glfwMakeContextCurrent(data->window);
    glfwSetFramebufferSizeCallback(data->window, framebufferSizeCallback);

    initGlad(data);
}

static void postInitOpenGL(GLFWwindow *glWin)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(glWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // enable mouse and hide the cursor
    glfwSetCursorPosCallback(glWin, mouseCallback);
}

int main(int ac, char** av)
{
    t_data      data;
    t_config    config;

    ft_bzero(&data, sizeof(t_data));
    ft_bzero(&config, sizeof(config));
    handleArguments(ac, av, &config);
    parseConfig(&config);
    parseObjFile(av[1], &data.model.obj.vertexBuffer, &data.model.obj.vertexBufferSize, &config);
    putConfigMessage(&config.defaultConf);
    
    initOpenGL(&data, &config);
    postInitOpenGL(data.window);
    initScene(&data, &config);

    compileShaders(&data, &config);
    setMainTexture(&data, &config);
    setModelData(&data);
    setLightData(&data);

    gameLoop(&data, &config);
    return end(&data);
}