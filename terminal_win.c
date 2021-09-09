#include <windows.h>
#include <stdio.h>
#include "steam_cmd.h"

static char init_done = 0;

void force_no_terminal()
{
	init_done = 1;
}

void init_terminal()
{
	init_done = 1;
	if (!init_done) {
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		init_done = 1;
	}
}
