/**
 * @file nav.h
 * @author Vladyslav Aviedov <vladaviedov at protonmail dot com>
 * @date 2024
 * @license LGPLv3.0
 * @brief Navigation menu builder.
 */
#pragma once

#include <stdint.h>
#include <ncurses.h>

#include "options.h"

typedef struct {
	int disabled;
	char *title;
	char *description;
	void (*override)(uint32_t);
} cs_entry;

typedef struct {
	char *menu_name;
	cs_entry *entries;
	uint32_t entry_count;
	cs_theme *theme_override;
	void (*select)(uint32_t);
	void (*render_hook)(void);
} cs_nav;

void cs_show_nav(WINDOW *win, const cs_nav *nav);
