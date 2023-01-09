#include "ObjectModel.h"
#include "Core.h"
#include <iostream>
#include <vector>

namespace ObjectModel
{
	//definition

	Root::Root()
		:
		name("unknow"),
		wrapper(0),
		nameLength(0),
		size(sizeof nameLength + sizeof wrapper + sizeof size) {}


	void Root::setName(std::string name)
	{
		this->name = name;
		nameLength = (int16_t)(name.length());
		size += nameLength;
	}

	int32_t Root::getSize()
	{
		return size;
	}

	void Root::pack(std::vector<int8_t>*, int16_t*)
	{

	}

	std::string Root::getName()
	{
		return name;
	}


	Primitive::Primitive()
	{
		size += sizeof type;
	}

	void Primitive::pack(std::vector<int8_t>* buffer, int16_t* iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<int8_t>(buffer, iterator, wrapper);
		Core::encode<int8_t>(buffer, iterator, type);
		Core::encode<int8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);
	}

	template<typename T>
	static Primitive* Primitive::create(std::string name, Type type, T value)
	{
		Primitive* p = new Primitive();
		p->setName(name);
		p->wrapper = static_cast<int8_t>(Wrapper::PRIMITIVE);
		p->type = static_cast<int8_t>(type);
		p->data = new std::vector<int8_t>(sizeof value);
		p->size += p->data->size();
		int16_t iterator = 0;
		Core::template encode<T>(p->data, &iterator, value);

		return p;
	}

	Array::Array()
	{
		size += sizeof type + sizeof count;
	}

	void Array::pack(std::vector<int8_t>* buffer, int16_t* iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<int8_t>(buffer, iterator, wrapper);
		Core::encode<int8_t>(buffer, iterator, type);
		Core::encode<int8_t>(buffer, iterator, count);
		Core::encode<int8_t>(buffer, iterator, *data);
		Core::encode<int32_t>(buffer, iterator, size);
	}

	template<typename T>
	static Array* Array::createArray(std::string name, Type type, std::vector<T> value)
	{
		Array* arr = new Array();
		arr->setName(name);
		arr->wrapper = static_cast<int8_t>(Wrapper::ARRAY);
		arr->type = static_cast<int8_t>(type);
		arr->count = value.size();
		arr->data = new std::vector<int8_t>(value.size() * sizeof(T));
		arr->size += value.size() * sizeof(T);
		int16_t iterator = 0;
		Core::template encode<T>(arr->data, &iterator, value);

		return arr;
	};

	template<typename T>
	static Array* Array::createString(std::string name, Type type, T value)
	{
		Array* str = new Array();
		str->setName(name);
		str->wrapper = static_cast<int8_t>(Wrapper::STRING);
		str->type = static_cast<int8_t>(type);
		str->count = value.size();
		str->data = new std::vector<int8_t>(value.size());
		str->size += value.size();
		int16_t iterator = 0;
		Core::template encode<T>(str->data, &iterator, value);

		return str;
	};



	Object::Object(std::string name)
	{
		setName(name);
		wrapper = static_cast<int8_t>(Wrapper::OBJECT);
		size += sizeof count;
	}

	void Object::addEntitie(Root* r)
	{
		this->entities.push_back(r);
		count += 1;
		size += r->getSize();
	}

	Root* Object::findByName(std::string name)
	{
		for (auto r : entities)
		{
			if (r->getName() == name) return r;

		}
		std::cout << "no as such" << std::endl;
		return new Object("ninja");
	}

	void Object::pack(std::vector<int8_t>* buffer, int16_t* iterator)
	{
		Core::encode<std::string>(buffer, iterator, name);
		Core::encode<int16_t>(buffer, iterator, nameLength);
		Core::encode<int8_t>(buffer, iterator, wrapper);
		Core::encode<int16_t>(buffer, iterator, count);
		for (Root* r : entities)
		{
			r->pack(buffer, iterator);
		}

		Core::encode<int32_t>(buffer, iterator, size);
	}

}