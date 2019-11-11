#ifndef AUDIOBUFFER_H
#define AUDIOBUFFER_H

#include <vector>

namespace tsal {

template <typename T>
class AudioBuffer {
  public:
    AudioBuffer(unsigned long frameCount, unsigned channelCount)
      : mBuffer(frameCount * channelCount, 0),
        mFrameCount(frameCount),
        mChannelCount(channelCount) {};
    void updateFrameCount(unsigned long frameCount);
    void updateChannelCount(unsigned channelCount);
    unsigned long getFrameCount() { return mFrameCount; }
    unsigned getChannelCount() { return mChannelCount; }

    const T& operator[](int index) const;
    T& operator[](int index);
  private:
    void resizeBuffer() { mBuffer.resize(mFrameCount * mChannelCount); };
    std::vector<T> mBuffer;
    unsigned long mFrameCount;
    unsigned mChannelCount;
};

template <typename T>
const T& AudioBuffer<T>::operator[](int index) const {
  return mBuffer[index];
}

template <typename T>
T& AudioBuffer<T>::operator[](int index) {
  return mBuffer[index];
}

template <typename T>
void AudioBuffer<T>::updateFrameCount(unsigned long frameCount) {
  mFrameCount = frameCount;
  resizeBuffer();
}

template <typename T>
void AudioBuffer<T>::updateChannelCount(unsigned channelCount) {
  mChannelCount = channelCount;
  resizeBuffer();
}

}

#endif
