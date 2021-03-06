#ifndef OSCILLATORNODE_H
#define OSCILLATORNODE_H

#include "OutputDevice.hpp"
#include "Mixer.hpp"

namespace tsal {

/** @class Oscillator
 * @brief A device that generates sound from a waveform
 *  
 * Oscillator is a low level synthesizer that generates samples from
 * algorithmic waveforms. It supports saw, sine, and square waveforms
 */
class Oscillator : public OutputDevice {
  public:
    Oscillator(Mixer* mixer) : OutputDevice(mixer){};
    /**
     * @brief Modes for the oscillator 
     * 
     * Oscillator mode can be switched at anytime during execution
     */
    enum OscillatorMode {
      SAW,
      SINE,
      SQUARE
    };

    double getSample();
    void getOutput(AudioBuffer<float> &buffer) override;
    void setMode(OscillatorMode mode);
    void setNote(double note);
    void setFrequency(double frequency);

    double getFrequency() const;
    unsigned getNote() const;

    static unsigned getNoteFromFrequency(double frequency);
    static double getFrequencyFromNote(double note);

  private:
    double polyBLEP(double t);
    double mFrequency;
    
    OscillatorMode mMode = SINE;
    double mPhase = 0.0;
    double mPhaseStep = 0.0;
    double mWaveFormValue = 0.0;

    static Util::ParameterRange<double> mNoteRange;
    static Util::ParameterRange<double> mFrequencyRange;
};

}
#endif
