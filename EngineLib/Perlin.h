#pragma once
/*
* Perlin
* Handles generation of noise values. This is split across several
* linked functions that feed into the primary noise() and octaveNoise() functions.
*
* This is based upon/adapted from Ken Perlin's "improved" noise, originally 
* implemented in Java. https://mrl.nyu.edu/~perlin/noise/ The original 
* implementation is copyright 2002 to Ken Perlin.
*/

#include <vector>
#include <numeric>
#include <random>
#include <iostream>

using namespace std;
typedef unsigned int uint;

namespace Engine {
	class Perlin {
	public:
		Perlin();
		Perlin(uint seed);
		Perlin(uint seed, uint octaves, float persistence);

		float noise2D(float x, float y);
		float noise3D(float x, float y, float z);
		float octaveNoise2D(float x, float y);
		float octaveNoise3D(float x, float y, float z);

		vector<uint>* getPermutations() { return &permutations; }
		uint getSeed() { return seed; }
		uint getOctaveCount() { return octaves; }
		float getPersistence() { return persistence; }

		void setSeed(uint newSeed);
		void setOctaveCount(uint oct) { if (oct < MAX_OCTAVES) octaves = oct; }
		void setPersistence(float per) { if (per > 0.0f && per <= 1.0f) persistence = per; }

		~Perlin() {};

	private:

		float lint(float t, float a, float b);
		float fade(float t);
		float gradient(int hash, float x, float y, float z = 0);
		int floor(float a);

		void shufflePermutations();

		uint seed, octaves;
		float persistence;

		// This vector is used in place of the original array. It is more
		// flexible to do this in C++ considering vectors can be altered more easily.
		// The order of numbers is as per Perlin's original p[] array.
		vector<uint> permutations = {
			151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
			8,99,37,240,21,10,23, 190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,
			117,35,11,32,57,177,33, 88,237,149,56,87,174,20,125,136,171,168, 68,175,74,
			165,71,134,139,48,27,166, 77,146,158,231,83,111,229,122,60,211,133,230,220,
			105,92,41,55,46,245,40,244, 102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,
			187,208, 89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,
			64,52,217,226,250,124,123, 5,202,38,147,118,126,255,82,85,212,207,206,59,227,
			47,16,58,17,182,189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,
			153,101,155,167, 43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185,
			112,104,218,246,97,228, 251,34,242,193,238,210,144,12,191,179,162,241, 81,51,
			145,235,249,14,239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,
			50,45,127, 4,150,254, 138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,
			215,61,156,180
		};

		const uint MAX_OCTAVES = 10;
	};

}