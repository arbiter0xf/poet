#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

#include "actor.h"
#include "item.h"

int get_first_free_inventory_slot(struct item** const inventory);
int get_first_free_actor_slot(struct actor** const actors);
int get_first_free_item_slot(struct item** const items);
int is_hud_interactive(void);
void initialize_io(void);
void teardown_io(void);
void populate_structures(void);
void unpopulate_structures(void);
void game_over(void);
int is_game_over(void);
enum position_update movement_towards_player(struct actor* const ha);
void copy_item_array(struct item** const items_src, struct item** const items_dst, const int length);

extern int g_game_over;

#endif
