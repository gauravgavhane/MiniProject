
██▓▒­░⡷⠂  ASCII Art Generator ⠐⢾░▒▓██

Use Case of the Application :

The ASCII Art Generator is a tool designed to convert images into ASCII art, a form of visual art created using characters from the ASCII standard. This application is useful for :
    - Creating artistic renditions of images in ASCII text format.
    - Generating ASCII-styled image representations for fun, presentations, or unique projects.
    - Saving the ASCII output as both a text file and an image file for further use.
------------------------------------------------------------------------------------------------------

Requirements : 

Before Running the Program
1. Operating System : Works on Linux, macOS, and Windows.
2. C++ Compiler : Any modern compiler that supports C++11 or later

3. OpenCV Library : Ensure OpenCV is installed on your system.
    On Ubuntu:   sudo apt update
                    sudo apt install libopencv-dev

    On macOS (via Homebrew):    brew install opencv

    On Windows: Download and install OpenCV from OpenCV official site.

4. Filesystem Library : Ensure your compiler supports the <filesystem> library (usually available in C++17 and later)
----------------------------------------------------------------------------------------------------------------------

How to Use : 
1. Launch the Program
   Run the program using a C++ compiler or IDE that supports OpenCV.

2. Enter the Image File Name
   Provide the file name (with extension) of the image you want to convert. Supported formats are .jpg .jpeg .png
   Example: input_image.jpg

3. Enter the Output Text File Name (Optional)
   Provide a file name to save the ASCII art in text format (e.g., ascii_art.txt). If you don't want to save the ASCII text file, press Enter to skip.

4. Enter the Output Image File Name (Optional)
   Provide a file name to save the ASCII art as an image (e.g., ascii_art.jpg). If you don't want to save the ASCII art as an image, press Enter to skip

5. View the Output
   The ASCII art is displayed in the terminal. If you provided file names, the results are saved to those files.

6. Repeat or Exit
   You can process another image or type exit to quit the application.
--------------------------------------------------------------------------------------------------------

Example : 

INPUT : 
Suppose you have an image file named sample_image.jpg.
Run the program and provide the following details:

• Image File:        sample_image.jpg
• Output Text File:  ascii_output.txt
• Output Image File: ascii_art.jpg

Command (if using g++ to compile and run): 
g++ ascii_art_generator.cpp -o ascii_art -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
./ascii_art

------------ Sample Interaction ------------

Enter the name of the image file (supported formats: .jpg, .jpeg, .png): sample_image.jpg
Enter the name of the output text file (e.g., ascii_art.txt), or press Enter to skip: ascii_output.txt
Enter the name of the output image file (e.g., ascii_art.jpg) or press Enter to skip: ascii_art.jpg

ASCII art has been saved to: ascii_output.txt
ASCII art image has been saved to: ascii_art.jpg

Do you want to process another image? (Y/N): n
Goodbye! Thank you for using the ASCII Art Generator.

------------ Output ------------

1. Text File : The ASCII art representation is saved in ascii_output.txt
2. Image File : The ASCII art is saved as an image in ascii_art.jpg.
3. Console : The ASCII art is displayed in the terminal for immediate viewing.

Enjoy creating ASCII art シ