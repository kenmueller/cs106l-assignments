#include "utils.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_set>

std::string kYourName = "Ken Mueller";

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead.
 */
std::unordered_set<std::string> get_applicants(const std::string& filename) {
  std::unordered_set<std::string> applicants;
  std::ifstream file(filename);

  if (!file.is_open())
    throw std::runtime_error("Unable to open " + filename);

  std::string line;

  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    applicants.insert(line);
  }

  return applicants;
}

std::string get_initials(const std::string& name) {
  const auto space_position = name.find(' ');

  if (space_position == std::string::npos)
    throw std::runtime_error("Invalid name " + name);

  return std::to_string(std::toupper(name[0])) +
         std::to_string(std::toupper(name[space_position + 1]));
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name       The returned queue of names should have the same initials as this name.
 * @param students   The set of student names.
 * @returns          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(const std::string& name,
                                            const std::unordered_set<std::string>& students) {
  const auto initials = get_initials(name);
  std::queue<const std::string*> matches;

  for (const auto& student : students)
    if (get_initials(student) == initials)
      matches.push(&student);

  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.empty())
    return "NO STUDENT FOUND.";

  std::srand(std::time(nullptr));

  const auto match_index = std::rand() % matches.size();

  for (int i = 0; i < match_index; i++)
    matches.pop();

  return *matches.front();
}

int main() { return run_autograder(); }
