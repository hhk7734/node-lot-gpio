/*
 * MIT License
 * 
 * Copyright (c) 2020 Hyeonki Hong <hhk7734@gmail.com>
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

#include "GpioWrapper.h"

#include <stdexcept>

Napi::FunctionReference GpioWrapper::m_constructor;

Napi::Object GpioWrapper::init( Napi::Env env, Napi::Object exports )
{
    Napi::HandleScope scope( env );

    Napi::Function funcs = DefineClass(
        env,
        "Gpio",
        {
            InstanceMethod( "mode", &GpioWrapper::mode ),
            InstanceMethod( "pull_up_down", &GpioWrapper::pull_up_down ),
            InstanceMethod( "drive", &GpioWrapper::drive ),
            InstanceMethod( "digital", &GpioWrapper::digital ),
            InstanceMethod( "on", &GpioWrapper::on ),
            InstanceMethod( "off", &GpioWrapper::off ),
            InstanceMethod( "toggle", &GpioWrapper::toggle ),
            InstanceMethod( "analog", &GpioWrapper::analog ),
        } );

    m_constructor = Napi::Persistent( funcs );
    m_constructor.SuppressDestruct();

    exports.Set( "Gpio", funcs );
    return exports;
}

GpioWrapper::GpioWrapper( const Napi::CallbackInfo &info )
    : Napi::ObjectWrap<GpioWrapper>( info )
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
        m_Gpio = new lot::Gpio( pin );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Value GpioWrapper::mode( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New( env, static_cast<int>( m_Gpio->mode() ) );
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
        m_Gpio->mode( static_cast<lot::GpioMode>( mode ) );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }

    return env.Null();
}

Napi::Value GpioWrapper::pull_up_down( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New(
                env, static_cast<int>( m_Gpio->pull_up_down() ) );
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
        m_Gpio->pull_up_down( static_cast<lot::PUDMode>( pud ) );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }

    return env.Null();
}

Napi::Value GpioWrapper::drive( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New( env, m_Gpio->drive() );
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
        m_Gpio->drive( drive );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }

    return env.Null();
}

Napi::Value GpioWrapper::digital( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New( env, m_Gpio->digital() );
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
        m_Gpio->digital( status );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }

    return env.Null();
}

void GpioWrapper::on( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    try
    {
        m_Gpio->on();
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

void GpioWrapper::off( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    try
    {
        m_Gpio->off();
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Value GpioWrapper::toggle( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    try
    {
        return Napi::Number::New( env, m_Gpio->toggle() );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }

    return env.Null();
}

Napi::Value GpioWrapper::analog( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() == 0 )
    {
        try
        {
            return Napi::Number::New( env, m_Gpio->analog() );
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
        m_Gpio->analog( value );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }

    return env.Null();
}