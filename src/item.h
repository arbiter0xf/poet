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
		int quality,
		enum spawn_item_type type);
void item_despawn(struct item* const item_to_despawn);

void transfer_inventory_content(struct item** inventory_from, struct item** inventory_to);
void item_add_to_inventory(struct item* item_to_add, struct item** inventory);

void item_charge_spend(struct item* const t);
void item_charge_refill(struct item* const t);
int item_get_charges(struct item* const t);
int item_is_consumable(struct item* const t);
char* item_get_name(struct item* const t);
int item_is_oneshot(struct item* const t);
void item_set_oneshot(struct item* const t, int oneshot);
int item_has_been_used(struct item* const t);
void item_set_has_been_used(struct item* const t, int has_been_used);
int item_get_inventory_index(struct item* const t);
void item_set_inventory_index(struct item* const t, int index);
void item_set_item_map(struct item* const t, struct item_map* const item_map);

void oneshot_on_consume(
		struct actor* const target,
		struct item* const self,
		void (*received_on_consume) (struct actor* const target, struct item* const self));

#endif
