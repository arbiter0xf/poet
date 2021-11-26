#include <assert.h>
#include <stdlib.h>

#include "util_poet.h"
#include "log.h"

int get_first_free_inventory_slot(struct item** const inventory)
{
	for (int i = 0; i < ACTOR_INVENTORY_SIZE; i++) {
		if (0 == inventory[i]) {
			return i;
		}
	}

	return -1;
}

int get_first_free_actor_slot(struct actor** const actors)
{
	for (int i = 0; i < ALL_ACTORS_SIZE; i++) {
		if (0 == actors[i]) {
			return i;
		}
	}

	return -1;
}

int get_first_free_item_slot(struct item** const items)
{
	return get_first_free_inventory_slot(items);
}

int is_hud_interactive(void)
{
	return DRAW_INVENTORY == g_hud_to_draw
		|| DRAW_SELECT_ITEM_OPERATION == g_hud_to_draw;
}

int max(int first, int second)
{
	if (first > second) {
		return first;
	}

	return second;
}

int min(int first, int second)
{
	if (first < second) {
		return first;
	}

	return second;
}

int center(int lesser, int greater)
{
	return greater - ((greater - lesser) / 2);
}

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

void populate_structures(void)
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

void unpopulate_structures(void)
{
	for (int i = 0; i < ITEM_OPERATIONS_SIZE; i++) {
		if (0 != g_item_operations[i]) {
			free(g_item_operations[i]);
			g_item_operations[i] = 0;
		}
	}
}
