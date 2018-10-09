#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include "Json.hpp"
#include "Api.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace nlohmann;

namespace
{
size_t callback(
    const char *in,
    size_t size,
    size_t num,
    string *out)
{
    const size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}
}

const string BASE_URL = "https://polecat.me/api/gameSave";

Api::Api()
{
    username = "";
    password = "";
}

Api::Api(string username, string password)
{

    CURL *curl = curl_easy_init();
    char *escapedName = curl_easy_escape(curl, username.c_str(), username.length());
    char *escapedPassword = curl_easy_escape(curl, password.c_str(), password.length());
    this->username = string(escapedName);
    this->password = string(escapedPassword);
}

string Api::getGameSave()
{
    const string getUrl = BASE_URL + "?" + "username=" + username + "&" + "password=" + password;
    const string url(getUrl);

    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    int *httpCode = new int(0);
    unique_ptr<string> httpData(new string());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, httpCode);
    curl_easy_cleanup(curl);

    if (*httpCode != 200)
    {
        cout << "Status code on get: " << *httpCode << endl;
        cout << *(httpData.get()) << endl;
        return "";
    }

    json j = json::parse(*(httpData.get()));
    if (j["gameSave"].is_null())
    {
        cout << "game save was null" << endl;
        return "";
    }
    return j["gameSave"];
}

bool Api::setGameSave(string save)
{
    const string getUrl = BASE_URL + "?" + "username=" + username + "&" + "password=" + password + "&" + "gameSave=" + save;
    const string url(getUrl);

    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    int *httpCode = new int(0);
    unique_ptr<string> httpData(new string());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, httpCode);
    curl_easy_cleanup(curl);

    if (*httpCode != 200)
    {
        cout << "Status code on post: " << *httpCode << endl;
        cout << *(httpData.get()) << endl;
        return false;
    }
    else
    {
        return true;
    }
}