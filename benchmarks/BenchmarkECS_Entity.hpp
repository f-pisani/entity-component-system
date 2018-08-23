#ifndef BENCHMARK_ECS_ENTITY_HPP_INCLUDED
#define BENCHMARK_ECS_ENTITY_HPP_INCLUDED

#include "Benchmark.hpp"
#include "../ecs.hpp"

class BenchmarkECS_Entity : public Benchmark
{
	public:
		BenchmarkECS_Entity();
		~BenchmarkECS_Entity();
		void Run(BenchmarkSettings S);
};

#endif // BENCHMARK_ECS_ENTITY_HPP_INCLUDED
