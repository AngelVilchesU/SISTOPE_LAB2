#include "fbroker.h"

void crearWorkers(int nroWorkers)
{
    execl("./worker", "./worker", NULL);
}