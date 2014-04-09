
#pragma once

#include "includes.h"
#include "../library/memory.h"

enum EventTypes
{
  EVENT_WINDOW_ACTIVATE,
  EVENT_WINDOW_DEACTIVATE,
	EVENT_WINDOW_RESIZE,
	EVENT_WINDOW_MANAGER,
	EVENT_WINDOW_CLOSED,
  EVENT_KEY_DOWN,
  EVENT_KEY_UP,
  EVENT_MOUSE_DOWN,
  EVENT_MOUSE_UP,
  EVENT_MOUSE_MOVE,
  EVENT_JOYSTICK_AXIS,
	EVENT_JOYSTICK_HAT,
	EVENT_JOYSTICK_BALL,
  EVENT_JOYSTICK_BUTTON_DOWN,
  EVENT_JOYSTICK_BUTTON_UP,
  EVENT_TIMER_TICK,
  EVENT_NETWORK_CONNECTION_REQUEST,
  EVENT_NETWORK_PACKET_RECEIVED,
  EVENT_NETWORK_DISCONNECTED,
  EVENT_DOWNLOAD_PROGRESS,
  EVENT_DOWNLOAD_COMPLETE,
  EVENT_AUDIO_FINISHED,
	EVENT_USER,
  EVENT_UNDEFINED
};

typedef struct FRAMEWORK_DOWNLOAD_EVENT
{
  std::string* URL;
  Memory* Contents;
  double DownloadedBytes;
  double TotalBytesToDownload;
  double UploadedBytes;
  double TotalBytesToUpload;
} FRAMEWORK_DOWNLOAD_EVENT;

typedef struct FRAMEWORK_NETWORK_EVENT
{
  ENetEvent Traffic;
} FRAMEWORK_NETWORK_EVENT;

typedef struct FRAMEWORK_DISPLAY_EVENT
{
	bool Active;
	int X;
	int Y;
	int Width;
	int Height;
} FRAMEWORK_DISPLAY_EVENT;

typedef struct FRAMEWORK_JOYSTICK_EVENT
{
	int ID;
	int Stick;
	int Axis;
	float Position;
	int Button;
} FRAMEWORK_JOYSTICK_EVENT;

typedef struct FRAMEWORK_MOUSE_EVENT
{
	int X;
	int Y;
	int WheelVertical;
	int WheelHorizontal;
	int DeltaX;
	int DeltaY;
	int Button;
} FRAMEWORK_MOUSE_EVENT;

typedef struct FRAMEWORK_KEYBOARD_EVENT
{
	int KeyCode;
	int Modifiers;
} FRAMEWORK_MOUSE_EVENT;

typedef union EventData
{
	FRAMEWORK_DISPLAY_EVENT		Display;
	FRAMEWORK_JOYSTICK_EVENT	Joystick;
	FRAMEWORK_KEYBOARD_EVENT	Keyboard;
	FRAMEWORK_MOUSE_EVENT			Mouse;
	Memory*										User;
  FRAMEWORK_NETWORK_EVENT   Network;
  FRAMEWORK_DOWNLOAD_EVENT  Download;
} EventData;

/*
   Class: Event

   Provides data regarding events that occur within the system
*/
class Event
{
  public:
    EventTypes Type;
    EventData Data;

    Event();
		~Event();
};
