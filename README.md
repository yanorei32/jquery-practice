# jQuery Practice

jQuery like ANSI terminal formatter.

**written-in-C** (joke project)


<img src=https://user-images.githubusercontent.com/11992915/167632311-ca44ace6-95f5-4e87-b189-c22848901ed5.png width=640px>

## example

```c
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

/* Hex color (must support 24-bit color) */
$(
  "<p>",
  (json){ text: "Hex Color" }
).css("background-color", "#e34234")
 .css("color", "#ee6")
 .appendTo("body");

/* Hex color with opacity emulation
      (must support 24-bit color)
   TERMINAL_COLOR macro is required.
   ex) #define TERMINAL_COLOR 0x1d, 0x1f, 0x21 */
$(
  "<p>",
  (json){ text: "Hex Color (opacity-emulation)" }
).css("background-color", "#e3423511")
 .css("color", "#ee61")
 .appendTo("body");
```
