#include <algorithm>
#include <optional>
#include <vector>

#include "autograder/utils.hpp"

struct Course {
  std::string title;
  std::string number_of_units;
  std::string quarter;

  constexpr bool operator==(const Course& other) const {
    return title == other.title && number_of_units == other.number_of_units &&
           quarter == other.quarter;
  }
};

class CourseDatabase {
public:
  CourseDatabase(std::string filename) {
    const auto lines = read_lines(filename);

    std::transform(lines.begin(), lines.end(), std::back_inserter(courses), [](const auto& line) {
      const auto parts = split(line, ',');
      return Course{parts[0], parts[1], parts[2]};
    });
  }

  /**
   * Finds a course in the database with the given title, if it exists.
   * @param course_title The title of the course to find.
   * @return An optional course.
   */
  constexpr std::optional<Course> find_course(std::string course_title) const {
    for (const auto& course : courses) {
      if (course.title == course_title) {
        return course;
      }
    }

    return std::nullopt;
  }

private:
  std::vector<Course> courses;
};

int main(int argc, char* argv[]) {
  static_assert(std::is_same_v<decltype(std::declval<CourseDatabase>().find_course("")),
                               std::optional<Course>>,
                "You must change the return type of CourseDatabase::find_course to something other "
                "than FillMeIn.");

  if (argc == 2) {
    const CourseDatabase db("autograder/courses.csv");
    const auto course = db.find_course(argv[1]);

    if (course) {
      std::cout << "Found course: " << course->title << "," << course->number_of_units << ","
                << course->quarter << std::endl;
    } else {
      std::cout << "Course not found." << std::endl;
    }

    return 0;
  }

  return run_autograder();
}
