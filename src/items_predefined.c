#include "items_predefined.h"

#include "util_poet.h"
#include "log.h"

static void apply_small_potion(struct actor* const target, struct item* const self);

struct item* spawn_small_potion(void)
{
	return spawn_item_consumable("Small potion", apply_small_potion, 5);
}

static void apply_small_potion(struct actor* const target, struct item* const self)
{
	if (item_get_charges(self) > 0) {
		actor_hitpoints_increase(target, 20);
		item_charge_spend(self);
	}
}
