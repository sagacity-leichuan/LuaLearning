// FirstTest.cpp : 定义控制台应用程序的入口点。
//

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
#include <string.h>

//传递普通参数
int CTest(lua_State *L)
{
	printf("int CTest\n");
	size_t len;
	const char *name = lua_tolstring(L,1,&len);
	printf("Lua name = %s\n",name);
	int age = lua_tonumber(L,2);
	printf("Lua age = %d\n", age);
	bool is = lua_toboolean(L, 3);
	printf("Lua is = %d\n", is);
	return 0;
}

//传递数组
int CTestArr(lua_State *L)
{
	printf("int CTestArr\n");
	int len = luaL_getn(L,1);
	for (int i = 1; i <= len; i++)
	{
		lua_pushnumber(L, i);
		lua_gettable(L,1); //pop index and push table[i]
		size_t size;
		printf("%s\n", lua_tolstring(L,-1,&size));
		lua_pop(L,1);
	}
	return 0;
}

//传递map表和判断参数类型
int CTestTable(lua_State *L)
{
	printf("int CTestTable\n"); 

	//luaL_checktype(L,1,LUA_TTABLE); //检查失败就停止执行
	if (lua_type(L, 2) != LUA_TNUMBER)
	{
		printf("para 2 is not number!\n");
	}
	lua_pushnil(L);
	while (lua_next(L, 1) != 0)
	{
		printf("Key = %s, Value = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	lua_getfield(L,1,"name");
	printf("name = %s\n",lua_tostring(L, -1));
	return 0;
}

//有返回值的函数
int CTestRe(lua_State *L)
{	
	//lua_pushstring(L, "return value");  //栈顶压入
	//lua_pushnumber(L, 123);
	//return 2;  //返回的是返回值个数
	lua_newtable(L);
	lua_pushstring(L, "name");
	lua_pushstring(L, "leichuan");
	lua_settable(L, -3);
	lua_pushstring(L, "age");
	lua_pushnumber(L, 120);
	lua_settable(L, -3);
	return 1;
}

int main(int argc, char* argv[])
{
	lua_State *lua = lua_open();
	//打开基本库
	luaopen_base(lua);

	//打开table库
	luaopen_table(lua);

	//打开IO库
	luaL_openlibs(lua);

	//打开string库
	luaopen_string(lua);

	//打开math库
	luaopen_math(lua);

	lua_register(lua, "CTest", CTest);
	lua_register(lua, "CTestArr", CTestArr);
	lua_register(lua, "CTestTable", CTestTable);
	lua_register(lua, "CTestRe", CTestRe);

	//给lua传递一个全局变量
	lua_pushstring(lua, "Hello");
	lua_setglobal(lua, "test");

	//给lua传递一个全局变量表
	lua_newtable(lua);            /* creates a table */
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "c to lua name");
	lua_settable(lua, -3);     //弹出key, value, 表在栈顶了
	lua_pushstring(lua, "age");
	lua_pushnumber(lua, 456);
	lua_settable(lua, -3);     //弹出key, value, 表在栈顶了
	lua_setglobal(lua, "cvar"); //将栈顶位置设置全局变量并出栈


	if (luaL_loadfile(lua, "main.lua"))
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n 执行脚本文件失败", error);
		return -1;
	}
	if (lua_pcall(lua, 0, 0, 0))
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n 执行脚本文件失败", error);

		return -1;
	}

#if 0
	//获取lua的全局变量
	lua_getglobal(lua,"width");
	int width = lua_tonumber(lua,-1);
	lua_pop(lua, 1);
	printf("width = %d\n", width);

	//获取lua的全局变量表
	lua_getglobal(lua, "tab");   //表压入栈顶
	lua_getfield(lua, -1, "name");//表中key的value压入栈顶
	printf("lua tab[\"name\"] = %s\n", lua_tostring(lua, -1)); //取出栈顶元素
	//lua_pop(lua, 1);
	//lua_getfield(lua, -1, "age");//表中key的value压入栈顶
	lua_getfield(lua, -2, "age");//表中key的value压入栈顶
	printf("lua tab[\"age\"] = %d\n", (int)lua_tonumber(lua, -1)); //取出栈顶元素
	lua_pop(lua, 3); //弹栈两个
#endif
	
	//调用lua函数
	printf("top is %d\n", lua_gettop(lua));
	int errfun = lua_gettop(lua);
	lua_getglobal(lua, "ferror");
	errfun++;  //记住错误函数在栈中的位置
	lua_getglobal(lua, "LEvent");
	//设置一个参数
	lua_pushstring(lua, "key");

	lua_newtable(lua);            /* creates a table */
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "leiyuhong");
	lua_settable(lua, -3);     //弹出key, value, 表在栈顶了
	lua_pushstring(lua, "age");
	lua_pushnumber(lua, 789565555);
	lua_settable(lua, -3);     //弹出key, value, 表在栈顶了

	if (lua_pcall(lua, 2, 1, errfun) != 0) //执行脚本中的函数
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n", error);
		lua_pop(lua,1);
	}
	else//取返回值
	{
		//const char * returnvalue = lua_tostring(lua, -1);
		//printf("%s\n",returnvalue);
		lua_getfield(lua, -1, "id");
		printf("return table id = %d\n", (int)lua_tonumber(lua, -1));
		lua_pop(lua, 2);
	}
	lua_pop(lua, 1);  //把错误处理函数出栈
	printf("top is %d\n", lua_gettop(lua));

	lua_close(lua);
	getchar();
	return 0;
}

