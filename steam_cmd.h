void steam_cmd_loadstats();
void steam_cmd_parselog(const char *log);

/* These stats are here for the example, once replaced by yours go replace them in steam_cmd.c as well */
enum Stat_Id {
	STAT_PETTING = 0,
	STAT_DOWN_AIR,
	STAT_DEATH,
	STAT_GAMEOVER,
	STAT_COUNT,

	STAT_UNINITIALIZED = -1,
};

enum Language_Id {
  LANGUAGE_ENGLISH = 0,
  LANGUAGE_FRENCH,
  LANGUAGE_ITALIANO,
  LANGUAGE_DEUTSCH,
  LANGUAGE_ESPANOL,
  LANGUAGE_PORTUGUES,
  LANGUAGE_COUNT,
};

extern unsigned int language;