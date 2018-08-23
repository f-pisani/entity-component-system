#ifndef SYSTEM_HPP_INCLUDED
#define SYSTEM_HPP_INCLUDED

#include "Common.hpp"
#include "BaseSystem.hpp"

namespace ECS
{
	template <class DerivedSystem>
	class System : public BaseSystem
	{
		public:
			System();
			System(const ECS::System<DerivedSystem>& system);
			ECS::System<DerivedSystem>& operator=(const ECS::System<DerivedSystem>& system);
			virtual ~System();

			static ECS::ID const ID;
	};
}


/*******************************************************************************
PUBLIC STATIC MEMBER TEMPLATE IMPLEMENTATION
*******************************************************************************/
template <class DerivedSystem>
ECS::ID const ECS::System<DerivedSystem>::ID = GetDerivedSystemID<DerivedSystem>();


/*******************************************************************************
PUBLIC METHODS TEMPLATE IMPLEMENTATION
*******************************************************************************/
template <class DerivedSystem>
ECS::System<DerivedSystem>::System()
{
}


template<class DerivedSystem>
ECS::System<DerivedSystem>::~System()
{
}


#endif // SYSTEM_HPP_INCLUDED
