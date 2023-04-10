#include "DockerApi.h"


size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userData) {
    ((std::string*) userData)->append(ptr, size * nmemb);
    return size * nmemb;
}


int DockerApi::getPresets(void)
{
    CURL* curl;
    CURLcode res;
    std::string response;
    rapidjson::Document document;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:50021/accent_phrases?text=A&speaker=1&is_kana=false");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
    }

    return 0;
}