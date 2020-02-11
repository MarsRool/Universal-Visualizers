#include "stdafx.h"
#include "DoublePreciseApproximate.h"

MR::Helpers::DoublePreciseApproximate::DoublePreciseApproximate() : value(0.0), epsilon(smallV), type(AccuracyType::Approximate)
{
}

MR::Helpers::DoublePreciseApproximate::DoublePreciseApproximate(double value, double epsilon, AccuracyType type) : value(value), epsilon(epsilon), type(type)
{
	if (epsilon < smallV)
		this->epsilon = smallV;
}

MR::Helpers::DoublePreciseApproximate::DoublePreciseApproximate(const DoublePreciseApproximate & other, double epsilon) : value(other.value)
{
	if (epsilon < smallV)
		this->epsilon = other.epsilon;
	else
		this->epsilon = epsilon;
	this->type = other.type;
}

const bool MR::Helpers::DoublePreciseApproximate::operator==(const DoublePreciseApproximate & right) const
{
	double epsilon;
	if (((type == right.type) ? type == AccuracyType::Precise : false))
	{//Precise
		return (this->value == right.value);
	}
	else
	{//Approximate
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (std::abs(this->value - right.value) <= epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator!=(const DoublePreciseApproximate & right) const
{
	return !(*this == right);
}

const bool MR::Helpers::DoublePreciseApproximate::operator>(const DoublePreciseApproximate & right) const
{
	double epsilon;
	if (((type == right.type) ? type == AccuracyType::Precise : false))
	{//Precise
		return (this->value > right.value);
	}
	else
	{//Approximate
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (this->value - right.value > epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator<(const DoublePreciseApproximate & right) const
{
	double epsilon;
	if (((type == right.type) ? type == AccuracyType::Precise : false))
	{//Precise
		return (this->value < right.value);
	}
	else
	{//Approximate
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (right.value - this->value > epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator>=(const DoublePreciseApproximate & right) const
{
	double epsilon;
	if (((type == right.type) ? type == AccuracyType::Precise : false))
	{//Precise
		return (this->value >= right.value);
	}
	else
	{//Approximate
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (this->value - right.value >= -epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator<=(const DoublePreciseApproximate & right) const
{
	double epsilon;
	if (((type == right.type) ? type == AccuracyType::Precise : false))
	{//Precise
		return (this->value <= right.value);
	}
	else
	{//Approximate
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (right.value - this->value >= -epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator==(double right) const
{
	if (type == AccuracyType::Precise)
	{//Precise
		return (this->value == right);
	}
	else
	{//Approximate
		return (std::abs(this->value - right) <= epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator!=(double right) const
{
	return !(*this == right);
}

const bool MR::Helpers::DoublePreciseApproximate::operator>(double right) const
{
	if (type == AccuracyType::Precise)
	{//Precise
		return (this->value > right);
	}
	else
	{//Approximate
		return (this->value - right > epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator<(double right) const
{
	if (type == AccuracyType::Precise)
	{//Precise
		return (this->value < right);
	}
	else
	{//Approximate
		return (right - this->value > epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator>=(double right) const
{
	if (type == AccuracyType::Precise)
	{//Precise
		return (this->value >= right);
	}
	else
	{//Approximate
		return (this->value - right >= -epsilon);
	}
}

const bool MR::Helpers::DoublePreciseApproximate::operator<=(double right) const
{
	if (type == AccuracyType::Precise)
	{//Precise
		return (this->value <= right);
	}
	else
	{//Approximate
		return (right - this->value >= -epsilon);
	}
}

MR::Helpers::DoublePreciseApproximate & MR::Helpers::DoublePreciseApproximate::operator=(const DoublePreciseApproximate & right)
{
	if (&right == this)
		return *this;
	this->epsilon = right.epsilon;
	this->value = right.value;
	this->type = right.type;
	return *this;
}

MR::Helpers::DoublePreciseApproximate & MR::Helpers::DoublePreciseApproximate::operator=(double right)
{
	this->value = right;
	return *this;
}

MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator+(const DoublePreciseApproximate & right) const
{
	double epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
	return DoublePreciseApproximate(this->value + right.value, epsilon);
}

MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator-(const DoublePreciseApproximate & right) const
{
	double epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
	return DoublePreciseApproximate(this->value - right.value, epsilon);
}

MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator*(const DoublePreciseApproximate & right) const
{
	double epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
	return DoublePreciseApproximate(this->value * right.value, epsilon);
}

MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator/(const DoublePreciseApproximate & right) const
{
	double epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
	if (right.value < epsilon)
		throw std::exception("DoublePreciseApproximate: dividing by zero");
	return DoublePreciseApproximate(this->value / right.value, epsilon);
}

MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator+(double right) const
{
	return DoublePreciseApproximate(this->value + right, epsilon);
}

MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator-(double right) const
{
	return DoublePreciseApproximate(this->value - right, epsilon);
}

MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator*(double right) const
{
	return DoublePreciseApproximate(this->value * right, epsilon);
}

MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator/(double right) const
{
	if (right < epsilon)
		throw std::exception("DoublePreciseApproximate: dividing by zero");
	return DoublePreciseApproximate(this->value / right, epsilon);
}