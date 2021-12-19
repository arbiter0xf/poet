#ifndef USER_INPUT_H_DEFINED
#define USER_INPUT_H_DEFINED

#define BUTTON_QUIT 'q'

enum cursor_movement {
	CURSOR_NONE,
	CURSOR_UP,
	CURSOR_DOWN,
};

enum hud_toggle {
	TOGGLE_NONE,
	TOGGLE_INVENTORY,
	TOGGLE_STATUS,
	TOGGLE_EQUIPMENT,
};

enum position_update {
	POSITION_UPDATE_NONE,
	POSITION_UPDATE_UP,
	POSITION_UPDATE_DOWN,
	POSITION_UPDATE_LEFT,
	POSITION_UPDATE_RIGHT,
	POSITION_UPDATE_WAIT,
};

int is_direction_button(int* const pressed_key);
int is_hud_select_button(int* const pressed_key);
int is_cursor_movement_button(int* const pressed_key);
int is_hud_toggle_button(int* const pressed_key);
int is_wait_button(int* const pressed_key);
enum cursor_movement key_to_cursor_movement(int* const pressed_key);
enum hud_toggle key_to_hud_toggle(int* const pressed_key);
enum position_update key_to_position_update(int* const pressed_key);

#endif
