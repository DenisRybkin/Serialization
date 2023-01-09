#pragma once
#include <iostream>
#include <vector>

#define abstract

namespace ObjectModel
{
	enum class Wrapper {
		PRIMITIVE = 1,
		ARRAY,
		STRING,
		OBJECT
	};

	enum class Type : int8_t {
		I8,
		I16,
		I32,
		I64,

		U8,
		U16,
		U32,
		U64,

		FLOAT,
		DOUBLE,

		BOOL
	};

	abstract class Root
	{
	protected:
		Root();
	protected:
		std::string name;
		int16_t nameLength;
		int8_t wrapper;
		int32_t size;
		int8_t type;

	public:
		int32_t getSize();
		void setName(std::string);
		std::string getName();
		virtual void pack(std::vector<int8_t>*, int16_t*);
	};

	class Primitive : public Root
	{
	private:
		int8_t type;
		std::vector<int8_t>* data;

	private:
		Primitive();

	public:
		template<typename T>
		static Primitive* create(std::string name, Type type, T value);

		void pack(std::vector<int8_t>*, int16_t*);
	};

	class Array : public Root
	{
	private:
		int8_t type;
		int32_t count;
		std::vector<int8_t>* data;

	private:
		Array();
	public:
		template<typename T>
		static Array* createArray(std::string name, Type type, std::vector<T> value);
		template<typename T>
		static Array* createString(std::string name, Type type, T value);

		void pack(std::vector<int8_t>*, int16_t*);
	};

	class Object : public Root
	{

	private:
		std::vector<Root*> entities;
		int16_t count = 0;
	public:
		Object(std::string);
		void addEntitie(Root* r);
		Root* findByName(std::string);
		void pack(std::vector<int8_t>*, int16_t*);
	};
}

