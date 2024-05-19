#pragma once
template <typename hook_type>
_declspec(noinline) hook_type vmt(std::uintptr_t address, std::uintptr_t hook_function, int index) {
	auto vtable = *(std::uintptr_t**)address;

	int vtable_size = 0;
	do vtable_size += 1;
	while (*(std::uintptr_t*)(std::uintptr_t(vtable) + (vtable_size * 8)));

	auto original_virtual_function = (void*)vtable[index];

	std::uintptr_t* fake_vtable = new std::uintptr_t[vtable_size * 8];

	for (int i = 0; i < vtable_size; i++) {
		if (i == index) continue;
		fake_vtable[i] = *(std::uintptr_t*)(std::uintptr_t(vtable) + (i * 8));
	} fake_vtable[index] = hook_function;

	*(std::uintptr_t**)address = fake_vtable;

	return hook_type(original_virtual_function);
}