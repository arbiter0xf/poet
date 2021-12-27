#ifndef ACTOR_H_DEFINED
#define ACTOR_H_DEFINED

#include "actor.h.types"
#include "announce.h"
#include "interact.h"
#include "item.h.types"

extern struct actor* g_all_actors[ALL_ACTORS_SIZE];
extern struct actor* g_hostile_actors[ALL_ACTORS_SIZE];
extern int g_all_actors_player_index;

extern struct item* g_stored_player_inventory[ACTOR_INVENTORY_SIZE];
extern struct item* g_stored_player_equipment[ACTOR_EQUIPMENT_SIZE];

struct actor*	get_player(void);
struct actor**	get_all_actors(void);
struct actor**	get_all_hostile_actors(void);
struct item**	actor_get_inventory(struct actor* const a);
struct item**	actor_get_equipment(struct actor* const a);
struct item*	actor_get_item(struct actor* const a, int index);
int		actor_get_inventory_size(void);
int		actor_get_row(struct actor* const a);
int		actor_get_col(struct actor* const a);
int		actor_get_is_hostile(struct actor* const a);
char*		actor_get_name(struct actor* const a);
int		actor_get_hitpoints(struct actor* const a);
int		actor_get_hitpoints_max(struct actor* const a);
int		actor_get_damage_unarmed(struct actor* const a);
int		actor_get_damage_armed(struct actor* const a);
void		(*player_get_op_equip(void)) (struct item* const item_to_equip);
void		(*player_get_op_use(void)) (struct item* const item_to_use);
void		actor_hitpoints_increase(struct actor* const, int inc_amount);
void		actor_set_row(struct actor* const a, int new_row);
void		actor_set_col(struct actor* const a, int new_col);
void		actor_set_base_damage_unarmed(struct actor* const a, int base_damage);
void		actor_set_base_damage_armed(struct actor* const a, int base_damage);
int		actor_is_armed(struct actor* const a);
int		player_has_spawned(void);
void		player_store_state(void);
void		player_restore_state(void);
void		actor_calculate_damage(struct actor* const a);
int		actor_reduce_damage(struct actor* const a, unsigned int damage);
void		actor_hitpoints_reduce(struct actor* const a, unsigned int reduction);
void		actor_take_damage(struct actor* const a, unsigned int damage);
void		actor_acquire_item(struct actor* const a, struct item* const new_item);

void despawn_actor(struct actor* const self);
void despawn_all_actors(void);
void spawn_item_drop(
		const int row,
		const int col,
		const int quality,
		enum spawn_item_type type);
struct actor* spawn_actor(
		const char* name,
		const int row,
		const int col,
		const char icon,
		void (*despawn) (struct actor* const self),
		void (*on_interact) (struct actor* const self, struct actor* const other),
		const int hitpoints_max,
		const int is_hostile);
void spawn_player(
		const int row,
		const int col);
struct actor* spawn_actor_skeleton(int row, int col);

#endif
