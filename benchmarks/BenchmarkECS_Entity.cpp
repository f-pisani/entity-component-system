#include "BenchmarkECS_Entity.hpp"

BenchmarkECS_Entity::BenchmarkECS_Entity()
{
}

BenchmarkECS_Entity::~BenchmarkECS_Entity()
{
}

void BenchmarkECS_Entity::Run(BenchmarkSettings S)
{
	ECS::World* world = nullptr;
	for(int bench_iteration=0; bench_iteration<S.ITERATION(); ++bench_iteration)
	{
		world = new ECS::World;

		start_bench("INSERT ENTITY");
			world->CreateMultipleEntity(S.ENTITY_COUNT());
		stop_bench("INSERT ENTITY");

		start_bench("REMOVE ENTITY");
			world->DeleteAllEntity();
			world->Process();
		stop_bench("REMOVE ENTITY");

		start_bench("INSERT+REMOVE ENTITY");
			world->CreateMultipleEntity(S.ENTITY_COUNT());
			world->DeleteAllEntity();
			world->Process();
		stop_bench("INSERT+REMOVE ENTITY");

		delete world;
	}
}
