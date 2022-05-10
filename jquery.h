#include <stdio.h>
#include <string.h>
#define BIGSTRING 65536

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
static char HTML[BIGSTRING];

void appendTo(char*) {
	if (!strcmp(state.tag, "<h1>"))
		strcat(HTML, "\e[1m");

	if (state.italic)
		strcat(HTML, "\e[3m");

	if (state.underline)
		strcat(HTML, "\e[4m");

	if (state.strike)
		strcat(HTML, "\e[9m");

	if (!strcmp(state.bgcolor, "black"))
		strcat(HTML, "\e[40m");
	if (!strcmp(state.bgcolor, "red"))
		strcat(HTML, "\e[41m");
	if (!strcmp(state.bgcolor, "green"))
		strcat(HTML, "\e[42m");
	if (!strcmp(state.bgcolor, "yellow"))
		strcat(HTML, "\e[43m");
	if (!strcmp(state.bgcolor, "blue"))
		strcat(HTML, "\e[44m");
	if (!strcmp(state.bgcolor, "magenta"))
		strcat(HTML, "\e[45m");
	if (!strcmp(state.bgcolor, "sean"))
		strcat(HTML, "\e[46m");
	if (!strcmp(state.bgcolor, "white"))
		strcat(HTML, "\e[47m");

	if (!strcmp(state.color, "black"))
		strcat(HTML, "\e[30m");
	if (!strcmp(state.color, "red"))
		strcat(HTML, "\e[31m");
	if (!strcmp(state.color, "green"))
		strcat(HTML, "\e[32m");
	if (!strcmp(state.color, "yellow"))
		strcat(HTML, "\e[33m");
	if (!strcmp(state.color, "blue"))
		strcat(HTML, "\e[34m");
	if (!strcmp(state.color, "magenta"))
		strcat(HTML, "\e[35m");
	if (!strcmp(state.color, "sean"))
		strcat(HTML, "\e[36m");
	if (!strcmp(state.color, "white"))
		strcat(HTML, "\e[37m");

	strcat(HTML, state.text);
	strcat(HTML, "\e[0m\n");
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

void reset() {
	HTML[0] = 0;
}

void render() {
	printf("%s", HTML);
	reset();
}
