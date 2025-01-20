#!/bin/bash

# Path to the directory to check
TARGET_DIR="/Applications/CASIO/PrizmSDK"

# Path to the file containing the list of required files (absolute paths)
FILE_LIST="files_list.txt"

# File to store missing files
MISSING_FILES="missing_files.txt"

# Clear the missing files list if it exists
> "$MISSING_FILES"

# Check if the target directory exists
if [ -d "$TARGET_DIR" ]; then
    # Loop through each line in the file list
    while IFS= read -r required_file; do
        # Skip empty lines or lines with only spaces
        if [[ -z "$required_file" || "$required_file" =~ ^[[:space:]]*$ ]]; then
            continue
        fi

        # Remove leading/trailing spaces from file names
        required_file=$(echo "$required_file" | xargs)

        # Ensure the path starts with the target directory
        if [[ "$required_file" != $TARGET_DIR* ]]; then
            echo "Skipping non-target path: $required_file"
            continue
        fi

        # Extract the relative path by removing the TARGET_DIR part
        relative_path="${required_file#$TARGET_DIR/}"

        # Search for the file in the target directory (recursively)
        file_found=$(find "$TARGET_DIR" -type f -path "$TARGET_DIR/$relative_path")

        if [ -z "$file_found" ]; then
            # If the file is not found, add it to the missing files list
            echo "$relative_path" >> "$MISSING_FILES"
        fi
    done < "$FILE_LIST"

    # Provide feedback to the user
    if [ -s "$MISSING_FILES" ]; then
        echo "The following files are missing:"
        cat "$MISSING_FILES"
    else
        echo "All required files are present in the directory."
    fi
else
    echo "Error: Target directory '$TARGET_DIR' does not exist."
    exit 1
fi
