// Define the SeedGenerator class
class SeedGenerator {
  // Method to generate seeds and analyze them
  static generateSeeds() {
    for (let i = 0; i < 50; i++) {
      const seed = SeedGenerator.generateRandomSeed(); // Generate a random seed
      console.log(`Seed ${i + 1}: ${seed}`);
      SeedGenerator.analyzeSeed(seed);
    }
  }

  // Method to generate a random seed
  static generateRandomSeed() {
    return Math.floor(Math.random() * Math.pow(2, 32)); // Generate a random 32-bit seed
  }

  // Method to analyze a seed and determine if it has a village
  static analyzeSeed(seed) {
    if (SeedGenerator.hasVillage(seed)) {
      console.log("This seed produces a world with a village.");
    } else {
      console.log("This seed does not produce a world with a village.");
    }
  }

  // Method to simulate world generation and check for a village
  static hasVillage(seed) {
    // For simplicity, let's assume a village spawns within 1000 blocks of the spawn point
    const spawnX = 0; // Player's spawn X coordinate
    const spawnZ = 0; // Player's spawn Z coordinate
    const radius = 1000; // Radius in blocks

    const random = new Random(seed);
    const villageX = random.nextInt(radius * 2) - radius + spawnX;
    const villageZ = random.nextInt(radius * 2) - radius + spawnZ;

    // Check if the village coordinates are within the spawn radius
    return Math.sqrt((villageX - spawnX) ** 2 + (villageZ - spawnZ) ** 2) <= radius;
  }
}

// Define a Random class to simulate Java's Random class
class Random {
  constructor(seed) {
    this.seed = seed || Date.now();
  }

  nextInt(max) {
    const x = Math.sin(this.seed++) * 10000;
    return Math.floor((x - Math.floor(x)) * max);
  }
}

// Example usage:
SeedGenerator.generateSeeds();
