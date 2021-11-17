#ifndef DRAW_H_DEFINED
#define DRAW_H_DEFINED

#include <ncurses.h>

#include "actor.h"
#include "item.h"
#include "stage.h"

#define HUD_ROWS 24
#define HUD_HEADING_SIZE 64

#define ROW_HUD_ZERO ROW_STAGE_ZERO
#define COL_HUD_ZERO COL_MAX + COL_STAGE_ZERO + 3

#define ITEM_OPERATIONS_SIZE HUD_ROWS

struct item_operation {
	char name[32];
};

enum hud_draw {
	DRAW_HIDE,
	DRAW_INVENTORY,
	DRAW_STATUS,
	DRAW_EQUIPMENT,
	DRAW_SELECT_ITEM_OPERATION,
};

void draw(struct actor ** const all_actors);
void draw_layer_terrain(void);
void draw_layer_actors(struct actor ** const all_actors);
void draw_hud_select_item_operation(
		struct item_operation** operations,
		const int cursor_pos);
void draw_hud_inventory(
		struct item** inventory,
		const int cursor_pos);
void draw_hud_hide(void);
void draw_hud_status(struct actor* player);
void draw_hud_equipment(void);
void draw_hud_stage_name(void);
void draw_layer_hud();

extern struct item_operation* g_item_operations[ITEM_OPERATIONS_SIZE];
extern enum hud_draw g_hud_to_draw;
extern char g_hud_heading[HUD_HEADING_SIZE];
extern int g_cursor_index;

#endif