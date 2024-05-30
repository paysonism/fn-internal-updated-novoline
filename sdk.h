#pragma once
#include "vector.h"


enum offsets : std::int32_t {
	BoneMatrix = 0x19A205C, // updated for v30.00
	StaticFindObject = 0x16CC96C, // updated for v30.00
	CurrentVehicle = 0x2960,
	LastFireTime = 0xC50,
	LastFireTimeVerified = 0xC54,
	CustomTimeDilation = 0x64,
	GlobalAnimRateScale = 0xa18,
	Mesh = 0x318,
	bIsReloadingWeapon = 0x388,
	VehicleAttributes = 0x10C8,
	CachedSpeed = 0xCEC,
	TopSpeedCurrentMultiplier = 0x968,
	PushForceCurrentMultiplier = 0x96C,
	WaterEffectsVehicleMaxSpeedKmh = 0x7FC,
	bAdsWhileNotOnGround = 0x5468,
	bDisableEquipAnimation = 0x362,
	bIgnoreTryToFireSlotCooldownRestriction = 0x12C9,
	ZiplineState = 0x24E0,
	TriggerType = 0xB4C,
	WeaponData = 0x500,
};


enum fort_item_tier : std::uint8_t {
	No_Tier = 0,
	I = 1,
	II = 2,
	III = 3,
	IV = 4,
	V = 5,
	VI = 6,
	VII = 7,
	VIII = 8,
	IX = 9,
	X = 10,
	NumItemTierValues = 11,
	EFortItemTier_MAX = 12
};

struct ftextdata {
	char pad_0[0x38];
	wchar_t* name;
	__int32 length;
};

struct ftext {
	ftextdata* data;
	char pad_0[0x10];

	wchar_t* c_str() const {
		if (this->data) {
			return data->name;
		}

		return nullptr;
	}
};

template <class type>
struct tarray {
public:
	tarray() { this->data = nullptr; this->count = this->max = 0; };

	type* data;
	std::int32_t count, max;

	type& operator[](int i) {
		return this->data[i];
	};

	int size() {
		return this->count;
	}

	bool valid(int i) {
		return bool(i < this->count);
	}
};

struct fstring : private tarray<wchar_t> {
	fstring() { };
	fstring(const wchar_t* other) {
		this->max = this->count = *other ? static_cast<int>(std::wcslen(other)) + 1 : 0;

		if (this->count)
			this->data = const_cast<wchar_t*>(other);
	};

	wchar_t* c_str() {
		return this->data;
	}

	bool valid() {
		return this->data != nullptr;
	}
};

struct fmatrix {
	double m[4][4];
};

struct fvector {
	fvector() : x(), y(), z() { }
	fvector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { }

	double x, y, z;

	operator bool() { return bool(this->x && this->y && this->z); }
	bool operator==(fvector in) { return bool(this->x == in.x && this->y == in.y && this->z == in.z); }
	fvector operator+(fvector in) { return fvector(this->x + in.x, this->y + in.y, this->z + in.z); }
	fvector operator-(fvector in) { return fvector(this->x - in.x, this->y - in.y, this->z - in.z); }
};

struct fvector2d {
	fvector2d() : x(), y() { }
	fvector2d(double _x, double _y) : x(_x), y(_y) { }

	double x, y;

	operator bool() { return bool(this->x && this->y); }
	bool operator==(fvector2d in) { return bool(this->x == in.x && this->y == in.y); }
	fvector2d operator+(fvector2d in) { return fvector2d(this->x + in.x, this->y + in.y); }
	fvector2d operator-(fvector2d in) { return fvector2d(this->x - in.x, this->y - in.y); }
};

struct frotator {
	frotator() : pitch(), yaw(), roll() { }
	frotator(double _pitch, double _yaw, double _roll) : pitch(_pitch), yaw(_yaw), roll(_roll) { }

	double pitch, yaw, roll;

	operator bool() { return bool(this->pitch && this->yaw); }
	bool operator==(frotator in) { return bool(this->pitch == in.pitch && this->yaw == in.yaw && this->roll == in.roll); }
	frotator operator+(frotator in) { return frotator(this->pitch + in.pitch, this->yaw + in.yaw, this->roll + in.roll); }
	frotator operator-(frotator in) { return frotator(this->pitch - in.pitch, this->yaw - in.yaw, this->roll - in.roll); }
};

struct flinearcolor {
	flinearcolor() : r(), g(), b(), a() { }
	flinearcolor(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) { }

	float r, g, b, a;

	operator bool() { return bool(this->r || this->g || this->b || this->a); }
	bool operator==(flinearcolor in) { return bool(this->r == in.r && this->g == in.g && this->b == in.b && this->a == in.a); }
};

struct fminimalviewinfo {
	fvector location;
	frotator rotation;
	float fov;
};

struct fname {
	fname() : index() { }
	fname(std::uint32_t _index) : index(_index) { }

	std::uint32_t index;
};

struct fkey {
	fname name;
	std::uint8_t details[20];
};



class uobject {
public:
	fname get_name() {
		return read<fname>(std::uintptr_t(this) + 0x18);
	}
	static uobject* find_object(const wchar_t* name, uobject* outer = nullptr) {
		return reinterpret_cast<uobject*>(uobject::static_find_objecttwo(nullptr, outer, name));
	}

	static uobject* static_find_objecttwo(uobject* klass, uobject* outer, const wchar_t* name) {
		return reinterpret_cast<uobject * (*)(uobject*, uobject*, const wchar_t*)>(game + offsets::StaticFindObject)(klass, outer, name);
	}

	static uobject* static_find_object(uobject* klass, uobject* outer, const wchar_t* name, bool exact) {
		return reinterpret_cast<uobject * (*)(uobject*, uobject*, const wchar_t*, bool)>(game + offsets::StaticFindObject)(klass, outer, name, exact);
	}
	void process_event(uobject* function, void* args) {
		auto vtable = *reinterpret_cast<void***>(this);
		reinterpret_cast<void(*)(void*, void*, void*)>(vtable[77])(this, function, args);
	}
};


class ucanvas : public uobject {
public:
	float clip_x() {
		return read<float>(std::uintptr_t(this) + 0x30); //maybe wrong
	}

	float clip_y() {
		return read<float>(std::uintptr_t(this) + 0x34); //maybe wrong
	}

	fvector2d k2_text_size(uobject* render_font, fstring render_text, fvector2d scale) {
		struct {
			uobject* render_font;
			fstring render_text;
			fvector2d scale;
			fvector2d return_value;
		} params = { render_font, render_text, scale };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Canvas.K2_TextSize", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	void k2_draw_text(uobject* render_font, fstring render_text, fvector2d screen_position, fvector2d scale, flinearcolor render_color, float kerning, flinearcolor shadow_color, fvector2d shadow_offset, bool center_x, bool center_y, bool outlined, flinearcolor outline_color) {
		struct {
			uobject* render_font;
			fstring render_text;
			fvector2d screen_position;
			fvector2d scale;
			flinearcolor render_color;
			float kerning;
			flinearcolor shadow_color;
			fvector2d shadow_offset;
			bool center_x;
			bool center_y;
			bool outlined;
			flinearcolor outline_color;
		} params = { render_font, render_text, screen_position, scale, render_color, kerning, shadow_color, shadow_offset, center_x, center_y, outlined, outline_color };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Canvas.K2_DrawText", false);
		this->process_event(function, &params);
	}

	void k2_draw_line(fvector2d screen_position_a, fvector2d screen_position_b, float thickness, flinearcolor render_color) {
		struct {
			fvector2d screen_position_a;
			fvector2d screen_position_b;
			float thickness;
			flinearcolor render_color;
		} params = { screen_position_a, screen_position_b, thickness, render_color };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Canvas.K2_DrawLine", false);
		this->process_event(function, &params);
	}
};

class uworld : public uobject {
public:

};

class uengine : public uobject {
public:
	uobject* get_font() {
		return read<uobject*>(std::uintptr_t(this) + 0x70);
	}
};

class ugameviewportclient : public uobject {
public:
	uworld* get_world() {
		return read<uworld*>(std::uintptr_t(this) + 0x78);
	}
};

class item_definition : public uobject {
public:
	//enum class EFortItemTier Tier; // 0x74(0x01)
	fort_item_tier get_tier() {
		return read<fort_item_tier>(std::uintptr_t(this) + 0x73);
	}

	ftext display_name() {
		return read<ftext>(std::uintptr_t(this) + 0x98);
	}
};


struct fortitementry { //0x1a0
	char pad_0[0x18];
	item_definition* item_def;
	char pad_1[0x180];
};

class weapon : public uobject {
public:

	std::int32_t get_magazine_ammo_count() {
		struct {
			std::int32_t return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortWeapon.GetMagazineAmmoCount", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	std::int32_t get_bullets_per_clip() {
		struct {
			std::int32_t return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortWeapon.GetBulletsPerClip", false);
		this->process_event(function, &params);
		return params.return_value;
	}


	item_definition* get_weapon_data() {
		struct {
			item_definition* return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortWeapon.GetWeaponData", false);
		this->process_event(function, &params);
		return params.return_value;
	}
};

class mesh : public uobject {
public:
	std::int32_t get_num_bones() {
		struct {
			std::int32_t return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"SkinnedMeshComponent.GetNumBones", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	fvector get_bone_location(std::int32_t index) {
		fmatrix out_matrix = { };
		reinterpret_cast<fmatrix* (*)(mesh*, fmatrix*, std::int32_t)>(game + offsets::BoneMatrix)(this, &out_matrix, index);

		return fvector(out_matrix.m[3][0], out_matrix.m[3][1], out_matrix.m[3][2]);
	}
};

class actor : public uobject {
public:
	void enable_input(uobject* playercontroller) {
		struct {
			uobject* playercontroller;
		} params = { playercontroller };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Actor.EnableInput", false);
		this->process_event(function, &params);
	}

	bool set_actor_location(fvector new_location, bool sweep, uint8_t sweep_hit_result, bool teleport) {
		static uobject* function;
		if (!function)
			function = uobject::static_find_object(0, 0, L"Actor.K2_SetActorLocation", false);

		struct { fvector a1; bool a2; uint8_t a3; bool a4; bool ret; } params;
		params.a1 = new_location;
		params.a2 = sweep;
		params.a3 = sweep_hit_result;
		params.a4 = teleport;

		this->process_event(function, &params);
		return params.ret;
	}
	
	bool k2_teleport_to(const fvector& DestLocation, const frotator& DestRotation) {
		static uobject* function;
		if (!function)
			function = uobject::static_find_object(0, 0, L"Actor.K2_TeleportTo", false);


		struct
		{
			fvector										DestLocation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			frotator										DestRotation;                                             // (Parm, ZeroConstructor, IsPlainOldData)
			bool										ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;
		params.DestLocation = DestLocation;
		params.DestRotation = DestRotation;

		this->process_event(function, &params);
		return params.ReturnValue;
	}

	char get_team() {
		static uobject* function = 0;
		if (!function)
			function = uobject::static_find_object(0, 0, L"FortniteGame.FortPawn.GetTeam", false);

		if (function == nullptr) return false;

		struct
		{
			char return_value;
		} params = { };

		this->process_event(function, &params);

		return params.return_value;
	}

	void disable_input(uobject* playercontroller) {
		struct {
			uobject* playercontroller;
		} params = { playercontroller };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Actor.DisableInput", false);
		this->process_event(function, &params);
	}

	bool was_recently_rendered(float tolerance) {
		struct {
			float tolerance;
			bool return_value;
		} params = { tolerance };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Actor.WasRecentlyRendered", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	bool set_actor_rotation(frotator new_rotation, bool teleport_physics) {
		struct {
			frotator new_rotation;
			bool teleport_physics;
			bool return_value;
		} params = { new_rotation, teleport_physics };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Actor.K2_SetActorRotation", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	bool set_actor_location2(Vector3 new_location, bool sweep, uint8_t sweep_hit_result, bool teleport) {
		static uobject* function;
		if (!function)
			function = uobject::static_find_object(0, 0, L"Actor.K2_SetActorLocation", false);

		struct { Vector3 a1; bool a2; uint8_t a3; bool a4; bool ret; } params;
		params.a1 = new_location;
		params.a2 = sweep;
		params.a3 = sweep_hit_result;
		params.a4 = teleport;

		this->process_event(function, &params);
		return params.ret;
	}


	bool k2_set_actor_location_and_rotation(const fvector& new_location, const frotator& new_rotation, bool b_sweep, bool b_teleport) {
		static uobject* function;
		if (!function)
			function = uobject::static_find_object(0, 0, L"Actor.K2_SetActorLocationAndRotation", false);

		struct aactor_k2_set_actor_location_and_rotation_params
		{
			fvector new_location; // (Parm, ZeroConstructor, IsPlainOldData)
			frotator new_rotation; // (Parm, ZeroConstructor, IsPlainOldData)
			bool b_sweep; // (Parm, ZeroConstructor, IsPlainOldData)
			int sweep_hit_result; // (Parm, OutParm, IsPlainOldData)
			bool b_teleport; // (Parm, ZeroConstructor, IsPlainOldData)
			bool return_value; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		};

		aactor_k2_set_actor_location_and_rotation_params params{};
		params.new_location = new_location;
		params.new_rotation = new_rotation;
		params.b_sweep = b_sweep;
		params.b_teleport = b_teleport;

		this->process_event(function, &params);
		return params.return_value;
	}

	frotator get_actor_rotation() {
		struct {
			frotator return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Actor.K2_GetActorRotation", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	fvector get_actor_location() {
		struct {
			fvector return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Actor.K2_GetActorLocation", false);
		this->process_event(function, &params);
		return params.return_value;
	}
};

struct container_struct_0x102a {
	char bForceSpawnLootOnDestruction : 1; // 0x102a(0x01)
	char bForceTossLootOnSpawn : 1; // 0x102a(0x01)
	char bAlreadySearched : 1; // 0x102a(0x01)
	char bGivePickupsDirectlyToPlayer : 1; // 0x102a(0x01)
	char bDoNotDropLootOnDestruction : 1; // 0x102a(0x01)
	char bSkipRollForDestruction : 1; // 0x102a(0x01)
	char pad_102A_6 : 2; // 0x102a(0x01)
};

class container_actor : public actor {
public:
	bool already_searched() {
		return read<container_struct_0x102a>(std::uintptr_t(this) + 0xeea).bAlreadySearched;
	}
};

class afortvehicle : public actor {
public:


};

class flag_actor : public actor {
public:


};

class trap_actor : public actor {
public:


};

class rift_actor : public actor {
public:


};

class vehicle_actor : public actor {
public:
	fstring get_display_name() {
		struct {
			fstring return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortAthenaVehicle.GetDisplayName", false);
		this->process_event(function, &params);
		return params.return_value;
	}
};

class pickup_actor : public actor {
public:
	item_definition* get_item_definition() {
		return read<item_definition*>(std::uintptr_t(this) + 0x338 + 0x18);
	}
};

struct weakspot_struft_0x2b8 {
	char bHit : 1; // 0x2b8(0x01)
	char bFadeOut : 1; // 0x2b8(0x01)
	char bActive : 1; // 0x2b8(0x01)
	char pad_2B8_3 : 5; // 0x2b8(0x01)
};

class weakspot_actor : public actor {
public:
	bool is_active() {
		weakspot_struft_0x2b8 weakspot_struct = read<weakspot_struft_0x2b8>(std::uintptr_t(this) + 0x2b8);
		return weakspot_struct.bActive;
	}
};


class player_pawn : public actor {
public:

	mesh* get_pawn_mesh() {
		return read<mesh*>(std::uintptr_t(this) + offsets::Mesh);
	}

	bool is_in_vehicle() {
		//IsInVehicle
		static uobject* function;
		if (!function)
			function = uobject::static_find_object(0, 0, L"FortPlayerPawn.IsInVehicle", false);

		struct { bool ret; } params;

		this->process_event(function, &params);
		return params.ret;
	}

	bool is_dead() {
		struct {
			bool return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortPawn.IsDead", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	bool is_dbno() {
		struct {
			bool return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortPawn.IsDBNO", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	char get_team() {
		struct {
			char return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortPawn.GetTeam", false);
		this->process_event(function, &params);
		return params.return_value;
	}


	weapon* get_current_weapon() {
		struct {
			weapon* return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortPawn.GetCurrentWeapon", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	afortvehicle* get_current_vehicle() {
		struct {
			afortvehicle* return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortPlayerPawn.GetVehicle", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	

};

class aplayercontroller : public uobject {
public:
	float input_pitch_scale() {
		return read<float>(std::uintptr_t(this) + 0x534);
	}

	float input_yaw_scale() {
		return read<float>(std::uintptr_t(this) + 0x530);
	}

	bool is_key_down(fkey key) {
		struct {
			fkey key;
			bool return_value;
		} params = { key };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerController.IsInputKeyDown", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	static bool is_visible(aplayercontroller* PlayerController, player_pawn* Pawn, fvector* ViewPoint)
	{

		auto subIsVisible = reinterpret_cast<bool(__fastcall*)(aplayercontroller * PlayerController, player_pawn * Pawn, fvector * ViewPoint)>(0x7857C3C); 
		return subIsVisible(PlayerController, Pawn, ViewPoint);

	}


	bool LineOfSightTo(class actor* Other, const struct fvector& ViewPoint)
	{
		struct
		{
			class actor* Other;                                                    // (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
			struct fvector                                    ViewPoint;                                                // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               bAlternateChecks;                                         // (Parm, ZeroConstructor, IsPlainOldData)
			bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
		} params;

		params.Other = Other;
		params.ViewPoint = ViewPoint;
		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Function Engine.Controller.LineOfSightTo", false);
		this->process_event(function, &params);
		return params.ReturnValue;
	}



	bool w2s(fvector world_location, fvector2d* screen_location) {
		struct {
			fvector world_location;
			fvector2d screen_location;
			bool return_value;
		} params = { world_location, fvector2d(), true };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerController.ProjectWorldLocationToScreen", false);
		this->process_event(function, &params);
		*screen_location = params.screen_location;
		return params.return_value;
	}

	player_pawn* get_pawn() {
		struct {
			player_pawn* return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"Controller.K2_GetPawn", false);
		this->process_event(function, &params);
		return params.return_value;
	}



	fvector2d get_mouse_position() {
		struct {
			float x;
			float y;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerController.GetMousePosition", false);
		this->process_event(function, &params);
		return fvector2d((double)params.x, (double)params.y);
	}

	void add_pitch_input(float val) {
		struct {
			float val;
		} params = { val };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerController.AddPitchInput", false);
		this->process_event(function, &params);
	}

	void add_yaw_input(float val) {
		struct {
			float val;
		} params = { val };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerController.AddYawInput", false);
		this->process_event(function, &params);
	}


	void fov(float NewFOV) {
		struct {
			float NewFOV; 
		} params = { NewFOV };
		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerController.FOV", false);
		params.NewFOV = NewFOV;
		this->process_event(function, &params);
	}

};

class ulocalplayer : public uobject {
public:
	ugameviewportclient* get_viewport() {
		return read<ugameviewportclient*>(std::uintptr_t(this) + 0x78);
	}
};

class ugameinstance : public uobject {
public:
	tarray<ulocalplayer*> get_local_players() {
		return read<tarray<ulocalplayer*>>(std::uintptr_t(this) + 0x38);
	}
};

class camera_manager : public uobject {
public:
	//struct FRotator GetCameraRotation(); // Function Engine.PlayerCameraManager.GetCameraRotation

	//struct FVector GetCameraLocation(); // Function Engine.PlayerCameraManager.GetCameraLocation

	frotator get_camera_rotation() {
		struct {
			frotator return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerCameraManager.GetCameraRotation", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	fvector get_camera_location() {
		struct {
			fvector return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerCameraManager.GetCameraLocation", false);
		this->process_event(function, &params);
		return params.return_value;
	}

	float get_fov_angle() {
		struct {
			float return_value;
		} params = { };

		static uobject* function;
		if (!function) function = uobject::static_find_object(nullptr, nullptr, L"PlayerCameraManager.GetFOVAngle", false);
		this->process_event(function, &params);
		return params.return_value;
	}
};

namespace library {
	class lib_game_statics : public uobject {
	public:
		tarray<uobject*> get_all_actors_of_class(uobject* world_context_object, uobject* actor_class) {
			struct {
				uobject* world_context_object;
				uobject* actor_class;
				tarray<uobject*> out_actors;
			} params = { world_context_object, actor_class };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"GameplayStatics.GetAllActorsOfClass", false);
			this->process_event(function, &params);
			return params.out_actors;
		}

		ugameinstance* get_game_instance(uobject* world_context_object) {
			struct {
				uobject* world_context_object;
				ugameinstance* return_value;
			} params = { world_context_object };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"GameplayStatics.GetGameInstance", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		aplayercontroller* get_player_controller(uobject* world_context_object, std::int32_t player_index) {
			struct {
				uobject* world_context_object;
				std::int32_t player_index;
				aplayercontroller* return_value;
			} params = { world_context_object, player_index };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"GameplayStatics.GetPlayerController", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double get_world_delta_seconds(uobject* world_context_object) {
			struct {
				uobject* world_context_object;
				double return_value;
			} params = { world_context_object };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"GameplayStatics.GetWorldDeltaSeconds", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		camera_manager* get_player_camera_manager(uobject* world_context_object, std::int32_t player_index) {
			struct {
				uobject* world_context_object;
				std::int32_t player_index;
				camera_manager* return_value;
			} params = { world_context_object, player_index };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"GameplayStatics.GetPlayerCameraManager", false);
			this->process_event(function, &params);
			return params.return_value;
		}
	};

	class lib_system : public uobject {
	public:
		fstring get_object_name(uobject* object) {
			struct {
				uobject* object;
				fstring return_value;
			} params = { object };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetSystemLibrary.GetObjectName", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		const char* get_object_name_char(uobject* object) {
			struct {
				uobject* object;
				const char* return_value;
			} params = { object };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetSystemLibrary.GetObjectName", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		uobject* get_outer_object(uobject* object) {
			struct {
				uobject* object;
				uobject* return_value;
			} params = { object };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetSystemLibrary.GetOuterObject", false);
			this->process_event(function, &params);
			return params.return_value;
		}
	};

	class lib_lib : public uobject {
	public:
		fstring get_player_name_safe(actor* actor, uobject* playernameprivate) {
			struct {
				uobject* actor;
				fstring return_value;
			} params = { actor };

			static uobject* function;
			if (!function) function = playernameprivate;
			this->process_event(function, &params);
			return params.return_value;
		}
	};

	class lib_string : public uobject {
	public:
		fname string_to_name(fstring in_string) {
			struct {
				fstring in_string;
				fname return_value;
			} params = { in_string };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetStringLibrary.Conv_StringToName", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		fstring build_string_double(fstring append_to, fstring prefix, double in_double, fstring suffix) {
			struct {
				fstring append_to;
				fstring prefix;
				double in_double;
				fstring suffix;
				fstring return_value;
			} params = { append_to, prefix, in_double, suffix };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetStringLibrary.BuildString_Double", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		fstring build_string_int(fstring append_to, fstring prefix, std::int32_t in_int, fstring suffix) {
			struct {
				fstring append_to;
				fstring prefix;
				std::int32_t in_int;
				fstring suffix;
				fstring return_value;
			} params = { append_to, prefix, in_int, suffix };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetStringLibrary.BuildString_Int", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		fstring concat_str_str(fstring a, fstring b) {
			struct {
				fstring a;
				fstring b;
				fstring return_value;
			} params = { a, b };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetStringLibrary.Concat_StrStr", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		bool contains(fstring search_in, fstring sub_string, bool use_case, bool search_from_end) {
			struct {
				fstring search_in;
				fstring sub_string;
				bool use_case;
				bool search_from_end;
				bool return_value;
			} params = { search_in, sub_string, use_case, search_from_end };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetStringLibrary.Contains", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		fstring to_upper(fstring source_string) {
			struct {
				fstring search_in;
				fstring return_value;
			} params = { source_string };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetStringLibrary.ToUpper", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		fstring to_lower(fstring source_string) {
			struct {
				fstring search_in;
				fstring return_value;
			} params = { source_string };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetStringLibrary.ToLower", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		bool equal(fstring a, fstring b) {
			struct {
				fstring a;
				fstring b;
				bool return_value;
			} params = { a, b };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetStringLibrary.EqualEqual_StrStr", false);
			this->process_event(function, &params);
			return params.return_value;
		}
	};

	class lib_text : public uobject {
	public:
		//struct FString Conv_TextToString(struct FText& InText); // Function Engine.KismetTextLibrary.Conv_TextToString
	};

	class lib_math : public uobject {
	public:
		double round(double value) {
			return std::round(value);
		}

		double distance2d(fvector2d v1, fvector2d v2) {
			struct {
				fvector2d v1;
				fvector2d v2;
				double return_value;
			} params = { v1, v2 };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.Distance2D", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double abs(double a) {
			struct {
				double a;
				double return_value;
			} params = { a };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.abs", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double sin(double a) {
			struct {
				double a;
				double return_value;
			} params = { a };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.sin", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double cos(double a) {
			struct {
				double a;
				double return_value;
			} params = { a };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.cos", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double tan(double a) {
			struct {
				double a;
				double return_value;
			} params = { a };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.tan", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double asin(double a) {
			struct {
				double a;
				double return_value;
			} params = { a };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.asin", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double acos(double a) {
			struct {
				double a;
				double return_value;
			} params = { a };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.acos", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double atan(double a) {
			struct {
				double a;
				double return_value;
			} params = { a };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.atan", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double atan2(double y, double x) {
			struct {
				double y;
				double x;
				double return_value;
			} params = { y, x };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.Atan2", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double vector_distance(fvector v1, fvector v2) {
			struct {
				fvector v1;
				fvector v2;
				double return_value;
			} params = { v1, v2 };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.Vector_Distance", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		frotator find_look_at_rotation(fvector start, fvector target) {
			struct {
				fvector start;
				fvector target;
				frotator return_value;
			} params = { start, target };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.FindLookAtRotation", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		double f_interp_to(double current, double target, double delta_time, double interp_speed) {
			struct {
				double current;
				double target;
				float delta_time;
				float interp_speed;
				frotator return_value;
			} params = { current, target, delta_time, interp_speed };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.FInterpTo", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		frotator interp_to(frotator current, frotator target, float delta_time, float interp_speed) {
			struct {
				frotator current;
				frotator target;
				float delta_time;
				float interp_speed;
				frotator return_value;
			} params = { current, target, delta_time, interp_speed };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.RInterpTo", false);
			this->process_event(function, &params);
			return params.return_value;
		}

		frotator interp_to_constant(frotator current, frotator target, float delta_time, float interp_speed) {
			struct {
				frotator current;
				frotator target;
				float delta_time;
				float interp_speed;
				frotator return_value;
			} params = { current, target, delta_time, interp_speed };

			static uobject* function;
			if (!function) function = uobject::static_find_object(nullptr, nullptr, L"KismetMathLibrary.RInterpTo_Constant", false);
			this->process_event(function, &params);
			return params.return_value;
		}
	};
}



namespace defines {
	static library::lib_game_statics* game_statics = nullptr;
	static library::lib_system* system = nullptr;
	static library::lib_string* string = nullptr;
	static library::lib_text* text = nullptr;
	static library::lib_math* math = nullptr;
	static library::lib_lib* lib = nullptr;

	static uobject* actor_player_class = nullptr;
	static uobject* actor_vehicle_class = nullptr;
	static uobject* actor_container_class = nullptr;
	static uobject* actor_pickup_class = nullptr;
	static uobject* actor_weakspot_class = nullptr;
	static uobject* actor_projectile_class = nullptr;
	static uobject* actor_rift_class = nullptr;
	static uobject* actor_marker_class = nullptr;
	static uobject* actor_flag_class = nullptr;
	static uobject* actor_trap_class = nullptr;
	static uobject* actor_player_nameprivate = nullptr;
	static uobject* actor_get_vehicle = nullptr;
	static uobject* mapmarkertest = nullptr;
	static fkey insert = fkey();
	static fkey space = fkey();
	static fkey enter = fkey();
	static fkey W = fkey();
	static fkey A = fkey();
	static fkey S = fkey();
	static fkey D = fkey();
	static fkey left_mouse_button = fkey();
	static fkey right_mouse_button = fkey();
	static fkey caps_lock = fkey();
	static fkey LShift = fkey();


	static bool init() {
		defines::game_statics = (library::lib_game_statics*)uobject::static_find_object(nullptr, nullptr, L"Engine.Default__GameplayStatics", false);
		defines::system = (library::lib_system*)uobject::static_find_object(nullptr, nullptr, L"Engine.Default__KismetSystemLibrary", false);
		defines::string = (library::lib_string*)uobject::static_find_object(nullptr, nullptr, L"Engine.Default__KismetStringLibrary", false);
		defines::text = (library::lib_text*)uobject::static_find_object(nullptr, nullptr, L"Engine.Default__KismetTextLibrary", false);
		defines::math = (library::lib_math*)uobject::static_find_object(nullptr, nullptr, L"Engine.Default__KismetMathLibrary", false);
		defines::lib = (library::lib_lib*)uobject::static_find_object(nullptr, nullptr, L"FortniteGame.Default__FortKismetLibrary", false);

		defines::actor_player_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortPlayerPawn", false);
		defines::actor_vehicle_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortAthenaVehicle", false);
		defines::actor_container_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.BuildingContainer", false);
		defines::actor_pickup_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortPickup", false);
		defines::actor_weakspot_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.BuildingWeakSpot", false);
		defines::actor_projectile_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortProjectileBase", false);
		defines::actor_rift_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortAthenaRiftPortal", false);
		defines::actor_marker_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortWorldMarker", false);
		defines::actor_flag_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortFlag", false);
		defines::actor_trap_class = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.BuildingTrap", false);
		defines::actor_player_nameprivate = uobject::static_find_object(nullptr, nullptr, L"FortKismetLibrary.GetPlayerNameSafe", false);
		defines::actor_get_vehicle = uobject::static_find_object(nullptr, nullptr, L"FortniteGame.FortPlayerPawn.GetVehicle", false);
		defines::mapmarkertest = uobject::static_find_object(nullptr, nullptr, L"AthenaPlayerMarker_WithCustomization", false);


		defines::insert = fkey{ defines::string->string_to_name(L"Insert"), 0 };
		defines::space = fkey{ defines::string->string_to_name(L"SpaceBar"), 0 };
		defines::enter = fkey{ defines::string->string_to_name(L"Enter"), 0 };
		defines::W = fkey{ defines::string->string_to_name(L"W"), 0 };
		defines::A = fkey{ defines::string->string_to_name(L"A"), 0 };
		defines::S = fkey{ defines::string->string_to_name(L"S"), 0 };
		defines::D = fkey{ defines::string->string_to_name(L"D"), 0 };
		defines::LShift = fkey{ defines::string->string_to_name(L"LeftShift"), 0 };
		defines::left_mouse_button = fkey{ defines::string->string_to_name(L"LeftMouseButton"), 0 };
		defines::right_mouse_button = fkey{ defines::string->string_to_name(L"RightMouseButton"), 0 };
		defines::caps_lock = fkey{ defines::string->string_to_name(L"CapsLock"), 0 };

		return true;
	}
}