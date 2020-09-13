// #include "abstract_wm.h"
#include "config.h"

int main(int argc, char **argv){

	new_config();
	printf("%s\n","Se completa new_config" );
	int scrno = 0;
	atexit(cleanup);
	printf("%s\n","Se completa atexit" );
	install_sig_handlers();
	printf("%s\n","Se completa install_sig_handlers" );
	if (!xcb_connection_has_error(conn = xcb_connect(NULL, &scrno))){
		printf("%s\n","Se completa if (!xcb_connection_has_error(conn = xcb_connect(NULL, &scrno)))" );
		if (setup(scrno)){
			printf("%s\n","Se completa if (setup(scrno))" );
			run();
			printf("%s\n","Se completa run" );
		} else {printf("%s\n","No se cumple que if (setup(scrno))" );}
	}else {printf("%s\n","No se cumple que if (!xcb_connection_has_error(conn = xcb_connect(NULL, &scrno)))" );}
	/* the WM has stopped running, because sigcode is not 0 */
	printf("%s\n","Se completan los dos if" );
	exit(sigcode);
	printf("%s\n","Se completa exit(sigcode)" );
}
