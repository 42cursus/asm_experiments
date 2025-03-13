/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_float_sse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:34:16 by abelov            #+#    #+#             */
/*   Updated: 2025/03/13 13:34:17 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xmmintrin.h>  // SSE2 intrinsics
#include <emmintrin.h>  // SSE2 integer intrinsics
#include <smmintrin.h>	// SSE4.1 intrinsics

// SSE2 scalar
float int_to_float_sse(int x) {
	float result;
	__asm__("cvtsi2ss %1, %0"  // Convert int to float
			: "=x" (result)
			: "r" (x)
			);
	return result;
}

float int_to_float_sse_intr(int x) {
	__m128 f = _mm_cvtsi32_ss(_mm_setzero_ps(), x); // Convert int to float
	return _mm_cvtss_f32(f); // Extract float value
}

// SSE2
void int_to_float_sse2_batch(const int *input, float *output, int count) {
	int i;
	for (i = 0; i + 4 <= count; i += 4) {
		__m128i ints = _mm_loadu_si128((__m128i*)&input[i]); // Load four integers
		__m128 floats = _mm_cvtepi32_ps(ints); // Convert to four floats
		_mm_storeu_ps(&output[i], floats); // Store four floats
	}
	// Process remaining elements (scalar)
	for (; i < count; i++) {
		output[i] = (float)input[i];
	}
}

// SSE4.1
void int_to_float_sse4_batch(const int *input, float *output, int count) {
	int i;
	for (i = 0; i + 4 <= count; i += 4) {
		__m128 floats = _mm_cvtsi32_ss(_mm_setzero_ps(), input[i]); // Convert first int
		floats = _mm_insert_ps(floats, _mm_cvtsi32_ss(_mm_setzero_ps(), input[i + 1]), 0x10);
		floats = _mm_insert_ps(floats, _mm_cvtsi32_ss(_mm_setzero_ps(), input[i + 2]), 0x20);
		floats = _mm_insert_ps(floats, _mm_cvtsi32_ss(_mm_setzero_ps(), input[i + 3]), 0x30);
		_mm_storeu_ps(&output[i], floats); // Store four floats
	}
	// Process remaining elements (scalar)
	for (; i < count; i++) {
		output[i] = (float)input[i];
	}
}
