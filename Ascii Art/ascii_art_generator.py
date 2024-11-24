# MIT License
# Copyright (c) 2024 Gaurav Suresh Gavhane
# See the LICENSE file for full details.

from PIL import Image
import os

# -------------------------------------------------------------------------------------
# Function: pixel_to_ascii
# Description: Maps a pixel value (0-255) to an ASCII character based on density.
# Input: pixel_value (int) - Grayscale pixel value (0-255).
# Output: str - Corresponding ASCII character.
# -------------------------------------------------------------------------------------

def pixel_to_ascii(pixel_value):
    ascii_chars = "@%#*+=-:. "  # Dense to less dense
    return ascii_chars[pixel_value * (len(ascii_chars) - 1) // 255]

# -------------------------------------------------------------------------------------
# Function: convert_image_to_ascii
# Description: Converts an image to ASCII art.
# Input:
#   image_path (str) - Path to the input image file.
#   width (int) - Desired width of the ASCII art (default is 80).
# Output: str - Generated ASCII art as a string.
# -------------------------------------------------------------------------------------

def convert_image_to_ascii(image_path, width=80):
    try:
        # Open the image and convert it to grayscale
        img = Image.open(image_path).convert("L")
        
        # Calculate height proportional to the new width
        aspect_ratio = img.height / img.width
        new_height = int(aspect_ratio * width * 0.55)  # Adjust for font aspect ratio
        img = img.resize((width, new_height))

        # Convert each pixel to an ASCII character
        ascii_art = ""
        for y in range(img.height):
            line = ""
            for x in range(img.width):
                pixel_value = img.getpixel((x, y))
                ascii_character = pixel_to_ascii(pixel_value)
                line = line + ascii_character
            ascii_art = ascii_art + line + "\n"

        return ascii_art
    except Exception as e:
        return f"Error processing the image: {e}"

# -------------------------------------------------------------------------------------
# Function: is_valid_image_format
# Description: Checks if the file has a valid image extension.
# Input: file_name (str) - Name of the file.
# Output: bool - True if the file extension is valid, False otherwise.
# -------------------------------------------------------------------------------------

def is_valid_image_format(file_name):
    valid_extensions = {".jpg", ".jpeg", ".png"}
    return os.path.splitext(file_name)[1].lower() in valid_extensions

# -------------------------------------------------------------------------------------
# Function: add_extension_if_missing
# Description: Adds a file extension to a file name if it is missing.
# Input:
#   file_name (str) - The input file name.
#   default_extension (str) - The default extension to add.
# Output: str - File name with the added extension (if missing).
# -------------------------------------------------------------------------------------

def add_extension_if_missing(file_name, default_extension):
    if not file_name.endswith(default_extension):
        return f"{file_name}{default_extension}"
    return file_name

# -------------------------------------------------------------------------------------
# Function: display_user_manual
# Description: Displays the user manual for the program.
# Input: None
# Output: None
# -------------------------------------------------------------------------------------

def display_user_manual():
    print("\n------------------- User Manual -------------------")
    print("| 1. Supported image formats: .jpg, .jpeg, .png   |")
    print("| 2. Provide the file path to the image.          |")
    print("| 3. Optionally save the ASCII art to a text file.|")
    print("| 4. Optionally save the ASCII art as an image.   |")
    print("| 5. View ASCII art directly in the terminal.     |")
    print("| 6. Type 'exit' anytime to quit the program.     |")
    print("--------------------------------------------------\n")


def main():
    print("\n--------------------------------------------------")
    print("|             ASCII Art Generator! 🎨            |")
    print("--------------------------------------------------")
    print("| Convert your images into stunning ASCII art.   |")
    print("--------------------------------------------------\n")
    
    # Display the user manual
    display_user_manual()

    while True:
        # Prompt the user to enter the image path
        image_path = input("Enter the path to the image file (supported formats: .jpg, .jpeg, .png): ").strip()

        if image_path.lower() == "exit":
            print("Thank you for using the ASCII Art Generator! Goodbye. 😊")
            break

        # Validate file existence and format
        if not os.path.exists(image_path):
            print(f"Error: The file '{image_path}' does not exist. Please try again.")
            continue

        if not is_valid_image_format(image_path):
            print("Error: Only .jpg, .jpeg, and .png files are supported. Please try again.")
            continue

        # Generate ASCII art
        ascii_art = convert_image_to_ascii(image_path)

        # Save ASCII art to a text file (optional)
        save_txt = input("\nEnter the name of the output text file (e.g., ascii_art.txt), or press Enter to skip: ").strip()
        if save_txt:
            save_txt = add_extension_if_missing(save_txt, ".txt")
            with open(save_txt, "w") as file:
                file.write(ascii_art)
            print(f"ASCII art has been saved to '{save_txt}'.")

        # Save ASCII art as an image (optional)
        save_img = input("\nEnter the name of the output image file (e.g., ascii_art.jpg), or press Enter to skip: ").strip()
        if save_img:
            save_img = add_extension_if_missing(save_img, ".jpg")
            try:
                # Create a blank white image to draw ASCII characters
                font_size = 10
                img_width = len(ascii_art.split("\n")[0]) * font_size
                img_height = len(ascii_art.split("\n")) * font_size
                output_img = Image.new("RGB", (img_width, img_height), "white")

                # Draw ASCII art onto the image
                from PIL import ImageDraw, ImageFont
                draw = ImageDraw.Draw(output_img)
                font = ImageFont.load_default()  # Default font
                y_offset = 0
                for line in ascii_art.split("\n"):
                    draw.text((0, y_offset), line, fill="black", font=font)
                    y_offset = y_offset + font_size

                output_img.save(save_img)
                print(f"ASCII art image has been saved to '{save_img}'.")
            except Exception as e:
                print(f"Error saving ASCII art as image: {e}")

        # Option to display ASCII art in the terminal
        show_art = input("\nDo you want to display the ASCII art in the terminal? (Y/N): ").strip().lower()
        if show_art == "y":
            print("\nHere is your ASCII art:\n")
            print(ascii_art)

        # Ask user if they want to process another image
        continue_choice = input("\nDo you want to process another image? (Y/N): ").strip().lower()
        if continue_choice != "y":
            print("Thank you for using the ASCII Art Generator! Goodbye. 😊")
            break

if __name__ == "__main__":
    main()
