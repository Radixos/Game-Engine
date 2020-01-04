/**
\class RenderCommand class
*/

#pragma once

namespace Engine
{
	class RenderCommand	//!<RenderCommand class
	{
	public:
		virtual void action() = 0;	//!<Virtual action function

		static RenderCommand* ClearDepthColourBufferCommand(float r, float g, float b, float a);	//!<A function for clearing depth colour
		static RenderCommand* setClearColourCommand(float r, float g, float b, float a);	//!<A function for setting clear colour
		static RenderCommand* setDepthTestLessCommand(bool enabled);	//!<A function for setting depth test
		static RenderCommand* setBackfaceCullingCommand(bool enabled);	//!<A function for setting back face culling
	};
}