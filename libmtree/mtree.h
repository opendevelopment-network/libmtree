/*-
 * Copyright (c) 2015 Michal Ratajsky <michal@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _LIBMTREE_MTREE_H_
#define _LIBMTREE_MTREE_H_

#include <sys/types.h>
#include <sys/stat.h>

#include <inttypes.h>

struct mtree_device;

typedef struct _mtree_entry	mtree_entry;
typedef struct _mtree_spec	mtree_spec;
typedef struct _mtree_spec_diff	mtree_spec_diff;

/*
 * Spec entry types
 */
typedef enum {
	MTREE_ENTRY_BLOCK,
	MTREE_ENTRY_CHAR,
	MTREE_ENTRY_DIR,
	MTREE_ENTRY_FIFO,
	MTREE_ENTRY_FILE,
	MTREE_ENTRY_LINK,
	MTREE_ENTRY_SOCKET,
	MTREE_ENTRY_UNKNOWN
} mtree_entry_type;

/*
 * Writing format
 */
typedef enum {
	MTREE_FORMAT_DEFAULT,
	MTREE_FORMAT_1_0,
	MTREE_FORMAT_2_0,
	MTREE_FORMAT_2_0_PATH_LAST,
	MTREE_FORMAT_DIFF_FIRST,
	MTREE_FORMAT_DIFF_SECOND,
	MTREE_FORMAT_DIFF_DIFFER
} mtree_format;

typedef enum {
	MTREE_DEVICE_386BSD,
	MTREE_DEVICE_4BSD,
	MTREE_DEVICE_BSDOS,
	MTREE_DEVICE_FREEBSD,
	MTREE_DEVICE_HPUX,
	MTREE_DEVICE_ISC,
	MTREE_DEVICE_LINUX,
	MTREE_DEVICE_NATIVE,
	MTREE_DEVICE_NETBSD,
	MTREE_DEVICE_OSF1,
	MTREE_DEVICE_SCO,
	MTREE_DEVICE_SOLARIS,
	MTREE_DEVICE_SUNOS,
	MTREE_DEVICE_SVR3,
	MTREE_DEVICE_SVR4,
	MTREE_DEVICE_ULTRIX
} mtree_device_format;

/*
 * Spec entry keywords
 */
#define MTREE_KEYWORD_CKSUM		0x00000001
#define MTREE_KEYWORD_CONTENTS		0x00000002
#define MTREE_KEYWORD_DEVICE		0x00000004
#define MTREE_KEYWORD_FLAGS		0x00000008
#define MTREE_KEYWORD_GID		0x00000010
#define MTREE_KEYWORD_GNAME		0x00000020
#define MTREE_KEYWORD_IGNORE		0x00000040
#define MTREE_KEYWORD_INODE		0x00000080
#define MTREE_KEYWORD_LINK		0x00000100
#define MTREE_KEYWORD_MD5		0x00000200
#define MTREE_KEYWORD_MD5DIGEST		0x00000400
#define MTREE_KEYWORD_MODE		0x00000800
#define MTREE_KEYWORD_NLINK		0x00001000
#define MTREE_KEYWORD_NOCHANGE		0x00002000
#define MTREE_KEYWORD_OPTIONAL		0x00004000
#define MTREE_KEYWORD_RIPEMD160DIGEST	0x00008000
#define MTREE_KEYWORD_RMD160		0x00010000
#define MTREE_KEYWORD_RMD160DIGEST	0x00020000
#define MTREE_KEYWORD_SHA1		0x00040000
#define MTREE_KEYWORD_SHA1DIGEST	0x00080000
#define MTREE_KEYWORD_SHA256		0x00100000
#define MTREE_KEYWORD_SHA256DIGEST	0x00200000
#define MTREE_KEYWORD_SHA384		0x00400000
#define MTREE_KEYWORD_SHA384DIGEST	0x00800000
#define MTREE_KEYWORD_SHA512		0x01000000
#define MTREE_KEYWORD_SHA512DIGEST	0x02000000
#define MTREE_KEYWORD_SIZE		0x04000000
#define MTREE_KEYWORD_TAGS		0x08000000
#define MTREE_KEYWORD_TIME		0x10000000
#define MTREE_KEYWORD_TYPE		0x20000000
#define MTREE_KEYWORD_UID		0x40000000
#define MTREE_KEYWORD_UNAME		0x80000000

/*
 * Reading options
 */
#define MTREE_READ_SKIP_FILE		0x01
#define MTREE_READ_SKIP_DIR		0x02
#define MTREE_READ_SKIP_LINK		0x04
#define MTREE_READ_SKIP_BLOCK		0x08
#define MTREE_READ_SKIP_CHAR		0x10
#define MTREE_READ_SKIP_FIFO		0x20
#define MTREE_READ_SKIP_SOCKET		0x40
#define MTREE_READ_SKIP_ALL		0x7F
#define MTREE_READ_SKIP_ON_ERROR	0x100

/*
 * Path reading options
 */
#define MTREE_READ_PATH_ABSOLUTE	0x01
#define MTREE_READ_PATH_DONT_RECURSE	0x04
#define MTREE_READ_PATH_DONT_CROSS_DEV	0x08
#define MTREE_READ_PATH_FOLLOW_SYMLINKS	0x10

/*
 * Writing options
 */
#define MTREE_WRITE_USE_SET		0x02
#define MTREE_WRITE_INDENT		0x04
#define MTREE_WRITE_INDENT_LEVEL	0x08
#define MTREE_WRITE_SPLIT_LONG_LINES	0x10
#define MTREE_WRITE_DIR_COMMENTS	0x20
#define MTREE_WRITE_DIR_BLANK_LINES	0x40

/*
 * Digest types
 */
#define MTREE_DIGEST_MD5		0x01
#define MTREE_DIGEST_RMD160		0x02
#define MTREE_DIGEST_SHA1		0x04
#define MTREE_DIGEST_SHA256		0x08
#define MTREE_DIGEST_SHA384		0x10
#define MTREE_DIGEST_SHA512		0x20

/*
 * Device fields
 */
#define MTREE_DEVICE_FIELD_NUMBER	0x01
#define MTREE_DEVICE_FIELD_MAJOR	0x02
#define MTREE_DEVICE_FIELD_MINOR	0x04
#define MTREE_DEVICE_FIELD_UNIT		0x08
#define MTREE_DEVICE_FIELD_SUBUNIT	0x10

#define MTREE_KEYWORD_MASK_ALL		(MTREE_KEYWORD_CKSUM |		\
					 MTREE_KEYWORD_CONTENTS |	\
					 MTREE_KEYWORD_DEVICE |		\
					 MTREE_KEYWORD_FLAGS |		\
					 MTREE_KEYWORD_GID |		\
					 MTREE_KEYWORD_GNAME |		\
					 MTREE_KEYWORD_IGNORE |		\
					 MTREE_KEYWORD_INODE |		\
					 MTREE_KEYWORD_LINK |		\
					 MTREE_KEYWORD_MASK_MD5 |	\
					 MTREE_KEYWORD_MODE |		\
					 MTREE_KEYWORD_NLINK |		\
					 MTREE_KEYWORD_NOCHANGE |	\
					 MTREE_KEYWORD_OPTIONAL |	\
					 MTREE_KEYWORD_MASK_RMD160 |	\
					 MTREE_KEYWORD_MASK_SHA1 |	\
					 MTREE_KEYWORD_MASK_SHA256 |	\
					 MTREE_KEYWORD_MASK_SHA384 |	\
					 MTREE_KEYWORD_MASK_SHA512 |	\
					 MTREE_KEYWORD_SIZE |		\
					 MTREE_KEYWORD_TAGS |		\
					 MTREE_KEYWORD_TIME |		\
					 MTREE_KEYWORD_TYPE |		\
					 MTREE_KEYWORD_UID |		\
					 MTREE_KEYWORD_UNAME)

#define MTREE_KEYWORD_MASK_DEFAULT	(MTREE_KEYWORD_FLAGS |		\
					 MTREE_KEYWORD_GID |		\
					 MTREE_KEYWORD_LINK |		\
					 MTREE_KEYWORD_MODE |		\
					 MTREE_KEYWORD_NLINK |		\
					 MTREE_KEYWORD_SIZE |		\
					 MTREE_KEYWORD_TIME |		\
					 MTREE_KEYWORD_TYPE |		\
					 MTREE_KEYWORD_UID)

#define MTREE_KEYWORD_MASK_MD5		(MTREE_KEYWORD_MD5 |		\
					 MTREE_KEYWORD_MD5DIGEST)
#define MTREE_KEYWORD_MASK_SHA1		(MTREE_KEYWORD_SHA1 |		\
					 MTREE_KEYWORD_SHA1DIGEST)
#define MTREE_KEYWORD_MASK_SHA256	(MTREE_KEYWORD_SHA256 |		\
					 MTREE_KEYWORD_SHA256DIGEST)
#define MTREE_KEYWORD_MASK_SHA384	(MTREE_KEYWORD_SHA384 |		\
					 MTREE_KEYWORD_SHA384DIGEST)
#define MTREE_KEYWORD_MASK_SHA512	(MTREE_KEYWORD_SHA512 |		\
					 MTREE_KEYWORD_SHA512DIGEST)
#define MTREE_KEYWORD_MASK_RMD160	(MTREE_KEYWORD_RMD160 |		\
					 MTREE_KEYWORD_RMD160DIGEST |	\
					 MTREE_KEYWORD_RIPEMD160DIGEST)

struct mtree_device	*mtree_device_create(void);
struct mtree_device	*mtree_device_copy(struct mtree_device *dev);
void			 mtree_device_free(struct mtree_device *dev);
mtree_device_format	 mtree_device_get_format(struct mtree_device *dev);
void			 mtree_device_set_format(struct mtree_device *dev,
			    mtree_device_format format);
dev_t			 mtree_device_get_value(struct mtree_device *dev, int field);
void			 mtree_device_set_value(struct mtree_device *dev, int field,
			    dev_t value);
int			 mtree_device_get_fields(struct mtree_device *dev);
void			 mtree_device_unset_fields(struct mtree_device *dev,
			    int fields);

mtree_entry 	*mtree_entry_get_first(mtree_entry *entry);
mtree_entry 	*mtree_entry_get_last(mtree_entry *entry);
mtree_entry 	*mtree_entry_get_previous(mtree_entry *entry);
mtree_entry 	*mtree_entry_get_next(mtree_entry *entry);
mtree_entry	*mtree_entry_get_parent(mtree_entry *entry);

const char	*mtree_entry_get_name(mtree_entry *entry);
const char	*mtree_entry_get_path(mtree_entry *entry);
long		 mtree_entry_get_keywords(mtree_entry *entry);

uint32_t	 mtree_entry_get_cksum(mtree_entry *entry);
gid_t		 mtree_entry_get_gid(mtree_entry *entry);
const char	*mtree_entry_get_gname(mtree_entry *entry);
const char	*mtree_entry_get_link(mtree_entry *entry);
const char	*mtree_entry_get_md5digest(mtree_entry *entry);
mode_t		 mtree_entry_get_mode(mtree_entry *entry);
nlink_t		 mtree_entry_get_nlink(mtree_entry *entry);
const char 	*mtree_entry_get_rmd160digest(mtree_entry *entry);
const char 	*mtree_entry_get_sha1digest(mtree_entry *entry);
const char 	*mtree_entry_get_sha256digest(mtree_entry *entry);
const char 	*mtree_entry_get_sha384digest(mtree_entry *entry);
const char 	*mtree_entry_get_sha512digest(mtree_entry *entry);
off_t		 mtree_entry_get_size(mtree_entry *entry);
struct timespec *mtree_entry_get_time(mtree_entry *entry);
mtree_entry_type mtree_entry_get_type(mtree_entry *entry);
uid_t		 mtree_entry_get_uid(mtree_entry *entry);
const char	*mtree_entry_get_uname(mtree_entry *entry);
void		 mtree_entry_set_keywords(mtree_entry *entry, long keywords,
		    int overwrite);
mtree_entry 	*mtree_entry_find_path(mtree_entry *entry, const char *path);

mtree_spec	*mtree_spec_create(void);
void		 mtree_spec_free(mtree_spec *spec);
void		 mtree_spec_reset(mtree_spec *spec);
mtree_entry	*mtree_spec_get_entries(mtree_spec *spec);
int		 mtree_spec_read_data(mtree_spec *spec, const char *data, int len);
int		 mtree_spec_read_data_end(mtree_spec *spec);
int		 mtree_spec_read_path(mtree_spec *spec, const char *path);
void		 mtree_spec_set_read_options(mtree_spec *spec, int options);
void		 mtree_spec_set_read_keywords(mtree_spec *spec, long keywords);
void		 mtree_spec_set_write_format(mtree_spec *spec, mtree_format format);
void		 mtree_spec_set_write_options(mtree_spec *spec, int options);

mtree_spec_diff *mtree_spec_diff_create(mtree_spec *spec1, mtree_spec *spec2);
void		 mtree_spec_diff_free(mtree_spec_diff *sd);
mtree_entry	*mtree_spec_diff_get_spec1_only(mtree_spec_diff *sd);
mtree_entry	*mtree_spec_diff_get_spec2_only(mtree_spec_diff *sd);
mtree_entry	*mtree_spec_diff_get_different(mtree_spec_diff *sd);

long		 mtree_keyword_parse(const char *keyword);
const char	*mtree_keyword_string(long keyword);
mtree_entry_type mtree_entry_type_parse(const char *type);
const char	*mtree_entry_type_string(mtree_entry_type type);

#endif /* !_LIBMTREE_MTREE_H_ */
