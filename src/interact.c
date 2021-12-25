#include "announce.h"
#include "interact.h"
#include "log.h"
#include "util_poet.h"

void interact_with_occupant_of(int row, int col, struct actor* const initiator)
{
	struct actor* self = 0;

	self = g_stage[row][col].occupant;
	strcpy(g_new_announcement, initiator->name);
	strcat(g_new_announcement, " interacts with ");
	strcat(g_new_announcement, self->name);
	announce(g_new_announcement);
	g_stage[row][col].occupant->op_on_interact(self, initiator);
}

void get_picked(struct actor* const self, struct actor* const initiator)
{
#if 0
	char str[DEBUG_MESSAGE_SIZE];

	strcpy(str, "get_picked() called by: ");
	strcat(str, self->name);
	strcat(str, ", initiated by: ");
	strcat(str, initiator->name);
	move(ROW_DEBUG_ZERO + g_row_debug_current, COL_DEBUG_ZERO);
	g_row_debug_current++;
	printw("%s", str);
#endif

	transfer_inventory_content(self->inventory, initiator->inventory);

	self->op_despawn(self);
}

void greet(struct actor* const self, struct actor* const initiator)
{
	strcat(g_new_announcement, self->name);
	strcat(g_new_announcement, " greets ");
	strcat(g_new_announcement, initiator->name);
	announce(g_new_announcement);
}

void initiate_trade(struct actor* const self, struct actor* const initiator)
{
	LOG_DEBUG("%s\n", "initiate_trade()");
}

void transport_to_stage(struct actor* const self, struct actor* const initiator)
{
	player_store_state();
	unload_stage();
	load_stage(STAGE_TYPE_DUNGEON);
	player_restore_state();
}

void do_combat(struct actor* const defender, struct actor* const attacker)
{
	char damage_num[32];
	unsigned int damage_attacker;
	unsigned int damage_attacker_reduced;

	if (actor_is_armed(attacker)) {
		damage_attacker = actor_get_damage_armed(attacker);
	} else {
		damage_attacker = actor_get_damage_unarmed(attacker);
	}
	damage_attacker_reduced = actor_reduce_damage(defender, damage_attacker);

	snprintf(damage_num, 32, "%d", damage_attacker_reduced);

	strcpy(g_new_announcement, attacker->name);
	strcat(g_new_announcement, " attacks ");
	strcat(g_new_announcement, defender->name);
	strcat(g_new_announcement, " and does ");
	strcat(g_new_announcement, damage_num);
	strcat(g_new_announcement, " damage");
	announce(g_new_announcement);

	LOG_DEBUG("%s\n", "next actor_take_damage()");
	actor_take_damage(defender, damage_attacker_reduced);
}
