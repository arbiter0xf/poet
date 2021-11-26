#include <string.h>

#include "actor.h"
#include "item.h"
#include "log.h"

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

void apply_operation_use(struct item* subject)
{
	LOG_DEBUG("%s\n", "apply_operation_use()");
}

void apply_operation_equip(struct item* subject)
{
	void (*op_equip) (struct item* const item_to_equip) = get_player_op_equip();
	op_equip(subject);
}

void apply_operation_drop(struct item* subject)
{
	LOG_DEBUG("%s\n", "apply_operation_drop()");
}
