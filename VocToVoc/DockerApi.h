#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include "VoiceVoxClasses.h"

#define CURL_STATICLIB
#include <curl/curl.h>

class DockerApi
{
public:
	static int getPresets(void);
}; // class DockerApi