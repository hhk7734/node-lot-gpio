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
#include <lot/Gpio.h>

class GpioWrapper : public Napi::ObjectWrap<GpioWrapper>
{
public:
    static Napi::Object init( Napi::Env env, Napi::Object exports );

    GpioWrapper( const Napi::CallbackInfo &info );

private:
    static Napi::FunctionReference m_constructor;
    lot::Gpio *                    m_Gpio;

    Napi::Value mode( const Napi::CallbackInfo &info );
    Napi::Value pull_up_down( const Napi::CallbackInfo &info );
    Napi::Value drive( const Napi::CallbackInfo &info );

    Napi::Value digital( const Napi::CallbackInfo &info );
    void        on( const Napi::CallbackInfo &info );
    void        off( const Napi::CallbackInfo &info );
    Napi::Value toggle( const Napi::CallbackInfo &info );

    Napi::Value analog( const Napi::CallbackInfo &info );
};