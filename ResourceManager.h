#pragma once

#include <iostream>
#include <string>
#include <map> 
#include <memory> // ze względu na unique pointer,
#include <stdexcept> //do sygnalizowania błędów występujących w czasie pracy programu
#include <cassert> //uby w razie nieudanej próby znaleznienia zasobu o podanym ID przerwać działanie funkcji


namespace Textures
		{
		enum IDT
			{
			Background,
			BackgroundButtons,
			Cursor
			};
		}

namespace Fonts
		{
		enum IDF
			{
			MainFont
			};
		}

namespace SoundBuffers
		{
		enum IDS
			{
			MainSound
			};
		}


template <typename Resource, typename Identifier>
class ResourceManager
{
	public:
		void load(Identifier id, const std::string& filename)
		{
			// Create and load resource
			std::unique_ptr<Resource> resource(new Resource());
			if (!resource->loadFromFile(filename))
				throw std::runtime_error("Manager zasobów - nieudane ładowanie pliku" + filename);

			// If loading successful, insert resource to map
			insertResource(id, std::move(resource));
		};

		template <typename Parameter>

		Resource& get(Identifier id)
		{
			auto found = mResourceMap.find(id);
			assert(found != mResourceMap.end());

			return *found->second;
		};

		const Resource& get(Identifier id) const
			{
				auto found = mResourceMap.find(id);
				assert(found != mResourceMap.end());

				return *found->second;
			};


	private:
		void insertResource(Identifier id, std::unique_ptr<Resource> resource)
			{
				// Insert and check success
				auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
				assert(inserted.second);
			};


		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};
