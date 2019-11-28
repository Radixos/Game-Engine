/** \file Character.h
*/
#pragma once

#include <glm/glm.hpp>

namespace Engine {
	class Character
	{
	private:
		glm::vec2 m_startUV;	//!<UV co-ords of the top left of character glyph
		glm::vec2 m_endUV;	//!<UV co-ords of the bottom right of character glyph
		glm::ivec2 m_size;	//!<Size of the character glyph
		glm::ivec2 m_bearing;	//!<Bearing of the character - position relative to an origin
		int m_advance;	//!<Distance to the next character
	public:
		Character() {};	//!<Default
		Character(glm::ivec2 size, glm::ivec2 bearing, int advance, glm::vec2 startUV = glm::vec2(0.f, 0.f), glm::vec2 endUV = glm::vec2(1.f, 1.f)) :
			m_startUV(startUV), m_endUV(endUV), m_size(size), m_bearing(bearing), m_advance(advance) {}
		void setUVs(glm::vec2 startUV, glm::vec2 endUV) { m_startUV = startUV; m_endUV = endUV; };	//!<Set UV co-ord
		inline glm::vec2 getstartUV() { return m_startUV; };	//!<Get top left UV coords
		inline glm::vec2 getendUV() { return m_endUV; };	//!<Get bottom right UV coords
		inline glm::ivec2 getSize() { return m_size; };	//!<Size
		inline glm::ivec2 getBearing() { return m_bearing; };	//!<Get bearing
		inline int getAdvance() { return m_advance; };	//!<Get advance
	};
}