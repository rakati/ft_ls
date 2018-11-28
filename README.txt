#README

the structure of the folowing project should be made clear here.

1- a struct will have all the info about input, so we can know what flags are
activated;
2- a function will first check if flag -R is set, then decide to call the main
directory listing function on which folders;
3- the function that gets info will see if flag -l is specified
then gets only info that needs to be displayed
4- a function will print the data we got depending on output type -l or normal
while also sorting the results if -t is specified



--------WHAT IS DONE UNTIL NOW------

i have added functions to get data, i can now print data in the form of ls -l
i can also print in normal mode

what is to do now is to try to sort files using -t and -r
also last thing is recursivity with -R

compile with :
	/*  gcc -Wall -Wextra -Werror *.c libft/libft.a 
libft/ft_printf/libftprintf.a -I./libft*/


-------ls -l fields---------

// a little analysis of the ls -l output

-rw-r--r--  1 abiri  candidate   403 Nov 23 14:32 README.md
Rights  | \ |user |group		| / |date        | name
		  /						  \
number of links				size in bytes
or sudirectories


----------stat struct--------

// stat is a function that returns information about file and
// directories, which are date of creation etc...
// the structure that is used to store stat data is as follows

struct stat {
	dev_t           st_dev;           /* ID of device containing file */
	mode_t          st_mode;          /* Mode of file (see below) */
	nlink_t         st_nlink;         /* Number of hard links */
	ino_t           st_ino;           /* File serial number */
	uid_t           st_uid;           /* User ID of the file */
	gid_t           st_gid;           /* Group ID of the file */
	dev_t           st_rdev;          /* Device ID */
	struct timespec st_atimespec;     /* time of last access */
	struct timespec st_mtimespec;     /* time of last data modification */
	struct timespec st_ctimespec;     /* time of last status change */
	struct timespec st_birthtimespec; /* time of file creation(birth) */
	off_t           st_size;          /* file size, in bytes */
	blkcnt_t        st_blocks;        /* blocks allocated for file */
	blksize_t       st_blksize;       /* optimal blocksize for I/O */
	uint32_t        st_flags;         /* user defined flags for file */
	uint32_t        st_gen;           /* file generation number */
	int32_t         st_lspare;        /* RESERVED: DO NOT USE! */
	int64_t         st_qspare[2];     /* RESERVED: DO NOT USE! */
};

--------timespec struct--------

struct timespec
{
	time_t tv_sec;  // whole seconds (valid values are >= 0)
	long tv_nsec;	// nanoseconds (valid values are [0, 999999999])
}

// tv_sec is very useful, getting hh/mm of modification or creation is easy
// the problem in conversions is getting the month

------------ctime--------------

// ctime is a very useful function that converts unix timestamp to human
// readable date.

-----getpwuid and getgrgid------

// these two functions return struct passwd and group
// this struct is as follows

struct passwd {
	char    *pw_name;       /* user name */
	char    *pw_passwd;     /* encrypted password */
	uid_t   pw_uid;         /* user uid */
	gid_t   pw_gid;         /* user gid */
	time_t  pw_change;      /* password change time */
	char    *pw_class;      /* user access class */
	char    *pw_gecos;      /* Honeywell login info */
	char    *pw_dir;        /* home directory */
	char    *pw_shell;      /* default shell */
	time_t  pw_expire;      /* account expiration */
	int     pw_fields;      /* internal: fields filled in */
};

struct group {
	char    *gr_name;       /* group name */
	char    *gr_passwd;     /* group password */
	gid_t   gr_gid;         /* group id */
	char    **gr_mem;       /* group members */
};

-----------listxattr------------

// listxattr is defined as follows

ssize_t
     listxattr(const char *path, char *namebuf, size_t size, int options);

----------type of the file-------

//	file type is defined in stat struct in st_mode
//	using an & logical operator with these defines

#define S_IFMT 0170000           /* type of file */
     #define        S_IFIFO  0010000  /* named pipe (fifo) */
     #define        S_IFCHR  0020000  /* character special */
     #define        S_IFDIR  0040000  /* directory */
     #define        S_IFBLK  0060000  /* block special */
     #define        S_IFREG  0100000  /* regular */
     #define        S_IFLNK  0120000  /* symbolic link */
     #define        S_IFSOCK 0140000  /* socket */
     #define        S_IFWHT  0160000  /* whiteout */
     #define S_ISUID 0004000  /* set user id on execution */
     #define S_ISGID 0002000  /* set group id on execution */
     #define S_ISVTX 0001000  /* save swapped text even after use */
     #define S_IRUSR 0000400  /* read permission, owner */
     #define S_IWUSR 0000200  /* write permission, owner */
     #define S_IXUSR 0000100  /* execute/search permission, owner */

// S_IFMT is a bit mask to extract file type information from mode
// apply bit mask with (mode & S_IFMT) then compare the result to
// S_IFIFO , S_IFREG...

// some masks for paermissions are not in the man
// S_IRGRP S_IWGRP S_IXGRP , 

------readlink is as follows-------

ssize_t
     readlink(const char *restrict path, char *restrict buf, size_t bufsize);

-------opendir and readdir---------

// opendir returns a struct DIR
// readdir returns a struct dirent which is a follows

struct dirent {
             ino_t      d_fileno;     /* file number of entry */
             __uint64_t d_seekoff;    /* seek offset (optional, used by servers) */
             __uint16_t d_reclen;     /* length of this record */
             __uint16_t d_namlen;     /* length of string in d_name */
             __uint8_t  d_type;       /* file type, see below */
             char    d_name[1024];    /* name must be no longer than this */
     };
