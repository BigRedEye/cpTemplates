#include <algorithm>
#include <array>
#include <cmath>
#include <complex>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <type_traits>
#include <vector>
#include <numeric>

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using ui8 = std::uint8_t;
using ui16 = std::uint16_t;
using ui32 = std::uint32_t;
using ui64 = std::uint64_t;

namespace fio {

#if __cplusplus < 201703L
#   error "Please, use complier with C++17 support"
#else

static constexpr size_t DefaultBufferSize = 8 * (1 << 20);

template<typename T>
struct maxExp10 {
    static constexpr size_t value = std::numeric_limits<T>::max_exponent10 - std::numeric_limits<T>::min_exponent10;
};

template<typename T>
constexpr std::array<T, maxExp10<T>::value> calcExp10() {
    std::array<T, maxExp10<T>::value> result;
    for (int i = 0; i < result.size(); ++i) {
        result[i] = std::pow(10., i + std::numeric_limits<T>::min_exponent10);
    }
    return result;
}

template<typename T>
inline T exp10(int p) {
    static std::array<T, maxExp10<T>::value> cache = calcExp10<T>();
    static int offset = -std::numeric_limits<T>::min_exponent10;
    return cache[offset + p];
}

template<typename T, typename = void>
struct Reader {
    template<typename F>
    T operator()(F&& peek) const {
        throw std::runtime_error("IO cannot read that type, use iostreams / stdio");
    }
};

template<typename T>
struct Reader<T, std::enable_if_t<std::is_integral_v<T>>> {
    template<typename F>
    T operator()(F&& peek) const {
        T result { 0 };
        T mult { 1 };
        char c = std::forward<F>(peek)();
        if constexpr (std::is_signed_v<T>) {
            if (c == '-') {
                mult = -1;
                c = peek();
            }
        }
        for (; ::isdigit(c); c = peek()) {
            result = result * 10 + (c - '0');
        }
        return result * mult;
    }
};

template<typename T>
struct Reader<T, std::enable_if_t<std::is_floating_point_v<T>>> {
    template<typename F>
        T operator()(F&& peek) const {
            T result { 0. };
            T mult { 1. };
            int exponent = 0;
            char c = std::forward<F>(peek)();
            if (c == '-') {
                mult = T { -1. };
                c = peek();
            }
            T coef = 1;
            for(; ::isdigit(c); c = peek()) {
                result = (result * 10.) + (c - '0');
            }
            if (c == '.') {
                c = peek();
                for(; ::isdigit(c); c = peek()) {
                    result = (result * 10.) + (c - '0');
                    --exponent;
                }
            }
            if (c == 'e' || c  == 'E') {
                exponent -= Reader<int>{}(std::forward<F>(peek));
            }
            result *= exp10<T>(exponent);
            return result * mult;
        }
};

template<typename T>
struct Reader<std::vector<T>, void> {
    template<typename F>
    std::vector<T> operator()(F&& peek) const {
        std::vector<T> result;
        Reader<size_t> rsize;
        Reader<T> rt;
        result.resize(rsize(std::forward<F>(peek)), T{});
        for (T& t : result) {
            t = rt(std::forward<F>(peek));
        }
        return result;
    }
};

template<>
struct Reader<std::string, void> {
    template<typename F>
    std::string operator()(F&& peek) const {
        std::string s;
        for (char c = peek(); !std::isspace(c); c = peek()) {
            s.push_back(c);
        }
        return s;
    }
};

template<>
struct Reader<char> {
    template<typename F>
    char operator()(F&& peek) const {
        return std::forward<F>(peek)();
    }
};

template<size_t BufferSize = DefaultBufferSize>
class IO {
public:
    using omanip = std::ostream& (*)(std::ostream&);

public:
    explicit IO(std::istream& is = std::cin, std::ostream& out = std::cout)
        : in_(is)
        , out_(out)
        , buffer_(BufferSize, '\0')
        , it_(buffer_.begin()) {
        readBuffer();
    }

    ~IO() {
        write('\n');
    }

    template<typename T>
    T read() {
        return Reader<T>{}([this] { return peek(); });
    }

    template<typename T>
    IO& read(T& t) {
        t = read<T>();
        return *this;
    }

    template<typename T>
    IO& read(std::vector<T>& v) {
        if (v.empty()) {
            v = read<std::vector<T>>();
        } else {
            for (T& t : v) {
                t = read<T>();
            }
        }
        return *this;
    }

    template<typename T>
    IO& write(const T& t) {
        out_ << t;
        return *this;
    }

    template<typename T>
    IO& write(const std::vector<T>& v) {
        for (auto&& i : v) {
            write(i).write(' ');
        }
        write('\n');
        return *this;
    }

    IO& write(omanip manip) {
        out_ << manip;
        return *this;
    }

    IO& flush() {
        return write(std::endl);
    }

    IO& after_point(int count) {
        out_ << std::fixed << std::setprecision(10);
    }

    char peek() {
        char res = *it_++;
        if (it_ == buffer_.end()) {
            readBuffer();
        }
        return res;
    }

    template<typename T>
    IO& operator>>(T& t) {
        return read(t);
    }

    template<typename T>
    IO& operator<<(T&& t) {
        return write(std::forward<T>(t));
    }

    IO& operator<<(omanip manip) {
        return write(manip);
    }

private:
    bool readBuffer() {
        if (!in_) {
            return false;
        }
        buffer_.resize(BufferSize);
        in_.read(&buffer_[0], buffer_.size());
        size_t bytes = in_.gcount();
        buffer_.resize(bytes);
        it_ = buffer_.begin();
        return !!in_;
    }

private:
    std::istream& in_;
    std::ostream& out_;
    std::vector<char> buffer_;
    std::vector<char>::iterator it_;
};

#endif // C++17

i32 main() {
    fio::IO io;
}
