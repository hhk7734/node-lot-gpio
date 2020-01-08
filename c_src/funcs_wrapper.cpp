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

        Napi::PropertyDescriptor::Value( "U5N1",
                                         Napi::Number::New( env, lot::U5N1 ) ),
        Napi::PropertyDescriptor::Value( "U6N1",
                                         Napi::Number::New( env, lot::U6N1 ) ),
        Napi::PropertyDescriptor::Value( "U7N1",
                                         Napi::Number::New( env, lot::U7N1 ) ),
        Napi::PropertyDescriptor::Value( "U8N1",
                                         Napi::Number::New( env, lot::U8N1 ) ),
        Napi::PropertyDescriptor::Value( "U5N2",
                                         Napi::Number::New( env, lot::U5N2 ) ),
        Napi::PropertyDescriptor::Value( "U6N2",
                                         Napi::Number::New( env, lot::U6N2 ) ),
        Napi::PropertyDescriptor::Value( "U7N2",
                                         Napi::Number::New( env, lot::U7N2 ) ),
        Napi::PropertyDescriptor::Value( "U8N2",
                                         Napi::Number::New( env, lot::U8N2 ) ),
        Napi::PropertyDescriptor::Value( "U5E1",
                                         Napi::Number::New( env, lot::U5E1 ) ),
        Napi::PropertyDescriptor::Value( "U6E1",
                                         Napi::Number::New( env, lot::U6E1 ) ),
        Napi::PropertyDescriptor::Value( "U7E1",
                                         Napi::Number::New( env, lot::U7E1 ) ),
        Napi::PropertyDescriptor::Value( "U8E1",
                                         Napi::Number::New( env, lot::U8E1 ) ),
        Napi::PropertyDescriptor::Value( "U5E2",
                                         Napi::Number::New( env, lot::U5E2 ) ),
        Napi::PropertyDescriptor::Value( "U6E2",
                                         Napi::Number::New( env, lot::U6E2 ) ),
        Napi::PropertyDescriptor::Value( "U7E2",
                                         Napi::Number::New( env, lot::U7E2 ) ),
        Napi::PropertyDescriptor::Value( "U8E2",
                                         Napi::Number::New( env, lot::U8E2 ) ),
        Napi::PropertyDescriptor::Value( "U5O1",
                                         Napi::Number::New( env, lot::U5O1 ) ),
        Napi::PropertyDescriptor::Value( "U6O1",
                                         Napi::Number::New( env, lot::U6O1 ) ),
        Napi::PropertyDescriptor::Value( "U7O1",
                                         Napi::Number::New( env, lot::U7O1 ) ),
        Napi::PropertyDescriptor::Value( "U8O1",
                                         Napi::Number::New( env, lot::U8O1 ) ),
        Napi::PropertyDescriptor::Value( "U5O2",
                                         Napi::Number::New( env, lot::U5O2 ) ),
        Napi::PropertyDescriptor::Value( "U6O2",
                                         Napi::Number::New( env, lot::U6O2 ) ),
        Napi::PropertyDescriptor::Value( "U7O2",
                                         Napi::Number::New( env, lot::U7O2 ) ),
        Napi::PropertyDescriptor::Value( "U8O2",
                                         Napi::Number::New( env, lot::U8O2 ) ),
        Napi::PropertyDescriptor::Value( "U5M1",
                                         Napi::Number::New( env, lot::U5M1 ) ),
        Napi::PropertyDescriptor::Value( "U6M1",
                                         Napi::Number::New( env, lot::U6M1 ) ),
        Napi::PropertyDescriptor::Value( "U7M1",
                                         Napi::Number::New( env, lot::U7M1 ) ),
        Napi::PropertyDescriptor::Value( "U8M1",
                                         Napi::Number::New( env, lot::U8M1 ) ),
        Napi::PropertyDescriptor::Value( "U5M2",
                                         Napi::Number::New( env, lot::U5M2 ) ),
        Napi::PropertyDescriptor::Value( "U6M2",
                                         Napi::Number::New( env, lot::U6M2 ) ),
        Napi::PropertyDescriptor::Value( "U7M2",
                                         Napi::Number::New( env, lot::U7M2 ) ),
        Napi::PropertyDescriptor::Value( "U8M2",
                                         Napi::Number::New( env, lot::U8M2 ) ),
        Napi::PropertyDescriptor::Value( "U5S1",
                                         Napi::Number::New( env, lot::U5S1 ) ),
        Napi::PropertyDescriptor::Value( "U6S1",
                                         Napi::Number::New( env, lot::U6S1 ) ),
        Napi::PropertyDescriptor::Value( "U7S1",
                                         Napi::Number::New( env, lot::U7S1 ) ),
        Napi::PropertyDescriptor::Value( "U8S1",
                                         Napi::Number::New( env, lot::U8S1 ) ),
        Napi::PropertyDescriptor::Value( "U5S2",
                                         Napi::Number::New( env, lot::U5S2 ) ),
        Napi::PropertyDescriptor::Value( "U6S2",
                                         Napi::Number::New( env, lot::U6S2 ) ),
        Napi::PropertyDescriptor::Value( "U7S2",
                                         Napi::Number::New( env, lot::U7S2 ) ),
        Napi::PropertyDescriptor::Value( "U8S2",
                                         Napi::Number::New( env, lot::U8S2 ) ),

        Napi::PropertyDescriptor::Value( "MODE0",
                                         Napi::Number::New( env, lot::MODE0 ) ),
        Napi::PropertyDescriptor::Value( "MODE1",
                                         Napi::Number::New( env, lot::MODE1 ) ),
        Napi::PropertyDescriptor::Value( "MODE2",
                                         Napi::Number::New( env, lot::MODE2 ) ),
        Napi::PropertyDescriptor::Value( "MODE3",
                                         Napi::Number::New( env, lot::MODE3 ) ),

        Napi::PropertyDescriptor::Value( "DEBUG",
                                         Napi::Number::New( env, lot::DEBUG ) ),
        Napi::PropertyDescriptor::Value( "INFO",
                                         Napi::Number::New( env, lot::INFO ) ),
        Napi::PropertyDescriptor::Value(
            "WARNING", Napi::Number::New( env, lot::WARNING ) ),
        Napi::PropertyDescriptor::Value( "ERROR",
                                         Napi::Number::New( env, lot::ERROR ) ),
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