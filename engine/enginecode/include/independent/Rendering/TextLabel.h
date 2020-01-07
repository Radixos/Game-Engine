/**
/class TextLabel class
*/
#pragma once

#include <sstream>
#include <glm/glm.hpp>
#include <include\platform\OpenGL\OpenGLMaterial.h>

namespace Engine {
	class TextLabel	//!<TextLabel class
	{
	public:
		virtual bool setFont(const std::string& fontName) = 0;	//!<Virtual function for setting the font
		virtual bool setCharSize(unsigned int charSize) = 0;	//!<Virtual function for setting char size
		virtual void setText(const std::string& text) = 0;	//!<Virtual function for setting the text
		virtual void setPosition(const glm::vec2& position) = 0;	//!<Virtual function for setting for setting the position
		virtual void setDirestion(float angle) = 0;	//!<Set angle in degrees
		virtual void setScale(float scale) = 0;	//!<Virtual function for setting the scale
		virtual void setColour(const glm::vec3& colour) = 0;	//!<Virtual function for setting the colour
		virtual const std::string& getFont() const = 0;	//!<Virtual function for getting the font
		virtual unsigned int getCharSize() const = 0;	//!<Virtual function for getting the char size
		virtual const std::string& getText() const = 0;	//!<Virtual function for getting the text
		virtual glm::vec2 getPosition() const = 0;	//!<Virtual function for getting the position
		virtual float getOrientation() const = 0;	//!<Virtual function for getting the orientation
		virtual float getScale() const = 0;	//!<Virtual function for getting the scale
		virtual glm::vec3 getColour() const = 0;	//!<Virtual function for getting the colour
		virtual glm::mat4 getModel() const = 0;	//!<Virtual function for getting getting the model
		virtual std::shared_ptr<Material> getMaterial() const = 0;	//!<Virtual function for getting the material

		static TextLabel* create(const std::string& fontName, unsigned int charSize,
			const std::string& text, const glm::vec2& position, float orientation, float scale, const glm::vec3& colour);	//!<Static function for creating a text label
	};
}