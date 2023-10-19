#include "audio_stream_csound.h"
#include "audio_stream_player_csound.h"
#include "csound_gdextension.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

AudioStreamCsound::AudioStreamCsound() : mix_rate(44100), stereo(false), hz(639) {
}

AudioStreamCsound::~AudioStreamCsound() {
}

Ref<AudioStreamPlayback> AudioStreamCsound::_instantiate_playback() const {
    Ref<AudioStreamPlaybackCsound> talking_tree;
    talking_tree.instantiate();
    talking_tree->base = Ref<AudioStreamCsound>(this);
    return talking_tree;
}

String AudioStreamCsound::get_stream_name() const {
    return "Csound";
}

void AudioStreamCsound::reset() {
    set_position(0);
}

void AudioStreamCsound::set_position(uint64_t p) {
    pos = p;
}

int AudioStreamCsound::gen_tone(AudioFrame *p_buffer, float p_rate, int p_frames) {
    if (CsoundEngine::get_singleton() != NULL) {
        return CsoundEngine::get_singleton()->gen_tone(p_buffer, p_rate, p_frames);
    }
    return 0;
}

void AudioStreamCsound::set_soundfont(Ref<SoundFontFileReader> p_soundfont) {
    soundfont = p_soundfont;
    if (soundfont != NULL && CsoundEngine::get_singleton() != NULL) {
        CsoundEngine::get_singleton()->set_soundfont(soundfont->get_path());
    }
}

Ref<SoundFontFileReader> AudioStreamCsound::get_soundfont() {
    return soundfont;
}

void AudioStreamCsound::set_midi_file(Ref<MidiFileReader> p_midi_file) {
    midi_file = p_midi_file;
    if (midi_file != NULL && CsoundEngine::get_singleton() != NULL) {
        CsoundEngine::get_singleton()->set_midi_file(midi_file);
    }
}

Ref<MidiFileReader> AudioStreamCsound::get_midi_file() {
    return midi_file;
}

void AudioStreamCsound::_bind_methods() {
    ClassDB::bind_method(D_METHOD("reset"), &AudioStreamCsound::reset);
    ClassDB::bind_method(D_METHOD("get_stream_name"), &AudioStreamCsound::get_stream_name);
    ClassDB::bind_method(D_METHOD("set_soundfont", "soundfont"), &AudioStreamCsound::set_soundfont);
    ClassDB::bind_method(D_METHOD("get_soundfont"), &AudioStreamCsound::get_soundfont);
    ClassDB::add_property(
        "AudioStreamCsound",
        PropertyInfo(Variant::OBJECT, "soundfont", PROPERTY_HINT_RESOURCE_TYPE, "SoundFontFileReader"), "set_soundfont",
        "get_soundfont");
    ClassDB::bind_method(D_METHOD("set_midi_file", "midi_file"), &AudioStreamCsound::set_midi_file);
    ClassDB::bind_method(D_METHOD("get_midi_file"), &AudioStreamCsound::get_midi_file);
    ClassDB::add_property("AudioStreamCsound",
                          PropertyInfo(Variant::OBJECT, "midi_file", PROPERTY_HINT_RESOURCE_TYPE, "MidiFileReader"),
                          "set_midi_file", "get_midi_file");
}
