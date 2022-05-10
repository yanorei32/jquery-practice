#include <stdio.h>
#include <string.h>
#define BIG_STRING   16384
#define SHORT_STRING    16

struct jQueryRet {
	void (*appendTo)(char*);
	struct jQueryRet (*css)(char*, char*);
} typedef jQueryRet;

struct {
	char* text;
} typedef jQueryReq;

jQueryReq typedef json;

struct {
	char tag[SHORT_STRING];
	char text[BIG_STRING];
	char color[SHORT_STRING];
	char bgcolor[SHORT_STRING];
	struct {
		unsigned int underline : 1, italic : 1, strike : 1;
	} style;
} typedef jQueryState;

static jQueryState state;

unsigned char hex2int(char c) {
	return '0' <= c && c <= '9' ? c - '0' : c - 'a' + 10;
}

unsigned char expandhex(char c) {
	unsigned char v = hex2int(c);
	return v * 16 + v;
}

unsigned char get2digit(char *s) {
	return hex2int(s[0]) * 16 + hex2int(s[1]);
}

/* 0: successful, 1: failed */
int col2seq(char *sequence, char *color) {
	unsigned char r, g, b;

	if (!strcmp(color, "black"))
		strcpy(sequence, "0");
	else if (!strcmp(color, "red"))
		strcpy(sequence, "1");
	else if (!strcmp(color, "green"))
		strcpy(sequence, "2");
	else if (!strcmp(color, "yellow"))
		strcpy(sequence, "3");
	else if (!strcmp(color, "blue"))
		strcpy(sequence, "4");
	else if (!strcmp(color, "magenta"))
		strcpy(sequence, "5");
	else if (!strcmp(color, "cyan"))
		strcpy(sequence, "6");
	else if (!strcmp(color, "white"))
		strcpy(sequence, "7");
	else if (color[0] == '#') {
		switch(strlen(++color)) {
			case 3:
				r = expandhex(color[0]),
				g = expandhex(color[1]),
				b = expandhex(color[2]);
				break;

			case 6:
				r = get2digit(color),
				g = get2digit(color+2),
				b = get2digit(color+4);
				break;

			default:
				return 1;
		}

		sprintf(sequence, "8;2;%d;%d;%d", r, g, b);
	} else return 1;

	return 0;
}

void appendTo(char*) {
	char seq[32] = {0};

	if (!strcmp(state.tag, "<h1>"))
		printf("\e[1m");

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

	printf("%s\e[0m\n", state.text);
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
	state = (jQueryState) { "", "", "", "", { 0, 0, 0 } };
	strcpy(state.tag, tag);
	strcpy(state.text, v.text);
	return (jQueryRet) { appendTo, css };
}
