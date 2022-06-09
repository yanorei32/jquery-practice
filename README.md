# jQuery Practice (TraditionalEdition)

jQuery like ANSI terminal formatter.

**written-in-C** (joke project)



## quick start

```bash
git clone https://github.com/yanorei32/jquery-practice
cd jquery-practice
CC main.c
./a.out
```

## example

```c
jquery(
  "<h1>",
  (json){ "Hello World" }
).css("background-color", "white")
 .css("color", "black")
 .appendTo("body");

jquery(
  "<p>",
  (json){ "Italic + Red" }
).css("font-style", "italic")
 .css("color", "red")
 .appendTo("body");

jquery(
  "<p>",
  (json){ "Strike + Underline" }
).css("text-decoration", "line-through underline")
 .appendTo("body");

/* Hex color (must support 24-bit color) */
jquery(
  "<p>",
  (json){ "Hex Color" }
).css("background-color", "#e34234")
 .css("color", "#ee6")
 .appendTo("body");

/* Hex color with opacity emulation
      (must support 24-bit color)
   TERMINAL_COLOR macro is required.
   ex) #define TERMINAL_COLOR 0x1d, 0x1f, 0x21 */
jquery(
  "<p>",
  (json){ "Hex Color (opacity-emulation)" }
).css("background-color", "#e3423511")
 .css("color", "#ee61")
 .appendTo("body");


jquery(
  "<span>",
  (json){ "Without \\n" }
).css("background-color", "#fff")
 .css("color", "#000")
 .appendTo("body");

puts();
```
