import shutil
import os

# Define source and destination directories
source_directory = "src"
backup_directory = "/path/to/backup_directory"

# Create backup directory if it doesn't exist
if not os.path.exists(backup_directory):
    os.makedirs(backup_directory)

# Copy files from source to backup directory
shutil.copytree(source_directory, backup_directory)
