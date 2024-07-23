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

def process_directory(root_dir):
    """ Process all PNG files in the given directory and subdirectories """
    for subdir, _, files in os.walk(root_dir):
        for file in files:
            if file.lower().endswith('.png'):
                png_path = os.path.join(subdir, file)
                xpm_path = os.path.splitext(png_path)[0] + '.xpm'
                try:
                    convert_png_to_xpm(png_path, xpm_path)
                    print(f'Converted {png_path} to {xpm_path}')
                except ValueError as e:
                    print(f'Error converting {png_path}: {e}')

if __name__ == '__main__':
    root_directory = '.'  # Set the root directory to process
    process_directory(root_directory)

