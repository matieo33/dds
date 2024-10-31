#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip> // std::setprecision
#include <set>

std::filesystem::path filePath;
bool success;

const std::filesystem::path inputFolder = "input";
const std::filesystem::path outputFolder = "output";

std::string genCmd(const std::filesystem::path filePath) {
    std::string command;    
    std::string fileExt = filePath.extension().string();
    const std::set<std::string> supportedExt = {".png", ".jpg", ".jpeg", ".bmp", ".tga", ".psd"};

    #if __linux__
    if (supportedExt.find(fileExt) != supportedExt.end()) { // Is supported extension (to dds)
        command = "magick " + inputFolder.string() + "/'" + filePath.filename().string() + "' " + outputFolder.string() + "/'" + filePath.filename().stem().string() + ".dds'";
        success = true;
        return command;
    }
    else { // Neither. Error.
        success = false;
        return command;
    }

    #elif _WIN32
    if (supportedExt.find(fileExt) != supportedExt.end()) { // Is supported extension (to dds)
        command = "magick \"" + inputFolder.string() + "\\" + filePath.filename().string() + "\" \"" +
                            outputFolder.string() + "\\" + filePath.filename().stem().string() + ".dds\"";
        success = true;
        return command;                    
    }
    else { // Neither. Error.
        success = false;
        return command;
    }
    #endif
}

int convert() {
    auto start2 = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: starts time for general function

    std::cout << "FILE" << std::setw(52) << "STATUS" << std::setw(52) << "TIME\n\n";

    for (const auto& entry : std::filesystem::directory_iterator(inputFolder)) {
        if (entry.is_regular_file()) {
            // Get the file path
            std::filesystem::path filePath = entry.path();

            // Shush when reading .gitignore file
            if (filePath.filename() == ".gitignore") {
                continue;
            }

            auto start = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: starts time

            std::string command = genCmd(filePath); // see std::string genCmd
            std::system(command.c_str());

            auto end = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: ends time
            std::chrono::duration<double> duration = end - start; // CHRONO CLOCK: calculates the time

            std::cout << std::left << std::setw(50) << filePath.filename().string() 
            << std::setw(50) << (success ? "success" : "failure, wrong file format or corrupted file") 
            << std::setw(50) << std::setprecision(5) 
            << duration.count() << "\n";
        }
    }

    auto end2 = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: ends time for general function
    std::chrono::duration<double> duration = end2 - start2; // CHRONO CLOCK: calculates time for general function

    std::cout << "\nConverted all files in " << std::setprecision(5) << duration.count() << " seconds." << "\n";

    return 0;
}

int main() {
    convert();

    std::cout << "Press Enter to exit...";
    std::cin.ignore();

    return 0;
}
