Catalan Explorer
===

Catalan Explorer, or CatExp, is a little app for visualizing the interpretation
of
[Catalan Numbers](https://en.wikipedia.org/wiki/Catalan_number). The
default visualization uses lattice paths: given an N x N square grid,
the Nth Catalan number is the number of ways to draw a path from the
top left corner to the bottom right, moving only right and down, and
never dipping below the main diagonal. And given a convex polygon with
N + 2 sides, it's also the number of ways to cut that polygon into
triangles. CatExp will draw these pictures for you, letting
you switch back and forth between representations.

Installation
---
CatExp is a [Qt](http://qt.io) application written in C++11. You will
need Qt5/`qmake` and a compiler that supports C++11 to get started.

Once you've cloned or downloaded this repository, you can build CatExp
with QtCreator if you have it. If not, `cd` into the project directory,
and let's assume `qmake` links to the `qmake` binary. Then just

    mkdir build
	cd build
	qmake ../CatalanExplorer.pro
	make

This creates the `CatExp` executable in the build directory.

Usage
----
Once you've launched the application, hovering over any of the keys
will give help info. The basic idea is to click out a path using the
East and South keys, or with the right and down arrow keys. This will
then be drawn according to the visualization selected from the
drop-down menu.

The Dimension box lets you change the size of the board/path being
considered. Increasing the dimension preserves any existing path,
leaving more room to expand it. Shrinking the dimension will clear the
current path. The path thus far is recorded below the dimension box,
and the progress bars at the bottom show you how many more East/South
steps you can take. Just keep in mind, CatExp won't let you make a
move that would make South steps outnumber East steps!

To Do
---
- Full binary tree viz
- Non-crossing partition viz
