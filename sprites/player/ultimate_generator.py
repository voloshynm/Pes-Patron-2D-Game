import os
from PIL import Image

# Define valid characters for color representation
VALID_CHARS = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?/~`'

def rgb_to_char(rgb, color_map, char_index):
    """ Convert RGB value to a character from VALID_CHARS """
    if rgb in color_map:
        return color_map[rgb]
    if char_index >= len(VALID_CHARS):
        raise ValueError("Not enough unique characters to represent all colors.")
    char = VALID_CHARS[char_index]
    color_map[rgb] = char
    return char

def convert_png_to_xpm(png_path, xpm_path):
    """ Convert a single PNG file to XPM format """
    with Image.open(png_path) as img:
        img = img.convert("RGB")
        width, height = img.size
        pixels = img.load()

        # Collect unique colors used in the image
        color_map = {}
        used_colors = set()
        for y in range(height):
            for x in range(width):
                color = pixels[x, y]
                used_colors.add(color)
        
        # Map colors to characters
        color_list = list(used_colors)
        for char_index, color in enumerate(color_list):
            rgb_to_char(color, color_map, char_index)

        # Prepare XPM data
        header = f'/* XPM */\nstatic char * image[] = {{\n'
        header += f'/* width height num_colors chars_per_pixel */\n'
        header += f'"{width} {height} {len(color_map)} 1",\n'

        # Add color definitions
        for color, char in color_map.items():
            hex_color = ''.join(f'{c:02x}' for c in color)
            header += f'"{char} c #{hex_color}",\n'

        # Add pixel data
        data = []
        for y in range(height):
            row = ''.join(color_map[pixels[x, y]] for x in range(width))
            data.append(f'"{row}",\n')

        # Combine all parts and save
        with open(xpm_path, 'w') as xpm_file:
            xpm_file.write(header)
            xpm_file.writelines(data)
            xpm_file.write('};\n')

def get_center_position(background_size, overlay_size):
    """ Calculate the center position for the overlay """
    bg_width, bg_height = background_size
    ov_width, ov_height = overlay_size
    return ((bg_width - ov_width) // 2, (bg_height - ov_height) // 2)

def overlay_images(background_path, overlay_path, output_path):
    """ Overlay images with the overlay centered """
    # Open the background and overlay images
    background = Image.open(background_path).convert('RGBA')
    overlay = Image.open(overlay_path).convert('RGBA')
    
    # Prepare the overlay image with transparency
    overlay_with_transparency = Image.new('RGBA', background.size, (0, 0, 0, 0))
    overlay_with_transparency.paste(overlay, get_center_position(background.size, overlay.size), overlay)
    
    # Combine the background and overlay images
    combined = Image.alpha_composite(background, overlay_with_transparency)
    
    # Save the resulting image
    combined.save(output_path, 'PNG')

def process_directory(root_dir):
    """ Process all PNG files in the given directory and subdirectories """
    background_image_path = os.path.join(root_dir, 'source.png')

    for subdir, _, files in os.walk(root_dir):
        for file in files:
            if file.lower().endswith('.png') and file.lower() != 'source.png':
                png_path = os.path.join(subdir, file)
                # Overlay source.png with the current PNG file
                overlay_images(background_image_path, png_path, png_path)
                print(f'Overlayed source.png with {png_path}')
                # Convert the new PNG to XPM
                xpm_path = os.path.splitext(png_path)[0] + '.xpm'
                try:
                    convert_png_to_xpm(png_path, xpm_path)
                    print(f'Converted {png_path} to {xpm_path}')
                except ValueError as e:
                    print(f'Error converting {png_path}: {e}')

if __name__ == '__main__':
    root_directory = '.'  # Set the root directory to process
    process_directory(root_directory)
