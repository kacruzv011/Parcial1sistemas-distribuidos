#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include "simulacion.h"

void simulateAndSave(HarmonicOscillator& system, double dt, int steps, 
                    const std::string& filename);
void runSimulations();

#endif // UTILIDADES_H