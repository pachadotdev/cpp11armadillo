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

class MessageStreambuf : public std::streambuf {
 private:
  std::string buffer;

 protected:
  virtual int overflow(int c) override {
    if (c != EOF) {
      buffer += static_cast<char>(c);
      if (c == '\n') {
        cpp11::message(buffer);
        buffer.clear();
      }
    }
    return c;
  }

  virtual std::streamsize xsputn(const char* s, std::streamsize n) override {
    buffer.append(s, n);
    size_t pos = 0;
    while ((pos = buffer.find('\n')) != std::string::npos) {
      cpp11::message(buffer.substr(0, pos));
      buffer.erase(0, pos + 1);
    }
    return n;
  }

 public:
  static MessageStreambuf& instance() {
    static MessageStreambuf instance;
    return instance;
  }
};

inline std::ostream& messagestream() {
  static std::ostream instance(&MessageStreambuf::instance());
  return instance;
}
