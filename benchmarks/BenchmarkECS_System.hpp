#ifndef BENCHMARK_ECS_SYSTEM_HPP_INCLUDED
#define BENCHMARK_ECS_SYSTEM_HPP_INCLUDED

#include "Benchmark.hpp"
#include "../ecs.hpp"

class BenchmarkECS_System : public Benchmark
{
	public:
		BenchmarkECS_System();
		~BenchmarkECS_System();
		void Run(BenchmarkSettings S);
};

#endif // BENCHMARK_ECS_SYSTEM_HPP_INCLUDED
