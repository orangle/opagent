/*
从单个文件开始写，注意函数声明，后面好做分离
*/
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char MONNITOR[30] = "";
char SERVERIP[16] = "127.0.0.1";
int SERVERPORT = 8888;

void load_settings(void);

void load_settings(void){
	lua_State *L = lua_open();
	luaL_openlibs(L);
	if (luaL_loadfile(L, "settings.lua") || lua_pcall(L, 0, 0, 0)){
		printf("Can not load setting.lua file: %s\n",lua_tostring(L, -1));
		lua_close(L);
		return ;
    }

	lua_getglobal(L, "MONNITOR");
	lua_getglobal(L, "SERVERIP");
	lua_getglobal(L, "SERVERPORT");

	//如果数据太长呢
	if (lua_isstring(L, -3)) {
		const char *monitor = lua_tostring(L, -3);
		if (strlen(monitor) < 1) {
			printf("MONNITOR is empty! error");
			exit(1);
		}
		memset(MONNITOR,'\0',sizeof(MONNITOR));
        strncpy(MONNITOR, monitor,sizeof(MONNITOR)-1);
	}

	if (lua_isstring(L, -2)) {
		const char *host = lua_tostring(L, -2);
		memset(SERVERIP,'\0',sizeof(SERVERIP));
        strncpy(SERVERIP, host,sizeof(SERVERIP)-1);
	}

	if (lua_tonumber(L, -1)) {
		SERVERPORT = lua_tonumber(L, -1);
	}

	lua_close(L);
}

int main(void){
	printf("start ...\n");
	load_settings();
	printf("MONNITOR is %s\n", MONNITOR);
	printf("SERVERIP is %s\n", SERVERIP);
	printf("SERVERPORT is %d\n", SERVERPORT);
	return 0;
}


