/* 
* scene.c
*/

#include "scop.h"
#include "config.h"
#include "materials.h" 

void initScene(t_data *data, void *vConfig)
{
    t_vec3 color;
    t_mtx4 temp, temp2;

    t_config *config = (t_config*)vConfig;
    color.z = (float)(config->modelColor & 255) / 255.f;
    color.y = (float)((config->modelColor >> 8) & 255) / 255.f; 
    color.x = (float)((config->modelColor >> 16) & 255) / 255.f;
    initMaterial(&data->model, config->material);
    data->model.obj.color = color;

    data->light.color = vec3(1.f, 1.f, 1.f);
    mtx4axerotation(&temp, LIGHTINITROTATION, vec3(1, -1, 0), 0);
    mtx4scale(&temp2, vec3(LIGHTSCALEINIT, LIGHTSCALEINIT, LIGHTSCALEINIT));
    mtx4dot(&data->light.world, &temp, &temp2);
    mtx4translation(&temp, vec3(config->modelBbox * LIGHTDISTRATE, 0, 0));
    mtx4copy(&temp2, &data->light.world);
    mtx4dot(&data->light.world, &temp2, &temp);

    mtx4(&data->model.obj.world);
    mtx4axerotation(&data->model.constRotation, FIXEDMS * OBJROTATIONRATE, vec3(0, 1.f, 0), 0);
    config->inputSpeed = OBJDISPLACERATE * sqrtf(config->modelBbox);
    data->oldElapsedTime = 0.f;
}

static void handleFrameRate(double *oldElapsedTime)
{
    double ElapsedTime = glfwGetTime();
    double MsBetweenFrames = ElapsedTime - *oldElapsedTime;

    *oldElapsedTime = ElapsedTime;
    if (MsBetweenFrames < FIXEDMS)
        usleep((FIXEDMS - MsBetweenFrames) * SECONDSTOMS);
}

[...]

static void handleObjectRotation(t_mtx4 *objWorld, t_mtx4 *constRotation, unsigned char *rotBlocked)
{
    if (*rotBlocked)
        return;

    t_mtx4 selfCopy;

    mtx4copy(&selfCopy, objWorld);
    mtx4dot(objWorld, &selfCopy, constRotation);
}

[...]

void updateScene(t_mesh *model, t_object *light, double *oldElapsetTime, void *vConfig)
{
    t_config *config = (t_config*)vConfig;

    handleFrameRate(oldElapsetTime);
    handleObjectRotation(&model->obj.world, &model->constRotation, &config->isRotationBlocked);
    handleLightRotations(&light->world, &config->modelBbox);
    handleTextureDepth(config);
}