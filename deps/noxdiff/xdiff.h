/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

/*
 * The no-xdiff build (see README.md).
 *
 * Upstream libgit2 bundles LibXDiff in deps/xdiff and compiles it into the
 * library.  This fork does not: deps/xdiff is deleted, and this header
 * stands in for it.  It declares only the names that libgit2's own sources
 * (diff_xdiff.c, merge_file.c, blame_git.c, patch_generate.c) refer to, so
 * that those files compile unchanged.  None of it carries any behaviour:
 * the two functions are defined in noxdiff.c and always fail.
 *
 * Nothing here is copied from LibXDiff.  The field names are the ones
 * libgit2's sources use; the numeric values only need to be distinct bits,
 * because nothing in this build interprets them.
 */

#ifndef INCLUDE_noxdiff_xdiff_h__
#define INCLUDE_noxdiff_xdiff_h__

/* Diff option bits that libgit2 sets in xpparam_t.flags. */
#define XDF_NEED_MINIMAL              (1 << 0)
#define XDF_IGNORE_WHITESPACE         (1 << 1)
#define XDF_IGNORE_WHITESPACE_CHANGE  (1 << 2)
#define XDF_IGNORE_WHITESPACE_AT_EOL  (1 << 3)
#define XDF_IGNORE_BLANK_LINES        (1 << 4)
#define XDF_PATIENCE_DIFF             (1 << 5)
#define XDF_INDENT_HEURISTIC          (1 << 6)
#define XDF_WHITESPACE_FLAGS \
	(XDF_IGNORE_WHITESPACE | XDF_IGNORE_WHITESPACE_CHANGE | XDF_IGNORE_WHITESPACE_AT_EOL)

/* Emit option bits that libgit2 sets in xdemitconf_t.flags. */
#define XDL_EMIT_FUNCNAMES            (1 << 0)

/* Merge levels, favour modes and styles that libgit2 sets in xmparam_t. */
#define XDL_MERGE_ZEALOUS             1
#define XDL_MERGE_ZEALOUS_ALNUM       2
#define XDL_MERGE_FAVOR_OURS          1
#define XDL_MERGE_FAVOR_THEIRS        2
#define XDL_MERGE_FAVOR_UNION         3
#define XDL_MERGE_DIFF3               1
#define XDL_MERGE_ZEALOUS_DIFF3       2

/* A span of bytes: an input file, or one piece of emitted output. */
typedef struct {
	char *ptr;
	long size;
} mmfile_t;

typedef mmfile_t mmbuffer_t;

typedef struct {
	unsigned long flags;
} xpparam_t;

typedef struct {
	void *priv;
	int (*out_line)(void *priv, mmbuffer_t *buffers, int count);
} xdemitcb_t;

typedef struct {
	long ctxlen;
	long interhunkctxlen;
	unsigned long flags;
	long (*find_func)(const char *line, long line_len,
		char *buffer, long buffer_size, void *priv);
	void *find_func_priv;
	int (*hunk_func)(long start_a, long count_a,
		long start_b, long count_b, void *priv);
} xdemitconf_t;

typedef struct {
	xpparam_t xpp;
	int marker_size;
	int level;
	int favor;
	int style;
	const char *ancestor;
	const char *file1;
	const char *file2;
} xmparam_t;

/* Both always return -1 and set a libgit2 error.  See noxdiff.c. */
int xdl_diff(mmfile_t *old_file, mmfile_t *new_file,
	xpparam_t const *params, xdemitconf_t const *config,
	xdemitcb_t *callback);

int xdl_merge(mmfile_t *ancestor, mmfile_t *ours, mmfile_t *theirs,
	xmparam_t const *params, mmbuffer_t *result);

#endif
