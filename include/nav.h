#pragma once

#include <stdint.h>
#include <ncurses.h>

#include "options.h"

typedef union {
	char *preset;
	char *(*dynamic)(uint32_t);
} cs_content_value;

typedef struct {
	int is_dynamic;
	cs_content_value value;
} cs_content;

typedef struct {
	int disabled;
	cs_content title;
	cs_content description;
	void (*override)(uint32_t);
} cs_entry;

typedef struct {
	char *menu_name;
	cs_entry *entries;
	uint32_t entry_count;
	void (*select)(uint32_t);
	cs_theme *theme_override;
} cs_nav;

void cs_show_nav(WINDOW *win, const cs_nav *nav);
