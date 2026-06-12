#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
class SensitiveDetector : public G4VSensitiveDetector {
public:
	SensitiveDetector(G4String);
	~SensitiveDetector();
	G4int highRiskEvents = 0;
	G4double totalDose = 0.0;

	G4double GetTotalDose() const { return totalDose;}
	G4double GetHighRiskEvents() const { return highRiskEvents; }

	void SensitiveDetector::Reset() {
		totalDose = 0.;
		highRiskEvents = 0;
	}

private:
	
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};
#endif 
