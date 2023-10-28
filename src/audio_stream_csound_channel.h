#ifndef AUDIOSTREAMCSOUNDCHANNEL_H
#define AUDIOSTREAMCSOUNDCHANNEL_H

#include "csound.hpp"

#include <godot_cpp/classes/audio_frame.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/godot.hpp>

#include "audio_stream_csound.h"
#include "csound_godot.h"

namespace godot {

class AudioStreamCsoundChannel : public AudioStreamCsound {
    GDCLASS(AudioStreamCsoundChannel, AudioStreamCsound)

private:
    friend class AudioStreamPlaybackCsound;
    float pos;
    int mix_rate;
    bool stereo;
    int hz;
    String csound_name;
    int left;
    int right;

public:
    AudioStreamCsoundChannel();
    void set_left(int p_left);
    int get_left();
    void set_right(int p_right);
    int get_right();
    int gen_tone(AudioFrame *p_buffer, float p_rate, int p_frames) override;
    virtual Ref<AudioStreamPlayback> _instantiate_playback() const override;

protected:
    static void _bind_methods();
};
} // namespace godot

#endif
