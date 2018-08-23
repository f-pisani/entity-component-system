#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "Common.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

namespace ECS
{
	class World
	{
		public:
			World();
			World(const ECS::World& world);
			World& operator=(const ECS::World& world);
			~World();
			void Process();

			/// [E]ntity
			ECS::Entity* CreateEntity();
			std::vector<ECS::Entity*> CreateMultipleEntity(size_t n);
			void DeleteEntity(ECS::ID id);
			void DeleteAllEntity();
			ECS::Entity* GetEntity(ECS::ID id);
			std::vector<ECS::Entity*> GetAllEntity();
			size_t GetEntityCount();

			/// [S]ystem
			template <class DerivedSystem, typename... Args> DerivedSystem* CreateSystem(Args&&... args);
			template <class DerivedSystem> DerivedSystem* GetSystem();
			template <class DerivedSystem> bool DeleteSystem();

		private:
			ECS::EntityManager entityManager_;
			ECS::SystemManager systemManager_;
	};
}


/// TEMPLATE IMPLEMENTATION
/// [S]ystem
template <class DerivedSystem, typename... Args> DerivedSystem* ECS::World::CreateSystem(Args&&... args)
{
	return systemManager_.Create<DerivedSystem, Args...>(static_cast<Args&&>(args)...);
}


template <class DerivedSystem> DerivedSystem* ECS::World::GetSystem()
{
	return systemManager_.Get<DerivedSystem>();
}

template <class DerivedSystem> bool ECS::World::DeleteSystem()
{
	return systemManager_.Delete<DerivedSystem>();
}
#endif // WORLD_HPP_INCLUDED
