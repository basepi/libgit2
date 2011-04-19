#ifndef INCLUDE_difftypes_h__
#define INCLUDE_difftypes_h__

#include "../common.h"

struct mem_store_node {
	struct mem_store_iter *next;
	long curr_idx;
};
typedef struct mem_store_node mem_store_node;

// TODO: ADD COMMENT HERE
// Equivalent to chastore_t
struct mem_store {
	// head and tail initially point to ancur; as we allocate more
	// memory, the tail and head grow apart, but the alloc'd
	// memory is linked by the chanode_t->next links, which usually
	// point to the first address in the chastore allocated blocks
	mem_store_node *head, *tail;
	// See xdl_cha_init:
	// - isize is the # of bytes in the sort of struct we're using
	long unit_size;
	// - nsize is the # of bytes we want to reserve for the store,
	// usually isize * the number of objects we want to store
	long store_size;
	// Handles all the allocation of new memory from the chastore
	// usually via xdl_cha_init()
	mem_store_node *ancur;
	// Handles traversal of chastore objects
	mem_store_node *sncur;
	// initially 0
	long scurr;
};
typedef struct mem_store mem_store;

// TODO: FIGURE OUT WHAT THE EFF THIS DOES (I forgot)
// TODO: ADD COMMENT HERE
// Equivalent to xdlclass_t
struct classd_record {
/*
	struct s_xdlclass *next;
	unsigned long ha;
	char const *line;
	long size;
	long idx;
*/
};
typedef struct classd_record classd_record;

// TODO: FIGURE OUT WHAT THE EFF THIS DOES (I forgot)
// TODO: ADD COMMENT HERE
// Equivalent to xdlclassifier_t
struct record_classifier {
	// Used to find hsize -- the smallest power of 2 greater than param
	// size in xdl_init_classifier
	unsigned int hbits;
	// Size of hash table rchash
	long table_size;
	// Hash table of classd_records
	classd_record **classd_hash;
	// The memory that rchash resides in
	// TODO: IMPLEMENT chastore; not implemented yet
	//chastore_t table_memory;
	// Number of elements in rchash
	long count;

	// TODO: CLEANUP, definitely not needed
	//long flags;
};
typedef struct record_classifier record_classifier;

// TODO: ADD COMMENT HERE
// Equivalent to xdfile_t
struct data_context {
	// TODO: IMPLEMENT THIS MINIMALLY
/*
	chastore_t rcha;
	// Number of records, which is DEFINITLY
	// lines
	long nrec;
	// Size of rhash???
	unsigned int hbits;
	// A hash table of xrecord pointers; build in
	// xdl_prepare_ctx()
	xrecord_t **rhash;
	// D-path start and end
	long dstart, dend;
	// All records
	xrecord_t **recs;
	// In xdl_recs_cmp, each of these chars is set to a "weight" -- usually
	// 0 or 1 depending on whether that particular record has changed. So
	// it's basically a bit vector made of chars
	char *rchg;
	// An ARRAY of longs that represent hashes; in xdl_recs_cmp(),
	// we access it as an array.
	long *rindex;
	// # of records * size of records???
	long nreff;
	// A hash of the entire xdfile contents
	unsigned long *ha;
*/
};
typedef struct data_context data_context;

/*
 * Represents the variables required to run the diffing
 * algorithm. For example, an array longs that hold the hashed
 * value of every line in the data we're diffing, as well as
 * the number of records are kept here.
 */
struct diff_environment {
	// TODO: IMPLEMENT THIS MINIMALLY
	data_context data_ctx1, data_ctx2;
	// Flags points to the flags member of git_diffresults_conf,
	// and is usually set in diff()
	unsigned long *flags;
/*
	chastore_t rcha;
	// Number of records, which is DEFINITLY
	// lines
	long nrec;
	// Size of rhash???
	unsigned int hbits;
	// A hash table of xrecord pointers; build in
	// xdl_prepare_ctx()
	xrecord_t **rhash;
	// D-path start and end
	long dstart, dend;
	// All records
	xrecord_t **recs;
	// In xdl_recs_cmp, each of these chars is set to a "weight" -- usually
	// 0 or 1 depending on whether that particular record has changed. So
	// it's basically a bit vector made of chars
	char *rchg;
	// An ARRAY of longs that represent hashes; in xdl_recs_cmp(),
	// we access it as an array.
	long *rindex;
	// # of records * size of records???
	long nreff;
	// A hash of the entire xdfile contents
	unsigned long *ha;
*/
};
typedef struct diff_environment diff_environment;

/*
 * Represents the inner variables required to run Myers O(ND)
 * diffing algorithm. This includes guiding information like
 * the maximum cost we're willing to incur before we switch
 * to a slightly different version of O(ND).
 */
struct myers_conf {
	// TODO: FIX THESE VAR NAMES
	// mAxcost, thanks for the var name asshole
	// maxcost is the square root of L (which
	// xdiffi.c calls "ndiags"), unless L < 256,
	// in which case, it becomes 256. We use this
	// to determine when our LCS traversal has
	// become too expensive, at which point we
	// switch to ... uh... something else
	long mxcost;
	long snake_cnt;
	long heur_min;
};
typedef struct myers_conf myers_conf;

/*
 * Represents file data (binary or text) in memory. Often
 * instances of these structs are the direct objects that
 * diffing is performed on.
 *
 * Typedef'd as both git_diff_m_data and git_diff_m_buffer,
 * which are identical in execution, but conceptually different
 * and follow a different pipeline.
 */
struct diff_mem {
	size_t size;
	char *data;
};
typedef struct diff_mem diff_mem_data;
typedef struct diff_mem diff_mem_buffer;

/*
 * Callback function; called directly after we perform the
 * diff and the output is assembled according to options
 * specified in the git_diff_out_conf struct.
 */
struct git_diff_callback {
	void *payload;
	int (*out_func)(void *, diff_mem_buffer *, int);
};
typedef struct git_diff_callback git_diff_callback;

/*
 * Fully configures not just how we generate diff's results,
 * but also *where* they go, and what form they take.
 */
struct git_diffresults_conf {
	// unique flags correspond to specific bit positions in 'flags'
	// TODO: find out if this should be a size_t
	unsigned long flags;
	git_diff_callback *callback;
	void (*results_hndlr)();
};
// typdef'd in include/types.h -- part of the public API

/*
 * Changeset generated by diff; used for things like "merge"
 *
 * TODO: find out if this should really be part of the public-
 * facing API.
 */
struct git_changeset {
	// TODO: fix the member names here so they make more sense
	struct git_changeset *next;
	long i1, i2;
	long chg1, chg2;
};
// typdef'd in include/types.h -- part of the public API

/*
 * Callback funciton that determines what we do with results;
 * e.g., in the normal case of printing the diff to std out,
 * this function will "assemble" the results into the correct
 * string, and then ship them to the git_diff_callback function
 * pointer to print them.
 */
typedef int (*diff_results_hndlr)(diff_environment *diff_env,
		git_changeset *diff, git_diff_callback *diff_cb,
		git_diffresults_conf const *results_conf);

#endif

