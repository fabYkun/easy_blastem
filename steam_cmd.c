#include "blastem.h"
#include "steam_cmd.h"
#include "steamshim_child.h"
#include "nuklear_ui/blastem_nuklear.h"
#include <unistd.h>

/* These stats are here for the example, once replaced by yours go replace them in steam_cmd.h as well */
static const char *stat_name[STAT_COUNT] = {
    [STAT_PETTING] = "STAT_PETTING",
    [STAT_DOWN_AIR] = "STAT_DOWN_AIR",
    [STAT_DEATH] = "STAT_DEATH",
    [STAT_GAMEOVER] = "STAT_GAMEOVER",
};
static unsigned int stat_value[STAT_COUNT] = { STAT_UNINITIALIZED, STAT_UNINITIALIZED, STAT_UNINITIALIZED, STAT_UNINITIALIZED };
unsigned int language = LANGUAGE_ENGLISH;

void steam_cmd_loadstats()
{
  for (size_t i = 0; i < STAT_COUNT; i++)
  {
    char const *name = stat_name[i];
    if (stat_value[i] == STAT_UNINITIALIZED) {
      int attempts = 10;
      STEAMSHIM_getStatI(name);
      while (STEAMSHIM_alive() && --attempts >= 0)
      {
        const STEAMSHIM_Event *e = STEAMSHIM_pump();
        if (e && e->type == SHIMEVENT_GETSTATI && strcmp(name, e->name) == 0)
        {
          printf("got stat: %s: %d\n", name, e->ivalue);
          stat_value[i] = e->ivalue;
          break;
        }
        usleep(1000);
      }
    }
    if (stat_value[i] == STAT_UNINITIALIZED) {
      printf("failed to get stat: %s: %d\n", name, stat_value[i]);
    }
  }
}

void steam_cmd_parselog(const char *log)
{
  if (strcmp(log, "MENU") == 0) {
    show_pause_menu();
  } else if (strcmp(log, "SAVE") == 0) {
    sram_save();
  } else if (strstr(log, "LANGUAGE:") != NULL) {
    unsigned int lang = atoi(&log[(sizeof("LANGUAGE:") - 1)]);
    if (lang < LANGUAGE_COUNT) {
      language = lang;
    }
  } else if (strstr(log, "SUCCESS:") != NULL) {
    printf("STEAMSHIM_setAchievement: %s\n", &log[(sizeof("SUCCESS:") - 1)]);
    STEAMSHIM_setAchievement(&log[(sizeof("SUCCESS:") - 1)], 1);
    STEAMSHIM_storeStats();
  }
  else if (strstr(log, "STAT:") != NULL)
  {
    const char *name = &log[5];
    for (size_t i = 0; i < STAT_COUNT; i++)
    {
      if (strcmp(stat_name[i], name) == 0)
      {
        if (stat_value[i] == STAT_UNINITIALIZED)
        {
          int attempts = 10;
          STEAMSHIM_getStatI(name);
          while (STEAMSHIM_alive() && --attempts >= 0)
          {
            const STEAMSHIM_Event *e = STEAMSHIM_pump();
            if (e && e->type == SHIMEVENT_GETSTATI && strcmp(name, e->name) == 0)
            {
              printf("got stat: %s: %d\n", name, e->ivalue);
              stat_value[i] = e->ivalue;
              break;
            }
            usleep(1000);
          }
        }
        if (stat_value[i] != STAT_UNINITIALIZED)
        {
          ++stat_value[i];
          STEAMSHIM_setStatI(name, stat_value[i]);
          printf("STEAMSHIM_setStatI: %s: %d\n", name, stat_value[i]);
          STEAMSHIM_storeStats();
        }
      }
    }
  }
}