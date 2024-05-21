/**
 * @file options.h
 * @author Vladyslav Aviedov <vladaviedov at protonmail dot com>
 * @date 2024
 * @license LGPLv3.0
 * @brief Cursel library options.
 */
#pragma once

typedef union {
	int color_pair;
	char decorator;
} cs_theme_element;

typedef struct {
	cs_theme_element normal;
	cs_theme_element selected;
	cs_theme_element disabled;
	cs_theme_element sel_dis;
	cs_theme_element description;
} cs_theme;

int cs_init();

int cs_finish();

int cs_theme_default(int use_color);

int cs_theme_set(int use_color, cs_theme theme);
