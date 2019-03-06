#pragma once

#include <quda.h>
#include <quda_internal.h>
#include <dirac_quda.h>
#include <color_spinor_field.h>

namespace quda {

  class EigenSolver {
    
  protected:
    QudaEigParam *eig_param;
    TimeProfile profile;
    
  public:
    EigenSolver(QudaEigParam *eig_param, TimeProfile &profile);
    virtual ~EigenSolver();
    
    virtual void operator()(std::vector<ColorSpinorField*> &kSpace,
			    std::vector<Complex> &evals) = 0;
    
    /**
       EiegnSolver factory
    */
    static EigenSolver* create(QudaEigParam *eig_param, const Dirac &mat, TimeProfile &profile);
    
    /**
       @brief Applies the specified matVec operation:
       M, Mdag, MMdag, MdagM
       @param[in] mat Matrix operator
       @param[in] out Output spinor
       @param[in] in Input spinor
       @param[in] eig_param Eigensolver parameters
    */
    void matVec(const Dirac &mat,
		ColorSpinorField &out,
		const ColorSpinorField &in,
		QudaEigParam *eig_param);
    
    /**
       @brief Promoted the specified matVec operation:
       M, Mdag, MMdag, MdagM to a Chebyshev polynomial
       @param[in] mat Matrix operator
       @param[in] out Output spinor
       @param[in] in Input spinor
       @param[in] eig_param Eigensolver parameters
    */
    void chebyOp(const Dirac &mat,
		 ColorSpinorField &out,
		 const ColorSpinorField &in,
		 QudaEigParam *eig_param);

    /**
       @brief Orthogonalise input vector r against
       vector space v
       @param[in] v Vector space
       @param[in] r Vector to be orthogonalised
       @param[in] j Number of vectors in v to orthogonalise against
    */
    void orthogonalise(std::vector<ColorSpinorField*> v,
		       std::vector<ColorSpinorField*> r,
		       int j);

    /**
       @brief Orthogonalise input vector r against
       vector space v using block-BLAS
       @param[in] v Vector space
       @param[in] r Vector to be orthogonalised
       @param[in] j Number of vectors in v to orthogonalise against
    */
    void blockOrthogonalise(std::vector<ColorSpinorField*> v,
			    std::vector<ColorSpinorField*> r,
			    int j);

    /**
       @brief Deflate vector with Eigenvectors
    */
    void deflate(std::vector<ColorSpinorField*> vec_defl,
		 std::vector<ColorSpinorField*> vec,
		 std::vector<ColorSpinorField*> evecs,
		 std::vector<Complex> evals);
    
  };
  
  
  
  /**
     @brief Implicily Restarted Lanczos Method.
  */
  class IRLM : public EigenSolver {

  private:
    const Dirac &mat;
    
  public:
    IRLM(QudaEigParam *eig_param, const Dirac &mat, TimeProfile &profile);
    virtual ~IRLM();

    /**
       @brief Compute eigenpairs
       @param[in] kSpace Krylov vector space
       @param[in] evals Computed eigenvalues
       
    */
    void operator()(std::vector<ColorSpinorField*> &kSpace,
		    std::vector<Complex> &evals);
    
    /**
       @brief Lanczos step: extends the Kylov space.
       @param[in] mat matrix operator
       @param[in] v Vector space
       @param[in] r Current vector to add
       @param[in] evecs List of eigenvectors
       @param[in] locked List of converged eigenvectors
       @param[in] eig_param Eigensolver parameters
       @param[in] alpha Diagonal of tridiagonal
       @param[in] beta Subdiagonal of tridiagonal
       @param[in] j Index of last vector added       
    */
    void lanczosStep(const Dirac &mat,
		     std::vector<ColorSpinorField*> v,
		     std::vector<ColorSpinorField*> r,
		     std::vector<ColorSpinorField*> evecs,
		     bool *locked,
		     QudaEigParam *eig_param,
		     double *alpha, double *beta, int j);

    /**
       @brief Computes Left/Right SVD from pre computed Right/Left 
       @param[in] mat matrix operator
       @param[in] v Vector space
       @param[in] r Current vector to add
       @param[in] kSpace
       @param[in] evecs Computed eigenvectors of NormOp
       @param[in] evals Computed eigenvalues of NormOp
       @param[in] eig_param Eigensolver parameters
       @param[in] inverse Inverse sort if using PolyAcc       
    */
    void computeSVD(const Dirac &mat,
		    std::vector<ColorSpinorField*> &kSpace,
		    std::vector<ColorSpinorField*> &evecs,
		    std::vector<Complex> &evals,
		    QudaEigParam *eig_param,
		    bool inverse);
    
  };

  class DeflationEigenSolver : public EigenSolver {
    
  private:
    EigenSolver *eig_solver;
    const Dirac &dirac;
    const char *prefix;

  public:
  DeflationEigenSolver(EigenSolver &eig_solver, const Dirac &dirac, QudaEigParam &eig_param, TimeProfile &profile, const char *prefix)
    : EigenSolver(&eig_param, profile), eig_solver(&eig_solver), dirac(dirac), prefix(prefix) { }
    virtual ~DeflationEigenSolver() { delete eig_solver; }

    void operator()(std::vector<ColorSpinorField*> &evecs,
		    std::vector<Complex> evals) {

      setOutputPrefix(prefix);

      //ColorSpinorField *out=nullptr;
      //ColorSpinorField *in=nullptr;

      (*eig_solver)(evecs, evals);

      setOutputPrefix("");
      
    }
  };


  
  void irlmSolve(std::vector<ColorSpinorField*> kSpace,
		 std::vector<Complex> &evals, const Dirac &mat,
		 QudaEigParam *eig_param);

  void iramSolve(std::vector<ColorSpinorField*> kSpace,
		 std::vector<Complex> &evals, const Dirac &mat,
		 QudaEigParam *eig_param);
  
  void arpack_solve(void *h_evecs, void *h_evals,
		    const Dirac &mat,
		    QudaEigParam *eig_param,
		    ColorSpinorParam *cpuParam);
  
}