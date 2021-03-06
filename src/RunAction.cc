//
// $Id$
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "G4Run.hh"
#include "G4GenericMessenger.hh"
#include "Randomize.hh"
#include "g4root.hh"
#include <iostream>
#include <ios>
#include "G4ios.hh"



RunAction::RunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  analysisManager->SetFileName("OutPut"); //default filename, can be changed by macro command

  analysisManager->CreateH1("Edep","Edep",3*8200,0.,8.2); // 1 keV binning
}


RunAction::~RunAction()
{

}


void RunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
