#ifndef ACTOR_H_DEFINED
#define ACTOR_H_DEFINED

#include "actor.h.types"
#include "announce.h"
#include "interact.h"
#include "item.h.types"

extern struct actor* g_all_actors[ALL_ACTORS_SIZE];
extern struct actor* g_hostile_actors[ALL_ACTORS_SIZE];
extern int g_all_actors_player_index;
extern int g_selected_item_index;

extern struct item* g_stored_player_inventory[ACTOR_INVENTORY_SIZE];
extern struct item* g_stored_player_equipment[ACTOR_EQUIPMENT_SIZE];

struct actor*	get_player(void);
struct actor**	get_all_actors(void);
struct actor**	get_all_hostile_actors(void);
struct item**	get_actor_inventory(struct actor* const a);
struct item**	get_actor_equipment(struct actor* const a);
struct item*	get_actor_item(struct actor* const a, int index);
int		get_actor_row(struct actor* const a);
int		get_actor_col(struct actor* const a);
int		get_actor_is_hostile(struct actor* const a);
char*		get_actor_name(struct actor* const a);
int		actor_get_hitpoints(struct actor* const a);
int		actor_get_hitpoints_max(struct actor* const a);
int		actor_get_damage_unarmed(struct actor* const a);
int		actor_get_damage_armed(struct actor* const a);
int		player_get_selected_item_index(void);
void		(*get_player_op_equip(void)) (struct item* const item_to_equip);
void		(*get_player_op_use(void)) (struct item* const item_to_use);
void		actor_hitpoints_increase(struct actor* const, int inc_amount);
void		set_actor_row(struct actor* const a, int new_row);
void		set_actor_col(struct actor* const a, int new_col);
void		actor_set_base_damage_unarmed(struct actor* const a, int base_damage);
void		actor_set_base_damage_armed(struct actor* const a, int base_damage);
void		player_set_selected_item_index(int index);
int		actor_is_armed(struct actor* const a);
int		player_has_spawned(void);
void		player_store_state(void);
void		player_restore_state(void);
void		actor_calculate_damage(struct actor* const a);
int		actor_reduce_damage(struct actor* const a, unsigned int damage);
void		actor_hitpoints_reduce(struct actor* const a, unsigned int reduction);
void		actor_take_damage(struct actor* const a, unsigned int damage);

void despawn_actor(struct actor* const self);
void despawn_all_actors(void);
void spawn_item_drop(
		const int row,
		const int col,
		struct actor ** const all_actors,
		struct item ** const all_items,
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
		const int col,
		struct actor ** const all_actors);
struct actor* spawn_actor_skeleton(int row, int col);

#endif
