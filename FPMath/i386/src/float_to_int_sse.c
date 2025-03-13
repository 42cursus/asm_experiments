/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_int_sse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:35:27 by abelov            #+#    #+#             */
/*   Updated: 2025/03/13 13:35:28 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xmmintrin.h> // SSE intrinsics
#include <smmintrin.h>

/**
 * cvtss2si → Converts a float to an int, truncating by default.
 * roundss → Applies rounding modes before conversion:
 * 	0 → Round to nearest (default)
 * 	1 → Round down (floor)
 * 	2 → Round up (ceil)
 * 	3 → Round toward zero (truncate)
 *
 * @param f
 * @param mode
 * @return
 */
int float_to_int_sse(float f, int mode) {
	int result;
	__asm__("roundss %1, %1, %2\n\t" // Round float based on mode
			"cvtss2si %1, %0"        // Convert rounded float to integer
			: "=r" (result)
			: "x" (f), "i" (mode)
			);
	return result;
}

int float_to_int_sse2_round(float f) {
	const __m128 half = _mm_set_ss(0.5f); // 0.5 to force rounding
	__m128 val = _mm_set_ss(f);

	// Add or subtract 0.5 based on the sign (to round correctly)
	__m128 sign_mask = _mm_set1_ps(-0.0f); // Mask for extracting sign bit
	__m128 bias = _mm_or_ps(half, _mm_and_ps(val, sign_mask)); // Apply sign
	val = _mm_add_ss(val, bias); // Add/subtract 0.5

	return _mm_cvtss_si32(val); // Convert to int
}

int float_to_int_sse4_round(float f, int mode) {
	__m128 val = _mm_set_ss(f);
	val = _mm_round_ss(val, val, mode); // Apply rounding mode
	return _mm_cvtss_si32(val); // Convert to int
}

int float_to_int_sse_intr(float f) {
	return _mm_cvtss_si32(_mm_set_ss(f)); // Convert float to int (truncates)
}

void float_to_int_sse_batch(const float *input, int *output, int count) {
	int i;
	for (i = 0; i + 4 <= count; i += 4) {
		__m128 floats = _mm_loadu_ps(&input[i]); // Load four floats
		__m128i ints = _mm_cvttps_epi32(floats); // Convert to four integers (truncates)
		_mm_storeu_si128((__m128i*)&output[i], ints); // Store four integers
	}
	// Process remaining elements (scalar)
	for (; i < count; i++) output[i] = (int) input[i];
}

void float_to_int_sse2_round_batch(const float *input, int *output, int count) {
	const __m128 half = _mm_set1_ps(0.5f);  // 0.5 to force rounding
	const __m128 sign_mask = _mm_set1_ps(-0.0f); // Used to extract sign

	int i;
	for (i = 0; i + 4 <= count; i += 4) {
		__m128 vals = _mm_loadu_ps(&input[i]); // Load 4 floats

		// Compute bias (+0.5 or -0.5 based on sign)
		__m128 bias = _mm_or_ps(half, _mm_and_ps(vals, sign_mask));

		// Apply rounding bias before truncation
		vals = _mm_add_ps(vals, bias);

		// Convert to 4 integers
		__m128i ints = _mm_cvttps_epi32(vals);

		// Store results
		_mm_storeu_si128((__m128i*)&output[i], ints);
	}

	// Process remaining elements (scalar)
	for (; i < count; i++) {
		float f = input[i];
		float bias = (f >= 0.0f) ? 0.5f : -0.5f;
		output[i] = (int)(f + bias);
	}
}
