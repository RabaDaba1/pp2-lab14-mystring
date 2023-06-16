//
// Created by krabc on 15.06.2023.
//

#ifndef ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H
#define ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <sstream>

class MyString {
public:
    MyString() =default;

    MyString(const char *text);

    MyString(const MyString &text);

    size_t size() const { return size_; }
    size_t capacity() const { return initialBufferSize_ + text_.capacity(); }

    void push_back(char c);

    void clear();

    bool empty() const { return size_ == 0; }

    bool startsWith(const char *text) const;
    bool endsWith(const char *text) const;

    bool all_of(const std::function<bool(char)>& predicate) const;

    MyString join(const std::vector<MyString> &texts) const;

    MyString& toLower();

    MyString& trim();

    std::set<MyString> getUniqueWords() const;

    std::map<MyString, size_t> countWordsUsageIgnoringCases() const;

    auto getPosition(size_t pos) const;

    static MyString generateRandomWord(size_t length);

    static constexpr std::size_t initialBufferSize_ = 20;

    struct iterator
    {
        char *c_str_begin {};
        size_t position {};
        std::string::iterator str_iterator;


        explicit iterator(MyString* myString, size_t position);

        iterator operator+(size_t pos);
        size_t operator-(iterator anotherIt);

        iterator& operator++();
        iterator& operator--();

        bool operator==(iterator anotherIt);
        bool operator!=(iterator &other);

        char& operator*() const;
    };

    struct const_iterator
    {
        char const *c {};
        char const *c_str_begin {};
        size_t position {};

        std::string::const_iterator str_iterator;

        explicit const_iterator(const MyString* myString, size_t position);

        const_iterator operator+(size_t pos) const;
        size_t operator-(const_iterator anotherIt) const;

        const_iterator& operator++();
        const_iterator& operator--();

        bool operator==(const_iterator anotherIt) const;
        bool operator!=(const_iterator anotherIt) const;

        char operator*() const;
    };

    iterator begin() { return iterator(this, 0); }
    const_iterator begin() const { return const_iterator(this, 0); }

    iterator end() { return iterator(this , size_); }
    const_iterator end() const { return const_iterator(this, size_); }

//    const_iterator cbegin() const { return {}; }
//    const_iterator cend() const { return {}; }

    char operator[](size_t i) const;

    MyString &operator+=(const char &text);

    bool operator==(const MyString& rhs) const;
    bool operator!=(const MyString& rhs) const;

    bool operator<(const MyString& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
    friend std::istringstream& operator>>(std::istringstream& is, MyString& obj);


    explicit operator std::string() const;
protected:
    std::string toString() const {
        return std::string(buffer_) + text_;
    }

    void setText(char const *newText);
    void setText(const std::string& newText);

private:
    char buffer_[initialBufferSize_] {};
    std::string text_ {};

    std::size_t size_ {};
};


#endif //ZAD14MYSTRING_DLASTUDENTOW_MYSTRING_H
