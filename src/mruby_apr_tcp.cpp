#include "mruby.h"
#include "mruby_apr.h"
#include "apr.h"
#include "apr_pools.h"
#include "apr_network_io.h"

//<
// # module APR::TCP
//>

//<
// ## `::get_open_port`
// Return an open TCP port number
//>
mrb_value
mrb_apr_tcp_get_open_port(mrb_state* mrb, mrb_value self) {
   // Bind a socket to port 0 (lets the OS choose)
   apr_socket_t *socket;
   apr_pool_t* pool;
   apr_pool_create(&pool, NULL);
   apr_socket_create(&socket, APR_INET, SOCK_STREAM, APR_PROTO_TCP, pool);
   apr_sockaddr_t *addr;
   apr_sockaddr_info_get(&addr, NULL, APR_INET, 0, 0, pool);
   apr_socket_bind(socket, addr);

   // Get the selected port for the socket
   apr_socket_addr_get(&addr, apr_interface_e::APR_LOCAL, socket);
   mrb_value port;
   SET_INT_VALUE(port, addr->port);

   apr_socket_close(socket);
   apr_pool_destroy(pool);
   return port;
}

void mrb_mruby_apr_tcp_init(mrb_state* mrb, RClass* apr_module) {
   auto apr_tcp_module = mrb_define_module_under(mrb, apr_module, "TCP");
   mrb_define_module_function(mrb, apr_tcp_module, "get_open_port", mrb_apr_tcp_get_open_port, MRB_ARGS_NONE());
}
