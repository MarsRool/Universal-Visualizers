#include "stdafx.h"
#include "DoublePreciseApproximate.h"

MR::Helpers::DoublePreciseApproximate::DoublePreciseApproximate()
{
	value = 0.0;
	epsilon = smallV;
	type = AccuracyType::Approximate;
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

inline MR::Helpers::DoublePreciseApproximate::AccuracyType MR::Helpers::DoublePreciseApproximate::getAccuracyType() const
{
	return type;
}

inline void MR::Helpers::DoublePreciseApproximate::setAccuracyType(AccuracyType type)
{
	this->type = type;
}

inline double MR::Helpers::DoublePreciseApproximate::getEpsilon() const
{
	return epsilon;
}

inline void MR::Helpers::DoublePreciseApproximate::setEpsilon(double epsilon)
{
	this->epsilon = epsilon;
}

inline double MR::Helpers::DoublePreciseApproximate::getValue() const
{
	return value;
}

inline double MR::Helpers::DoublePreciseApproximate::operator()() const
{
	return value;
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator==(const DoublePreciseApproximate & right) const
{
	double epsilon;
	switch (((type == right.type) ? type : AccuracyType::Approximate))
	{
	case AccuracyType::Precise:
		return (this->value == right.value);
	case AccuracyType::Approximate:
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (std::abs(this->value - right.value) <= epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator!=(const DoublePreciseApproximate & right) const
{
	return !(*this == right);
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator>(const DoublePreciseApproximate & right) const
{
	double epsilon;
	switch (((type == right.type) ? type : AccuracyType::Approximate))
	{
	case AccuracyType::Precise:
		return (this->value > right.value);
	case AccuracyType::Approximate:
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (this->value - right.value > epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator<(const DoublePreciseApproximate & right) const
{
	double epsilon;
	switch (((type == right.type) ? type : AccuracyType::Approximate))
	{
	case AccuracyType::Precise:
		return (this->value < right.value);
	case AccuracyType::Approximate:
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (right.value - this->value > epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator>=(const DoublePreciseApproximate & right) const
{
	double epsilon;
	switch (((type == right.type) ? type : AccuracyType::Approximate))
	{
	case AccuracyType::Precise:
		return (this->value >= right.value);
	case AccuracyType::Approximate:
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (this->value - right.value >= -epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator<=(const DoublePreciseApproximate & right) const
{
	double epsilon;
	switch (((type == right.type) ? type : AccuracyType::Approximate))
	{
	case AccuracyType::Precise:
		return (this->value <= right.value);
	case AccuracyType::Approximate:
		epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
		return (right.value - this->value >= -epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator==(double right) const
{
	switch (type)
	{
	case AccuracyType::Precise:
		return (this->value == right);
	case AccuracyType::Approximate:
		return (std::abs(this->value - right) <= epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator!=(double right) const
{
	return !(*this == right);
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator>(double right) const
{
	switch (type)
	{
	case AccuracyType::Precise:
		return (this->value > right);
	case AccuracyType::Approximate:
		return (this->value - right > epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator<(double right) const
{
	switch (type)
	{
	case AccuracyType::Precise:
		return (this->value < right);
	case AccuracyType::Approximate:
		return (right - this->value > epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator>=(double right) const
{
	switch (type)
	{
	case AccuracyType::Precise:
		return (this->value >= right);
	case AccuracyType::Approximate:
		return (this->value - right >= -epsilon);
	default:
		return false;
	}
}

inline const bool MR::Helpers::DoublePreciseApproximate::operator<=(double right) const
{
	switch (type)
	{
	case AccuracyType::Precise:
		return (this->value <= right);
	case AccuracyType::Approximate:
		return (right - this->value >= -epsilon);
	default:
		return false;
	}
}

inline MR::Helpers::DoublePreciseApproximate & MR::Helpers::DoublePreciseApproximate::operator=(const DoublePreciseApproximate & right)
{
	if (&right == this)
		return *this;
	this->epsilon = right.epsilon;
	this->value = right.value;
	this->type = right.type;
	return *this;
}

inline MR::Helpers::DoublePreciseApproximate & MR::Helpers::DoublePreciseApproximate::operator=(double right)
{
	this->value = right;
	return *this;
}

inline MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator+(const DoublePreciseApproximate & right) const
{
	double epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
	return DoublePreciseApproximate(this->value + right.value, epsilon);
}

inline MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator-(const DoublePreciseApproximate & right) const
{
	double epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
	return DoublePreciseApproximate(this->value - right.value, epsilon);
}

inline MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator*(const DoublePreciseApproximate & right) const
{
	double epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
	return DoublePreciseApproximate(this->value * right.value, epsilon);
}

inline MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator/(const DoublePreciseApproximate & right) const
{
	double epsilon = (this->epsilon < right.epsilon) ? this->epsilon : right.epsilon;
	if (right.value < epsilon)
		throw std::exception("DoublePreciseApproximate: dividing by zero");
	return DoublePreciseApproximate(this->value / right.value, epsilon);
}

inline MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator+(double right) const
{
	return DoublePreciseApproximate(this->value + right, epsilon);
}

inline MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator-(double right) const
{
	return DoublePreciseApproximate(this->value - right, epsilon);
}

inline MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator*(double right) const
{
	return DoublePreciseApproximate(this->value * right, epsilon);
}

inline MR::Helpers::DoublePreciseApproximate MR::Helpers::DoublePreciseApproximate::operator/(double right) const
{
	if (right < epsilon)
		throw std::exception("DoublePreciseApproximate: dividing by zero");
	return DoublePreciseApproximate(this->value / right, epsilon);
}