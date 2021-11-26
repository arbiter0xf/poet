#ifndef INTERACT_H_DEFINED
#define INTERACT_H_DEFINED

#include "actor.h"
#include "draw.h"
#include "item.h"
#include "stage.h"

void interact_with_occupant_of(int row, int col, struct actor* const initiator);
void get_picked(struct actor* const self, struct actor* const initiator);
void greet(struct actor* const self, struct actor* const initiator);
void add_to_inventory(struct item* item_to_add, struct item** inventory);
void transfer_inventory_content(struct item** inventory_from, struct item** inventory_to);
void initiate_trade(struct actor* const self, struct actor* const initiator);
void transport_to_stage(struct actor* const self, struct actor* const initiator);

#endif
