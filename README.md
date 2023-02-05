# Remo

Remo is an interpreted high-level programming language designed **for fun**.

Feel free to contribute!
If you have any question about the language, feel free to ask it in **``Issues``**.

Or you can go to the "examples" folder for a few examples (there are only a few).

Currently, the disassembler and bytecode chunks have been implemented.

## What's new

Remo can now execute bytes! The VM is fully capable of interpreting the bytecode.

## How to compile

If you would like to compile it, run the following (assuming you're in the ``remo`` folder)

```
cd src
make
```

This should output ``compiled. Have fun!``.
Now you can run ``./remo`` and have a look at a strange output. I tried handcrafting a chunk that
says "1 + 2 - 3 * 4 / 5", and the output was 2.183333. I'm not sure if it's correct since I didn't verify it.

Remo runs on a stack-based VM.


