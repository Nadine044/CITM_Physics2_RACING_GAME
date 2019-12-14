#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModuleCircuit.h"
#include "Color.h"

ModuleCircuit::ModuleCircuit(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleCircuit::~ModuleCircuit()
{}

bool ModuleCircuit::Start()
{
	bool ret = false;

	LOG("Loading Circuit");

	wall.SetPos(10, 1.5f, 2);
	wall.size = {5, 3, 5};
	wall.color = Red;
	physWall = App->physics->AddBody(wall, WALL_MASS);

	return true;
}

update_status ModuleCircuit::Update(float dt)
{
	wall.Render();

	return UPDATE_CONTINUE;
}

bool ModuleCircuit::CleanUp()
{
	LOG("Unloading Circuit");

	return true;
}
