#include "user.h"

User::User(const std::string& name) : _name(name), _capacity(0), _size(0), _friends(nullptr) {}

User::~User() { delete[] _friends; }

User::User(const User& other) : _name(other._name), _capacity(other._capacity), _size(other._size) {
  set_friends(other._friends);
}

User& User::operator=(const User& other) {
  if (this != &other) {
    _name = other._name;
    _size = other._size;
    _capacity = other._capacity;

    delete[] _friends;
    set_friends(other._friends);
  }

  return *this;
}

void User::add_friend(const std::string& name) {
  if (_size == _capacity) {
    const std::string* const old_friends = _friends;

    _capacity = 2 * _capacity + 1;
    set_friends(old_friends);

    delete[] old_friends;
  }

  _friends[_size++] = name;
}

std::string User::get_name() const { return _name; }

size_t User::size() const { return _size; }

void User::set_friend(size_t index, const std::string& name) { _friends[index] = name; }

std::ostream& operator<<(std::ostream& os, const User& user) {
  os << "User(name=" << user._name << ", friends=[";

  for (size_t i = 0; i < user._size; ++i) {
    if (i > 0) {
      os << ", ";
    }

    os << user._friends[i];
  }

  os << "])";

  return os;
}

User& User::operator+=(User& other) {
  add_friend(other._name);
  other.add_friend(_name);

  return *this;
}

bool User::operator<(const User& other) const { return _name < other._name; }

void User::set_friends(const std::string* const other_friends) {
  if (_capacity > 0) {
    _friends = new std::string[_capacity];

    for (size_t i = 0; i < _size; i++) {
      _friends[i] = other_friends[i];
    }
  } else {
    _friends = nullptr;
  }
}
