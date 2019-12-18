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
	initialTerrain.SetPos(0, 0.1f, 0);
	initialTerrain.size = { 40, 0.2f, 50};
	initialTerrain.color = Brown;
	physWall = App->physics->AddBody(initialTerrain, WALL_MASS);

	//FIRST RAMP
	firstRamp = CreateRamp(vec3(0, 6.f, 35.5f), vec3(40, 0.2f, 25), 0, Red, -30, vec3(1, 0, 0), true);

	//FIRST FLOOR
	first_terrain.SetPos(0, 6, 53.5f);
	first_terrain.size = { 40, 12.f, 15};
	first_terrain.color = Brown;
	physFirstTerrain = App->physics->AddBody(first_terrain, WALL_MASS);

	//SECOND RAMP
	secondRamp = CreateRamp(vec3(0, 22, 77.5f), vec3(40, 0.2f, 40), 0, Red, -30, vec3(1, 0, 0), true);

	//SECOND FLOOR
	secondTerrain.SetPos(0, 16, 109.8f);
	secondTerrain.size = { 40, 32, 30 };
	secondTerrain.color = Brown;
	physSecondTerrain = App->physics->AddBody(secondTerrain, WALL_MASS);

	//THIRD RAMP (DESCENDING ONE)
	thirdRamp = CreateRamp(vec3(0, 16, 140.8f), vec3(40, 0.2f, 45.25f), 0, White, 45, vec3(1, 0, 0), true);

	//THIRD TERRAIN
	thirdTerrain.SetPos(-80, 0.1f, 171.8f);
	thirdTerrain.size = {200, 0.2f, 30};
	thirdTerrain.color = Red;
	physThirdTerrain = App->physics->AddBody(thirdTerrain, WALL_MASS);

	//FOURTH TERRAIN
	fourthTerrain.SetPos(-165, 0.1f, 106.15f);
	fourthTerrain.size = { 30, 0.2f, 101.3f };
	fourthTerrain.color = Green;
	physFourthTerrain = App->physics->AddBody(fourthTerrain, WALL_MASS);

	//FIFTH TERRAIN
	fifthTerrain.SetPos(-50, 0.1f, 77.65f);
	fifthTerrain.size = { 200, 0.2f, 33.8f };
	fifthTerrain.color = Blue;
	physFifthTerrain = App->physics->AddBody(fifthTerrain, WALL_MASS);

	//SIXTH TERRAIN
	sixthTerrain.SetPos(35, 0.1f, 41.875f);
	sixthTerrain.size = { 30, 0.2f, 37.75f };
	sixthTerrain.color = White;
	physSixthTerrain = App->physics->AddBody(sixthTerrain, WALL_MASS);

	//SEVENTH TERRAIN
	seventhTerrain.SetPos(-10, 0.1f, 36);
	seventhTerrain.size = { 60, 0.2f, 20.5f };
	seventhTerrain.color = Green;
	physSeventhTerrain = App->physics->AddBody(seventhTerrain, WALL_MASS);

	//FOURTH RAMP
	fourthRamp = CreateRamp(vec3(-47, 3.169f, 36), vec3(15, 0.2f, 20.5f), 0, Red, -25, vec3(0, 0, 1 ), true);

	//FIRST ELEVATED 0º RAMP
	fifthRamp = CreateRamp(vec3(-100, 16, 36), vec3(50, 0.2f, 20.5f), 0, Blue, 0, vec3(0, 0, 0), true);

	//SECOND ELEVATED 0º RAMP
	sixthRamp = CreateRamp(vec3(-140, 16, 16), vec3(30, 0.2f, 60), 0, White, 0, vec3(0, 0, 0), true);

	//SEVENTH RAMP
	seventhRamp = CreateRamp(vec3(-75.65f, 8, 0), vec3(100, 0.2f, 30), 0, Green, -9.20f, vec3(0, 0, 1), true);

	//EIGHT TERRAIN
	eightTerrain.SetPos(-22.825f, 0.1f, 0);
	eightTerrain.size = { 6.80f, 0.2f, 30 };
	eightTerrain.color = Blue;
	physEightTerrain = App->physics->AddBody(eightTerrain, WALL_MASS);

	return true;
}

update_status ModuleCircuit::Update(float dt)
{
	initialTerrain.Render();
	firstRamp.Render();
	first_terrain.Render();
	secondRamp.Render();
	secondTerrain.Render();
	thirdRamp.Render();
	thirdTerrain.Render();
	fourthTerrain.Render();
	fifthTerrain.Render();
	sixthTerrain.Render();
	seventhTerrain.Render();
	fourthRamp.Render();
	fifthRamp.Render();
	sixthRamp.Render();
	seventhRamp.Render();
	eightTerrain.Render();

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


