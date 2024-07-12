import os

def rename_files(directory):
    # Get a list of all files in the directory
    files = os.listdir(directory)
    
    # Sort the files to ensure consistent ordering
    files.sort()
    
    # Initialize a counter for the new names
    counter = 2
    
    # Iterate through the files
    for filename in files:
        # Check if the file is a regular file (not a directory)
        if os.path.isfile(os.path.join(directory, filename)):
            # Split the filename and extension
            name, ext = os.path.splitext(filename)
            
            # Generate the new filename with a numeric prefix
            new_filename = os.path.join(directory, f"{counter}{ext}")
            
            # Handle the case where the target filename already exists
            if os.path.exists(new_filename):
                # Find a unique name by appending an incrementing number
                index = 1
                while True:
                    new_filename = os.path.join(directory, f"{counter}_{index}{ext}")
                    if not os.path.exists(new_filename):
                        break
                    index += 1
            
            # Rename the file
            os.rename(os.path.join(directory, filename), new_filename)
            
            # Print feedback (optional)
            print(f"Renamed {filename} to {os.path.basename(new_filename)}")
            
            # Increment the counter
            counter += 1

if __name__ == "__main__":
    # Update this path to the directory containing your files
    directory = r"C:\Users\maxvo\Downloads\Apocalypse Character Pack\Apocalypse Character Pack\Wall"

    # Call the function to rename files
    rename_files(directory)
