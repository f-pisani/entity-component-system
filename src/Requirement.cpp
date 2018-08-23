#include "Requirement.hpp"

ECS::Requirement::Requirement(std::vector<size_t> req_and, std::vector<size_t> req_or, std::vector<size_t> req_not) :
	and_(req_and), or_(req_or), not_(req_not)
{
}


ECS::Requirement::~Requirement()
{
}


std::vector<size_t> ECS::Requirement::GetAnd()
{
	return and_;
}


std::vector<size_t> ECS::Requirement::GetOr()
{
	return or_;
}


std::vector<size_t> ECS::Requirement::GetNot()
{
	return not_;
}
