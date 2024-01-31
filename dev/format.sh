#!/bin/bash

# wget https://apt.llvm.org/llvm.sh
# chmod +x llvm.sh

find . -name '*.cpp' -or -name '*.h' -or -name '*.hpp' | xargs clang-format-14 -i -style=file
