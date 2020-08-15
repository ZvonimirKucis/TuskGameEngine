#include "tuskpch.h"
#include "RenderCommand.h"

namespace Tusk {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}