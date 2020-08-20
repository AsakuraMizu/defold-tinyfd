# Tiny File Dialog for Defold

Tiny cross-platform (OSX, Windows, Linux) native dialogs for Defold.

Based on zlib licensed [tinyfiledialog](http://tinyfiledialogs.sourceforge.net) with [some modifications](#modifications).

## Modifications

+ ~~Added platform define guards since Defold Native Extensions currently compiles everything in the src directory.~~
+ Change `malloc` to `(wchar_t *)malloc` in `tinyfiledialogs.c` at [L1093](tinyfd/src/tinyfiledialogs/tinyfiledialogs.c#L3)
