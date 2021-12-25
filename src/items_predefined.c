#include "items_predefined.h"

#include "util_poet.h"
#include "log.h"

static void apply_small_potion(struct actor* target);

struct item* spawn_small_potion(void)
{
	struct item** all_items;
	int first_free;

	all_items = get_all_items();
	first_free = get_first_free_item_slot(all_items);

	if (-1 == first_free) {
		LOG_ERROR("%s", "No free item slots when spawning item");
		return 0;
	}

	return spawn_item_consumable(all_items, first_free, "Small potion", apply_small_potion);
}

static void apply_small_potion(struct actor* const target)
{
	actor_hitpoints_increase(target, 20);
}
