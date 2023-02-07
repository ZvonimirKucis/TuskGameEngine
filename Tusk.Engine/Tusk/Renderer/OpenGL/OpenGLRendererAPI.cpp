#include "tuskpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Tusk {
	
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         Logger::Fatal("%s", message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       Logger::Error("%s", message); return;
			case GL_DEBUG_SEVERITY_LOW:          Logger::Warn("%s", message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: Logger::Trace("%s", message); return;
		}
		
		Logger::Fatal("Unknown severity level!");
	}

	void OpenGLRendererAPI::init() {
	#ifdef _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);

		glEnable(GL_MULTISAMPLE);

		/*glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);*/
	}

	void OpenGLRendererAPI::setDepthFunc(DepthFunc func) {
		switch (func) {
			case DepthFunc::LEQUAL:
				glDepthFunc(GL_LEQUAL);
				break;
			case DepthFunc::LESS:
				glDepthFunc(GL_LESS);
				break;
		}
	}

	void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::setClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {
		uint32_t count = indexCount ? indexCount : vertexArray->getIndexBuffer()->getCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}

}
