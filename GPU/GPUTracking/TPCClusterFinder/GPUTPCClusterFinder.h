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

/// \file GPUTPCClusterFinder.h
/// \author David Rohr

#ifndef O2_GPU_GPUTPCCLUSTERFINDER_H
#define O2_GPU_GPUTPCCLUSTERFINDER_H

#include "GPUDef.h"
#include "GPUProcessor.h"
#include "GPUDataTypes.h"
#include "Digit.h"

namespace GPUCA_NAMESPACE
{

class MCCompLabel;
namespace dataformats
{
template <typename TruthElement>
class MCTruthContainer;
} // namespace dataformats

namespace tpc
{
struct ClusterNative;
}

namespace gpu
{
struct GPUTPCClusterMCInterim;

struct ChargePos;

class GPUTPCClusterFinder : public GPUProcessor
{
 public:
  struct Memory {
    struct counters_t {
      size_t nDigits = 0;
      size_t nPeaks = 0;
      size_t nClusters = 0;
      unsigned int nPages = 0;
    } counters;
  };

  struct ZSOffset {
    unsigned int offset;
    unsigned short endpoint;
    unsigned short num;
  };

#ifndef GPUCA_GPUCODE
  ~GPUTPCClusterFinder();
  void InitializeProcessor();
  void RegisterMemoryAllocation();
  void SetMaxData(const GPUTrackingInOutPointers& io);

  void* SetPointersInput(void* mem);
  void* SetPointersOutput(void* mem);
  void* SetPointersScratch(void* mem);
  void* SetPointersMemory(void* mem);
  void* SetPointersZSOffset(void* mem);

  size_t getNSteps(size_t items) const;
  void SetNMaxDigits(size_t nDigits, size_t nPages);

  void PrepareMC();
  void clearMCMemory();
#endif
  unsigned char* mPzs = nullptr;
  ZSOffset* mPzsOffsets = nullptr;
  deprecated::Digit* mPdigits = nullptr; // input digits, only set if ZS is skipped
  ChargePos* mPpositions = nullptr;
  ChargePos* mPpeakPositions = nullptr;
  ChargePos* mPfilteredPeakPositions = nullptr;
  unsigned char* mPisPeak = nullptr;
  ushort* mPchargeMap = nullptr;
  unsigned char* mPpeakMap = nullptr;
  uint* mPindexMap = nullptr;
  uint* mPclusterInRow = nullptr;
  tpc::ClusterNative* mPclusterByRow = nullptr;
  GPUTPCClusterMCInterim* mPlabelsByRow = nullptr;
  int* mPbuf = nullptr;
  Memory* mPmemory = nullptr;

  o2::dataformats::MCTruthContainer<o2::MCCompLabel> const* mPinputLabels = nullptr;
  uint* mPlabelHeaderOffset = nullptr;
  uint* mPlabelDataOffset = nullptr;

  int mISlice = 0;
  constexpr static int mScanWorkGroupSize = GPUCA_THREAD_COUNT_SCAN;
  size_t mNMaxClusterPerRow = 0;
  size_t mNMaxPages = 0;
  size_t mNMaxDigits = 0;
  size_t mNMaxPeaks = 0;
  size_t mNMaxClusters = 0;
  size_t mBufSize = 0;
  size_t mNBufs = 0;

  unsigned short mMemoryId = 0;
  unsigned short mZSOffsetId = 0;

#ifndef GPUCA_GPUCODE
  void DumpDigits(std::ostream& out);
  void DumpChargeMap(std::ostream& out, std::string_view);
  void DumpPeaks(std::ostream& out);
  void DumpPeaksCompacted(std::ostream& out);
  void DumpSuppressedPeaks(std::ostream& out);
  void DumpSuppressedPeaksCompacted(std::ostream& out);
  void DumpCountedPeaks(std::ostream& out);
  void DumpClusters(std::ostream& out);
#endif
};

} // namespace gpu
} // namespace GPUCA_NAMESPACE

#endif