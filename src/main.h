#ifndef _MAIN_H
#define _MAIN_H

#define USE_SENDFILE 1

#define MAXEVENTS	1024
#define MAX_PORCESS	1024

#ifdef USE_SENDFILE
#define BUF_SIZE	1024
#else
#define BUF_SIZE	1024 * 2
#endif
#define MAX_URL_LENGTH	128

#define PORT 8080

#define INDEX_FILE "/index.json"

struct process {
	int id;
	int sock;
	int status;
	int response_code;
	int fd;
	int read_pos;
	int write_pos;
	int total_length;
	int header_length;
	int content_length;
	int content_get;
	char buf[BUF_SIZE];
	char header[BUF_SIZE];
};

void send_response_header(struct process *process);

int setNonblocking(int fd);

struct process *find_process_by_sock(int sock);

struct process *accept_sock(int listen_sock);

void read_request(struct process *process);

void send_response_header(struct process *process);

void send_response(struct process *process);

void cleanup(struct process *process);

void handle_error(struct process *process, char *error_string);

void reset_process(struct process *process);

int open_file(char *filename);

void err_sys(const char* s){
	perror(s);
	exit(1);
}

int Read(int fd , char* s){
	int pos = 0;
	char tmp[5];
	while(1){
		int res = read(fd , tmp , 1);
		if(res < 0) err_sys("read error");
		if(tmp[0] == '\n' || res == 0) break;
		if(res != 0) s[pos ++] = tmp[0];
	}
	s[pos] = '\0';
	return pos;
}

#endif