#include "World.hpp"

ECS::World::World() :
	entityManager_(), systemManager_(entityManager_)
{
}


ECS::World::~World()
{
}


void ECS::World::Process()
{
	entityManager_.Update();
	systemManager_.Update();
}


/// [E]ntity
ECS::Entity* ECS::World::CreateEntity()
{
	return entityManager_.Create();
}


std::vector<ECS::Entity*> ECS::World::CreateMultipleEntity(size_t n)
{
	return entityManager_.CreateMultiple(n);
}


void ECS::World::DeleteEntity(ECS::ID id)
{
	entityManager_.Delete(id);
}


void ECS::World::DeleteAllEntity()
{
	entityManager_.DeleteAll();
}


ECS::Entity* ECS::World::GetEntity(ECS::ID id)
{
	return entityManager_.Get(id);
}


std::vector<ECS::Entity*> ECS::World::GetAllEntity()
{
	return entityManager_.GetAll();
}


size_t ECS::World::GetEntityCount()
{
	return entityManager_.Count();
}
