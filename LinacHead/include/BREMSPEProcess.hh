#ifndef BREMSPEPROCESS_HH
#define BREMSPEPROCESS_HH 1
#include "G4WrapperProcess.hh"

class BREMSPEProcess : public G4WrapperProcess {
  public:
  BREMSPEProcess();	
  virtual ~BREMSPEProcess();	
  G4VParticleChange* PostStepDoIt(const G4Track& track, const G4Step& step);
  void SetNSplit(G4int);
  void SetIsActive(G4bool);
  G4bool GetIsActive();
  G4int GetNSplit();
  G4int GetNSecondaries();
};
#endif
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
