#include "EventSysytem.h"


namespace EventSysytem
{
	System::System(std::string name)
		:
		name(name),
		descriptor(123),
		index(1),
		active(true) {}

	System::~System()
	{

	}

	void System::addEvent(Event* e)
	{
		e->bind(this, e);
	}

	Event* System::getEvent()
	{
		return this->events.front();
	}

	int32_t Event::getID()
	{
		return ID;
	}

	bool System::isActive()
	{
		if (!system) return true;
		else return false;
	}

	void System::serialize()
	{
		ObjectModel::Object system("SysInfo");
		ObjectModel::Array* name = ObjectModel::Array::createString("SysName", ObjectModel::Type::I8, this->name);
		ObjectModel::Primitive* descriptor = ObjectModel::Primitive::create("descriptor", ObjectModel::Type::I32, this->descriptor);
		ObjectModel::Primitive* index = ObjectModel::Primitive::create("index", ObjectModel::Type::I16, this->index);
		ObjectModel::Primitive* active = ObjectModel::Primitive::create("index", ObjectModel::Type::BOOL, this->active);
		system.addEntitie(name);
		system.addEntitie(descriptor);
		system.addEntitie(index);
		system.addEntitie(active);

		for (Event* e : events)
		{
			KeyboardEvent* kb = static_cast<KeyboardEvent*>(e);
			ObjectModel::Object* eventObject = new ObjectModel::Object("Event: " + std::to_string(e->getID()));
			kb->serialize(eventObject);
			system.addEntitie(eventObject);
		}

		Core::Util::retrieveNsave(&system);
	}

	/*----------*/

	Event::Event(DeviceType dType)
	{
		std::random_device rd;
		std::uniform_int_distribution<> destr(1, 100);
		this->ID = destr(rd);
		this->dType = dType;
	}

	void Event::bind(System* system, Event* event)
	{
		this->system = system;
		this->system->events.push_back(event);
	}

	void Event::serialize(ObjectModel::Object* o)
	{
		ObjectModel::Primitive* ID = ObjectModel::Primitive::create("ID", ObjectModel::Type::I32, this->getID());
		ObjectModel::Primitive* dType = ObjectModel::Primitive::create("dType", ObjectModel::Type::I8, static_cast<int8_t>(this->dType));

		o->addEntitie(ID);
		o->addEntitie(dType);
	}

	Event::DeviceType Event::getdType()
	{
		return this->dType;
	}

	/*----------*/

	KeyboardEvent::KeyboardEvent(int16_t keyCode, bool pressed, bool released)
		:
		Event(Event::KEYBOARD),
		keyCode(keyCode),
		pressed(pressed),
		released(released) {}

	void KeyboardEvent::serialize(ObjectModel::Object* o)
	{
		Event::serialize(o);
		ObjectModel::Primitive* keyCode = ObjectModel::Primitive::create("keyCode", ObjectModel::Type::I16, this->keyCode);
		ObjectModel::Primitive* pressed = ObjectModel::Primitive::create("pressed", ObjectModel::Type::BOOL, this->pressed);
		ObjectModel::Primitive* released = ObjectModel::Primitive::create("released", ObjectModel::Type::BOOL, this->released);
		o->addEntitie(keyCode);
		o->addEntitie(pressed);
		o->addEntitie(released);
	}
}