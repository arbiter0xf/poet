#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#include "actor.h.types"
#include "draw.h.types"
#include "item.h.types"

extern struct item* g_selected_item;
extern struct item* g_all_items[ALL_ITEMS_SIZE];
extern struct item_operation* g_item_operations[ITEM_OPERATIONS_SIZE];

struct item** get_all_items(void);
struct item* get_selected_item(void);
void set_selected_item(struct item* new_item);
struct item_operation* get_item_operation(int index);

void apply_operation_use(struct item* object_item);
void apply_operation_equip(struct item* object_item);
void apply_operation_drop(struct item* object_item);

struct item* spawn_item_consumable(
		const char* name,
		void (*consume) (struct actor* const user, struct item* const self),
		const int charges_max);
struct item* spawn_item_equipment(
		struct item** const all_items,
		int first_free,
		const char* name,
		int suitable_slot);
struct item* spawn_item(
		struct item** const all_items,
		int quality,
		enum spawn_item_type type);

void transfer_inventory_content(struct item** inventory_from, struct item** inventory_to);
void add_to_inventory(struct item* item_to_add, struct item** inventory);

void item_charge_decrement(struct item* const i);
int item_get_charges(struct item* const i);

#endif
