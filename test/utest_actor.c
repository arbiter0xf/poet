#include <criterion/criterion.h>
#include "../src/actor.h"
#include "../src/util_poet.h"
#include "../src/interact.h"

#if 0
void setup(void) {
	    puts("Runs before the test");
}

void teardown(void) {
	    puts("Runs after the test");
}
#endif

Test(actor, player_has_spawned)
{
	cr_expect(0 == player_has_spawned());
	spawn_player(2, 2);
	cr_expect(1 == player_has_spawned());
}

Test(actor, player_get_coordinates)
{
	spawn_player(2, 2);
	cr_expect(2 == actor_get_col(get_player()));
	cr_expect(2 == actor_get_row(get_player()));
}

Test(actor, player_change_coordinates)
{
	spawn_player(2, 2);
	actor_set_row(get_player(), 4);
	actor_set_col(get_player(), 4);
	cr_expect(4 == actor_get_col(get_player()));
	cr_expect(4 == actor_get_row(get_player()));
}

Test(actor, player_spawn_sets_tile_as_occupied)
{
	cr_expect(0 == tile_is_occupied(2, 2));
	spawn_player(2, 2);
	cr_expect(1 == tile_is_occupied(2, 2));
}

Test(actor, player_coordinate_change_unoccupies_tile)
{
	spawn_player(2, 2);
	cr_expect(1 == tile_is_occupied(2, 2));
	actor_set_row(get_player(), 4);
	actor_set_col(get_player(), 4);
	cr_expect(0 == tile_is_occupied(2, 2));
}

Test(actor, player_coordinate_change_occupies_tile)
{
	spawn_player(2, 2);
	actor_set_row(get_player(), 4);
	actor_set_col(get_player(), 4);
	cr_expect(1 == tile_is_occupied(4, 4));
}

Test(actor, hostile_actor_get_coordinates)
{
	struct actor* a;

	a = spawn_actor(
			"orc",
			5, 8,
			ICON_ORC,
			despawn_actor,
			do_combat,
			20,
			1);

	cr_expect(1 == actor_get_is_hostile(a));
	cr_expect(5 == actor_get_row(a));
	cr_expect(8 == actor_get_col(a));

	a->op_despawn(a);
}

Test(actor, combat_with_damage_reduces_hitpoints)
{
	struct actor* a;
	struct actor* p;

	spawn_player(2, 2);
	p = get_player();
	a = spawn_actor(
			"orc",
			5, 8,
			ICON_ORC,
			despawn_actor,
			do_combat,
			20,
			1);

	actor_set_base_damage_unarmed(a, 3);
	actor_calculate_damage(a);
	actor_set_base_damage_unarmed(p, 5);
	actor_calculate_damage(p);

	cr_expect(20 == actor_get_hitpoints(a));
	cr_expect(100 == actor_get_hitpoints(p));

	do_combat(a, p);

	cr_expect(15 == actor_get_hitpoints(a));
	cr_expect(100 == actor_get_hitpoints(p));

	do_combat(p, a);

	cr_expect(15 == actor_get_hitpoints(a));
	cr_expect(97 == actor_get_hitpoints(p));
}
