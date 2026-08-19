#pragma once

#include "utilities/signature.hpp"

#include <cstdint>

// Main program declarations.
//
// polymeric 2026

// CONSTANTS

// Mod information

inline constexpr char MOD_AUTHOR[] = "polymeric";
inline constexpr char MOD_NAME[] = "Translation Extensions";
inline constexpr char MOD_IDENTIFIER[] = "polymeric.translation_extensions";
inline constexpr char MOD_URL[] = "https://github.com/p0lymeric/mewgenics_translation_extensions";
inline constexpr char MOD_VERSION[] = "0.0.1";

// These signatures were extracted from Mewgenics.exe

// Function offsets are encoded as relative VAs
inline constexpr const auto ADDRESS_glaiel__CatAdventureCutscene__init = DirectSig::make<"48 8B C4 48 89 50 10 48 89 48 08 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 38 FD FF FF 48 81 EC 88 03 00 00">(0);
inline constexpr const auto ADDRESS_glaiel__BossIntroCutscene__init = DirectSig::make<"48 8B C4 4C 89 40 18 48 89 50 10 48 89 48 08 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 38 FE FF FF">(0);
inline constexpr const auto ADDRESS_maybe_CatDatabase_get_cat_data = DirectSig::make<"48 89 5C 24 08 48 89 74 24 20 48 89 54 24 10 57 48 83 EC 40 4C 8B C2 48 8B F9 48 83 FA FF 0F 84 ?? ?? ?? ??">(0);
inline constexpr const auto ADDRESS_maybe_StringsDatabase__do_translation = DirectSig::make<"48 89 5C 24 10 48 89 4C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 D9 48 81 EC B0 00 00 00">(0);
inline constexpr const auto ADDRESS_maybe_StringsDatabase__has_translation = DirectSig::make<"49 B9 25 23 22 84 E4 9C F2 CB 48 85 D2 74 ?? 49 B8 B3 01 00 00 00 01 00 00 0F 1F 00 0F B6 04 19">(-244);

// Data offsets are encoded as relative VAs

// TLS variable offsets are encoded relative to the base VA of their TLS slot

// Structure offsets are encoded relative to structure base
// TODO write a verifier to ensure that offsets have not likely moved
inline const ptrdiff_t CATDATA_SEX_OFFSET = 0x58;
// inline const ptrdiff_t STRINGSDATABASE_LANGCODE_OFFSET = 0x40;

// CROSS-TU DECLARATIONS

// The "everything" struct
// Exporter: amoeboid.cpp
struct GlobalContext;
extern GlobalContext G;

// TYPE DECLARATIONS

struct GlobalContext {
    // amoeboid.dll offset.
    uintptr_t dll_base_va;
    uintptr_t dll_image_size;

    // Mewgenics.exe offset.
    uintptr_t host_exec_base_va;
    uintptr_t host_exec_image_size;

    // Whether it is permissible for the dll to self-eject.
    // (false if the dll cannot self-uninstall its hooks)
    bool dll_can_self_eject;
};
