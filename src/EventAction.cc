//    **********************************
//    *                                *
//    *        EventAction.cc          *
//    *                                *
//    **********************************
#include "EventAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4UImanager.hh"
#include "G4StepPoint.hh"
#include "G4Step.hh"
#include "G4ios.hh"
#include <iostream> 
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SDManager.hh"
#include "G4THitsMap.hh"
#include "g4root.hh"

#include "RandGauss.h"


EventAction::EventAction()
{
  hitsCollectionID = -1;
}
 
EventAction::~EventAction()
{

    
}
 
void EventAction::BeginOfEventAction(const G4Event* evt)
{ 
  /*evtNo = evt -> GetEventID(); 
  G4int printModul = 5000;
  if (evtNo%printModul == 0 && evtNo>0) 
  {
    G4cout << "\n---> Processing Of Event: " << evtNo << G4endl;
  }*/
}

void EventAction::EndOfEventAction(const G4Event* evt)
{  
    
// IMPLEMENT WHAT TO DO AT THE END OF AN EVENT
  if(hitsCollectionID==-1) {
    G4SDManager* fSDM = G4SDManager::GetSDMpointer();
    hitsCollectionID = fSDM->GetCollectionID("theDetector/eDep");
    //fSDM->ListTree();
  }

  G4HCofThisEvent* HCofEvent = evt->GetHCofThisEvent();

  G4THitsMap<G4double>* evtMap = static_cast<G4THitsMap<G4double>*>(HCofEvent->GetHC(hitsCollectionID));

  G4double total_edep = 0.;
  std::map<G4int,G4double*>::iterator itr;
  for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) {
    G4double edep = *(itr->second);
    total_edep += edep;
    ///G4int copyNb = (itr->first);
    //G4cout << "edep = " << edep << G4endl;
  }
  //G4cout << "total_edep = " << total_edep << G4endl;
  if(!total_edep) total_edep = -1.*MeV; // set it negative to not be included in the first bin, but in the underflow bin 


  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(0,total_edep);
}

