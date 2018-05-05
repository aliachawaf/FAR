struct data {
  int arg1;
  int arg2;
};
typedef struct data data;
struct reponse {
  int somme;
  int errno;
};
typedef struct reponse reponse;
program CALCUL{
  version VERSION_UN{
    void CALCUL_NULL(void) = 0;
    reponse CALCUL_ADDITION(data) = 1;
  } = 1;
} = 0x20000001;
