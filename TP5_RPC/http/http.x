const BUFFER_SIZE = 1024;

struct data1 {
  char request[BUFFER_SIZE];
};
typedef struct data1 data1;

struct data2 {
  int fd;
};
typedef struct data2 data2;

struct response {
  int fd;
  char char_read[BUFFER_SIZE];
  int byte_read_nbr;
};
typedef struct response response;

program HTTP{ 
  version VERSION_UN{
    void HTTP_NULL(void) = 0;
    response HTTP_REQUEST1(data1) = 1;
    response HTTP_REQUEST2(data2) = 2;
  } = 1;
} = 0x20000001;
