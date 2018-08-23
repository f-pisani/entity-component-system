#ifndef BASESYSTEM_HPP_INCLUDED
#define BASESYSTEM_HPP_INCLUDED

#include <vector>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

#include "Entity.hpp"
#include "Requirement.hpp"

namespace ECS
{
	class BaseSystem
	{
		static std::unordered_map<std::type_index, ECS::ID> derivedSystemID_;
		ECS::Requirement requirement_;
		unsigned int priority_;
		bool passive_;

		public:
			BaseSystem();
			virtual ~BaseSystem();

			virtual void Update(std::vector<ECS::Entity*> entity) = 0;

			void SetRequirement(ECS::Requirement requirement);
			ECS::Requirement GetRequirement() const;
			void SetPriority(unsigned int priority);
			unsigned int GetPriority() const;
			void SetPassive(bool passive);
			bool IsPassive();

		protected:
			template<class DerivedSystem> static ECS::ID GetDerivedSystemID();
	};
}


/*******************************************************************************
PROTECTED METHODS TEMPLATE IMPLEMENTATION
*******************************************************************************/
template<class DerivedSystem> ECS::ID ECS::BaseSystem::GetDerivedSystemID()
{
	if(derivedSystemID_.size() == 0)
		derivedSystemID_ = std::unordered_map<std::type_index, ECS::ID>();

	if(derivedSystemID_.count(std::type_index(typeid(DerivedSystem))) == 0)
		derivedSystemID_[std::type_index(typeid(DerivedSystem))] = derivedSystemID_.size();

	return derivedSystemID_[std::type_index(typeid(DerivedSystem))];
}


#endif // BASESYSTEM_HPP_INCLUDED
