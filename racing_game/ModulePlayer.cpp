#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
	best_time = 10000.0f;
	start_timer = false;
	add_lap = true;
	winner = false;
	laps = 4;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 0.8, 6);
	car.chassis_offset.Set(0, 1.5, 0);
	

	car.winger_size.Set(4, 0.3, 1);
	car.winger_offset.Set(0, 2.5, -2);

	car.stick_size.Set(0.3, 0.7, 0.3);
	car.stick_offset.Set(-1, 2, -2);

	car.stick2_size.Set(0.3, 0.7, 0.3);
	car.stick2_offset.Set(1, 2, -2);

	car.centre_size.Set(3, 2, 2);
	car.centre_offset.Set(0, 2.5, 0);

	car.back_size.Set(3, 0.8, 1.9);
	car.back_offset.Set(0, 2.3, 2);

	car.light1_size.Set(0.3, 0.2, 0.5);
	car.light1_offset.Set(-1, 1.5, -2.8);

	car.light2_size.Set(0.3, 0.2, 0.5);
	car.light2_offset.Set(1, 1.5, -2.8);

	car.mass = 700.0f;
	car.suspensionStiffness = 5.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 100.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;

	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car, App->scene_intro);
	vehicle->type = VEHICLE1;
	vehicle->SetPos(3, 0, 0);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if (!winner && !App->player2->winner)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			if (vehicle->GetKmh()<-3)
				brake = BRAKE_POWER;

			else
				acceleration = MAX_ACCELERATION;

			if (a.ReadSec() > 1.5f) a.Start();
			if (a.ReadSec() == 0.0f)
			{
				a.Start();
				App->audio->PlayFx(App->audio->LoadFx("Game/FX/Accelerate.WAV"), 0);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			if (vehicle->GetKmh()>5)
			{
				brake = BRAKE_POWER;
				if (b.ReadSec() > 1.0f) b.Start();
				if (b.ReadSec() == 0.0f)
				{
					b.Start();
					App->audio->PlayFx(App->audio->LoadFx("Game/FX/Brake.WAV"), 0);
				}
			}
			else
				acceleration = MIN_ACCELERATION;
		}

		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
		{
			vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
			vehicle->body->setAngularVelocity(btVector3(0, 0, 0));

			int x = (int)vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getX();
			int z = (int)vehicle->vehicle->getRigidBody()->getCenterOfMassPosition().getZ();
			vehicle->SetTransform(IdentityMatrix.M);
			vehicle->SetPos(x, 10, z);
		}

		if (!winner)
		{
			vehicle->ApplyEngineForce(acceleration);
			vehicle->Turn(turn);
			vehicle->Brake(brake);
		}

		if (start_timer)
		{
			if (App->player->timer.ReadSec() < App->player->best_time && timer.running)
				App->player->best_time = App->player->timer.ReadSec();

			App->player->timer.Start();
			start_timer = false;
		}

		if (laps == 0)
		{
			winner = true;
			if (played == false)
			{
				App->audio->PlayFx(App->audio->LoadFx("Game/FX/Win.WAV"), 0);
				played = true;
			}
		}

	}

	vehicle->Render(Red);
	return UPDATE_CONTINUE;
}

void ModulePlayer::ResetInfo()
{
	timer.Reset();
	best_time = 10000.0f;
	start_timer = false;
	add_lap = true;
	winner = false;
	played = false;
	laps = 4;
	vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
	vehicle->body->setAngularVelocity(btVector3(0, 0, 0));
	vehicle->SetTransform(IdentityMatrix.M);
}



