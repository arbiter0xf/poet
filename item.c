#include <string.h>

#include "item.h"
#include "log.h"

struct item* g_selected_item = 0;

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
	LOG_DEBUG("%s\n", "apply_operation_equip()");
}

void apply_operation_drop(struct item* subject)
{
	LOG_DEBUG("%s\n", "apply_operation_drop()");
}