#include <iostream>
#include <fstream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

#ifndef microgray
constexpr G4double microgray = 1.e-6 * gray;
#endif

int main(int argc, char** argv) {

  std::ofstream outFile;


  G4RunManager* runManager = new G4RunManager();

  DetectorConstruction* detConstruction = new DetectorConstruction();
  runManager->SetUserInitialization(detConstruction);
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());

  PrimaryGenerator* generator = new PrimaryGenerator();
  runManager->SetNumberOfThreads(4);
  runManager->SetUserAction(generator);

  runManager->Initialize();

  std::vector<G4double> thicknessList;
  for (G4double d = 2.0 * cm; d <= 15.0 * cm; d += 0.5 * cm)
    thicknessList.push_back(d);

  G4String energyLevel = "";

  for (G4int j = 1; j < 6; j++) {
    if (j == 1) { energyLevel = "10";  generator->SetParticleEnergy(10.  * MeV); }
    if (j == 2) { energyLevel = "25";  generator->SetParticleEnergy(25.  * MeV); }
    if (j == 3) { energyLevel = "50";  generator->SetParticleEnergy(50.  * MeV); }
    if (j == 4) { energyLevel = "100"; generator->SetParticleEnergy(100. * MeV); }
    if (j == 5) { energyLevel = "300"; generator->SetParticleEnergy(300. * MeV); }

    outFile.open("official_proton_" + energyLevel + "MeV.csv");
    outFile << "Material, Thickness (cm), Dose (rad), High Risk Events\n";

    for (G4int k = 0; k < 1; k++) {
      for (G4int i = 1; i < 4; i++) {

        detConstruction->SetShieldMat(i);

        for (auto depth : thicknessList) {
          detConstruction->SetShieldThickness(depth);
          runManager->ReinitializeGeometry();
		  auto UImanager = G4UImanager::GetUIpointer();
			UImanager->ApplyCommand("/vis/scene/notifyHandlers");
			UImanager->ApplyCommand("/vis/viewer/refresh");

          runManager->BeamOn(100000);

          SensitiveDetector* sd = detConstruction->GetSensitiveDetector();

          if (sd) {
            G4String matName;
            if (i == 1) matName = "Aluminum Wall 6mm (BaseLine)";
            else if (i == 2) matName = "HDPE";
            else if (i == 3) matName = "Composite (27H:13S)";
            else if (i == 4) matName = "Hydrgel";
            else if (i == 5) matName = "Silicone";

            G4cout << "==========================================" << G4endl;
            G4cout << "Material Name: " << matName << G4endl;
            G4cout << "Energy Level: " << j  << "/5" << G4endl;
            G4cout << "RunNum: " << k + 1 << "/30" << G4endl;
            G4cout << "Depth: " << depth / cm << " cm" << G4endl;
            G4cout << "Absorbed dose: " << (sd->GetTotalDose()) * 100 << " rad" << G4endl;
            G4cout << "High Risk Events: " << (sd->GetHighRiskEvents()) << G4endl;
            G4cout << "==========================================" << G4endl;

            outFile << matName << "," << depth / cm << ","
                    << (sd->GetTotalDose()) * 100 << ","
                    << sd->GetHighRiskEvents() << "\n";
          }
        }
      }
    }

    outFile.close();
  }
  delete runManager;

  return 0;
}