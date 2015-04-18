#include "NLPVectorExpression.h"

#include <cassert>


NLPVectorExpression::NLPVectorExpression(const Index _dimension)
{
	expressions_.resize(_dimension, NLPExpression());
}

NLPVectorExpression::~NLPVectorExpression()
{

}

void NLPVectorExpression::get_segment(const Index _index, const Index _sub_dimension) const
{
	assert(_index + _sub_dimension <= dimension());

	NLPVectorExpression segment(_sub_dimension);
	for (Index i = 0; i < _sub_dimension; ++i)
	{
		segment.expressions_[i] = this->expressions_[_index + i];
	}
}

void NLPVectorExpression::set_segment(const Index _index, const NLPVectorExpression &_segment)
{
	const Index sub_dimension = _segment.dimension();
	assert(_index + sub_dimension <= dimension());

	for (Index i = 0; i < sub_dimension; ++i)
	{
		this->expressions_[i] = _segment.expressions_[_index + i];
	}
}

NLPVectorExpression& NLPVectorExpression::operator+=(const NLPVectorExpression& rhs)
{
	assert(this->dimension() == rhs.dimension());
	std::vector< NLPExpression >::iterator it = this->expressions_.begin();
	std::vector< NLPExpression >::const_iterator jt = rhs.expressions_.begin();
	for (; it != this->expressions_.end() && jt != rhs.expressions_.end(); ++it, ++jt)
	{
		(*it) += (*jt);
	}
	return *this;
}

NLPVectorExpression& NLPVectorExpression::operator-=(const NLPVectorExpression& rhs)
{
	assert(this->dimension() == rhs.dimension());
	std::vector< NLPExpression >::iterator it = this->expressions_.begin();
	std::vector< NLPExpression >::const_iterator jt = rhs.expressions_.begin();
	for (; it != this->expressions_.end() && jt != rhs.expressions_.end(); ++it, ++jt)
	{
		(*it) -= (*jt);
	}
	return *this;
}

NLPVectorExpression& NLPVectorExpression::operator*=(const Number& rhs)
{
	for (std::vector< NLPExpression >::iterator it = this->expressions_.begin();
		it != this->expressions_.end(); ++it)
	{
		(*it) *= rhs;
	}
	return *this;
}

NLPVectorExpression& NLPVectorExpression::operator*=(const NLPExpression& rhs)
{
	for (std::vector< NLPExpression >::iterator it = this->expressions_.begin();
		it != this->expressions_.end(); ++it)
	{
		(*it) *= rhs;
	}
	return *this;
}

NLPExpression& NLPVectorExpression::operator[](const Index i)
{
	assert(i < dimension());
	return expressions_[i];
}

const NLPExpression& NLPVectorExpression::operator[](const Index i) const
{
	assert(i < dimension());
	return expressions_[i];
}

NLPExpression NLPVectorExpression::dot_product(
	const NLPVectorExpression& _vector_1, const NLPVectorExpression& _vector_2)
{
	assert(_vector_1.dimension() == _vector_2.dimension());
	const Index dimension = _vector_1.dimension();

	NLPExpression output;
	for (unsigned int i = 0; i < dimension; ++i)
		output += (_vector_1.expressions_[i] * _vector_2.expressions_[i]);

	return output;
}

NLPVectorExpression NLPVectorExpression::cross_product(
	const NLPVectorExpression& _vector_1, const NLPVectorExpression& _vector_2)
{
	assert(_vector_1.dimension() == _vector_2.dimension());
	const Index dimension = _vector_1.dimension();

	// NOTE:
	// Implemented only for 3 dimension.
	assert(dimension == 3);

	// (coeff, v1_index, v2_index);
	const int cross_product_terms[3][2][3] = {
		{ { 1, 0, 1 }, { -1, 1, 0 } },
		{ { 1, 1, 2 }, { -1, 2, 1 } },
		{ { 1, 2, 0 }, { -1, 0, 2 } }
	};

	NLPVectorExpression output(dimension);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			output[i] += (_vector_1.expressions_[cross_product_terms[i][j][1]]
				* _vector_2.expressions_[cross_product_terms[i][j][2]]);

			// Coefficient.
			output[i] *= static_cast<Number>(cross_product_terms[i][j][0]);
		}
	}

	return output;
}