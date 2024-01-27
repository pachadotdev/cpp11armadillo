#include <cpp11.hpp>

using namespace cpp11;

[[cpp11::register]] list mylist() {
  int a = 1;
  // double b = 2.0;

  writable::doubles_matrix<> b(2, 2);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      if (i == j) {
        b(i, j) = 1.0;
      } else {
        b(i, j) = 0.0;
      }
    }
  }

  writable::list x;

  x.push_back({"a"_nm = b});
  x.push_back({"b"_nm = b});

  return x;
}
