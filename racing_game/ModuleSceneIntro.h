#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateLinearCircuit(vec3 pos);
	void ColorLinearCircuit(vec3 pos);

	void Create_Vertical_Small_Wall(vec3 pos);
	void Create_Vertical_Large_Wall(vec3 pos);

	void Color_Vertical_Small_Wall(vec3 pos);
	void Color_Vertical_Large_Wall(vec3 pos);

	void Create_Horizontal_Large_Wall(vec3 pos);
	void Create_Horizontal_Small_Wall(vec3 pos);
	void Create_Horizontal_Rotate_Wall(vec3 pos);
	void Create_Inverse_Horizontal_Rotate_Wall(vec3 pos);
	void Create_Small_Horizontal_Rotate_Wall(vec3 pos);
	void Create_Small_Inverse_Horizontal_Rotate_Wall(vec3 pos);
	void Horizontal_Small_Wall(vec3 pos);

	void Color_Horizontal_Large_Wall(vec3 pos);
	void Color_Horizontal_Small_Wall(vec3 pos);
	void Color_HorizontalSmall_Wall(vec3 pos);
	void Color_Horizontal_Rotate_Wall(vec3 pos);
	void Color_Inverse_Horizontal_Rotate_Wall(vec3 pos);

	void CreateCircuit(vec3 pos);
	void CreateCircuitColor(vec3 pos);


public:

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	int num_players;

	PhysBody3D* bs;
	PhysBody3D* es;
};
