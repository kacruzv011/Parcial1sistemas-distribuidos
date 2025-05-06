#include "simulacion.h"
#include <cmath>  // Incluido para usar cos()

HarmonicOscillator::HarmonicOscillator(double mass, double damping, 
                                     double springConstant, 
                                     double forceAmplitude, 
                                     double forceFrequency)
    : m(mass), c(damping), k(springConstant), 
      F0(forceAmplitude), w(forceFrequency), 
      x(0), v(0), t(0) {}

void HarmonicOscillator::updateEulerCromer(double dt) {
    t += dt;
    const double cos_wt = cos(w * t);  // Calculamos una vez
    const double force = F0 * cos_wt;   // Reutilizamos
    const double a = (force - c * v - k * x) / m;
    
    v += a * dt;
    x += v * dt;
}

void HarmonicOscillator::reset() { 
    x = 0; 
    v = 0; 
    t = 0; 
}