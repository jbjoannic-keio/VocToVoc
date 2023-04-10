#pragma once

#include <vector>
#include <string>
#include <optional>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>


// Returned by /accent_phrases vector
// Returned by /mora_data vector
// Returned by /mora_length vector
// Returned by /mora_pitch vector



class Mora {
public:
	std::string text;
	std::optional<std::string> consonant;
	std::optional<float> consonantLength;
	std::string vowel;
	float vowelLength;
	float pitch;
};

rapidjson::Document MoraToJson(Mora& mora);
Mora JsonToMora(rapidjson::Value& value);

class AccentPhrase {
public:
	std::vector<Mora> moras;
	int accent;
	std::optional<Mora> pauseMora;
	std::optional<bool> isInterrogative;
};

rapidjson::Document AccentPhraseToJson(AccentPhrase& accentPhrase);
AccentPhrase JsonToAccentPhrase(rapidjson::Value& value);

// Returned by /audio_query
// Returned by /audio_query_from_preset
class AudioQuery {
public:
	std::vector<AccentPhrase> accentPhrases;
	float speedScale;
	float pitchScale;
	float intonationScale;
	float volumeScale;
	float prePhonemeLength;
	float postPhonemeLength;
	int outputSampligRate;
	bool outputStereo;
	std::optional<std::string> kana;
};

rapidjson::Document AudioQueryToJson(AudioQuery& audioQuery);
AudioQuery JsonToAudioQuery(rapidjson::Value& document);
/*
class BodySettingPostSettingPost {
public:
	optional<string> corsPoliciyMode;
	optional<string> allowOrigin;
};

rapidjson::Document BodySettingPostSettingPostToJson(BodySettingPostSettingPost& bodySettingPostSettingPost);
BodySettingPostSettingPost JsonToBodySettingPostSettingPost(rapidjson::Document& document);


// Returned by /downloadable_libraries vector
// Returned by /installed_libraries vector
class DowloadableLibrary {
public:
	string name;
	string uuid;
	string version;
	string downloadUrl;
	int bytes;
	vector<LibrarySpeaker> speakers;
};

rapidjson::Document DowloadableLibraryToJson(DowloadableLibrary& dowloadableLibrary);
DowloadableLibrary JsonToDowloadableLibrary(rapidjson::Document& document);


//Returned by /engine_manifest
class EngineManifest {
public:
	string manifestVersion;
	string name;
	string brandName;
	string uuid;
	string utl;
	string icon;
	int defaultSamplingRate;
	string termsOfService;
	vector<UpdateInfo> updateInfos;
	vector<LicenseInfo> dependencyLicenses;
	SupportedFeatures supportedFeatures;
};

rapidjson::Document EngineManifestToJson(EngineManifest& engineManifest);
EngineManifest JsonToEngineManifest(rapidjson::Document& document);

class HTTPValidationError {
public:
	optional<vector<ValidationError>> detail;
};

rapidjson::Document HTTPValidationErrorToJson(HTTPValidationError& hTTPValidationError);
HTTPValidationError JsonToHTTPValidationError(rapidjson::Document& document);

class LibrarySpeaker {
public:
	Speaker speaker;
	SpeakerInfo speakerInfo;
};

rapidjson::Document LibrarySpeakerToJson(LibrarySpeaker& librarySpeaker);
LibrarySpeaker JsonToLibrarySpeaker(rapidjson::Document& document);

class LicenseInfo {
public:
	string name;
	optional<string> version;
	optional<string> license;
	string text;
};

rapidjson::Document LicenseInfoToJson(LicenseInfo& licenseInfo);
LicenseInfo JsonToLicenseInfo(rapidjson::Document& document);
*/



/*
class MorphableTargetInfo {
public:
	bool isMorphable;
};

rapidjson::Document MorphableTargetInfoToJson(MorphableTargetInfo& morphableTargetInfo);
MorphableTargetInfo JsonToMorphableTargetInfo(rapidjson::Document& document);

enum ParseKanaBadRequestError {
	UNKNOWN_TEXT,
	ACCENT_TOP,
	ACCENT_TWICE,
	ACCENT_NOTFOUND,
	EMPTY_PHRASE,
	INTERROGATION_MARK_NOT_AT_END,
	INFINITE_LOOP,
};

class ParseKanaBadRequest {
public:
	string text;
	ParseKanaBadRequestError errorName;
	string errorArgs; ////////////??????
};

rapidjson::Document ParseKanaBadRequestToJson(ParseKanaBadRequest& parseKanaBadRequest);
ParseKanaBadRequest JsonToParseKanaBadRequest(rapidjson::Document& document);


//Returned by /presets vector
class Preset {
public:
	int id;
	string name;
	string speakerUuid;
	int styleId;
	float speedScale;
	float speedScale;
	float pitchScale;
	float intonationScale;
	float volumeScale;
	float prePhonemeLength;
	float postPhonemeLength;
};

rapidjson::Document PresetToJson(Preset& preset);
Preset JsonToPreset(rapidjson::Document& document);
*/
//Returned by /speakers vector


enum SpeakerSupportPermittedSynthesisMorphing {
	ALL,
	SELF_ONLY,
	NOTHING,
};

class SpeakerSupportedFeatures {
public:
	std::optional<std::string> permittedSynthesisMorphing;
};

rapidjson::Document SpeakerSupportedFeaturesToJson(SpeakerSupportedFeatures& speakerSupportedFeatures);
SpeakerSupportedFeatures JsonToSpeakerSupportedFeatures(rapidjson::Value& value);



class SpeakerStyle {
public:
	std::string name;
	int id;
};

rapidjson::Document SpeakerStyleToJson(SpeakerStyle& speakerStyle);
SpeakerStyle JsonToSpeakerStyle(rapidjson::Value& value);


class Speaker {
public:
	std::optional<SpeakerSupportedFeatures> supportedFeatures;
	std::string name;
	std::string speakerUuid;
	std::vector<SpeakerStyle> styles;
	std::optional<std::string> version;
};

rapidjson::Document SpeakerToJson(Speaker& speaker);
Speaker JsonToSpeaker(rapidjson::Value& value);

class StyleInfo {
public:
	int id;
	std::string icon;
	std::optional <std::string > portrait;
	std::vector<std::string> voiceSamples;
};

rapidjson::Document StyleInfoToJson(StyleInfo& styleInfo);
StyleInfo JsonToStyleInfo(rapidjson::Value& value);


//Returned by /speaker_info
class SpeakerInfo {
public:
	std::string policy;
	std::string portrait;
	std::vector<StyleInfo> styleInfos;
};

rapidjson::Document SpeakerInfoToJson(SpeakerInfo& speakerInfo);
SpeakerInfo JsonToSpeakerInfo(rapidjson::Value& value);


/*
//Returned by /supported_devices
class SupportedDevicesInfo {
public:
	bool cpu;
	bool cuda;
	bool dml;
};

rapidjson::Document SupportedDevicesInfoToJson(SupportedDevicesInfo& supportedDevicesInfo);
SupportedDevicesInfo JsonToSupportedDevicesInfo(rapidjson::Document& document);

class SupportedFeatures {
public:
	bool adjustMoraPitch;
	bool adjustPhonemeLength;
	bool adjustSpeedScale;
	bool adjustPitchScale;
	bool adjust_intonation_scale;
	bool adjust_volume_scale;
	bool interrogative_upspeak;
	bool synthesis_morphing;
	bool manage_library;
};

rapidjson::Document SupportedFeaturesToJson(SupportedFeatures& supportedFeatures);
SupportedFeatures JsonToSupportedFeatures(rapidjson::Document& document);

class UpdateInfo {
public:
	string version;
	vector<string> descriptions;
	optional<vector<string>> contributors;
};

rapidjson::Document UpdateInfoToJson(UpdateInfo& updateInfo);
UpdateInfo JsonToUpdateInfo(rapidjson::Document& document);

class UserDictWord {
public:
	string surface;
	int priority;
	optional<int> contextId;
	string partOfSpeech;
	string partOfSpeechDetail1;
	string partOfSpeechDetail2;
	string partOfSpeechDetail3;
	string inflectionalType;
	string inflectionalForm;
	string stem;
	string yomi;
	string pronunciation;
	int accentType;
	optional<int> moraCount;
	string accentAssociativeRule;
};

rapidjson::Document UserDictWordToJson(UserDictWord& userDictWord);
UserDictWord JsonToUserDictWord(rapidjson::Document& document);

// Returned by /user_dict
// Returned by /import_user_dict
class UserDict {
public:
	UserDictWord additionalProp1;
	UserDictWord additionalProp2;
	UserDictWord additionalProp3;
};

rapidjson::Document UserDictToJson(UserDict& userDict);
UserDict JsonToUserDict(rapidjson::Document& document);

class ValidationError {
public:
	vector<string> loc;
	string msg;
	string type;
};

rapidjson::Document ValidationErrorToJson(ValidationError& validationError);
ValidationError JsonToValidationError(rapidjson::Document& document);

enum WordTypes {
	PROPER_NOUN,
	COMMUN_NOUN,
	VERB,
	ADJECTIVE,
	SUFFIX,
};

*/