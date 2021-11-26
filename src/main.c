#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "actor.h"
#include "announce.h"
#include "draw.h"
#include "interact.h"
#include "item.h"
#include "log.h"
#include "stage.h"
#include "update.h"
#include "user_input.h"
#include "util.h"

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

void initialize_io(void)
{
	initscr();
	noecho(); // Do not echo read chars
	cbreak(); // Read input contiguously
	keypad(stdscr, TRUE); // Read more keys, including arrow keys
	curs_set(0);

	initialize_logging();
}

void teardown_io(void)
{
	teardown_logging();
	endwin();
}

void populate_structures()
{
	const char* op_names[] = {
		"use",
		"equip",
		"drop",
	};
	void (*op_apply_functions[]) (struct item* const subject) = {
		apply_operation_use,
		apply_operation_equip,
		apply_operation_drop,
	};

	const int available_names = sizeof(op_names) / sizeof(op_names[0]);
	const int available_functions =
		sizeof(op_apply_functions) / sizeof(op_apply_functions[0]);
	const int available_operations = available_names;

	assert(available_names == available_functions);

	for (int i = 0; 1; i++) {
		if (i >= ITEM_OPERATIONS_SIZE) {
			break;
		}

		if (i >= available_operations) {
			break;
		}

		g_item_operations[i] = malloc(sizeof(struct item_operation));
		strcpy(g_item_operations[i]->name, op_names[i]);
		g_item_operations[i]->apply = op_apply_functions[i];
	}
}

void unpopulate_structures()
{
	for (int i = 0; i < ITEM_OPERATIONS_SIZE; i++) {
		if (0 != g_item_operations[i]) {
			free(g_item_operations[i]);
			g_item_operations[i] = 0;
		}
	}
}

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

	while (BUTTON_QUIT != pressed_key) {
		draw(get_all_actors());
		pressed_key = getch();
		update(&pressed_key);
	}

	unpopulate_structures();
	teardown_io();

	return 0;
}
