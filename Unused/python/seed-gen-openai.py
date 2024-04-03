import openai

# Set up your OpenAI API key
api_key = 'YOUR_OPENAI_API_KEY'
openai.api_key = api_key

# Define the prompt format for generating Minecraft seeds
prompt_template = """
Generate a Minecraft seed with the following characteristics:
- Desired Structures: {structures}
- Desired Biomes: {biomes}
- World Size: {world_size}
- Resources: {resources}
- Difficulty: {difficulty}
- Cheats: {cheats}
- Villages: {villages}
- Mineshafts: {mineshafts}
- Strongholds: {strongholds}
- Biome Types: {biome_types}
- Terrain Features: {terrain_features}
- Spawn Location: {spawn_location}
"""

# Function to generate Minecraft seeds based on player input
def generate_minecraft_seed(structures, biomes, world_size, resources, difficulty, cheats, villages, mineshafts, strongholds, biome_types, terrain_features, spawn_location):
    # Prepare the prompt using the provided parameters
    prompt = prompt_template.format(structures=structures, biomes=biomes, world_size=world_size,
                                    resources=resources, difficulty=difficulty, cheats=cheats,
                                    villages=villages, mineshafts=mineshafts, strongholds=strongholds,
                                    biome_types=biome_types, terrain_features=terrain_features,
                                    spawn_location=spawn_location)

    # Generate Minecraft seed using GPT-3
    response = openai.Completion.create(
        engine="text-davinci-002",
        prompt=prompt,
        temperature=0.7,
        max_tokens=100
    )

    # Extract and return the generated Minecraft seed
    seed = response.choices[0].text.strip()
    return seed

# Function to validate and process user input for various features
def process_input(input_str):
    # Split the input string by comma and strip whitespace from each element
    options = [option.strip() for option in input_str.split(',')]
    # Filter out empty strings
    options = [option for option in options if option]
    return options

# Main function to handle user interaction and generate seeds
def main():
    print("Welcome to Minecraft Seed Generator with OpenAI!")

    # Get user input for various features
    desired_structures = input("Enter desired structures (comma-separated): ")
    desired_biomes = input("Enter desired biomes (comma-separated): ")
    world_size = input("Enter world size (small, medium, large): ").lower()
    resources = input("Enter desired resources (comma-separated): ")
    difficulty = input("Enter difficulty level (easy, normal, hard): ").lower()
    cheats = input("Enable cheats? (yes/no): ").lower()
    villages = input("Include villages? (yes/no): ").lower()
    mineshafts = input("Include mineshafts? (yes/no): ").lower()
    strongholds = input("Include strongholds? (yes/no): ").lower()
    biome_types = input("Enter desired biome types (comma-separated): ")
    terrain_features = input("Enter desired terrain features (comma-separated): ")
    spawn_location = input("Enter spawn location (x,y,z): ")

    # Process user input
    structures = process_input(desired_structures)
    biomes = process_input(desired_biomes)

    # Check if input is valid
    if not structures or not biomes or world_size not in ['small', 'medium', 'large'] \
            or difficulty not in ['easy', 'normal', 'hard'] or cheats not in ['yes', 'no'] \
            or villages not in ['yes', 'no'] or mineshafts not in ['yes', 'no'] or strongholds not in ['yes', 'no']:
        print("Error: Invalid input.")
        return

    # Generate Minecraft seed
    generated_seed = generate_minecraft_seed(desired_structures, desired_biomes, world_size,
                                              resources, difficulty, cheats, villages, mineshafts, strongholds,
                                              biome_types, terrain_features, spawn_location)
    print("\nGenerated Minecraft Seed:")
    print(generated_seed)

# Example usage
if __name__ == "__main__":
    main()
