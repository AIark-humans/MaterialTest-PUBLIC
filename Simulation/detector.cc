#include "detector.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name), totalDose(0)
{ }

SensitiveDetector::~SensitiveDetector()
{ }



G4bool SensitiveDetector::ProcessHits(G4Step * aStep, G4TouchableHistory * ROhist){

    auto particle = aStep->GetTrack()->GetDefinition()->GetParticleName();//particle 
    G4double limit = 10;// LET threshold for high risk events, in keV/um. This value is based on literature.

    G4double edep = aStep->GetTotalEnergyDeposit(); //Energy deposited by particle
    G4double stepLength = aStep->GetStepLength(); //Distance particle traveled between checks 

    G4LogicalVolume* detectorVolume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    G4double detectorMass = detectorVolume->GetMass();


    //Calculating if current event is a high risk event for SEUs
    if (edep > 0 && stepLength > 0) {
        G4double approxLET = edep / stepLength; // In actuality LET = dE/dx, however due to limited computing resources delta E/ delta x was implemented instead.
        approxLET = approxLET / ( keV / um ); //Ensuring proper units 

        if (approxLET > 10) {
            highRiskEvents++;
        }
    }

    if (edep > 0){
        G4double dose = (edep / (detectorMass));
        totalDose += dose;
    }

    return true;
}

