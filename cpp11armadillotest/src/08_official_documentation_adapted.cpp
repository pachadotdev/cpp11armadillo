#include "00_main.h"

[[cpp11::register]] doubles_matrix<> matrix_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  double x = A(0, 0);  // access an element on row 1, column 1
  A = A + x;           // scalar addition

  mat B = A + A;  // matrix addition
  mat C = A * B;  // matrix multiplication
  mat D = A % B;  // element-wise matrix multiplication

  mat res = B + C + D;

  return as_doubles_matrix(res);  // convert from C++ to R
}

[[cpp11::register]] list matrix_fun2_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);
  mat B = A + A;

  cx_mat X(A, B);  // construct a complex matrix out of two real matrices

  B.zeros();                       // set all elements to zero
  B.set_size(A.n_rows, A.n_cols);  // resize the matrix
  B.ones(5, 6);                    // same as mat B(5, 6, fill::ones)

  mat::fixed<5, 6> F;  // fixed size matrix

  double aux_mem[24];               // auxiliary memory
  mat H(&aux_mem[0], 4, 6, false);  // use auxiliary memory

  X = X + F.submat(0, 0, 1, 1) + H(1, 2);

  Mat<double> res_real = real(X);
  Mat<double> res_imag = imag(X);

  writable::list res;
  res.push_back({"real"_nm = as_doubles_matrix(res_real)});
  res.push_back({"imag"_nm = as_doubles_matrix(res_imag)});

  return res;
}

[[cpp11::register]] doubles column_fun1_(const doubles& x, const doubles& y) {
  vec X = as_Col(x);  // convert from R to C++
  vec Y = as_Col(y);

  mat A(10, 10, fill::randu);
  vec Z = A.col(5);  // extract a column vector

  Z = Z + Y + X;

  return as_doubles(Z);  // convert from C++ to R
}

[[cpp11::register]] doubles row_fun1_(const doubles& x, const doubles& y) {
  vec X = as_Col(x);  // convert from R to C++
  vec Y = as_Col(y);

  mat A(10, 10, fill::randu);

  rowvec Z = A.row(5);    // extract a row vector
  Z = Z + Y.t() + X.t();  // transpose Y and X to be able to sum

  vec res = Z.t();

  return as_doubles(res);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> cube_fun1_(const doubles_matrix<>& a,
                                                const doubles_matrix<>& b) {
  mat A = as_Mat(a);  // convert from R to C++
  mat B = as_Mat(b);

  cube X(A.n_rows, A.n_cols, 2);  // create a cube with 2 slices
  X.slice(0) = A;                 // copy A into first slice
  X.slice(1) = B;                 // copy B into second slice

  cube Y = X + X;  // cube addition
  cube Z = X % X;  // element-wise cube multiplication

  mat res = Y.slice(0) + Z.slice(1);

  return as_doubles_matrix(res);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> field_fun1_(const doubles_matrix<>& a,
                                                 const doubles_matrix<>& b) {
  mat A = as_Mat(a);  // convert from R to C++
  mat B = as_Mat(b);

  field<mat> F(A.n_rows, A.n_cols, 3);  // create a field with 2 matrices
  F(0) = A;                             // copy A into first location
  F(1) = B;                             // copy B into second location
  F(2) = F(0) + F(1);                   // matrix addition

  mat res = F(0) + F(1) + F(2).t();

  return as_doubles_matrix(res);  // convert from C++ to R
}

[[cpp11::register]] integers attr_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  // uword or int can be used
  int n_rows = A.n_rows;  // number of rows
  int n_cols = A.n_cols;  // number of columns
  int n_elem = A.n_elem;  // number of elements

  writable::integers res({n_rows, n_cols, n_elem});
  res.attr("names") = strings({"n_rows", "n_cols", "n_elem"});

  return res;
}

[[cpp11::register]] doubles_matrix<> access_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A(1, 1) = 123.0;    // set element at row 2, column 2

  vec B(2, fill::randu);

  double x = A(0, 1);  // copy element at row 1, column 2 to a double
  double y = B(1);     // copy element at coordinate 2 to a double

  uword i, j;  // int also works
  uword N = A.n_rows;
  uword M = A.n_cols;

  for (i = 0; i < N; ++i) {
    for (j = 0; j < M; ++j) {
      A(i, j) = A(i, j) + x + y;
    }
  }

  return as_doubles_matrix(A);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> initialization_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);         // convert from R to C++
  mat B = {{1, 2}, {3, 4}};  // create new matrix
  vec C = {1, 2};            // create new column vector

  // sum C to the diagonal of A
  A(0, 0) = A(0, 0) + C(0);
  A(1, 1) = A(1, 1) + C(1);

  mat D = A + B;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> zeros_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A.zeros();          // set all elements to zero

  mat B;
  B.zeros(size(A));  // set size to be the same as A and set all elements to zero

  mat C(A.n_rows, A.n_cols, fill::zeros);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> ones_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A.ones();           // set all elements to zero

  mat B;
  B.ones(size(A));  // set size to be the same as A and set all elements to zero

  mat C(A.n_rows, A.n_cols, fill::ones);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> eye_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A.eye();            // create an identity matrix

  mat B;
  B.eye(size(A));  // another identity matrix

  uword N = A.n_rows;
  uword M = A.n_cols;
  mat C(N, M, fill::randu);
  C.eye(N, M);  // yet another identity matrix

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> randu_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  mat B;
  B.randu(size(A));  // random uniform matrix with the same size as A

  mat C(A.n_rows, A.n_cols, fill::randu);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> randn_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  mat B;
  B.randn(size(A));  // random normal matrix with the same size as A

  mat C(A.n_rows, A.n_cols, fill::randn);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> randu_fun2_(const int& n) {
  GetRNGstate();  // Ensure R's RNG state is synchronized
  mat y(n, n);
  ::arma_rng::randu<double>::fill(y.memptr(), y.n_elem);
  PutRNGstate();

  return as_doubles_matrix(y);
}

[[cpp11::register]] doubles_matrix<> randn_fun2_(const int& n) {
  GetRNGstate();  // Ensure R's RNG state is synchronized
  mat y(n, n);
  ::arma_rng::randn<double>::fill(y.memptr(), y.n_elem);
  PutRNGstate();

  return as_doubles_matrix(y);
}

[[cpp11::register]] doubles_matrix<> fill_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  uword N = A.n_rows;
  uword M = A.n_cols;

  mat B(size(A), fill::value(200.0));  // create a matrix filled with 200.0
  mat C(N, M, fill::value(100.0));     // matrix filled with 100.0
  mat D(N, M, fill::zeros);            // matrix filled with zeros
  mat E(N, M, fill::ones);             // matrix filled with ones

  mat F = A + B + C + D + E;

  return as_doubles_matrix(F);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> imbue_fun1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  std::mt19937 engine;  // Mersenne twister random number engine
  std::uniform_real_distribution<double> distr(0.0, 1.0);

  mat B(size(A), fill::none);                // create an empty matrix
  B.imbue([&]() { return distr(engine); });  // fill with random values

  mat C = A + B;

  return as_doubles_matrix(C);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> imbue_fun2_(const doubles_matrix<>& a) {
  GetRNGstate();  // Ensure R's RNG state is synchronized

  mat A = as_Mat(a);  // Convert from R to C++

  mat B(size(A), fill::none);             // Create an empty matrix
  B.imbue([]() { return unif_rand(); });  // Fill with random values

  mat C = A + B;

  PutRNGstate();

  return as_doubles_matrix(C);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> clean_fun1_(const int& n) {
  mat A(n, n, fill::randu); // create a random matrix

  A(0, 0) = datum::eps;  // set the diagonal with small values (+/- epsilon)
  A(1, 1) = -datum::eps;

  A.clean(datum::eps);  // set elements with small values to zero

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> replace_fun1_(const int& n) {
  mat A(n, n, fill::randu);  // create a random matrix

  A.diag().fill(datum::nan);  // set the diagonal with NaN values
  A.replace(datum::nan, 0);   // replace each NaN with 0

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> clamp_fun1_(const int& n) {
  mat A(n, n, fill::ones);  // create a random matrix
  A.diag().fill(0.1);       // set the diagonal with 0.1 values

  A.clamp(0.2, 0.8);  // clamp values to the [0.2, 0.8] interval

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> transform_fun1_(const int& n) {
  mat A(n, n, fill::ones);  // create a matrix filled with ones
  A.transform([](double val) { return (val + 122.0); });
  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> for_each_fun1_(const int& n) {
  // add 122 to each element in a dense matrix, the '&' is important
  mat D(n, n, fill::ones);
  D.for_each([](mat::elem_type& val) { val += 122.0; });

  // add 122 to each non-zero element in a sparse matrix
  sp_mat S;
  S.sprandu(n, n, 1.0);
  S.for_each([](sp_mat::elem_type& val) { val += 123.0; });

  // set the size of all matrices in a field
  field<mat> F(2, 2);
  F.for_each([n](mat& X) { X.zeros(n, n); });  // capture n for the lambda

  mat res = D + S + F(0) + F(1);

  return as_doubles_matrix(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles set_size_fun1_(const int& n) {
  mat A;
  A.set_size(n, n);  // or:  mat A(n, n, fill::none);

  mat B;
  B.set_size(size(A));  // or:  mat B(size(A), fill::none);

  vec C;
  C.set_size(n);  // or:  vec v(n, fill::none);

  A.fill(1.0);  // set all elements to 1.0
  B.fill(2.0);  // set all elements to 2.0
  C.fill(3.0);  // set all elements to 3.0

  vec res = A.col(0) + B.col(1) + C;

  return as_doubles(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> reshape_fun1_(const int& n) {
  mat A(n + 1, n - 1, fill::randu);
  A.reshape(n - 1, n + 1);
  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> resize_fun1_(const int& n) {
  mat A(n + 1, n - 1, fill::randu);
  A.resize(n - 1, n + 1);
  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] integers copy_size_fun1_(const int& n) {
  mat A(n, n, fill::randu);

  mat B;
  B.copy_size(A);

  int N = B.n_rows;
  int M = B.n_cols;
  
  writable::integers res({N, M});
  res.attr("names") = strings({"n_rows", "n_cols"});

  return as_integers(res);  // Convert from C++ to R
}

[[cpp11::register]] integers reset_fun1_(const int& n) {
  mat A(n, n, fill::randu);
  A.reset();

  int N = A.n_rows;
  int M = A.n_cols;

  writable::integers res({N, M});
  res.attr("names") = strings({"n_rows", "n_cols"});

  return as_integers(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> subview_fun1_(const int& n) {
  mat A(n, n, fill::zeros);

  A.submat(0, 1, 2, 3) = randu<mat>(3, 3);
  A(span(0, 2), span(1, 3)) = randu<mat>(3, 3);
  A(0, 1, size(3, 3)) = randu<mat>(3, 3);

  mat B = A.submat(0, 1, 2, 3);
  mat C = A(span(0, 2), span(1, 3));
  mat D = A(0, 1, size(3, 3));

  A.col(1) = randu<mat>(5, 1);
  A(span::all, 1) = randu<mat>(5, 1);

  mat X(5, 5, fill::randu);

  // get all elements of X that are greater than 0.5
  vec q = X.elem(find(X > 0.5));

  // add 123 to all elements of X greater than 0.5
  X.elem(find(X > 0.5)) += 123.0;

  // set four specific elements of X to 1
  uvec indices = {2, 3, 6, 8};

  X.elem(indices) = ones<vec>(4);

  // add 123 to the last 5 elements of vector a
  vec a(10, fill::randu);
  a.tail(5) += 123.0;

  // add 123 to the first 3 elements of column 2 of X
  X.col(2).head(3) += 123;

  return as_doubles_matrix(X);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> subview_fun2_(const int& n) {
  cube A(n, 3, 4, fill::randu);

  mat B = A.slice(1);  // each slice is a matrix

  A.slice(0)(1, 2) = 99.0;

  A.subcube(0, 0, 1, 1, 1, 2) = randu<cube>(2, 2, 2);
  A(span(0, 1), span(0, 1), span(1, 2)) = randu<cube>(2, 2, 2);
  A(0, 0, 1, size(2, 2, 2)) = randu<cube>(2, 2, 2);

  // add 123 to all elements of A greater than 0.5
  A.elem(find(A > 0.5)) += 123.0;

  cube C = A.head_slices(2);  // get first two slices

  A.head_slices(2) += 123.0;

  mat res = A.slice(0) + B + C.slice(1);

  return as_doubles_matrix(res);  // Convert from C++ to R
}
