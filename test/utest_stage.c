#include <criterion/criterion.h>

#include "../src/stage.h"
#include "../src/update.h"
#include "../src/user_input.h"
#include "../src/util_poet.h"

#if 0
cr_log_warn("message");
#endif

void setup(void) {
	populate_structures();
}

void teardown(void) {
	unpopulate_structures();
}

Test(stage, columns_in_rect_corners, .init = setup, .fini = teardown)
{
	load_stage(STAGE_TYPE_TEST1);
	cr_expect(1 == tile_is_column(&(g_stage[2][2])));
	cr_expect(1 == tile_is_column(&(g_stage[2][8])));
	cr_expect(1 == tile_is_column(&(g_stage[8][2])));
	cr_expect(1 == tile_is_column(&(g_stage[8][8])));
}

Test(stage, rect_surrounded_by_void, .init = setup, .fini = teardown)
{
	load_stage(STAGE_TYPE_TEST1);

	for (int i = 1; i <= 9; i++) {
		cr_expect(1 == tile_is_void(&(g_stage[i][1])));
	}
	for (int i = 1; i <= 9; i++) {
		cr_expect(1 == tile_is_void(&(g_stage[1][i])));
	}
	for (int i = 1; i <= 9; i++) {
		cr_expect(1 == tile_is_void(&(g_stage[i][9])));
	}
	for (int i = 1; i <= 9; i++) {
		cr_expect(1 == tile_is_void(&(g_stage[9][i])));
	}
}

Test(stage, player_items_retained_on_stage_transport, .init = setup, .fini = teardown)
{
	struct actor* player;

	load_stage(STAGE_TYPE_TEST2);
	player = get_player();

	cr_expect(0 == player->inventory[0]);
	update_position(POSITION_UPDATE_RIGHT, player); // Hit item drop
	cr_expect(0 != player->inventory[0]);

	update_position(POSITION_UPDATE_DOWN, player); // Hit portal

	// Player should have been despawned during stage transport
	player = get_player();

	cr_expect(2 == get_actor_row(player)); // Coordinates of new stage
	cr_expect(2 == get_actor_col(player));
	cr_expect(0 != player->inventory[0]); // Items retained
}
