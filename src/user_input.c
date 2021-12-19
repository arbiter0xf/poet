#include <ncurses.h>

#include "user_input.h"
#include "util_poet.h"

int is_direction_button(int* const pressed_key)
{
	if (KEY_DOWN == *pressed_key) {
		return 1;
	}

	if (KEY_UP == *pressed_key) {
		return 1;
	}

	if (KEY_LEFT == *pressed_key) {
		return 1;
	}

	if (KEY_RIGHT == *pressed_key) {
		return 1;
	}

	return 0;
}

int is_hud_select_button(int* const pressed_key)
{
	if (is_hud_interactive() && '\n' == *pressed_key) {
		return 1;
	}

	return 0;
}

int is_cursor_movement_button(int* const pressed_key)
{
	if (is_hud_interactive() && is_direction_button(pressed_key)) {
		return 1;
	}

	return 0;
}

int is_hud_toggle_button(int* const pressed_key) {
	if ('i' == *pressed_key) {
		return 1;
	}

	if ('s' == *pressed_key) {
		return 1;
	}

	if ('e' == *pressed_key) {
		return 1;
	}

	return 0;
}

int is_wait_button(int* const pressed_key) {
	if ('w' == *pressed_key) {
		return 1;
	}

	return 0;
}

enum cursor_movement key_to_cursor_movement(int* const pressed_key)
{
	if (KEY_UP == *pressed_key)	{ return CURSOR_UP; }
	if (KEY_DOWN == *pressed_key)	{ return CURSOR_DOWN; }

	return CURSOR_NONE;
}

enum hud_toggle key_to_hud_toggle(int* const pressed_key)
{
	if ('i' == *pressed_key) { return TOGGLE_INVENTORY; }
	if ('s' == *pressed_key) { return TOGGLE_STATUS; }
	if ('e' == *pressed_key) { return TOGGLE_EQUIPMENT; }

	return TOGGLE_NONE;
}

enum position_update key_to_position_update(int* const pressed_key)
{
	if (KEY_UP == *pressed_key)	{ return POSITION_UPDATE_UP; }
	if (KEY_DOWN == *pressed_key)	{ return POSITION_UPDATE_DOWN; }
	if (KEY_LEFT == *pressed_key)	{ return POSITION_UPDATE_LEFT; }
	if (KEY_RIGHT == *pressed_key)	{ return POSITION_UPDATE_RIGHT; }
	if ('w' == *pressed_key)	{ return POSITION_UPDATE_WAIT; }

	return POSITION_UPDATE_NONE;
}
