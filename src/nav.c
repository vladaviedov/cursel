/**
 * @file nav.c
 * @author Vladyslav Aviedov <vladaviedov at protonmail dot com>
 * @date 2024
 * @license LGPLv3.0
 * @brief Navigation menu builder.
 */
#include "nav.h"

#include <ncurses.h>
#include <stdint.h>

#include "state.h"

typedef enum {
	CS_CONTENT_NORMAL,
	CS_CONTENT_SELECTED,
	CS_CONTENT_DISABLED
} content_state;

void cs_show_nav(WINDOW *win, const cs_nav *nav) {
	keypad(stdscr, 1);
	int width = getmaxx(win);
	int height = getmaxy(win);

	int running = 1;

	uint32_t selected = 0;
	int show_desc = 0;

	cs_theme *theme = (nav->theme_override != NULL)
						  ? nav->theme_override
						  : &global_state.theme;

	while (running) {
		if (nav->render_hook != NULL) {
			nav->render_hook();
		}

		wclear(win);

		box(win, 0, 0);
		mvwprintw(win, 0, 1, "%s", nav->menu_name);

		uint32_t desc_shift = 0;
		for (uint32_t i = 0; i < nav->entry_count; i++) {
			wmove(win, i + 2 + desc_shift, 1);

			cs_entry *entry = nav->entries + i;
			cs_theme_element theme_item;

			if (i == selected) {
				if (entry->disabled) {
					theme_item = theme->sel_dis;
				} else {
					theme_item = theme->selected;
				}
			} else {
				if (entry->disabled) {
					theme_item = theme->disabled;
				} else {
					theme_item = theme->normal;
				}
			}

			if (global_state.use_color) {
				wattron(win, COLOR_PAIR(theme_item.color_pair));
				wprintw(win, "  ");
			} else {
				wprintw(win, "%c ", theme_item.decorator);
			}

			wprintw(win, "%s", entry->title);

			if (global_state.use_color) {
				wattroff(win, COLOR_PAIR(theme_item.color_pair));
			}

			if (show_desc && i == selected) {
				wmove(win, i + 3, 3);

				if (global_state.use_color) {
					wattron(win, COLOR_PAIR(theme->description.color_pair));
					wprintw(win, "  ");
				} else {
					wprintw(win, "%c ", theme->description.decorator);
				}

				wprintw(win, "%s", entry->description);

				if (global_state.use_color) {
					wattroff(win, COLOR_PAIR(theme_item.color_pair));
				}

				desc_shift = 1;
			}
		}

		wrefresh(win);

		switch (wgetch(stdscr)) {
		case KEY_DOWN: // fallthrough
		case 'j':
			if (selected < nav->entry_count - 1) {
				selected++;
			}
			break;
		case KEY_UP: // fallthrough
		case 'k':
			if (selected > 0) {
				selected--;
			}
			break;
		case '\n':
			if (nav->entries[selected].disabled) {
				break;
			}

			if (nav->entries[selected].override != NULL) {
				nav->entries[selected].override(selected);
			} else {
				nav->select(selected);
			}
			break;
		case KEY_F(1):
			show_desc = !show_desc;
			break;
		case 'q':
			running = 0;
			break;
		}
	}
}
