

void signal_handler(int sig, siginfo_t *info, void *context)
{
    static char utf8_buffer[4] = {0};
    static int utf8_index = 0;
    static int utf8_start = 0;
    static pid_t client_pid = -1;
	static char k = 7;
	static char c = 0;

    (void)context;
    if (client_pid == -1)
        client_pid = info->si_pid;
    else if (client_pid != info->si_pid) {
        utf8_index = 0;
        utf8_start = 0;
		c = 0;
		k = 7;
        client_pid = info->si_pid;
    }
    if (sig == SIGUSR1)
		c += 0 << k;
	else
		c += 1 << k;
	k--;
	if (k == -1)
	{    
		if (utf8_index == 0 && (c & 0xF0) == 0xF0)
       		utf8_start = 1;
		if (utf8_start)
		{
        	utf8_buffer[utf8_index] = c;
        	utf8_index++;
    	}
		else
		{
        	write(1, &c, 1);
        	send_back_sig(c, client_pid);
    	}
    	if (utf8_index == 4)
		{
        	write(1, utf8_buffer, utf8_index);
        	send_back_sig(utf8_buffer[0], client_pid);
        	utf8_index = 0;
        	utf8_start = 0;
        	for (int i = 0; i < 4; i++)
            	utf8_buffer[i] = 0;
    	}
		k = 7;
		c = 0;
	}
}