#include "items_predefined.h"

#include "util_poet.h"
#include "log.h"

static void apply_small_potion(struct actor* target);

struct item* spawn_small_potion(void)
{
	return spawn_item_consumable("Small potion", apply_small_potion);
}

static void apply_small_potion(struct actor* const target)
{
	actor_hitpoints_increase(target, 20);
}
