#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <array>
#include "math.h"

#include "VectorExceptions.h"

// Vector Template
template<class TYPE, unsigned int DIM>
class CVector
{
public:

   // Constructors & Destructors
   CVector() : m_data(std::array<TYPE, DIM>{0}) {};
   CVector(const CVector<TYPE, DIM>& vector)
   {
      std::copy(vector.begin(), vector.end(), begin());
   }

   CVector(std::initializer_list<TYPE> data)
   {
      if (data.size() > DIM)
      {
         throw XVectorDimensionIncorrect(DIM, data.size());
      }
      std::copy(data.begin(), data.end(), begin());
   }

   ~CVector() {};

   // Basic Properties
   int Size()
   {
      return m_data.size();
   }

   // Validation
   int IsEqualLength(const CVector& vec)
   {
      return m_data.size() == vec.Size();
   }

   // Random Access Operators
   TYPE& operator[] (unsigned int n)
   {
      return m_data[n];
   }

   const TYPE& operator[] (unsigned int n) const
   {
      return m_data[n];
   }

   // Iterators
   typename std::array<TYPE, DIM>::iterator begin()
   {
      return m_data.begin();
   }

   typename std::array<TYPE, DIM>::const_iterator begin() const
   {
      return m_data.begin();
   }

   typename std::array<TYPE, DIM>::iterator end()
   {
      return m_data.end();
   }

   typename std::array<TYPE, DIM>::const_iterator end() const
   {
      return m_data.end();
   }

   // Arithmetic Operators
   friend CVector<TYPE, DIM> operator+(CVector<TYPE, DIM> lhs, const CVector<TYPE, DIM>& rhs)
   {
      return lhs += rhs;
   }

   CVector<TYPE, DIM>& operator+=(const CVector<TYPE, DIM>& rhs)
   {
      for (unsigned int i = 0; i < DIM; ++i)
      {
         m_data[i] += rhs[i];
      }
      return *this;
   }

   friend CVector<TYPE, DIM> operator-(CVector<TYPE, DIM> lhs, const CVector<TYPE, DIM>& rhs)
   {
      return lhs -= rhs;
   }

   CVector<TYPE, DIM>& operator-=(const CVector<TYPE, DIM>& rhs)
   {
      for (unsigned int i = 0; i < DIM; ++i)
      {
         m_data[i] -= rhs[i];
      }
      return *this;
   }

   // Multiplication with other types
   friend CVector<TYPE, DIM> operator*(CVector lhs, const TYPE& rhs)
   {
      return lhs *= rhs;
   }

   friend CVector<TYPE, DIM> operator*(const TYPE& lhs, CVector rhs)
   {
      return rhs *= lhs;
   }

   CVector<TYPE, DIM>& operator*=(const TYPE& rhs)
   {
      for (unsigned int i = 0; i < DIM; ++i)
      {
         m_data[i] *= rhs;
      }
      return *this;
   }

   // Component wise multiplication
   //friend CVector<TYPE, DIM> operator*(CVector<TYPE, DIM> lhs, const CVector<TYPE, DIM>& rhs)
   //{
   //   return lhs *= rhs;
   //}

   //CVector<TYPE, DIM>& operator*=(const CVector<TYPE, DIM>& rhs)
   //{
   //   for (unsigned int i = 0; i < DIM; ++i)
   //   {
   //      m_data[i] *= rhs[i];
   //   }
   //   return *this;
   //}

   // Component wise division
   //friend CVector<TYPE, DIM> operator/(CVector<TYPE, DIM> lhs, const CVector<TYPE, DIM>& rhs)
   //{
   //   return lhs /= rhs;
   //}

   //CVector<TYPE, DIM>& operator/=(const CVector<TYPE, DIM>& rhs)
   //{
   //   for (unsigned int i = 0; i < DIM; ++i)
   //   {
   //      m_data[i] /= rhs[i];
   //   }
   //   return *this;
   //}

   // TODO: Scalar multiplication

   // Assignment operator
   CVector<TYPE, DIM>& operator=(const CVector<TYPE, DIM>& other)
   {
      for (unsigned int i = 0; i < DIM; ++i)
      {
         m_data[i] = other[i];
      }
      return *this;
   }

   // Comparison operators
   // TODO: Implement ==
   // TODO: Implement !=

   // Mathematical Validation functions
   // TODO: Implement Parallel check - opposite direction but not necessarily the same magnitude
   // TODO: Implement AntiParallel check - same direction but not necessarily the same magnitude
   // TODO: Implement Opposite check - same magnitude but opposite direction

   // Mathematical vector operations
   TYPE NormSquared()
   {
      // The euclidean norm squared - the sum of the squares of all the vector elements
      TYPE result = static_cast<TYPE>(0);
      for (auto& data : m_data)
      {
         result += data*data;
      }
      return result;
   }

   TYPE Norm()
   {
      // Also known as length or magnitude
      // The euclidean norm - defined as the square root of sum of the squares of all the vector elements
      // Physically this is the length of the vector
      return std::sqrt(NormSquared());
   }

   void Normalise()
   {
      auto magnitude = Norm();
      for (auto i=0; i<DIM; ++i)
      {
         m_data[i] /= magnitude;
      }
   }

   // Dot/Scalar Product a . b
   friend TYPE DotProduct(const CVector<TYPE, DIM>& lhs, const CVector<TYPE, DIM>& rhs)
   {
      if (!lhs.IsEqualLength(rhs))
      {
         throw XVectorDimensionMismatch(lhs.Size(), rhs.Size());
      }

      TYPE result = static_cast<TYPE>(0);
      for (int i = 0; i < lhs.Size(); ++i)
      {
         result += lhs[i] * rhs[i];
      }
      return result;
   }

   // Angle between two vectors (using dot product) - radians
   friend TYPE AngleBetween(const CVector<TYPE, DIM>& lhs, const CVector<TYPE, DIM>& rhs)
   {
      // Validates size in DotProduct
      return acos(DotProduct(lhs, rhs) / (lhs.Norm() * rhs.Norm()));
   }

   // TODO: Cross/Vector Product (2&3 dims only)
   // TODO: Scalar triple product - a dot(b x c) (2&3 dims only)

private:
   std::array<TYPE, DIM> m_data;

};

typedef CVector<double, 2> CVector2;
typedef CVector<double, 3> CVector3;
typedef CVector<double, 4> CVector4;

#endif // __VECTOR_H__
