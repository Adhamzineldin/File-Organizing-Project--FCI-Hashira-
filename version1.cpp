#include <iostream>
#include <unordered_map>
#include <filesystem>

using namespace std;

//NAME DEFINITIONS
string image = "images";
string document = "documents";
string audio = "audios";
string video = "videos";
string others = "others";


//FUNCTION DEFINITIONS
string getCategory(const string& extension) {
    static unordered_map<std::string, std::string> categories = {
        {".jpg", image}, {".jpeg", image}, {".png", image}, {".gif", image},
        {".bmp", image}, {".tiff", image}, {".txt", document}, {".pdf", document},
        {".doc", document}, {".docx", document}, {".xls", document}, {".xlsx", document},
        {".ppt", document}, {".pptx", document}, {".mp3", audio}, {".wav", audio},
        {".flac", audio}, {".mp4", video}, {".mkv", video}, {".avi", video},
        {".mov", video}
    };

    auto it = categories.find(extension);
    if (it != categories.end()) {
        return it->second;
    }
    return others;
}


void organizeDirectory(const string& path) {
    cout << "Enter the directory path: ";
    string directoryPath;
    getline(cin, directoryPath);

    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (filesystem::is_regular_file(entry.path())) {

            string extension = entry.path().extension().string();
            string category = getCategory(extension);

            filesystem::path categoryPath = directoryPath + "/" + category;
            if (!filesystem::exists(categoryPath)) {
                filesystem::create_directory(categoryPath);
            }

            filesystem::path newFilePath = categoryPath / entry.path().filename();
            filesystem::rename(entry.path(), newFilePath);
            cout << "Moved " << entry.path().filename() << " to " << category << " folder." << endl;
        }
    }

    cout << "Directory organized successfully." << endl;
}


int main() {
    organizeDirectory(".");
    return 0;
}

// this comment to add verison commit :)
