#pragma once

#include <list>
#include <array>
#include <string>

#include <functional>

//#include <imgui.h>

namespace lib {
	class element {
	public:
		virtual void render() = 0;

		bool operator==(const element& other) {
			return this == &other;
		}
	};

	class window {
	private:
		std::string _title;
		ImVec4 _active_color;
		ImVec4 _dropdown_hover_color;
		ImVec4 _dropdown_active_color;

		std::list<element*> elements;
	public:
		void render() {

			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, _active_color);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, _dropdown_active_color);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, _dropdown_hover_color);
			
			ImGui::Begin(_title.c_str(), nullptr);
				
			if (ImGui::IsWindowHovered()) {
				ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
			}
			else {
				ImGui::SetMouseCursor(ImGuiMouseCursor_None);
			}

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

			for (auto element : elements) {
				element->render();
			}

			ImGui::End();
		}

		window(const char* title)
			: _title(title),
			_active_color(ImVec4(0.16f, 0.29f, 0.48f, 1.00f)),
			_dropdown_hover_color(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)),
			_dropdown_active_color(ImVec4(0.06f, 0.53f, 0.98f, 1.00f))
		{
		}

		void add_element(element* element) {
			if (std::find(elements.begin(), elements.end(), element) == elements.end()) {
				elements.push_back(element);
			}
		}

		const std::string get_title() const {
			return _title;
		}

		void set_color(float r, float g, float b) {
			_active_color = ImVec4(r, g, b, 1.0f);
			_dropdown_hover_color = ImVec4(r + 0.10f, g + 0.11f, b + 0.11f, 1.0f);
			_dropdown_active_color = ImVec4(r - 0.10f, g - 0.11f, b - 0.11f, 1.0f);
		}
	};

	class button : public element {
		std::function<void()> _callback;
		std::string _text;
		bool _same_line;
		ImVec4 _color;
		ImVec4 _hover_color;
		ImVec4 _active_color;
	public:
		void render() override {
			ImGui::PushStyleColor(ImGuiCol_Button, _color);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, _hover_color);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, _active_color);

			if (_same_line) {
				ImGui::SameLine();
			}

			if (ImGui::Button(_text.c_str()) && _callback) {
				_callback();
			}

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		button(bool same_line = false)
			: _color(ImVec4(0.26f, 0.59f, 0.98f, 0.40f)),
			_hover_color(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)),
			_active_color(ImVec4(0.06f, 0.53f, 0.98f, 1.00f)),
			_same_line(same_line)
		{
		}

		button(const char* text, bool same_line = false)
			: _text(text),
			_same_line(same_line),
			_color(ImVec4(0.26f, 0.59f, 0.98f, 0.40f)),
			_hover_color(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)),
			_active_color(ImVec4(0.06f, 0.53f, 0.98f, 1.00f))
		{
		}

		button(const char* text, std::function<void()> callback, bool same_line = false)
			: _text(text),
			_callback(callback),
			_same_line(same_line),
			_color(ImVec4(0.26f, 0.59f, 0.98f, 0.40f)),
			_hover_color(ImVec4(0.26f, 0.59f, 0.98f, 1.00f)),
			_active_color(ImVec4(0.06f, 0.53f, 0.98f, 1.00f))
		{
		}

		void set_text(const char* text) {
			_text = text;
		}

		void set_color(float r, float g, float b) {
			_color = ImVec4(r, g, b, 0.62f);
			_hover_color = ImVec4(r + 0.05f, g + 0.08f, b + 0.09f, 0.79f);
			_active_color = ImVec4(r + 0.11f, g + 0.14f, b + 0.18f, 1.00f);
		}

		void set_callback(std::function<void()> callback) {
			_callback = callback;
		}

		const std::string get_text() const {
			return _text;
		}
	};

	class label : public element {
		std::string _text;
		bool _same_line;
	public:
		void render() override {
			if (_same_line) {
				ImGui::SameLine();
			}

			ImGui::Text(_text.c_str());
		}

		label(bool same_line = false) 
			: _same_line(same_line)
		{
		}

		label(const char* text, bool same_line = false)
			: _text(text),
			_same_line(same_line)
		{
		}

		void set_text(const char* text) {
			_text = text;
		}

		const std::string get_text() const {
			return _text;
		}
	};

	class check_box : public element {
		std::string _text;
		bool _same_line;
		bool _toggled;
		std::function<void(bool)> _callback;
	public:
		void render() override {
			if (_same_line) {
				ImGui::SameLine();
			}

			if (ImGui::Checkbox(_text.c_str(), &_toggled) && _callback) {
				_callback(_toggled);
			}
		}

		check_box(const char* text, bool same_line = false)
			: _text(text),
			_toggled(false),
			_same_line(same_line)
		{
		}

		void set_text(const char* text) {
			_text = text;
		}

		void set_toggle(bool toggle) {
			_toggled = toggle;
		}

		void set_callback(std::function<void(bool)> callback) {
			_callback = callback;
		}

		const bool is_toggled() const {
			return _toggled;
		}

		const std::string get_text() const {
			return _text;
		}
	};

	class slider : public element {
		int _min, _max, _current;
		std::string _text;
		bool _same_line;
	public:
		void render() override {
			ImGui::SliderInt(_text.c_str(), &_current, _min, _max);
		}

		slider(const char* text, bool same_line) 
			: _text(text),
			_same_line(same_line),
			_current(0),
			_min(0),
			_max(10)
		{
		}

		void set_text(const char* new_text) {
			_text = new_text;
		}

		void set_min(int min) {
			_min = min;
		}

		void set_max(int max) {
			_max = max;
		}

		const std::string get_text() const {
			return _text;
		}

		const int get() const {
			return _current;
		}

		const int get_min() const {
			return _min;
		}

		const int get_max() const {
			return _max;
		}
	};

	struct color3 {
		float r;
		float g;
		float b;
	};

	class color_picker : public element {
		std::string _text;
		bool _same_line;
		std::array<float, 4> _colors;
	public:
		void render() override {
			if (_same_line) {
				ImGui::SameLine();
			}

			ImGui::ColorPicker4(
				_text.c_str(),
				_colors.data(),
				ImGuiColorEditFlags_NoAlpha | 
					ImGuiColorEditFlags_PickerHueWheel | 
					ImGuiColorEditFlags_RGB |
					ImGuiColorEditFlags_NoSidePreview
			);
		}

		color_picker(bool same_line = false)
			: _text(std::to_string(std::rand())),
			_colors({ 0, 0, 0, 0 }),
			_same_line(same_line)
		{
		}

		void set_text(const char* new_text) {
			_text = new_text;
		}

		const std::string get_text() const {
			return _text;
		}

		const color3 get_colors() {
			return { _colors[0], _colors[1], _colors[2] };
		}
	};

	class combo_box : public element {
		std::vector<std::string> _members;
		std::function<void(const char*)> _callback;
		std::string _selected;
		std::string _id;
		bool _same_line;
	public:
		void render() override {
			if (_same_line) {
				ImGui::SameLine();
			}
			
			if (ImGui::BeginCombo(_id.c_str(), _selected.c_str())) {
				for (auto& member : _members) {
					auto member_str = member.c_str();
					bool is_selected = &_selected == &member;

					if (ImGui::Selectable(member_str, is_selected)) {
						_selected = member;

						if (_callback) {
							_callback(member_str);
						}
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}
		}

		combo_box(const char* id, bool same_line = false)
			: _id(id),
			_same_line(same_line)
		{ 
		}

		void set_text(const char* id) {
			_id = id;
		}

		void set_callback(std::function<void(const char*)> callback) {
			_callback = callback;
		}

		void add(const char* member) {
			_members.emplace_back(member);
		}

		void remove(const char* member) {
			std::remove_if(_members.begin(), _members.end(), [=](auto& str) {
				return member == str;
			});
		}

		const std::string get_text() const {
			return _id;
		}
	};

	class tab : public element {
	private:
		std::list<element*> elements;
		std::string _title;
	public:
		void render() override {
			if (ImGui::BeginTabItem(_title.c_str())) {
				for (auto element : elements) {
					element->render();
				}

				ImGui::EndTabItem();
			}
		}

		tab(const char* title) 
			: _title(title)
		{
		}

		void set_title(const char* new_title) {
			_title = new_title;
		}

		void add_element(element* element) {
			if (std::find(elements.begin(), elements.end(), element) == elements.end()) {
				elements.push_back(element);
			}
		}

		std::string get_title() const {
			return _title;
		}
	};

	class tab_selector : public element {
		std::list<tab> tabs;
		std::string _id;
		bool _same_line;
	public:
		void render() override {
			if (_same_line) {
				ImGui::SameLine();
			}

			if (ImGui::BeginTabBar(_id.c_str())) {
				for (auto& tab : tabs) {
					tab.render();
				}

				ImGui::EndTabBar();
			}
		}

		tab_selector(const char* id, bool same_line = false) 
			: _id(id),
			_same_line(same_line)
		{
		}

		tab* add_tab(const char* title) {
			return &tabs.emplace_back(title);
		}
	}; 
}
