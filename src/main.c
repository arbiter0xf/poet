#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "actor.h"
#include "announce.h"
#include "draw.h"
#include "interact.h"
#include "item.h"
#include "stage.h"
#include "update.h"
#include "user_input.h"
#include "util_poet.h"

#define ROW_DEBUG_ZERO 45
#define COL_DEBUG_ZERO 5

#define BUTTON_QUIT 'q'

#define DEBUG_MESSAGE_SIZE 128

#define DEBUG_PRINT_ENABLE 0

#if 0
// Uncomment to disable asserts
#define NDEBUG
#endif

#if 0
move(ROW_DEBUG_ZERO + g_row_debug_current, COL_DEBUG_ZERO);
printw("");
g_row_debug_current++;
#endif

int g_row_debug_current = 0;

int main(void) {
	int pressed_key = 0;
	time_t t;

	srandom((unsigned) time(&t));

	initialize_io();
	populate_structures();
	load_stage(STAGE_TYPE_HIDEOUT);
	dump_stage_to_file();

	while (BUTTON_QUIT != pressed_key) {
		draw(get_all_actors());
		pressed_key = getch();
		update(&pressed_key);
	}

	unpopulate_structures();
	teardown_io();

	return 0;
}
