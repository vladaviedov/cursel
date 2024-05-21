#include <ncurses.h>
#include <stdint.h>
#include <time.h>

#include <cursel/nav.h>
#include <cursel/options.h>

static void select(uint32_t index);

static WINDOW *out_win = NULL;

int main(void) {
	// Initialize
	if (!cs_init()) {
		return 1;
	}
	if (!cs_theme_default(1)) {
		return 1;
	}

	// Make window
	WINDOW *menu_win = newwin(15, 30, 0, 0);
	out_win = newwin(3, 30, 0, 30);
	refresh();

	cs_entry entries[] = {
		[0] = {
			.disabled = 0,
			.title = "Item 1",
			.override = NULL,
			.description = "First item description",
		},
		[1] = {
			.disabled = 0,
			.title = "Item 2",
			.override = NULL,
			.description = "Second item description",
		},
		[2] = {
			.disabled = 1,
			.title = "Disabled Item 3",
			.override = NULL,
			.description = "Disabled item description",
		},
		[3] = {
			.disabled = 0,
			.title = "Item 4",
			.override = NULL,
			.description = "Last item description",
		},
	};
	cs_nav nav_menu = {
		.menu_name = "Example Menu",
		.entries = entries,
		.entry_count = sizeof(entries) / sizeof(cs_entry),
		.theme_override = NULL,
		.select = &select,
		.render_hook = NULL,
	};

	cs_show_nav(menu_win, &nav_menu);

	endwin();
	return 0;
}

static void select(uint32_t index) {
	wclear(out_win);
	box(out_win, 0, 0);
	mvwprintw(out_win, 1, 1, "Selected index: %u", index);
	wrefresh(out_win);
}
