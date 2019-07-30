#include "Sequencer.hpp"
#include "Mixer.hpp"

namespace tsal {

void Sequencer::tick() {
  // This has some margin of error since mSamplesPerTick is a floating point number
  // But it seems to work well enough, maybe in the future it would be better to change to a more consistent timing method
  if (++mSampleTime > mSamplesPerTick) {
    mTick++;
    // for (unsigned i = 0; i < mEvents.size(); i++) {
    //   if (mTick >= mEvents[i]->tick) {
    //     mEvents[i]->callback();
    //     mEvents.erase(mEvents.begin() + i);
    //   }
    // }
    while (!mEventQueue.empty() && mTick >= mEventQueue.top()->tick) {
      mEventQueue.top()->callback();
      delete mEventQueue.top();
      mEventQueue.pop();
    }
    mSampleTime = 0;
  }
}

void Sequencer::setTick(unsigned tick) {
  mTick = tick;
}

/**
 * @brief Set the BPM (beats pre minute)
 * 
 * @param bpm 
 */
void Sequencer::setBPM(unsigned bpm) {
  mBPM = Util::checkParameterRange("Sequencer: BPM", bpm, mBPMRange);
  setSamplesPerTick();
}

/**
 * @brief Set the PPQ (pulses per quater)
 * 
 * @param ppq 
 */
void Sequencer::setPPQ(unsigned ppq) {
  mPPQ = Util::checkParameterRange("Sequencer: PPQ", ppq, mPPQRange);
  setSamplesPerTick();
}

void Sequencer::setSamplesPerTick() {
  mSamplesPerTick = mSampleRate / ((mBPM * mPPQ) / 60);
}

void Sequencer::schedule(std::function<void ()> callback, Timing::NoteScale scale, unsigned duration) {
  int tick = getTicksInNote(scale) * duration;
  mEventQueue.push(new Event(mTick + tick, callback));
}

unsigned Sequencer::getTick() const {
  return mTick;
}

unsigned Sequencer::getTicksInNote(Timing::NoteScale note) const {
  return (note == Timing::TICK) ? 1 : mPPQ * 4.0 * (1.0/note);
}

Util::ParameterRange<unsigned> Sequencer::mBPMRange = std::make_pair(1, 1000);
Util::ParameterRange<unsigned> Sequencer::mPPQRange = std::make_pair(1, 1000);

}
