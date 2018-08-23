#ifndef BENCHMARK_ECS_COMPONENT_HPP_INCLUDED
#define BENCHMARK_ECS_COMPONENT_HPP_INCLUDED

#include "Benchmark.hpp"
#include "../ecs.hpp"

class BenchmarkECS_Component : public Benchmark
{
	public:
		BenchmarkECS_Component();
		~BenchmarkECS_Component();
		void Run(BenchmarkSettings S);
};

#endif // BENCHMARK_ECS_COMPONENT_HPP_INCLUDED
