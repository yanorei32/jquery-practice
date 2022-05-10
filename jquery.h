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

void appendTo(char*) {
	if (!strcmp(state.tag, "<h1>"))
		printf("\e[1m");

	if (state.style.italic)
		printf("\e[3m");

	if (state.style.underline)
		printf("\e[4m");

	if (state.style.strike)
		printf("\e[9m");

	if (!strcmp(state.bgcolor, "black"))
		printf("\e[40m");
	if (!strcmp(state.bgcolor, "red"))
		printf("\e[41m");
	if (!strcmp(state.bgcolor, "green"))
		printf("\e[42m");
	if (!strcmp(state.bgcolor, "yellow"))
		printf("\e[43m");
	if (!strcmp(state.bgcolor, "blue"))
		printf("\e[44m");
	if (!strcmp(state.bgcolor, "magenta"))
		printf("\e[45m");
	if (!strcmp(state.bgcolor, "cyan"))
		printf("\e[46m");
	if (!strcmp(state.bgcolor, "white"))
		printf("\e[47m");

	if (!strcmp(state.color, "black"))
		printf("\e[30m");
	if (!strcmp(state.color, "red"))
		printf("\e[31m");
	if (!strcmp(state.color, "green"))
		printf("\e[32m");
	if (!strcmp(state.color, "yellow"))
		printf("\e[33m");
	if (!strcmp(state.color, "blue"))
		printf("\e[34m");
	if (!strcmp(state.color, "magenta"))
		printf("\e[35m");
	if (!strcmp(state.color, "cyan"))
		printf("\e[36m");
	if (!strcmp(state.color, "white"))
		printf("\e[37m");

	printf("%s", state.text);
	printf("\e[0m\n");
}

jQueryRet css(char* property, char* value) {
	if (!strcmp(property, "background-color"))
		strcpy(state.bgcolor, value);
	
	if (!strcmp(property, "color"))
		strcpy(state.color, value);

	if (!strcmp(property, "text-decoration")) {
		state.style.strike = !!strstr(value, "line-through");
		state.style.underline = !!strstr(value, "underline");
	}

	if (!strcmp(property, "font-style"))
		state.style.italic = !strcmp(value, "italic");

	return (jQueryRet) { appendTo, css };
}

jQueryRet $(char* tag, jQueryReq v) {
	state = (jQueryState) { "", "", "", "", { 0, 0, 0 } };
	strcpy(state.tag, tag);
	strcpy(state.text, v.text);
	return (jQueryRet) { appendTo, css };
}
