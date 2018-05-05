struct data { 
  string ip<>;
  int port;
};
typedef struct data data;
struct reponse {
  string message<>;
  int errno;
};
typedef struct reponse reponse;
program CALCUL{
  version VERSION_UN{
    void CALCUL_NULL(void) = 0;
    reponse CALCUL_MY_TIME(data) = 1;
  } = 1;
} = 0x20000001;
