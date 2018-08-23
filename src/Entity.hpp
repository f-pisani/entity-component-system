#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <unordered_map>

#include "Common.hpp"
#include "ComponentManager.hpp"

namespace ECS
{
	class EntityManager;
	class Entity
	{
		ECS::ID id_;
		ECS::EntityManager& entityManager_;
		ECS::ComponentManager& componentManager_;
		std::unordered_map<ECS::ID, BaseComponent*> componentCache_;

		public:
			Entity(ECS::ID id, ECS::EntityManager& entityManager, ECS::ComponentManager& componentManager);
			Entity(const Entity& entity);
			Entity& operator=(const Entity& entity);
			operator ECS::ID();
			~Entity();

			/// [E]ntity
			ECS::ID GetID();
			void Destroy();

			/// [C]omponent
			template <typename DerivedComponent, typename... Args> DerivedComponent* AddComponent(Args&&... args);
			template <typename DerivedComponent> DerivedComponent* GetComponent();
			template <typename DerivedComponent> void DestroyComponent();
			void DestroyComponents();
			std::vector<ECS::ID> GetComponentsID();
			size_t GetComponentsCount();
	};
}


/*******************************************************************************
PUBLIC METHODS TEMPLATE IMPLEMENTATION
*******************************************************************************/
template <typename DerivedComponent, typename... Args> DerivedComponent* ECS::Entity::AddComponent(Args&&... args)
{
	componentCache_[ECS::Component<DerivedComponent>::ID] = componentManager_.Create<DerivedComponent, Args...>(id_, static_cast<Args&&>(args)...);
	if(componentCache_[ECS::Component<DerivedComponent>::ID] == nullptr)
	{
		componentCache_.erase(ECS::Component<DerivedComponent>::ID);
		return nullptr;
	}
	else
		return static_cast<DerivedComponent*>(componentCache_[ECS::Component<DerivedComponent>::ID]);
}


template <typename DerivedComponent> DerivedComponent* ECS::Entity::GetComponent()
{
	if(componentCache_.count(ECS::Component<DerivedComponent>::ID))
		return static_cast<DerivedComponent*>(componentCache_[ECS::Component<DerivedComponent>::ID]);

	return nullptr;
}


template <typename DerivedComponent> void ECS::Entity::DestroyComponent()
{
	componentManager_.Delete<DerivedComponent>(id_);
	componentCache_.erase(ECS::Component<DerivedComponent>::ID);
}


#endif // ENTITY_HPP_INCLUDED
