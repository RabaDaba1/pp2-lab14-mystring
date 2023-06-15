//
// Created by krabc on 15.06.2023.
//

#include "mystring.h"

#include <cstring>

using namespace std;

/** CONSTRUCTORS **/
MyString::MyString(const char *text) {
    size_t text_size = strlen(text);

    strncpy(buffer_, text, initialBufferSize_-1);

    if (text_size >= initialBufferSize_)
        text_.assign(text+initialBufferSize_-1);

    size_ = text_size;
}

MyString::MyString(const MyString &text) {
    strcpy(buffer_, text.buffer_);

    if (text.size_ >= initialBufferSize_)
        text_ = text.text_;

    size_ = text.size_;
}

void MyString::clear() {
    text_.clear();
    memset(buffer_, 0, strlen(buffer_));

    size_ = 0;
}

void MyString::push_back(char c) {

}

bool MyString::startsWith(const char *text) const {
    return false;
}

bool MyString::endsWith(const char *text) const {
    return false;
}


bool MyString::all_of(std::function<bool(char)> predicate) const {
    return false;
}

MyString MyString::join(const vector<MyString> &texts) const {
    return *this;
}

MyString &MyString::toLower() {
    return *this;
}

MyString& MyString::trim() {
    return *this;
}

std::set<MyString> MyString::getUniqueWords() const {
    return {};
}

std::map<MyString, size_t> MyString::countWordsUsageIgnoringCases() const {
    return {};
}

auto MyString::getPosition() const {
    return 0;
}

MyString MyString::generateRandomWord(size_t length) {
    return MyString("Elo");
}

/** OVERLOADED OPERATORS **/
MyString &MyString::operator+=(const char &text) {
    return *this;
}

bool MyString::operator==(const MyString &rhs) const {
    return false;
}

bool MyString::operator!=(const MyString &rhs) const {
    return false;
}

char MyString::operator[](size_t i) const {
    if (i < MyString::initialBufferSize_)
        return buffer_[i];
    else
        return text_[i-MyString::initialBufferSize_];
}

bool MyString::operator<(const MyString &rhs) const {
    return false;
}

std::ostream& operator<<(std::ostream& os, const MyString& obj) {
    os << string(obj);
    return os;
}

std::istream& operator>>(std::istream& is, const MyString& obj) {
    return is;
}

MyString::operator std::string() const {
    return string(buffer_) + text_;
}


/** ITERATOR **/
MyString::iterator::iterator(MyString *myString, size_t position) {

}

MyString::iterator MyString::iterator::operator+(size_t pos) {
    return *this;
}

size_t MyString::iterator::operator-(MyString::iterator anotherIt) {
    return 0;
}

MyString::iterator &MyString::iterator::operator++() {
    return *this;
}

MyString::iterator &MyString::iterator::operator--() {
    return *this;
}

bool MyString::iterator::operator==(MyString::iterator anotherIt) {
    return false;
}

bool MyString::iterator::operator!=(MyString::iterator &other) {
    return false;
}

char &MyString::iterator::operator*() {
    return reinterpret_cast<char &>(c);
}

MyString::const_iterator::const_iterator(const MyString *myString, size_t position) {

}

MyString::const_iterator MyString::const_iterator::operator+(size_t pos) const {
    return *this;
}

size_t MyString::const_iterator::operator-(MyString::const_iterator anotherIt) const {
    return 0;
}

MyString::const_iterator &MyString::const_iterator::operator++() {
    return *this;
}

MyString::const_iterator &MyString::const_iterator::operator--() {
    return *this;
}

bool MyString::const_iterator::operator==(MyString::const_iterator anotherIt) const {
    return false;
}

bool MyString::const_iterator::operator!=(MyString::const_iterator anotherIt) const {
    return false;
}

char MyString::const_iterator::operator*() const {
    return 0;
}

