#ifdef __CINT__
 
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
 
#pragma link C++ class AliHBTAnalysis+;
#pragma link C++ class AliHBTParticle+;
#pragma link C++ class AliHBTEvent+;
#pragma link C++ class AliHBTRun+;
#pragma link C++ class AliHBTFunction+;
#pragma link C++ class AliHBTMonitorFunction+;

#pragma link C++ class AliHBTOnePairFctn+;
#pragma link C++ class AliHBTOnePairFctn1D+;
#pragma link C++ class AliHBTOnePairFctn2D+;
#pragma link C++ class AliHBTOnePairFctn3D+;
#pragma link C++ class AliHBTTwoPairFctn+;
#pragma link C++ class AliHBTTwoPairFctn1D+;
#pragma link C++ class AliHBTTwoPairFctn2D+;
#pragma link C++ class AliHBTTwoPairFctn3D+;

#pragma link C++ class AliHBTMonOneParticleFctn+;
#pragma link C++ class AliHBTMonOneParticleFctn1D+;
#pragma link C++ class AliHBTMonOneParticleFctn2D+;
#pragma link C++ class AliHBTMonOneParticleFctn3D+;
#pragma link C++ class AliHBTMonTwoParticleFctn+;
#pragma link C++ class AliHBTMonTwoParticleFctn1D+;
#pragma link C++ class AliHBTMonTwoParticleFctn2D+;
#pragma link C++ class AliHBTMonTwoParticleFctn3D+;

#pragma link C++ class AliHBTPair+;
#pragma link C++ class AliHBTParticleCut-;
#pragma link C++ class AliHBTEmptyParticleCut-;
#pragma link C++ class AliHBTPairCut-;
#pragma link C++ class AliHBTEmptyPairCut-;

#pragma link C++ class AliHbtBaseCut+;
#pragma link C++ class AliHbtBasePairCut+;
#pragma link C++ class AliHBTQInvCut+;
#pragma link C++ class AliHBTKtCut+;
#pragma link C++ class AliHBTQSideCMSLCCut+;
#pragma link C++ class AliHBTQOutCMSLCCut+;
#pragma link C++ class AliHBTQLongCMSLCCut+;

#pragma link C++ class AliHBTMomentumCut+;
#pragma link C++ class AliHBTPtCut+;
#pragma link C++ class AliHBTEnergyCut+;
#pragma link C++ class AliHBTRapidityCut+;
#pragma link C++ class AliHBTPseudoRapidityCut+;
#pragma link C++ class AliHBTPxCut+;
#pragma link C++ class AliHBTPyCut+;
#pragma link C++ class AliHBTPzCut+;
#pragma link C++ class AliHBTPhiCut+;
#pragma link C++ class AliHBTThetaCut+;
#pragma link C++ class AliHBTVxCut+;
#pragma link C++ class AliHBTVyCut+;
#pragma link C++ class AliHBTVzCut+;


#pragma link C++ class AliHBTReader+;
#pragma link C++ class AliHBTReaderTPC+;
#pragma link C++ class AliHBTReaderITSv1+;
#pragma link C++ class AliHBTReaderITSv2+;
#pragma link C++ class AliHBTReaderPPprod+;
#pragma link C++ class AliHBTReaderKineTree+;
#pragma link C++ class AliHBTReaderInternal+;

#pragma link C++ class AliHBTQInvCorrelFctn+;
#pragma link C++ class AliHBTTwoKStarCorrelFctn+;
#pragma link C++ class AliHBTQOutCMSLCCorrelFctn+;
#pragma link C++ class AliHBTQLongCMSLCCorrelFctn+;
#pragma link C++ class AliHBTQSideCMSLCCorrelFctn+;

#pragma link C++ class AliHBTInvMassCorrelFctn+;

#pragma link C++ class AliHBTQInvResolVsQInvFctn+;
#pragma link C++ class AliHBTQOutResolVsQInvFctn+;
#pragma link C++ class AliHBTQSideResolVsQInvFctn+;
#pragma link C++ class AliHBTQLongResolVsQInvFctn+;

#pragma link C++ class AliHBTQInvResolVsKtFctn+;
#pragma link C++ class AliHBTQOutResolVsKtFctn+;
#pragma link C++ class AliHBTQSideResolVsKtFctn+;
#pragma link C++ class AliHBTQLongResolVsKtFctn+;

#pragma link C++ class AliHBTQOutResolVsQOutFctn+;
#pragma link C++ class AliHBTQSideResolVsQSideFctn+;
#pragma link C++ class AliHBTQLongResolVsQLongFctn+;

#pragma link C++ class AliHBTPairThetaResolVsQInvFctn+;
#pragma link C++ class AliHBTPairPhiResolVsQInvFctn+;
#pragma link C++ class AliHBTPairThetaResolVsKtFctn+;
#pragma link C++ class AliHBTPairPhiResolVsKtFctn+;

#pragma link C++ class AliHBTQInvDistributionVsKtFctn+;
#pragma link C++ class AliHBTQOutDistributionVsKtFctn+;
#pragma link C++ class AliHBTQSideDistributionVsKtFctn+;
#pragma link C++ class AliHBTQLongDistributionVsKtFctn+;

#pragma link C++ class AliHBTMonPxDistributionFctn+;
#pragma link C++ class AliHBTMonPyDistributionFctn+;
#pragma link C++ class AliHBTMonPzDistributionFctn+;
#pragma link C++ class AliHBTMonPDistributionFctn+;
#pragma link C++ class AliHBTMonPtDistributionFctn+;
#pragma link C++ class AliHBTMonPhiDistributionFctn+;
#pragma link C++ class AliHBTMonThetaDistributionFctn+;

#pragma link C++ class AliHBTMonPxDistributionVsPtFctn+;
#pragma link C++ class AliHBTMonPyDistributionVsPtFctn+;
#pragma link C++ class AliHBTMonPzDistributionVsPtFctn+;
#pragma link C++ class AliHBTMonPDistributionVsPtFctn+;
#pragma link C++ class AliHBTMonPhiDistributionVsPtFctn+;
#pragma link C++ class AliHBTMonThetaDistributionVsPtFctn+;

#pragma link C++ class AliHBTMonPxResolutionFctn+;
#pragma link C++ class AliHBTMonPyResolutionFctn+;
#pragma link C++ class AliHBTMonPzResolutionFctn+;
#pragma link C++ class AliHBTMonPResolutionFctn+;
#pragma link C++ class AliHBTMonPtResolutionFctn+;
#pragma link C++ class AliHBTMonPhiResolutionFctn+;
#pragma link C++ class AliHBTMonThetaResolutionFctn+;

#pragma link C++ class AliHBTMonPxResolutionVsPtFctn+;
#pragma link C++ class AliHBTMonPyResolutionVsPtFctn+;
#pragma link C++ class AliHBTMonPzResolutionVsPtFctn+;
#pragma link C++ class AliHBTMonPResolutionVsPtFctn+;
#pragma link C++ class AliHBTMonPtResolutionVsPtFctn+;
#pragma link C++ class AliHBTMonPhiResolutionVsPtFctn+;
#pragma link C++ class AliHBTMonThetaResolutionVsPtFctn+;

#pragma link C++ class AliHBTTwoTrackEffFctn+;
#pragma link C++ class AliHBTTwoTrackEffFctn3D+;

#pragma link C++ class AliHBTLLWeights+;
#pragma link C++ class AliHBTLLWeightQInvFctn+;

#endif
