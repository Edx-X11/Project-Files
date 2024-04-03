# Seed Generator

The Seed Generator is a Java application that generates random seeds and analyzes them to determine if they produce a world with a village.

## Usage

To use the Seed Generator application, follow these steps:

1. Ensure you have Java installed on your system.
2. Compile the Java files using a Java compiler.
3. Run the Main class to execute the seed generation process.

```bash
javac Main.java SeedGenerator.java
java Main

# Functionality
The Seed Generator application generates 50 random seeds and analyzes each one to determine if it produces a world with a village. Its also to be ran via the console.

# Here's how it works:

The SeedGenerator class generates 50 random seeds using a Random object.
For each seed, it analyzes whether the world generated with that seed contains a village within a radius of 1000 blocks from the spawn point.
If a village is found, it prints a message indicating that the seed produces a world with a village. Otherwise, it prints a message indicating that the seed does not produce a world with a village.
# Contributing
Contributions to the Seed Generator project are welcome! If you'd like to contribute, please fork the repository and submit a pull request with your changes.

# License
The Seed Generator project is licensed under the MIT License. See the LICENSE file for details.