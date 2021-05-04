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

/// \file GPUTRDTrackletWord.h
/// \brief TRD Tracklet word for GPU tracker - 32bit tracklet info + half chamber ID + index

/// \author Ole Schmidt

#ifndef GPUTRDTRACKLETWORD_H
#define GPUTRDTRACKLETWORD_H

#include "GPUDef.h"

#ifndef GPUCA_TPC_GEOMETRY_O2 // compatibility to Run 2 data types

class AliTRDtrackletWord;
class AliTRDtrackletMCM;

namespace GPUCA_NAMESPACE
{
namespace gpu
{

class GPUTRDTrackletWord
{
 public:
  GPUd() GPUTRDTrackletWord(unsigned int trackletWord = 0);
  GPUd() GPUTRDTrackletWord(unsigned int trackletWord, int hcid);
  GPUdDefault() GPUTRDTrackletWord(const GPUTRDTrackletWord& rhs) CON_DEFAULT;
  GPUdDefault() GPUTRDTrackletWord& operator=(const GPUTRDTrackletWord& rhs) CON_DEFAULT;
  GPUdDefault() ~GPUTRDTrackletWord() CON_DEFAULT;
#ifndef GPUCA_GPUCODE_DEVICE
  GPUTRDTrackletWord(const AliTRDtrackletWord& rhs);
  GPUTRDTrackletWord(const AliTRDtrackletMCM& rhs);
  GPUTRDTrackletWord& operator=(const AliTRDtrackletMCM& rhs);
#endif

  // ----- Override operators < and > to enable tracklet sorting by HCId -----
  GPUd() bool operator<(const GPUTRDTrackletWord& t) const { return (GetHCId() < t.GetHCId()); }
  GPUd() bool operator>(const GPUTRDTrackletWord& t) const { return (GetHCId() > t.GetHCId()); }
  GPUd() bool operator<=(const GPUTRDTrackletWord& t) const { return (GetHCId() < t.GetHCId()) || (GetHCId() == t.GetHCId()); }

  // ----- Getters for contents of tracklet word -----
  GPUd() int GetYbin() const;
  GPUd() int GetdYbin() const;
  GPUd() int GetZbin() const { return ((mTrackletWord >> 20) & 0xf); }
  GPUd() int GetPID() const { return ((mTrackletWord >> 24) & 0xff); }

  // ----- Getters for offline corresponding values -----
  GPUd() double GetPID(int /* is */) const { return (double)GetPID() / 256.f; }
  GPUd() int GetDetector() const { return mHCId / 2; }
  GPUd() int GetHCId() const { return mHCId; }
  GPUd() float GetdYdX() const { return (GetdYbin() * 140e-4f / 3.f); }
  GPUd() float GetdY() const { return GetdYbin() * 140e-4f; }
  GPUd() float GetY() const { return (GetYbin() * 160e-4f); }
  GPUd() unsigned int GetTrackletWord() const { return mTrackletWord; }

  GPUd() void SetTrackletWord(unsigned int trackletWord) { mTrackletWord = trackletWord; }
  GPUd() void SetDetector(int id) { mHCId = 2 * id + (GetYbin() < 0 ? 0 : 1); }
  GPUd() void SetHCId(int id) { mHCId = id; }

 protected:
  int mHCId;                  // half-chamber ID
  unsigned int mTrackletWord; // tracklet word: PID | Z | deflection length | Y
                              //          bits:   8   4            7          13
};
} // namespace gpu
} // namespace GPUCA_NAMESPACE

#else // compatibility with Run 3 data types

#include "DataFormatsTRD/Tracklet64.h"

namespace GPUCA_NAMESPACE
{
namespace gpu
{

class GPUTRDTrackletWord : private o2::trd::Tracklet64
{
 public:
  GPUd() GPUTRDTrackletWord(uint64_t trackletWord = 0) : o2::trd::Tracklet64(trackletWord){};
  GPUdDefault() GPUTRDTrackletWord(const GPUTRDTrackletWord& rhs) CON_DEFAULT;
  GPUdDefault() GPUTRDTrackletWord& operator=(const GPUTRDTrackletWord& rhs) CON_DEFAULT;
  GPUdDefault() ~GPUTRDTrackletWord() CON_DEFAULT;

  // ----- Override operators < and > to enable tracklet sorting by HCId -----
  GPUd() bool operator<(const GPUTRDTrackletWord& t) const { return (getHCID() < t.getHCID()); }
  GPUd() bool operator>(const GPUTRDTrackletWord& t) const { return (getHCID() > t.getHCID()); }
  GPUd() bool operator<=(const GPUTRDTrackletWord& t) const { return (getHCID() < t.getHCID()) || (getHCID() == t.getHCID()); }

  GPUd() int GetZbin() const { return getPadRow(); }
  GPUd() float GetY() const { return getUncalibratedY(); }
  GPUd() float GetdY() const { return getUncalibratedDy(); }
  GPUd() int GetDetector() const { return getDetector(); }
  GPUd() int GetHCId() const { return getHCID(); }

  // IMPORTANT: Do not add members, this class must keep the same memory layout as o2::trd::Tracklet64
};

#ifdef GPUCA_NOCOMPAT
static_assert(sizeof(GPUTRDTrackletWord) == sizeof(o2::trd::Tracklet64), "Incorrect memory layout");
#endif

} // namespace gpu
} // namespace GPUCA_NAMESPACE

#endif // GPUCA_TPC_GEOMETRY_O2

#endif // GPUTRDTRACKLETWORD_H
