#include "tuskpch.h"
#include "RenderCommand.h"

namespace Tusk {
	Scope<RendererAPI> RenderCommand::_rendererAPI = RendererAPI::create();
}