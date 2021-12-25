#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "items_predefined.h"
#include "log.h"
#include "util_poet.h"

struct item* g_selected_item = 0;
struct item* g_all_items[ALL_ITEMS_SIZE] = {0};
struct item_operation* g_item_operations[ITEM_OPERATIONS_SIZE] = {0};

struct item** get_all_items(void)
{
	return g_all_items;
}

struct item* get_selected_item(void)
{
	return g_selected_item;
}

void set_selected_item(struct item* new_item)
{
	g_selected_item = new_item;
}

struct item_operation* get_item_operation(int index)
{
	return g_item_operations[index];
}

void apply_operation_use(struct item* object_item)
{
	void (*op_use) (struct item* const item_to_use) = get_player_op_use();
	op_use(object_item);
}

void apply_operation_equip(struct item* object_item)
{
	void (*op_equip) (struct item* const item_to_equip) = get_player_op_equip();
	op_equip(object_item);
}

void apply_operation_drop(struct item* subject)
{
	LOG_DEBUG("%s\n", "apply_operation_drop()");
}

struct item* spawn_item_consumable(
		struct item ** const all_items,
		int first_free,
		const char* name,
		void (*affect) (struct actor* const user))
{
	all_items[first_free] = malloc(sizeof(struct item));
	all_items[first_free]->consumable = 1;
	strcpy(all_items[first_free]->name, name);
	all_items[first_free]->all_items_index = first_free;
	all_items[first_free]->suitable_equipment_slot = EQUIPMENT_SLOT_NONE;
	all_items[first_free]->affect = affect;

	return all_items[first_free];
}

struct item* spawn_item_equipment(
		struct item ** const all_items,
		int first_free,
		const char* name,
		int suitable_slot)
{
	all_items[first_free] = malloc(sizeof(struct item));
	all_items[first_free]->consumable = 0;
	strcpy(all_items[first_free]->name, name);
	all_items[first_free]->all_items_index = first_free;
	all_items[first_free]->suitable_equipment_slot = suitable_slot;

	return all_items[first_free];
}

struct item* spawn_item(
		struct item ** const all_items,
		int quality,
		enum spawn_item_type type)
{
	struct item* new_item = 0;
	int first_free = -1;

	first_free = get_first_free_item_slot(all_items);

	if (-1 == first_free) {
		LOG_ERROR("%s", "No free item slots when spawning item");
		return 0;
	}

	if (SPAWN_ITEM_TYPE_RANDOM == type) {
		if (0 == random() % 2) {
			new_item = spawn_small_potion();
		} else {
			new_item =  spawn_item_equipment(
					all_items,
					first_free,
					"dagger",
					EQUIPMENT_SLOT_RIGHT_HAND);
		}
	} else if (SPAWN_ITEM_TYPE_CONSUMABLE == type) {
		new_item = spawn_small_potion();
	} else if (SPAWN_ITEM_TYPE_EQUIPMENT == type) {
		new_item = spawn_item_equipment(
				all_items,
				first_free,
				"dagger",
				EQUIPMENT_SLOT_RIGHT_HAND);
	}

	return new_item;
}

void add_to_inventory(struct item* item_to_add, struct item** inventory)
{
	int first_free = -1;
#if 0
	char str_debug[DEBUG_MESSAGE_SIZE];

	strcpy(str, "add_to_inventory() adding item: ");
	strcat(str, item_to_add->name);
	move(ROW_DEBUG_ZERO + g_row_debug_current, COL_DEBUG_ZERO);
	g_row_debug_current++;
	printw("%s", str);
#endif

	first_free = get_first_free_inventory_slot(inventory);
	if (-1 == first_free) {
		strcpy(g_new_announcement, "Inventory full");
		announce(g_new_announcement);
		return;
	}

	inventory[first_free] = item_to_add;
}

void transfer_inventory_content(struct item** inventory_from, struct item** inventory_to)
{
	int i = 0;

	while (0 != inventory_from[i] && i < ACTOR_INVENTORY_SIZE) {
		add_to_inventory(inventory_from[i], inventory_to);
		inventory_from[0] = 0;
		i++;
	}
}
