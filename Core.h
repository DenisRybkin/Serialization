#pragma once
#include <vector>
#include <iostream>
#include <bitset>
#include <fstream>
#include "ObjectModel.h"

namespace Core
{
	namespace Util
	{
		bool isLitleEndian();

		void save(const char* file, std::vector<int8_t> buffer);

		void retrieveNsave(ObjectModel::Root* r);
	}

	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, T value);

	template<>
	void encode<float>(std::vector<int8_t>* buffer, int16_t* iterator, float value);

	template<>
	void encode<double>(std::vector<int8_t>* buffer, int16_t* iterator, double value);

	template<>
	void encode<std::string>(std::vector<int8_t>* buffer, int16_t* iterator, std::string value);

	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, std::vector<T> value);
};