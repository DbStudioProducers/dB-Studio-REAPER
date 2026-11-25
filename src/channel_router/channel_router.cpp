#include "dbstudio/channel_router/channel_router.h"

#include <cmath>

namespace dbstudio::audio {

bool RoutingMatrix::setRoute(const std::size_t input,
                             const std::size_t aux,
                             const float left_gain,
                             const float right_gain) noexcept {
    if (input >= kInputChannels || aux >= kAuxBuses ||
        !std::isfinite(left_gain) || !std::isfinite(right_gain)) {
        return false;
    }
    gains[aux][input] = {left_gain, right_gain};
    return true;
}

bool ChannelRouter::process(const AudioBlockView& input,
                            AuxOutputBlockView& output,
                            const RoutingMatrix& routing) const noexcept {
    if (input.frame_count == 0 || output.frame_count != input.frame_count ||
        input.sample_rate_hz <= 0.0 || output.sample_rate_hz != input.sample_rate_hz) {
        return false;
    }

    for (float* channel : output.channels) {
        if (channel == nullptr) {
            return false;
        }
    }

    for (float* channel : output.channels) {
        for (std::size_t frame = 0; frame < output.frame_count; ++frame) {
            channel[frame] = 0.0F;
        }
    }

    for (std::size_t aux = 0; aux < kAuxBuses; ++aux) {
        float* left = output.channels[aux * kChannelsPerAux];
        float* right = output.channels[aux * kChannelsPerAux + 1];

        for (std::size_t source = 0; source < kInputChannels; ++source) {
            const auto route = routing.gains[aux][source];
            if (route.left == 0.0F && route.right == 0.0F) {
                continue;
            }
            const float* const samples = input.channels[source];
            if (samples == nullptr) {
                return false;
            }

            for (std::size_t frame = 0; frame < input.frame_count; ++frame) {
                const float sample = samples[frame];
                left[frame] += sample * route.left;
                right[frame] += sample * route.right;
            }
        }
    }
    return true;
}

} // namespace dbstudio::audio
