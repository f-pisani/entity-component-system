#ifndef SYSTEMMANAGER_HPP_INCLUDED
#define SYSTEMMANAGER_HPP_INCLUDED

#include <map>
#include <vector>

#include "Common.hpp"
#include "EntityManager.hpp"
#include "System.hpp"

namespace ECS
{
	class SystemManager
	{
		void synchronization();

		ECS::EntityManager& entityManager_;
		std::map<ECS::ID, ECS::BaseSystem*> system_;
		std::vector<ECS::ID> deleteSystem_;

		public:
			SystemManager(ECS::EntityManager& entityManager);
			SystemManager(const ECS::SystemManager& systemManager);
			SystemManager& operator=(const ECS::SystemManager& systemManager);
			~SystemManager();

			template <class DerivedSystem, typename... Args> DerivedSystem* Create(Args&&... args);
			template <class DerivedSystem> DerivedSystem* Get();
			template <class DerivedSystem> bool Delete();

			void Update();
	};
}


/*******************************************************************************
PUBLIC METHODS TEMPLATE IMPLEMENTATION
*******************************************************************************/
template <class DerivedSystem, typename... Args> DerivedSystem* ECS::SystemManager::Create(Args&&... args)
{
	static_assert(std::is_base_of<ECS::System<DerivedSystem>, DerivedSystem>::value,
				 "Template argument 'DerivedSystem' should inherit from ECS::System<DerivedSystem>.");

	system_[DerivedSystem::ID] = std::move(new DerivedSystem(std::forward<Args>(args)...));

	return static_cast<DerivedSystem*>(system_[DerivedSystem::ID]);
}


template <class DerivedSystem> DerivedSystem* ECS::SystemManager::Get()
{
	static_assert(std::is_base_of<ECS::System<DerivedSystem>, DerivedSystem>::value,
				 "Template argument 'DerivedSystem' should inherit from ECS::System<DerivedSystem>.");

	return static_cast<DerivedSystem*>(system_[DerivedSystem::ID]);
}


template <class DerivedSystem> bool ECS::SystemManager::Delete()
{
	static_assert(std::is_base_of<ECS::System<DerivedSystem>, DerivedSystem>::value,
				 "Template argument 'DerivedSystem' should inherit from ECS::System<DerivedSystem>.");

	if(system_.count(DerivedSystem::ID) && std::find(deleteSystem_.begin(), deleteSystem_.end(), DerivedSystem::ID) == deleteSystem_.end())
	{
		deleteSystem_.push_back(DerivedSystem::ID);
		return true;
	}

	return false;
}


#endif // SYSTEMMANAGER_HPP_INCLUDED
