/**
/class AssetManager class
*/
#pragma once
#include <iostream>
#include <map>
#include "systems/Log.h"

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

	template<class G>
	inline bool AssetManager<G>::contains(const std::string & key)
	{
		auto asset = m_container.find(key);
		if (asset != m_container.end())
			return true;

		return false;
	}

	template<class G>
	inline void AssetManager<G>::add(const std::string & key, std::shared_ptr<G>& element)
	{
		if (!contains(key))
		{
			m_container[key] = element;
			return;
		}

		ENG_CORE_ERROR("Asset with key {0} already included", key);

	}

	template<class G>
	inline std::shared_ptr<G> AssetManager<G>::get(const std::string & key)
	{
		if (contains(key))
		{
			return m_container[key];
		}

		ENG_CORE_ERROR("Asset with key {0} doen not exist", key);
	}
}