#pragma once
#include "vector.h"

namespace settings {
	namespace bones
	{
		bool head = true;
		bool neck = false;
		bool torso = false;
		bool pelvis = false;
	}

	namespace aimbot {

		bool enable = true;
		bool bulletp = false;
		int aim_key = VK_RBUTTON;
		bool memory = false;
		bool mouse = false;
		bool silent = false;
		bool sticky_silent = false;
		bool interpolate = false;
		bool constant = false;
		bool show_fov = false;
		bool visible_only = false;
		bool target_line = false;
		float mouse_speed = 5;
		float interpolate_speed = 5;
		float field_of_view = 10;
	}

	namespace player {
		bool enable = true;
		bool skeleton = false;
		bool box = true;
		bool normal_box = false;
		bool cornered_box = false;
		bool snapline = false;
		bool player_name = false;
		bool active_weapon = false;
		bool display_distance = false;
		float max_distance = 300;
	}

	namespace containers {
		bool enable = true;
		bool ignore_opened = false;
		bool display_distance = true;
		bool lines = false;
		bool chest = false;
		bool ammo_box = false;
		bool cooler_and_food = false;
		bool safe = false;
		float max_distance = 60;
		float line_offset = 20;
	}

	namespace pickups {
		bool enable = true;
		bool display_distance = true;
		bool lines = false;
		bool common = false;
		bool uncommon = false;
		bool rare = false;
		bool epic = false;
		bool legendary = false;
		bool mythic = false;
		float max_distance = 60;
		float line_offset = 20;
	}

	namespace weakspot {
		bool enable = false;
		bool weakspot_aimbot = false;
		bool silent = false;
		bool interpolate = false;
		bool constant = false;
		bool target_line = false;
		float interpolate_speed = 1;
	}

	namespace radar {
		bool enable = false;
		bool show_line_of_sight = true;
		bool useless_circle = false;
		bool players = true;
		bool containers = false;
		bool pickups = false;
		bool vehicles = false;
		float range = 70;
		float positionx = 50;
		float positiony = 50;
		float size = 200;
	}

	namespace miscellaneous {
		bool vehiclefly = false;
		float vehicle_flight_speed = 50;
		bool nobloom = false;
		bool fovchanger = false;
		bool fullautoweapons = false;
		bool bullettp = false;
		bool magicbullet = false;
		bool norecoil = false;
		bool adswhilejumping = false;
		float vehiclegravityslider = 0.01;
		bool doublepump = false;
		bool boatspeed = false;
		float boatspeedslider = 10;
		bool rapidfire = false;
		bool noreload = false;
		bool ziplinefly = false;
		bool testingthing = false;
		bool playerfly = false;
		bool creativefly = false;
		bool speedhack = false;
		bool instantrespawntest = false;
		bool vehiclespinbot = false;
		bool ziplinetp = false;
		float fovslider = 120;
		Vector3 AddPlayerFlyLocation;
		float PlayerFlySpeed = 50;
		Vector3 SetLocation;
		Vector3 vehiclelocation;
		float speedhackslider = 50;
	}
	
	namespace rifts {
		bool enable = false;
		bool display_distance = false;
		float max_distance = 60;
	}

	namespace miscactors {
		bool enable = true;
		bool display_distance = true;
		float max_distance = 60;
		bool vehicles = false;
		bool rifts = false;
		bool flags = false;
		bool traps = false;

	}
	namespace vehicles {
		bool enable = false;
		bool display_distance = false;
		float max_distance = 450;
	}

	namespace style {
		bool text_outlined = true;
		bool performance = false;
	}
}
