// Tinyfd.cpp
// Extension lib defines
#define LIB_NAME "tinyfd"
#define MODULE_NAME LIB_NAME

// include the Defold SDK
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_LINUX) || defined(DM_PLATFORM_OSX) || defined(DM_PLATFORM_WINDOWS)

#include "tinyfiledialogs/tinyfiledialogs.h"

static int Tfd_beep(lua_State* L) {
    tinyfd_beep();
    return 0;
}

static int Tfd_notifyPopup(lua_State* L) {
    const char * aTitle = luaL_optstring(L, 1, 0);
    const char * aMessage = luaL_optstring(L, 2, 0);
    const char * aIconType = luaL_optstring(L, 3, 0);

    int res = tinyfd_notifyPopup(aTitle, aMessage, aIconType);
    lua_pushinteger(L, res);
    return 1;
}

static int Tfd_messageBox(lua_State* L) {
    const char * aTitle = luaL_optstring(L, 1, 0);
    const char * aMessage = luaL_optstring(L, 2, 0);
    const char * aDialogType = luaL_optstring(L, 3, 0);
    const char * aIconType = luaL_optstring(L, 4, 0);
    int aDefaultButton = luaL_optint(L, 5, 0);

    int res = tinyfd_messageBox(aTitle, aMessage, aDialogType, aIconType, aDefaultButton);
    lua_pushinteger(L, res);
    return 1;
}

static int Tfd_inputBox(lua_State* L) {
    const char * aTitle = luaL_optstring(L, 1, 0);
    const char * aMessage = luaL_optstring(L, 2, 0);
    const char * aDefaultInput = luaL_optstring(L, 3, 0);

    char * res = tinyfd_inputBox(aTitle, aMessage, aDefaultInput);
    lua_pushstring(L, res);
    return 1;
}

static int Tfd_saveFileDialog(lua_State* L) {
    const char * aTitle = luaL_optstring(L, 1, 0);
    const char * aDefaultPathAndFile = luaL_optstring(L, 2, 0);
    int aNumOfFilterPatterns = 0;
    const char * * aFilterPatterns = 0;
    const char * aSingleFilterDescription = luaL_optstring(L, 4, 0);

    if (!lua_isnil(L, 3)) {
        luaL_checktype(L, 3, LUA_TTABLE);
        aNumOfFilterPatterns = lua_objlen(L, 3);
        aFilterPatterns = new const char*[aNumOfFilterPatterns];

        for (int i = 0; i < aNumOfFilterPatterns; ++i) {
            lua_pushinteger(L, i + 1);
            lua_gettable(L, 3);
            aFilterPatterns[i] = luaL_checkstring(L, -1);
            lua_pop(L, 1);
        }
    }

    char * res = tinyfd_saveFileDialog(aTitle, aDefaultPathAndFile, aNumOfFilterPatterns, aFilterPatterns, aSingleFilterDescription);
    lua_pushstring(L, res);
    return 1;
}

static int Tfd_openFileDialog(lua_State* L) {
    const char * aTitle = luaL_optstring(L, 1, 0);
    const char * aDefaultPathAndFile = luaL_optstring(L, 2, 0);
    int aNumOfFilterPatterns = 0;
    const char * * aFilterPatterns = 0;
    const char * aSingleFilterDescription = luaL_optstring(L, 4, 0);
    int aAllowMultipleSelects = luaL_optint(L, 5, 0);

    if (!lua_isnil(L, 3)) {
        luaL_checktype(L, 3, LUA_TTABLE);
        aNumOfFilterPatterns = lua_objlen(L, 3);
        aFilterPatterns = new const char*[aNumOfFilterPatterns];

        for (int i = 0; i < aNumOfFilterPatterns; ++i) {
            lua_pushinteger(L, i + 1);
            lua_gettable(L, 3);
            aFilterPatterns[i] = luaL_checkstring(L, -1);
            lua_pop(L, 1);
        }
    }

    char * res = tinyfd_openFileDialog(aTitle, aDefaultPathAndFile, aNumOfFilterPatterns, aFilterPatterns, aSingleFilterDescription, aAllowMultipleSelects);
    lua_pushstring(L, res);
    return 1;
}

static int Tfd_selectFolder(lua_State* L) {
    const char * aTitle = luaL_optstring(L, 1, 0);
    const char * aDefaultPath = luaL_optstring(L, 2, 0);

    char * res = tinyfd_selectFolderDialog(aTitle, aDefaultPath);
    lua_pushstring(L, res);
    return 1;
}

static int Tfd_colorChooser(lua_State* L) {
    const char * aTitle = luaL_optstring(L, 1, 0);
    const char * aDefaultHexRGB = luaL_optstring(L, 2, 0);

    char * res = tinyfd_colorChooser(aTitle, aDefaultHexRGB, 0, 0);
    lua_pushstring(L, res);
    return 1;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"beep", Tfd_beep},
    {"notify_popup", Tfd_notifyPopup},
    {"message_box", Tfd_messageBox},
    {"input_box", Tfd_inputBox},
    {"save_file", Tfd_saveFileDialog},
    {"open_file", Tfd_openFileDialog},
    {"select_folder", Tfd_selectFolder},
    {"color_chooser", Tfd_colorChooser},
    {0, 0}
};

#else

static const luaL_reg Module_methods[] =
{
    {0, 0}
};

#endif

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);

    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);

    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result InitializeTinyfd(dmExtension::Params* params)
{
    LuaInit(params->m_L);

    #ifdef DM_PLATFORM_WINDOWS
    tinyfd_winUtf8 = 0;
    #endif

    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeTinyfd(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(tinyfd, LIB_NAME, 0, 0, InitializeTinyfd, 0, 0, FinalizeTinyfd)
