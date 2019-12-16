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

	//INITIAL TERRAIN
	wall.SetPos(0, 0.1f, 0);
	wall.size = {100, 0.2f, 50};
	wall.color = Brown;
	physWall = App->physics->AddBody(wall, WALL_MASS);

	//FIRST RAMP
	firstRamp = CreateRamp(vec3(0, 6.f, 35.5f), vec3(100, 0.2f, 25), 0, Red, -30, vec3(1, 0, 0), true);

	//FIRST FLOOR
	first_terrain.SetPos(0, 6, 53.5f);
	first_terrain.size = {100, 12.f, 15};
	first_terrain.color = Brown;
	physFirstTerrain = App->physics->AddBody(first_terrain, WALL_MASS);

	//SECOND RAMP
	secondRamp = CreateRamp(vec3(0, 22, 77.5f), vec3(100, 0.2f, 40), 0, Red, -30, vec3(1, 0, 0), true);

	return true;
}

update_status ModuleCircuit::Update(float dt)
{
	wall.Render();
	firstRamp.Render();
	first_terrain.Render();
	secondRamp.Render();

	return UPDATE_CONTINUE;
}

bool ModuleCircuit::CleanUp()
{
	LOG("Unloading Circuit");

	return true;
}

Cube ModuleCircuit::CreateRamp(vec3 position, vec3 size, float mass, Color color, float angle, vec3 angle_rot, bool is_collider)
{
	Cube cube(size.x, size.y, size.z);
	cube.SetPos(position.x, position.y, position.z);
	cube.color = color;

	if (angle != 0.0f)
	{
		cube.SetRotation(angle, angle_rot);
	}

	if (is_collider)
	{
		App->physics->AddBody(cube, mass);
	}

	return cube;
}
