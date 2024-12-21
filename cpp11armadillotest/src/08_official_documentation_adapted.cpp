#include "00_main.h"

[[cpp11::register]] doubles_matrix<> matrix1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  double x = A(0, 0);  // access an element on row 1, column 1
  A = A + x;           // scalar addition

  mat B = A + A;  // matrix addition
  mat C = A * B;  // matrix multiplication
  mat D = A % B;  // element-wise matrix multiplication

  mat res = B + C + D;

  return as_doubles_matrix(res);  // convert from C++ to R
}

[[cpp11::register]] list matrix2_(const doubles_matrix<>& a) {
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

[[cpp11::register]] doubles column1_(const doubles& x, const doubles& y) {
  vec X = as_Col(x);  // convert from R to C++
  vec Y = as_Col(y);

  mat A(10, 10, fill::randu);
  vec Z = A.col(5);  // extract a column vector

  Z = Z + Y + X;

  return as_doubles(Z);  // convert from C++ to R
}

[[cpp11::register]] doubles row1_(const doubles& x, const doubles& y) {
  vec X = as_Col(x);  // convert from R to C++
  vec Y = as_Col(y);

  mat A(10, 10, fill::randu);

  rowvec Z = A.row(5);    // extract a row vector
  Z = Z + Y.t() + X.t();  // transpose Y and X to be able to sum

  vec res = Z.t();

  return as_doubles(res);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> cube1_(const doubles_matrix<>& a,
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

[[cpp11::register]] doubles_matrix<> field1_(const doubles_matrix<>& a,
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

[[cpp11::register]] integers attr1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  // uword or int can be used
  int n_rows = A.n_rows;  // number of rows
  int n_cols = A.n_cols;  // number of columns
  int n_elem = A.n_elem;  // number of elements

  writable::integers res({n_rows, n_cols, n_elem});
  res.attr("names") = strings({"n_rows", "n_cols", "n_elem"});

  return res;
}

[[cpp11::register]] doubles_matrix<> access1_(const doubles_matrix<>& a) {
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

[[cpp11::register]] doubles_matrix<> initialization1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);         // convert from R to C++
  mat B = {{1, 2}, {3, 4}};  // create new matrix
  vec C = {1, 2};            // create new column vector

  // sum C to the diagonal of A
  A(0, 0) = A(0, 0) + C(0);
  A(1, 1) = A(1, 1) + C(1);

  mat D = A + B;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> zeros1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A.zeros();          // set all elements to zero

  mat B;
  B.zeros(size(A));  // set size to be the same as A and set all elements to zero

  mat C(A.n_rows, A.n_cols, fill::zeros);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> ones1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++
  A.ones();           // set all elements to zero

  mat B;
  B.ones(size(A));  // set size to be the same as A and set all elements to zero

  mat C(A.n_rows, A.n_cols, fill::ones);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> eye1_(const doubles_matrix<>& a) {
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

[[cpp11::register]] doubles_matrix<> randu1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  mat B;
  B.randu(size(A));  // random uniform matrix with the same size as A

  mat C(A.n_rows, A.n_cols, fill::randu);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> randn1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  mat B;
  B.randn(size(A));  // random normal matrix with the same size as A

  mat C(A.n_rows, A.n_cols, fill::randn);

  mat D = A + B + C;

  return as_doubles_matrix(D);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> randu2_(const int& n) {
  GetRNGstate();  // Ensure R's RNG state is synchronized
  mat y(n, n);
  ::arma_rng::randu<double>::fill(y.memptr(), y.n_elem);
  PutRNGstate();

  return as_doubles_matrix(y);
}

[[cpp11::register]] doubles_matrix<> randn2_(const int& n) {
  GetRNGstate();  // Ensure R's RNG state is synchronized
  mat y(n, n);
  ::arma_rng::randn<double>::fill(y.memptr(), y.n_elem);
  PutRNGstate();

  return as_doubles_matrix(y);
}

[[cpp11::register]] doubles_matrix<> fill1_(const doubles_matrix<>& a) {
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

[[cpp11::register]] doubles_matrix<> imbue1_(const doubles_matrix<>& a) {
  mat A = as_Mat(a);  // convert from R to C++

  std::mt19937 engine;  // Mersenne twister random number engine
  std::uniform_real_distribution<double> distr(0.0, 1.0);

  mat B(size(A), fill::none);                // create an empty matrix
  B.imbue([&]() { return distr(engine); });  // fill with random values

  mat C = A + B;

  return as_doubles_matrix(C);  // convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> imbue2_(const doubles_matrix<>& a) {
  GetRNGstate();  // Ensure R's RNG state is synchronized

  mat A = as_Mat(a);  // Convert from R to C++

  mat B(size(A), fill::none);             // Create an empty matrix
  B.imbue([]() { return unif_rand(); });  // Fill with random values

  mat C = A + B;

  PutRNGstate();

  return as_doubles_matrix(C);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> clean1_(const int& n) {
  mat A(n, n, fill::randu); // create a random matrix

  A(0, 0) = datum::eps;  // set the diagonal with small values (+/- epsilon)
  A(1, 1) = -datum::eps;

  A.clean(datum::eps);  // set elements with small values to zero

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> replace1_(const int& n) {
  mat A(n, n, fill::randu);  // create a random matrix

  A.diag().fill(datum::nan);  // set the diagonal with NaN values
  A.replace(datum::nan, 0);   // replace each NaN with 0

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> clamp1_(const int& n) {
  mat A(n, n, fill::ones);  // create a random matrix
  A.diag().fill(0.1);       // set the diagonal with 0.1 values

  A.clamp(0.2, 0.8);  // clamp values to the [0.2, 0.8] interval

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> transform1_(const int& n) {
  mat A(n, n, fill::ones);  // create a matrix filled with ones
  A.transform([](double val) { return (val + 122.0); });
  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> for_each1_(const int& n) {
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

[[cpp11::register]] doubles set_size1_(const int& n) {
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

[[cpp11::register]] doubles_matrix<> reshape1_(const int& n) {
  mat A(n + 1, n - 1, fill::randu);
  A.reshape(n - 1, n + 1);
  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> resize1_(const int& n) {
  mat A(n + 1, n - 1, fill::randu);
  A.resize(n - 1, n + 1);
  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] integers copy_size1_(const int& n) {
  mat A(n, n, fill::randu);

  mat B;
  B.copy_size(A);

  int N = B.n_rows;
  int M = B.n_cols;
  
  writable::integers res({N, M});
  res.attr("names") = strings({"n_rows", "n_cols"});

  return as_integers(res);  // Convert from C++ to R
}

[[cpp11::register]] integers reset1_(const int& n) {
  mat A(n, n, fill::randu);
  A.reset();

  int N = A.n_rows;
  int M = A.n_cols;

  writable::integers res({N, M});
  res.attr("names") = strings({"n_rows", "n_cols"});

  return as_integers(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> subview1_(const int& n) {
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

[[cpp11::register]] doubles_matrix<> subview2_(const int& n) {
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

[[cpp11::register]] doubles diagonal1_(const int& n) {
  mat X(n, n, fill::randu);

  vec A = X.diag(); // extract the main diagonal
  double B = accu(X.diag(1)); // sum of elements on the first upper diagonal
  double C = accu(X.diag(-1)); // sum of elements on the first lower diagonal

  X.diag() = randu<vec>(n);
  X.diag() += A;
  X.diag() /= B;
  X.diag() *= C;

  sp_mat S = sprandu<sp_mat>(n, n, 0.0);
  S.diag().ones();

  vec v(S.diag());  // copy sparse diagonal to dense vector
  v += X.diag();

  return as_doubles(v);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> each_col1_(const int& n) {
  mat X(n, n + 1, fill::ones);

  // create a vector with n elements ranging from 5 to 10
  vec v = linspace<vec>(5, 10, n);

  // in-place addition of v to each column vector of X
  X.each_col() += v;

  // generate Y by adding v to each column vector of X
  mat Y = X.each_col() + v;

  // subtract v from columns 1 and 2 of X
  X.cols(0, 1).each_col() -= v;

  uvec indices(2);
  indices(0) = 1;
  indices(1) = 2;

  X.each_col(indices) = v;  // copy v to columns 1 and 2 of X

  // lambda function with non-const vector
  X.each_col([](vec& a) { 2 * a; });

  const mat& XX = X;

  // lambda function with const vector
  XX.each_col([](const vec& b) { 3 * b; });

  mat res = X + Y + XX;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> each_row1_(const int& n) {
  mat X(n + 1, n, fill::ones);

  // create a vector with n elements ranging from 5 to 10
  rowvec v = linspace<rowvec>(5, 10, n);

  // in-place addition of v to each rows vector of X
  X.each_row() += v;

  // generate Y by adding v to each rows vector of X
  mat Y = X.each_row() + v;

  // subtract v from rows 1 and 2 of X
  X.rows(0, 1).each_row() -= v;

  uvec indices(2);
  indices(0) = 1;
  indices(1) = 2;

  X.each_row(indices) = v;       // copy v to columns 1 and 2 of X

  // lambda function with non-const vector
  X.each_row([](rowvec& a) { a / 2; });

  const mat& XX = X;

  // lambda function with const vector
  XX.each_row([](const rowvec& b) { b / 3; });

  mat res = X + Y + XX;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> each_slice1_(const int& n) {
  cube C(n, n + 1, 6, fill::randu);

  mat M = repmat(linspace<vec>(1, n, n), 1, n + 1);

  C.each_slice() += M;  // in-place addition of M to each slice of C

  cube D = C.each_slice() + M;  // generate D by adding M to each slice of C

  // sum all slices of D into a single n x (n + 1) matrix
  mat D_flat = sum(D, 2);

  uvec indices(2);
  indices(0) = 2;
  indices(1) = 4;

  C.each_slice(indices) = M;  // copy M to slices 2 and 4 in C
  C.each_slice([](mat& X) { X * 2.0; });  // lambda function with non-const matrix
  mat C_flat = sum(C, 2);

  const cube& CC = C;
  CC.each_slice([](const mat& X) { X / 3.0; });  // lambda function with const matrix

  mat CC_flat = sum(CC, 2);

  mat res = C_flat + D_flat + CC_flat;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

[[cpp11::register]] list set_real1_(const int& n) {
  mat A(n + 1, n - 1, fill::randu);

  cx_mat C(n + 1, n - 1, fill::zeros);

  C.set_real(A);

  return as_complex_matrix(C);  // Convert from C++ to R
}

[[cpp11::register]] list set_real2_(const int& n) {
  mat A(n - 1, n + 1, fill::randu);
  mat B(n - 1, n + 1, fill::randu);

  cx_mat C = cx_mat(A, B);

  return as_complex_matrix(C);  // Convert from C++ to R
}

[[cpp11::register]] list set_imag1_(const int& n) {
  mat B(n + 1, n - 1, fill::randu);

  cx_mat C(n + 1, n - 1, fill::zeros);

  C.set_imag(B);

  return as_complex_matrix(C);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> insert_columns1_(const int& n) {
  mat A(n, n * 2, fill::randu);
  mat B(n, n - 1, fill::ones);

  // at column n - 1, insert a copy of B
  // A will now have 3n - 1 columns
  A.insert_cols(n - 1, B);

  // at column 1, insert 2n zeroed columns
  // B will now have 3n - 1 columns
  B.insert_cols(1, n * 2);

  mat res = A + B;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> insert_rows1_(const int& n) {
  mat A(n * 2, n, fill::randu);
  mat B(n - 1, n, fill::ones);

  // at row n - 1, insert a copy of B
  // A will now have 3n - 1 rows
  A.insert_rows(n - 1, B);

  // at row 1, insert 2n zeroed rows
  // B will now have 3n - 1 columns
  B.insert_rows(1, n * 2);

  mat res = A + B;

  return as_doubles_matrix(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> insert_slices1_(const int& n) {
  cube A(n, n, n * 2, fill::randu);
  cube B(n, n, n - 1, fill::ones);

  // At slice n - 1, insert a copy of B
  // A will now have 3n - 1 slices
  A.insert_slices(n - 1, B);

  // At slice 1, insert 2n zeroed slices
  // B will now have 3n - 1 slices
  B.insert_slices(1, n * 2);

  mat res = sum(A + B, 2);

  return as_doubles_matrix(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> shed_columns1_(const int& n) {
  mat A(n, n * 5, fill::randu);

  // remove the first column
  A.shed_col(0);

  // remove columns 1 and 2
  A.shed_cols(0, 1);

  // remove columns 2 and 4
  uvec indices(2);
  indices(0) = 1;
  indices(1) = 3;
  A.shed_cols(indices);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> shed_rows1_(const int& n) {
  mat A(n * 5, n, fill::randu);

  // remove the first row
  A.shed_row(0);

  // remove rows 1 and 2
  A.shed_rows(0, 1);

  // remove rows 2 and 4
  uvec indices(2);
  indices(0) = 1;
  indices(1) = 3;
  A.shed_rows(indices);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> shed_slices1_(const int& n) {
  cube A(n, n, n * 5, fill::randu);

  // remove the first slice
  A.shed_slice(0);

  // remove slices 1 and 2
  A.shed_slices(0, 1);

  // remove slices 2 and 4
  uvec indices(2);
  indices(0) = 1;
  indices(1) = 3;
  A.shed_slices(indices);

  mat res = sum(A, 2);

  return as_doubles_matrix(res);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> swap_columns1_(const int& n) {
  mat A(n, n * 5, fill::randu);

  // swap columns 1 and 2
  A.swap_cols(0, 1);

  // swap columns 2 and 4
  A.swap_cols(1, 3);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> swap_rows1_(const int& n) {
  mat A(n * 5, n, fill::randu);

  // swap rows 1 and 2
  A.swap_rows(0, 1);

  // swap rows 2 and 4
  A.swap_rows(1, 3);

  return as_doubles_matrix(A);  // Convert from C++ to R
}

[[cpp11::register]] doubles_matrix<> swap1_(const int& n) {
  mat A(n, n + 1, fill::zeros);
  mat B(n * 2, n - 1, fill::ones);

  A.swap(B);

  return as_doubles_matrix(A);  // Convert from C++ to R
}
