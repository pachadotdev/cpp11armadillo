#!/bin/bash

# wget https://apt.llvm.org/llvm.sh
# chmod +x llvm.sh

find . -name '*.cpp' -or -name '*.h' | xargs clang-format-14 -i -style=file
