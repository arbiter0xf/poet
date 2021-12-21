#ifndef UPDATE_H_DEFINED
#define UPDATE_H_DEFINED

#include "actor.h"
#include "draw.h"
#include "item.h"
#include "stage.h"
#include "user_input.h"

void update(int* const pressed_key);
void update_position(
		enum position_update update,
		struct actor* const actor);

#endif
