#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <assert.h>
#include <random>
#include <string>
#include "Core.h"
#include "ObjectModel.h"
#include "EventSysytem.h"

using namespace EventSysytem;
using namespace ObjectModel;

int main(int argc, char** argv)
{
	assert(Core::Util::isLitleEndian());



	int32_t foo = 5;
	Primitive* p = Primitive::create("int32", Type::I32, foo);
	Core::Util::retrieveNsave(p);
	int32_t foo0 = 5;


#if 0
	std::vector<int64_t> data{ 1,2,3,4 };
	Array* arr = Array::createArray("array", Type::I64, data);
	Core::Util::retrieveNsave(arr);

	std::string name = "name";
	Array* str = Array::createString("name", Type::I8, name);
	Core::Util::retrieveNsave(str);
#endif

#if 0
	Object object("Object");
	object.addEntitie(p);
	object.addEntitie(arr);
	object.addEntitie(str);

	Object object2("Object2");
	object.addEntitie(p);
	Core::Util::retrieveNsave(&object2);

	object.addEntitie(&object2);

	Core::Util::retrieveNsave(&object);

#endif

#if 0
	System Foo("Foo");
	Event* e = new KeyboardEvent('a', true, false);


	Foo.addEvent(e);
	KeyboardEvent* kb = static_cast<KeyboardEvent*>(Foo.getEvent());
#endif 
	(void)argc;
	(void)argv;
	return 0;
}