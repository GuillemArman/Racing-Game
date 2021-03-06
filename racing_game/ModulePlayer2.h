#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define MIN_ACCELERATION -700.0f

#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 350.0F

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2(Application* app, bool start_enabled = false);
	virtual ~ModulePlayer2();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void ResetInfo();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	int laps;
	bool add_lap;
	bool winner;

	// For FX
	Timer a;
	Timer b;
	bool played;
};
