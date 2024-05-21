/**
 * @file options.c
 * @author Vladyslav Aviedov <vladaviedov at protonmail dot com>
 * @date 2024
 * @license LGPLv3.0
 * @brief Cursel library options.
 */
#include "options.h"

#include <ncurses.h>

#include "state.h"

// No color - default decorators
#define N_COLOR_NORMAL ' '
#define N_COLOR_SELECTED '>'
#define N_COLOR_DISABLED 'x'
#define N_COLOR_SEL_DIS 'z'
#define N_COLOR_DESCRIPTION ' '

// Yes color - default colors
#define Y_COLOR_NORMAL_IDX 1
#define Y_COLOR_NORMAL_FG COLOR_WHITE
#define Y_COLOR_NORMAL_BG COLOR_BLACK

#define Y_COLOR_SELECTED_IDX 2
#define Y_COLOR_SELECTED_FG COLOR_BLACK
#define Y_COLOR_SELECTED_BG COLOR_WHITE

#define Y_COLOR_DISABLED_IDX 3
#define Y_COLOR_DISABLED_FG COLOR_RED
#define Y_COLOR_DISABLED_BG COLOR_BLACK

#define Y_COLOR_SEL_DIS_IDX 4
#define Y_COLOR_SEL_DIS_FG COLOR_RED
#define Y_COLOR_SEL_DIS_BG COLOR_WHITE

#define Y_COLOR_DESCRIPTION_IDX 5
#define Y_COLOR_DESCRIPTION_FG COLOR_YELLOW
#define Y_COLOR_DESCRIPTION_BG COLOR_BLACK

int cs_init() {
	initscr();
	if (has_colors()) {
		start_color();
	}

	return noecho() != ERR
		   && cbreak() != ERR
		   && curs_set(0) != ERR;
}

int cs_finish() {
	return endwin() != ERR;
}

int cs_theme_default(int use_color) {
	if (use_color) {
		if (!has_colors()) {
			return 0;
		}

		init_pair(Y_COLOR_NORMAL_IDX,
			Y_COLOR_NORMAL_FG,
			Y_COLOR_NORMAL_BG);
		init_pair(Y_COLOR_SELECTED_IDX,
			Y_COLOR_SELECTED_FG,
			Y_COLOR_SELECTED_BG);
		init_pair(Y_COLOR_DISABLED_IDX,
			Y_COLOR_DISABLED_FG,
			Y_COLOR_DISABLED_BG);
		init_pair(Y_COLOR_SEL_DIS_IDX,
			Y_COLOR_SEL_DIS_FG,
			Y_COLOR_SEL_DIS_BG);
		init_pair(Y_COLOR_DESCRIPTION_IDX,
			Y_COLOR_DESCRIPTION_FG,
			Y_COLOR_DESCRIPTION_BG);

		global_state.theme.normal.color_pair = Y_COLOR_NORMAL_IDX;
		global_state.theme.selected.color_pair = Y_COLOR_SELECTED_IDX;
		global_state.theme.disabled.color_pair = Y_COLOR_DISABLED_IDX;
		global_state.theme.sel_dis.color_pair = Y_COLOR_SEL_DIS_IDX;
		global_state.theme.description.color_pair = Y_COLOR_DESCRIPTION_IDX;

		global_state.use_color = 1;
	} else {
		global_state.theme.normal.decorator = N_COLOR_NORMAL;
		global_state.theme.selected.decorator = N_COLOR_SELECTED;
		global_state.theme.disabled.decorator = N_COLOR_DISABLED;
		global_state.theme.sel_dis.decorator = N_COLOR_SEL_DIS;
		global_state.theme.description.decorator = N_COLOR_DESCRIPTION;

		global_state.use_color = 0;
	}

	return 1;
}

int cs_theme_set(int use_color, cs_theme theme) {
	if (use_color && !has_colors()) {
		return 0;
	}

	global_state.use_color = use_color;
	global_state.theme = theme;

	return 1;
}
