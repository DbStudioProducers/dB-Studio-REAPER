# dB Studio REAPER Edition

**Status:** architecture scaffold only; this is not yet a functional audio receiver.

A REAPER-oriented edition of dB Studio. REAPER integration is optional: the core system must continue to run without REAPER or ReaRoute.

## Baseline
- JUCE 8; XQUIC / QUIC v1 / TLS 1.3 target.
- Windows 10/11 desktop; Android and iOS receiver targets.
- 32 input channels and 16 stereo AUX mixes as reference.
- Dedicated local Wi-Fi; internet not required for normal operation.
- No Bluetooth in v1; wired P2 and USB-C mobile output.
- Preserve the approved dark, high-contrast Live Control UX.

## Planned REAPER integration
1. Generic multichannel audio ingress.
2. Optional Windows ReaRoute adapter.
3. OSC control and ReaScript setup/mapping helpers.
4. Evaluate a VST3 companion only after core integration is validated.

See `docs/` for architecture, integration, roadmap and decisions.
