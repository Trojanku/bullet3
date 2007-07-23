/* atan2f4 -
   Copyright (C) 2006, 2007 Sony Computer Entertainment Inc.
   All rights reserved.

   Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Sony Computer Entertainment Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
 */

#include <simdmath.h>
#include <altivec.h>

#include "common-types.h"


//
// Inverse tangent function of two variables
//
vector float
atan2f4 (vector float y, vector float x)
{
    vec_float4 res = atanf4(divf4(y,x));

    // Use the arguments to determine the quadrant of the result:
    // if (x < 0)
    //   if (y < 0)
    //      res = -PI + res
    //   else
    //      res = PI + res
    //
    vec_uint4 yNeg = (vec_uint4)vec_cmpgt( ((vec_float4){0.0f, 0.0f, 0.0f, 0.0f}) ,y);
    vec_uint4 xNeg = (vec_uint4)vec_cmpgt( ((vec_float4){0.0f, 0.0f, 0.0f, 0.0f}) ,x);

    vec_float4 bias = vec_sel(vec_splatsf4(3.14159265358979323846f),vec_splatsf4(-3.14159265358979323846f),yNeg);

    vec_float4 newRes = vec_add(bias, res);

    res = vec_sel(res,newRes,xNeg);

    return res;
}
