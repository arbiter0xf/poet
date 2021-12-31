#include <criterion/criterion.h>

#include "../src/actor.h"
#include "../src/item.h"
#include "../src/items_predefined.h"
#include "../src/update.h"
#include "../src/user_input.h"

#if 0
cr_log_warn("message");
#endif

Test(item, small_potion_can_be_consumed)
{
	struct item* small_potion = spawn_small_potion();
	cr_expect(1 == small_potion->consumable);
}

Test(item, small_potion_restores_hp_to_player)
{
	struct actor* player;
	struct item* small_potion;

	spawn_player(2, 2);
	player = get_player();
	small_potion = spawn_small_potion();

	actor_hitpoints_reduce(player, 30);
	cr_expect(70 == actor_get_hitpoints(player));

	small_potion->consume(player, small_potion);
	cr_expect(90 == actor_get_hitpoints(player));
}

Test(item, small_potion_restores_hp_to_hostile_actor)
{
	struct actor* skeleton;
	struct item* small_potion;

	skeleton = spawn_actor_skeleton(2, 2);
	small_potion = spawn_small_potion();

	actor_hitpoints_reduce(skeleton, 20);
	cr_expect(5 == actor_get_hitpoints(skeleton));

	small_potion->consume(skeleton, small_potion);
	cr_expect(25 == actor_get_hitpoints(skeleton));
}

Test(item, potion_effect_capped_to_max_hp)
{
	struct actor* player;
	struct item* small_potion;

	spawn_player(2, 2);
	player = get_player();
	small_potion = spawn_small_potion();

	cr_expect(actor_get_hitpoints(player) == actor_get_hitpoints_max(player));
	small_potion->consume(player, small_potion);
	cr_expect(actor_get_hitpoints(player) == actor_get_hitpoints_max(player));
}

Test(item, potion_charge_amount_decreases_on_use)
{
	struct actor* player;
	struct item* small_potion;

	spawn_player(2, 2);
	player = get_player();
	small_potion = spawn_small_potion();

	cr_expect(5 == item_get_charges(small_potion));
	small_potion->consume(player, small_potion);
	cr_expect(4 == item_get_charges(small_potion));
}

Test(item, consuming_potion_has_no_effect_when_out_of_charges)
{
	struct actor* player;
	struct item* small_potion;

	spawn_player(2, 2);
	player = get_player();
	small_potion = spawn_small_potion();

	small_potion->consume(player, small_potion);
	small_potion->consume(player, small_potion);
	small_potion->consume(player, small_potion);
	small_potion->consume(player, small_potion);
	small_potion->consume(player, small_potion);
	cr_expect(0 == item_get_charges(small_potion));

	actor_hitpoints_reduce(player, 30);
	cr_expect(70 == actor_get_hitpoints(player));

	small_potion->consume(player, small_potion);
	cr_expect(70 == actor_get_hitpoints(player));
}

Test(item, charges_can_be_restored)
{
	struct actor* player;
	struct item* small_potion;

	spawn_player(2, 2);
	player = get_player();
	small_potion = spawn_small_potion();

	small_potion->consume(player, small_potion);
	small_potion->consume(player, small_potion);
	cr_expect(3 == item_get_charges(small_potion));

	for (int i = 0; i < 9; i++) {
		item_charge_refill(small_potion);
	}
	cr_expect(3 == item_get_charges(small_potion));

	item_charge_refill(small_potion);
	cr_expect(4 == item_get_charges(small_potion));
}

Test(item, update_restores_charges_to_items_owned_by_player)
{
	struct actor* player;
	struct item* small_potion;
	int pressed_key = BUTTON_WAIT;

	spawn_player(2, 2);
	player = get_player();
	small_potion = spawn_small_potion();

	actor_acquire_item(player, small_potion);
	small_potion->consume(player, small_potion);
	cr_expect(4 == item_get_charges(small_potion));

	update_set_ui_enabled(0);
	for (int i = 0; i < 9; i++) {
		update(&pressed_key);
	}
	cr_expect(4 == item_get_charges(small_potion));
	update(&pressed_key);
	cr_expect(5 == item_get_charges(small_potion));
}

Test(item, item_of_actor_can_be_retrieved_by_name)
{
	struct actor* skeleton;
	struct item* small_potion;

	small_potion = spawn_small_potion();
	skeleton = spawn_actor_skeleton(2, 2);
	actor_acquire_item(skeleton, small_potion);

	small_potion = actor_get_owned_item_by_name(skeleton, "Small potion");
	cr_expect(0 != small_potion);
}

Test(item, map_name_contains_map_details)
{
	struct item* map;
	char* map_name;

	spawn_player(2, 2);
	map = spawn_item_map(1, MAP_ENVIRONMENT_DUNGEON);
	map_name = item_get_name(map);

	cr_expect(0 == strcmp(map_name, "Map lvl 1 Dungeon"));
}

Test(item, map_can_be_retrieved_from_player_by_name)
{
	struct actor* player;
	struct item* map;

	spawn_player(2, 2);
	player = get_player();
	map = spawn_item_map(1, MAP_ENVIRONMENT_DUNGEON);

	actor_acquire_item(player, map);
	map = actor_get_owned_item_by_name(player, "Map lvl 1 Dungeon");
	cr_expect(0 != map);
}

Test(item, map_item_is_discarded_when_used_by_player)
{
	struct actor* player;
	struct item* map;

	spawn_player(2, 2);
	player = get_player();
	map = spawn_item_map(1, MAP_ENVIRONMENT_DUNGEON);

	actor_acquire_item(player, map);
	player->op_use(map);

	map = actor_get_owned_item_by_name(player, "Map lvl 1 Dungeon");
	cr_expect(0 == map);
}
