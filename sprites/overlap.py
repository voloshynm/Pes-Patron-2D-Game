import os
import random
from PIL import Image

def get_position(position, background_size, overlay_size):
    """
    Calculate the position where the overlay image should be placed
    based on the specified position string.
    """
    bg_width, bg_height = background_size
    ov_width, ov_height = overlay_size
    
    if position == 'top-left':
        return (0, 0)
    elif position == 'top-center':
        return ((bg_width - ov_width) // 2, 0)
    elif position == 'top-right':
        return (bg_width - ov_width, 0)
    elif position == 'center-left':
        return (0, (bg_height - ov_height) // 2)
    elif position == 'center':
        return ((bg_width - ov_width) // 2, (bg_height - ov_height) // 2)
    elif position == 'center-right':
        return (bg_width - ov_width, (bg_height - ov_height) // 2)
    elif position == 'bottom-left':
        return (0, bg_height - ov_height)
    elif position == 'bottom-center':
        return ((bg_width - ov_width) // 2, bg_height - ov_height)
    elif position == 'bottom-right':
        return (bg_width - ov_width, bg_height - ov_height)
    else:
        raise ValueError("Invalid position specified")

def overlay_images(background_path, overlay_path, output_path, position):
    # Open the background and overlay images
    background = Image.open(background_path).convert('RGBA')
    overlay = Image.open(overlay_path).convert('RGBA')
    
    # Prepare the overlay image with transparency
    overlay_with_transparency = Image.new('RGBA', background.size, (0, 0, 0, 0))
    overlay_with_transparency.paste(overlay, get_position(position, background.size, overlay.size), overlay)
    
    # Combine the background and overlay images
    combined = Image.alpha_composite(background, overlay_with_transparency)
    
    # Save the resulting image
    combined.save(output_path, 'PNG')

# Create a new directory for output images
output_dir = 'output_images'
os.makedirs(output_dir, exist_ok=True)

# Paths to your files
background_image_path = '0.png'

# Positions to choose from
positions = [
    'top-left', 'top-center', 'top-right',
    'center-left', 'center', 'center-right',
    'bottom-left', 'bottom-center', 'bottom-right'
]

# Process each overlay image
for i in range(1, 26):
    overlay_image_path = f'{i}.png'
    output_image_path = os.path.join(output_dir, f'{i}.png')  # Save to the new directory
    
    # Randomly choose a position
    position = random.choice(positions)
    
    # Overlay images with the selected position
    overlay_images(background_image_path, overlay_image_path, output_image_path, position)
    print(f'Processed {overlay_image_path} with random position {position}, saved to {output_image_path}')

