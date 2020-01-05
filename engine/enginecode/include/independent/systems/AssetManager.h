/** /file AssetManager.h
*/
#pragma once
#include <iostream>
#include <map>

namespace Engine {
	template <class G>
	class AssetManager
	{
	public:
		bool contains(const std::string& key) /*{return &key}*/;	//!<Is this item in the container already
		void add(const std::string& key, std::shared_ptr<G>& element);	//!<Add element to the container
		std::shared_ptr<G> get(const std::string& key);	//!<Get a point to an asset
	private:
		std::map<std::string, std::shared_ptr<G>> m_container;	//Data structure to hold assets
	};
}