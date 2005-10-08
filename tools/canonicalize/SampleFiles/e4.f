C ========== begin copyright notice ==============
C This file is part of 
C ---------------
C xaifBooster
C ---------------
C Distributed under the BSD license as follows:
C Copyright (c) 2005, The University of Chicago
C All rights reserved.
C
C Redistribution and use in source and binary forms, 
C with or without modification, are permitted provided that the following conditions are met:
C
C    - Redistributions of source code must retain the above copyright notice, 
C      this list of conditions and the following disclaimer.
C    - Redistributions in binary form must reproduce the above copyright notice, 
C      this list of conditions and the following disclaimer in the documentation 
C      and/or other materials provided with the distribution.
C    - Neither the name of The University of Chicago nor the names of its contributors 
C      may be used to endorse or promote products derived from this software without 
C      specific prior written permission.
C
C THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
C EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
C OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
C SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
C INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
C PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
C INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
C LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
C OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
C 
C General Information:
C xaifBooster is intended for the transformation of 
C numerical programs represented as xml files according 
C to the XAIF schema. It is part of the OpenAD framework. 
C The main application is automatic 
C differentiation, i.e. the generation of code for 
C the computation of derivatives. 
C The following people are the principal authors of the 
C current version: 
C 	Uwe Naumann
C	Jean Utke
C Additional contributors are: 
C	Andrew Lyons
C	Peter Fine
C
C For more details about xaifBooster and its use in OpenAD please visit:
C   http://www.mcs.anl.gov/openad
C
C This work is partially supported by:
C 	NSF-ITR grant OCE-0205590
C ========== end copyright notice ==============
      module all_globals_mod

      end module

c$openad XXX Template ad_template.f
c-----------------------------------------------------------------------
      subroutine box_timestep (
     & gammaLoc, fldStar, extForLoc,
     & uVelLoc, fldNow, fldOld, fldNew )
c-----------------------------------------------------------------------

      implicit none

      integer l

c -- routine arguments:
      double precision uVelLoc
      double precision gammaLoc
      double precision fldStar(3 -1)
      double precision extForLoc(3 -1)
      double precision fldNow(3)
      double precision fldNew(3)
      double precision fldOld(3)

c-- local variables:
      double precision vol(3)
      double precision delta_t
      double precision dFldDt(3)
c$openad INDEPENDENT(fldnow)
c -- initialization
      vol(1)=10.
      vol(2)=12.
      vol(3)=14.
      delta_t=20.

c-- routine body

      if ( uVelLoc .GE. 0. ) then
         dFldDt(1) =
     & ( extForLoc(1)
     & + gammaLoc*( fldStar(1) - fldNow(1) )*vol(1)
     & + uVelLoc* ( fldNow(3) - fldNow(1) ) ) / vol(1)
         dFldDt(2) =
     & ( extForLoc(2)
     & + gammaLoc*( fldStar(2) - fldNow(2) )*vol(2)
     & + uVelLoc* ( fldNow(1) - fldNow(2) ) ) / vol(2)
         dFldDt(3) =
     & uVelLoc*( fldNow(2) - fldNow(3) ) / vol(3)
      else
         dFldDt(1) =
     & ( extForLoc(1)
     & + gammaLoc*( fldStar(1) - fldNow(1) )*vol(1)
     & - uVelLoc* ( fldNow(2) - fldNow(1) ) ) / vol(1)
         dFldDt(2) =
     & ( extForLoc(2)
     & + gammaLoc*( fldStar(2) - fldNow(2) )*vol(2)
     & - uVelLoc* ( fldNow(3) - fldNow(2) ) ) / vol(2)
         dFldDt(3) =
     & -uVelLoc*( fldNow(1) - fldNow(3) ) / vol(3)
      end if

      do l = 1, 3
         fldNew(l) = fldOld(l) + 2.D0*delta_t*dFldDt(l)
      enddo
c$openad DEPENDENT(fldnew)
      end
