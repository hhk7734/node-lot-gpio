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

#include "UartWrapper.h"

#include <stdexcept>
#include <iostream>

Napi::FunctionReference UartWrapper::m_constructor;

Napi::Object UartWrapper::init( Napi::Env env, Napi::Object exports )
{
    Napi::HandleScope scope( env );

    Napi::Function funcs = DefineClass(
        env,
        "Uart",
        {
            InstanceMethod( "init", &UartWrapper::init ),
            InstanceMethod( "baudrate", &UartWrapper::baudrate ),
            InstanceMethod( "mode", &UartWrapper::mode ),
            InstanceMethod( "available", &UartWrapper::available ),
            InstanceMethod( "transmit", &UartWrapper::transmit ),
            InstanceMethod( "receive", &UartWrapper::receive ),
        } );

    m_constructor = Napi::Persistent( funcs );
    m_constructor.SuppressDestruct();

    exports.Set( "Uart", funcs );
    return exports;
}

UartWrapper::UartWrapper( const Napi::CallbackInfo &info )
    : Napi::ObjectWrap<UartWrapper>( info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !( info[0].IsNumber() || info[0].IsString() ) )
    {
        Napi::TypeError::New( env,
                              "Arguments must be (bus number) or (device)." )
            .ThrowAsJavaScriptException();
    }

    if( info[0].IsNumber() )
    {
        int bus_num = info[0].As<Napi::Number>();
        try
        {
            m_Uart = new lot::Uart( bus_num );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
        return;
    }

    if( info[0].IsString() )
    {
        std::string device = info[0].As<Napi::String>();
        try
        {
            m_Uart = new lot::Uart( device.c_str() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }
}

void UartWrapper::init( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    uint32_t baud_rate;
    int      mode;

    switch( info.Length() )
    {
        case 0:
            baud_rate = 115200;
            mode      = static_cast<int>( lot::U8N1 );
            break;
        case 1:
            if( !info[0].IsNumber() )
            {
                Napi::TypeError::New( env,
                                      "Arguments should be (baud_rate = "
                                      "115200, mode = lot.U8N1)." )
                    .ThrowAsJavaScriptException();
            }
            baud_rate = info[0].As<Napi::Number>();
            mode      = static_cast<int>( lot::U8N1 );
            break;
        default:
            if( !info[0].IsNumber() || !info[1].IsNumber() )
            {
                Napi::TypeError::New( env,
                                      "Arguments should be (baud_rate = "
                                      "115200, mode = lot.U8N1)." )
                    .ThrowAsJavaScriptException();
            }
            baud_rate = info[0].As<Napi::Number>();
            mode      = info[1].As<Napi::Number>();
            break;
    }

    try
    {
        m_Uart->init( baud_rate, static_cast<lot::uart_mode_t>( mode ) );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

void UartWrapper::baudrate( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env,
                              "Arguments must be (baudrate) such as (115200)." )
            .ThrowAsJavaScriptException();
    }

    uint32_t baud_rate = info[0].As<Napi::Number>();

    try
    {
        m_Uart->baudrate( baud_rate );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

void UartWrapper::mode( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env,
                              "Arguments must be (mode) such as (lot.U8N1)." )
            .ThrowAsJavaScriptException();
    }

    int mode = info[0].As<Napi::Number>();

    try
    {
        m_Uart->mode( static_cast<lot::uart_mode_t>( mode ) );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Value UartWrapper::available( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    try
    {
        return Napi::Number::New( env, m_Uart->available() );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }

    return env.Null();
}

void UartWrapper::transmit( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !info[0].IsBuffer() )
    {
        Napi::TypeError::New( env, "Arguments must be (buffer)." )
            .ThrowAsJavaScriptException();
    }

    Napi::Buffer<uint8_t> buffer = info[0].As<Napi::Buffer<uint8_t>>();

    if( buffer.Length() > 0 )
    {
        try
        {
            m_Uart->transmit( buffer.Data(), buffer.Length() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }
}

Napi::Value UartWrapper::receive( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    try
    {
        int length = m_Uart->available();
        if( length > 0 )
        {
            uint8_t *buf = new uint8_t[length];
            m_Uart->receive( buf, length );
            Napi::Buffer<uint8_t> buffer
                = Napi::Buffer<uint8_t>::Copy( env, buf, length );
            delete buf;
            return buffer;
        }
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }

    return Napi::Buffer<uint8_t>::New( env, 0 );
}