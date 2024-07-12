import sys
import os
from PIL import Image

def generate_xpm(sprite, filename):
    """Generate a simple XPM file from a Pillow image."""
    width, height = sprite.size
    pixels = sprite.load()
    
    colors = {}
    color_codes = []
    color_index = 0

    def to_hex(color):
        return "#{:02x}{:02x}{:02x}".format(color[0], color[1], color[2])

    # First pass to gather colors
    for y in range(height):
        for x in range(width):
            color = pixels[x, y][:3]  # Discard alpha channel if present
            if color not in colors:
                color_code = chr(33 + color_index)  # Start from '!'
                colors[color] = color_code
                color_codes.append(f"{color_code} c {to_hex(color)}")
                color_index += 1

    # Header
    xpm_data = [
        f"/* XPM */",
        f"static char * xpm[] = {{",
        f"\"{width} {height} {len(colors)} 1\","
    ] + [f"\"{color_code}\"," for color_code in color_codes]

    # Image data
    for y in range(height):
        row = ''.join(colors[pixels[x, y][:3]] for x in range(width))
        xpm_data.append(f"\"{row}\",")

    xpm_data[-1] = xpm_data[-1][:-1]  # Remove last comma
    xpm_data.append("};")

    # Write to file
    with open(filename, 'w') as f:
        f.write("\n".join(xpm_data))

def split_sprites(input_image, output_folder, sprite_size):
    # Open the image
    img = Image.open(input_image)

    # Get dimensions of the image
    width, height = img.size

    # Calculate number of sprites horizontally and vertically
    num_sprites_x = width // sprite_size
    num_sprites_y = height // sprite_size

    # Ensure output folder exists
    os.makedirs(output_folder, exist_ok=True)

    # Loop through each sprite and save it
    for y in range(num_sprites_y):
        # Create the subdirectory for the y value if it doesn't exist
        subdirectory = f"{output_folder}/{y}"
        os.makedirs(subdirectory, exist_ok=True)

        for x in range(num_sprites_x):
            # Define the region to crop
            left = x * sprite_size
            upper = y * sprite_size
            right = left + sprite_size
            lower = upper + sprite_size

            # Crop the sprite
            sprite = img.crop((left, upper, right, lower))

            # Save the sprite as PNG
            png_filename = f"{subdirectory}/{x}.png"
            sprite.save(png_filename)

            # Save the sprite as XPM
            xpm_filename = f"{subdirectory}/{x}.xpm"
            generate_xpm(sprite, xpm_filename)

if __name__ == "__main__":
    # Ensure the script is called with the correct number of arguments
    if len(sys.argv) != 2:
        print("Usage: python split_sprites.py <input_image>")
        sys.exit(1)

    # Get the input image file name from the command line argument
    input_image = sys.argv[1]

    # Generate the output folder name from the input file name
    base_name = os.path.splitext(input_image)[0]
    output_folder = base_name

    # Define the size of each sprite (32x32 pixels)
    sprite_size = 32

    # Call the function to split the sprites
    split_sprites(input_image, output_folder, sprite_size)
