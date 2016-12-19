#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 100.0f, 60.0f));
	App->camera->LookAt(vec3(0, 0, 60));

	CreateCircuit(vec3(200, 0, 0));
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = false;
	p.wire = false;
	p.color = Red;
	p.Render();

	Cube cube(1000, 1000, 1000);
	cube.SetPos(0, 0, 0);
	cube.Scale(1, 0, 1);
	cube.color = Red;
	cube.Render();

	CreateCircuitColor(vec3(0, 0, 0));

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{}


void ModuleSceneIntro::CreateLinearCircuit(vec3 pos)
{
	Cube left_limit(3, 3, 70);
	left_limit.SetPos(-pos.x, pos.y, pos.z);
	
	Cube right_limit(3, 3, 70);
	right_limit.SetPos((-pos+15).x, pos.y, pos.z);

	App->physics->AddBody(left_limit, 100000);
	App->physics->AddBody(right_limit, 100000);

}

void ModuleSceneIntro::ColorLinearCircuit(vec3 pos)
{
	Cube left_limit(3, 5, 70);
	left_limit.SetPos(-pos.x, pos.y, pos.z);
	left_limit.Render();

	Cube right_limit(3, 5, 70);
	right_limit.SetPos((-pos + 15).x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Create_Vertical_Small_Wall(vec3 pos)
{
	Cube right_limit(3, 5, 15);
	right_limit.SetPos(pos.x, pos.y, pos.z);

	App->physics->AddBody(right_limit, 100000);
}

void ModuleSceneIntro::Create_Vertical_Large_Wall(vec3 pos)
{
	Cube right_limit(3, 5, 70);
	right_limit.SetPos(pos.x, pos.y, pos.z);

	App->physics->AddBody(right_limit, 100000);
}

void ModuleSceneIntro::Color_Vertical_Small_Wall(vec3 pos)
{
	Cube right_limit(3, 5, 15);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Color_Vertical_Large_Wall(vec3 pos)
{
	Cube right_limit(3, 5, 70);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Create_Horizontal_Large_Wall(vec3 pos)
{
	Cube right_limit(70, 5, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);

	App->physics->AddBody(right_limit, 100000);
}

void ModuleSceneIntro::Create_Horizontal_Small_Wall(vec3 pos)
{
	Cube right_limit(15, 5, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);

	App->physics->AddBody(right_limit, 100000);
}

void ModuleSceneIntro::Color_Horizontal_Large_Wall(vec3 pos)
{
	Cube right_limit(70, 5, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Color_Horizontal_Small_Wall(vec3 pos)
{
	Cube right_limit(15, 5, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::CreateCircuit(vec3 pos)
{
	CreateLinearCircuit(vec3(7.5, 0, 30));
	Create_Vertical_Small_Wall(vec3(-7.5, 0, 73));
	Create_Horizontal_Large_Wall(vec3(41, 0, 67));
	Create_Horizontal_Large_Wall(vec3(26, 0, 82));
	Create_Vertical_Small_Wall(vec3(77, 0, 73));
	CreateLinearCircuit(vec3(-62, 0, 116));
	Create_Vertical_Small_Wall(vec3(62, 0, 158));
	Create_Horizontal_Large_Wall(vec3(96, 0,168));
	Create_Horizontal_Small_Wall(vec3(86, 0, 149));
	Create_Horizontal_Small_Wall(vec3(100, 0, 149));
}

void ModuleSceneIntro::CreateCircuitColor(vec3 pos)
{
	ColorLinearCircuit(vec3(7.5f, 0, 31));
	Color_Vertical_Small_Wall(vec3(-7.5, 0, 73));
	Color_Horizontal_Large_Wall(vec3(41, 0, 67));
	Color_Horizontal_Large_Wall(vec3(26, 0, 82));
	Color_Vertical_Small_Wall(vec3(77, 0, 73));
	ColorLinearCircuit(vec3(-62, 0, 115));
	Color_Vertical_Small_Wall(vec3(62, 0, 158));
	Color_Horizontal_Large_Wall(vec3(96, 0, 168));
	Color_Horizontal_Small_Wall(vec3(86, 0, 149));
	Color_Horizontal_Small_Wall(vec3(100, 0, 149));
}