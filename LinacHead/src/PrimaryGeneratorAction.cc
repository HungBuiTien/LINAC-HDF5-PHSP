#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "Randomize.hh"
#include "Randomize.hh"
#include "Randomize.hh"
#include "G4Threading.hh"
#include "H5Cpp.h"
#include "G4GeneralParticleSource.hh"
#ifdef G4MULTITHREADED
    #include "G4MTRunManager.hh"
#else
    #include "G4RunManager.hh"
#endif

namespace 
{
    G4Mutex PrimaryGeneratorAction_Mutex = G4MUTEX_INITIALIZER ; 
}

PrimaryGeneratorAction::PrimaryGeneratorAction()
:particleGun(0)
{
    G4AutoLock _m(&PrimaryGeneratorAction_Mutex);
    gen = new G4GeneralParticleSource;
    //
    _m.unlock();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{   
    particleGun->GeneratePrimaryVertex(anEvent);
}

