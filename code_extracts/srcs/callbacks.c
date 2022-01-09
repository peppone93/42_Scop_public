/* 
* callbacks.c
*/

#include "scop.h"

/* The first two parameters of glViewport set the location
    third and fourth parameter set the width and height of the window in pixels
*/
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

static void applyPitch(t_camera *camera)
{
    t_mtx4 Rot, yRot;

    mtx4xrotation(&yRot, camera->cursor.pitch, 0); //pitch
    mtx4dot(&Rot, &yRot, &camera->view);
    mtx4copy(&camera->view, &Rot);
}

void mouseCallback(GLFWwindow* window, double x, double y)
{
    static float totalPitch;
    t_camera *camera = (t_camera*)glfwGetWindowUserPointer(window);

    if (!*camera->isFpsMode)
        return ;

    camera->cursor.yaw = (x - camera->cursor.oldX);
    camera->cursor.pitch = (y - camera->cursor.oldY); 
    camera->cursor.oldX = x;
    camera->cursor.oldY = y;

    camera->cursor.yaw *= CAMSENSIVITY;
    camera->cursor.pitch *= CAMSENSIVITY;

    totalPitch += camera->cursor.pitch;
    if (totalPitch > PITCHLIMIT || totalPitch < -PITCHLIMIT)
    {
        totalPitch -= camera->cursor.pitch;
        camera->cursor.pitch = 0;
    }
    applyPitch(camera);
}