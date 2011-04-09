/**
 * diff Implements the Myers O(ND) diff algorithm and the public API
 *
 * @author Alex Clemmer <clemmer.alexander@gmail.com>
 * @author Landon Gilbert-Bland <landogbland@gmail.com>
 * @author Andrew Kuhnhausen <andrew.kuhnhausen@gmail.com>
 * @author Colton Myers <colton.myers@gmail.com>
 */

#ifndef INCLUDE_diff_h__
#define INCLUDE_diff_h__

/**
 * \struct git_diff_data
 * Represents the metadata for the diff
 */
typedef struct {
    /*! The number of records (lines) in the content */
    long num_records;
    /*! Ordered list of hashed records */
    unsigned long const *hashed_records;
    /*! The index of the record in the content */
    long *record_index;
    /*! The set of records that have changed, represented by 1: changed */
    char *records_changed;
} git_diff_data;

typedef struct s_middle_edit {
    // begin..end of sequences a, b
    const long *begin_a, *end_a, *begin_b, *end_b;
    // the difference value of begin b, a
    const long *k;
} middle_edit;
/**
 * @brief Find minimal paths by bisecting the sequences a, b
 */

/**
 * @brief
 */


#endif
