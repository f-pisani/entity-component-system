#include "BaseComponent.hpp"
/*******************************************************************************
PRIVATE STATIC MEMBER IMPLEMENTATION
*******************************************************************************/
std::unordered_map<std::type_index, ECS::ID> ECS::BaseComponent::derivedComponentID_ = std::unordered_map<std::type_index, ECS::ID>();


/*******************************************************************************
PUBLIC METHODS IMPLEMENTATION
*******************************************************************************/
ECS::BaseComponent::BaseComponent()
{
}

ECS::BaseComponent::~BaseComponent()
{
}
