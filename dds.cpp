#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip> // Include this header for std::setprecision

std::filesystem::path filePath;

const std::filesystem::path inputFolder = "input";
const std::filesystem::path outputFolder = "output";

std::string genCmd(const std::filesystem::path filePath) {    
    #if __linux__
    std::string command = "magick " + inputFolder.string() + "/'" + filePath.filename().string() + "' " + outputFolder.string() + "/'" + filePath.filename().stem().string() + ".dds'";
    #elif _WIN32
    std::string command = "magick \"" + inputFolder.string() + "\\" + filePath.filename().string() + "\" \"" +
                            outputFolder.string() + "\\" + filePath.filename().stem().string() + ".dds\"";
    #endif
    return command;
}

int main() {
    auto start2 = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: starts time for general function

    for (const auto& entry : std::filesystem::directory_iterator(inputFolder)) {
        if (entry.is_regular_file()) {
            // Get the file path
            std::filesystem::path filePath = entry.path();

            // don't bitch about gitignore file please!!!
            if (filePath.filename() == ".gitignore") {
                continue;
            }

            std::cout << "Found file: " << filePath << "\n";

            auto start = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: starts time

            std::string command = genCmd(filePath);
            std::system(command.c_str());

            auto end = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: ends time
            std::chrono::duration<double> duration = end - start; // CHRONO CLOCK: calculates the time

            std::cout << "Converted in " << std::setprecision(5) << duration.count() << " seconds." << "\n";
        }
    }

    auto end2 = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: starts time for general function
    std::chrono::duration<double> duration = end2 - start2; // CHRONO CLOCK: calculates time for general function

    std::cout << "Converted all files in " << std::setprecision(5) << duration.count() << " seconds." << "\n";

    std::cout << "Press Enter to exit...";
    std::cin.ignore();

    return 0;
}
