#include <stdio.h>
#include <string.h>
#define BIGSTRING 16384

struct jQueryRet {
	void (*appendTo)(char*);
	struct jQueryRet (*css)(char*, char*);
} typedef jQueryRet;

struct {
	char* text;
} typedef jQueryReq;

jQueryReq typedef json;

struct {
	char tag[BIGSTRING];
	char text[BIGSTRING];
	char color[BIGSTRING];
	char bgcolor[BIGSTRING];
	int underline, italic, strike;
} typedef jQueryState;

static jQueryState state;

void appendTo(char*) {
	if (!strcmp(state.tag, "<h1>"))
		printf("\e[1m");

	if (state.italic)
		printf("\e[3m");

	if (state.underline)
		printf("\e[4m");

	if (state.strike)
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
		state.strike = !!strstr(value, "line-through");
		state.underline = !!strstr(value, "underline");
	}

	if (!strcmp(property, "font-style"))
		state.italic = !strcmp(value, "italic");

	return (jQueryRet) { appendTo, css };
}

jQueryRet $(char* tag, jQueryReq v) {
	state = (jQueryState) { "", "", "", "", 0, 0, 0 };
	strcpy(state.tag, tag);
	strcpy(state.text, v.text);
	return (jQueryRet) { appendTo, css };
}
