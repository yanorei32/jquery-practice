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
}
