#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include "Common.hpp"
#include "BaseComponent.hpp"

namespace ECS
{
	template<class DerivedComponent>
	class Component : public BaseComponent
	{
		public:
			Component();
			virtual ~Component();

			static ECS::ID const ID;
	};
}


/*******************************************************************************
PUBLIC STATIC MEMBER TEMPATE IMPLEMENTATION
*******************************************************************************/
template<class DerivedComponent> ECS::ID const ECS::Component<DerivedComponent>::ID = ECS::BaseComponent::GetDerivedComponentID<DerivedComponent>();


/*******************************************************************************
PUBLIC METHODS TEMPLATE IMPLEMENTATION
*******************************************************************************/
template<class DerivedComponent> ECS::Component<DerivedComponent>::Component()
{
}



template<class DerivedComponent> ECS::Component<DerivedComponent>::~Component()
{
}


#endif // COMPONENT_HPP_INCLUDED
