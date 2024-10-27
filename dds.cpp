#include <iostream>
#include <filesystem>
#include <chrono>

int main() {
    // input folder
    std::filesystem::path inputFolder = "input";

    // output folder
    std::filesystem::path outputFolder = "output";


    auto start2 = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: starts time for general function


    for (const auto& entry : std::filesystem::directory_iterator(inputFolder)) {
        if (entry.is_regular_file()) {
            // Get the file path
            std::filesystem::path filePath = entry.path();
            std::cout << "Found file: " << filePath << std::endl;

            auto start = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: starts time

            std::string inputfolderchar = inputFolder.string();
            std::string filepathchar = filePath.filename().string(); // This works
            std::string filepathchar2 = filePath.filename().stem().string(); // This works
            std::string outputfolderchar = outputFolder.string();

            // wtf
            std::string command = "magick " + inputfolderchar + "/" + filepathchar + " " + outputfolderchar + "/" + filepathchar2 + ".dds";

            // should work
            std::system(command.c_str());

            auto end = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: ends time
            std::chrono::duration<double> duration = end - start; // CHRONO CLOCK: calculates the time

            std::cout << "Converted in " << std::setprecision(5) << duration.count() << " seconds." << std::endl;
        }
    }

    auto end2 = std::chrono::high_resolution_clock::now(); // CHRONO CLOCK: starts time for general function
    std::chrono::duration<double> duration = end2 - start2; // CHRONO CLOCK: calculates time for general function
    std::cout << "Converted all files in " << std::setprecision(5) << duration.count() << " seconds." << std::endl;
    return 0;
}
