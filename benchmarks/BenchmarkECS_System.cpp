#include "BenchmarkECS_System.hpp"
#include "BenchmarkECS_Component.hpp"

BenchmarkECS_System::BenchmarkECS_System()
{
}

BenchmarkECS_System::~BenchmarkECS_System()
{
}

void BenchmarkECS_System::Run(BenchmarkSettings S)
{
	ECS::World* world = nullptr;
	std::vector<ECS::Entity*> entity;
	for(int bench_iteration=0; bench_iteration<S.ITERATION(); ++bench_iteration)
	{
		world = new ECS::World;
		start_bench("INSERT SYSTEM");
			System1 *s1 = world->CreateSystem<System1>();
			s1->SetRequirement(ECS::Requirement(ECS::Requirement::Require<Component1, Component3>()));

			System2 *s2 = world->CreateSystem<System2>();
			s2->SetRequirement(ECS::Requirement(ECS::Requirement::Require<Component2, Component5>()));

			System3 *s3 = world->CreateSystem<System3>();
			s3->SetRequirement(ECS::Requirement(ECS::Requirement::Require<Component4, Component7>()));

			System4 *s4 = world->CreateSystem<System4>();
			s4->SetRequirement(ECS::Requirement(ECS::Requirement::Require<Component6, Component9>()));

			System5 *s5 = world->CreateSystem<System5>();
			s5->SetRequirement(ECS::Requirement(ECS::Requirement::Require<Component8, Component10>()));
		stop_bench("INSERT SYSTEM");

		for(int i=0; i<S.ENTITY_COUNT(); ++i)
		{
			entity.push_back(world->CreateEntity());
			switch(i%5)
			{
				case 0:
					entity[i]->AddComponent<Component1>();
					entity[i]->AddComponent<Component3>();
				break;

				case 1:
					entity[i]->AddComponent<Component2>();
					entity[i]->AddComponent<Component5>();
				break;

				case 2:
					entity[i]->AddComponent<Component4>();
					entity[i]->AddComponent<Component7>();
				break;

				case 3:
					entity[i]->AddComponent<Component6>();
					entity[i]->AddComponent<Component9>();
				break;

				case 4:
					entity[i]->AddComponent<Component8>();
					entity[i]->AddComponent<Component10>();
				break;

				default: ;
			}
		}

		start_bench("WORLD PROCESS SYSTEM");
			world->Process();
		stop_bench("WORLD PROCESS SYSTEM");

		start_bench("REMOVE SYSTEM");
			world->DeleteSystem<System1>();
			world->DeleteSystem<System2>();
			world->DeleteSystem<System3>();
			world->DeleteSystem<System4>();
			world->DeleteSystem<System5>();
			world->Process();
		stop_bench("REMOVE SYSTEM");

		delete world;
		entity.clear();
		entity.resize(0);
	}
}
