#pragma once
#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <assert.h>
#include <random>
#include <string>
#include "Core.h"
#include "ObjectModel.h"

namespace EventSysytem
{

	class System
	{
	private:
		friend class Event;
		std::string name;
		int32_t descriptor;
		int16_t index;
		bool active;
		std::vector<Event*> events;

	public:
		System(std::string);
		~System();

	public:
		void addEvent(Event*);
		Event* getEvent();
		bool isActive();
		void serialize();
	};

	/*----------*/

	class Event
	{

	private:
		int32_t ID;
	public:
		enum DeviceType : int8_t
		{
			KEYBOARD = 1,
			MOUSE,
			TOUCHPAD,
			JOYSTICK
		};
		DeviceType dType;
		System* system = nullptr;

	public:
		Event(DeviceType);
		DeviceType getdType();
		int32_t getID();
		friend std::ostream& operator<<(std::ostream& stream, const DeviceType dType)
		{
			std::string result;
#define PRINT(a) result = #a;
			switch (dType) {
			case KEYBOARD: PRINT(KEYBOARD); break;
			case MOUSE: PRINT(MOUSE); break;
			case TOUCHPAD: PRINT(TOUCHPAD); break;
			case JOYSTICK: PRINT(JOYSTICK); break;

			}
			return stream << result;
		}
		void bind(System* system, Event* event);
		void serialize(ObjectModel::Object* o);

	};

	/*----------*/

	class KeyboardEvent : public Event
	{
	private:
		int16_t keyCode;
		bool pressed;
		bool released;
	public:
		KeyboardEvent(int16_t keyCode, bool pressed, bool released);
		void serialize(ObjectModel::Object* o);
	};
};

