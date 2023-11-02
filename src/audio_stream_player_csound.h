#ifndef AUDIOSTREAMPLAYERCSOUND_H
#define AUDIOSTREAMPLAYERCSOUND_H

#include <godot_cpp/classes/audio_frame.hpp>
#include <godot_cpp/classes/audio_server.hpp>
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/audio_stream_playback.hpp>
#include <godot_cpp/godot.hpp>

#include "audio_stream_csound.h"

namespace godot {

class AudioStreamPlaybackCsound : public AudioStreamPlayback {
    GDCLASS(AudioStreamPlaybackCsound, AudioStreamPlayback)
    friend class AudioStreamCsound;

private:
    struct PlaybackEntry {
        Ref<AudioStreamPlayback> playback;
        String channel_left;
        String channel_right;
    };

    Vector<PlaybackEntry> playback_list;
    Ref<AudioStreamCsound> base;
    bool active;

public:
    static void _bind_methods();

    virtual void _start(double p_from_pos = 0.0) override;
    virtual void _stop() override;
    virtual bool _is_playing() const override;
    virtual int _get_loop_count() const override;
    virtual double _get_playback_position() const override;
    virtual void _seek(double p_time) override;
    virtual int _mix(AudioFrame *p_buffer, double p_rate_scale, int p_frames) override;
    virtual void _tag_used_streams() override;
    virtual float _get_length() const;
    AudioStreamPlaybackCsound();
    ~AudioStreamPlaybackCsound();
};
} // namespace godot

#endif
