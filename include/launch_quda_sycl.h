#pragma once
#include "quda_internal.h"

namespace quda {

  /**
     @brief Wrapper around cudaLaunchKernel
     @param[in] func Device function symbol
     @param[in] gridDim Grid dimensions
     @param[in] blockDim Block dimensions
     @param[in] args Arguments
     @param[in] sharedMem Shared memory requested per thread block
     @param[in] stream Stream identifier
  */
  qudaError_t qudaLaunchKernel(const void *func, dim3 gridDim0, dim3 blockDim0,
			       void **args, size_t sharedMem,
                               qudaStream_t stream);

#if 0
  /**
     @brief Wrapper around cudaLaunchKernel
     @param[in] func Device function symbol
     @param[in] gridDim Grid dimensions
     @param[in] blockDim Block dimensions
     @param[in] sharedMem Shared memory requested per thread block
     @param[in] stream Stream identifier
     @param[in] args Arguments
  */
  template <typename... Args>
  qudaError_t qudaLaunchX(dim3 gridDim, dim3 blockDim, size_t sharedMem,
			  qudaStream_t stream, const void *func, const Args&...args)
  {
    constexpr int size = sizeof...(Args);
    void *arga[size]{const_cast<void *>(static_cast<const void *>(&args))...};
    cudaError_t err;
    err = qudaLaunchKernel(func, gridDim, blockDim, arga, sharedMem, stream);
    return err;
  }

  qudaError_t qudaLaunch_(dim3 gridDim, dim3 blockDim, size_t sharedMem,
			  qudaStream_t stream, const void *func, void **args)
  {
    cudaError_t err;
    err = qudaLaunchKernel(func, gridDim, blockDim, args, sharedMem, stream);
    return err;
  }
#endif

#if 0
  qudaError_t qudaLaunch_(dim3 gridDim0, dim3 blockDim0, size_t sharedMem0,
			  qudaStream_t stream0, const char *func,
			  const char *file, const char *line,
			  std::function<void()> f);

  inline qudaError_t
  qudaLaunch_(TuneParam tp, qudaStream_t stream, const char *func,
	      const char *file, const char *line, std::function<void()> f)
  {
    return qudaLaunch_(tp.grid, tp.block, tp.shared_bytes, stream, func,
  		       file, line, f);
  }

  inline qudaError_t
  qudaLaunch_(TuneParam tp, const char *func,
	      const char *file, const char *line, std::function<void()> f)
  {
    qudaStream_t stream = 0;
    return qudaLaunch_(tp.grid, tp.block, tp.shared_bytes, stream, func,
  		       file, line, f);
  }

  inline qudaError_t
  qudaLaunch_(dim3 gridDim0, dim3 blockDim0, const char *func,
	      const char *file, const char *line, std::function<void()> f)
  {
    qudaStream_t stream = 0;
    int shared = 0;
    return qudaLaunch_(gridDim0, blockDim0, shared, stream, func,
  		       file, line, f);
  }
#endif

#if 0
  template <template<typename> typename F, typename A1>
  qudaError_t qudaLaunch(dim3 gridDim, dim3 blockDim, size_t sharedMem,
			 qudaStream_t stream, F<A1> func, A1 arg1)
  {
    //constexpr int size = sizeof...(Args);
    //void *arga[size]{static_cast<void *>(args)...};
    void *arga[1]{arg1};
    cudaError_t err;
    err = qudaLaunchKernel(func, gridDim, blockDim, arga, sharedMem, stream);
    return err;
  }

  template <template<typename,typename> typename F, typename A1, typename A2>
  qudaError_t qudaLaunch(dim3 gridDim, dim3 blockDim, size_t sharedMem,
			  qudaStream_t stream, F<A1,A2> func, A1 arg1, A2 arg2)
  {
    //constexpr int size = sizeof...(Args);
    //void *arga[size]{static_cast<void *>(args)...};
    void *arga[2]{arg1,arg2};
    cudaError_t err;
    err = qudaLaunchKernel(func, gridDim, blockDim, arga, sharedMem, stream);
    return err;
  }
#endif

#if 0
#define qudaLaunch(gridDim, blockDim, sharedMem, stream, func0, ...) \
  ::quda::qudaLaunch_(gridDim, blockDim, sharedMem, stream,  __func__, \
                      quda::file_name(__FILE__), __STRINGIFY__(__LINE__), \
                      [=](){                                            \
                        func0(__VA_ARGS__);                             \
                      })
#endif

#define unwrap(...) __VA_ARGS__

#if 0
#define funcPtr(f,a) \
  (([&](auto... args) -> decltype(auto) {		\
      return (void (*)(decltype(args)...))(f); })a)
#endif
#if 0
#define funcPtr(f,a)					\
  (([&](auto... args) -> void * {		\
      return reinterpret_cast<void *>((void (*)(decltype(args)...))(f)); })a)
//#define toDecltype(a,...) decltype(a)
//#define toDecltype(a,b) decltype(a),decltype(b)
//#define funcPtr(f,a) ((void *)(toDecltype a))(f)
#define qudaLaunch(kernelName_, launchParams_, kernelArgs_) \
 qudaLaunchX(unwrap launchParams_,funcPtr(kernelName_,kernelArgs_),unwrap kernelArgs_)
#endif

#if 0
#define qudaLaunch(kernelName_, launchParams_, kernelArgs_) \
  ::quda::qudaLaunch_(unwrap launchParams_,  __func__,			\
                      quda::file_name(__FILE__), __STRINGIFY__(__LINE__), \
                      [=](){                                            \
                        kernelName_ kernelArgs_;                             \
                      })
#else
#endif


inline sycl::range<3>
getGlobalSize(TuneParam tp)
{
  auto x = tp.grid.x * tp.block.x;
  auto y = tp.grid.y * tp.block.y;
  auto z = tp.grid.z * tp.block.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getGlobalSize(TuneParam tp, qudaStream_t stream)
{
  auto x = tp.grid.x * tp.block.x;
  auto y = tp.grid.y * tp.block.y;
  auto z = tp.grid.z * tp.block.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getGlobalSize(dim3 gridDim0, dim3 blockDim0)
{
  auto x = gridDim0.x * blockDim0.x;
  auto y = gridDim0.y * blockDim0.y;
  auto z = gridDim0.z * blockDim0.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getGlobalSize(dim3 gridDim0, dim3 blockDim0, size_t sharedMem0)
{
  auto x = gridDim0.x * blockDim0.x;
  auto y = gridDim0.y * blockDim0.y;
  auto z = gridDim0.z * blockDim0.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getGlobalSize(dim3 gridDim0, dim3 blockDim0, size_t sharedMem0,
	      qudaStream_t stream0)
{
  auto x = gridDim0.x * blockDim0.x;
  auto y = gridDim0.y * blockDim0.y;
  auto z = gridDim0.z * blockDim0.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getLocalSize(TuneParam tp)
{
  auto x = tp.block.x;
  auto y = tp.block.y;
  auto z = tp.block.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getLocalSize(TuneParam tp, qudaStream_t stream)
{
  auto x = tp.block.x;
  auto y = tp.block.y;
  auto z = tp.block.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getLocalSize(dim3 gridDim0, dim3 blockDim0)
{
  auto x = blockDim0.x;
  auto y = blockDim0.y;
  auto z = blockDim0.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getLocalSize(dim3 gridDim0, dim3 blockDim0, size_t sharedMem0)
{
  auto x = blockDim0.x;
  auto y = blockDim0.y;
  auto z = blockDim0.z;
  return sycl::range<3>{z,y,x};
}

inline sycl::range<3>
getLocalSize(dim3 gridDim0, dim3 blockDim0, size_t sharedMem0,
	     qudaStream_t stream0)
{
  auto x = blockDim0.x;
  auto y = blockDim0.y;
  auto z = blockDim0.z;
  return sycl::range<3>{z,y,x};
}

#define getSizes(lp) (getGlobalSize lp, getLocalSize lp)

#define unwrap(...) __VA_ARGS__

#define qudaLaunch(kernelName_, launchParams_, kernelArgs_)		\
  do { defaultQueue.submit([&] (sycl::handler &h)			\
		      {	h.parallel_for<class test>			\
			  (getSizes(launchParams_),			\
			   [=](sycl::nd_item<3> ndi) {			\
			     kernelName_(unwrap kernelArgs_, ndi);	\
			   });						\
		      }); } while(0)


}