#!/bin/bash

# Define input file and target directory
INPUT_FILE="files_list.txt"

# Check each line in the input file
while IFS= read -r file_path; do
    # Use grep to check if the file path exists in the target directory
    if ! grep -qF "$file_path" <(find "$FXCGSDK" -not -path '*/.*'); then
        echo "Missing: $file_path"
    fi
done < "$INPUT_FILE"
