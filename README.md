# Lua-ImGui
Object-oriented Lua binding for ImGui

This has been attempted naively, so you may encounter my strange code structuring.
Feel free to contribute better solutions!

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
