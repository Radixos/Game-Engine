/** \class RenderAPI class
*/

#pragma once
namespace Engine
{

	class RenderAPI	//!<RenderAPI class
	{
	public:
		enum class API	//!<Enum class for API types
		{
			None = 0, OpenGL = 1, Direct3D = 2
		};

		static API getApi() { return s_API; }	//!<getAPI function for returning API

	private:
		static API s_API;
	};
}