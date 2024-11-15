#include "class.h"
#include <format>
#include <iostream>

assignment::assignment() : name("Untitled"), points(0) {}
assignment::assignment(const std::string& name, const size_t points) : name(name), points(points) {}

std::string assignment::get_name() const { return name; }
void assignment::set_name(std::string name) { this->name = name; }

size_t assignment::get_points() const { return points; }
void assignment::set_points(size_t points) { this->points = points; }

void assignment::print_name_and_points() const { std::cout << get_name_and_points() << std::endl; }

std::string assignment::get_name_and_points() const {
  return std::format("{} ({} point{})", name, points, points == 1 ? "" : "s");
}
