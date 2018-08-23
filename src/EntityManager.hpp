#ifndef ENTITYMANAGER_HPP_INCLUDED
#define ENTITYMANAGER_HPP_INCLUDED

#include <unordered_map>
#include <vector>

#include "Common.hpp"
#include "Entity.hpp"

namespace ECS
{
	class EntityManager
	{
		void synchronization();

		std::vector<ECS::ID> freeID_;
		std::unordered_map<ECS::ID, Entity*> entity_;
		std::vector<ECS::ID> deleteEntity_;
		ECS::ComponentManager componentManager_;

		public:
			EntityManager();
			EntityManager(const EntityManager& entityManager);
			EntityManager& operator=(const EntityManager& entityManager);
			~EntityManager();

			Entity* Create();
			std::vector<ECS::Entity*> CreateMultiple(size_t n);
			void Delete(ECS::ID entityID);
			void DeleteAll();
			Entity* Get(ECS::ID entityID);
			std::vector<ECS::Entity*> GetAll();
			size_t Count();

			ECS::ComponentManager& GetComponentManager();

			void Update();
	};
}

#endif // ENTITYMANAGER_HPP_INCLUDED
