#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"

class Json_importer
{
public:
	Json_importer(char *file_name);
	~Json_importer();
	int get_int(char* class_name, char* attr);
	char get_char(char* class_name, char* attr);
private:
	FILE* file;
	rapidjson::Document data;
	void parse();
	auto get_obj(char* class_name)
	{
		auto it = data.FindMember(class_name);
		if (it != data.MemberEnd()) {
			rapidjson::Type type = it->value.GetType();
			if (type != rapidjson::kObjectType)
			{
				std::cout << class_name << " is an invalid key\n";
				exit(1);
			}
			return it->value.GetObject();
		}
		else
		{
			std::cout << "Key " << class_name << " was not found\n";
			exit(1);
		}
	}
};
