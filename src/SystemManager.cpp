#include "SystemManager.hpp"
/*******************************************************************************
PUBLIC METHODS IMPLEMENTATION
*******************************************************************************/
ECS::SystemManager::SystemManager(ECS::EntityManager& entityManager) :
	entityManager_(entityManager), system_(), deleteSystem_()
{

}


ECS::SystemManager::~SystemManager()
{
	for(auto& itSystem : system_)
		delete itSystem.second;

	system_.clear();
	deleteSystem_.clear();
	deleteSystem_.resize(0);
}


void ECS::SystemManager::Update()
{
	synchronization();

	std::multimap<unsigned int, ECS::BaseSystem*, std::greater<unsigned int>> systemByPriority;
	for(auto& itSystem : system_)
	{
		if(!itSystem.second->IsPassive())
			systemByPriority.insert(std::make_pair(itSystem.second->GetPriority(), itSystem.second));
	}

	ECS::ComponentManager& componentManager = entityManager_.GetComponentManager();
	for(auto &itSystemByPriority : systemByPriority)
	{
		ECS::BaseSystem* current_system(itSystemByPriority.second);
		ECS::Requirement requirements(current_system->GetRequirement());
		current_system->Update(componentManager.Query(requirements));
	}
}


/*******************************************************************************
PRIVATE METHODS IMPLEMENTATION
*******************************************************************************/
void ECS::SystemManager::synchronization()
{
	for(auto& idToRemove : deleteSystem_)
	{
		delete system_[idToRemove];
		system_.erase(idToRemove);
	}

	deleteSystem_.clear();
	deleteSystem_.resize(0);
}
