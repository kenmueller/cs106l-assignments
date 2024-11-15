#pragma once

#include <queue>
#include <string>
#include <unordered_set>

extern std::string kYourName;

std::unordered_set<std::string> get_applicants(const std::string& filename);
std::queue<const std::string*> find_matches(const std::string& name,
                                            const std::unordered_set<std::string>& students);
std::string get_match(std::queue<const std::string*>& matches);

int run_autograder();
