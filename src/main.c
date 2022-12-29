#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int print(lua_State *L)
{
    const int argc = lua_gettop(L);

    for (int i = 1; i <= argc; i++)
    {
        printf("%s ", lua_tostring(L, i));
    }
    printf("\n");

    return 0;
}

static const luaL_Reg luaosLibs[] = {
    {LUA_COLIBNAME, luaopen_coroutine},
    {LUA_TABLIBNAME, luaopen_table},
    {LUA_STRLIBNAME, luaopen_string},
    {LUA_MATHLIBNAME, luaopen_math},
    {LUA_UTF8LIBNAME, luaopen_utf8},
    {NULL, NULL}};

void luaOSL_openlibs(lua_State *L)
{
    const luaL_Reg *lib;
    /* "require" functions from 'loadedlibs' and set results to global table */
    for (lib = luaosLibs; lib->func; lib++)
    {
        luaL_requiref(L, lib->name, lib->func, 1);
        lua_pop(L, 1); /* remove lib */
    }
}

int main()
{
    lua_State *L = luaL_newstate();
    luaOSL_openlibs(L);

    lua_register(L, "print", print);

    luaL_dostring(L, "print(69)");

    return 0;
}