#ifndef UTIL_H_DEFINED
#define UTIL_H_DEFINED

#include "actor.h"
#include "item.h"

int get_first_free_inventory_slot(struct item** const inventory);
int get_first_free_actor_slot(struct actor** const actors);
int get_first_free_item_slot(struct item** const items);
int is_hud_interactive(void);

#endif
