#include <stdio.h>
#include <signal.h>

static int s_recibida = 0;
static void handler (int signum){
	printf("\nNueva acción del handler\n");
	s_recibida++;
}

int main(){
	struct sigaction sa;
	sa.sa_handler = handler;	// establece el manejador al handler definido arriba
	sigemptyset(&sa.sa_mask);

	// Reiniciar las funciones que hayan sido interrumpidas por un manejador
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &sa, NULL) == -1)
		printf("Error en el manejador");
		
	while(s_recibida < 3);
}