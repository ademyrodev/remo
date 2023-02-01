# Remo

Remo is an interpreted high-level programming language designed **for fun**.

Feel free to contribute!
If you have any question about the language, feel free to ask it in **``Issues``**.

Or you can go to the "examples" folder for a few examples (there are only a few).

Currently, the disassembler and bytecode chunks have been implemented.

## How to compile

Currently, Remo is not an interpreter - it only has one handcrafted chunk that's displayed when
the program is run. There's no action whatsoever.

If you would like to compile it, run the following (assuming you're in the ``remo`` folder)

```
cd src
make
```

This should output ``compiled. Have fun!``.
Now you can run ``./remo`` and take a look at a chunk that contains the bytecode for a 
program that says ``1 + 1``.

Remo runs on a stack-based VM (at least that's the goal, it hasn't been implemented yet).


