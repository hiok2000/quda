#include <quda_internal.h>

#pragma once

#define FMULS_GETRF(m_, n_)                                                                                            \
  (((m_) < (n_)) ? (0.5 * (m_) * ((m_) * ((n_) - (1. / 3.) * (m_)-1.) + (n_)) + (2. / 3.) * (m_)) :                    \
                   (0.5 * (n_) * ((n_) * ((m_) - (1. / 3.) * (n_)-1.) + (m_)) + (2. / 3.) * (n_)))
#define FADDS_GETRF(m_, n_)                                                                                            \
  (((m_) < (n_)) ? (0.5 * (m_) * ((m_) * ((n_) - (1. / 3.) * (m_)) - (n_)) + (1. / 6.) * (m_)) :                       \
                   (0.5 * (n_) * ((n_) * ((m_) - (1. / 3.) * (n_)) - (m_)) + (1. / 6.) * (n_)))

#define FLOPS_ZGETRF(m_, n_)                                                                                           \
  (6. * FMULS_GETRF((double)(m_), (double)(n_)) + 2.0 * FADDS_GETRF((double)(m_), (double)(n_)))
#define FLOPS_CGETRF(m_, n_)                                                                                           \
  (6. * FMULS_GETRF((double)(m_), (double)(n_)) + 2.0 * FADDS_GETRF((double)(m_), (double)(n_)))

#define FMULS_GETRI(n_) ((n_) * ((5. / 6.) + (n_) * ((2. / 3.) * (n_) + 0.5)))
#define FADDS_GETRI(n_) ((n_) * ((5. / 6.) + (n_) * ((2. / 3.) * (n_)-1.5)))

#define FLOPS_ZGETRI(n_) (6. * FMULS_GETRI((double)(n_)) + 2.0 * FADDS_GETRI((double)(n_)))
#define FLOPS_CGETRI(n_) (6. * FMULS_GETRI((double)(n_)) + 2.0 * FADDS_GETRI((double)(n_)))

namespace quda
{

  namespace blas_lapack
  {

    bool use_native();
    void set_native(bool native);

    /**
       The native namespace is where we can deploy target specific
       blas/lapack operations, using vendor-specific libraries.  In
       the case of CUDA, this corresponds to the use of cuBLAS.
     */
    namespace native
    {

      /**
         @brief Create the BLAS context
      */
      void init();

      /**
         @brief Destroy the BLAS context
      */
      void destroy();

      /**
         Batch inversion the matrix field using an LU decomposition method.
         @param[out] Ainv Matrix field containing the inverse matrices
         @param[in] A Matrix field containing the input matrices
         @param[in] n Dimension each matrix
         @param[in] batch Problem batch size
         @param[in] precision Precision of the input/output data
         @param[in] Location of the input/output data
         @return Number of flops done in this computation
      */
      long long BatchInvertMatrix(void *Ainv, void *A, const int n, const uint64_t batch, QudaPrecision precision,
                                  QudaFieldLocation location);

    } // namespace native

    /**
       The generic namespace is where we can deploy any
       target-independent blas/lapack operations that are not supported
       on the native target.  To this end, we use Eigen on the host.
     */
    namespace generic
    {

      /**
         @brief Create the BLAS context
      */
      void init();

      /**
         @brief Destroy the BLAS context
      */
      void destroy();

      /**
         Batch inversion the matrix field using an LU decomposition method.
         @param[out] Ainv Matrix field containing the inverse matrices
         @param[in] A Matrix field containing the input matrices
         @param[in] n Dimension each matrix
         @param[in] batch Problem batch size
         @param[in] precision Precision of the input/output data
         @param[in] Location of the input/output data
         @return Number of flops done in this computation
      */
      long long BatchInvertMatrix(void *Ainv, void *A, const int n, const uint64_t batch, QudaPrecision precision,
                                  QudaFieldLocation location);

    } // namespace generic
  }   // namespace blas_lapack
} // namespace quda
