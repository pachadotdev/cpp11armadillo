#include <cpp11.hpp>
#include <cpp11armadillo.hpp>
#include <unordered_map>

using namespace arma;
using namespace cpp11;

Mat<double> ols_(const Mat<double>& Y, const Mat<double>& X);
