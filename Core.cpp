#include "Core.h"
#include "ObjectModel.h"

namespace Core
{

	namespace Util
	{
		bool isLitleEndian()
		{
			int8_t foo = 5;
			std::string result = std::bitset<8>(foo).to_string();
			return result.back() == '1';
		}

		void save(const char* file, std::vector<int8_t> buffer)
		{
			std::ofstream out;
			out.open(file);


			for (unsigned i = 0; i < buffer.size(); i++)
			{
				out << buffer[i];
			}

			out.close();
		}

		void retrieveNsave(ObjectModel::Root* r)
		{
			int16_t iterator = 0;
			std::cout << r->getSize() << "_____size_____" << std::endl;
			std::vector<int8_t> buffer(r->getSize());
			std::string name = r->getName().substr(0, r->getName().length()).append(".ttc");
			r->pack(&buffer, &iterator);
			save(name.c_str(), buffer);
		}
	};


	// root encode
	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, T value)
	{
		for (unsigned i = 0, shift = 0; i < sizeof(T); i++)
		{
			(*buffer)[(*iterator)++] = (value >> ((sizeof(T) * 8) - 8) - ((i == 0) ? shift : shift += 8));
		}
	};

	//encode for floats
	template<>
	void encode<float>(std::vector<int8_t>* buffer, int16_t* iterator, float value)
	{
		int32_t result = *reinterpret_cast<int32_t*>(&value);
		encode<int32_t>(buffer, iterator, result);
	}


	//encode for doubles
	template<>
	void encode<double>(std::vector<int8_t>* buffer, int16_t* iterator, double value)
	{
		int32_t result = *reinterpret_cast<int64_t*>(&value);
		encode<int64_t>(buffer, iterator, result);
	};


	// encode for strings
	template<>
	void encode<std::string>(std::vector<int8_t>* buffer, int16_t* iterator, std::string value)
	{
		for (unsigned i = 0; i < value.size(); i++)
		{
			encode<int8_t>(buffer, iterator, value[i]);
		}
	};

	// encode for arrays
	template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator, std::vector<T> value)
	{
		for (unsigned i = 0; i < value.size(); i++)
		{
			encode<T>(buffer, iterator, value[i]);
		}
	}

};