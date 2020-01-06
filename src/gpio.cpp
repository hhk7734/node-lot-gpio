/*
 * MIT License
 * 
 * Copyright (c) 2019-2020 Hyeonki Hong <hhk7734@gmail.com>
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

#include <iostream>
#include <stdexcept>

/*
 * lot/lot-API/lot_time.h
 */
Napi::Object nodelot::init_funcs( Napi::Env env, Napi::Object exports )
{
    exports.Set( "init_time", Napi::Function::New( env, init_time ) );
    exports.Set( "delay_us", Napi::Function::New( env, delay_us ) );
    exports.Set( "delay_ms", Napi::Function::New( env, delay_ms ) );
    exports.Set( "micros", Napi::Function::New( env, micros ) );
    exports.Set( "millis", Napi::Function::New( env, millis ) );

    return exports;
}

void nodelot::init_time( const Napi::CallbackInfo &info )
{
    lot::init_time();
}

void nodelot::delay_us( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (micros) such as (100)." )
            .ThrowAsJavaScriptException();
    }

    int us = info[0].As<Napi::Number>();

    lot::delay_us( us );
}

void nodelot::delay_ms( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (millis) such as (100)." )
            .ThrowAsJavaScriptException();
    }

    int ms = info[0].As<Napi::Number>();

    lot::delay_us( ms );
}

Napi::Number nodelot::micros( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    return Napi::Number::New( env, lot::micros() );
}

Napi::Number nodelot::millis( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    return Napi::Number::New( env, lot::millis() );
}

/*
 * lot/Gpio.h
 */
Napi::FunctionReference nodelot::Gpio::m_constructor;

Napi::Object nodelot::Gpio::init( Napi::Env env, Napi::Object exports )
{
    Napi::HandleScope scope( env );

    Napi::Function funcs = DefineClass(
        env,
        "Gpio",
        {
            InstanceMethod( "mode", &nodelot::Gpio::mode ),
            InstanceMethod( "pull_up_down", &nodelot::Gpio::pull_up_down ),
            InstanceMethod( "drive", &nodelot::Gpio::drive ),
            InstanceMethod( "digital", &nodelot::Gpio::digital ),
            InstanceMethod( "on", &nodelot::Gpio::on ),
            InstanceMethod( "off", &nodelot::Gpio::off ),
            InstanceMethod( "toggle", &nodelot::Gpio::toggle ),
            InstanceMethod( "analog", &nodelot::Gpio::analog ),
        } );

    m_constructor = Napi::Persistent( funcs );
    m_constructor.SuppressDestruct();

    exports.Set( "Gpio", funcs );
    return exports;
}

nodelot::Gpio::Gpio( const Napi::CallbackInfo &info )
    : Napi::ObjectWrap<Gpio>( info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (pin) such as (13)." )
            .ThrowAsJavaScriptException();
    }

    int pin = info[0].As<Napi::Number>();

    try
    {
        m_gpio = new lot::Gpio( pin );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Number nodelot::Gpio::mode( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New( env, static_cast<int>( m_gpio->mode() ) );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }

    if( !info[0].IsNumber() )
    {
        Napi::TypeError::New( env,
                              "Arguments should be (mode) such as (lot.DOUT)." )
            .ThrowAsJavaScriptException();
    }

    int mode = info[0].As<Napi::Number>();

    try
    {
        m_gpio->mode( static_cast<lot::pin_mode_t>( mode ) );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
    return Napi::Number::New( env, -1 );
}

Napi::Number nodelot::Gpio::pull_up_down( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New(
                env, static_cast<int>( m_gpio->pull_up_down() ) );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }

    if( !info[0].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments should be (pud) such as (lot.PULL_UP)." )
            .ThrowAsJavaScriptException();
    }

    int pud = info[0].As<Napi::Number>();

    try
    {
        m_gpio->pull_up_down( static_cast<lot::pud_mode_t>( pud ) );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
    return Napi::Number::New( env, -1 );
}

Napi::Number nodelot::Gpio::drive( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New( env, m_gpio->drive() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }

    if( !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments should be (drive)." )
            .ThrowAsJavaScriptException();
    }

    uint32_t drive = info[0].As<Napi::Number>();

    try
    {
        m_gpio->drive( drive );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
    return Napi::Number::New( env, -1 );
}

Napi::Number nodelot::Gpio::digital( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New( env, m_gpio->digital() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }

    if( !info[0].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments should be (status) such as (lot.HIGH)." )
            .ThrowAsJavaScriptException();
    }

    int status = info[0].As<Napi::Number>();

    try
    {
        m_gpio->digital( status );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
    return Napi::Number::New( env, -1 );
}

void nodelot::Gpio::on( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    try
    {
        m_gpio->on();
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

void nodelot::Gpio::off( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    try
    {
        m_gpio->off();
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Number nodelot::Gpio::toggle( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    try
    {
        return Napi::Number::New( env, m_gpio->toggle() );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
    return Napi::Number::New( env, -1 );
}

Napi::Number nodelot::Gpio::analog( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New( env, m_gpio->analog() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }

    if( !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (value)." )
            .ThrowAsJavaScriptException();
    }

    int value = info[0].As<Napi::Number>();

    try
    {
        m_gpio->analog( value );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
    return Napi::Number::New( env, -1 );
}