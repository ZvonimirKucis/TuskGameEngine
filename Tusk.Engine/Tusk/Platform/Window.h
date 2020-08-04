#pragma once

#include "tuskpch.h"

#include "../Events/Event.h"

namespace Tusk {
	struct WindowCreateInfo
	{
		std::string title;
		I32 width;
		I32 height;

		WindowCreateInfo(const std::string title = "Tusk Engine",
			I32 width = 1280,
			I32 height = 720)
			: title(title), width(width), height(height)
		{

		}
	};

	class TUSK_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void onUpdate() = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		virtual void setEventCallback(const EventCallbackFn & callback) = 0;

		virtual void* getNativeWindow() const = 0;

		static Window* create(const WindowCreateInfo& props = WindowCreateInfo());
	};
}