
      subroutine indep_dep_init(fc,numIV)
      integer current,numIV,g_p_actual,DVcounter,
     +   counter,ivIndex(10000),fc,firstCall,last
      include 'g_pmax.h'
      character*10 indep_tags(g_pmax_)
      common /g_indep_dep/ indep_tags, current,
     +      g_p_actual, DVcounter, counter, ivIndex, firstCall

      firstCall=fc
      current = 1
	counter = 1
	DVcounter = 0
      g_p_actual = numIV
	do j=1,numIV
	   read(92,*) ivIndex(j)
	enddo 
      end

c
c ******************* IV routines ***************************
      subroutine g_tagIV_D(g_p_, var, g_var, ldg_var, tag, units)
      include 'g_pmax.h'
       integer current, g_p_actual, DVcounter,
     +   counter,ivIndex(10000),firstCall
        character*10 indep_tags(g_pmax_)
        common /g_indep_dep/ indep_tags, current,
     +      g_p_actual, DVcounter, counter,ivIndex,firstCall

        logical exists
        double precision var
        character*(*) tag,units
        integer g_p_, ldg_var
        double precision g_var(ldg_var)
	  character*80 blank2zero
	  external blank2zero
        integer :: ad_iv=0

	if(g_p_ .eq. 0) then
	   ad_iv = ad_iv + 1
	   write(77,100)  ad_iv, blank2zero(tag), var, units
 100     format(i10,5x,A,1x,1pg12.4,1x,A) 
      endif

        if (g_p_ .gt. g_pmax_) then
          print *, 'Parameter g_p_ is greater than g_pmax_'
          stop
        endif

	do i=1,g_pmax_
	   g_var(i)=0.0
	enddo


	if(current .eq. ivIndex(counter) .and. counter .le. g_p_) then
         g_var(counter) = 1.0
	   indep_tags(counter) = tag
C ************************** LICH 8/16/2004 *************************
C     polish format          
	   write(94,101) ivIndex(counter),var,blank2zero(tag),units
 101     format(i6,2x,e12.6,3x,a,1x,a)
	   counter = counter + 1
	endif

	current = current + 1

      end
C
C
      subroutine g_tagIV_R(g_p_, var, g_var, ldg_var, tag, units)
      include 'g_pmax.h'
       integer current, g_p_actual, DVcounter,
     +   counter,ivIndex(1000),firstCall
        character*10 indep_tags(g_pmax_)
        common /g_indep_dep/ indep_tags, current,
     +      g_p_actual, DVcounter, counter,ivIndex,firstCall

        logical exists
        real var
        character*(*) tag, units
        integer g_p_, ldg_var
        real g_var(ldg_var)
	  character*80 blank2zero
	  external blank2zero
        integer :: ad_iv=0

c g_p_= 0 is a flag this is used to run in "variable detect mode"
c in this mode, data is written to a "mapping file"
	if(g_p_ .eq. 0) then
	   ad_iv = ad_iv + 1
	   write(77,100)  ad_iv, blank2zero(tag), var, units
 100     format(i10,5x,A,1x,1pg12.4,1x,A) 
      endif

      if (g_p_ .gt. g_pmax_) then
         print *, 'Parameter g_p_ is greater than g_pmax_'
         stop
      endif

	do i=1,g_pmax_
	   g_var(i)=0.0
	enddo


	if(current .eq. ivIndex(counter) .and. counter .le. g_p_) then
         g_var(counter) = 1.0
	   indep_tags(counter) = tag
	   write(94,101) ivIndex(counter),var,blank2zero(tag),units
 101     format(i10,2x,e12.6,3x,a,1x,a)
	   counter = counter + 1
	endif

	current = current + 1

      end
C
c ***************** DV routines **************************
c
      subroutine g_tagDV_D(g_p_, var, g_var, ldg_var, tag, units)
      include 'g_pmax.h'

        integer current,g_p_actual,DVcounter,
     +	  counter,ivIndex(10000),firstCall
        character*10 indep_tags(g_pmax_)
        common /g_indep_dep/ indep_tags, current,
     +       g_p_actual, DVcounter,counter, ivIndex, firstCall

        double precision var
        character*(*) tag,units
        character*10  dep, indep
        integer g_p_, ldg_var
        double precision g_var(ldg_var)
      character*80 blank2zero
	external blank2zero
        if (g_p_ .gt. g_pmax_) then
          print *, 'Parameter g_p_ is greater than g_pmax_'
          stop
        endif

	DVcounter = DVcounter + 1

      if(firstCall .eq. 1) then
	   write(95,102) DVcounter,var,blank2zero(tag),units
 102     format(i10,2x,e12.6,3x,a,1x,a)
	endif
	
	do i=1,g_p_
        indep = indep_tags(i)
	  write (96, *) ivIndex(i),DVcounter, g_var(i)
	  if (DVcounter .eq. 77) then
	    write(396, *) ivIndex(i),var,g_var(i)
	  endif
	enddo
      end
c
c ------------------------------------------------------------------------
c
      subroutine g_tagDV_R(g_p_, var, g_var, ldg_var, tag,units)
      include 'g_pmax.h'

      integer current,g_p_actual,DVcounter,
     +	  counter,ivIndex(10000),firstCall
      character*10 indep_tags(g_pmax_)
      common /g_indep_dep/ indep_tags, current,
     +       g_p_actual, DVcounter,counter, ivIndex, firstCall

      real var
      character*(*) tag,units
      character*10  dep, indep
      integer g_p_, ldg_var
      real g_var(ldg_var)
      character*80 blank2zero
	external blank2zero
 

        if (g_p_ .gt. g_pmax_) then
          print *, 'Parameter g_p_ is greater than g_pmax_'
          stop
        endif

	DVcounter = DVcounter + 1

      if(firstCall .eq. 1) then
	   write(95,102) DVcounter,var,blank2zero(tag),units
 102     format(i10,2x,e12.6,3x,a,1x,a)
	endif
	
	do i=1,g_p_
        indep = indep_tags(i)
	  write (96, *) ivIndex(i),DVcounter, g_var(i)
	enddo
      end

c *********************************************************************************
c

c ******************************************************************
      subroutine writeADO(adoFile,adTitle,numIVs)
      include 'g_pmax.h'
      integer fc,firstCall,last, current,numIV,g_p_actual,DVcounter,
     +   counter,ivIndex(10000)
      common /g_indep_dep/ indep_tags, current,
     +      g_p_actual, DVcounter, counter, ivIndex, firstCall
	character*(*) adoFile,adTitle
	double precision, allocatable, dimension(:,:) :: deriv
	integer error, g_p_, nRuns
	character*80 desc_name
	character*15 units
	double precision value
	integer numIVs, numDVs
	integer get_nRuns, getNumDVs
	external get_nRuns, getNumDVs

c close intermediate files
	close(94)
	close(95)
	close(96)
	print *,'creating AD output file'

c recompute number of runs that was required (need to write a function for this)
      nRuns = numIVs/g_pmax_
	iremainder = numIVs - g_pmax_*nRuns
	if(iremainder .gt. 0) nRuns=nRuns+1
	nRuns = get_nRuns(numIVs)

c  collapse IV,DV,and derivative files into one file
      open(unit=97,file=adoFile)
      write(97,'(A)') adTitle
c
c     IV indices and values
      open(unit=94,file='IVs.txt')
	write(97,*) numIVs
	do i=1,numIVs
	   read(94,101) k,value,desc_name,units
C ************************** LICH 8/16/2004 *************************
C     polish format          
 101     format(i6,2x,e12.6,3x,a,1x,a)
	   write(97,103) k,value,desc_name,units
 103     format(i10,2x,e12.6,3x,A,1x,a15)
	enddo
	close(94)
c
c     DV indices and values
      open(unit=95,file='DVs.txt')
	numDVs = getNumDVs()
	write(97,*) numDVs
	do i=1,numDVs   
	   read(95,106) k,value,desc_name,units
 106     format(i10,2x,e12.6,3x,a,1x,a15)
	   write(97,104) k,value,desc_name,units
 104     format(i10,2x,e12.6,3x,A,1x,a15)
	enddo
      close(95)
c
      open(unit=96,file='derivs.txt')
	allocate(deriv(numIVs,numDVs),stat=error)
	if(error /= 0) then
	   print *,"writeADO: could not allocate space for deriv"
	   stop
	endif
      do i=1,nRuns
	   if(i .eq. nRuns) then
	      g_p_=numIVs - g_pmax_*(nRuns-1)
	   else 
	      g_p_ = g_pmax_
	   endif
	   do j=1,numDVs
	      do k=1,g_p_
	         read(96,*) ick,jck,value
	         iindex=(i-1)*g_pmax_ + k
	         deriv(iindex,j)=value
	      enddo
	   enddo
	enddo
      close(96)

	do i=1,numIVs
	   do j=1,numDVs
C ************************** LICH 8/25/2004 *************************
C     data compatible with the GUI program          
	      if(abs(deriv(i,j)) .gt. 10.0**30) then
			  if(deriv(i,j) .gt. 0) deriv(i,j) = 10.0**30
			  if(deriv(i,j) .lt. 0) deriv(i,j) = -10.0**30
	      endif
	      write(97,*) deriv(i,j)
	   enddo
	enddo
	deallocate(deriv,stat=error)
	if(error /= 0) then
	   print *,"writeADO: could not deallocate deriv"
	   stop
	endif
	close(97)

	return
	end
c
c ******************************************************************
      integer function getNumDVs()
      include 'g_pmax.h'
      integer fc,firstCall,last, current,numIV,g_p_actual,DVcounter,
     +   counter,ivIndex(10000)
      character*10 indep_tags(g_pmax_)
      common /g_indep_dep/ indep_tags, current,
     +      g_p_actual, DVcounter, counter, ivIndex, firstCall
	getNumDVs=DVcounter
	end
c
c ****************************************************************
      integer function get_nRuns(numIVs)
      include 'g_pmax.h'
	integer numIVs, iremainder, nRuns
c
      nRuns = numIVs/g_pmax_
	iremainder = numIVs - g_pmax_*nRuns
	if(iremainder .gt. 0) nRuns=nRuns+1
	get_nRuns = nRuns
c	return
	end
c ************************************************************
c
	character*80 function blank2zero(oldName)
	character*(*) oldName
	integer swap
	integer j
	swap=0
	j=0
	do i=1,80
	   if(oldName(i:i).eq.'(') then 
	      swap=1
	   else if(oldName(i:i).eq.')') then 
	      swap=0
	   endif
c strip or swap blank as needed
	   if(oldName(i:i).eq.' ') then 
	      if(swap.eq.1) then
	         j=j+1
		     blank2zero(j:j)='0'
	      endif
	   else
	      j=j+1
	      blank2zero(j:j)=oldName(i:i)
	   endif
	end do

c add blanks to the end of new string
      do i=j+1,80
	   blank2zero(i:i)=' '
	enddo
	end
