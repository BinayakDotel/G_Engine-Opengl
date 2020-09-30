#pragma once
#include <string>
#include <vector>

struct Animation {
	std::vector<std::string> idle;
	std::vector<std::string> action;
	std::vector<std::string> run;
};