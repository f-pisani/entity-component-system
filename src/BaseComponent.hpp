#ifndef BASECOMPONENT_HPP_INCLUDED
#define BASECOMPONENT_HPP_INCLUDED

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "Common.hpp"

namespace ECS
{
	class BaseComponent
	{
		static std::unordered_map<std::type_index, ECS::ID> derivedComponentID_;

		public:
			BaseComponent();
			virtual ~BaseComponent();
			template<class DerivedComponent> static ECS::ID GetDerivedComponentID();
	};
}

/*******************************************************************************
PROTECTED METHODS TEMPLATE IMPLEMENTATION
*******************************************************************************/
template<class DerivedComponent> ECS::ID ECS::BaseComponent::GetDerivedComponentID()
{
	if(derivedComponentID_.size()==0)
		derivedComponentID_ = std::unordered_map<std::type_index, ECS::ID>();

	if(derivedComponentID_.count(std::type_index(typeid(DerivedComponent))) == 0)
		derivedComponentID_[std::type_index(typeid(DerivedComponent))] = derivedComponentID_.size()-1;

	return derivedComponentID_[std::type_index(typeid(DerivedComponent))];
}


#endif // BASECOMPONENT_HPP_INCLUDED
