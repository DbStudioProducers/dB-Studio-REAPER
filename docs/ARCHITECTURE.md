# Architecture

## Principle
Keep the dB Studio audio/network engine independent from DAWs. REAPER is an optional source/control integration, never a runtime prerequisite.

## Proposed path
REAPER / audio interface / digital mixer -> AudioIngress -> JUCE 8 engine and channel router -> 16 stereo AUX buses -> authenticated XQUIC transport (QUIC v1 / TLS 1.3) -> Android/iOS receiver -> P2 or USB-C output.

## Proposed modules
- `AudioIngress`: common interface for hardware and virtual sources.
- `ReaperBridge`: optional REAPER adapters and session metadata.
- `ChannelRouter`: maps inputs to the 32-channel model and AUX buses.
- `AudioEngine`: JUCE processing and real-time-safe pipeline.
- `Transport`: XQUIC framing and network workers.
- `Identity` / `Authorization`: pairing, credentials, revocation and per-AUX permissions.
- `ReceiverProtocol`: versioned desktop/mobile messages.
- `Diagnostics`: latency, jitter, loss and reconnect telemetry.

These are proposed boundaries, not claims that the modules exist yet.

## Real-time rules
No allocations, blocking locks, file I/O or network I/O in the audio callback. Use bounded queues, define sample format/rate/channel layout/packet duration, and test overflow, underrun, jitter and clock drift.

## Isolation
REAPER integration must be optional and feature-gated. Its absence or failure must not prevent standalone operation. REAPER dependencies must not leak into mobile builds.
