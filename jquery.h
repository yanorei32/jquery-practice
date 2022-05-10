/*\
| | jQuery like ANSI terminal format library
| |   https://github.com/yanorei32/jquery-practice
| |
| | It's joke. The software provided "AS IS",
| |   without warranty of any kind.
| |
| | Author:  yanorei32
| | Date:    2022-05-10
| | LICENSE: The Unlicense
\*/

#ifndef JQUERY_H
#define JQUERY_H

#include <stdio.h>
#include <string.h>
#define LONG_STRING  16384
#define SHORT_STRING    16

#ifndef TERMINAL_COLOR
#define TERMINAL_COLOR 0x00, 0x00, 0x00
#endif

static const unsigned char base_color[] = { TERMINAL_COLOR };

struct jQueryRet {
	void (*appendTo)(char*);
	struct jQueryRet (*css)(char*, char*);
} typedef jQueryRet;

struct {
	char* text;
} typedef jQueryReq;

jQueryReq typedef json;

struct {
	char text[LONG_STRING];
	char color[SHORT_STRING];
	char bgcolor[SHORT_STRING];
	struct {
		unsigned int underline : 1, italic : 1, strike : 1, bold : 1, newline: 1;
	} style;
} typedef jQueryState;

static jQueryState state;

unsigned char hex2int(char c) {
	return '0' <= c && c <= '9' ? c - '0' :
		'A' <= c && c <= 'F' ? c - 'A' + 10 :
		'a' <= c && c <= 'f' ? c - 'a' + 10 : 0;
}

unsigned char expandhex(char c) {
	unsigned char v = hex2int(c);
	return v * 16 + v;
}

unsigned char get2digit(char *s) {
	return hex2int(s[0]) * 16 + hex2int(s[1]);
}

/* 0: successful, 1: failed */
int col2seq(char *seq, char *col) {
	unsigned char r, g, b, a = 255;

	if (!strcmp(col, "black"))
		strcpy(seq, "0");
	else if (!strcmp(col, "red"))
		strcpy(seq, "1");
	else if (!strcmp(col, "green"))
		strcpy(seq, "2");
	else if (!strcmp(col, "yellow"))
		strcpy(seq, "3");
	else if (!strcmp(col, "blue"))
		strcpy(seq, "4");
	else if (!strcmp(col, "magenta"))
		strcpy(seq, "5");
	else if (!strcmp(col, "cyan"))
		strcpy(seq, "6");
	else if (!strcmp(col, "white"))
		strcpy(seq, "7");
	else if (col[0] == '#') {
		switch(strlen(++col)) {
			case 4:
				a = expandhex(col[3]);
			case 3:
				r = expandhex(col[0]),
				g = expandhex(col[1]),
				b = expandhex(col[2]);
				break;

			case 8:
				a = get2digit(col+6);
			case 6:
				r = get2digit(col),
				g = get2digit(col+2),
				b = get2digit(col+4);
				break;

			default:
				return 1;
		}

		if (a != 255) {
			float fg = (float)a / 255;
			r = base_color[0] * (1-fg) + r * fg;
			g = base_color[1] * (1-fg) + g * fg;
			b = base_color[2] * (1-fg) + b * fg;
		}

		sprintf(seq, "8;2;%d;%d;%d", r, g, b);
	} else return 1;

	return 0;
}

void appendTo(char*) {
	char seq[32] = {0};

	if (state.style.italic)
		printf("\e[3m");

	if (state.style.underline)
		printf("\e[4m");

	if (state.style.strike)
		printf("\e[9m");

	if(!col2seq(seq, state.color))
		printf("\e[3%sm", seq);

	if(!col2seq(seq, state.bgcolor))
		printf("\e[4%sm", seq);

	printf("%s\e[0m%c", state.text, state.style.newline * '\n');
	fflush(stdout);
}

jQueryRet css(char* property, char* value) {
	if (!strcmp(property, "background-color"))
		strcpy(state.bgcolor, value);
	
	else if (!strcmp(property, "color"))
		strcpy(state.color, value);

	else if (!strcmp(property, "font-style"))
		state.style.italic = !strcmp(value, "italic");

	else if (!strcmp(property, "text-decoration")) {
		state.style.strike = !!strstr(value, "line-through");
		state.style.underline = !!strstr(value, "underline");
	}

	return (jQueryRet) { appendTo, css };
}

jQueryRet $(char* tag, jQueryReq v) {
	state = (jQueryState) { "", "", "", { 0, 0, 0, 0, 1 } };

	state.style.bold = !strcmp(tag, "<h1>");
	state.style.newline = !!strcmp(tag, "<span>");

	strcpy(state.text, v.text);
	return (jQueryRet) { appendTo, css };
}

#endif
