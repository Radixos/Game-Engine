/** \file RenderAPI.h
*/

#pragma once
namespace Engine
{

	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, Direct3D = 2
		};

		static API getApi() { return s_API; }

	private:
		static API s_API;
	};
}