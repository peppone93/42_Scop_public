/* 
* gameloop.c
*/

#include "scop.h"
#include "config.h"
#include "materials.h"

[...]

static void processLight(t_camera *cam, t_object *light, t_config *config)
{
    if (!config->isLightOn || config->textureDepth >= 0.999f)
        return ;

    glUseProgram(light->shaderProgramID);
    glBindVertexArray(light->vaoID);

    mtx4dot(&light->transform, &cam->combined, &light->world);
    updateLightUniforms(light);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindVertexArray(0);
}

[...]

void gameLoop(t_data *data, void* vConfig)
{
    t_config *config = (t_config*)vConfig;
    char keyStatus[ONETIMEKEYS];

    initGameLoop(data, vConfig, keyStatus);
    while(!glfwWindowShouldClose(data->window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInputs(data, data->window, vConfig, keyStatus);
        updateScene(&data->model, &data->light, &data->oldElapsedTime, vConfig);
        processCamera(&data->camera, &data->model.obj.world, &data->light.world, vConfig);
        processModel(&data->camera, &data->model, &data->light, config);
        processLight(&data->camera, &data->light, config);
        glfwSwapBuffers(data->window);
    }
}