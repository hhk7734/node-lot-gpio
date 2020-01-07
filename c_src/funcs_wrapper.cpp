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

#include "funcs_wrapper.h"

#include <lot/lot.h>

/*
 * lot/lot-API/lot_time.h
 * lot/lot-API/lotdef.h
 */
Napi::Object init_funcs( Napi::Env env, Napi::Object exports )
{
    /*
     * lot/lot-API/lotdef.h
     */
    exports.DefineProperties( {
        Napi::PropertyDescriptor::Value(
            "UNUSED", Napi::Number::New( env, lot::UNUSED ) ),

        Napi::PropertyDescriptor::Value( "ALT0",
                                         Napi::Number::New( env, lot::ALT0 ) ),
        Napi::PropertyDescriptor::Value( "ALT1",
                                         Napi::Number::New( env, lot::ALT1 ) ),
        Napi::PropertyDescriptor::Value( "ALT2",
                                         Napi::Number::New( env, lot::ALT2 ) ),
        Napi::PropertyDescriptor::Value( "ALT3",
                                         Napi::Number::New( env, lot::ALT3 ) ),
        Napi::PropertyDescriptor::Value( "ALT4",
                                         Napi::Number::New( env, lot::ALT4 ) ),
        Napi::PropertyDescriptor::Value( "ALT5",
                                         Napi::Number::New( env, lot::ALT5 ) ),
        Napi::PropertyDescriptor::Value( "ALT6",
                                         Napi::Number::New( env, lot::ALT6 ) ),
        Napi::PropertyDescriptor::Value( "ALT7",
                                         Napi::Number::New( env, lot::ALT7 ) ),
        Napi::PropertyDescriptor::Value( "DIN",
                                         Napi::Number::New( env, lot::DIN ) ),
        Napi::PropertyDescriptor::Value( "DOUT",
                                         Napi::Number::New( env, lot::DOUT ) ),
        Napi::PropertyDescriptor::Value( "AIN",
                                         Napi::Number::New( env, lot::AIN ) ),
        Napi::PropertyDescriptor::Value( "AOUT",
                                         Napi::Number::New( env, lot::AOUT ) ),
        Napi::PropertyDescriptor::Value( "PWM",
                                         Napi::Number::New( env, lot::PWM ) ),

        Napi::PropertyDescriptor::Value(
            "PULL_OFF", Napi::Number::New( env, lot::PULL_OFF ) ),
        Napi::PropertyDescriptor::Value(
            "PULL_DOWN", Napi::Number::New( env, lot::PULL_DOWN ) ),
        Napi::PropertyDescriptor::Value(
            "PULL_UP", Napi::Number::New( env, lot::PULL_UP ) ),

        Napi::PropertyDescriptor::Value( "LOW",
                                         Napi::Number::New( env, lot::LOW ) ),
        Napi::PropertyDescriptor::Value( "HIGH",
                                         Napi::Number::New( env, lot::HIGH ) ),

        Napi::PropertyDescriptor::Value(
            "LSB_FIRST", Napi::Number::New( env, lot::LSB_FIRST ) ),
        Napi::PropertyDescriptor::Value(
            "MSB_FIRST", Napi::Number::New( env, lot::MSB_FIRST ) ),
    } );

    /*
     * lot/lot-API/lot_time.h
     */
    exports.Set( "init_time", Napi::Function::New( env, init_time_wrapper ) );
    exports.Set( "delay_us", Napi::Function::New( env, delay_us_wrapper ) );
    exports.Set( "delay_ms", Napi::Function::New( env, delay_ms_wrapper ) );
    exports.Set( "micros", Napi::Function::New( env, micros_wrapper ) );
    exports.Set( "millis", Napi::Function::New( env, millis_wrapper ) );

    return exports;
}

/*
 * lot/lot-API/lot_time.h
 */
void init_time_wrapper( const Napi::CallbackInfo &info )
{
    lot::init_time();
}

void delay_us_wrapper( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (micros) such as (100)." )
            .ThrowAsJavaScriptException();
    }

    uint32_t us = info[0].As<Napi::Number>();

    lot::delay_us( us );
}

void delay_ms_wrapper( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    if( info.Length() < 1 || !info[0].IsNumber() )
    {
        Napi::TypeError::New( env, "Arguments must be (millis) such as (100)." )
            .ThrowAsJavaScriptException();
    }

    uint32_t ms = info[0].As<Napi::Number>();

    lot::delay_us( ms );
}

Napi::Number micros_wrapper( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    return Napi::Number::New( env, lot::micros() );
}

Napi::Number millis_wrapper( const Napi::CallbackInfo &info )
{
    Napi::Env env = info.Env();

    return Napi::Number::New( env, lot::millis() );
}