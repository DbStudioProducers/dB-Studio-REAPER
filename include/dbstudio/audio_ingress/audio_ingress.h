#pragma once

#include "dbstudio/audio_ingress/audio_block_view.h"

namespace dbstudio::audio {

// Backend adapters (hardware, virtual device, or REAPER/ReaRoute) implement this
// lifecycle contract. Audio buffers are borrowed only for the duration of callback.
class AudioIngressCallback {
public:
    virtual ~AudioIngressCallback() = default;
    virtual void onAudioBlock(const AudioBlockView& block) noexcept = 0;
};

class AudioIngress {
public:
    virtual ~AudioIngress() = default;
    virtual bool start(AudioIngressCallback& callback) noexcept = 0;
    virtual void stop() noexcept = 0;
    [[nodiscard]] virtual bool isRunning() const noexcept = 0;
};

} // namespace dbstudio::audio
