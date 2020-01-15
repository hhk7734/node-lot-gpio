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

#include "I2cWrapper.h"

#include <stdexcept>

Napi::FunctionReference I2cWrapper::m_constructor;

Napi::Object I2cWrapper::init( Napi::Env env, Napi::Object exports )
{
    Napi::HandleScope scope( env );

    Napi::Function funcs = DefineClass(
        env,
        "I2c",
        {
            InstanceMethod( "init", &I2cWrapper::init ),
            InstanceMethod( "clock", &I2cWrapper::clock ),
            InstanceMethod( "transmit", &I2cWrapper::transmit ),
            InstanceMethod( "receive", &I2cWrapper::receive ),
            InstanceMethod( "write_reg", &I2cWrapper::write_reg ),
            InstanceMethod( "read_reg", &I2cWrapper::read_reg ),
        } );

    m_constructor = Napi::Persistent( funcs );
    m_constructor.SuppressDestruct();

    exports.Set( "I2c", funcs );
    return exports;
}

I2cWrapper::I2cWrapper( const Napi::CallbackInfo &info )
    : Napi::ObjectWrap<I2cWrapper>( info )
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
            m_I2c = new lot::I2c( bus_num );
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
            m_I2c = new lot::I2c( device.c_str() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }
}

void I2cWrapper::init( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    uint32_t i2c_clock;

    if( info.Length() == 0 )
    {
        i2c_clock = 400000;
    }
    else
    {
        if( !info[0].IsNumber() )
        {
            Napi::TypeError::New( env,
                                  "Arguments should be (i2c_clock = 400000)." )
                .ThrowAsJavaScriptException();
        }
        i2c_clock = info[0].As<Napi::Number>();
    }

    try
    {
        m_I2c->init( i2c_clock );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

void I2cWrapper::clock( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (i2c_clock) such as (400000)." )
            .ThrowAsJavaScriptException();
    }

    uint32_t i2c_clock = info[0].As<Napi::Number>();

    try
    {
        m_I2c->clock( i2c_clock );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

void I2cWrapper::transmit( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsBuffer() )
    {
        Napi::TypeError::New( env,
                              "Arguments must be (slave_address, buffer)." )
            .ThrowAsJavaScriptException();
    }

    int                   slave_address = info[0].As<Napi::Number>();
    Napi::Buffer<uint8_t> buffer        = info[1].As<Napi::Buffer<uint8_t>>();

    if( buffer.Length() > 0 )
    {
        try
        {
            m_I2c->transmit( static_cast<uint8_t>( slave_address ),
                             buffer.Data(),
                             buffer.Length() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }
}

Napi::Value I2cWrapper::receive( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    int size = 1;

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env,
                              "Arguments must be (slave_address, size = 1)." )
            .ThrowAsJavaScriptException();
    }

    if( info.Length() > 1 )
    {
        if( !info[1].IsNumber() )
        {
            Napi::TypeError::New(
                env, "Arguments must be (slave_address, size = 1)." )
                .ThrowAsJavaScriptException();
        }
        size = info[1].As<Napi::Number>();
    }

    int slave_address = info[0].As<Napi::Number>();


    if( size > 0 )
    {
        try
        {
            uint8_t *buf = new uint8_t[size];
            m_I2c->receive( static_cast<uint8_t>( slave_address ), buf, size );
            Napi::Buffer<uint8_t> buffer
                = Napi::Buffer<uint8_t>::Copy( env, buf, size );
            delete buf;
            return buffer;
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }

    return Napi::Buffer<uint8_t>::New( env, 0 );
}

void I2cWrapper::write_reg( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 3 || !info[0].IsNumber() || !info[1].IsNumber()
        || !info[2].IsBuffer() )
    {
        Napi::TypeError::New(
            env,
            "Arguments must be (slave_address, register_address, buffer)." )
            .ThrowAsJavaScriptException();
    }

    int                   slave_address    = info[0].As<Napi::Number>();
    int                   register_address = info[1].As<Napi::Number>();
    Napi::Buffer<uint8_t> buffer = info[2].As<Napi::Buffer<uint8_t>>();

    if( buffer.Length() > 0 )
    {
        try
        {
            m_I2c->write_reg( static_cast<uint8_t>( slave_address ),
                              static_cast<uint8_t>( register_address ),
                              buffer.Data(),
                              buffer.Length() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }
}

Napi::Value I2cWrapper::read_reg( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    int size = 1;

    if( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber() )
    {
        Napi::TypeError::New(
            env,
            "Arguments must be (slave_address, register_address, size = 1)." )
            .ThrowAsJavaScriptException();
    }

    if( info.Length() > 2 )
    {
        if( !info[2].IsNumber() )
        {
            Napi::TypeError::New( env,
                                  "Arguments must be (slave_address, "
                                  "register_address, size = 1)." )
                .ThrowAsJavaScriptException();
        }
        size = info[2].As<Napi::Number>();
    }

    int slave_address    = info[0].As<Napi::Number>();
    int register_address = info[1].As<Napi::Number>();


    if( size > 0 )
    {
        try
        {
            uint8_t *buf = new uint8_t[size];
            m_I2c->read_reg( static_cast<uint8_t>( slave_address ),
                             static_cast<uint8_t>( register_address ),
                             buf,
                             size );
            Napi::Buffer<uint8_t> buffer
                = Napi::Buffer<uint8_t>::Copy( env, buf, size );
            delete buf;
            return buffer;
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }

    return Napi::Buffer<uint8_t>::New( env, 0 );
}