/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

/*
 * The two entry points libgit2 calls into LibXDiff through, defined so that
 * the library links without LibXDiff.  Each does no work and fails.
 *
 * What that disables: generating a text patch (git_patch_*, git_diff_print
 * in patch format, git_diff_foreach -- which builds a patch per file even
 * without hunk callbacks, so git_index_add_all and git_index_update_all go
 * with it -- git_diff_stats, git_diff_buffers, git_diff_blobs), blame, and
 * the textual
 * three-way merge (git_merge_file*, and the text merge driver that
 * git_merge, git_cherrypick, git_revert and git_rebase use on conflicting
 * files).  Each of those returns an error rather than a wrong answer.
 *
 * What still works: everything that does not produce hunks, including
 * repository init, the index, commits, trees, refs, config, the list of
 * changed files from git_diff_* (git_diff_num_deltas / git_diff_get_delta),
 * status, fetch and push.
 */

#include "common.h"
#include "xdiff.h"

static int noxdiff_unavailable(const char *what)
{
	git_error_set(GIT_ERROR_INVALID,
		"%s is unavailable: this libgit2 is built without xdiff", what);
	return -1;
}

int xdl_diff(mmfile_t *old_file, mmfile_t *new_file,
	xpparam_t const *params, xdemitconf_t const *config,
	xdemitcb_t *callback)
{
	GIT_UNUSED(old_file);
	GIT_UNUSED(new_file);
	GIT_UNUSED(params);
	GIT_UNUSED(config);
	GIT_UNUSED(callback);
	return noxdiff_unavailable("text diff");
}

int xdl_merge(mmfile_t *ancestor, mmfile_t *ours, mmfile_t *theirs,
	xmparam_t const *params, mmbuffer_t *result)
{
	GIT_UNUSED(ancestor);
	GIT_UNUSED(ours);
	GIT_UNUSED(theirs);
	GIT_UNUSED(params);
	if (result) {
		result->ptr = NULL;
		result->size = 0;
	}
	return noxdiff_unavailable("text merge");
}
