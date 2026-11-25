#pragma once

#include <array>
#include <cstddef>

namespace dbstudio::audio {

inline constexpr std::size_t kInputChannels = 32;
inline constexpr std::size_t kAuxBuses = 16;
inline constexpr std::size_t kChannelsPerAux = 2;

struct AudioBlockView {
    // Non-owning, planar float buffers. Each non-null channel has frame_count samples.
    std::array<const float*, kInputChannels> channels{};
    std::size_t frame_count{0};
    double sample_rate_hz{0.0};
};

struct AuxOutputBlockView {
    // Interleaving is deliberately avoided: each AUX has separate L/R planes.
    std::array<float*, kAuxBuses * kChannelsPerAux> channels{};
    std::size_t frame_count{0};
    double sample_rate_hz{0.0};
};

} // namespace dbstudio::audio
