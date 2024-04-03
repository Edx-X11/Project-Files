const fs = require('fs');

function generateSeeds() {
    const seeds = [];
    for (let i = 0; i < 50; i++) {
        const seed = generateSeed();
        seeds.push(seed);
        analyzeSeed(seed);
    }
    logSeeds(seeds);
}

function generateSeed() {
    return Math.floor(Math.random() * Number.MAX_SAFE_INTEGER);
}

function analyzeSeed(seed) {
    // Simulate analyzing the seed here
    if (seed % 2 === 0) {
        console.log(`Seed ${seed}: This seed produces a world with a village.`);
    } else {
        console.log(`Seed ${seed}: This seed does not produce a world with a village.`);
    }
}

function logSeeds(seeds) {
    const fileName = 'seed_log.txt';
    const data = seeds.map((seed, index) => `Seed ${index + 1}: ${seed}`).join('\n');
    fs.writeFile(fileName, data, (err) => {
        if (err) {
            console.error('Error writing seed log:', err);
        } else {
            console.log('Seed log saved to', fileName);
        }
    });
}

// Call the function to generate and log seeds
generateSeeds();
