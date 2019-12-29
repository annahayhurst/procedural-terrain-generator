#include "stdafx.h"
#include "CppUnitTest.h"

#include "Perlin.h"
#include "Perlin.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests_PCG {	

	// Tests concerning the Perlin class
	TEST_CLASS(PerlinTest) {
	public:
		
		// Test default constructor
		TEST_METHOD(Perlin_DefaultConstructor) {
			Engine::Perlin per;
			
			// Check permutation vector was made
			Assert::IsNotNull(per.getPermutations());
			vector<uint> p = *per.getPermutations();
			
			// Check that values are correct
			uint first = 151, last = 180;
			Assert::AreEqual(p[0], first);
			Assert::AreEqual(p[255], last);
		}

		// Test seeded constructor
		TEST_METHOD(Perlin_SeededConstructor) {
			uint seed = 123;
			Engine::Perlin per = Engine::Perlin(123);

			// Check seed is correct
			Assert::AreEqual(per.getSeed(), seed);

			// Check permutation vector was made
			Assert::IsNotNull(per.getPermutations());
			vector<uint> p = *per.getPermutations();
			
			// Check that permutations are not default
			uint first = 151, last = 180;
			Assert::AreNotEqual(p[0], first);
			Assert::AreNotEqual(p[255], last);

		}

		// Test default noise method with default permutations. Check that noise values are consistent with previous ones.
		TEST_METHOD(Perlin_Noise) {
			Engine::Perlin per;

			float noiseArray[] = { 
				0.083736f, 0.197373f, - 0.106716f, - 0.09144f, 0.0983613f, 0.196723f, 0.112657f, - 0.106716f, - 0.180532f, - 0.0907892f, 
				- 0.202597f, 0.0897426f, - 0.00678929f, 0.0999267f, 0.198156f, 0.0838019f
			};

			float resultArray[16];

			int i = 0;
			for (float x = 0.1f; x < 4.1f; x++) {
				for (float y = 0.1f; y < 4.1f; y++) {
					resultArray[i] = per.noise2D(x, y);
					std::cout << resultArray[i] << " ";
					i++;
				}
			}

			for(i = 0; i < 16; i++) Assert::AreEqual(resultArray[i], noiseArray[i], 0.05f);

		}

		// Test octave noise. Ensure the results are consistent.
		TEST_METHOD(Perlin_OctaveNoise) {
			uint seed = 345;
			Engine::Perlin per(seed, 3, 0.95f);

			float noiseArray[] = {
				-0.114235f, 0.0297673f, 0.00294358f, - 0.174481f, 0.107972f, - 0.00744739f, 0.0121495f, 0.0886794f, 0.0279725f, 0.0992485f,
				- 0.208666f, - 0.111889f, - 0.124575f, 0.1107f, 0.217854f, - 0.196451f
			};

			float resultArray[16];

			int i = 0;
			for (float x = 0.1f; x < 4.1f; x++) {
				for (float y = 0.1f; y < 4.1f; y++) {
					resultArray[i] = per.octaveNoise2D(x, y);
					i++;
				}
			}

			for (i = 0; i < 16; i++) Assert::AreEqual(resultArray[i], noiseArray[i], 0.01f);
		}

	};
}