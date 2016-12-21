#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->audio->PlayMusic("song.ogg",1);

	num_players = 0;

	App->camera->Move(vec3(1.0f, 100.0f, 60.0f));
	App->camera->LookAt(vec3(0, 0, 60));

	CreateCircuit(vec3(200, 0, 0));

	Cube ramp_up(22, 2, 46);
	ramp_up.color = White;
	ramp_up.SetPos(5, 0, 69.5);
	ramp_up.SetRotation(-15, vec3(1, 0, 0));
	App->physics->AddBody(ramp_up, this, false, 0);

	Cube long_ramp(18, 2, 150);
	long_ramp.color = White;
	long_ramp.SetPos(223, 0, 125);
	long_ramp.SetRotation(-15, vec3(1, 0, 0));
	App->physics->AddBody(long_ramp, this, false, 0);

	Cube long_ramp_down(18, 2, 150);
	long_ramp_down.color = White;
	long_ramp_down.SetPos(252, 8, 125);
	long_ramp_down.SetRotation(-8, vec3(1, 0, 0));
	App->physics->AddBody(long_ramp_down, this, false, 0);

	Cube ramp_down(22, 2, 46);
	ramp_down.color = White;
	ramp_down.SetPos(5, 0, 138);
	ramp_down.SetRotation(15, vec3(1, 0, 0));
	App->physics->AddBody(ramp_down, this, false, 0);

	Cube roof(22, 2, 25);
	roof.color = White;
	roof.SetPos(5, 6, 104);
	App->physics->AddBody(roof, this, false, 0);

	Cube roof2(50, 2, 22);
	roof2.color = White;
	roof2.SetPos(237, 19, 209);
	App->physics->AddBody(roof2, this, false, 0);

	// Creating sensor beginning
	Cube b_sensor(15, 2, 1);
	b_sensor.SetPos(5, 1, 30);
	b_sensor.color = Black;
	bs = App->physics->AddBody(b_sensor, App->scene_intro, true, 0);

	// Sensor end
	Cube e_sensor(1, 5, 15);
	e_sensor.SetPos(85, 1, 100);
	es = App->physics->AddBody(e_sensor, App->scene_intro, true, 0);

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
	// Checking if 1 or 2 is pressed and enabling player modules

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		num_players = 1;

		if (App->player2->IsEnabled())
		{
			App->player2->vehicle->SetPos(0, 0, -200);
			App->player2->ResetInfo();
		}

		App->player->Enable();
		App->player->vehicle->SetPos(3, 0, 0);
		App->player->ResetInfo();
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		num_players = 2;

		App->player->Enable();
		App->player->vehicle->SetPos(7, 0, 0);
		App->player->ResetInfo();

		App->player2->Enable();
		App->player2->vehicle->SetPos(1, 0, 0);
		App->player2->ResetInfo();
	}

	// ----------------------------------------------------------

	Plane p(0, 1, 0, 0);
	p.axis = false;
	p.wire = false;
	p.color = Green;
	//p.Render();

	Cube cube(1000, 1000, 1000);
	cube.SetPos(0, 0, 0);
	cube.Scale(1, 0, 1);
	cube.color = Green;
	cube.Render();

	Cube ramp_up(22, 2, 46);
	ramp_up.color = White;
	ramp_up.SetPos(5, 0, 69.5);
	ramp_up.SetRotation(-15, vec3(1, 0, 0));
	ramp_up.Render();

	Cube long_ramp(22, 2, 150);
	long_ramp.color = White;
	long_ramp.SetPos(223, 0, 125);
	long_ramp.SetRotation(-15, vec3(1, 0, 0));
	long_ramp.Render();

	Cube long_ramp_down(18, 2, 150);
	long_ramp_down.color = White;
	long_ramp_down.SetPos(252, 8, 125);
	long_ramp_down.SetRotation(-8, vec3(1, 0, 0));
	long_ramp_down.Render();

	Cube ramp_down(22, 2, 46);
	ramp_down.color = White;
	ramp_down.SetPos(5, 0, 138);
	ramp_down.SetRotation(15, vec3(1, 0, 0));
	ramp_down.Render();

	Cube roof(22, 2, 25);
	roof.color = White;
	roof.SetPos(5, 6, 104);
	roof.Render();

	Cube roof2(50, 2, 22);
	roof2.color = White;
	roof2.SetPos(237, 19, 209);
	roof2.Render();

	// Creating sensor beginning
	Cube b_sensor(20, 1, 0.5);
	b_sensor.SetPos(5, 0.5, 30);
	b_sensor.color = Black;
	b_sensor.Render();

	CreateCircuitColor(vec3(0, 0, 0));

	// Changing window title ---------------------------------------------------------------


	if (num_players == 0)
	{
		char title[80];
		sprintf_s(title, "Please, press '1' for single player or '2' for multiplayer.");
		App->window->SetTitle(title);
	}
	else if (num_players == 1)
	{
		char title[150];
		sprintf_s(title, "Press '1' to restart | Player 1: %.1f Km/h - Time: %.2f s - Best time: %.2f s", App->player->vehicle->GetKmh(), App->player->timer.ReadSec(), App->player->best_time);
		App->window->SetTitle(title);
	}
	else if (num_players == 2 && !App->player->winner && !App->player2->winner)
	{
		char title[150];
		sprintf_s(title, "Press '2' to restart | Player 1: %i laps remaining - Player 2: %i laps remaining", App->player->laps, App->player2->laps);
		App->window->SetTitle(title);
	}
	else if (num_players == 2 && App->player->winner && !App->player2->winner)
	{
		char title[50];
		sprintf_s(title, "Winner: Player 1! | Press '2' to restart");
		App->window->SetTitle(title);
	}
	else
	{
		char title[50];
		sprintf_s(title, "Winner: Player 2! | Press '2' to restart");
		App->window->SetTitle(title);
	}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (num_players == 1 && body1->type == VEHICLE1)
	{
		if (body2 == bs && App->player->add_lap)
		{
			App->player->start_timer = true;
			App->player->add_lap = false;
		}

		if (body2 == es)
			App->player->add_lap = true;
	}

	if (num_players == 2 && body1->type == VEHICLE1)
	{
		if (body2 == bs && App->player->add_lap)
		{
			App->player->laps--;
			App->player->add_lap = false;
		}
		if (body2 == es)
			App->player->add_lap = true;
	}

	if (num_players == 2 && body1->type == VEHICLE2)
	{
		if (body2 == bs && App->player2->add_lap)
		{
			App->player2->laps--;
			App->player2->add_lap = false;
		}
		if (body2 == es)
			App->player2->add_lap = true;
	}
}

void ModuleSceneIntro::CreateLinearCircuit(vec3 pos)
{
	Cube left_limit(3, 8, 70);
	left_limit.SetPos(-pos.x, pos.y, pos.z);

	Cube right_limit(3, 8, 70);
	right_limit.SetPos((-pos + 25).x, pos.y, pos.z);

	App->physics->AddBody(left_limit, this, false, 100000);
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::ColorLinearCircuit(vec3 pos)
{
	Cube left_limit(3, 8, 70);
	left_limit.SetPos(-pos.x, pos.y, pos.z);
	left_limit.Render();

	Cube right_limit(3, 8, 70);
	right_limit.SetPos((-pos + 25).x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Create_Vertical_Small_Wall(vec3 pos)
{
	Cube right_limit(3, 8, 15);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::Create_Vertical_Large_Wall(vec3 pos)
{
	Cube right_limit(3, 8, 70);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::Color_Vertical_Small_Wall(vec3 pos)
{
	Cube right_limit(3, 8, 15);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Color_Vertical_Large_Wall(vec3 pos)
{
	Cube right_limit(3, 8, 70);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Create_Horizontal_Large_Wall(vec3 pos)
{
	Cube right_limit(70, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::Create_Horizontal_Small_Wall(vec3 pos)
{
	Cube right_limit(15, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::Create_Horizontal_Rotate_Wall(vec3 pos)
{
	Cube right_limit(35, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.SetRotation(-30, vec3(0, 1, 0));
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::Create_Small_Horizontal_Rotate_Wall(vec3 pos)
{
	Cube right_limit(17, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.SetRotation(-30, vec3(0, 1, 0));
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::Create_Inverse_Horizontal_Rotate_Wall(vec3 pos)
{
	Cube right_limit(37, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.SetRotation(30, vec3(0, 1, 0));
	App->physics->AddBody(right_limit, this, false, 100000);
}
void ModuleSceneIntro::Color_Small_Horizontal_Rotate_Wall(vec3 pos)
{
	Cube right_limit(17, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.SetRotation(-30, vec3(0, 1, 0));

	right_limit.Render();

}
void ModuleSceneIntro::Color_Small_Inverse_Horizontal_Rotate_Wall(vec3 pos)
{
	Cube right_limit(17, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.SetRotation(30, vec3(0, 1, 0));

	right_limit.Render();

}
void ModuleSceneIntro::Create_Small_Inverse_Horizontal_Rotate_Wall(vec3 pos)
{
	Cube right_limit(17, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.SetRotation(30, vec3(0, 1, 0));
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::Color_Horizontal_Rotate_Wall(vec3 pos)
{
	Cube right_limit(35, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.SetRotation(-30, vec3(0, 1, 0));
	right_limit.Render();
}


void ModuleSceneIntro::Color_Inverse_Horizontal_Rotate_Wall(vec3 pos)
{
	Cube right_limit(35, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.SetRotation(30, vec3(0, 1, 0));
	right_limit.Render();
}

void ModuleSceneIntro::Horizontal_Small_Wall(vec3 pos)
{
	Cube right_limit(22, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	App->physics->AddBody(right_limit, this, false, 100000);
}

void ModuleSceneIntro::Color_Horizontal_Large_Wall(vec3 pos)
{
	Cube right_limit(70, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Color_Horizontal_Small_Wall(vec3 pos)
{
	Cube right_limit(15, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}

void ModuleSceneIntro::Color_HorizontalSmall_Wall(vec3 pos)
{
	Cube right_limit(22, 8, 3);
	right_limit.SetPos(pos.x, pos.y, pos.z);
	right_limit.Render();
}


void ModuleSceneIntro::CreateCircuit(vec3 pos)
{
	Create_Vertical_Small_Wall(vec3(17.5, 0, 12));
	Create_Vertical_Small_Wall(vec3(-7.5, 0, 12));
	Create_Vertical_Small_Wall(vec3(-7.5, 0, -3));
	Create_Vertical_Small_Wall(vec3(-7.5, 0, -18));
	Create_Horizontal_Large_Wall(vec3(26, 0, -26));
	Create_Horizontal_Large_Wall(vec3(51, 0, 3));
	Create_Horizontal_Large_Wall(vec3(121, 0, 3));
	Create_Horizontal_Large_Wall(vec3(191, 0, 3));
	Create_Horizontal_Large_Wall(vec3(96, 0, -26));
	Create_Horizontal_Large_Wall(vec3(166, 0, -26));
	Create_Horizontal_Large_Wall(vec3(236, 0, -26));

	Create_Vertical_Large_Wall(vec3(263, 0, 35));
	Create_Vertical_Small_Wall(vec3(263, 0, -7));

	Create_Vertical_Large_Wall(vec3(240, 0, 37));


	CreateLinearCircuit(vec3(7.5, 0, 54));
	CreateLinearCircuit(vec3(7.5, 0, 150));
	Create_Vertical_Small_Wall(vec3(17.5, 0, 190));
	Create_Vertical_Small_Wall(vec3(17.5, 0, 205));
	Create_Vertical_Small_Wall(vec3(17.5, 0, 220));
	Create_Horizontal_Small_Wall(vec3(-13.5, 0, 185));
	Create_Horizontal_Small_Wall(vec3(-28.5, 0, 185));
	Create_Horizontal_Small_Wall(vec3(-43.5, 0, 185));
	Create_Horizontal_Large_Wall(vec3(-16, 0, 229));
	Create_Vertical_Large_Wall(vec3(-50, 0, 150));
	Horizontal_Small_Wall(vec3(-60.5, 0, 229));

	Create_Vertical_Large_Wall(vec3(-75, 0, 195));
	Create_Vertical_Large_Wall(vec3(-75, 0, 125));


	Create_Horizontal_Small_Wall(vec3(-13.5, 0, 114));
	Create_Horizontal_Small_Wall(vec3(-28.5, 0, 114));
	Create_Horizontal_Small_Wall(vec3(-43.5, 0, 114));

	Create_Horizontal_Large_Wall(vec3(50.5, 0, 112.5));
	Create_Horizontal_Large_Wall(vec3(50.5, 0, 89));

	Create_Horizontal_Small_Wall(vec3(-13.5, 0, 89));
	Create_Horizontal_Small_Wall(vec3(-28.5, 0, 89));
	Create_Horizontal_Small_Wall(vec3(-43.5, 0, 89));
	Create_Horizontal_Small_Wall(vec3(-57.5, 0, 89));
	Create_Horizontal_Small_Wall(vec3(-72.5, 0, 89));

	Create_Horizontal_Rotate_Wall(vec3(101.5, 0, 120));
	Create_Inverse_Horizontal_Rotate_Wall(vec3(102.5, 0, 80));

	Create_Horizontal_Rotate_Wall(vec3(175.5, 0, 80));
	Create_Inverse_Horizontal_Rotate_Wall(vec3(175.5, 0, 120));

	Create_Horizontal_Small_Wall(vec3(124, 0, 129));
	Create_Horizontal_Small_Wall(vec3(139, 0, 129));
	Create_Horizontal_Small_Wall(vec3(154, 0, 129));

	Create_Horizontal_Small_Wall(vec3(127, 0, 73));
	Create_Horizontal_Small_Wall(vec3(141, 0, 73));
	Create_Horizontal_Small_Wall(vec3(154, 0, 73));


	Create_Horizontal_Small_Wall(vec3(124, 0, 111.5));
	Create_Horizontal_Small_Wall(vec3(139, 0, 111.5));

	Create_Horizontal_Small_Wall(vec3(125, 0, 89));
	Create_Horizontal_Small_Wall(vec3(139, 0, 89));


	Create_Small_Horizontal_Rotate_Wall(vec3(107.5, 0, 106.5));
	Create_Small_Inverse_Horizontal_Rotate_Wall(vec3(109.5, 0, 94));

	Create_Small_Horizontal_Rotate_Wall(vec3(155.5, 0, 92));
	Create_Small_Inverse_Horizontal_Rotate_Wall(vec3(155.5, 0, 106.5));


	Create_Horizontal_Small_Wall(vec3(200, 0, 110.5));
	Create_Horizontal_Small_Wall(vec3(200, 0, 88));

	Create_Horizontal_Small_Wall(vec3(215, 0, 88));
	Create_Horizontal_Small_Wall(vec3(230, 0, 88));

	Create_Vertical_Large_Wall(vec3(235, 0, 124));
	Create_Vertical_Small_Wall(vec3(210, 0, 116));
}

void ModuleSceneIntro::CreateCircuitColor(vec3 pos)
{
	Color_Vertical_Small_Wall(vec3(17.5, 0, 12));
	Color_Vertical_Small_Wall(vec3(-7.5, 0, 12));
	Color_Vertical_Small_Wall(vec3(-7.5, 0, -3));
	Color_Vertical_Small_Wall(vec3(-7.5, 0, -18));
	Color_Horizontal_Large_Wall(vec3(26, 0, -26));
	Color_Horizontal_Large_Wall(vec3(51, 0, 3));
	Color_Horizontal_Large_Wall(vec3(121, 0, 3));
	Color_Horizontal_Large_Wall(vec3(191, 0, 3));
	Color_Horizontal_Large_Wall(vec3(206, 0, 3));

	Color_Horizontal_Large_Wall(vec3(96, 0, -26));
	Color_Horizontal_Large_Wall(vec3(166, 0, -26));
	Color_Horizontal_Large_Wall(vec3(229.5, 0, -26));

	Color_Vertical_Large_Wall(vec3(263, 0, 35));
	Color_Vertical_Small_Wall(vec3(263, 0, -7));
	Color_Vertical_Small_Wall(vec3(263, 0, -18));

	Color_Vertical_Large_Wall(vec3(240, 0, 37));

	//start
	ColorLinearCircuit(vec3(7.5, 0, 54));
	ColorLinearCircuit(vec3(7.5, 0, 150));
	Color_Vertical_Small_Wall(vec3(17.5, 0, 120));
	Color_Vertical_Small_Wall(vec3(17.5, 0, 190));
	Color_Vertical_Small_Wall(vec3(17.5, 0, 205));
	Color_Vertical_Small_Wall(vec3(17.5, 0, 220));
	Color_Horizontal_Small_Wall(vec3(-13.5, 0, 185));
	Color_Horizontal_Small_Wall(vec3(-28.5, 0, 185));
	Color_Horizontal_Small_Wall(vec3(-43.5, 0, 185));
	Color_Horizontal_Large_Wall(vec3(-16, 0, 229));

	Color_Horizontal_Large_Wall(vec3(-40, 0, 229));
	Color_Vertical_Large_Wall(vec3(-50, 0, 150));

	Color_HorizontalSmall_Wall(vec3(-63, 0, 229));

	Color_Vertical_Large_Wall(vec3(-75, 0, 195.5));
	Color_Vertical_Large_Wall(vec3(-75, 0, 152.5));
	Color_Vertical_Large_Wall(vec3(-75, 0, 125));


	Color_Horizontal_Small_Wall(vec3(-13.5, 0, 114));
	Color_Horizontal_Small_Wall(vec3(-28.5, 0, 114));
	Color_Horizontal_Small_Wall(vec3(-43.5, 0, 114));

	Color_Horizontal_Large_Wall(vec3(50.5, 0, 111.5));
	Color_Horizontal_Large_Wall(vec3(52.5, 0, 111.5));
	Color_Horizontal_Large_Wall(vec3(50.5, 0, 90));

	Color_Horizontal_Small_Wall(vec3(-13.5, 0, 89));
	Color_Horizontal_Small_Wall(vec3(-28.5, 0, 89));
	Color_Horizontal_Small_Wall(vec3(-43.5, 0, 89));
	Color_Horizontal_Small_Wall(vec3(-57.5, 0, 89));
	Color_Horizontal_Small_Wall(vec3(-69, 0, 89));

	Color_Horizontal_Rotate_Wall(vec3(101.5, 0, 120));
	Color_Inverse_Horizontal_Rotate_Wall(vec3(100.5, 0, 81));


	Color_Horizontal_Small_Wall(vec3(124, 0, 129));
	Color_Horizontal_Small_Wall(vec3(139, 0, 129));
	Color_Horizontal_Small_Wall(vec3(154, 0, 129));

	Color_Horizontal_Small_Wall(vec3(123, 0, 72));
	Color_Horizontal_Small_Wall(vec3(126, 0, 72));
	Color_Horizontal_Small_Wall(vec3(141, 0, 72));
	Color_Horizontal_Small_Wall(vec3(154, 0, 72));

	Color_Horizontal_Small_Wall(vec3(124, 0, 111.5));
	Color_Horizontal_Small_Wall(vec3(122, 0, 111.5));
	Color_Horizontal_Small_Wall(vec3(139, 0, 111.5));
	Color_Horizontal_Small_Wall(vec3(142, 0, 111.5));
	Color_Horizontal_Small_Wall(vec3(125, 0, 89));
	Color_Horizontal_Small_Wall(vec3(124.5, 0, 89));
	Color_Horizontal_Small_Wall(vec3(139, 0, 89));
	Color_Horizontal_Small_Wall(vec3(142, 0, 89));

	Color_Horizontal_Rotate_Wall(vec3(175.5, 0, 80));
	Color_Inverse_Horizontal_Rotate_Wall(vec3(175.5, 0, 120));

	Color_Horizontal_Small_Wall(vec3(198, 0, 110.5));
	Color_Horizontal_Small_Wall(vec3(204, 0, 110.5));
	Color_Horizontal_Small_Wall(vec3(198, 0, 88));

	Color_Horizontal_Small_Wall(vec3(215, 0, 88));
	Color_Horizontal_Small_Wall(vec3(210, 0, 88));
	Color_Horizontal_Small_Wall(vec3(230, 0, 88));

	Color_Vertical_Large_Wall(vec3(235, 0, 124));
	Color_Vertical_Small_Wall(vec3(210, 0, 116));

	Color_Small_Horizontal_Rotate_Wall(vec3(107.5, 0, 106.5));
	Color_Small_Horizontal_Rotate_Wall(vec3(109.5, 0, 106.5));
	Color_Small_Horizontal_Rotate_Wall(vec3(110.5, 0, 107.5));
	Color_Small_Inverse_Horizontal_Rotate_Wall(vec3(109.5, 0, 94));
	Color_Small_Inverse_Horizontal_Rotate_Wall(vec3(111.5, 0, 94));

	Color_Small_Horizontal_Rotate_Wall(vec3(155.5, 0, 92));
	Color_Small_Inverse_Horizontal_Rotate_Wall(vec3(155.5, 0, 106.5));
}