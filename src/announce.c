#include <ncurses.h>
#include <string.h>

#include "announce.h"

char g_new_announcement[ANNOUNCEMENT_SIZE] = {0};

#ifndef NOANNOUNCE
void announce(const char* new_announcement)
{
	// TODO announcement history viewing
	char space_row[128];
	static char announcements_shortlist[5][128];

	for (int i = 0; i < 128; i++) {
		space_row[i] = ' ';
	}
	space_row[128 - 1] = '\0';

	for (int i = 3; i >= 0; i--) {
		strcpy(announcements_shortlist[i + 1], announcements_shortlist[i]);
	}
	strcpy(announcements_shortlist[0], new_announcement);

	move(ROW_ANNOUNCE_ZERO, COL_ANNOUNCE_ZERO);
	for (int i = 0; i < 5; i++) {
		move(ROW_ANNOUNCE_ZERO + i, COL_ANNOUNCE_ZERO);
		printw("%s", space_row);
		move(ROW_ANNOUNCE_ZERO + i, COL_ANNOUNCE_ZERO);
		printw("%s", announcements_shortlist[i]);
	}
}
#else
void announce(const char* new_announcement)
{
	(void) new_announcement;
}
#endif
