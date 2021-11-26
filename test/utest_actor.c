#include <criterion/criterion.h>
#include "../src/actor.h"
#include "../src/util_poet.h"

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
	spawn_player(2, 2, get_all_actors());
	cr_expect(1 == player_has_spawned());
}

Test(actor, player_get_coordinates)
{
	spawn_player(2, 2, get_all_actors());
	cr_expect(2 == get_actor_col(get_player()));
	cr_expect(2 == get_actor_row(get_player()));
}

Test(actor, player_change_coordinates)
{
	spawn_player(2, 2, get_all_actors());
	set_actor_row(get_player(), 4);
	set_actor_col(get_player(), 4);
	cr_expect(4 == get_actor_col(get_player()));
	cr_expect(4 == get_actor_row(get_player()));
}

Test(actor, player_spawn_sets_tile_as_occupied)
{
	cr_expect(0 == tile_is_occupied(2, 2));
	spawn_player(2, 2, get_all_actors());
	cr_expect(1 == tile_is_occupied(2, 2));
}

Test(actor, player_coordinate_change_unoccupies_tile)
{
	spawn_player(2, 2, get_all_actors());
	cr_expect(1 == tile_is_occupied(2, 2));
	set_actor_row(get_player(), 4);
	set_actor_col(get_player(), 4);
	cr_expect(0 == tile_is_occupied(2, 2));
}

Test(actor, player_coordinate_change_occupies_tile)
{
	spawn_player(2, 2, get_all_actors());
	set_actor_row(get_player(), 4);
	set_actor_col(get_player(), 4);
	cr_expect(1 == tile_is_occupied(4, 4));
}
