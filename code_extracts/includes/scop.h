/* 
* scop.h
*/

#ifndef SCOP_H
#define SCOP_H

#include "glad.h"
#include "glfw3.h"
#include "libft.h"
#include "vec.h"
#include "bmp.h"
#include "mtx.h"
#include "materials.h"

#define FALSE	0
#define TRUE	1
#define CAMSENSIVITY 0.05f

#define OBJROTATIONRATE 18.f
#define OBJDISPLACERATE 0.1f

#define LIGHTSCALEINIT 0.15f
#define LIGHTDISTRATE 6.66f
#define LIGHTINITROTATION 15.f
#define LIGHTROTATIONRATE 0.5f

#define PITCHLIMIT 87.f

#define SECONDSTOMS 1e6
#define FIXEDMS15	0.06666666 // 15FPS
#define FIXEDMS30	0.03333333 // 30FPS
#define FIXEDMS60	0.01666666 // 60FPS
#define FIXEDMS FIXEDMS60 // Frame rate = 60fps

#define ONETIMEKEYS 5

typedef struct		s_object
{
	unsigned int	shaderProgramID;
	unsigned int	vboID;
	unsigned int	vaoID;
	float			*vertexBuffer;
	unsigned int	vertexBufferSize;
	unsigned int	*indicesBuffer;

	unsigned int	U_posID;
	t_vec3			pos;
	unsigned int	U_colorID;
	t_vec3			color;

	unsigned int	U_transformID;
	t_mtx4			transform;
	unsigned int	U_worldID;
	t_mtx4 			world;
}					t_object;

typedef struct		s_material
{
	unsigned int	U_ambientID;
	t_vec3			ambient;
	unsigned int	U_diffuseID;
	t_vec3			diffuse;
	unsigned int	U_specularID;	
	t_vec3			specular;
	unsigned int	U_shiniessID;
	float			shininess;
}					t_material;

typedef struct		s_mesh
{
	t_object		obj;
	t_material		material;
	t_mtx4			constRotation;

	unsigned int	U_lightColorID;
	unsigned int	U_worldNormalID;
	t_mtx3 			worldNormal;

	unsigned int	T_textureID;
}					t_mesh;

typedef struct		s_shader
{
	unsigned int	vertexShaderID;		
	unsigned int	fragmentShaderID;
	char			*vertexShaderData;
	char			*fragmentShaderData;
}					t_shader;

typedef struct		s_cursor
{
    float 			oldX;
	float			oldY;
	float			yaw;
	float			pitch;
}					t_cursor;

typedef struct		s_camera
{
	unsigned int	U_dirID;
	t_vec3			dir;
	t_mtx4			view;
	t_mtx4			projection;
    t_mtx4			combined;
	t_cursor		cursor;
	unsigned char	*isFpsMode;
}					t_camera;

typedef struct		s_data
{
	GLFWwindow      *window;
	t_object		light;
	t_mesh			model;
	t_shader		shader;
	t_camera		camera;
	double			oldElapsedTime;	
}					t_data;

void scopExit(char *str);
void secureExit(t_data *data, char *str);
void *scopMemAlloc(t_data *data, size_t size);
int	 end(t_data *data);

void setMainTexture(t_data *data, void *config);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double x, double y);

void compileShaders(t_data *data, void *config);
void handleShadersUniforms(t_data *data, void *config);
void assignMaterialUniforms(t_mesh *model);
void updateModelUniforms(t_camera *cam, t_mesh *model, t_object *light, void *vConfig);

void setMaterial(t_mesh *model, i_materialIDX materialIDX);
void setLightData(t_data *data);
void setModelData(t_data *data);

void processInputs(t_data *data, GLFWwindow *glWin, void* vConfig, char *keystatus);
void gameLoop(t_data *data, void* vConfig);

void initScene(t_data *data, void *vConfig);
void initCamera(GLFWwindow *glWin, t_camera *camera, void *vConfig);
void initMaterial(t_mesh *model, i_materialIDX materialIDX);

void updateLightUniforms(t_object *light);
void updateScene(t_mesh *model, t_object *light, double *oldElapsetTime, void *vConfig);
void processCamera(t_camera *cam, t_mtx4 *modelM, t_mtx4 *lightM, void *vConfig);

#endif