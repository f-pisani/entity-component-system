#include "BaseSystem.hpp"
/*******************************************************************************
PRIVATE STATIC MEMBER IMPLEMENTATION
*******************************************************************************/
std::unordered_map<std::type_index, ECS::ID> ECS::BaseSystem::derivedSystemID_ = std::unordered_map<std::type_index, ECS::ID>();


/*******************************************************************************
PUBLIC METHODS IMPLEMENTATION
*******************************************************************************/
ECS::BaseSystem::BaseSystem() :
	requirement_(), priority_(0), passive_(false)
{
}


ECS::BaseSystem::~BaseSystem()
{
}


void ECS::BaseSystem::SetRequirement(ECS::Requirement requirement)
{
	requirement_ = requirement;
}


ECS::Requirement ECS::BaseSystem::GetRequirement() const
{
	return requirement_;
}


void ECS::BaseSystem::SetPriority(unsigned int priority)
{
	priority_ = priority;
}


unsigned int ECS::BaseSystem::GetPriority() const
{
	return priority_;
}


void ECS::BaseSystem::SetPassive(bool passive)
{
	passive_ = passive;
}


bool ECS::BaseSystem::IsPassive()
{
	return passive_;
}
