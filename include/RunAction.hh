//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/include/RunAction.hh
/// \brief Definition of the B1::RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;
class G4Step;
class G4LogicalVolume;
class TFile;
class TTree;

namespace B1
{

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run *) override;
    void EndOfRunAction(const G4Run *) override;
    void SetFilePath(const G4String &p) { fFilePath = p; }
    void SetAngle(G4double theta, G4double phi) { fTheta = theta; fPhi = phi; }
    void SetEnergy(G4double energy) { fEnergy = energy; }
    void SetPosition(G4double x, G4double y, G4double z) { fX = x; fY = y; fZ = z; }
    void AddStep(const G4Step *);
    void FillAndReset();

  private:
    G4LogicalVolume *fScoringVolume;
    G4int fNCellX, fNCellY;
    G4double fDetectorMinZ;
    G4double fDetectorX, fDetectorY, fDetectorZ;
    G4String fFilePath;
    G4double fTheta, fPhi, fEnergy;
    G4double fX, fY, fZ;
    std::vector<std::unordered_map<G4int, G4double>> fEdepMap;
    std::vector<G4int> fPos;
    std::vector<G4double> fEdep;
    TFile *fFile;
    TTree *fTree;
};

}

#endif

