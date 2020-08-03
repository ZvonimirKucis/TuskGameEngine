#pragma once

#include "Layer.h"

namespace Tusk {
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return _layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return _layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return _layers.begin(); }
		std::vector<Layer*>::const_iterator end()	const { return _layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return _layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return _layers.rend(); }
	private:
		std::vector<Layer*> _layers;
		unsigned int _layerInsertIndex = 0;
	};
}