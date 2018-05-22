#ifndef SPH_SKEIN_H__
#define SPH_SKEIN_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>
#include "sph_types.h"

#if SPH_64

/**
 * Output size (in bits) for Skein-224.
 */
#define SPH_SIZE_skein224   224

/**
 * Output size (in bits) for Skein-256.
 */
#define SPH_SIZE_skein256   256

/**
 * Output size (in bits) for Skein-384.
 */
#define SPH_SIZE_skein384   384

/**
 * Output size (in bits) for Skein-512.
 */
#define SPH_SIZE_skein512   512

/**
 * This structure is a context for Skein computations (with a 384- or
 * 512-bit output): it contains the intermediate values and some data
 * from the last entered block. Once a Skein computation has been
 * performed, the context can be reused for another computation.
 *
 * The contents of this structure are private. A running Skein computation
 * can be cloned by copying the context (e.g. with a simple
 * <code>memcpy()</code>).
 */
typedef struct {
#ifndef DOXYGEN_IGNORE
	unsigned char buf[64];    /* first field, for alignment */
	size_t ptr;
	sph_u64 h0, h1, h2, h3, h4, h5, h6, h7;
	sph_u64 bcount;
#endif
} sph_skein_big_context;

/**
 * Type for a Skein-224 context (identical to the common "big" context).
 */
typedef sph_skein_big_context sph_skein224_context;

/**
 * Type for a Skein-256 context (identical to the common "big" context).
 */
typedef sph_skein_big_context sph_skein256_context;

/**
 * Type for a Skein-384 context (identical to the common "big" context).
 */
typedef sph_skein_big_context sph_skein384_context;

/**
 * Type for a Skein-512 context (identical to the common "big" context).
 */
typedef sph_skein_big_context sph_skein512_context;

/**
 * Initialize a Skein-224 context. This process performs no memory allocation.
 *
 * @param cc   the Skein-224 context (pointer to a
 *             <code>sph_skein224_context</code>)
 */
void sph_skein224_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the Skein-224 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_skein224(void *cc, const void *data, size_t len);

/**
 * Terminate the current Skein-224 computation and output the result into
 * the provided buffer. The destination buffer must be wide enough to
 * accomodate the result (28 bytes). The context is automatically
 * reinitialized.
 *
 * @param cc    the Skein-224 context
 * @param dst   the destination buffer
 */
void sph_skein224_close(void *cc, void *dst);

/**
 * Add a few additional bits (0 to 7) to the current computation, then
 * terminate it and output the result in the provided buffer, which must
 * be wide enough to accomodate the result (28 bytes). If bit number i
 * in <code>ub</code> has value 2^i, then the extra bits are those
 * numbered 7 downto 8-n (this is the big-endian convention at the byte
 * level). The context is automatically reinitialized.
 *
 * @param cc    the Skein-224 context
 * @param ub    the extra bits
 * @param n     the number of extra bits (0 to 7)
 * @param dst   the destination buffer
 */
void sph_skein224_addbits_and_close(
	void *cc, unsigned ub, unsigned n, void *dst);

/**
 * Initialize a Skein-256 context. This process performs no memory allocation.
 *
 * @param cc   the Skein-256 context (pointer to a
 *             <code>sph_skein256_context</code>)
 */
void sph_skein256_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the Skein-256 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_skein256(void *cc, const void *data, size_t len);

/**
 * Terminate the current Skein-256 computation and output the result into
 * the provided buffer. The destination buffer must be wide enough to
 * accomodate the result (32 bytes). The context is automatically
 * reinitialized.
 *
 * @param cc    the Skein-256 context
 * @param dst   the destination buffer
 */
void sph_skein256_close(void *cc, void *dst);

/**
 * Add a few additional bits (0 to 7) to the current computation, then
 * terminate it and output the result in the provided buffer, which must
 * be wide enough to accomodate the result (32 bytes). If bit number i
 * in <code>ub</code> has value 2^i, then the extra bits are those
 * numbered 7 downto 8-n (this is the big-endian convention at the byte
 * level). The context is automatically reinitialized.
 *
 * @param cc    the Skein-256 context
 * @param ub    the extra bits
 * @param n     the number of extra bits (0 to 7)
 * @param dst   the destination buffer
 */
void sph_skein256_addbits_and_close(
	void *cc, unsigned ub, unsigned n, void *dst);

/**
 * Initialize a Skein-384 context. This process performs no memory allocation.
 *
 * @param cc   the Skein-384 context (pointer to a
 *             <code>sph_skein384_context</code>)
 */
void sph_skein384_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the Skein-384 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_skein384(void *cc, const void *data, size_t len);

/**
 * Terminate the current Skein-384 computation and output the result into
 * the provided buffer. The destination buffer must be wide enough to
 * accomodate the result (48 bytes). The context is automatically
 * reinitialized.
 *
 * @param cc    the Skein-384 context
 * @param dst   the destination buffer
 */
void sph_skein384_close(void *cc, void *dst);

/**
 * Add a few additional bits (0 to 7) to the current computation, then
 * terminate it and output the result in the provided buffer, which must
 * be wide enough to accomodate the result (48 bytes). If bit number i
 * in <code>ub</code> has value 2^i, then the extra bits are those
 * numbered 7 downto 8-n (this is the big-endian convention at the byte
 * level). The context is automatically reinitialized.
 *
 * @param cc    the Skein-384 context
 * @param ub    the extra bits
 * @param n     the number of extra bits (0 to 7)
 * @param dst   the destination buffer
 */
void sph_skein384_addbits_and_close(
	void *cc, unsigned ub, unsigned n, void *dst);

/**
 * Initialize a Skein-512 context. This process performs no memory allocation.
 *
 * @param cc   the Skein-512 context (pointer to a
 *             <code>sph_skein512_context</code>)
 */
void sph_skein512_init(void *cc);

/**
 * Process some data bytes. It is acceptable that <code>len</code> is zero
 * (in which case this function does nothing).
 *
 * @param cc     the Skein-512 context
 * @param data   the input data
 * @param len    the input data length (in bytes)
 */
void sph_skein512(void *cc, const void *data, size_t len);

/**
 * Terminate the current Skein-512 computation and output the result into
 * the provided buffer. The destination buffer must be wide enough to
 * accomodate the result (64 bytes). The context is automatically
 * reinitialized.
 *
 * @param cc    the Skein-512 context
 * @param dst   the destination buffer
 */
void sph_skein512_close(void *cc, void *dst);

/**
 * Add a few additional bits (0 to 7) to the current computation, then
 * terminate it and output the result in the provided buffer, which must
 * be wide enough to accomodate the result (64 bytes). If bit number i
 * in <code>ub</code> has value 2^i, then the extra bits are those
 * numbered 7 downto 8-n (this is the big-endian convention at the byte
 * level). The context is automatically reinitialized.
 *
 * @param cc    the Skein-512 context
 * @param ub    the extra bits
 * @param n     the number of extra bits (0 to 7)
 * @param dst   the destination buffer
 */
void sph_skein512_addbits_and_close(
	void *cc, unsigned ub, unsigned n, void *dst);

#endif

#ifdef __cplusplus
}
#endif

#endif
