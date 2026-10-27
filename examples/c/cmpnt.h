// an example how we should implement a compoenta 
// in an fbp paradigm
// an example how we should implement a component
// in an fbp paradigm

#include <fluv/fluv.h> //component allowed to include only this header


fv_error_t fv_read(fv_port_t *port) {
    // Implementation for reading a component
    return FV_SUCCESS;
}

fv_error_t fv_write(fv_port_t *port) {
    // Implementation for writing a component
    return FV_SUCCESS;
}


fv_error_t fv_main(void) {
    // Main function to demonstrate component usage
    fv_read();
    fv_write();
    return FV_SUCCESS;
}