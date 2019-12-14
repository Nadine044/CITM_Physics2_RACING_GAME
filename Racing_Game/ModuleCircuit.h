#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define WALL_MASS 100000

class ModuleCircuit : public Module
{
public:
	ModuleCircuit(Application* app, bool start_enabled = true);
	virtual ~ModuleCircuit();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	Cube wall;
	PhysBody3D* physWall = nullptr;
};

/*#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Primitive.h"

//EN START() CREATE BODY, HACER FUNCIÓN PARA RECOPILAR TODAS LAS WALL

#define WALL_MASS 100000

class ModuleTrack : public Module {
public:
	ModuleTrack(Application* app, bool start_enable = true);
	virtual ~ModuleTrack();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void DrawWalls() const;

	p2List<Cube> wallList;
	
};*/
