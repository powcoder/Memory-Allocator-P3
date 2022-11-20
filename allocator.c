/**
 * @file
 *
 * Implementations of allocator functions.
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "allocator.h"
#include "logger.h"

static unsigned long g_regions = 0; /*!< Allocation counter */
static unsigned long g_allocations = 0; /*!< Allocation counter */

/** Linked list of memory regions, starting with the most recently-mapped */
static struct mem_region *g_region_list = NULL;

/** Linked list of free memory blocks, starting with the most recently-freed */
static struct mem_block *g_free_list = NULL;

/** Mutex for protecting the region list */
pthread_mutex_t rlist_lock = PTHREAD_MUTEX_INITIALIZER;

/** Mutex for protecting the free list */
pthread_mutex_t flist_lock = PTHREAD_MUTEX_INITIALIZER;


/**
 * Given a free block, this function will split it into two blocks (if
 * possible).
 *
 * @param block Block to split
 * @param size Size of the newly-created block. This block should be at the
 * "end" of the original block:
 * 
 *     +----------------------+-----+
 *     | (old block)          | new |
 *     +----------------------+-----+
 *     ^                      ^
 *     |                      |
 *     |                      +-- pointer to beginning of new block
 *     |
 *     +-- original block pointer (unchanged)
 *         update its size: old_block_size - new_block_size
 *
 *
 * @return address of the resulting second block (the original address will be
 * unchanged) or NULL if the block cannot be split.
 */
struct mem_block *split_block(struct mem_block *block, size_t size)
{
    // TODO block splitting algorithm
    return NULL;
}

/**
 * Given a free block, this function attempts to merge it with neighboring
 * blocks --- both the previous and next neighbors --- and update the linked
 * list accordingly.
 *
 * For example,
 *
 * merge(b1)
 *   -or-
 * merge(b2)
 *
 *     +-------------+--------------+-----------+
 *     | b1 (free)   | b2 (free)    | b3 (used) |
 *     +-------------+--------------+-----------+
 *
 *                   |
 *                   V
 *
 *     +----------------------------+-----------+
 *     | b1 (free)                  | b3 (used) |
 *     +----------------------------+-----------+
 *
 * merge(b3) = NULL
 *
 * @param block the block to merge
 *
 * @return address of the merged block or NULL if the block cannot be merged.
 */
struct mem_block *merge_block(struct mem_block *block)
{
    // TODO block merging algorithm
    return NULL;
}

/**
 * Given a block size (header + data), locate a suitable location in the free
 * list using the first fit free space management algorithm.
 *
 * @param size size of the block (header + data)
 */
void *first_fit(size_t size)
{
    // TODO: first fit FSM implementation
    return NULL;
}

/**
 * Given a block size (header + data), locate a suitable location in the free
 * list using the worst fit free space management algorithm. If there are ties
 * (i.e., you find multiple worst fit candidates with the same size), use the
 * first candidate found in the list.
 *
 * @param size size of the block (header + data)
 */
void *worst_fit(size_t size)
{
    // TODO: worst fit FSM implementation
    return NULL;
}

/**
 * Given a block size (header + data), locate a suitable location in the free
 * list using the best fit free space management algorithm. If there are ties
 * (i.e., you find multiple best fit candidates with the same size), use the
 * first candidate found in the list.
 *
 * @param size size of the block (header + data)
 */
void *best_fit(size_t size)
{
    // TODO: best fit FSM implementation
    return NULL;
}

void *reuse(size_t size)
{
    // TODO: using free space management (FSM) algorithms, find a block of
    // memory that we can reuse. Return NULL if no suitable block is found.
    return NULL;
}

void *malloc_impl(size_t size, char *name)
{
    // TODO: allocate memory. You'll first check if you can reuse an existing
    // block. If not, map a new memory region.

    return NULL;
}

void free_impl(void *ptr)
{
    if (ptr == NULL) {
        /* Freeing a NULL pointer does nothing */
        return;
    }

    // TODO: free memory. If the containing region is empty (i.e., there are no
    // more blocks in use), then it should be unmapped.
}

void *calloc_impl(size_t nmemb, size_t size, char *name)
{
    // TODO: hmm, what does calloc do?
    return NULL;
}

void *realloc_impl(void *ptr, size_t size, char *name)
{
    if (ptr == NULL) {
        /* If the pointer is NULL, then we simply malloc a new block */
        return malloc_impl(size, name);
    }

    if (size == 0) {
        /* Realloc to 0 is often the same as freeing the memory block... But the
         * C standard doesn't require this. We will free the block and return
         * NULL here. */
        free_impl(ptr);
        return NULL;
    }

    // TODO: reallocation logic

    return NULL;
}

/**
 * print_memory
 *
 * Prints out the current memory state, including both the regions and blocks.
 * Entries are printed in order, so there is an implied link from the topmost
 * entry to the next, and so on.
 *
 * Format:
 *
 *    -- Current Memory State --
 *    [REGION <region no>] <start addr>
 *      [BLOCK] <block no> <start addr>-<end addr> '<name>' <block-size> [FREE]
 *      [BLOCK] <block no> <start addr>-<end addr> '<name>' <block-size> [USED]
 *      [BLOCK] <block no> <start addr>-<end addr> '<name>' <block-size> [FREE]
 *    [REGION <region no>] <start addr>
 *      [BLOCK] <block no> <start addr>-<end addr> '<name>' <block-size> [USED]
 */
void print_memory(void)
{
    // TODO implement memory printout
}
