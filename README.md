# Lua-ImGui
Object-oriented Lua bindings for ImGui

This has been **attempted naively**, so you may encounter my strange code structuring.
Feel free to contribute better solutions!

# Example
```cpp
#include "Lua-ImGui/lib.hpp"

std::vector<lib::window> windows;
lua_State *l_G = luaL_newstate();

#include "Lua-ImGui/helper.hpp"
#include "Lua-ImGui/bind.hpp"

int main() {
  lua_bind::init(); // Initializes the "ImGui" global
  
  /* 
  lua_close(l_G); 
  -- Lua state is not closed, since element callback functions are stored in the registry
  -- If you have a better solution, feel free to make a pull request!
  */
}
```

# Lua API
```lua
-- Main window
local Window = ImGui.new("Window", "example title")

-- Inner elements
local Label = ImGui.new("Label", Window)
local TabSelector = ImGui.new("TabSelector", Window)

local Tab1 = TabSelector:AddTab("Tab1")
local Tab2 = TabSelector:AddTab("Tab2")

local Button = ImGui.new("Button", Tab1)
local Slider = ImGui.new("Slider", Tab1, true) -- (boolean: 3) aligns it side-by-side !
local ColorPicker = ImGui.new("ColorPicker", Tab2)

Label.Text = "Lua-ImGui Example"
Slider.Text = "Slider Example"
Button.Text = "Button Example"

Slider.Min = -10
Slider.Max = 10

Button.Callback = function()
  ImGui.new("Label", Tab1).Text = "Hello world"
end
```
<img src="https://i.gyazo.com/0cae8cae14688cc204b3cff064e8ba63.gif" />
