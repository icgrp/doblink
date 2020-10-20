# Instructions for Setting up LLVM/clang for Cross Compiling to RISCV

## Build LLVM 11

### We are going to be modifying the RISCV LLVM backend, so eventually (soon) we will be compiling our custom version (checked into this repo).

- To start/test get grab LLVM from https://github.com/llvm/llvm-project
  - `git clone https://github.com/llvm/llvm-project.git `
- Checkout release branch 11.0.0

  - ` git checkout llvmorg-11.0.0`

- Build LLVM, clang, and lld for RISCV targets.

  - See https://llvm.org/docs/GettingStarted.html for details and different options that you can use. I used:

  ```
  $ cd llvm-project
  $ mkdir build
  $ cd build
  $ cmake -DLLVM_ENABLE_PROJECTS='clang;lld' -DCMAKE_INSTALL_PREFIX=/Users/tzvi/Dropbox/Dropbox_Documents/Upenn/ESE450/LLVM/install -DLLVM_TARGETS_TO_BUILD="RISCV" -DLLVM_OPTIMIZED_TABLEGEN=On -G "Unix Makefiles" ../llvm
  $ make -j8
  ```

  (Be sure to change your paths as needed, and set -j8 to reflect approx your number of CPU cores)

## Get the gcc RISCV toolchain

### We won't be using gcc to compile our code, but this is the easiest way to provide clang with the necessary RISCV C headers, runtime & standard libraries to link with.

- Follow instructions at https://github.com/riscv/homebrew-riscv (MacOS) or https://github.com/riscv/riscv-gnu-toolchain (Linux). Be sure to use the multilib flag to get support for 32-bit targets.

## Use Clang to compile a source file

### We need to use the following options:

- `--sysroot=/usr/local/opt/riscv-gnu-toolchain` Tell clang where to find the RISCV gcc installation. Replace this path with yours.
- `-fuse-ld=lld` Tell clang to use the LLVM linker (lld) rather than the system default.
- `-mno-relax` Got complaints saying to add this
- `--target=riscv32-unknown-unknown-elf` and `-march=rv32i` Specify the target. These options play together in ways I don't fully understand yet, and can be edited to get different subtargets I believe.

```
$ /Users/tzvi/Dropbox/Dropbox_Documents/Upenn/ESE450/LLVM/install/bin/clang-11 --sysroot=/usr/local/opt/riscv-gnu-toolchain -fuse-ld=lld -mno-relax --target=riscv32-unknown-unknown-elf -march=rv32i test.c
```

Note that you can set your PATH to have `/Users/tzvi/Dropbox/Dropbox_Documents/Upenn/ESE450/LLVM/install/bin/` in it, but be careful if you already have a system clang installed; that's why I kept it explicit here.

## Verify it Works

Appending the `-v` flag and experimenting with different permuations of the above options, as well as trying to compile just .s files, and also inspecting the generated assembly (`-S` option), can let you verify the right programs are getting called and the right locations included.

You should then be able to follow examples here (https://riscv.org/wp-content/uploads/2015/02/riscv-software-stack-tutorial-hpca2015.pdf) or anywhere else however you want to verify this works.
