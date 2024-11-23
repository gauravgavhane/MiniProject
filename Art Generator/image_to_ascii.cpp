#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>
#include <algorithm>
#include <filesystem> // For file existence check
namespace fs = std::filesystem;

///////////////////////////////////////////////////////////////////////////////////////
//
// Function Name : pixelToASCII
// Description   : Function to map pixel value to an ASCII character.
// Input         : Integer (pixelValue) - Grayscale intensity value of a pixel (0-255).
// Output        : Character - Corresponding ASCII character based on pixel intensity.
//
///////////////////////////////////////////////////////////////////////////////////////

char pixelToASCII(int pixelValue) 
{
    const std::string asciiChars = "@%#*+=-:. ";  // Dense to less dense characters
    return asciiChars[(pixelValue * (asciiChars.length() - 1)) / 255];  // Map pixel to ASCII
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function Name : isValidImageFormat
// Description   : Function to validate the file format of the provided image.
// Input         : const std::string &fileName - Name of the file with extension.
// Output        : Boolean - True if the file has a valid image extension (.jpg, .jpeg, .png), False otherwise.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isValidImageFormat(const std::string &fileName) 
{
    const std::string validExtensions[] = {".jpg", ".jpeg", ".png"};
    std::string fileExtension = fileName.substr(fileName.find_last_of('.'));
    std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
    
    for (const auto &ext : validExtensions) 
    {
        if (fileExtension == ext) {
            return true;
        }
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
// Function Name : displayUserManual
// Description   : Function to display instructions and usage guidelines for the application.
// Input         : None
// Output        : None (Instructions printed to the console).
//
/////////////////////////////////////////////////////////////////////////////////////////////

void displayUserManual() 
{
    std::cout << "\n██▓▒­░⡷⠂  User Manual  ⠐⢾░▒▓██ \n";
    std::cout << "1. Enter the name of the image file (with extension .jpg, .jpeg, or .png).\n";
    std::cout << "2. Enter the output text file name (e.g., ascii_art.txt). If left blank, no ASCII art file will be saved\n";
    std::cout << "3. Optionally, enter the output image file name (e.g., ascii_art.jpg) to save the ASCII art as an image\n";
    std::cout << "4. Type 'exit' anytime to quit the program.\n";
    std::cout << "---------------------------------------------------------------------------------------------------------\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function Name : imageToASCII
// Description   : Function to convert an image to ASCII art and save it as text or an image file.
// Input         : - const std::string &imagePath - Path to the input image file.
//                 - const std::string &outputFile - Name of the output text file for ASCII art (optional).
//                 - const std::string &outputImageFile - Name of the output image file for ASCII art (optional).
// Output        : None (ASCII art is saved to the specified files if provided).
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void imageToASCII(const std::string &imagePath, const std::string &outputFile, const std::string &outputImageFile) 
{
    // Load the image in grayscale mode
    cv::Mat img = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    // Check if the image is successfully loaded
    if (img.empty()) 
    {
        std::cerr << "Error: Could not open or find the image: " << imagePath << std::endl;
        return;
    }

    // Resize image for better terminal visualization
    cv::resize(img, img, cv::Size(img.cols / 8, img.rows / 8));

    // If the output text file is provided, create an output file stream for saving the ASCII art
    std::ofstream fileOut;
    if (!outputFile.empty()) 
    {
        fileOut.open(outputFile);
        if (!fileOut.is_open()) 
        {
            std::cerr << "Error: Could not open the output file: " << outputFile << std::endl;
            return;
        }
    }

    // Create a blank canvas for saving ASCII art as an image
    int fontSize = 10;
    cv::Mat asciiImage = cv::Mat::zeros(img.rows * fontSize, img.cols * fontSize, CV_8UC3);
    asciiImage.setTo(cv::Scalar(255, 255, 255)); // Set white background
    cv::Scalar textColor = cv::Scalar(0, 0, 0); // Black text

    // Loop through each pixel, convert to ASCII, save to file and render on canvas
    for (int y = 0; y < img.rows; y++) 
    {
        for (int x = 0; x < img.cols; x++) 
        {
            int pixelValue = img.at<uchar>(y, x);
            char asciiChar = pixelToASCII(pixelValue);

            // Write ASCII character to file if provided
            if (!outputFile.empty()) {
                fileOut << asciiChar;
            }

            // Draw the ASCII character on the canvas
            cv::putText(asciiImage, std::string(1, asciiChar), cv::Point(x * fontSize, (y + 1) * fontSize),
                        cv::FONT_HERSHEY_SIMPLEX, 0.4, textColor, 1);
        }

        if (!outputFile.empty()) 
        {
            fileOut << '\n';
        }
    }

    if (!outputFile.empty()) 
    {
        fileOut.close();
        std::cout << "ASCII art has been saved to: " << outputFile << std::endl;
    }

    if (!outputImageFile.empty()) 
    {
        cv::imwrite(outputImageFile, asciiImage);
        std::cout << "ASCII art image has been saved to: " << outputImageFile << std::endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Function Name : addExtensionIfMissing
// Description   : Function to append a file extension to a file name if missing.
// Input         : 
//                 - const std::string &fileName - File name provided by the user.
//                 - const std::string &extension - Extension to be appended (e.g., ".txt").
// Output        : std::string - Updated file name with extension.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string addExtensionIfMissing(const std::string &fileName, const std::string &extension) 
{
    if (fileName.find(extension) == std::string::npos) 
    {
        return fileName + extension;
    }
    return fileName;
}

int main() 
{
    std::string imagePath, outputFile, outputImageFile, userChoice;

    // Display the User Manual
    std::cout << "\n真の芸術は爆発だ|真の芸術は爆発だ|真の芸術は爆発だ|真の芸術は爆発だ     \n";
    std::cout << "漢字                                                           本日     \n";
    std::cout << "日本               Welcome to ASCII Art Generator !            漢字     \n";
    std::cout << "漢字                                                           本日     \n";
    std::cout << "真の芸術は爆発だ|真の芸術は爆発だ|真の芸術は爆発だ|真の芸術は爆発だ     \n\n";

    // Show user manual initially
    displayUserManual();

    do 
    {
        std::cout << "\nEnter the name of the image file (supported formats: .jpg, .jpeg, .png): ";
        std::cin >> imagePath;

        if (imagePath == "exit") 
        {
            std::cout << "Exiting the program...\n";
            break;
        }

        if (imagePath.find('.') == std::string::npos) 
        {
            imagePath += ".jpg";
            std::cout << "No extension provided. Assuming .jpg format.\n";
        }

        if (!isValidImageFormat(imagePath)) 
        {
            std::cerr << "Error: Unsupported file format. Please use .jpg, .jpeg, or .png.\n";
            continue;
        }

        // Check if the file exists
        if (!fs::exists(imagePath)) 
        {
            std::cerr << "Error: File not available or check the filename: " << imagePath << std::endl;
            continue;
        }

        std::cout << "Enter the name of the output text file (e.g., ascii_art.txt), or press Enter to skip: ";
        std::cin.ignore();
        std::getline(std::cin, outputFile);

        if (!outputFile.empty()) 
        {
            outputFile = addExtensionIfMissing(outputFile, ".txt");
        }

        std::cout << "Enter the name of the output image file (e.g., ascii_art.jpg) or press Enter to skip : ";
        std::getline(std::cin, outputImageFile);

        if (!outputImageFile.empty()) 
        {
            outputImageFile = addExtensionIfMissing(outputImageFile, ".jpg");
        }

        imageToASCII(imagePath, outputFile, outputImageFile);

        std::cout << "\nDo you want to process another image? (Y/N): ";
        std::cin >> userChoice;

        std::transform(userChoice.begin(), userChoice.end(), userChoice.begin(), ::tolower);

    } 
    while (userChoice == "y");

    std::cout << "Goodbye! Thank you for using the ASCII Art Generator\n";

    return 0;
}
