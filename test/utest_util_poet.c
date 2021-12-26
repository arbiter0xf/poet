#include <criterion/criterion.h>

#include "../src/actor.h"
#include "../src/user_input.h"
#include "../src/util_poet.h"

#if 0
cr_log_warn("message");
#endif

Test(util_poet, get_movement_leading_from_actors_position_towards_player)
{
	struct actor* player;
	struct actor* skeleton;
	enum position_update movement;

	spawn_player(2, 2);
	player = get_player();
	skeleton = spawn_actor_skeleton(3, 3);

	movement = movement_towards_player(skeleton);
	cr_expect(POSITION_UPDATE_UP == movement);

	actor_set_row(skeleton, 2);
	actor_set_col(skeleton, 4);

	movement = movement_towards_player(skeleton);
	cr_expect(POSITION_UPDATE_LEFT == movement);

	actor_set_row(skeleton, 2);
	actor_set_col(skeleton, 0);

	movement = movement_towards_player(skeleton);
	cr_expect(POSITION_UPDATE_RIGHT == movement);

	actor_set_row(skeleton, 0);
	actor_set_col(skeleton, 0);

	movement = movement_towards_player(skeleton);
	cr_expect(POSITION_UPDATE_DOWN == movement);

	player->op_despawn(player);
	skeleton->op_despawn(skeleton);
}
