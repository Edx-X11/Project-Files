use std::fs::File;
use std::io::{Write, Result};
use std::time::SystemTime;

// Function to log backup activities
fn log_backup(source_directory: &str, backup_directory: &str) -> Result<()> {
    let timestamp = SystemTime::now();
    let message = format!("Backup initiated for directory: {} to: {}", source_directory, backup_directory);
    let log_entry = format!("{} {}", timestamp.strftime("%Y-%m-%d %H:%M:%S").unwrap(), message);

    // Append log entry to a log file
    let mut log_file = File::create("backup_log.txt")?;
    writeln!(log_file, "{}", log_entry)?;

    // Perform backup operation (copy files from source to backup directory)
    // You can use your preferred method for file copying here

    Ok(())
}

fn main() {
    let source_directory = "Unused/backups";
    let backup_directory = "Unused/backups";

    if let Err(err) = log_backup(source_directory, backup_directory) {
        eprintln!("Error: {}", err);
    }
}
