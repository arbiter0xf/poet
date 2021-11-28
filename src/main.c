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

	struct terrain floor = {
		.icon = '.',
		.name = "floor",
		.traversable = 1,
	};

	struct terrain wall_vertical = {
		.icon = '|',
		.name = "wall_vertical",
		.traversable = 0,
	};

	struct terrain wall_horizontal = {
		.icon = '-',
		.name = "wall_horizontal",
		.traversable = 0,
	};

	struct terrain column = {
		.icon = '+',
		.name = "column",
		.traversable = 0,
	};

	struct terrain terrain_void = {
		.icon = ' ',
		.name = "void",
		.traversable = 0,
	};

	g_all_terrains[ALL_TERRAINS_FLOOR]		= &floor;
	g_all_terrains[ALL_TERRAINS_WALL_VERTICAL]	= &wall_vertical;
	g_all_terrains[ALL_TERRAINS_WALL_HORIZONTAL]	= &wall_horizontal;
	g_all_terrains[ALL_TERRAINS_COLUMN]		= &column;
	g_all_terrains[ALL_TERRAINS_VOID]		= &terrain_void;

	srandom((unsigned) time(&t));

	initialize_io();
	populate_structures();
	load_stage(STAGE_TYPE_HIDEOUT);
#if 0
	dump_stage_to_file();
#endif

	while (BUTTON_QUIT != pressed_key) {
		draw(get_all_actors());
		pressed_key = getch();
		update(&pressed_key);
	}

	unpopulate_structures();
	teardown_io();

	return 0;
}
