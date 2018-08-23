#include "BenchmarkECS_Component.hpp"

BenchmarkECS_Component::BenchmarkECS_Component()
{
}


BenchmarkECS_Component::~BenchmarkECS_Component()
{
}


void BenchmarkECS_Component::Run(BenchmarkSettings S)
{
	ECS::World* world = nullptr;
	std::vector<ECS::Entity*> entity;
	for(int bench_iteration=0; bench_iteration<S.ITERATION(); ++bench_iteration)
	{
		world = new ECS::World;

		for(int i=0; i<S.ENTITY_COUNT(); ++i)
			entity.push_back(world->CreateEntity());

		start_bench("INSERT COMPONENT");
			for(size_t i=0; i<entity.size(); ++i)
			{
				entity[i]->AddComponent<Component1>();
				entity[i]->AddComponent<Component2>();
				entity[i]->AddComponent<Component3>();
				entity[i]->AddComponent<Component4>();
				entity[i]->AddComponent<Component5>();
				entity[i]->AddComponent<Component6>();
				entity[i]->AddComponent<Component7>();
				entity[i]->AddComponent<Component8>();
				entity[i]->AddComponent<Component9>();
				entity[i]->AddComponent<Component10>();
			}
		stop_bench("INSERT COMPONENT");

		start_bench("ACCESS COMPONENT");
			for(size_t i=0; i<entity.size(); ++i)
			{
				entity[i]->GetComponent<Component1>()->random = 0;
				entity[i]->GetComponent<Component2>()->random = 0;
				entity[i]->GetComponent<Component3>()->random = 0;
				entity[i]->GetComponent<Component4>()->random = 0;
				entity[i]->GetComponent<Component5>()->random = 0;
				entity[i]->GetComponent<Component6>()->random = 0;
				entity[i]->GetComponent<Component7>()->random = 0;
				entity[i]->GetComponent<Component8>()->random = 0;
				entity[i]->GetComponent<Component9>()->random = 0;
				entity[i]->GetComponent<Component10>()->random = 0;
			}
			world->Process();
		stop_bench("ACCESS COMPONENT");

		start_bench("REMOVE COMPONENT");
			for(size_t i=0; i<entity.size(); ++i)
				entity[i]->DestroyComponents();
			world->Process();
		stop_bench("REMOVE COMPONENT");

		for(size_t i=0; i<entity.size(); ++i)
			entity[i]->Destroy();
		world->Process();

		entity.clear();
		entity.resize(0);

		for(int i=0; i<S.ENTITY_COUNT(); ++i)
			entity.push_back(world->CreateEntity());
		start_bench("INSERT+REMOVE COMPONENT");
			for(size_t i=0; i<entity.size(); ++i)
			{
				entity[i]->AddComponent<Component1>();
				entity[i]->AddComponent<Component2>();
				entity[i]->AddComponent<Component3>();
				entity[i]->AddComponent<Component4>();
				entity[i]->AddComponent<Component5>();
				entity[i]->AddComponent<Component6>();
				entity[i]->AddComponent<Component7>();
				entity[i]->AddComponent<Component8>();
				entity[i]->AddComponent<Component9>();
				entity[i]->AddComponent<Component10>();
			}

			for(size_t i=0; i<entity.size(); ++i)
				entity[i]->DestroyComponents();
			world->Process();
		stop_bench("INSERT+REMOVE COMPONENT");

		for(size_t i=0; i<entity.size(); ++i)
			entity[i]->Destroy();
		world->Process();

		delete world;
		entity.clear();
		entity.resize(0);
	}
}
