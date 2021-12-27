#ifndef UPDATE_H_DEFINED
#define UPDATE_H_DEFINED

#include "actor.h"
#include "draw.h"
#include "item.h"
#include "stage.h"
#include "user_input.h"

extern int g_ui_enabled;

void update(int* const pressed_key);
void update_position(
		enum position_update update,
		struct actor* const actor);
void update_set_ui_enabled(int enabled);
int update_is_ui_enabled(void);

#endif
