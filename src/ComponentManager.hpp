#ifndef COMPONENTMANAGER_HPP_INCLUDED
#define COMPONENTMANAGER_HPP_INCLUDED

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <typeinfo>

#include "Common.hpp"
#include "Component.hpp"
#include "Requirement.hpp"

namespace ECS
{
	class EntityManager;
	class Entity;
	class ComponentManager
	{
		void synchronization();

		ECS::EntityManager& entityManager_;
		std::unordered_map<ECS::ID, std::unordered_map<ECS::ID, BaseComponent*>> component_;
		std::vector<std::pair<ECS::ID, ECS::ID>> deleteComponent_;

		public:
			ComponentManager(ECS::EntityManager& entityManager);
			ComponentManager(const ComponentManager& componentManager);
			ComponentManager& operator=(const ComponentManager componentManager);
			~ComponentManager();

			template <typename DerivedComponent, typename... Args> DerivedComponent* Create(ECS::ID entityID, Args&&... args);
			template <typename DerivedComponent> DerivedComponent* Get(ECS::ID entityID);
			template <typename DerivedComponent> void Delete(ECS::ID entityID);
			void DeleteAll(ECS::ID entityID);
			std::vector<ECS::Entity*> Query(ECS::Requirement requirement);

			void Update();
	};
}


/*******************************************************************************
PUBLIC METHODS TEMPLATE IMPLEMENTATION
*******************************************************************************/
template <typename DerivedComponent, typename... Args> DerivedComponent* ECS::ComponentManager::Create(ECS::ID entityID, Args&&... args)
{
	static_assert(std::is_base_of<ECS::Component<DerivedComponent>, DerivedComponent>::value,
				  "Template argument 'DerivedComponent' should inherit from ECS::Component<DerivedComponent>.");

	component_[entityID][DerivedComponent::ID] = std::move(new DerivedComponent(std::forward<Args>(args)...));
	return static_cast<DerivedComponent*>(component_[entityID][DerivedComponent::ID]);
}


template <typename DerivedComponent> DerivedComponent* ECS::ComponentManager::Get(ECS::ID entityID)
{
	static_assert(std::is_base_of<ECS::Component<DerivedComponent>, DerivedComponent>::value,
				  "Template argument 'DerivedComponent' should inherit from ECS::Component<DerivedComponent>.");

	if(component_[entityID].count(DerivedComponent::ID))
		return static_cast<DerivedComponent*>(component_[entityID][DerivedComponent::ID]);

	return nullptr;
}


template <typename DerivedComponent> void ECS::ComponentManager::Delete(ECS::ID entityID)
{
	static_assert(std::is_base_of<ECS::Component<DerivedComponent>, DerivedComponent>::value,
				  "Template argument 'DerivedComponent' should inherit from ECS::Component<DerivedComponent>.");

	if(component_[entityID].count(DerivedComponent::ID))
		deleteComponent_.push_back(std::make_pair(entityID, DerivedComponent::ID));
}


#endif // COMPONENTMANAGER_HPP_INCLUDED
