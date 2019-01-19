// FirstTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
#include <string.h>

//������ͨ����
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

//��������
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

//����map����жϲ�������
int CTestTable(lua_State *L)
{
	printf("int CTestTable\n"); 

	//luaL_checktype(L,1,LUA_TTABLE); //���ʧ�ܾ�ִֹͣ��
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

//�з���ֵ�ĺ���
int CTestRe(lua_State *L)
{	
	//lua_pushstring(L, "return value");  //ջ��ѹ��
	//lua_pushnumber(L, 123);
	//return 2;  //���ص��Ƿ���ֵ����
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
	//�򿪻�����
	luaopen_base(lua);

	//��table��
	luaopen_table(lua);

	//��IO��
	luaL_openlibs(lua);

	//��string��
	luaopen_string(lua);

	//��math��
	luaopen_math(lua);

	lua_register(lua, "CTest", CTest);
	lua_register(lua, "CTestArr", CTestArr);
	lua_register(lua, "CTestTable", CTestTable);
	lua_register(lua, "CTestRe", CTestRe);

	//��lua����һ��ȫ�ֱ���
	lua_pushstring(lua, "Hello");
	lua_setglobal(lua, "test");

	//��lua����һ��ȫ�ֱ�����
	lua_newtable(lua);            /* creates a table */
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "c to lua name");
	lua_settable(lua, -3);     //����key, value, ����ջ����
	lua_pushstring(lua, "age");
	lua_pushnumber(lua, 456);
	lua_settable(lua, -3);     //����key, value, ����ջ����
	lua_setglobal(lua, "cvar"); //��ջ��λ������ȫ�ֱ�������ջ


	if (luaL_loadfile(lua, "main.lua"))
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n ִ�нű��ļ�ʧ��", error);
		return -1;
	}
	if (lua_pcall(lua, 0, 0, 0))
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n ִ�нű��ļ�ʧ��", error);

		return -1;
	}

#if 0
	//��ȡlua��ȫ�ֱ���
	lua_getglobal(lua,"width");
	int width = lua_tonumber(lua,-1);
	lua_pop(lua, 1);
	printf("width = %d\n", width);

	//��ȡlua��ȫ�ֱ�����
	lua_getglobal(lua, "tab");   //��ѹ��ջ��
	lua_getfield(lua, -1, "name");//����key��valueѹ��ջ��
	printf("lua tab[\"name\"] = %s\n", lua_tostring(lua, -1)); //ȡ��ջ��Ԫ��
	//lua_pop(lua, 1);
	//lua_getfield(lua, -1, "age");//����key��valueѹ��ջ��
	lua_getfield(lua, -2, "age");//����key��valueѹ��ջ��
	printf("lua tab[\"age\"] = %d\n", (int)lua_tonumber(lua, -1)); //ȡ��ջ��Ԫ��
	lua_pop(lua, 3); //��ջ����
#endif
	
	//����lua����
	printf("top is %d\n", lua_gettop(lua));
	int errfun = lua_gettop(lua);
	lua_getglobal(lua, "ferror");
	errfun++;  //��ס��������ջ�е�λ��
	lua_getglobal(lua, "LEvent");
	//����һ������
	lua_pushstring(lua, "key");

	lua_newtable(lua);            /* creates a table */
	lua_pushstring(lua, "name");
	lua_pushstring(lua, "leiyuhong");
	lua_settable(lua, -3);     //����key, value, ����ջ����
	lua_pushstring(lua, "age");
	lua_pushnumber(lua, 789565555);
	lua_settable(lua, -3);     //����key, value, ����ջ����

	if (lua_pcall(lua, 2, 1, errfun) != 0) //ִ�нű��еĺ���
	{
		const char * error = lua_tostring(lua, -1);
		printf("%s\n", error);
		lua_pop(lua,1);
	}
	else//ȡ����ֵ
	{
		//const char * returnvalue = lua_tostring(lua, -1);
		//printf("%s\n",returnvalue);
		lua_getfield(lua, -1, "id");
		printf("return table id = %d\n", (int)lua_tonumber(lua, -1));
		lua_pop(lua, 2);
	}
	lua_pop(lua, 1);  //�Ѵ���������ջ
	printf("top is %d\n", lua_gettop(lua));

	lua_close(lua);
	getchar();
	return 0;
}

