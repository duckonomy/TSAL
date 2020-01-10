#include "ProgressOctave.hpp"

namespace tsal {

ProgressOctave::ProgressOctave(const Context& context, unsigned startNote, unsigned problemSize, unsigned numWorkers) : Instrument(context), mRoutedOscillators(context) {
  mStartNote = startNote;
  mProblemSize = problemSize;
  mNumWorkers = numWorkers;
}

void ProgressOctave::getOutput(AudioBuffer<float> &buffer) {
  mRoutedOscillators.getOutput(buffer);
}

void ProgressOctave::updateContext(const Context& context) {
  OutputDevice::updateContext(mContext);
  mRoutedOscillators.updateContext(mContext);
  
  double startingFrequency = Oscillator::getFrequencyFromNote(mStartNote);
  // Jump by 2 octaves, basically 3 * startingFrequency
  double octavePortion = (3 * startingFrequency) / mNumWorkers;
  mStepValue = octavePortion / mProblemSize;
  for (unsigned i = 0; i < mNumWorkers; i++) {
    mOscillators.push_back(std::make_unique<Oscillator>(mContext));
    mRoutedOscillators.add(*mOscillators[i]);
    mOscillators[i]->setVolume(0.5);
    mOscillators[i]->setFrequency(startingFrequency + octavePortion * i);
  }
}

/* @brief Update the oscillator that corresponds to the id
 *
 * @param id
 */
void ProgressOctave::update(unsigned id) {
  mOscillators[id]->setFrequency(mOscillators[id]->getFrequency() + mStepValue);
}

}
