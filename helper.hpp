#pragma once

template<typename T>
constexpr inline void set_userdata(lua_State* L, T* element) {
	*static_cast<T**>(lua_newuserdata(L, sizeof(T*))) = element;
}

template<typename T>
constexpr inline T* to_class_ptr(lua_State* L, int idx) {
	return *static_cast<T**>(lua_touserdata(L, idx));
}

void set_type(lua_State* L, const char* type_name) {
	lua_pushstring(L, type_name);

	lua_pushvalue(L, -1);
	lua_setfield(L, -3, "__type");

	lua_pushcclosure(L, [](lua_State* L) {
		lua_pushstring(L, lua_tostring(L, lua_upvalueindex(1)));
		return 1;
		}, 1);
	lua_setfield(L, -2, "__tostring");
}

void assign_to_parent(lua_State* L, lib::element* element) {
	lua_getmetatable(L, 2);
	lua_getfield(L, -1, "__type");

	const char* type = lua_tostring(L, -1);
	lua_pop(L, 2);

	if (strcmp(type, "Window") == 0) {
		auto window = to_class_ptr<lib::window>(L, 2);
		window->add_element(element);
	}
	else if (strcmp(type, "Tab") == 0) {
		auto tab = to_class_ptr<lib::tab>(L, 2);
		tab->add_element(element);
	}
}
