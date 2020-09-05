#pragma once

namespace lua_bind {
	void window(lua_State *L) {
		auto window = &windows.emplace_back(lua_tostring(L, 2));
		set_userdata<lib::window>(L, window);

		lua_newtable(L);

		lua_pushvalue(L, -2);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto window = to_class_ptr<lib::window>(L, lua_upvalueindex(1));

			lua_pop(L, 2);

			if (strcmp(idx, "Title") == 0) {
				lua_pushstring(L, window->get_title().c_str());
			}

			return 1;
			}, 1);
		lua_setfield(L, -2, "__index");

		lua_pushstring(L, "Window");
		lua_setfield(L, -2, "__type");

		lua_setmetatable(L, -2);
	}

	void button(lua_State *L) {
		bool same_line = !lua_isnil(L, 3) && lua_isboolean(L, 3) && lua_toboolean(L, 3);
		auto button = new lib::button(same_line);

		set_userdata<lib::button>(L, button);
		assign_to_parent(L, button);

		lua_newtable(L); // metatable 

		set_type(L, "Button");

		lua_pushlightuserdata(L, button);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto button = (lib::button*)lua_touserdata(L, lua_upvalueindex(1));

			lua_pop(L, 2);

			if (strcmp(idx, "Text") == 0) {
				lua_pushstring(L, button->get_text().c_str());
			}

			return 1;
			}, 1);
		lua_setfield(L, -2, "__index");

		lua_pushlightuserdata(L, button);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto button = (lib::button*)lua_touserdata(L, lua_upvalueindex(1));

			if (strcmp(idx, "Text") == 0) {
				button->set_text(lua_tostring(L, 3));
			}
			else if (strcmp(idx, "Callback") == 0) {
				int ref = luaL_ref(L, LUA_REGISTRYINDEX);

				button->set_callback([=]() {
					lua_rawgeti(l_G, LUA_REGISTRYINDEX, ref);
					lua_pcall(L, 0, 0, 0);
					});
			}

			return 0;
			}, 1);
		lua_setfield(L, -2, "__newindex");

		lua_setmetatable(L, -2);
	}

	void label(lua_State* L) {
		bool same_line = !lua_isnil(L, 3) && lua_isboolean(L, 3) && lua_toboolean(L, 3);
		auto label = new lib::label(same_line);

		set_userdata<lib::label>(L, label);
		assign_to_parent(L, label);

		lua_newtable(L); // metatable

		set_type(L, "Label");

		lua_pushlightuserdata(L, label);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto label = (lib::label*)lua_touserdata(L, lua_upvalueindex(1));

			lua_pop(L, 2);

			if (strcmp(idx, "Text") == 0) {
				lua_pushstring(L, label->get_text().c_str());
			}

			return 1;
			}, 1);
		lua_setfield(L, -2, "__index");

		lua_pushlightuserdata(L, label);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto label = (lib::label*)(lua_touserdata(L, lua_upvalueindex(1)));

			if (strcmp(idx, "Text") == 0) {
				label->set_text(lua_tostring(L, 3));
			}

			return 0;
			}, 1);
		lua_setfield(L, -2, "__newindex");

		lua_setmetatable(L, -2);
	}

	void check_box(lua_State *L) {
		bool same_line = !lua_isnil(L, 3) && lua_isboolean(L, 3) && lua_toboolean(L, 3);
		auto check_box = new lib::check_box(std::to_string(std::rand()).c_str(), same_line);

		set_userdata<lib::check_box>(L, check_box);
		assign_to_parent(L, check_box);

		lua_newtable(L);

		set_type(L, "Checkbox");

		lua_pushlightuserdata(L, check_box);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto check_box = (lib::check_box*)lua_touserdata(L, lua_upvalueindex(1));

			lua_pop(L, 2);

			if (strcmp(idx, "Checked") == 0) {
				lua_pushboolean(L, check_box->is_toggled());
			}
			else if (strcmp(idx, "Text") == 0) {
				lua_pushstring(L, check_box->get_text().c_str());
			}

			return 1;
			}, 1);
		lua_setfield(L, -2, "__index");

		lua_pushlightuserdata(L, check_box);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto check_box = (lib::check_box*)lua_touserdata(L, lua_upvalueindex(1));

			if (strcmp(idx, "Checked") == 0) {
				check_box->set_toggle(lua_toboolean(L, 3));
			}
			else if (strcmp(idx, "Text") == 0) {
				check_box->set_text(lua_tostring(L, 3));
			}
			else if (strcmp(idx, "Callback") == 0) {
				int ref = luaL_ref(L, LUA_REGISTRYINDEX);

				check_box->set_callback([=](bool toggled) {
					lua_rawgeti(l_G, LUA_REGISTRYINDEX, ref);
					lua_pushboolean(l_G, toggled);
					lua_pcall(l_G, 1, 0, 0);
				});
			}

			return 0;
			}, 1);
		lua_setfield(L, -2, "__newindex");

		lua_setmetatable(L, -2);
	}

	void slider(lua_State *L) {
		bool same_line = !lua_isnil(L, 3) && lua_isboolean(L, 3) && lua_toboolean(L, 3);
		auto slider = new lib::slider(std::to_string(std::rand()).c_str(), same_line);

		set_userdata<lib::slider>(L, slider);
		assign_to_parent(L, slider);

		lua_newtable(L);

		set_type(L, "Slider");

		lua_pushlightuserdata(L, slider);
		lua_pushcclosure(L, [](lua_State* L) { 
			const char* idx = lua_tostring(L, 2);
			auto slider = (lib::slider*)lua_touserdata(L, lua_upvalueindex(1));

			if (strcmp(idx, "Value")) {
				lua_pushnumber(L, slider->get());
			}
			else if (strcmp(idx, "Min") == 0) {
				lua_pushnumber(L, slider->get_min());
			}
			else if (strcmp(idx, "Max") == 0) {
				lua_pushnumber(L, slider->get_max());
			}
			else if (strcmp(idx, "Text") == 0) {
				lua_pushstring(L, slider->get_text().c_str());
			}

			return 1; 
		}, 1);
		lua_setfield(L, -2, "__index");

		lua_pushlightuserdata(L, slider);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto slider = (lib::slider*)lua_touserdata(L, lua_upvalueindex(1));

			if (strcmp(idx, "Min") == 0) {
				slider->set_min(lua_tonumber(L, 3));
			}
			else if (strcmp(idx, "Max") == 0) {
				slider->set_max(lua_tonumber(L, 3));
			}
			else if (strcmp(idx, "Text") == 0) {
				slider->set_text(lua_tostring(L, 3));
			}

			return 0;
			}, 1);
		lua_setfield(L, -2, "__newindex");

		lua_setmetatable(L, -2);
	}

	void color_picker(lua_State *L) {
		bool same_line = !lua_isnil(L, 3) && lua_isboolean(L, 3) && lua_toboolean(L, 3);
		auto color_picker = new lib::color_picker(same_line);

		set_userdata<lib::color_picker>(L, color_picker);
		assign_to_parent(L, color_picker);

		lua_newtable(L);

		set_type(L, "ColorPicker");

		lua_pushlightuserdata(L, color_picker);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto color_picker = (lib::color_picker*)lua_touserdata(L, lua_upvalueindex(1));

			lua_pop(L, 2);

			if (strcmp(idx, "PickedColor3") == 0) {
				lua_pushnil(L);
			}
			else if (strcmp(idx, "Text") == 0) {
				lua_pushstring(L, color_picker->get_text().c_str());
			}

			return 1;
			}, 1);
		lua_setfield(L, -2, "__index");

		lua_pushlightuserdata(L, color_picker);
		lua_pushcclosure(L, [](lua_State* L) {
			auto color_picker = (lib::color_picker*)lua_touserdata(L, lua_upvalueindex(1));

			if (strcmp(lua_tostring(L, 2), "Text") == 0) {
				color_picker->set_text(lua_tostring(L, 3));
			}

			return 0;
			}, 1);
		lua_setfield(L, -2, "__newindex");

		lua_setmetatable(L, -2);
	}

	void list_box(lua_State *L) {
		bool same_line = !lua_isnil(L, 3) && lua_isboolean(L, 3) && lua_toboolean(L, 3);
		auto list_box = new lib::combo_box(std::to_string(std::rand()).c_str(), same_line);
		
		set_userdata<lib::combo_box>(L, list_box);
		assign_to_parent(L, list_box);

		lua_newtable(L); // metatable

		set_type(L, "ListBox");

		lua_pushvalue(L, -2);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto list_box = (lib::combo_box*)lua_touserdata(L, lua_upvalueindex(1));

			//lua_pop(L, 2);

			if (strcmp(idx, "Text") == 0) {
				lua_pushstring(L, list_box->get_text().c_str());
			}
			else if (strcmp(idx, "Add") == 0) {
				lua_pushcclosure(L, [](lua_State *L) {
					auto list_box = to_class_ptr<lib::combo_box>(L, 1);
					list_box->add(lua_tostring(L, 2));
					return 0;
				}, 0);
			}
			else if (strcmp(idx, "Remove") == 0) {
				lua_pushcclosure(L, [](lua_State* L) {
					auto list_box = to_class_ptr<lib::combo_box>(L, 1);
					list_box->remove(lua_tostring(L, 2));
					return 0;
				}, 0);
			}

			return 1;
		}, 1);
		lua_setfield(L, -2, "__index");

		lua_pushvalue(L, -2);
		lua_pushcclosure(L, [](lua_State *L) {
			const char* idx = lua_tostring(L, 2);
			auto list_box = (lib::combo_box*)lua_touserdata(L, lua_upvalueindex(1));

			if (strcmp(idx, "Text") == 0) {
				list_box->set_text(lua_tostring(L, 3));
			}
			else if (strcmp(idx, "Callback") == 0) {
				int ref = luaL_ref(L, LUA_REGISTRYINDEX);

				list_box->set_callback([=](const char* selected) {
					lua_rawgeti(l_G, LUA_REGISTRYINDEX, ref);
					lua_pushstring(L, selected);
					lua_pcall(L, 1, 0, 0);
				});
			}

			return 0;
		}, 1);
		lua_setfield(L, -2, "__newindex");

		lua_setmetatable(L, -2);
	}

	int tab(lua_State *L) {
		auto tab_selector = to_class_ptr<lib::tab_selector>(L, 1);
		auto tab = tab_selector->add_tab(lua_tostring(L, 2));

		lua_pop(L, 2);

		set_userdata<lib::tab>(L, tab);

		lua_newtable(L);

		set_type(L, "Tab");

		lua_pushvalue(L, -2);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto tab = to_class_ptr<lib::tab>(L, lua_upvalueindex(1));

			lua_pop(L, 2);

			if (strcmp(idx, "Text")) {
				lua_pushstring(L, tab->get_title().c_str());
			}

			return 1;
			}, 1);
		lua_setfield(L, -2, "__index");

		lua_pushvalue(L, -2);
		lua_pushcclosure(L, [](lua_State* L) {
			const char* idx = lua_tostring(L, 2);
			auto tab = to_class_ptr<lib::tab>(L, lua_upvalueindex(1));

			if (strcmp(idx, "Text")) {
				tab->set_title(lua_tostring(L, 3));
			}

			return 0;
			}, 1);
		lua_setfield(L, -2, "__newindex");

		lua_setmetatable(L, -2);
		return 1;
	}

	void tab_selector(lua_State* L) {
		bool same_line = !lua_isnil(L, 3) && lua_isboolean(L, 3) && lua_toboolean(L, 3);
		auto tab_selector = new lib::tab_selector(std::to_string(std::rand()).c_str(), same_line);

		set_userdata<lib::tab_selector>(L, tab_selector);
		assign_to_parent(L, tab_selector);

		lua_newtable(L);

		set_type(L, "TabSelector");

		lua_pushvalue(L, -2);
		lua_pushcclosure(L, [](lua_State* L) {
			if (strcmp(lua_tostring(L, 2), "AddTab") == 0) {
				lua_pushvalue(L, lua_upvalueindex(1));
				lua_pushcclosure(L, tab, 1);
			}
			return 1;
		}, 1);
		lua_setfield(L, -2, "__index");

		lua_setmetatable(L, -2);
	}

	void init() {
		lua_newtable(l_G);
		lua_pushcclosure(l_G, [](lua_State* L) {
			if (lua_isstring(L, 1)) {
				const char* element = lua_tostring(L, 1);

				if (strcmp(element, "Window") == 0) {
					lua_bind::window(L);
				}
				else if (strcmp(element, "Button") == 0) {
					lua_bind::button(L);
				}
				else if (strcmp(element, "Label") == 0) {
					lua_bind::label(L);
				}
				else if (strcmp(element, "Checkbox") == 0) {
					lua_bind::check_box(L);
				}
				else if (strcmp(element, "Slider") == 0) {
					lua_bind::slider(L);
				}
				else if (strcmp(element, "ColorPicker") == 0) {
					lua_bind::color_picker(L);
				}
				else if (strcmp(element, "ListBox") == 0) {
					lua_bind::list_box(L);
				}
				else if (strcmp(element, "TabSelector") == 0) {
					lua_bind::tab_selector(L);
				}
			}

			return 1;
			}, 0);
		lua_setfield(l_G, -2, "new");
		lua_setglobal(l_G, "ImGui");
	}
}
