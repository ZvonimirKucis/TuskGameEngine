#include "tuskpch.h"
#include "RendererCommand.h"

namespace Tusk {

	Scope<RendererAPI> RenderCommand::_rendererAPI = RendererAPI::Create();
}