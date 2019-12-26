#include <napi.h>

#include "gpio.h"

Napi::Object init_all( Napi::Env env, Napi::Object exports )
{
    return gpio::init( env, exports );
}

NODE_API_MODULE( NODE_GYP_MODULE_NAME, init_all )