#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define MIN_ACCELERATION -700.0f

#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 350.0F

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = false);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
};