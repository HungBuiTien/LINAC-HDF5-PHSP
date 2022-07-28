#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4GenericPolycone.hh"
#include"G4Tubs.hh"
#include"G4Cons.hh"
#include"G4Paraboloid.hh"
#include"G4SubtractionSolid.hh"
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4Box;
class DetectorMessenger;
class G4tgrMessenger;
class H5PhaseSpaceWriter;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction();
  G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();

  //
  void SetVerbose(G4int val);
  void SetH5PhaseSpaceZStop(G4double _Zstop);
  void SetH5PhaseSpaceName(G4String _PhaseSpaceName);
  void SetNumberOfEventsPerThread(int);

  //Messengers
  DetectorMessenger * pDetectorMessenger;

  //Strings
  G4String H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;

  //Integers
  int NUMBER_OF_THREADS;
  int NumberOfEventsPerThread;

  //classes
  H5PhaseSpaceWriter  *mSD;

  // Physical Detectors
  G4LogicalVolume* logicWorld;
  G4VPhysicalVolume* physWorld;

  G4bool check_overlap;

  void SetJawAperture(G4int idJaw, G4ThreeVector &centre, G4ThreeVector halfSize, G4RotationMatrix *cRotation);
  void Jaw1X();
	void Jaw2X();
	void Jaw1Y();
	void Jaw2Y();

};
#endif