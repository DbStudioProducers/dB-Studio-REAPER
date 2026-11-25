#include "dbstudio/channel_router/channel_router.h"

#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

namespace {
void require(const bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}
}

int main() {
    using namespace dbstudio::audio;
    constexpr std::size_t frames = 4;

    std::array<float, frames> source0{1.0F, 0.5F, -1.0F, 0.0F};
    std::array<float, frames> source1{0.25F, 0.25F, 0.25F, 0.25F};
    std::array<std::array<float, frames>, kAuxBuses * 2> output_samples{};

    AudioBlockView input{};
    input.channels[0] = source0.data();
    input.channels[1] = source1.data();
    input.frame_count = frames;
    input.sample_rate_hz = 48000.0;

    AuxOutputBlockView output{};
    output.frame_count = frames;
    output.sample_rate_hz = 48000.0;
    for (std::size_t channel = 0; channel < output.channels.size(); ++channel) {
        output.channels[channel] = output_samples[channel].data();
    }

    RoutingMatrix matrix{};
    require(matrix.setRoute(0, 0, 1.0F, 0.5F), "configure source 0 -> AUX 1");
    require(matrix.setRoute(1, 0, 0.5F, 1.0F), "configure source 1 -> AUX 1");
    require(!matrix.setRoute(32, 0, 1.0F, 1.0F), "reject input index out of range");
    require(!matrix.setRoute(0, 16, 1.0F, 1.0F), "reject AUX index out of range");
    require(!matrix.setRoute(0, 0, INFINITY, 1.0F), "reject non-finite gain");

    ChannelRouter router{};
    require(router.process(input, output, matrix), "process valid block");
    require(std::fabs(output_samples[0][0] - 1.125F) < 0.0001F, "left mix sum");
    require(std::fabs(output_samples[1][0] - 0.75F) < 0.0001F, "right mix sum");
    require(std::fabs(output_samples[0][2] + 0.875F) < 0.0001F, "negative sample sum");
    require(output_samples[2][0] == 0.0F, "unused AUX remains silent");

    AudioBlockView malformed = input;
    malformed.frame_count = 0;
    require(!router.process(malformed, output, matrix), "reject zero-frame block");

    malformed = input;
    malformed.sample_rate_hz = std::numeric_limits<double>::infinity();
    require(!router.process(malformed, output, matrix), "reject non-finite sample rate");

    RoutingMatrix missing_source{};
    require(missing_source.setRoute(7, 2, 1.0F, 1.0F), "configure route with absent source");
    output_samples[4][0] = 42.0F;
    require(!router.process(input, output, missing_source), "reject active route with null source");
    require(output_samples[4][0] == 42.0F, "invalid block leaves output untouched");

    std::cout << "All channel router tests passed\n";
    return EXIT_SUCCESS;
}
