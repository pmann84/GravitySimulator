#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <array>

// TODO: Add specialisations for 2/3 dimensions - as vector product and triple product don't apply for higher dimensional vectors

template<class TYPE, unsigned int DIM>
class CVector
{
public:

   // Constructors & Destructors
   CVector() : m_data(std::array<TYPE, DIM>{0}) {};
   CVector(std::initializer_list<TYPE> data)
   {
      if (data.size() > DIM)
      {
         throw;
      }
      std::copy(data.begin(), data.end(), m_data.begin());
   }

   ~CVector() {};

   // Random Access Operators
   TYPE& operator[] (unsigned int n)
   {
      return m_data[n];
   }

   const TYPE& operator[] (unsigned int n) const
   {
      return m_data[n];
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
   friend CVector<TYPE, DIM> operator*(CVector lhs, const float& rhs)
   {
      return lhs *= rhs;
   }

   CVector<TYPE, DIM>& operator*=(const float& rhs)
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

   // Assignment operators
   // TODO: Implement =

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

   // TODO: Dot Product
   // TODO: Cross Product
   // TODO: Scalar triple product - a dot (b x c)

private:
   std::array<TYPE, DIM> m_data;

};

typedef CVector<double, 2> CVector2;

#endif // __VECTOR_H__
