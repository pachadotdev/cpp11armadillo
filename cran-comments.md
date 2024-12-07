## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.
* The goal is to address the gcc15 issues by upgrading the Armadillo version
  from 14.0.02 to 14.2.2 in this release.
* I also added a configure file that checks that a minimal 2x2 matrix can be
  built. This is not required for the package, as it is header only, but it
  will provide informative error messages if the Armadillo library is not
  compatible with the C++ compiler.
  