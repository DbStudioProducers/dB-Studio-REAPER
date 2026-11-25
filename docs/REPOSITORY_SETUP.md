# Repository setup

This repository is the public, independent REAPER edition of dB Studio.

## Source baseline
Standard remains https://github.com/DbStudioProducers/dB-Studio-Windows.
At scaffold preparation, PR #4 was open/Draft and its head commit was `161dd9ee4163d915ca918fde4c75fa89d60d49c6`.

Do not merge PR #4 or alter Standard. Before importing code, re-check the chosen source branch and commit. Inspect the license and dependencies. Port shared modules selectively in a separate commit; do not blindly mirror the repo. Run tests before each build.

## Initial repository state
The initial README and scaffold were committed to the `main` branch. Choose a license deliberately after reviewing source and dependencies; do not add license headers or assume licensing rights for imported code.
