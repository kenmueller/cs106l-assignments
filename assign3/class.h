#ifndef CLASS_H
#define CLASS_H

#include <string>

class assignment {
public:
  assignment();
  assignment(const std::string& name, const size_t points);

  std::string get_name() const;
  void set_name(std::string name);

  size_t get_points() const;
  void set_points(size_t points);

  void print_name_and_points() const;

private:
  std::string name;
  size_t points;

  std::string get_name_and_points() const;
};

#endif
