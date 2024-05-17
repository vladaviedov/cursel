#pragma once

#include "options.h"

typedef struct {
	int use_color;
	cs_theme theme;
} cs_state;

extern cs_state global_state;
