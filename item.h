#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#include "draw.h.const"

#define ITEM_OPERATIONS_SIZE HUD_ROWS

struct item {
	int amount;
	char consumable;
	char name[32];
	int all_items_index;
	/* int supported_item_operations[ITEM_OPERATIONS_SIZE] */
};

struct item_operation {
	char name[32];
	void (*apply) (struct item* const subject);
};

extern struct item* g_selected_item;
extern struct item_operation* g_item_operations[ITEM_OPERATIONS_SIZE];

struct item* get_selected_item(void);
void set_selected_item(struct item* new_item);
struct item_operation* get_item_operation(int index);

void apply_operation_use(struct item* subject);
void apply_operation_equip(struct item* subject);
void apply_operation_drop(struct item* subject);

#endif
