#ifndef DRAW_H_DEFINED
#define DRAW_H_DEFINED

#include <ncurses.h>

#include "actor.h"
#include "item.h.types"
#include "stage.h"

enum hud_draw {
	DRAW_HIDE,
	DRAW_INVENTORY,
	DRAW_STATUS,
	DRAW_EQUIPMENT,
	DRAW_SELECT_ITEM_OPERATION,
};

extern enum hud_draw g_hud_to_draw;
extern char g_hud_heading[HUD_HEADING_SIZE];
extern int g_cursor_index;

void draw(struct actor ** const all_actors);
void draw_stage(void);
void draw_hud_select_item_operation(
		struct item_operation** operations,
		const int cursor_pos);
void draw_hud_inventory(
		struct item** inventory,
		const int cursor_pos);
void draw_hud_hide(void);
void draw_hud_status(void);
void draw_hud_equipment(void);
void draw_hud_stage_name(void);
void draw_hud(void);

#endif
