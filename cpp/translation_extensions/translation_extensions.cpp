#include "amoeboid.hpp"
#include "utilities/debug_console.hpp"
#include "utilities/function_hook.hpp"
#include "utilities/strings.hpp"
#include "utilities/portal.hpp"
#include "types/msvc.hpp"

#include <cstdint>

// Translation Extensions
//
// polymeric 2026

struct CatData {};
struct Component {};
struct CatAdventureCutscene : Component {};
struct BossIntroCutscene : Component {};
struct CatDatabase {};
struct StringsDatabase {};

enum struct TranslationOverrideState {
    Inactive,
    ValidForCatDataCapture,
    ValidForOverride,
};

struct TrapPrivateState {
    TranslationOverrideState to_state = TranslationOverrideState::Inactive;
    CatData *to_catdata = nullptr;
};

static TrapPrivateState P;

// returns false if the csv line is not present or the cell contains a blank string
MAKE_SFPORTAL(ADDRESS_maybe_StringsDatabase__has_translation,
    bool, __cdecl, maybe_StringsDatabase__has_translation,
    (StringsDatabase *thiss, MsvcReleaseModeXString *key),
    (thiss, key)
)

MAKE_SHOOK(0, ADDRESS_glaiel__CatAdventureCutscene__init,
    void, __cdecl, glaiel__CatAdventureCutscene__init,
    CatAdventureCutscene *thiss, void *config
) {
    D::debug("CatAdventureCutscene::init");
    P.to_state = TranslationOverrideState::ValidForCatDataCapture;
    glaiel__CatAdventureCutscene__init_hook.orig(thiss, config);
    P.to_state = TranslationOverrideState::Inactive;
}

MAKE_SHOOK(0, ADDRESS_glaiel__BossIntroCutscene__init,
    void, __cdecl, glaiel__BossIntroCutscene__init,
    BossIntroCutscene *thiss, MsvcReleaseModeXString *arg2, MsvcReleaseModeXString *arg3
) {
    D::debug("BossIntroCutscene::init");
    P.to_state = TranslationOverrideState::ValidForCatDataCapture;
    glaiel__BossIntroCutscene__init_hook.orig(thiss, arg2, arg3);
    P.to_state = TranslationOverrideState::Inactive;
}

MAKE_SHOOK(0, ADDRESS_maybe_CatDatabase_get_cat_data,
    CatData *, __cdecl, maybe_CatDatabase_get_cat_data,
    CatDatabase *thiss, int64_t sql_key
) {
    // D::debug("maybe_CatDatabase_get_cat_data");
    CatData *cat = maybe_CatDatabase_get_cat_data_hook.orig(thiss, sql_key);
    if(P.to_state == TranslationOverrideState::ValidForCatDataCapture) {
        P.to_state = TranslationOverrideState::ValidForOverride;
        P.to_catdata = cat;
    }
    return cat;
}

MAKE_SHOOK(0, ADDRESS_maybe_StringsDatabase__do_translation,
    MsvcReleaseModeXWString *, __cdecl, maybe_StringsDatabase__do_translation,
    StringsDatabase *thiss, MsvcReleaseModeXWString *p_writeback, MsvcReleaseModeXString *p_key, bool try_recurse_mfn
) {
    maybe_StringsDatabase__do_translation_hook.orig(thiss, p_writeback, p_key, try_recurse_mfn);
    if(P.to_state == TranslationOverrideState::ValidForOverride) {
        D::debug("Translation: {} -> {}", p_key->as_native_string_view(), convert_utf16_wstring_to_utf8_string(p_writeback->as_native_wstring_view()));
        bool try_alt_translation;
        std::string alt_translation_key;
        switch(*reinterpret_cast<int32_t *>(reinterpret_cast<uint8_t *>(P.to_catdata) + CATDATA_SEX_OFFSET)) {
            case 0:
                try_alt_translation = true;
                alt_translation_key = std::format("{}_M", p_key->as_native_string_view());
                break;
            case 1:
                try_alt_translation = true;
                alt_translation_key = std::format("{}_F", p_key->as_native_string_view());
                break;
            case 2:
                try_alt_translation = true;
                alt_translation_key = std::format("{}_N", p_key->as_native_string_view());
                break;
            default:
                try_alt_translation = false;
                break;
        }
        bool had_alt_translation = false;
        if(try_alt_translation) {
            MsvcReleaseModeXString alt_translation_key_host;
            alt_translation_key_host.construct(alt_translation_key.data(), alt_translation_key.size());
            had_alt_translation = maybe_StringsDatabase__has_translation(thiss, &alt_translation_key_host);
            D::debug("Override key exists?: {} -> {}", alt_translation_key, had_alt_translation);
            if(had_alt_translation) {
                p_writeback->destroy();
                maybe_StringsDatabase__do_translation_hook.orig(thiss, p_writeback, &alt_translation_key_host, false);
                D::debug("Override result: {} -> {}", alt_translation_key, convert_utf16_wstring_to_utf8_string(p_writeback->as_native_wstring_view()));
            }
            alt_translation_key_host.destroy();
        }
    }
    return p_writeback;
}
