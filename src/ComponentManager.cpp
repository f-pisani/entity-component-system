#include "ComponentManager.hpp"
#include "EntityManager.hpp"
/*******************************************************************************
PUBLIC METHODS IMPLEMENTATION
*******************************************************************************/
ECS::ComponentManager::ComponentManager(ECS::EntityManager& entityManager) :
	entityManager_(entityManager), component_(), deleteComponent_()
{

}


ECS::ComponentManager::~ComponentManager()
{
	for(auto& itEntityComponent : component_)
	{
		for(auto& itComponent : itEntityComponent.second)
			delete itComponent.second;

		itEntityComponent.second.clear();
	}

	component_.clear();
	deleteComponent_.clear();
	deleteComponent_.resize(0);
}


void ECS::ComponentManager::DeleteAll(ECS::ID entityID)
{
	if(component_.count(entityID))
	{
		for(auto& itEntityComponentsID : component_[entityID])
			deleteComponent_.push_back(std::pair<ECS::ID, ECS::ID>(entityID, itEntityComponentsID.first));
	}
}


std::vector<ECS::Entity*> ECS::ComponentManager::Query(ECS::Requirement requirement)
{
	std::vector<ECS::Entity*> entity;
	std::vector<size_t> reqAnd = requirement.GetAnd();
	std::vector<size_t> reqOr = requirement.GetOr();
	std::vector<size_t> reqNot = requirement.GetNot();

	for(auto& itComponent : component_)
	{
		bool isValidEntity(true);

		// AND
		if(!reqAnd.empty())
		{
			for(auto& itReqAnd : reqAnd)
			{
				if(itComponent.second.count(itReqAnd)==0)
				{
					isValidEntity = false;
					break;
				}
			}
		}

		// OR
		if(!reqOr.empty() && isValidEntity)
		{
			bool isReqOrValid(false);
			for(auto& itReqOr : reqOr)
			{
				if(itComponent.second.count(itReqOr)==1)
				{
					isReqOrValid = true;
					break;
				}
			}

			if(!isReqOrValid)
				isValidEntity = false;
		}

		// NOT
		if(!reqNot.empty() && isValidEntity)
		{
			for(auto& itReqNot : reqNot)
			{
				if(itComponent.second.count(itReqNot)==0)
				{
					isValidEntity = false;
					break;
				}
			}
		}

		if(isValidEntity)
			entity.push_back(entityManager_.Get(itComponent.first));
	}

	return entity;
}


void ECS::ComponentManager::Update()
{
	synchronization();
}


/*******************************************************************************
PRIVATE METHODS IMPLEMENTATION
*******************************************************************************/
void ECS::ComponentManager::synchronization()
{
	for(auto& pairToRemove : deleteComponent_)
	{
		ECS::ID entityID = pairToRemove.first;
		ECS::ID componentID = pairToRemove.second;

		delete component_[entityID][componentID];
		component_[entityID].erase(componentID);

		if(component_[entityID].empty())
			component_.erase(entityID);
	}

	deleteComponent_.clear();
	deleteComponent_.resize(0);
}
