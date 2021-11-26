#ifndef ANNOUNCE_H_DEFINED
#define ANNOUNCE_H_DEFINED

#define ROW_ANNOUNCE_ZERO 35
#define COL_ANNOUNCE_ZERO 5

#define ANNOUNCEMENT_SIZE 128

extern char g_new_announcement[ANNOUNCEMENT_SIZE];

void announce(const char* new_announcement);

#endif
