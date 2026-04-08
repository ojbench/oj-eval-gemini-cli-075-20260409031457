#ifndef STR_HPP
#define STR_HPP

#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
    char *data;
    size_t length;

public:
    str() : data(new char[1]), length(0) {
        data[0] = '\0';
    }

    str(const char &c) : data(new char[2]), length(1) {
        data[0] = c;
        data[1] = '\0';
    }

    str(const char *&& s_) {
        if (s_) {
            length = std::strlen(s_);
            data = new char[length + 1];
            std::strcpy(data, s_);
        } else {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
    }

    str &operator=(const char *&& s_) {
        if (data != s_) {
            delete[] data;
            if (s_) {
                length = std::strlen(s_);
                data = new char[length + 1];
                std::strcpy(data, s_);
            } else {
                length = 0;
                data = new char[1];
                data[0] = '\0';
            }
        }
        return *this;
    }

    str(const str &other) : length(other.length) {
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }

    str &operator=(const str &other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }

    char &operator[](size_t pos) {
        return data[pos];
    }

    size_t len() const {
        return length;
    }

    str join(const std::vector<str> &strs) const {
        if (strs.empty()) return str();
        size_t total_len = 0;
        for (size_t i = 0; i < strs.size(); ++i) {
            total_len += strs[i].len();
        }
        total_len += length * (strs.size() - 1);

        str result;
        delete[] result.data;
        result.length = total_len;
        result.data = new char[total_len + 1];
        result.data[0] = '\0';

        for (size_t i = 0; i < strs.size(); ++i) {
            std::strcat(result.data, strs[i].data);
            if (i != strs.size() - 1) {
                std::strcat(result.data, data);
            }
        }
        return result;
    }

    str slice(size_t l, size_t r) const {
        if (l >= r || l >= length) return str();
        if (r > length) r = length;
        size_t new_len = r - l;
        str result;
        delete[] result.data;
        result.length = new_len;
        result.data = new char[new_len + 1];
        std::strncpy(result.data, data + l, new_len);
        result.data[new_len] = '\0';
        return result;
    }

    ~str() {
        delete[] data;
    }
};

#endif
