# Unreleased
* Removed uses of deprecated libtcod types such as TCODList.
* Switched to TCOD_RENDERER_SDL2 as the default renderer.
* Virtual classes now have default destructors.
* Headers now include what they need.
* "umbra_" prefix removed from headers.
* Reverted some module handing so that Pyromancer works again.
* General fixes and updates for code working with C++17.
* ``UmbraEngine::getFontDir`` now returns ``std::filesystem::path`` instead of ``const char*``.
* Logging functions now use ``fmt`` instead of C variadic print functions.
* ``UmbraLog::get`` now returns ``std::string`` instead of a pointer to a temporary string.
* Added ``UmbraModule::onEvent`` to transition away from libtcod events.
