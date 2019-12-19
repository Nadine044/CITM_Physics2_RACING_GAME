#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	//Personalized properties
	car.core.Set(3.f, 3.5f, 2.75f);
	car.core_offset.Set(0, 3.f, 1.875f);
	car.wall1_car.Set(0.15f, 1.5f, 5.5f);
	car.wall1_car_offset.Set(1.425f, 2, -2.25f);
	car.wall2_car.Set(0.15f, 1.5f, 5.5f);
	car.wall2_car_offset.Set(-1.425f, 2, -2.25f);
	car.wall3_car.Set(2.85f, 1.5f, 0.15f);
	car.wall3_car_offset.Set(0, 2, -4.925f);
	car.front.Set(3, 2, 1.75f);
	car.front_offset.Set(0, 2.25f, 4.125f);

	// Car properties ----------------------------------------
	car.chassis_size.Set(3, 0.3f, 10);
	car.chassis_offset.Set(0, 1.1f, 0);
	car.mass = 600.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 500.0f;
	car.frictionSlip = 10.5;
	car.maxSuspensionForce = 6000.0f; //10000?? MYTODO

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 1.f;
	float wheel_width = 0.3f;
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

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 5, 0);

	//---------------------------------------

	//TRAILER
	VehicleInfo trailerInfo;

	//Personalized properties
	trailerInfo.wall1_car.Set(0.15f, 1.5f, 10);
	trailerInfo.wall1_car_offset.Set(1.425f, 2, 0);
	trailerInfo.wall2_car.Set(0.15f, 1.5f, 10);
	trailerInfo.wall2_car_offset.Set(-1.425f, 2, 0);
	trailerInfo.wall3_car.Set(2.85f, 1.5f, 0.15f);
	trailerInfo.wall3_car_offset.Set(0, 2, -4.925f);
	trailerInfo.wall4_car.Set(2.85f, 1.5f, 0.15f);
	trailerInfo.wall4_car_offset.Set(0, 2, 4.925f);

	// Car properties ----------------------------------------
	trailerInfo.chassis_size.Set(3, 0.3f, 10);
	trailerInfo.chassis_offset.Set(0, 1.1f, 0);
	trailerInfo.mass = 500.0f;
	trailerInfo.suspensionStiffness = 15.88f;
	trailerInfo.suspensionCompression = 0.83f;
	trailerInfo.suspensionDamping = 0.88f;
	trailerInfo.maxSuspensionTravelCm = 1000.0f;
	trailerInfo.frictionSlip = 50.5;
	trailerInfo.maxSuspensionForce = 6000.0f; //10000?? MYTODO

	// Wheel properties ---------------------------------------
	float connection_height2 = 1.2f;
	float wheel_radius2 = 1.f;
	float wheel_width2 = 0.3f;
	float suspensionRestLength2 = 1.2f;

	// Don't change anything below this line ------------------

	float half_width2 = trailerInfo.chassis_size.x*0.5f;
	float half_length2 = trailerInfo.chassis_size.z*0.5f;

	vec3 direction2(0, -1, 0);
	vec3 axis2(-1, 0, 0);

	trailerInfo.num_wheels = 4;
	trailerInfo.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	trailerInfo.wheels[0].connection.Set(half_width2 - 0.3f * wheel_width2, connection_height2, half_length2 - wheel_radius2);
	trailerInfo.wheels[0].direction = direction2;
	trailerInfo.wheels[0].axis = axis2;
	trailerInfo.wheels[0].suspensionRestLength = suspensionRestLength2;
	trailerInfo.wheels[0].radius = wheel_radius2;
	trailerInfo.wheels[0].width = wheel_width2;
	trailerInfo.wheels[0].front = true;
	trailerInfo.wheels[0].drive = true;
	trailerInfo.wheels[0].brake = false;
	trailerInfo.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	trailerInfo.wheels[1].connection.Set(-half_width2 + 0.3f * wheel_width2, connection_height2, half_length2 - wheel_radius2);
	trailerInfo.wheels[1].direction = direction2;
	trailerInfo.wheels[1].axis = axis2;
	trailerInfo.wheels[1].suspensionRestLength = suspensionRestLength2;
	trailerInfo.wheels[1].radius = wheel_radius2;
	trailerInfo.wheels[1].width = wheel_width2;
	trailerInfo.wheels[1].front = true;
	trailerInfo.wheels[1].drive = true;
	trailerInfo.wheels[1].brake = false;
	trailerInfo.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	trailerInfo.wheels[2].connection.Set(half_width2 - 0.3f * wheel_width2, connection_height2, -half_length2 + wheel_radius2);
	trailerInfo.wheels[2].direction = direction2;
	trailerInfo.wheels[2].axis = axis2;
	trailerInfo.wheels[2].suspensionRestLength = suspensionRestLength2;
	trailerInfo.wheels[2].radius = wheel_radius2;
	trailerInfo.wheels[2].width = wheel_width2;
	trailerInfo.wheels[2].front = false;
	trailerInfo.wheels[2].drive = false;
	trailerInfo.wheels[2].brake = true;
	trailerInfo.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	trailerInfo.wheels[3].connection.Set(-half_width2 + 0.3f * wheel_width2, connection_height2, -half_length2 + wheel_radius2);
	trailerInfo.wheels[3].direction = direction2;
	trailerInfo.wheels[3].axis = axis2;
	trailerInfo.wheels[3].suspensionRestLength = suspensionRestLength2;
	trailerInfo.wheels[3].radius = wheel_radius2;
	trailerInfo.wheels[3].width = wheel_width2;
	trailerInfo.wheels[3].front = false;
	trailerInfo.wheels[3].drive = false;
	trailerInfo.wheels[3].brake = true;
	trailerInfo.wheels[3].steering = false;

	trailer = App->physics->AddVehicle(trailerInfo);
	trailer->SetPos(0, 5, 0);

	//ATTACHING VEHICLE WITH TRAILER

	App->physics->AddConstraintP2P(*vehicle, *trailer, vec3{ 0, 0.25f, -6 }, vec3{ 0, -0.25f, 6 });
	
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

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	vehicle->GetPos();
	if (vehicle->GetPos().z > 109.8f && vehicle->GetPos().x > -20)
	{
		App->camera->Look(vec3(50, 55, 160), vec3(-20, 0, 80), false);
	}
	else
		App->camera->FollowVehicle(30);	

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();
	trailer->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



