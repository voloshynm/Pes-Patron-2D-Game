import os
from PIL import Image

def generate_xpm(png_filename, xpm_filename):
    """Generate a simple XPM file from a PNG image."""
    img = Image.open(png_filename)
    width, height = img.size
    pixels = img.load()

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
        "/* XPM */",
        f"static char * {os.path.splitext(os.path.basename(xpm_filename))[0]}[] = {{",
        f"\"{width} {height} {len(colors)} 1\","
    ] + [f"\"{color_code}\"," for color_code in color_codes]

    # Image data
    for y in range(height):
        row = ''.join(colors[pixels[x, y][:3]] for x in range(width))
        xpm_data.append(f"\"{row}\",")

    xpm_data[-1] = xpm_data[-1][:-1]  # Remove last comma
    xpm_data.append("};")

    # Write to file
    with open(xpm_filename, 'w') as f:
        f.write("\n".join(xpm_data))

def create_xpm_from_pngs(directory):
    for filename in os.listdir(directory):
        if filename.endswith(".png"):
            png_filename = os.path.join(directory, filename)
            xpm_filename = os.path.join(directory, os.path.splitext(filename)[0] + ".xpm")
            generate_xpm(png_filename, xpm_filename)
            print(f"Generated: {xpm_filename}")

if __name__ == "__main__":
    # Update this path to the directory containing your PNG files
    directory = r"C:\Users\maxvo\Downloads\Apocalypse Character Pack\Apocalypse Character Pack\Floor"

    # Call the function to create XPM files from PNGs
    create_xpm_from_pngs(directory)
