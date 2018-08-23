#include "Entity.hpp"
#include "EntityManager.hpp"
/*******************************************************************************
PUBLIC METHODS IMPLEMENTATION
*******************************************************************************/
ECS::Entity::Entity( ECS::ID id, ECS::EntityManager& entityManager, ECS::ComponentManager& componentManager) :
	id_(id), entityManager_(entityManager), componentManager_(componentManager), componentCache_()
{

}


ECS::Entity::operator ECS::ID()
{
	return id_;
}


ECS::Entity::~Entity()
{

}


ECS::ID ECS::Entity::GetID()
{
	return id_;
}


void ECS::Entity::Destroy()
{
	entityManager_.Delete(id_);
}


void ECS::Entity::DestroyComponents()
{
	return componentManager_.DeleteAll(id_);
}


std::vector<ECS::ID> ECS::Entity::GetComponentsID()
{
	std::vector<ECS::ID> ids;
	for(auto& itComponentCache : componentCache_)
		ids.push_back(itComponentCache.first);

	return ids;
}


size_t ECS::Entity::GetComponentsCount()
{
	return componentCache_.size();
}
