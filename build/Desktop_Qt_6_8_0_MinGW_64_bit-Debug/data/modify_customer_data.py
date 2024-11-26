def modify_file(file_path):
    try:
        # Open the file and read all lines
        with open(file_path, 'r') as file:
            lines = file.readlines()
        
        # Process each line
        modified_lines = []
        for line in lines:
            # Strip whitespace and split by comma
            parts = line.strip().split(',')
            if len(parts) >= 4:  # Ensure there are at least 4 fields
                # Retain the first 4 fields, replace the rest with "0,0"
                modified_line = ','.join(parts[:4]) + ",0,0"
                modified_lines.append(modified_line)
            else:
                # If the line doesn't match the format, keep it unchanged
                modified_lines.append(line.strip())
        
        # Write the modified lines back to the file
        with open(file_path, 'w') as file:
            file.write('\n'.join(modified_lines) + '\n')

        print("File modification completed.")
    
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    # Ask the user for the file path
    file_path = input("Enter the path to the file: ").strip()
    
    # Call the function to modify the file
    modify_file(file_path)
