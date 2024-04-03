import java.util.Random;

class SeedGenerator {
    public static void generateSeeds() {
        Random random = new Random();
        for (int i = 0; i < 50; i++) {
            long seed = random.nextLong() & 0xFFFFFFFFL; // Generate a random 32-bit seed
            System.out.println("Seed " + (i + 1) + ": " + seed);
            analyzeSeed(seed);
        }
    }

    private static void analyzeSeed(long seed) {
        if (hasVillage(seed)) {
            System.out.println("This seed produces a world with a village.");
        } else {
            System.out.println("This seed does not produce a world with a village.");
        }
    }

    private static boolean hasVillage(long seed) {
        // Simulate world generation to check for a village
        // For simplicity, let's assume a village spawns within 1000 blocks of the spawn point
        int spawnX = 0; // Player's spawn X coordinate
        int spawnZ = 0; // Player's spawn Z coordinate
        int radius = 1000; // Radius in blocks

        Random random = new Random(seed);
        int villageX = random.nextInt(radius * 2) - radius + spawnX;
        int villageZ = random.nextInt(radius * 2) - radius + spawnZ;

        // Check if the village coordinates are within the spawn radius
        return Math.sqrt((villageX - spawnX) * (villageX - spawnX) + (villageZ - spawnZ) * (villageZ - spawnZ)) <= radius;
    }
}
