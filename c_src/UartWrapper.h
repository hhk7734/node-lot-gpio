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

#pragma once

#include <napi.h>
#include <lot/Uart.h>

class UartWrapper : public Napi::ObjectWrap<UartWrapper>
{
public:
    static Napi::Object init( Napi::Env env, Napi::Object exports );

    UartWrapper( const Napi::CallbackInfo &info );

private:
    static Napi::FunctionReference m_constructor;
    lot::Uart *                    m_Uart;

    void        baudrate( const Napi::CallbackInfo &info );
    void        mode( const Napi::CallbackInfo &info );
    Napi::Value available( const Napi::CallbackInfo &info );
    void        transmit( const Napi::CallbackInfo &info );
    Napi::Value receive( const Napi::CallbackInfo &info );
};