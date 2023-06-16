//
// Created by krabc on 15.06.2023.
//

#include "mystring.h"

#include <cstring>
#include <sstream>
#include <random>

using namespace std;

/** CONSTRUCTORS **/
MyString::MyString(const char *text) {
    setText(text);
}

MyString::MyString(const MyString &text) {
    strcpy(buffer_, text.buffer_);
    text_ = text.text_;

    size_ = text.size_;
}

void MyString::clear() {
    text_.clear();
    memset(buffer_, 0, strlen(buffer_));

    size_ = 0;
}

void MyString::push_back(char c) {
    *(end()) = c;
}

bool MyString::startsWith(const char *text) const {
    return toString().find(text) == 0;
}

bool MyString::endsWith(const char *text) const {
    return toString().find(text) == size_- strlen(text);
}

bool MyString::all_of(const std::function<bool(char)>& predicate) const {
    string text = toString();
    return std::all_of(text.begin(), text.end(), predicate);
}

MyString MyString::join(const vector<MyString> &texts) const {
    string joinedText;
    string currentText = toString();

    for (const auto &text: texts)
        joinedText += (text.toString() + currentText);

    return {joinedText.substr(0, joinedText.size()-currentText.size()).c_str()};
}

MyString& MyString::toLower() {
    std::transform(begin(), end(), begin(),
                   [](unsigned char c){ return std::tolower(c); });

    return *this;
}

MyString& MyString::trim() {
    string text = toString();

    text.erase(0, text.find_first_not_of(" \n\r\t"));
    text.erase(text.find_last_not_of(" \n\r\t") + 1);

    setText(text);

    return *this;
}

std::set<MyString> MyString::getUniqueWords() const {
    set<MyString> result;
    istringstream ss(toString());

    string buff;
    while (getline(ss, buff, ' '))
        result.insert(MyString(buff.c_str()));

    return result;
}

std::map<MyString, size_t> MyString::countWordsUsageIgnoringCases() const {
    std::map<MyString, size_t> result;
    std::istringstream ss(toString());

    string buff;
    while (getline(ss, buff, ' ')) {
        MyString word(buff.c_str());
        result[word.toLower()]++;
    }

    return result;
}

auto MyString::getPosition(size_t pos) const {

}

static const char AlphaNumeric[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "abcdefghijklmnopqrstuvwxyz";
int MyLen = sizeof(AlphaNumeric) - 1;
char randomChar() { return AlphaNumeric[rand() % MyLen]; }
MyString MyString::generateRandomWord(size_t length) {
    string random_str {};
    for(int m = 0; m < length; m++)
        random_str.push_back(randomChar());

    return {random_str.c_str()};
}

/** OVERLOADED OPERATORS **/
MyString& MyString::operator+=(const char &text) {
    if (size_ >= initialBufferSize_-1)
        text_.push_back(text);
    else
        buffer_[size_] = text;

    size_++;
    return *this;
}

bool MyString::operator==(const MyString &rhs) const {
    return toString() == rhs.toString() && size_ == rhs.size_;
}

bool MyString::operator!=(const MyString &rhs) const {
    return !(*this == rhs);
}

char MyString::operator[](size_t i) const {
    if (i >= size_)
        throw std::out_of_range("");

    if (i < MyString::initialBufferSize_-1)
        return buffer_[i];
    else
        return text_[i-MyString::initialBufferSize_+1];
}

bool MyString::operator<(const MyString &rhs) const {
    return false;
}

std::ostream& operator<<(std::ostream& os, const MyString& obj) {
    os << string(obj);
    return os;
}

std::istringstream& operator>>(std::istringstream &is, MyString& obj) {
    string buff = is.str();

    obj.setText(buff);

    return is;
}

MyString::operator std::string() const {
    return toString();
}

void MyString::setText(char const *newText) {
    size_t text_size = strlen(newText);

    strncpy(buffer_, newText, initialBufferSize_-1);

    if (text_size >= initialBufferSize_)
        text_.assign(newText+initialBufferSize_-1);

    size_ = text_size;
}

void MyString::setText(const std::string& newText) {
    setText(newText.c_str());
}

/** ITERATOR **/
MyString::iterator::iterator(MyString *myString, size_t pos) {
    c_str_begin = myString->buffer_;
    str_iterator = myString->text_.begin();

    position = pos;
}

MyString::iterator MyString::iterator::operator+(size_t pos) {
    MyString::iterator newIterator = *this;
    newIterator.position += pos;

    return newIterator;
}

size_t MyString::iterator::operator-(MyString::iterator anotherIt) {
    return position - anotherIt.position;
}

MyString::iterator &MyString::iterator::operator++() {
    position++;
    return *this;
}

MyString::iterator &MyString::iterator::operator--() {
    position--;
    return *this;
}

bool MyString::iterator::operator==(MyString::iterator anotherIt) {
    return position== anotherIt.position && string(c_str_begin) == string(anotherIt.c_str_begin) && str_iterator == anotherIt.str_iterator;
}

bool MyString::iterator::operator!=(MyString::iterator &other) {
    return !(*this == other);
}

char &MyString::iterator::operator*() const {
    return position < initialBufferSize_-1 ? *(c_str_begin + position) : *(str_iterator + position - initialBufferSize_ + 1);
}

MyString::const_iterator::const_iterator(const MyString *myString, size_t pos) {
    c_str_begin = myString->buffer_;
    str_iterator = myString->text_.begin();

    position = pos;
}

MyString::const_iterator MyString::const_iterator::operator+(size_t pos) const {
    MyString::const_iterator newIterator = *this;
    newIterator.position += pos;

    return newIterator;
}

size_t MyString::const_iterator::operator-(MyString::const_iterator anotherIt) const {
    return position - anotherIt.position;
}

MyString::const_iterator &MyString::const_iterator::operator++() {
    ++position;
    return *this;
}

MyString::const_iterator &MyString::const_iterator::operator--() {
    --position;
    return *this;
}

bool MyString::const_iterator::operator==(MyString::const_iterator anotherIt) const {
    return position== anotherIt.position && c_str_begin == anotherIt.c_str_begin && str_iterator == anotherIt.str_iterator;
}

bool MyString::const_iterator::operator!=(MyString::const_iterator anotherIt) const {
    return !(*this == anotherIt);
}

char MyString::const_iterator::operator*() const {
    return position < initialBufferSize_ ? *(c_str_begin+position) : *(str_iterator + position - initialBufferSize_);
}