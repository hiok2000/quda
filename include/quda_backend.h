#pragma once

// TBD: API calls

// curand_normal
// curand_normal_double
// curand_uniform
// curand_uniform_double

// cuMemAlloc
// cuMemFree

// cudaFree
// cudaFreeHost

// cudaCreateTextureObject
// cudaDestroyTextureObject
// cudaDeviceCanAccessPeer
// cudaDeviceGetStreamPriorityRange
// cudaDeviceReset
// cudaDeviceSetCacheConfig
// cudaDeviceSynchronize
// cudaDriverGetVersion

// cudaEventCreate
// cudaEventDestroy
// cudaEventElapsedTime
// cudaEventRecord
// cudaEventSynchronize

// cufftExecC2C
// cufftExecZ2Z
// cufftPlanMany
 
// cudaGetTextureObjectResourceDesc
// cudaGetDeviceCount 
// cudaGetDeviceProperties
// cudaGetErrorString
// cudaGetLastError

// cudaHostGetDevicePointer

// cudaHostAlloc
// cudaHostRegister
// cudaHostRegisterDefault
// cudaHostRegisterMapped
// cudaHostRegisterPortable
// cudaHostUnregister

// cudaIpcCloseMemHandle
// cudaIpcGetEventHandle
// cudaIpcGetMemHandle
// cudaIpcOpenEventHandle
// cudaIpcOpenMemHandle

// cudaProfilerStart
// cudaProfilerStop

// cudaRuntimeGetVersion
// cudaSetDevice

// cudaStreamCreateWithPriority
// cudaStreamDestroy


#ifdef CUDA_BACKEND
#include <cuda.h>
#include <cuda_runtime.h>

#define QUDA_SUCCESS CUDA_SUCCESS
#define QUDA_MEMORYTYPE_ARRAY CU_MEMORYTYPE_ARRAY
#define QUDA_MEMORYTYPE_DEVICE CU_MEMORYTYPE_DEVICE
#define QUDA_MEMORYTYPE_UNIFIED CU_MEMORYTYPE_UNIFIED
#define QUDA_MEMORYTYPE_HOST CU_MEMORYTYPE_HOST
#define QUDAFFT_C2C CUFFT_C2C
#define qudaChannelFormatDesc cudaChannelFormatDesc
#define qudaChannelFormatKindFloat cudaChannelFormatKindFloat
#define qudaChannelFormatKindSigned cudaChannelFormatKindSigned
#define qudaEventDisableTiming cudaEventDisableTiming
#define qudaEventInterprocess cudaEventInterprocess
#define qudaFuncCachePreferL1 cudaFuncCachePreferL1
#define qudafftComplex cufftComplex
#define qudafftDoubleComplex cufftDoubleComplex
#define qudafftHandle cufftHandle
#define qudafftResult cufftResult
#define qudaIpcEventHandle_t cudaIpcEventHandle_t
#define qudaIpcMemHandle_t cudaIpcMemHandle_t
#define qudaIpcMemLazyEnablePeerAccess cudaIpcMemLazyEnablePeerAccess
#define qudaTextureDesc cudaTextureDesc
#define qudaTextureObject_t cudaTextureObject_t
#define qudaReadModeElementType cudaReadModeElementType
#define qudaReadModeNormalizedFloat cudaReadModeNormalizedFloat
#define qudaResourceDesc cudaResourceDesc
#define qudaResourceTypeLinear cudaResourceTypeLinear
#define qudaStreamDefault cudaStreamDefault
#define qudaStream_t cudaStream_t
#define qudaSuccess cudaSuccess
#define qudaEvent_t cudaEvent_t
#define qudaError_t cudaError_t
#define qudaDeviceptr_t CUdeviceptr
#define qudaMemoryType CUmemorytype
#define qudaCUresult CUresult
#define qudaMemcpyKind cudaMemcpyKind
#define qudaMemcpyDeviceToHost cudaMemcpyDeviceToHost
#define qudaMemcpyHostToDevice cudaMemcpyHostToDevice
#define qudaMemcpyDeviceToDevice cudaMemcpyDeviceToDevice
#define qudaFuncAttribute cudaFuncAttribute
#define qudaDeviceProp cudaDeviceProp
#define qudaWarpSize warpSize

#endif

#ifdef HIP_BACKEND
#include <hip/hip_runtime.h>
#include <hip/hip_profiler_api.h

#define QUDA_SUCCESS hipSuccess
#define QUDA_MEMORYTYPE_ARRAY hipMemoryTypeArray
#define QUDA_MEMORYTYPE_DEVICE hipMemoryTypeDevice
#define QUDA_MEMORYTYPE_UNIFIED hipMemoryTypeUnified
#define QUDA_MEMORYTYPE_HOST hipMemoryTypeHost
#define QUDAFFT_C2C HIPFFT_C2C
#define qudaChannelFormatDesc hipChannelFormatDesc
#define qudaChannelFormatKindFloat hipChannelFormatKindFloat
#define qudaChannelFormatKindSigned hipChannelFormatKindSigned

#define qudaEventDisableTiming hipEventDisableTiming
#define qudaEventInterprocess hipEventInterprocess

#define qudaFuncCachePreferL1 hipFuncCachePreferL1
#define qudafftComplex hipfftComplex
#define qudafftDoubleComplex hipfftDoubleComplex
#define qudafftHandle hipfftHandle
#define qudafftResult hipfftResult

#define qudaIpcEventHandle_t hipIpcEventHandle_t
#define qudaIpcMemHandle_t hipIpcMemHandle_t
#define qudaIpcMemLazyEnablePeerAccess hipIpcMemLazyEnablePeerAccess

#define qudaReadModeElementType hipReadModeElementType
#define qudaReadModeNormalizedFloat hipReadModeNormalizedFloat

#define qudaResourceDesc hipResourceDesc
#define qudaResourceTypeLinear hipResourceTypeLinear

#define qudaStreamDefault hipStreamDefault

#define qudaStream_t hipStream_t
#define qudaSuccess hipSuccess
#define qudaEvent_t hipEvent_t
#define qudaError_t hipError_t
#define qudaTextureObject_t hipTextureObject_t
#define qudaDeviceptr_t hipDeviceptr_t
#define qudaMemoryType hipMemoryType
#define qudaCUresult  hipError_t

#define qudaMemcpyKind hipMemcpyKind
#define qudaMemcpyDeviceToHost hipMemcpyDeviceToHost
#define qudaMemcpyHostToDevice hipMemcpyHostToDevice
#define qudaMemcpyDeviceToDevice hipMemcpyDeviceToDevice

#define qudaFuncAttribute hipFuncAttribute
#define qudaDeviceProp hipDeviceProp
#define qudaTextureDesc hipTextureDesc
#define qudaWarpSize hipWarpSize


#endif