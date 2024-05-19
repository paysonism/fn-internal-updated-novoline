#pragma once
#include <Windows.h>

bool in_area(fvector2d target, fvector2d pos, fvector2d size)
{
	if (target.x > pos.x && target.y > pos.y)
		if (target.x < pos.x + size.x && target.y < pos.y + size.y)
			return true;

	return false;
}

namespace menu {
	fvector2d pos = { 25, 25 };

	static void run(ucanvas* canvas) {
		if (render::show_menu) {

			ZeroGUI::SetupCanvas(canvas);
			ZeroGUI::Input::Handle();

			float width = ((double)canvas->clip_x());
			float height = ((double)canvas->clip_y());
			if (ZeroGUI::Window("Payson Internal | github.com/paysonism", &pos, fvector2d{ 500.0f, 900.0f }, render::show_menu, width, height)) {
				ZeroGUI::Draw_Cursor(render::draw_cursor);
				static int tab = 0;

				if (ZeroGUI::ButtonTab(("Aimbot"), fvector2d{ 118.5, 25 }, tab == 0)) tab = 0;
				ZeroGUI::SameLine();
				if (ZeroGUI::ButtonTab(("Visuals"), fvector2d{ 118.5, 25 }, tab == 0)) tab = 1;
				ZeroGUI::SameLine();
				if (ZeroGUI::ButtonTab(("Exploits"), fvector2d{ 118.5, 25 }, tab == 0)) tab = 2;
				ZeroGUI::SameLine();
				if (ZeroGUI::ButtonTab(("Misc"), fvector2d{ 118.5, 25 }, tab == 0)) tab = 3;



				if (tab == 0)
				{
					ZeroGUI::Checkbox("Enable Mouse Aim", &settings::aimbot::mouse);
					ZeroGUI::SliderFloat("Mouse Smoothing", &settings::aimbot::mouse_speed, 1, 25);
					ZeroGUI::Checkbox("Visible Only", &settings::aimbot::visible_only);
					ZeroGUI::Checkbox("Target Line", &settings::aimbot::target_line);
					ZeroGUI::Checkbox("Show FOV Circle", &settings::aimbot::show_fov);
					ZeroGUI::SliderFloat("FOV Value", &settings::aimbot::field_of_view, 1, 360);
					ZeroGUI::Text("Aim Bone");
					ZeroGUI::Checkbox("Head", &settings::bones::head);
					if (settings::bones::head == true)
					{
						settings::bones::torso = false;
						settings::bones::neck = false;
						settings::bones::pelvis = false;
					}
					ZeroGUI::Checkbox("Chest", &settings::bones::torso);
					if (settings::bones::torso == true)
					{
						settings::bones::head = false;
						settings::bones::neck = false;
						settings::bones::pelvis = false;
					}
					ZeroGUI::Checkbox("Neck", &settings::bones::neck);
					if (settings::bones::neck == true)
					{
						settings::bones::head = false;
						settings::bones::torso = false;
						settings::bones::pelvis = false;
					}
					ZeroGUI::Checkbox("Pelvis", &settings::bones::pelvis);
					if (settings::bones::pelvis == true)
					{
						settings::bones::head = false;
						settings::bones::torso = false;
						settings::bones::neck = false;
					}
					fvector2d size = fvector2d{ 150, 25 };
					ZeroGUI::Text("Aim Key");
					ZeroGUI::Hotkey(" ", size, &settings::aimbot::aim_key);
				}

				else if (tab == 1)
				{
					ZeroGUI::Checkbox("Box", &settings::player::normal_box);
					ZeroGUI::Checkbox("Cornered Box", &settings::player::cornered_box);
					ZeroGUI::Checkbox("Skeleton", &settings::player::skeleton);
					ZeroGUI::Checkbox("Distance", &settings::player::display_distance);
					ZeroGUI::Checkbox("Snapline", &settings::player::snapline);
					ZeroGUI::Checkbox("Current Weapon", &settings::player::active_weapon);
					ZeroGUI::Checkbox("Username", &settings::player::player_name);

					ZeroGUI::Checkbox("Radar", &settings::radar::enable);
					if (settings::radar::enable) {
						ZeroGUI::SliderFloat("Radar Size", &settings::radar::size, 0, 300);
						ZeroGUI::SliderFloat("Radar Position X", &settings::radar::positionx, 0, 500);
						ZeroGUI::SliderFloat("Radar Position Y", &settings::radar::positiony, 0, 500);
					}

					ZeroGUI::SliderFloat("Player Render Distance", &settings::player::max_distance, 5, 300);
					ZeroGUI::SliderFloat("Container Render Distance", &settings::containers::max_distance, 5, 450);
					ZeroGUI::SliderFloat("Loot Render Distance", &settings::pickups::max_distance, 5, 450);
					ZeroGUI::SliderFloat("Vehicle Render Distance", &settings::miscactors::max_distance, 5, 450);

					ZeroGUI::NextColumn(140);
					ZeroGUI::Text(" ");
					ZeroGUI::Checkbox("Chests", &settings::containers::chest);
					ZeroGUI::Checkbox("Vehicles", &settings::miscactors::vehicles);
					ZeroGUI::Checkbox("Ammo Boxes", &settings::containers::ammo_box);
					ZeroGUI::Checkbox("Coolers", &settings::containers::cooler_and_food);
					ZeroGUI::Checkbox("Safes", &settings::containers::safe);

					ZeroGUI::NextColumn(280);
					ZeroGUI::Text(" ");
					ZeroGUI::Checkbox("Common Loot", &settings::pickups::common);
					ZeroGUI::Checkbox("Uncommon Loot", &settings::pickups::uncommon);
					ZeroGUI::Checkbox("Rare Loot", &settings::pickups::rare);
					ZeroGUI::Checkbox("Epic Loot", &settings::pickups::epic);
					ZeroGUI::Checkbox("Legendary Loot", &settings::pickups::legendary);
					ZeroGUI::Checkbox("Mythic Loot", &settings::pickups::mythic);
				}




				else if (tab == 2)
				{
					ZeroGUI::Checkbox("Projectile Bullet TP", &settings::miscellaneous::bullettp);
					ZeroGUI::Checkbox("FOV Changer", &settings::miscellaneous::fovchanger);
					ZeroGUI::Checkbox("Aim While Jumping", &settings::miscellaneous::adswhilejumping);
					ZeroGUI::Checkbox("No Recoil", &settings::miscellaneous::norecoil);
					ZeroGUI::Checkbox("No Bloom [!]", &settings::miscellaneous::nobloom);
					ZeroGUI::Checkbox("No Reload", &settings::miscellaneous::noreload);
					ZeroGUI::Checkbox("Rapid Fire", &settings::miscellaneous::rapidfire);
					ZeroGUI::SliderFloat("FOV Value", &settings::miscellaneous::fovslider, 0, 180);
				}
				else if (tab == 3)
				{
					ZeroGUI::Text("not pasted at all");
					ZeroGUI::Text("github.com/paysonism");
					ZeroGUI::Text("discord.gg/saturniv");
				}
			}
		}
	}
}



#define M_PI   3.14159265358979323846264338327950288

float degree_to_radian(float degree) {
	return degree * (M_PI / 180);
}

void angle_rotation(const frotator& angles, fvector* forward)
{
	float	sp, sy, cp, cy;

	sy = sin(degree_to_radian(angles.yaw));
	cy = cos(degree_to_radian(angles.yaw));

	sp = sin(degree_to_radian(angles.pitch));
	cp = cos(degree_to_radian(angles.pitch));

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

namespace fortnite {
	namespace temp {
		bool silent_active = false;
		frotator silent_rotation = frotator();
		bool sticky_silent_active = false;
		frotator sticky_silent_rotation = frotator();
	}
	bool visible;
	namespace radar {
		fvector2d position, size;
		fvector camera_location;
		frotator camera_rotation;

		void range(double* x, double* y, double range) {
			if (defines::math->abs((*x)) > range || defines::math->abs((*y)) > range) {
				if ((*y) > (*x)) {
					if ((*y) > -(*x)) {
						(*x) = range * (*x) / (*y);
						(*y) = range;
					}
					else {
						(*y) = -range * (*y) / (*x);
						(*x) = -range;
					}
				}
				else {
					if ((*y) > -(*x)) {
						(*y) = range * (*y) / (*x);
						(*x) = range;
					}
					else {
						(*x) = -range * (*x) / (*y);
						(*y) = -range;
					}
				}
			}
		}

		void rotate_point(fvector2d* screen, fvector origin, fvector camera_location, frotator camera_rotation) {
			auto yaw = camera_rotation.yaw * 3.1415927 / 180;

			double dx = origin.x - camera_location.x;
			double dy = origin.y - camera_location.y;

			double fsin_yaw = defines::math->sin(yaw);
			double fminus_cos_yaw = -defines::math->cos(yaw);

			double x = -(dy * fminus_cos_yaw + dx * fsin_yaw);
			double y = dx * fminus_cos_yaw - dy * fsin_yaw;

			double range_value = settings::radar::range * 1000;
			range(&x, &y, range_value);

			auto DrawPos = radar::position;
			auto DrawSize = radar::size;

			int rad_x = (int)DrawPos.x;
			int rad_y = (int)DrawPos.y;

			double r_siz_x = DrawSize.x;
			double r_siz_y = DrawSize.y;

			int x_max = (int)r_siz_x + rad_x - 5;
			int y_max = (int)r_siz_y + rad_y - 5;

			double out_screen_x = rad_x + ((int)r_siz_x / 2 + int(x / range_value * r_siz_x));
			double out_screen_y = rad_y + ((int)r_siz_y / 2 + int(y / range_value * r_siz_y));

			if (out_screen_x > x_max)
				out_screen_x = x_max;

			if (out_screen_x < rad_x)
				out_screen_x = rad_x;

			if (out_screen_y > y_max)
				out_screen_y = y_max;

			if (out_screen_y < rad_y)
				out_screen_y = rad_y;

			*screen = fvector2d(out_screen_x, out_screen_y);
		}

		void add_to_radar(fvector world_location, flinearcolor color) {
			fvector2d screen;
			rotate_point(&screen, world_location, radar::camera_location, radar::camera_rotation);

			render::filled_box(screen, fvector2d(4, 4), color);
		}

		void radar_initialize(fvector2d position, fvector2d size, fvector camera_location, frotator camera_rotation) {
			radar::position = position;
			radar::size = size;
			radar::camera_location = camera_location;
			radar::camera_rotation = camera_rotation;

			render::filled_box(position, size, flinearcolor(0.025f, 0.025f, 0.025f, 1.f));

			if (settings::radar::useless_circle) {
				render::circle(fvector2d(position.x + size.x / 2, position.y + size.y / 2), size.x / 2, 100, flinearcolor(1.f, 1.f, 1.f, 1.f));
			}

			if (settings::radar::show_line_of_sight) {
				render::line(fvector2d(position.x + size.x / 2, position.y + size.y), fvector2d(position.x + size.x / 2, position.y + size.y / 2), flinearcolor(1.f, 1.f, 1.f, 1.f), 1.f);
				render::line(fvector2d(position.x + size.x / 2, position.y + size.y / 2), fvector2d(position.x, position.y), flinearcolor(1.f, 1.f, 1.f, 1.f), 1.f);
				render::line(fvector2d(position.x + size.x / 2, position.y + size.y / 2), fvector2d(position.x + size.x, position.y), flinearcolor(1.f, 1.f, 1.f, 1.f), 1.f);
			}
		}
	}

	void set_aim_mouse(aplayercontroller* controller, fvector aim_location, float width, float height, float smooth) {
		float ScreenCenterX = (width / 2);
		float ScreenCenterY = (height / 2);
		float TargetX = 0;
		float TargetY = 0;
		auto aim_screen = fvector2d();
		if (controller->w2s(aim_location, &aim_screen) && aim_screen) {
			if (aim_screen.x != 0)
			{
				if (aim_screen.x > ScreenCenterX)
				{
					TargetX = -(ScreenCenterX - aim_screen.x);
					TargetX /= smooth;
					if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = -0;
				}

				if (aim_screen.x < ScreenCenterX)
				{
					TargetX = aim_screen.x - ScreenCenterX;
					TargetX /= smooth;
					if (TargetX + ScreenCenterX < 0) TargetX = -0;
				}
			}

			if (aim_screen.y != 0)
			{
				if (aim_screen.y > ScreenCenterY)
				{
					TargetY = -(ScreenCenterY - aim_screen.y);
					TargetY /= smooth;
					if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = -0;
				}

				if (aim_screen.y < ScreenCenterY)
				{
					TargetY = aim_screen.y - ScreenCenterY;
					TargetY /= smooth;
					if (TargetY + ScreenCenterY < 0) TargetY = -0;
				}
			}

			INPUT input = {};
			input.type = INPUT_MOUSE;
			input.mi.dx = static_cast<LONG>(TargetX);
			input.mi.dy = static_cast<LONG>(TargetY);
			input.mi.dwFlags = MOUSEEVENTF_MOVE;
			SendInput(1, &input, sizeof(INPUT));
		}
	}

	

	void set_aim(uworld* world, aplayercontroller* controller, fvector camera_location, frotator camera_rotation, fvector aim_location, bool interpolate, bool constant, double speed) {
		auto aim_rotation = defines::math->find_look_at_rotation(camera_location, aim_location);
		auto world_delta_seconds = defines::game_statics->get_world_delta_seconds(world);

		auto result = aim_rotation;
		if (interpolate) {
			if (constant)
				result = defines::math->interp_to_constant(camera_rotation, aim_rotation, world_delta_seconds, speed);
			else
				result = defines::math->interp_to(camera_rotation, aim_rotation, world_delta_seconds, speed);
		}

		result.pitch = (result.pitch - camera_rotation.pitch) / controller->input_pitch_scale();
		result.yaw = (result.yaw - camera_rotation.yaw) / controller->input_yaw_scale();

		controller->add_pitch_input((float)result.pitch);
		controller->add_yaw_input((float)result.yaw);
	}

	fvector bottom, bottom_2, head, head_2, neck, chest, pelvis, rshoulder, relbow, rhand, rthigh, rknee, rfoot, rfootout, lshoulder, lelbow, lhand, lthigh, lknee, lfoot, lfootout;
	fvector2d s_bottom, s_bottom_2, s_head, s_head_2, s_neck, s_chest, s_pelvis, s_rshoulder, s_relbow, s_rhand, s_rthigh, s_rknee, s_rfoot, s_rfootout, s_lshoulder, s_lelbow, s_lhand, s_lthigh, s_lknee, s_lfoot, s_lfootout;

	bool get_performance_bones(aplayercontroller* controller, mesh* mesh) {
		bool success = true;

		bottom = mesh->get_bone_location(0);
		if (success && !controller->w2s(bottom, &s_bottom)) success = false;

	
		head = mesh->get_bone_location(67);
		if (success && !controller->w2s(head, &s_head)) success = false;

		if (!s_bottom || !s_head) 
			return false;


		return success;
	}	

	bool get_all_bones(aplayercontroller* controller, mesh* mesh) {
		bool success = true;

		bottom = mesh->get_bone_location(0);
		if (success && !controller->w2s(bottom, &s_bottom)) success = false;

		bottom_2 = bottom; bottom_2.z -= 10;
		if (success && !controller->w2s(bottom_2, &s_bottom_2)) success = false;

		head = mesh->get_bone_location(67);
		if (success && !controller->w2s(head, &s_head)) success = false;

		head_2 = head; head_2.z += 13;
		if (success && !controller->w2s(head_2, &s_head_2)) success = false;

		neck = mesh->get_bone_location(67);
		if (success && !controller->w2s(neck, &s_neck)) success = false;

		chest = mesh->get_bone_location(7); chest.z += 7;
		if (success && !controller->w2s(chest, &s_chest)) success = false;

		pelvis = mesh->get_bone_location(2);
		if (success && !controller->w2s(pelvis, &s_pelvis)) success = false;

		rshoulder = mesh->get_bone_location(38);
		if (success && !controller->w2s(rshoulder, &s_rshoulder)) success = false;

		relbow = mesh->get_bone_location(39);
		if (success && !controller->w2s(relbow, &s_relbow)) success = false;

		rhand = mesh->get_bone_location(40);
		if (success && !controller->w2s(rhand, &s_rhand)) success = false;

		rthigh = mesh->get_bone_location(78);
		if (success && !controller->w2s(rthigh, &s_rthigh)) success = false;

		rknee = mesh->get_bone_location(79);
		if (success && !controller->w2s(rknee, &s_rknee)) success = false;

		rfoot = mesh->get_bone_location(82);
		if (success && !controller->w2s(rfoot, &s_rfoot)) success = false;

		rfootout = mesh->get_bone_location(83);
		if (success && !controller->w2s(rfootout, &s_rfootout)) success = false;

		lshoulder = mesh->get_bone_location(9);
		if (success && !controller->w2s(lshoulder, &s_lshoulder)) success = false;

		lelbow = mesh->get_bone_location(10);
		if (success && !controller->w2s(lelbow, &s_lelbow)) success = false;

		lhand = mesh->get_bone_location(11);
		if (success && !controller->w2s(lhand, &s_lhand)) success = false;

		lthigh = mesh->get_bone_location(71);
		if (success && !controller->w2s(lthigh, &s_lthigh)) success = false;

		lknee = mesh->get_bone_location(72);
		if (success && !controller->w2s(lknee, &s_lknee)) success = false;

		lfoot = mesh->get_bone_location(75);
		if (success && !controller->w2s(lfoot, &s_lfoot)) success = false;

		lfootout = mesh->get_bone_location(76);
		if (success && !controller->w2s(lfootout, &s_lfootout)) success = false;

		if (!s_bottom || !s_head || !s_neck || !s_chest || !s_rshoulder || !s_relbow || !s_rhand || !s_lshoulder || !s_lelbow || !s_lhand || !s_rthigh || !s_rknee || !s_rfoot || !s_rfootout || !s_lthigh || !s_lknee || !s_lfoot || !s_lfootout)
			return false;

		return success;
	}
}

namespace essential_hooks {
	fvector location_o = fvector();
	frotator rotation_o = frotator();

	ulocalplayer* local_player_old = 0;
	aplayercontroller* player_controller_old = 0;

	using get_view_point_sim = void(*)(ulocalplayer* local_player, fminimalviewinfo* out_viewinfo, BYTE stereo_pass);
	get_view_point_sim get_view_point_o = 0;

	void get_view_point(ulocalplayer* local_player, fminimalviewinfo* out_viewinfo, BYTE stereo_pass) {
		get_view_point_o(local_player, out_viewinfo, stereo_pass);

		if (fortnite::temp::silent_active) {
			out_viewinfo->location = location_o;
			out_viewinfo->rotation = rotation_o;
		}

		if (fortnite::temp::sticky_silent_active) {
			out_viewinfo->location = location_o;
			out_viewinfo->location.z += 40;
			out_viewinfo->rotation = fortnite::temp::sticky_silent_rotation;
		}
	}

	using get_player_view_point_sim = void(*)(aplayercontroller* controller, fvector* location, frotator* rotation);
	get_player_view_point_sim get_player_view_point_o = 0;

	void get_player_view_point(aplayercontroller* controller, fvector* location, frotator* rotation) {
		get_player_view_point_o(controller, location, rotation);

		location_o = *location;
		rotation_o = *rotation;

		if (fortnite::temp::silent_active) {
			*rotation = fortnite::temp::silent_rotation;
		}

		if (fortnite::temp::sticky_silent_active) {
			*rotation = fortnite::temp::sticky_silent_rotation;
		}
	}

	void run(aplayercontroller* controller, ulocalplayer* local_player) {
		if (local_player != essential_hooks::local_player_old) {
 			void** LocalPlayer_VTable = *(void***)(local_player);
			DWORD OldProtection;
			(VirtualProtect)(&LocalPlayer_VTable[88], 8, PAGE_EXECUTE_READWRITE, &OldProtection);
			essential_hooks::get_view_point_o = decltype(essential_hooks::get_view_point_o)(LocalPlayer_VTable[88]);
			LocalPlayer_VTable[88] = &essential_hooks::get_view_point;
			(VirtualProtect)(&LocalPlayer_VTable[88], 8, OldProtection, &OldProtection);

			essential_hooks::local_player_old = local_player;
		}

		if (controller != essential_hooks::player_controller_old) {
			void** PlayerController_VTable = *(void***)(controller);
			DWORD OldProtection;
			(VirtualProtect)(&PlayerController_VTable[245], 8, PAGE_EXECUTE_READWRITE, &OldProtection);
			essential_hooks::get_player_view_point_o = decltype(essential_hooks::get_player_view_point_o)(PlayerController_VTable[245]);
			PlayerController_VTable[245] = &essential_hooks::get_player_view_point;
			(VirtualProtect)(&PlayerController_VTable[245], 8, OldProtection, &OldProtection);
			essential_hooks::player_controller_old = controller;
		}
	}
}



void novoline_main(ugameviewportclient* viewport, ucanvas* canvas) {
	auto screen_size = fvector2d((double)canvas->clip_x(), (double)canvas->clip_y());
	auto center = fvector2d((double)screen_size.x / 2, (double)screen_size.y / 2);
	bool player_silent = false;

	auto world = viewport->get_world();
	if (!world) return;

	auto game_instance = defines::game_statics->get_game_instance(world);
	if (!game_instance) return;

	auto local_player = game_instance->get_local_players()[0];
	if (!game_instance) return;

	auto controller = defines::game_statics->get_player_controller(world, std::int32_t(0));
	if (!controller) return;

	auto camera_manager = defines::game_statics->get_player_camera_manager(world, std::int32_t(0));
	if (!camera_manager) return;

	render::world = world;
	render::canvas = canvas;
	render::controller = controller;
	render::screen_center = center;
	render::screen_size = screen_size;


	if (render::is_insert_clicked()) render::show_menu = !render::show_menu;
	menu::run(canvas);

	auto camera_location = camera_manager->get_camera_location();
	auto camera_rotation = camera_manager->get_camera_rotation();
	auto camera_fov = camera_manager->get_fov_angle();


	auto radius = (settings::aimbot::field_of_view * center.x / (double)camera_fov) / 2;

	auto local_pawn_holding_pickaxe = false;
	auto local_pawn = controller->get_pawn();

	if (settings::radar::enable) {
		fortnite::radar::radar_initialize(fvector2d(settings::radar::positionx, settings::radar::positiony), fvector2d(settings::radar::size, settings::radar::size), camera_location, camera_rotation);
	}

	//exploits

	if (settings::miscellaneous::fovchanger) {
		if (local_pawn) {
			controller->fov(settings::miscellaneous::fovslider);
		}
	}

	if (settings::miscellaneous::norecoil) {
		*(float*)(controller + offsets::CustomTimeDilation) = -1;
	}


	if (settings::miscellaneous::noreload) {
		if (local_pawn) {
			auto CurrentWeapon = local_pawn->get_current_weapon();
			if (CurrentWeapon)
			{
				bool bIsReloadingWeapon = *(bool*)(CurrentWeapon + offsets::bIsReloadingWeapon); //0x358 = bIsReloadingWeapon
				auto Mesh = *(uintptr_t*)(local_pawn + offsets::Mesh); // 0x318 = Mesh

				if (bIsReloadingWeapon)
				{
					*(float*)(Mesh + offsets::GlobalAnimRateScale) = 999; // 0xA60 = GlobalAnimRateScale
				}
				else
				{
					*(float*)(Mesh + offsets::GlobalAnimRateScale) = 1; // 0xA60 = GlobalAnimRateScale
				}
			}
		}
	}

	if (settings::miscellaneous::nobloom)
		if (local_pawn) {
			{
				auto CurrentWeapon = local_pawn->get_current_weapon();
				if (CurrentWeapon && 0x64)
				{
					*(float*)(CurrentWeapon + 0x64) = FLT_MAX;
				}
			}
		}






	if (settings::player::enable) {
		double closest_distance = DBL_MAX;
		player_pawn* target_player = 0;

		tarray<uobject*> player_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_player_class);
		for (int i = 0; i < player_array.size(); i++) {
			if (!player_array.valid(i)) continue;

			auto player = (player_pawn*)player_array[i];
			if (player == local_pawn) continue;
			if (!player) continue;

			if (player->is_dead()) continue;

			auto object_name = defines::system->get_object_name(player);

			if (!defines::string->contains(object_name.c_str(), L"PlayerPawn", false, false)) continue;

			auto skeleton_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
			auto esp_color = flinearcolor(1.f, 0.f, 0.f, 1.f);
			auto black_color = flinearcolor(0.f, 0.f, 0.f, 1.f);

			auto world_location = player->get_actor_location();

			if (settings::radar::enable && settings::radar::players) {
				fortnite::radar::add_to_radar(world_location, esp_color);
			}

			auto max_distance = settings::player::max_distance;
			double distance = defines::math->vector_distance(world_location, camera_location) * 0.01;
			if (distance > max_distance) continue;

			bool visible = player->was_recently_rendered(0.f);
			if (visible) {
				fortnite::visible = true;
				skeleton_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
			}
			else {
				fortnite::visible = false;
				skeleton_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
			}




			auto mesh = player->get_pawn_mesh();
			if (!mesh) continue;

			if (!settings::style::performance) {
				if (!fortnite::get_all_bones(controller, mesh)) continue;
			}
			else {
				if (!fortnite::get_performance_bones(controller, mesh)) continue;
			}
			if (settings::style::performance) {
				if (!in_area(fortnite::s_bottom, fvector2d(50, 50), fvector2d(screen_size.x - (50 * 2), screen_size.y - (50 * 2)))) continue;
			}

			if (settings::player::skeleton) {
				render::line_with_outline(fortnite::s_head, fortnite::s_neck, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_neck, fortnite::s_chest, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_chest, fortnite::s_pelvis, skeleton_color, 1.f);

				render::line_with_outline(fortnite::s_chest, fortnite::s_rshoulder, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_rshoulder, fortnite::s_relbow, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_relbow, fortnite::s_rhand, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_pelvis, fortnite::s_rthigh, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_rthigh, fortnite::s_rknee, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_rknee, fortnite::s_rfoot, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_rfoot, fortnite::s_rfootout, skeleton_color, 1.f);

				render::line_with_outline(fortnite::s_chest, fortnite::s_lshoulder, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_lshoulder, fortnite::s_lelbow, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_lelbow, fortnite::s_lhand, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_pelvis, fortnite::s_lthigh, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_lthigh, fortnite::s_lknee, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_lknee, fortnite::s_lfoot, skeleton_color, 1.f);
				render::line_with_outline(fortnite::s_lfoot, fortnite::s_lfootout, skeleton_color, 1.f);
			}
			auto most_left = DBL_MAX;
			auto most_right = DBL_MIN;
			auto most_top = DBL_MAX;
			auto most_bottom = DBL_MIN;


			if (!settings::style::performance) {
				fvector2d bones_to_check[] = { fortnite::s_bottom, fortnite::s_head, fortnite::s_head_2, fortnite::s_neck, fortnite::s_chest, fortnite::s_pelvis, fortnite::s_rshoulder, fortnite::s_relbow, fortnite::s_rhand, fortnite::s_rthigh, fortnite::s_rknee, fortnite::s_rfoot, fortnite::s_rfootout, fortnite::s_lshoulder, fortnite::s_lelbow,fortnite::s_lhand, fortnite::s_lthigh, fortnite::s_lknee, fortnite::s_lfoot, fortnite::s_lfootout };

				for (int i = 0; i < 20; i++) {
					auto bone = bones_to_check[i];

					if (bone.x < most_left)
						most_left = bone.x;

					if (bone.x > most_right)
						most_right = bone.x;

					if (bone.y < most_top)
						most_top = bone.y;

					if (bone.y > most_bottom)
						most_bottom = bone.y;
				}
			}
			else {
				fvector2d bones_to_check[] = { fortnite::s_bottom, fortnite::s_head };

				for (int i = 0; i < 2; i++) {
					auto bone = bones_to_check[i];

					if (bone.x < most_left)
						most_left = bone.x;

					if (bone.x > most_right)
						most_right = bone.x;

					if (bone.y < most_top)
						most_top = bone.y;

					if (bone.y > most_bottom)
						most_bottom = bone.y;
				}
			}
			auto actor_height = most_bottom - most_top;
			auto actor_width = most_right - most_left;

			auto calculated_distance = max_distance - distance;
			auto offset = calculated_distance * 0.035;
			auto corner_wide = actor_width / 3;
			auto corner_heit = actor_height / 3;

			auto text_offset = double(0);
			fvector2d bottom_middle;
			fvector2d top_middle;
			if (!settings::style::performance) {
				bottom_middle = fvector2d(most_left + actor_width / 2, fortnite::s_bottom_2.y);
			}
			else {
				bottom_middle = fvector2d(most_left + actor_width / 2, fortnite::s_bottom_2.y);
			}



			if (settings::player::cornered_box) {
				//top left
				render::line_with_outline(fvector2d(most_left - offset, most_top - offset), fvector2d(most_left - offset + corner_wide, most_top - offset), esp_color, 1.f);
				render::line_with_outline(fvector2d(most_left - offset, most_top - offset), fvector2d(most_left - offset, most_top - offset + corner_heit), esp_color, 1.f);

				//top right
				render::line_with_outline(fvector2d(most_right + offset, most_top - offset), fvector2d(most_right + offset - corner_wide, most_top - offset), esp_color, 1.f);
				render::line_with_outline(fvector2d(most_right + offset, most_top - offset), fvector2d(most_right + offset, most_top - offset + corner_heit), esp_color, 1.f);

				//bottom left
				render::line_with_outline(fvector2d(most_left - offset, most_bottom + offset), fvector2d(most_left - offset + corner_wide, most_bottom + offset), esp_color, 1.f);
				render::line_with_outline(fvector2d(most_left - offset, most_bottom + offset), fvector2d(most_left - offset, most_bottom + offset - corner_heit), esp_color, 1.f);

				//bottom right
				render::line_with_outline(fvector2d(most_right + offset, most_bottom + offset), fvector2d(most_right + offset - corner_wide, most_bottom + offset), esp_color, 1.f);
				render::line_with_outline(fvector2d(most_right + offset, most_bottom + offset), fvector2d(most_right + offset, most_bottom + offset - corner_heit), esp_color, 1.f);

				// Outline on the other side

			}
			if (settings::player::normal_box) {
				render::line_with_outline(fvector2d(most_left - offset, most_top - offset), fvector2d(most_left - offset, most_bottom + offset), esp_color, 1.f);


				// right line
				render::line_with_outline(fvector2d(most_right + offset, most_top - offset), fvector2d(most_right + offset, most_bottom + offset), esp_color, 1.f);

				// top line
				render::line_with_outline(fvector2d(most_left - offset, most_top - offset), fvector2d(most_right + offset, most_top - offset), esp_color, 1.f);

				// bottom line
				render::line_with_outline(fvector2d(most_left - offset, most_bottom + offset), fvector2d(most_right + offset, most_bottom + offset), esp_color, 1.f);
			}

			if (settings::player::player_name) {
				if (player && defines::actor_player_nameprivate && local_pawn) {
					auto playername = defines::lib->get_player_name_safe(player, defines::actor_player_nameprivate);
					render::text(playername.c_str(), fvector2d(bottom_middle.x, bottom_middle.y + text_offset), flinearcolor(1.f, 1.f, 1.f, 1.f), true, false, settings::style::text_outlined);
					text_offset += 15;
				}
			}

			if (settings::player::display_distance) {
				auto final = defines::string->build_string_double(L"", L"[", defines::math->round(distance), L"M]");
				render::text(final.c_str(), fvector2d(bottom_middle.x, bottom_middle.y + text_offset), flinearcolor(1.f, 1.f, 1.f, 1.f), true, false, settings::style::text_outlined);
				text_offset += 15;
			}

			if (settings::player::active_weapon) {
				if (local_pawn) {
					if (auto current_weapon = player->get_current_weapon()) {
						if (auto weapon_data = current_weapon->get_weapon_data()) {
							auto display_name = weapon_data->display_name();
							if (display_name.data && display_name.c_str()) {
								auto tier = weapon_data->get_tier();

								auto render_color = flinearcolor();
								if (tier == fort_item_tier::I) render_color = flinearcolor(0.4f, 0.4f, 0.4f, 1.f);
								else if (tier == fort_item_tier::II) render_color = flinearcolor(0.2f, 0.8f, 0.4f, 1.f);
								else if (tier == fort_item_tier::III) render_color = flinearcolor(0.f, 0.4f, 0.8f, 1.f);
								else if (tier == fort_item_tier::IV) render_color = flinearcolor(1.f, 0.f, 1.f, 1.f);
								else if (tier == fort_item_tier::V) render_color = flinearcolor(0.7f, 0.7f, 0.f, 1.f);
								else if (tier == fort_item_tier::VI) render_color = flinearcolor(1.f, 1.f, 0.f, 1.f);

								if (render_color) {
									auto a = defines::string->build_string_int(display_name.c_str(), L" [", current_weapon->get_magazine_ammo_count(), L"");
									auto b = defines::string->build_string_int(L"", L"/", current_weapon->get_bullets_per_clip(), L"]");
									auto c = defines::string->concat_str_str(a, b);
									render::text(c.c_str(), fvector2d(bottom_middle.x, bottom_middle.y + text_offset), render_color, true, false, settings::style::text_outlined);
									text_offset += 15;
								}
							}
						}
					}
				}
			}



			if (settings::player::snapline) {
				render::line_with_outline(fvector2d(center.x, screen_size.y - 15), fvector2d(bottom_middle.x, bottom_middle.y + text_offset), flinearcolor(1.f, 1.f, 1.f, 1.f), 1.f);
			}

			if (!local_pawn_holding_pickaxe && ((settings::aimbot::visible_only && visible) || (!settings::aimbot::visible_only)) && local_pawn && render::in_circle(center.x, center.y, radius, fortnite::s_head.x, fortnite::s_head.y)) {
				double distance = defines::math->distance2d(fortnite::s_head, center);
				if (distance < closest_distance) {
					target_player = player;
					closest_distance = distance;
				}
			}
		}

		if (settings::aimbot::enable) {
			auto temp_silent_active = false;
			auto temp_silent_rotation = frotator();

			auto temp_sticky_silent_active = false;
			auto temp_sticky_silent_rotation = frotator();

			if (settings::aimbot::show_fov) {
				render::circle(center, radius, 100, flinearcolor(0.9f, 0.9f, 0.9f, 1.f));
			}



			if (target_player && local_pawn) {
				if (auto mesh = target_player->get_pawn_mesh()) {

					int32_t bone = 67;

					if (settings::bones::head)
						bone = 67;
					else if (settings::bones::neck)
						bone = 67;
					else if (settings::bones::torso)
						bone = 7;
					else if (settings::bones::pelvis)
						bone = 2;


					auto aim_location = mesh->get_bone_location(bone);
					auto skeleton_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
					auto esp_color = flinearcolor(1.f, 0.f, 0.f, 1.f);
					auto visible = target_player->was_recently_rendered(0.f);
					if (visible) {
						skeleton_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
					}
					else {
						skeleton_color = flinearcolor(0.f, 1.f, 1.f, 1.f);
					}

					if (settings::aimbot::target_line) {
						auto aim_screen = fvector2d();
						if (controller->w2s(aim_location, &aim_screen) && aim_screen) {
							render::line_with_outline(center, aim_screen, flinearcolor(1.f, 1.f, 1.f, 1.f), 1.f);
						}
					}

					if (settings::miscellaneous::bullettp)
					{
						tarray<uobject*> projectile_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_projectile_class);
						for (int i = 0; i < projectile_array.size(); i++) {
							if (!projectile_array.valid(i)) continue;

							auto projectile = (actor*)projectile_array[i];
							if (!projectile) continue;

							auto object_name = defines::system->get_object_name(projectile);

							if (!defines::string->contains(object_name.c_str(), L"Bullet", false, false))
								continue;

							projectile->set_actor_location(aim_location, false, 0, false);
						}
					}

					if (settings::miscellaneous::magicbullet)
					{
						tarray<uobject*> projectile_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_projectile_class);
						for (int i = 0; i < projectile_array.size(); i++) {
							if (!projectile_array.valid(i)) continue;

							auto projectile = (actor*)projectile_array[i];
							if (!projectile) continue;

							auto object_name = defines::system->get_object_name(projectile);
							projectile->set_actor_location(aim_location, false, 0, false);
						}
					}




					if (GetAsyncKeyState(settings::aimbot::aim_key) & 0x8000) {
						if (settings::aimbot::mouse) {
							float width = ((double)canvas->clip_x());
							float height = ((double)canvas->clip_y());

							fortnite::set_aim_mouse(controller, aim_location, width, height, settings::aimbot::mouse_speed);
						}
					}
				}
			}

			fortnite::temp::silent_active = temp_silent_active;
			fortnite::temp::silent_rotation = temp_silent_rotation;

			fortnite::temp::sticky_silent_active = temp_sticky_silent_active;
			fortnite::temp::sticky_silent_rotation = temp_sticky_silent_rotation;
		}
	}

	if (settings::weakspot::enable) {
		weakspot_actor* target_weakspot = 0;
		tarray<uobject*> weakspot_array = defines::game_statics->get_all_actors_of_class(world, defines::actor_weakspot_class);
		for (int i = 0; i < weakspot_array.size(); i++) {
			if (!weakspot_array.valid(i)) continue;

			auto weakspot = (weakspot_actor*)weakspot_array[i];
			if (!weakspot) continue;

			if (!weakspot->is_active()) continue;

			target_weakspot = weakspot;
		}

		auto temp_silent_active = false;
		auto temp_silent_rotation = frotator();

		if (target_weakspot) {
			auto aim_location = target_weakspot->get_actor_location();
			auto aim_screen = fvector2d();
			if (controller->w2s(aim_location, &aim_screen) && aim_screen) {

				render::text(L"[X]", aim_screen, flinearcolor(1.f, 0.f, 0.f, 1.f), true, true, settings::style::text_outlined);

				if (settings::weakspot::weakspot_aimbot && local_pawn) {
					if (settings::weakspot::target_line) {
						render::line_with_outline(center, aim_screen, flinearcolor(1.f, 0.f, 0.f, 1.f), 1.f);
					}

					if (controller->is_key_down(defines::left_mouse_button)) {
						if (settings::weakspot::silent) {
							temp_silent_active = true;
							temp_silent_rotation = defines::math->find_look_at_rotation(camera_location, aim_location);
						}
						else {
							fortnite::set_aim(world, controller, camera_location, camera_rotation, aim_location, settings::weakspot::interpolate, settings::weakspot::constant, settings::weakspot::interpolate_speed);
						}
					}
				}
			}
		}
	}
}

namespace payson1337 {
	using draw_transition_sim = void(*)(ugameviewportclient* viewport, ucanvas* canvas);
	draw_transition_sim draw_transition_o = 0;


	void draw_transition(ugameviewportclient* viewport, ucanvas* canvas) {
		novoline_main(viewport, canvas);
		return draw_transition_o(viewport, canvas);
	}


	static void init() {
		game = get_module(L"FortniteClient-Win64-Shipping.exe");

		if (!game)
			return;

		defines::init();


		if (auto world = uobject::find_object(L"Frontend", reinterpret_cast<uobject*>(-1))) {
			auto game_instance = defines::game_statics->get_game_instance(world);
			auto local_player = game_instance->get_local_players()[0];


			auto controller = defines::game_statics->get_player_controller(world, std::int32_t(0));
			auto viewport = local_player->get_viewport();

			auto engine = (uengine*)defines::system->get_outer_object(game_instance);
			render::font = engine->get_font();



			draw_transition_o = vmt<decltype(draw_transition_o)>(std::uintptr_t(viewport), std::uintptr_t(draw_transition), 113);
		}

	}
}