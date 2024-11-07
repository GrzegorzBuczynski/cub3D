

int open_file(const char *filename, int flags, int mode)
{
	int fd = open(filename, flags, mode);
	if (fd < 0) {
		perror("open");
		exit(1);
	}
	return fd;
}