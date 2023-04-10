#include "VoiceVoxClasses.h"
#include <iostream>
rapidjson::Document AccentPhraseToJson(AccentPhrase& accentPhrase) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value moras(rapidjson::kArrayType);

	for (Mora& mora : accentPhrase.moras) {

		rapidjson::Value moraJson(rapidjson::kObjectType);
		moraJson.AddMember("text", rapidjson::Value(mora.text.c_str(), allocator).Move(), allocator);
		if (mora.consonant.has_value()) {
			moraJson.AddMember("consonant", rapidjson::Value(mora.consonant.value().c_str(), allocator).Move(), allocator);
		}
		if (mora.consonantLength.has_value()) {
			moraJson.AddMember("consonant_length", mora.consonantLength.value(), allocator);
		}
		moraJson.AddMember("vowel", rapidjson::Value(mora.vowel.c_str(), allocator).Move(), allocator);
		moraJson.AddMember("vowel_length", mora.vowelLength, allocator);
		moraJson.AddMember("pitch", mora.pitch, allocator);

		moras.PushBack(moraJson, allocator);
	}

	document.AddMember("moras", moras, allocator);
	document.AddMember("accent", accentPhrase.accent, allocator);
	
	if (accentPhrase.pauseMora.has_value()) {
		Mora mora = accentPhrase.pauseMora.value();
		rapidjson::Value moraJson(rapidjson::kObjectType);
		moraJson.AddMember("text", rapidjson::Value(mora.text.c_str(), allocator).Move(), allocator);
		if (mora.consonant.has_value()) {
			moraJson.AddMember("consonant", rapidjson::Value(mora.consonant.value().c_str(), allocator).Move(), allocator);
		}
		if (mora.consonantLength.has_value()) {
			moraJson.AddMember("consonant_length", mora.consonantLength.value(), allocator);
		}
		moraJson.AddMember("vowel", rapidjson::Value(mora.vowel.c_str(), allocator).Move(), allocator);
		moraJson.AddMember("vowel_length", mora.vowelLength, allocator);
		moraJson.AddMember("pitch", mora.pitch, allocator);
		//rapidjson::Document moraJson = MoraToJson(mora);
		document.AddMember("pause_mora", moraJson, allocator);
	}

	if (accentPhrase.isInterrogative.has_value()) {
		document.AddMember("is_interrogative", accentPhrase.isInterrogative.value(), allocator);
	}

	return document;
};

AccentPhrase JsonToAccentPhrase(rapidjson::Value& value) {
	AccentPhrase accentPhrase;

	for (rapidjson::Value& moraJson : value["moras"].GetArray()) {
		accentPhrase.moras.push_back(JsonToMora(moraJson));
	}
	accentPhrase.accent = value["accent"].GetInt();

	
	if (value.HasMember("pause_mora")) {
		accentPhrase.pauseMora = JsonToMora(value["pause_mora"]);
	}

	if (value.HasMember("is_interrogative")) {
		accentPhrase.isInterrogative = value["is_interrogative"].GetBool();
	}

	return accentPhrase;
};




rapidjson::Document AudioQueryToJson(AudioQuery& audioQuery) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value accentPhrases(rapidjson::kArrayType);
	for (AccentPhrase& accentPhrase : audioQuery.accentPhrases) {
		rapidjson::Value accentPhraseJson(rapidjson::kObjectType);
		rapidjson::Value moras(rapidjson::kArrayType);
		for (Mora& mora : accentPhrase.moras) {
			rapidjson::Value moraJson(rapidjson::kObjectType);
			moraJson.AddMember("text", rapidjson::Value(mora.text.c_str(), allocator).Move(), allocator);
			if (mora.consonant.has_value()) {
				moraJson.AddMember("consonant", rapidjson::Value(mora.consonant.value().c_str(), allocator).Move(), allocator);
			}
			if (mora.consonantLength.has_value()) {
				moraJson.AddMember("consonant_length", mora.consonantLength.value(), allocator);
			}
			moraJson.AddMember("vowel", rapidjson::Value(mora.vowel.c_str(), allocator).Move(), allocator);
			moraJson.AddMember("vowel_length", mora.vowelLength, allocator);
			moraJson.AddMember("pitch", mora.pitch, allocator);
			moras.PushBack(moraJson, allocator);
		}
		accentPhraseJson.AddMember("moras", moras, allocator);
		accentPhraseJson.AddMember("accent", accentPhrase.accent, allocator);
		if (accentPhrase.pauseMora.has_value()) {
			Mora mora = accentPhrase.pauseMora.value();
			rapidjson::Value moraJson(rapidjson::kObjectType);
			moraJson.AddMember("text", rapidjson::Value(mora.text.c_str(), allocator).Move(), allocator);
			if (mora.consonant.has_value()) {
				moraJson.AddMember("consonant", rapidjson::Value(mora.consonant.value().c_str(), allocator).Move(), allocator);
			}
			if (mora.consonantLength.has_value()) {
				moraJson.AddMember("consonant_length", mora.consonantLength.value(), allocator);
			}
			moraJson.AddMember("vowel", rapidjson::Value(mora.vowel.c_str(), allocator).Move(), allocator);
			moraJson.AddMember("vowel_length", mora.vowelLength, allocator);
			moraJson.AddMember("pitch", mora.pitch, allocator);
			accentPhraseJson.AddMember("pause_mora", moraJson, allocator);
		}
		if (accentPhrase.isInterrogative.has_value()) {
			accentPhraseJson.AddMember("is_interrogative", accentPhrase.isInterrogative.value(), allocator);
		}
		accentPhrases.PushBack(accentPhraseJson, allocator);
	}
	document.AddMember("accent_phrases", accentPhrases, allocator);
	document.AddMember("speedScale", audioQuery.speedScale, allocator);
	document.AddMember("pitchScale", audioQuery.pitchScale, allocator);
	document.AddMember("intonationScale", audioQuery.intonationScale, allocator);
	document.AddMember("volumeScale", audioQuery.volumeScale, allocator);
	document.AddMember("prePhonemeLength", audioQuery.prePhonemeLength, allocator);
	document.AddMember("postPhonemeLength", audioQuery.postPhonemeLength, allocator);
	document.AddMember("outputSamplingRate", audioQuery.outputSampligRate, allocator);
	document.AddMember("outputStereo", audioQuery.outputStereo, allocator);
	if (audioQuery.kana.has_value()) {
		document.AddMember("kana", rapidjson::Value(audioQuery.kana.value().c_str(), allocator).Move(), allocator);
	}
	return document;
}

AudioQuery JsonToAudioQuery(rapidjson::Value& value) {
	AudioQuery audioQuery;

	for (rapidjson::Value& accentPhraseJson : value["accent_phrases"].GetArray()) {
		audioQuery.accentPhrases.push_back(JsonToAccentPhrase(accentPhraseJson));
	}
	audioQuery.speedScale = value["speedScale"].GetFloat();
	audioQuery.pitchScale = value["pitchScale"].GetFloat();
	audioQuery.intonationScale = value["intonationScale"].GetFloat();
	audioQuery.volumeScale = value["volumeScale"].GetFloat();
	audioQuery.prePhonemeLength = value["prePhonemeLength"].GetFloat();
	audioQuery.postPhonemeLength = value["postPhonemeLength"].GetFloat();
	audioQuery.outputSampligRate = value["outputSamplingRate"].GetInt();
	audioQuery.outputStereo = value["outputStereo"].GetBool();
	if (value.HasMember("kana")) {
		audioQuery.kana = value["kana"].GetString();
	}
	return audioQuery;
}

/*
rapidjson::Document BodySettingPostSettingPostToJson(BodySettingPostSettingPost& bodySettingPostSettingPost);
BodySettingPostSettingPost JsonToBodySettingPostSettingPost(rapidjson::Document& document);


rapidjson::Document DowloadableLibraryToJson(DowloadableLibrary& dowloadableLibrary);
DowloadableLibrary JsonToDowloadableLibrary(rapidjson::Document& document);


rapidjson::Document EngineManifestToJson(EngineManifest& engineManifest);
EngineManifest JsonToEngineManifest(rapidjson::Document& document);


rapidjson::Document HTTPValidationErrorToJson(HTTPValidationError& hTTPValidationError);
HTTPValidationError JsonToHTTPValidationError(rapidjson::Document& document);


rapidjson::Document LibrarySpeakerToJson(LibrarySpeaker& librarySpeaker);
LibrarySpeaker JsonToLibrarySpeaker(rapidjson::Document& document);


rapidjson::Document LicenseInfoToJson(LicenseInfo& licenseInfo);
LicenseInfo JsonToLicenseInfo(rapidjson::Document& document);

*/
rapidjson::Document MoraToJson(Mora& mora) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember("text", rapidjson::Value(mora.text.c_str(), allocator).Move(), allocator);


	if (mora.consonant.has_value()) {
		document.AddMember("consonant", rapidjson::Value(mora.consonant.value().c_str(), allocator).Move(), allocator);
	}

	if (mora.consonantLength.has_value()) {
		document.AddMember("consonant_length", mora.consonantLength.value(), allocator);
	}

	document.AddMember("vowel", rapidjson::Value(mora.vowel.c_str(), allocator).Move(), allocator);

	document.AddMember("vowel_length", mora.vowelLength, allocator);

	document.AddMember("pitch", mora.pitch, allocator);

	return document;
};

Mora JsonToMora(rapidjson::Value& value) {
	Mora mora;
	if (value.HasMember("text")) {
		mora.text = value["text"].GetString();
	}
	if (value.HasMember("consonant")) {
		mora.consonant = value["consonant"].GetString();
	}

	if (value.HasMember("consonant_length")) {
		mora.consonantLength = value["consonant_length"].GetFloat();
	}

	mora.vowel = value["vowel"].GetString();

	mora.vowelLength = value["vowel_length"].GetFloat();

	mora.pitch = value["pitch"].GetFloat();

	return mora;
};


/*
rapidjson::Document MorphableTargetInfoToJson(MorphableTargetInfo& morphableTargetInfo);
MorphableTargetInfo JsonToMorphableTargetInfo(rapidjson::Document& document);


rapidjson::Document ParseKanaBadRequestToJson(ParseKanaBadRequest& parseKanaBadRequest);
ParseKanaBadRequest JsonToParseKanaBadRequest(rapidjson::Document& document);
 /////////////////////////////////////////////////////////////////////////////////////////////////

rapidjson::Document PresetToJson(Preset& preset);
Preset JsonToPreset(rapidjson::Document& document);
*/
//
rapidjson::Document SpeakerToJson(Speaker& speaker) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	if (speaker.supportedFeatures.has_value()) {
		rapidjson::Value supportedFeaturesJson(rapidjson::kObjectType);
		if (speaker.supportedFeatures.value().permittedSynthesisMorphing.has_value()) {
			supportedFeaturesJson.AddMember("permitted_synthesis_morphing", rapidjson::Value(speaker.supportedFeatures.value().permittedSynthesisMorphing.value().c_str(), allocator).Move(), allocator);
		}
		document.AddMember("supported_features", supportedFeaturesJson, allocator);
	}

	document.AddMember("name", rapidjson::Value(speaker.name.c_str(), allocator).Move(), allocator);

	document.AddMember("speaker_uuid", rapidjson::Value(speaker.speakerUuid.c_str(), allocator).Move(), allocator);

	rapidjson::Value stylesJson(rapidjson::kArrayType);
	for (SpeakerStyle style : speaker.styles) {
		rapidjson::Value styleJson(rapidjson::kObjectType);
		styleJson.AddMember("name", rapidjson::Value(style.name.c_str(), allocator).Move(), allocator);
		styleJson.AddMember("id", style.id, allocator);
		stylesJson.PushBack(styleJson, allocator);
	}
	document.AddMember("styles", stylesJson, allocator);

	if (speaker.version.has_value()) {
		document.AddMember("version", rapidjson::Value(speaker.version.value().c_str(), allocator).Move(), allocator);
	}

	return document;
};

Speaker JsonToSpeaker(rapidjson::Value& value) {
	Speaker speaker;

	if (value.HasMember("supported_features")) {
		speaker.supportedFeatures = JsonToSpeakerSupportedFeatures(value["supported_features"]);
	}
	speaker.name = value["name"].GetString();
	speaker.speakerUuid = value["speaker_uuid"].GetString();
	
	for (rapidjson::Value& styleJson : value["styles"].GetArray()) {
		speaker.styles.push_back(JsonToSpeakerStyle(styleJson));
	}

	if (value.HasMember("version")) {
		speaker.version = value["version"].GetString();
	}

	return speaker;
}


//
rapidjson::Document SpeakerInfoToJson(SpeakerInfo& speakerInfo) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember("policy", rapidjson::Value(speakerInfo.policy.c_str(), allocator).Move(), allocator);
	document.AddMember("portrait", rapidjson::Value(speakerInfo.portrait.c_str(), allocator).Move(), allocator);

	rapidjson::Value styleInfos(rapidjson::kArrayType);
	for (StyleInfo styleInfo : speakerInfo.styleInfos) {
		rapidjson::Value styleInfoJson(rapidjson::kObjectType);

		styleInfoJson.AddMember("id", styleInfo.id, allocator);
		styleInfoJson.AddMember("icon", rapidjson::Value(styleInfo.icon.c_str(), allocator).Move(), allocator);
		if (styleInfo.portrait.has_value()) {
			styleInfoJson.AddMember("portrait", rapidjson::Value(styleInfo.portrait.value().c_str(), allocator).Move(), allocator); {
			}
		}
		rapidjson::Value voiceSamplesJson(rapidjson::kArrayType);
		for (std::string voiceSample : styleInfo.voiceSamples) {
			voiceSamplesJson.PushBack(rapidjson::Value(voiceSample.c_str(), allocator).Move(), allocator);
		}
		styleInfoJson.AddMember("voice_samples", voiceSamplesJson, allocator);
		styleInfos.PushBack(styleInfoJson, allocator);
	}
	document.AddMember("style_infos", styleInfos, allocator);

	return document;

};
SpeakerInfo JsonToSpeakerInfo(rapidjson::Value& value) {
	SpeakerInfo speakerInfo;

	speakerInfo.policy = value["policy"].GetString();
	speakerInfo.portrait = value["portrait"].GetString();
	for (rapidjson::Value& styleInfoJson : value["style_infos"].GetArray()) {
		speakerInfo.styleInfos.push_back(JsonToStyleInfo(styleInfoJson));
	}
	return speakerInfo;
};

//
rapidjson::Document SpeakerStyleToJson(SpeakerStyle& speakerStyle) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember("name", rapidjson::Value(speakerStyle.name.c_str(), allocator).Move(), allocator);
	document.AddMember("id", speakerStyle.id, allocator);

	return document;
};
SpeakerStyle JsonToSpeakerStyle(rapidjson::Value& value) {
	SpeakerStyle speakerStyle;

	speakerStyle.name = value["name"].GetString();
	speakerStyle.id = value["id"].GetInt();

	return speakerStyle;
};


rapidjson::Document SpeakerSupportedFeaturesToJson(SpeakerSupportedFeatures& speakerSupportedFeatures) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	if (speakerSupportedFeatures.permittedSynthesisMorphing.has_value()) {
		document.AddMember("permitted_synthesis_morphing", rapidjson::Value(speakerSupportedFeatures.permittedSynthesisMorphing.value().c_str(), allocator).Move(), allocator);
	}
	return document;
};
SpeakerSupportedFeatures JsonToSpeakerSupportedFeatures(rapidjson::Value& value) {
	SpeakerSupportedFeatures speakerSupportedFeatures;
	if (value.HasMember("permitted_synthesis_morphing")) {
		speakerSupportedFeatures.permittedSynthesisMorphing = value["permitted_synthesis_morphing"].GetString();
	}
	return speakerSupportedFeatures;
};


rapidjson::Document StyleInfoToJson(StyleInfo& styleInfo) {
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember("id", styleInfo.id, allocator);
	document.AddMember("icon", rapidjson::Value(styleInfo.icon.c_str(), allocator).Move(), allocator);
	if (styleInfo.portrait.has_value()) {
		document.AddMember("portrait", rapidjson::Value(styleInfo.portrait.value().c_str(), allocator).Move(), allocator);
	}
	rapidjson::Value voiceSamplesJson(rapidjson::kArrayType);
	for (std::string voiceSample : styleInfo.voiceSamples) {
		voiceSamplesJson.PushBack(rapidjson::Value(voiceSample.c_str(), allocator).Move(), allocator);
	}
	document.AddMember("voice_samples", voiceSamplesJson, allocator);
	return document;
};
StyleInfo JsonToStyleInfo(rapidjson::Value& value) {
	StyleInfo styleInfo;
	
	styleInfo.id = value["id"].GetInt();
	styleInfo.icon = value["icon"].GetString();
	if (value.HasMember("portrait")) {
		styleInfo.portrait = value["portrait"].GetString();
	}
	for (rapidjson::Value& voiceSampleJson : value["voice_samples"].GetArray()) {
		styleInfo.voiceSamples.push_back(voiceSampleJson.GetString());
	}
	return styleInfo;
};


/*
rapidjson::Document SupportedDevicesInfoToJson(SupportedDevicesInfo& supportedDevicesInfo);
SupportedDevicesInfo JsonToSupportedDevicesInfo(rapidjson::Document& document);




rapidjson::Document SupportedFeaturesToJson(SupportedFeatures& supportedFeatures);
SupportedFeatures JsonToSupportedFeatures(rapidjson::Document& document);


rapidjson::Document UpdateInfoToJson(UpdateInfo& updateInfo);
UpdateInfo JsonToUpdateInfo(rapidjson::Document& document);



rapidjson::Document UserDictWordToJson(UserDictWord& userDictWord);
UserDictWord JsonToUserDictWord(rapidjson::Document& document);


rapidjson::Document UserDictToJson(UserDict& userDict);
UserDict JsonToUserDict(rapidjson::Document& document);



rapidjson::Document ValidationErrorToJson(ValidationError& validationError);
ValidationError JsonToValidationError(rapidjson::Document& document);
*/