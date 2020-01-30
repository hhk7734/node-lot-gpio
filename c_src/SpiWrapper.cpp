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

#include "SpiWrapper.h"

#include <stdexcept>

Napi::FunctionReference SpiWrapper::m_constructor;

Napi::Object SpiWrapper::init( Napi::Env env, Napi::Object exports )
{
    Napi::HandleScope scope( env );

    Napi::Function funcs = DefineClass(
        env,
        "Spi",
        {
            InstanceMethod( "clock", &SpiWrapper::clock ),
            InstanceMethod( "mode", &SpiWrapper::mode ),
            InstanceMethod( "bit_order", &SpiWrapper::bit_order ),
            InstanceMethod( "transceive", &SpiWrapper::transceive ),
            InstanceMethod( "write_reg", &SpiWrapper::write_reg ),
            InstanceMethod( "read_reg", &SpiWrapper::read_reg ),
        } );

    m_constructor = Napi::Persistent( funcs );
    m_constructor.SuppressDestruct();

    exports.Set( "Spi", funcs );
    return exports;
}

SpiWrapper::SpiWrapper( const Napi::CallbackInfo &info )
    : Napi::ObjectWrap<SpiWrapper>( info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( ( info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber() )
        && ( info.Length() < 1 || !info[0].IsString() ) )
    {
        Napi::TypeError::New(
            env, "Arguments must be (bus number, chip_select) or (device)." )
            .ThrowAsJavaScriptException();
    }

    if( info[0].IsNumber() )
    {
        int bus_num     = info[0].As<Napi::Number>();
        int chip_select = info[1].As<Napi::Number>();
        try
        {
            m_Spi = new lot::Spi( bus_num, chip_select );
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
            m_Spi = new lot::Spi( device.c_str() );
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }
}

void SpiWrapper::clock( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (spi_clock) such as (1000000)." )
            .ThrowAsJavaScriptException();
    }

    uint32_t spi_clock = info[0].As<Napi::Number>();

    try
    {
        m_Spi->clock( spi_clock );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

void SpiWrapper::mode( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (spi_mode) such as (lot.MODE0)." )
            .ThrowAsJavaScriptException();
    }

    int spi_mode = info[0].As<Napi::Number>();

    try
    {
        m_Spi->mode( static_cast<lot::SpiMode>( spi_mode ) );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

void SpiWrapper::bit_order( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New(
            env, "Arguments must be (spi_bit_order) such as (lot.MSB_FIRST)." )
            .ThrowAsJavaScriptException();
    }

    int spi_bit_order = info[0].As<Napi::Number>();

    try
    {
        m_Spi->bit_order( static_cast<lot::BitOrder>( spi_bit_order ) );
    }
    catch( const std::exception &e )
    {
        Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
    }
}

Napi::Value SpiWrapper::transceive( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    Napi::Buffer<uint8_t> tx_buffer;
    int                   cs_pin = -1;

    bool is_error = false;

    switch( info.Length() )
    {
        default:
            if( info[1].IsNumber() )
            {
                cs_pin = info[1].As<Napi::Number>();
            }
            else
            {
                is_error = true;
                break;
            }
            [[fallthrough]];
        case 1:
            if( info[0].IsBuffer() )
            {
                tx_buffer = info[1].As<Napi::Buffer<uint8_t>>();
            }
            else
            {
                is_error = true;
            }
            break;
        case 0:
            is_error = true;
            break;
    }

    if( is_error )
    {
        Napi::TypeError::New(
            env, "Arguments must be (buffer) or (buffer, cs_pin)." )
            .ThrowAsJavaScriptException();
    }

    int size = tx_buffer.Length();
    if( size > 0 )
    {
        try
        {
            uint8_t *buf = new uint8_t[size];

            if( cs_pin < 0 )
            {
                m_Spi->transceive( tx_buffer.Data(), buf, size );
            }
            else
            {
                m_Spi->transceive( tx_buffer.Data(), buf, size, cs_pin );
            }

            Napi::Buffer<uint8_t> rx_buffer
                = Napi::Buffer<uint8_t>::Copy( env, buf, size );
            delete buf;
            return rx_buffer;
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }
    return Napi::Buffer<uint8_t>::New( env, 0 );
}

void SpiWrapper::write_reg( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    int                   register_address = -1;
    Napi::Buffer<uint8_t> buffer;
    int                   cs_pin = -1;

    bool is_error = false;

    switch( info.Length() )
    {
        default:
            if( info[2].IsNumber() )
            {
                cs_pin = info[2].As<Napi::Number>();
            }
            else
            {
                is_error = true;
                break;
            }
            [[fallthrough]];
        case 2:
            if( !info[0].IsNumber() || !info[1].IsBuffer() )
            {
                is_error = true;
            }
            else
            {
                register_address = info[0].As<Napi::Number>();
                buffer           = info[1].As<Napi::Buffer<uint8_t>>();
            }
            break;
        case 0 ... 1:
            is_error = true;
            break;
    }

    if( is_error )
    {
        Napi::TypeError::New( env,
                              "Arguments must be (register_address, buffer) or "
                              "(register_address, buffer, cs_pin)." )
            .ThrowAsJavaScriptException();
    }

    if( buffer.Length() > 0 )
    {
        try
        {
            if( cs_pin < 0 )
            {
                m_Spi->write_reg( static_cast<uint8_t>( register_address ),
                                  buffer.Data(),
                                  buffer.Length() );
            }
            else
            {
                m_Spi->write_reg( static_cast<uint8_t>( register_address ),
                                  buffer.Data(),
                                  buffer.Length(),
                                  cs_pin );
            }
        }
        catch( const std::exception &e )
        {
            Napi::Error::New( env, e.what() ).ThrowAsJavaScriptException();
        }
    }
}

Napi::Value SpiWrapper::read_reg( const Napi::CallbackInfo &info )
{
    Napi::Env         env = info.Env();
    Napi::HandleScope scope( env );

    int register_address = -1;
    int size             = -1;
    int cs_pin           = -1;

    bool is_error = false;

    switch( info.Length() )
    {
        default:
            if( info[2].IsNumber() )
            {
                cs_pin = info[2].As<Napi::Number>();
            }
            else
            {
                is_error = true;
                break;
            }
            [[fallthrough]];
        case 2:
            if( !info[0].IsNumber() || !info[1].IsNumber() )
            {
                is_error = true;
            }
            else
            {
                register_address = info[0].As<Napi::Number>();
                size             = info[1].As<Napi::Number>();
            }
            break;
        case 0 ... 1:
            is_error = true;
            break;
    }

    if( is_error )
    {
        Napi::TypeError::New( env,
                              "Arguments must be (register_address, size) or "
                              "(register_address, size, cs_pin)." )
            .ThrowAsJavaScriptException();
    }

    if( size > 0 )
    {
        try
        {
            uint8_t *buf = new uint8_t[size];

            if( cs_pin < 0 )
            {
                m_Spi->read_reg(
                    static_cast<uint8_t>( register_address ), buf, size );
            }
            else
            {
                m_Spi->read_reg( static_cast<uint8_t>( register_address ),
                                 buf,
                                 size,
                                 cs_pin );
            }

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