#ifndef INCLUDE_libdiff_h__
#define INCLUDE_libdiff_h__

#include "../common.h"

/*
 * Represents the variables required to run the diffing
 * algorithm. For example, an array longs that hold the hashed
 * value of every line in the data we're diffing, as well as
 * the number of records are kept here.
 */
struct diff_environment {
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
typedef struct diff_environment diff_environment;

struct algo_environment {
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
typedef struct algo_environment algo_environment;

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

int diff(diff_mem_data *data1, diff_mem_data *data2,
		git_diffresults_conf const *results_conf);

#endif
