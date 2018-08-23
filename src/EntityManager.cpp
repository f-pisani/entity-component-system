#include "EntityManager.hpp"
/*******************************************************************************
PUBLIC METHODS IMPLEMENTATION
*******************************************************************************/
ECS::EntityManager::EntityManager() :
	freeID_(), entity_(), deleteEntity_(), componentManager_(ECS::ComponentManager(*this))
{
	freeID_.reserve(32768);
	for(size_t i=32768; i>0; --i)
		freeID_.push_back(std::move(i));
}


ECS::EntityManager::~EntityManager()
{
	freeID_.clear();
	for(auto& itEntity : entity_)
		delete itEntity.second;

	entity_.clear();
	deleteEntity_.clear();
}


ECS::Entity* ECS::EntityManager::Create()
{
	if(freeID_.empty())
	{
		size_t actualCapacity = freeID_.capacity();
		size_t newCapacity = actualCapacity*2;
		freeID_.reserve(newCapacity);

		for(size_t i=newCapacity; i>actualCapacity; --i)
			freeID_.push_back(i);
	}

	ECS::ID id(freeID_.back());
	freeID_.erase(freeID_.end()-1);

	entity_[id] = std::move(new ECS::Entity(id, *this, componentManager_));

	return entity_[id];
}

std::vector<ECS::Entity*> ECS::EntityManager::CreateMultiple(size_t n)
{
	std::vector<ECS::Entity*> entity(n);
	for(size_t i=0; i<n; ++i)
		entity.push_back(Create());

	return entity;
}


void ECS::EntityManager::Delete(ECS::ID entityID)
{
	if(entity_.count(entityID))
		deleteEntity_.push_back(entityID);
}


void ECS::EntityManager::DeleteAll()
{
	for(auto& itEntity : entity_)
		deleteEntity_.push_back(itEntity.first);
}


ECS::Entity* ECS::EntityManager::Get(ECS::ID entityID)
{
	if(entity_.count(entityID))
		return entity_[entityID];

	return nullptr;
}


std::vector<ECS::Entity*> ECS::EntityManager::GetAll()
{
	std::vector<ECS::Entity*> entity;
	for(auto& itEntity : entity_)
		entity.push_back(itEntity.second);

	return entity;
}


size_t ECS::EntityManager::Count()
{
	return entity_.size();
}


ECS::ComponentManager& ECS::EntityManager::GetComponentManager()
{
	return componentManager_;
}


void ECS::EntityManager::Update()
{
	synchronization();

	componentManager_.Update();
}


/*******************************************************************************
PRIVATE METHODS IMPLEMENTATION
*******************************************************************************/
void ECS::EntityManager::synchronization()
{
	std::sort(deleteEntity_.begin(), deleteEntity_.end());
	deleteEntity_.resize(std::distance(deleteEntity_.begin(), std::unique(deleteEntity_.begin(), deleteEntity_.end())));

	for(auto& idToRemove : deleteEntity_)
	{
		componentManager_.DeleteAll(idToRemove);

		delete entity_[idToRemove];
		entity_.erase(idToRemove);
		freeID_.push_back(idToRemove);
	}

	deleteEntity_.clear();
	deleteEntity_.resize(0);
}
