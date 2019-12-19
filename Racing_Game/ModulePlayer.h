#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 4000.0f
#define TURN_DEGREES 30.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	PhysVehicle3D* trailer;
	float turn;
	float acceleration;
	float brake;

public:
	bool sensor = false;
	int numLap = 0;
};