# REAPER integration plan

## 1. Audio ingress
First implement a generic multichannel `AudioIngress` contract. Evaluate ReaRoute as an optional Windows route from REAPER to dB Studio. Validate driver installation, channel count, sample rate, buffer size, device ownership, exclusivity and restart behavior. ReaRoute must not be the only input path.

## 2. Control and metadata
Use REAPER OSC for reliable control/feedback and ReaScript for setup automation. Define a versioned mapping for REAPER track/output -> dB Studio input -> AUX destination -> musician/device label. Mappings must be inspectable and recoverable after project changes.

## 3. Optional VST3 companion
Evaluate a VST3 companion only after audio ingress and OSC/ReaScript are stable. It must not bypass desktop authentication or authorization.

## Acceptance tests
- Standard/standalone mode works with REAPER absent.
- Missing ReaRoute is detected and explained.
- Multichannel mapping survives restart.
- No duplicate device ownership or feedback loop.
- Measure latency, jitter, dropouts and CPU under load.
- OSC loss/reconnect does not stop audio transport.
- Project changes cannot silently route a musician to an unauthorized AUX.

## Initial exclusions
No Bluetooth, no simultaneous P2+USB-C requirement, and no claim of VST3 functionality until a tested plugin exists.
