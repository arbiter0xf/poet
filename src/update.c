#include "actor.h"
#include "announce.h"
#include "interact.h"
#include "item.h"
#include "log.h"
#include "update.h"
#include "user_input.h"
#include "util_poet.h"

int g_ui_enabled = 1;

static void toggle_hud_inventory(void);
static void toggle_hud_status(void);
static void toggle_hud_equipment(void);
static void select_operation_for_item(int cursor_index);
static void set_hud_select_item_operation(struct item* const selected_item);
static void set_hud_hide(void);
static void apply_operation_to_item(struct item* const selected_item, struct item_operation* operation);
static void toggle_hud(const enum hud_toggle toggle);
static void move_cursor(const enum cursor_movement movement);
static void update_hud(int* const pressed_key);
static void update_player(int* const pressed_key);
static void update_player_items(struct actor* const player);
static void update_all_hostile_actors();
static void update_hostile_actor();

void update_set_ui_enabled(int enabled)
{
	g_ui_enabled = enabled;
}

int update_is_ui_enabled(void)
{
	return g_ui_enabled;
}

void update(int* const pressed_key)
{
	if (BUTTON_QUIT == *pressed_key) {
		return;
	}

	// Player and UI related updates dependent on user input.
	if (update_is_ui_enabled()) {
		update_hud(pressed_key);
	}

	if (is_game_over()) {
		return;
	}

	if (player_has_spawned()) {
		update_player(pressed_key);
	}

	// Enemy updates independent of user input.
	update_all_hostile_actors();
}

static void update_hud(int* const pressed_key)
{
	if (is_hud_toggle_button(pressed_key)) {
		toggle_hud(key_to_hud_toggle(pressed_key));
		*pressed_key = 0;
		return;
	}

	if (is_cursor_movement_button(pressed_key)) {
		move_cursor(key_to_cursor_movement(pressed_key));
		*pressed_key = 0;
		return;
	}

	if (is_hud_select_button(pressed_key)) {
		if (DRAW_INVENTORY == g_hud_to_draw) {
			select_operation_for_item(g_cursor_index);
			*pressed_key = 0;
			return;
		}
		if (DRAW_SELECT_ITEM_OPERATION == g_hud_to_draw) {
			apply_operation_to_item(get_selected_item(), get_item_operation(g_cursor_index));
			*pressed_key = 0;
			return;
		}
	}
}

static void toggle_hud(const enum hud_toggle toggle)
{
	if (TOGGLE_INVENTORY == toggle) {
		toggle_hud_inventory();
	}

	if (TOGGLE_STATUS == toggle) {
		toggle_hud_status();
	}

	if (TOGGLE_EQUIPMENT == toggle) {
		toggle_hud_equipment();
	}
}

static void toggle_hud_inventory(void)
{
	if (DRAW_INVENTORY == g_hud_to_draw) {
		g_hud_to_draw = DRAW_HIDE;
		return;
	}

	g_hud_to_draw = DRAW_INVENTORY;
	bzero(g_hud_heading, HUD_HEADING_SIZE);
	strcpy(g_hud_heading, "INVENTORY");
	g_cursor_index = 0;
}

static void toggle_hud_status(void)
{
	if (DRAW_STATUS == g_hud_to_draw) {
		g_hud_to_draw = DRAW_HIDE;
		return;
	}

	bzero(g_hud_heading, HUD_HEADING_SIZE);
	strcpy(g_hud_heading, "STATUS");
	g_hud_to_draw = DRAW_STATUS;
}

static void toggle_hud_equipment(void)
{
	if (DRAW_EQUIPMENT == g_hud_to_draw) {
		g_hud_to_draw = DRAW_HIDE;
		return;
	}

	bzero(g_hud_heading, HUD_HEADING_SIZE);
	strcpy(g_hud_heading, "EQUIPMENT");
	g_hud_to_draw = DRAW_EQUIPMENT;
}

static void move_cursor(const enum cursor_movement movement)
{
	int new_cursor;

	if (CURSOR_DOWN == movement) {
		new_cursor = g_cursor_index + 1;
	}

	if (CURSOR_UP == movement) {
		new_cursor = g_cursor_index - 1;
	}

	if (new_cursor < 0 || new_cursor > HUD_ROWS - 1) {
		// Out of bounds
		return;
	}

	g_cursor_index = new_cursor;
}

static void select_operation_for_item(int cursor_index)
{
	struct actor* player;
	struct item* selected_item;

	player = get_player();
	selected_item = actor_get_item(player, cursor_index);

	set_selected_item(selected_item);
	set_hud_select_item_operation(selected_item);
}

static void set_hud_hide(void)
{
	g_hud_to_draw = DRAW_HIDE;
}

static void set_hud_select_item_operation(struct item* const selected_item)
{
	bzero(g_hud_heading, HUD_HEADING_SIZE);
	strcpy(g_hud_heading, "For item - ");
	strcat(g_hud_heading, selected_item->name);
	strcat(g_hud_heading, ", do");
	g_hud_to_draw = DRAW_SELECT_ITEM_OPERATION;
	g_cursor_index = 0;
}

static void apply_operation_to_item(struct item* const selected_item, struct item_operation* operation)
{
	LOG_INFO("apply operation %s for item %s\n", operation->name, selected_item->name);
	operation->apply(selected_item);
	set_hud_hide();
}

static void update_player(int* const pressed_key)
{
	struct actor* const player = get_player();

	if (is_direction_button(pressed_key) || is_wait_button(pressed_key)) {
		update_position(key_to_position_update(pressed_key), player);
		*pressed_key = 0;
	}

	update_player_items(player);
}

static void update_player_items(struct actor* const player)
{
	struct item** const inventory = actor_get_inventory(player);
	const int inventory_size = actor_get_inventory_size();

	for (int i = 0; i < inventory_size; i++) {
		if (0 == inventory[i]) {
			continue;
		}

		if (inventory[i]->consumable) {
			item_charge_refill(inventory[i]);
		}
	}
}

void update_position(
		enum position_update update,
		struct actor* const actor)
{
	int new_position_row = actor->row;
	int new_position_col = actor->col;

	if (POSITION_UPDATE_WAIT == update) {
		return;
	}

	if (POSITION_UPDATE_DOWN == update) {
		new_position_row = actor->row + 1;
	}

	if (POSITION_UPDATE_UP == update) {
		new_position_row = actor->row - 1;
	}

	if (POSITION_UPDATE_LEFT == update) {
		new_position_col = actor->col - 1;
	}

	if (POSITION_UPDATE_RIGHT == update) {
		new_position_col = actor->col + 1;
	}

	if (!tile_is_traversable_terrain(new_position_row, new_position_col)) {
		return;
	}

	if (tile_is_occupied(new_position_row, new_position_col)) {
		interact_with_occupant_of(new_position_row, new_position_col, actor);
		return;
	}

	g_stage[actor->row][actor->col].occupant = 0;
	actor->row = new_position_row;
	actor->col = new_position_col;
	g_stage[actor->row][actor->col].occupant = actor;
}

static void update_all_hostile_actors()
{
	struct actor** const hostile_actors = get_all_hostile_actors();

	for (int i = 0; i < ALL_HOSTILE_ACTORS_SIZE; i++) {
		if (0 != hostile_actors[i]) {
			update_hostile_actor(hostile_actors[i]);
		}
	}
}

static void update_hostile_actor(struct actor* const ha)
{
	enum position_update next_movement;

	next_movement = movement_towards_player(ha);
	update_position(next_movement, ha);
}
