#ifndef PhysicsList_h
#define PhysicsList_h 1
#include "G4VModularPhysicsList.hh"
#include "G4EmConfigurator.hh"
#include "globals.hh"
#include "G4Threading.hh"
class G4VPhysicsConstructor;
class PhysicsListMessenger;
class BREMSPEProcess;
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
class PhysicsList: public G4VUserPhysicsList
{
public:
  PhysicsList();
  virtual ~PhysicsList();
  void ConstructParticle();
  void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);
  void ConstructProcess();
  void AddStepMax();
  void SetBremspe_Nsplit(G4int);
  void SetBremspe_Enabled(bool);
  void ConstructEM();
  G4EmConfigurator em_config;
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4bool radioactiveDecayIsRegisted;
  G4String                             emName;
  G4VPhysicsConstructor*               emPhysicsList;
  G4VPhysicsConstructor*               decPhysicsList;
  G4VPhysicsConstructor*               HadronElasticPhysicsList;
  G4VPhysicsConstructor*               HadronInelasticPhysicsList;
  G4VPhysicsConstructor*               IonBinaryCascadePhysicsList;
  PhysicsListMessenger* pMessenger;
  G4int fNSplit;
  bool fSplittingActive;
  BREMSPEProcess*BREMSPE;
};

#endif
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
