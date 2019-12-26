#include "gpio.h"

#include <lot/lot.h>

Napi::Object gpio::init( Napi::Env env, Napi::Object exports )
{
    lot::init();

    exports.Set( "set_pin_mode", Napi::Function::New( env, set_pin_mode ) );
    exports.Set( "get_pin_mode", Napi::Function::New( env, get_pin_mode ) );
    exports.Set( "set_pin_pull_up_down",
                 Napi::Function::New( env, set_pin_pull_up_down ) );
    exports.Set( "get_pin_pull_up_down",
                 Napi::Function::New( env, get_pin_pull_up_down ) );
    exports.Set( "set_pin_speed", Napi::Function::New( env, set_pin_speed ) );
    exports.Set( "get_pin_speed", Napi::Function::New( env, get_pin_speed ) );
    exports.Set( "set_pin_drive", Napi::Function::New( env, set_pin_drive ) );
    exports.Set( "get_pin_drive", Napi::Function::New( env, get_pin_drive ) );
    exports.Set( "digital_write", Napi::Function::New( env, digital_write ) );
    exports.Set( "digital_read", Napi::Function::New( env, digital_read ) );
    exports.Set( "analog_write", Napi::Function::New( env, analog_write ) );
    exports.Set( "analog_read", Napi::Function::New( env, analog_read ) );

    return exports;
}

void gpio::set_pin_mode( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

Napi::String gpio::get_pin_mode( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

void gpio::set_pin_pull_up_down( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

Napi::String gpio::get_pin_pull_up_down( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

void gpio::set_pin_speed( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

Napi::Number gpio::get_pin_speed( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

void gpio::set_pin_drive( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

Napi::Number gpio::get_pin_drive( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

void gpio::digital_write( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

Napi::String gpio::digital_read( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

void gpio::analog_write( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}

Napi::Number gpio::analog_read( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();
}