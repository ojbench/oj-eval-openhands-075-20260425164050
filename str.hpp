#pragma once
#include <algorithm>
#include <cstring>
#include <vector>

class str {
private:
    char* data_;
    size_t size_;

    void allocate_and_copy_from(const char* src, size_t n) {
        delete[] data_;
        size_ = n;
        data_ = new char[size_ + 1];
        if (n && src) std::memcpy(data_, src, n);
        data_[size_] = '\0';
    }

public:
    str() : data_(nullptr), size_(0) {
        data_ = new char[1];
        data_[0] = '\0';
    }

    str(const char& c) : data_(nullptr), size_(1) {
        data_ = new char[2];
        data_[0] = c;
        data_[1] = '\0';
    }

    // Additional convenience constructor from C-string (lvalue)
    str(const char* s_) : data_(nullptr), size_(0) {
        const char* s = s_ ? s_ : "";
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        if (size_) std::memcpy(data_, s, size_);
        data_[size_] = '\0';
    }

    // treat rvalue const char* as a C-string source
    str(const char*&& s_) : data_(nullptr), size_(0) {
        const char* s = s_ ? s_ : "";
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        if (size_) std::memcpy(data_, s, size_);
        data_[size_] = '\0';
    }

    // Assignment from C-string (lvalue)
    str& operator=(const char* s_) {
        const char* s = s_ ? s_ : "";
        size_t n = std::strlen(s);
        allocate_and_copy_from(s, n);
        return *this;
    }

    str& operator=(const char*&& s_) {
        const char* s = s_ ? s_ : "";
        size_t n = std::strlen(s);
        allocate_and_copy_from(s, n);
        return *this;
    }

    str(const str& other) : data_(nullptr), size_(other.size_) {
        data_ = new char[size_ + 1];
        if (size_) std::memcpy(data_, other.data_, size_);
        data_[size_] = '\0';
    }

    // Move operations for efficiency
    str(str&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = new char[1];
        other.data_[0] = '\0';
        other.size_ = 0;
    }

    str& operator=(str&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = new char[1];
        other.data_[0] = '\0';
        other.size_ = 0;
        return *this;
    }

    str& operator=(const str& other) {
        if (this == &other) return *this;
        allocate_and_copy_from(other.data_, other.size_);
        return *this;
    }

    char& operator[](size_t pos) { return data_[pos]; }
    const char& operator[](size_t pos) const { return data_[pos]; }

    size_t len() const { return size_; }

    str join(const std::vector<str>& strs) const {
        if (strs.empty()) return str();
        size_t k = strs.size();
        size_t sep_len = size_;
        size_t total = 0;
        for (const auto& s : strs) total += s.size_;
        if (k > 1 && sep_len) total += sep_len * (k - 1);

        str res; // will replace its buffer
        delete[] res.data_;
        res.size_ = total;
        res.data_ = new char[total + 1];

        size_t pos = 0;
        if (strs[0].size_) {
            std::memcpy(res.data_ + pos, strs[0].data_, strs[0].size_);
            pos += strs[0].size_;
        }
        for (size_t i = 1; i < k; ++i) {
            if (sep_len) {
                std::memcpy(res.data_ + pos, data_, sep_len);
                pos += sep_len;
            }
            if (strs[i].size_) {
                std::memcpy(res.data_ + pos, strs[i].data_, strs[i].size_);
                pos += strs[i].size_;
            }
        }
        res.data_[total] = '\0';
        return res;
    }

    str slice(size_t l, size_t r) const {
        if (l > size_) l = size_;
        if (r > size_) r = size_;
        if (l >= r) return str();
        size_t n = r - l;
        str res;
        delete[] res.data_;
        res.size_ = n;
        res.data_ = new char[n + 1];
        std::memcpy(res.data_, data_ + l, n);
        res.data_[n] = '\0';
        return res;
    }

    ~str() { delete[] data_; }
};
