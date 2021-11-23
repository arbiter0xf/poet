#ifndef STAGE_H_DEFINED
#define STAGE_H_DEFINED

#include <string.h>

#define STAGE_SIZE_HORIZONTAL 20
#define STAGE_SIZE_VERTICAL STAGE_SIZE_HORIZONTAL

#define STAGE_NAME_SIZE 128

#define ALL_TERRAINS_FLOOR 0
#define ALL_TERRAINS_WALL_VERTICAL 1
#define ALL_TERRAINS_WALL_HORIZONTAL 2
#define ALL_TERRAINS_COLUMN 3
#define ALL_TERRAINS_VOID 4

#define ALL_TERRAINS_SIZE 16

enum stage_type {
	STAGE_TYPE_HIDEOUT,
	STAGE_TYPE_DUNGEON,
};

struct terrain {
	char icon;
	const char name[32];
	char traversable;
};

struct tile {
	struct terrain* terrain;
	struct actor* occupant;
};

void load_stage(enum stage_type s_type, struct terrain ** const all_terrains);
int is_traversable_terrain(int row, int col);
int is_occupied(int row, int col);
void set_stage_slice_around_player(void);

extern struct terrain* g_all_terrains[ALL_TERRAINS_SIZE];
extern struct tile g_stage_slice[ROW_DRAW_STAGE_LEN][COL_DRAW_STAGE_LEN];
extern struct tile g_stage[STAGE_SIZE_VERTICAL][STAGE_SIZE_HORIZONTAL];
extern char g_stage_name[STAGE_NAME_SIZE];

#endif
