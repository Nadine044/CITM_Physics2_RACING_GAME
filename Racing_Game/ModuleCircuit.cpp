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

	wall.SetPos(0, 0.1f, 0);
	wall.size = {100, 0.2f, 100};
	wall.color = Brown;
	physWall = App->physics->AddBody(wall, WALL_MASS);

	testRamp = CreateRamp(vec3(10, 1, 5), vec3(3, 1, 20), 0, Red, 45, vec3(1, 0, 0), true);

	return true;
}

update_status ModuleCircuit::Update(float dt)
{
	wall.Render();
	testRamp.Render();

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
