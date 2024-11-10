#pragma once
#include "json.hpp"
#include <string>
#include<mutex>
#include<iostream>
#include<fstream>
using json = nlohmann::json;
using namespace std;

class openJson
{

private:

	//object from JSON type
	static json file;
	static std::mutex mutex;
	openJson();
	openJson(string) = delete;
	openJson& operator=(const openJson&) = delete;
public:
	static json GetFile();
};

