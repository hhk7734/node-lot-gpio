/*
 * MIT License
 * Copyright (c) 2019 Hyeonki Hong <hhk7734@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "gpio.h"
#include "def.h"

#include <lot/lot.h>
#include <string>
#include <iostream>

Napi::Object gpio::init( Napi::Env env, Napi::Object exports )
{
    lot::init();

    exports.Set( "get_lot_pin_available",
                 Napi::Function::New( env, get_lot_pin_available ) );
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

Napi::Value gpio::get_lot_pin_available( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (pin) such as (13)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin = static_cast<int>( info[0].As<Napi::Number>() );

    try
    {
        lot::pin_size_t retval = lot::get_lot_pin_available( pin );
        if( retval != UNUSED )
        {
            return Napi::Number::New( env, static_cast<int>( retval ) );
        }
        else
        {
            return Napi::String::New( env, "UNUSED" );
        }
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
        return Napi::Value( env, 0 );
    }
}

void gpio::set_pin_mode( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsString() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (pin, mode) such as (13, \"OUT\")." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin  = static_cast<int>( info[0].As<Napi::Number>() );
    std::string     mode = info[1].As<Napi::String>();

    try
    {
        lot::set_pin_mode(
            pin, static_cast<lot::pin_mode_t>( def::mode_str_to_num[mode] ) );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::String gpio::get_pin_mode( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (pin) such as (13)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin = static_cast<int>( info[0].As<Napi::Number>() );

    try
    {
        std::string retval = def::mode_num_to_str[lot::get_pin_mode( pin )];
        return Napi::String::New( env, retval );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
        return Napi::String( env, nullptr );
    }
}

void gpio::set_pin_pull_up_down( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsString() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (pin, pud) such as (13, \"PULL_UP\")." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin = static_cast<int>( info[0].As<Napi::Number>() );
    std::string     pud = info[1].As<Napi::String>();

    try
    {
        lot::set_pin_pull_up_down(
            pin, static_cast<lot::pud_mode_t>( def::pud_str_to_num[pud] ) );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::String gpio::get_pin_pull_up_down( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (pin) such as (13)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin = static_cast<int>( info[0].As<Napi::Number>() );

    try
    {
        std::string retval
            = def::mode_num_to_str[lot::get_pin_pull_up_down( pin )];
        return Napi::String::New( env, retval );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
        return Napi::String( env, nullptr );
    }
}

void gpio::set_pin_speed( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (pin, speed) such as (13, speed)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin   = static_cast<int>( info[0].As<Napi::Number>() );
    uint32_t        speed = info[1].As<Napi::Number>();

    try
    {
        lot::set_pin_speed( pin, speed );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Number gpio::get_pin_speed( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (pin) such as (13)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin = static_cast<int>( info[0].As<Napi::Number>() );

    try
    {
        return Napi::Number::New( env, lot::get_pin_speed( pin ) );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
        return Napi::Number::New( env, 0 );
    }
}

void gpio::set_pin_drive( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (pin, drive) such as (13, drive)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin   = static_cast<int>( info[0].As<Napi::Number>() );
    uint32_t        drive = info[1].As<Napi::Number>();

    try
    {
        lot::set_pin_drive( pin, drive );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Number gpio::get_pin_drive( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (pin) such as (13)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin = static_cast<int>( info[0].As<Napi::Number>() );

    try
    {
        return Napi::Number::New( env, lot::get_pin_drive( pin ) );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
        return Napi::Number::New( env, 0 );
    }
}

void gpio::digital_write( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsString() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (pin, status) such as (13, \"HIGH\")." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin    = static_cast<int>( info[0].As<Napi::Number>() );
    std::string     status = info[1].As<Napi::String>();

    try
    {
        lot::digital_write(
            pin,
            static_cast<lot::pin_status_t>( def::status_str_to_num[status] ) );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::String gpio::digital_read( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (pin) such as (13)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin = static_cast<int>( info[0].As<Napi::Number>() );

    try
    {
        std::string retval = def::status_num_to_str[static_cast<int>(
            lot::digital_read( pin ) )];
        return Napi::String::New( env, retval );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
        return Napi::String( env, nullptr );
    }
}

void gpio::analog_write( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (pin, value) such as (13, value)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin   = static_cast<int>( info[0].As<Napi::Number>() );
    uint32_t        value = info[1].As<Napi::Number>();

    try
    {
        lot::analog_write( pin, value );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Number gpio::analog_read( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (pin) such as (13)." )
            .ThrowAsJavaScriptException();
    }

    lot::pin_size_t pin = static_cast<int>( info[0].As<Napi::Number>() );

    try
    {
        return Napi::Number::New( env, lot::analog_read( pin ) );
    }
    catch( const std::exception &e )
    {
        Napi::TypeError::New( env, e.what() ).ThrowAsJavaScriptException();
        return Napi::Number::New( env, 0 );
    }
}