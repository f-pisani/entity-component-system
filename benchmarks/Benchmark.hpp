#ifndef BENCHMARK_HPP_INCLUDED
#define BENCHMARK_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <ratio>
#include <chrono>

#include "../ecs.hpp"
class BenchmarkSettings
{
	public:
		BenchmarkSettings(int iteration, int count) : iteration_(iteration), entityCount_(count){}
		~BenchmarkSettings(){}
		inline int ITERATION(){ return iteration_; }
		inline int ENTITY_COUNT(){ return entityCount_; }

	private:
		const int iteration_;
		const int entityCount_;
};

class Benchmark
{
	public:
		Benchmark();
		virtual ~Benchmark();

		virtual void Run(BenchmarkSettings settings) =0;
		void Print();
		void SaveCSV(std::string filename);

		static const BenchmarkSettings LOW_BENCH_SETTINGS;
		static const BenchmarkSettings MEDIUM_BENCH_SETTINGS;
		static const BenchmarkSettings HIGH_BENCH_SETTINGS;
		static const BenchmarkSettings EXTREME_BENCH_SETTINGS;

	protected:
		void start_bench(std::string name);
		void stop_bench(std::string name);

	private:
		std::unordered_map<std::string, std::pair<std::chrono::steady_clock::time_point, std::chrono::steady_clock::time_point>> benchChrono_;
		std::unordered_map<std::string, std::vector<std::chrono::duration<double>>> results_;
};

class Component1 : public ECS::Component<Component1>
{
	public:
		Component1() : random(0) {}
		~Component1(){}
		int random;
};

class Component2 : public ECS::Component<Component2>
{
	public:
		Component2() : random(0) {}
		~Component2(){}
		int random;
};

class Component3 : public ECS::Component<Component3>
{
	public:
		Component3() : random(0) {}
		~Component3(){}
		int random;
};

class Component4 : public ECS::Component<Component4>
{
	public:
		Component4() : random(0) {}
		~Component4(){}
		int random;
};

class Component5 : public ECS::Component<Component5>
{
	public:
		Component5() : random(0) {}
		~Component5(){}
		int random;
};

class Component6 : public ECS::Component<Component6>
{
	public:
		Component6() : random(0) {}
		~Component6(){}
		int random;
};

class Component7 : public ECS::Component<Component7>
{
	public:
		Component7() : random(0) {}
		~Component7(){}
		int random;
};

class Component8 : public ECS::Component<Component8>
{
	public:
		Component8() : random(0) {}
		~Component8(){}
		int random;
};

class Component9 : public ECS::Component<Component9>
{
	public:
		Component9() : random(0) {}
		~Component9(){}
		int random;
};

class Component10 : public ECS::Component<Component10>
{
	public:
		Component10() : random(0) {}
		~Component10(){}
		int random;
};

class System1 : public ECS::System<System1>
{
	public:
		System1(){}
		~System1(){}

		void Update(std::vector<ECS::Entity*> entity)
		{
			for(size_t i=0; i<entity.size(); ++i)
			{
				entity[i]->GetComponent<Component1>()->random++;
				entity[i]->GetComponent<Component3>()->random++;
			}
		}
};

class System2 : public ECS::System<System2>
{
	public:
		System2(){}
		~System2(){}

		void Update(std::vector<ECS::Entity*> entity)
		{
			for(size_t i=0; i<entity.size(); ++i)
			{
				entity[i]->GetComponent<Component2>()->random++;
				entity[i]->GetComponent<Component5>()->random++;
			}
		}
};

class System3 : public ECS::System<System3>
{
	public:
		System3(){}
		~System3(){}

		void Update(std::vector<ECS::Entity*> entity)
		{
			for(size_t i=0; i<entity.size(); ++i)
			{
				entity[i]->GetComponent<Component4>()->random++;
				entity[i]->GetComponent<Component7>()->random++;
			}
		}
};

class System4 : public ECS::System<System4>
{
	public:
		System4(){}
		~System4(){}

		void Update(std::vector<ECS::Entity*> entity)
		{
			for(size_t i=0; i<entity.size(); ++i)
			{
				entity[i]->GetComponent<Component6>()->random++;
				entity[i]->GetComponent<Component9>()->random++;
			}
		}
};

class System5 : public ECS::System<System5>
{
	public:
		System5(){}
		~System5(){}

		void Update(std::vector<ECS::Entity*> entity)
		{
			for(size_t i=0; i<entity.size(); ++i)
			{
				entity[i]->GetComponent<Component8>()->random++;
				entity[i]->GetComponent<Component10>()->random++;
			}
		}
};

#endif // BENCHMARK_HPP_INCLUDED
