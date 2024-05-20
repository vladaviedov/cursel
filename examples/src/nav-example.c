#include <stdint.h>
#include <time.h>
#include <ncurses.h>

#include <cursel/nav.h>
#include <cursel/options.h>

static char *generate_desc(uint32_t index);
static char *generate_title(uint32_t index);
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
			.title.is_dynamic = 0,
			.title.value.preset = "Item 1",
			.override = NULL,
			.description.is_dynamic = 0,
			.description.value.preset = "First item description",
		},
		[1] = {
			.disabled = 0,
			.title.is_dynamic = 0,
			.title.value.preset = "Item 2",
			.override = NULL,
			.description.is_dynamic = 1,
			.description.value.dynamic = &generate_desc,
		},
		[2] = {
			.disabled = 1,
			.title.is_dynamic = 0,
			.title.value.preset = "Disabled Item",
			.override = NULL,
			.description.is_dynamic = 0,
			.description.value.preset = "First item description",
		},
		[3] = {
			.disabled = 0,
			.title.is_dynamic = 1,
			.title.value.dynamic = &generate_title,
			.override = NULL,
			.description.is_dynamic = 0,
			.description.value.preset = "Last item description",
		},
	};
	cs_nav nav_menu = {
		.menu_name = "Example Menu",
		.entries = entries,
		.entry_count = sizeof(entries) / sizeof(cs_entry),
		.select = &select,
		.theme_override = NULL,
	};

	cs_show_nav(menu_win, &nav_menu);

	endwin();
	return 0;
}

static char desc_buffer[128];

static char *generate_desc(uint32_t index) {
	time_t timestamp = time(NULL);
	struct tm *time_data = localtime(&timestamp);
	snprintf(desc_buffer, 128, "Current time: %02d:%02d:%02d",
		time_data->tm_hour,
		time_data->tm_min,
		time_data->tm_sec);

	return desc_buffer;
}

static uint32_t counter = 0;
static char title_buffer[128];

static char *generate_title(uint32_t index) {
	counter++;
	snprintf(title_buffer, 128, "Menu refreshed %u times", counter);

	return title_buffer;
}

static void select(uint32_t index) {
	wclear(out_win);
	box(out_win, 0, 0);
	mvwprintw(out_win, 1, 1, "Selected index: %u", index);
	wrefresh(out_win);
}
