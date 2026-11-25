# Architecture decisions

- **Separate repository:** `dB-Studio-REAPER` evolves independently from `dB-Studio-Windows`.
- **Optional DAW:** REAPER, ReaRoute, OSC and ReaScript are optional integrations.
- **Shared baseline:** JUCE 8, XQUIC, QUIC v1, TLS 1.3, local dedicated Wi-Fi, 32 inputs, 16 stereo AUX reference layout, Android/iOS, Live Control UX. These are targets, not proof of implementation.
- **No blind copy:** inspect source tree, license, dependencies and generated files before porting. Preserve notices. Never copy build artifacts, keys, certificates, tokens or user data.
- **ReaRoute optional:** generic ingress API is primary; ReaRoute is one Windows adapter only.
