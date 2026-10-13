# C++ DAP probe

`program` is a freestanding C++ program built with AmigaPorts
`m68k-amigaos-g++` (GCC 16.2.0b, DWARF 5 in the packed trailing
`HUNK_DEBUG` container, as for `../packed`). It covers what a C++
debugger needs beyond C:

- a namespace with a class whose method is overloaded (`geo::Scaler::scale`);
- a function template instantiated twice (`geo::repeat<int, 2>` and
  `geo::repeat<short, 3>`), with a type and a value parameter;
- a function in an anonymous namespace taking an lvalue and an rvalue
  reference (`adjust`);
- a class with two ordinary bases and a virtual base (`Item`);
- pointers to a data member and to a member function (`axis`, `method`).

`entry` has C linkage and is defined first, so AmigaDOS enters it at the
start of the first hunk; it calls everything once and then loops. No SDK
or runtime library is linked (`-fno-exceptions -fno-rtti`).

Rebuild with `make AMIGA_CXX=/path/to/m68k-amigaos-g++`. The committed
binary was built with GCC 16.2.0b (20261010) and AmigaPorts binutils
2.46.0.20260504. The tests read the committed binary, so neither
command needs a cross-compiler:

```sh
cargo test --no-default-features --features dap --lib debuginfo
cargo test --release --test dap_stdio dap_debugs_cpp -- --ignored
```
