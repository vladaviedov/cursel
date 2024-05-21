/**
 * @file state.h
 * @author Vladyslav Aviedov <vladaviedov at protonmail dot com>
 * @date 2024
 * @license LGPLv3.0
 * @brief Internal library state.
 */
#pragma once

#include "options.h"

typedef struct {
	int use_color;
	cs_theme theme;
} cs_state;

extern cs_state global_state;
