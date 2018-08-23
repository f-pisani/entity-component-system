#ifndef REQUIREMENT_HPP_INCLUDED
#define REQUIREMENT_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <typeinfo>

namespace ECS
{
	class Requirement
	{
		public:
			Requirement(std::vector<size_t> req_and = std::vector<size_t>(),
						std::vector<size_t> req_or = std::vector<size_t>(),
						std::vector<size_t> req_not = std::vector<size_t>());
			~Requirement();

			template<typename... Req> static std::vector<size_t> Require();

			std::vector<size_t> GetAnd();
			std::vector<size_t> GetOr();
			std::vector<size_t> GetNot();

		private:
			std::vector<size_t> and_;
			std::vector<size_t> or_;
			std::vector<size_t> not_;
	};
}


/// TEMPLATE IMPLEMENTATION
template<typename... Req> std::vector<size_t> ECS::Requirement::Require()
{
	std::vector<size_t> req;
	req.insert(req.end(), {Req::ID...});

	return req;
}


#endif // REQUIREMENT_HPP_INCLUDED
