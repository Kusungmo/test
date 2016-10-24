#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/kdev_t.h>
#include <linux/poll.h>
#include <signal.h>

#include "key_driver.h"

void main()
{
	int		fd;
	char		led_onoff = 0;
	char		key;
	struct pollfd	events[2];
	int		retval;

	fd = open(, O_RDWR|O_NONBLOCK);

	while (1)
	{
		events[0].fd		= fd;
		events[0].events	= POLLIN;	// waiting read

		retval = poll(events, 1, 1000);		// event waiting
		if (retval < 0)
		{
			perror("Poll_test");
			exit(0);
		}

		if (retval == 0)
		{
			puts("[APP] LED Off!!");
			led_onoff = 0;
			write(fd, &led_onoff, 1);
		}

		if (events[0].revents & POLLIN)
		{
			//puts("[APP] Wakeup_Poll_Event!!\n");
			led_onoff = 1;
			write(fd, &led_onoff, 1);

			read(fd, &key, 1);
			printf("[APP] KEY: %d\n", key);

			sleep(2);
		}
	}

	led_onoff = 0;
	write(fd, &led_onoff, 1);

	close(fd);
}

