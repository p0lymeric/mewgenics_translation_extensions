## Translation Extensions

## Use

Framework mod that extends Mewgenics' language translation capabilities. Currently, this mod is under development and experimental.

- Adds support for `_M`/`_F`/`_N` cat quotes used in cutscenes (`CAT_VS_BOSS_QUOTES_*`, `CAT_EMBARK_QUOTES_*`, `CAT_RETURN_EARLY_QUOTES_*`, `CAT_RETURN_QUOTES_*`), for languages that grammatically differentiate by speaker gender.

This mod does nothing in itself. Additional translation data in combined.csv is required for features to have an effect.

## Installation requirements

This mod is packaged for the [Mewtator](https://www.nexusmods.com/mewgenics/mods/1) mod loader and [Mewjector](https://www.nexusmods.com/mewgenics/mods/218) dll loader.

Both are highly recommended for a standard install.

If you encounter crashes, please verify:
* the version of Mewgenics you have installed matches the required version specified in this mod's release notes.
* you have the latest versions of [Mewtator](https://www.nexusmods.com/mewgenics/mods/1) and [Mewjector](https://www.nexusmods.com/mewgenics/mods/218) installed.
* you have dll mod support enabled in Mewtator.

## Build requirements

This repository is self-contained, apart from tooling (all C/C++ source code, including that of dependencies, is included).

To compile the dll from source, [CMake](https://cmake.org/) and a contemporary version of the [MSVC compiler (2022/2026)](https://visualstudio.microsoft.com/downloads/) are required.

Developers may appreciate that this dll can be injected standalone with the tool provided under `cpp/cosmic_ooze`, or another tool such as Cheat Engine or System Informer. Players should use Mewjector.

## Licensing

All original material outside of `third_party` directories are distributed under the MIT license. See [LICENSE.md](LICENSE.md) for details.

See [ATTRIBUTION.md](ATTRIBUTION.md) and license documents under `third_party` directories for dependency licenses.
