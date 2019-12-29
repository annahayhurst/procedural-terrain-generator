#include "Perlin.h"

namespace Engine {
	// Default, unseeded constructor. Initialises the default permutation vector
	// (as set out by Perlin)
	Perlin::Perlin() : seed(0), octaves(5), persistence(0.25f) {
		permutations.resize(512);

		// Duplicate first set of values to get to 512
		for (int i = 0; i < 256; i++) {
			permutations[i + 256] = permutations[i];
		}

	}

	Perlin::Perlin(uint seed) : seed(seed), octaves(5), persistence(0.25f) {
		shufflePermutations();
	}

	// Construct the permutation array using a seed value. This constructor is not a part of the
	// original noise implementation but is important to add for procedural generation.
	Perlin::Perlin(uint seed, uint octaves, float persistence) : seed(seed), octaves(octaves), persistence(persistence) {
		shufflePermutations();
	}

	// Calculate noise value for a given (x, y) co-ordinate by creating a unit square around it, finding
	// where (x, y) sits within the square, then fading the co-ordinates, hashing to find a gradient and 
	// linearly interpolating between those gradients and the faded co-ordinates.
	// This is a simplification of noise3D (see below).
	float Perlin::noise2D(float x, float y) {
		// Generate unit square that contains the point
		int X = floor(x) & 255;
		int	Y = floor(y) & 255;

		// Find relative position of this point in the square
		x -= floor(x);
		y -= floor(y);

		// Apply fade curve to each co-ordinate
		float u = fade(x);
		float v = fade(y);

		// Using permutation values, hash coordinates of the corners.
		int A = permutations[X] + Y, AA = permutations[A], AB = permutations[A + 1],
			B = permutations[X + 1] + Y, BA = permutations[B], BB = permutations[B + 1];

		float i1 = lint(u, gradient(permutations[AA], x, y), gradient(permutations[BA], x - 1, y));
		float i2 = lint(u, gradient(permutations[AB], x, y - 1), gradient(permutations[BB], x - 1, y - 1));

		return lint(v, i1, i2);
	}

	// Generates a single noise value for a given coordinate by creating a unit cube around the point,
	// finding the point within the cube, fading the values, hashing the coordinates of the cube corners
	// and finally linearly interpolating these points.
	float Perlin::noise3D(float x, float y, float z) {
		// Generate unit cube that contains the point
		// The factor 255 is introduced to wrap the integer 'cells'
		int X = floor(x) & 255;
		int Y = floor(y) & 255;
		int Z = floor(z) & 255;

		// Find the relative position of the point WITHIN this cube (scale between 0 and 1)
		x -= floor(x);
		y -= floor(y);
		z -= floor(z);

		// Apply fade curve to each coordinate
		float u = fade(x);
		float v = fade(y);
		float w = fade(z);

		// Using permutation values, hash the coordinates of cube corners
		// (Hashes used for gradient function)
		int A = permutations[X] + Y, AA = permutations[A] + Z, AB = permutations[A + 1] + Z,
			B = permutations[X + 1] + Y, BA = permutations[B] + Z, BB = permutations[B + 1] + Z;

		// Linear interpolate as appropriate to create the final value based on the faded values
		// and the calculated hashed cube corners. Simplified from the original implementation for readability
		float i1, i2, j1, j2;
		// All hash values and hash values + 1 represented. Combinations of x, y, z, and x-1, y-1, z-1.
		i1 = lint(u, gradient(permutations[AB + 1], x, y - 1, z - 1), gradient(permutations[BB + 1], x - 1, y - 1, z - 1)); // Innermost interpolation
		j1 = lint(v, lint(u, gradient(permutations[AA + 1], x, y, z - 1), gradient(permutations[BA + 1], x - 1, y, z - 1)), i1);
		i2 = lint(u, gradient(permutations[AB], x, y - 1, z), gradient(permutations[BB], x - 1, y - 1, z));
		j2 = lint(v, lint(u, gradient(permutations[AA], x, y, z), gradient(permutations[BA], x - 1, y, z)), i2);

		return lint(w, j2, j1); // Outermost interpolation, giving the final value

	}

	// Octaves and persistence are not present in Perlin's original work. They have been added as 
	// a tool to help shape the noise to appear more "natural" and blended. Each successive
	// octave has a smaller effect on the final noise, according to persistence.
	// An octave count of 1, or a persistence of 0, will cause the output to be identical to the original noise.
	// The following article was used to help write this function: https://flafla2.github.io/2014/08/09/perlinnoise.html
	float Perlin::octaveNoise2D(float x, float y) {
		float total = 0.0f;
		float max = 0.0f; // this puts a cap on the final value, so it normalises btwn 0 and 1
		float frq = 1.0f, amp = 1.0f; // these decrease each iteration

		for (uint i = 0; i < octaves; ++i) {
			total += noise2D(frq*x, frq*y) * amp;

			// If we add each amplitude value, we can divide through to normalise.
			max += amp;

			// As octave gets higher, increase frequency according to 2^i (higher frequency = more jagged noise)
			frq *= 2;

			// As octave gets higher, decrease amplitude according to persistence^i (lower amplitude = affects final noise less)
			// The higher the persistence, the more each octave's noise will affect the overall noise.
			amp *= persistence;
		}

		return total / max;
	}

	// An implementation of octave noise made suitable for 3D. As above, but making use of the noise3D function.
	float Perlin::octaveNoise3D(float x, float y, float z) {
		float total = 0.0f;
		float max = 0.0f; // this puts a cap on the final value, so it normalises btwn 0 and 1
		float frq = 1.0f, amp = 1.0f; // these decrease each iteration

		for (uint i = 0; i < octaves; ++i) {
			total += noise3D(frq*x, frq*y, frq*z) * amp;

			// If we add each amplitude value, we can divide through to normalise.
			max += amp;

			// As octave gets higher, increase frequency according to 2^i (higher frequency = more jagged noise)
			frq *= 2;

			// As octave gets higher, decrease amplitude according to persistence^i (lower amplitude = affects final noise less)
			// The higher the persistence, the more each octave's noise will affect the overall noise.
			amp *= persistence;
		}

		return total / max;
	}

	void Perlin::setSeed(uint newSeed) {
		seed = newSeed;
		shufflePermutations();
	}


	// Interpolate to create a straight line between two points.
	// This is nested within itself in the noise function multiple times to correctly imitate
	// the full linear interpolation formula.
	float Perlin::lint(float t, float a, float b) {
		return a + ((b - a) * t);
	}

	// Fade applies an 'ease curve' to the gradients, which causes real numbers to tend towards integer values.
	// This helps to give a smoother appearance to the produced noise.
	float Perlin::fade(float t) {
		// Perlin's fade equation is 6t^5 - 15t^4 + 10t^3
		return t * t * t * (t * (t * 6 - 15) + 10);
	}


	// Calculates dot product between pseudorandom (hashed) gradient vectors and the supplied point. 
	// Works in terms of binary, producing values u and v according to the hash value (comparing to its most significant bits)
	// When applying gradients to 2D noise, z is always 0.
	float Perlin::gradient(int hash, float x, float y, float z) {
		int h = hash & 15; // (15 = 01111) so we take the first 4 digits of the hash

		float a;
		if (h < 8) a = x; // if most sig. bit of hash is 0 then u = x, otherwise y (8 = 01000)
		else a = y;

		float b;
		if (h < 4) {
			b = y; // 1st + 2nd sig. bits are 0, then v = y (4 = 00100)
		}
		else if (h == 12 || h == 14) {
			b = x; // 1st + 2nd sig. bits are 1 (12 = 01100, 14 = 01110)
		}
		else {
			b = z; // 1st + 2nd sig. bits are different
		}

		// If 2nd to last bit is 0, v is positive (2 = 00010)
		// If 2nd to last bit is 1, v is negative.
		if ((h & 2) != 0) {
			b = -b;
		}

		// If last bit is 0, u is positive (1 = 00001)
		// If last bit is 1, u is negative.
		if ((h & 1) != 0) {
			a = -a;
		}

		return a + b;

	}

	// Helper function to find the floor without fiddling with type casting (due to cmath floor returning a float)
	int Perlin::floor(float a) {
		int aInt = (int)a;

		return (a >= aInt) ? (aInt) : (aInt - 1);
	}

	// Shuffle the permutations vector using a random engine. A new permutations vector means new noise values
	// can be generated for the same set of coordinates.
	void Perlin::shufflePermutations() {

		// Use seed value to create a random "engine" that generates pseudorandom values
		default_random_engine shuffler(seed);

		// Create a new order of permutations by shuffling with the engine
		shuffle(permutations.begin(), permutations.end(), shuffler);

		// Now, as in default constructor, duplicate to create a 512 array.
		permutations.resize(512);

		for (int i = 0; i < 256; i++) {
			permutations[i + 256] = permutations[i];
		}

	}

}