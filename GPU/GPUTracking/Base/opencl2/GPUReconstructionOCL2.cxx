//**************************************************************************\
//* This file is property of and copyright by the ALICE Project            *\
//* ALICE Experiment at CERN, All rights reserved.                         *\
//*                                                                        *\
//* Primary Authors: Matthias Richter <Matthias.Richter@ift.uib.no>        *\
//*                  for The ALICE HLT Project.                            *\
//*                                                                        *\
//* Permission to use, copy, modify and distribute this software and its   *\
//* documentation strictly for non-commercial purposes is hereby granted   *\
//* without fee, provided that the above copyright notice appears in all   *\
//* copies and that both the copyright notice and this permission notice   *\
//* appear in the supporting documentation. The authors make no claims     *\
//* about the suitability of this software for any purpose. It is          *\
//* provided "as is" without express or implied warranty.                  *\
//**************************************************************************

/// \file GPUReconstructionOCL2.cxx
/// \author David Rohr

#define GPUCA_GPUTYPE_RADEON
#define __OPENCL_HOST__

#include "GPUReconstructionOCL2.h"
#include "GPUReconstructionOCL2Internals.h"
#include "GPUReconstructionIncludes.h"

using namespace GPUCA_NAMESPACE::gpu;

#include <cstring>
#include <unistd.h>
#include <typeinfo>
#include <cstdlib>

#ifdef OPENCL2_ENABLED_AMD
extern "C" char _makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_amd[];
extern "C" unsigned int _makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_amd_size;
#endif
#ifdef OPENCL2_ENABLED_SPIRV
extern "C" char _makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_spirv[];
extern "C" unsigned int _makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_spirv_size;
#endif
extern "C" char _makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_src[];
extern "C" unsigned int _makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_src_size;

GPUReconstruction* GPUReconstruction_Create_OCL2(const GPUSettingsProcessing& cfg) { return new GPUReconstructionOCL2(cfg); }

GPUReconstructionOCL2Backend::GPUReconstructionOCL2Backend(const GPUSettingsProcessing& cfg) : GPUReconstructionOCL(cfg)
{
}

template <class T, int I, typename... Args>
int GPUReconstructionOCL2Backend::runKernelBackend(krnlSetup& _xyz, const Args&... args)
{
  cl_kernel k = _xyz.y.num > 1 ? getKernelObject<cl_kernel, T, I, true>() : getKernelObject<cl_kernel, T, I, false>();
  return runKernelBackendCommon(_xyz, k, args...);
}

template <class S, class T, int I, bool MULTI>
S& GPUReconstructionOCL2Backend::getKernelObject()
{
  static unsigned int krnl = FindKernel<T, I>(MULTI ? 2 : 1);
  return mInternals->kernels[krnl].first;
}

int GPUReconstructionOCL2Backend::GetOCLPrograms()
{
  char platform_version[64] = {}, platform_vendor[64] = {};
  clGetPlatformInfo(mInternals->platform, CL_PLATFORM_VERSION, sizeof(platform_version), platform_version, nullptr);
  clGetPlatformInfo(mInternals->platform, CL_PLATFORM_VENDOR, sizeof(platform_vendor), platform_vendor, nullptr);
  float ver = 0;
  sscanf(platform_version, "OpenCL %f", &ver);

  cl_int return_status[1] = {CL_SUCCESS};
  cl_int ocl_error;
#ifdef OPENCL2_ENABLED_AMD
  if (strcmp(platform_vendor, "Advanced Micro Devices, Inc.") == 0) {
    size_t program_sizes[1] = {_makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_amd_size};
    char* program_binaries[1] = {_makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_amd};
    mInternals->program = clCreateProgramWithBinary(mInternals->context, 1, &mInternals->device, program_sizes, (const unsigned char**)program_binaries, return_status, &ocl_error);
  } else
#endif

#ifdef OPENCL2_ENABLED_SPIRV // clang-format off
  if (ver >= 2.2) {
    mInternals->program = clCreateProgramWithIL(mInternals->context, _makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_spirv, _makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_spirv_size, &ocl_error);
  } else
#endif // clang-format on

  {
    size_t program_sizes[1] = {_makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_src_size};
    char* programs_sources[1] = {_makefile_opencl_program_Base_opencl_GPUReconstructionOCL2_cl_src};
    mInternals->program = clCreateProgramWithSource(mInternals->context, (cl_uint)1, (const char**)&programs_sources, program_sizes, &ocl_error);
  }

  if (GPUFailedMsgI(ocl_error)) {
    GPUError("Error creating OpenCL program from binary");
    return 1;
  }
  if (GPUFailedMsgI(return_status[0])) {
    GPUError("Error creating OpenCL program from binary (device status)");
    return 1;
  }

  if (GPUFailedMsgI(clBuildProgram(mInternals->program, 1, &mInternals->device, GPUCA_M_STR(OCL_FLAGS), nullptr, nullptr))) {
    cl_build_status status;
    if (GPUFailedMsgI(clGetProgramBuildInfo(mInternals->program, mInternals->device, CL_PROGRAM_BUILD_STATUS, sizeof(status), &status, nullptr)) == 0 && status == CL_BUILD_ERROR) {
      size_t log_size;
      clGetProgramBuildInfo(mInternals->program, mInternals->device, CL_PROGRAM_BUILD_LOG, 0, nullptr, &log_size);
      std::unique_ptr<char[]> build_log(new char[log_size + 1]);
      clGetProgramBuildInfo(mInternals->program, mInternals->device, CL_PROGRAM_BUILD_LOG, log_size, build_log.get(), nullptr);
      build_log[log_size] = 0;
      GPUError("Build Log:\n\n%s\n", build_log.get());
    }
    return 1;
  }
  return 0;
}

bool GPUReconstructionOCL2Backend::CheckPlatform(unsigned int i)
{
  char platform_version[64] = {}, platform_vendor[64] = {};
  clGetPlatformInfo(mInternals->platforms[i], CL_PLATFORM_VERSION, sizeof(platform_version), platform_version, nullptr);
  clGetPlatformInfo(mInternals->platforms[i], CL_PLATFORM_VENDOR, sizeof(platform_vendor), platform_vendor, nullptr);
  float ver1 = 0;
  sscanf(platform_version, "OpenCL %f", &ver1);
  if (ver1 >= 2.2f) {
    if (mDeviceProcessingSettings.debugLevel >= 2) {
      GPUInfo("OpenCL 2.2 capable platform found");
    }
    return true;
  }

  if (strcmp(platform_vendor, "Advanced Micro Devices, Inc.") == 0 && ver1 >= 2.0f) {
    float ver2 = 0;
    const char* pos = strchr(platform_version, '(');
    if (pos) {
      sscanf(pos, "(%f)", &ver2);
    }
    if ((ver1 >= 2.f && ver2 >= 2000.f) || ver1 >= 2.1f) {
      if (mDeviceProcessingSettings.debugLevel >= 2) {
        GPUInfo("AMD ROCm OpenCL Platform found");
      }
      return true;
    }
  }
  return false;
}
