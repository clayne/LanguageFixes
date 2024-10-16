#include "Language.h"

namespace Language
{
	std::string GetOutput(RE::TESObjectREFR* a_owner, RE::TESBoundObject* a_object, const srell::smatch& a_match)
	{
		switch (gameLanguageHash) {
		case "CHINESE"_h:
			return chinese(a_owner, a_object, a_match).output();
		case "FRENCH"_h:
			return french(a_owner, a_object, a_match).output();
		case "GERMAN"_h:
			return german(a_owner, a_object, a_match).output();
		case "JAPANESE"_h:
			return japanese(a_owner, a_object, a_match).output();
		case "KOREAN"_h:
			return korean(a_owner, a_object, a_match).output();
		case "POLISH"_h:
			return polish(a_owner, a_object, a_match).output();
		case "PORTUGUESE"_h:
			return portuguese(a_owner, a_object, a_match).output();
		case "SPANISH"_h:
			return spanish(a_owner, a_object, a_match).output();
		default:
			return generic(a_owner, a_object, a_match).output();
		}
	}

	void LoadSettings()
	{
		constexpr auto path = L"Data/SKSE/Plugins/po3_LanguageFixes.ini";

		CSimpleIniA ini;
		ini.SetUnicode();

		ini.LoadFile(path);

		ini::get_value(ini, languageOverride, "Settings", "sLanguageOverride", nullptr);
		ini::get_value(ini, doNPCReplacement, "Settings", "bNPCNameReplacement", nullptr);

		(void)ini.SaveFile(path);
	}

	void GetGameLanguageHash()
	{
		std::string gameLanguage = string::toupper(RE::GetINISetting("sLanguage:General")->GetString());

		if (languageOverride.empty()) {
			logger::info("Language override set to AUTODETECT ({})", gameLanguage);
			gameLanguageHash = string::const_hash(gameLanguage);
		} else {
			string::trim(languageOverride);
			languageOverride = string::toupper(languageOverride);

			logger::info("Language override set to {}", languageOverride);
			gameLanguageHash = string::const_hash(languageOverride);
		}
	}
}
