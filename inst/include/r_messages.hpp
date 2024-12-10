// Custom stream buffer that calls cpp11::stop() when it receives output

#include <cpp11.hpp>
#include <ostream>
#include <streambuf>

class StopStreambuf : public std::streambuf {
 public:
  virtual std::streamsize xsputn(const char* s, std::streamsize n) {
    cpp11::stop(std::string(s, n));
    return n;
  }
  virtual int overflow(int c) {
    char ch = c;
    cpp11::stop(std::string(&ch, 1));
    return c;
  }

  static StopStreambuf& instance() {
    static StopStreambuf instance;
    return instance;
  }
};

inline std::ostream& stopstream() {
  static std::ostream instance(&StopStreambuf::instance());
  return instance;
}
