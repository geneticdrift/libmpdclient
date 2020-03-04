/* libmpdclient
   (c) 2003-2019 The Music Player Daemon Project
   This project's homepage is: http://www.musicpd.org

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   - Neither the name of the Music Player Daemon nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*! \file
 * \brief MPD client library
 *
 * Do not include this header directly.  Use mpd/client.h instead.
 */

#ifndef MPD_TAGSTATS_H
#define MPD_TAGSTATS_H

#include "compiler.h"

#include "mpd/tag.h"

#include <stdbool.h>

struct mpd_connection;
struct mpd_pair;

/**
 * \struct mpd_tagstats
 *
 * An opaque object representing MPD's response to the "tagstats"
 * command.  To release this object, call mpd_tagstats_free().
 */
struct mpd_tagstats;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Send the "tagstats" command to MPD. Call mpd_recv_tagstats() to read the response.
 *
 * @return true on success
 */
bool
mpd_send_tagstats(struct mpd_connection *connection);

/**
 * Begins parsing tagstats: creates a new empty #mpd_tagstats object.
 * Free it with mpd_tagstats_free().
 *
 * @return the newly allocated #mpd_tagstats object, or NULL if out of
 * memory
 */
mpd_malloc
struct mpd_tagstats *
mpd_tagstats_begin(void);

/**
 * Parses the pair, adding its information to the specified #mpd_tagstats
 * object.
 */
void
mpd_tagstats_feed(struct mpd_tagstats *status, const struct mpd_pair *pair);

/**
 * Reads the "stats" response from MPD.
 *
 * @return a #mpd_tagstats object, or NULL on error
 */
mpd_malloc
struct mpd_tagstats *
mpd_recv_tagstats(struct mpd_connection *connection);

/**
 * Shortcut for mpd_send_tagstats() and mpd_recv_tagstats().
 */
mpd_malloc
struct mpd_tagstats *
mpd_run_tagstats(struct mpd_connection *connection);

/**
 * Frees a #mpd_tagstats object.
 */
void mpd_tagstats_free(struct mpd_tagstats *stats);

/**
 * @return the number of distinct values of tag type in MPD's database, or 0 if
 * unknown
 */
unsigned
mpd_tagstats_get_number_of_values(const struct mpd_tagstats *stats,
								  enum mpd_tag_type type);

#ifdef __cplusplus
}
#endif

#endif
