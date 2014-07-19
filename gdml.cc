#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GDMLParser.hh"

class DummyPhysicsList: public G4VUserPhysicsList
{
  public:
    DummyPhysicsList() {}
    ~DummyPhysicsList() {}

  protected:
    // Construct particle and physics process
    void ConstructParticle() {}
    void ConstructProcess() {}
    void SetCuts() {}
};

class DummyPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
  public:
    DummyPrimaryGeneratorAction() {}
    ~DummyPrimaryGeneratorAction() {}

  public:
    void GeneratePrimaries(G4Event*) {}
};

class GDMLDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    GDMLDetectorConstruction(G4VPhysicalVolume *setWorld = 0)
    {
      World = setWorld;
    }

    G4VPhysicalVolume *Construct()
    {
      return World;
    }

  private:
    G4VPhysicalVolume *World;
};

int main(int argc,char** argv)
{
    G4RunManager* runManager = new G4RunManager();

    G4GDMLParser parser;
    parser.Read("output.gdml",false);
    G4VUserDetectorConstruction* detector = new GDMLDetectorConstruction(parser.GetWorldVolume());

    runManager->SetUserInitialization(detector);

    runManager->SetUserInitialization( new DummyPhysicsList());
    runManager->SetUserAction(new DummyPrimaryGeneratorAction());
    runManager->Initialize();

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    G4UImanager * UImanager = G4UImanager::GetUIpointer();  
    G4UIExecutive * ui = new G4UIExecutive(argc,argv);
    UImanager->ApplyCommand("/control/execute vis.mac");     
    ui->SessionStart();
    
    delete ui;
    delete visManager;
    delete runManager;
    return 0;
}