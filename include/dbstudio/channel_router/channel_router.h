#pragma once

#include "dbstudio/audio_ingress/audio_block_view.h"

#include <array>
#include <cstddef>

namespace dbstudio::audio {

// Immutable after setup and safe to read from the real-time processing thread.
// A route adds one mono input to the left/right channels of one stereo AUX.
struct RoutingMatrix {
    struct GainPair {
        float left{0.0F};
        float right{0.0F};
    };

    std::array<std::array<GainPair, kInputChannels>, kAuxBuses> gains{};

    [[nodiscard]] bool setRoute(std::size_t input,
                                std::size_t aux,
                                float left_gain,
                                float right_gain) noexcept;
};

class ChannelRouter final {
public:
    // No allocations, locks, logging, or I/O. Output is cleared before summing.
    // Returns false for malformed blocks or missing buffers used by active routes.
    [[nodiscard]] bool process(const AudioBlockView& input,
                               AuxOutputBlockView& output,
                               const RoutingMatrix& routing) const noexcept;
};

} // namespace dbstudio::audio
