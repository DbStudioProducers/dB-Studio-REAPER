# Roadmap and acceptance criteria

1. **Repository foundation:** create separate public repo; preserve Standard and PR #4; record source commit, license provenance and dependency versions.
2. **Core parity:** identify reusable Standard modules; review licenses before copying; isolate REAPER-specific code.
3. **Audio ingress:** generic multichannel API; optional ReaRoute proof of concept; validate 32 inputs -> 16 stereo AUX; stress-test callback.
4. **REAPER control:** OSC lifecycle/feedback, ReaScript setup, versioned mapping import/export, missing/reconnect tests.
5. **Network/receivers:** authenticated XQUIC; Android and iOS receivers; jitter buffer, stereo playback, AUX authorization and reconnect.
6. **Validation:** unit/integration/security tests; Windows/Android/iOS builds; virtual end-to-end tests; physical Wi-Fi tests when hardware is available; measure latency/jitter/loss/CPU at 1, 4, 8 and 16 receivers.

## Definition of done
REAPER ingress/control works in a real session; standalone fallback works; authenticated stereo audio reaches mobile receivers; AUX permissions are enforced; automated and physical validation evidence is published.
