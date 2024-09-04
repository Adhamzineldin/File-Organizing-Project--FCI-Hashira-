#include <iostream>
#include <unordered_map>
#include <filesystem>
#include <windows.h>
#include <fstream>

using namespace std;

//NAME DEFINITIONS
string image = "images";
string document = "documents";
string audio = "audios";;
string video = "videos";
string others = "others";

void menu();

void createSettingIfNotExists() {

    if (!filesystem::exists("./settings.txt")) {
        ofstream file("./settings.txt");
        file << "images: " << "images" << endl;
        file << "documents: " << "documents" << endl;
        file << "audios: " << "audios" << endl;
        file << "videos: " << "videos" << endl;
        file << "others: " << "others" << endl;
        file.close();
    }
}

void loadSettings() {
    ifstream file("settings.txt");
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(": ");
        string key = line.substr(0, pos);
        string value = line.substr(pos + 2);
        if (key == "images") {
            image = value;
        } else if (key == "documents") {
            document = value;
        } else if (key == "audios") {
            audio = value;
        } else if (key == "videos") {
            video = value;
        } else if (key == "others") {
            others = value;
        }
    }
    file.close();
}
void updateSettings(){
    cout << "Enter the category names for the following file types:" << endl;
    cout << "Images: ";
    getline(cin, image);
    cout << "Documents: ";
    getline(cin, document);
    cout << "Audios: ";
    getline(cin, audio);
    cout << "Videos: ";
    getline(cin, video);
    cout << "Others: ";
    getline(cin, others);
    ofstream file("settings.txt");
    file << "images: " << image << endl;
    file << "documents: " << document << endl;
    file << "audios: " << audio << endl;
    file << "videos: " << video << endl;
    file << "others: " << others << endl;
    file.close();
    loadSettings();
    menu();
}







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


void organizeDirectory() {
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
    ShellExecute(NULL, "open", directoryPath.c_str(), NULL, NULL, SW_RESTORE);
    menu();

}

void menu(){
    createSettingIfNotExists();
    loadSettings();
    cout << "1. Organize Directory" << endl;
    cout << "2. Update Settings" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore();
    switch(choice){
        case 1:
            organizeDirectory();
            break;
        case 2:
            updateSettings();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            menu();
            break;
    }
}





int main()
{
    menu();
    return 0;
}

// this comment to add verison commit :)
