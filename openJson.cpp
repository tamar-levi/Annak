#include "openJson.h"

json openJson::file = json();
std::mutex openJson::mutex;



json openJson::GetFile()
{

    std::lock_guard<std::mutex> lock(mutex);
    if (file.empty())
    {
        ifstream ifs("JSON.json");
        if (!ifs.is_open())
        {
            throw "Failed to open file.";
        }
        string content((istreambuf_iterator<char>(ifs)),
            (istreambuf_iterator<char>()));
        file = json::parse(content);
        ifs.close();
    }
    return file;
}
