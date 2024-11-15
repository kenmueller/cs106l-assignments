#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string COURSES_OFFERED_PATH = "student_output/courses_offered.csv";
const std::string COURSES_NOT_OFFERED_PATH = "student_output/courses_not_offered.csv";

struct Course {
  std::string title;
  std::string number_of_units;
  std::string quarter;
};

#include "utils.cpp"

/**
 * @param filename The name of the file to parse.
 * @param courses A vector of courses to populate.
 */
void parse_csv(const std::string& filename, std::vector<Course>& courses) {
  std::ifstream infile(filename);
  std::string line;

  // Skip the header
  std::getline(infile, line);

  while (std::getline(infile, line)) {
    const auto tokens = split(line, ',');

    if (!tokens.size() == 3)
      throw std::runtime_error("Invalid CSV file");

    std::cout << tokens[0] << tokens[1] << tokens[2] << std::endl;

    courses.push_back({tokens[0], tokens[1], tokens[2]});
  }
}

/**
 * @param all_courses A vector of all courses gotten by calling `parse_csv`.
 *                    This vector will be modified by removing all offered courses.
 */
void write_courses_offered(std::vector<Course>& all_courses) {
  std::ofstream outfile(COURSES_OFFERED_PATH);
  outfile << "Title" << ',' << "Number of Units" << ',' << "Quarter" << std::endl;

  std::vector<Course> courses_offered;

  for (const auto& course : all_courses) {
    if (course.quarter == "null")
      continue;

    outfile << course.title << ',' << course.number_of_units << ',' << course.quarter << std::endl;
    courses_offered.push_back(course);
  }

  outfile.close();

  for (const auto& course : courses_offered)
    delete_elem_from_vector(all_courses, course);
}

/**
 * This function writes the courses NOT offered to the file
 * "student_output/courses_not_offered.csv".
 *
 * This function is ALWAYS called after the `write_courses_offered` function.
 * `unlisted_courses` will trivially contain classes that are not offered
 * since you delete offered classes from `all_courses` in the
 * `write_courses_offered` function.
 *
 * HINT: This should be VERY similar to `write_courses_offered`
 *
 * @param unlisted_courses A vector of courses that are not offered.
 */
void write_courses_not_offered(std::vector<Course>& unlisted_courses) {
  std::ofstream outfile(COURSES_NOT_OFFERED_PATH);
  outfile << "Title" << ',' << "Number of Units" << ',' << "Quarter" << std::endl;

  for (const auto& course : unlisted_courses)
    outfile << course.title << ',' << course.number_of_units << ',' << course.quarter << std::endl;

  outfile.close();

  unlisted_courses.clear();
}

int main() {
  static_assert(is_valid_course<Course>, "Course struct is not correctly defined!");

  std::vector<Course> courses;
  parse_csv("courses.csv", courses);

  write_courses_offered(courses);
  write_courses_not_offered(courses);

  return run_autograder();
}
