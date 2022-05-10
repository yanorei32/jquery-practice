#define TERMINAL_COLOR 0x1d, 0x1f, 0x21
#include "jquery.h"

signed main() {
	$(
		"<h1>",
		(json){ text: "Hello World" }
	).css("background-color", "white")
	 .css("color", "black")
	 .appendTo("body");

	$(
		"<p>",
		(json){ text: "Italic + Red" }
	).css("font-style", "italic")
	 .css("color", "red")
	 .appendTo("body");

	$(
		"<p>",
		(json){ text: "Strike + Underline" }
	).css("text-decoration", "line-through underline")
	 .appendTo("body");

	$(
		"<p>",
		(json){ text: "Hex Color" }
	).css("background-color", "#e34234")
	 .css("color", "#ee6")
	 .appendTo("body");

	$(
		"<p>",
		(json){ text: "Hex Color (opacity-emulation)" }
	).css("background-color", "#e3423488")
	 .css("color", "#ee68")
	 .appendTo("body");

	$(
		"<p>",
		(json){ text: "Hex Color (opacity-emulation)" }
	).css("background-color", "#e3423444")
	 .css("color", "#ee64")
	 .appendTo("body");

	$(
		"<p>",
		(json){ text: "Hex Color (opacity-emulation)" }
	).css("background-color", "#e3423522")
	 .css("color", "#ee62")
	 .appendTo("body");
}
