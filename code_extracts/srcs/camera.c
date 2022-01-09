/* 
* camera.c
*/

#include "scop.h"
#include "config.h"

void initCamera(GLFWwindow *glWin, t_camera *camera, void *vConfig)
{
    t_config *config = (t_config*)vConfig;
    float ratio = (float)config->winWidth / (float)config->winHeight;

    camera->isFpsMode = &config->isFpsMode;
    camera->cursor.oldX = config->winWidth / 2.f;
    camera->cursor.oldY = config->winHeight / 2.f;
    camera->cursor.pitch = 0;
    camera->cursor.yaw = 0;
    mtx4translation(&camera->view, vec3(0, 0, -config->modelBbox * 2.f));
    mtx4perspective(&camera->projection, 60.f, ratio, 0.01f, 500.f);

    glfwSetWindowUserPointer(glWin, camera);
}

static void applyYaw(t_camera *camera, t_mtx4 *obj, t_mtx4 *lht, unsigned char isFpsMode)
{
    if (!isFpsMode)
        return ;

    t_mtx4 selfCopy, translation, rotation;

    mtx4translation(&translation, vec3(camera->view.m[3][0], camera->view.m[3][1], camera->view.m[3][2]));
    mtx4yrotation(&rotation, camera->cursor.yaw, 0);
    camera->cursor.yaw = 0;

    mtx4copy(&selfCopy, obj);
    mtx4dot(obj, &translation, &selfCopy);
    mtx4copy(&selfCopy, obj);
    mtx4dot(obj, &rotation, &selfCopy);

    mtx4copy(&selfCopy, lht);
    mtx4dot(lht, &translation, &selfCopy);
    mtx4copy(&selfCopy, lht);
    mtx4dot(lht, &rotation, &selfCopy);

    mtx4translation(&translation, vec3(-camera->view.m[3][0], -camera->view.m[3][1], -camera->view.m[3][2]));

    mtx4copy(&selfCopy, obj);
    mtx4dot(obj, &translation, &selfCopy);

    mtx4copy(&selfCopy, lht);
    mtx4dot(lht, &translation, &selfCopy);
}

void processCamera(t_camera *cam, t_mtx4 *modelM, t_mtx4 *lightM, void *vConfig)
{
    t_config *config = (t_config*)vConfig;

    applyYaw(cam, modelM, lightM, config->isFpsMode);
    mtx4dot(&cam->combined, &cam->projection, &cam->view);
}