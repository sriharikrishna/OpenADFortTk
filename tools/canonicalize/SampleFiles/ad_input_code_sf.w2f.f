        module w2f__types

        integer :: w2f__4, w2f__8, w2f__16
        parameter (w2f__4 = kind(0.0))
        parameter (w2f__8 = kind(0.0d0))
        parameter (w2f__16 = selected_real_kind(p=30))

        integer :: w2f__i1, w2f__i2, w2f__i4,w2f__i8
        parameter (w2f__i1 = selected_int_kind(r=2))
        parameter (w2f__i2 = selected_int_kind(r=3))
        parameter (w2f__i4 = selected_int_kind(r=8))
        parameter (w2f__i8 = selected_int_kind(r=16))

        end module w2f__types
C ***********************************************************
C Fortran file translated from WHIRL Wed Sep  7 09:54:58 2005
C ***********************************************************
C ***********************************************************

      MODULE size_mod
      use w2f__types
      IMPLICIT NONE
      SAVE
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) MAX_OLX
      PARAMETER ( MAX_OLX = 3)
      INTEGER(w2f__i4) MAX_OLY
      PARAMETER ( MAX_OLY = 3)
      INTEGER(w2f__i4) NOBCS
      PARAMETER ( NOBCS = 4)
      INTEGER(w2f__i4) NPX
      PARAMETER ( NPX = 1)
      INTEGER(w2f__i4) NPY
      PARAMETER ( NPY = 1)
      INTEGER(w2f__i4) NR
      PARAMETER ( NR = 15)
      INTEGER(w2f__i4) NSX
      PARAMETER ( NSX = 1)
      INTEGER(w2f__i4) NSY
      PARAMETER ( NSY = 1)
      INTEGER(w2f__i4) NX
      PARAMETER ( NX = 90)
      INTEGER(w2f__i4) NY
      PARAMETER ( NY = 40)
      INTEGER(w2f__i4) OLX
      PARAMETER ( OLX = 3)
      INTEGER(w2f__i4) OLY
      PARAMETER ( OLY = 3)
      INTEGER(w2f__i4) SNX
      PARAMETER ( SNX = 90)
      INTEGER(w2f__i4) SNY
      PARAMETER ( SNY = 40)
C
C     **** Statements ****
C
      END MODULE

      MODULE eeparams_mod
      use w2f__types
      use size_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      LOGICAL(w2f__i4) EEBOOTERROR
      INTEGER(w2f__i4) EEDATAUNIT
      LOGICAL(w2f__i4) EEENDERROR
      INTEGER(w2f__i4) ERRORMESSAGEUNIT
      LOGICAL(w2f__i4) FATALERROR
      INTEGER(w2f__i4) IOERRORCOUNT(1 : 32)
      INTEGER(w2f__i4) MODELDATAUNIT
      INTEGER(w2f__i4) MYBXHI(1 : 32)
      INTEGER(w2f__i4) MYBXLO(1 : 32)
      INTEGER(w2f__i4) MYBYHI(1 : 32)
      INTEGER(w2f__i4) MYBYLO(1 : 32)
      INTEGER(w2f__i4) MYPROCID
      INTEGER(w2f__i4) MYPX
      INTEGER(w2f__i4) MYPY
      INTEGER(w2f__i4) MYXGLOBALLO
      INTEGER(w2f__i4) MYYGLOBALLO
      INTEGER(w2f__i4) NTHREADS
      INTEGER(w2f__i4) NTX
      INTEGER(w2f__i4) NTY
      INTEGER(w2f__i4) NUMBEROFPROCS
      INTEGER(w2f__i4) PIDIO
      INTEGER(w2f__i4) SCRUNIT1
      INTEGER(w2f__i4) SCRUNIT2
      INTEGER(w2f__i4) STANDARDMESSAGEUNIT
      LOGICAL(w2f__i4) USECOUPLER
      LOGICAL(w2f__i4) USECUBEDSPHEREEXCHANGE
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) CACHELINESIZE
      PARAMETER ( CACHELINESIZE = 256)
      CHARACTER(1) COMMENTCHARACTER
      PARAMETER ( COMMENTCHARACTER = "#")
      INTEGER(w2f__i4) EXCH_IGNORE_CORNERS
      PARAMETER ( EXCH_IGNORE_CORNERS = 0)
      INTEGER(w2f__i4) EXCH_UPDATE_CORNERS
      PARAMETER ( EXCH_UPDATE_CORNERS = 1)
      INTEGER(w2f__i4) FORWARD_SIMULATION
      PARAMETER ( FORWARD_SIMULATION = 0)
      INTEGER(w2f__i4) INDEX_I
      PARAMETER ( INDEX_I = 1)
      INTEGER(w2f__i4) INDEX_J
      PARAMETER ( INDEX_J = 2)
      INTEGER(w2f__i4) INDEX_K
      PARAMETER ( INDEX_K = 3)
      INTEGER(w2f__i4) INDEX_NONE
      PARAMETER ( INDEX_NONE = 4)
      INTEGER(w2f__i4) LSHARE1
      PARAMETER ( LSHARE1 = 256)
      INTEGER(w2f__i4) LSHARE4
      PARAMETER ( LSHARE4 = 64)
      INTEGER(w2f__i4) LSHARE8
      PARAMETER ( LSHARE8 = 32)
      INTEGER(w2f__i4) MAX_LEN_FNAM
      PARAMETER ( MAX_LEN_FNAM = 512)
      INTEGER(w2f__i4) MAX_LEN_MBUF
      PARAMETER ( MAX_LEN_MBUF = 512)
      INTEGER(w2f__i4) MAX_LEN_PREC
      PARAMETER ( MAX_LEN_PREC = 200)
      INTEGER(w2f__i4) MAX_NO_BARRIERS
      PARAMETER ( MAX_NO_BARRIERS = 1)
      INTEGER(w2f__i4) MAX_NO_PROCS
      PARAMETER ( MAX_NO_PROCS = 2048)
      INTEGER(w2f__i4) MAX_NO_THREADS
      PARAMETER ( MAX_NO_THREADS = 32)
      CHARACTER(2) PRINT_MAP_XY
      PARAMETER ( PRINT_MAP_XY = "XY")
      CHARACTER(2) PRINT_MAP_XZ
      PARAMETER ( PRINT_MAP_XZ = "XZ")
      CHARACTER(2) PRINT_MAP_YZ
      PARAMETER ( PRINT_MAP_YZ = "YZ")
      INTEGER(w2f__i4) REVERSE_SIMULATION
      PARAMETER ( REVERSE_SIMULATION = 1)
      CHARACTER(1) SQUEEZE_BOTH
      PARAMETER ( SQUEEZE_BOTH = "B")
      CHARACTER(1) SQUEEZE_LEFT
      PARAMETER ( SQUEEZE_LEFT = "L")
      CHARACTER(1) SQUEEZE_RIGHT
      PARAMETER ( SQUEEZE_RIGHT = "R")
      INTEGER(w2f__i4) TANGENT_SIMULATION
      PARAMETER ( TANGENT_SIMULATION = 2)
C
C     **** Statements ****
C
      END MODULE

      MODULE params_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) ABEPS
      REAL(w2f__8) ADJDUMPFREQ
      REAL(w2f__8) ADJMONITORFREQ
      REAL(w2f__8) AFFACMOM
      LOGICAL(w2f__i4) ALLOWFREEZING
      REAL(w2f__8) ALPH_AB
      REAL(w2f__8) ATM_CP
      REAL(w2f__8) ATM_KAPPA
      REAL(w2f__8) ATM_PO
      REAL(w2f__8) ATM_RD
      REAL(w2f__8) ATM_RQ
      REAL(w2f__8) BASETIME
      CHARACTER(512) BATHYFILE
      REAL(w2f__8) BETA
      REAL(w2f__8) BETA_AB
      REAL(w2f__8) BOTTOMDRAGLINEAR
      REAL(w2f__8) BOTTOMDRAGQUADRATIC
      CHARACTER(512) BUOYANCYRELATION
      REAL(w2f__8) CADJFREQ
      LOGICAL(w2f__i4) CALENDARDUMPS
      REAL(w2f__8) CELSIUS2K
      REAL(w2f__8) CFFACMOM
      INTEGER(w2f__i4) CG2DCHKRESFREQ
      INTEGER(w2f__i4) CG2DMAXITERS
      REAL(w2f__8) CG2DPCOFFDFAC
      INTEGER(w2f__i4) CG2DPRECONDFREQ
      REAL(w2f__8) CG2DTARGETRESIDUAL
      REAL(w2f__8) CG2DTARGETRESWUNIT
      INTEGER(w2f__i4) CG3DCHKRESFREQ
      INTEGER(w2f__i4) CG3DMAXITERS
      REAL(w2f__8) CG3DTARGETRESIDUAL
      CHARACTER(5) CHECKPTSUFF(1 : 2)
      REAL(w2f__8) CHKPTFREQ
      REAL(w2f__8) CONVERTEMP2RUNIT
      REAL(w2f__8) CONVERTFW2SALT
      REAL(w2f__8) COSPOWER
      INTEGER(w2f__i4) DEBUGLEVEL
      LOGICAL(w2f__i4) DEBUGMODE
      REAL(w2f__8) DELR(1 : 15)
      REAL(w2f__8) DELRC(1 : 16)
      REAL(w2f__8) DELT
      REAL(w2f__8) DELTAT
      REAL(w2f__8) DELTATCLOCK
      REAL(w2f__8) DELTATFREESURF
      REAL(w2f__8) DELTATMOM
      REAL(w2f__8) DELX(1 : 90)
      CHARACTER(512) DELXFILE
      REAL(w2f__8) DELY(1 : 40)
      CHARACTER(512) DELYFILE
      REAL(w2f__8) DIAGFREQ
      REAL(w2f__8) DIFFK4S
      REAL(w2f__8) DIFFK4T
      REAL(w2f__8) DIFFKHS
      REAL(w2f__8) DIFFKHT
      REAL(w2f__8) DIFFKRBL79DEEP
      REAL(w2f__8) DIFFKRBL79HO
      REAL(w2f__8) DIFFKRBL79SCL
      REAL(w2f__8) DIFFKRBL79SURF
      REAL(w2f__8) DIFFKRNRS(1 : 15)
      REAL(w2f__8) DIFFKRNRT(1 : 15)
      LOGICAL(w2f__i4) DOSALTCLIMRELAX
      LOGICAL(w2f__i4) DOTHETACLIMRELAX
      LOGICAL(w2f__i4) DOTR1CLIMRELAX
      CHARACTER(512) DQDTFILE
      REAL(w2f__8) DTTRACERLEV(1 : 15)
      REAL(w2f__8) DUMPFREQ
      LOGICAL(w2f__i4) DUMPINITANDLAST
      CHARACTER(512) EDDYTAUXFILE
      CHARACTER(512) EDDYTAUYFILE
      CHARACTER(512) EMPMRFILE
      REAL(w2f__8) ENDTIME
      CHARACTER(6) EOSTYPE
      LOGICAL(w2f__i4) EXACTCONSERV
      REAL(w2f__8) EXTERNFORCINGCYCLE
      REAL(w2f__8) EXTERNFORCINGPERIOD
      REAL(w2f__8) F0
      LOGICAL(w2f__i4) FLUIDISAIR
      LOGICAL(w2f__i4) FLUIDISWATER
      REAL(w2f__8) FOFACMOM
      LOGICAL(w2f__i4) FORCING_IN_AB
      REAL(w2f__8) FREESURFFAC
      REAL(w2f__8) GBARO
      LOGICAL(w2f__i4) GLOBALFILES
      REAL(w2f__8) GRAVITY
      REAL(w2f__8) HEATCAPACITY_CP
      REAL(w2f__8) HFACINF
      REAL(w2f__8) HFACMIN
      REAL(w2f__8) HFACMINDP
      REAL(w2f__8) HFACMINDR
      REAL(w2f__8) HFACMINDZ
      REAL(w2f__8) HFACSUP
      LOGICAL(w2f__i4) HIGHORDERVORTICITY
      REAL(w2f__8) HORIVERTRATIO
      CHARACTER(512) HORIZGRIDFILE
      CHARACTER(512) HYDROGSALTFILE
      CHARACTER(512) HYDROGTHETAFILE
      REAL(w2f__8) IMPLICDIV2DFLOW
      LOGICAL(w2f__i4) IMPLICITDIFFUSION
      LOGICAL(w2f__i4) IMPLICITFREESURFACE
      LOGICAL(w2f__i4) IMPLICITVISCOSITY
      REAL(w2f__8) IMPLICSURFPRESS
      LOGICAL(w2f__i4) INADEXACT
      LOGICAL(w2f__i4) INADFALSE
      LOGICAL(w2f__i4) INADMODE
      LOGICAL(w2f__i4) INADTRUE
      INTEGER(w2f__i4) INTEGR_GEOPOT
      REAL(w2f__8) IVDC_KAPPA
      CHARACTER(512) LAMBDASALTFILE
      CHARACTER(512) LAMBDATHETAFILE
      REAL(w2f__8) LAMBDATR1CLIMRELAX
      REAL(w2f__8) LATBANDCLIMRELAX
      CHARACTER(512) MDSIOLOCALDIR
      CHARACTER(512) MERIDWINDFILE
      LOGICAL(w2f__i4) METRICTERMS
      LOGICAL(w2f__i4) MOMADVECTION
      LOGICAL(w2f__i4) MOMFORCING
      LOGICAL(w2f__i4) MOMIMPLVERTADV
      LOGICAL(w2f__i4) MOMPRESSUREFORCING
      LOGICAL(w2f__i4) MOMSTEPPING
      LOGICAL(w2f__i4) MOMVISCOSITY
      REAL(w2f__8) MONITORFREQ
      LOGICAL(w2f__i4) MONITOR_STDIO
      REAL(w2f__8) MTFACMOM
      LOGICAL(w2f__i4) MULTIDIMADVECTION
      INTEGER(w2f__i4) NCHECKLEV
      INTEGER(w2f__i4) NENDITER
      REAL(w2f__8) NH_AM2
      INTEGER(w2f__i4) NITER0
      LOGICAL(w2f__i4) NONHYDROSTATIC
      INTEGER(w2f__i4) NONLINFREESURF
      LOGICAL(w2f__i4) NO_SLIP_BOTTOM
      LOGICAL(w2f__i4) NO_SLIP_SIDES
      INTEGER(w2f__i4) NTIMESTEPS
      INTEGER(w2f__i4) NUMSTEPSPERPICKUP
      REAL(w2f__8) OMEGA
      LOGICAL(w2f__i4) OUTPUTTYPESINCLUSIVE
      REAL(w2f__8) PCHKPTFREQ
      LOGICAL(w2f__i4) PERIODICEXTERNALFORCING
      REAL(w2f__8) PFFACMOM
      REAL(w2f__8) PHIMIN
      CHARACTER(10) PICKUPSUFF
      LOGICAL(w2f__i4) PICKUP_READ_MDSIO
      LOGICAL(w2f__i4) PICKUP_WRITE_IMMED
      LOGICAL(w2f__i4) PICKUP_WRITE_MDSIO
      CHARACTER(512) PLOADFILE
      CHARACTER(512) PSURFINITFILE
      LOGICAL(w2f__i4) QUASIHYDROSTATIC
      REAL(w2f__8) RCD
      INTEGER(w2f__i4) READBINARYPREC
      REAL(w2f__8) RECIP_CP
      REAL(w2f__8) RECIP_GRAVITY
      REAL(w2f__8) RECIP_HORIVERTRATIO
      REAL(w2f__8) RECIP_RHOCONST
      REAL(w2f__8) RECIP_RHONIL
      REAL(w2f__8) RECIP_RSPHERE
      REAL(w2f__8) RHOCONST
      REAL(w2f__8) RHOCONSTFRESH
      REAL(w2f__8) RHONIL
      LOGICAL(w2f__i4) RIGIDLID
      REAL(w2f__8) ROTATIONPERIOD
      REAL(w2f__8) RO_SEALEVEL
      REAL(w2f__8) RSPHERE
      LOGICAL(w2f__i4) SADOURNYCORIOLIS
      LOGICAL(w2f__i4) SALTADVECTION
      INTEGER(w2f__i4) SALTADVSCHEME
      CHARACTER(512) SALTCLIMFILE
      CHARACTER(512) SALTFLUXFILE
      LOGICAL(w2f__i4) SALTFORCING
      LOGICAL(w2f__i4) SALTIMPLVERTADV
      LOGICAL(w2f__i4) SALTSTEPPING
      INTEGER(w2f__i4) SALTVERTADVSCHEME
      REAL(w2f__8) SALT_EVPRRN
      INTEGER(w2f__i4) SELECTFINDROSURF
      INTEGER(w2f__i4) SELECT_RSTAR
      LOGICAL(w2f__i4) SETCENTERDR
      LOGICAL(w2f__i4) SNAPSHOT_MDSIO
      REAL(w2f__8) SREF(1 : 15)
      LOGICAL(w2f__i4) STAGGERTIMESTEP
      LOGICAL(w2f__i4) STARTFROMPICKUPAB2
      REAL(w2f__8) STARTTIME
      CHARACTER(512) SURFQFILE
      CHARACTER(512) SURFQNETFILE
      CHARACTER(512) SURFQSWFILE
      REAL(w2f__8) TAUCD
      REAL(w2f__8) TAUSALTCLIMRELAX
      REAL(w2f__8) TAUTHETACLIMRELAX
      REAL(w2f__8) TAUTR1CLIMRELAX
      REAL(w2f__8) TAVEFREQ
      REAL(w2f__8) TAVE_LASTITER
      REAL(w2f__8) TCYLIN
      REAL(w2f__8) TCYLOUT
      LOGICAL(w2f__i4) TEMPADVECTION
      INTEGER(w2f__i4) TEMPADVSCHEME
      LOGICAL(w2f__i4) TEMPFORCING
      LOGICAL(w2f__i4) TEMPIMPLVERTADV
      LOGICAL(w2f__i4) TEMPSTEPPING
      INTEGER(w2f__i4) TEMPVERTADVSCHEME
      REAL(w2f__8) TEMP_EVPRRN
      CHARACTER(512) THETACLIMFILE
      REAL(w2f__8) THETAMIN
      CHARACTER(512) THE_RUN_NAME
      LOGICAL(w2f__i4) TIMEAVE_MDSIO
      CHARACTER(512) TOPOFILE
      REAL(w2f__8) TREF(1 : 15)
      LOGICAL(w2f__i4) UNIFORMLIN_PHISURF
      LOGICAL(w2f__i4) UPWINDSHEAR
      LOGICAL(w2f__i4) UPWINDVORTICITY
      LOGICAL(w2f__i4) USEABSVORTICITY
      LOGICAL(w2f__i4) USEAIM
      LOGICAL(w2f__i4) USEANISOTROPICVISCAGRIDMAX
      LOGICAL(w2f__i4) USEBETAPLANEF
      LOGICAL(w2f__i4) USEBULKFORCE
      LOGICAL(w2f__i4) USECDSCHEME
      LOGICAL(w2f__i4) USECONSTANTF
      LOGICAL(w2f__i4) USECORIOLIS
      LOGICAL(w2f__i4) USEDIAGNOSTICS
      LOGICAL(w2f__i4) USEDYNP_INEOS_ZC
      LOGICAL(w2f__i4) USEEBM
      LOGICAL(w2f__i4) USEECCO
      LOGICAL(w2f__i4) USEENERGYCONSERVINGCORIOLIS
      LOGICAL(w2f__i4) USEFIZHI
      LOGICAL(w2f__i4) USEFLT
      LOGICAL(w2f__i4) USEFULLLEITH
      LOGICAL(w2f__i4) USEGCHEM
      LOGICAL(w2f__i4) USEGGL90
      LOGICAL(w2f__i4) USEGMREDI
      LOGICAL(w2f__i4) USEGRDCHK
      LOGICAL(w2f__i4) USEGRIDALT
      LOGICAL(w2f__i4) USEJAMARTMOMADV
      LOGICAL(w2f__i4) USEJAMARTWETPOINTS
      LOGICAL(w2f__i4) USEKPP
      LOGICAL(w2f__i4) USELAND
      LOGICAL(w2f__i4) USEMATRIX
      LOGICAL(w2f__i4) USEMNC
      LOGICAL(w2f__i4) USEMULTIDIMADVEC
      LOGICAL(w2f__i4) USEMY82
      LOGICAL(w2f__i4) USENHMTERMS
      LOGICAL(w2f__i4) USEOBCS
      LOGICAL(w2f__i4) USEOLDFREEZING
      LOGICAL(w2f__i4) USEOPPS
      LOGICAL(w2f__i4) USEPICKUPBEFOREC35
      LOGICAL(w2f__i4) USEPICKUPBEFOREC54
      LOGICAL(w2f__i4) USEPP81
      LOGICAL(w2f__i4) USEPTRACERS
      LOGICAL(w2f__i4) USEREALFRESHWATERFLUX
      LOGICAL(w2f__i4) USERUNCLOCK
      LOGICAL(w2f__i4) USESBO
      LOGICAL(w2f__i4) USESEAICE
      LOGICAL(w2f__i4) USESHAP_FILT
      LOGICAL(w2f__i4) USESINGLECPUIO
      LOGICAL(w2f__i4) USESPHEREF
      LOGICAL(w2f__i4) USETHSICE
      LOGICAL(w2f__i4) USEZONAL_FILT
      LOGICAL(w2f__i4) USINGCARTESIANGRID
      LOGICAL(w2f__i4) USINGCURVILINEARGRID
      LOGICAL(w2f__i4) USINGCYLINDRICALGRID
      LOGICAL(w2f__i4) USINGPCOORDS
      LOGICAL(w2f__i4) USINGSPHERICALPOLARGRID
      LOGICAL(w2f__i4) USINGSPHERICALPOLARMTERMS
      LOGICAL(w2f__i4) USINGZCOORDS
      CHARACTER(512) UVELINITFILE
      LOGICAL(w2f__i4) VECTORINVARIANTMOMENTUM
      REAL(w2f__8) VFFACMOM
      REAL(w2f__8) VISCA4
      REAL(w2f__8) VISCA4D
      REAL(w2f__8) VISCA4GRID
      REAL(w2f__8) VISCA4GRIDMAX
      REAL(w2f__8) VISCA4GRIDMIN
      REAL(w2f__8) VISCA4MAX
      REAL(w2f__8) VISCA4W
      REAL(w2f__8) VISCA4Z
      REAL(w2f__8) VISCAH
      REAL(w2f__8) VISCAHD
      REAL(w2f__8) VISCAHGRID
      REAL(w2f__8) VISCAHGRIDMAX
      REAL(w2f__8) VISCAHGRIDMIN
      REAL(w2f__8) VISCAHMAX
      REAL(w2f__8) VISCAHW
      REAL(w2f__8) VISCAHZ
      REAL(w2f__8) VISCAR
      REAL(w2f__8) VISCASTRAIN
      REAL(w2f__8) VISCATENSION
      REAL(w2f__8) VISCC2LEITH
      REAL(w2f__8) VISCC2LEITHD
      REAL(w2f__8) VISCC2SMAG
      REAL(w2f__8) VISCC4LEITH
      REAL(w2f__8) VISCC4LEITHD
      CHARACTER(512) VVELINITFILE
      INTEGER(w2f__i4) WRITEBINARYPREC
      INTEGER(w2f__i4) WRITESTATEPREC
      CHARACTER(512) ZONALWINDFILE
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) DEBLEVA
      PARAMETER ( DEBLEVA = 1)
      INTEGER(w2f__i4) DEBLEVB
      PARAMETER ( DEBLEVB = 2)
      INTEGER(w2f__i4) DEBLEVZERO
      PARAMETER ( DEBLEVZERO = 0)
      REAL(w2f__8) DEG2RAD
      PARAMETER ( DEG2RAD =   0.01745329251994330)
      INTEGER(w2f__i4) MAXNOCHKPTLEV
      PARAMETER ( MAXNOCHKPTLEV = 2)
      REAL(w2f__8) PI
      PARAMETER ( PI =     3.141592653589793)
      INTEGER(w2f__i4) PRECFLOAT32
      PARAMETER ( PRECFLOAT32 = 32)
      INTEGER(w2f__i4) PRECFLOAT64
      PARAMETER ( PRECFLOAT64 = 64)
      REAL(w2f__4) UNSET_FLOAT4
      PARAMETER ( UNSET_FLOAT4 =     123456.7)
      REAL(w2f__8) UNSET_FLOAT8
      PARAMETER ( UNSET_FLOAT8 =     123456.7000000000)
      INTEGER(w2f__i4) UNSET_I
      PARAMETER ( UNSET_I = 123456789)
      REAL(w2f__8) UNSET_RL
      PARAMETER ( UNSET_RL =     123456.7000000000)
      REAL(w2f__8) UNSET_RS
      PARAMETER ( UNSET_RS =     123456.7031250000)
C
C     **** Statements ****
C
      END MODULE

      MODULE bar2_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      LOGICAL(w2f__i4) BAR2COLLECTSTATISTICS
      INTEGER(w2f__i4) BAR2_BARRIERCOUNT(1 : 64, 1 : 32)
      INTEGER(w2f__i4) BAR2_LEVEL(1 : 64, 1 : 32)
      INTEGER(w2f__i4) BAR2_SPINSCOUNT(1 : 64, 1 : 32)
      INTEGER(w2f__i4) BAR2_SPINSMAX(1 : 64, 1 : 32)
      INTEGER(w2f__i4) BAR2_SPINSMIN(1 : 64, 1 : 32)
C
C     **** Statements ****
C
      END MODULE

      MODULE barrier_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      INTEGER(w2f__i4) DOOR1
      INTEGER(w2f__i4) DOOR2
      INTEGER(w2f__i4) DOOR3
      INTEGER(w2f__i4) KEY1(1 : 64, 1 : 32)
      INTEGER(w2f__i4) KEY2(1 : 64, 1 : 32)
      INTEGER(w2f__i4) KEY3(1 : 64, 1 : 32)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) INVALID
      PARAMETER ( INVALID = 0)
      INTEGER(w2f__i4) OPEN
      PARAMETER ( OPEN = 1)
      INTEGER(w2f__i4) SHUT
      PARAMETER ( SHUT = 0)
      INTEGER(w2f__i4) VALID
      PARAMETER ( VALID = 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE cd_code_vars_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) ETANM1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) UNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) UVELD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VVELD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE cg2d_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) AS2D(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) AW2D(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) CG2DNORM
      LOGICAL(w2f__i4) CG2DNORMALISERHS
      REAL(w2f__8) CG2DTOLERANCE
      REAL(w2f__8) CG2D_Q(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) CG2D_R(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) CG2D_S(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) PC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) PS(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) PW(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE cg3d_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Statements ****
C
      END MODULE

      MODULE cost_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) CMEANTHETA(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) CMEANUVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) CMEANVVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) FC
      REAL(w2f__8) LASTINTERVAL
      REAL(w2f__8) MULT_ATL
      REAL(w2f__8) MULT_EFLUX
      REAL(w2f__8) MULT_ENTROPY
      REAL(w2f__8) MULT_TEST
      REAL(w2f__8) MULT_TRACER
      REAL(w2f__8) MULT_T_MISFIT
      REAL(w2f__8) OBJF_ATL(1 : 1, 1 : 1)
      REAL(w2f__8) OBJF_EFLUX(1 : 1, 1 : 1)
      REAL(w2f__8) OBJF_ENTROPY(1 : 1, 1 : 1)
      REAL(w2f__8) OBJF_TEST(1 : 1, 1 : 1)
      REAL(w2f__8) OBJF_TRACER(1 : 1, 1 : 1)
      REAL(w2f__8) OBJF_T_MISFIT(1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE ctrl_dummy_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) XX_AQH_DUMMY
      REAL(w2f__8) XX_AQH_MEAN_DUMMY
      REAL(w2f__8) XX_ATEMP_DUMMY
      REAL(w2f__8) XX_ATEMP_MEAN_DUMMY
      REAL(w2f__8) XX_BOTTOMDRAG_DUMMY
      REAL(w2f__8) XX_DIFFKR_DUMMY
      REAL(w2f__8) XX_EDTAUX_DUMMY
      REAL(w2f__8) XX_EDTAUY_DUMMY
      REAL(w2f__8) XX_EFLUXP_DUMMY
      REAL(w2f__8) XX_EFLUXY_DUMMY
      REAL(w2f__8) XX_ETAN_DUMMY
      REAL(w2f__8) XX_HFACC_DUMMY
      REAL(w2f__8) XX_HFLUX_DUMMY
      REAL(w2f__8) XX_HFLUX_MEAN_DUMMY
      REAL(w2f__8) XX_KAPGM_DUMMY
      REAL(w2f__8) XX_OBCSE_DUMMY
      REAL(w2f__8) XX_OBCSN_DUMMY
      REAL(w2f__8) XX_OBCSS_DUMMY
      REAL(w2f__8) XX_OBCSW_DUMMY
      REAL(w2f__8) XX_PRECIP_DUMMY
      REAL(w2f__8) XX_PRECIP_MEAN_DUMMY
      REAL(w2f__8) XX_PSBAR_MEAN_DUMMY
      REAL(w2f__8) XX_RELAXSSS_DUMMY
      REAL(w2f__8) XX_RELAXSST_DUMMY
      REAL(w2f__8) XX_SALT_DUMMY
      REAL(w2f__8) XX_SALT_INI_FIN_DUMMY
      REAL(w2f__8) XX_SBAR_MEAN_DUMMY
      REAL(w2f__8) XX_SFLUX_DUMMY
      REAL(w2f__8) XX_SFLUX_MEAN_DUMMY
      REAL(w2f__8) XX_SSS_DUMMY
      REAL(w2f__8) XX_SST_DUMMY
      REAL(w2f__8) XX_SWDOWN_DUMMY
      REAL(w2f__8) XX_SWDOWN_MEAN_DUMMY
      REAL(w2f__8) XX_SWFLUX_DUMMY
      REAL(w2f__8) XX_SWFLUX_MEAN_DUMMY
      REAL(w2f__8) XX_TAUU_DUMMY
      REAL(w2f__8) XX_TAUV_DUMMY
      REAL(w2f__8) XX_TAUX_MEAN_DUMMY
      REAL(w2f__8) XX_TAUY_MEAN_DUMMY
      REAL(w2f__8) XX_TBAR_MEAN_DUMMY
      REAL(w2f__8) XX_THETA_DUMMY
      REAL(w2f__8) XX_THETA_INI_FIN_DUMMY
      REAL(w2f__8) XX_TR1_DUMMY
      REAL(w2f__8) XX_UBAR_MEAN_DUMMY
      REAL(w2f__8) XX_UVEL_DUMMY
      REAL(w2f__8) XX_UWIND_DUMMY
      REAL(w2f__8) XX_UWIND_MEAN_DUMMY
      REAL(w2f__8) XX_VBAR_MEAN_DUMMY
      REAL(w2f__8) XX_VVEL_DUMMY
      REAL(w2f__8) XX_VWIND_DUMMY
      REAL(w2f__8) XX_VWIND_MEAN_DUMMY
      REAL(w2f__8) XX_WBAR_MEAN_DUMMY
C
C     **** Statements ****
C
      END MODULE

      MODULE ctrl_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      CHARACTER(9) COSTNAME
      CHARACTER(9) CTRLNAME
      LOGICAL(w2f__i4) DOADMTLM
      LOGICAL(w2f__i4) DOINITXX
      LOGICAL(w2f__i4) DOPACKDIAG
      LOGICAL(w2f__i4) DOZSCALEPACK
      LOGICAL(w2f__i4) DOZSCALEUNPACK
      REAL(w2f__8) FILEFC
      INTEGER(w2f__i4) FILEI
      INTEGER(w2f__i4) FILEIG
      INTEGER(w2f__i4) FILEJ
      INTEGER(w2f__i4) FILEJG
      INTEGER(w2f__i4) FILEK
      INTEGER(w2f__i4) FILENCBUFFINDEX
      CHARACTER(1) FILENCVARGRD(1 : 40)
      INTEGER(w2f__i4) FILENCVARINDEX(1 : 40)
      INTEGER(w2f__i4) FILENCVARNRMAX(1 : 40)
      INTEGER(w2f__i4) FILENCVARRECS(1 : 40)
      INTEGER(w2f__i4) FILENCVARXMAX(1 : 40)
      INTEGER(w2f__i4) FILENCVARYMAX(1 : 40)
      INTEGER(w2f__i4) FILENSX
      INTEGER(w2f__i4) FILENSY
      INTEGER(w2f__i4) FILENVARLENGTH
      INTEGER(w2f__i4) FILENVARTYPE
      INTEGER(w2f__i4) FILENWETCGLOBAL(1 : 15)
      INTEGER(w2f__i4) FILENWETSGLOBAL(1 : 15)
      INTEGER(w2f__i4) FILENWETVGLOBAL(1 : 15)
      INTEGER(w2f__i4) FILENWETWGLOBAL(1 : 15)
      INTEGER(w2f__i4) FILEOPTIMCYCLE
      CHARACTER(10) FILEYCTRLID
      CHARACTER(80) FNAME_AQH(1 : 2)
      CHARACTER(80) FNAME_ATEMP(1 : 2)
      CHARACTER(80) FNAME_BOTTOMDRAG(1 : 2)
      CHARACTER(80) FNAME_DIFFKR(1 : 2)
      CHARACTER(80) FNAME_EDTAUX(1 : 2)
      CHARACTER(80) FNAME_EDTAUY(1 : 2)
      CHARACTER(80) FNAME_EFLUXP(1 : 2)
      CHARACTER(80) FNAME_EFLUXY(1 : 2)
      CHARACTER(80) FNAME_ETAN(1 : 2)
      CHARACTER(80) FNAME_HFACC(1 : 2)
      CHARACTER(80) FNAME_HFLUX(1 : 2)
      CHARACTER(80) FNAME_KAPGM(1 : 2)
      CHARACTER(80) FNAME_OBCSE(1 : 2)
      CHARACTER(80) FNAME_OBCSN(1 : 2)
      CHARACTER(80) FNAME_OBCSS(1 : 2)
      CHARACTER(80) FNAME_OBCSW(1 : 2)
      CHARACTER(80) FNAME_PRECIP(1 : 2)
      CHARACTER(80) FNAME_RELAXSSS(1 : 2)
      CHARACTER(80) FNAME_RELAXSST(1 : 2)
      CHARACTER(80) FNAME_SALT(1 : 2)
      CHARACTER(80) FNAME_SFLUX(1 : 2)
      CHARACTER(80) FNAME_SSS(1 : 2)
      CHARACTER(80) FNAME_SST(1 : 2)
      CHARACTER(80) FNAME_SWDOWN(1 : 2)
      CHARACTER(80) FNAME_SWFLUX(1 : 2)
      CHARACTER(80) FNAME_TAUU(1 : 2)
      CHARACTER(80) FNAME_TAUV(1 : 2)
      CHARACTER(80) FNAME_THETA(1 : 2)
      CHARACTER(80) FNAME_TR1(1 : 2)
      CHARACTER(80) FNAME_UVEL(1 : 2)
      CHARACTER(80) FNAME_UWIND(1 : 2)
      CHARACTER(80) FNAME_VVEL(1 : 2)
      CHARACTER(80) FNAME_VWIND(1 : 2)
      CHARACTER(9) MASKNAME
      CHARACTER(9) METANAME
      INTEGER(w2f__i4) NBUFFGLOBAL
      CHARACTER(1) NCVARGRD(1 : 40)
      INTEGER(w2f__i4) NCVARINDEX(1 : 40)
      INTEGER(w2f__i4) NCVARNRMAX(1 : 40)
      INTEGER(w2f__i4) NCVARRECS(1 : 40)
      INTEGER(w2f__i4) NCVARRECSEND(1 : 40)
      INTEGER(w2f__i4) NCVARRECSTART(1 : 40)
      INTEGER(w2f__i4) NCVARXMAX(1 : 40)
      INTEGER(w2f__i4) NCVARYMAX(1 : 40)
      INTEGER(w2f__i4) NVARLENGTH
      INTEGER(w2f__i4) NVARTYPE
      INTEGER(w2f__i4) NWETCGLOBAL(1 : 15)
      INTEGER(w2f__i4) NWETCTILE(1 : 1, 1 : 1, 1 : 15)
      INTEGER(w2f__i4) NWETSGLOBAL(1 : 15)
      INTEGER(w2f__i4) NWETSTILE(1 : 1, 1 : 1, 1 : 15)
      INTEGER(w2f__i4) NWETVGLOBAL(1 : 15)
      INTEGER(w2f__i4) NWETVTILE(1 : 1, 1 : 1, 1 : 15)
      INTEGER(w2f__i4) NWETWGLOBAL(1 : 15)
      INTEGER(w2f__i4) NWETWTILE(1 : 1, 1 : 1, 1 : 15)
      CHARACTER(9) SCALNAME
      REAL(w2f__8) TMPFLD2D(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) TMPFLD3D(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WUNIT(1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) XX_AQHPERIOD
      INTEGER(w2f__i4) XX_AQHSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_AQHSTARTDATE1
      INTEGER(w2f__i4) XX_AQHSTARTDATE2
      CHARACTER(512) XX_AQH_FILE
      REAL(w2f__8) XX_ATEMPPERIOD
      INTEGER(w2f__i4) XX_ATEMPSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_ATEMPSTARTDATE1
      INTEGER(w2f__i4) XX_ATEMPSTARTDATE2
      CHARACTER(512) XX_ATEMP_FILE
      CHARACTER(512) XX_BOTTOMDRAG_FILE
      CHARACTER(512) XX_DIFFKR_FILE
      CHARACTER(512) XX_EDTAUX_FILE
      CHARACTER(512) XX_EDTAUY_FILE
      CHARACTER(512) XX_EFLUXP_FILE
      CHARACTER(512) XX_EFLUXY_FILE
      CHARACTER(512) XX_ETAN_FILE
      CHARACTER(512) XX_HFACC_FILE
      REAL(w2f__8) XX_HFLUXPERIOD
      INTEGER(w2f__i4) XX_HFLUXSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_HFLUXSTARTDATE1
      INTEGER(w2f__i4) XX_HFLUXSTARTDATE2
      CHARACTER(512) XX_HFLUX_FILE
      CHARACTER(512) XX_KAPGM_FILE
      REAL(w2f__8) XX_OBCSEPERIOD
      INTEGER(w2f__i4) XX_OBCSESTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_OBCSESTARTDATE1
      INTEGER(w2f__i4) XX_OBCSESTARTDATE2
      CHARACTER(512) XX_OBCSE_FILE
      REAL(w2f__8) XX_OBCSNPERIOD
      INTEGER(w2f__i4) XX_OBCSNSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_OBCSNSTARTDATE1
      INTEGER(w2f__i4) XX_OBCSNSTARTDATE2
      CHARACTER(512) XX_OBCSN_FILE
      REAL(w2f__8) XX_OBCSSPERIOD
      INTEGER(w2f__i4) XX_OBCSSSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_OBCSSSTARTDATE1
      INTEGER(w2f__i4) XX_OBCSSSTARTDATE2
      CHARACTER(512) XX_OBCSS_FILE
      REAL(w2f__8) XX_OBCSWPERIOD
      INTEGER(w2f__i4) XX_OBCSWSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_OBCSWSTARTDATE1
      INTEGER(w2f__i4) XX_OBCSWSTARTDATE2
      CHARACTER(512) XX_OBCSW_FILE
      REAL(w2f__8) XX_PRECIPPERIOD
      INTEGER(w2f__i4) XX_PRECIPSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_PRECIPSTARTDATE1
      INTEGER(w2f__i4) XX_PRECIPSTARTDATE2
      CHARACTER(512) XX_PRECIP_FILE
      CHARACTER(512) XX_RELAXSSS_FILE
      CHARACTER(512) XX_RELAXSST_FILE
      CHARACTER(512) XX_SALT_FILE
      CHARACTER(512) XX_SALT_INI_FIN_FILE
      REAL(w2f__8) XX_SFLUXPERIOD
      INTEGER(w2f__i4) XX_SFLUXSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_SFLUXSTARTDATE1
      INTEGER(w2f__i4) XX_SFLUXSTARTDATE2
      CHARACTER(512) XX_SFLUX_FILE
      CHARACTER(512) XX_SSS_FILE
      CHARACTER(512) XX_SST_FILE
      REAL(w2f__8) XX_SWDOWNPERIOD
      INTEGER(w2f__i4) XX_SWDOWNSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_SWDOWNSTARTDATE1
      INTEGER(w2f__i4) XX_SWDOWNSTARTDATE2
      CHARACTER(512) XX_SWDOWN_FILE
      REAL(w2f__8) XX_SWFLUXPERIOD
      INTEGER(w2f__i4) XX_SWFLUXSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_SWFLUXSTARTDATE1
      INTEGER(w2f__i4) XX_SWFLUXSTARTDATE2
      CHARACTER(512) XX_SWFLUX_FILE
      REAL(w2f__8) XX_TAUUPERIOD
      INTEGER(w2f__i4) XX_TAUUSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_TAUUSTARTDATE1
      INTEGER(w2f__i4) XX_TAUUSTARTDATE2
      CHARACTER(512) XX_TAUU_FILE
      REAL(w2f__8) XX_TAUVPERIOD
      INTEGER(w2f__i4) XX_TAUVSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_TAUVSTARTDATE1
      INTEGER(w2f__i4) XX_TAUVSTARTDATE2
      CHARACTER(512) XX_TAUV_FILE
      CHARACTER(512) XX_THETA_FILE
      CHARACTER(512) XX_THETA_INI_FIN_FILE
      CHARACTER(512) XX_TR1_FILE
      CHARACTER(512) XX_UVEL_FILE
      REAL(w2f__8) XX_UWINDPERIOD
      INTEGER(w2f__i4) XX_UWINDSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_UWINDSTARTDATE1
      INTEGER(w2f__i4) XX_UWINDSTARTDATE2
      CHARACTER(512) XX_UWIND_FILE
      CHARACTER(512) XX_VVEL_FILE
      REAL(w2f__8) XX_VWINDPERIOD
      INTEGER(w2f__i4) XX_VWINDSTARTDATE(1 : 4)
      INTEGER(w2f__i4) XX_VWINDSTARTDATE1
      INTEGER(w2f__i4) XX_VWINDSTARTDATE2
      CHARACTER(512) XX_VWIND_FILE
      CHARACTER(2) YADMARK
      CHARACTER(2) YADPREFIX
      CHARACTER(10) YCTRLID
      CHARACTER(4) YCTRLPOSPACK
      CHARACTER(4) YCTRLPOSUNPACK
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) CTRLPREC
      PARAMETER ( CTRLPREC = 64)
      INTEGER(w2f__i4) MAXCVARS
      PARAMETER ( MAXCVARS = 40)
C
C     **** Statements ****
C
      END MODULE

      MODULE ctrl_weights_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) WSALT(1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WTHETA(1 : 15, 1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE dfile_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Statements ****
C
      END MODULE

      MODULE dynvars_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) DIFFKR(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) ETAH(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) ETAN(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) GS(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GSNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GT(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GTNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GU(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GUNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GV(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GVNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) IVDCONVCOUNT(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) PHIHYDLOW(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SALT(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) THETA(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) TOTPHIHYD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) UVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE eeio_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Statements ****
C
      END MODULE

      MODULE eesupport_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      LOGICAL(w2f__i4) ALLMYEDGESARESHAREDMEMORY(1 : 32)
      CHARACTER(10) COMMNAME(1 : 4)
      INTEGER(w2f__i4) MYPID
      CHARACTER(128) MYPROCESSSTR
      LOGICAL(w2f__i4) NOTUSINGXPERIODICITY
      LOGICAL(w2f__i4) NOTUSINGYPERIODICITY
      INTEGER(w2f__i4) NPROCS
      INTEGER(w2f__i4) PIDE
      INTEGER(w2f__i4) PIDN
      INTEGER(w2f__i4) PIDS
      INTEGER(w2f__i4) PIDW
      LOGICAL(w2f__i4) PRINTMAPINCLUDESZEROS
      LOGICAL(w2f__i4) THERROR(1 : 32)
      LOGICAL(w2f__i4) THREADISCOMPLETE(1 : 32)
      LOGICAL(w2f__i4) THREADISRUNNING(1 : 32)
      INTEGER(w2f__i4) TILEBIE(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEBIN(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEBIS(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEBIW(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEBJE(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEBJN(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEBJS(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEBJW(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILECOMMMODEE(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILECOMMMODEN(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILECOMMMODES(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILECOMMMODEW(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILENO(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILENOE(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILENON(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILENOS(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILENOW(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEPIDE(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEPIDN(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEPIDS(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILEPIDW(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILETAGRECVE(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILETAGRECVN(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILETAGRECVS(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILETAGRECVW(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILETAGSENDE(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILETAGSENDN(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILETAGSENDS(1 : 1, 1 : 1)
      INTEGER(w2f__i4) TILETAGSENDW(1 : 1, 1 : 1)
      LOGICAL(w2f__i4) USINGMPI
      LOGICAL(w2f__i4) USINGSYNCMESSAGES
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) COMM_GET
      PARAMETER ( COMM_GET = 4)
      INTEGER(w2f__i4) COMM_MSG
      PARAMETER ( COMM_MSG = 2)
      INTEGER(w2f__i4) COMM_NONE
      PARAMETER ( COMM_NONE = 1)
      INTEGER(w2f__i4) COMM_PUT
      PARAMETER ( COMM_PUT = 3)
      CHARACTER(14) ERROR_HEADER
      PARAMETER ( ERROR_HEADER = " *** ERROR ***")
      INTEGER(w2f__i4) MAX_NUM_COMM_MODES
      PARAMETER ( MAX_NUM_COMM_MODES = 4)
      INTEGER(w2f__i4) NULL_TILE
      PARAMETER ( NULL_TILE = -1)
      CHARACTER(7) PROCESS_HEADER
      PARAMETER ( PROCESS_HEADER = "PID.TID")
C
C     **** Statements ****
C
      END MODULE

      MODULE eos_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) EOSC(1 : 9, 1 : 16)
      REAL(w2f__8) EOSJMDCFW(1 : 6)
      REAL(w2f__8) EOSJMDCKFW(1 : 5)
      REAL(w2f__8) EOSJMDCKP(1 : 14)
      REAL(w2f__8) EOSJMDCKSW(1 : 7)
      REAL(w2f__8) EOSJMDCSW(1 : 9)
      REAL(w2f__8) EOSMDJWFDEN(0 : 12)
      REAL(w2f__8) EOSMDJWFNUM(0 : 11)
      REAL(w2f__8) EOSREFS(1 : 16)
      REAL(w2f__8) EOSREFT(1 : 16)
      REAL(w2f__8) EOSSIG0(1 : 16)
      CHARACTER(6) EQUATIONOFSTATE
      REAL(w2f__8) SBETA
      REAL(w2f__8) TALPHA
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) SITOBAR
      PARAMETER ( SITOBAR = 1.000000000000000d-05)
      REAL(w2f__8) SITODBAR
      PARAMETER ( SITODBAR = 0.0001000000000000000)
C
C     **** Statements ****
C
      END MODULE

      MODULE exch_jam_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) EXCHBUF1(1 : 4320)
      REAL(w2f__8) EXCHBUF2(1 : 4320)
C
C     **** Statements ****
C
      END MODULE

      MODULE exch_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) EXCH_SPIN_LIMIT
      PARAMETER ( EXCH_SPIN_LIMIT = 100000000)
      INTEGER(w2f__i4) L_BUFFERX
      PARAMETER ( L_BUFFERX = 2208)
      INTEGER(w2f__i4) L_BUFFERY
      PARAMETER ( L_BUFFERY = 4608)
      INTEGER(w2f__i4) L_EBUFFER
      PARAMETER ( L_EBUFFER = 2208)
      INTEGER(w2f__i4) L_NBUFFER
      PARAMETER ( L_NBUFFER = 4608)
      INTEGER(w2f__i4) L_SBUFFER
      PARAMETER ( L_SBUFFER = 4608)
      INTEGER(w2f__i4) L_WBUFFER
      PARAMETER ( L_WBUFFER = 2208)
      INTEGER(w2f__i4) MAX_NR_EXCH
      PARAMETER ( MAX_NR_EXCH = 16)
      INTEGER(w2f__i4) MAX_OLX_EXCH
      PARAMETER ( MAX_OLX_EXCH = 3)
      INTEGER(w2f__i4) MAX_OLY_EXCH
      PARAMETER ( MAX_OLY_EXCH = 3)
      INTEGER(w2f__i4) NUMBER_OF_BUFFER_LEVELS
      PARAMETER ( NUMBER_OF_BUFFER_LEVELS = 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE fc_namemangle_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Statements ****
C
      END MODULE

      MODULE ffields_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) DQDT(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) EMPMR(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) EMPMR0(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) EMPMR1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) FU(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) FV(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) LAMBDASALTCLIMRELAX(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) LAMBDATHETACLIMRELAX(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) QNET(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) QNET0(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) QNET1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) QSW(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SALTFLUX(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SALTFLUX0(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SALTFLUX1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SSS(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SSS0(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SSS1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SST(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SST0(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SST1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SURFACEFORCINGS(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SURFACEFORCINGT(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SURFACEFORCINGTICE(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SURFACEFORCINGU(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SURFACEFORCINGV(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) TAUX0(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) TAUX1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) TAUY0(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) TAUY1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE gad_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      LOGICAL(w2f__i4) SALTADAMSBASHFORTH
      LOGICAL(w2f__i4) SALTMULTIDIMADVEC
      LOGICAL(w2f__i4) TEMPADAMSBASHFORTH
      LOGICAL(w2f__i4) TEMPMULTIDIMADVEC
      LOGICAL(w2f__i4) TR1_ADAMSBASHFORTH
      LOGICAL(w2f__i4) TR1_MULTIDIMADVEC
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) ENUM_CENTERED_2ND
      PARAMETER ( ENUM_CENTERED_2ND = 2)
      INTEGER(w2f__i4) ENUM_CENTERED_4TH
      PARAMETER ( ENUM_CENTERED_4TH = 4)
      INTEGER(w2f__i4) ENUM_DST3
      PARAMETER ( ENUM_DST3 = 30)
      INTEGER(w2f__i4) ENUM_DST3_FLUX_LIMIT
      PARAMETER ( ENUM_DST3_FLUX_LIMIT = 33)
      INTEGER(w2f__i4) ENUM_FLUX_LIMIT
      PARAMETER ( ENUM_FLUX_LIMIT = 77)
      INTEGER(w2f__i4) ENUM_UPWIND_3RD
      PARAMETER ( ENUM_UPWIND_3RD = 3)
      INTEGER(w2f__i4) GAD_SALINITY
      PARAMETER ( GAD_SALINITY = 2)
      INTEGER(w2f__i4) GAD_TEMPERATURE
      PARAMETER ( GAD_TEMPERATURE = 1)
      INTEGER(w2f__i4) GAD_TR1
      PARAMETER ( GAD_TR1 = 3)
      REAL(w2f__8) ONESIXTH
      PARAMETER ( ONESIXTH =    0.1666666666666667)
C
C     **** Statements ****
C
      END MODULE

      MODULE g_cost_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) G_FC
C
C     **** Statements ****
C
      END MODULE

      MODULE global_max_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      INTEGER(w2f__i4) PHIGMI(1 : 64, 1 : 32)
      REAL(w2f__8) PHIGMRL(1 : 32, 1 : 32)
      REAL(w2f__4) PHIGMRS(1 : 64, 1 : 32)
C
C     **** Statements ****
C
      END MODULE

      MODULE global_sum_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      INTEGER(w2f__i4) PHIGSI(1 : 64, 1 : 32)
      REAL(w2f__8) PHIGSRL(1 : 32, 1 : 32)
      REAL(w2f__4) PHIGSRS(1 : 64, 1 : 32)
C
C     **** Statements ****
C
      END MODULE

      MODULE grdchk_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) ADXXMEM(1 : 4000)
      INTEGER(w2f__i4) BIMEM(1 : 4000)
      INTEGER(w2f__i4) BJMEM(1 : 4000)
      REAL(w2f__8) FCPMMEM(1 : 4000)
      REAL(w2f__8) FCPPMEM(1 : 4000)
      REAL(w2f__8) FCRMEM(1 : 4000)
      REAL(w2f__8) FTLXXMEM(1 : 4000)
      REAL(w2f__8) GFDMEM(1 : 4000)
      INTEGER(w2f__i4) GRDCHKVARINDEX
      INTEGER(w2f__i4) GRDCHKWHICHPROC
      REAL(w2f__8) GRDCHK_EPS
      INTEGER(w2f__i4) ICHKMEM(1 : 4000)
      INTEGER(w2f__i4) ICOMPMEM(1 : 4000)
      INTEGER(w2f__i4) IERRMEM(1 : 4000)
      INTEGER(w2f__i4) IGLOPOS
      INTEGER(w2f__i4) ILOCMEM(1 : 4000)
      INTEGER(w2f__i4) IOBCSMEM(1 : 4000)
      INTEGER(w2f__i4) IRECMEM(1 : 4000)
      INTEGER(w2f__i4) ITESTMEM(1 : 4000)
      INTEGER(w2f__i4) JGLOPOS
      INTEGER(w2f__i4) JLOCMEM(1 : 4000)
      INTEGER(w2f__i4) KGLOPOS
      INTEGER(w2f__i4) KLOCMEM(1 : 4000)
      INTEGER(w2f__i4) MAXNCVARCOMPS
      INTEGER(w2f__i4) NBEG
      INTEGER(w2f__i4) NCVARCOMP
      INTEGER(w2f__i4) NEND
      INTEGER(w2f__i4) NSTEP
      INTEGER(w2f__i4) NWETTILE(1 : 1, 1 : 1, 1 : 15, 1 : 4)
      INTEGER(w2f__i4) OBCSGLO
      REAL(w2f__8) RATIOADMEM(1 : 4000)
      REAL(w2f__8) RATIOFTLMEM(1 : 4000)
      INTEGER(w2f__i4) RECGLO
      LOGICAL(w2f__i4) USECENTRALDIFF
      REAL(w2f__8) XXMEMPERT(1 : 4000)
      REAL(w2f__8) XXMEMREF(1 : 4000)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) MAXGRDCHECKS
      PARAMETER ( MAXGRDCHECKS = 4000)
C
C     **** Statements ****
C
      END MODULE

      MODULE grid_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) ANGLECOSC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) ANGLESINC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) COSFACU(-2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) COSFACV(-2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) DRC(1 : 15)
      REAL(w2f__8) DRF(1 : 15)
      REAL(w2f__8) DXC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) DXF(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) DXG(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) DXV(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) DYC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) DYF(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) DYG(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) DYU(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) FCORI(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) FCORICOS(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) FCORIG(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) GLOBALAREA
      REAL(w2f__8) GRAVITYSIGN
      REAL(w2f__8) HFACC(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) HFACS(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) HFACW(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) KLOWC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKC(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKH(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKS(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKW(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RA(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RAS(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RAW(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RAZ(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RC(1 : 15)
      REAL(w2f__8) RECIP_DRC(1 : 15)
      REAL(w2f__8) RECIP_DRF(1 : 15)
      REAL(w2f__8) RECIP_DXC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_DXF(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_DXG(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_DXV(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_DYC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_DYF(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_DYG(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_DYU(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_HFACC(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_HFACS(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_HFACW(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_RA(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_RAS(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_RAW(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_RAZ(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_RCOL(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RF(1 : 16)
      REAL(w2f__8) RKSIGN
      REAL(w2f__8) RO_SURF(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) R_LOW(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SAFAC(1 : 15)
      REAL(w2f__8) SQCOSFACU(-2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) SQCOSFACV(-2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) TANPHIATU(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) TANPHIATV(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) XC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) XC0
      REAL(w2f__8) XG(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) YC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) YC0
      REAL(w2f__8) YG(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE gw_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Statements ****
C
      END MODULE

      MODULE mpi_info_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Statements ****
C
      END MODULE

      MODULE optim_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      CHARACTER(3) COPT
      REAL(w2f__8) EPS
      REAL(w2f__8) EPSF
      REAL(w2f__8) EPSG
      REAL(w2f__8) EPSX
      REAL(w2f__8) FMIN
      INTEGER(w2f__i4) IPRINT
      INTEGER(w2f__i4) NFUNC
      LOGICAL(w2f__i4) NONDIMCONTROL
      INTEGER(w2f__i4) NUMITER
      INTEGER(w2f__i4) NUPDATE
      INTEGER(w2f__i4) NVARS
      INTEGER(w2f__i4) OPTIMCYCLE
C
C     **** Local Variables and Functions ****
C
      CHARACTER(5) LSOPTVERSION
      PARAMETER ( LSOPTVERSION = "2.1.0")
      CHARACTER(5) OFFLINEVERSION
      PARAMETER ( OFFLINEVERSION = "0.1.1")
C
C     **** Statements ****
C
      END MODULE

      MODULE solve_for_pressure3d_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Statements ****
C
      END MODULE

      MODULE solve_for_pressure_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) CG2D_B(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) CG2D_X(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE surface_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      REAL(w2f__8) BO_SURF(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) KSURFC(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) KSURFS(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) KSURFW(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) PHI0SURF(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) RECIP_BO(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) TOPOZ(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
C
C     **** Statements ****
C
      END MODULE

      MODULE tamc_keys_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      INTEGER(w2f__i4) IKEY
      INTEGER(w2f__i4) KEY
C
C     **** Statements ****
C
      END MODULE

      MODULE tamc_mod
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
      SAVE
C
C     **** Global Variables & Derived Type Definitions ****
C
      INTEGER(w2f__i4) ACT0
      INTEGER(w2f__i4) ACT1
      INTEGER(w2f__i4) ACT2
      INTEGER(w2f__i4) ACT3
      INTEGER(w2f__i4) ACT4
      INTEGER(w2f__i4) IDYNKEY
      INTEGER(w2f__i4) IGADKEY
      INTEGER(w2f__i4) IGMKEY
      INTEGER(w2f__i4) IIKEY
      INTEGER(w2f__i4) IKEY_DAILY_1
      INTEGER(w2f__i4) IKEY_DAILY_2
      INTEGER(w2f__i4) IKEY_DYNAMICS
      INTEGER(w2f__i4) IKEY_YEARLY
      INTEGER(w2f__i4) IKPPKEY
      INTEGER(w2f__i4) ILOOP_DAILY
      INTEGER(w2f__i4) IPTRKEY
      INTEGER(w2f__i4) ITDKEY
      INTEGER(w2f__i4) KKEY
      INTEGER(w2f__i4) MAX0
      INTEGER(w2f__i4) MAX1
      INTEGER(w2f__i4) MAX2
      INTEGER(w2f__i4) MAX3
      INTEGER(w2f__i4) PASSKEY
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) ISBYTE
      PARAMETER ( ISBYTE = 8)
      INTEGER(w2f__i4) MAXCUBE
      PARAMETER ( MAXCUBE = 1)
      INTEGER(w2f__i4) MAXIMPL
      PARAMETER ( MAXIMPL = 6)
      INTEGER(w2f__i4) MAXPASS
      PARAMETER ( MAXPASS = 2)
      INTEGER(w2f__i4) NCHECK_CHKPT
      PARAMETER ( NCHECK_CHKPT = 6)
      INTEGER(w2f__i4) NCHKLEV_1
      PARAMETER ( NCHKLEV_1 = 2)
      INTEGER(w2f__i4) NCHKLEV_2
      PARAMETER ( NCHKLEV_2 = 240)
      INTEGER(w2f__i4) NCHKLEV_3
      PARAMETER ( NCHKLEV_3 = 60)
      INTEGER(w2f__i4) NDAYS_CHKPT
      PARAMETER ( NDAYS_CHKPT = 31)
      INTEGER(w2f__i4) NGEOM_CHKPT
      PARAMETER ( NGEOM_CHKPT = 15)
      INTEGER(w2f__i4) NMONTHS_CHKPT
      PARAMETER ( NMONTHS_CHKPT = 12)
      INTEGER(w2f__i4) NTHREADS_CHKPT
      PARAMETER ( NTHREADS_CHKPT = 1)
      INTEGER(w2f__i4) NYEARS_CHKPT
      PARAMETER ( NYEARS_CHKPT = 1)
C
C     **** Statements ****
C
      END MODULE

      SUBROUTINE cd_code_scheme(BI, BJ, K, DPHIHYDX, DPHIHYDY, GUFLD,
     >  GVFLD, GUCOR, GVCOR, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use cd_code_vars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) DPHIHYDX(-2 : 93, -2 : 43)
      REAL(w2f__8) DPHIHYDY(-2 : 93, -2 : 43)
      REAL(w2f__8) GUFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) GVFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) GUCOR(-2 : 93, -2 : 43)
      REAL(w2f__8) GVCOR(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) AB05
      REAL(w2f__8) AB15
      REAL(w2f__8) AF(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      REAL(w2f__8) PF(-2 : 93, -2 : 43)
      REAL(w2f__8) PHXFAC
      REAL(w2f__8) PHYFAC
      REAL(w2f__8) VF(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
      INTEGER(w2f__i4) doloop_ub11
      INTEGER(w2f__i4) doloop_ub12
      INTEGER(w2f__i4) doloop_ub13
      INTEGER(w2f__i4) doloop_ub14
C
C     **** Statements ****
C
      IMIN = -1
      IMAX = 92
      JMIN = -1
      JMAX = 42
      AB15 = ABEPS + 1.5D00
      AB05 = (-5.0D-01) - ABEPS
      IF(STAGGERTIMESTEP) THEN
        PHXFAC = PFFACMOM
        PHYFAC = PFFACMOM
      ELSE
        PHXFAC = 0.0D00
        PHYFAC = 0.0D00
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          PF(I, J) = (AB05 *(ETANM1(I, J, BI, BJ) * BO_SURF(I, J, BI,
     >  BJ)) + AB15 *(ETAN(I, J, BI, BJ) * BO_SURF(I, J, BI, BJ)))
        END DO
      END DO
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          AF(I, J) = (MASKS(I, J, K, BI, BJ) *(GVFLD(I, J) -(DPHIHYDY(I
     > , J) * PHYFAC + RECIP_DYC(I, J, BI, BJ) *(PF(I, J) - PF(I, J + (
     > -1))))))
        END DO
      END DO
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          VF(I, J) = (MASKW(I, J, K, BI, BJ) *(AF(I + (-1), J + 1) + AF
     > (I + (-1), J) + AF(I, J) + AF(I, J + 1)) * 2.5D-01 - UVEL(I, J,
     >  K, BI, BJ) *(FCORI(I, J, BI, BJ) + FCORI(I + (-1), J, BI, BJ))
     >  * 5.0D-01)
        END DO
      END DO
      doloop_ub1 = JMAX
      DO J = JMIN, doloop_ub1, 1
        doloop_ub2 = IMAX
        DO I = IMIN, doloop_ub2, 1
          VVELD(I, J, K, BI, BJ) = (VVELD(I, J, K, BI, BJ) + VF(I, J) *
     >  DELTATMOM)
        END DO
      END DO
      doloop_ub3 = JMAX
      DO J = JMIN, doloop_ub3, 1
        doloop_ub4 = IMAX
        DO I = IMIN, doloop_ub4, 1
          VVELD(I, J, K, BI, BJ) = (MASKW(I, J, K, BI, BJ) *(VVELD(I, J
     > , K, BI, BJ) * RCD +(AB05 *(VNM1(I + (-1), J + 1, K, BI, BJ) +
     >  VNM1(I + (-1), J, K, BI, BJ) + VNM1(I, J, K, BI, BJ) + VNM1(I,
     >  J + 1, K, BI, BJ)) * 2.5D-01 + AB15 *(VVEL(I + (-1), J + 1, K,
     >  BI, BJ) + VVEL(I + (-1), J, K, BI, BJ) + VVEL(I, J, K, BI, BJ)
     >  + VVEL(I, J + 1, K, BI, BJ)) * 2.5D-01) *(1.0D00 - RCD)))
        END DO
      END DO
      doloop_ub5 = JMAX
      DO J = JMIN, doloop_ub5, 1
        doloop_ub6 = IMAX
        DO I = IMIN, doloop_ub6, 1
          GUCOR(I, J) = (CFFACMOM * VVELD(I, J, K, BI, BJ) *(FCORI(I, J
     > , BI, BJ) + FCORI(I + (-1), J, BI, BJ)) * 5.0D-01)
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -1, 93, 1
          AF(I, J) = (MASKW(I, J, K, BI, BJ) *(GUFLD(I, J) -(DPHIHYDX(I
     > , J) * PHXFAC + RECIP_DXC(I, J, BI, BJ) *(PF(I, J) - PF(I + (-1)
     > , J)))))
        END DO
      END DO
      doloop_ub7 = JMAX
      DO J = JMIN, doloop_ub7, 1
        doloop_ub8 = IMAX
        DO I = IMIN, doloop_ub8, 1
          VF(I, J) = (VVEL(I, J, K, BI, BJ) *(FCORI(I, J, BI, BJ) +
     >  FCORI(I, J + (-1), BI, BJ)) * 5.0D-01 + MASKS(I, J, K, BI, BJ)
     >  *(AF(I + 1, J + (-1)) + AF(I + 1, J) + AF(I, J) + AF(I, J + (-1
     > ))) * 2.5D-01)
        END DO
      END DO
      doloop_ub9 = JMAX
      DO J = JMIN, doloop_ub9, 1
        doloop_ub10 = IMAX
        DO I = IMIN, doloop_ub10, 1
          UVELD(I, J, K, BI, BJ) = (UVELD(I, J, K, BI, BJ) + VF(I, J) *
     >  DELTATMOM)
        END DO
      END DO
      doloop_ub11 = JMAX
      DO J = JMIN, doloop_ub11, 1
        doloop_ub12 = IMAX
        DO I = IMIN, doloop_ub12, 1
          UVELD(I, J, K, BI, BJ) = (MASKS(I, J, K, BI, BJ) *(UVELD(I, J
     > , K, BI, BJ) * RCD +(AB05 *(UNM1(I + 1, J + (-1), K, BI, BJ) +
     >  UNM1(I, J + (-1), K, BI, BJ) + UNM1(I, J, K, BI, BJ) + UNM1(I +
     >  1, J, K, BI, BJ)) * 2.5D-01 + AB15 *(UVEL(I + 1, J + (-1), K,
     >  BI, BJ) + UVEL(I, J + (-1), K, BI, BJ) + UVEL(I, J, K, BI, BJ)
     >  + UVEL(I + 1, J, K, BI, BJ)) * 2.5D-01) *(1.0D00 - RCD)))
        END DO
      END DO
      doloop_ub13 = JMAX
      DO J = JMIN, doloop_ub13, 1
        doloop_ub14 = IMAX
        DO I = IMIN, doloop_ub14, 1
          GVCOR(I, J) = (-(CFFACMOM * UVELD(I, J, K, BI, BJ) *(FCORI(I,
     >  J, BI, BJ) + FCORI(I, J + (-1), BI, BJ)) * 5.0D-01))
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          UNM1(I, J, K, BI, BJ) = UVEL(I, J, K, BI, BJ)
          VNM1(I, J, K, BI, BJ) = VVEL(I, J, K, BI, BJ)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE cd_code_ini_vars(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use cd_code_vars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL cd_code_read_checkpoint
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                UNM1(I, J, K, BI, BJ) = 0.0D00
                VNM1(I, J, K, BI, BJ) = 0.0D00
                UVELD(I, J, K, BI, BJ) = 0.0D00
                VVELD(I, J, K, BI, BJ) = 0.0D00
              END DO
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ETANM1(I, J, BI, BJ) = 0.0D00
            END DO
          END DO
        END DO
      END DO
      IF(NITER0 .ne. 0) THEN
        CALL cd_code_read_checkpoint(NITER0, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_accumulate_mean(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) ITHI
      INTEGER(w2f__i4) ITLO
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JTHI
      INTEGER(w2f__i4) JTLO
      INTEGER(w2f__i4) K
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      JTLO = MYBYLO(MYTHID)
      JTHI = MYBYHI(MYTHID)
      ITLO = MYBXLO(MYTHID)
      ITHI = MYBXHI(MYTHID)
      doloop_ub = JTHI
      DO BJ = JTLO, doloop_ub, 1
        doloop_ub0 = ITHI
        DO BI = ITLO, doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                CMEANTHETA(I, J, K, BI, BJ) = (CMEANTHETA(I, J, K, BI,
     >  BJ) + DELTATCLOCK *(THETA(I, J, K, BI, BJ) / LASTINTERVAL))
                CMEANUVEL(I, J, K, BI, BJ) = (CMEANUVEL(I, J, K, BI, BJ
     > ) + DELTATCLOCK *(UVEL(I, J, K, BI, BJ) / LASTINTERVAL))
                CMEANVVEL(I, J, K, BI, BJ) = (CMEANVVEL(I, J, K, BI, BJ
     > ) + DELTATCLOCK *(VVEL(I, J, K, BI, BJ) / LASTINTERVAL))
              END DO
            END DO
          END DO
        END DO
      END DO
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_final(MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use params_mod
      use cost_mod
      use ctrl_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL cost_atlantic_heat
      EXTERNAL global_sum_r8
      INTEGER(w2f__i4) ITHI
      INTEGER(w2f__i4) ITLO
      INTEGER(w2f__i4) JTHI
      INTEGER(w2f__i4) JTLO
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      JTLO = MYBYLO(MYTHID)
      JTHI = MYBYHI(MYTHID)
      ITLO = MYBXLO(MYTHID)
      ITHI = MYBXHI(MYTHID)
      CALL cost_atlantic_heat(MYTHID)
      doloop_ub = JTHI
      DO BJ = JTLO, doloop_ub, 1
        doloop_ub0 = ITHI
        DO BI = ITLO, doloop_ub0, 1
          WRITE(STANDARDMESSAGEUNIT, '(A,D22.15)')
     >  ' --> objf_test(bi,bj)   = ', OBJF_TEST(BI, BJ)
          WRITE(STANDARDMESSAGEUNIT, '(A,D22.15)')
     >  ' --> objf_tracer(bi,bj) = ', OBJF_TRACER(BI, BJ)
          WRITE(STANDARDMESSAGEUNIT, '(A,D22.15)')
     >  ' --> objf_atl(bi,bj)    = ', OBJF_ATL(BI, BJ)
          FC = FC + OBJF_TEST(BI, BJ) * MULT_TEST + OBJF_TRACER(BI, BJ)
     >  * MULT_TRACER + OBJF_ATL(BI, BJ) * MULT_ATL
        END DO
      END DO
      WRITE(STANDARDMESSAGEUNIT, '(A,D22.15)') '  local fc = ', FC
      CALL global_sum_r8(FC, MYTHID)
      WRITE(STANDARDMESSAGEUNIT, '(A,D22.15)') ' global fc = ', FC
      TAVEFREQ = 0.0D00
      DUMPFREQ = 0.0D00
      PCHKPTFREQ = 0.0D00
      MONITORFREQ = 0.0D00
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_init_varia(MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL barrier
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) ITHI
      INTEGER(w2f__i4) ITLO
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JTHI
      INTEGER(w2f__i4) JTLO
      INTEGER(w2f__i4) K
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      JTLO = MYBYLO(MYTHID)
      JTHI = MYBYHI(MYTHID)
      ITLO = MYBXLO(MYTHID)
      ITHI = MYBXHI(MYTHID)
      doloop_ub = JTHI
      DO BJ = JTLO, doloop_ub, 1
        doloop_ub0 = ITHI
        DO BI = ITLO, doloop_ub0, 1
          OBJF_ATL(BI, BJ) = 0.0D00
          OBJF_TEST(BI, BJ) = 0.0D00
          OBJF_TRACER(BI, BJ) = 0.0D00
          DO K = 1, 15, 1
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                CMEANTHETA(I, J, K, BI, BJ) = 0.0D00
                CMEANUVEL(I, J, K, BI, BJ) = 0.0D00
                CMEANVVEL(I, J, K, BI, BJ) = 0.0D00
              END DO
            END DO
          END DO
        END DO
      END DO
      IF(MYTHID .eq. 1) THEN
        FC = 0.0D00
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_tile(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL cost_accumulate_mean
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          IF(MYTIME .GT.(ENDTIME - LASTINTERVAL)) THEN
            CALL cost_accumulate_mean(MYTHID)
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_test(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_tracer(BI, BJ, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_atlantic_heat(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) COUNTT(1 : 15)
      REAL(w2f__8) COUNTV(1 : 15)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IG
      INTEGER(w2f__i4) ISEC
      PARAMETER ( ISEC = 59)
      INTEGER(w2f__i4) ISECBEG
      PARAMETER ( ISECBEG = 69)
      INTEGER(w2f__i4) ISECEND
      PARAMETER ( ISECEND = 87)
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JG
      INTEGER(w2f__i4) JSEC
      PARAMETER ( JSEC = 28)
      INTEGER(w2f__i4) JSECBEG
      PARAMETER ( JSECBEG = 10)
      INTEGER(w2f__i4) JSECEND
      PARAMETER ( JSECEND = 27)
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KMAXDEPTH
      PARAMETER ( KMAXDEPTH = 5)
      REAL(w2f__8) LOCFC
      REAL(w2f__8) PETAWATT
      PARAMETER ( PETAWATT =     999999986991104.0)
      REAL(w2f__8) SUM
      REAL(w2f__8) THETA_BAR(1 : 15)
      REAL(w2f__8) VVEL_BAR(1 : 15)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          LOCFC = 0.0D00
          SUM = 0.0D00
          DO J = 1, 40, 1
            JG = J + MYYGLOBALLO + BJ * 40 +(-41)
            IF(JG .eq. 28) THEN
              DO K = 1, 15, 1
                VVEL_BAR(K) = 0.0
                THETA_BAR(K) = 0.0
                COUNTT(K) = 0.0
                COUNTV(K) = 0.0
                DO I = 1, 90, 1
                  IG = I + MYXGLOBALLO + BI * 90 +(-91)
                  IF((IG .GE. 69) .AND.(IG .LE. 87)) THEN
                    VVEL_BAR(K) = (VVEL_BAR(K) + MASKC(I, J + (-1), K,
     >  BI, BJ) * MASKC(I, J, K, BI, BJ) * CMEANVVEL(I, J, K, BI, BJ) *
     >  MASKS(I, J, K, BI, BJ))
                    THETA_BAR(K) = (THETA_BAR(K) + MASKC(I, J + (-1), K
     > , BI, BJ) * MASKC(I, J, K, BI, BJ) * DXG(I, J, BI, BJ) * MASKS(I
     > , J, K, BI, BJ) *(CMEANTHETA(I, J, K, BI, BJ) + CMEANTHETA(I, J
     >  + (-1), K, BI, BJ)) * 5.0D-01)
                    COUNTT(K) = (COUNTT(K) + MASKC(I, J + (-1), K, BI,
     >  BJ) * MASKC(I, J, K, BI, BJ) * MASKS(I, J, K, BI, BJ))
                    COUNTV(K) = (COUNTV(K) + MASKC(I, J + (-1), K, BI,
     >  BJ) * MASKC(I, J, K, BI, BJ) * MASKS(I, J, K, BI, BJ))
                  ENDIF
                END DO
              END DO
              DO K = 1, 15, 1
                IF((COUNTV(K) .ne. 0.0D00) .AND.((K .LE. 5) .AND.(
     > COUNTT(K) .ne. 0.0D00))) THEN
                  SUM = SUM +((DRF(K) * THETA_BAR(K) * VVEL_BAR(K)) /(
     > COUNTT(K) * COUNTV(K)))
                ENDIF
              END DO
            ENDIF
          END DO
          OBJF_ATL(BI, BJ) = ((RHOCONST * SUM * HEATCAPACITY_CP) /
     >  9.99999986991104D+14)
        END DO
      END DO
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_vector(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      END SUBROUTINE

      SUBROUTINE cost_state_final(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_get_gen(XX_GEN_FILE, XX_GENSTARTDATE,
     >  XX_GENPERIOD, GENMASK, GENFLD, XX_GEN0, XX_GEN1, XX_GEN_DUMMY,
     >  MYTIME, MYITER, MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use params_mod
      use grid_mod
      use ctrl_mod
      use ctrl_dummy_mod
      use optim_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(512) XX_GEN_FILE
      INTEGER(w2f__i4) XX_GENSTARTDATE(1 : 4)
      REAL(w2f__8) XX_GENPERIOD
      REAL(w2f__8) GENMASK(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GENFLD(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) XX_GEN0(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) XX_GEN1(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) XX_GEN_DUMMY
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_get_gen_rec(XX_GENSTARTDATE, XX_GENPERIOD, FAC,
     >  FIRST, CHANGED, COUNT0, COUNT1, MYTIME, MYITER, MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use ctrl_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) XX_GENSTARTDATE(1 : 4)
      REAL(w2f__8) XX_GENPERIOD
      REAL(w2f__8) FAC
      LOGICAL(w2f__i4) FIRST
      LOGICAL(w2f__i4) CHANGED
      INTEGER(w2f__i4) COUNT0
      INTEGER(w2f__i4) COUNT1
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_init_variables(MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use params_mod
      use grid_mod
      use ctrl_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) ITHI
      INTEGER(w2f__i4) ITLO
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JTHI
      INTEGER(w2f__i4) JTLO
C
C     **** Statements ****
C
      JTLO = MYBYLO(MYTHID)
      JTHI = MYBYHI(MYTHID)
      ITLO = MYBXLO(MYTHID)
      ITHI = MYBXHI(MYTHID)
      JMIN = -2
      JMAX = 43
      IMIN = -2
      IMAX = 93
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_map_ini(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ffields_mod
      use ctrl_mod
      use ctrl_dummy_mod
      use optim_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL active_read_xyz_loc
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      LOGICAL(w2f__i4) DOGLOBALREAD
      LOGICAL(w2f__i4) EQUAL
      EXTERNAL exch_xyz_rl
      REAL(w2f__8) FAC
      CHARACTER(80) FNAMEGENERIC
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IL
      EXTERNAL ilnblnk
      INTEGER(w2f__i4) ilnblnk
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) ITHI
      INTEGER(w2f__i4) ITLO
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JTHI
      INTEGER(w2f__i4) JTLO
      INTEGER(w2f__i4) K
      LOGICAL(w2f__i4) LADINIT
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
C
C     **** Statements ****
C
      JTLO = MYBYLO(MYTHID)
      JTHI = MYBYHI(MYTHID)
      ITLO = MYBXLO(MYTHID)
      ITHI = MYBXHI(MYTHID)
      JMIN = 1
      JMAX = 40
      IMIN = 1
      IMAX = 90
      DOGLOBALREAD = .FALSE.
      LADINIT = .FALSE.
      EQUAL = .TRUE.
      IF(EQUAL) THEN
        FAC = 1.0D00
      ELSE
        FAC = 0.0D00
      ENDIF
      IL = ilnblnk(XX_THETA_FILE)
      WRITE(FNAMEGENERIC, '(2a,i10.10)') XX_THETA_FILE(1_w2f__i8 : MAX(
     > IL, 0)), '.', OPTIMCYCLE
      CALL active_read_xyz_loc(FNAMEGENERIC, TMPFLD3D, (1),
     >  DOGLOBALREAD, LADINIT, OPTIMCYCLE, MYTHID, XX_THETA_DUMMY)
      doloop_ub = JTHI
      DO BJ = JTLO, doloop_ub, 1
        doloop_ub0 = ITHI
        DO BI = ITLO, doloop_ub0, 1
          DO K = 1, 15, 1
            doloop_ub1 = JMAX
            DO J = JMIN, doloop_ub1, 1
              doloop_ub2 = IMAX
              DO I = IMIN, doloop_ub2, 1
                THETA(I, J, K, BI, BJ) = (THETA(I, J, K, BI, BJ) +
     >  TMPFLD3D(I, J, K, BI, BJ) * FAC)
                IF(THETA(I, J, K, BI, BJ) .LT.(-2.0D00)) THEN
                  THETA(I, J, K, BI, BJ) = (-2.0)
                ENDIF
              END DO
            END DO
          END DO
        END DO
      END DO
      IL = ilnblnk(XX_SALT_FILE)
      WRITE(FNAMEGENERIC, '(2a,i10.10)') XX_SALT_FILE(1_w2f__i8 : MAX(
     > IL, 0)), '.', OPTIMCYCLE
      CALL active_read_xyz_loc(FNAMEGENERIC, TMPFLD3D, (1),
     >  DOGLOBALREAD, LADINIT, OPTIMCYCLE, MYTHID, XX_SALT_DUMMY)
      doloop_ub3 = JTHI
      DO BJ = JTLO, doloop_ub3, 1
        doloop_ub4 = ITHI
        DO BI = ITLO, doloop_ub4, 1
          DO K = 1, 15, 1
            doloop_ub5 = JMAX
            DO J = JMIN, doloop_ub5, 1
              doloop_ub6 = IMAX
              DO I = IMIN, doloop_ub6, 1
                SALT(I, J, K, BI, BJ) = (SALT(I, J, K, BI, BJ) +
     >  TMPFLD3D(I, J, K, BI, BJ) * FAC)
              END DO
            END DO
          END DO
        END DO
      END DO
      IL = ilnblnk(XX_DIFFKR_FILE)
      WRITE(FNAMEGENERIC, '(2a,i10.10)') XX_DIFFKR_FILE(1_w2f__i8 : MAX
     > (IL, 0)), '.', OPTIMCYCLE
      CALL active_read_xyz_loc(FNAMEGENERIC, TMPFLD3D, (1),
     >  DOGLOBALREAD, LADINIT, OPTIMCYCLE, MYTHID, XX_DIFFKR_DUMMY)
      doloop_ub7 = JTHI
      DO BJ = JTLO, doloop_ub7, 1
        doloop_ub8 = ITHI
        DO BI = ITLO, doloop_ub8, 1
          DO K = 1, 15, 1
            doloop_ub9 = JMAX
            DO J = JMIN, doloop_ub9, 1
              doloop_ub10 = IMAX
              DO I = IMIN, doloop_ub10, 1
                DIFFKR(I, J, K, BI, BJ) = (TMPFLD3D(I, J, K, BI, BJ) +
     >  DIFFKR(I, J, K, BI, BJ))
              END DO
            END DO
          END DO
        END DO
      END DO
      CALL exch_xyz_rl(THETA, MYTHID)
      CALL exch_xyz_rl(SALT, MYTHID)
      CALL exch_xyz_rl(DIFFKR, MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_map_ini_ecco(MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ffields_mod
      use ctrl_mod
      use ctrl_dummy_mod
      use optim_mod
      use tamc_mod
      use tamc_keys_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_map_forcing(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use ffields_mod
      use dynvars_mod
      use grid_mod
      use ctrl_mod
      use ctrl_dummy_mod
      use optim_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL active_read_xy_loc
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      LOGICAL(w2f__i4) DOGLOBALREAD
      EXTERNAL exch_uv_xy_rs
      EXTERNAL exch_xy_rl
      CHARACTER(80) FNAMEHFLUX
      CHARACTER(80) FNAMESFLUX
      CHARACTER(80) FNAMETAUU
      CHARACTER(80) FNAMETAUV
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IL
      EXTERNAL ilnblnk
      INTEGER(w2f__i4) ilnblnk
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) ITHI
      INTEGER(w2f__i4) ITLO
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JTHI
      INTEGER(w2f__i4) JTLO
      LOGICAL(w2f__i4) LADINIT
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
      INTEGER(w2f__i4) doloop_ub11
      INTEGER(w2f__i4) doloop_ub12
      INTEGER(w2f__i4) doloop_ub13
      INTEGER(w2f__i4) doloop_ub14
C
C     **** Statements ****
C
      JTLO = MYBYLO(MYTHID)
      JTHI = MYBYHI(MYTHID)
      ITLO = MYBXLO(MYTHID)
      ITHI = MYBXHI(MYTHID)
      JMIN = 1
      JMAX = 40
      IMIN = 1
      IMAX = 90
      DOGLOBALREAD = .FALSE.
      LADINIT = .FALSE.
      IL = ilnblnk(XX_TAUU_FILE)
      WRITE(FNAMETAUU, '(2a,i10.10)') XX_TAUU_FILE(1_w2f__i8 : MAX(IL,
     >  0)), '.', OPTIMCYCLE
      CALL active_read_xy_loc(FNAMETAUU, TMPFLD2D, (1), DOGLOBALREAD,
     >  LADINIT, OPTIMCYCLE, MYTHID, XX_TAUU_DUMMY)
      doloop_ub = JTHI
      DO BJ = JTLO, doloop_ub, 1
        doloop_ub0 = ITHI
        DO BI = ITLO, doloop_ub0, 1
          doloop_ub1 = JMAX
          DO J = JMIN, doloop_ub1, 1
            doloop_ub2 = IMAX
            DO I = IMIN, doloop_ub2, 1
              FU(I, J, BI, BJ) = (TMPFLD2D(I, J, BI, BJ) + FU(I, J, BI,
     >  BJ))
            END DO
          END DO
        END DO
      END DO
      IL = ilnblnk(XX_TAUV_FILE)
      WRITE(FNAMETAUV, '(2a,i10.10)') XX_TAUV_FILE(1_w2f__i8 : MAX(IL,
     >  0)), '.', OPTIMCYCLE
      CALL active_read_xy_loc(FNAMETAUV, TMPFLD2D, (1), DOGLOBALREAD,
     >  LADINIT, OPTIMCYCLE, MYTHID, XX_TAUV_DUMMY)
      doloop_ub3 = JTHI
      DO BJ = JTLO, doloop_ub3, 1
        doloop_ub4 = ITHI
        DO BI = ITLO, doloop_ub4, 1
          doloop_ub5 = JMAX
          DO J = JMIN, doloop_ub5, 1
            doloop_ub6 = IMAX
            DO I = IMIN, doloop_ub6, 1
              FV(I, J, BI, BJ) = (TMPFLD2D(I, J, BI, BJ) + FV(I, J, BI,
     >  BJ))
            END DO
          END DO
        END DO
      END DO
      IL = ilnblnk(XX_SFLUX_FILE)
      WRITE(FNAMESFLUX, '(2a,i10.10)') XX_SFLUX_FILE(1_w2f__i8 : MAX(IL
     > , 0)), '.', OPTIMCYCLE
      CALL active_read_xy_loc(FNAMESFLUX, TMPFLD2D, (1), DOGLOBALREAD,
     >  LADINIT, OPTIMCYCLE, MYTHID, XX_SFLUX_DUMMY)
      doloop_ub7 = JTHI
      DO BJ = JTLO, doloop_ub7, 1
        doloop_ub8 = ITHI
        DO BI = ITLO, doloop_ub8, 1
          doloop_ub9 = JMAX
          DO J = JMIN, doloop_ub9, 1
            doloop_ub10 = IMAX
            DO I = IMIN, doloop_ub10, 1
              EMPMR(I, J, BI, BJ) = (TMPFLD2D(I, J, BI, BJ) + EMPMR(I,
     >  J, BI, BJ))
            END DO
          END DO
        END DO
      END DO
      IL = ilnblnk(XX_HFLUX_FILE)
      WRITE(FNAMEHFLUX, '(2a,i10.10)') XX_HFLUX_FILE(1_w2f__i8 : MAX(IL
     > , 0)), '.', OPTIMCYCLE
      CALL active_read_xy_loc(FNAMEHFLUX, TMPFLD2D, (1), DOGLOBALREAD,
     >  LADINIT, OPTIMCYCLE, MYTHID, XX_HFLUX_DUMMY)
      doloop_ub11 = JTHI
      DO BJ = JTLO, doloop_ub11, 1
        doloop_ub12 = ITHI
        DO BI = ITLO, doloop_ub12, 1
          doloop_ub13 = JMAX
          DO J = JMIN, doloop_ub13, 1
            doloop_ub14 = IMAX
            DO I = IMIN, doloop_ub14, 1
              QNET(I, J, BI, BJ) = (TMPFLD2D(I, J, BI, BJ) + QNET(I, J,
     >  BI, BJ))
            END DO
          END DO
        END DO
      END DO
      CALL exch_uv_xy_rs(FU, FV, (.TRUE.), MYTHID)
      CALL exch_xy_rl(EMPMR, MYTHID)
      CALL exch_xy_rl(QNET, MYTHID)
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_smooth(FLD, MASK)
      use w2f__types
      use size_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) FLD(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) MASK(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) FLD_TMP(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IM1
      INTEGER(w2f__i4) IMAX
      PARAMETER ( IMAX = 92)
      INTEGER(w2f__i4) IMIN
      PARAMETER ( IMIN = -1)
      INTEGER(w2f__i4) IP1
      INTEGER(w2f__i4) ITHI
      INTEGER(w2f__i4) ITLO
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JM1
      INTEGER(w2f__i4) JMAX
      PARAMETER ( JMAX = 42)
      INTEGER(w2f__i4) JMIN
      PARAMETER ( JMIN = -1)
      INTEGER(w2f__i4) JP1
      INTEGER(w2f__i4) JTHI
      INTEGER(w2f__i4) JTLO
      INTEGER(w2f__i4) K
      REAL(w2f__8) P0
      PARAMETER ( P0 =     0.000000000000000)
      REAL(w2f__8) P0625
      PARAMETER ( P0625 =   0.06250000000000000)
      REAL(w2f__8) P125
      PARAMETER ( P125 =    0.1250000000000000)
      REAL(w2f__8) P25
      PARAMETER ( P25 =    0.2500000000000000)
      REAL(w2f__8) P5
      PARAMETER ( P5 =    0.5000000000000000)
      REAL(w2f__8) TEMPVAR
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      JTLO = 1
      JTHI = 1
      ITLO = 1
      ITHI = 1
      K = 1
      doloop_ub = JTHI
      DO BJ = JTLO, doloop_ub, 1
        doloop_ub0 = ITHI
        DO BI = ITLO, doloop_ub0, 1
          DO J = -1, 42, 1
            JM1 = J +(-1)
            JP1 = J + 1
            DO I = -1, 92, 1
              IM1 = I +(-1)
              IP1 = I + 1
              TEMPVAR = MASK(I, J, K, BI, BJ) * 2.5D-01 +(MASK(I, JP1,
     >  K, BI, BJ) + MASK(I, JM1, K, BI, BJ) + MASK(IM1, J, K, BI, BJ)
     >  + MASK(IP1, J, K, BI, BJ)) * 1.25D-01 +(MASK(IP1, JP1, K, BI,
     >  BJ) + MASK(IP1, JM1, K, BI, BJ) + MASK(IM1, JM1, K, BI, BJ) +
     >  MASK(IM1, JP1, K, BI, BJ)) * 6.25D-02
              IF(TEMPVAR .GE. 2.5D-01) THEN
                FLD_TMP(I, J) = ((MASK(I, J, K, BI, BJ) * FLD(I, J, BI,
     >  BJ) * 2.5D-01 +(FLD(IM1, J, BI, BJ) * MASK(IM1, J, K, BI, BJ) +
     >  FLD(IP1, J, BI, BJ) * MASK(IP1, J, K, BI, BJ) + FLD(I, JM1, BI,
     >  BJ) * MASK(I, JM1, K, BI, BJ) + FLD(I, JP1, BI, BJ) * MASK(I,
     >  JP1, K, BI, BJ)) * 1.25D-01 +(FLD(IM1, JM1, BI, BJ) * MASK(IM1,
     >  JM1, K, BI, BJ) + FLD(IM1, JP1, BI, BJ) * MASK(IM1, JP1, K, BI,
     >  BJ) + FLD(IP1, JM1, BI, BJ) * MASK(IP1, JM1, K, BI, BJ) + FLD(
     > IP1, JP1, BI, BJ) * MASK(IP1, JP1, K, BI, BJ)) * 6.25D-02) /
     >  TEMPVAR)
              ELSE
                FLD_TMP(I, J) = FLD(I, J, BI, BJ)
              ENDIF
            END DO
          END DO
          DO J = -1, 42, 1
            DO I = -1, 92, 1
              FLD(I, J, BI, BJ) = FLD_TMP(I, J)
            END DO
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_getobcse(MYTIME, MYITER, MYTHID)
      use w2f__types
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_getobcsn(MYTIME, MYITER, MYTHID)
      use w2f__types
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_getobcss(MYTIME, MYITER, MYTHID)
      use w2f__types
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_getobcsw(MYTIME, MYITER, MYTHID)
      use w2f__types
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_obcsbal(MYTIME, MYITER, MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ctrl_mod
      use ctrl_dummy_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_init_obcs_variables(MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use params_mod
      use grid_mod
      use ctrl_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) ITHI
      INTEGER(w2f__i4) ITLO
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JTHI
      INTEGER(w2f__i4) JTLO
C
C     **** Statements ****
C
      JTLO = MYBYLO(MYTHID)
      JTHI = MYBYHI(MYTHID)
      ITLO = MYBXLO(MYTHID)
      ITHI = MYBXHI(MYTHID)
      JMIN = -2
      JMAX = 43
      IMIN = -2
      IMAX = 93
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_getrec(THEFIELD, FAC, FIRST, CHANGED, COUNT0,
     >  COUNT1, MYTIME, MYITER, MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use ctrl_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(*) THEFIELD
      REAL(w2f__8) FAC
      LOGICAL(w2f__i4) FIRST
      LOGICAL(w2f__i4) CHANGED
      INTEGER(w2f__i4) COUNT0
      INTEGER(w2f__i4) COUNT1
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__124
C
C     **** Statements ****
C
      t__124 = LEN(THEFIELD)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ctrl_volflux(OBCSNCOUNT, SUMAREA, SUMFLUX, MYTHID)
      use w2f__types
      use eeparams_mod
      use size_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ctrl_mod
      use ctrl_dummy_mod
      use optim_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) OBCSNCOUNT
      REAL(w2f__8) SUMAREA
      REAL(w2f__8) SUMFLUX
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_advection(IMPLICITADVECTION, ADVECTIONSCHEME,
     >  VERTADVECSCHEME, TRACERIDENTITY, UVEL, VVEL, WVEL, TRACER,
     >  GTRACER, BI, BJ, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use gad_mod
      use tamc_mod
      use tamc_keys_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      LOGICAL(w2f__i4) IMPLICITADVECTION
      INTEGER(w2f__i4) ADVECTIONSCHEME
      INTEGER(w2f__i4) VERTADVECSCHEME
      INTEGER(w2f__i4) TRACERIDENTITY
      REAL(w2f__8) UVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GTRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) AF(-2 : 93, -2 : 43)
      REAL(w2f__8) AFX(-2 : 93, -2 : 43)
      REAL(w2f__8) AFY(-2 : 93, -2 : 43)
      EXTERNAL calc_common_factors
      LOGICAL(w2f__i4) CALC_FLUXES_X
      LOGICAL(w2f__i4) CALC_FLUXES_Y
      EXTERNAL debug_cs_corner_uv
      LOGICAL(w2f__i4) E_EDGE
      REAL(w2f__8) FVERT(-2 : 93, -2 : 43, 1 : 2)
      EXTERNAL gad_dst3fl_adv_r
      EXTERNAL gad_dst3fl_adv_x
      EXTERNAL gad_dst3fl_adv_y
      EXTERNAL gad_dst3_adv_r
      EXTERNAL gad_dst3_adv_x
      EXTERNAL gad_dst3_adv_y
      EXTERNAL gad_fluxlimit_adv_r
      EXTERNAL gad_fluxlimit_adv_x
      EXTERNAL gad_fluxlimit_adv_y
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMAXUPD
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMINUPD
      LOGICAL(w2f__i4) INTERIORONLY
      INTEGER(w2f__i4) IPASS
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMAXUPD
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMINUPD
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KDOWN
      REAL(w2f__8) KP1MSK
      INTEGER(w2f__i4) KUP
      REAL(w2f__8) LOCALTIJ(-2 : 93, -2 : 43)
      REAL(w2f__8) LOCALTIJK(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) MASKLOCS(-2 : 93, -2 : 43)
      REAL(w2f__8) MASKLOCW(-2 : 93, -2 : 43)
      REAL(w2f__8) MASKUP(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) NCFACE
      INTEGER(w2f__i4) NIPASS
      LOGICAL(w2f__i4) N_EDGE
      LOGICAL(w2f__i4) OVERLAPONLY
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANSKP1(-2 : 93, -2 : 43)
      LOGICAL(w2f__i4) S_EDGE
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      LOGICAL(w2f__i4) W_EDGE
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
C
C     **** Statements ****
C
      ACT0 = TRACERIDENTITY +(-1)
      MAX0 = 2
      ACT1 = BI - MYBXLO(MYTHID)
      MAX1 = MYBXHI(MYTHID) - MYBXLO(MYTHID) + 1
      ACT2 = BJ - MYBYLO(MYTHID)
      MAX2 = MYBYHI(MYTHID) - MYBYLO(MYTHID) + 1
      ACT3 = MYTHID +(-1)
      MAX3 = NTX * NTY
      ACT4 = IKEY_DYNAMICS +(-1)
      IGADKEY = ACT0 + ACT1 * MAX0 + MAX1 * ACT2 * MAX0 + MAX2 * MAX1 *
     >  ACT3 * MAX0 + MAX3 * MAX2 * MAX1 * ACT4 * MAX0 + 1
      IF(TRACERIDENTITY .GT. 2) THEN
        WRITE(*, *) 'ph-pass gad_advection ', 2, TRACERIDENTITY
        STOP 'maxpass seems smaller than tracerIdentity'
        RETURN
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          XA(I, J) = 0.0D00
          YA(I, J) = 0.0D00
          UTRANS(I, J) = 0.0D00
          VTRANS(I, J) = 0.0D00
          RTRANS(I, J) = 0.0D00
          FVERT(I, J, 1) = 0.0D00
          FVERT(I, J, 2) = 0.0D00
          RTRANSKP1(I, J) = 0.0D00
        END DO
      END DO
      IF(USECUBEDSPHEREEXCHANGE) THEN
        NIPASS = 3
        IF(NIPASS .GT. 1) THEN
          STOP 'maxcube needs to be = 3'
          RETURN
        ENDIF
        NCFACE = BI
        N_EDGE = .TRUE.
        S_EDGE = .TRUE.
        E_EDGE = .TRUE.
        W_EDGE = .TRUE.
      ELSE
        NIPASS = 2
        N_EDGE = .FALSE.
        S_EDGE = .FALSE.
        E_EDGE = .FALSE.
        W_EDGE = .FALSE.
      ENDIF
      IMIN = -2
      IMAX = 93
      JMIN = -2
      JMAX = 43
      DO K = 1, 15, 1
        KKEY = K + IGADKEY * 15 +(-15)
        CALL calc_common_factors(BI, BJ, IMIN, IMAX, JMIN, JMAX, (K),
     >  XA, YA, UTRANS, VTRANS, RTRANS, MASKUP, MYTHID)
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            LOCALTIJ(I, J) = TRACER(I, J, K, BI, BJ)
            MASKLOCW(I, J) = MASKW(I, J, K, BI, BJ)
            MASKLOCS(I, J) = MASKS(I, J, K, BI, BJ)
          END DO
        END DO
        doloop_ub = NIPASS
        DO IPASS = 1, doloop_ub, 1
          PASSKEY = IPASS + K + IGADKEY * 15 +(-16)
          IF(NIPASS .GT. 2) THEN
            STOP 'GAD_ADVECTION: nipass > maxcube. check tamc.h'
            RETURN
          ENDIF
          INTERIORONLY = .FALSE.
          OVERLAPONLY = .FALSE.
          IF(USECUBEDSPHEREEXCHANGE) THEN
            IF(IPASS .eq. 1) THEN
              OVERLAPONLY = MOD(NCFACE, 3) .eq. 0
              INTERIORONLY = MOD(NCFACE, 3) .ne. 0
              CALC_FLUXES_X = (NCFACE .eq. 2) .OR.((NCFACE .eq. 1) .OR.
     > (NCFACE .eq. 6))
              CALC_FLUXES_Y = (NCFACE .eq. 5) .OR.((NCFACE .eq. 3) .OR.
     > (NCFACE .eq. 4))
            ELSE
              IF(IPASS .eq. 2) THEN
                OVERLAPONLY = MOD(NCFACE, 3) .eq. 2
                CALC_FLUXES_X = (NCFACE .eq. 4) .OR.((NCFACE .eq. 2)
     >  .OR.(NCFACE .eq. 3))
                CALC_FLUXES_Y = (NCFACE .eq. 1) .OR.((NCFACE .eq. 5)
     >  .OR.(NCFACE .eq. 6))
              ELSE
                CALC_FLUXES_X = (NCFACE .eq. 5) .OR.(NCFACE .eq. 6)
                CALC_FLUXES_Y = (NCFACE .eq. 2) .OR.(NCFACE .eq. 3)
              ENDIF
            ENDIF
          ELSE
            CALC_FLUXES_X = MOD(IPASS, 2) .eq. 1
            CALC_FLUXES_Y = .NOT. CALC_FLUXES_X
          ENDIF
          IF(CALC_FLUXES_X) THEN
            IF(S_EDGE .OR.(N_EDGE .OR.(.NOT. OVERLAPONLY))) THEN
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  AF(I, J) = 0.0
                END DO
              END DO
              IF(ADVECTIONSCHEME .eq. 77) THEN
                CALL gad_fluxlimit_adv_x(BI, BJ, (K), DTTRACERLEV(K),
     >  UTRANS, UVEL, MASKLOCW, LOCALTIJ, AF, MYTHID)
              ELSE
                IF(ADVECTIONSCHEME .eq. 30) THEN
                  CALL gad_dst3_adv_x(BI, BJ, (K), DTTRACERLEV(K),
     >  UTRANS, UVEL, MASKLOCW, LOCALTIJ, AF, MYTHID)
                ELSE
                  IF(ADVECTIONSCHEME .eq. 33) THEN
                    CALL gad_dst3fl_adv_x(BI, BJ, (K), DTTRACERLEV(K),
     >  UTRANS, UVEL, MASKLOCW, LOCALTIJ, AF, MYTHID)
                  ELSE
                    STOP
     >  'GAD_ADVECTION: adv. scheme incompatibale with mu' // 'lti-dim'
                    RETURN
                  ENDIF
                ENDIF
              ENDIF
            ENDIF
            IF(OVERLAPONLY) THEN
              IMINUPD = -1
              IMAXUPD = 92
              IF(W_EDGE) THEN
                IMINUPD = 1
              ENDIF
              IF(E_EDGE) THEN
                IMAXUPD = 90
              ENDIF
              IF(S_EDGE) THEN
                DO J = -2, 0, 1
                  doloop_ub0 = IMAXUPD
                  DO I = IMINUPD, doloop_ub0, 1
                    LOCALTIJ(I, J) = (LOCALTIJ(I, J) - RECIP_RA(I, J,
     >  BI, BJ) * RECIP_DRF(K) * DTTRACERLEV(K) * RECIP_HFACC(I, J, K,
     >  BI, BJ) *(AF(I + 1, J) - AF(I, J) - TRACER(I, J, K, BI, BJ) *(
     > UTRANS(I + 1, J) - UTRANS(I, J))))
                  END DO
                END DO
              ENDIF
              IF(N_EDGE) THEN
                DO J = 41, 43, 1
                  doloop_ub1 = IMAXUPD
                  DO I = IMINUPD, doloop_ub1, 1
                    LOCALTIJ(I, J) = (LOCALTIJ(I, J) - RECIP_RA(I, J,
     >  BI, BJ) * RECIP_DRF(K) * DTTRACERLEV(K) * RECIP_HFACC(I, J, K,
     >  BI, BJ) *(AF(I + 1, J) - AF(I, J) - TRACER(I, J, K, BI, BJ) *(
     > UTRANS(I + 1, J) - UTRANS(I, J))))
                  END DO
                END DO
              ENDIF
            ELSE
              JMINUPD = -2
              JMAXUPD = 43
              IF(INTERIORONLY .AND. S_EDGE) THEN
                JMINUPD = 1
              ENDIF
              IF(INTERIORONLY .AND. N_EDGE) THEN
                JMAXUPD = 40
              ENDIF
              doloop_ub2 = JMAXUPD
              DO J = JMINUPD, doloop_ub2, 1
                DO I = -1, 92, 1
                  LOCALTIJ(I, J) = (LOCALTIJ(I, J) - RECIP_RA(I, J, BI,
     >  BJ) * RECIP_DRF(K) * DTTRACERLEV(K) * RECIP_HFACC(I, J, K, BI,
     >  BJ) *(AF(I + 1, J) - AF(I, J) - TRACER(I, J, K, BI, BJ) *(
     > UTRANS(I + 1, J) - UTRANS(I, J))))
                END DO
              END DO
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  AFX(I, J) = AF(I, J)
                END DO
              END DO
            ENDIF
          ENDIF
          IF(CALC_FLUXES_Y) THEN
            IF(W_EDGE .OR.(E_EDGE .OR.(.NOT. OVERLAPONLY))) THEN
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  AF(I, J) = 0.0
                END DO
              END DO
              IF(ADVECTIONSCHEME .eq. 77) THEN
                CALL gad_fluxlimit_adv_y(BI, BJ, (K), DTTRACERLEV(K),
     >  VTRANS, VVEL, MASKLOCS, LOCALTIJ, AF, MYTHID)
              ELSE
                IF(ADVECTIONSCHEME .eq. 30) THEN
                  CALL gad_dst3_adv_y(BI, BJ, (K), DTTRACERLEV(K),
     >  VTRANS, VVEL, MASKLOCS, LOCALTIJ, AF, MYTHID)
                ELSE
                  IF(ADVECTIONSCHEME .eq. 33) THEN
                    CALL gad_dst3fl_adv_y(BI, BJ, (K), DTTRACERLEV(K),
     >  VTRANS, VVEL, MASKLOCS, LOCALTIJ, AF, MYTHID)
                  ELSE
                    STOP
     >  'GAD_ADVECTION: adv. scheme incompatibale with mu' // 'tli-dim'
                    RETURN
                  ENDIF
                ENDIF
              ENDIF
            ENDIF
            IF(OVERLAPONLY) THEN
              JMINUPD = -1
              JMAXUPD = 42
              IF(S_EDGE) THEN
                JMINUPD = 1
              ENDIF
              IF(N_EDGE) THEN
                JMAXUPD = 40
              ENDIF
              IF(W_EDGE) THEN
                doloop_ub3 = JMAXUPD
                DO J = JMINUPD, doloop_ub3, 1
                  DO I = -2, 0, 1
                    LOCALTIJ(I, J) = (LOCALTIJ(I, J) - RECIP_RA(I, J,
     >  BI, BJ) * RECIP_DRF(K) * DTTRACERLEV(K) * RECIP_HFACC(I, J, K,
     >  BI, BJ) *(AF(I, J + 1) - AF(I, J) - TRACER(I, J, K, BI, BJ) *(
     > VTRANS(I, J + 1) - VTRANS(I, J))))
                  END DO
                END DO
              ENDIF
              IF(E_EDGE) THEN
                doloop_ub4 = JMAXUPD
                DO J = JMINUPD, doloop_ub4, 1
                  DO I = 91, 93, 1
                    LOCALTIJ(I, J) = (LOCALTIJ(I, J) - RECIP_RA(I, J,
     >  BI, BJ) * RECIP_DRF(K) * DTTRACERLEV(K) * RECIP_HFACC(I, J, K,
     >  BI, BJ) *(AF(I, J + 1) - AF(I, J) - TRACER(I, J, K, BI, BJ) *(
     > VTRANS(I, J + 1) - VTRANS(I, J))))
                  END DO
                END DO
              ENDIF
            ELSE
              IMINUPD = -2
              IMAXUPD = 93
              IF(INTERIORONLY .AND. W_EDGE) THEN
                IMINUPD = 1
              ENDIF
              IF(E_EDGE .AND. INTERIORONLY) THEN
                IMAXUPD = 90
              ENDIF
              DO J = -1, 42, 1
                doloop_ub5 = IMAXUPD
                DO I = IMINUPD, doloop_ub5, 1
                  LOCALTIJ(I, J) = (LOCALTIJ(I, J) - RECIP_RA(I, J, BI,
     >  BJ) * RECIP_DRF(K) * DTTRACERLEV(K) * RECIP_HFACC(I, J, K, BI,
     >  BJ) *(AF(I, J + 1) - AF(I, J) - TRACER(I, J, K, BI, BJ) *(
     > VTRANS(I, J + 1) - VTRANS(I, J))))
                END DO
              END DO
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  AFY(I, J) = AF(I, J)
                END DO
              END DO
            ENDIF
          ENDIF
        END DO
        IF(IMPLICITADVECTION) THEN
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              GTRACER(I, J, K, BI, BJ) = ((LOCALTIJ(I, J) - TRACER(I, J
     > , K, BI, BJ)) / DTTRACERLEV(K))
            END DO
          END DO
        ELSE
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LOCALTIJK(I, J, K) = LOCALTIJ(I, J)
            END DO
          END DO
        ENDIF
        IF(USECUBEDSPHEREEXCHANGE .AND.((MYITER .eq.(NITER0 + 1)) .AND.
     > ((K .LE. 3) .AND.((TRACERIDENTITY .eq. 1) .AND.(DEBUGLEVEL .GE.
     >  2))))) THEN
          CALL debug_cs_corner_uv(' afx,afy from GAD_ADVECTION', AFX,
     >  AFY, (K), STANDARDMESSAGEUNIT, BI, BJ, MYTHID)
        ENDIF
      END DO
      IF(.NOT. IMPLICITADVECTION) THEN
        DO K = 15, 1, (-1)
          KKEY = K + IGADKEY * 15 +(-15)
          KUP = MOD(K + 1, 2) + 1
          KDOWN = MOD(K, 2) + 1
          KP1MSK = 1.0D00
          IF(K .eq. 15) THEN
            KP1MSK = 0.0D00
          ENDIF
          IF(K .eq. 1) THEN
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                RTRANSKP1(I, J) = (RTRANS(I, J) * KP1MSK)
                RTRANS(I, J) = 0.0
                FVERT(I, J, KUP) = 0.0
              END DO
            END DO
          ELSE
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                RTRANSKP1(I, J) = (RTRANS(I, J) * KP1MSK)
                RTRANS(I, J) = (MASKC(I, J, K + (-1), BI, BJ) * RA(I, J
     > , BI, BJ) * WVEL(I, J, K, BI, BJ))
                FVERT(I, J, KUP) = 0.0
              END DO
            END DO
            IF(VERTADVECSCHEME .eq. 77) THEN
              CALL gad_fluxlimit_adv_r(BI, BJ, (K), DTTRACERLEV(K),
     >  RTRANS, WVEL, LOCALTIJK, FVERT((-2), (-2), KUP), MYTHID)
            ELSE
              IF(VERTADVECSCHEME .eq. 30) THEN
                CALL gad_dst3_adv_r(BI, BJ, (K), DTTRACERLEV(K), RTRANS
     > , WVEL, LOCALTIJK, FVERT((-2), (-2), KUP), MYTHID)
              ELSE
                IF(VERTADVECSCHEME .eq. 33) THEN
                  CALL gad_dst3fl_adv_r(BI, BJ, (K), DTTRACERLEV(K),
     >  RTRANS, WVEL, LOCALTIJK, FVERT((-2), (-2), KUP), MYTHID)
                ELSE
                  STOP
     >  'GAD_ADVECTION: adv. scheme incompatibale with mu' // 'tli-dim'
                  RETURN
                ENDIF
              ENDIF
            ENDIF
          ENDIF
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LOCALTIJ(I, J) = (LOCALTIJK(I, J, K) - RKSIGN * RECIP_RA(
     > I, J, BI, BJ) * RECIP_DRF(K) * DTTRACERLEV(K) * RECIP_HFACC(I, J
     > , K, BI, BJ) *(FVERT(I, J, KDOWN) - FVERT(I, J, KUP) - TRACER(I,
     >  J, K, BI, BJ) *(RTRANSKP1(I, J) - RTRANS(I, J))))
              GTRACER(I, J, K, BI, BJ) = ((LOCALTIJ(I, J) - TRACER(I, J
     > , K, BI, BJ)) / DTTRACERLEV(K))
            END DO
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_biharm_x(BI, BJ, K, XA, DEL2T, DIFFK4, DFX, MYTHID
     > )
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2T(-2 : 93, -2 : 43)
      REAL(w2f__8) DIFFK4
      REAL(w2f__8) DFX(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -1, 93, 1
          DFX(I, J) = (DFX(I, J) + SQCOSFACU(J, BI, BJ) * RECIP_DXC(I,
     >  J, BI, BJ) * XA(I, J) * DIFFK4 *(DEL2T(I, J) - DEL2T(I + (-1),
     >  J)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_biharm_y(BI, BJ, K, YA, DEL2T, DIFFK4, DFY, MYTHID
     > )
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2T(-2 : 93, -2 : 43)
      REAL(w2f__8) DIFFK4
      REAL(w2f__8) DFY(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          DFY(I, J) = (DFY(I, J) + RECIP_DYC(I, J, BI, BJ) * YA(I, J) *
     >  DIFFK4 *(DEL2T(I, J) - DEL2T(I, J + (-1))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_c2_adv_r(BI, BJ, K, RTRANS, TRACER, WT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
C
C     **** Statements ****
C
      KM1 = MAX(K +(-1), 1)
      IF((K .eq. 1) .OR.(K .GT. 15)) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            WT(I, J) = 0.0
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            WT(I, J) = (RTRANS(I, J) * MASKC(I, J, KM1, BI, BJ) *(
     > TRACER(I, J, K, BI, BJ) + TRACER(I, J, KM1, BI, BJ)) * 5.0D-01)
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_c2_adv_x(BI, BJ, K, UTRANS, TRACER, UT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) UT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        UT((-2), J) = 0.0
        DO I = -1, 93, 1
          UT(I, J) = (UTRANS(I, J) *(TRACER(I, J) + TRACER(I + (-1), J)
     > ) * 5.0D-01)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_c2_adv_y(BI, BJ, K, VTRANS, TRACER, VT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) VT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO I = -2, 93, 1
        VT(I, (-2)) = 0.0
      END DO
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          VT(I, J) = (VTRANS(I, J) *(TRACER(I, J) + TRACER(I, J + (-1))
     > ) * 5.0D-01)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_c4_adv_r(BI, BJ, K, RTRANS, TRACER, WT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KM2
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) MASKBOUND
      REAL(w2f__8) MASKPM
      REAL(w2f__8) RJ
      REAL(w2f__8) RJJM
      REAL(w2f__8) RJJP
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
C
C     **** Statements ****
C
      KM2 = MAX(K +(-2), 1)
      KM1 = MAX(K +(-1), 1)
      KP1 = MIN(K + 1, 15)
      MASKPM = 1.0D00
      IF((K .GE. 15) .OR.(K .LE. 2)) THEN
        MASKPM = 0.0D00
      ENDIF
      IF((K .eq. 1) .OR.(K .GT. 15)) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            WT(I, J) = 0.0
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            MASKBOUND = MASKC(I, J, KP1, BI, BJ) * MASKC(I, J, KM2, BI,
     >  BJ) * MASKPM
            RJP = MASKC(I, J, KP1, BI, BJ) *(TRACER(I, J, KP1, BI, BJ)
     >  - TRACER(I, J, K, BI, BJ))
            RJ = (TRACER(I, J, K, BI, BJ) - TRACER(I, J, KM1, BI, BJ))
            RJM = MASKC(I, J, KM1, BI, BJ) *(TRACER(I, J, KM1, BI, BJ)
     >  - TRACER(I, J, KM2, BI, BJ))
            RJJP = (RJP - RJ)
            RJJM = (RJ - RJM)
            WT(I, J) = (MASKC(I, J, KM1, BI, BJ) *(RTRANS(I, J) *((
     > TRACER(I, J, K, BI, BJ) + TRACER(I, J, KM1, BI, BJ)) * 5.0D-01 -
     > (RJJM + RJJP) * 1.66666666666666657415D-01 * 5.0D-01) + ABS(
     > RTRANS(I, J)) * 1.66666666666666657415D-01 *(RJJM - RJJP) *
     >  5.0D-01 *(1.0D00 - MASKBOUND)))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_c4_adv_x(BI, BJ, K, UTRANS, TRACER, UT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) UT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RJ
      REAL(w2f__8) RJJM
      REAL(w2f__8) RJJP
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        UT((-2), J) = 0.0
        UT((-1), J) = 0.0
        UT(93, J) = 0.0
        DO I = 0, 92, 1
          RJP = MASKW(I + 1, J, K, BI, BJ) *(TRACER(I + 1, J) - TRACER(
     > I, J))
          RJ = MASKW(I, J, K, BI, BJ) *(TRACER(I, J) - TRACER(I + (-1),
     >  J))
          RJM = MASKW(I + (-1), J, K, BI, BJ) *(TRACER(I + (-1), J) -
     >  TRACER(I + (-2), J))
          RJJP = (RJP - RJ)
          RJJM = (RJ - RJM)
          UT(I, J) = (UTRANS(I, J) *(TRACER(I, J) + TRACER(I + (-1), J)
     >  -(RJJM + RJJP) * 1.66666666666666657415D-01) * 5.0D-01 + ABS(
     > UTRANS(I, J)) * 5.0D-01 * 1.66666666666666657415D-01 *(RJJP -
     >  RJJM) *(1.0D00 - MASKW(I + (-1), J, K, BI, BJ) * MASKW(I + 1, J
     > , K, BI, BJ)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_c4_adv_y(BI, BJ, K, VTRANS, TRACER, VT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) VT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RJ
      REAL(w2f__8) RJJM
      REAL(w2f__8) RJJP
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
C
C     **** Statements ****
C
      DO I = -2, 93, 1
        VT(I, (-2)) = 0.0
        VT(I, (-1)) = 0.0
        VT(I, 43) = 0.0
      END DO
      DO J = 0, 42, 1
        DO I = -2, 93, 1
          RJP = MASKS(I, J + 1, K, BI, BJ) *(TRACER(I, J + 1) - TRACER(
     > I, J))
          RJ = MASKS(I, J, K, BI, BJ) *(TRACER(I, J) - TRACER(I, J + (
     > -1)))
          RJM = MASKS(I, J + (-1), K, BI, BJ) *(TRACER(I, J + (-1)) -
     >  TRACER(I, J + (-2)))
          RJJP = (RJP - RJ)
          RJJM = (RJ - RJM)
          VT(I, J) = (VTRANS(I, J) *(TRACER(I, J) + TRACER(I, J + (-1))
     >  -(RJJM + RJJP) * 1.66666666666666657415D-01) * 5.0D-01 + ABS(
     > VTRANS(I, J)) * 5.0D-01 * 1.66666666666666657415D-01 *(RJJP -
     >  RJJM) *(1.0D00 - MASKS(I, J + (-1), K, BI, BJ) * MASKS(I, J + 1
     > , K, BI, BJ)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_calc_rhs(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KM1,
     >  KUP, KDOWN, XA, YA, UTRANS, VTRANS, RTRANS, RTRANSKP1, MASKUP,
     >  UVEL, VVEL, WVEL, DIFFKH, DIFFK4, KAPPAR, TRACER,
     >  TRACERIDENTITY, ADVECTIONSCHEME, VERTADVECSCHEME, CALCADVECTION
     > , IMPLICITADVECTION, FVERT, GTRACER, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      use gad_mod
      use tamc_mod
      use tamc_keys_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KUP
      INTEGER(w2f__i4) KDOWN
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANSKP1(-2 : 93, -2 : 43)
      REAL(w2f__8) MASKUP(-2 : 93, -2 : 43)
      REAL(w2f__8) UVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) DIFFKH
      REAL(w2f__8) DIFFK4
      REAL(w2f__8) KAPPAR(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) TRACERIDENTITY
      INTEGER(w2f__i4) ADVECTIONSCHEME
      INTEGER(w2f__i4) VERTADVECSCHEME
      LOGICAL(w2f__i4) CALCADVECTION
      LOGICAL(w2f__i4) IMPLICITADVECTION
      REAL(w2f__8) FVERT(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) GTRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) ADVFAC
      REAL(w2f__8) AF(-2 : 93, -2 : 43)
      EXTERNAL debug_cs_corner_uv
      REAL(w2f__8) DF(-2 : 93, -2 : 43)
      REAL(w2f__8) DF4(-2 : 93, -2 : 43)
      REAL(w2f__8) FMER(-2 : 93, -2 : 43)
      REAL(w2f__8) FZON(-2 : 93, -2 : 43)
      EXTERNAL gad_biharm_x
      EXTERNAL gad_biharm_y
      EXTERNAL gad_c2_adv_r
      EXTERNAL gad_c2_adv_x
      EXTERNAL gad_c2_adv_y
      EXTERNAL gad_c4_adv_r
      EXTERNAL gad_c4_adv_x
      EXTERNAL gad_c4_adv_y
      EXTERNAL gad_del2
      EXTERNAL gad_diff_r
      EXTERNAL gad_diff_x
      EXTERNAL gad_diff_y
      EXTERNAL gad_dst3fl_adv_r
      EXTERNAL gad_dst3fl_adv_x
      EXTERNAL gad_dst3fl_adv_y
      EXTERNAL gad_dst3_adv_r
      EXTERNAL gad_dst3_adv_x
      EXTERNAL gad_dst3_adv_y
      EXTERNAL gad_fluxlimit_adv_r
      EXTERNAL gad_fluxlimit_adv_x
      EXTERNAL gad_fluxlimit_adv_y
      EXTERNAL gad_grad_x
      EXTERNAL gad_grad_y
      EXTERNAL gad_u3_adv_r
      EXTERNAL gad_u3_adv_x
      EXTERNAL gad_u3_adv_y
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) LOCALT(-2 : 93, -2 : 43)
      REAL(w2f__8) RADVFAC
C
C     **** Statements ****
C
      ADVFAC = 0.0D00
      IF(CALCADVECTION) THEN
        ADVFAC = 1.0D00
      ENDIF
      RADVFAC = ADVFAC * RKSIGN
      IF(IMPLICITADVECTION) THEN
        RADVFAC = 0.0D00
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          FZON(I, J) = 0.0D00
          FMER(I, J) = 0.0D00
          FVERT(I, J, KUP) = 0.0D00
          DF(I, J) = 0.0D00
          DF4(I, J) = 0.0D00
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          LOCALT(I, J) = TRACER(I, J, K, BI, BJ)
        END DO
      END DO
      IF(DIFFK4 .ne. 0.0D00) THEN
        CALL gad_grad_x(BI, BJ, K, XA, LOCALT, FZON, MYTHID)
        CALL gad_grad_y(BI, BJ, K, YA, LOCALT, FMER, MYTHID)
        CALL gad_del2(BI, BJ, K, FZON, FMER, DF4, MYTHID)
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          FZON(I, J) = 0.0D00
        END DO
      END DO
      IF(CALCADVECTION) THEN
        IF(ADVECTIONSCHEME .eq. 2) THEN
          CALL gad_c2_adv_x(BI, BJ, K, UTRANS, LOCALT, AF, MYTHID)
        ELSE
          IF(ADVECTIONSCHEME .eq. 77) THEN
            CALL gad_fluxlimit_adv_x(BI, BJ, K, DTTRACERLEV(K), UTRANS,
     >  UVEL, MASKW((-2), (-2), K, BI, BJ), LOCALT, AF, MYTHID)
          ELSE
            IF(ADVECTIONSCHEME .eq. 3) THEN
              CALL gad_u3_adv_x(BI, BJ, K, UTRANS, LOCALT, AF, MYTHID)
            ELSE
              IF(ADVECTIONSCHEME .eq. 4) THEN
                CALL gad_c4_adv_x(BI, BJ, K, UTRANS, LOCALT, AF, MYTHID
     > )
              ELSE
                IF(ADVECTIONSCHEME .eq. 30) THEN
                  CALL gad_dst3_adv_x(BI, BJ, K, DTTRACERLEV(K), UTRANS
     > , UVEL, MASKW((-2), (-2), K, BI, BJ), LOCALT, AF, MYTHID)
                ELSE
                  IF(ADVECTIONSCHEME .eq. 33) THEN
                    IF(INADMODE) THEN
                      CALL gad_dst3_adv_x(BI, BJ, K, DTTRACERLEV(K),
     >  UTRANS, UVEL, MASKW((-2), (-2), K, BI, BJ), LOCALT, AF, MYTHID)
                    ELSE
                      CALL gad_dst3fl_adv_x(BI, BJ, K, DTTRACERLEV(K),
     >  UTRANS, UVEL, MASKW((-2), (-2), K, BI, BJ), LOCALT, AF, MYTHID)
                    ENDIF
                  ELSE
                    STOP 'GAD_CALC_RHS: Bad advectionScheme (X)'
                    RETURN
                  ENDIF
                ENDIF
              ENDIF
            ENDIF
          ENDIF
        ENDIF
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            FZON(I, J) = (AF(I, J) + FZON(I, J))
          END DO
        END DO
      ENDIF
      IF(DIFFKH .ne. 0.0D00) THEN
        CALL gad_diff_x(BI, BJ, K, XA, DIFFKH, LOCALT, DF, MYTHID)
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            DF(I, J) = 0.0D00
          END DO
        END DO
      ENDIF
      IF(DIFFK4 .ne. 0.0D00) THEN
        CALL gad_biharm_x(BI, BJ, K, XA, DF4, DIFFK4, DF, MYTHID)
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          FZON(I, J) = (DF(I, J) + FZON(I, J))
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          FMER(I, J) = 0.0D00
        END DO
      END DO
      IF(CALCADVECTION) THEN
        IF(ADVECTIONSCHEME .eq. 2) THEN
          CALL gad_c2_adv_y(BI, BJ, K, VTRANS, LOCALT, AF, MYTHID)
        ELSE
          IF(ADVECTIONSCHEME .eq. 77) THEN
            CALL gad_fluxlimit_adv_y(BI, BJ, K, DTTRACERLEV(K), VTRANS,
     >  VVEL, MASKS((-2), (-2), K, BI, BJ), LOCALT, AF, MYTHID)
          ELSE
            IF(ADVECTIONSCHEME .eq. 3) THEN
              CALL gad_u3_adv_y(BI, BJ, K, VTRANS, LOCALT, AF, MYTHID)
            ELSE
              IF(ADVECTIONSCHEME .eq. 4) THEN
                CALL gad_c4_adv_y(BI, BJ, K, VTRANS, LOCALT, AF, MYTHID
     > )
              ELSE
                IF(ADVECTIONSCHEME .eq. 30) THEN
                  CALL gad_dst3_adv_y(BI, BJ, K, DTTRACERLEV(K), VTRANS
     > , VVEL, MASKS((-2), (-2), K, BI, BJ), LOCALT, AF, MYTHID)
                ELSE
                  IF(ADVECTIONSCHEME .eq. 33) THEN
                    IF(INADMODE) THEN
                      CALL gad_dst3_adv_y(BI, BJ, K, DTTRACERLEV(K),
     >  VTRANS, VVEL, MASKS((-2), (-2), K, BI, BJ), LOCALT, AF, MYTHID)
                    ELSE
                      CALL gad_dst3fl_adv_y(BI, BJ, K, DTTRACERLEV(K),
     >  VTRANS, VVEL, MASKS((-2), (-2), K, BI, BJ), LOCALT, AF, MYTHID)
                    ENDIF
                  ELSE
                    STOP 'GAD_CALC_RHS: Bad advectionScheme (Y)'
                    RETURN
                  ENDIF
                ENDIF
              ENDIF
            ENDIF
          ENDIF
        ENDIF
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            FMER(I, J) = (AF(I, J) + FMER(I, J))
          END DO
        END DO
      ENDIF
      IF(DIFFKH .ne. 0.0D00) THEN
        CALL gad_diff_y(BI, BJ, K, YA, DIFFKH, LOCALT, DF, MYTHID)
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            DF(I, J) = 0.0D00
          END DO
        END DO
      ENDIF
      IF(DIFFK4 .ne. 0.0D00) THEN
        CALL gad_biharm_y(BI, BJ, K, YA, DF4, DIFFK4, DF, MYTHID)
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          FMER(I, J) = (DF(I, J) + FMER(I, J))
        END DO
      END DO
      IF((K .GE. 2) .AND.(CALCADVECTION .AND.(.NOT. IMPLICITADVECTION))
     > ) THEN
        IF(VERTADVECSCHEME .eq. 2) THEN
          CALL gad_c2_adv_r(BI, BJ, K, RTRANS, TRACER, AF, MYTHID)
        ELSE
          IF(VERTADVECSCHEME .eq. 77) THEN
            CALL gad_fluxlimit_adv_r(BI, BJ, K, DTTRACERLEV(K), RTRANS,
     >  WVEL, TRACER, AF, MYTHID)
          ELSE
            IF(VERTADVECSCHEME .eq. 3) THEN
              CALL gad_u3_adv_r(BI, BJ, K, RTRANS, TRACER, AF, MYTHID)
            ELSE
              IF(VERTADVECSCHEME .eq. 4) THEN
                CALL gad_c4_adv_r(BI, BJ, K, RTRANS, TRACER, AF, MYTHID
     > )
              ELSE
                IF(VERTADVECSCHEME .eq. 30) THEN
                  CALL gad_dst3_adv_r(BI, BJ, K, DTTRACERLEV(K), RTRANS
     > , WVEL, TRACER, AF, MYTHID)
                ELSE
                  IF(VERTADVECSCHEME .eq. 33) THEN
                    IF(INADMODE) THEN
                      CALL gad_dst3_adv_r(BI, BJ, K, DTTRACERLEV(K),
     >  RTRANS, WVEL, TRACER, AF, MYTHID)
                    ELSE
                      CALL gad_dst3fl_adv_r(BI, BJ, K, DTTRACERLEV(K),
     >  RTRANS, WVEL, TRACER, AF, MYTHID)
                    ENDIF
                  ELSE
                    STOP 'GAD_CALC_RHS: Bad vertAdvecScheme (R)'
                    RETURN
                  ENDIF
                ENDIF
              ENDIF
            ENDIF
          ENDIF
        ENDIF
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            FVERT(I, J, KUP) = (AF(I, J) + FVERT(I, J, KUP))
          END DO
        END DO
      ENDIF
      IF(IMPLICITDIFFUSION) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            DF(I, J) = 0.0D00
          END DO
        END DO
      ELSE
        CALL gad_diff_r(BI, BJ, K, KAPPAR, TRACER, DF, MYTHID)
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          FVERT(I, J, KUP) = (FVERT(I, J, KUP) + MASKUP(I, J) * DF(I, J
     > ))
        END DO
      END DO
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          GTRACER(I, J, K, BI, BJ) = (GTRACER(I, J, K, BI, BJ) -
     >  RECIP_RA(I, J, BI, BJ) * RECIP_DRF(K) * RECIP_HFACC(I, J, K, BI
     > , BJ) *((FMER(I, J + 1) - FMER(I, J)) +(FZON(I + 1, J) - FZON(I,
     >  J)) + RKSIGN *(FVERT(I, J, KDOWN) - FVERT(I, J, KUP)) - ADVFAC
     >  * LOCALT(I, J) *((UTRANS(I + 1, J) - UTRANS(I, J)) +(VTRANS(I,
     >  J + 1) - VTRANS(I, J)) + RADVFAC *(RTRANSKP1(I, J) - RTRANS(I,
     >  J)))))
        END DO
      END DO
      IF(USECUBEDSPHEREEXCHANGE .AND.((MYITER .eq.(NITER0 + 1)) .AND.((
     > K .eq. 2) .AND.((TRACERIDENTITY .eq. 1) .AND.(DEBUGLEVEL .GE. 2)
     > )))) THEN
        CALL debug_cs_corner_uv(' fZon,fMer from GAD_CALC_RHS', FZON,
     >  FMER, K, STANDARDMESSAGEUNIT, BI, BJ, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_del2(BI, BJ, K, DTDX, DTDY, DEL2, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) DTDX(-2 : 93, -2 : 43)
      REAL(w2f__8) DTDY(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          DEL2(I, J) = 0.0D00
        END DO
      END DO
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          DEL2(I, J) = (RECIP_HFACC(I, J, K, BI, BJ) * RECIP_DRF(K) *
     >  RECIP_RA(I, J, BI, BJ) *((DTDX(I + 1, J) - DTDX(I, J)) +(DTDY(I
     > , J + 1) - DTDY(I, J))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_diff_r(BI, BJ, K, KAPPAR, TRACER, DFR, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) KAPPAR(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) DFR(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
C
C     **** Statements ****
C
      KM1 = MAX(K +(-1), 1)
      IF((K .eq. 1) .OR.(K .GT. 15)) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            DFR(I, J) = 0.0
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            DFR(I, J) = (-(RKSIGN * RECIP_DRC(K) * KAPPAR(I, J) * RA(I,
     >  J, BI, BJ) *(TRACER(I, J, K, BI, BJ) - TRACER(I, J, KM1, BI, BJ
     > ))))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_diff_x(BI, BJ, K, XA, DIFFKH, TRACER, DFX, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) DIFFKH
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) DFX(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DFX((-2), J) = 0.0
        DO I = -1, 93, 1
          DFX(I, J) = (-(COSFACU(J, BI, BJ) * RECIP_DXC(I, J, BI, BJ) *
     >  XA(I, J) * DIFFKH *(TRACER(I, J) - TRACER(I + (-1), J))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_diff_y(BI, BJ, K, YA, DIFFKH, TRACER, DFY, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
      REAL(w2f__8) DIFFKH
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) DFY(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO I = -2, 93, 1
        DFY(I, (-2)) = 0.0
      END DO
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          DFY(I, J) = (-(RECIP_DYC(I, J, BI, BJ) * YA(I, J) * DIFFKH *(
     > TRACER(I, J) - TRACER(I, J + (-1)))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_dst3_adv_x(BI, BJ, K, DELTATLOC, UTRANS, UVEL,
     >  MASKLOCW, TRACER, UT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) DELTATLOC
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) UVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKLOCW(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) UT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) CFL
      REAL(w2f__8) D0
      REAL(w2f__8) D1
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) PSIM
      REAL(w2f__8) PSIP
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) SMALLNO
      REAL(w2f__8) THETAM
      REAL(w2f__8) THETAP
      REAL(w2f__8) UFLD
C
C     **** Statements ****
C
      IF(INADMODE) THEN
        SMALLNO = 9.99999999999999945153D-21
      ELSE
        SMALLNO = 9.99999999999999945153D-21
      ENDIF
      DO J = -2, 43, 1
        UT((-2), J) = 0.0
        UT((-1), J) = 0.0
        UT(93, J) = 0.0
        DO I = 0, 92, 1
          RJP = MASKLOCW(I + 1, J) *(TRACER(I + 1, J) - TRACER(I, J))
          RJ = MASKLOCW(I, J) *(TRACER(I, J) - TRACER(I + (-1), J))
          RJM = MASKLOCW(I + (-1), J) *(TRACER(I + (-1), J) - TRACER(I
     >  + (-2), J))
          UFLD = RECIP_HFACW(I, J, K, BI, BJ) * RECIP_DRF(K) * UTRANS(I
     > , J) * RECIP_DYG(I, J, BI, BJ)
          CFL = ABS(RECIP_DXC(I, J, BI, BJ) * DELTATLOC * UFLD)
          D0 = (1.0D00 - CFL) *(2.0D00 - CFL) *
     >  1.66666666666666657415D-01
          D1 = (1.0D00 - CFL * CFL) * 1.66666666666666657415D-01
          IF((SMALLNO .GT. ABS(RJ)) .OR.(SMALLNO .GT. ABS(RJM))) THEN
            THETAP = 0.0D00
            PSIP = 0.0D00
          ELSE
            THETAP = (RJM + SMALLNO) /(RJ + SMALLNO)
            PSIP = D0 + D1 * THETAP
          ENDIF
          IF((SMALLNO .GT. ABS(RJ)) .OR.(SMALLNO .GT. ABS(RJP))) THEN
            THETAM = 0.0D00
            PSIM = 0.0D00
          ELSE
            THETAM = (RJP + SMALLNO) /(RJ + SMALLNO)
            PSIM = D0 + D1 * THETAM
          ENDIF
          UT(I, J) = ((UTRANS(I, J) + ABS(UTRANS(I, J))) * 5.0D-01 *(
     > TRACER(I + (-1), J) + PSIP * RJ) +(UTRANS(I, J) - ABS(UTRANS(I,
     >  J))) * 5.0D-01 *(TRACER(I, J) - PSIM * RJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_dst3_adv_y(BI, BJ, K, DELTATLOC, VTRANS, VVEL,
     >  MASKLOCS, TRACER, VT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) DELTATLOC
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKLOCS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) VT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) CFL
      REAL(w2f__8) D0
      REAL(w2f__8) D1
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) PSIM
      REAL(w2f__8) PSIP
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) SMALLNO
      REAL(w2f__8) THETAM
      REAL(w2f__8) THETAP
      REAL(w2f__8) VFLD
C
C     **** Statements ****
C
      IF(INADMODE) THEN
        SMALLNO = 9.99999999999999945153D-21
      ELSE
        SMALLNO = 9.99999999999999945153D-21
      ENDIF
      DO I = -2, 93, 1
        VT(I, (-2)) = 0.0
        VT(I, (-1)) = 0.0
        VT(I, 43) = 0.0
      END DO
      DO J = 0, 42, 1
        DO I = -2, 93, 1
          RJP = MASKLOCS(I, J + 1) *(TRACER(I, J + 1) - TRACER(I, J))
          RJ = MASKLOCS(I, J) *(TRACER(I, J) - TRACER(I, J + (-1)))
          RJM = MASKLOCS(I, J + (-1)) *(TRACER(I, J + (-1)) - TRACER(I,
     >  J + (-2)))
          VFLD = RECIP_HFACS(I, J, K, BI, BJ) * RECIP_DRF(K) * VTRANS(I
     > , J) * RECIP_DXG(I, J, BI, BJ)
          CFL = ABS(RECIP_DYC(I, J, BI, BJ) * DELTATLOC * VFLD)
          D0 = (1.0D00 - CFL) *(2.0D00 - CFL) *
     >  1.66666666666666657415D-01
          D1 = (1.0D00 - CFL * CFL) * 1.66666666666666657415D-01
          IF((SMALLNO .GT. ABS(RJ)) .OR.(SMALLNO .GT. ABS(RJM))) THEN
            THETAP = 0.0D00
            PSIP = 0.0D00
          ELSE
            THETAP = (RJM + SMALLNO) /(RJ + SMALLNO)
            PSIP = D0 + D1 * THETAP
          ENDIF
          IF((SMALLNO .GT. ABS(RJ)) .OR.(SMALLNO .GT. ABS(RJP))) THEN
            THETAM = 0.0D00
            PSIM = 0.0D00
          ELSE
            THETAM = (RJP + SMALLNO) /(RJ + SMALLNO)
            PSIM = D0 + D1 * THETAM
          ENDIF
          VT(I, J) = ((VTRANS(I, J) + ABS(VTRANS(I, J))) * 5.0D-01 *(
     > TRACER(I, J + (-1)) + PSIP * RJ) +(VTRANS(I, J) - ABS(VTRANS(I,
     >  J))) * 5.0D-01 *(TRACER(I, J) - PSIM * RJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_dst3_adv_r(BI_ARG, BJ_ARG, K, DTARG, RTRANS, WVEL,
     >  TRACER, WT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI_ARG
      INTEGER(w2f__i4) BJ_ARG
      INTEGER(w2f__i4) K
      REAL(w2f__8) DTARG
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) WVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) CFL
      REAL(w2f__8) D0
      REAL(w2f__8) D1
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KM2
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) PSIM
      REAL(w2f__8) PSIP
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) SMALLNO
      REAL(w2f__8) THETAM
      REAL(w2f__8) THETAP
      REAL(w2f__8) WFLD
C
C     **** Statements ****
C
      IF(.NOT. MULTIDIMADVECTION) THEN
        BI = BI_ARG
        BJ = BJ_ARG
      ELSE
        BI = 1
        BJ = 1
      ENDIF
      IF(INADMODE) THEN
        SMALLNO = 9.99999999999999945153D-21
      ELSE
        SMALLNO = 9.99999999999999945153D-21
      ENDIF
      KM2 = MAX(K +(-2), 1)
      KM1 = MAX(K +(-1), 1)
      KP1 = MIN(K + 1, 15)
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          RJP = MASKC(I, J, KP1, BI_ARG, BJ_ARG) *(TRACER(I, J, K, BI,
     >  BJ) - TRACER(I, J, KP1, BI, BJ))
          RJ = MASKC(I, J, KM1, BI_ARG, BJ_ARG) * MASKC(I, J, K, BI_ARG
     > , BJ_ARG) *(TRACER(I, J, KM1, BI, BJ) - TRACER(I, J, K, BI, BJ))
          RJM = MASKC(I, J, KM1, BI_ARG, BJ_ARG) *(TRACER(I, J, KM2, BI
     > , BJ) - TRACER(I, J, KM1, BI, BJ))
          WFLD = RTRANS(I, J) * RECIP_RA(I, J, BI_ARG, BJ_ARG)
          CFL = ABS(RECIP_DRC(K) * DTARG * WFLD)
          D0 = (1.0D00 - CFL) *(2.0D00 - CFL) *
     >  1.66666666666666657415D-01
          D1 = (1.0D00 - CFL * CFL) * 1.66666666666666657415D-01
          IF((SMALLNO .GT. ABS(RJ)) .OR.(SMALLNO .GT. ABS(RJM))) THEN
            THETAP = 0.0D00
            PSIP = 0.0D00
          ELSE
            THETAP = (RJM + SMALLNO) /(RJ + SMALLNO)
            PSIP = D0 + D1 * THETAP
          ENDIF
          IF((SMALLNO .GT. ABS(RJ)) .OR.(SMALLNO .GT. ABS(RJP))) THEN
            THETAM = 0.0D00
            PSIM = 0.0D00
          ELSE
            THETAM = (RJP + SMALLNO) /(RJ + SMALLNO)
            PSIM = D0 + D1 * THETAM
          ENDIF
          WT(I, J) = ((RTRANS(I, J) + ABS(RTRANS(I, J))) * 5.0D-01 *(
     > TRACER(I, J, K, BI, BJ) + PSIM * RJ) +(RTRANS(I, J) - ABS(RTRANS
     > (I, J))) * 5.0D-01 *(TRACER(I, J, KM1, BI, BJ) - PSIP * RJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_dst3fl_adv_x(BI, BJ, K, DELTATLOC, UTRANS, UVEL,
     >  MASKLOCW, TRACER, UT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) DELTATLOC
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) UVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKLOCW(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) UT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) CFL
      REAL(w2f__8) D0
      REAL(w2f__8) D1
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) PSIM
      REAL(w2f__8) PSIP
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) THETAM
      REAL(w2f__8) THETAP
      REAL(w2f__8) UFLD
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        UT((-2), J) = 0.0D00
        UT((-1), J) = 0.0D00
        UT(93, J) = 0.0D00
        DO I = 0, 92, 1
          RJP = MASKLOCW(I + 1, J) *(TRACER(I + 1, J) - TRACER(I, J))
          RJ = MASKLOCW(I, J) *(TRACER(I, J) - TRACER(I + (-1), J))
          RJM = MASKLOCW(I + (-1), J) *(TRACER(I + (-1), J) - TRACER(I
     >  + (-2), J))
          UFLD = RECIP_HFACW(I, J, K, BI, BJ) * RECIP_DRF(K) * UTRANS(I
     > , J) * RECIP_DYG(I, J, BI, BJ)
          CFL = ABS(RECIP_DXC(I, J, BI, BJ) * DELTATLOC * UFLD)
          D0 = (1.0D00 - CFL) *(2.0D00 - CFL) *
     >  1.66666666666666657415D-01
          D1 = (1.0D00 - CFL * CFL) * 1.66666666666666657415D-01
          THETAP = RJM /(RJ + 9.99999999999999945153D-21)
          PSIP = D0 + D1 * THETAP
          PSIP = MAX(MIN(MIN(PSIP, THETAP *((1.0D00 - CFL) /(CFL +
     >  9.99999999999999945153D-21))), 1.0D00), 0.0D00)
          THETAM = RJP /(RJ + 9.99999999999999945153D-21)
          PSIM = D0 + D1 * THETAM
          PSIM = MAX(MIN(MIN(PSIM, THETAM *((1.0D00 - CFL) /(CFL +
     >  9.99999999999999945153D-21))), 1.0D00), 0.0D00)
          UT(I, J) = ((UTRANS(I, J) + ABS(UTRANS(I, J))) * 5.0D-01 *(
     > TRACER(I + (-1), J) + PSIP * RJ) +(UTRANS(I, J) - ABS(UTRANS(I,
     >  J))) * 5.0D-01 *(TRACER(I, J) - PSIM * RJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_dst3fl_adv_y(BI, BJ, K, DELTATLOC, VTRANS, VVEL,
     >  MASKLOCS, TRACER, VT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) DELTATLOC
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKLOCS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) VT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) CFL
      REAL(w2f__8) D0
      REAL(w2f__8) D1
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) PSIM
      REAL(w2f__8) PSIP
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) THETAM
      REAL(w2f__8) THETAP
      REAL(w2f__8) VFLD
C
C     **** Statements ****
C
      DO I = -2, 93, 1
        VT(I, (-2)) = 0.0D00
        VT(I, (-1)) = 0.0D00
        VT(I, 43) = 0.0D00
      END DO
      DO J = 0, 42, 1
        DO I = -2, 93, 1
          RJP = MASKLOCS(I, J + 1) *(TRACER(I, J + 1) - TRACER(I, J))
          RJ = MASKLOCS(I, J) *(TRACER(I, J) - TRACER(I, J + (-1)))
          RJM = MASKLOCS(I, J + (-1)) *(TRACER(I, J + (-1)) - TRACER(I,
     >  J + (-2)))
          VFLD = RECIP_HFACS(I, J, K, BI, BJ) * RECIP_DRF(K) * VTRANS(I
     > , J) * RECIP_DXG(I, J, BI, BJ)
          CFL = ABS(RECIP_DYC(I, J, BI, BJ) * DELTATLOC * VFLD)
          D0 = (1.0D00 - CFL) *(2.0D00 - CFL) *
     >  1.66666666666666657415D-01
          D1 = (1.0D00 - CFL * CFL) * 1.66666666666666657415D-01
          THETAP = RJM /(RJ + 9.99999999999999945153D-21)
          PSIP = D0 + D1 * THETAP
          PSIP = MAX(MIN(MIN(PSIP, THETAP *((1.0D00 - CFL) /(CFL +
     >  9.99999999999999945153D-21))), 1.0D00), 0.0D00)
          THETAM = RJP /(RJ + 9.99999999999999945153D-21)
          PSIM = D0 + D1 * THETAM
          PSIM = MAX(MIN(MIN(PSIM, THETAM *((1.0D00 - CFL) /(CFL +
     >  9.99999999999999945153D-21))), 1.0D00), 0.0D00)
          VT(I, J) = ((VTRANS(I, J) + ABS(VTRANS(I, J))) * 5.0D-01 *(
     > TRACER(I, J + (-1)) + PSIP * RJ) +(VTRANS(I, J) - ABS(VTRANS(I,
     >  J))) * 5.0D-01 *(TRACER(I, J) - PSIM * RJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_dst3fl_adv_r(BI_ARG, BJ_ARG, K, DTARG, RTRANS,
     >  WVEL, TRACER, WT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI_ARG
      INTEGER(w2f__i4) BJ_ARG
      INTEGER(w2f__i4) K
      REAL(w2f__8) DTARG
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) WVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) CFL
      REAL(w2f__8) D0
      REAL(w2f__8) D1
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KM2
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) PSIM
      REAL(w2f__8) PSIP
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) THETAM
      REAL(w2f__8) THETAP
      REAL(w2f__8) WFLD
C
C     **** Statements ****
C
      IF(.NOT. MULTIDIMADVECTION) THEN
        BI = BI_ARG
        BJ = BJ_ARG
      ELSE
        BI = 1
        BJ = 1
      ENDIF
      KM2 = MAX(K +(-2), 1)
      KM1 = MAX(K +(-1), 1)
      KP1 = MIN(K + 1, 15)
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          RJP = MASKC(I, J, KP1, BI_ARG, BJ_ARG) *(TRACER(I, J, K, BI,
     >  BJ) - TRACER(I, J, KP1, BI, BJ))
          RJ = MASKC(I, J, KM1, BI_ARG, BJ_ARG) * MASKC(I, J, K, BI_ARG
     > , BJ_ARG) *(TRACER(I, J, KM1, BI, BJ) - TRACER(I, J, K, BI, BJ))
          RJM = MASKC(I, J, KM1, BI_ARG, BJ_ARG) *(TRACER(I, J, KM2, BI
     > , BJ) - TRACER(I, J, KM1, BI, BJ))
          WFLD = RTRANS(I, J) * RECIP_RA(I, J, BI_ARG, BJ_ARG)
          CFL = ABS(RECIP_DRC(K) * DTARG * WFLD)
          D0 = (1.0D00 - CFL) *(2.0D00 - CFL) *
     >  1.66666666666666657415D-01
          D1 = (1.0D00 - CFL * CFL) * 1.66666666666666657415D-01
          THETAP = RJM /(RJ + 9.99999999999999945153D-21)
          PSIP = D0 + D1 * THETAP
          PSIP = MAX(MIN(MIN(PSIP, THETAP *((1.0D00 - CFL) /(CFL +
     >  9.99999999999999945153D-21))), 1.0D00), 0.0D00)
          THETAM = RJP /(RJ + 9.99999999999999945153D-21)
          PSIM = D0 + D1 * THETAM
          PSIM = MAX(MIN(MIN(PSIM, THETAM *((1.0D00 - CFL) /(CFL +
     >  9.99999999999999945153D-21))), 1.0D00), 0.0D00)
          WT(I, J) = ((RTRANS(I, J) + ABS(RTRANS(I, J))) * 5.0D-01 *(
     > TRACER(I, J, K, BI, BJ) + PSIM * RJ) +(RTRANS(I, J) - ABS(RTRANS
     > (I, J))) * 5.0D-01 *(TRACER(I, J, KM1, BI, BJ) - PSIP * RJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_fluxlimit_adv_r(BI_ARG, BJ_ARG, K, DTARG, RTRANS,
     >  WVEL, TRACER, WT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI_ARG
      INTEGER(w2f__i4) BJ_ARG
      INTEGER(w2f__i4) K
      REAL(w2f__8) DTARG
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) WVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) CR
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KM2
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) WFLD
C
C     **** Statements ****
C
      IF(.NOT. MULTIDIMADVECTION) THEN
        BI = BI_ARG
        BJ = BJ_ARG
      ELSE
        BI = 1
        BJ = 1
      ENDIF
      KM2 = MAX(K +(-2), 1)
      KM1 = MAX(K +(-1), 1)
      KP1 = MIN(K + 1, 15)
      IF(K .GT. 15) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            WT(I, J) = 0.0
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            WFLD = RTRANS(I, J) * RECIP_RA(I, J, BI_ARG, BJ_ARG)
            RJP = MASKC(I, J, KP1, BI_ARG, BJ_ARG) *(TRACER(I, J, KP1,
     >  BI, BJ) - TRACER(I, J, K, BI, BJ))
            RJ = (TRACER(I, J, K, BI, BJ) - TRACER(I, J, KM1, BI, BJ))
            RJM = MASKC(I, J, KM2, BI_ARG, BJ_ARG) *(TRACER(I, J, KM1,
     >  BI, BJ) - TRACER(I, J, KM2, BI, BJ))
            IF(RJ .ne. 0.0D00) THEN
              IF(RTRANS(I, J) .LT. 0.0D00) THEN
                CR = RJM / RJ
              ELSE
                CR = RJP / RJ
              ENDIF
            ELSE
              IF(RTRANS(I, J) .LT. 0.0D00) THEN
                CR = RJM * 1.00000002004087734272D+20
              ELSE
                CR = RJP * 1.00000002004087734272D+20
              ENDIF
            ENDIF
            CR = (MAX(MAX(MIN(CR, 2.0D00), MIN(CR * 2.0D00, 1.0D00)),
     >  0.0D00))
            WT(I, J) = (MASKC(I, J, KM1, BI_ARG, BJ_ARG) *(RTRANS(I, J)
     >  *(TRACER(I, J, K, BI, BJ) + TRACER(I, J, KM1, BI, BJ)) *
     >  5.0D-01 + RJ *(CR * RECIP_DRC(K) * DTARG * RTRANS(I, J) * WFLD
     >  + ABS(RTRANS(I, J)) *(1.0D00 - CR)) * 5.0D-01))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_fluxlimit_adv_x(BI, BJ, K, DELTATLOC, UTRANS, UVEL
     > , MASKLOCW, TRACER, UT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) DELTATLOC
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) UVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKLOCW(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) UT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) CR
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) UFLD
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        UT((-2), J) = 0.0
        UT((-1), J) = 0.0
        UT(93, J) = 0.0
        DO I = 0, 92, 1
          UFLD = RECIP_HFACW(I, J, K, BI, BJ) * RECIP_DRF(K) * UTRANS(I
     > , J) * RECIP_DYG(I, J, BI, BJ)
          RJP = MASKLOCW(I + 1, J) *(TRACER(I + 1, J) - TRACER(I, J))
          RJ = MASKLOCW(I, J) *(TRACER(I, J) - TRACER(I + (-1), J))
          RJM = MASKLOCW(I + (-1), J) *(TRACER(I + (-1), J) - TRACER(I
     >  + (-2), J))
          IF(RJ .ne. 0.0D00) THEN
            IF(UTRANS(I, J) .GT. 0.0D00) THEN
              CR = RJM / RJ
            ELSE
              CR = RJP / RJ
            ENDIF
          ELSE
            IF(UTRANS(I, J) .GT. 0.0D00) THEN
              CR = RJM * 1.00000002004087734272D+20
            ELSE
              CR = RJP * 1.00000002004087734272D+20
            ENDIF
          ENDIF
          CR = (MAX(MAX(MIN(CR, 2.0D00), MIN(CR * 2.0D00, 1.0D00)),
     >  0.0D00))
          UT(I, J) = (UTRANS(I, J) *(TRACER(I, J) + TRACER(I + (-1), J)
     > ) * 5.0D-01 - RJ *(CR * RECIP_DXC(I, J, BI, BJ) * DELTATLOC *
     >  UTRANS(I, J) * UFLD + ABS(UTRANS(I, J)) *(1.0D00 - CR)) *
     >  5.0D-01)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_fluxlimit_adv_y(BI, BJ, K, DELTATLOC, VTRANS, VVEL
     > , MASKLOCS, TRACER, VT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) DELTATLOC
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VVEL(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MASKLOCS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) VT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) CR
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RJ
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) VFLD
C
C     **** Statements ****
C
      DO I = -2, 93, 1
        VT(I, (-2)) = 0.0
        VT(I, (-1)) = 0.0
        VT(I, 43) = 0.0
      END DO
      DO J = 0, 42, 1
        DO I = -2, 93, 1
          VFLD = RECIP_HFACS(I, J, K, BI, BJ) * RECIP_DRF(K) * VTRANS(I
     > , J) * RECIP_DXG(I, J, BI, BJ)
          RJP = MASKLOCS(I, J + 1) *(TRACER(I, J + 1) - TRACER(I, J))
          RJ = MASKLOCS(I, J) *(TRACER(I, J) - TRACER(I, J + (-1)))
          RJM = MASKLOCS(I, J + (-1)) *(TRACER(I, J + (-1)) - TRACER(I,
     >  J + (-2)))
          IF(RJ .ne. 0.0D00) THEN
            IF(VTRANS(I, J) .GT. 0.0D00) THEN
              CR = RJM / RJ
            ELSE
              CR = RJP / RJ
            ENDIF
          ELSE
            IF(VTRANS(I, J) .GT. 0.0D00) THEN
              CR = RJM * 1.00000002004087734272D+20
            ELSE
              CR = RJP * 1.00000002004087734272D+20
            ENDIF
          ENDIF
          CR = (MAX(MAX(MIN(CR, 2.0D00), MIN(CR * 2.0D00, 1.0D00)),
     >  0.0D00))
          VT(I, J) = (VTRANS(I, J) *(TRACER(I, J) + TRACER(I, J + (-1))
     > ) * 5.0D-01 - RJ *(CR * RECIP_DYC(I, J, BI, BJ) * DELTATLOC *
     >  VTRANS(I, J) * VFLD + ABS(VTRANS(I, J)) *(1.0D00 - CR)) *
     >  5.0D-01)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_grad_x(BI, BJ, K, XA, TRACER, DTDX, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) DTDX(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DTDX((-2), J) = 0.0
        DO I = -1, 93, 1
          DTDX(I, J) = (SQCOSFACU(J, BI, BJ) * XA(I, J) * RECIP_DXC(I,
     >  J, BI, BJ) *(TRACER(I, J) - TRACER(I + (-1), J)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_grad_y(BI, BJ, K, YA, TRACER, DTDY, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) DTDY(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO I = -2, 93, 1
        DTDY(I, (-2)) = 0.0
      END DO
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          DTDY(I, J) = (YA(I, J) * RECIP_DYC(I, J, BI, BJ) *(TRACER(I,
     >  J) - TRACER(I, J + (-1))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_u3_adv_r(BI, BJ, K, RTRANS, TRACER, WT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KM2
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) RJ
      REAL(w2f__8) RJJM
      REAL(w2f__8) RJJP
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
C
C     **** Statements ****
C
      KM2 = MAX(K +(-2), 1)
      KM1 = MAX(K +(-1), 1)
      KP1 = MIN(K + 1, 15)
      IF((K .eq. 1) .OR.(K .GT. 15)) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            WT(I, J) = 0.0
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            RJP = MASKC(I, J, KP1, BI, BJ) *(TRACER(I, J, KP1, BI, BJ)
     >  - TRACER(I, J, K, BI, BJ))
            RJ = (TRACER(I, J, K, BI, BJ) - TRACER(I, J, KM1, BI, BJ))
            RJM = MASKC(I, J, KM2, BI, BJ) *(TRACER(I, J, KM1, BI, BJ)
     >  - TRACER(I, J, KM2, BI, BJ))
            RJJP = RJP - RJ
            RJJM = RJ - RJM
            WT(I, J) = (MASKC(I, J, KM1, BI, BJ) *(RTRANS(I, J) *((
     > TRACER(I, J, K, BI, BJ) + TRACER(I, J, KM1, BI, BJ)) * 5.0D-01 -
     > (RJJM + RJJP) * 1.66666666666666657415D-01 * 5.0D-01) + ABS(
     > RTRANS(I, J)) * 1.66666666666666657415D-01 *(RJJM - RJJP) *
     >  5.0D-01))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_u3_adv_x(BI, BJ, K, UTRANS, TRACER, UT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) UT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RJ
      REAL(w2f__8) RJJM
      REAL(w2f__8) RJJP
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        UT((-2), J) = 0.0
        UT((-1), J) = 0.0
        UT(93, J) = 0.0
        DO I = 0, 92, 1
          RJP = MASKW(I + 1, J, K, BI, BJ) *(TRACER(I + 1, J) - TRACER(
     > I, J))
          RJ = MASKW(I, J, K, BI, BJ) *(TRACER(I, J) - TRACER(I + (-1),
     >  J))
          RJM = MASKW(I + (-1), J, K, BI, BJ) *(TRACER(I + (-1), J) -
     >  TRACER(I + (-2), J))
          RJJP = RJP - RJ
          RJJM = RJ - RJM
          UT(I, J) = (UTRANS(I, J) *(TRACER(I, J) + TRACER(I + (-1), J)
     >  -(RJJM + RJJP) * 1.66666666666666657415D-01) * 5.0D-01 + ABS(
     > UTRANS(I, J)) * 5.0D-01 * 1.66666666666666657415D-01 *(RJJP -
     >  RJJM))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE gad_u3_adv_y(BI, BJ, K, VTRANS, TRACER, VT, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43)
      REAL(w2f__8) VT(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RJ
      REAL(w2f__8) RJJM
      REAL(w2f__8) RJJP
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
C
C     **** Statements ****
C
      DO I = -2, 93, 1
        VT(I, (-2)) = 0.0
        VT(I, (-1)) = 0.0
        VT(I, 43) = 0.0
      END DO
      DO J = 0, 42, 1
        DO I = -2, 93, 1
          RJP = MASKS(I, J + 1, K, BI, BJ) *(TRACER(I, J + 1) - TRACER(
     > I, J))
          RJ = MASKS(I, J, K, BI, BJ) *(TRACER(I, J) - TRACER(I, J + (
     > -1)))
          RJM = MASKS(I, J + (-1), K, BI, BJ) *(TRACER(I, J + (-1)) -
     >  TRACER(I, J + (-2)))
          RJJP = RJP - RJ
          RJJM = RJ - RJM
          VT(I, J) = (VTRANS(I, J) *(TRACER(I, J) + TRACER(I, J + (-1))
     >  -(RJJM + RJJP) * 1.66666666666666657415D-01) * 5.0D-01 + ABS(
     > VTRANS(I, J)) * 5.0D-01 * 1.66666666666666657415D-01 *(RJJP -
     >  RJJM))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_calc_rtrans(K, BI, BJ, RTRANSU, RTRANSV, MYTIME,
     >  MYITER, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) RTRANSU(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANSV(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF(K .GT. 15) THEN
        DO J = -1, 43, 1
          DO I = -1, 93, 1
            RTRANSU(I, J) = 0.0
            RTRANSV(I, J) = 0.0
          END DO
        END DO
      ELSE
        DO J = -1, 43, 1
          DO I = -1, 93, 1
            RTRANSU(I, J) = ((RA(I, J, BI, BJ) * WVEL(I, J, K, BI, BJ)
     >  + RA(I + (-1), J, BI, BJ) * WVEL(I + (-1), J, K, BI, BJ)) *
     >  5.0D-01)
            RTRANSV(I, J) = ((RA(I, J, BI, BJ) * WVEL(I, J, K, BI, BJ)
     >  + RA(I, J + (-1), BI, BJ) * WVEL(I, J + (-1), K, BI, BJ)) *
     >  5.0D-01)
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_fluxform(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KUP,
     >  KDOWN, KAPPARU, KAPPARV, FVERU, FVERV, GUDISS, GVDISS, MYTIME,
     >  MYITER, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use ffields_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KUP
      INTEGER(w2f__i4) KDOWN
      REAL(w2f__8) KAPPARU(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) KAPPARV(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) FVERU(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) FVERV(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) GUDISS(-2 : 93, -2 : 43)
      REAL(w2f__8) GVDISS(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) AHDUDXFAC
      REAL(w2f__8) AHDUDYFAC
      REAL(w2f__8) AHDVDXFAC
      REAL(w2f__8) AHDVDYFAC
      REAL(w2f__8) ARDUDRFAC
      REAL(w2f__8) ARDVDRFAC
      LOGICAL(w2f__i4) BOTTOMDRAGTERMS
      REAL(w2f__8) CF(-2 : 93, -2 : 43)
      REAL(w2f__8) FMER(-2 : 93, -2 : 43)
      REAL(w2f__8) FUFAC
      REAL(w2f__8) FVFAC
      REAL(w2f__8) FVRDW(-2 : 93, -2 : 43)
      REAL(w2f__8) FVRUP(-2 : 93, -2 : 43)
      REAL(w2f__8) FZON(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) KE(-2 : 93, -2 : 43)
      EXTERNAL mom_calc_hfacz
      EXTERNAL mom_calc_ke
      EXTERNAL mom_calc_rtrans
      EXTERNAL mom_calc_strain
      EXTERNAL mom_calc_tension
      EXTERNAL mom_u_adv_uu
      EXTERNAL mom_u_adv_vu
      EXTERNAL mom_u_adv_wu
      EXTERNAL mom_u_bottomdrag
      EXTERNAL mom_u_coriolis
      EXTERNAL mom_u_coriolis_nh
      EXTERNAL mom_u_del2u
      EXTERNAL mom_u_metric_cylinder
      EXTERNAL mom_u_metric_nh
      EXTERNAL mom_u_metric_sphere
      EXTERNAL mom_u_rviscflux
      EXTERNAL mom_u_sidedrag
      EXTERNAL mom_u_xviscflux
      EXTERNAL mom_u_yviscflux
      EXTERNAL mom_v_adv_uv
      EXTERNAL mom_v_adv_vv
      EXTERNAL mom_v_adv_wv
      EXTERNAL mom_v_bottomdrag
      EXTERNAL mom_v_coriolis
      EXTERNAL mom_v_del2v
      EXTERNAL mom_v_metric_cylinder
      EXTERNAL mom_v_metric_nh
      EXTERNAL mom_v_metric_sphere
      EXTERNAL mom_v_rviscflux
      EXTERNAL mom_v_sidedrag
      EXTERNAL mom_v_xviscflux
      EXTERNAL mom_v_yviscflux
      REAL(w2f__8) MT(-2 : 93, -2 : 43)
      REAL(w2f__8) MTFACU
      REAL(w2f__8) MTFACV
      REAL(w2f__8) RTRANSU(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANSV(-2 : 93, -2 : 43)
      REAL(w2f__8) RVELDUDRFAC
      REAL(w2f__8) RVELDVDRFAC
      REAL(w2f__8) R_HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) STRAIN(-2 : 93, -2 : 43)
      REAL(w2f__8) TENSION(-2 : 93, -2 : 43)
      REAL(w2f__8) UDUDXFAC
      REAL(w2f__8) UDVDXFAC
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) V4F(-2 : 93, -2 : 43)
      REAL(w2f__8) VDUDYFAC
      REAL(w2f__8) VDVDYFAC
      REAL(w2f__8) VF(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
      INTEGER(w2f__i4) doloop_ub11
      INTEGER(w2f__i4) doloop_ub12
      INTEGER(w2f__i4) doloop_ub13
      INTEGER(w2f__i4) doloop_ub14
      INTEGER(w2f__i4) doloop_ub15
      INTEGER(w2f__i4) doloop_ub16
      INTEGER(w2f__i4) doloop_ub17
      INTEGER(w2f__i4) doloop_ub18
      INTEGER(w2f__i4) doloop_ub19
      INTEGER(w2f__i4) doloop_ub20
      INTEGER(w2f__i4) doloop_ub21
      INTEGER(w2f__i4) doloop_ub22
      INTEGER(w2f__i4) doloop_ub23
      INTEGER(w2f__i4) doloop_ub24
      INTEGER(w2f__i4) doloop_ub25
      INTEGER(w2f__i4) doloop_ub26
      INTEGER(w2f__i4) doloop_ub27
      INTEGER(w2f__i4) doloop_ub28
      INTEGER(w2f__i4) doloop_ub29
      INTEGER(w2f__i4) doloop_ub30
      INTEGER(w2f__i4) doloop_ub31
      INTEGER(w2f__i4) doloop_ub32
      INTEGER(w2f__i4) doloop_ub33
      INTEGER(w2f__i4) doloop_ub34
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          VF(I, J) = 0.0
          V4F(I, J) = 0.0
          CF(I, J) = 0.0
          MT(I, J) = 0.0
          FZON(I, J) = 0.0
          FMER(I, J) = 0.0
          FVRUP(I, J) = 0.0
          FVRDW(I, J) = 0.0
          RTRANSU(I, J) = 0.0
          RTRANSV(I, J) = 0.0
          STRAIN(I, J) = 0.0
          TENSION(I, J) = 0.0
          GUDISS(I, J) = 0.0
          GVDISS(I, J) = 0.0
        END DO
      END DO
      UDUDXFAC = AFFACMOM
      AHDUDXFAC = VFFACMOM
      VDUDYFAC = AFFACMOM
      AHDUDYFAC = VFFACMOM
      RVELDUDRFAC = AFFACMOM
      ARDUDRFAC = VFFACMOM
      MTFACU = MTFACMOM
      FUFAC = CFFACMOM
      UDVDXFAC = AFFACMOM
      AHDVDXFAC = VFFACMOM
      VDVDYFAC = AFFACMOM
      AHDVDYFAC = VFFACMOM
      RVELDVDRFAC = AFFACMOM
      ARDVDRFAC = VFFACMOM
      MTFACV = MTFACMOM
      FVFAC = CFFACMOM
      IF(IMPLICITVISCOSITY) THEN
        ARDUDRFAC = 0.0D00
        ARDVDRFAC = 0.0D00
      ENDIF
      IF((BOTTOMDRAGLINEAR .ne. 0.0D00) .OR.(NO_SLIP_BOTTOM .OR.(
     > BOTTOMDRAGQUADRATIC .ne. 0.0D00))) THEN
        BOTTOMDRAGTERMS = .TRUE.
      ELSE
        BOTTOMDRAGTERMS = .FALSE.
      ENDIF
      CALL mom_calc_hfacz(BI, BJ, K, HFACZ, R_HFACZ, MYTHID)
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          XA(I, J) = (HFACW(I, J, K, BI, BJ) * DRF(K) * DYG(I, J, BI,
     >  BJ))
          YA(I, J) = (HFACS(I, J, K, BI, BJ) * DRF(K) * DXG(I, J, BI,
     >  BJ))
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          UFLD(I, J) = UVEL(I, J, K, BI, BJ)
          VFLD(I, J) = VVEL(I, J, K, BI, BJ)
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          UTRANS(I, J) = (UFLD(I, J) * XA(I, J))
          VTRANS(I, J) = (VFLD(I, J) * YA(I, J))
        END DO
      END DO
      IF(BOTTOMDRAGTERMS) THEN
        CALL mom_calc_ke(BI, BJ, K, (3), UFLD, VFLD, KE, MYTHID)
      ENDIF
      IF((VISCASTRAIN .ne. 0.0D00) .OR.(VISCATENSION .ne. 0.0D00)) THEN
        CALL mom_calc_tension(BI, BJ, K, UFLD, VFLD, TENSION, MYTHID)
        CALL mom_calc_strain(BI, BJ, K, UFLD, VFLD, HFACZ, STRAIN,
     >  MYTHID)
      ENDIF
      IF((K .eq. 1) .AND. MOMADVECTION) THEN
        CALL mom_calc_rtrans(K, BI, BJ, RTRANSU, RTRANSV, MYTIME,
     >  MYITER, MYTHID)
        CALL mom_u_adv_wu(BI, BJ, K, UVEL, WVEL, RTRANSU, FVERU((-2), (
     > -2), KUP), MYTHID)
        CALL mom_v_adv_wv(BI, BJ, K, VVEL, WVEL, RTRANSV, FVERV((-2), (
     > -2), KUP), MYTHID)
      ENDIF
      IF(MOMADVECTION) THEN
        CALL mom_calc_rtrans((K + 1), BI, BJ, RTRANSU, RTRANSV, MYTIME,
     >  MYITER, MYTHID)
      ENDIF
      IF(MOMADVECTION) THEN
        CALL mom_u_adv_uu(BI, BJ, K, UTRANS, UFLD, FZON, MYTHID)
        CALL mom_u_adv_vu(BI, BJ, K, VTRANS, UFLD, FMER, MYTHID)
        CALL mom_u_adv_wu(BI, BJ, (K + 1), UVEL, WVEL, RTRANSU, FVERU((
     > -2), (-2), KDOWN), MYTHID)
        doloop_ub7 = JMAX
        DO J = JMIN, doloop_ub7, 1
          doloop_ub8 = IMAX
          DO I = IMIN, doloop_ub8, 1
            GU(I, J, K, BI, BJ) = (-(RECIP_RAW(I, J, BI, BJ) *
     >  RECIP_DRF(K) * RECIP_HFACW(I, J, K, BI, BJ) *(UDUDXFAC *(FZON(I
     > , J) - FZON(I + (-1), J)) + VDUDYFAC *(FMER(I, J + 1) - FMER(I,
     >  J)) + RVELDUDRFAC * RKSIGN *(FVERU(I, J, KDOWN) - FVERU(I, J,
     >  KUP)))))
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            GU(I, J, K, BI, BJ) = 0.0D00
          END DO
        END DO
      ENDIF
      IF(MOMVISCOSITY) THEN
        IF(VISCA4 .ne. 0.0D00) THEN
          CALL mom_u_del2u(BI, BJ, K, UFLD, HFACZ, V4F, MYTHID)
        ENDIF
        CALL mom_u_xviscflux(BI, BJ, K, UFLD, V4F, FZON, MYTHID)
        CALL mom_u_yviscflux(BI, BJ, K, UFLD, V4F, HFACZ, FMER, MYTHID)
        IF(.NOT. IMPLICITVISCOSITY) THEN
          CALL mom_u_rviscflux(BI, BJ, K, UVEL, KAPPARU, FVRUP, MYTHID)
          CALL mom_u_rviscflux(BI, BJ, (K + 1), UVEL, KAPPARU, FVRDW,
     >  MYTHID)
        ENDIF
        doloop_ub9 = JMAX
        DO J = JMIN, doloop_ub9, 1
          doloop_ub10 = IMAX
          DO I = IMIN, doloop_ub10, 1
            GUDISS(I, J) = (-(RECIP_RAW(I, J, BI, BJ) * RECIP_DRF(K) *
     >  RECIP_HFACW(I, J, K, BI, BJ) *(AHDUDXFAC *(FZON(I, J) - FZON(I
     >  + (-1), J)) + AHDUDYFAC *(FMER(I, J + 1) - FMER(I, J)) +
     >  ARDUDRFAC * RKSIGN *(FVRDW(I, J) - FVRUP(I, J)))))
          END DO
        END DO
        IF(NO_SLIP_SIDES) THEN
          CALL mom_u_sidedrag(BI, BJ, K, UFLD, V4F, HFACZ, VF, MYTHID)
          doloop_ub11 = JMAX
          DO J = JMIN, doloop_ub11, 1
            doloop_ub12 = IMAX
            DO I = IMIN, doloop_ub12, 1
              GUDISS(I, J) = (GUDISS(I, J) + VF(I, J))
            END DO
          END DO
        ENDIF
        IF(BOTTOMDRAGTERMS) THEN
          CALL mom_u_bottomdrag(BI, BJ, K, UFLD, KE, KAPPARU, VF,
     >  MYTHID)
          doloop_ub13 = JMAX
          DO J = JMIN, doloop_ub13, 1
            doloop_ub14 = IMAX
            DO I = IMIN, doloop_ub14, 1
              GUDISS(I, J) = (GUDISS(I, J) + VF(I, J))
            END DO
          END DO
        ENDIF
      ENDIF
      IF(USENHMTERMS) THEN
        CALL mom_u_metric_nh(BI, BJ, K, UFLD, WVEL, MT, MYTHID)
        doloop_ub15 = JMAX
        DO J = JMIN, doloop_ub15, 1
          doloop_ub16 = IMAX
          DO I = IMIN, doloop_ub16, 1
            GU(I, J, K, BI, BJ) = (GU(I, J, K, BI, BJ) + MT(I, J) *
     >  MTFACU)
          END DO
        END DO
      ENDIF
      IF(USINGSPHERICALPOLARMTERMS) THEN
        CALL mom_u_metric_sphere(BI, BJ, K, UFLD, VFLD, MT, MYTHID)
        doloop_ub17 = JMAX
        DO J = JMIN, doloop_ub17, 1
          doloop_ub18 = IMAX
          DO I = IMIN, doloop_ub18, 1
            GU(I, J, K, BI, BJ) = (GU(I, J, K, BI, BJ) + MT(I, J) *
     >  MTFACU)
          END DO
        END DO
      ENDIF
      IF(USINGCYLINDRICALGRID) THEN
        CALL mom_u_metric_cylinder(BI, BJ, K, UFLD, VFLD, MT, MYTHID)
        doloop_ub19 = JMAX
        DO J = JMIN, doloop_ub19, 1
          doloop_ub20 = IMAX
          DO I = IMIN, doloop_ub20, 1
            GU(I, J, K, BI, BJ) = (GU(I, J, K, BI, BJ) + MT(I, J) *
     >  MTFACU)
          END DO
        END DO
      ENDIF
      IF(MOMADVECTION) THEN
        CALL mom_v_adv_uv(BI, BJ, K, UTRANS, VFLD, FZON, MYTHID)
        CALL mom_v_adv_vv(BI, BJ, K, VTRANS, VFLD, FMER, MYTHID)
        CALL mom_v_adv_wv(BI, BJ, (K + 1), VVEL, WVEL, RTRANSV, FVERV((
     > -2), (-2), KDOWN), MYTHID)
        doloop_ub21 = JMAX
        DO J = JMIN, doloop_ub21, 1
          doloop_ub22 = IMAX
          DO I = IMIN, doloop_ub22, 1
            GV(I, J, K, BI, BJ) = (-(RECIP_RAS(I, J, BI, BJ) *
     >  RECIP_DRF(K) * RECIP_HFACS(I, J, K, BI, BJ) *(UDVDXFAC *(FZON(I
     >  + 1, J) - FZON(I, J)) + VDVDYFAC *(FMER(I, J) - FMER(I, J + (-1
     > ))) + RVELDVDRFAC * RKSIGN *(FVERV(I, J, KDOWN) - FVERV(I, J,
     >  KUP)))))
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            GV(I, J, K, BI, BJ) = 0.0D00
          END DO
        END DO
      ENDIF
      IF(MOMVISCOSITY) THEN
        IF(VISCA4 .ne. 0.0D00) THEN
          CALL mom_v_del2v(BI, BJ, K, VFLD, HFACZ, V4F, MYTHID)
        ENDIF
        CALL mom_v_xviscflux(BI, BJ, K, VFLD, V4F, HFACZ, FZON, MYTHID)
        CALL mom_v_yviscflux(BI, BJ, K, VFLD, V4F, FMER, MYTHID)
        IF(.NOT. IMPLICITVISCOSITY) THEN
          CALL mom_v_rviscflux(BI, BJ, K, VVEL, KAPPARV, FVRUP, MYTHID)
          CALL mom_v_rviscflux(BI, BJ, (K + 1), VVEL, KAPPARV, FVRDW,
     >  MYTHID)
        ENDIF
        doloop_ub23 = JMAX
        DO J = JMIN, doloop_ub23, 1
          doloop_ub24 = IMAX
          DO I = IMIN, doloop_ub24, 1
            GVDISS(I, J) = (-(RECIP_RAS(I, J, BI, BJ) * RECIP_DRF(K) *
     >  RECIP_HFACS(I, J, K, BI, BJ) *(AHDVDXFAC *(FZON(I + 1, J) -
     >  FZON(I, J)) + AHDVDYFAC *(FMER(I, J) - FMER(I, J + (-1))) +
     >  ARDVDRFAC * RKSIGN *(FVRDW(I, J) - FVRUP(I, J)))))
          END DO
        END DO
        IF(NO_SLIP_SIDES) THEN
          CALL mom_v_sidedrag(BI, BJ, K, VFLD, V4F, HFACZ, VF, MYTHID)
          doloop_ub25 = JMAX
          DO J = JMIN, doloop_ub25, 1
            doloop_ub26 = IMAX
            DO I = IMIN, doloop_ub26, 1
              GVDISS(I, J) = (GVDISS(I, J) + VF(I, J))
            END DO
          END DO
        ENDIF
        IF(BOTTOMDRAGTERMS) THEN
          CALL mom_v_bottomdrag(BI, BJ, K, VFLD, KE, KAPPARV, VF,
     >  MYTHID)
          doloop_ub27 = JMAX
          DO J = JMIN, doloop_ub27, 1
            doloop_ub28 = IMAX
            DO I = IMIN, doloop_ub28, 1
              GVDISS(I, J) = (GVDISS(I, J) + VF(I, J))
            END DO
          END DO
        ENDIF
      ENDIF
      IF(USENHMTERMS) THEN
        CALL mom_v_metric_nh(BI, BJ, K, VFLD, WVEL, MT, MYTHID)
        doloop_ub29 = JMAX
        DO J = JMIN, doloop_ub29, 1
          doloop_ub30 = IMAX
          DO I = IMIN, doloop_ub30, 1
            GV(I, J, K, BI, BJ) = (GV(I, J, K, BI, BJ) + MT(I, J) *
     >  MTFACV)
          END DO
        END DO
      ENDIF
      IF(USINGSPHERICALPOLARMTERMS) THEN
        CALL mom_v_metric_sphere(BI, BJ, K, UFLD, MT, MYTHID)
        doloop_ub31 = JMAX
        DO J = JMIN, doloop_ub31, 1
          doloop_ub32 = IMAX
          DO I = IMIN, doloop_ub32, 1
            GV(I, J, K, BI, BJ) = (GV(I, J, K, BI, BJ) + MT(I, J) *
     >  MTFACV)
          END DO
        END DO
      ENDIF
      IF(USINGCYLINDRICALGRID) THEN
        CALL mom_v_metric_cylinder(BI, BJ, K, UFLD, VFLD, MT, MYTHID)
        doloop_ub33 = JMAX
        DO J = JMIN, doloop_ub33, 1
          doloop_ub34 = IMAX
          DO I = IMIN, doloop_ub34, 1
            GV(I, J, K, BI, BJ) = (GV(I, J, K, BI, BJ) + MT(I, J) *
     >  MTFACV)
          END DO
        END DO
      ENDIF
      IF(.NOT. USECDSCHEME) THEN
        CALL mom_u_coriolis(BI, BJ, K, VFLD, CF, MYTHID)
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            GU(I, J, K, BI, BJ) = (GU(I, J, K, BI, BJ) + CF(I, J) *
     >  FUFAC)
          END DO
        END DO
        CALL mom_v_coriolis(BI, BJ, K, UFLD, CF, MYTHID)
        doloop_ub1 = JMAX
        DO J = JMIN, doloop_ub1, 1
          doloop_ub2 = IMAX
          DO I = IMIN, doloop_ub2, 1
            GV(I, J, K, BI, BJ) = (GV(I, J, K, BI, BJ) + CF(I, J) *
     >  FVFAC)
          END DO
        END DO
      ENDIF
      IF(NONHYDROSTATIC .OR. QUASIHYDROSTATIC) THEN
        CALL mom_u_coriolis_nh(BI, BJ, K, WVEL, CF, MYTHID)
        doloop_ub3 = JMAX
        DO J = JMIN, doloop_ub3, 1
          doloop_ub4 = IMAX
          DO I = IMIN, doloop_ub4, 1
            GU(I, J, K, BI, BJ) = (GU(I, J, K, BI, BJ) + CF(I, J) *
     >  FUFAC)
          END DO
        END DO
      ENDIF
      doloop_ub5 = JMAX
      DO J = JMIN, doloop_ub5, 1
        doloop_ub6 = IMAX
        DO I = IMIN, doloop_ub6, 1
          GU(I, J, K, BI, BJ) = (GU(I, J, K, BI, BJ) * MASKW(I, J, K,
     >  BI, BJ))
          GUDISS(I, J) = (GUDISS(I, J) * MASKW(I, J, K, BI, BJ))
          GV(I, J, K, BI, BJ) = (GV(I, J, K, BI, BJ) * MASKS(I, J, K,
     >  BI, BJ))
          GVDISS(I, J) = (GVDISS(I, J) * MASKS(I, J, K, BI, BJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_adv_uu(BI, BJ, K, UTRANS, UFLD, ADVECTFLUXUU,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) ADVECTFLUXUU(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          ADVECTFLUXUU(I, J) = ((UTRANS(I, J) + UTRANS(I + 1, J)) *
     >  2.5D-01 *(UFLD(I, J) + UFLD(I + 1, J)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_adv_vu(BI, BJ, K, VTRANS, UFLD, ADVECTFLUXVU,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) ADVECTFLUXVU(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 43, 1
        DO I = -1, 93, 1
          ADVECTFLUXVU(I, J) = ((VTRANS(I, J) + VTRANS(I + (-1), J)) *
     >  2.5D-01 *(UFLD(I, J) + UFLD(I, J + (-1))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_adv_wu(BI, BJ, K, UFLD, WFLD, RTRANS,
     >  ADVECTIVEFLUXWU, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) ADVECTIVEFLUXWU(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF(USINGPCOORDS .AND.((K .eq. 16) .AND. USEREALFRESHWATERFLUX))
     >  THEN
        DO J = -1, 43, 1
          DO I = -1, 93, 1
            ADVECTIVEFLUXWU(I, J) = (RTRANS(I, J) * UFLD(I, J, K + (-1)
     > , BI, BJ))
          END DO
        END DO
      ELSE
        IF((K .GT. 15) .OR.((K .eq. 1) .AND. RIGIDLID)) THEN
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ADVECTIVEFLUXWU(I, J) = 0.0
            END DO
          END DO
        ELSE
          IF(K .eq. 1) THEN
            DO J = -1, 43, 1
              DO I = -1, 93, 1
                ADVECTIVEFLUXWU(I, J) = (RTRANS(I, J) * UFLD(I, J, K,
     >  BI, BJ))
              END DO
            END DO
          ELSE
            DO J = -1, 43, 1
              DO I = -1, 93, 1
                ADVECTIVEFLUXWU(I, J) = (RTRANS(I, J) * 5.0D-01 *(UFLD(
     > I, J, K, BI, BJ) + UFLD(I, J, K + (-1), BI, BJ)))
              END DO
            END DO
            IF((SELECT_RSTAR .eq. 0) .AND.(.NOT. RIGIDLID)) THEN
              DO J = -1, 43, 1
                DO I = -1, 93, 1
                  ADVECTIVEFLUXWU(I, J) = (ADVECTIVEFLUXWU(I, J) + UFLD
     > (I, J, K, BI, BJ) *(RA(I, J, BI, BJ) * WFLD(I, J, K, BI, BJ) *(
     > MASKC(I, J, K, BI, BJ) - MASKC(I, J, K + (-1), BI, BJ)) + RA(I +
     >  (-1), J, BI, BJ) * WFLD(I + (-1), J, K, BI, BJ) *(MASKC(I + (-1
     > ), J, K, BI, BJ) - MASKC(I + (-1), J, K + (-1), BI, BJ))) *
     >  2.5D-01)
                END DO
              END DO
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_coriolis(BI, BJ, K, VFLD, UCORIOLISTERM, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) UCORIOLISTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) ONE
      PARAMETER ( ONE =     1.000000000000000)
C
C     **** Statements ****
C
      IF(USEENERGYCONSERVINGCORIOLIS) THEN
        DO J = -2, 42, 1
          DO I = -1, 93, 1
            UCORIOLISTERM(I, J) = ((FCORI(I, J, BI, BJ) * 5.0D-01 *(
     > VFLD(I, J) + VFLD(I, J + 1)) + FCORI(I + (-1), J, BI, BJ) *
     >  5.0D-01 *(VFLD(I + (-1), J) + VFLD(I + (-1), J + 1))) * 5.0D-01
     > )
          END DO
        END DO
      ELSE
        DO J = -2, 42, 1
          DO I = -1, 93, 1
            UCORIOLISTERM(I, J) = ((FCORI(I, J, BI, BJ) + FCORI(I + (-1
     > ), J, BI, BJ)) * 5.0D-01 * 2.5D-01 *(VFLD(I + (-1), J + 1) +
     >  VFLD(I + (-1), J) + VFLD(I, J) + VFLD(I, J + 1)))
          END DO
        END DO
      ENDIF
      IF(USEJAMARTWETPOINTS) THEN
        DO J = -2, 42, 1
          DO I = -1, 93, 1
            UCORIOLISTERM(I, J) = ((UCORIOLISTERM(I, J) * 4.0D00) / MAX
     > (MASKS(I + (-1), J + 1, K, BI, BJ) + MASKS(I + (-1), J, K, BI,
     >  BJ) + MASKS(I, J, K, BI, BJ) + MASKS(I, J + 1, K, BI, BJ),
     >  1.0D00))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_coriolis_nh(BI, BJ, K, WFLD, UCORIOLISTERM,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) WFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) UCORIOLISTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) WMSK
C
C     **** Statements ****
C
      KP1 = MIN(K + 1, 15)
      WMSK = 1.0D00
      IF(K .eq. 15) THEN
        WMSK = 0.0D00
      ENDIF
      DO J = -2, 42, 1
        DO I = -1, 93, 1
          UCORIOLISTERM(I, J) = (RECIP_HORIVERTRATIO * GRAVITYSIGN *(
     > FCORICOS(I, J, BI, BJ) * 5.0D-01 *(WFLD(I, J, K, BI, BJ) + WFLD(
     > I, J, KP1, BI, BJ) * WMSK) + FCORICOS(I + (-1), J, BI, BJ) *
     >  5.0D-01 *(WFLD(I + (-1), J, K, BI, BJ) + WFLD(I + (-1), J, KP1,
     >  BI, BJ) * WMSK)) * 5.0D-01)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_del2u(BI, BJ, K, UFLD, HFACZ, DEL2U, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2U(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) FMER(-2 : 93, -2 : 43)
      REAL(w2f__8) FZON(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZCLOSEDN
      REAL(w2f__8) HFACZCLOSEDS
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 42, 1
        DO I = -2, 92, 1
          FZON(I, J) = (RECIP_DXF(I, J, BI, BJ) * DYF(I, J, BI, BJ) *
     >  DRF(K) * HFACC(I, J, K, BI, BJ) *(UFLD(I + 1, J) - UFLD(I, J)))
        END DO
      END DO
      DO J = -1, 43, 1
        DO I = -1, 92, 1
          FMER(I, J) = (RECIP_DYU(I, J, BI, BJ) * DXV(I, J, BI, BJ) *
     >  DRF(K) * HFACZ(I, J) *(UFLD(I, J) - UFLD(I, J + (-1))))
        END DO
      END DO
      DO J = -1, 42, 1
        DO I = -1, 92, 1
          DEL2U(I, J) = (MASKW(I, J, K, BI, BJ) * RECIP_RAW(I, J, BI,
     >  BJ) * RECIP_DRF(K) * RECIP_HFACW(I, J, K, BI, BJ) *(FMER(I, J +
     >  1) + FZON(I, J) - FZON(I + (-1), J) - FMER(I, J)))
        END DO
      END DO
      IF(NO_SLIP_SIDES) THEN
        DO J = -1, 42, 1
          DO I = -1, 92, 1
            HFACZCLOSEDS = HFACW(I, J, K, BI, BJ) - HFACZ(I, J)
            HFACZCLOSEDN = HFACW(I, J, K, BI, BJ) - HFACZ(I, J + 1)
            DEL2U(I, J) = (DEL2U(I, J) - MASKW(I, J, K, BI, BJ) * UFLD(
     > I, J) * DRF(K) * RECIP_RAW(I, J, BI, BJ) * RECIP_DRF(K) *
     >  RECIP_HFACW(I, J, K, BI, BJ) *(RECIP_DYU(I, J, BI, BJ) * DXV(I,
     >  J, BI, BJ) * HFACZCLOSEDS + RECIP_DYU(I, J + 1, BI, BJ) * DXV(I
     > , J + 1, BI, BJ) * HFACZCLOSEDN) * 2.0D00)
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_metric_cylinder(BI, BJ, K, UFLD, VFLD,
     >  UMETRICTERMS, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) UMETRICTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RADIUS
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -1, 93, 1
          RADIUS = (YG(I, J, BI, BJ) + YG(I, J + 1, BI, BJ)) * 5.0D-01
          IF(RADIUS .GT. 0.0D00) THEN
            UMETRICTERMS(I, J) = ((UFLD(I, J) * 2.5D-01 *(VFLD(I + (-1)
     > , J + 1) + VFLD(I, J + 1) + VFLD(I, J) + VFLD(I + (-1), J))) /
     >  RADIUS)
          ELSE
            UMETRICTERMS(I, J) = 0.0
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_metric_nh(BI, BJ, K, UFLD, WFLD, UMETRICTERMS,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) WFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) UMETRICTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) WVELBOTTOMOVERRIDE
C
C     **** Statements ****
C
      KP1 = MIN(K + 1, 15)
      WVELBOTTOMOVERRIDE = 1.0D00
      IF(K .eq. 15) THEN
        WVELBOTTOMOVERRIDE = 0.0D00
      ENDIF
      DO J = -2, 43, 1
        DO I = -1, 93, 1
          UMETRICTERMS(I, J) = (GRAVITYSIGN * RECIP_HORIVERTRATIO *
     >  UFLD(I, J) * RECIP_RSPHERE * 2.5D-01 *(WFLD(I, J, K, BI, BJ) +
     >  WFLD(I + (-1), J, K, BI, BJ) + WVELBOTTOMOVERRIDE *(WFLD(I, J,
     >  KP1, BI, BJ) + WFLD(I + (-1), J, KP1, BI, BJ))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_metric_sphere(BI, BJ, K, UFLD, VFLD,
     >  UMETRICTERMS, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) UMETRICTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -1, 93, 1
          UMETRICTERMS(I, J) = (TANPHIATU(I, J, BI, BJ) * UFLD(I, J) *
     >  RECIP_RSPHERE * 2.5D-01 *(VFLD(I + (-1), J + 1) + VFLD(I, J + 1
     > ) + VFLD(I, J) + VFLD(I + (-1), J)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_xviscflux(BI, BJ, K, UFLD, DEL2U, XVISCFLUXU,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2U(-2 : 93, -2 : 43)
      REAL(w2f__8) XVISCFLUXU(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          XVISCFLUXU(I, J) = (RECIP_DXF(I, J, BI, BJ) * HFACC(I, J, K,
     >  BI, BJ) * DRF(K) * DYF(I, J, BI, BJ) *(COSFACU(J, BI, BJ) *
     >  VISCA4 *(DEL2U(I + 1, J) - DEL2U(I, J)) - COSFACU(J, BI, BJ) *
     >  VISCAH *(UFLD(I + 1, J) - UFLD(I, J))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_yviscflux(BI, BJ, K, UFLD, DEL2U, HFACZ,
     >  YVISCFLUXU, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2U(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) YVISCFLUXU(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          YVISCFLUXU(I, J) = (RECIP_DYU(I, J, BI, BJ) * HFACZ(I, J) *
     >  DRF(K) * DXV(I, J, BI, BJ) *(VISCA4 *(DEL2U(I, J) - DEL2U(I, J
     >  + (-1))) - VISCAH *(UFLD(I, J) - UFLD(I, J + (-1)))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_adv_uv(BI, BJ, K, UTRANS, VFLD, ADVECTFLUXUV,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) ADVECTFLUXUV(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 43, 1
        DO I = -1, 93, 1
          ADVECTFLUXUV(I, J) = ((UTRANS(I, J) + UTRANS(I, J + (-1))) *
     >  2.5D-01 *(VFLD(I, J) + VFLD(I + (-1), J)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_adv_vv(BI, BJ, K, VTRANS, VFLD, ADVECTFLUXVV,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) ADVECTFLUXVV(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          ADVECTFLUXVV(I, J) = ((VTRANS(I, J) + VTRANS(I, J + 1)) *
     >  2.5D-01 *(VFLD(I, J) + VFLD(I, J + 1)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_adv_wv(BI, BJ, K, VFLD, WFLD, RTRANS,
     >  ADVECTIVEFLUXWV, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) ADVECTIVEFLUXWV(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF(USINGPCOORDS .AND.((K .eq. 16) .AND. USEREALFRESHWATERFLUX))
     >  THEN
        DO J = -1, 43, 1
          DO I = -1, 93, 1
            ADVECTIVEFLUXWV(I, J) = (RTRANS(I, J) * VFLD(I, J, K + (-1)
     > , BI, BJ))
          END DO
        END DO
      ELSE
        IF((K .GT. 15) .OR.((K .eq. 1) .AND. RIGIDLID)) THEN
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ADVECTIVEFLUXWV(I, J) = 0.0
            END DO
          END DO
        ELSE
          IF(K .eq. 1) THEN
            DO J = -1, 43, 1
              DO I = -1, 93, 1
                ADVECTIVEFLUXWV(I, J) = (RTRANS(I, J) * VFLD(I, J, K,
     >  BI, BJ))
              END DO
            END DO
          ELSE
            DO J = -1, 43, 1
              DO I = -1, 93, 1
                ADVECTIVEFLUXWV(I, J) = (RTRANS(I, J) * 5.0D-01 *(VFLD(
     > I, J, K, BI, BJ) + VFLD(I, J, K + (-1), BI, BJ)))
              END DO
            END DO
            IF((SELECT_RSTAR .eq. 0) .AND.(.NOT. RIGIDLID)) THEN
              DO J = -1, 43, 1
                DO I = -1, 93, 1
                  ADVECTIVEFLUXWV(I, J) = (ADVECTIVEFLUXWV(I, J) + VFLD
     > (I, J, K, BI, BJ) *(RA(I, J, BI, BJ) * WFLD(I, J, K, BI, BJ) *(
     > MASKC(I, J, K, BI, BJ) - MASKC(I, J, K + (-1), BI, BJ)) + RA(I,
     >  J + (-1), BI, BJ) * WFLD(I, J + (-1), K, BI, BJ) *(MASKC(I, J +
     >  (-1), K, BI, BJ) - MASKC(I, J + (-1), K + (-1), BI, BJ))) *
     >  2.5D-01)
                END DO
              END DO
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_coriolis(BI, BJ, K, UFLD, VCORIOLISTERM, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VCORIOLISTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) ONE
      PARAMETER ( ONE =     1.000000000000000)
C
C     **** Statements ****
C
      IF(USEENERGYCONSERVINGCORIOLIS) THEN
        DO J = -1, 43, 1
          DO I = -2, 92, 1
            VCORIOLISTERM(I, J) = ((FCORI(I, J, BI, BJ) * 5.0D-01 *(
     > UFLD(I, J) + UFLD(I + 1, J)) + FCORI(I, J + (-1), BI, BJ) *
     >  5.0D-01 *(UFLD(I, J + (-1)) + UFLD(I + 1, J + (-1)))) *(
     > -5.0D-01))
          END DO
        END DO
      ELSE
        DO J = -1, 43, 1
          DO I = -2, 92, 1
            VCORIOLISTERM(I, J) = (-((FCORI(I, J, BI, BJ) + FCORI(I, J
     >  + (-1), BI, BJ)) * 5.0D-01 * 2.5D-01 *(UFLD(I + 1, J + (-1)) +
     >  UFLD(I, J + (-1)) + UFLD(I, J) + UFLD(I + 1, J))))
          END DO
        END DO
      ENDIF
      IF(USEJAMARTWETPOINTS) THEN
        DO J = -1, 43, 1
          DO I = -2, 92, 1
            VCORIOLISTERM(I, J) = ((VCORIOLISTERM(I, J) * 4.0D00) / MAX
     > (MASKW(I + 1, J + (-1), K, BI, BJ) + MASKW(I, J + (-1), K, BI,
     >  BJ) + MASKW(I, J, K, BI, BJ) + MASKW(I + 1, J, K, BI, BJ),
     >  1.0D00))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_del2v(BI, BJ, K, VFLD, HFACZ, DEL2V, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2V(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) FMER(-2 : 93, -2 : 43)
      REAL(w2f__8) FZON(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZCLOSEDE
      REAL(w2f__8) HFACZCLOSEDW
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 42, 1
        DO I = -1, 93, 1
          FZON(I, J) = (RECIP_DXV(I, J, BI, BJ) * DYU(I, J, BI, BJ) *
     >  DRF(K) * HFACZ(I, J) *(VFLD(I, J) - VFLD(I + (-1), J)))
        END DO
      END DO
      DO J = -2, 42, 1
        DO I = -1, 92, 1
          FMER(I, J) = (RECIP_DYF(I, J, BI, BJ) * DXF(I, J, BI, BJ) *
     >  DRF(K) * HFACC(I, J, K, BI, BJ) *(VFLD(I, J + 1) - VFLD(I, J)))
        END DO
      END DO
      DO J = -1, 42, 1
        DO I = -1, 92, 1
          DEL2V(I, J) = (MASKS(I, J, K, BI, BJ) * RECIP_RAS(I, J, BI,
     >  BJ) * RECIP_DRF(K) * RECIP_HFACS(I, J, K, BI, BJ) *(FMER(I, J)
     >  + FZON(I + 1, J) - FZON(I, J) - FMER(I, J + (-1))))
        END DO
      END DO
      IF(NO_SLIP_SIDES) THEN
        DO J = -1, 42, 1
          DO I = -1, 92, 1
            HFACZCLOSEDW = HFACS(I, J, K, BI, BJ) - HFACZ(I, J)
            HFACZCLOSEDE = HFACS(I, J, K, BI, BJ) - HFACZ(I + 1, J)
            DEL2V(I, J) = (DEL2V(I, J) - MASKS(I, J, K, BI, BJ) * VFLD(
     > I, J) * DRF(K) * RECIP_RAS(I, J, BI, BJ) * RECIP_DRF(K) *
     >  RECIP_HFACS(I, J, K, BI, BJ) *(RECIP_DXV(I, J, BI, BJ) * DYU(I,
     >  J, BI, BJ) * HFACZCLOSEDW + RECIP_DXV(I + 1, J, BI, BJ) * DYU(I
     >  + 1, J, BI, BJ) * HFACZCLOSEDE) * 2.0D00)
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_metric_cylinder(BI, BJ, K, UFLD, VFLD,
     >  VMETRICTERMS, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VMETRICTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RADIUS
C
C     **** Statements ****
C
      DO J = -1, 43, 1
        DO I = -2, 92, 1
          RADIUS = (YG(I, J, BI, BJ) + YG(I + 1, J, BI, BJ)) * 5.0D-01
          IF(RADIUS .GT. 0.0D00) THEN
            VMETRICTERMS(I, J) = (-(((UFLD(I + 1, J + (-1)) + UFLD(I, J
     >  + (-1)) + UFLD(I, J) + UFLD(I + 1, J)) * 2.5D-01 * 2.5D-01 *(
     > UFLD(I + 1, J + (-1)) + UFLD(I, J + (-1)) + UFLD(I, J) + UFLD(I
     >  + 1, J))) / RADIUS))
          ELSE
            VMETRICTERMS(I, J) = 0.0
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_metric_nh(BI, BJ, K, VFLD, WFLD, VMETRICTERMS,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) WFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VMETRICTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) WVELBOTTOMOVERRIDE
C
C     **** Statements ****
C
      KP1 = MIN(K + 1, 15)
      WVELBOTTOMOVERRIDE = 1.0D00
      IF(K .eq. 15) THEN
        WVELBOTTOMOVERRIDE = 0.0D00
      ENDIF
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          VMETRICTERMS(I, J) = (GRAVITYSIGN * RECIP_HORIVERTRATIO *
     >  VFLD(I, J) * RECIP_RSPHERE * 2.5D-01 *(WFLD(I, J + (-1), K, BI,
     >  BJ) + WFLD(I, J, K, BI, BJ) + WVELBOTTOMOVERRIDE *(WFLD(I, J,
     >  KP1, BI, BJ) + WFLD(I, J + (-1), KP1, BI, BJ))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_metric_sphere(BI, BJ, K, UFLD, VMETRICTERMS,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VMETRICTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 43, 1
        DO I = -2, 92, 1
          VMETRICTERMS(I, J) = (-(TANPHIATV(I, J, BI, BJ) *
     >  RECIP_RSPHERE * 2.5D-01 *(UFLD(I + 1, J + (-1)) + UFLD(I, J + (
     > -1)) + UFLD(I, J) + UFLD(I + 1, J)) * 2.5D-01 *(UFLD(I + 1, J +
     >  (-1)) + UFLD(I, J + (-1)) + UFLD(I, J) + UFLD(I + 1, J))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_xviscflux(BI, BJ, K, VFLD, DEL2V, HFACZ,
     >  XVISCFLUXV, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2V(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) XVISCFLUXV(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -1, 93, 1
          XVISCFLUXV(I, J) = (RECIP_DXV(I, J, BI, BJ) * HFACZ(I, J) *
     >  DRF(K) * DYU(I, J, BI, BJ) *(COSFACV(J, BI, BJ) * VISCA4 *(
     > DEL2V(I, J) - DEL2V(I + (-1), J)) - COSFACV(J, BI, BJ) * VISCAH
     >  *(VFLD(I, J) - VFLD(I + (-1), J))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_yviscflux(BI, BJ, K, VFLD, DEL2V, YVISCFLUXV,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2V(-2 : 93, -2 : 43)
      REAL(w2f__8) YVISCFLUXV(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          YVISCFLUXV(I, J) = (RECIP_DYF(I, J, BI, BJ) * HFACC(I, J, K,
     >  BI, BJ) * DRF(K) * DXF(I, J, BI, BJ) *(VISCA4 *(DEL2V(I, J + 1)
     >  - DEL2V(I, J)) - VISCAH *(VFLD(I, J + 1) - VFLD(I, J))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vecinv(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KUP,
     >  KDOWN, KAPPARU, KAPPARV, FVERU, FVERV, GUDISS, GVDISS, MYTIME,
     >  MYITER, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KUP
      INTEGER(w2f__i4) KDOWN
      REAL(w2f__8) KAPPARU(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) KAPPARV(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) FVERU(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) FVERV(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) GUDISS(-2 : 93, -2 : 43)
      REAL(w2f__8) GVDISS(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) ARDUDRFAC
      REAL(w2f__8) ARDVDRFAC
      LOGICAL(w2f__i4) BOTTOMDRAGTERMS
      EXTERNAL debug_cs_corner_uv
      REAL(w2f__8) DEL2U(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2V(-2 : 93, -2 : 43)
      EXTERNAL different_multiple
      LOGICAL(w2f__i4) different_multiple
      REAL(w2f__8) DSTAR(-2 : 93, -2 : 43)
      REAL(w2f__8) HDIV(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) KE(-2 : 93, -2 : 43)
      EXTERNAL mom_calc_absvort3
      EXTERNAL mom_calc_hdiv
      EXTERNAL mom_calc_hfacz
      EXTERNAL mom_calc_ke
      EXTERNAL mom_calc_relvort3
      EXTERNAL mom_calc_strain
      EXTERNAL mom_calc_tension
      EXTERNAL mom_hdissip
      EXTERNAL mom_u_bottomdrag
      EXTERNAL mom_u_rviscflux
      EXTERNAL mom_u_sidedrag
      EXTERNAL mom_vi_coriolis
      EXTERNAL mom_vi_del2uv
      EXTERNAL mom_vi_hdissip
      EXTERNAL mom_vi_u_coriolis
      EXTERNAL mom_vi_u_coriolis_c4
      EXTERNAL mom_vi_u_grad_ke
      EXTERNAL mom_vi_u_vertshear
      EXTERNAL mom_vi_v_coriolis
      EXTERNAL mom_vi_v_coriolis_c4
      EXTERNAL mom_vi_v_grad_ke
      EXTERNAL mom_vi_v_vertshear
      EXTERNAL mom_v_bottomdrag
      EXTERNAL mom_v_rviscflux
      EXTERNAL mom_v_sidedrag
      REAL(w2f__8) OMEGA3(-2 : 93, -2 : 43)
      REAL(w2f__8) R_HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) STRAIN(-2 : 93, -2 : 43)
      REAL(w2f__8) TENSION(-2 : 93, -2 : 43)
      REAL(w2f__8) UCF(-2 : 93, -2 : 43)
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VCF(-2 : 93, -2 : 43)
      REAL(w2f__8) VF(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VORT3(-2 : 93, -2 : 43)
      REAL(w2f__8) VRF(-2 : 93, -2 : 43)
      LOGICAL(w2f__i4) WRITEDIAG
      EXTERNAL write_local_rl
      REAL(w2f__8) ZSTAR(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
      INTEGER(w2f__i4) doloop_ub11
      INTEGER(w2f__i4) doloop_ub12
      INTEGER(w2f__i4) doloop_ub13
      INTEGER(w2f__i4) doloop_ub14
      INTEGER(w2f__i4) doloop_ub15
      INTEGER(w2f__i4) doloop_ub16
      INTEGER(w2f__i4) doloop_ub17
      INTEGER(w2f__i4) doloop_ub18
      INTEGER(w2f__i4) doloop_ub19
      INTEGER(w2f__i4) doloop_ub20
      INTEGER(w2f__i4) doloop_ub21
      INTEGER(w2f__i4) doloop_ub22
      INTEGER(w2f__i4) doloop_ub23
      INTEGER(w2f__i4) doloop_ub24
      INTEGER(w2f__i4) doloop_ub25
      INTEGER(w2f__i4) doloop_ub26
      INTEGER(w2f__i4) doloop_ub27
      INTEGER(w2f__i4) doloop_ub28
      INTEGER(w2f__i4) doloop_ub29
      INTEGER(w2f__i4) doloop_ub30
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      WRITEDIAG = different_multiple(DIAGFREQ, MYTIME, DELTATCLOCK)
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          VF(I, J) = 0.0
          VRF(I, J) = 0.0
          UCF(I, J) = 0.0
          VCF(I, J) = 0.0
          DEL2U(I, J) = 0.0
          DEL2V(I, J) = 0.0
          DSTAR(I, J) = 0.0
          ZSTAR(I, J) = 0.0
          GUDISS(I, J) = 0.0
          GVDISS(I, J) = 0.0
          VORT3(I, J) = 0.0
          OMEGA3(I, J) = 0.0
          KE(I, J) = 0.0
          STRAIN(I, J) = 0.0D00
          TENSION(I, J) = 0.0D00
        END DO
      END DO
      ARDUDRFAC = VFFACMOM
      ARDVDRFAC = VFFACMOM
      IF((BOTTOMDRAGLINEAR .ne. 0.0D00) .OR.(NO_SLIP_BOTTOM .OR.(
     > BOTTOMDRAGQUADRATIC .ne. 0.0D00))) THEN
        BOTTOMDRAGTERMS = .TRUE.
      ELSE
        BOTTOMDRAGTERMS = .FALSE.
      ENDIF
      CALL mom_calc_hfacz(BI, BJ, K, HFACZ, R_HFACZ, MYTHID)
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          UFLD(I, J) = UVEL(I, J, K, BI, BJ)
          VFLD(I, J) = VVEL(I, J, K, BI, BJ)
        END DO
      END DO
      CALL mom_calc_ke(BI, BJ, K, (2), UFLD, VFLD, KE, MYTHID)
      CALL mom_calc_hdiv(BI, BJ, K, (2), UFLD, VFLD, HDIV, MYTHID)
      CALL mom_calc_relvort3(BI, BJ, K, UFLD, VFLD, HFACZ, VORT3,
     >  MYTHID)
      IF(USEABSVORTICITY) THEN
        CALL mom_calc_absvort3(BI, BJ, K, VORT3, OMEGA3, MYTHID)
      ENDIF
      IF(MOMVISCOSITY) THEN
        IF((VISCC4LEITHD .ne. 0.0D00) .OR.((VISCC4LEITH .ne. 0.0D00)
     >  .OR.((VISCA4GRID .ne. 0.0D00) .OR.((VISCA4Z .ne. 0.0D00) .OR.((
     > VISCA4D .ne. 0.0D00) .OR.(NO_SLIP_SIDES .AND.(VISCA4 .ne. 0.0D00
     > ))))))) THEN
          CALL mom_vi_del2uv(BI, BJ, K, HDIV, VORT3, HFACZ, DEL2U,
     >  DEL2V, MYTHID)
          CALL mom_calc_hdiv(BI, BJ, K, (2), DEL2U, DEL2V, DSTAR,
     >  MYTHID)
          CALL mom_calc_relvort3(BI, BJ, K, DEL2U, DEL2V, HFACZ, ZSTAR,
     >  MYTHID)
        ENDIF
        IF((VISCC4LEITHD .ne. 0.0D00) .OR.((VISCC2LEITHD .ne. 0.0D00)
     >  .OR.((VISCC4LEITH .ne. 0.0D00) .OR.((VISCC2LEITH .ne. 0.0D00)
     >  .OR.((VISCA4GRID .ne. 0.0D00) .OR.((VISCAHGRID .ne. 0.0D00)
     >  .OR.((VISCA4Z .ne. 0.0D00) .OR.((VISCA4D .ne. 0.0D00) .OR.((
     > VISCAHD .ne. 0.0D00) .OR.(VISCAHZ .ne. 0.0D00)))))))))) THEN
          CALL mom_vi_hdissip(BI, BJ, K, HDIV, VORT3, HFACZ, DSTAR,
     >  ZSTAR, GUDISS, GVDISS, MYTHID)
        ENDIF
        IF((VISCC2SMAG .ne. 0.0D00) .OR.((VISCASTRAIN .ne. 0.0D00) .OR.
     > (VISCATENSION .ne. 0.0D00))) THEN
          CALL mom_calc_tension(BI, BJ, K, UFLD, VFLD, TENSION, MYTHID)
          CALL mom_calc_strain(BI, BJ, K, UFLD, VFLD, HFACZ, STRAIN,
     >  MYTHID)
          CALL mom_hdissip(BI, BJ, K, TENSION, STRAIN, HFACZ,
     >  VISCATENSION, VISCASTRAIN, GUDISS, GVDISS, MYTHID)
        ENDIF
      ENDIF
      IF(MOMVISCOSITY .AND.(.NOT. IMPLICITVISCOSITY)) THEN
        CALL mom_u_rviscflux(BI, BJ, (K + 1), UVEL, KAPPARU, VRF,
     >  MYTHID)
        doloop_ub3 = JMAX
        DO J = JMIN, doloop_ub3, 1
          doloop_ub4 = IMAX
          DO I = IMIN, doloop_ub4, 1
            FVERU(I, J, KDOWN) = (VRF(I, J) * ARDUDRFAC)
          END DO
        END DO
        DO J = -1, 42, 1
          DO I = -1, 92, 1
            GUDISS(I, J) = (GUDISS(I, J) - RKSIGN * RECIP_RAW(I, J, BI,
     >  BJ) * RECIP_DRF(K) * RECIP_HFACW(I, J, K, BI, BJ) *(FVERU(I, J,
     >  KDOWN) - FVERU(I, J, KUP)))
          END DO
        END DO
      ENDIF
      IF(MOMVISCOSITY .AND. NO_SLIP_SIDES) THEN
        CALL mom_u_sidedrag(BI, BJ, K, UFLD, DEL2U, HFACZ, VF, MYTHID)
        doloop_ub5 = JMAX
        DO J = JMIN, doloop_ub5, 1
          doloop_ub6 = IMAX
          DO I = IMIN, doloop_ub6, 1
            GUDISS(I, J) = (GUDISS(I, J) + VF(I, J))
          END DO
        END DO
      ENDIF
      IF(BOTTOMDRAGTERMS .AND. MOMVISCOSITY) THEN
        CALL mom_u_bottomdrag(BI, BJ, K, UFLD, KE, KAPPARU, VF, MYTHID)
        doloop_ub7 = JMAX
        DO J = JMIN, doloop_ub7, 1
          doloop_ub8 = IMAX
          DO I = IMIN, doloop_ub8, 1
            GUDISS(I, J) = (GUDISS(I, J) + VF(I, J))
          END DO
        END DO
      ENDIF
      IF(MOMVISCOSITY .AND.(.NOT. IMPLICITVISCOSITY)) THEN
        CALL mom_v_rviscflux(BI, BJ, (K + 1), VVEL, KAPPARV, VRF,
     >  MYTHID)
        doloop_ub9 = JMAX
        DO J = JMIN, doloop_ub9, 1
          doloop_ub10 = IMAX
          DO I = IMIN, doloop_ub10, 1
            FVERV(I, J, KDOWN) = (VRF(I, J) * ARDVDRFAC)
          END DO
        END DO
        doloop_ub11 = JMAX
        DO J = JMIN, doloop_ub11, 1
          doloop_ub12 = IMAX
          DO I = IMIN, doloop_ub12, 1
            GVDISS(I, J) = (GVDISS(I, J) - RKSIGN * RECIP_RAS(I, J, BI,
     >  BJ) * RECIP_DRF(K) * RECIP_HFACS(I, J, K, BI, BJ) *(FVERV(I, J,
     >  KDOWN) - FVERV(I, J, KUP)))
          END DO
        END DO
      ENDIF
      IF(MOMVISCOSITY .AND. NO_SLIP_SIDES) THEN
        CALL mom_v_sidedrag(BI, BJ, K, VFLD, DEL2V, HFACZ, VF, MYTHID)
        doloop_ub13 = JMAX
        DO J = JMIN, doloop_ub13, 1
          doloop_ub14 = IMAX
          DO I = IMIN, doloop_ub14, 1
            GVDISS(I, J) = (GVDISS(I, J) + VF(I, J))
          END DO
        END DO
      ENDIF
      IF(BOTTOMDRAGTERMS .AND. MOMVISCOSITY) THEN
        CALL mom_v_bottomdrag(BI, BJ, K, VFLD, KE, KAPPARV, VF, MYTHID)
        doloop_ub15 = JMAX
        DO J = JMIN, doloop_ub15, 1
          doloop_ub16 = IMAX
          DO I = IMIN, doloop_ub16, 1
            GVDISS(I, J) = (GVDISS(I, J) + VF(I, J))
          END DO
        END DO
      ENDIF
      IF(USECORIOLIS .AND.(.NOT.(USECDSCHEME .OR.(MOMADVECTION .AND.
     >  USEABSVORTICITY)))) THEN
        IF(USEABSVORTICITY) THEN
          CALL mom_vi_u_coriolis(BI, BJ, K, VFLD, OMEGA3, HFACZ,
     >  R_HFACZ, UCF, MYTHID)
          CALL mom_vi_v_coriolis(BI, BJ, K, UFLD, OMEGA3, HFACZ,
     >  R_HFACZ, VCF, MYTHID)
        ELSE
          CALL mom_vi_coriolis(BI, BJ, K, UFLD, VFLD, HFACZ, R_HFACZ,
     >  UCF, VCF, MYTHID)
        ENDIF
        doloop_ub17 = JMAX
        DO J = JMIN, doloop_ub17, 1
          doloop_ub18 = IMAX
          DO I = IMIN, doloop_ub18, 1
            GU(I, J, K, BI, BJ) = UCF(I, J)
            GV(I, J, K, BI, BJ) = VCF(I, J)
          END DO
        END DO
        IF(WRITEDIAG) THEN
          IF(SNAPSHOT_MDSIO) THEN
            CALL write_local_rl('fV', 'I10', (1), UCF, BI, BJ, K,
     >  MYITER, MYTHID)
            CALL write_local_rl('fU', 'I10', (1), VCF, BI, BJ, K,
     >  MYITER, MYTHID)
          ENDIF
        ENDIF
      ELSE
        doloop_ub19 = JMAX
        DO J = JMIN, doloop_ub19, 1
          doloop_ub20 = IMAX
          DO I = IMIN, doloop_ub20, 1
            GU(I, J, K, BI, BJ) = 0.0D00
            GV(I, J, K, BI, BJ) = 0.0D00
          END DO
        END DO
      ENDIF
      IF(MOMADVECTION) THEN
        IF(HIGHORDERVORTICITY .AND. USEABSVORTICITY) THEN
          CALL mom_vi_u_coriolis_c4(BI, BJ, K, VFLD, OMEGA3, R_HFACZ,
     >  UCF, MYTHID)
        ELSE
          IF(HIGHORDERVORTICITY) THEN
            CALL mom_vi_u_coriolis_c4(BI, BJ, K, VFLD, VORT3, R_HFACZ,
     >  UCF, MYTHID)
          ELSE
            IF(USEABSVORTICITY) THEN
              CALL mom_vi_u_coriolis(BI, BJ, K, VFLD, OMEGA3, HFACZ,
     >  R_HFACZ, UCF, MYTHID)
            ELSE
              CALL mom_vi_u_coriolis(BI, BJ, K, VFLD, VORT3, HFACZ,
     >  R_HFACZ, UCF, MYTHID)
            ENDIF
          ENDIF
        ENDIF
        doloop_ub21 = JMAX
        DO J = JMIN, doloop_ub21, 1
          doloop_ub22 = IMAX
          DO I = IMIN, doloop_ub22, 1
            GU(I, J, K, BI, BJ) = (UCF(I, J) + GU(I, J, K, BI, BJ))
          END DO
        END DO
        IF(HIGHORDERVORTICITY .AND. USEABSVORTICITY) THEN
          CALL mom_vi_v_coriolis_c4(BI, BJ, K, UFLD, OMEGA3, R_HFACZ,
     >  VCF, MYTHID)
        ELSE
          IF(HIGHORDERVORTICITY) THEN
            CALL mom_vi_v_coriolis_c4(BI, BJ, K, UFLD, VORT3, R_HFACZ,
     >  VCF, MYTHID)
          ELSE
            IF(USEABSVORTICITY) THEN
              CALL mom_vi_v_coriolis(BI, BJ, K, UFLD, OMEGA3, HFACZ,
     >  R_HFACZ, VCF, MYTHID)
            ELSE
              CALL mom_vi_v_coriolis(BI, BJ, K, UFLD, VORT3, HFACZ,
     >  R_HFACZ, VCF, MYTHID)
            ENDIF
          ENDIF
        ENDIF
        doloop_ub23 = JMAX
        DO J = JMIN, doloop_ub23, 1
          doloop_ub24 = IMAX
          DO I = IMIN, doloop_ub24, 1
            GV(I, J, K, BI, BJ) = (VCF(I, J) + GV(I, J, K, BI, BJ))
          END DO
        END DO
        IF(WRITEDIAG) THEN
          IF(SNAPSHOT_MDSIO) THEN
            CALL write_local_rl('zV', 'I10', (1), UCF, BI, BJ, K,
     >  MYITER, MYTHID)
            CALL write_local_rl('zU', 'I10', (1), VCF, BI, BJ, K,
     >  MYITER, MYTHID)
          ENDIF
        ENDIF
        IF(.NOT. MOMIMPLVERTADV) THEN
          CALL mom_vi_u_vertshear(BI, BJ, K, UVEL, WVEL, UCF, MYTHID)
          doloop_ub25 = JMAX
          DO J = JMIN, doloop_ub25, 1
            doloop_ub26 = IMAX
            DO I = IMIN, doloop_ub26, 1
              GU(I, J, K, BI, BJ) = (UCF(I, J) + GU(I, J, K, BI, BJ))
            END DO
          END DO
          CALL mom_vi_v_vertshear(BI, BJ, K, VVEL, WVEL, VCF, MYTHID)
          doloop_ub27 = JMAX
          DO J = JMIN, doloop_ub27, 1
            doloop_ub28 = IMAX
            DO I = IMIN, doloop_ub28, 1
              GV(I, J, K, BI, BJ) = (VCF(I, J) + GV(I, J, K, BI, BJ))
            END DO
          END DO
        ENDIF
        CALL mom_vi_u_grad_ke(BI, BJ, K, KE, UCF, MYTHID)
        doloop_ub29 = JMAX
        DO J = JMIN, doloop_ub29, 1
          doloop_ub30 = IMAX
          DO I = IMIN, doloop_ub30, 1
            GU(I, J, K, BI, BJ) = (UCF(I, J) + GU(I, J, K, BI, BJ))
          END DO
        END DO
        CALL mom_vi_v_grad_ke(BI, BJ, K, KE, VCF, MYTHID)
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            GV(I, J, K, BI, BJ) = (VCF(I, J) + GV(I, J, K, BI, BJ))
          END DO
        END DO
        IF(WRITEDIAG) THEN
          IF(SNAPSHOT_MDSIO) THEN
            CALL write_local_rl('KEx', 'I10', (1), UCF, BI, BJ, K,
     >  MYITER, MYTHID)
            CALL write_local_rl('KEy', 'I10', (1), VCF, BI, BJ, K,
     >  MYITER, MYTHID)
          ENDIF
        ENDIF
      ENDIF
      doloop_ub1 = JMAX
      DO J = JMIN, doloop_ub1, 1
        doloop_ub2 = IMAX
        DO I = IMIN, doloop_ub2, 1
          GU(I, J, K, BI, BJ) = (GU(I, J, K, BI, BJ) * MASKW(I, J, K,
     >  BI, BJ))
          GV(I, J, K, BI, BJ) = (GV(I, J, K, BI, BJ) * MASKS(I, J, K,
     >  BI, BJ))
        END DO
      END DO
      IF(USECUBEDSPHEREEXCHANGE .AND.((MYITER .eq. NITER0) .AND.((K
     >  .eq. 4) .AND.(DEBUGLEVEL .GE. 2)))) THEN
        CALL debug_cs_corner_uv(' uDiss,vDiss from MOM_VECINV', GUDISS,
     >  GVDISS, K, STANDARDMESSAGEUNIT, BI, BJ, MYTHID)
      ENDIF
      IF(WRITEDIAG) THEN
        IF(SNAPSHOT_MDSIO) THEN
          CALL write_local_rl('Ds', 'I10', (1), STRAIN, BI, BJ, K,
     >  MYITER, MYTHID)
          CALL write_local_rl('Dt', 'I10', (1), TENSION, BI, BJ, K,
     >  MYITER, MYTHID)
          CALL write_local_rl('Du', 'I10', (1), GUDISS, BI, BJ, K,
     >  MYITER, MYTHID)
          CALL write_local_rl('Dv', 'I10', (1), GVDISS, BI, BJ, K,
     >  MYITER, MYTHID)
          CALL write_local_rl('Z3', 'I10', (1), VORT3, BI, BJ, K,
     >  MYITER, MYTHID)
          CALL write_local_rl('W3', 'I10', (1), OMEGA3, BI, BJ, K,
     >  MYITER, MYTHID)
          CALL write_local_rl('KE', 'I10', (1), KE, BI, BJ, K, MYITER,
     >  MYTHID)
          CALL write_local_rl('D', 'I10', (1), HDIV, BI, BJ, K, MYITER,
     >  MYTHID)
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_coriolis(BI, BJ, K, UFLD, VFLD, HFACZ, R_HFACZ,
     >  UCORIOLISTERM, VCORIOLISTERM, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) R_HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) UCORIOLISTERM(-2 : 93, -2 : 43)
      REAL(w2f__8) VCORIOLISTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) EPSIL
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) UBARXY
      REAL(w2f__8) VBARXY
C
C     **** Statements ****
C
      EPSIL = 1.00000000000000006228D-09
      IF(USEJAMARTWETPOINTS) THEN
        DO J = -2, 42, 1
          DO I = -1, 93, 1
            VBARXY = (HFACS(I, J, K, BI, BJ) * VFLD(I, J) * DXG(I, J,
     >  BI, BJ) + HFACS(I, J + 1, K, BI, BJ) * VFLD(I, J + 1) * DXG(I,
     >  J + 1, BI, BJ) + HFACS(I + (-1), J, K, BI, BJ) * VFLD(I + (-1),
     >  J) * DXG(I + (-1), J, BI, BJ) + HFACS(I + (-1), J + 1, K, BI,
     >  BJ) * VFLD(I + (-1), J + 1) * DXG(I + (-1), J + 1, BI, BJ)) /
     >  MAX(EPSIL, HFACS(I + (-1), J + 1, K, BI, BJ) + HFACS(I, J + 1,
     >  K, BI, BJ) + HFACS(I, J, K, BI, BJ) + HFACS(I + (-1), J, K, BI,
     >  BJ))
            UCORIOLISTERM(I, J) = (MASKW(I, J, K, BI, BJ) * RECIP_DXC(I
     > , J, BI, BJ) * VBARXY *(FCORIG(I, J, BI, BJ) + FCORIG(I, J + 1,
     >  BI, BJ)) * 5.0D-01)
          END DO
        END DO
      ELSE
        DO J = -2, 42, 1
          DO I = -1, 93, 1
            VBARXY = (VFLD(I, J) * DXG(I, J, BI, BJ) + VFLD(I, J + 1) *
     >  DXG(I, J + 1, BI, BJ) + VFLD(I + (-1), J) * DXG(I + (-1), J, BI
     > , BJ) + VFLD(I + (-1), J + 1) * DXG(I + (-1), J + 1, BI, BJ)) *
     >  2.5D-01
            UCORIOLISTERM(I, J) = (MASKW(I, J, K, BI, BJ) * RECIP_DXC(I
     > , J, BI, BJ) * VBARXY *(FCORIG(I, J, BI, BJ) + FCORIG(I, J + 1,
     >  BI, BJ)) * 5.0D-01)
          END DO
        END DO
      ENDIF
      IF(USEJAMARTWETPOINTS) THEN
        DO J = -1, 43, 1
          DO I = -2, 92, 1
            UBARXY = (HFACW(I, J, K, BI, BJ) * UFLD(I, J) * DYG(I, J,
     >  BI, BJ) + HFACW(I, J + (-1), K, BI, BJ) * UFLD(I, J + (-1)) *
     >  DYG(I, J + (-1), BI, BJ) + HFACW(I + 1, J, K, BI, BJ) * UFLD(I
     >  + 1, J) * DYG(I + 1, J, BI, BJ) + HFACW(I + 1, J + (-1), K, BI,
     >  BJ) * UFLD(I + 1, J + (-1)) * DYG(I + 1, J + (-1), BI, BJ)) /
     >  MAX(EPSIL, HFACW(I + 1, J + (-1), K, BI, BJ) + HFACW(I + 1, J,
     >  K, BI, BJ) + HFACW(I, J, K, BI, BJ) + HFACW(I, J + (-1), K, BI,
     >  BJ))
            VCORIOLISTERM(I, J) = (-(MASKS(I, J, K, BI, BJ) * RECIP_DYC
     > (I, J, BI, BJ) * UBARXY *(FCORIG(I, J, BI, BJ) + FCORIG(I + 1, J
     > , BI, BJ)) * 5.0D-01))
          END DO
        END DO
      ELSE
        DO J = -1, 43, 1
          DO I = -2, 92, 1
            UBARXY = (UFLD(I, J) * DYG(I, J, BI, BJ) + UFLD(I, J + (-1)
     > ) * DYG(I, J + (-1), BI, BJ) + UFLD(I + 1, J) * DYG(I + 1, J, BI
     > , BJ) + UFLD(I + 1, J + (-1)) * DYG(I + 1, J + (-1), BI, BJ)) *
     >  2.5D-01
            VCORIOLISTERM(I, J) = (-(MASKS(I, J, K, BI, BJ) * RECIP_DYC
     > (I, J, BI, BJ) * UBARXY *(FCORIG(I, J, BI, BJ) + FCORIG(I + 1, J
     > , BI, BJ)) * 5.0D-01))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_del2uv(BI, BJ, K, HDIV, VORT3, HFACZ, DEL2U,
     >  DEL2V, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) HDIV(-2 : 93, -2 : 43)
      REAL(w2f__8) VORT3(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2U(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2V(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) DIJ
      REAL(w2f__8) DIM
      REAL(w2f__8) DMJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      LOGICAL(w2f__i4) NORTHEASTCORNER
      LOGICAL(w2f__i4) NORTHWESTCORNER
      LOGICAL(w2f__i4) SOUTHEASTCORNER
      LOGICAL(w2f__i4) SOUTHWESTCORNER
      REAL(w2f__8) UDIJ
      REAL(w2f__8) ZIJ
      REAL(w2f__8) ZIP
      REAL(w2f__8) ZPJ
C
C     **** Statements ****
C
      IF(USECUBEDSPHEREEXCHANGE) THEN
        SOUTHWESTCORNER = .TRUE.
        SOUTHEASTCORNER = .TRUE.
        NORTHWESTCORNER = .TRUE.
        NORTHEASTCORNER = .TRUE.
      ENDIF
      DO J = -1, 42, 1
        DO I = -1, 92, 1
          DIM = HDIV(I, J + (-1))
          DIJ = HDIV(I, J)
          DMJ = HDIV(I + (-1), J)
          ZIP = VORT3(I, J + 1) * HFACZ(I, J + 1)
          ZIJ = VORT3(I, J) * HFACZ(I, J)
          ZPJ = VORT3(I + 1, J) * HFACZ(I + 1, J)
          UDIJ = DIJ
          IF(USECUBEDSPHEREEXCHANGE) THEN
            IF((J .eq. 0) .AND.((I .eq. 1) .AND. SOUTHWESTCORNER)) THEN
              DMJ = HDIV(0, 1)
            ENDIF
            IF((J .eq. 1) .AND.((I .eq. 0) .AND. SOUTHWESTCORNER)) THEN
              DIM = HDIV(1, 0)
            ENDIF
            IF((J .eq. 41) .AND.((I .eq. 1) .AND. NORTHWESTCORNER))
     >  THEN
              DMJ = HDIV(0, 40)
            ENDIF
            IF((J .eq. 41) .AND.((I .eq. 0) .AND. NORTHWESTCORNER))
     >  THEN
              DIJ = HDIV(1, 41)
            ENDIF
            IF((J .eq. 0) .AND.((I .eq. 91) .AND. SOUTHEASTCORNER))
     >  THEN
              UDIJ = HDIV(91, 1)
            ENDIF
            IF((J .eq. 1) .AND.((I .eq. 91) .AND. SOUTHEASTCORNER))
     >  THEN
              DIM = HDIV(90, 0)
            ENDIF
            IF((J .eq. 41) .AND.((I .eq. 91) .AND. NORTHEASTCORNER))
     >  THEN
              UDIJ = HDIV(91, 40)
              DIJ = HDIV(90, 41)
            ENDIF
          ENDIF
          DEL2U(I, J) = (RECIP_DXC(I, J, BI, BJ) *(UDIJ - DMJ) -
     >  RECIP_DYG(I, J, BI, BJ) * RECIP_HFACW(I, J, K, BI, BJ) *(ZIP -
     >  ZIJ))
          DEL2V(I, J) = (RECIP_DXG(I, J, BI, BJ) * RECIP_HFACS(I, J, K,
     >  BI, BJ) *(ZPJ - ZIJ) + RECIP_DYC(I, J, BI, BJ) *(DIJ - DIM))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_hdissip(BI, BJ, K, HDIV, VORT3, HFACZ, DSTAR,
     >  ZSTAR, UDISSIP, VDISSIP, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) HDIV(-2 : 93, -2 : 43)
      REAL(w2f__8) VORT3(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) DSTAR(-2 : 93, -2 : 43)
      REAL(w2f__8) ZSTAR(-2 : 93, -2 : 43)
      REAL(w2f__8) UDISSIP(-2 : 93, -2 : 43)
      REAL(w2f__8) VDISSIP(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) ALIN
      REAL(w2f__8) ALINMAX
      REAL(w2f__8) ALINMIN
      REAL(w2f__8) ALTH2
      REAL(w2f__8) ALTH4
      REAL(w2f__8) DIJ
      REAL(w2f__8) DIM
      REAL(w2f__8) DMJ
      REAL(w2f__8) GRDDIV
      REAL(w2f__8) GRDVRT
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) L2
      REAL(w2f__8) L2RDT
      REAL(w2f__8) L3
      REAL(w2f__8) L4
      REAL(w2f__8) L4RDT
      REAL(w2f__8) L5
      REAL(w2f__8) RECIP_DT
      REAL(w2f__8) UD2
      REAL(w2f__8) UD4
      LOGICAL(w2f__i4) USEVARIABLEVISCOSITY
      REAL(w2f__8) VD2
      REAL(w2f__8) VD4
      REAL(w2f__8) VG2
      REAL(w2f__8) VG2MAX
      REAL(w2f__8) VG2MIN
      REAL(w2f__8) VG4
      REAL(w2f__8) VG4MAX
      REAL(w2f__8) VG4MIN
      REAL(w2f__8) VISCA4_D(-2 : 93, -2 : 43)
      REAL(w2f__8) VISCA4_Z(-2 : 93, -2 : 43)
      REAL(w2f__8) VISCAH_D(-2 : 93, -2 : 43)
      REAL(w2f__8) VISCAH_Z(-2 : 93, -2 : 43)
      REAL(w2f__8) ZIJ
      REAL(w2f__8) ZIP
      REAL(w2f__8) ZPJ
      LOGICAL(w2f__i4) t__407
      LOGICAL(w2f__i4) t__408
      LOGICAL(w2f__i4) t__409
      LOGICAL(w2f__i4) t__410
C
C     **** Statements ****
C
      USEVARIABLEVISCOSITY = (VISCC4LEITHD .ne. 0.0D00) .OR.((
     > VISCC4LEITH .ne. 0.0D00) .OR.((VISCC2LEITHD .ne. 0.0D00) .OR.((
     > VISCC2LEITH .ne. 0.0D00) .OR.((VISCA4GRID .ne. 0.0D00) .OR.(
     > VISCAHGRID .ne. 0.0D00)))))
      IF(DELTATMOM .ne. 0.0D00) THEN
        RECIP_DT = 1D00 / DELTATMOM
      ELSE
        RECIP_DT = 0.0D00
      ENDIF
      VG2 = RECIP_DT * VISCAHGRID
      VG2MIN = RECIP_DT * VISCAHGRIDMIN
      VG2MAX = RECIP_DT * VISCAHGRIDMAX
      VG4 = RECIP_DT * VISCA4GRID
      VG4MIN = RECIP_DT * VISCA4GRIDMIN
      VG4MAX = RECIP_DT * VISCA4GRIDMAX
      IF(USEVARIABLEVISCOSITY) THEN
        DO J = -1, 42, 1
          DO I = -1, 92, 1
            L2 = RA(I, J, BI, BJ)
            L3 = (L2 ** 1.5D00)
            L4 = (L2 ** 2)
            L5 = ((L2 ** 2.5D00)) * 1.25D-01
            IF(USEANISOTROPICVISCAGRIDMAX) THEN
              L2RDT = RECIP_DT /(((RECIP_DXF(I, J, BI, BJ) ** 2) +(
     > RECIP_DYF(I, J, BI, BJ) ** 2)) * 2.0D00)
              L4RDT = RECIP_DT /(((RECIP_DXF(I, J, BI, BJ) ** 4) +(
     > RECIP_DYF(I, J, BI, BJ) ** 4)) * 6.0D00 +(((RECIP_DXF(I, J, BI,
     >  BJ) * RECIP_DYF(I, J, BI, BJ)) ** 2)) * 8.0D00)
            ENDIF
            IF(USEFULLLEITH) THEN
              GRDVRT = (((RECIP_DXG(I, J, BI, BJ) *(VORT3(I + 1, J) -
     >  VORT3(I, J))) ** 2) +((RECIP_DYG(I, J, BI, BJ) *(VORT3(I, J + 1
     > ) - VORT3(I, J))) ** 2) +((RECIP_DXG(I, J + 1, BI, BJ) *(VORT3(I
     >  + 1, J + 1) - VORT3(I, J + 1))) ** 2) +((RECIP_DYG(I + 1, J, BI
     > , BJ) *(VORT3(I + 1, J + 1) - VORT3(I + 1, J))) ** 2)) * 2.5D-01
              GRDDIV = (((RECIP_DXG(I, J, BI, BJ) *(HDIV(I + 1, J) -
     >  HDIV(I, J))) ** 2) +((RECIP_DYG(I, J, BI, BJ) *(HDIV(I, J + 1)
     >  - HDIV(I, J))) ** 2) +((RECIP_DXG(I + (-1), J, BI, BJ) *(HDIV(I
     >  + (-1), J) - HDIV(I, J))) ** 2) +((RECIP_DYG(I, J + (-1), BI,
     >  BJ) *(HDIV(I, J + (-1)) - HDIV(I, J))) ** 2)) * 2.5D-01
              t__407 = (GRDDIV *(VISCC2LEITHD ** 2) + GRDVRT *(
     > VISCC2LEITH ** 2)) .ne. 0.0D00
              IF(t__407) THEN
                ALTH2 = L3 * SQRT(GRDDIV *(VISCC2LEITHD ** 2) + GRDVRT
     >  *(VISCC2LEITH ** 2))
              ELSE
                ALTH2 = 0.0D00
              ENDIF
              t__408 = (GRDDIV *(VISCC4LEITHD ** 2) + GRDVRT *(
     > VISCC4LEITH ** 2)) .ne. 0.0D00
              IF(t__408) THEN
                ALTH4 = L5 * SQRT(GRDDIV *(VISCC4LEITHD ** 2) + GRDVRT
     >  *(VISCC4LEITH ** 2))
              ELSE
                ALTH4 = 0.0D00
              ENDIF
            ELSE
              GRDVRT = ABS(RECIP_DXG(I, J, BI, BJ) *(VORT3(I + 1, J) -
     >  VORT3(I, J)))
              GRDVRT = MAX(GRDVRT, ABS(RECIP_DYG(I, J, BI, BJ) *(VORT3(
     > I, J + 1) - VORT3(I, J))))
              GRDVRT = MAX(GRDVRT, ABS(RECIP_DXG(I, J + 1, BI, BJ) *(
     > VORT3(I + 1, J + 1) - VORT3(I, J + 1))))
              GRDVRT = MAX(GRDVRT, ABS(RECIP_DYG(I + 1, J, BI, BJ) *(
     > VORT3(I + 1, J + 1) - VORT3(I + 1, J))))
              GRDDIV = ABS(RECIP_DXG(I, J, BI, BJ) *(HDIV(I + 1, J) -
     >  HDIV(I, J)))
              GRDDIV = MAX(GRDDIV, ABS(RECIP_DYG(I, J, BI, BJ) *(HDIV(I
     > , J + 1) - HDIV(I, J))))
              GRDDIV = MAX(GRDDIV, ABS(RECIP_DXG(I + (-1), J, BI, BJ) *
     > (HDIV(I + (-1), J) - HDIV(I, J))))
              GRDDIV = MAX(GRDDIV, ABS(RECIP_DYG(I, J + (-1), BI, BJ) *
     > (HDIV(I, J + (-1)) - HDIV(I, J))))
              ALTH2 = L3 *(GRDVRT * VISCC2LEITH +(GRDDIV * VISCC2LEITHD
     > ))
              ALTH4 = L5 *(GRDVRT * VISCC4LEITH +(GRDDIV * VISCC4LEITHD
     > ))
            ENDIF
            ALIN = ALTH2 + VISCAHD + L2 * VG2
            VISCAH_D(I, J) = MIN(ALIN, VISCAHMAX)
            IF(USEANISOTROPICVISCAGRIDMAX) THEN
              ALINMAX = L2RDT * VISCAHGRIDMAX
              VISCAH_D(I, J) = MIN(VISCAH_D(I, J), ALINMAX)
            ELSE
              IF(VG2MAX .GT. 0.0D00) THEN
                ALINMAX = L2 * VG2MAX
                VISCAH_D(I, J) = MIN(VISCAH_D(I, J), ALINMAX)
              ENDIF
            ENDIF
            ALINMIN = L2 * VG2MIN
            VISCAH_D(I, J) = MAX(VISCAH_D(I, J), ALINMIN)
            ALIN = ALTH4 + VISCA4D + L4 * VG4
            VISCA4_D(I, J) = MIN(ALIN, VISCA4MAX)
            IF(USEANISOTROPICVISCAGRIDMAX) THEN
              ALINMAX = L4RDT * VISCA4GRIDMAX
              VISCA4_D(I, J) = MIN(VISCA4_D(I, J), ALINMAX)
            ELSE
              IF(VG4MAX .GT. 0.0D00) THEN
                ALINMAX = L4 * VG4MAX
                VISCA4_D(I, J) = MIN(VISCA4_D(I, J), ALINMAX)
              ENDIF
            ENDIF
            ALINMIN = L4 * VG4MIN
            VISCA4_D(I, J) = MAX(VISCA4_D(I, J), ALINMIN)
            L2 = RAZ(I, J, BI, BJ)
            L3 = (L2 ** 1.5D00)
            L4 = (L2 ** 2)
            L5 = ((L2 ** 2.5D00)) * 1.25D-01
            IF(USEANISOTROPICVISCAGRIDMAX) THEN
              L2RDT = RECIP_DT /(((RECIP_DXV(I, J, BI, BJ) ** 2) +(
     > RECIP_DYU(I, J, BI, BJ) ** 2)) * 2.0D00)
              L4RDT = RECIP_DT /(((RECIP_DXV(I, J, BI, BJ) ** 4) +(
     > RECIP_DYU(I, J, BI, BJ) ** 4)) * 6.0D00 +(((RECIP_DXV(I, J, BI,
     >  BJ) * RECIP_DYU(I, J, BI, BJ)) ** 2)) * 8.0D00)
            ENDIF
            IF(USEFULLLEITH) THEN
              GRDVRT = (((RECIP_DXG(I, J, BI, BJ) *(VORT3(I + 1, J) -
     >  VORT3(I, J))) ** 2) +((RECIP_DYG(I, J, BI, BJ) *(VORT3(I, J + 1
     > ) - VORT3(I, J))) ** 2) +((RECIP_DXG(I + (-1), J, BI, BJ) *(
     > VORT3(I + (-1), J) - VORT3(I, J))) ** 2) +((RECIP_DYG(I, J + (-1
     > ), BI, BJ) *(VORT3(I, J + (-1)) - VORT3(I, J))) ** 2)) * 2.5D-01
              GRDDIV = (((RECIP_DXG(I, J, BI, BJ) *(HDIV(I + 1, J) -
     >  HDIV(I, J))) ** 2) +((RECIP_DYG(I, J, BI, BJ) *(HDIV(I, J + 1)
     >  - HDIV(I, J))) ** 2) +((RECIP_DXG(I, J + 1, BI, BJ) *(HDIV(I +
     >  1, J + 1) - HDIV(I, J + 1))) ** 2) +((RECIP_DYG(I + 1, J, BI,
     >  BJ) *(HDIV(I + 1, J + 1) - HDIV(I + 1, J))) ** 2)) * 2.5D-01
              t__409 = (GRDDIV *(VISCC2LEITHD ** 2) + GRDVRT *(
     > VISCC2LEITH ** 2)) .ne. 0.0D00
              IF(t__409) THEN
                ALTH2 = L3 * SQRT(GRDDIV *(VISCC2LEITHD ** 2) + GRDVRT
     >  *(VISCC2LEITH ** 2))
              ELSE
                ALTH2 = 0.0D00
              ENDIF
              t__410 = (GRDDIV *(VISCC4LEITHD ** 2) + GRDVRT *(
     > VISCC4LEITH ** 2)) .ne. 0.0D00
              IF(t__410) THEN
                ALTH4 = L5 * SQRT(GRDDIV *(VISCC4LEITHD ** 2) + GRDVRT
     >  *(VISCC4LEITH ** 2))
              ELSE
                ALTH4 = 0.0D00
              ENDIF
            ELSE
              GRDVRT = ABS(RECIP_DXG(I, J, BI, BJ) *(VORT3(I + 1, J) -
     >  VORT3(I, J)))
              GRDVRT = MAX(GRDVRT, ABS(RECIP_DYG(I, J, BI, BJ) *(VORT3(
     > I, J + 1) - VORT3(I, J))))
              GRDVRT = MAX(GRDVRT, ABS(RECIP_DXG(I + (-1), J, BI, BJ) *
     > (VORT3(I + (-1), J) - VORT3(I, J))))
              GRDVRT = MAX(GRDVRT, ABS(RECIP_DYG(I, J + (-1), BI, BJ) *
     > (VORT3(I, J + (-1)) - VORT3(I, J))))
              GRDDIV = ABS(RECIP_DXG(I, J, BI, BJ) *(HDIV(I + 1, J) -
     >  HDIV(I, J)))
              GRDDIV = MAX(GRDDIV, ABS(RECIP_DYG(I, J, BI, BJ) *(HDIV(I
     > , J + 1) - HDIV(I, J))))
              GRDDIV = MAX(GRDDIV, ABS(RECIP_DXG(I + (-1), J, BI, BJ) *
     > (HDIV(I + 1, J + 1) - HDIV(I, J + 1))))
              GRDDIV = MAX(GRDDIV, ABS(RECIP_DYG(I, J + (-1), BI, BJ) *
     > (HDIV(I + 1, J + 1) - HDIV(I + 1, J))))
              ALTH2 = L3 *(GRDVRT * VISCC2LEITH +(GRDDIV * VISCC2LEITHD
     > ))
              ALTH4 = L5 *(GRDVRT * VISCC4LEITH +(GRDDIV * VISCC4LEITHD
     > ))
            ENDIF
            ALIN = ALTH2 + VISCAHZ + L2 * VG2
            VISCAH_Z(I, J) = MIN(ALIN, VISCAHMAX)
            IF(USEANISOTROPICVISCAGRIDMAX) THEN
              ALINMAX = L2RDT * VISCAHGRIDMAX
              VISCAH_Z(I, J) = MIN(VISCAH_Z(I, J), ALINMAX)
            ELSE
              IF(VG2MAX .GT. 0.0D00) THEN
                ALINMAX = L2 * VG2MAX
                VISCAH_Z(I, J) = MIN(VISCAH_Z(I, J), ALINMAX)
              ENDIF
            ENDIF
            ALINMIN = L2 * VG2MIN
            VISCAH_Z(I, J) = MAX(VISCAH_Z(I, J), ALINMIN)
            ALIN = ALTH4 + VISCA4Z + L4 * VG4
            VISCA4_Z(I, J) = MIN(ALIN, VISCA4MAX)
            IF(USEANISOTROPICVISCAGRIDMAX) THEN
              ALINMAX = L4RDT * VISCA4GRIDMAX
              VISCA4_Z(I, J) = MIN(VISCA4_Z(I, J), ALINMAX)
            ELSE
              IF(VG4MAX .GT. 0.0D00) THEN
                ALINMAX = L4 * VG4MAX
                VISCA4_Z(I, J) = MIN(VISCA4_Z(I, J), ALINMAX)
              ENDIF
            ENDIF
            ALINMIN = L4 * VG4MIN
            VISCA4_Z(I, J) = MAX(VISCA4_Z(I, J), ALINMIN)
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            VISCAH_D(I, J) = VISCAHD
            VISCAH_Z(I, J) = VISCAHZ
            VISCA4_D(I, J) = VISCA4D
            VISCA4_Z(I, J) = VISCA4Z
          END DO
        END DO
      ENDIF
      IF((VISCAHZ .ne. 0.0D00) .OR.((VISCAHD .ne. 0.0D00) .OR.((
     > VISCAHGRID .ne. 0.0D00) .OR.(VISCC2LEITH .ne. 0.0D00)))) THEN
        DO J = -1, 42, 1
          DO I = -1, 92, 1
            DIM = HDIV(I, J + (-1))
            DIJ = HDIV(I, J)
            DMJ = HDIV(I + (-1), J)
            ZIP = VORT3(I, J + 1) * HFACZ(I, J + 1)
            ZIJ = VORT3(I, J) * HFACZ(I, J)
            ZPJ = VORT3(I + 1, J) * HFACZ(I + 1, J)
            IF(USEVARIABLEVISCOSITY) THEN
              DIJ = VISCAH_D(I, J) * DIJ
              DIM = VISCAH_D(I, J + (-1)) * DIM
              DMJ = VISCAH_D(I + (-1), J) * DMJ
              ZIJ = VISCAH_Z(I, J) * ZIJ
              ZIP = VISCAH_Z(I, J + 1) * ZIP
              ZPJ = VISCAH_Z(I + 1, J) * ZPJ
              UD2 = (RECIP_DXC(I, J, BI, BJ) * COSFACU(J, BI, BJ) *(DIJ
     >  - DMJ) - RECIP_DYG(I, J, BI, BJ) * RECIP_HFACW(I, J, K, BI, BJ)
     >  *(ZIP - ZIJ))
              VD2 = (COSFACV(J, BI, BJ) * RECIP_DXG(I, J, BI, BJ) *
     >  RECIP_HFACS(I, J, K, BI, BJ) *(ZPJ - ZIJ) + RECIP_DYC(I, J, BI,
     >  BJ) *(DIJ - DIM))
            ELSE
              UD2 = RECIP_DXC(I, J, BI, BJ) * COSFACU(J, BI, BJ) *
     >  VISCAHD *(DIJ - DMJ) - RECIP_DYG(I, J, BI, BJ) * RECIP_HFACW(I,
     >  J, K, BI, BJ) * VISCAHZ *(ZIP - ZIJ)
              VD2 = RECIP_DXG(I, J, BI, BJ) * COSFACV(J, BI, BJ) *
     >  RECIP_HFACS(I, J, K, BI, BJ) * VISCAHZ *(ZPJ - ZIJ) + RECIP_DYC
     > (I, J, BI, BJ) * VISCAHD *(DIJ - DIM)
            ENDIF
            UDISSIP(I, J) = UD2
            VDISSIP(I, J) = VD2
          END DO
        END DO
      ELSE
        DO J = -1, 42, 1
          DO I = -1, 92, 1
            UDISSIP(I, J) = 0.0
            VDISSIP(I, J) = 0.0
          END DO
        END DO
      ENDIF
      IF((VISCA4Z .ne. 0.0D00) .OR.((VISCA4D .ne. 0.0D00) .OR.((
     > VISCA4GRID .ne. 0.0D00) .OR.(VISCC4LEITH .ne. 0.0D00)))) THEN
        DO J = -1, 42, 1
          DO I = -1, 92, 1
            DIM = DSTAR(I, J + (-1))
            DIJ = DSTAR(I, J)
            DMJ = DSTAR(I + (-1), J)
            ZIP = HFACZ(I, J + 1) * ZSTAR(I, J + 1)
            ZIJ = HFACZ(I, J) * ZSTAR(I, J)
            ZPJ = HFACZ(I + 1, J) * ZSTAR(I + 1, J)
            IF(USEVARIABLEVISCOSITY) THEN
              DIJ = VISCA4_D(I, J) * DIJ
              DIM = VISCA4_D(I, J + (-1)) * DIM
              DMJ = VISCA4_D(I + (-1), J) * DMJ
              ZIJ = VISCA4_Z(I, J) * ZIJ
              ZIP = VISCA4_Z(I, J + 1) * ZIP
              ZPJ = VISCA4_Z(I + 1, J) * ZPJ
              UD4 = (RECIP_DXC(I, J, BI, BJ) * COSFACU(J, BI, BJ) *(DIJ
     >  - DMJ) - RECIP_DYG(I, J, BI, BJ) * RECIP_HFACW(I, J, K, BI, BJ)
     >  *(ZIP - ZIJ))
              VD4 = (COSFACV(J, BI, BJ) * RECIP_DXG(I, J, BI, BJ) *
     >  RECIP_HFACS(I, J, K, BI, BJ) *(ZPJ - ZIJ) + RECIP_DYC(I, J, BI,
     >  BJ) *(DIJ - DIM))
            ELSE
              UD4 = RECIP_DXC(I, J, BI, BJ) * COSFACU(J, BI, BJ) *
     >  VISCA4D *(DIJ - DMJ) - RECIP_DYG(I, J, BI, BJ) * RECIP_HFACW(I,
     >  J, K, BI, BJ) * VISCA4Z *(ZIP - ZIJ)
              VD4 = RECIP_DXG(I, J, BI, BJ) * COSFACV(J, BI, BJ) *
     >  RECIP_HFACS(I, J, K, BI, BJ) * VISCA4Z *(ZPJ - ZIJ) + RECIP_DYC
     > (I, J, BI, BJ) * VISCA4D *(DIJ - DIM)
            ENDIF
            UDISSIP(I, J) = (UDISSIP(I, J) - UD4)
            VDISSIP(I, J) = (VDISSIP(I, J) - VD4)
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_u_coriolis(BI, BJ, K, VFLD, OMEGA3, HFACZ,
     >  R_HFACZ, UCORIOLISTERM, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) OMEGA3(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) R_HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) UCORIOLISTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) EPSIL
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      LOGICAL(w2f__i4) USE_ORIGINAL_HFAC
      PARAMETER ( USE_ORIGINAL_HFAC = .FALSE.)
      REAL(w2f__8) VBARXY
      REAL(w2f__8) VORT3U
      REAL(w2f__8) ZM
      REAL(w2f__8) ZP
C
C     **** Statements ****
C
      EPSIL = 1.00000000000000006228D-09
      DO J = -2, 42, 1
        DO I = -1, 93, 1
          IF(.FALSE.) THEN
            VBARXY = (HFACS(I, J, K, BI, BJ) * VFLD(I, J) * DXG(I, J,
     >  BI, BJ) + HFACS(I, J + 1, K, BI, BJ) * VFLD(I, J + 1) * DXG(I,
     >  J + 1, BI, BJ) + HFACS(I + (-1), J, K, BI, BJ) * VFLD(I + (-1),
     >  J) * DXG(I + (-1), J, BI, BJ) + HFACS(I + (-1), J + 1, K, BI,
     >  BJ) * VFLD(I + (-1), J + 1) * DXG(I + (-1), J + 1, BI, BJ)) *
     >  2.5D-01
            IF(UPWINDVORTICITY) THEN
              IF(VBARXY .GT. 0.0D00) THEN
                VORT3U = OMEGA3(I, J) * R_HFACZ(I, J)
              ELSE
                VORT3U = OMEGA3(I, J + 1) * R_HFACZ(I, J + 1)
              ENDIF
            ELSE
              VORT3U = (OMEGA3(I, J) * R_HFACZ(I, J) + OMEGA3(I, J + 1)
     >  * R_HFACZ(I, J + 1)) * 5.0D-01
            ENDIF
          ELSE
            IF(SADOURNYCORIOLIS) THEN
              ZM = (HFACS(I, J, K, BI, BJ) * VFLD(I, J) * DXG(I, J, BI,
     >  BJ) + HFACS(I + (-1), J, K, BI, BJ) * VFLD(I + (-1), J) * DXG(I
     >  + (-1), J, BI, BJ)) * 5.0D-01
              ZP = (HFACS(I, J + 1, K, BI, BJ) * VFLD(I, J + 1) * DXG(I
     > , J + 1, BI, BJ) + HFACS(I + (-1), J + 1, K, BI, BJ) * VFLD(I +
     >  (-1), J + 1) * DXG(I + (-1), J + 1, BI, BJ)) * 5.0D-01
              IF(UPWINDVORTICITY) THEN
                IF((ZM + ZP) .GT. 0.0D00) THEN
                  VORT3U = OMEGA3(I, J) * R_HFACZ(I, J) * ZM
                ELSE
                  VORT3U = OMEGA3(I, J + 1) * R_HFACZ(I, J + 1) * ZP
                ENDIF
              ELSE
                ZM = OMEGA3(I, J) * R_HFACZ(I, J) * ZM
                ZP = OMEGA3(I, J + 1) * R_HFACZ(I, J + 1) * ZP
                VORT3U = (ZM + ZP) * 5.0D-01
              ENDIF
              VBARXY = 1.0D00
            ELSE
              VBARXY = ((HFACZ(I, J) * VFLD(I, J) * DXG(I, J, BI, BJ) +
     >  HFACZ(I, J) * VFLD(I + (-1), J) * DXG(I + (-1), J, BI, BJ) +
     >  HFACZ(I, J + 1) * VFLD(I, J + 1) * DXG(I, J + 1, BI, BJ) +
     >  HFACZ(I, J + 1) * VFLD(I + (-1), J + 1) * DXG(I + (-1), J + 1,
     >  BI, BJ)) * 5.0D-01) / MAX(EPSIL, HFACZ(I, J) + HFACZ(I, J + 1))
              IF(UPWINDVORTICITY) THEN
                IF(VBARXY .GT. 0.0D00) THEN
                  VORT3U = OMEGA3(I, J)
                ELSE
                  VORT3U = OMEGA3(I, J + 1)
                ENDIF
              ELSE
                VORT3U = (OMEGA3(I, J) + OMEGA3(I, J + 1)) * 5.0D-01
              ENDIF
            ENDIF
          ENDIF
          IF(USEJAMARTMOMADV) THEN
            VBARXY = (HFACW(I, J, K, BI, BJ) * VBARXY * 4.0D00) / MAX(
     > EPSIL, HFACS(I + (-1), J + 1, K, BI, BJ) + HFACS(J, I + 1, K, BI
     > , BJ) + HFACS(I, J, K, BI, BJ) + HFACS(I + (-1), J, K, BI, BJ))
          ENDIF
          UCORIOLISTERM(I, J) = (MASKW(I, J, K, BI, BJ) * RECIP_DXC(I,
     >  J, BI, BJ) * VBARXY * VORT3U)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_u_coriolis_c4(BI, BJ, K, VFLD, OMEGA3, R_HFACZ,
     >  UCORIOLISTERM, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) OMEGA3(-2 : 93, -2 : 43)
      REAL(w2f__8) R_HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) UCORIOLISTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      LOGICAL(w2f__i4) FOURTHVORT3
      PARAMETER ( FOURTHVORT3 = .TRUE.)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) ONESIXTH
      PARAMETER ( ONESIXTH =    0.1666666666666667)
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      LOGICAL(w2f__i4) UPWINDVORT3
      PARAMETER ( UPWINDVORT3 = .FALSE.)
      REAL(w2f__8) VBARXM
      REAL(w2f__8) VBARXP
      REAL(w2f__8) VBARXY
      REAL(w2f__8) VORT3U
C
C     **** Statements ****
C
      DO J = 1, 40, 1
        DO I = 1, 91, 1
          IF(SADOURNYCORIOLIS) THEN
            VBARXY = 1.0D00
            VBARXM = (HFACS(I, J, K, BI, BJ) * VFLD(I, J) * DXG(I, J,
     >  BI, BJ) + HFACS(I + (-1), J, K, BI, BJ) * VFLD(I + (-1), J) *
     >  DXG(I + (-1), J, BI, BJ)) * 5.0D-01
            VBARXP = (HFACS(I, J + 1, K, BI, BJ) * VFLD(I, J + 1) * DXG
     > (I, J + 1, BI, BJ) + HFACS(I + (-1), J + 1, K, BI, BJ) * VFLD(I
     >  + (-1), J + 1) * DXG(I + (-1), J + 1, BI, BJ)) * 5.0D-01
            IF(UPWINDVORTICITY) THEN
              IF((VBARXM + VBARXP) .GT. 0.0D00) THEN
                VORT3U = OMEGA3(I, J) * R_HFACZ(I, J) * VBARXM
              ELSE
                VORT3U = OMEGA3(I, J + 1) * R_HFACZ(I, J + 1) * VBARXP
              ENDIF
            ELSE
              IF(.TRUE.) THEN
                RJP = OMEGA3(I, J + 1) * R_HFACZ(I, J + 1) -(OMEGA3(I,
     >  J + 2) * R_HFACZ(I, J + 2) - OMEGA3(I, J) * R_HFACZ(I, J)) *
     >  1.66666666666666657415D-01
                RJM = OMEGA3(I, J) * R_HFACZ(I, J) +(OMEGA3(I, J + 1) *
     >  R_HFACZ(I, J + 1) - OMEGA3(I, J + (-1)) * R_HFACZ(I, J + (-1)))
     >  * 1.66666666666666657415D-01
                VORT3U = (RJM * VBARXM + RJP * VBARXP) * 5.0D-01
              ELSE
                VORT3U = (OMEGA3(I, J) * R_HFACZ(I, J) * VBARXM +
     >  OMEGA3(I, J + 1) * R_HFACZ(I, J + 1) * VBARXP) * 5.0D-01
              ENDIF
            ENDIF
          ELSE
            VBARXY = (HFACS(I, J, K, BI, BJ) * VFLD(I, J) * DXG(I, J,
     >  BI, BJ) + HFACS(I, J + 1, K, BI, BJ) * VFLD(I, J + 1) * DXG(I,
     >  J + 1, BI, BJ) + HFACS(I + (-1), J, K, BI, BJ) * VFLD(I + (-1),
     >  J) * DXG(I + (-1), J, BI, BJ) + HFACS(I + (-1), J + 1, K, BI,
     >  BJ) * VFLD(I + (-1), J + 1) * DXG(I + (-1), J + 1, BI, BJ)) *
     >  2.5D-01
            IF(.FALSE.) THEN
              IF(VBARXY .GT. 0.0D00) THEN
                VORT3U = OMEGA3(I, J) * R_HFACZ(I, J)
              ELSE
                VORT3U = OMEGA3(I, J + 1) * R_HFACZ(I, J + 1)
              ENDIF
            ELSE
              IF(.TRUE.) THEN
                RJP = OMEGA3(I, J + 2) * R_HFACZ(I, J + 2) - OMEGA3(I,
     >  J + 1) * R_HFACZ(I, J + 1)
                RJM = OMEGA3(I, J) * R_HFACZ(I, J) - OMEGA3(I, J + (-1)
     > ) * R_HFACZ(I, J + (-1))
                VORT3U = (OMEGA3(I, J) * R_HFACZ(I, J) + OMEGA3(I, J +
     >  1) * R_HFACZ(I, J + 1) -(RJP - RJM) *
     >  8.33333358168601989746D-02) * 5.0D-01
              ELSE
                VORT3U = (OMEGA3(I, J) * R_HFACZ(I, J) + OMEGA3(I, J +
     >  1) * R_HFACZ(I, J + 1)) * 5.0D-01
              ENDIF
            ENDIF
          ENDIF
          UCORIOLISTERM(I, J) = (MASKW(I, J, K, BI, BJ) * RECIP_DXC(I,
     >  J, BI, BJ) * VBARXY * VORT3U)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_u_grad_ke(BI, BJ, K, KE, DKEDX, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) KE(-2 : 93, -2 : 43)
      REAL(w2f__8) DKEDX(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -1, 93, 1
          DKEDX(I, J) = (-(MASKW(I, J, K, BI, BJ) * RECIP_DXC(I, J, BI,
     >  BJ) *(KE(I, J) - KE(I + (-1), J))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_u_vertshear(BI, BJ, K, UFLD, WFLD, USHEARTERM,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) USHEARTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) MASK_KM1
      REAL(w2f__8) MASK_KP1
      REAL(w2f__8) UZM
      REAL(w2f__8) UZP
      REAL(w2f__8) WBARXM
      REAL(w2f__8) WBARXP
C
C     **** Statements ****
C
      KP1 = MIN(K + 1, 15)
      MASK_KP1 = 1.0D00
      IF(K .eq. 15) THEN
        MASK_KP1 = 0.0D00
      ENDIF
      KM1 = MAX(K +(-1), 1)
      MASK_KM1 = 1.0D00
      IF(K .eq. 1) THEN
        MASK_KM1 = 0.0D00
      ENDIF
      DO J = -2, 43, 1
        DO I = -1, 93, 1
          WBARXM = MASK_KM1 *(MASKC(I, J, KM1, BI, BJ) * RA(I, J, BI,
     >  BJ) * WFLD(I, J, K, BI, BJ) + MASKC(I + (-1), J, KM1, BI, BJ) *
     >  RA(I + (-1), J, BI, BJ) * WFLD(I + (-1), J, K, BI, BJ)) *
     >  5.0D-01
          WBARXP = MASK_KP1 *(RA(I, J, BI, BJ) * WFLD(I, J, KP1, BI, BJ
     > ) + RA(I + (-1), J, BI, BJ) * WFLD(I + (-1), J, KP1, BI, BJ)) *
     >  5.0D-01
          UZM = RKSIGN *(UFLD(I, J, K, BI, BJ) - UFLD(I, J, KM1, BI, BJ
     > ) * MASK_KM1)
          UZP = RKSIGN *(UFLD(I, J, KP1, BI, BJ) * MASK_KP1 - UFLD(I, J
     > , K, BI, BJ))
          IF(UPWINDSHEAR) THEN
            USHEARTERM(I, J) = (-(RECIP_DRF(K) * RECIP_HFACW(I, J, K,
     >  BI, BJ) * RECIP_RAW(I, J, BI, BJ) *((UZM * WBARXM + UZP *
     >  WBARXP) +(UZP * ABS(WBARXP) - UZM * ABS(WBARXM))) * 5.0D-01))
          ELSE
            USHEARTERM(I, J) = (-(RECIP_DRF(K) * RECIP_HFACW(I, J, K,
     >  BI, BJ) * RECIP_RAW(I, J, BI, BJ) *(UZM * WBARXM + UZP * WBARXP
     > ) * 5.0D-01))
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_v_coriolis(BI, BJ, K, UFLD, OMEGA3, HFACZ,
     >  R_HFACZ, VCORIOLISTERM, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) OMEGA3(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) R_HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) VCORIOLISTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) EPSIL
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) UBARXY
      LOGICAL(w2f__i4) USE_ORIGINAL_HFAC
      PARAMETER ( USE_ORIGINAL_HFAC = .FALSE.)
      REAL(w2f__8) VORT3V
      REAL(w2f__8) ZM
      REAL(w2f__8) ZP
C
C     **** Statements ****
C
      EPSIL = 1.00000000000000006228D-09
      DO J = -1, 43, 1
        DO I = -2, 92, 1
          IF(.FALSE.) THEN
            UBARXY = (HFACW(I, J, K, BI, BJ) * UFLD(I, J) * DYG(I, J,
     >  BI, BJ) + HFACW(I + 1, J, K, BI, BJ) * UFLD(I + 1, J) * DYG(I +
     >  1, J, BI, BJ) + HFACW(I, J + (-1), K, BI, BJ) * UFLD(I, J + (-1
     > )) * DYG(I, J + (-1), BI, BJ) + HFACW(I + 1, J + (-1), K, BI, BJ
     > ) * UFLD(I + 1, J + (-1)) * DYG(I + 1, J + (-1), BI, BJ)) *
     >  2.5D-01
            IF(UPWINDVORTICITY) THEN
              IF(UBARXY .GT. 0.0D00) THEN
                VORT3V = OMEGA3(I, J) * R_HFACZ(I, J)
              ELSE
                VORT3V = OMEGA3(I + 1, J) * R_HFACZ(I + 1, J)
              ENDIF
            ELSE
              VORT3V = (OMEGA3(I, J) * R_HFACZ(I, J) + OMEGA3(I + 1, J)
     >  * R_HFACZ(I + 1, J)) * 5.0D-01
            ENDIF
          ELSE
            IF(SADOURNYCORIOLIS) THEN
              ZM = (HFACW(I, J, K, BI, BJ) * UFLD(I, J) * DYG(I, J, BI,
     >  BJ) + HFACW(I, J + (-1), K, BI, BJ) * UFLD(I, J + (-1)) * DYG(I
     > , J + (-1), BI, BJ)) * 5.0D-01
              ZP = (HFACW(I + 1, J, K, BI, BJ) * UFLD(I + 1, J) * DYG(I
     >  + 1, J, BI, BJ) + HFACW(I + 1, J + (-1), K, BI, BJ) * UFLD(I +
     >  1, J + (-1)) * DYG(I + 1, J + (-1), BI, BJ)) * 5.0D-01
              IF(UPWINDVORTICITY) THEN
                IF((ZM + ZP) .GT. 0.0D00) THEN
                  VORT3V = OMEGA3(I, J) * R_HFACZ(I, J) * ZM
                ELSE
                  VORT3V = OMEGA3(I + 1, J) * R_HFACZ(I + 1, J) * ZP
                ENDIF
              ELSE
                ZM = OMEGA3(I, J) * R_HFACZ(I, J) * ZM
                ZP = OMEGA3(I + 1, J) * R_HFACZ(I + 1, J) * ZP
                VORT3V = (ZM + ZP) * 5.0D-01
              ENDIF
              UBARXY = 1.0D00
            ELSE
              UBARXY = ((HFACZ(I, J) * UFLD(I, J) * DYG(I, J, BI, BJ) +
     >  HFACZ(I, J) * UFLD(I, J + (-1)) * DYG(I, J + (-1), BI, BJ) +
     >  HFACZ(I + 1, J) * UFLD(I + 1, J) * DYG(I + 1, J, BI, BJ) +
     >  HFACZ(I + 1, J) * UFLD(I + 1, J + (-1)) * DYG(I + 1, J + (-1),
     >  BI, BJ)) * 5.0D-01) / MAX(EPSIL, HFACZ(I, J) + HFACZ(I + 1, J))
              IF(UPWINDVORTICITY) THEN
                IF(UBARXY .GT. 0.0D00) THEN
                  VORT3V = OMEGA3(I, J)
                ELSE
                  VORT3V = OMEGA3(I + 1, J)
                ENDIF
              ELSE
                VORT3V = (OMEGA3(I, J) + OMEGA3(I + 1, J)) * 5.0D-01
              ENDIF
            ENDIF
          ENDIF
          IF(USEJAMARTMOMADV) THEN
            UBARXY = (HFACS(I, J, K, BI, BJ) * UBARXY * 4.0D00) / MAX(
     > EPSIL, HFACW(I + 1, J + (-1), K, BI, BJ) + HFACW(I + 1, J, K, BI
     > , BJ) + HFACW(I, J, K, BI, BJ) + HFACW(I, J + (-1), K, BI, BJ))
          ENDIF
          VCORIOLISTERM(I, J) = (-(MASKS(I, J, K, BI, BJ) * RECIP_DYC(I
     > , J, BI, BJ) * UBARXY * VORT3V))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_v_coriolis_c4(BI, BJ, K, UFLD, OMEGA3, R_HFACZ,
     >  VCORIOLISTERM, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) OMEGA3(-2 : 93, -2 : 43)
      REAL(w2f__8) R_HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) VCORIOLISTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      LOGICAL(w2f__i4) FOURTHVORT3
      PARAMETER ( FOURTHVORT3 = .TRUE.)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) ONESIXTH
      PARAMETER ( ONESIXTH =    0.1666666666666667)
      REAL(w2f__8) RJM
      REAL(w2f__8) RJP
      REAL(w2f__8) UBARXY
      REAL(w2f__8) UBARYM
      REAL(w2f__8) UBARYP
      LOGICAL(w2f__i4) UPWINDVORT3
      PARAMETER ( UPWINDVORT3 = .FALSE.)
      REAL(w2f__8) VORT3V
C
C     **** Statements ****
C
      DO J = 1, 41, 1
        DO I = 1, 90, 1
          IF(SADOURNYCORIOLIS) THEN
            UBARXY = 1.0D00
            UBARYM = (HFACW(I, J, K, BI, BJ) * UFLD(I, J) * DYG(I, J,
     >  BI, BJ) + HFACW(I, J + (-1), K, BI, BJ) * UFLD(I, J + (-1)) *
     >  DYG(I, J + (-1), BI, BJ)) * 5.0D-01
            UBARYP = (HFACW(I + 1, J, K, BI, BJ) * UFLD(I + 1, J) * DYG
     > (I + 1, J, BI, BJ) + HFACW(I + 1, J + (-1), K, BI, BJ) * UFLD(I
     >  + 1, J + (-1)) * DYG(I + 1, J + (-1), BI, BJ)) * 5.0D-01
            IF(UPWINDVORTICITY) THEN
              IF((UBARYM + UBARYP) .GT. 0.0D00) THEN
                VORT3V = OMEGA3(I, J) * R_HFACZ(I, J) * UBARYM
              ELSE
                VORT3V = OMEGA3(I + 1, J) * R_HFACZ(I + 1, J) * UBARYP
              ENDIF
            ELSE
              IF(.TRUE.) THEN
                RJP = OMEGA3(I + 1, J) * R_HFACZ(I + 1, J) -(OMEGA3(I +
     >  2, J) * R_HFACZ(I + 2, J) - OMEGA3(I, J) * R_HFACZ(I, J)) *
     >  1.66666666666666657415D-01
                RJM = OMEGA3(I, J) * R_HFACZ(I, J) +(OMEGA3(I + 1, J) *
     >  R_HFACZ(I + 1, J) - OMEGA3(I + (-1), J) * R_HFACZ(I + (-1), J))
     >  * 1.66666666666666657415D-01
                VORT3V = (RJM * UBARYM + RJP * UBARYP) * 5.0D-01
              ELSE
                VORT3V = (OMEGA3(I, J) * R_HFACZ(I, J) * UBARYM +
     >  OMEGA3(I + 1, J) * R_HFACZ(I + 1, J) * UBARYP) * 5.0D-01
              ENDIF
            ENDIF
          ELSE
            UBARXY = (HFACW(I, J, K, BI, BJ) * UFLD(I, J) * DYG(I, J,
     >  BI, BJ) + HFACW(I + 1, J, K, BI, BJ) * UFLD(I + 1, J) * DYG(I +
     >  1, J, BI, BJ) + HFACW(I, J + (-1), K, BI, BJ) * UFLD(I, J + (-1
     > )) * DYG(I, J + (-1), BI, BJ) + HFACW(I + 1, J + (-1), K, BI, BJ
     > ) * UFLD(I + 1, J + (-1)) * DYG(I + 1, J + (-1), BI, BJ)) *
     >  2.5D-01
            IF(.FALSE.) THEN
              IF(UBARXY .GT. 0.0D00) THEN
                VORT3V = OMEGA3(I, J) * R_HFACZ(I, J)
              ELSE
                VORT3V = OMEGA3(I + 1, J) * R_HFACZ(I + 1, J)
              ENDIF
            ELSE
              IF(.TRUE.) THEN
                RJP = OMEGA3(I + 2, J) * R_HFACZ(I + 2, J) - OMEGA3(I +
     >  1, J) * R_HFACZ(I + 1, J)
                RJM = OMEGA3(I, J) * R_HFACZ(I, J) - OMEGA3(I + (-1), J
     > ) * R_HFACZ(I + (-1), J)
                VORT3V = (OMEGA3(I, J) * R_HFACZ(I, J) + OMEGA3(I + 1,
     >  J) * R_HFACZ(I + 1, J) -(RJP - RJM) *
     >  8.33333358168601989746D-02) * 5.0D-01
              ELSE
                VORT3V = (OMEGA3(I, J) * R_HFACZ(I, J) + OMEGA3(I + 1,
     >  J) * R_HFACZ(I + 1, J)) * 5.0D-01
              ENDIF
            ENDIF
          ENDIF
          VCORIOLISTERM(I, J) = (-(MASKS(I, J, K, BI, BJ) * RECIP_DYC(I
     > , J, BI, BJ) * UBARXY * VORT3V))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_v_grad_ke(BI, BJ, K, KE, DKEDY, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) KE(-2 : 93, -2 : 43)
      REAL(w2f__8) DKEDY(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          DKEDY(I, J) = (-(MASKS(I, J, K, BI, BJ) * RECIP_DYC(I, J, BI,
     >  BJ) *(KE(I, J) - KE(I, J + (-1)))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_vi_v_vertshear(BI, BJ, K, VFLD, WFLD, VSHEARTERM,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VSHEARTERM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KP1
      REAL(w2f__8) MASK_KM1
      REAL(w2f__8) MASK_KP1
      REAL(w2f__8) VZM
      REAL(w2f__8) VZP
      REAL(w2f__8) WBARYM
      REAL(w2f__8) WBARYP
C
C     **** Statements ****
C
      KP1 = MIN(K + 1, 15)
      MASK_KP1 = 1.0D00
      IF(K .eq. 15) THEN
        MASK_KP1 = 0.0D00
      ENDIF
      KM1 = MAX(K +(-1), 1)
      MASK_KM1 = 1.0D00
      IF(K .eq. 1) THEN
        MASK_KM1 = 0.0D00
      ENDIF
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          WBARYM = MASK_KM1 *(MASKC(I, J, KM1, BI, BJ) * RA(I, J, BI,
     >  BJ) * WFLD(I, J, K, BI, BJ) + MASKC(I, J + (-1), KM1, BI, BJ) *
     >  RA(I, J + (-1), BI, BJ) * WFLD(I, J + (-1), K, BI, BJ)) *
     >  5.0D-01
          WBARYP = MASK_KP1 *(RA(I, J, BI, BJ) * WFLD(I, J, KP1, BI, BJ
     > ) + RA(I, J + (-1), BI, BJ) * WFLD(I, J + (-1), KP1, BI, BJ)) *
     >  5.0D-01
          VZM = RKSIGN *(VFLD(I, J, K, BI, BJ) - VFLD(I, J, KM1, BI, BJ
     > ) * MASK_KM1)
          VZP = RKSIGN *(VFLD(I, J, KP1, BI, BJ) * MASK_KP1 - VFLD(I, J
     > , K, BI, BJ))
          IF(UPWINDSHEAR) THEN
            VSHEARTERM(I, J) = (-(RECIP_DRF(K) * RECIP_HFACS(I, J, K,
     >  BI, BJ) * RECIP_RAS(I, J, BI, BJ) *((VZM * WBARYM + VZP *
     >  WBARYP) +(VZP * ABS(WBARYP) - VZM * ABS(WBARYM))) * 5.0D-01))
          ELSE
            VSHEARTERM(I, J) = (-(RECIP_DRF(K) * RECIP_HFACS(I, J, K,
     >  BI, BJ) * RECIP_RAS(I, J, BI, BJ) *(VZM * WBARYM + VZP * WBARYP
     > ) * 5.0D-01))
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_calc_absvort3(BI, BJ, K, VORT3, OMEGA3, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VORT3(-2 : 93, -2 : 43)
      REAL(w2f__8) OMEGA3(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) NONLINFAC
      REAL(w2f__8) USECORIOLISFAC
C
C     **** Statements ****
C
      IF(MOMADVECTION) THEN
        NONLINFAC = 1.0D00
      ELSE
        NONLINFAC = 0.0D00
      ENDIF
      IF(USECORIOLIS) THEN
        USECORIOLISFAC = 1.0D00
      ELSE
        USECORIOLISFAC = 0.0D00
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          OMEGA3(I, J) = (VORT3(I, J) * NONLINFAC + FCORIG(I, J, BI, BJ
     > ) * USECORIOLISFAC)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_calc_hdiv(BI, BJ, K, HDIVSCHEME, UFLD, VFLD, HDIV,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) HDIVSCHEME
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) HDIV(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF(HDIVSCHEME .eq. 1) THEN
        DO J = -2, 42, 1
          DO I = -2, 92, 1
            HDIV(I, J) = (RECIP_RA(I, J, BI, BJ) *(VFLD(I, J + 1) * DXG
     > (I, J + 1, BI, BJ) + UFLD(I + 1, J) * DYG(I + 1, J, BI, BJ) -
     >  UFLD(I, J) * DYG(I, J, BI, BJ) - VFLD(I, J) * DXG(I, J, BI, BJ)
     > ))
          END DO
        END DO
      ELSE
        IF(HDIVSCHEME .eq. 2) THEN
          DO J = -2, 42, 1
            DO I = -2, 92, 1
              HDIV(I, J) = (RECIP_HFACC(I, J, K, BI, BJ) * RECIP_RA(I,
     >  J, BI, BJ) *(HFACS(I, J + 1, K, BI, BJ) * VFLD(I, J + 1) * DXG(
     > I, J + 1, BI, BJ) + HFACW(I + 1, J, K, BI, BJ) * UFLD(I + 1, J)
     >  * DYG(I + 1, J, BI, BJ) - HFACW(I, J, K, BI, BJ) * UFLD(I, J) *
     >  DYG(I, J, BI, BJ) - HFACS(I, J, K, BI, BJ) * VFLD(I, J) * DXG(I
     > , J, BI, BJ)))
            END DO
          END DO
        ELSE
          STOP 'S/R MOM_CALC_HDIV: We should never reach this po' //
     >  'int!'
          RETURN
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_calc_hfacz(BI, BJ, K, HFACZ, R_HFACZ, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) R_HFACZ(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) HFACZOPEN
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO I = -2, 93, 1
        HFACZ(I, (-2)) = 0.0
        R_HFACZ(I, (-2)) = 0.0
      END DO
      DO J = -1, 43, 1
        HFACZ((-2), J) = 0.0
        R_HFACZ((-2), J) = 0.0
        DO I = -1, 93, 1
          HFACZOPEN = MIN(HFACW(I, J, K, BI, BJ), HFACW(I, J + (-1), K,
     >  BI, BJ))
          HFACZOPEN = MIN(HFACS(I, J, K, BI, BJ), HFACZOPEN)
          HFACZOPEN = MIN(HFACS(I + (-1), J, K, BI, BJ), HFACZOPEN)
          HFACZ(I, J) = HFACZOPEN
          IF(HFACZ(I, J) .eq. 0.0D00) THEN
            R_HFACZ(I, J) = 0.0
          ELSE
            R_HFACZ(I, J) = 1D00 / (HFACZ(I, J))
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_calc_ke(BI, BJ, K, KESCHEME, UFLD, VFLD, KE,
     >  MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KESCHEME
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) KE(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF(KESCHEME .eq. 1) THEN
        DO J = -2, 42, 1
          DO I = -2, 92, 1
            KE(I, J) = ((((UFLD(I, J) + UFLD(I + 1, J)) ** 2) +((VFLD(I
     > , J) + VFLD(I, J + 1)) ** 2)) * 1.25D-01)
          END DO
        END DO
      ELSE
        IF(KESCHEME .eq. 2) THEN
          DO J = -2, 42, 1
            DO I = -2, 92, 1
              KE(I, J) = ((UFLD(I, J) * UFLD(I, J) + UFLD(I + 1, J) *
     >  UFLD(I + 1, J) + VFLD(I, J) * VFLD(I, J) + VFLD(I, J + 1) *
     >  VFLD(I, J + 1)) * 2.5D-01)
            END DO
          END DO
        ELSE
          IF(KESCHEME .eq. 3) THEN
            DO J = -2, 42, 1
              DO I = -2, 92, 1
                KE(I, J) = (RECIP_HFACC(I, J, K, BI, BJ) *(HFACW(I, J,
     >  K, BI, BJ) * UFLD(I, J) * UFLD(I, J) + HFACW(I + 1, J, K, BI,
     >  BJ) * UFLD(I + 1, J) * UFLD(I + 1, J) + HFACS(I, J, K, BI, BJ)
     >  * VFLD(I, J) * VFLD(I, J) + HFACS(I, J + 1, K, BI, BJ) * VFLD(I
     > , J + 1) * VFLD(I, J + 1)) * 2.5D-01)
              END DO
            END DO
          ELSE
            IF(KESCHEME .eq. 4) THEN
              DO J = -2, 42, 1
                DO I = -2, 92, 1
                  KE(I, J) = (RECIP_RA(I, J, BI, BJ) * RECIP_HFACC(I, J
     > , K, BI, BJ) *(RAW(I, J, BI, BJ) * HFACW(I, J, K, BI, BJ) * UFLD
     > (I, J) * UFLD(I, J) + RAW(I + 1, J, BI, BJ) * HFACW(I + 1, J, K,
     >  BI, BJ) * UFLD(I + 1, J) * UFLD(I + 1, J) + RAS(I, J, BI, BJ) *
     >  HFACS(I, J, K, BI, BJ) * VFLD(I, J) * VFLD(I, J) + RAS(I, J + 1
     > , BI, BJ) * HFACS(I, J + 1, K, BI, BJ) * VFLD(I, J + 1) * VFLD(I
     > , J + 1)) * 2.5D-01)
                END DO
              END DO
            ELSE
              STOP 'S/R MOM_CALC_KE: We should never reach this poin'
     >  // 't!'
              RETURN
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_calc_relvort3(BI, BJ, K, UFLD, VFLD, HFACZ, VORT3,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) VORT3(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      LOGICAL(w2f__i4) NORTHEASTCORNER
      LOGICAL(w2f__i4) NORTHWESTCORNER
      LOGICAL(w2f__i4) SOUTHEASTCORNER
      LOGICAL(w2f__i4) SOUTHWESTCORNER
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          VORT3(I, J) = 0.0D00
        END DO
      END DO
      DO J = -1, 43, 1
        DO I = -1, 93, 1
          VORT3(I, J) = (RECIP_RAZ(I, J, BI, BJ) *(UFLD(I, J + (-1)) *
     >  DXC(I, J + (-1), BI, BJ) + VFLD(I, J) * DYC(I, J, BI, BJ) -
     >  VFLD(I + (-1), J) * DYC(I + (-1), J, BI, BJ) - UFLD(I, J) * DXC
     > (I, J, BI, BJ)))
          IF(HFACZ(I, J) .ne. 0.0D00) THEN
          ELSE
            VORT3(I, J) = 0.0
          ENDIF
        END DO
      END DO
      IF(USECUBEDSPHEREEXCHANGE) THEN
        SOUTHWESTCORNER = .FALSE.
        SOUTHEASTCORNER = .FALSE.
        NORTHWESTCORNER = .FALSE.
        NORTHEASTCORNER = .FALSE.
        SOUTHWESTCORNER = .TRUE.
        SOUTHEASTCORNER = .TRUE.
        NORTHWESTCORNER = .TRUE.
        NORTHEASTCORNER = .TRUE.
        IF(SOUTHWESTCORNER) THEN
          I = 1
          J = 1
          VORT3(I, J) = (RECIP_RAZ(I, J, BI, BJ) *(UFLD(I, J + (-1)) *
     >  DXC(I, J + (-1), BI, BJ) + VFLD(I, J) * DYC(I, J, BI, BJ) -
     >  UFLD(I, J) * DXC(I, J, BI, BJ)))
          IF(HFACZ(I, J) .eq. 0.0D00) THEN
            VORT3(I, J) = 0.0D00
          ENDIF
          VORT3(I + (-1), J) = (MASKS(I, J + (-1), K, BI, BJ) * MASKW(I
     >  + (-1), J, K, BI, BJ) * MASKS(I + (-2), J, K, BI, BJ) * MASKS(I
     >  + (-1), J, K, BI, BJ) * RECIP_RAZ(I + (-1), J, BI, BJ) *(VFLD(I
     > , J + (-1)) * DYC(I, J + (-1), BI, BJ) + VFLD(I + (-1), J) * DYC
     > (I + (-1), J, BI, BJ) - VFLD(I + (-2), J) * DYC(I + (-2), J, BI,
     >  BJ) - UFLD(I + (-1), J) * DXC(I + (-1), J, BI, BJ)))
          VORT3(I, J + (-1)) = VORT3(I + (-1), J)
        ENDIF
        IF(SOUTHEASTCORNER) THEN
          I = 91
          J = 1
          VORT3(I, J) = (RECIP_RAZ(I, J, BI, BJ) *(UFLD(I, J + (-1)) *
     >  DXC(I, J + (-1), BI, BJ) -(UFLD(I, J) * DXC(I, J, BI, BJ) +
     >  VFLD(I + (-1), J) * DYC(I + (-1), J, BI, BJ))))
          IF(HFACZ(I, J) .eq. 0.0D00) THEN
            VORT3(I, J) = 0.0D00
          ENDIF
          VORT3(I + 1, J) = (MASKS(I + (-1), J + (-1), K, BI, BJ) *
     >  MASKW(I + 1, J, K, BI, BJ) * MASKS(I, J, K, BI, BJ) * MASKS(I +
     >  1, J, K, BI, BJ) * RECIP_RAZ(I + 1, J, BI, BJ) *(VFLD(I + 1, J)
     >  * DYC(I + 1, J, BI, BJ) - VFLD(I, J) * DYC(I, J, BI, BJ) - UFLD
     > (I + 1, J) * DXC(I + 1, J, BI, BJ) - VFLD(I + (-1), J + (-1)) *
     >  DYC(I + (-1), J + (-1), BI, BJ)))
          VORT3(I, J + (-1)) = VORT3(I + 1, J)
        ENDIF
        IF(NORTHWESTCORNER) THEN
          I = 1
          J = 41
          VORT3(I, J) = (RECIP_RAZ(I, J, BI, BJ) *(UFLD(I, J + (-1)) *
     >  DXC(I, J + (-1), BI, BJ) + VFLD(I, J) * DYC(I, J, BI, BJ) -
     >  UFLD(I, J) * DXC(I, J, BI, BJ)))
          IF(HFACZ(I, J) .eq. 0.0D00) THEN
            VORT3(I, J) = 0.0D00
          ENDIF
          VORT3(I + (-1), J) = (MASKW(I + (-1), J + (-1), K, BI, BJ) *
     >  MASKS(I, J + 1, K, BI, BJ) * MASKS(I + (-2), J, K, BI, BJ) *
     >  MASKS(I + (-1), J, K, BI, BJ) * RECIP_RAZ(I + (-1), J, BI, BJ)
     >  *(VFLD(I, J + 1) * DYC(I, J + 1, BI, BJ) + VFLD(I + (-1), J) *
     >  DYC(I + (-1), J, BI, BJ) - VFLD(I + (-2), J) * DYC(I + (-2), J,
     >  BI, BJ) + UFLD(I + (-1), J + (-1)) * DXC(I + (-1), J + (-1), BI
     > , BJ)))
          VORT3(I, J + 1) = VORT3(I + (-1), J)
        ENDIF
        IF(NORTHEASTCORNER) THEN
          I = 91
          J = 41
          VORT3(I, J) = (RECIP_RAZ(I, J, BI, BJ) *(UFLD(I, J + (-1)) *
     >  DXC(I, J + (-1), BI, BJ) -(UFLD(I, J) * DXC(I, J, BI, BJ) +
     >  VFLD(I + (-1), J) * DYC(I + (-1), J, BI, BJ))))
          IF(HFACZ(I, J) .eq. 0.0D00) THEN
            VORT3(I, J) = 0.0D00
          ENDIF
          VORT3(I + 1, J) = (MASKW(I + 1, J + (-1), K, BI, BJ) * MASKS(
     > I + (-1), J + 1, K, BI, BJ) * MASKS(I, J, K, BI, BJ) * MASKS(I +
     >  1, J, K, BI, BJ) * RECIP_RAZ(I + 1, J, BI, BJ) *(UFLD(I + 1, J
     >  + (-1)) * DXC(I + 1, J + (-1), BI, BJ) + VFLD(I + 1, J) * DYC(I
     >  + 1, J, BI, BJ) - VFLD(I, J) * DYC(I, J, BI, BJ) - VFLD(I + (-1
     > ), J + 1) * DYC(I + (-1), J + 1, BI, BJ)))
          VORT3(I, J + 1) = VORT3(I + 1, J)
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_calc_strain(BI, BJ, K, UFLD, VFLD, HFACZ, STRAIN,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) STRAIN(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -1, 43, 1
        DO I = -1, 93, 1
          STRAIN(I, J) = (RECIP_RAZ(I, J, BI, BJ) *(UFLD(I, J) * DXC(I,
     >  J, BI, BJ) + VFLD(I, J) * DYC(I, J, BI, BJ) - VFLD(I + (-1), J)
     >  * DYC(I + (-1), J, BI, BJ) - UFLD(I, J + (-1)) * DXC(I, J + (-1
     > ), BI, BJ)))
          IF(HFACZ(I, J) .eq. 0.0D00) THEN
            STRAIN(I, J) = 0.0
          ENDIF
        END DO
      END DO
      IF(USECUBEDSPHEREEXCHANGE) THEN
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_calc_tension(BI, BJ, K, UFLD, VFLD, TENSION,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) TENSION(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          TENSION(I, J) = (RECIP_RA(I, J, BI, BJ) *(VFLD(I, J) * DXG(I,
     >  J, BI, BJ) + UFLD(I + 1, J) * DYG(I + 1, J, BI, BJ) - UFLD(I, J
     > ) * DYG(I, J, BI, BJ) - VFLD(I, J + 1) * DXG(I, J + 1, BI, BJ)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_hdissip(BI, BJ, K, TENSION, STRAIN, HFACZ, VISCAT,
     >  VISCAS, UDISSIP, VDISSIP, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use grid_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) TENSION(-2 : 93, -2 : 43)
      REAL(w2f__8) STRAIN(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) VISCAT
      REAL(w2f__8) VISCAS
      REAL(w2f__8) UDISSIP(-2 : 93, -2 : 43)
      REAL(w2f__8) VDISSIP(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) ALINMAX
      REAL(w2f__8) ALINMIN
      REAL(w2f__8) ASMAG
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) LENA2
      REAL(w2f__8) LENAZ2
      REAL(w2f__8) SMAGFAC
      REAL(w2f__8) VG2MAX
      REAL(w2f__8) VG2MIN
      REAL(w2f__8) VISCA_S(-2 : 93, -2 : 43)
      REAL(w2f__8) VISCA_T(-2 : 93, -2 : 43)
C
C     **** Statements ****
C
      IF(DELTATMOM .ne. 0.0D00) THEN
        VG2MIN = VISCAHGRIDMIN / DELTATMOM
        VG2MAX = VISCAHGRIDMAX / DELTATMOM
      ELSE
        VG2MIN = 0.0D00
        VG2MAX = 0.0D00
      ENDIF
      SMAGFAC = (VISCC2SMAG / 3.141592653589793116D00) ** 2
      DO J = -1, 42, 1
        DO I = -1, 92, 1
          IF(VISCC2SMAG .ne. 0.0D00) THEN
            LENA2 = ((RA(I, J, BI, BJ) * 2.0D00) /(DXF(I, J, BI, BJ) +
     >  DYF(I, J, BI, BJ))) ** 2
            ASMAG = SQRT((TENSION(I, J) ** 2) +((STRAIN(I + 1, J) ** 2)
     >  +(STRAIN(I, J + 1) ** 2) +(STRAIN(I + (-1), J) ** 2) +(STRAIN(I
     > , J + (-1)) ** 2)) * 2.5D-01) * LENA2 * SMAGFAC
            VISCA_T(I, J) = MIN(VISCAHMAX, MAX(VISCAT, ASMAG))
            IF(VG2MAX .GT. 0.0D00) THEN
              ALINMAX = LENA2 * VG2MAX
              VISCA_T(I, J) = MIN(VISCA_T(I, J), ALINMAX)
            ENDIF
            ALINMIN = LENA2 * VG2MIN
            VISCA_T(I, J) = MAX(VISCA_T(I, J), ALINMIN)
            LENAZ2 = ((RAZ(I, J, BI, BJ) * 2.0D00) /(DXV(I, J, BI, BJ)
     >  + DYU(I, J, BI, BJ))) ** 2
            ASMAG = SQRT((STRAIN(I, J) ** 2) +((TENSION(I, J) ** 2) +(
     > TENSION(I, J + 1) ** 2) +(TENSION(I + 1, J) ** 2) +(TENSION(I +
     >  1, J + 1) ** 2)) * 2.5D-01) * LENAZ2 * SMAGFAC
            VISCA_S(I, J) = MIN(VISCAHMAX, MAX(VISCAS, ASMAG))
            IF(VG2MAX .GT. 0.0D00) THEN
              ALINMAX = LENAZ2 * VG2MAX
              VISCA_S(I, J) = MIN(VISCA_S(I, J), ALINMAX)
            ENDIF
            ALINMIN = LENAZ2 * VG2MIN
            VISCA_S(I, J) = MAX(VISCA_S(I, J), ALINMIN)
          ELSE
            VISCA_T(I, J) = VISCAT
            VISCA_S(I, J) = VISCAS
          ENDIF
        END DO
      END DO
      DO J = -1, 42, 1
        DO I = -1, 92, 1
          UDISSIP(I, J) = (RECIP_DXC(I, J, BI, BJ) * RECIP_DYG(I, J, BI
     > , BJ) * RECIP_DYG(I, J, BI, BJ) *(TENSION(I, J) * VISCA_T(I, J)
     >  * DYF(I, J, BI, BJ) * DYF(I, J, BI, BJ) - TENSION(I + (-1), J)
     >  * VISCA_T(I + (-1), J) * DYF(I + (-1), J, BI, BJ) * DYF(I + (-1
     > ), J, BI, BJ)) + RECIP_DYG(I, J, BI, BJ) * RECIP_DXC(I, J, BI,
     >  BJ) * RECIP_DXC(I, J, BI, BJ) *(STRAIN(I, J + 1) * VISCA_S(I, J
     >  + 1) * DXV(I, J + 1, BI, BJ) * DXV(I, J + 1, BI, BJ) - STRAIN(I
     > , J) * VISCA_S(I, J) * DXV(I, J, BI, BJ) * DXV(I, J, BI, BJ)))
          VDISSIP(I, J) = (RECIP_DXG(I, J, BI, BJ) * RECIP_DYC(I, J, BI
     > , BJ) * RECIP_DYC(I, J, BI, BJ) *(STRAIN(I + 1, J) * VISCA_S(I +
     >  1, J) * DYU(I + 1, J, BI, BJ) * DYU(I + 1, J, BI, BJ) - STRAIN(
     > I, J) * VISCA_S(I, J) * DYU(I, J, BI, BJ) * DYU(I, J, BI, BJ)) -
     >  RECIP_DYC(I, J, BI, BJ) * RECIP_DXG(I, J, BI, BJ) * RECIP_DXG(I
     > , J, BI, BJ) *(TENSION(I, J) * VISCA_T(I, J) * DXF(I, J, BI, BJ)
     >  * DXF(I, J, BI, BJ) - TENSION(I, J + (-1)) * VISCA_T(I, J + (-1
     > )) * DXF(I, J + (-1), BI, BJ) * DXF(I, J + (-1), BI, BJ)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_bottomdrag(BI, BJ, K, UFLD, KE, KAPPARU,
     >  UDRAGTERMS, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) KE(-2 : 93, -2 : 43)
      REAL(w2f__8) KAPPARU(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) UDRAGTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KBOTTOM
      INTEGER(w2f__i4) KDOWN
      INTEGER(w2f__i4) KDOWNC
      REAL(w2f__8) MASKDOWN
      REAL(w2f__8) RDRCKP1
      REAL(w2f__8) VISCFAC
C
C     **** Statements ****
C
      IF(USINGZCOORDS) THEN
        KBOTTOM = 15
        KDOWN = MIN(KBOTTOM, K + 1)
        KDOWNC = KDOWN
      ELSE
        KBOTTOM = 1
        KDOWN = MAX(KBOTTOM, K +(-1))
        KDOWNC = K
      ENDIF
      RDRCKP1 = RECIP_DRC(KDOWNC)
      IF(K .eq. KBOTTOM) THEN
        RDRCKP1 = RECIP_DRF(K)
      ENDIF
      VISCFAC = 0.0D00
      IF(NO_SLIP_BOTTOM) THEN
        VISCFAC = 1.0D00
      ENDIF
      DO J = -2, 42, 1
        DO I = -1, 92, 1
          MASKDOWN = MASKW(I, J, KDOWN, BI, BJ)
          IF(K .eq. KBOTTOM) THEN
            MASKDOWN = 0.0D00
          ENDIF
          UDRAGTERMS(I, J) = (-(UFLD(I, J) * RECIP_DRF(K) * RECIP_HFACW
     > (I, J, K, BI, BJ) *(BOTTOMDRAGLINEAR + VISCFAC * RDRCKP1 *
     >  KAPPARU(I, J, KDOWNC) * 2.0D00) *(1.0D00 - MASKDOWN)))
          IF((KE(I, J) + KE(I + (-1), J)) .ne. 0.0D00) THEN
            UDRAGTERMS(I, J) = (UDRAGTERMS(I, J) - UFLD(I, J) * SQRT(KE
     > (I, J) + KE(I + (-1), J)) * BOTTOMDRAGQUADRATIC * RECIP_DRF(K) *
     >  RECIP_HFACW(I, J, K, BI, BJ) *(1.0D00 - MASKDOWN))
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_rviscflux(BI, BJ, K, UFLD, KAPPARU, RVISCFLUXU,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) KAPPARU(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) RVISCFLUXU(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF((K .GT. 15) .OR.(K .LE. 1)) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            RVISCFLUXU(I, J) = 0.0D00
          END DO
        END DO
      ELSE
        DO J = -2, 42, 1
          DO I = -2, 92, 1
            RVISCFLUXU(I, J) = (-(MASKW(I, J, K + (-1), BI, BJ) * MASKW
     > (I, J, K, BI, BJ) * RECIP_DRC(K) * RKSIGN * KAPPARU(I, J, K) *
     >  RAW(I, J, BI, BJ) *(UFLD(I, J, K, BI, BJ) - UFLD(I, J, K + (-1)
     > , BI, BJ))))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_u_sidedrag(BI, BJ, K, UFLD, DEL2U, HFACZ,
     >  UDRAGTERMS, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2U(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) UDRAGTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) A4TMP
      REAL(w2f__8) AHTMP
      REAL(w2f__8) HFACZCLOSEDN
      REAL(w2f__8) HFACZCLOSEDS
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          HFACZCLOSEDS = HFACW(I, J, K, BI, BJ) - HFACZ(I, J)
          HFACZCLOSEDN = HFACW(I, J, K, BI, BJ) - HFACZ(I, J + 1)
          AHTMP = MIN(VISCAHMAX, VISCAH +((RAW(I, J, BI, BJ) *
     >  VISCAHGRID) / DELTATMOM))
          A4TMP = MIN(VISCA4MAX, VISCA4 +((VISCA4GRID *((RAW(I, J, BI,
     >  BJ) ** 2))) / DELTATMOM))
          A4TMP = MIN(A4TMP, (VISCA4GRIDMAX *((RAW(I, J, BI, BJ) ** 2))
     > ) / DELTATMOM)
          A4TMP = MAX(A4TMP, (VISCA4GRIDMIN *((RAW(I, J, BI, BJ) ** 2))
     > ) / DELTATMOM)
          UDRAGTERMS(I, J) = (-(DRF(K) * RECIP_RAW(I, J, BI, BJ) *
     >  RECIP_DRF(K) * RECIP_HFACW(I, J, K, BI, BJ) *(RECIP_DYU(I, J,
     >  BI, BJ) * DXV(I, J, BI, BJ) * HFACZCLOSEDS + RECIP_DYU(I, J + 1
     > , BI, BJ) * DXV(I, J + 1, BI, BJ) * HFACZCLOSEDN) * 2.0D00 *(
     > UFLD(I, J) * AHTMP - DEL2U(I, J) * A4TMP)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_bottomdrag(BI, BJ, K, VFLD, KE, KAPPARV,
     >  VDRAGTERMS, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) KE(-2 : 93, -2 : 43)
      REAL(w2f__8) KAPPARV(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) VDRAGTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KBOTTOM
      INTEGER(w2f__i4) KDOWN
      INTEGER(w2f__i4) KDOWNC
      REAL(w2f__8) MASKDOWN
      REAL(w2f__8) RDRCKP1
      REAL(w2f__8) VISCFAC
C
C     **** Statements ****
C
      IF(USINGZCOORDS) THEN
        KBOTTOM = 15
        KDOWN = MIN(KBOTTOM, K + 1)
        KDOWNC = KDOWN
      ELSE
        KBOTTOM = 1
        KDOWN = MAX(KBOTTOM, K +(-1))
        KDOWNC = K
      ENDIF
      RDRCKP1 = RECIP_DRC(KDOWNC)
      VISCFAC = 0.0D00
      IF(NO_SLIP_BOTTOM) THEN
        VISCFAC = 1.0D00
      ENDIF
      IF(K .eq. KBOTTOM) THEN
        RDRCKP1 = RECIP_DRF(K)
      ENDIF
      DO J = -1, 42, 1
        DO I = -2, 92, 1
          MASKDOWN = MASKS(I, J, KDOWN, BI, BJ)
          IF(K .eq. KBOTTOM) THEN
            MASKDOWN = 0.0D00
          ENDIF
          VDRAGTERMS(I, J) = (-(VFLD(I, J) * RECIP_DRF(K) * RECIP_HFACS
     > (I, J, K, BI, BJ) *(BOTTOMDRAGLINEAR + VISCFAC * RDRCKP1 *
     >  KAPPARV(I, J, KDOWNC) * 2.0D00) *(1.0D00 - MASKDOWN)))
          IF((KE(I, J) + KE(I, J + (-1))) .ne. 0.0D00) THEN
            VDRAGTERMS(I, J) = (VDRAGTERMS(I, J) - VFLD(I, J) * SQRT(KE
     > (I, J) + KE(I, J + (-1))) * BOTTOMDRAGQUADRATIC * RECIP_DRF(K) *
     >  RECIP_HFACS(I, J, K, BI, BJ) *(1.0D00 - MASKDOWN))
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_rviscflux(BI, BJ, K, VFLD, KAPPARV, RVISCFLUXV,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) KAPPARV(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) RVISCFLUXV(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF((K .GT. 15) .OR.(K .LE. 1)) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            RVISCFLUXV(I, J) = 0.0D00
          END DO
        END DO
      ELSE
        DO J = -2, 42, 1
          DO I = -2, 92, 1
            RVISCFLUXV(I, J) = (-(MASKS(I, J, K + (-1), BI, BJ) * MASKS
     > (I, J, K, BI, BJ) * RECIP_DRC(K) * RKSIGN * KAPPARV(I, J, K) *
     >  RAS(I, J, BI, BJ) *(VFLD(I, J, K, BI, BJ) - VFLD(I, J, K + (-1)
     > , BI, BJ))))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE mom_v_sidedrag(BI, BJ, K, VFLD, DEL2V, HFACZ,
     >  VDRAGTERMS, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43)
      REAL(w2f__8) DEL2V(-2 : 93, -2 : 43)
      REAL(w2f__8) HFACZ(-2 : 93, -2 : 43)
      REAL(w2f__8) VDRAGTERMS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) A4TMP
      REAL(w2f__8) AHTMP
      REAL(w2f__8) HFACZCLOSEDE
      REAL(w2f__8) HFACZCLOSEDW
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 42, 1
        DO I = -2, 92, 1
          HFACZCLOSEDW = HFACS(I, J, K, BI, BJ) - HFACZ(I, J)
          HFACZCLOSEDE = HFACS(I, J, K, BI, BJ) - HFACZ(I + 1, J)
          AHTMP = MIN(VISCAHMAX, VISCAH +((RAS(I, J, BI, BJ) *
     >  VISCAHGRID) / DELTATMOM))
          A4TMP = MIN(VISCA4MAX, VISCA4 +((VISCA4GRID *((RAS(I, J, BI,
     >  BJ) ** 2))) / DELTATMOM))
          IF(VISCA4GRIDMAX .GT. 0.0D00) THEN
            A4TMP = MIN(A4TMP, (VISCA4GRIDMAX *((RAW(I, J, BI, BJ) ** 2
     > ))) / DELTATMOM)
          ENDIF
          A4TMP = MAX(A4TMP, (VISCA4GRIDMIN *((RAW(I, J, BI, BJ) ** 2))
     > ) / DELTATMOM)
          VDRAGTERMS(I, J) = (-(DRF(K) * RECIP_RAS(I, J, BI, BJ) *
     >  RECIP_DRF(K) * RECIP_HFACS(I, J, K, BI, BJ) *(RECIP_DXV(I, J,
     >  BI, BJ) * DYU(I, J, BI, BJ) * HFACZCLOSEDW + RECIP_DXV(I + 1, J
     > , BI, BJ) * DYU(I + 1, J, BI, BJ) * HFACZCLOSEDE) * 2.0D00 *(
     > COSFACV(J, BI, BJ) * VFLD(I, J) * AHTMP - COSFACV(J, BI, BJ) *
     >  DEL2V(I, J) * A4TMP - COSFACV(J, BI, BJ) * DEL2V(I, J) * VISCA4
     > )))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      Function different_multiple(FREQ, VAL1, STEP)
      use w2f__types
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) FREQ
      REAL(w2f__8) VAL1
      REAL(w2f__8) STEP
      LOGICAL(w2f__i4) different_multiple
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) D1
      REAL(w2f__8) D2
      REAL(w2f__8) D3
      REAL(w2f__8) V1
      REAL(w2f__8) V2
      REAL(w2f__8) V3
      REAL(w2f__8) V4
C
C     **** Statements ****
C
      different_multiple = .FALSE.
      IF(FREQ .ne. 0.0D00) THEN
        IF(FREQ .LT. ABS(STEP)) THEN
          different_multiple = .TRUE.
        ELSE
          V1 = VAL1
          V2 = VAL1 - STEP
          V3 = VAL1 + STEP
          V4 = NINT(V1 / FREQ) * FREQ
          D1 = V1 - V4
          D2 = V2 - V4
          D3 = V3 - V4
          IF((ABS(D1) .LE. ABS(D2)) .AND.(ABS(D1) .LE. ABS(D3))) THEN
            different_multiple = .TRUE.
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END FUNCTION

      SUBROUTINE adams_bashforth2(BI, BJ, K, GTRACER, GTRNM1, MYITER,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) GTRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GTRNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) AB05
      REAL(w2f__8) AB15
      REAL(w2f__8) GTRTMP
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF(MYITER .eq. 0) THEN
        AB15 = 1.0D00
        AB05 = 0.0D00
      ELSE
        AB15 = ABEPS + 1.5D00
        AB05 = -(ABEPS + 5.0D-01)
      ENDIF
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          GTRTMP = GTRACER(I, J, K, BI, BJ) * AB15 + GTRNM1(I, J, K, BI
     > , BJ) * AB05
          GTRNM1(I, J, K, BI, BJ) = GTRACER(I, J, K, BI, BJ)
          GTRACER(I, J, K, BI, BJ) = GTRTMP
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_3d_diffusivity(BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  TRIDENTITY, TRUSEGMREDI, TRUSEKPP, KAPPARTR, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) TRIDENTITY
      LOGICAL(w2f__i4) TRUSEGMREDI
      LOGICAL(w2f__i4) TRUSEKPP
      REAL(w2f__8) KAPPARTR(-2 : 93, -2 : 43, 1 : 15)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      REAL(w2f__8) KBRYANLEWIS79
      CHARACTER(512) MSGBUF
      EXTERNAL print_error
C
C     **** Statements ****
C
      IF(TRIDENTITY .eq. 1) THEN
        DO K = 1, 15, 1
          KBRYANLEWIS79 = DIFFKRBL79SURF +((ATAN(-((RF(K) -
     >  DIFFKRBL79HO) / DIFFKRBL79SCL)) / 3.141592653589793116D00) +
     >  5.0D-01) *(DIFFKRBL79DEEP - DIFFKRBL79SURF)
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              KAPPARTR(I, J, K) = (KBRYANLEWIS79 + DIFFKR(I, J, K, BI,
     >  BJ) + IVDCONVCOUNT(I, J, K, BI, BJ) * IVDC_KAPPA)
            END DO
          END DO
        END DO
      ELSE
        IF(TRIDENTITY .eq. 2) THEN
          DO K = 1, 15, 1
            KBRYANLEWIS79 = DIFFKRBL79SURF +((ATAN(-((RF(K) -
     >  DIFFKRBL79HO) / DIFFKRBL79SCL)) / 3.141592653589793116D00) +
     >  5.0D-01) *(DIFFKRBL79DEEP - DIFFKRBL79SURF)
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                KAPPARTR(I, J, K) = (KBRYANLEWIS79 + DIFFKR(I, J, K, BI
     > , BJ) + IVDCONVCOUNT(I, J, K, BI, BJ) * IVDC_KAPPA)
              END DO
            END DO
          END DO
        ELSE
          WRITE(MSGBUF, '(A,I4)')
     >  ' CALC_3D_DIFFUSIVITY: Invalid tracer Id: ', TRIDENTITY
          CALL print_error(MSGBUF, MYTHID)
          STOP 'ABNORMAL END: S/R CALC_3D_DIFFUSIVITY'
          RETURN
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_buoyancy(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  RHOLOC, BUOY, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) RHOLOC(-2 : 93, -2 : 43)
      REAL(w2f__8) BUOY(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
C
C     **** Statements ****
C
      IF(BUOYANCYRELATION .EQ. 'ATMOSPHERIC') THEN
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            BUOY(I, J) = ((THETA(I, J, K, BI, BJ) - TREF(K)) / TREF(K))
          END DO
        END DO
      ELSE
        IF(BUOYANCYRELATION .EQ. 'OCEANIC') THEN
          doloop_ub1 = JMAX
          DO J = JMIN, doloop_ub1, 1
            doloop_ub2 = IMAX
            DO I = IMIN, doloop_ub2, 1
              BUOY(I, J) = (-(RHOLOC(I, J) * GRAVITY * RECIP_RHOCONST))
            END DO
          END DO
        ELSE
          IF(BUOYANCYRELATION .EQ. 'OCEANICP') THEN
            doloop_ub3 = JMAX
            DO J = JMIN, doloop_ub3, 1
              doloop_ub4 = IMAX
              DO I = IMIN, doloop_ub4, 1
                IF(RHOLOC(I, J) .ne. 0.0D00) THEN
                  RHOLOC(I, J) = 1D00 / (RHOLOC(I, J))
                  BUOY(I, J) = RHOLOC(I, J)
                ENDIF
              END DO
            END DO
          ELSE
            STOP 'CALC_BUOANCY: variable "buoyancyRelation" has an' //
     >  ' illegal value'
            RETURN
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_common_factors(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  XA, YA, UTRANS, VTRANS, RTRANS, MASKUP, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) MASKUP(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          XA(I, J) = 0.0D00
          YA(I, J) = 0.0D00
          UTRANS(I, J) = 0.0D00
          VTRANS(I, J) = 0.0D00
          RTRANS(I, J) = 0.0D00
        END DO
      END DO
      IF(K .eq. 1) THEN
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            MASKUP(I, J) = 0.0
          END DO
        END DO
      ELSE
        doloop_ub1 = JMAX
        DO J = JMIN, doloop_ub1, 1
          doloop_ub2 = IMAX
          DO I = IMIN, doloop_ub2, 1
            MASKUP(I, J) = (MASKC(I, J, K, BI, BJ) * MASKC(I, J, K + (
     > -1), BI, BJ))
          END DO
        END DO
      ENDIF
      doloop_ub3 = JMAX
      DO J = JMIN, doloop_ub3, 1
        doloop_ub4 = IMAX
        DO I = IMIN, doloop_ub4, 1
          XA(I, J) = (HFACW(I, J, K, BI, BJ) * DRF(K) * DYG(I, J, BI,
     >  BJ))
          YA(I, J) = (HFACS(I, J, K, BI, BJ) * DRF(K) * DXG(I, J, BI,
     >  BJ))
        END DO
      END DO
      doloop_ub5 = JMAX
      DO J = JMIN, doloop_ub5, 1
        doloop_ub6 = IMAX
        DO I = IMIN, doloop_ub6, 1
          UTRANS(I, J) = (XA(I, J) * UVEL(I, J, K, BI, BJ))
          VTRANS(I, J) = (YA(I, J) * VVEL(I, J, K, BI, BJ))
        END DO
      END DO
      doloop_ub7 = JMAX
      DO J = JMIN, doloop_ub7, 1
        doloop_ub8 = IMAX
        DO I = IMIN, doloop_ub8, 1
          RTRANS(I, J) = (MASKUP(I, J) * RA(I, J, BI, BJ) * WVEL(I, J,
     >  K, BI, BJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_diffusivity(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  MASKUP, KAPPART, KAPPARS, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) MASKUP(-2 : 93, -2 : 43)
      REAL(w2f__8) KAPPART(-2 : 93, -2 : 43)
      REAL(w2f__8) KAPPARS(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) KBRYANLEWIS79
C
C     **** Statements ****
C
      KBRYANLEWIS79 = DIFFKRBL79SURF +((ATAN(-((RF(K) - DIFFKRBL79HO) /
     >  DIFFKRBL79SCL)) / 3.141592653589793116D00) + 5.0D-01) *(
     > DIFFKRBL79DEEP - DIFFKRBL79SURF)
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          KAPPART(I, J) = (KBRYANLEWIS79 + DIFFKR(I, J, K, BI, BJ) +
     >  IVDCONVCOUNT(I, J, K, BI, BJ) * IVDC_KAPPA)
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          KAPPARS(I, J) = (KBRYANLEWIS79 + DIFFKR(I, J, K, BI, BJ) +
     >  IVDCONVCOUNT(I, J, K, BI, BJ) * IVDC_KAPPA)
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          KAPPART(I, J) = (MASKUP(I, J) * KAPPART(I, J))
          KAPPARS(I, J) = (MASKUP(I, J) * KAPPARS(I, J))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_div_ghat(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, XA,
     >  YA, CG2D_B, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use solve_for_pressure3d_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
      REAL(w2f__8) CG2D_B(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) PF(-2 : 93, -2 : 43)
C
C     **** Statements ****
C
      IF(IMPLICDIV2DFLOW .eq. 1.0D00) THEN
        DO J = 1, 40, 1
          DO I = 1, 91, 1
            PF(I, J) = ((XA(I, J) * GU(I, J, K, BI, BJ)) / DELTATMOM)
          END DO
        END DO
      ELSE
        IF(EXACTCONSERV) THEN
          DO J = 1, 40, 1
            DO I = 1, 91, 1
              PF(I, J) = ((GU(I, J, K, BI, BJ) * XA(I, J) *
     >  IMPLICDIV2DFLOW) / DELTATMOM)
            END DO
          END DO
        ELSE
          DO J = 1, 40, 1
            DO I = 1, 91, 1
              PF(I, J) = ((XA(I, J) *(GU(I, J, K, BI, BJ) *
     >  IMPLICDIV2DFLOW + UVEL(I, J, K, BI, BJ) *(1.0D00 -
     >  IMPLICDIV2DFLOW))) / DELTATMOM)
            END DO
          END DO
        ENDIF
      ENDIF
      DO J = 1, 40, 1
        DO I = 1, 90, 1
          CG2D_B(I, J, BI, BJ) = (PF(I + 1, J) + CG2D_B(I, J, BI, BJ) -
     >  PF(I, J))
        END DO
      END DO
      IF(IMPLICDIV2DFLOW .eq. 1.0D00) THEN
        DO J = 1, 41, 1
          DO I = 1, 90, 1
            PF(I, J) = ((YA(I, J) * GV(I, J, K, BI, BJ)) / DELTATMOM)
          END DO
        END DO
      ELSE
        IF(EXACTCONSERV) THEN
          DO J = 1, 41, 1
            DO I = 1, 90, 1
              PF(I, J) = ((GV(I, J, K, BI, BJ) * YA(I, J) *
     >  IMPLICDIV2DFLOW) / DELTATMOM)
            END DO
          END DO
        ELSE
          DO J = 1, 41, 1
            DO I = 1, 90, 1
              PF(I, J) = ((YA(I, J) *(GV(I, J, K, BI, BJ) *
     >  IMPLICDIV2DFLOW + VVEL(I, J, K, BI, BJ) *(1.0D00 -
     >  IMPLICDIV2DFLOW))) / DELTATMOM)
            END DO
          END DO
        ENDIF
      ENDIF
      DO J = 1, 40, 1
        DO I = 1, 90, 1
          CG2D_B(I, J, BI, BJ) = (PF(I, J + 1) + CG2D_B(I, J, BI, BJ) -
     >  PF(I, J))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_grad_phi_hyd(K, BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  PHIHYDC, ALPHRHO, TFLD, SFLD, DPHIHYDX, DPHIHYDY, MYTIME,
     >  MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      REAL(w2f__8) PHIHYDC(-2 : 93, -2 : 43)
      REAL(w2f__8) ALPHRHO(-2 : 93, -2 : 43)
      REAL(w2f__8) TFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) DPHIHYDX(-2 : 93, -2 : 43)
      REAL(w2f__8) DPHIHYDY(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) VARLOC(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      IF(.TRUE.) THEN
        doloop_ub = JMAX
        DO J = JMIN +(-1), doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN +(-1), doloop_ub0, 1
            VARLOC(I, J) = (PHIHYDC(I, J) + PHI0SURF(I, J, BI, BJ))
          END DO
        END DO
      ENDIF
      doloop_ub1 = JMAX
      DO J = JMIN, doloop_ub1, 1
        doloop_ub2 = IMAX
        DO I = IMIN, doloop_ub2, 1
          DPHIHYDX(I, J) = (RECIP_DXC(I, J, BI, BJ) *(VARLOC(I, J) -
     >  VARLOC(I + (-1), J)))
          DPHIHYDY(I, J) = (RECIP_DYC(I, J, BI, BJ) *(VARLOC(I, J) -
     >  VARLOC(I, J + (-1))))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_grad_phi_surf(BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  ETAFLD, PHISURFX, PHISURFY, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      REAL(w2f__8) ETAFLD(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) PHISURFX(-2 : 93, -2 : 43)
      REAL(w2f__8) PHISURFY(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          PHISURFX(I, J) = (RECIP_DXC(I, J, BI, BJ) *(ETAFLD(I, J, BI,
     >  BJ) * BO_SURF(I, J, BI, BJ) - ETAFLD(I + (-1), J, BI, BJ) *
     >  BO_SURF(I + (-1), J, BI, BJ)))
        END DO
      END DO
      doloop_ub1 = JMAX
      DO J = JMIN, doloop_ub1, 1
        doloop_ub2 = IMAX
        DO I = IMIN, doloop_ub2, 1
          PHISURFY(I, J) = (RECIP_DYC(I, J, BI, BJ) *(ETAFLD(I, J, BI,
     >  BJ) * BO_SURF(I, J, BI, BJ) - ETAFLD(I, J + (-1), BI, BJ) *
     >  BO_SURF(I, J + (-1), BI, BJ)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_gs(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KM1, KUP,
     >  KDOWN, XA, YA, UTRANS, VTRANS, RTRANS, RTRANSKP1, MASKUP,
     >  KAPPARS, FVERS, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KUP
      INTEGER(w2f__i4) KDOWN
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANSKP1(-2 : 93, -2 : 43)
      REAL(w2f__8) MASKUP(-2 : 93, -2 : 43)
      REAL(w2f__8) KAPPARS(-2 : 93, -2 : 43)
      REAL(w2f__8) FVERS(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL adams_bashforth2
      LOGICAL(w2f__i4) CALCADVECTION
      EXTERNAL external_forcing_s
      EXTERNAL gad_calc_rhs
      INTEGER(w2f__i4) ITERNB
C
C     **** Statements ****
C
      CALCADVECTION = SALTADVECTION .AND.(.NOT. SALTMULTIDIMADVEC)
      CALL gad_calc_rhs(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KM1, KUP,
     >  KDOWN, XA, YA, UTRANS, VTRANS, RTRANS, RTRANSKP1, MASKUP, UVEL,
     >  VVEL, WVEL, DIFFKHS, DIFFK4S, KAPPARS, SALT, (2), SALTADVSCHEME
     > , SALTVERTADVSCHEME, CALCADVECTION, SALTIMPLVERTADV, FVERS, GS,
     >  MYTIME, MYITER, MYTHID)
      IF(FORCING_IN_AB .AND. SALTFORCING) THEN
        CALL external_forcing_s(IMIN, IMAX, JMIN, JMAX, BI, BJ, K,
     >  MYTIME, MYTHID)
      ENDIF
      IF(SALTADAMSBASHFORTH) THEN
        ITERNB = MYITER
        IF(STAGGERTIMESTEP) THEN
          ITERNB = MYITER +(-1)
        ENDIF
        CALL adams_bashforth2(BI, BJ, K, GS, GSNM1, ITERNB, MYTHID)
      ENDIF
      IF(SALTFORCING .AND.(.NOT. FORCING_IN_AB)) THEN
        CALL external_forcing_s(IMIN, IMAX, JMIN, JMAX, BI, BJ, K,
     >  MYTIME, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_gt(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KM1, KUP,
     >  KDOWN, XA, YA, UTRANS, VTRANS, RTRANS, RTRANSKP1, MASKUP,
     >  KAPPART, FVERT, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use gad_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KUP
      INTEGER(w2f__i4) KDOWN
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANSKP1(-2 : 93, -2 : 43)
      REAL(w2f__8) MASKUP(-2 : 93, -2 : 43)
      REAL(w2f__8) KAPPART(-2 : 93, -2 : 43)
      REAL(w2f__8) FVERT(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL adams_bashforth2
      LOGICAL(w2f__i4) CALCADVECTION
      EXTERNAL external_forcing_t
      EXTERNAL gad_calc_rhs
      INTEGER(w2f__i4) ITERNB
C
C     **** Statements ****
C
      CALCADVECTION = TEMPADVECTION .AND.(.NOT. TEMPMULTIDIMADVEC)
      CALL gad_calc_rhs(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KM1, KUP,
     >  KDOWN, XA, YA, UTRANS, VTRANS, RTRANS, RTRANSKP1, MASKUP, UVEL,
     >  VVEL, WVEL, DIFFKHT, DIFFK4T, KAPPART, THETA, (1),
     >  TEMPADVSCHEME, TEMPVERTADVSCHEME, CALCADVECTION,
     >  TEMPIMPLVERTADV, FVERT, GT, MYTIME, MYITER, MYTHID)
      IF(FORCING_IN_AB .AND. TEMPFORCING) THEN
        CALL external_forcing_t(IMIN, IMAX, JMIN, JMAX, BI, BJ, K,
     >  MYTIME, MYTHID)
      ENDIF
      IF(TEMPADAMSBASHFORTH) THEN
        ITERNB = MYITER
        IF(STAGGERTIMESTEP) THEN
          ITERNB = MYITER +(-1)
        ENDIF
        CALL adams_bashforth2(BI, BJ, K, GT, GTNM1, ITERNB, MYTHID)
      ENDIF
      IF(TEMPFORCING .AND.(.NOT. FORCING_IN_AB)) THEN
        CALL external_forcing_t(IMIN, IMAX, JMIN, JMAX, BI, BJ, K,
     >  MYTIME, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_ivdc(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, RHOKM1,
     >  RHOKP1, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) RHOKM1(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOKP1(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          IF((HFACC(I, J, K, BI, BJ) .GT. 0.0D00) .AND.((GRAVITYSIGN *
     >  RKSIGN *(RHOKM1(I, J) - RHOKP1(I, J))) .GT. 0.0D00)) THEN
            IVDCONVCOUNT(I, J, K, BI, BJ) = 1.0D00
          ELSE
            IVDCONVCOUNT(I, J, K, BI, BJ) = 0.0D00
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_phi_hyd(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, TFLD,
     >  SFLD, PHIHYDF, PHIHYDC, DPHIHYDX, DPHIHYDY, MYTIME, MYITER,
     >  MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      use tamc_mod
      use tamc_keys_mod
      use surface_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) TFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) PHIHYDF(-2 : 93, -2 : 43)
      REAL(w2f__8) PHIHYDC(-2 : 93, -2 : 43)
      REAL(w2f__8) DPHIHYDX(-2 : 93, -2 : 43)
      REAL(w2f__8) DPHIHYDY(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      LOGICAL(w2f__i4) ADDSURFPHIANOM
      REAL(w2f__8) ALPHARHO(-2 : 93, -2 : 43)
      EXTERNAL calc_grad_phi_hyd
      REAL(w2f__8) DDPIM
      REAL(w2f__8) DDPIP
      REAL(w2f__8) DDRLOC
      EXTERNAL diags_phi_hyd
      EXTERNAL diags_phi_rlow
      REAL(w2f__8) DRLOCM
      REAL(w2f__8) DRLOCP
      EXTERNAL find_rho
      REAL(w2f__8) HALF
      PARAMETER ( HALF =    0.5000000000000000)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMNLOC
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMNLOC
      REAL(w2f__8) LOCALPHA
      REAL(w2f__8) ONE
      PARAMETER ( ONE =     1.000000000000000)
      EXTERNAL quasihydrostaticterms
      REAL(w2f__8) REC_DRM
      REAL(w2f__8) REC_DRP
      REAL(w2f__8) SURFPHIFAC
      LOGICAL(w2f__i4) USEDIAGPHIRLOW
      REAL(w2f__8) ZERO
      PARAMETER ( ZERO =     0.000000000000000)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
      INTEGER(w2f__i4) doloop_ub11
      INTEGER(w2f__i4) doloop_ub12
      INTEGER(w2f__i4) doloop_ub13
      INTEGER(w2f__i4) doloop_ub14
      INTEGER(w2f__i4) doloop_ub15
      INTEGER(w2f__i4) doloop_ub16
C
C     **** Statements ****
C
      USEDIAGPHIRLOW = .TRUE.
      ADDSURFPHIANOM = (SELECT_RSTAR .eq. 0) .AND.(NONLINFREESURF .GT.
     >  3)
      SURFPHIFAC = 0.0D00
      IF(ADDSURFPHIANOM) THEN
        SURFPHIFAC = 1.0D00
      ENDIF
      ACT1 = BI - MYBXLO(MYTHID)
      MAX1 = MYBXHI(MYTHID) - MYBXLO(MYTHID) + 1
      ACT2 = BJ - MYBYLO(MYTHID)
      MAX2 = MYBYHI(MYTHID) - MYBYLO(MYTHID) + 1
      ACT3 = MYTHID +(-1)
      MAX3 = NTX * NTY
      ACT4 = IKEY_DYNAMICS +(-1)
      IKEY = ACT1 + ACT2 * MAX1 + MAX2 * ACT3 * MAX1 + MAX3 * MAX2 *
     >  ACT4 * MAX1 + 1
      IF(K .eq. 1) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            PHIHYDF(I, J) = 0.0
          END DO
        END DO
      ENDIF
      IF(BUOYANCYRELATION .EQ. 'OCEANIC') THEN
        KKEY = K + IKEY * 15 +(-15)
        CALL find_rho(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, K, TFLD, SFLD,
     >  ALPHARHO, MYTHID)
        IF(QUASIHYDROSTATIC) THEN
          CALL quasihydrostaticterms(BI, BJ, K, ALPHARHO, MYTHID)
        ENDIF
        IF(INTEGR_GEOPOT .eq. 1) THEN
          doloop_ub = JMAX
          DO J = JMIN, doloop_ub, 1
            doloop_ub0 = IMAX
            DO I = IMIN, doloop_ub0, 1
              PHIHYDC(I, J) = (PHIHYDF(I, J) + RECIP_RHOCONST *
     >  ALPHARHO(I, J) * GRAVITY * DRF(K) * 5.0D-01)
              PHIHYDF(I, J) = (PHIHYDF(I, J) + RECIP_RHOCONST *
     >  ALPHARHO(I, J) * DRF(K) * GRAVITY)
            END DO
          END DO
        ELSE
          DRLOCM = DRC(K) * 5.0D-01
          IF(K .eq. 1) THEN
            DRLOCM = RF(K) - RC(K)
          ENDIF
          IF(K .eq. 15) THEN
            DRLOCP = RC(K) - RF(K + 1)
          ELSE
            DRLOCP = DRC(K + 1) * 5.0D-01
          ENDIF
          doloop_ub1 = JMAX
          DO J = JMIN, doloop_ub1, 1
            doloop_ub2 = IMAX
            DO I = IMIN, doloop_ub2, 1
              PHIHYDC(I, J) = (PHIHYDF(I, J) + RECIP_RHOCONST *
     >  ALPHARHO(I, J) * DRLOCM * GRAVITY)
              PHIHYDF(I, J) = (PHIHYDC(I, J) + RECIP_RHOCONST *
     >  ALPHARHO(I, J) * DRLOCP * GRAVITY)
            END DO
          END DO
        ENDIF
      ELSE
        IF(BUOYANCYRELATION .EQ. 'OCEANICP') THEN
          KKEY = K + IKEY * 15 +(-15)
          CALL find_rho(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, K, TFLD,
     >  SFLD, ALPHARHO, MYTHID)
          doloop_ub3 = JMAX
          DO J = JMIN, doloop_ub3, 1
            doloop_ub4 = IMAX
            DO I = IMIN, doloop_ub4, 1
              LOCALPHA = ALPHARHO(I, J) + RHOCONST
              ALPHARHO(I, J) = (MASKC(I, J, K, BI, BJ) *(1D00 /
     >  LOCALPHA - RECIP_RHOCONST))
            END DO
          END DO
          IF(INTEGR_GEOPOT .eq. 1) THEN
            doloop_ub5 = JMAX
            DO J = JMIN, doloop_ub5, 1
              doloop_ub6 = IMAX
              DO I = IMIN, doloop_ub6, 1
                IF(KSURFC(I, J, BI, BJ) .eq. K) THEN
                  DDRLOC = RO_SURF(I, J, BI, BJ) - RC(K)
                  PHIHYDC(I, J) = (ALPHARHO(I, J) * DDRLOC)
                ELSE
                  PHIHYDC(I, J) = (PHIHYDF(I, J) + ALPHARHO(I, J) * DRF
     > (K) * 5.0D-01)
                ENDIF
                PHIHYDF(I, J) = (PHIHYDC(I, J) + ALPHARHO(I, J) * DRF(K
     > ) * 5.0D-01)
              END DO
            END DO
          ELSE
            DRLOCM = DRC(K) * 5.0D-01
            IF(K .eq. 1) THEN
              DRLOCM = RF(K) - RC(K)
            ENDIF
            IF(K .eq. 15) THEN
              DRLOCP = RC(K) - RF(K + 1)
            ELSE
              DRLOCP = DRC(K + 1) * 5.0D-01
            ENDIF
            REC_DRM = 1D00 / (RF(K) - RC(K))
            REC_DRP = 1D00 / (RC(K) - RF(K + 1))
            doloop_ub7 = JMAX
            DO J = JMIN, doloop_ub7, 1
              doloop_ub8 = IMAX
              DO I = IMIN, doloop_ub8, 1
                IF(KSURFC(I, J, BI, BJ) .eq. K) THEN
                  DDRLOC = RO_SURF(I, J, BI, BJ) - RC(K)
                  PHIHYDC(I, J) = (ALPHARHO(I, J) *(DRLOCM * REC_DRM *
     >  MAX(DDRLOC, 0.0D00) + DRLOCP * REC_DRP * MIN(DDRLOC, 0.0D00)))
                ELSE
                  PHIHYDC(I, J) = (PHIHYDF(I, J) + ALPHARHO(I, J) *
     >  DRLOCM)
                ENDIF
                PHIHYDF(I, J) = (PHIHYDC(I, J) + ALPHARHO(I, J) *
     >  DRLOCP)
              END DO
            END DO
          ENDIF
        ELSE
          IF(BUOYANCYRELATION .EQ. 'ATMOSPHERIC') THEN
            doloop_ub9 = JMAX
            DO J = JMIN, doloop_ub9, 1
              doloop_ub10 = IMAX
              DO I = IMIN, doloop_ub10, 1
                ALPHARHO(I, J) = (MASKC(I, J, K, BI, BJ) *(TFLD(I, J, K
     > , BI, BJ) *(SFLD(I, J, K, BI, BJ) * ATM_RQ + 1.0D00) - TREF(K)))
              END DO
            END DO
            IF(INTEGR_GEOPOT .eq. 0) THEN
              IF(K .eq. 1) THEN
                DDPIM = ATM_CP *((((RF(K) / ATM_PO) ** ATM_KAPPA)) -(((
     > RC(K) / ATM_PO) ** ATM_KAPPA)))
              ELSE
                DDPIM = ATM_CP *((((RC(K + (-1)) / ATM_PO) ** ATM_KAPPA
     > )) -(((RC(K) / ATM_PO) ** ATM_KAPPA))) * 5.0D-01
              ENDIF
              IF(K .eq. 15) THEN
                DDPIP = ATM_CP *((((RC(K) / ATM_PO) ** ATM_KAPPA)) -(((
     > RF(K + 1) / ATM_PO) ** ATM_KAPPA)))
              ELSE
                DDPIP = ATM_CP *((((RC(K) / ATM_PO) ** ATM_KAPPA)) -(((
     > RC(K + 1) / ATM_PO) ** ATM_KAPPA))) * 5.0D-01
              ENDIF
              doloop_ub11 = JMAX
              DO J = JMIN, doloop_ub11, 1
                doloop_ub12 = IMAX
                DO I = IMIN, doloop_ub12, 1
                  PHIHYDC(I, J) = (PHIHYDF(I, J) + ALPHARHO(I, J) *
     >  DDPIM)
                  PHIHYDF(I, J) = (PHIHYDC(I, J) + ALPHARHO(I, J) *
     >  DDPIP)
                END DO
              END DO
            ELSE
              IF(INTEGR_GEOPOT .eq. 1) THEN
                DDPIM = ATM_CP *((((RF(K) / ATM_PO) ** ATM_KAPPA)) -(((
     > RC(K) / ATM_PO) ** ATM_KAPPA)))
                DDPIP = ATM_CP *((((RC(K) / ATM_PO) ** ATM_KAPPA)) -(((
     > RF(K + 1) / ATM_PO) ** ATM_KAPPA)))
                doloop_ub13 = JMAX
                DO J = JMIN, doloop_ub13, 1
                  doloop_ub14 = IMAX
                  DO I = IMIN, doloop_ub14, 1
                    IF(KSURFC(I, J, BI, BJ) .eq. K) THEN
                      DDRLOC = RO_SURF(I, J, BI, BJ) - RC(K)
                      PHIHYDC(I, J) = (ALPHARHO(I, J) * DDPIM *
     >  RECIP_DRF(K) * DDRLOC * 2.0D00)
                    ELSE
                      PHIHYDC(I, J) = (PHIHYDF(I, J) + ALPHARHO(I, J) *
     >  DDPIM)
                    ENDIF
                    PHIHYDF(I, J) = (PHIHYDC(I, J) + ALPHARHO(I, J) *
     >  DDPIP)
                  END DO
                END DO
              ELSE
                IF((INTEGR_GEOPOT .eq. 2) .OR.(INTEGR_GEOPOT .eq. 3))
     >  THEN
                  IF(K .eq. 1) THEN
                    DDPIM = ATM_CP *((((RF(K) / ATM_PO) ** ATM_KAPPA))
     >  -(((RC(K) / ATM_PO) ** ATM_KAPPA)))
                  ELSE
                    DDPIM = ATM_CP *((((RC(K + (-1)) / ATM_PO) **
     >  ATM_KAPPA)) -(((RC(K) / ATM_PO) ** ATM_KAPPA))) * 5.0D-01
                  ENDIF
                  IF(K .eq. 15) THEN
                    DDPIP = ATM_CP *((((RC(K) / ATM_PO) ** ATM_KAPPA))
     >  -(((RF(K + 1) / ATM_PO) ** ATM_KAPPA)))
                  ELSE
                    DDPIP = ATM_CP *((((RC(K) / ATM_PO) ** ATM_KAPPA))
     >  -(((RC(K + 1) / ATM_PO) ** ATM_KAPPA))) * 5.0D-01
                  ENDIF
                  REC_DRM = 1D00 / (RF(K) - RC(K))
                  REC_DRP = 1D00 / (RC(K) - RF(K + 1))
                  doloop_ub15 = JMAX
                  DO J = JMIN, doloop_ub15, 1
                    doloop_ub16 = IMAX
                    DO I = IMIN, doloop_ub16, 1
                      IF(KSURFC(I, J, BI, BJ) .eq. K) THEN
                        DDRLOC = RO_SURF(I, J, BI, BJ) - RC(K)
                        PHIHYDC(I, J) = (ALPHARHO(I, J) *(DDPIM *
     >  REC_DRM * MAX(DDRLOC, 0.0D00) + DDPIP * REC_DRP * MIN(DDRLOC,
     >  0.0D00)))
                      ELSE
                        PHIHYDC(I, J) = (PHIHYDF(I, J) + ALPHARHO(I, J)
     >  * DDPIM)
                      ENDIF
                      PHIHYDF(I, J) = (PHIHYDC(I, J) + ALPHARHO(I, J) *
     >  DDPIP)
                    END DO
                  END DO
                ELSE
                  STOP 'CALC_PHI_HYD: Bad integr_GeoPot option !'
                  RETURN
                ENDIF
              ENDIF
            ENDIF
          ELSE
            STOP 'CALC_PHI_HYD: Bad value of buoyancyRelation !'
            RETURN
          ENDIF
        ENDIF
      ENDIF
      IF(USEDIAGPHIRLOW) THEN
        CALL diags_phi_rlow(K, BI, BJ, IMIN, IMAX, JMIN, JMAX, PHIHYDF,
     >  PHIHYDC, ALPHARHO, TFLD, SFLD, MYTIME, MYITER, MYTHID)
      ENDIF
      CALL diags_phi_hyd(K, BI, BJ, IMIN, IMAX, JMIN, JMAX, PHIHYDC,
     >  MYTIME, MYITER, MYTHID)
      IF(MOMPRESSUREFORCING) THEN
        IMNLOC = MAX(IMIN, -1)
        JMNLOC = MAX(JMIN, -1)
        CALL calc_grad_phi_hyd(K, BI, BJ, IMNLOC, IMAX, JMNLOC, JMAX,
     >  PHIHYDC, ALPHARHO, TFLD, SFLD, DPHIHYDX, DPHIHYDY, MYTIME,
     >  MYITER, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE calc_viscosity(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  KAPPARU, KAPPARV, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) KAPPARU(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) KAPPARV(-2 : 93, -2 : 43, 1 : 15)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          KAPPARU(I, J, K) = VISCAR
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          KAPPARV(I, J, K) = VISCAR
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE convect(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, RHOKM1,
     >  RHOKP1, CONVECTCOUNT, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) RHOKM1(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOKP1(-2 : 93, -2 : 43)
      REAL(w2f__8) CONVECTCOUNT(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL different_multiple
      LOGICAL(w2f__i4) different_multiple
      REAL(w2f__8) DSUM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) SMIX(-2 : 93, -2 : 43)
      REAL(w2f__8) TMIX(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      IF(different_multiple(CADJFREQ, MYTIME, DELTATCLOCK)) THEN
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            TMIX(I, J) = (DRF(K) * THETA(I, J, K, BI, BJ) * HFACC(I, J,
     >  K, BI, BJ) + DRF(K + (-1)) * THETA(I, J, K + (-1), BI, BJ) *
     >  HFACC(I, J, K + (-1), BI, BJ))
            SMIX(I, J) = (DRF(K) * SALT(I, J, K, BI, BJ) * HFACC(I, J,
     >  K, BI, BJ) + DRF(K + (-1)) * SALT(I, J, K + (-1), BI, BJ) *
     >  HFACC(I, J, K + (-1), BI, BJ))
            DSUM(I, J) = (DRF(K) * HFACC(I, J, K, BI, BJ) + DRF(K + (-1
     > )) * HFACC(I, J, K + (-1), BI, BJ))
          END DO
        END DO
        doloop_ub1 = JMAX
        DO J = JMIN, doloop_ub1, 1
          doloop_ub2 = IMAX
          DO I = IMIN, doloop_ub2, 1
            IF((HFACC(I, J, K, BI, BJ) .GT. 0.0D00) .AND.((GRAVITYSIGN
     >  * RKSIGN *(RHOKM1(I, J) - RHOKP1(I, J))) .GT. 0.0D00)) THEN
              THETA(I, J, K + (-1), BI, BJ) = (TMIX(I, J) / DSUM(I, J))
              THETA(I, J, K, BI, BJ) = (TMIX(I, J) / DSUM(I, J))
              SALT(I, J, K + (-1), BI, BJ) = (SMIX(I, J) / DSUM(I, J))
              SALT(I, J, K, BI, BJ) = (SMIX(I, J) / DSUM(I, J))
              CONVECTCOUNT(I, J, K) = (CONVECTCOUNT(I, J, K) + 1.0D00)
            ENDIF
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE convective_adjustment(BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use tamc_mod
      use tamc_keys_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) CONVECTCOUNT(-2 : 93, -2 : 43, 1 : 15)
      EXTERNAL convectively_mixtracer
      EXTERNAL convective_weights
      INTEGER(w2f__i4) DELTAK
      EXTERNAL different_multiple
      LOGICAL(w2f__i4) different_multiple
      EXTERNAL find_rho
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KBOTTOM
      INTEGER(w2f__i4) KDIR
      INTEGER(w2f__i4) KTOP
      REAL(w2f__8) RHOK(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOKM1(-2 : 93, -2 : 43)
      REAL(w2f__8) WEIGHTA(-2 : 93, -2 : 43)
      REAL(w2f__8) WEIGHTB(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_stride
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_count
      INTEGER(w2f__i4) doloop_var
C
C     **** Statements ****
C
      IF(different_multiple(CADJFREQ, MYTIME, DELTATCLOCK)) THEN
        KTOP = 0
        KBOTTOM = 0
        KDIR = 0
        DELTAK = 0
        DO K = 1, 15, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              CONVECTCOUNT(I, J, K) = 0.0
            END DO
          END DO
        END DO
        ACT1 = BI - MYBXLO(MYTHID)
        MAX1 = MYBXHI(MYTHID) - MYBXLO(MYTHID) + 1
        ACT2 = BJ - MYBYLO(MYTHID)
        MAX2 = MYBYHI(MYTHID) - MYBYLO(MYTHID) + 1
        ACT3 = MYTHID +(-1)
        MAX3 = NTX * NTY
        ACT4 = IKEY_DYNAMICS +(-1)
        IKEY = ACT1 + ACT2 * MAX1 + MAX2 * ACT3 * MAX1 + MAX3 * MAX2 *
     >  ACT4 * MAX1 + 1
        IF((GRAVITYSIGN * RKSIGN) .GT. 0.0D00) THEN
          KTOP = 2
          KBOTTOM = 15
          KDIR = 1
          DELTAK = -1
        ELSE
          KTOP = 15
          KBOTTOM = 2
          KDIR = -1
          DELTAK = 0
        ENDIF
        doloop_stride = KDIR
        doloop_ub = KBOTTOM
        K = KTOP
        doloop_count = (KDIR + KBOTTOM - K) / KDIR
        DO doloop_var = 0, doloop_count + (-1), 1
          KKEY = K + IKEY * 15 +(-15)
          CALL find_rho(BI, BJ, IMIN, IMAX, JMIN, JMAX, (K +(-1)), (
     > DELTAK + K), THETA, SALT, RHOKM1, MYTHID)
          CALL find_rho(BI, BJ, IMIN, IMAX, JMIN, JMAX, (K), (DELTAK +
     >  K), THETA, SALT, RHOK, MYTHID)
          CALL convective_weights(BI, BJ, (K), RHOKM1, RHOK, WEIGHTA,
     >  WEIGHTB, CONVECTCOUNT, MYTHID)
          CALL convectively_mixtracer(BI, BJ, (K), WEIGHTA, WEIGHTB,
     >  THETA, MYTHID)
          CALL convectively_mixtracer(BI, BJ, (K), WEIGHTA, WEIGHTB,
     >  SALT, MYTHID)
          K = K + doloop_stride
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE convective_adjustment_ini(BI, BJ, IMIN, IMAX, JMIN,
     >  JMAX, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use tamc_mod
      use tamc_keys_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) CONVECTCOUNT(-2 : 93, -2 : 43, 1 : 15)
      EXTERNAL convectively_mixtracer
      EXTERNAL convective_weights
      INTEGER(w2f__i4) DELTAK
      EXTERNAL different_multiple
      LOGICAL(w2f__i4) different_multiple
      EXTERNAL find_rho
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KBOTTOM
      INTEGER(w2f__i4) KDIR
      INTEGER(w2f__i4) KTOP
      REAL(w2f__8) RHOK(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOKM1(-2 : 93, -2 : 43)
      REAL(w2f__8) WEIGHTA(-2 : 93, -2 : 43)
      REAL(w2f__8) WEIGHTB(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_stride
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_count
      INTEGER(w2f__i4) doloop_var
C
C     **** Statements ****
C
      IF(different_multiple(CADJFREQ, MYTIME, DELTATCLOCK)) THEN
        KTOP = 0
        KBOTTOM = 0
        KDIR = 0
        DELTAK = 0
        DO K = 1, 15, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              CONVECTCOUNT(I, J, K) = 0.0
            END DO
          END DO
        END DO
        ACT1 = BI - MYBXLO(MYTHID)
        MAX1 = MYBXHI(MYTHID) - MYBXLO(MYTHID) + 1
        ACT2 = BJ - MYBYLO(MYTHID)
        MAX2 = MYBYHI(MYTHID) - MYBYLO(MYTHID) + 1
        ACT3 = MYTHID +(-1)
        MAX3 = NTX * NTY
        ACT4 = 0
        IKEY = ACT1 + ACT2 * MAX1 + MAX2 * ACT3 * MAX1 + MAX3 * MAX2 *
     >  ACT4 * MAX1 + 1
        IF((GRAVITYSIGN * RKSIGN) .GT. 0.0D00) THEN
          KTOP = 2
          KBOTTOM = 15
          KDIR = 1
          DELTAK = -1
        ELSE
          KTOP = 15
          KBOTTOM = 2
          KDIR = -1
          DELTAK = 0
        ENDIF
        doloop_stride = KDIR
        doloop_ub = KBOTTOM
        K = KTOP
        doloop_count = (KDIR + KBOTTOM - K) / KDIR
        DO doloop_var = 0, doloop_count + (-1), 1
          KKEY = K + IKEY * 15 +(-15)
          CALL find_rho(BI, BJ, IMIN, IMAX, JMIN, JMAX, (K +(-1)), (
     > DELTAK + K), THETA, SALT, RHOKM1, MYTHID)
          CALL find_rho(BI, BJ, IMIN, IMAX, JMIN, JMAX, (K), (DELTAK +
     >  K), THETA, SALT, RHOK, MYTHID)
          CALL convective_weights(BI, BJ, (K), RHOKM1, RHOK, WEIGHTA,
     >  WEIGHTB, CONVECTCOUNT, MYTHID)
          CALL convectively_mixtracer(BI, BJ, (K), WEIGHTA, WEIGHTB,
     >  THETA, MYTHID)
          CALL convectively_mixtracer(BI, BJ, (K), WEIGHTA, WEIGHTB,
     >  SALT, MYTHID)
          K = K + doloop_stride
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE convective_weights(BI, BJ, K, RHOKM1, RHOK, WEIGHTA,
     >  WEIGHTB, CONVECTCOUNT, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) RHOKM1(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOK(-2 : 93, -2 : 43)
      REAL(w2f__8) WEIGHTA(-2 : 93, -2 : 43)
      REAL(w2f__8) WEIGHTB(-2 : 93, -2 : 43)
      REAL(w2f__8) CONVECTCOUNT(-2 : 93, -2 : 43, 1 : 15)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) D1
      REAL(w2f__8) D2
      REAL(w2f__8) DS
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          IF(((HFACC(I, J, K, BI, BJ) * HFACC(I, J, K + (-1), BI, BJ))
     >  .GT. 0.0D00) .AND.((GRAVITYSIGN * RKSIGN *(RHOKM1(I, J) - RHOK(
     > I, J))) .GT. 0.0D00)) THEN
            D1 = DRF(K + (-1)) * HFACC(I, J, K + (-1), BI, BJ)
            D2 = DRF(K) * HFACC(I, J, K, BI, BJ)
            DS = D1 + D2
            WEIGHTA(I, J) = (D2 / DS)
            WEIGHTB(I, J) = (D1 / DS)
            CONVECTCOUNT(I, J, K) = (CONVECTCOUNT(I, J, K) + 1.0D00)
          ELSE
            WEIGHTA(I, J) = 0.0
            WEIGHTB(I, J) = 0.0
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE convectively_mixtracer(BI, BJ, K, WEIGHTA, WEIGHTB,
     >  TRACER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) WEIGHTA(-2 : 93, -2 : 43)
      REAL(w2f__8) WEIGHTB(-2 : 93, -2 : 43)
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) DELTRAC
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          DELTRAC = TRACER(I, J, K, BI, BJ) - TRACER(I, J, K + (-1), BI
     > , BJ)
          TRACER(I, J, K + (-1), BI, BJ) = (TRACER(I, J, K + (-1), BI,
     >  BJ) + WEIGHTA(I, J) * DELTRAC)
          TRACER(I, J, K, BI, BJ) = (TRACER(I, J, K, BI, BJ) - WEIGHTB(
     > I, J) * DELTRAC)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE correction_step(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  PHISURFX, PHISURFY, MYCURRENTTIME, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) PHISURFX(-2 : 93, -2 : 43)
      REAL(w2f__8) PHISURFY(-2 : 93, -2 : 43)
      REAL(w2f__8) MYCURRENTTIME
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) HX3DFAC
      REAL(w2f__8) HXFAC
      REAL(w2f__8) HY3DFAC
      REAL(w2f__8) HYFAC
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      HXFAC = PFFACMOM
      HYFAC = PFFACMOM
      IF(NONHYDROSTATIC) THEN
        HX3DFAC = PFFACMOM
        HY3DFAC = PFFACMOM
      ELSE
        HX3DFAC = 0.0D00
        HY3DFAC = 0.0D00
      ENDIF
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          UVEL(I, J, K, BI, BJ) = (MASKW(I, J, K, BI, BJ) *(GU(I, J, K,
     >  BI, BJ) - PHISURFX(I, J) * IMPLICSURFPRESS * HXFAC * DELTATMOM)
     > )
        END DO
      END DO
      doloop_ub1 = JMAX
      DO J = JMIN, doloop_ub1, 1
        doloop_ub2 = IMAX
        DO I = IMIN, doloop_ub2, 1
          VVEL(I, J, K, BI, BJ) = (MASKS(I, J, K, BI, BJ) *(GV(I, J, K,
     >  BI, BJ) - PHISURFY(I, J) * IMPLICSURFPRESS * HYFAC * DELTATMOM)
     > )
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE cycle_tracer(BI, BJ, K, TRACER, GTRACER, MYTIME,
     >  MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GTRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          TRACER(I, J, K, BI, BJ) = GTRACER(I, J, K, BI, BJ)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE diags_phi_hyd(K, BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  PHIHYDC, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      REAL(w2f__8) PHIHYDC(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          TOTPHIHYD(I, J, K, BI, BJ) = (PHI0SURF(I, J, BI, BJ) +
     >  PHIHYDC(I, J) + ETAN(I, J, BI, BJ) * BO_SURF(I, J, BI, BJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE diags_phi_rlow(K, BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  PHIHYDF, PHIHYDC, ALPHRHO, TFLD, SFLD, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      REAL(w2f__8) PHIHYDF(-2 : 93, -2 : 43)
      REAL(w2f__8) PHIHYDC(-2 : 93, -2 : 43)
      REAL(w2f__8) ALPHRHO(-2 : 93, -2 : 43)
      REAL(w2f__8) TFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) DDRLOC
      REAL(w2f__8) HALF
      PARAMETER ( HALF =    0.5000000000000000)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) ONE
      PARAMETER ( ONE =     1.000000000000000)
      REAL(w2f__8) RATIORM
      REAL(w2f__8) RATIORP
      REAL(w2f__8) ZERO
      PARAMETER ( ZERO =     0.000000000000000)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
C
C     **** Statements ****
C
      IF(BUOYANCYRELATION .EQ. 'OCEANIC') THEN
        IF(INTEGR_GEOPOT .eq. 1) THEN
          doloop_ub = JMAX
          DO J = JMIN, doloop_ub, 1
            doloop_ub0 = IMAX
            DO I = IMIN, doloop_ub0, 1
              IF(KLOWC(I, J, BI, BJ) .eq. K) THEN
                DDRLOC = RC(K) - R_LOW(I, J, BI, BJ)
                PHIHYDLOW(I, J, BI, BJ) = (PHIHYDC(I, J) +
     >  RECIP_RHOCONST * ALPHRHO(I, J) * DDRLOC * GRAVITY)
              ENDIF
            END DO
          END DO
        ELSE
          RATIORM = 1.0D00
          RATIORP = 1.0D00
          IF(K .GT. 1) THEN
            RATIORM = (DRC(K) * 5.0D-01) /(RF(K) - RC(K))
          ENDIF
          IF(K .LT. 15) THEN
            RATIORP = (DRC(K + 1) * 5.0D-01) /(RC(K) - RF(K + 1))
          ENDIF
          doloop_ub1 = JMAX
          DO J = JMIN, doloop_ub1, 1
            doloop_ub2 = IMAX
            DO I = IMIN, doloop_ub2, 1
              IF(KLOWC(I, J, BI, BJ) .eq. K) THEN
                DDRLOC = RC(K) - R_LOW(I, J, BI, BJ)
                PHIHYDLOW(I, J, BI, BJ) = (PHIHYDC(I, J) +
     >  RECIP_RHOCONST * ALPHRHO(I, J) * GRAVITY *(RATIORM * MIN(DDRLOC
     > , 0.0D00) + RATIORP * MAX(DDRLOC, 0.0D00)))
              ENDIF
            END DO
          END DO
        ENDIF
      ENDIF
      IF(K .eq. 15) THEN
        IF((BUOYANCYRELATION .EQ. 'OCEANICP') .OR.(BUOYANCYRELATION
     >  .EQ. 'ATMOSPHERIC')) THEN
          doloop_ub3 = JMAX
          DO J = JMIN, doloop_ub3, 1
            doloop_ub4 = IMAX
            DO I = IMIN, doloop_ub4, 1
              PHIHYDLOW(I, J, BI, BJ) = PHIHYDF(I, J)
            END DO
          END DO
        ENDIF
        doloop_ub5 = JMAX
        DO J = JMIN, doloop_ub5, 1
          doloop_ub6 = IMAX
          DO I = IMIN, doloop_ub6, 1
            PHIHYDLOW(I, J, BI, BJ) = (PHI0SURF(I, J, BI, BJ) +
     >  PHIHYDLOW(I, J, BI, BJ) + ETAN(I, J, BI, BJ) * BO_SURF(I, J, BI
     > , BJ))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE do_atmospheric_phys(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL debug_enter
      EXTERNAL debug_leave
C
C     **** Statements ****
C
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_enter('DO_ATMOSPHERIC_PHYS', MYTHID)
      ENDIF
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_leave('DO_ATMOSPHERIC_PHYS', MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE do_fields_blocking_exchanges(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use cd_code_vars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL exch_uv_xyz_rl
      EXTERNAL exch_xyz_rl
C
C     **** Statements ****
C
      IF(.NOT.(STAGGERTIMESTEP .AND. USEMULTIDIMADVEC)) THEN
        CALL exch_uv_xyz_rl(UVEL, VVEL, (.TRUE.), MYTHID)
        CALL exch_xyz_rl(WVEL, MYTHID)
      ENDIF
      CALL exch_xyz_rl(THETA, MYTHID)
      CALL exch_xyz_rl(SALT, MYTHID)
      CALL exch_xyz_rl(UVELD, MYTHID)
      CALL exch_xyz_rl(VVELD, MYTHID)
      IF(USEDYNP_INEOS_ZC) THEN
        CALL exch_xyz_rl(TOTPHIHYD, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE do_oceanic_phys(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use tamc_mod
      use tamc_keys_mod
      use ffields_mod
      use eos_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL calc_ivdc
      EXTERNAL debug_call
      EXTERNAL debug_enter
      EXTERNAL debug_leave
      EXTERNAL debug_msg
      INTEGER(w2f__i4) DODIAGSRHO
      EXTERNAL external_forcing_surf
      EXTERNAL find_rho
      EXTERNAL freeze_surface
      EXTERNAL grad_sigma
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) K
      REAL(w2f__8) RHOK(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOKM1(-2 : 93, -2 : 43)
      REAL(w2f__8) SIGMAR(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) SIGMAX(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) SIGMAY(-2 : 93, -2 : 43, 1 : 15)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      ITDKEY = 1
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_enter('DO_OCEANIC_PHYS', MYTHID)
      ENDIF
      DODIAGSRHO = 0
      IF((ALLOWFREEZING .AND.(.NOT. USESEAICE)) .AND.(.NOT. USETHSICE))
     >  THEN
        CALL freeze_surface(MYTIME, MYITER, MYTHID)
      ENDIF
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          ACT1 = BI - MYBXLO(MYTHID)
          MAX1 = MYBXHI(MYTHID) - MYBXLO(MYTHID) + 1
          ACT2 = BJ - MYBYLO(MYTHID)
          MAX2 = MYBYHI(MYTHID) - MYBYLO(MYTHID) + 1
          ACT3 = MYTHID +(-1)
          MAX3 = NTX * NTY
          ACT4 = IKEY_DYNAMICS +(-1)
          ITDKEY = ACT1 + ACT2 * MAX1 + MAX2 * ACT3 * MAX1 + MAX3 *
     >  MAX2 * ACT4 * MAX1 + 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              RHOK(I, J) = 0.0D00
              RHOKM1(I, J) = 0.0D00
            END DO
          END DO
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                SIGMAX(I, J, K) = 0.0D00
                SIGMAY(I, J, K) = 0.0D00
                SIGMAR(I, J, K) = 0.0D00
                IVDCONVCOUNT(I, J, K, BI, BJ) = 0.0
              END DO
            END DO
          END DO
          IMIN = -2
          IMAX = 93
          JMIN = -2
          JMAX = 43
          IF(DEBUGLEVEL .GE. 2) THEN
            CALL debug_msg('ENTERING UPWARD K LOOP', MYTHID)
          ENDIF
          DO K = 15, 1, (-1)
            KKEY = K + ITDKEY * 15 +(-15)
            IF((DODIAGSRHO .GE. 1) .OR.(USEGMREDI .OR.((K .GT. 1) .AND.
     > (IVDC_KAPPA .ne. 0.0D00)))) THEN
              IF(DEBUGLEVEL .GE. 2) THEN
                CALL debug_call('FIND_RHO', MYTHID)
              ENDIF
              CALL find_rho((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K), (K
     > ), THETA, SALT, RHOK, MYTHID)
              IF(K .GT. 1) THEN
                CALL find_rho((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K +(
     > -1)), (K), THETA, SALT, RHOKM1, MYTHID)
              ENDIF
              IF(DEBUGLEVEL .GE. 2) THEN
                CALL debug_call('GRAD_SIGMA', MYTHID)
              ENDIF
              CALL grad_sigma((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K),
     >  RHOK, RHOKM1, RHOK, SIGMAX, SIGMAY, SIGMAR, MYTHID)
            ENDIF
            IF((K .GT. 1) .AND.(IVDC_KAPPA .ne. 0.0D00)) THEN
              IF(DEBUGLEVEL .GE. 2) THEN
                CALL debug_call('CALC_IVDC', MYTHID)
              ENDIF
              CALL calc_ivdc((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K),
     >  RHOKM1, RHOK, MYTIME, MYITER, MYTHID)
            ENDIF
          END DO
          IF(DEBUGLEVEL .GE. 2) THEN
            CALL debug_call('EXTERNAL_FORCING_SURF', MYTHID)
          ENDIF
          CALL external_forcing_surf((BI), (BJ), IMIN, IMAX, JMIN, JMAX
     > , MYTIME, MYITER, MYTHID)
        END DO
      END DO
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_leave('DO_OCEANIC_PHYS', MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE do_stagger_fields_exchanges(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL exch_uv_xyz_rl
      EXTERNAL exch_xyz_rl
C
C     **** Statements ****
C
      IF(STAGGERTIMESTEP .AND. USEMULTIDIMADVEC) THEN
        CALL exch_uv_xyz_rl(UVEL, VVEL, (.TRUE.), MYTHID)
        CALL exch_xyz_rl(WVEL, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE dynamics(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use cd_code_vars_mod
      use grid_mod
      use tamc_mod
      use tamc_keys_mod
      use ffields_mod
      use eos_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL calc_grad_phi_surf
      EXTERNAL calc_phi_hyd
      EXTERNAL calc_viscosity
      EXTERNAL debug_enter
      EXTERNAL debug_leave
      EXTERNAL debug_stats_rl
      REAL(w2f__8) DPHIHYDX(-2 : 93, -2 : 43)
      REAL(w2f__8) DPHIHYDY(-2 : 93, -2 : 43)
      REAL(w2f__8) FVERU(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) FVERV(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) GUDISSIP(-2 : 93, -2 : 43)
      REAL(w2f__8) GVDISSIP(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      EXTERNAL impldiff
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) K
      REAL(w2f__8) KAPPARU(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) KAPPARV(-2 : 93, -2 : 43, 1 : 15)
      INTEGER(w2f__i4) KDOWN
      INTEGER(w2f__i4) KM1
      INTEGER(w2f__i4) KP1
      INTEGER(w2f__i4) KUP
      EXTERNAL mom_fluxform
      EXTERNAL mom_vecinv
      REAL(w2f__8) PHIHYDC(-2 : 93, -2 : 43)
      REAL(w2f__8) PHIHYDF(-2 : 93, -2 : 43)
      REAL(w2f__8) PHISURFX(-2 : 93, -2 : 43)
      REAL(w2f__8) PHISURFY(-2 : 93, -2 : 43)
      EXTERNAL timestep
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_enter('DYNAMICS', MYTHID)
      ENDIF
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          ACT1 = BI - MYBXLO(MYTHID)
          MAX1 = MYBXHI(MYTHID) - MYBXLO(MYTHID) + 1
          ACT2 = BJ - MYBYLO(MYTHID)
          MAX2 = MYBYHI(MYTHID) - MYBYLO(MYTHID) + 1
          ACT3 = MYTHID +(-1)
          MAX3 = NTX * NTY
          ACT4 = IKEY_DYNAMICS +(-1)
          IDYNKEY = ACT1 + ACT2 * MAX1 + MAX2 * ACT3 * MAX1 + MAX3 *
     >  MAX2 * ACT4 * MAX1 + 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                KAPPARU(I, J, K) = 0.0D00
                KAPPARV(I, J, K) = 0.0D00
                GU(I, J, K, BI, BJ) = 0.0D00
                GV(I, J, K, BI, BJ) = 0.0D00
              END DO
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              FVERU(I, J, 1) = 0.0D00
              FVERU(I, J, 2) = 0.0D00
              FVERV(I, J, 1) = 0.0D00
              FVERV(I, J, 2) = 0.0D00
              PHIHYDF(I, J) = 0.0D00
              PHIHYDC(I, J) = 0.0D00
              DPHIHYDX(I, J) = 0.0D00
              DPHIHYDY(I, J) = 0.0D00
              PHISURFX(I, J) = 0.0D00
              PHISURFY(I, J) = 0.0D00
              GUDISSIP(I, J) = 0.0D00
              GVDISSIP(I, J) = 0.0D00
            END DO
          END DO
          IMIN = 0
          IMAX = 91
          JMIN = 0
          JMAX = 41
          IF(IMPLICSURFPRESS .ne. 1.0D00) THEN
            CALL calc_grad_phi_surf((BI), (BJ), IMIN, IMAX, JMIN, JMAX,
     >  ETAN, PHISURFX, PHISURFY, MYTHID)
          ENDIF
          DO K = 1, 15, 1
            CALL calc_viscosity((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K)
     > , KAPPARU, KAPPARV, MYTHID)
          END DO
          DO K = 1, 15, 1
            KM1 = MAX(K +(-1), 1)
            KP1 = MIN(K + 1, 15)
            KUP = MOD(K + 1, 2) + 1
            KDOWN = MOD(K, 2) + 1
            KKEY = K + IDYNKEY * 15 +(-15)
            CALL calc_phi_hyd((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K),
     >  THETA, SALT, PHIHYDF, PHIHYDC, DPHIHYDX, DPHIHYDY, MYTIME,
     >  MYITER, MYTHID)
            IF(MOMSTEPPING) THEN
              IF(.NOT. VECTORINVARIANTMOMENTUM) THEN
                CALL mom_fluxform((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (
     > K), KUP, KDOWN, KAPPARU, KAPPARV, FVERU, FVERV, GUDISSIP,
     >  GVDISSIP, MYTIME, MYITER, MYTHID)
              ENDIF
              IF(VECTORINVARIANTMOMENTUM) THEN
                CALL mom_vecinv((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K)
     > , KUP, KDOWN, KAPPARU, KAPPARV, FVERU, FVERV, GUDISSIP, GVDISSIP
     > , MYTIME, MYITER, MYTHID)
              ENDIF
              CALL timestep((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K),
     >  DPHIHYDX, DPHIHYDY, PHISURFX, PHISURFY, GUDISSIP, GVDISSIP,
     >  MYTIME, MYITER, MYTHID)
            ENDIF
          END DO
          IF(IMPLICITVISCOSITY) THEN
            CALL impldiff((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (0),
     >  KAPPARU, RECIP_HFACW, GU, MYTHID)
            CALL impldiff((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (0),
     >  KAPPARV, RECIP_HFACS, GV, MYTHID)
          ENDIF
          IF(IMPLICITVISCOSITY .AND. USECDSCHEME) THEN
            CALL impldiff((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (0),
     >  KAPPARU, RECIP_HFACW, VVELD, MYTHID)
            CALL impldiff((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (0),
     >  KAPPARV, RECIP_HFACS, UVELD, MYTHID)
          ENDIF
        END DO
      END DO
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_stats_rl((1), ETAN, 'EtaN (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), UVEL, 'Uvel (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), VVEL, 'Vvel (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), WVEL, 'Wvel (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), THETA, 'Theta (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), SALT, 'Salt (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GU, 'Gu (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GV, 'Gv (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GT, 'Gt (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GS, 'Gs (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GUNM1, 'GuNm1 (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GVNM1, 'GvNm1 (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GTNM1, 'GtNm1 (DYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GSNM1, 'GsNm1 (DYNAMICS)', MYTHID)
      ENDIF
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_leave('DYNAMICS', MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE external_fields_load(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use ffields_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) AWGHT
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) BWGHT
      EXTERNAL exch_uv_xy_rs
      EXTERNAL exch_xy_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IFCYC
      INTEGER(w2f__i4) IFPRD
      INTEGER(w2f__i4) IFTM
      INTEGER(w2f__i4) IMYTM
      INTEGER(w2f__i4) INTIME0
      INTEGER(w2f__i4) INTIME1
      INTEGER(w2f__i4) J
      EXTERNAL mdsreadfield
      INTEGER(w2f__i4) NFORCINGPERIODS
      REAL(w2f__8) RDT
      REAL(w2f__8) TMP1WGHT
      REAL(w2f__8) TMP2WGHT
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      IF(PERIODICEXTERNALFORCING) THEN
        RDT = 1D00 / DELTATCLOCK
        NFORCINGPERIODS = NINT(EXTERNFORCINGCYCLE / EXTERNFORCINGPERIOD
     > )
        IMYTM = NINT(MYTIME * RDT)
        IFPRD = NINT(RDT * EXTERNFORCINGPERIOD)
        IFCYC = NINT(RDT * EXTERNFORCINGCYCLE)
        IFTM = MOD(IFCYC + IMYTM -(IFPRD / 2), IFCYC)
        INTIME0 = (IFTM / IFPRD) + 1
        INTIME1 = MOD(INTIME0, NFORCINGPERIODS) + 1
        TMP1WGHT = FLOAT(IFTM - IFPRD *(INTIME0 +(-1)))
        TMP2WGHT = FLOAT(IFPRD)
        AWGHT = TMP1WGHT / TMP2WGHT
        BWGHT = 1.0D00 - AWGHT
        IF((MYITER .eq. NITER0) .OR.((IFTM - IFPRD *(INTIME0 +(-1)))
     >  .eq. 0)) THEN
          IF(MYTHID .eq. 1) THEN
            WRITE(STANDARDMESSAGEUNIT, '(A,2I5,I10,1P1E20.12)')
     >  'S/R EXTERNAL_FIELDS_LOAD: Reading new data:', INTIME0, INTIME1
     > , MYITER, MYTIME
            IF(ZONALWINDFILE .NE. ' ') THEN
              CALL mdsreadfield(ZONALWINDFILE, READBINARYPREC, 'RS', (1
     > ), TAUX0, INTIME0, MYTHID)
              CALL mdsreadfield(ZONALWINDFILE, READBINARYPREC, 'RS', (1
     > ), TAUX1, INTIME1, MYTHID)
            ENDIF
            IF(MERIDWINDFILE .NE. ' ') THEN
              CALL mdsreadfield(MERIDWINDFILE, READBINARYPREC, 'RS', (1
     > ), TAUY0, INTIME0, MYTHID)
              CALL mdsreadfield(MERIDWINDFILE, READBINARYPREC, 'RS', (1
     > ), TAUY1, INTIME1, MYTHID)
            ENDIF
            IF(SURFQFILE .NE. ' ') THEN
              CALL mdsreadfield(SURFQFILE, READBINARYPREC, 'RS', (1),
     >  QNET0, INTIME0, MYTHID)
              CALL mdsreadfield(SURFQFILE, READBINARYPREC, 'RS', (1),
     >  QNET1, INTIME1, MYTHID)
            ELSE
              IF(SURFQNETFILE .NE. ' ') THEN
                CALL mdsreadfield(SURFQNETFILE, READBINARYPREC, 'RS', (
     > 1), QNET0, INTIME0, MYTHID)
                CALL mdsreadfield(SURFQNETFILE, READBINARYPREC, 'RS', (
     > 1), QNET1, INTIME1, MYTHID)
              ENDIF
            ENDIF
            IF(EMPMRFILE .NE. ' ') THEN
              CALL mdsreadfield(EMPMRFILE, READBINARYPREC, 'RS', (1),
     >  EMPMR0, INTIME0, MYTHID)
              CALL mdsreadfield(EMPMRFILE, READBINARYPREC, 'RS', (1),
     >  EMPMR1, INTIME1, MYTHID)
            ENDIF
            IF(SALTFLUXFILE .NE. ' ') THEN
              CALL mdsreadfield(SALTFLUXFILE, READBINARYPREC, 'RS', (1)
     > , SALTFLUX0, INTIME0, MYTHID)
              CALL mdsreadfield(SALTFLUXFILE, READBINARYPREC, 'RS', (1)
     > , SALTFLUX1, INTIME1, MYTHID)
            ENDIF
            IF(THETACLIMFILE .NE. ' ') THEN
              CALL mdsreadfield(THETACLIMFILE, READBINARYPREC, 'RS', (1
     > ), SST0, INTIME0, MYTHID)
              CALL mdsreadfield(THETACLIMFILE, READBINARYPREC, 'RS', (1
     > ), SST1, INTIME1, MYTHID)
            ENDIF
            IF(SALTCLIMFILE .NE. ' ') THEN
              CALL mdsreadfield(SALTCLIMFILE, READBINARYPREC, 'RS', (1)
     > , SSS0, INTIME0, MYTHID)
              CALL mdsreadfield(SALTCLIMFILE, READBINARYPREC, 'RS', (1)
     > , SSS1, INTIME1, MYTHID)
            ENDIF
          ENDIF
          CALL exch_xy_rl(SST0, MYTHID)
          CALL exch_xy_rl(SST1, MYTHID)
          CALL exch_xy_rl(SSS0, MYTHID)
          CALL exch_xy_rl(SSS1, MYTHID)
          CALL exch_uv_xy_rs(TAUX0, TAUY0, (.TRUE.), MYTHID)
          CALL exch_uv_xy_rs(TAUX1, TAUY1, (.TRUE.), MYTHID)
          CALL exch_xy_rl(QNET0, MYTHID)
          CALL exch_xy_rl(QNET1, MYTHID)
          CALL exch_xy_rl(EMPMR0, MYTHID)
          CALL exch_xy_rl(EMPMR1, MYTHID)
          CALL exch_xy_rl(SALTFLUX0, MYTHID)
          CALL exch_xy_rl(SALTFLUX1, MYTHID)
        ENDIF
        doloop_ub = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub, 1
          doloop_ub0 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub0, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                SST(I, J, BI, BJ) = (SST0(I, J, BI, BJ) * BWGHT + SST1(
     > I, J, BI, BJ) * AWGHT)
                SSS(I, J, BI, BJ) = (SSS0(I, J, BI, BJ) * BWGHT + SSS1(
     > I, J, BI, BJ) * AWGHT)
                FU(I, J, BI, BJ) = (TAUX0(I, J, BI, BJ) * BWGHT + TAUX1
     > (I, J, BI, BJ) * AWGHT)
                FV(I, J, BI, BJ) = (TAUY0(I, J, BI, BJ) * BWGHT + TAUY1
     > (I, J, BI, BJ) * AWGHT)
                QNET(I, J, BI, BJ) = (QNET0(I, J, BI, BJ) * BWGHT +
     >  QNET1(I, J, BI, BJ) * AWGHT)
                EMPMR(I, J, BI, BJ) = (EMPMR0(I, J, BI, BJ) * BWGHT +
     >  EMPMR1(I, J, BI, BJ) * AWGHT)
                SALTFLUX(I, J, BI, BJ) = (SALTFLUX0(I, J, BI, BJ) *
     >  BWGHT + SALTFLUX1(I, J, BI, BJ) * AWGHT)
              END DO
            END DO
          END DO
        END DO
        IF((DEBUGLEVEL .GE. 1) .AND.(MYTIME .LT. 6.2208D+07)) THEN
          IF(MYTHID .eq. 1) THEN
            WRITE(STANDARDMESSAGEUNIT, '(a,1p7e12.4,2i6,2e12.4)')
     >  'time,SST,SSS,fu,fv,Q,E-P,i0,i1,a,b = ', MYTIME, SST(1, 40, 1,
     >  1), SSS(1, 40, 1, 1), FU(1, 40, 1, 1), FV(1, 40, 1, 1), QNET(1,
     >  40, 1, 1), EMPMR(1, 40, 1, 1), INTIME0, INTIME1, AWGHT, BWGHT
            WRITE(STANDARDMESSAGEUNIT, '(a,1p4e12.4,2E23.15)')
     >  'time,fu0,fu1,fu = ', MYTIME, TAUX0(1, 40, 1, 1), TAUX1(1, 40,
     >  1, 1), FU(1, 40, 1, 1), AWGHT, BWGHT
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE lef_zero(ARR, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) ARR(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ARR(I, J, BI, BJ) = 0.0
            END DO
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE external_forcing_u(IMIN, IMAX, JMIN, JMAX, BI, BJ,
     >  KLEV, MYTIME, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) KLEV
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KSURFACE
C
C     **** Statements ****
C
      IF(FLUIDISAIR) THEN
        KSURFACE = 0
      ELSE
        IF(USINGPCOORDS) THEN
          KSURFACE = 15
        ELSE
          KSURFACE = 1
        ENDIF
      ENDIF
      IF(KLEV .eq. KSURFACE) THEN
        DO J = 0, 41, 1
          DO I = 1, 91, 1
            GU(I, J, KLEV, BI, BJ) = (GU(I, J, KLEV, BI, BJ) +
     >  RECIP_HFACW(I, J, KLEV, BI, BJ) * RECIP_DRF(KLEV) *
     >  SURFACEFORCINGU(I, J, BI, BJ) * FOFACMOM)
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE external_forcing_v(IMIN, IMAX, JMIN, JMAX, BI, BJ,
     >  KLEV, MYTIME, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) KLEV
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KSURFACE
C
C     **** Statements ****
C
      IF(FLUIDISAIR) THEN
        KSURFACE = 0
      ELSE
        IF(USINGPCOORDS) THEN
          KSURFACE = 15
        ELSE
          KSURFACE = 1
        ENDIF
      ENDIF
      IF(KLEV .eq. KSURFACE) THEN
        DO J = 1, 41, 1
          DO I = 0, 91, 1
            GV(I, J, KLEV, BI, BJ) = (GV(I, J, KLEV, BI, BJ) +
     >  RECIP_HFACS(I, J, KLEV, BI, BJ) * RECIP_DRF(KLEV) *
     >  SURFACEFORCINGV(I, J, BI, BJ) * FOFACMOM)
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE external_forcing_t(IMIN, IMAX, JMIN, JMAX, BI, BJ,
     >  KLEV, MYTIME, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) KLEV
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KSURFACE
C
C     **** Statements ****
C
      IF(FLUIDISAIR) THEN
        KSURFACE = 0
      ELSE
        IF(USINGPCOORDS) THEN
          KSURFACE = 15
        ELSE
          KSURFACE = 1
        ENDIF
      ENDIF
      IF(KLEV .eq. KSURFACE) THEN
        DO J = 1, 40, 1
          DO I = 1, 90, 1
            GT(I, J, KLEV, BI, BJ) = (GT(I, J, KLEV, BI, BJ) +
     >  RECIP_HFACC(I, J, KLEV, BI, BJ) * RECIP_DRF(KLEV) *
     >  SURFACEFORCINGT(I, J, BI, BJ))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE external_forcing_s(IMIN, IMAX, JMIN, JMAX, BI, BJ,
     >  KLEV, MYTIME, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) KLEV
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KSURFACE
C
C     **** Statements ****
C
      IF(FLUIDISAIR) THEN
        KSURFACE = 0
      ELSE
        IF(USINGPCOORDS) THEN
          KSURFACE = 15
        ELSE
          KSURFACE = 1
        ENDIF
      ENDIF
      IF(KLEV .eq. KSURFACE) THEN
        DO J = 1, 40, 1
          DO I = 1, 90, 1
            GS(I, J, KLEV, BI, BJ) = (GS(I, J, KLEV, BI, BJ) +
     >  RECIP_HFACC(I, J, KLEV, BI, BJ) * RECIP_DRF(KLEV) *
     >  SURFACEFORCINGS(I, J, BI, BJ))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE external_forcing_surf(BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use ffields_mod
      use dynvars_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) KS
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
C
C     **** Statements ****
C
      IF(USINGPCOORDS) THEN
        KS = 15
      ELSE
        KS = 1
      ENDIF
      IF(DOSALTCLIMRELAX .OR. DOTHETACLIMRELAX) THEN
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            SURFACEFORCINGT(I, J, BI, BJ) = (-(HFACC(I, J, KS, BI, BJ)
     >  * DRF(KS) * LAMBDATHETACLIMRELAX(I, J, BI, BJ) *(THETA(I, J, KS
     > , BI, BJ) - SST(I, J, BI, BJ))))
            SURFACEFORCINGS(I, J, BI, BJ) = (-(HFACC(I, J, KS, BI, BJ)
     >  * DRF(KS) * LAMBDASALTCLIMRELAX(I, J, BI, BJ) *(SALT(I, J, KS,
     >  BI, BJ) - SSS(I, J, BI, BJ))))
          END DO
        END DO
      ELSE
        doloop_ub1 = JMAX
        DO J = JMIN, doloop_ub1, 1
          doloop_ub2 = IMAX
          DO I = IMIN, doloop_ub2, 1
            SURFACEFORCINGT(I, J, BI, BJ) = 0.0D00
            SURFACEFORCINGS(I, J, BI, BJ) = 0.0D00
          END DO
        END DO
      ENDIF
      doloop_ub3 = JMAX
      DO J = JMIN, doloop_ub3, 1
        doloop_ub4 = IMAX
        DO I = IMIN, doloop_ub4, 1
          SURFACEFORCINGU(I, J, BI, BJ) = (RECIP_RHOCONST * FU(I, J, BI
     > , BJ) * HORIVERTRATIO)
          SURFACEFORCINGV(I, J, BI, BJ) = (RECIP_RHOCONST * FV(I, J, BI
     > , BJ) * HORIVERTRATIO)
          SURFACEFORCINGT(I, J, BI, BJ) = (SURFACEFORCINGT(I, J, BI, BJ
     > ) - RECIP_RHOCONST * HORIVERTRATIO * RECIP_CP *(QNET(I, J, BI,
     >  BJ)))
          SURFACEFORCINGS(I, J, BI, BJ) = (SURFACEFORCINGS(I, J, BI, BJ
     > ) - RECIP_RHOCONST * SALTFLUX(I, J, BI, BJ) * HORIVERTRATIO)
        END DO
      END DO
      IF(.TRUE.) THEN
        IF(CONVERTFW2SALT .eq.(-1.0D00)) THEN
          doloop_ub5 = JMAX
          DO J = JMIN, doloop_ub5, 1
            doloop_ub6 = IMAX
            DO I = IMIN, doloop_ub6, 1
              SURFACEFORCINGS(I, J, BI, BJ) = (SURFACEFORCINGS(I, J, BI
     > , BJ) + CONVERTEMP2RUNIT * EMPMR(I, J, BI, BJ) * SALT(I, J, KS,
     >  BI, BJ))
            END DO
          END DO
        ELSE
          doloop_ub7 = JMAX
          DO J = JMIN, doloop_ub7, 1
            doloop_ub8 = IMAX
            DO I = IMIN, doloop_ub8, 1
              SURFACEFORCINGS(I, J, BI, BJ) = (SURFACEFORCINGS(I, J, BI
     > , BJ) + CONVERTEMP2RUNIT * EMPMR(I, J, BI, BJ) * CONVERTFW2SALT)
            END DO
          END DO
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE find_alpha(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KREF,
     >  ALPHALOC)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KREF
      REAL(w2f__8) ALPHALOC(-2 : 93, -2 : 43)
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) BULKMOD(-2 : 93, -2 : 43)
      REAL(w2f__8) DDEN_DTHETA
      REAL(w2f__8) DKDTHETA
      REAL(w2f__8) DKDTHETAFRESH
      REAL(w2f__8) DKDTHETAPRES
      REAL(w2f__8) DKDTHETASALT
      REAL(w2f__8) DNUM_DTHETA
      REAL(w2f__8) DRHOP0DTHETA
      REAL(w2f__8) DRHOP0DTHETAFRESH
      REAL(w2f__8) DRHOP0DTHETASALT
      EXTERNAL find_bulkmod
      EXTERNAL find_rhoden
      EXTERNAL find_rhonum
      EXTERNAL find_rhop0
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) LOCPRES(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) P1
      REAL(w2f__8) P1T1
      REAL(w2f__8) P2
      EXTERNAL pressure_for_eos
      REAL(w2f__8) REFSALT
      REAL(w2f__8) REFTEMP
      REAL(w2f__8) RHODEN(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOLOC(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOP0(-2 : 93, -2 : 43)
      REAL(w2f__8) S1
      REAL(w2f__8) S3O2
      REAL(w2f__8) SP
      REAL(w2f__8) SP5
      REAL(w2f__8) T1
      REAL(w2f__8) T2
      REAL(w2f__8) T3
      REAL(w2f__8) TP
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
C
C     **** Statements ****
C
      IF(EQUATIONOFSTATE .EQ. 'LINEAR') THEN
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            ALPHALOC(I, J) = (-(RHONIL * TALPHA))
          END DO
        END DO
      ELSE
        IF(EQUATIONOFSTATE .EQ. 'POLY3') THEN
          REFTEMP = EOSREFT(KREF)
          REFSALT = EOSREFS(KREF)
          doloop_ub1 = JMAX
          DO J = JMIN, doloop_ub1, 1
            doloop_ub2 = IMAX
            DO I = IMIN, doloop_ub2, 1
              TP = THETA(I, J, K, BI, BJ) - REFTEMP
              SP = SALT(I, J, K, BI, BJ) - REFSALT
              ALPHALOC(I, J) = (EOSC(1, KREF) + SP *(EOSC(4, KREF) +
     >  EOSC(8, KREF) * SP) + TP *(EOSC(6, KREF) * TP * 3.0D00 +(EOSC(3
     > , KREF) + EOSC(7, KREF) * SP) * 2.0D00))
            END DO
          END DO
        ELSE
          IF((EQUATIONOFSTATE(1_w2f__i8 : 5) .EQ. 'JMD95') .OR.(
     > EQUATIONOFSTATE .EQ. 'UNESCO')) THEN
            CALL pressure_for_eos(BI, BJ, IMIN, IMAX, JMIN, JMAX, KREF,
     >  LOCPRES, MYTHID)
            CALL find_rhop0(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, THETA,
     >  SALT, RHOP0, MYTHID)
            CALL find_bulkmod(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, THETA, SALT, BULKMOD, MYTHID)
            doloop_ub3 = JMAX
            DO J = JMIN, doloop_ub3, 1
              doloop_ub4 = IMAX
              DO I = IMIN, doloop_ub4, 1
                T1 = THETA(I, J, K, BI, BJ)
                T2 = T1 * T1
                T3 = T1 * T2
                S1 = SALT(I, J, K, BI, BJ)
                IF(S1 .GT. 0.0D00) THEN
                  S3O2 = SQRT(S1 * S1 * S1)
                ELSE
                  S1 = 0.0D00
                  S3O2 = 0.0D00
                ENDIF
                P1 = LOCPRES(I, J) * 1.0000000000000000818D-05
                P2 = P1 * P1
                DRHOP0DTHETAFRESH = EOSJMDCFW(2) + T1 * EOSJMDCFW(3) *
     >  2.0D00 + T2 * EOSJMDCFW(4) * 3.0D00 + T3 * EOSJMDCFW(5) *
     >  4.0D00 + T1 * T3 * EOSJMDCFW(6) * 5.0D00
                DRHOP0DTHETASALT = S1 *(EOSJMDCSW(2) + T1 * EOSJMDCSW(3
     > ) * 2.0D00 + T2 * EOSJMDCSW(4) * 3.0D00 + T3 * EOSJMDCSW(5) *
     >  4.0D00) + S3O2 *(EOSJMDCSW(7) + T1 * EOSJMDCSW(8) * 2.0D00)
                DKDTHETAFRESH = EOSJMDCKFW(2) + T1 * EOSJMDCKFW(3) *
     >  2.0D00 + T2 * EOSJMDCKFW(4) * 3.0D00 + T3 * EOSJMDCKFW(5) *
     >  4.0D00
                DKDTHETASALT = S1 *(EOSJMDCKSW(2) + T1 * EOSJMDCKSW(3)
     >  * 2.0D00 + T2 * EOSJMDCKSW(4) * 3.0D00) + S3O2 *(EOSJMDCKSW(6)
     >  + T1 * EOSJMDCKSW(7) * 2.0D00)
                DKDTHETAPRES = P1 *(EOSJMDCKP(2) + T1 * EOSJMDCKP(3) *
     >  2.0D00 + T2 * EOSJMDCKP(4) * 3.0D00) + P1 * S1 *(EOSJMDCKP(6) +
     >  T1 * EOSJMDCKP(7) * 2.0D00) + P2 *(EOSJMDCKP(10) + T1 *
     >  EOSJMDCKP(11) * 2.0D00) + P2 * S1 *(EOSJMDCKP(13) + T1 *
     >  EOSJMDCKP(14) * 2.0D00)
                DRHOP0DTHETA = DRHOP0DTHETAFRESH + DRHOP0DTHETASALT
                DKDTHETA = DKDTHETAPRES + DKDTHETAFRESH + DKDTHETASALT
                ALPHALOC(I, J) = ((DRHOP0DTHETA *(BULKMOD(I, J) ** 2) -
     >  DRHOP0DTHETA * BULKMOD(I, J) * P1 - DKDTHETA * RHOP0(I, J) * P1
     > ) /((BULKMOD(I, J) - P1) ** 2))
              END DO
            END DO
          ELSE
            IF(EQUATIONOFSTATE .EQ. 'MDJWF') THEN
              CALL pressure_for_eos(BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  KREF, LOCPRES, MYTHID)
              CALL find_rhonum(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, THETA, SALT, RHOLOC, MYTHID)
              CALL find_rhoden(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, THETA, SALT, RHODEN, MYTHID)
              doloop_ub5 = JMAX
              DO J = JMIN, doloop_ub5, 1
                doloop_ub6 = IMAX
                DO I = IMIN, doloop_ub6, 1
                  T1 = THETA(I, J, K, BI, BJ)
                  T2 = T1 * T1
                  S1 = SALT(I, J, K, BI, BJ)
                  IF(S1 .GT. 0.0D00) THEN
                    SP5 = SQRT(S1)
                  ELSE
                    S1 = 0.0D00
                    SP5 = 0.0D00
                  ENDIF
                  P1 = LOCPRES(I, J) * 1.00000000000000004792D-04
                  P1T1 = P1 * T1
                  DNUM_DTHETA = EOSMDJWFNUM(1) + T1 *(EOSMDJWFNUM(2) *
     >  2.0D00 + T1 * EOSMDJWFNUM(3) * 3.0D00) + EOSMDJWFNUM(5) * S1 +
     >  P1T1 *(EOSMDJWFNUM(8) * 2.0D00 + P1 * EOSMDJWFNUM(11) * 2.0D00)
                  DDEN_DTHETA = EOSMDJWFDEN(1) + T1 *(EOSMDJWFDEN(2) *
     >  2.0D00 + T1 *(EOSMDJWFDEN(3) * 3.0D00 + T1 * EOSMDJWFDEN(4) *
     >  4.0D00)) + S1 *(EOSMDJWFDEN(6) + T1 *(SP5 * EOSMDJWFDEN(9) *
     >  2.0D00 + T1 * EOSMDJWFDEN(7) * 3.0D00)) + P1 * P1 *(EOSMDJWFDEN
     > (12) * P1 + T2 * EOSMDJWFDEN(11) * 3.0D00)
                  ALPHALOC(I, J) = (RHODEN(I, J) *(DNUM_DTHETA -
     >  DDEN_DTHETA *(RHODEN(I, J) * RHOLOC(I, J))))
                END DO
              END DO
            ELSE
              WRITE(*, *) 'FIND_ALPHA: equationOfState = ',
     >  EQUATIONOFSTATE
              STOP 'FIND_ALPHA: "equationOfState" has illegal value'
              RETURN
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE find_beta(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KREF,
     >  BETALOC)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KREF
      REAL(w2f__8) BETALOC(-2 : 93, -2 : 43)
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) BULKMOD(-2 : 93, -2 : 43)
      REAL(w2f__8) DDEN_DSALT
      REAL(w2f__8) DKDS
      REAL(w2f__8) DKDSPRES
      REAL(w2f__8) DKDSSALT
      REAL(w2f__8) DNUM_DSALT
      REAL(w2f__8) DRHOP0DS
      EXTERNAL find_bulkmod
      EXTERNAL find_rhoden
      EXTERNAL find_rhonum
      EXTERNAL find_rhop0
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) LOCPRES(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) P1
      REAL(w2f__8) P1T1
      EXTERNAL pressure_for_eos
      REAL(w2f__8) REFSALT
      REAL(w2f__8) REFTEMP
      REAL(w2f__8) RHODEN(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOLOC(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOP0(-2 : 93, -2 : 43)
      REAL(w2f__8) S1
      REAL(w2f__8) S3O2
      REAL(w2f__8) SP
      REAL(w2f__8) SP5
      REAL(w2f__8) T1
      REAL(w2f__8) T2
      REAL(w2f__8) T3
      REAL(w2f__8) TP
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
C
C     **** Statements ****
C
      IF(EQUATIONOFSTATE .EQ. 'LINEAR') THEN
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            BETALOC(I, J) = (RHONIL * SBETA)
          END DO
        END DO
      ELSE
        IF(EQUATIONOFSTATE .EQ. 'POLY3') THEN
          REFTEMP = EOSREFT(KREF)
          REFSALT = EOSREFS(KREF)
          doloop_ub1 = JMAX
          DO J = JMIN, doloop_ub1, 1
            doloop_ub2 = IMAX
            DO I = IMIN, doloop_ub2, 1
              TP = THETA(I, J, K, BI, BJ) - REFTEMP
              SP = SALT(I, J, K, BI, BJ) - REFSALT
              BETALOC(I, J) = (EOSC(2, KREF) + SP *(EOSC(5, KREF) *
     >  2.0D00 + EOSC(9, KREF) * SP * 3.0D00) + TP *(EOSC(4, KREF) +
     >  EOSC(7, KREF) * TP + EOSC(8, KREF) * SP * 2.0D00))
            END DO
          END DO
        ELSE
          IF((EQUATIONOFSTATE(1_w2f__i8 : 5) .EQ. 'JMD95') .OR.(
     > EQUATIONOFSTATE .EQ. 'UNESCO')) THEN
            CALL pressure_for_eos(BI, BJ, IMIN, IMAX, JMIN, JMAX, KREF,
     >  LOCPRES, MYTHID)
            CALL find_rhop0(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, THETA,
     >  SALT, RHOP0, MYTHID)
            CALL find_bulkmod(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, THETA, SALT, BULKMOD, MYTHID)
            doloop_ub3 = JMAX
            DO J = JMIN, doloop_ub3, 1
              doloop_ub4 = IMAX
              DO I = IMIN, doloop_ub4, 1
                T1 = THETA(I, J, K, BI, BJ)
                T2 = T1 * T1
                T3 = T1 * T2
                S1 = SALT(I, J, K, BI, BJ)
                IF(S1 .GT. 0.0D00) THEN
                  S3O2 = SQRT(S1) * 1.5D00
                ELSE
                  S1 = 0.0D00
                  S3O2 = 0.0D00
                ENDIF
                P1 = LOCPRES(I, J) * 1.0000000000000000818D-05
                DRHOP0DS = 0.0D00
                DRHOP0DS = EOSJMDCSW(1) + DRHOP0DS + EOSJMDCSW(2) * T1
     >  + EOSJMDCSW(3) * T2 + EOSJMDCSW(4) * T3 + T1 * EOSJMDCSW(5) *
     >  T3 + S3O2 *(EOSJMDCSW(6) + EOSJMDCSW(7) * T1 + EOSJMDCSW(8) *
     >  T2) + S1 * EOSJMDCSW(9) * 2.0D00
                DKDS = 0.0D00
                DKDSSALT = EOSJMDCKSW(1) + EOSJMDCKSW(2) * T1 +
     >  EOSJMDCKSW(3) * T2 + EOSJMDCKSW(4) * T3 + S3O2 *(EOSJMDCKSW(5)
     >  + EOSJMDCKSW(6) * T1 + EOSJMDCKSW(7) * T2)
                DKDSPRES = EOSJMDCKP(8) * P1 * S3O2 + P1 *(EOSJMDCKP(5)
     >  + EOSJMDCKP(6) * T1 + EOSJMDCKP(7) * T2) + P1 * P1 *(EOSJMDCKP(
     > 12) + EOSJMDCKP(13) * T1 + EOSJMDCKP(14) * T2)
                DKDS = DKDSPRES + DKDSSALT
                BETALOC(I, J) = ((DRHOP0DS *(BULKMOD(I, J) ** 2) -
     >  DRHOP0DS * BULKMOD(I, J) * P1 - DKDS * RHOP0(I, J) * P1) /((
     > BULKMOD(I, J) - P1) ** 2))
              END DO
            END DO
          ELSE
            IF(EQUATIONOFSTATE .EQ. 'MDJWF') THEN
              CALL pressure_for_eos(BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  KREF, LOCPRES, MYTHID)
              CALL find_rhonum(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, THETA, SALT, RHOLOC, MYTHID)
              CALL find_rhoden(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, THETA, SALT, RHODEN, MYTHID)
              doloop_ub5 = JMAX
              DO J = JMIN, doloop_ub5, 1
                doloop_ub6 = IMAX
                DO I = IMIN, doloop_ub6, 1
                  T1 = THETA(I, J, K, BI, BJ)
                  T2 = T1 * T1
                  S1 = SALT(I, J, K, BI, BJ)
                  IF(S1 .GT. 0.0D00) THEN
                    SP5 = SQRT(S1)
                  ELSE
                    S1 = 0.0D00
                    SP5 = 0.0D00
                  ENDIF
                  P1 = LOCPRES(I, J) * 1.00000000000000004792D-04
                  P1T1 = P1 * T1
                  DNUM_DSALT = EOSMDJWFNUM(4) + EOSMDJWFNUM(5) * T1 +
     >  S1 * EOSMDJWFNUM(6) * 2.0D00 + EOSMDJWFNUM(9) * P1
                  DDEN_DSALT = EOSMDJWFDEN(5) + T1 *(EOSMDJWFDEN(6) +
     >  EOSMDJWFDEN(7) * T2) + SP5 * 1.5D00 *(EOSMDJWFDEN(8) +
     >  EOSMDJWFDEN(9) * T2)
                  BETALOC(I, J) = (RHODEN(I, J) *(DNUM_DSALT -
     >  DDEN_DSALT *(RHODEN(I, J) * RHOLOC(I, J))))
                END DO
              END DO
            ELSE
              WRITE(*, *) 'FIND_BETA: equationOfState = ',
     >  EQUATIONOFSTATE
              STOP 'FIND_BETA: "equationOfState" has illegal value'
              RETURN
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE find_rho(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, KREF, TFLD
     > , SFLD, RHOLOC, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KREF
      REAL(w2f__8) TFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RHOLOC(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) BULKMOD(-2 : 93, -2 : 43)
      REAL(w2f__8) DELTASIG
      REAL(w2f__8) DRHO
      EXTERNAL find_bulkmod
      EXTERNAL find_rhoden
      EXTERNAL find_rhonum
      EXTERNAL find_rhop0
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) LOCPRES(-2 : 93, -2 : 43)
      CHARACTER(512) MSGBUF
      EXTERNAL pressure_for_eos
      EXTERNAL print_error
      REAL(w2f__8) REFSALT
      REAL(w2f__8) REFTEMP
      REAL(w2f__8) RHODEN(-2 : 93, -2 : 43)
      REAL(w2f__8) RHONUM(-2 : 93, -2 : 43)
      REAL(w2f__8) RHOP0(-2 : 93, -2 : 43)
      REAL(w2f__8) SIGREF
      REAL(w2f__8) SP
      REAL(w2f__8) TP
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          RHOLOC(I, J) = 0.0D00
          RHOP0(I, J) = 0.0D00
          BULKMOD(I, J) = 0.0D00
        END DO
      END DO
      IF(EQUATIONOFSTATE .EQ. 'LINEAR') THEN
        REFTEMP = TREF(KREF)
        REFSALT = SREF(KREF)
        DRHO = RHONIL - RHOCONST
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            RHOLOC(I, J) = (DRHO + RHONIL *(SBETA *(SFLD(I, J, K, BI,
     >  BJ) - REFSALT) - TALPHA *(TFLD(I, J, K, BI, BJ) - REFTEMP)))
          END DO
        END DO
      ELSE
        IF(EQUATIONOFSTATE .EQ. 'POLY3') THEN
          REFTEMP = EOSREFT(KREF)
          REFSALT = EOSREFS(KREF)
          SIGREF = EOSSIG0(KREF) +(1.0D+03 - RHOCONST)
          doloop_ub1 = JMAX
          DO J = JMIN, doloop_ub1, 1
            doloop_ub2 = IMAX
            DO I = IMIN, doloop_ub2, 1
              TP = TFLD(I, J, K, BI, BJ) - REFTEMP
              SP = SFLD(I, J, K, BI, BJ) - REFSALT
              DELTASIG = SP *(EOSC(2, KREF) + SP *(EOSC(5, KREF) + EOSC
     > (9, KREF) * SP)) + TP *(EOSC(1, KREF) + SP *(EOSC(4, KREF) +
     >  EOSC(8, KREF) * SP) + TP *(EOSC(3, KREF) + EOSC(6, KREF) * TP +
     >  EOSC(7, KREF) * SP))
              RHOLOC(I, J) = (DELTASIG + SIGREF)
            END DO
          END DO
        ELSE
          IF((EQUATIONOFSTATE(1_w2f__i8 : 5) .EQ. 'JMD95') .OR.(
     > EQUATIONOFSTATE .EQ. 'UNESCO')) THEN
            CALL pressure_for_eos(BI, BJ, IMIN, IMAX, JMIN, JMAX, KREF,
     >  LOCPRES, MYTHID)
            CALL find_rhop0(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, TFLD,
     >  SFLD, RHOP0, MYTHID)
            CALL find_bulkmod(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, TFLD, SFLD, BULKMOD, MYTHID)
            doloop_ub3 = JMAX
            DO J = JMIN, doloop_ub3, 1
              doloop_ub4 = IMAX
              DO I = IMIN, doloop_ub4, 1
                RHOLOC(I, J) = ((RHOP0(I, J) /(1.0D00 -((LOCPRES(I, J)
     >  * 1.0000000000000000818D-05) / BULKMOD(I, J)))) - RHOCONST)
              END DO
            END DO
          ELSE
            IF(EQUATIONOFSTATE .EQ. 'MDJWF') THEN
              CALL pressure_for_eos(BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  KREF, LOCPRES, MYTHID)
              CALL find_rhonum(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, TFLD, SFLD, RHONUM, MYTHID)
              CALL find_rhoden(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, TFLD, SFLD, RHODEN, MYTHID)
              doloop_ub5 = JMAX
              DO J = JMIN, doloop_ub5, 1
                doloop_ub6 = IMAX
                DO I = IMIN, doloop_ub6, 1
                  RHOLOC(I, J) = (RHODEN(I, J) * RHONUM(I, J) -
     >  RHOCONST)
                END DO
              END DO
            ELSE
              IF(EQUATIONOFSTATE .EQ. 'IDEALG') THEN
              ELSE
                WRITE(MSGBUF, '(3a)') ' FIND_RHO: equationOfState = "',
     >  EQUATIONOFSTATE, '"'
                CALL print_error(MSGBUF, MYTHID)
                STOP 'ABNORMAL END: S/R FIND_RHO'
                RETURN
              ENDIF
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE find_rhop0(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, TFLD,
     >  SFLD, RHOP0, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) TFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RHOP0(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RFRESH
      REAL(w2f__8) RSALT
      REAL(w2f__8) S
      REAL(w2f__8) S3O2
      REAL(w2f__8) T
      REAL(w2f__8) T2
      REAL(w2f__8) T3
      REAL(w2f__8) T4
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          T = TFLD(I, J, K, BI, BJ)
          T2 = T * T
          T3 = T * T2
          T4 = T * T3
          S = SFLD(I, J, K, BI, BJ)
          IF(S .GT. 0.0D00) THEN
            S3O2 = S * SQRT(S)
          ELSE
            S = 0.0D00
            S3O2 = 0.0D00
          ENDIF
          RFRESH = EOSJMDCFW(1) + EOSJMDCFW(2) * T + EOSJMDCFW(3) * T2
     >  + EOSJMDCFW(4) * T3 + EOSJMDCFW(5) * T4 + T * EOSJMDCFW(6) * T4
          RSALT = S *(EOSJMDCSW(1) + EOSJMDCSW(2) * T + EOSJMDCSW(3) *
     >  T2 + EOSJMDCSW(4) * T3 + EOSJMDCSW(5) * T4) + S3O2 *(EOSJMDCSW(
     > 6) + EOSJMDCSW(7) * T + EOSJMDCSW(8) * T2) + S * EOSJMDCSW(9) *
     >  S
          RHOP0(I, J) = (RFRESH + RSALT)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE find_bulkmod(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, TFLD, SFLD, BULKMOD, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) LOCPRES(-2 : 93, -2 : 43)
      REAL(w2f__8) TFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) BULKMOD(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) BMFRESH
      REAL(w2f__8) BMPRES
      REAL(w2f__8) BMSALT
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) P
      REAL(w2f__8) P2
      REAL(w2f__8) S
      REAL(w2f__8) S3O2
      REAL(w2f__8) T
      REAL(w2f__8) T2
      REAL(w2f__8) T3
      REAL(w2f__8) T4
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          T = TFLD(I, J, K, BI, BJ)
          T2 = T * T
          T3 = T * T2
          T4 = T * T3
          S = SFLD(I, J, K, BI, BJ)
          IF(S .GT. 0.0D00) THEN
            S3O2 = S * SQRT(S)
          ELSE
            S = 0.0D00
            S3O2 = 0.0D00
          ENDIF
          P = LOCPRES(I, J) * 1.0000000000000000818D-05
          P2 = P * P
          BMFRESH = EOSJMDCKFW(1) + EOSJMDCKFW(2) * T + EOSJMDCKFW(3) *
     >  T2 + EOSJMDCKFW(4) * T3 + EOSJMDCKFW(5) * T4
          BMSALT = S *(EOSJMDCKSW(1) + EOSJMDCKSW(2) * T + EOSJMDCKSW(3
     > ) * T2 + EOSJMDCKSW(4) * T3) + S3O2 *(EOSJMDCKSW(5) + EOSJMDCKSW
     > (6) * T + EOSJMDCKSW(7) * T2)
          BMPRES = P *(EOSJMDCKP(1) + EOSJMDCKP(2) * T + EOSJMDCKP(3) *
     >  T2 + EOSJMDCKP(4) * T3) + P * S *(EOSJMDCKP(5) + EOSJMDCKP(6) *
     >  T + EOSJMDCKP(7) * T2) + EOSJMDCKP(8) * P * S3O2 + P2 *(
     > EOSJMDCKP(9) + EOSJMDCKP(10) * T + EOSJMDCKP(11) * T2) + P2 * S
     >  *(EOSJMDCKP(12) + EOSJMDCKP(13) * T + EOSJMDCKP(14) * T2)
          BULKMOD(I, J) = (BMPRES + BMFRESH + BMSALT)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE find_rhonum(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, LOCPRES
     > , TFLD, SFLD, RHONUM, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) LOCPRES(-2 : 93, -2 : 43)
      REAL(w2f__8) TFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RHONUM(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) P1
      REAL(w2f__8) S1
      REAL(w2f__8) T1
      REAL(w2f__8) T2
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          T1 = TFLD(I, J, K, BI, BJ)
          T2 = T1 * T1
          S1 = SFLD(I, J, K, BI, BJ)
          P1 = LOCPRES(I, J) * 1.00000000000000004792D-04
          RHONUM(I, J) = (EOSMDJWFNUM(0) + T1 *(EOSMDJWFNUM(1) + T1 *(
     > EOSMDJWFNUM(2) + EOSMDJWFNUM(3) * T1)) + S1 *(EOSMDJWFNUM(4) +
     >  EOSMDJWFNUM(5) * T1 + EOSMDJWFNUM(6) * S1) + P1 *(EOSMDJWFNUM(7
     > ) + EOSMDJWFNUM(8) * T2 + EOSMDJWFNUM(9) * S1 + P1 *(EOSMDJWFNUM
     > (10) + EOSMDJWFNUM(11) * T2)))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE find_rhoden(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, LOCPRES
     > , TFLD, SFLD, RHODEN, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) LOCPRES(-2 : 93, -2 : 43)
      REAL(w2f__8) TFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) RHODEN(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) DEN
      REAL(w2f__8) EPSLN
      PARAMETER ( EPSLN =     0.000000000000000)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) P1
      REAL(w2f__8) P1T1
      REAL(w2f__8) S1
      REAL(w2f__8) SP5
      REAL(w2f__8) T1
      REAL(w2f__8) T2
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          T1 = TFLD(I, J, K, BI, BJ)
          T2 = T1 * T1
          S1 = SFLD(I, J, K, BI, BJ)
          IF(S1 .GT. 0.0D00) THEN
            SP5 = SQRT(S1)
          ELSE
            S1 = 0.0D00
            SP5 = 0.0D00
          ENDIF
          P1 = LOCPRES(I, J) * 1.00000000000000004792D-04
          P1T1 = P1 * T1
          DEN = EOSMDJWFDEN(0) + T1 *(EOSMDJWFDEN(1) + T1 *(EOSMDJWFDEN
     > (2) + T1 *(EOSMDJWFDEN(3) + EOSMDJWFDEN(4) * T1))) + S1 *(
     > EOSMDJWFDEN(5) + T1 *(EOSMDJWFDEN(6) + EOSMDJWFDEN(7) * T2) +
     >  SP5 *(EOSMDJWFDEN(8) + EOSMDJWFDEN(9) * T2)) + P1 *(EOSMDJWFDEN
     > (10) + P1T1 *(EOSMDJWFDEN(11) * T2 + EOSMDJWFDEN(12) * P1))
          RHODEN(I, J) = 1D00 / (DEN)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE find_rho_scalar(TLOC, SLOC, PLOC, RHOLOC, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) TLOC
      REAL(w2f__8) SLOC
      REAL(w2f__8) PLOC
      REAL(w2f__8) RHOLOC
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) BMFRESH
      REAL(w2f__8) BMPRES
      REAL(w2f__8) BMSALT
      REAL(w2f__8) BULKMOD
      REAL(w2f__8) DEN
      REAL(w2f__8) EPSLN
      PARAMETER ( EPSLN =     0.000000000000000)
      CHARACTER(512) MSGBUF
      REAL(w2f__8) P1
      REAL(w2f__8) P1T1
      REAL(w2f__8) P2
      EXTERNAL print_error
      REAL(w2f__8) RFRESH
      REAL(w2f__8) RHODEN
      REAL(w2f__8) RHONUM
      REAL(w2f__8) RHOP0
      REAL(w2f__8) RSALT
      REAL(w2f__8) S1
      REAL(w2f__8) S3O2
      REAL(w2f__8) SP5
      REAL(w2f__8) T1
      REAL(w2f__8) T2
      REAL(w2f__8) T3
      REAL(w2f__8) T4
C
C     **** Statements ****
C
      RHOLOC = 0.0D00
      RHOP0 = 0.0D00
      BULKMOD = 0.0D00
      RFRESH = 0.0D00
      RSALT = 0.0D00
      BMFRESH = 0.0D00
      BMSALT = 0.0D00
      BMPRES = 0.0D00
      RHONUM = 0.0D00
      RHODEN = 0.0D00
      DEN = 0.0D00
      T1 = TLOC
      T2 = T1 * T1
      T3 = T1 * T2
      T4 = T1 * T3
      S1 = SLOC
      IF(S1 .LT. 0.0D00) THEN
        WRITE(*, '(a,i3,a,i3,a,i3,a,e13.5)')
     >  ' FIND_RHO_SCALAR:   WARNING, salinity = ', S1
        S1 = 0.0D00
      ENDIF
      IF(EQUATIONOFSTATE .EQ. 'LINEAR') THEN
        RHOLOC = 0.0D00
      ELSE
        IF(EQUATIONOFSTATE .EQ. 'POLY3') THEN
          WRITE(*, '(a)')
     >  ' FIND_RHO_SCALAR: for POLY3, the density is not'
          WRITE(*, '(a)')
     >  '                 computed correctly in this rout' // 'ine'
          RHOLOC = 0.0D00
        ELSE
          IF((EQUATIONOFSTATE(1_w2f__i8 : 5) .EQ. 'JMD95') .OR.(
     > EQUATIONOFSTATE .EQ. 'UNESCO')) THEN
            S3O2 = S1 * SQRT(S1)
            P1 = PLOC * 1.0000000000000000818D-05
            P2 = P1 * P1
            RFRESH = EOSJMDCFW(1) + EOSJMDCFW(2) * T1 + EOSJMDCFW(3) *
     >  T2 + EOSJMDCFW(4) * T3 + EOSJMDCFW(5) * T4 + T1 * EOSJMDCFW(6)
     >  * T4
            RSALT = S1 *(EOSJMDCSW(1) + EOSJMDCSW(2) * T1 + EOSJMDCSW(3
     > ) * T2 + EOSJMDCSW(4) * T3 + EOSJMDCSW(5) * T4) + S3O2 *(
     > EOSJMDCSW(6) + EOSJMDCSW(7) * T1 + EOSJMDCSW(8) * T2) + S1 *
     >  EOSJMDCSW(9) * S1
            RHOP0 = RFRESH + RSALT
            BMFRESH = EOSJMDCKFW(1) + EOSJMDCKFW(2) * T1 + EOSJMDCKFW(3
     > ) * T2 + EOSJMDCKFW(4) * T3 + EOSJMDCKFW(5) * T4
            BMSALT = S1 *(EOSJMDCKSW(1) + EOSJMDCKSW(2) * T1 +
     >  EOSJMDCKSW(3) * T2 + EOSJMDCKSW(4) * T3) + S3O2 *(EOSJMDCKSW(5)
     >  + EOSJMDCKSW(6) * T1 + EOSJMDCKSW(7) * T2)
            BMPRES = P1 *(EOSJMDCKP(1) + EOSJMDCKP(2) * T1 + EOSJMDCKP(
     > 3) * T2 + EOSJMDCKP(4) * T3) + P1 * S1 *(EOSJMDCKP(5) +
     >  EOSJMDCKP(6) * T1 + EOSJMDCKP(7) * T2) + EOSJMDCKP(8) * P1 *
     >  S3O2 + P2 *(EOSJMDCKP(9) + EOSJMDCKP(10) * T1 + EOSJMDCKP(11) *
     >  T2) + P2 * S1 *(EOSJMDCKP(12) + EOSJMDCKP(13) * T1 + EOSJMDCKP(
     > 14) * T2)
            BULKMOD = BMPRES + BMFRESH + BMSALT
            RHOLOC = (RHOP0 /(1.0D00 -(P1 / BULKMOD))) - RHOCONST
          ELSE
            IF(EQUATIONOFSTATE .EQ. 'MDJWF') THEN
              SP5 = SQRT(S1)
              P1 = PLOC * 1.00000000000000004792D-04
              P1T1 = P1 * T1
              RHONUM = EOSMDJWFNUM(0) + T1 *(EOSMDJWFNUM(1) + T1 *(
     > EOSMDJWFNUM(2) + EOSMDJWFNUM(3) * T1)) + S1 *(EOSMDJWFNUM(4) +
     >  EOSMDJWFNUM(5) * T1 + EOSMDJWFNUM(6) * S1) + P1 *(EOSMDJWFNUM(7
     > ) + EOSMDJWFNUM(8) * T2 + EOSMDJWFNUM(9) * S1 + P1 *(EOSMDJWFNUM
     > (10) + EOSMDJWFNUM(11) * T2))
              DEN = EOSMDJWFDEN(0) + T1 *(EOSMDJWFDEN(1) + T1 *(
     > EOSMDJWFDEN(2) + T1 *(EOSMDJWFDEN(3) + EOSMDJWFDEN(4) * T1))) +
     >  S1 *(EOSMDJWFDEN(5) + T1 *(EOSMDJWFDEN(6) + EOSMDJWFDEN(7) * T2
     > ) + SP5 *(EOSMDJWFDEN(8) + EOSMDJWFDEN(9) * T2)) + P1 *(
     > EOSMDJWFDEN(10) + P1T1 *(EOSMDJWFDEN(11) * T2 + EOSMDJWFDEN(12)
     >  * P1))
              RHODEN = 1D00 / (DEN)
              RHOLOC = RHODEN * RHONUM - RHOCONST
            ELSE
              IF(EQUATIONOFSTATE .EQ. 'IDEALG') THEN
              ELSE
                WRITE(MSGBUF, '(3A)')
     >  ' FIND_RHO_SCALAR : equationOfState = "', EQUATIONOFSTATE, '"'
                CALL print_error(MSGBUF, MYTHID)
                STOP 'ABNORMAL END: S/R FIND_RHO_SCALAR'
                RETURN
              ENDIF
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE look_for_neg_salinity(BI, BJ, IMIN, IMAX, JMIN, JMAX,
     >  K, SFLD, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) SFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) LOCALWARNING
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      LOCALWARNING = 0
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          IF(SFLD(I, J, K, BI, BJ) .LT. 0.0D00) THEN
            LOCALWARNING = LOCALWARNING + 1
            SFLD(I, J, K, BI, BJ) = 0.0D00
          ENDIF
        END DO
      END DO
      IF(LOCALWARNING .GT. 0) THEN
        WRITE(STANDARDMESSAGEUNIT, '(A,A)')
     >  'S/R LOOK_FOR_NEG_SALINITY: found negative salini' // 'ty',
     >  'values and reset them to zero.'
        WRITE(STANDARDMESSAGEUNIT, '(A,I3)')
     >  'S/R LOOK_FOR_NEG_SALINITY: current level is k = ', K
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE forward_step(ILOOP, MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use ffields_mod
      use tamc_mod
      use ctrl_mod
      use ctrl_dummy_mod
      use cost_mod
      use eos_mod
      use cd_code_vars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) ILOOP
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL cost_tile
      EXTERNAL ctrl_map_forcing
      EXTERNAL debug_call
      EXTERNAL debug_enter
      EXTERNAL debug_leave
      EXTERNAL do_atmospheric_phys
      EXTERNAL do_fields_blocking_exchanges
      EXTERNAL do_oceanic_phys
      EXTERNAL do_stagger_fields_exchanges
      EXTERNAL do_statevars_diags
      EXTERNAL do_statevars_tave
      EXTERNAL do_the_model_io
      EXTERNAL dynamics
      EXTERNAL external_fields_load
      EXTERNAL momentum_correction_step
      EXTERNAL packages_write_pickup
      EXTERNAL solve_for_pressure
      EXTERNAL thermodynamics
      EXTERNAL timer_start
      EXTERNAL timer_stop
      EXTERNAL tracers_correction_step
      EXTERNAL write_checkpoint
C
C     **** Statements ****
C
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_enter('FORWARD_STEP', MYTHID)
      ENDIF
      MYITER = ILOOP + NITER0 +(-1)
      MYTIME = STARTTIME + FLOAT(ILOOP +(-1)) * DELTATCLOCK
      IF(USEDIAGNOSTICS) THEN
        CALL timer_start('DO_STATEVARS_DIAGS  [FORWARD_STEP]', MYTHID)
        CALL do_statevars_diags(MYTIME, (0), MYITER, MYTHID)
        CALL timer_stop('DO_STATEVARS_DIAGS  [FORWARD_STEP]', MYTHID)
      ENDIF
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_call('EXTERNAL_FIELDS_LOAD', MYTHID)
      ENDIF
      CALL timer_start('EXTERNAL_FIELDS_LOAD[FORWARD_STEP]', MYTHID)
      CALL external_fields_load(MYTIME, MYITER, MYTHID)
      CALL timer_stop('EXTERNAL_FIELDS_LOAD[FORWARD_STEP]', MYTHID)
      IF(MYITER .eq. NITER0) THEN
        CALL ctrl_map_forcing(MYTHID)
      ENDIF
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_call('DO_ATMOSPHERIC_PHYS', MYTHID)
      ENDIF
      CALL timer_start('DO_ATMOSPHERIC_PHYS [FORWARD_STEP]', MYTHID)
      CALL do_atmospheric_phys(MYTIME, MYITER, MYTHID)
      CALL timer_stop('DO_ATMOSPHERIC_PHYS [FORWARD_STEP]', MYTHID)
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_call('DO_OCEANIC_PHYS', MYTHID)
      ENDIF
      CALL timer_start('DO_OCEANIC_PHYS     [FORWARD_STEP]', MYTHID)
      CALL do_oceanic_phys(MYTIME, MYITER, MYTHID)
      CALL timer_stop('DO_OCEANIC_PHYS     [FORWARD_STEP]', MYTHID)
      IF(.NOT. STAGGERTIMESTEP) THEN
        IF(DEBUGLEVEL .GE. 2) THEN
          CALL debug_call('THERMODYNAMICS', MYTHID)
        ENDIF
        CALL timer_start('THERMODYNAMICS      [FORWARD_STEP]', MYTHID)
        CALL thermodynamics(MYTIME, MYITER, MYTHID)
        CALL timer_stop('THERMODYNAMICS      [FORWARD_STEP]', MYTHID)
      ENDIF
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_call('DYNAMICS', MYTHID)
      ENDIF
      CALL timer_start('DYNAMICS            [FORWARD_STEP]', MYTHID)
      CALL dynamics(MYTIME, MYITER, MYTHID)
      CALL timer_stop('DYNAMICS            [FORWARD_STEP]', MYTHID)
      MYITER = ILOOP + NITER0
      MYTIME = STARTTIME + FLOAT(ILOOP) * DELTATCLOCK
      IF(MOMSTEPPING) THEN
        CALL timer_start('SOLVE_FOR_PRESSURE  [FORWARD_STEP]', MYTHID)
        CALL solve_for_pressure(MYTIME, MYITER, MYTHID)
        CALL timer_stop('SOLVE_FOR_PRESSURE  [FORWARD_STEP]', MYTHID)
      ENDIF
      CALL timer_start('UV_CORRECTION_STEP  [FORWARD_STEP]', MYTHID)
      CALL momentum_correction_step(MYTIME, MYITER, MYTHID)
      CALL timer_stop('UV_CORRECTION_STEP  [FORWARD_STEP]', MYTHID)
      IF(STAGGERTIMESTEP) THEN
        IF(DEBUGLEVEL .GE. 2) THEN
          CALL debug_call('DO_STAGGER_FIELDS_EXCH.', MYTHID)
        ENDIF
        CALL timer_start('BLOCKING_EXCHANGES  [FORWARD_STEP]', MYTHID)
        CALL do_stagger_fields_exchanges(MYTIME, MYITER, MYTHID)
        CALL timer_stop('BLOCKING_EXCHANGES  [FORWARD_STEP]', MYTHID)
        IF(USEDIAGNOSTICS) THEN
          CALL timer_start('DO_STATEVARS_DIAGS  [FORWARD_STEP]', MYTHID
     > )
          CALL do_statevars_diags(MYTIME, (1), MYITER, MYTHID)
          CALL timer_stop('DO_STATEVARS_DIAGS  [FORWARD_STEP]', MYTHID)
        ENDIF
        IF(DEBUGLEVEL .GE. 2) THEN
          CALL debug_call('THERMODYNAMICS', MYTHID)
        ENDIF
        CALL timer_start('THERMODYNAMICS      [FORWARD_STEP]', MYTHID)
        CALL thermodynamics(MYTIME, MYITER, MYTHID)
        CALL timer_stop('THERMODYNAMICS      [FORWARD_STEP]', MYTHID)
      ENDIF
      CALL timer_start('TS_CORRECTION_STEP  [FORWARD_STEP]', MYTHID)
      CALL tracers_correction_step(MYTIME, MYITER, MYTHID)
      CALL timer_stop('TS_CORRECTION_STEP  [FORWARD_STEP]', MYTHID)
      CALL timer_start('BLOCKING_EXCHANGES  [FORWARD_STEP]', MYTHID)
      CALL do_fields_blocking_exchanges(MYTHID)
      CALL timer_stop('BLOCKING_EXCHANGES  [FORWARD_STEP]', MYTHID)
      CALL timer_start('DO_STATEVARS_TAVE   [FORWARD_STEP]', MYTHID)
      CALL do_statevars_tave(MYTIME, MYITER, MYTHID)
      CALL timer_stop('DO_STATEVARS_TAVE   [FORWARD_STEP]', MYTHID)
      CALL timer_start('COST_TILE           [FORWARD_STEP]', MYTHID)
      CALL cost_tile(MYTIME, MYITER, MYTHID)
      CALL timer_stop('COST_TILE           [FORWARD_STEP]', MYTHID)
      CALL timer_start('DO_THE_MODEL_IO     [FORWARD_STEP]', MYTHID)
      CALL do_the_model_io(MYTIME, MYITER, MYTHID)
      CALL timer_stop('DO_THE_MODEL_IO     [FORWARD_STEP]', MYTHID)
      CALL timer_start('WRITE_CHECKPOINT    [FORWARD_STEP]', MYTHID)
      CALL packages_write_pickup((.FALSE.), MYTIME, MYITER, MYTHID)
      CALL write_checkpoint((.FALSE.), MYTIME, MYITER, MYTHID)
      CALL timer_stop('WRITE_CHECKPOINT    [FORWARD_STEP]', MYTHID)
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_leave('FORWARD_STEP', MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE freeze(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) TFREEZING
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      TFREEZING = -1.89999999999999991118D00
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          IF(GT(I, J, K, BI, BJ) .LT. TFREEZING) THEN
            GT(I, J, K, BI, BJ) = TFREEZING
          ENDIF
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE freeze_surface(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      REAL(w2f__8) TFREEZING
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      IF(USINGPCOORDS) THEN
        K = 15
      ELSE
        K = 1
      ENDIF
      TFREEZING = -1.89999999999999991118D00
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              IF(THETA(I, J, K, BI, BJ) .LT. TFREEZING) THEN
                SURFACEFORCINGTICE(I, J, BI, BJ) = ((HFACC(I, J, K, BI,
     >  BJ) * DRF(K) *(TFREEZING - THETA(I, J, K, BI, BJ))) /
     >  DTTRACERLEV(K))
                THETA(I, J, K, BI, BJ) = TFREEZING
              ELSE
                SURFACEFORCINGTICE(I, J, BI, BJ) = 0.0D00
              ENDIF
            END DO
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE grad_sigma(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, RHOK,
     >  SIGKM1, SIGKP1, SIGMAX, SIGMAY, SIGMAR, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) RHOK(-2 : 93, -2 : 43)
      REAL(w2f__8) SIGKM1(-2 : 93, -2 : 43)
      REAL(w2f__8) SIGKP1(-2 : 93, -2 : 43)
      REAL(w2f__8) SIGMAX(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) SIGMAY(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) SIGMAR(-2 : 93, -2 : 43, 1 : 15)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) RHOLOC(-2 : 93, -2 : 43)
C
C     **** Statements ****
C
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          RHOLOC(I, J) = RHOK(I, J)
        END DO
      END DO
      DO J = -2, 43, 1
        DO I = -1, 93, 1
          SIGMAX(I, J, K) = (RECIP_DXC(I, J, BI, BJ) * MASKW(I, J, K,
     >  BI, BJ) *(RHOLOC(I, J) - RHOLOC(I + (-1), J)))
        END DO
      END DO
      DO J = -1, 43, 1
        DO I = -2, 93, 1
          SIGMAY(I, J, K) = (RECIP_DYC(I, J, BI, BJ) * MASKS(I, J, K,
     >  BI, BJ) *(RHOLOC(I, J) - RHOLOC(I, J + (-1))))
        END DO
      END DO
      IF(K .eq. 1) THEN
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            SIGMAR(I, J, K) = 0.0
          END DO
        END DO
      ELSE
        DO J = -2, 43, 1
          DO I = -2, 93, 1
            SIGMAR(I, J, K) = (RKSIGN * RECIP_DRC(K) * MASKC(I, J, K,
     >  BI, BJ) *(SIGKP1(I, J) - SIGKM1(I, J)))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE impldiff(BI, BJ, IMIN, IMAX, JMIN, JMAX, TRACERID,
     >  KAPPARX, RECIP_HFAC, GXNM1, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use tamc_keys_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) TRACERID
      REAL(w2f__8) KAPPARX(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) RECIP_HFAC(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GXNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) A(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) B(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) BET(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) C(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) DELTATX(1 : 15)
      REAL(w2f__8) GAM(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) GYNM1(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
      INTEGER(w2f__i4) doloop_ub11
      INTEGER(w2f__i4) doloop_ub12
      INTEGER(w2f__i4) doloop_ub13
      INTEGER(w2f__i4) doloop_ub14
      INTEGER(w2f__i4) doloop_ub15
      INTEGER(w2f__i4) doloop_ub16
      INTEGER(w2f__i4) doloop_ub17
      INTEGER(w2f__i4) doloop_ub18
      INTEGER(w2f__i4) doloop_ub19
      INTEGER(w2f__i4) doloop_ub20
      INTEGER(w2f__i4) doloop_ub21
      INTEGER(w2f__i4) doloop_ub22
      INTEGER(w2f__i4) doloop_ub23
      INTEGER(w2f__i4) doloop_ub24
C
C     **** Statements ****
C
      IF(TRACERID .GE. 1) THEN
        DO K = 1, 15, 1
          DELTATX(K) = DTTRACERLEV(K)
        END DO
      ELSE
        DO K = 1, 15, 1
          DELTATX(K) = DELTATMOM
        END DO
      ENDIF
      DO K = 1, 15, 1
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            GYNM1(I, J, K, BI, BJ) = 0.0D00
          END DO
        END DO
      END DO
      doloop_ub1 = JMAX
      DO J = JMIN, doloop_ub1, 1
        doloop_ub2 = IMAX
        DO I = IMIN, doloop_ub2, 1
          A(I, J, 1) = 0.0D00
        END DO
      END DO
      DO K = 2, 15, 1
        doloop_ub3 = JMAX
        DO J = JMIN, doloop_ub3, 1
          doloop_ub4 = IMAX
          DO I = IMIN, doloop_ub4, 1
            A(I, J, K) = (-(RECIP_DRC(K) * KAPPARX(I, J, K) * RECIP_DRF
     > (K) * DELTATX(K) * RECIP_HFAC(I, J, K, BI, BJ)))
            IF(RECIP_HFAC(I, J, K + (-1), BI, BJ) .eq. 0.0D00) THEN
              A(I, J, K) = 0.0
            ENDIF
          END DO
        END DO
      END DO
      DO K = 1, 14, 1
        doloop_ub5 = JMAX
        DO J = JMIN, doloop_ub5, 1
          doloop_ub6 = IMAX
          DO I = IMIN, doloop_ub6, 1
            C(I, J, K) = (-(RECIP_DRC(K + 1) * KAPPARX(I, J, K + 1) *
     >  RECIP_DRF(K) * DELTATX(K) * RECIP_HFAC(I, J, K, BI, BJ)))
            IF(RECIP_HFAC(I, J, K + 1, BI, BJ) .eq. 0.0D00) THEN
              C(I, J, K) = 0.0
            ENDIF
          END DO
        END DO
      END DO
      doloop_ub7 = JMAX
      DO J = JMIN, doloop_ub7, 1
        doloop_ub8 = IMAX
        DO I = IMIN, doloop_ub8, 1
          C(I, J, 15) = 0.0D00
        END DO
      END DO
      DO K = 1, 15, 1
        doloop_ub9 = JMAX
        DO J = JMIN, doloop_ub9, 1
          doloop_ub10 = IMAX
          DO I = IMIN, doloop_ub10, 1
            B(I, J, K) = (1.0D00 - C(I, J, K) - A(I, J, K))
          END DO
        END DO
      END DO
      DO K = 1, 15, 1
        doloop_ub11 = JMAX
        DO J = JMIN, doloop_ub11, 1
          doloop_ub12 = IMAX
          DO I = IMIN, doloop_ub12, 1
            BET(I, J, K) = 1.0D00
            GAM(I, J, K) = 0.0D00
          END DO
        END DO
      END DO
      IF(.TRUE.) THEN
        K = 1
        doloop_ub13 = JMAX
        DO J = JMIN, doloop_ub13, 1
          doloop_ub14 = IMAX
          DO I = IMIN, doloop_ub14, 1
            IF(B(I, J, 1) .ne. 0.0D00) THEN
              BET(I, J, 1) = 1D00 / (B(I, J, 1))
            ENDIF
          END DO
        END DO
      ENDIF
      IF(.TRUE.) THEN
        DO K = 2, 15, 1
          doloop_ub15 = JMAX
          DO J = JMIN, doloop_ub15, 1
            doloop_ub16 = IMAX
            DO I = IMIN, doloop_ub16, 1
              GAM(I, J, K) = (BET(I, J, K + (-1)) * C(I, J, K + (-1)))
              IF((B(I, J, K) - A(I, J, K) * GAM(I, J, K)) .ne. 0.0D00)
     >  THEN
                BET(I, J, K) = 1D00 / (B(I, J, K) - A(I, J, K) * GAM(I,
     >  J, K))
              ENDIF
            END DO
          END DO
        END DO
      ENDIF
      doloop_ub17 = JMAX
      DO J = JMIN, doloop_ub17, 1
        doloop_ub18 = IMAX
        DO I = IMIN, doloop_ub18, 1
          GYNM1(I, J, 1, BI, BJ) = (BET(I, J, 1) * GXNM1(I, J, 1, BI,
     >  BJ))
        END DO
      END DO
      DO K = 2, 15, 1
        doloop_ub19 = JMAX
        DO J = JMIN, doloop_ub19, 1
          doloop_ub20 = IMAX
          DO I = IMIN, doloop_ub20, 1
            GYNM1(I, J, K, BI, BJ) = (BET(I, J, K) *(GXNM1(I, J, K, BI,
     >  BJ) - A(I, J, K) * GYNM1(I, J, K + (-1), BI, BJ)))
          END DO
        END DO
      END DO
      DO K = 14, 1, (-1)
        doloop_ub21 = JMAX
        DO J = JMIN, doloop_ub21, 1
          doloop_ub22 = IMAX
          DO I = IMIN, doloop_ub22, 1
            GYNM1(I, J, K, BI, BJ) = (GYNM1(I, J, K, BI, BJ) - GAM(I, J
     > , K + 1) * GYNM1(I, J, K + 1, BI, BJ))
          END DO
        END DO
      END DO
      DO K = 1, 15, 1
        doloop_ub23 = JMAX
        DO J = JMIN, doloop_ub23, 1
          doloop_ub24 = IMAX
          DO I = IMIN, doloop_ub24, 1
            GXNM1(I, J, K, BI, BJ) = GYNM1(I, J, K, BI, BJ)
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_autodiff(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
              END DO
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
            END DO
          END DO
        END DO
      END DO
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_cartesian_grid(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IG
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JG
      REAL(w2f__8) XG0
      REAL(w2f__8) XGLOC(-2 : 94, -2 : 44)
      REAL(w2f__8) YG0
      REAL(w2f__8) YGLOC(-2 : 94, -2 : 44)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          JG = MYYGLOBALLO + BJ * 40 +(-40)
          IG = MYXGLOBALLO + BI * 90 +(-90)
          XG0 = 0.0D00
          doloop_ub1 = IG +(-1)
          DO I = 1, doloop_ub1, 1
            XG0 = DELX(I) + XG0
          END DO
          DO I = 1, 3, 1
            XG0 = XG0 - DELX(MOD(IG - I + 269, 90) + 1)
          END DO
          YG0 = 0.0D00
          doloop_ub2 = JG +(-1)
          DO J = 1, doloop_ub2, 1
            YG0 = DELY(J) + YG0
          END DO
          DO J = 1, 3, 1
            YG0 = YG0 - DELY(MOD(JG - J + 119, 40) + 1)
          END DO
          DO J = -2, 44, 1
            XGLOC((-2), J) = XG0
            DO I = -2, 93, 1
              XGLOC(I + 1, J) = (DELX(MOD(I + MYXGLOBALLO + BI * 90 +
     >  178, 90) + 1) + XGLOC(I, J))
            END DO
          END DO
          DO I = -2, 94, 1
            YGLOC(I, (-2)) = YG0
            DO J = -2, 43, 1
              YGLOC(I, J + 1) = (DELY(MOD(J + MYYGLOBALLO + BJ * 40 +
     >  78, 40) + 1) + YGLOC(I, J))
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              XG(I, J, BI, BJ) = XGLOC(I, J)
              YG(I, J, BI, BJ) = YGLOC(I, J)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              XC(I, J, BI, BJ) = ((XGLOC(I + 1, J + 1) + XGLOC(I, J + 1
     > ) + XGLOC(I, J) + XGLOC(I + 1, J)) * 2.5D-01)
              YC(I, J, BI, BJ) = ((YGLOC(I + 1, J + 1) + YGLOC(I, J + 1
     > ) + YGLOC(I, J) + YGLOC(I + 1, J)) * 2.5D-01)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              DXF(I, J, BI, BJ) = DELX(MOD(I + MYXGLOBALLO + BI * 90 +
     >  178, 90) + 1)
              DYF(I, J, BI, BJ) = DELY(MOD(J + MYYGLOBALLO + BJ * 40 +
     >  78, 40) + 1)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              DXG(I, J, BI, BJ) = DELX(MOD(I + MYXGLOBALLO + BI * 90 +
     >  178, 90) + 1)
              DYG(I, J, BI, BJ) = DELY(MOD(J + MYYGLOBALLO + BJ * 40 +
     >  78, 40) + 1)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              DXC(I, J, BI, BJ) = 0.0
              DYC(I, J, BI, BJ) = 0.0
              DXV(I, J, BI, BJ) = 0.0
              DYU(I, J, BI, BJ) = 0.0
              RAW(I, J, BI, BJ) = 0.0
              RAS(I, J, BI, BJ) = 0.0
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -1, 93, 1
              DXC(I, J, BI, BJ) = ((DXF(I, J, BI, BJ) + DXF(I + (-1), J
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -1, 43, 1
            DO I = -2, 93, 1
              DYC(I, J, BI, BJ) = ((DYF(I, J, BI, BJ) + DYF(I, J + (-1)
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -1, 43, 1
            DO I = -1, 93, 1
              DXV(I, J, BI, BJ) = ((DXG(I, J, BI, BJ) + DXG(I + (-1), J
     > , BI, BJ)) * 5.0D-01)
              DYU(I, J, BI, BJ) = ((DYG(I, J, BI, BJ) + DYG(I, J + (-1)
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              RA(I, J, BI, BJ) = (DXF(I, J, BI, BJ) * DYF(I, J, BI, BJ)
     > )
              RAW(I, J, BI, BJ) = (DXC(I, J, BI, BJ) * DYG(I, J, BI, BJ
     > ))
              RAS(I, J, BI, BJ) = (DXG(I, J, BI, BJ) * DYC(I, J, BI, BJ
     > ))
              RAZ(I, J, BI, BJ) = (DXV(I, J, BI, BJ) * DYU(I, J, BI, BJ
     > ))
              TANPHIATU(I, J, BI, BJ) = 0.0
              TANPHIATV(I, J, BI, BJ) = 0.0
              ANGLECOSC(I, J, BI, BJ) = 1.0
              ANGLESINC(I, J, BI, BJ) = 0.0
            END DO
          END DO
          DO J = -2, 43, 1
            COSFACU(J, BI, BJ) = 1.0
            COSFACV(J, BI, BJ) = 1.0
            SQCOSFACU(J, BI, BJ) = 1.0
            SQCOSFACV(J, BI, BJ) = 1.0
          END DO
        END DO
      END DO
      IF(LATBANDCLIMRELAX .eq. 1.2345669999999999709D+05) THEN
        IF(MYTHID .eq. 1) THEN
          LATBANDCLIMRELAX = 0.0D00
          DO J = 1, 40, 1
            LATBANDCLIMRELAX = DELY(J) + LATBANDCLIMRELAX
          END DO
          LATBANDCLIMRELAX = LATBANDCLIMRELAX * 3.0D00
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_cg2d(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      use cg2d_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) AC
      REAL(w2f__8) ACS
      REAL(w2f__8) ACW
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_uv_xy_rs
      EXTERNAL exch_xy_rl
      REAL(w2f__8) FACEAREA
      EXTERNAL global_max_r8
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      CHARACTER(512) MSGBUF
      REAL(w2f__8) MYNORM
      EXTERNAL print_message
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              AW2D(I, J, BI, BJ) = 0.0D00
              AS2D(I, J, BI, BJ) = 0.0D00
              PW(I, J, BI, BJ) = 0.0D00
              PS(I, J, BI, BJ) = 0.0D00
              PC(I, J, BI, BJ) = 0.0D00
              CG2D_Q(I, J, BI, BJ) = 0.0D00
            END DO
          END DO
          DO J = 0, 41, 1
            DO I = 0, 91, 1
              CG2D_R(I, J, BI, BJ) = 0.0D00
              CG2D_S(I, J, BI, BJ) = 0.0D00
            END DO
          END DO
        END DO
      END DO
      MYNORM = 0.0D00
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          DO J = 1, 40, 1
            DO I = 1, 90, 1
              AW2D(I, J, BI, BJ) = 0.0D00
              AS2D(I, J, BI, BJ) = 0.0D00
            END DO
          END DO
          DO K = 1, 15, 1
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                FACEAREA = HFACW(I, J, K, BI, BJ) * DRF(K) * DYG(I, J,
     >  BI, BJ)
                AW2D(I, J, BI, BJ) = (AW2D(I, J, BI, BJ) + RECIP_DXC(I,
     >  J, BI, BJ) * FACEAREA * IMPLICDIV2DFLOW * IMPLICSURFPRESS)
                FACEAREA = HFACS(I, J, K, BI, BJ) * DRF(K) * DXG(I, J,
     >  BI, BJ)
                AS2D(I, J, BI, BJ) = (AS2D(I, J, BI, BJ) + RECIP_DYC(I,
     >  J, BI, BJ) * FACEAREA * IMPLICDIV2DFLOW * IMPLICSURFPRESS)
              END DO
            END DO
          END DO
          DO J = 1, 40, 1
            DO I = 1, 90, 1
              MYNORM = MAX(MYNORM, ABS(AW2D(I, J, BI, BJ)))
              MYNORM = MAX(MYNORM, ABS(AS2D(I, J, BI, BJ)))
            END DO
          END DO
        END DO
      END DO
      CALL global_max_r8(MYNORM, MYTHID)
      IF(MYNORM .ne. 0.0D00) THEN
        MYNORM = 1D00 / MYNORM
      ELSE
        MYNORM = 1.0D00
      ENDIF
      CG2DNORM = MYNORM
      doloop_ub3 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
        doloop_ub4 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub4, 1
          DO J = 1, 40, 1
            DO I = 1, 90, 1
              AW2D(I, J, BI, BJ) = (AW2D(I, J, BI, BJ) * MYNORM)
              AS2D(I, J, BI, BJ) = (AS2D(I, J, BI, BJ) * MYNORM)
            END DO
          END DO
        END DO
      END DO
      CALL exch_uv_xy_rs(AW2D, AS2D, (.FALSE.), MYTHID)
      CG2DNORMALISERHS = CG2DTARGETRESWUNIT .LE. 0.0D00
      IF(CG2DNORMALISERHS) THEN
        CG2DTOLERANCE = CG2DTARGETRESIDUAL
      ELSE
        CG2DTOLERANCE = (GLOBALAREA * CG2DTARGETRESWUNIT * CG2DNORM) /
     >  DELTATMOM
      ENDIF
      IF(MYTHID .eq. 1) THEN
        WRITE(MSGBUF, '(2A,1PE23.16)') 'INI_CG2D: ',
     >  'CG2D normalisation factor = ', CG2DNORM
        CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
        IF(.NOT. CG2DNORMALISERHS) THEN
          WRITE(MSGBUF, '(2A,1PE22.15,A,1PE16.10,A)') 'INI_CG2D: ',
     >  'cg2dTolerance =', CG2DTOLERANCE, ' (Area=', GLOBALAREA, ')'
          CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
        ENDIF
        WRITE(MSGBUF, *) ' '
        CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      ENDIF
      doloop_ub5 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub5, 1
        doloop_ub6 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub6, 1
          DO J = 1, 40, 1
            DO I = 1, 90, 1
              PC(I, J, BI, BJ) = 1.0D00
              AC = -(AS2D(I, J + 1, BI, BJ) + AS2D(I, J, BI, BJ) + AW2D
     > (I, J, BI, BJ) + AW2D(I + 1, J, BI, BJ) +(((RA(I, J, BI, BJ) *
     >  RECIP_BO(I, J, BI, BJ) * MYNORM * FREESURFFAC) / DELTATMOM) /
     >  DELTATFREESURF))
              ACS = -(AS2D(I, J, BI, BJ) + AS2D(I, J + (-1), BI, BJ) +
     >  AW2D(I, J + (-1), BI, BJ) + AW2D(I + 1, J + (-1), BI, BJ) +(((
     > RA(I, J + (-1), BI, BJ) * RECIP_BO(I, J + (-1), BI, BJ) * MYNORM
     >  * FREESURFFAC) / DELTATMOM) / DELTATFREESURF))
              ACW = -(AS2D(I + (-1), J + 1, BI, BJ) + AS2D(I + (-1), J,
     >  BI, BJ) + AW2D(I, J, BI, BJ) + AW2D(I + (-1), J, BI, BJ) +(((RA
     > (I + (-1), J, BI, BJ) * RECIP_BO(I + (-1), J, BI, BJ) * MYNORM *
     >  FREESURFFAC) / DELTATMOM) / DELTATFREESURF))
              IF(AC .eq. 0.0D00) THEN
                PC(I, J, BI, BJ) = 1.0D00
              ELSE
                PC(I, J, BI, BJ) = 1D00 / AC
              ENDIF
              IF((AC + ACW) .eq. 0.0D00) THEN
                PW(I, J, BI, BJ) = 0.0
              ELSE
                PW(I, J, BI, BJ) = (-(AW2D(I, J, BI, BJ) /(((
     > CG2DPCOFFDFAC *(AC + ACW)) ** 2))))
              ENDIF
              IF((AC + ACS) .eq. 0.0D00) THEN
                PS(I, J, BI, BJ) = 0.0
              ELSE
                PS(I, J, BI, BJ) = (-(AS2D(I, J, BI, BJ) /(((
     > CG2DPCOFFDFAC *(AC + ACS)) ** 2))))
              ENDIF
            END DO
          END DO
        END DO
      END DO
      CALL exch_xy_rl(PC, MYTHID)
      CALL exch_uv_xy_rs(PW, PS, (.FALSE.), MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_cori(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_xy_rl
      EXTERNAL exch_z_xy_rs
      REAL(w2f__8) FACGRID
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      EXTERNAL read_rec_xy_rs
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
C
C     **** Statements ****
C
      IF(USECONSTANTF) THEN
        doloop_ub = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub, 1
          doloop_ub0 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub0, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                FCORI(I, J, BI, BJ) = F0
                FCORIG(I, J, BI, BJ) = F0
                FCORICOS(I, J, BI, BJ) = 0.0
              END DO
            END DO
          END DO
        END DO
      ELSE
        IF(USEBETAPLANEF) THEN
          FACGRID = 1.0D00
          IF(USINGSPHERICALPOLARGRID) THEN
            FACGRID = RSPHERE * 1.74532925199432954744D-02
          ENDIF
          doloop_ub1 = MYBYHI(MYTHID)
          DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
            doloop_ub2 = MYBXHI(MYTHID)
            DO BI = MYBXLO(MYTHID), doloop_ub2, 1
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  FCORI(I, J, BI, BJ) = (F0 + FACGRID * YC(I, J, BI, BJ
     > ) * BETA)
                  FCORIG(I, J, BI, BJ) = (F0 + FACGRID * YG(I, J, BI,
     >  BJ) * BETA)
                  FCORICOS(I, J, BI, BJ) = 0.0
                END DO
              END DO
            END DO
          END DO
        ELSE
          IF(USESPHEREF) THEN
            doloop_ub3 = MYBYHI(MYTHID)
            DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
              doloop_ub4 = MYBXHI(MYTHID)
              DO BI = MYBXLO(MYTHID), doloop_ub4, 1
                DO J = -2, 43, 1
                  DO I = -2, 93, 1
                    FCORI(I, J, BI, BJ) = (SIN(YC(I, J, BI, BJ) *
     >  1.74532925199432954744D-02) * OMEGA * 2.0D00)
                    FCORIG(I, J, BI, BJ) = (SIN(YG(I, J, BI, BJ) *
     >  1.74532925199432954744D-02) * OMEGA * 2.0D00)
                    FCORICOS(I, J, BI, BJ) = (COS(YC(I, J, BI, BJ) *
     >  1.74532925199432954744D-02) * OMEGA * 2.0D00)
                  END DO
                END DO
              END DO
            END DO
          ELSE
            doloop_ub5 = MYBYHI(MYTHID)
            DO BJ = MYBYLO(MYTHID), doloop_ub5, 1
              doloop_ub6 = MYBXHI(MYTHID)
              DO BI = MYBXLO(MYTHID), doloop_ub6, 1
                DO J = -2, 43, 1
                  DO I = -2, 93, 1
                    FCORI(I, J, BI, BJ) = 0.0
                    FCORIG(I, J, BI, BJ) = 0.0
                    FCORICOS(I, J, BI, BJ) = 0.0
                  END DO
                END DO
              END DO
            END DO
            CALL read_rec_xy_rs('fCoriC.bin', FCORI, (1), (0), MYTHID)
            CALL read_rec_xy_rs('fCoriG.bin', FCORIG, (1), (0), MYTHID)
            CALL read_rec_xy_rs('fCorCs.bin', FCORICOS, (1), (0),
     >  MYTHID)
            IF(USECUBEDSPHEREEXCHANGE) THEN
              doloop_ub7 = MYBYHI(MYTHID)
              DO BJ = MYBYLO(MYTHID), doloop_ub7, 1
                doloop_ub8 = MYBXHI(MYTHID)
                DO BI = MYBXLO(MYTHID), doloop_ub8, 1
                  IF((BI .GE. 5) .OR.(BI .LE. 3)) THEN
                    FCORIG(91, 1, BI, BJ) = FCORIG(1, 1, BI, BJ)
                  ELSE
                    FCORIG(91, 1, BI, BJ) = (- FCORIG(1, 1, BI, BJ))
                  ENDIF
                  IF(BI .GE. 3) THEN
                    FCORIG(1, 41, BI, BJ) = FCORIG(1, 1, BI, BJ)
                    FCORIG(91, 41, BI, BJ) = FCORIG(91, 1, BI, BJ)
                  ELSE
                    FCORIG(1, 41, BI, BJ) = (- FCORIG(1, 1, BI, BJ))
                    FCORIG(91, 41, BI, BJ) = (- FCORIG(91, 1, BI, BJ))
                  ENDIF
                END DO
              END DO
            ENDIF
            CALL exch_xy_rl(FCORI, MYTHID)
            CALL exch_z_xy_rs(FCORIG, MYTHID)
            CALL exch_xy_rl(FCORICOS, MYTHID)
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_curvilinear_grid(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_uv_agrid_xy_rs
      EXTERNAL exch_uv_xy_rs
      EXTERNAL exch_xy_rl
      EXTERNAL exch_z_xy_rs
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      EXTERNAL mdsreadfield
      INTEGER(w2f__i4) MYITER
      EXTERNAL plot_field_xyrl
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              XC(I, J, BI, BJ) = 0.0
              YC(I, J, BI, BJ) = 0.0
              XG(I, J, BI, BJ) = 0.0
              YG(I, J, BI, BJ) = 0.0
              DXC(I, J, BI, BJ) = 0.0
              DYC(I, J, BI, BJ) = 0.0
              DXG(I, J, BI, BJ) = 0.0
              DYG(I, J, BI, BJ) = 0.0
              DXF(I, J, BI, BJ) = 0.0
              DYF(I, J, BI, BJ) = 0.0
              DXV(I, J, BI, BJ) = 0.0
              DYU(I, J, BI, BJ) = 0.0
              RA(I, J, BI, BJ) = 0.0
              RAZ(I, J, BI, BJ) = 0.0
              RAW(I, J, BI, BJ) = 0.0
              RAS(I, J, BI, BJ) = 0.0
              TANPHIATU(I, J, BI, BJ) = 0.0
              TANPHIATV(I, J, BI, BJ) = 0.0
              ANGLECOSC(I, J, BI, BJ) = 1.0
              ANGLESINC(I, J, BI, BJ) = 0.0
              COSFACU(J, BI, BJ) = 1.0
              COSFACV(J, BI, BJ) = 1.0
              SQCOSFACU(J, BI, BJ) = 1.0
              SQCOSFACV(J, BI, BJ) = 1.0
            END DO
          END DO
        END DO
      END DO
      CALL mdsreadfield('LONC.bin', READBINARYPREC, 'RS', (1), XC, (1),
     >  MYTHID)
      CALL mdsreadfield('LATC.bin', READBINARYPREC, 'RS', (1), YC, (1),
     >  MYTHID)
      CALL exch_xy_rl(XC, MYTHID)
      CALL exch_xy_rl(YC, MYTHID)
      CALL mdsreadfield('DXF.bin', READBINARYPREC, 'RS', (1), DXF, (1),
     >  MYTHID)
      CALL mdsreadfield('DYF.bin', READBINARYPREC, 'RS', (1), DYF, (1),
     >  MYTHID)
      CALL exch_xy_rl(DXF, MYTHID)
      CALL exch_xy_rl(DYF, MYTHID)
      IF(USECUBEDSPHEREEXCHANGE) THEN
        doloop_ub1 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
          doloop_ub2 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub2, 1
            DO J = 1, 40, 1
              DO I = 1, 3, 1
                DXF(1 - I, J, BI, BJ) = DXF(I, J, BI, BJ)
                DXF(I + 90, J, BI, BJ) = DXF(91 - I, J, BI, BJ)
                DYF(1 - I, J, BI, BJ) = DYF(I, J, BI, BJ)
                DYF(I + 90, J, BI, BJ) = DYF(91 - I, J, BI, BJ)
              END DO
            END DO
            DO J = 1, 3, 1
              DO I = 1, 90, 1
                DXF(I, 1 - J, BI, BJ) = DXF(I, J, BI, BJ)
                DXF(I, J + 40, BI, BJ) = DXF(I, 41 - J, BI, BJ)
                DYF(I, 1 - J, BI, BJ) = DYF(I, J, BI, BJ)
                DYF(I, J + 40, BI, BJ) = DYF(I, 41 - J, BI, BJ)
              END DO
            END DO
          END DO
        END DO
      ENDIF
      CALL mdsreadfield('RA.bin', READBINARYPREC, 'RS', (1), RA, (1),
     >  MYTHID)
      CALL exch_xy_rl(RA, MYTHID)
      CALL mdsreadfield('LONG.bin', READBINARYPREC, 'RS', (1), XG, (1),
     >  MYTHID)
      CALL mdsreadfield('LATG.bin', READBINARYPREC, 'RS', (1), YG, (1),
     >  MYTHID)
      IF(USECUBEDSPHEREEXCHANGE) THEN
        BI = 3
        BJ = 1
        YG(1, 41, BJ, 1) = YG(1, 1, BI, 1)
        BJ = BJ + 2
        YG(1, 41, BJ, 1) = YG(1, 1, BI, 1)
        BJ = BJ + 2
        YG(1, 41, BJ, 1) = YG(1, 1, BI, 1)
        BI = 6
        BJ = 2
        YG(91, 1, BJ, 1) = YG(1, 1, BI, 1)
        BJ = BJ + 2
        YG(91, 1, BJ, 1) = YG(1, 1, BI, 1)
        BJ = BJ + 2
        YG(91, 1, BJ, 1) = YG(1, 1, BI, 1)
      ENDIF
      CALL exch_z_xy_rs(XG, MYTHID)
      CALL exch_z_xy_rs(YG, MYTHID)
      CALL mdsreadfield('DXV.bin', READBINARYPREC, 'RS', (1), DXV, (1),
     >  MYTHID)
      CALL mdsreadfield('DYU.bin', READBINARYPREC, 'RS', (1), DYU, (1),
     >  MYTHID)
      IF(.NOT. USECUBEDSPHEREEXCHANGE) THEN
        CALL exch_z_xy_rs(DXV, MYTHID)
        CALL exch_z_xy_rs(DYU, MYTHID)
      ELSE
        doloop_ub3 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
          doloop_ub4 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub4, 1
            DO J = 1, 40, 1
              DO I = 1, 3, 1
                DXV(1 - I, J, BI, BJ) = DXV(I + 1, J, BI, BJ)
                DXV(I + 90, J, BI, BJ) = DXV(I, J, BI, BJ)
                DYU(1 - I, J, BI, BJ) = DYU(I + 1, J, BI, BJ)
                DYU(I + 90, J, BI, BJ) = DYU(I, J, BI, BJ)
              END DO
            END DO
            DO J = 1, 3, 1
              DO I = -2, 93, 1
                DXV(I, 1 - J, BI, BJ) = DXV(I, J + 1, BI, BJ)
                DXV(I, J + 40, BI, BJ) = DXV(I, J, BI, BJ)
                DYU(I, 1 - J, BI, BJ) = DYU(I, J + 1, BI, BJ)
                DYU(I, J + 40, BI, BJ) = DYU(I, J, BI, BJ)
              END DO
            END DO
          END DO
        END DO
      ENDIF
      CALL mdsreadfield('RAZ.bin', READBINARYPREC, 'RS', (1), RAZ, (1),
     >  MYTHID)
      IF(USECUBEDSPHEREEXCHANGE) THEN
        CALL exch_z_xy_rs(RAZ, MYTHID)
        doloop_ub5 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub5, 1
          doloop_ub6 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub6, 1
            RAZ(91, 1, BI, BJ) = RAZ(1, 1, BI, BJ)
            RAZ(1, 41, BI, BJ) = RAZ(1, 1, BI, BJ)
          END DO
        END DO
      ENDIF
      CALL exch_z_xy_rs(RAZ, MYTHID)
      CALL mdsreadfield('DXC.bin', READBINARYPREC, 'RS', (1), DXC, (1),
     >  MYTHID)
      CALL mdsreadfield('DYC.bin', READBINARYPREC, 'RS', (1), DYC, (1),
     >  MYTHID)
      CALL exch_uv_xy_rs(DXC, DYC, (.FALSE.), MYTHID)
      CALL mdsreadfield('RAW.bin', READBINARYPREC, 'RS', (1), RAW, (1),
     >  MYTHID)
      CALL mdsreadfield('RAS.bin', READBINARYPREC, 'RS', (1), RAS, (1),
     >  MYTHID)
      IF(USECUBEDSPHEREEXCHANGE) THEN
        doloop_ub7 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub7, 1
          doloop_ub8 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub8, 1
            DO J = 1, 40, 1
            END DO
          END DO
        END DO
      ENDIF
      CALL exch_uv_xy_rs(RAW, RAS, (.FALSE.), MYTHID)
      CALL mdsreadfield('DXG.bin', READBINARYPREC, 'RS', (1), DXG, (1),
     >  MYTHID)
      CALL mdsreadfield('DYG.bin', READBINARYPREC, 'RS', (1), DYG, (1),
     >  MYTHID)
      IF(USECUBEDSPHEREEXCHANGE) THEN
        doloop_ub9 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub9, 1
          doloop_ub10 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub10, 1
            DO J = 1, 40, 1
            END DO
          END DO
        END DO
      ENDIF
      CALL exch_uv_xy_rs(DYG, DXG, (.FALSE.), MYTHID)
      CALL exch_uv_agrid_xy_rs(ANGLESINC, ANGLECOSC, (.TRUE.), MYTHID)
      IF(DEBUGLEVEL .GE. 2) THEN
        MYITER = 1
        CALL plot_field_xyrl(XC, 'Current XC      ', MYITER, MYTHID)
        CALL plot_field_xyrl(YC, 'Current YC      ', MYITER, MYTHID)
        CALL plot_field_xyrl(DXF, 'Current DXF     ', MYITER, MYTHID)
        CALL plot_field_xyrl(XC, 'Current XC      ', MYITER, MYTHID)
        CALL plot_field_xyrl(DYF, 'Current DYF     ', MYITER, MYTHID)
        CALL plot_field_xyrl(RA, 'Current RA      ', MYITER, MYTHID)
        CALL plot_field_xyrl(XG, 'Current XG      ', MYITER, MYTHID)
        CALL plot_field_xyrl(YG, 'Current YG      ', MYITER, MYTHID)
        CALL plot_field_xyrl(DXV, 'Current DXV     ', MYITER, MYTHID)
        CALL plot_field_xyrl(DYU, 'Current DYU     ', MYITER, MYTHID)
        CALL plot_field_xyrl(RAZ, 'Current RAZ     ', MYITER, MYTHID)
        CALL plot_field_xyrl(DXC, 'Current DXC     ', MYITER, MYTHID)
        CALL plot_field_xyrl(DYC, 'Current DYC     ', MYITER, MYTHID)
        CALL plot_field_xyrl(RAW, 'Current RAW     ', MYITER, MYTHID)
        CALL plot_field_xyrl(RAS, 'Current RAS     ', MYITER, MYTHID)
        CALL plot_field_xyrl(DXG, 'Current DXG     ', MYITER, MYTHID)
        CALL plot_field_xyrl(DYG, 'Current DYG     ', MYITER, MYTHID)
        CALL plot_field_xyrl(ANGLECOSC, 'Current AngleCS ', MYITER,
     >  MYTHID)
        CALL plot_field_xyrl(ANGLESINC, 'Current AngleSN ', MYITER,
     >  MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE readsymtile_rs(FNAME, IREC, ARRAY, BI, BJ, BUF, MYTHID
     > )
      use w2f__types
      use size_mod
      use eeparams_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(*) FNAME
      INTEGER(w2f__i4) IREC
      REAL(w2f__8) ARRAY(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) BUF(1 : 91, 1 : 41)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__729
      INTEGER(w2f__i4) DUNIT
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) ILEN
      EXTERNAL ilnblnk
      INTEGER(w2f__i4) ilnblnk
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) LENGTH_OF_REC
      EXTERNAL mdsfindunit
      EXTERNAL mds_reclen
      INTEGER(w2f__i4) mds_reclen
      CHARACTER(4) t__730
C
C     **** Statements ****
C
      t__729 = LEN(FNAME)
      ILEN = ilnblnk(FNAME(1_w2f__i8 : MAX(t__729, 0_w2f__i8)))
      CALL mdsfindunit(DUNIT, MYTHID)
      LENGTH_OF_REC = mds_reclen((64), (3731), MYTHID)
C     OPEN( dUnit, file=fName(1:iLen), status='old',             access='direct', recl=length_of_rec )
      t__730 = 'OLD '
      OPEN(UNIT = DUNIT, RECL = LENGTH_OF_REC, ACCESS = 'DIRECT',
     >  STATUS = t__730(1_w2f__i8 : 3), FILE = FNAME(1_w2f__i8 : MAX(
     > ILEN, 0)))
      READ(DUNIT, REC = IREC) BUF
C     CLOSE( dUnit )
      CLOSE(UNIT = DUNIT)
      DO J = 1, 41, 1
        DO I = 1, 91, 1
          ARRAY(I, J, BI, BJ) = BUF(I, J)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_cylinder_grid(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) DTHETA
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IG
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JG
      REAL(w2f__8) THISRAD
      REAL(w2f__8) XG0
      REAL(w2f__8) XGLOC(-2 : 94, -2 : 44)
      REAL(w2f__8) YG0
      REAL(w2f__8) YGLOC(-2 : 94, -2 : 44)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          JG = MYYGLOBALLO + BJ * 40 +(-40)
          IG = MYXGLOBALLO + BI * 90 +(-90)
          XG0 = THETAMIN
          doloop_ub1 = IG +(-1)
          DO I = 1, doloop_ub1, 1
            XG0 = DELX(I) + XG0
          END DO
          DO I = 1, 3, 1
            XG0 = XG0 - DELX(MOD(IG - I + 269, 90) + 1)
          END DO
          YG0 = 0.0D00
          doloop_ub2 = JG +(-1)
          DO J = 1, doloop_ub2, 1
            YG0 = DELY(J) + YG0
          END DO
          DO J = 1, 3, 1
            YG0 = YG0 - DELY(MOD(JG - J + 119, 40) + 1)
          END DO
          DO J = -2, 44, 1
            XGLOC((-2), J) = XG0
            DO I = -2, 93, 1
              XGLOC(I + 1, J) = (DELX(MOD(I + MYXGLOBALLO + BI * 90 +
     >  178, 90) + 1) + XGLOC(I, J))
            END DO
          END DO
          DO I = -2, 94, 1
            YGLOC(I, (-2)) = YG0
            DO J = -2, 43, 1
              YGLOC(I, J + 1) = (DELY(MOD(J + MYYGLOBALLO + BJ * 40 +
     >  78, 40) + 1) + YGLOC(I, J))
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              XG(I, J, BI, BJ) = XGLOC(I, J)
              YG(I, J, BI, BJ) = YGLOC(I, J)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              XC(I, J, BI, BJ) = ((XGLOC(I + 1, J + 1) + XGLOC(I, J + 1
     > ) + XGLOC(I, J) + XGLOC(I + 1, J)) * 2.5D-01)
              YC(I, J, BI, BJ) = ((YGLOC(I + 1, J + 1) + YGLOC(I, J + 1
     > ) + YGLOC(I, J) + YGLOC(I + 1, J)) * 2.5D-01)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              THISRAD = YC(I, J, BI, BJ)
              DTHETA = DELX(MOD(I + MYXGLOBALLO + BI * 90 + 178, 90) +
     >  1)
              DXF(I, J, BI, BJ) = (DTHETA * THISRAD *
     >  1.74532925199432954744D-02)
              DYF(I, J, BI, BJ) = DELY(MOD(J + MYYGLOBALLO + BJ * 40 +
     >  78, 40) + 1)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              THISRAD = (YGLOC(I, J) + YGLOC(I + 1, J)) * 5.0D-01
              DTHETA = DELX(MOD(I + MYXGLOBALLO + BI * 90 + 178, 90) +
     >  1)
              DXG(I, J, BI, BJ) = (DTHETA * THISRAD *
     >  1.74532925199432954744D-02)
              DYG(I, J, BI, BJ) = DELY(MOD(J + MYYGLOBALLO + BJ * 40 +
     >  78, 40) + 1)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              DXC(I, J, BI, BJ) = 0.0
              DYC(I, J, BI, BJ) = 0.0
              DXV(I, J, BI, BJ) = 0.0
              DYU(I, J, BI, BJ) = 0.0
              RAW(I, J, BI, BJ) = 0.0
              RAS(I, J, BI, BJ) = 0.0
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -1, 93, 1
              DXC(I, J, BI, BJ) = ((DXF(I, J, BI, BJ) + DXF(I + (-1), J
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -1, 43, 1
            DO I = -2, 93, 1
              DYC(I, J, BI, BJ) = ((DYF(I, J, BI, BJ) + DYF(I, J + (-1)
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -1, 43, 1
            DO I = -1, 93, 1
              DXV(I, J, BI, BJ) = ((DXG(I, J, BI, BJ) + DXG(I + (-1), J
     > , BI, BJ)) * 5.0D-01)
              DYU(I, J, BI, BJ) = ((DYG(I, J, BI, BJ) + DYG(I, J + (-1)
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              RA(I, J, BI, BJ) = (DXF(I, J, BI, BJ) * DYF(I, J, BI, BJ)
     > )
              RAW(I, J, BI, BJ) = (DXC(I, J, BI, BJ) * DYG(I, J, BI, BJ
     > ))
              RAS(I, J, BI, BJ) = (DXG(I, J, BI, BJ) * DYC(I, J, BI, BJ
     > ))
              RAZ(I, J, BI, BJ) = (DXV(I, J, BI, BJ) * DYU(I, J, BI, BJ
     > ))
              TANPHIATU(I, J, BI, BJ) = 0.0
              TANPHIATV(I, J, BI, BJ) = 0.0
              ANGLECOSC(I, J, BI, BJ) = 1.0
              ANGLESINC(I, J, BI, BJ) = 0.0
            END DO
          END DO
          DO J = -2, 43, 1
            COSFACU(J, BI, BJ) = 1.0
            COSFACV(J, BI, BJ) = 1.0
            SQCOSFACU(J, BI, BJ) = 1.0
            SQCOSFACV(J, BI, BJ) = 1.0
          END DO
        END DO
      END DO
      IF(LATBANDCLIMRELAX .eq. 1.2345669999999999709D+05) THEN
        IF(MYTHID .eq. 1) THEN
          LATBANDCLIMRELAX = 0.0D00
          DO J = 1, 40, 1
            LATBANDCLIMRELAX = DELY(J) + LATBANDCLIMRELAX
          END DO
          LATBANDCLIMRELAX = LATBANDCLIMRELAX * 3.0D00
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_depths(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL barrier
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_xy_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IG
      EXTERNAL ini_p_ground
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JG
      CHARACTER(512) MSGBUF
      EXTERNAL print_error
      EXTERNAL read_rec_xy_rs
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
C
C     **** Statements ****
C
      IF((TOPOFILE .NE. ' ') .AND.(USINGPCOORDS .AND.(BATHYFILE .NE.
     >  ' '))) THEN
        WRITE(MSGBUF, '(A,A)')
     >  'S/R INI_DEPTHS: both bathyFile & topoFile are sp' //
     >  'ecified:', ' select the right one !'
        CALL print_error(MSGBUF, MYTHID)
        STOP 'ABNORMAL END: S/R INI_DEPTHS'
        RETURN
      ENDIF
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              R_LOW(I, J, BI, BJ) = 0.0
              RO_SURF(I, J, BI, BJ) = 0.0
              TOPOZ(I, J, BI, BJ) = 0.0
            END DO
          END DO
        END DO
      END DO
      IF(USINGPCOORDS .OR.(BATHYFILE .EQ. ' ')) THEN
        doloop_ub1 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
          doloop_ub2 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub2, 1
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                R_LOW(I, J, BI, BJ) = RF(16)
              END DO
            END DO
          END DO
        END DO
      ELSE
        IF(MYTHID .eq. 1) THEN
          CALL read_rec_xy_rs(BATHYFILE, R_LOW, (1), (0), MYTHID)
        ENDIF
      ENDIF
      CALL exch_xy_rl(R_LOW, MYTHID)
      IF(USINGPCOORDS .AND.(BATHYFILE .NE. ' ')) THEN
        IF(MYTHID .eq. 1) THEN
          CALL read_rec_xy_rs(BATHYFILE, RO_SURF, (1), (0), MYTHID)
        ENDIF
        CALL barrier(MYTHID)
      ELSE
        IF(TOPOFILE .EQ. ' ') THEN
          doloop_ub3 = MYBYHI(MYTHID)
          DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
            doloop_ub4 = MYBXHI(MYTHID)
            DO BI = MYBXLO(MYTHID), doloop_ub4, 1
              DO J = 1, 40, 1
                DO I = 1, 90, 1
                  RO_SURF(I, J, BI, BJ) = RO_SEALEVEL
                END DO
              END DO
            END DO
          END DO
        ELSE
          IF(MYTHID .eq. 1) THEN
            CALL read_rec_xy_rs(TOPOFILE, TOPOZ, (1), (0), MYTHID)
          ENDIF
          CALL barrier(MYTHID)
          IF(BUOYANCYRELATION .EQ. 'ATMOSPHERIC') THEN
            CALL ini_p_ground((2), TOPOZ, RO_SURF, MYTHID)
            CALL barrier(MYTHID)
          ELSE
            doloop_ub5 = MYBYHI(MYTHID)
            DO BJ = MYBYLO(MYTHID), doloop_ub5, 1
              doloop_ub6 = MYBXHI(MYTHID)
              DO BI = MYBXLO(MYTHID), doloop_ub6, 1
                DO J = 1, 40, 1
                  DO I = 1, 90, 1
                    RO_SURF(I, J, BI, BJ) = TOPOZ(I, J, BI, BJ)
                  END DO
                END DO
              END DO
            END DO
          ENDIF
        ENDIF
      ENDIF
      CALL exch_xy_rl(RO_SURF, MYTHID)
      IF(USINGPCOORDS) THEN
        doloop_ub7 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub7, 1
          doloop_ub8 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub8, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                IG = I + MYXGLOBALLO + BI * 90 +(-91)
                JG = J + MYYGLOBALLO + BJ * 40 +(-41)
                IF(USINGSPHERICALPOLARGRID .AND.(ABS(YC(I, J, BI, BJ))
     >  .GE. 9.0D+01)) THEN
                  RO_SURF(I, J, BI, BJ) = RF(16)
                ENDIF
              END DO
            END DO
          END DO
        END DO
      ELSE
        doloop_ub9 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub9, 1
          doloop_ub10 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub10, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                IG = I + MYXGLOBALLO + BI * 90 +(-91)
                JG = J + MYYGLOBALLO + BJ * 40 +(-41)
                IF(USINGSPHERICALPOLARGRID .AND.(ABS(YC(I, J, BI, BJ))
     >  .GE. 9.0D+01)) THEN
                  R_LOW(I, J, BI, BJ) = RO_SEALEVEL
                ENDIF
              END DO
            END DO
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_fields(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL ini_pnh
      EXTERNAL ini_pressure
      EXTERNAL ini_psurf
      EXTERNAL ini_salt
      EXTERNAL ini_theta
      EXTERNAL ini_vel
      EXTERNAL read_checkpoint
C
C     **** Statements ****
C
      IF((PICKUPSUFF .EQ. ' ') .AND.((NITER0 .eq. 0) .AND.(BASETIME
     >  .eq. STARTTIME))) THEN
        CALL ini_vel(MYTHID)
        CALL ini_theta(MYTHID)
        CALL ini_salt(MYTHID)
        CALL ini_psurf(MYTHID)
        CALL ini_pressure(MYTHID)
        IF(NONHYDROSTATIC) THEN
          CALL ini_pnh(MYTHID)
        ENDIF
      ELSE
        CALL read_checkpoint(NITER0, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_forcing(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL barrier
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_xy_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      EXTERNAL read_fld_xy_rs
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      CALL barrier(MYTHID)
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              FU(I, J, BI, BJ) = 0.0D00
              FV(I, J, BI, BJ) = 0.0D00
              QNET(I, J, BI, BJ) = 0.0D00
              EMPMR(I, J, BI, BJ) = 0.0D00
              SALTFLUX(I, J, BI, BJ) = 0.0D00
              SST(I, J, BI, BJ) = 0.0D00
              SSS(I, J, BI, BJ) = 0.0D00
              QSW(I, J, BI, BJ) = 0.0D00
              SURFACEFORCINGU(I, J, BI, BJ) = 0.0D00
              SURFACEFORCINGV(I, J, BI, BJ) = 0.0D00
              SURFACEFORCINGT(I, J, BI, BJ) = 0.0D00
              SURFACEFORCINGS(I, J, BI, BJ) = 0.0D00
              SURFACEFORCINGTICE(I, J, BI, BJ) = 0.0D00
              TAUX0(I, J, BI, BJ) = 0.0D00
              TAUX1(I, J, BI, BJ) = 0.0D00
              TAUY0(I, J, BI, BJ) = 0.0D00
              TAUY1(I, J, BI, BJ) = 0.0D00
              QNET0(I, J, BI, BJ) = 0.0D00
              QNET1(I, J, BI, BJ) = 0.0D00
              EMPMR0(I, J, BI, BJ) = 0.0D00
              EMPMR1(I, J, BI, BJ) = 0.0D00
              SALTFLUX0(I, J, BI, BJ) = 0.0D00
              SALTFLUX1(I, J, BI, BJ) = 0.0D00
              SST0(I, J, BI, BJ) = 0.0D00
              SST1(I, J, BI, BJ) = 0.0D00
              SSS0(I, J, BI, BJ) = 0.0D00
              SSS1(I, J, BI, BJ) = 0.0D00
            END DO
          END DO
        END DO
      END DO
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              IF(DOTHETACLIMRELAX .AND.(LATBANDCLIMRELAX .GE. ABS(YC(I,
     >  J, BI, BJ)))) THEN
                LAMBDATHETACLIMRELAX(I, J, BI, BJ) = 1D00 /
     >  TAUTHETACLIMRELAX
              ELSE
                LAMBDATHETACLIMRELAX(I, J, BI, BJ) = 0.0D00
              ENDIF
              IF(DOSALTCLIMRELAX .AND.(LATBANDCLIMRELAX .GE. ABS(YC(I,
     >  J, BI, BJ)))) THEN
                LAMBDASALTCLIMRELAX(I, J, BI, BJ) = 1D00 /
     >  TAUSALTCLIMRELAX
              ELSE
                LAMBDASALTCLIMRELAX(I, J, BI, BJ) = 0.0D00
              ENDIF
            END DO
          END DO
        END DO
      END DO
      IF(MYTHID .eq. 1) THEN
        IF(ZONALWINDFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(ZONALWINDFILE, ' ', FU, (0), MYTHID)
        ENDIF
        IF(MERIDWINDFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(MERIDWINDFILE, ' ', FV, (0), MYTHID)
        ENDIF
        IF(SURFQFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(SURFQFILE, ' ', QNET, (0), MYTHID)
        ELSE
          IF(SURFQNETFILE .NE. ' ') THEN
            CALL read_fld_xy_rs(SURFQNETFILE, ' ', QNET, (0), MYTHID)
          ENDIF
        ENDIF
        IF(EMPMRFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(EMPMRFILE, ' ', EMPMR, (0), MYTHID)
        ENDIF
        IF(SALTFLUXFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(SALTFLUXFILE, ' ', SALTFLUX, (0), MYTHID)
        ENDIF
        IF(THETACLIMFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(THETACLIMFILE, ' ', SST, (0), MYTHID)
        ENDIF
        IF(SALTCLIMFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(SALTCLIMFILE, ' ', SSS, (0), MYTHID)
        ENDIF
        IF(LAMBDATHETAFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(LAMBDATHETAFILE, ' ',
     >  LAMBDATHETACLIMRELAX, (0), MYTHID)
        ENDIF
        IF(LAMBDASALTFILE .NE. ' ') THEN
          CALL read_fld_xy_rs(LAMBDASALTFILE, ' ', LAMBDASALTCLIMRELAX,
     >  (0), MYTHID)
        ENDIF
      ENDIF
      CALL exch_xy_rl(FU, MYTHID)
      CALL exch_xy_rl(FV, MYTHID)
      CALL exch_xy_rl(QNET, MYTHID)
      CALL exch_xy_rl(EMPMR, MYTHID)
      CALL exch_xy_rl(SALTFLUX, MYTHID)
      CALL exch_xy_rl(SST, MYTHID)
      CALL exch_xy_rl(SSS, MYTHID)
      CALL exch_xy_rl(LAMBDATHETACLIMRELAX, MYTHID)
      CALL exch_xy_rl(LAMBDASALTCLIMRELAX, MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_grid(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL ini_cartesian_grid
      EXTERNAL ini_curvilinear_grid
      EXTERNAL ini_cylinder_grid
      EXTERNAL ini_spherical_polar_grid
      EXTERNAL ini_vertical_grid
      EXTERNAL load_grid_spacing
      CHARACTER(512) MSGBUF
      EXTERNAL print_error
C
C     **** Statements ****
C
      CALL load_grid_spacing(MYTHID)
      CALL ini_vertical_grid(MYTHID)
      IF(USINGCARTESIANGRID) THEN
        CALL ini_cartesian_grid(MYTHID)
      ELSE
        IF(USINGSPHERICALPOLARGRID) THEN
          CALL ini_spherical_polar_grid(MYTHID)
        ELSE
          IF(USINGCURVILINEARGRID) THEN
            CALL ini_curvilinear_grid(MYTHID)
          ELSE
            IF(USINGCYLINDRICALGRID) THEN
              CALL ini_cylinder_grid(MYTHID)
            ELSE
              IF(MYTHID .eq. 1) THEN
                WRITE(MSGBUF, '(2A)') 'S/R INI_GRID: ',
     >  'No grid coordinate system has been selected'
                CALL print_error(MSGBUF, MYTHID)
                STOP 'ABNORMAL END: S/R INI_GRID'
                RETURN
              ENDIF
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_linear_phisurf(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) DPIDP
      EXTERNAL exch_xy_rl
      EXTERNAL find_rho_scalar
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      REAL(w2f__8) RHOLOC
      EXTERNAL write_fld_xy_rl
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              BO_SURF(I, J, BI, BJ) = 0.0D00
              RECIP_BO(I, J, BI, BJ) = 0.0D00
            END DO
          END DO
        END DO
      END DO
      IF(BUOYANCYRELATION .EQ. 'OCEANIC') THEN
        doloop_ub1 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
          doloop_ub2 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub2, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                BO_SURF(I, J, BI, BJ) = GBARO
                RECIP_BO(I, J, BI, BJ) = 1D00 / GBARO
              END DO
            END DO
          END DO
        END DO
      ELSE
        IF(UNIFORMLIN_PHISURF) THEN
          doloop_ub3 = MYBYHI(MYTHID)
          DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
            doloop_ub4 = MYBXHI(MYTHID)
            DO BI = MYBXLO(MYTHID), doloop_ub4, 1
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  BO_SURF(I, J, BI, BJ) = RECIP_RHOCONST
                  RECIP_BO(I, J, BI, BJ) = RHOCONST
                END DO
              END DO
            END DO
          END DO
        ELSE
          IF(BUOYANCYRELATION .EQ. 'OCEANICP') THEN
            doloop_ub5 = MYBYHI(MYTHID)
            DO BJ = MYBYLO(MYTHID), doloop_ub5, 1
              doloop_ub6 = MYBXHI(MYTHID)
              DO BI = MYBXLO(MYTHID), doloop_ub6, 1
                DO J = -2, 43, 1
                  DO I = -2, 93, 1
                    IF((KSURFC(I, J, BI, BJ) .LE. 15) .AND.(RO_SURF(I,
     >  J, BI, BJ) .GT. 0.0D00)) THEN
                      K = KSURFC(I, J, BI, BJ)
                      CALL find_rho_scalar(TREF(K), SREF(K), RO_SURF(I,
     >  J, BI, BJ), RHOLOC, MYTHID)
                      RHOLOC = RHOLOC + RHOCONST
                      IF(RHOLOC .eq. 0.0D00) THEN
                        BO_SURF(I, J, BI, BJ) = 0.0D00
                      ELSE
                        BO_SURF(I, J, BI, BJ) = 1D00 / RHOLOC
                      ENDIF
                      RECIP_BO(I, J, BI, BJ) = RHOLOC
                    ELSE
                      BO_SURF(I, J, BI, BJ) = 0.0D00
                      RECIP_BO(I, J, BI, BJ) = 0.0D00
                    ENDIF
                  END DO
                END DO
              END DO
            END DO
          ELSE
            IF(BUOYANCYRELATION .EQ. 'ATMOSPHERIC') THEN
              doloop_ub7 = MYBYHI(MYTHID)
              DO BJ = MYBYLO(MYTHID), doloop_ub7, 1
                doloop_ub8 = MYBXHI(MYTHID)
                DO BI = MYBXLO(MYTHID), doloop_ub8, 1
                  DO J = -2, 43, 1
                    DO I = -2, 93, 1
                      IF((KSURFC(I, J, BI, BJ) .LE. 15) .AND.(RO_SURF(I
     > , J, BI, BJ) .GT. 0.0D00)) THEN
                        DPIDP = ((RO_SURF(I, J, BI, BJ) / ATM_PO) **(
     > ATM_KAPPA +(-1.0D00))) *((ATM_CP * ATM_KAPPA) / ATM_PO)
                        BO_SURF(I, J, BI, BJ) = (TREF(KSURFC(I, J, BI,
     >  BJ)) * DPIDP)
                        RECIP_BO(I, J, BI, BJ) = 1D00 / (BO_SURF(I, J,
     >  BI, BJ))
                      ELSE
                        BO_SURF(I, J, BI, BJ) = 0.0
                        RECIP_BO(I, J, BI, BJ) = 0.0
                      ENDIF
                    END DO
                  END DO
                END DO
              END DO
            ELSE
              STOP 'INI_LINEAR_PHISURF: We should never reach this p'
     >  // 'oint!'
              RETURN
            ENDIF
          ENDIF
        ENDIF
      ENDIF
      CALL exch_xy_rl(BO_SURF, MYTHID)
      CALL exch_xy_rl(RECIP_BO, MYTHID)
      IF(((BUOYANCYRELATION .EQ. 'OCEANICP') .OR.(BUOYANCYRELATION .EQ.
     >  'ATMOSPHERIC')) .AND.(.NOT. UNIFORMLIN_PHISURF)) THEN
        IF(MYTHID .eq. 1) THEN
          CALL write_fld_xy_rl('Bo_surf', ' ', BO_SURF, (0), MYTHID)
        ENDIF
      ENDIF
      doloop_ub9 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub9, 1
        doloop_ub10 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub10, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              PHI0SURF(I, J, BI, BJ) = 0.0
            END DO
          END DO
        END DO
      END DO
      IF((BUOYANCYRELATION .EQ. 'ATMOSPHERIC') .AND.(TOPOFILE .NE. ' ')
     > ) THEN
        STOP 'CANNOT PRESENTLY USE THIS OPTION WITH ADJOINT'
        RETURN
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_masks_etc(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Global Variables & Derived Type Definitions ****
C
      SAVE /local_ini_masks_etc/
      COMMON /local_ini_masks_etc/ TMPFLD
      REAL(w2f__8) TMPFLD(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL barrier
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_uv_xyz_rs
      EXTERNAL global_sum_r8
      REAL(w2f__8) HFACCTMP
      REAL(w2f__8) HFACMNSZ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      EXTERNAL plot_field_xyrs
      EXTERNAL plot_field_xyzrs
      REAL(w2f__8) TILEAREA
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
      INTEGER(w2f__i4) doloop_ub11
      INTEGER(w2f__i4) doloop_ub12
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            HFACMNSZ = MAX(HFACMIN, MIN(RECIP_DRF(K) * HFACMINDR,
     >  1.0D00))
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                HFACCTMP = RECIP_DRF(K) *(RF(K) - R_LOW(I, J, BI, BJ))
                HFACCTMP = MIN(MAX(HFACCTMP, 0.0D00), 1.0D00)
                IF(HFACCTMP .LT. HFACMNSZ) THEN
                  IF(HFACCTMP .LT.(HFACMNSZ * 5.0D-01)) THEN
                    HFACC(I, J, K, BI, BJ) = 0.0
                  ELSE
                    HFACC(I, J, K, BI, BJ) = HFACMNSZ
                  ENDIF
                ELSE
                  HFACC(I, J, K, BI, BJ) = HFACCTMP
                ENDIF
              END DO
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              R_LOW(I, J, BI, BJ) = RF(1)
              DO K = 15, 1, (-1)
                R_LOW(I, J, BI, BJ) = (R_LOW(I, J, BI, BJ) - DRF(K) *
     >  HFACC(I, J, K, BI, BJ))
              END DO
            END DO
          END DO
        END DO
      END DO
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          DO K = 1, 15, 1
            HFACMNSZ = MAX(HFACMIN, MIN(RECIP_DRF(K) * HFACMINDR,
     >  1.0D00))
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                HFACCTMP = RECIP_DRF(K) *(RF(K) - RO_SURF(I, J, BI, BJ)
     > )
                HFACCTMP = HFACC(I, J, K, BI, BJ) - MAX(HFACCTMP,
     >  0.0D00)
                HFACCTMP = MAX(HFACCTMP, 0.0D00)
                IF(HFACCTMP .LT. HFACMNSZ) THEN
                  IF(HFACCTMP .LT.(HFACMNSZ * 5.0D-01)) THEN
                    HFACC(I, J, K, BI, BJ) = 0.0
                  ELSE
                    HFACC(I, J, K, BI, BJ) = HFACMNSZ
                  ENDIF
                ELSE
                  HFACC(I, J, K, BI, BJ) = HFACCTMP
                ENDIF
              END DO
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              TMPFLD(I, J, BI, BJ) = 0.0
              KSURFC(I, J, BI, BJ) = 16
              MASKH(I, J, BI, BJ) = 0.0
              RO_SURF(I, J, BI, BJ) = R_LOW(I, J, BI, BJ)
              DO K = 15, 1, (-1)
                RO_SURF(I, J, BI, BJ) = (RO_SURF(I, J, BI, BJ) + DRF(K)
     >  * HFACC(I, J, K, BI, BJ))
                IF(HFACC(I, J, K, BI, BJ) .ne. 0.0D00) THEN
                  KSURFC(I, J, BI, BJ) = K
                  MASKH(I, J, BI, BJ) = 1.0
                  TMPFLD(I, J, BI, BJ) = (TMPFLD(I, J, BI, BJ) + 1.0D00
     > )
                ENDIF
              END DO
              KLOWC(I, J, BI, BJ) = 0
              DO K = 1, 15, 1
                IF(HFACC(I, J, K, BI, BJ) .ne. 0.0D00) THEN
                  KLOWC(I, J, BI, BJ) = K
                ENDIF
              END DO
            END DO
          END DO
        END DO
      END DO
      CALL plot_field_xyrs(R_LOW, 'Model R_low (ini_masks_etc)', (1),
     >  MYTHID)
      CALL plot_field_xyrs(RO_SURF, 'Model Ro_surf (ini_masks_etc)', (1
     > ), MYTHID)
      GLOBALAREA = 0.0D00
      doloop_ub3 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
        doloop_ub4 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub4, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              TMPFLD(I, J, BI, BJ) = (RO_SURF(I, J, BI, BJ) - R_LOW(I,
     >  J, BI, BJ))
              IF(TMPFLD(I, J, BI, BJ) .LE. 0.0D00) THEN
                RECIP_RCOL(I, J, BI, BJ) = 0.0
              ELSE
                RECIP_RCOL(I, J, BI, BJ) = 1D00 / (TMPFLD(I, J, BI, BJ)
     > )
              ENDIF
            END DO
          END DO
          TILEAREA = 0.0D00
          DO J = 1, 40, 1
            DO I = 1, 90, 1
              TILEAREA = TILEAREA + MASKH(I, J, BI, BJ) * RA(I, J, BI,
     >  BJ)
            END DO
          END DO
          GLOBALAREA = TILEAREA + GLOBALAREA
        END DO
      END DO
      CALL global_sum_r8(GLOBALAREA, MYTHID)
      doloop_ub5 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub5, 1
        doloop_ub6 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub6, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -1, 93, 1
                HFACW(I, J, K, BI, BJ) = MIN(HFACC(I, J, K, BI, BJ),
     >  HFACC(I + (-1), J, K, BI, BJ))
              END DO
            END DO
            DO J = -1, 43, 1
              DO I = -2, 93, 1
                HFACS(I, J, K, BI, BJ) = MIN(HFACC(I, J, K, BI, BJ),
     >  HFACC(I, J + (-1), K, BI, BJ))
              END DO
            END DO
          END DO
        END DO
      END DO
      CALL exch_uv_xyz_rs(HFACW, HFACS, (.FALSE.), MYTHID)
      doloop_ub7 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub7, 1
        doloop_ub8 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub8, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                IF(DYG(I, J, BI, BJ) .eq. 0.0D00) THEN
                  HFACW(I, J, K, BI, BJ) = 0.0
                ENDIF
                IF(DXG(I, J, BI, BJ) .eq. 0.0D00) THEN
                  HFACS(I, J, K, BI, BJ) = 0.0
                ENDIF
              END DO
            END DO
          END DO
        END DO
      END DO
      CALL barrier(MYTHID)
      CALL plot_field_xyzrs(HFACC, 'hFacC', (15), (1), MYTHID)
      CALL plot_field_xyzrs(HFACW, 'hFacW', (15), (1), MYTHID)
      CALL plot_field_xyzrs(HFACS, 'hFacS', (15), (1), MYTHID)
      doloop_ub9 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub9, 1
        doloop_ub10 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub10, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                IF(HFACC(I, J, K, BI, BJ) .ne. 0.0D00) THEN
                  RECIP_HFACC(I, J, K, BI, BJ) = 1D00 / (HFACC(I, J, K,
     >  BI, BJ))
                  MASKC(I, J, K, BI, BJ) = 1.0
                ELSE
                  RECIP_HFACC(I, J, K, BI, BJ) = 0.0
                  MASKC(I, J, K, BI, BJ) = 0.0
                ENDIF
                IF(HFACW(I, J, K, BI, BJ) .ne. 0.0D00) THEN
                  RECIP_HFACW(I, J, K, BI, BJ) = 1D00 / (HFACW(I, J, K,
     >  BI, BJ))
                  MASKW(I, J, K, BI, BJ) = 1.0
                ELSE
                  RECIP_HFACW(I, J, K, BI, BJ) = 0.0
                  MASKW(I, J, K, BI, BJ) = 0.0
                ENDIF
                IF(HFACS(I, J, K, BI, BJ) .ne. 0.0D00) THEN
                  RECIP_HFACS(I, J, K, BI, BJ) = 1D00 / (HFACS(I, J, K,
     >  BI, BJ))
                  MASKS(I, J, K, BI, BJ) = 1.0
                ELSE
                  RECIP_HFACS(I, J, K, BI, BJ) = 0.0
                  MASKS(I, J, K, BI, BJ) = 0.0
                ENDIF
              END DO
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              KSURFW(I, J, BI, BJ) = 16
              KSURFS(I, J, BI, BJ) = 16
              DO K = 15, 1, (-1)
                IF(HFACW(I, J, K, BI, BJ) .ne. 0.0D00) THEN
                  KSURFW(I, J, BI, BJ) = K
                ENDIF
                IF(HFACS(I, J, K, BI, BJ) .ne. 0.0D00) THEN
                  KSURFS(I, J, BI, BJ) = K
                ENDIF
              END DO
            END DO
          END DO
        END DO
      END DO
      doloop_ub11 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub11, 1
        doloop_ub12 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub12, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              IF(DXG(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_DXG(I, J, BI, BJ) = 1D00 / (DXG(I, J, BI, BJ))
              ENDIF
              IF(DYG(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_DYG(I, J, BI, BJ) = 1D00 / (DYG(I, J, BI, BJ))
              ENDIF
              IF(DXC(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_DXC(I, J, BI, BJ) = 1D00 / (DXC(I, J, BI, BJ))
              ENDIF
              IF(DYC(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_DYC(I, J, BI, BJ) = 1D00 / (DYC(I, J, BI, BJ))
              ENDIF
              IF(DXF(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_DXF(I, J, BI, BJ) = 1D00 / (DXF(I, J, BI, BJ))
              ENDIF
              IF(DYF(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_DYF(I, J, BI, BJ) = 1D00 / (DYF(I, J, BI, BJ))
              ENDIF
              IF(DXV(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_DXV(I, J, BI, BJ) = 1D00 / (DXV(I, J, BI, BJ))
              ENDIF
              IF(DYU(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_DYU(I, J, BI, BJ) = 1D00 / (DYU(I, J, BI, BJ))
              ENDIF
              IF(RA(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_RA(I, J, BI, BJ) = 1D00 / (RA(I, J, BI, BJ))
              ENDIF
              IF(RAS(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_RAS(I, J, BI, BJ) = 1D00 / (RAS(I, J, BI, BJ))
              ENDIF
              IF(RAW(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_RAW(I, J, BI, BJ) = 1D00 / (RAW(I, J, BI, BJ))
              ENDIF
              IF(RAZ(I, J, BI, BJ) .ne. 0.0D00) THEN
                RECIP_RAZ(I, J, BI, BJ) = 1D00 / (RAZ(I, J, BI, BJ))
              ENDIF
            END DO
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_mixing(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_xyz_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                DIFFKR(I, J, K, BI, BJ) = DIFFKRNRS(K)
              END DO
            END DO
          END DO
        END DO
      END DO
      CALL exch_xyz_rl(DIFFKR, MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_p_ground(SELECTMODE, HFLD, PFLD, MYTHID)
      use w2f__types
      use size_mod
      use grid_mod
      use eeparams_mod
      use params_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) SELECTMODE
      REAL(w2f__8) HFLD(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      REAL(w2f__8) PFLD(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL analylic_theta
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) DDPI
      REAL(w2f__8) DPHVR
      REAL(w2f__8) DPIHVR(1 : 60)
      REAL(w2f__8) DZLOC
      LOGICAL(w2f__i4) FINDPOSURF
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) KLEV
      INTEGER(w2f__i4) KS
      CHARACTER(512) MSGBUF
      INTEGER(w2f__i4) NLEVHVR
      PARAMETER ( NLEVHVR = 60)
      REAL(w2f__8) PHILOC
      REAL(w2f__8) PHIREF(1 : 31)
      REAL(w2f__8) PIHVR(1 : 61)
      REAL(w2f__8) PILOC
      REAL(w2f__8) PLEVHVR(1 : 61)
      REAL(w2f__8) PLOWHVR
      REAL(w2f__8) PMIDHVR(1 : 60)
      REAL(w2f__8) PO_SURF
      EXTERNAL print_error
      REAL(w2f__8) PSNORM
      REAL(w2f__8) RATIORM(1 : 15)
      REAL(w2f__8) RATIORP(1 : 15)
      REAL(w2f__8) RECIP_KAPPA
      REAL(w2f__8) RHALF(1 : 31)
      REAL(w2f__8) RMIDKP1
      REAL(w2f__8) THETAHVR(1 : 60)
      REAL(w2f__8) YLATLOC
      REAL(w2f__8) ZLOC
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
C
C     **** Statements ****
C
      IF((SELECTFINDROSURF .GT. 1) .OR.(SELECTFINDROSURF .LT. 0)) THEN
        WRITE(MSGBUF, '(A,I2,A)') 'INI_P_GROUND: selectFindRoSurf =',
     >  SELECTFINDROSURF, ' <== bad value !'
        CALL print_error(MSGBUF, MYTHID)
        STOP 'INI_P_GROUND'
        RETURN
      ENDIF
      DO K = 1, 15, 1
        RHALF(K * 2 + (-1)) = RF(K)
        RHALF(K * 2) = RC(K)
      END DO
      RHALF(31) = RF(16)
      IF((SELECTMODE * SELECTFINDROSURF) .LE. 0) THEN
        PHIREF(1) = 0.0
        IF(INTEGR_GEOPOT .eq. 1) THEN
          DO K = 1, 30, 1
            KS = (K + 1) / 2
            DDPI = ATM_CP *((((RHALF(K) / ATM_PO) ** ATM_KAPPA)) -(((
     > RHALF(K + 1) / ATM_PO) ** ATM_KAPPA)))
            PHIREF(K + 1) = (PHIREF(K) + TREF(KS) * DDPI)
          END DO
        ELSE
          K = 1
          DDPI = ATM_CP *((((RF(K) / ATM_PO) ** ATM_KAPPA)) -(((RC(K) /
     >  ATM_PO) ** ATM_KAPPA)))
          PHIREF(K * 2) = (PHIREF(1) + TREF(K) * DDPI)
          DO K = 1, 14, 1
            DDPI = ATM_CP *((((RC(K) / ATM_PO) ** ATM_KAPPA)) -(((RC(K
     >  + 1) / ATM_PO) ** ATM_KAPPA)))
            PHIREF(K * 2 + 1) = (PHIREF(K * 2) + TREF(K) * DDPI *
     >  5.0D-01)
            PHIREF(K * 2 + 2) = (PHIREF(K * 2) + DDPI * 5.0D-01 *(TREF(
     > K) + TREF(K + 1)))
          END DO
          K = 15
          DDPI = ATM_CP *((((RC(K) / ATM_PO) ** ATM_KAPPA)) -(((RF(K +
     >  1) / ATM_PO) ** ATM_KAPPA)))
          PHIREF(K * 2 + 1) = (PHIREF(K * 2) + TREF(K) * DDPI)
        ENDIF
        DO K = 1, 31, 1
          PHIREF(K) = (PHIREF(K) * RECIP_GRAVITY)
        END DO
        IF(MYTHID .eq. 1) THEN
          WRITE(STANDARDMESSAGEUNIT, '(2A)')
     >  'INI_P_GROUND: PhiRef/g [m] at Center (integer) ',
     >  'and Interface (half-int.) levels:'
          DO K = 1, 31, 1
            WRITE(STANDARDMESSAGEUNIT, '(A,F5.1,A,F10.1,A,F12.3)')
     >  '  K=', (K * 5.0E-01), '  ;  r=', RHALF(K), '  ;  phiRef/g=',
     >  PHIREF(K)
          END DO
        ENDIF
      ENDIF
      IF((SELECTFINDROSURF .eq. 0) .AND.(SELECTMODE .GT. 0)) THEN
        doloop_ub = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub, 1
          doloop_ub0 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub0, 1
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                KS = 1
                DO K = 1, 30, 1
                  IF(PHIREF(K) .LE. HFLD(I, J, BI, BJ)) THEN
                    KS = K
                  ENDIF
                END DO
                PO_SURF = RHALF(KS) +(((RHALF(KS + 1) - RHALF(KS)) *(
     > HFLD(I, J, BI, BJ) - PHIREF(KS))) /(PHIREF(KS + 1) - PHIREF(KS))
     > )
                PFLD(I, J, BI, BJ) = PO_SURF
              END DO
            END DO
          END DO
        END DO
      ENDIF
      IF(SELECTFINDROSURF .eq. 1) THEN
        RECIP_KAPPA = 1D00 / ATM_KAPPA
        PLOWHVR = 4.00000000000000022204D-01
        DPHVR = 6.0D+01
        DPHVR = (1.0D00 - PLOWHVR) / DPHVR
        PLEVHVR(1) = (RO_SEALEVEL / ATM_PO)
        PIHVR(1) = (ATM_CP *((PLEVHVR(1) ** ATM_KAPPA)))
        DO K = 1, 60, 1
          PLEVHVR(K + 1) = (PLEVHVR(1) - FLOAT(K) * DPHVR)
          PIHVR(K + 1) = (ATM_CP *((PLEVHVR(K + 1) ** ATM_KAPPA)))
          PMIDHVR(K) = ((PLEVHVR(K) + PLEVHVR(K + 1)) * 5.0D-01)
          DPIHVR(K) = (PIHVR(K) - PIHVR(K + 1))
        END DO
        DO K = 1, 15, 1
          RATIORM(K) = 1.0D00
          RATIORP(K) = 1.0D00
          IF(K .GT. 1) THEN
            RATIORM(K) = ((DRC(K) * 5.0D-01) /(RF(K) - RC(K)))
          ENDIF
          IF(K .LT. 15) THEN
            RATIORP(K) = ((DRC(K + 1) * 5.0D-01) /(RC(K) - RF(K + 1)))
          ENDIF
        END DO
      ENDIF
      IF((SELECTMODE * SELECTFINDROSURF) .GT. 0) THEN
        doloop_ub1 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
          doloop_ub2 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub2, 1
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                IF(HFLD(I, J, BI, BJ) .LE. 0.0D00) THEN
                  PFLD(I, J, BI, BJ) = RO_SEALEVEL
                ELSE
                  YLATLOC = YC(I, J, BI, BJ)
                  CALL analylic_theta(YLATLOC, PMIDHVR, THETAHVR, (60),
     >  MYTHID)
                  ZLOC = 0.0D00
                  DO K = 1, 60, 1
                    IF(ZLOC .GE. 0.0D00) THEN
                      DZLOC = RECIP_GRAVITY * DPIHVR(K) * THETAHVR(K)
                      IF(HFLD(I, J, BI, BJ) .LE.(DZLOC + ZLOC)) THEN
                        PILOC = PIHVR(K) -((GRAVITY *(HFLD(I, J, BI, BJ
     > ) - ZLOC)) / THETAHVR(K))
                        PSNORM = (PILOC / ATM_CP) ** RECIP_KAPPA
                        ZLOC = -1.0D00
                      ELSE
                        ZLOC = DZLOC + ZLOC
                      ENDIF
                    ENDIF
                  END DO
                  IF(ZLOC .GE. 0.0D00) THEN
                    WRITE(MSGBUF, '(2A)')
     >  'INI_P_GROUND: FAIL in trying to find Pfld:',
     >  ' selectMode,i,j,bi,bj=', SELECTMODE, I, J, BI, BJ
                    CALL print_error(MSGBUF, MYTHID)
                    WRITE(MSGBUF, '(A,F7.1,2A,F6.4,A,F8.0)')
     >  'INI_P_GROUND: Hfld=', HFLD(I, J, BI, BJ), ' exceeds',
     >  ' Zloc(lowest P=', PLEVHVR(61), ' )=', ZLOC
                    CALL print_error(MSGBUF, MYTHID)
                    STOP 'ABNORMAL END: S/R INI_P_GROUND'
                    RETURN
                  ELSE
                    PFLD(I, J, BI, BJ) = (PSNORM * ATM_PO)
                  ENDIF
                ENDIF
              END DO
            END DO
            IF((SELECTMODE .eq. 2) .AND.(INTEGR_GEOPOT .ne. 1)) THEN
              DO J = 1, 40, 1
                DO I = 1, 90, 1
                  PO_SURF = PFLD(I, J, BI, BJ)
                  IF((RC(1) .GT. PO_SURF) .AND.(RC(15) .LT. PO_SURF))
     >  THEN
                    FINDPOSURF = .TRUE.
                    DO K = 1, 15, 1
                      IF(FINDPOSURF .AND.(RC(K) .LE. PO_SURF)) THEN
                        PO_SURF = RC(K) +((PO_SURF - RC(K)) / RATIORM(K
     > ))
                        FINDPOSURF = .FALSE.
                      ENDIF
                      RMIDKP1 = RF(K + 1)
                      IF(K .LT. 15) THEN
                        RMIDKP1 = (RC(K) + RC(K + 1)) * 5.0D-01
                      ENDIF
                      IF(FINDPOSURF .AND.(PO_SURF .GE. RMIDKP1)) THEN
                        PO_SURF = RC(K) +((PO_SURF - RC(K)) / RATIORP(K
     > ))
                        FINDPOSURF = .FALSE.
                      ENDIF
                    END DO
                    IF(FINDPOSURF) THEN
                      STOP 'S/R INI_P_GROUND: Pb with selectMode=2'
                      RETURN
                    ENDIF
                  ENDIF
                  PFLD(I, J, BI, BJ) = PO_SURF
                END DO
              END DO
            ENDIF
          END DO
        END DO
      ENDIF
      IF(SELECTMODE .LT. 0) THEN
        doloop_ub3 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
          doloop_ub4 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub4, 1
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                KS = KSURFC(I, J, BI, BJ)
                IF(KS .LE. 15) THEN
                  IF(RC(KS) .LE. PFLD(I, J, BI, BJ)) THEN
                    PHILOC = PHIREF(KS * 2) +(((PHIREF(KS * 2 + (-1)) -
     >  PHIREF(KS * 2)) *(PFLD(I, J, BI, BJ) - RC(KS))) /(RHALF(KS * 2
     >  + (-1)) - RHALF(KS * 2)))
                  ELSE
                    PHILOC = PHIREF(KS * 2) +(((PHIREF(KS * 2 + 1) -
     >  PHIREF(KS * 2)) *(PFLD(I, J, BI, BJ) - RC(KS))) /(RHALF(KS * 2
     >  + 1) - RHALF(KS * 2)))
                  ENDIF
                  HFLD(I, J, BI, BJ) = PHILOC
                ELSE
                  HFLD(I, J, BI, BJ) = 0.0
                ENDIF
              END DO
            END DO
            IF(SELECTFINDROSURF .eq. 1) THEN
              DO J = 1, 40, 1
                DO I = 1, 90, 1
                  ZLOC = 0.0D00
                  IF(PFLD(I, J, BI, BJ) .LT. RO_SEALEVEL) THEN
                    PO_SURF = PFLD(I, J, BI, BJ)
                    IF((SELECTMODE .eq.(-2)) .AND.(INTEGR_GEOPOT .ne. 1
     > )) THEN
                      IF((RC(1) .GT. PO_SURF) .AND.(RC(15) .LT. PO_SURF
     > )) THEN
                        FINDPOSURF = .TRUE.
                        DO K = 1, 15, 1
                          IF(FINDPOSURF .AND.(RC(K) .LE. PO_SURF)) THEN
                            PO_SURF = RC(K) + RATIORM(K) *(PO_SURF - RC
     > (K))
                            FINDPOSURF = .FALSE.
                          ENDIF
                          IF(FINDPOSURF .AND.(RF(K + 1) .LE. PO_SURF))
     >  THEN
                            PO_SURF = RC(K) + RATIORP(K) *(PO_SURF - RC
     > (K))
                            FINDPOSURF = .FALSE.
                          ENDIF
                        END DO
                      ENDIF
                    ENDIF
                    PSNORM = PO_SURF / ATM_PO
                    KLEV = INT((PLEVHVR(1) - PSNORM) / DPHVR) + 1
                    YLATLOC = YC(I, J, BI, BJ)
                    CALL analylic_theta(YLATLOC, PMIDHVR, THETAHVR,
     >  KLEV, MYTHID)
                    doloop_ub5 = KLEV +(-1)
                    DO K = 1, doloop_ub5, 1
                      DZLOC = RECIP_GRAVITY * DPIHVR(K) * THETAHVR(K)
                      ZLOC = DZLOC + ZLOC
                    END DO
                    DZLOC = RECIP_GRAVITY * THETAHVR(KLEV) *(PIHVR(KLEV
     > ) - ATM_CP *((PSNORM ** ATM_KAPPA)))
                    ZLOC = DZLOC + ZLOC
                  ENDIF
                  PHI0SURF(I, J, BI, BJ) = (GRAVITY *(ZLOC - HFLD(I, J,
     >  BI, BJ)))
                  HFLD(I, J, BI, BJ) = ZLOC
                END DO
              END DO
            ENDIF
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE analylic_theta(YLAT, PNLEV, THETALEV, KSIZE, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) YLAT
      INTEGER(w2f__i4) KSIZE
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) PNLEV(1 : KSIZE)
      REAL(w2f__8) THETALEV(1 : KSIZE)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__762
      INTEGER(w2f__i8) t__763
      REAL(w2f__8) A1TMP
      REAL(w2f__8) CATMP
      SAVE CATMP
      REAL(w2f__8) CBTMP
      SAVE CBTMP
      INTEGER(w2f__i4) K
      REAL(w2f__8) PPH
      REAL(w2f__8) PPL
      REAL(w2f__8) PPM
      REAL(w2f__8) PPN0
      SAVE PPN0
      REAL(w2f__8) PPN1
      SAVE PPN1
      REAL(w2f__8) PPN2
      SAVE PPN2
      REAL(w2f__8) PPN3A
      SAVE PPN3A
      REAL(w2f__8) PPN3B
      SAVE PPN3B
      REAL(w2f__8) PPN4
      SAVE PPN4
      REAL(w2f__8) PPR
      REAL(w2f__8) TTDC
      SAVE TTDC
      REAL(w2f__8) TTP1
      SAVE TTP1
      REAL(w2f__8) TTP2
      SAVE TTP2
      REAL(w2f__8) TTP2Y
      REAL(w2f__8) TTP3
      SAVE TTP3
      REAL(w2f__8) TTP4
      SAVE TTP4
      REAL(w2f__8) TTP4Y
      REAL(w2f__8) TTP5
      SAVE TTP5
      REAL(w2f__8) YATMP
      REAL(w2f__8) YBTMP
      REAL(w2f__8) YCTMP
      REAL(w2f__8) YDTMP
      REAL(w2f__8) YYA
      SAVE YYA
      REAL(w2f__8) YYAD
      SAVE YYAD
      REAL(w2f__8) YYB
      SAVE YYB
      REAL(w2f__8) YYBD
      SAVE YYBD
      REAL(w2f__8) YYC
      SAVE YYC
      REAL(w2f__8) YYCD
      SAVE YYCD
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
C
C     **** Initializers ****
C
      DATA CATMP / 2.60000000000000008882D00 /
      DATA CBTMP / 1.5D00 /
      DATA PPN0 / 1.00000000000000005551D-01 /
      DATA PPN1 / 1.9000000000000000222D-01 /
      DATA PPN2 / 2.99999999999999988898D-01 /
      DATA PPN3A / 9.00000000000000022204D-01 /
      DATA PPN3B / 6.99999999999999955591D-01 /
      DATA PPN4 / 9.25000000000000044409D-01 /
      DATA TTDC / 3.29999999999999982236D00 /
      DATA TTP1 / 3.5D+02 /
      DATA TTP2 / 3.42D+02 /
      DATA TTP3 / 3.07D+02 /
      DATA TTP4 / 3.01D+02 /
      DATA TTP5 / 2.57D+02 /
      DATA YYA / 4.5D+01 /
      DATA YYAD / 9.00000000000000022204D-01 /
      DATA YYB / 6.5D+01 /
      DATA YYBD / 9.00000000000000022204D-01 /
      DATA YYC / 6.5D+01 /
      DATA YYCD / 1.0D+01 /
C
C     **** Statements ****
C
      t__762 = KSIZE
      t__763 = MAX(t__762, 0_w2f__i8)
      YATMP = ABS(YLAT) - YYA
      YATMP = YYA + MIN(YATMP / YYAD, 0.0D00) + MAX(YATMP, 0.0D00)
      YATMP = COS(MAX(YATMP, 0.0D00) * 1.74532925199432954744D-02)
      YBTMP = ABS(YLAT) - YYB
      YBTMP = YYB +(YBTMP / YYBD)
      YBTMP = COS(MAX(MIN(YBTMP, 9.0D+01), 0.0D00) *
     >  1.74532925199432954744D-02)
      YCTMP = ABS(YLAT) - YYC
      YCTMP = MAX(1.0D00 -((YCTMP / YYCD) ** 2), 0.0D00)
      YDTMP = PPN3A + YCTMP *(PPN3B - PPN3A)
      TTP2Y = TTP3 +(YATMP ** CATMP) *(TTP2 - TTP3)
      TTP4Y = TTP5 +(YBTMP ** CBTMP) *(TTP4 - TTP5)
      A1TMP = (PPN2 * PPN1 *(TTP1 - TTP2Y)) /(PPN2 - PPN1)
      doloop_ub = KSIZE
      DO K = 1, doloop_ub, 1
        PPL = MIN(PNLEV(K), PPN1)
        PPM = MIN(PPN2, MAX(PNLEV(K), PPN1))
        PPH = MAX(PNLEV(K), PPN2)
        PPR = (PPN0 + ABS(PPL - PPN0) - PPN1) /(PPN2 - PPN1)
        THETALEV(K) = (A1TMP *(1D00 / PPM - 1D00 / PPN1) +(PPL **(-
     >  ATM_KAPPA)) *((PPN1 ** ATM_KAPPA) * TTP1 *(1.0D00 - PPR) +(PPN2
     >  ** ATM_KAPPA) * PPR * TTP2Y) +(((PPH - PPN2) *(TTP4Y - TTP2Y))
     >  /(PPN4 - PPN2)) +((MAX(PNLEV(K) - YDTMP, 0.0D00) *(TTDC + YCTMP
     > )) /(1.0D00 - YDTMP)))
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_pressure(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use eos_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) K
      CHARACTER(512) MSGBUF
      EXTERNAL print_message
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      IMIN = -2
      IMAX = 93
      JMIN = -2
      JMAX = 43
      WRITE(MSGBUF, '(a)')
     >  'Start initial hydrostatic pressure computation'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                TOTPHIHYD(I, J, K, BI, BJ) = 0.0D00
              END DO
            END DO
          END DO
        END DO
      END DO
      IF(USEDYNP_INEOS_ZC) THEN
      ELSE
        WRITE(MSGBUF, '(A,A)')
     >  'Pressure is predetermined for buoyancyRelation ',
     >  BUOYANCYRELATION(1_w2f__i8 : 11)
        CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      ENDIF
      WRITE(MSGBUF, '(A)') ' '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_pnh(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_psurf(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use surface_mod
      use cd_code_vars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_xy_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      EXTERNAL read_fld_xy_rl
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ETAN(I, J, BI, BJ) = 0.0D00
            END DO
          END DO
        END DO
      END DO
      IF(PSURFINITFILE .NE. ' ') THEN
        IF(MYTHID .eq. 1) THEN
          CALL read_fld_xy_rl(PSURFINITFILE, ' ', ETAN, (0), MYTHID)
        ENDIF
      ENDIF
      CALL exch_xy_rl(ETAN, MYTHID)
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ETANM1(I, J, BI, BJ) = ETAN(I, J, BI, BJ)
            END DO
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_salt(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_xyz_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) LOCALWARNINGS
      CHARACTER(512) MSGBUF
      EXTERNAL plot_field_xyzrl
      EXTERNAL print_error
      EXTERNAL read_fld_xyz_rl
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                SALT(I, J, K, BI, BJ) = SREF(K)
              END DO
            END DO
          END DO
        END DO
      END DO
      IF(HYDROGSALTFILE .NE. ' ') THEN
        IF(MYTHID .eq. 1) THEN
          CALL read_fld_xyz_rl(HYDROGSALTFILE, ' ', SALT, (0), MYTHID)
        ENDIF
        CALL exch_xyz_rl(SALT, MYTHID)
      ENDIF
      LOCALWARNINGS = 0
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                IF(MASKC(I, J, K, BI, BJ) .eq. 0.0D00) THEN
                  SALT(I, J, K, BI, BJ) = 0.0
                ENDIF
              END DO
            END DO
            IF(SREF(K) .ne. 0.0D00) THEN
              DO J = 1, 40, 1
                DO I = 1, 90, 1
                  IF((SALT(I, J, K, BI, BJ) .eq. 0.0D00) .AND.(MASKC(I,
     >  J, K, BI, BJ) .ne. 0.0D00)) THEN
                    LOCALWARNINGS = LOCALWARNINGS + 1
                  ENDIF
                END DO
              END DO
            ENDIF
          END DO
        END DO
      END DO
      IF(LOCALWARNINGS .ne. 0) THEN
        WRITE(MSGBUF, '(A,A)')
     >  'S/R INI_SALT: salt = 0 identically. If this is i' //
     >  'ntentional',
     >  'you will need to edit ini_salt.F to avoid this s' //
     >  'afety check'
        CALL print_error(MSGBUF, MYTHID)
        STOP 'ABNORMAL END: S/R INI_SALT'
        RETURN
      ENDIF
      CALL plot_field_xyzrl(SALT, 'Initial Salinity', (15), (1), MYTHID
     > )
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_spherical_polar_grid(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) DLAT
      REAL(w2f__8) DLON
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IG
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JG
      REAL(w2f__8) LAT
      REAL(w2f__8) XG0
      REAL(w2f__8) XGLOC(-2 : 94, -2 : 44)
      REAL(w2f__8) YG0
      REAL(w2f__8) YGLOC(-2 : 94, -2 : 44)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          JG = MYYGLOBALLO + BJ * 40 +(-40)
          IG = MYXGLOBALLO + BI * 90 +(-90)
          XG0 = THETAMIN
          doloop_ub1 = IG +(-1)
          DO I = 1, doloop_ub1, 1
            XG0 = DELX(I) + XG0
          END DO
          DO I = 1, 3, 1
            XG0 = XG0 - DELX(MOD(IG - I + 269, 90) + 1)
          END DO
          YG0 = PHIMIN
          doloop_ub2 = JG +(-1)
          DO J = 1, doloop_ub2, 1
            YG0 = DELY(J) + YG0
          END DO
          DO J = 1, 3, 1
            YG0 = YG0 - DELY(MOD(JG - J + 119, 40) + 1)
          END DO
          DO J = -2, 44, 1
            XGLOC((-2), J) = XG0
            DO I = -2, 93, 1
              XGLOC(I + 1, J) = (DELX(MOD(I + MYXGLOBALLO + BI * 90 +
     >  178, 90) + 1) + XGLOC(I, J))
            END DO
          END DO
          DO I = -2, 94, 1
            YGLOC(I, (-2)) = YG0
            DO J = -2, 43, 1
              YGLOC(I, J + 1) = (DELY(MOD(J + MYYGLOBALLO + BJ * 40 +
     >  78, 40) + 1) + YGLOC(I, J))
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              XG(I, J, BI, BJ) = XGLOC(I, J)
              YG(I, J, BI, BJ) = YGLOC(I, J)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              XC(I, J, BI, BJ) = ((XGLOC(I + 1, J + 1) + XGLOC(I, J + 1
     > ) + XGLOC(I, J) + XGLOC(I + 1, J)) * 2.5D-01)
              YC(I, J, BI, BJ) = ((YGLOC(I + 1, J + 1) + YGLOC(I, J + 1
     > ) + YGLOC(I, J) + YGLOC(I + 1, J)) * 2.5D-01)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LAT = YC(I, J, BI, BJ)
              DLON = DELX(MOD(I + MYXGLOBALLO + BI * 90 + 178, 90) + 1)
              DLAT = DELY(MOD(J + MYYGLOBALLO + BJ * 40 + 78, 40) + 1)
              DXF(I, J, BI, BJ) = (DLON * RSPHERE * COS(LAT *
     >  1.74532925199432954744D-02) * 1.74532925199432954744D-02)
              DYF(I, J, BI, BJ) = (DLAT * RSPHERE *
     >  1.74532925199432954744D-02)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LAT = (YGLOC(I, J) + YGLOC(I + 1, J)) * 5.0D-01
              DLON = DELX(MOD(I + MYXGLOBALLO + BI * 90 + 178, 90) + 1)
              DLAT = DELY(MOD(J + MYYGLOBALLO + BJ * 40 + 78, 40) + 1)
              DXG(I, J, BI, BJ) = (DLON * RSPHERE * COS(LAT *
     >  1.74532925199432954744D-02) * 1.74532925199432954744D-02)
              IF(DXG(I, J, BI, BJ) .LT. 1.0D00) THEN
                DXG(I, J, BI, BJ) = 0.0
              ENDIF
              DYG(I, J, BI, BJ) = (DLAT * RSPHERE *
     >  1.74532925199432954744D-02)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              DXC(I, J, BI, BJ) = 0.0
              DYC(I, J, BI, BJ) = 0.0
              DXV(I, J, BI, BJ) = 0.0
              DYU(I, J, BI, BJ) = 0.0
              RAW(I, J, BI, BJ) = 0.0
              RAS(I, J, BI, BJ) = 0.0
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -1, 93, 1
              DXC(I, J, BI, BJ) = ((DXF(I, J, BI, BJ) + DXF(I + (-1), J
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -1, 43, 1
            DO I = -2, 93, 1
              DYC(I, J, BI, BJ) = ((DYF(I, J, BI, BJ) + DYF(I, J + (-1)
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -1, 43, 1
            DO I = -1, 93, 1
              DXV(I, J, BI, BJ) = ((DXG(I, J, BI, BJ) + DXG(I + (-1), J
     > , BI, BJ)) * 5.0D-01)
              DYU(I, J, BI, BJ) = ((DYG(I, J, BI, BJ) + DYG(I, J + (-1)
     > , BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LAT = (YGLOC(I, J) + YGLOC(I + 1, J)) * 5.0D-01
              DLON = DELX(MOD(I + MYXGLOBALLO + BI * 90 + 178, 90) + 1)
              DLAT = DELY(MOD(J + MYYGLOBALLO + BJ * 40 + 78, 40) + 1)
              RA(I, J, BI, BJ) = (ABS(SIN((DLAT + LAT) *
     >  1.74532925199432954744D-02) - SIN(LAT *
     >  1.74532925199432954744D-02)) * DLON * RSPHERE * RSPHERE *
     >  1.74532925199432954744D-02)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -1, 93, 1
              RAW(I, J, BI, BJ) = ((RA(I, J, BI, BJ) + RA(I + (-1), J,
     >  BI, BJ)) * 5.0D-01)
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LAT = YC(I, J, BI, BJ)
              DLON = DELX(MOD(I + MYXGLOBALLO + BI * 90 + 178, 90) + 1)
              DLAT = (DELY(MOD(J + MYYGLOBALLO + BJ * 40 + 77, 40) + 1)
     >  + DELY(MOD(J + MYYGLOBALLO + BJ * 40 + 78, 40) + 1)) * 5.0D-01
              RAS(I, J, BI, BJ) = (ABS(SIN(LAT *
     >  1.74532925199432954744D-02) - SIN((LAT - DLAT) *
     >  1.74532925199432954744D-02)) * DLON * RSPHERE * RSPHERE *
     >  1.74532925199432954744D-02)
              IF((ABS(LAT) .GT. 9.0D+01) .OR.(ABS(LAT - DLAT) .GT.
     >  9.0D+01)) THEN
                RAS(I, J, BI, BJ) = 0.0
              ENDIF
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LAT = (YGLOC(I, J) + YGLOC(I, J + 1)) * 5.0D-01
              DLON = (DELX(MOD(I + MYXGLOBALLO + BI * 90 + 177, 90) + 1
     > ) + DELX(MOD(I + MYXGLOBALLO + BI * 90 + 178, 90) + 1)) *
     >  5.0D-01
              DLAT = (DELY(MOD(J + MYYGLOBALLO + BJ * 40 + 77, 40) + 1)
     >  + DELY(MOD(J + MYYGLOBALLO + BJ * 40 + 78, 40) + 1)) * 5.0D-01
              RAZ(I, J, BI, BJ) = (ABS(SIN(LAT *
     >  1.74532925199432954744D-02) - SIN((LAT - DLAT) *
     >  1.74532925199432954744D-02)) * DLON * RSPHERE * RSPHERE *
     >  1.74532925199432954744D-02)
              IF((ABS(LAT) .GT. 9.0D+01) .OR.(ABS(LAT - DLAT) .GT.
     >  9.0D+01)) THEN
                RAZ(I, J, BI, BJ) = 0.0
              ENDIF
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LAT = (YGLOC(I, J) + YGLOC(I, J + 1)) * 5.0D-01
              TANPHIATU(I, J, BI, BJ) = TAN(LAT *
     >  1.74532925199432954744D-02)
              LAT = (YGLOC(I, J) + YGLOC(I + 1, J)) * 5.0D-01
              TANPHIATV(I, J, BI, BJ) = TAN(LAT *
     >  1.74532925199432954744D-02)
              ANGLECOSC(I, J, BI, BJ) = 1.0
              ANGLESINC(I, J, BI, BJ) = 0.0
            END DO
          END DO
          DO J = -2, 43, 1
            JG = J + MYYGLOBALLO + BJ * 40 +(-41)
            JG = MIN(MAX(JG, 1), 40)
            IF(COSPOWER .ne. 0.0D00) THEN
              COSFACU(J, BI, BJ) = (COS(YC(1, J, BI, BJ) *
     >  1.74532925199432954744D-02) ** COSPOWER)
              COSFACV(J, BI, BJ) = (COS((YC(1, J, BI, BJ) - DELY(JG) *
     >  5.0D-01) * 1.74532925199432954744D-02) ** COSPOWER)
              COSFACU(J, BI, BJ) = ABS(COSFACU(J, BI, BJ))
              COSFACV(J, BI, BJ) = ABS(COSFACV(J, BI, BJ))
              SQCOSFACU(J, BI, BJ) = SQRT(COSFACU(J, BI, BJ))
              SQCOSFACV(J, BI, BJ) = SQRT(COSFACV(J, BI, BJ))
            ELSE
              COSFACU(J, BI, BJ) = 1.0
              COSFACV(J, BI, BJ) = 1.0
              SQCOSFACU(J, BI, BJ) = 1.0
              SQCOSFACV(J, BI, BJ) = 1.0
            ENDIF
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_theta(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_xyz_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) LOCALWARNINGS
      CHARACTER(512) MSGBUF
      EXTERNAL plot_field_xyzrl
      EXTERNAL print_error
      EXTERNAL read_fld_xyz_rl
      REAL(w2f__8) TFREEZING
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                THETA(I, J, K, BI, BJ) = TREF(K)
              END DO
            END DO
          END DO
        END DO
      END DO
      IF(HYDROGTHETAFILE .NE. ' ') THEN
        IF(MYTHID .eq. 1) THEN
          CALL read_fld_xyz_rl(HYDROGTHETAFILE, ' ', THETA, (0), MYTHID
     > )
        ENDIF
        CALL exch_xyz_rl(THETA, MYTHID)
      ENDIF
      LOCALWARNINGS = 0
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                IF(MASKC(I, J, K, BI, BJ) .eq. 0.0D00) THEN
                  THETA(I, J, K, BI, BJ) = 0.0
                ENDIF
              END DO
            END DO
            IF(TREF(K) .ne. 0.0D00) THEN
              DO J = 1, 40, 1
                DO I = 1, 90, 1
                  IF((THETA(I, J, K, BI, BJ) .eq. 0.0D00) .AND.(MASKC(I
     > , J, K, BI, BJ) .ne. 0.0D00)) THEN
                    LOCALWARNINGS = LOCALWARNINGS + 1
                  ENDIF
                END DO
              END DO
            ENDIF
          END DO
        END DO
      END DO
      IF(LOCALWARNINGS .ne. 0) THEN
        WRITE(MSGBUF, '(A,A)')
     >  'S/R INI_THETA: theta = 0 identically. If this is' //
     >  ' intentional',
     >  'you will need to edit ini_theta.F to avoid this ' //
     >  'safety check'
        CALL print_error(MSGBUF, MYTHID)
        STOP 'ABNORMAL END: S/R INI_THETA'
        RETURN
      ENDIF
      TFREEZING = -1.89999999999999991118D00
      IF(ALLOWFREEZING) THEN
        doloop_ub3 = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
          doloop_ub4 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub4, 1
            DO K = 1, 15, 1
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  IF(THETA(I, J, K, BI, BJ) .LT. TFREEZING) THEN
                    THETA(I, J, K, BI, BJ) = TFREEZING
                  ENDIF
                END DO
              END DO
            END DO
          END DO
        END DO
      ENDIF
      CALL plot_field_xyzrl(THETA, 'Initial Temperature', (15), (1),
     >  MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_dynvars(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                UVEL(I, J, K, BI, BJ) = 0.0D00
                VVEL(I, J, K, BI, BJ) = 0.0D00
                WVEL(I, J, K, BI, BJ) = 0.0D00
                THETA(I, J, K, BI, BJ) = 0.0D00
                SALT(I, J, K, BI, BJ) = 0.0D00
                GU(I, J, K, BI, BJ) = 0.0D00
                GV(I, J, K, BI, BJ) = 0.0D00
                GT(I, J, K, BI, BJ) = 0.0D00
                GS(I, J, K, BI, BJ) = 0.0D00
                GUNM1(I, J, K, BI, BJ) = 0.0D00
                GVNM1(I, J, K, BI, BJ) = 0.0D00
                GTNM1(I, J, K, BI, BJ) = 0.0D00
                GSNM1(I, J, K, BI, BJ) = 0.0D00
                TOTPHIHYD(I, J, K, BI, BJ) = 0.0D00
                IVDCONVCOUNT(I, J, K, BI, BJ) = 0.0D00
              END DO
            END DO
          END DO
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ETAN(I, J, BI, BJ) = 0.0D00
              ETAH(I, J, BI, BJ) = 0.0D00
              PHIHYDLOW(I, J, BI, BJ) = 0.0D00
            END DO
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_vel(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL exch_uv_xyz_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      EXTERNAL read_fld_xyz_rl
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                UVEL(I, J, K, BI, BJ) = 0.0D00
                VVEL(I, J, K, BI, BJ) = 0.0D00
              END DO
            END DO
          END DO
        END DO
      END DO
      IF(UVELINITFILE .NE. ' ') THEN
        IF(MYTHID .eq. 1) THEN
          CALL read_fld_xyz_rl(UVELINITFILE, ' ', UVEL, (0), MYTHID)
        ENDIF
      ENDIF
      IF(VVELINITFILE .NE. ' ') THEN
        IF(MYTHID .eq. 1) THEN
          CALL read_fld_xyz_rl(VVELINITFILE, ' ', VVEL, (0), MYTHID)
        ENDIF
      ENDIF
      CALL exch_uv_xyz_rl(UVEL, VVEL, (.TRUE.), MYTHID)
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                UVEL(I, J, K, BI, BJ) = (UVEL(I, J, K, BI, BJ) * MASKW(
     > I, J, K, BI, BJ))
                VVEL(I, J, K, BI, BJ) = (VVEL(I, J, K, BI, BJ) * MASKS(
     > I, J, K, BI, BJ))
              END DO
            END DO
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE ini_vertical_grid(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) K
      CHARACTER(512) MSGBUF
      EXTERNAL print_error
C
C     **** Statements ****
C
      IF(SETCENTERDR) THEN
        DO K = 1, 16, 1
          IF(DELRC(K) .LE. 0.0D00) THEN
            WRITE(MSGBUF, '(A,I4,A,E16.8)')
     >  'S/R INI_VERTICAL_GRID: delRc(K=', K, ' )=', DELRC(K)
            CALL print_error(MSGBUF, (1))
            WRITE(MSGBUF, '(A)')
     >  'S/R INI_VERTICAL_GRID: Vert. grid spacing MUST B' // 'E > 0'
            CALL print_error(MSGBUF, (1))
            STOP 'ABNORMAL END: S/R INI_VERTICAL_GRID'
            RETURN
          ENDIF
        END DO
        RF(1) = RO_SEALEVEL
        RC(1) = (RF(1) + DELRC(1) * RKSIGN)
        DRC(1) = DELRC(1)
        DRF(1) = DELRC(1)
        DO K = 2, 15, 1
          DRC(K) = DELRC(K)
          DRF(K + (-1)) = (DRF(K + (-1)) + DELRC(K) * 5.0D-01)
          DRF(K) = (DELRC(K) * 5.0D-01)
          RC(K) = (RC(K + (-1)) + DRC(K) * RKSIGN)
          RF(K) = (RF(K + (-1)) + DRF(K + (-1)) * RKSIGN)
        END DO
        DRF(15) = (DELRC(16) + DRF(15))
        RF(16) = (RF(15) + DRF(15) * RKSIGN)
      ELSE
        DO K = 1, 15, 1
          IF(DELR(K) .LE. 0.0D00) THEN
            WRITE(MSGBUF, '(A,I4,A,E16.8)')
     >  'S/R INI_VERTICAL_GRID: delR(K=', K, ' )=', DELR(K)
            CALL print_error(MSGBUF, (1))
            WRITE(MSGBUF, '(A)')
     >  'S/R INI_VERTICAL_GRID: Vert. grid spacing MUST B' // 'E > 0'
            CALL print_error(MSGBUF, (1))
            STOP 'ABNORMAL END: S/R INI_VERTICAL_GRID'
            RETURN
          ENDIF
        END DO
        RF(1) = RO_SEALEVEL
        DO K = 1, 15, 1
          DRF(K) = DELR(K)
          RF(K + 1) = (RF(K) + DELR(K) * RKSIGN)
        END DO
        DRC(1) = (DELR(1) * 5.0D-01)
        RC(1) = (RF(1) + DELR(1) * RKSIGN * 5.0D-01)
        DO K = 2, 15, 1
          DRC(K) = ((DELR(K) + DELR(K + (-1))) * 5.0D-01)
          RC(K) = (RC(K + (-1)) + DRC(K) * RKSIGN)
        END DO
      ENDIF
      DO K = 1, 15, 1
        SAFAC(K) = 1.0D00
        RECIP_DRC(K) = 1D00 / (DRC(K))
        RECIP_DRF(K) = 1D00 / (DRF(K))
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE initialise_varia(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL barrier
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL convective_adjustment_ini
      EXTERNAL debug_call
      EXTERNAL debug_enter
      EXTERNAL debug_leave
      EXTERNAL exch_xyz_rl
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      EXTERNAL ini_autodiff
      EXTERNAL ini_cg2d
      EXTERNAL ini_cori
      EXTERNAL ini_dynvars
      EXTERNAL ini_fields
      EXTERNAL ini_linear_phisurf
      EXTERNAL ini_mixing
      EXTERNAL integr_continuity
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      EXTERNAL packages_init_variables
      EXTERNAL state_summary
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      IF(DEBUGMODE) THEN
        CALL debug_enter('INITIALISE_VARIA', MYTHID)
      ENDIF
      NITER0 = NINT((STARTTIME - BASETIME) / DELTATCLOCK)
      IF(DEBUGMODE) THEN
        CALL debug_call('INI_LINEAR_PHISURF', MYTHID)
      ENDIF
      CALL ini_linear_phisurf(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('INI_CORI', MYTHID)
      ENDIF
      CALL ini_cori(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('INI_CG2D', MYTHID)
      ENDIF
      CALL ini_cg2d(MYTHID)
      CALL barrier(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('INI_MIXING', MYTHID)
      ENDIF
      CALL ini_mixing(MYTHID)
      CALL barrier(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('INI_DYNVARS', MYTHID)
      ENDIF
      CALL ini_dynvars(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('INI_FIELDS', MYTHID)
      ENDIF
      CALL ini_fields(MYTHID)
      CALL barrier(MYTHID)
      CALL ini_autodiff(MYTHID)
      CALL barrier(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('PACKAGES_INIT_VARIABLES', MYTHID)
      ENDIF
      CALL packages_init_variables(MYTHID)
      IF((BASETIME .eq. STARTTIME) .AND.(CADJFREQ .ne. 0.0D00)) THEN
        IF(DEBUGMODE) THEN
          CALL debug_call('CONVECTIVE_ADJUSTMENT_INI', MYTHID)
        ENDIF
        doloop_ub = MYBYHI(MYTHID)
        DO BJ = MYBYLO(MYTHID), doloop_ub, 1
          doloop_ub0 = MYBXHI(MYTHID)
          DO BI = MYBXLO(MYTHID), doloop_ub0, 1
            IMIN = -2
            IMAX = 93
            JMIN = -2
            JMAX = 43
            CALL convective_adjustment_ini((BI), (BJ), IMIN, IMAX, JMIN
     > , JMAX, STARTTIME, NITER0, MYTHID)
          END DO
        END DO
        CALL barrier(MYTHID)
      ENDIF
      IF(DEBUGMODE) THEN
        CALL debug_call('INTEGR_CONTINUITY', MYTHID)
      ENDIF
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          CALL integr_continuity((BI), (BJ), UVEL, VVEL, STARTTIME,
     >  NITER0, MYTHID)
        END DO
      END DO
      CALL exch_xyz_rl(WVEL, MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('STATE_SUMMARY', MYTHID)
      ENDIF
      CALL state_summary(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_leave('INITIALISE_VARIA', MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE integrate_for_w(BI, BJ, K, UFLD, VFLD, WFLD, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) WFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
C
C     **** Statements ****
C
      DO J = 1, 41, 1
        DO I = 1, 91, 1
          UTRANS(I, J) = (HFACW(I, J, K, BI, BJ) * DRF(K) * DYG(I, J,
     >  BI, BJ) * UFLD(I, J, K, BI, BJ))
          VTRANS(I, J) = (HFACS(I, J, K, BI, BJ) * DRF(K) * DXG(I, J,
     >  BI, BJ) * VFLD(I, J, K, BI, BJ))
        END DO
      END DO
      IF(RIGIDLID) THEN
        IF(K .eq. 1) THEN
          DO J = 1, 40, 1
            DO I = 1, 90, 1
              WFLD(I, J, K, BI, BJ) = 0.0
            END DO
          END DO
        ELSE
          IF(K .eq. 15) THEN
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                WFLD(I, J, K, BI, BJ) = (-(MASKC(I, J, K + (-1), BI, BJ
     > ) * MASKC(I, J, K, BI, BJ) * RECIP_RA(I, J, BI, BJ) *(VTRANS(I,
     >  J + 1) + UTRANS(I + 1, J) - UTRANS(I, J) - VTRANS(I, J))))
              END DO
            END DO
          ELSE
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                WFLD(I, J, K, BI, BJ) = (MASKC(I, J, K + (-1), BI, BJ)
     >  * MASKC(I, J, K, BI, BJ) *(WFLD(I, J, K + 1, BI, BJ) - RECIP_RA
     > (I, J, BI, BJ) *(VTRANS(I, J + 1) + UTRANS(I + 1, J) - UTRANS(I,
     >  J) - VTRANS(I, J))))
              END DO
            END DO
          ENDIF
        ENDIF
      ELSE
        IF(K .eq. 15) THEN
          DO J = 1, 40, 1
            DO I = 1, 90, 1
              WFLD(I, J, K, BI, BJ) = (-(MASKC(I, J, K, BI, BJ) *
     >  RECIP_RA(I, J, BI, BJ) *(VTRANS(I, J + 1) + UTRANS(I + 1, J) -
     >  UTRANS(I, J) - VTRANS(I, J))))
            END DO
          END DO
        ELSE
          DO J = 1, 40, 1
            DO I = 1, 90, 1
              WFLD(I, J, K, BI, BJ) = (MASKC(I, J, K, BI, BJ) *(WFLD(I,
     >  J, K + 1, BI, BJ) - RECIP_RA(I, J, BI, BJ) *(VTRANS(I, J + 1) +
     >  UTRANS(I + 1, J) - UTRANS(I, J) - VTRANS(I, J))))
            END DO
          END DO
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE integr_continuity(BI, BJ, UFLD, VFLD, MYTIME, MYITER,
     >  MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use surface_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      REAL(w2f__8) UFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) VFLD(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL integrate_for_w
      INTEGER(w2f__i4) K
C
C     **** Statements ****
C
      DO K = 15, 1, (-1)
        CALL integrate_for_w(BI, BJ, (K), UFLD, VFLD, WVEL, MYTHID)
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE load_grid_spacing(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL barrier
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) ILEN
      EXTERNAL ilnblnk
      INTEGER(w2f__i4) ilnblnk
      INTEGER(w2f__i4) IUNIT
      INTEGER(w2f__i4) J
      EXTERNAL mdsfindunit
      CHARACTER(512) MSGBUF
      EXTERNAL print_message
      REAL(w2f__4) TMP4DELX(1 : 90)
      REAL(w2f__4) TMP4DELY(1 : 40)
      REAL(w2f__8) TMP8DELX(1 : 90)
      REAL(w2f__8) TMP8DELY(1 : 40)
      CHARACTER(4) t__793
      CHARACTER(4) t__794
      CHARACTER(4) t__795
      CHARACTER(4) t__796
C
C     **** Statements ****
C
      IF(DELXFILE .NE. ' ') THEN
        IF(MYTHID .eq. 1) THEN
          CALL mdsfindunit(IUNIT, MYTHID)
          ILEN = ilnblnk(DELXFILE)
          IF(READBINARYPREC .eq. 32) THEN
C           OPEN(iUnit, FILE=delXFile(1:iLen), STATUS='OLD',        FORM='UNFORMATTED',ACCESS='DIRECT',RECL=4*Nx)
            t__793 = 'OLD '
            OPEN(UNIT = IUNIT, RECL = 360, FORM = 'UNFORMATTED', ACCESS
     >  = 'DIRECT', STATUS = t__793(1_w2f__i8 : 3), FILE = DELXFILE(
     > 1_w2f__i8 : MAX(ILEN, 0)))
            READ(IUNIT, REC = 1) TMP4DELX
C           CLOSE(iUnit)
            CLOSE(UNIT = IUNIT)
            DO I = 1, 90, 1
              DELX(I) = TMP4DELX(I)
            END DO
          ELSE
            IF(READBINARYPREC .eq. 64) THEN
C             OPEN(iUnit, FILE=delXFile(1:iLen), STATUS='OLD',        FORM='UNFORMATTED',ACCESS='DIRECT',RECL=4*2*Nx)
              t__794 = 'OLD '
              OPEN(UNIT = IUNIT, RECL = 720, FORM = 'UNFORMATTED',
     >  ACCESS = 'DIRECT', STATUS = t__794(1_w2f__i8 : 3), FILE =
     >  DELXFILE(1_w2f__i8 : MAX(ILEN, 0)))
              READ(IUNIT, REC = 1) TMP8DELX
C             CLOSE(iUnit)
              CLOSE(UNIT = IUNIT)
              DO I = 1, 90, 1
                DELX(I) = TMP8DELX(I)
              END DO
            ENDIF
          ENDIF
          WRITE(MSGBUF, '(3A)') 'S/R LOAD_GRID_SPACING:',
     >  ' delX loaded from file: ', DELXFILE(1_w2f__i8 : MAX(ILEN, 0))
          CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', MYTHID)
        ENDIF
      ENDIF
      IF(DELYFILE .NE. ' ') THEN
        IF(MYTHID .eq. 1) THEN
          CALL mdsfindunit(IUNIT, MYTHID)
          ILEN = ilnblnk(DELYFILE)
          IF(READBINARYPREC .eq. 32) THEN
C           OPEN(iUnit, FILE=delYFile(1:iLen), STATUS='OLD',        FORM='UNFORMATTED',ACCESS='DIRECT',RECL=4*Ny)
            t__795 = 'OLD '
            OPEN(UNIT = IUNIT, RECL = 160, FORM = 'UNFORMATTED', ACCESS
     >  = 'DIRECT', STATUS = t__795(1_w2f__i8 : 3), FILE = DELYFILE(
     > 1_w2f__i8 : MAX(ILEN, 0)))
            READ(IUNIT, REC = 1) TMP4DELY
C           CLOSE(iUnit)
            CLOSE(UNIT = IUNIT)
            DO J = 1, 40, 1
              DELY(J) = TMP4DELY(J)
            END DO
          ELSE
            IF(READBINARYPREC .eq. 64) THEN
C             OPEN(iUnit, FILE=delYFile(1:iLen), STATUS='OLD',        FORM='UNFORMATTED',ACCESS='DIRECT',RECL=4*2*Ny)
              t__796 = 'OLD '
              OPEN(UNIT = IUNIT, RECL = 320, FORM = 'UNFORMATTED',
     >  ACCESS = 'DIRECT', STATUS = t__796(1_w2f__i8 : 3), FILE =
     >  DELYFILE(1_w2f__i8 : MAX(ILEN, 0)))
              READ(IUNIT, REC = 1) TMP8DELY
C             CLOSE(iUnit)
              CLOSE(UNIT = IUNIT)
              DO J = 1, 40, 1
                DELY(J) = TMP8DELY(J)
              END DO
            ENDIF
          ENDIF
          WRITE(MSGBUF, '(3A)') 'S/R LOAD_GRID_SPACING:',
     >  ' delY loaded from file: ', DELYFILE(1_w2f__i8 : MAX(ILEN, 0))
          CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', MYTHID)
        ENDIF
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE modeldata_example(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      CHARACTER(512) MSGBUF
      EXTERNAL print_message
C
C     **** Statements ****
C
      WRITE(MSGBUF, '(A)') '// Shown below is an example "data" file.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '// To use this example copy and paste the  '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '// ">" lines. Then remove the text up to'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '// and including the ">".'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># Example "data" file'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># Lines beginning "#" are comments'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># o Continuous equation parameters'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   gravity - Accel due to gravity (m.s^2)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   rhonil  - Reference density (kg/m^3)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   tAlpha  - Thermal expansion coefficient (1/' // 'oC)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   sBeta   - Haline contraction coefficient (1' // '/ppt)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   f0      - Reference coriolis parameter ( 1/' // 's ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#             ( South edge f on beta plane.)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   beta    - df/dy ( s^-1.m^-1 ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   viscAh  - Horizontal eddy viscosity coeffic' // 'ient '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^2/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   viscAz  - Vertical eddy viscosity coefficie' // 'nt '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^2/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   viscA4  - Biharmonic eddy viscosity coeffic' // 'ient '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^4/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   diffKhT - Horizontal temperature diffusivit' // 'y '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^2/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   diffKzT - Vertical temperature diffusivity '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^2/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   diffK4T - Biharmonic temperature diffusivit' // 'y '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^4/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   diffKhS - Horizontal salt diffusivity '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^2/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   diffKzS - Vertical salt diffusivity '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^2/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   diffK4S - Biharmonic salt diffusivity '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#             ( m^4/s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   momStepping - On/Off flag for momentum'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                  equation.          '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   momViscosity - On/Off flag for momentum'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#                  mixing.                 '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   momAdvection - On/Off flag for momentum'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#                  self transport.         '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   momPressureForcing - On/Off flag for moment' // 'um'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#                        pressure terms.       ' // '  '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   useCoriolis  - On/Off flag for momentum'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#                  equation coriolis term. '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   tempStepping - On/Off flag for temperature'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                  eqaution.         '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   tempDiffusion- On/Off flag for temperature'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#                  mixing.                 '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   tempAdvection- On/Off flag for temperature'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                  transport.         '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   tempForcing  - On/Off flag for temperature'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                  forcing.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   saltDiffusion- On/Off flag for salt'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#                  mixing.                 '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   saltAdvection- On/Off flag for salt'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                  transport.         '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   saltForcing  - On/Off flag for salt'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                  forcing.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   tRef         - Reference vertical pot. temp'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   sRef         - Reference vertical salinity'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>&PARM01'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> gravity=9.81,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> rhonil=999.8,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> tAlpha=2.e-4,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> sBeta=7e-4'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> f0=1.e-4'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> viscAh=1.e3'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> viscAz=1.e-5'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> viscA4=0.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> diffKhT=1.e3'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> diffKzT=1.e-5'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> diffK4T=0.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> diffKhS=1.e3'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> diffKzS=1.e-5'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> diffK4S=0.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> momStepping=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> momViscosity=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> momAdvection=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> momPressureForcing=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> momForcing=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> useCoriolis=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> tempStepping=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> tempDiffusion=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> tempAdvection=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> tempForcing=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> saltDiffusion=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> saltAdvection=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> saltForcing=.TRUE.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> tRef=20.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> sRef=35.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> implicitFreeSurface=.TRUE.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> rigidLid=.FALSE.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> GMmaxSlope=1.d-2,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> GMlength=200.d3,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> GMalpha=200.d3,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> GMdepth=1000.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> GMkBackground=0.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>/                     '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># o Elliptic solver parameters'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   cg2dMaxIters - Maximum number of 2d '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                  solver iterations.   '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   cg2dChkReqFreq - Frequency solver tests '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                    convergence.       '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   cg2dTargetResidual - Solver target'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#                        residual.    '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>&PARM02'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> cg2dMaxIters=200,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> cg2dChkResFreq=5,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> cg2dTargetResidual=1.e-7,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>/                     '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># o Timestepping parameters'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   nIter0 - Start timestep index'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   nTimeSteps - Number of timesteps in run.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   delT - Timestep ( s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   deltaTtracer - Tracer timestep ( s ).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   abEps - Adams-Bashforth stabilising '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#           factor.                     '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   tauCD - CD scheme coupling timescale (s)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   startTime - Integration starting time (s)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   endTime - Integration ending time (s)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   cAdjFreq - Convective adjustment period (s)'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   chkPtFreq - Frequency at which check  '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#               pointing is done ( s ).   '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   dumpFreq - Frequency at which model  '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#              state is stored ( s ).     '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>&PARM03'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> nIter0=0'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> nTimeSteps=5000'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> delT=3600.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> deltaTtracer=3600.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> abEps=0.1'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> tauCD=345600.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> startTime=0.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> endTime=31104000.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> chkPtFreq=864000.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> dumpFreq=2592000.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> cAdjFreq=86400.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>/                     '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># o Gridding parameters'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   l - Global domain grid-points in X'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   m - Global domain grid-points in Y'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   n - Grid-points in Z'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   usingSphericalPolarGrid - On/Off flag for'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#       selecting spherical polar coordinates'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   usingCartesianGrid - On/Off flag for'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#        selecting cartesian coordinates'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   delX - Zonal grid spacing. Degrees'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#          for spherical polar and m for'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#          cartesian. A value for each point'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#          in X can be specified.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#   delY - Meridional grid spacing. Degrees'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#          for spherical polar and m for'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)')
     >  '>#          cartesian. A value for each point'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#          in Y can be specified.'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   delZ - Vertical grid spacing (m).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   delP - Vertical grid spacing (Pa).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   phiMin - Southern boundary latitude'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#            (spherical polar grid).   '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#   rSphere- Radius of globe           '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>#            (spherical polar grid).   '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>&PARM04'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> n=20,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> l=122,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> m=86,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> usingSphericalPolarGrid=.TRUE.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> usingCartesianGrid=.FALSE.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> delx=1.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> dely=1.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> delz=  100.,  100.,  100.,  100.,  100.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>        100.,  100.,  100.,  100.,  100.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>        100.,  100.,  100.,  100.,  100.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>        100.,  100.,  100.,  100.,  100.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> phiMin=-80.,'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '> rSphere=6430.E3'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '>/                     '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># Note: Some systems use & as the '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># namelist terminator. Other systems'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') '># use a / character (as shown here).'
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      WRITE(MSGBUF, '(A)') ' '
      CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE momentum_correction_step(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL calc_grad_phi_surf
      EXTERNAL correction_step
      EXTERNAL exch_xy_rl
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      EXTERNAL integr_continuity
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) K
      REAL(w2f__8) PHISURFX(-2 : 93, -2 : 43)
      REAL(w2f__8) PHISURFY(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              PHISURFX(I, J) = 0.0
              PHISURFY(I, J) = 0.0
            END DO
          END DO
          IMIN = -1
          IMAX = 93
          JMIN = -1
          JMAX = 43
          CALL calc_grad_phi_surf((BI), (BJ), IMIN, IMAX, JMIN, JMAX,
     >  ETAN, PHISURFX, PHISURFY, MYTHID)
          DO K = 1, 15, 1
            IF(MOMSTEPPING) THEN
              CALL correction_step((BI), (BJ), IMIN, IMAX, JMIN, JMAX,
     >  (K), PHISURFX, PHISURFY, MYTIME, MYTHID)
            ENDIF
          END DO
        END DO
      END DO
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          CALL integr_continuity((BI), (BJ), UVEL, VVEL, MYTIME, MYITER
     > , MYTHID)
        END DO
      END DO
      IF(EXACTCONSERV .AND.(IMPLICDIV2DFLOW .ne. 0.0D00)) THEN
        CALL exch_xy_rl(ETAN, MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE packages_init_variables(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use tamc_mod
      use tamc_keys_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL barrier
      EXTERNAL cd_code_ini_vars
      EXTERNAL cost_init_varia
      EXTERNAL ctrl_init_variables
      EXTERNAL ctrl_map_ini
      EXTERNAL debug_call
      EXTERNAL debug_enter
      EXTERNAL debug_leave
      EXTERNAL ini_forcing
C
C     **** Statements ****
C
      IF(DEBUGMODE) THEN
        CALL debug_enter('PACKAGES_INIT_VARIABLES', MYTHID)
      ENDIF
      IF(DEBUGMODE) THEN
        CALL debug_call('CD_CODE_INI', MYTHID)
      ENDIF
      IF(USECDSCHEME) THEN
        CALL cd_code_ini_vars(MYTHID)
      ENDIF
      CALL ctrl_init_variables(MYTHID)
      CALL ctrl_map_ini(MYTHID)
      CALL barrier(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('INI_FORCING', MYTHID)
      ENDIF
      CALL ini_forcing(MYTHID)
      CALL cost_init_varia(MYTHID)
      CALL barrier(MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_leave('PACKAGES_INIT_VARIABLES', MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE plot_field_xyrs(FLD, FLDNAM, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) FLD(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      CHARACTER(*) FLDNAM
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__809
      EXTERNAL barrier
      INTEGER(w2f__i4) BIEND
      INTEGER(w2f__i4) BISTART
      INTEGER(w2f__i4) BISTRIDE
      INTEGER(w2f__i4) BJEND
      INTEGER(w2f__i4) BJSTART
      INTEGER(w2f__i4) BJSTRIDE
      CHARACTER(512) FLDTITLE
      INTEGER(w2f__i4) IEND
      INTEGER(w2f__i4) ISTART
      INTEGER(w2f__i4) ISTRIDE
      INTEGER(w2f__i4) JEND
      INTEGER(w2f__i4) JSTART
      INTEGER(w2f__i4) JSTRIDE
      INTEGER(w2f__i4) KEND
      INTEGER(w2f__i4) KSTART
      INTEGER(w2f__i4) KSTRIDE
      EXTERNAL print_maprs
C
C     **** Statements ****
C
      t__809 = LEN(FLDNAM)
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        IF(MYITER .GE. 0) THEN
          WRITE(FLDTITLE, '(A,A,A,I10)') '// Field ', FLDNAM(1_w2f__i8
     >  : MAX(t__809, 0_w2f__i8)), ' at iteration ', MYITER
        ELSE
          WRITE(FLDTITLE, '(A,A)') '// Field ', FLDNAM(1_w2f__i8 : MAX(
     > t__809, 0_w2f__i8))
        ENDIF
        ISTART = -2
        IEND = 93
        ISTRIDE = 1
        JSTART = 43
        JEND = -2
        JSTRIDE = -1
        KSTART = 1
        KEND = 1
        KSTRIDE = 1
        BISTART = 1
        BIEND = 1
        BISTRIDE = 1
        BJSTART = 1
        BJEND = 1
        BJSTRIDE = -1
        CALL print_maprs(FLD, FLDTITLE, 'XY', (-2), (93), (-2), (43), (
     > 1), (1), (1), (1), ISTART, IEND, ISTRIDE, JSTART, JEND, JSTRIDE,
     >  KSTART, KEND, KSTRIDE, BISTART, BIEND, BISTRIDE, BJSTART, BJEND
     > , BJSTRIDE)
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE plot_field_xyrl(FLD, FLDNAM, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) FLD(-2 : 93, -2 : 43, 1 : 1, 1 : 1)
      CHARACTER(*) FLDNAM
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__817
      EXTERNAL barrier
      INTEGER(w2f__i4) BIEND
      INTEGER(w2f__i4) BISTART
      INTEGER(w2f__i4) BISTRIDE
      INTEGER(w2f__i4) BJEND
      INTEGER(w2f__i4) BJSTART
      INTEGER(w2f__i4) BJSTRIDE
      CHARACTER(512) FLDTITLE
      INTEGER(w2f__i4) IEND
      INTEGER(w2f__i4) ISTART
      INTEGER(w2f__i4) ISTRIDE
      INTEGER(w2f__i4) JEND
      INTEGER(w2f__i4) JSTART
      INTEGER(w2f__i4) JSTRIDE
      INTEGER(w2f__i4) KEND
      INTEGER(w2f__i4) KSTART
      INTEGER(w2f__i4) KSTRIDE
      EXTERNAL print_maprl
C
C     **** Statements ****
C
      t__817 = LEN(FLDNAM)
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        IF(MYITER .GE. 0) THEN
          WRITE(FLDTITLE, '(A,A,A,I10)') '// Field ', FLDNAM(1_w2f__i8
     >  : MAX(t__817, 0_w2f__i8)), ' at iteration ', MYITER
        ELSE
          WRITE(FLDTITLE, '(A,A)') '// Field ', FLDNAM(1_w2f__i8 : MAX(
     > t__817, 0_w2f__i8))
        ENDIF
        ISTART = -2
        IEND = 93
        ISTRIDE = 1
        JSTART = 43
        JEND = -2
        JSTRIDE = -1
        KSTART = 1
        KEND = 1
        KSTRIDE = 1
        BISTART = 1
        BIEND = 1
        BISTRIDE = 1
        BJSTART = 1
        BJEND = 1
        BJSTRIDE = -1
        CALL print_maprl(FLD, FLDTITLE, 'XY', (-2), (93), (-2), (43), (
     > 1), (1), (1), (1), ISTART, IEND, ISTRIDE, JSTART, JEND, JSTRIDE,
     >  KSTART, KEND, KSTRIDE, BISTART, BIEND, BISTRIDE, BJSTART, BJEND
     > , BJSTRIDE)
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE plot_field_xyzrs(FLD, FLDNAM, FLDNZ, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(*) FLDNAM
      INTEGER(w2f__i4) FLDNZ
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) FLD(-2 : 93, -2 : 43, 1 : FLDNZ, 1 : 1, 1 : 1)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__822
      INTEGER(w2f__i8) t__826
      INTEGER(w2f__i8) t__830
      EXTERNAL barrier
      INTEGER(w2f__i4) BIEND
      INTEGER(w2f__i4) BISTART
      INTEGER(w2f__i4) BISTRIDE
      INTEGER(w2f__i4) BJEND
      INTEGER(w2f__i4) BJSTART
      INTEGER(w2f__i4) BJSTRIDE
      CHARACTER(512) FLDTITLE
      INTEGER(w2f__i4) IEND
      INTEGER(w2f__i4) ISTART
      INTEGER(w2f__i4) ISTRIDE
      INTEGER(w2f__i4) JEND
      INTEGER(w2f__i4) JSTART
      INTEGER(w2f__i4) JSTRIDE
      INTEGER(w2f__i4) KEND
      INTEGER(w2f__i4) KSTART
      INTEGER(w2f__i4) KSTRIDE
      EXTERNAL print_maprs
      INTEGER(w2f__i8) t__827
      INTEGER(w2f__i8) t__828
      INTEGER(w2f__i8) t__829
C
C     **** Statements ****
C
      t__822 = FLDNZ
      t__826 = MAX(t__822, 0_w2f__i8)
      t__827 = t__826 * 8832_w2f__i8
      t__828 = t__827
      t__829 = t__826 * 4416_w2f__i8
      t__830 = LEN(FLDNAM)
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        IF(MYITER .GE. 0) THEN
          WRITE(FLDTITLE, '(A,A,A,I10)') '// Field ', FLDNAM(1_w2f__i8
     >  : MAX(t__830, 0_w2f__i8)), ' at iteration ', MYITER
        ELSE
          WRITE(FLDTITLE, '(A,A)') '// Field ', FLDNAM(1_w2f__i8 : MAX(
     > t__830, 0_w2f__i8))
        ENDIF
        ISTART = -2
        IEND = 93
        ISTRIDE = 1
        JSTART = 43
        JEND = -2
        JSTRIDE = -1
        KSTART = 1
        KEND = 1
        KSTRIDE = 1
        BISTART = 1
        BIEND = 1
        BISTRIDE = 1
        BJSTART = 1
        BJEND = 1
        BJSTRIDE = -1
        CALL print_maprs(FLD, FLDTITLE, 'XY', (-2), (93), (-2), (43), (
     > 1), FLDNZ, (1), (1), ISTART, IEND, ISTRIDE, JSTART, JEND,
     >  JSTRIDE, KSTART, KEND, KSTRIDE, BISTART, BIEND, BISTRIDE,
     >  BJSTART, BJEND, BJSTRIDE)
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE plot_field_xyzrl(FLD, FLDNAM, FLDNZ, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(*) FLDNAM
      INTEGER(w2f__i4) FLDNZ
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) FLD(-2 : 93, -2 : 43, 1 : FLDNZ, 1 : 1, 1 : 1)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__835
      INTEGER(w2f__i8) t__839
      INTEGER(w2f__i8) t__843
      EXTERNAL barrier
      INTEGER(w2f__i4) BIEND
      INTEGER(w2f__i4) BISTART
      INTEGER(w2f__i4) BISTRIDE
      INTEGER(w2f__i4) BJEND
      INTEGER(w2f__i4) BJSTART
      INTEGER(w2f__i4) BJSTRIDE
      CHARACTER(512) FLDTITLE
      INTEGER(w2f__i4) IEND
      INTEGER(w2f__i4) ISTART
      INTEGER(w2f__i4) ISTRIDE
      INTEGER(w2f__i4) JEND
      INTEGER(w2f__i4) JSTART
      INTEGER(w2f__i4) JSTRIDE
      INTEGER(w2f__i4) KEND
      INTEGER(w2f__i4) KSTART
      INTEGER(w2f__i4) KSTRIDE
      EXTERNAL print_maprl
      INTEGER(w2f__i8) t__840
      INTEGER(w2f__i8) t__841
      INTEGER(w2f__i8) t__842
C
C     **** Statements ****
C
      t__835 = FLDNZ
      t__839 = MAX(t__835, 0_w2f__i8)
      t__840 = t__839 * 8832_w2f__i8
      t__841 = t__840
      t__842 = t__839 * 4416_w2f__i8
      t__843 = LEN(FLDNAM)
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        IF(MYITER .GE. 0) THEN
          WRITE(FLDTITLE, '(A,A,A,I10)') '// Field ', FLDNAM(1_w2f__i8
     >  : MAX(t__843, 0_w2f__i8)), ' at iteration ', MYITER
        ELSE
          WRITE(FLDTITLE, '(A,A)') '// Field ', FLDNAM(1_w2f__i8 : MAX(
     > t__843, 0_w2f__i8))
        ENDIF
        ISTART = -2
        IEND = 93
        ISTART = 1
        IEND = 90
        ISTRIDE = 1
        JSTART = 43
        JEND = -2
        JSTART = 40
        JEND = 1
        JSTRIDE = -1
        KSTART = 1
        KEND = FLDNZ
        KEND = 1
        KSTRIDE = 1
        BISTART = 1
        BIEND = 1
        BISTRIDE = 1
        BJSTART = 1
        BJEND = 1
        BJSTRIDE = -1
        CALL print_maprl(FLD, FLDTITLE, 'XY', (-2), (93), (-2), (43), (
     > 1), FLDNZ, (1), (1), ISTART, IEND, ISTRIDE, JSTART, JEND,
     >  JSTRIDE, KSTART, KEND, KSTRIDE, BISTART, BIEND, BISTRIDE,
     >  BJSTART, BJEND, BJSTRIDE)
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE plot_field_xzrs(FLD, FLDNAM, FLDNZ, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(*) FLDNAM
      INTEGER(w2f__i4) FLDNZ
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) FLD(-2 : 93, 1 : FLDNZ, 1 : 1, 1 : 1)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__846
      INTEGER(w2f__i8) t__850
      INTEGER(w2f__i8) t__854
      EXTERNAL barrier
      INTEGER(w2f__i4) BIEND
      INTEGER(w2f__i4) BISTART
      INTEGER(w2f__i4) BISTRIDE
      INTEGER(w2f__i4) BJEND
      INTEGER(w2f__i4) BJSTART
      INTEGER(w2f__i4) BJSTRIDE
      CHARACTER(512) FLDTITLE
      INTEGER(w2f__i4) IEND
      INTEGER(w2f__i4) ISTART
      INTEGER(w2f__i4) ISTRIDE
      INTEGER(w2f__i4) JEND
      INTEGER(w2f__i4) JSTART
      INTEGER(w2f__i4) JSTRIDE
      INTEGER(w2f__i4) KEND
      INTEGER(w2f__i4) KSTART
      INTEGER(w2f__i4) KSTRIDE
      EXTERNAL print_maprs
      INTEGER(w2f__i8) t__851
      INTEGER(w2f__i8) t__852
      INTEGER(w2f__i8) t__853
C
C     **** Statements ****
C
      t__846 = FLDNZ
      t__850 = MAX(t__846, 0_w2f__i8)
      t__851 = t__850 * 192_w2f__i8
      t__852 = t__851
      t__853 = t__850 * 96_w2f__i8
      t__854 = LEN(FLDNAM)
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        IF(MYITER .GE. 0) THEN
          WRITE(FLDTITLE, '(A,A,A,I10)') '// Field ', FLDNAM(1_w2f__i8
     >  : MAX(t__854, 0_w2f__i8)), ' at iteration ', MYITER
        ELSE
          WRITE(FLDTITLE, '(A,A)') '// Field ', FLDNAM(1_w2f__i8 : MAX(
     > t__854, 0_w2f__i8))
        ENDIF
        ISTART = 1
        IEND = 90
        ISTRIDE = 1
        JSTART = 1
        JEND = 1
        JSTRIDE = 1
        KSTART = 1
        KEND = FLDNZ
        KSTRIDE = 1
        BISTART = 1
        BIEND = 1
        BISTRIDE = 1
        BJSTART = 1
        BJEND = 1
        BJSTRIDE = -1
        CALL print_maprs(FLD, FLDTITLE, 'XZ', (-2), (93), (1), FLDNZ, (
     > 1), (1), (1), (1), ISTART, IEND, ISTRIDE, JSTART, JEND, JSTRIDE,
     >  KSTART, KEND, KSTRIDE, BISTART, BIEND, BISTRIDE, BJSTART, BJEND
     > , BJSTRIDE)
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE plot_field_xzrl(FLD, FLDNAM, FLDNZ, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(*) FLDNAM
      INTEGER(w2f__i4) FLDNZ
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) FLD(-2 : 93, 1 : FLDNZ, 1 : 1, 1 : 1)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__857
      INTEGER(w2f__i8) t__861
      INTEGER(w2f__i8) t__865
      EXTERNAL barrier
      INTEGER(w2f__i4) BIEND
      INTEGER(w2f__i4) BISTART
      INTEGER(w2f__i4) BISTRIDE
      INTEGER(w2f__i4) BJEND
      INTEGER(w2f__i4) BJSTART
      INTEGER(w2f__i4) BJSTRIDE
      CHARACTER(512) FLDTITLE
      INTEGER(w2f__i4) IEND
      INTEGER(w2f__i4) ISTART
      INTEGER(w2f__i4) ISTRIDE
      INTEGER(w2f__i4) JEND
      INTEGER(w2f__i4) JSTART
      INTEGER(w2f__i4) JSTRIDE
      INTEGER(w2f__i4) KEND
      INTEGER(w2f__i4) KSTART
      INTEGER(w2f__i4) KSTRIDE
      EXTERNAL print_maprl
      INTEGER(w2f__i8) t__862
      INTEGER(w2f__i8) t__863
      INTEGER(w2f__i8) t__864
C
C     **** Statements ****
C
      t__857 = FLDNZ
      t__861 = MAX(t__857, 0_w2f__i8)
      t__862 = t__861 * 192_w2f__i8
      t__863 = t__862
      t__864 = t__861 * 96_w2f__i8
      t__865 = LEN(FLDNAM)
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        IF(MYITER .GE. 0) THEN
          WRITE(FLDTITLE, '(A,A,A,I10)') '// Field ', FLDNAM(1_w2f__i8
     >  : MAX(t__865, 0_w2f__i8)), ' at iteration ', MYITER
        ELSE
          WRITE(FLDTITLE, '(A,A)') '// Field ', FLDNAM(1_w2f__i8 : MAX(
     > t__865, 0_w2f__i8))
        ENDIF
        ISTART = 1
        IEND = 90
        ISTRIDE = 1
        JSTART = 1
        JEND = 1
        JSTRIDE = -1
        KSTART = 1
        KEND = FLDNZ
        KSTRIDE = 1
        BISTART = 1
        BIEND = 1
        BISTRIDE = 1
        BJSTART = 1
        BJEND = 1
        BJSTRIDE = -1
        CALL print_maprl(FLD, FLDTITLE, 'XZ', (-2), (93), (1), (1), (1)
     > , FLDNZ, (1), (1), ISTART, IEND, ISTRIDE, JSTART, JEND, JSTRIDE,
     >  KSTART, KEND, KSTRIDE, BISTART, BIEND, BISTRIDE, BJSTART, BJEND
     > , BJSTRIDE)
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE plot_field_yzrs(FLD, FLDNAM, FLDNZ, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(*) FLDNAM
      INTEGER(w2f__i4) FLDNZ
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) FLD(-2 : 43, 1 : FLDNZ, 1 : 1, 1 : 1)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__868
      INTEGER(w2f__i8) t__872
      INTEGER(w2f__i8) t__876
      EXTERNAL barrier
      INTEGER(w2f__i4) BIEND
      INTEGER(w2f__i4) BISTART
      INTEGER(w2f__i4) BISTRIDE
      INTEGER(w2f__i4) BJEND
      INTEGER(w2f__i4) BJSTART
      INTEGER(w2f__i4) BJSTRIDE
      CHARACTER(512) FLDTITLE
      INTEGER(w2f__i4) IEND
      INTEGER(w2f__i4) ISTART
      INTEGER(w2f__i4) ISTRIDE
      INTEGER(w2f__i4) JEND
      INTEGER(w2f__i4) JSTART
      INTEGER(w2f__i4) JSTRIDE
      INTEGER(w2f__i4) KEND
      INTEGER(w2f__i4) KSTART
      INTEGER(w2f__i4) KSTRIDE
      EXTERNAL print_maprs
      INTEGER(w2f__i8) t__873
      INTEGER(w2f__i8) t__874
      INTEGER(w2f__i8) t__875
C
C     **** Statements ****
C
      t__868 = FLDNZ
      t__872 = MAX(t__868, 0_w2f__i8)
      t__873 = t__872 * 92_w2f__i8
      t__874 = t__873
      t__875 = t__872 * 46_w2f__i8
      t__876 = LEN(FLDNAM)
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        IF(MYITER .GE. 0) THEN
          WRITE(FLDTITLE, '(A,A,A,I10)') '// Field ', FLDNAM(1_w2f__i8
     >  : MAX(t__876, 0_w2f__i8)), ' at iteration ', MYITER
        ELSE
          WRITE(FLDTITLE, '(A,A)') '// Field ', FLDNAM(1_w2f__i8 : MAX(
     > t__876, 0_w2f__i8))
        ENDIF
        ISTART = 1
        IEND = 1
        ISTRIDE = 1
        JSTART = 40
        JEND = 1
        JSTRIDE = -1
        KSTART = 1
        KEND = FLDNZ
        KSTRIDE = 1
        BISTART = 1
        BIEND = 1
        BISTRIDE = 1
        BJSTART = 1
        BJEND = 1
        BJSTRIDE = -1
        CALL print_maprs(FLD, FLDTITLE, 'YZ', (1), (1), (-2), (43), (1)
     > , FLDNZ, (1), (1), ISTART, IEND, ISTRIDE, JSTART, JEND, JSTRIDE,
     >  KSTART, KEND, KSTRIDE, BISTART, BIEND, BISTRIDE, BJSTART, BJEND
     > , BJSTRIDE)
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE plot_field_yzrl(FLD, FLDNAM, FLDNZ, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      CHARACTER(*) FLDNAM
      INTEGER(w2f__i4) FLDNZ
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) FLD(-2 : 43, 1 : FLDNZ, 1 : 1, 1 : 1)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__879
      INTEGER(w2f__i8) t__883
      INTEGER(w2f__i8) t__887
      EXTERNAL barrier
      INTEGER(w2f__i4) BIEND
      INTEGER(w2f__i4) BISTART
      INTEGER(w2f__i4) BISTRIDE
      INTEGER(w2f__i4) BJEND
      INTEGER(w2f__i4) BJSTART
      INTEGER(w2f__i4) BJSTRIDE
      CHARACTER(512) FLDTITLE
      INTEGER(w2f__i4) IEND
      INTEGER(w2f__i4) ISTART
      INTEGER(w2f__i4) ISTRIDE
      INTEGER(w2f__i4) JEND
      INTEGER(w2f__i4) JSTART
      INTEGER(w2f__i4) JSTRIDE
      INTEGER(w2f__i4) KEND
      INTEGER(w2f__i4) KSTART
      INTEGER(w2f__i4) KSTRIDE
      EXTERNAL print_maprl
      INTEGER(w2f__i8) t__884
      INTEGER(w2f__i8) t__885
      INTEGER(w2f__i8) t__886
C
C     **** Statements ****
C
      t__879 = FLDNZ
      t__883 = MAX(t__879, 0_w2f__i8)
      t__884 = t__883 * 92_w2f__i8
      t__885 = t__884
      t__886 = t__883 * 46_w2f__i8
      t__887 = LEN(FLDNAM)
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        IF(MYITER .GE. 0) THEN
          WRITE(FLDTITLE, '(A,A,A,I10)') '// Field ', FLDNAM(1_w2f__i8
     >  : MAX(t__887, 0_w2f__i8)), ' at iteration ', MYITER
        ELSE
          WRITE(FLDTITLE, '(A,A)') '// Field ', FLDNAM(1_w2f__i8 : MAX(
     > t__887, 0_w2f__i8))
        ENDIF
        ISTART = 1
        IEND = 1
        ISTRIDE = 1
        JSTART = 40
        JEND = 1
        JSTRIDE = -1
        KSTART = 1
        KEND = FLDNZ
        KSTRIDE = 1
        BISTART = 1
        BIEND = 1
        BISTRIDE = 1
        BJSTART = 1
        BJEND = 1
        BJSTRIDE = -1
        CALL print_maprl(FLD, FLDTITLE, 'YZ', (1), (1), (-2), (43), (1)
     > , FLDNZ, (1), (1), ISTART, IEND, ISTRIDE, JSTART, JEND, JSTRIDE,
     >  KSTART, KEND, KSTRIDE, BISTART, BIEND, BISTRIDE, BJSTART, BJEND
     > , BJSTRIDE)
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE pressure_for_eos(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  LOCPRES, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) LOCPRES(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Statements ****
C
      IF(USINGZCOORDS) THEN
        IF(USEDYNP_INEOS_ZC) THEN
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LOCPRES(I, J) = (MASKC(I, J, K, BI, BJ) * RHOCONST *(
     > TOTPHIHYD(I, J, K, BI, BJ) - RC(K) * GRAVITY))
            END DO
          END DO
        ELSE
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LOCPRES(I, J) = (-(MASKC(I, J, K, BI, BJ) * GRAVITY * RC(
     > K) * RHOCONST))
            END DO
          END DO
        ENDIF
      ELSE
        IF(USINGPCOORDS) THEN
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              LOCPRES(I, J) = (RC(K) * MASKC(I, J, K, BI, BJ))
            END DO
          END DO
        ENDIF
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE quasihydrostaticterms(BI, BJ, K, EFFECTIVEBUOY, MYTHID
     > )
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) K
      REAL(w2f__8) EFFECTIVEBUOY(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      REAL(w2f__8) SCALINGFACTOR
C
C     **** Statements ****
C
      SCALINGFACTOR = RHOCONST / GRAVITY
      SCALINGFACTOR = 1D00 / GRAVITY
      DO J = -2, 43, 1
        DO I = -2, 92, 1
          EFFECTIVEBUOY(I, J) = (EFFECTIVEBUOY(I, J) - FCORICOS(I, J,
     >  BI, BJ) * SCALINGFACTOR * 5.0D-01 *(UVEL(I, J, K, BI, BJ) +
     >  UVEL(I + 1, J, K, BI, BJ)))
        END DO
      END DO
      IF(USENHMTERMS) THEN
        DO J = -2, 42, 1
          DO I = -2, 92, 1
            EFFECTIVEBUOY(I, J) = (EFFECTIVEBUOY(I, J) - RECIP_RSPHERE
     >  * SCALINGFACTOR *(((UVEL(I, J, K, BI, BJ) ** 2) +(UVEL(I + 1, J
     > , K, BI, BJ) ** 2)) * 5.0D-01 +((VVEL(I, J, K, BI, BJ) ** 2) +(
     > VVEL(I, J + 1, K, BI, BJ) ** 2)) * 5.0D-01))
          END DO
        END DO
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE solve_for_pressure(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use cd_code_vars_mod
      use grid_mod
      use surface_mod
      use ffields_mod
      use solve_for_pressure_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL calc_div_ghat
      EXTERNAL cg2d
      EXTERNAL debug_stats_rl
      EXTERNAL different_multiple
      LOGICAL(w2f__i4) different_multiple
      EXTERNAL exch_xy_rl
      REAL(w2f__8) FIRSTRESIDUAL
      EXTERNAL global_sum_r8
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) K
      REAL(w2f__8) LASTRESIDUAL
      CHARACTER(512) MSGBUF
      INTEGER(w2f__i4) NUMITERS
      EXTERNAL print_message
      LOGICAL(w2f__i4) PUTPMEINXVECTOR
      REAL(w2f__8) SUMEMP
      REAL(w2f__8) TILEEMP
      REAL(w2f__8) TMPFAC
      REAL(w2f__8) UF(-2 : 93, -2 : 43)
      REAL(w2f__8) VF(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
C
C     **** Statements ****
C
      PUTPMEINXVECTOR = .FALSE.
      SUMEMP = 0.0D00
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ETANM1(I, J, BI, BJ) = ETAN(I, J, BI, BJ)
              CG2D_X(I, J, BI, BJ) = (ETAN(I, J, BI, BJ) * BO_SURF(I, J
     > , BI, BJ))
              CG2D_B(I, J, BI, BJ) = 0.0
            END DO
          END DO
          IF(USEREALFRESHWATERFLUX) THEN
            TMPFAC = CONVERTEMP2RUNIT * FREESURFFAC
            IF(EXACTCONSERV) THEN
              TMPFAC = IMPLICDIV2DFLOW * CONVERTEMP2RUNIT * FREESURFFAC
            ENDIF
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                CG2D_B(I, J, BI, BJ) = ((EMPMR(I, J, BI, BJ) * RA(I, J,
     >  BI, BJ) * TMPFAC) / DELTATMOM)
              END DO
            END DO
          ENDIF
          IF(PUTPMEINXVECTOR) THEN
            TILEEMP = 0.0D00
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                TILEEMP = TILEEMP + MASKH(I, J, BI, BJ) * EMPMR(I, J,
     >  BI, BJ) * RA(I, J, BI, BJ)
              END DO
            END DO
            SUMEMP = SUMEMP + TILEEMP
          ENDIF
        END DO
      END DO
      IF(PUTPMEINXVECTOR) THEN
        CALL global_sum_r8(SUMEMP, MYTHID)
      ENDIF
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          IF(PUTPMEINXVECTOR) THEN
            TMPFAC = 0.0D00
            IF(GLOBALAREA .GT. 0.0D00) THEN
              TMPFAC = (SUMEMP * CONVERTEMP2RUNIT * DELTATFREESURF *
     >  FREESURFFAC) / GLOBALAREA
            ENDIF
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                CG2D_X(I, J, BI, BJ) = (CG2D_X(I, J, BI, BJ) - BO_SURF(
     > I, J, BI, BJ) * TMPFAC)
              END DO
            END DO
          ENDIF
          DO K = 15, 1, (-1)
            DO J = 1, 41, 1
              DO I = 1, 91, 1
                UF(I, J) = (HFACW(I, J, K, BI, BJ) * DRF(K) * DYG(I, J,
     >  BI, BJ))
                VF(I, J) = (HFACS(I, J, K, BI, BJ) * DRF(K) * DXG(I, J,
     >  BI, BJ))
              END DO
            END DO
            CALL calc_div_ghat((BI), (BJ), (1), (90), (1), (40), (K),
     >  UF, VF, CG2D_B, MYTHID)
          END DO
        END DO
      END DO
      doloop_ub3 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub3, 1
        doloop_ub4 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub4, 1
          IF(EXACTCONSERV) THEN
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                CG2D_B(I, J, BI, BJ) = (CG2D_B(I, J, BI, BJ) - ETAH(I,
     >  J, BI, BJ) *(((RA(I, J, BI, BJ) * FREESURFFAC) / DELTATMOM) /
     >  DELTATFREESURF))
              END DO
            END DO
          ELSE
            DO J = 1, 40, 1
              DO I = 1, 90, 1
                CG2D_B(I, J, BI, BJ) = (CG2D_B(I, J, BI, BJ) - ETAN(I,
     >  J, BI, BJ) *(((RA(I, J, BI, BJ) * FREESURFFAC) / DELTATMOM) /
     >  DELTATFREESURF))
              END DO
            END DO
          ENDIF
        END DO
      END DO
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_stats_rl((1), CG2D_B, 'cg2d_b (SOLVE_FOR_PRESSURE)',
     >  MYTHID)
      ENDIF
      FIRSTRESIDUAL = 0.0D00
      LASTRESIDUAL = 0.0D00
      NUMITERS = CG2DMAXITERS
      CALL cg2d(CG2D_B, CG2D_X, FIRSTRESIDUAL, LASTRESIDUAL, NUMITERS,
     >  MYTHID)
      CALL exch_xy_rl(CG2D_X, MYTHID)
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_stats_rl((1), CG2D_X, 'cg2d_x (SOLVE_FOR_PRESSURE)',
     >  MYTHID)
      ENDIF
      IF(different_multiple(MONITORFREQ, MYTIME, DELTATCLOCK)) THEN
        IF(DEBUGLEVEL .GE. 1) THEN
          IF(MYTHID .eq. 1) THEN
            WRITE(MSGBUF, '(A34,1PE24.14)') 'cg2d_init_res =',
     >  FIRSTRESIDUAL
            CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
            WRITE(MSGBUF, '(A34,I6)') 'cg2d_iters =', NUMITERS
            CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
            WRITE(MSGBUF, '(A34,1PE24.14)') 'cg2d_res =', LASTRESIDUAL
            CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
          ENDIF
        ENDIF
      ENDIF
      doloop_ub5 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub5, 1
        doloop_ub6 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub6, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              ETAN(I, J, BI, BJ) = (CG2D_X(I, J, BI, BJ) * RECIP_BO(I,
     >  J, BI, BJ))
            END DO
          END DO
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE state_summary(MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL barrier
      CHARACTER(512) MSGBUF
      EXTERNAL print_message
C
C     **** Statements ****
C
      CALL barrier(MYTHID)
      IF(MYTHID .eq. 1) THEN
        WRITE(MSGBUF, '(A)')
     >  '// =============================================' //
     >  '=========='
        CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
        WRITE(MSGBUF, '(A)') '// Model current state'
        CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
        WRITE(MSGBUF, '(A)')
     >  '// =============================================' //
     >  '=========='
        CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
        WRITE(MSGBUF, '(A)') ' '
        CALL print_message(MSGBUF, STANDARDMESSAGEUNIT, 'R', (1))
      ENDIF
      CALL barrier(MYTHID)
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE timestep(BI, BJ, IMIN, IMAX, JMIN, JMAX, K, DPHIHYDX,
     >  DPHIHYDY, PHISURFX, PHISURFY, GUDISSIP, GVDISSIP, MYTIME,
     >  MYITER, MYTHID)
      use w2f__types
      use size_mod
      use dynvars_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use surface_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      REAL(w2f__8) DPHIHYDX(-2 : 93, -2 : 43)
      REAL(w2f__8) DPHIHYDY(-2 : 93, -2 : 43)
      REAL(w2f__8) PHISURFX(-2 : 93, -2 : 43)
      REAL(w2f__8) PHISURFY(-2 : 93, -2 : 43)
      REAL(w2f__8) GUDISSIP(-2 : 93, -2 : 43)
      REAL(w2f__8) GVDISSIP(-2 : 93, -2 : 43)
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      REAL(w2f__8) AB05
      REAL(w2f__8) AB15
      EXTERNAL adams_bashforth2
      EXTERNAL cd_code_scheme
      EXTERNAL external_forcing_u
      EXTERNAL external_forcing_v
      REAL(w2f__8) GUCOR(-2 : 93, -2 : 43)
      REAL(w2f__8) GUTMP(-2 : 93, -2 : 43)
      REAL(w2f__8) GVCOR(-2 : 93, -2 : 43)
      REAL(w2f__8) GVTMP(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      LOGICAL(w2f__i4) MOMDISSIP_IN_AB
      LOGICAL(w2f__i4) MOMFORCING_IN_AB
      REAL(w2f__8) PHXFAC
      REAL(w2f__8) PHYFAC
      REAL(w2f__8) PSFAC
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
      INTEGER(w2f__i4) doloop_ub3
      INTEGER(w2f__i4) doloop_ub4
      INTEGER(w2f__i4) doloop_ub5
      INTEGER(w2f__i4) doloop_ub6
      INTEGER(w2f__i4) doloop_ub7
      INTEGER(w2f__i4) doloop_ub8
      INTEGER(w2f__i4) doloop_ub9
      INTEGER(w2f__i4) doloop_ub10
      INTEGER(w2f__i4) doloop_ub11
      INTEGER(w2f__i4) doloop_ub12
      INTEGER(w2f__i4) doloop_ub13
      INTEGER(w2f__i4) doloop_ub14
      INTEGER(w2f__i4) doloop_ub15
      INTEGER(w2f__i4) doloop_ub16
      INTEGER(w2f__i4) doloop_ub17
      INTEGER(w2f__i4) doloop_ub18
C
C     **** Statements ****
C
      IF(MYITER .eq. 0) THEN
        AB15 = 1.0D00
        AB05 = 0.0D00
      ELSE
        AB15 = ABEPS + 1.5D00
        AB05 = (-5.0D-01) - ABEPS
      ENDIF
      PSFAC = PFFACMOM *(1.0D00 - IMPLICSURFPRESS)
      PHXFAC = PFFACMOM
      PHYFAC = PFFACMOM
      MOMFORCING_IN_AB = FORCING_IN_AB
      MOMFORCING_IN_AB = .TRUE.
      MOMDISSIP_IN_AB = .TRUE.
      DO J = -2, 43, 1
        DO I = -2, 93, 1
          GUTMP(I, J) = 0.0D00
          GVTMP(I, J) = 0.0D00
          GUCOR(I, J) = 0.0D00
          GVCOR(I, J) = 0.0D00
        END DO
      END DO
      IF(.NOT. STAGGERTIMESTEP) THEN
        doloop_ub = JMAX
        DO J = JMIN, doloop_ub, 1
          doloop_ub0 = IMAX
          DO I = IMIN, doloop_ub0, 1
            GU(I, J, K, BI, BJ) = (GU(I, J, K, BI, BJ) - DPHIHYDX(I, J)
     >  * PHXFAC)
            GV(I, J, K, BI, BJ) = (GV(I, J, K, BI, BJ) - DPHIHYDY(I, J)
     >  * PHYFAC)
          END DO
        END DO
        PHXFAC = 0.0D00
        PHYFAC = 0.0D00
      ENDIF
      IF(MOMDISSIP_IN_AB .AND. MOMVISCOSITY) THEN
        doloop_ub1 = JMAX
        DO J = JMIN, doloop_ub1, 1
          doloop_ub2 = IMAX
          DO I = IMIN, doloop_ub2, 1
            GU(I, J, K, BI, BJ) = (GUDISSIP(I, J) + GU(I, J, K, BI, BJ)
     > )
            GV(I, J, K, BI, BJ) = (GVDISSIP(I, J) + GV(I, J, K, BI, BJ)
     > )
          END DO
        END DO
      ENDIF
      IF(MOMFORCING_IN_AB .AND. MOMFORCING) THEN
        CALL external_forcing_u(IMIN, IMAX, JMIN, JMAX, BI, BJ, K,
     >  MYTIME, MYTHID)
        CALL external_forcing_v(IMIN, IMAX, JMIN, JMAX, BI, BJ, K,
     >  MYTIME, MYTHID)
      ENDIF
      IF(USECDSCHEME) THEN
        doloop_ub3 = JMAX
        DO J = JMIN, doloop_ub3, 1
          doloop_ub4 = IMAX
          DO I = IMIN, doloop_ub4, 1
            GUTMP(I, J) = GU(I, J, K, BI, BJ)
            GVTMP(I, J) = GV(I, J, K, BI, BJ)
          END DO
        END DO
      ENDIF
      CALL adams_bashforth2(BI, BJ, K, GU, GUNM1, MYITER, MYTHID)
      CALL adams_bashforth2(BI, BJ, K, GV, GVNM1, MYITER, MYTHID)
      IF(MOMFORCING .AND.(.NOT. MOMFORCING_IN_AB)) THEN
        IF(USECDSCHEME) THEN
          doloop_ub5 = JMAX
          DO J = JMIN, doloop_ub5, 1
            doloop_ub6 = IMAX
            DO I = IMIN, doloop_ub6, 1
              GUTMP(I, J) = (GUTMP(I, J) - GU(I, J, K, BI, BJ))
              GVTMP(I, J) = (GVTMP(I, J) - GV(I, J, K, BI, BJ))
            END DO
          END DO
        ENDIF
        CALL external_forcing_u(IMIN, IMAX, JMIN, JMAX, BI, BJ, K,
     >  MYTIME, MYTHID)
        CALL external_forcing_v(IMIN, IMAX, JMIN, JMAX, BI, BJ, K,
     >  MYTIME, MYTHID)
        IF(USECDSCHEME) THEN
          doloop_ub7 = JMAX
          DO J = JMIN, doloop_ub7, 1
            doloop_ub8 = IMAX
            DO I = IMIN, doloop_ub8, 1
              GUTMP(I, J) = (GUTMP(I, J) + GU(I, J, K, BI, BJ))
              GVTMP(I, J) = (GVTMP(I, J) + GV(I, J, K, BI, BJ))
            END DO
          END DO
        ENDIF
      ENDIF
      IF(USECDSCHEME) THEN
        CALL cd_code_scheme(BI, BJ, K, DPHIHYDX, DPHIHYDY, GUTMP, GVTMP
     > , GUCOR, GVCOR, MYTIME, MYITER, MYTHID)
        doloop_ub9 = JMAX
        DO J = JMIN, doloop_ub9, 1
          doloop_ub10 = IMAX
          DO I = IMIN, doloop_ub10, 1
            GUTMP(I, J) = (GUCOR(I, J) + GU(I, J, K, BI, BJ))
            GVTMP(I, J) = (GVCOR(I, J) + GV(I, J, K, BI, BJ))
          END DO
        END DO
      ELSE
        doloop_ub11 = JMAX
        DO J = JMIN, doloop_ub11, 1
          doloop_ub12 = IMAX
          DO I = IMIN, doloop_ub12, 1
            GUTMP(I, J) = GU(I, J, K, BI, BJ)
            GVTMP(I, J) = GV(I, J, K, BI, BJ)
          END DO
        END DO
      ENDIF
      IF(MOMVISCOSITY .AND.(.NOT. MOMDISSIP_IN_AB)) THEN
        doloop_ub13 = JMAX
        DO J = JMIN, doloop_ub13, 1
          doloop_ub14 = IMAX
          DO I = IMIN, doloop_ub14, 1
            GUTMP(I, J) = (GUDISSIP(I, J) + GUTMP(I, J))
            GVTMP(I, J) = (GVDISSIP(I, J) + GVTMP(I, J))
          END DO
        END DO
      ENDIF
      doloop_ub15 = JMAX
      DO J = JMIN, doloop_ub15, 1
        doloop_ub16 = IMAX
        DO I = IMIN, doloop_ub16, 1
          GU(I, J, K, BI, BJ) = (UVEL(I, J, K, BI, BJ) + MASKW(I, J, K,
     >  BI, BJ) * DELTATMOM *(GUTMP(I, J) - PHISURFX(I, J) * PSFAC -
     >  DPHIHYDX(I, J) * PHXFAC))
        END DO
      END DO
      doloop_ub17 = JMAX
      DO J = JMIN, doloop_ub17, 1
        doloop_ub18 = IMAX
        DO I = IMIN, doloop_ub18, 1
          GV(I, J, K, BI, BJ) = (VVEL(I, J, K, BI, BJ) + MASKS(I, J, K,
     >  BI, BJ) * DELTATMOM *(GVTMP(I, J) - PHISURFY(I, J) * PSFAC -
     >  DPHIHYDY(I, J) * PHYFAC))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE the_correction_step(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL calc_grad_phi_surf
      EXTERNAL convective_adjustment
      EXTERNAL correction_step
      EXTERNAL cycle_tracer
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) K
      REAL(w2f__8) PHISURFX(-2 : 93, -2 : 43)
      REAL(w2f__8) PHISURFY(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              PHISURFX(I, J) = 0.0
              PHISURFY(I, J) = 0.0
            END DO
          END DO
          IMIN = -1
          IMAX = 93
          JMIN = -1
          JMAX = 43
          CALL calc_grad_phi_surf((BI), (BJ), IMIN, IMAX, JMIN, JMAX,
     >  ETAN, PHISURFX, PHISURFY, MYTHID)
          DO K = 1, 15, 1
            IF(MOMSTEPPING) THEN
              CALL correction_step((BI), (BJ), IMIN, IMAX, JMIN, JMAX,
     >  (K), PHISURFX, PHISURFY, MYTIME, MYTHID)
            ENDIF
            IF(TEMPSTEPPING) THEN
              CALL cycle_tracer((BI), (BJ), (K), THETA, GT, MYTIME,
     >  MYITER, MYTHID)
            ENDIF
            IF(SALTSTEPPING) THEN
              CALL cycle_tracer((BI), (BJ), (K), SALT, GS, MYTIME,
     >  MYITER, MYTHID)
            ENDIF
          END DO
          IMIN = 1
          IMAX = 90
          JMIN = 1
          JMAX = 40
          CALL convective_adjustment((BI), (BJ), IMIN, IMAX, JMIN, JMAX
     > , MYTIME, MYITER, MYTHID)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE the_main_loop(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use grid_mod
      use dynvars_mod
      use ffields_mod
      use eos_mod
      use gad_mod
      use cd_code_vars_mod
      use tamc_mod
      use ctrl_mod
      use ctrl_dummy_mod
      use cost_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      EXTERNAL autodiff_inadmode_set
      EXTERNAL autodiff_inadmode_unset
      EXTERNAL barrier
      EXTERNAL cost_final
      EXTERNAL debug_call
      EXTERNAL debug_enter
      EXTERNAL debug_leave
      EXTERNAL do_the_model_io
      EXTERNAL forward_step
      INTEGER(w2f__i4) ILEV_1
      INTEGER(w2f__i4) ILEV_2
      INTEGER(w2f__i4) ILEV_3
      INTEGER(w2f__i4) ILOOP
      EXTERNAL initialise_varia
      INTEGER(w2f__i4) MAX_LEV2
      INTEGER(w2f__i4) MAX_LEV3
      INTEGER(w2f__i4) MAX_LEV4
      EXTERNAL timer_start
      EXTERNAL timer_stop
C
C     **** Statements ****
C
      IF(DEBUGMODE) THEN
        CALL debug_enter('THE_MAIN_LOOP', MYTHID)
      ENDIF
      NITER0 = NINT((STARTTIME - BASETIME) / DELTATCLOCK)
      IKEY_DYNAMICS = 1
      CALL timer_start('ADJOINT SPIN-UP', MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('INITIALISE_VARIA', MYTHID)
      ENDIF
      CALL timer_start('INITIALISE_VARIA    [THE_MAIN_LOOP]', MYTHID)
      CALL initialise_varia(MYTHID)
      CALL timer_stop('INITIALISE_VARIA    [THE_MAIN_LOOP]', MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_call('DO_THE_MODEL_IO', MYTHID)
      ENDIF
      CALL timer_start('DO_THE_MODEL_IO     [THE_MAIN_LOOP]', MYTHID)
      CALL do_the_model_io(MYTIME, MYITER, MYTHID)
      CALL timer_stop('DO_THE_MODEL_IO     [THE_MAIN_LOOP]', MYTHID)
      CALL timer_stop('ADJOINT SPIN-UP', MYTHID)
      CALL barrier(MYTHID)
      CALL timer_start('MAIN LOOP           [THE_MAIN_LOOP]', MYTHID)
      MAX_LEV4 = (NTIMESTEPS / 28800) + 1
      MAX_LEV3 = (NTIMESTEPS / 480) + 1
      MAX_LEV2 = (NTIMESTEPS / 2) + 1
      DO ILEV_3 = 1, 60, 1
        IF(ILEV_3 .LE. MAX_LEV3) THEN
          DO ILEV_2 = 1, 240, 1
            IF(ILEV_2 .LE. MAX_LEV2) THEN
              DO ILEV_1 = 1, 2, 1
                ILOOP = ILEV_1 + ILEV_2 * 2 + ILEV_3 * 480 +(-482)
                IF(ILOOP .LE. NTIMESTEPS) THEN
                  NITER0 = NINT((STARTTIME - BASETIME) / DELTATCLOCK)
                  IKEY_DYNAMICS = ILEV_1
                  CALL autodiff_inadmode_unset(MYTHID)
                  CALL autodiff_inadmode_unset(MYTHID)
                  IF(DEBUGMODE) THEN
                    CALL debug_call('FORWARD_STEP', MYTHID)
                  ENDIF
                  CALL timer_start(
     > 'FORWARD_STEP        [THE_MAIN_LOOP]', MYTHID)
                  CALL forward_step(ILOOP, MYTIME, MYITER, MYTHID)
                  CALL timer_stop('FORWARD_STEP        [THE_MAIN_LOOP]'
     > , MYTHID)
                  CALL autodiff_inadmode_set(MYTHID)
                  CALL autodiff_inadmode_set(MYTHID)
                ENDIF
              END DO
            ENDIF
          END DO
        ENDIF
      END DO
      CALL timer_start('COST_FINAL         [ADJOINT SPIN-DOWN]', MYTHID
     > )
      CALL cost_final(MYTHID)
      CALL timer_stop('COST_FINAL         [ADJOINT SPIN-DOWN]', MYTHID)
      CALL barrier(MYTHID)
      CALL timer_stop('MAIN LOOP           [THE_MAIN_LOOP]', MYTHID)
      IF(DEBUGMODE) THEN
        CALL debug_leave('THE_MAIN_LOOP', MYTHID)
      ENDIF
      RETURN
      END SUBROUTINE

      SUBROUTINE thermodynamics(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use gad_mod
      use tamc_mod
      use tamc_keys_mod
      use ffields_mod
      use eos_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL calc_3d_diffusivity
      EXTERNAL calc_common_factors
      EXTERNAL calc_diffusivity
      EXTERNAL calc_gs
      EXTERNAL calc_gt
      EXTERNAL debug_call
      EXTERNAL debug_enter
      EXTERNAL debug_leave
      EXTERNAL debug_msg
      EXTERNAL debug_stats_rl
      EXTERNAL freeze
      REAL(w2f__8) FVERS(-2 : 93, -2 : 43, 1 : 2)
      REAL(w2f__8) FVERT(-2 : 93, -2 : 43, 1 : 2)
      EXTERNAL gad_advection
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      EXTERNAL impldiff
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) K
      REAL(w2f__8) KAPPARK(-2 : 93, -2 : 43, 1 : 15)
      REAL(w2f__8) KAPPARS(-2 : 93, -2 : 43)
      REAL(w2f__8) KAPPART(-2 : 93, -2 : 43)
      INTEGER(w2f__i4) KDOWN
      INTEGER(w2f__i4) KM1
      REAL(w2f__8) KP1MSK
      INTEGER(w2f__i4) KUP
      REAL(w2f__8) MASKUP(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) RTRANSKP1(-2 : 93, -2 : 43)
      EXTERNAL timestep_tracer
      REAL(w2f__8) UTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) VTRANS(-2 : 93, -2 : 43)
      REAL(w2f__8) XA(-2 : 93, -2 : 43)
      REAL(w2f__8) YA(-2 : 93, -2 : 43)
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_enter('THERMODYNAMICS', MYTHID)
      ENDIF
      IKEY = 1
      ITDKEY = 1
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          ACT1 = BI - MYBXLO(MYTHID)
          MAX1 = MYBXHI(MYTHID) - MYBXLO(MYTHID) + 1
          ACT2 = BJ - MYBYLO(MYTHID)
          MAX2 = MYBYHI(MYTHID) - MYBYLO(MYTHID) + 1
          ACT3 = MYTHID +(-1)
          MAX3 = NTX * NTY
          ACT4 = IKEY_DYNAMICS +(-1)
          ITDKEY = ACT1 + ACT2 * MAX1 + MAX2 * ACT3 * MAX1 + MAX3 *
     >  MAX2 * ACT4 * MAX1 + 1
          DO J = -2, 43, 1
            DO I = -2, 93, 1
              XA(I, J) = 0.0D00
              YA(I, J) = 0.0D00
              UTRANS(I, J) = 0.0D00
              VTRANS(I, J) = 0.0D00
              RTRANS(I, J) = 0.0D00
              RTRANSKP1(I, J) = 0.0D00
              FVERT(I, J, 1) = 0.0D00
              FVERT(I, J, 2) = 0.0D00
              FVERS(I, J, 1) = 0.0D00
              FVERS(I, J, 2) = 0.0D00
              KAPPART(I, J) = 0.0D00
              KAPPARS(I, J) = 0.0D00
            END DO
          END DO
          DO K = 1, 15, 1
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                KAPPARK(I, J, K) = 0.0D00
                GT(I, J, K, BI, BJ) = 0.0D00
                GS(I, J, K, BI, BJ) = 0.0D00
              END DO
            END DO
          END DO
          IF(TEMPMULTIDIMADVEC) THEN
            IF(DEBUGLEVEL .GE. 2) THEN
              CALL debug_call('GAD_ADVECTION', MYTHID)
            ENDIF
            CALL gad_advection(TEMPIMPLVERTADV, TEMPADVSCHEME,
     >  TEMPVERTADVSCHEME, (1), UVEL, VVEL, WVEL, THETA, GT, (BI), (BJ)
     > , MYTIME, MYITER, MYTHID)
          ENDIF
          IF(SALTMULTIDIMADVEC) THEN
            IF(DEBUGLEVEL .GE. 2) THEN
              CALL debug_call('GAD_ADVECTION', MYTHID)
            ENDIF
            CALL gad_advection(SALTIMPLVERTADV, SALTADVSCHEME,
     >  SALTVERTADVSCHEME, (2), UVEL, VVEL, WVEL, SALT, GS, (BI), (BJ),
     >  MYTIME, MYITER, MYTHID)
          ENDIF
          IF(DEBUGLEVEL .GE. 2) THEN
            CALL debug_msg('ENTERING DOWNWARD K LOOP', MYTHID)
          ENDIF
          DO K = 15, 1, (-1)
            KKEY = K + ITDKEY * 15 +(-15)
            KM1 = MAX(K +(-1), 1)
            KUP = MOD(K + 1, 2) + 1
            KDOWN = MOD(K, 2) + 1
            IMIN = -2
            IMAX = 93
            JMIN = -2
            JMAX = 43
            KP1MSK = 1.0D00
            IF(K .eq. 15) THEN
              KP1MSK = 0.0D00
            ENDIF
            DO J = -2, 43, 1
              DO I = -2, 93, 1
                RTRANSKP1(I, J) = (RTRANS(I, J) * KP1MSK)
              END DO
            END DO
            CALL calc_common_factors((BI), (BJ), IMIN, IMAX, JMIN, JMAX
     > , (K), XA, YA, UTRANS, VTRANS, RTRANS, MASKUP, MYTHID)
            IF(K .eq. 1) THEN
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  RTRANS(I, J) = 0.0
                END DO
              END DO
            ELSE
              DO J = -2, 43, 1
                DO I = -2, 93, 1
                  RTRANS(I, J) = (RTRANS(I, J) * MASKC(I, J, K + (-1),
     >  BI, BJ))
                END DO
              END DO
            ENDIF
            IF(.NOT. IMPLICITDIFFUSION) THEN
              CALL calc_diffusivity((BI), (BJ), IMIN, IMAX, JMIN, JMAX,
     >  (K), MASKUP, KAPPART, KAPPARS, MYTHID)
            ENDIF
            IMIN = 0
            IMAX = 92
            JMIN = 0
            JMAX = 42
            IF(TEMPSTEPPING) THEN
              CALL calc_gt((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K), KM1
     > , KUP, KDOWN, XA, YA, UTRANS, VTRANS, RTRANS, RTRANSKP1, MASKUP,
     >  KAPPART, FVERT, MYTIME, MYITER, MYTHID)
              CALL timestep_tracer((BI), (BJ), IMIN, IMAX, JMIN, JMAX,
     >  (K), TEMPADVSCHEME, THETA, GT, MYITER, MYTHID)
            ENDIF
            IF(SALTSTEPPING) THEN
              CALL calc_gs((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K), KM1
     > , KUP, KDOWN, XA, YA, UTRANS, VTRANS, RTRANS, RTRANSKP1, MASKUP,
     >  KAPPARS, FVERS, MYTIME, MYITER, MYTHID)
              CALL timestep_tracer((BI), (BJ), IMIN, IMAX, JMIN, JMAX,
     >  (K), SALTADVSCHEME, SALT, GS, MYITER, MYTHID)
            ENDIF
            IF((USEOLDFREEZING .AND.(.NOT. USESEAICE)) .AND.(.NOT.((K
     >  .eq. 1) .AND. USETHSICE))) THEN
              CALL freeze((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (K),
     >  MYTHID)
            ENDIF
          END DO
          IMIN = 1
          IMAX = 90
          JMIN = 1
          JMAX = 40
          IF(IMPLICITDIFFUSION .AND. TEMPSTEPPING) THEN
            CALL calc_3d_diffusivity((BI), (BJ), IMIN, IMAX, JMIN, JMAX
     > , (1), USEGMREDI, USEKPP, KAPPARK, MYTHID)
          ENDIF
          IF(IMPLICITDIFFUSION .AND. TEMPSTEPPING) THEN
            CALL impldiff((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (1),
     >  KAPPARK, RECIP_HFACC, GT, MYTHID)
          ENDIF
          IF(IMPLICITDIFFUSION .AND. SALTSTEPPING) THEN
            CALL calc_3d_diffusivity((BI), (BJ), IMIN, IMAX, JMIN, JMAX
     > , (2), USEGMREDI, USEKPP, KAPPARK, MYTHID)
          ENDIF
          IF(IMPLICITDIFFUSION .AND. SALTSTEPPING) THEN
            CALL impldiff((BI), (BJ), IMIN, IMAX, JMIN, JMAX, (2),
     >  KAPPARK, RECIP_HFACC, GS, MYTHID)
          ENDIF
        END DO
      END DO
      IF(DEBUGMODE) THEN
        CALL debug_stats_rl((15), UVEL, 'Uvel (THERMODYNAMICS)', MYTHID
     > )
        CALL debug_stats_rl((15), VVEL, 'Vvel (THERMODYNAMICS)', MYTHID
     > )
        CALL debug_stats_rl((15), WVEL, 'Wvel (THERMODYNAMICS)', MYTHID
     > )
        CALL debug_stats_rl((15), THETA, 'Theta (THERMODYNAMICS)',
     >  MYTHID)
        CALL debug_stats_rl((15), SALT, 'Salt (THERMODYNAMICS)', MYTHID
     > )
        CALL debug_stats_rl((15), GT, 'Gt (THERMODYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GS, 'Gs (THERMODYNAMICS)', MYTHID)
        CALL debug_stats_rl((15), GTNM1, 'GtNm1 (THERMODYNAMICS)',
     >  MYTHID)
        CALL debug_stats_rl((15), GSNM1, 'GsNm1 (THERMODYNAMICS)',
     >  MYTHID)
      ENDIF
      IF(DEBUGLEVEL .GE. 2) THEN
        CALL debug_leave('THERMODYNAMICS', MYTHID)
      ENDIF
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE timestep_tracer(BI, BJ, IMIN, IMAX, JMIN, JMAX, K,
     >  ADVECTION_SCHEME, TRACER, GTRACER, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) K
      INTEGER(w2f__i4) ADVECTION_SCHEME
      REAL(w2f__8) TRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      REAL(w2f__8) GTRACER(-2 : 93, -2 : 43, 1 : 15, 1 : 1, 1 : 1)
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
C
C     **** Statements ****
C
      doloop_ub = JMAX
      DO J = JMIN, doloop_ub, 1
        doloop_ub0 = IMAX
        DO I = IMIN, doloop_ub0, 1
          GTRACER(I, J, K, BI, BJ) = (TRACER(I, J, K, BI, BJ) +
     >  DTTRACERLEV(K) * GTRACER(I, J, K, BI, BJ))
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE tracers_correction_step(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i4) BI
      INTEGER(w2f__i4) BJ
      EXTERNAL convective_adjustment
      EXTERNAL cycle_tracer
      INTEGER(w2f__i4) IMAX
      INTEGER(w2f__i4) IMIN
      INTEGER(w2f__i4) JMAX
      INTEGER(w2f__i4) JMIN
      INTEGER(w2f__i4) K
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i4) doloop_ub0
      INTEGER(w2f__i4) doloop_ub1
      INTEGER(w2f__i4) doloop_ub2
C
C     **** Statements ****
C
      doloop_ub = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub, 1
        doloop_ub0 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub0, 1
          DO K = 1, 15, 1
            IF(TEMPSTEPPING) THEN
              CALL cycle_tracer((BI), (BJ), (K), THETA, GT, MYTIME,
     >  MYITER, MYTHID)
            ENDIF
            IF(SALTSTEPPING) THEN
              CALL cycle_tracer((BI), (BJ), (K), SALT, GS, MYTIME,
     >  MYITER, MYTHID)
            ENDIF
          END DO
        END DO
      END DO
      doloop_ub1 = MYBYHI(MYTHID)
      DO BJ = MYBYLO(MYTHID), doloop_ub1, 1
        doloop_ub2 = MYBXHI(MYTHID)
        DO BI = MYBXLO(MYTHID), doloop_ub2, 1
          IMIN = 1
          IMAX = 90
          JMIN = 1
          JMAX = 40
          CALL convective_adjustment((BI), (BJ), IMIN, IMAX, JMIN, JMAX
     > , MYTIME, MYITER, MYTHID)
        END DO
      END DO
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE update_etah(MYTIME, MYITER, MYTHID)
      use w2f__types
      use size_mod
      use eeparams_mod
      use params_mod
      use dynvars_mod
      use grid_mod
      use surface_mod
      use ffields_mod
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYITER
      INTEGER(w2f__i4) MYTHID
C
C     **** Statements ****
C
      RETURN
      RETURN
      END SUBROUTINE

      SUBROUTINE swfrac(IMAX, FACT, MYTIME, MYTHID, SWDK)
      use w2f__types
      IMPLICIT NONE
C
C     **** Parameters and Result ****
C
      INTEGER(w2f__i4) IMAX
      REAL(w2f__8) FACT
      REAL(w2f__8) MYTIME
      INTEGER(w2f__i4) MYTHID
      REAL(w2f__8) SWDK(1 : IMAX)
C
C     **** Local Variables and Functions ****
C
      INTEGER(w2f__i8) t__922
      INTEGER(w2f__i8) t__924
      REAL(w2f__8) A1(1 : 5)
      SAVE A1
      REAL(w2f__8) A2(1 : 5)
      SAVE A2
      REAL(w2f__8) FACZ
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) JWTYPE
      INTEGER(w2f__i4) NWTYPE
      PARAMETER ( NWTYPE = 5)
      REAL(w2f__8) RFAC(1 : 5)
      SAVE RFAC
C
C     **** Temporary Variables ****
C
      INTEGER(w2f__i4) doloop_ub
      INTEGER(w2f__i8) tmp0
C
C     **** Initializers ****
C
      DATA(A1(tmp0), tmp0 = 1, 5, 1) / 3.49999994039535522461D-01,
     >  6.00000023841857910156D-01, 1.0D00, 1.5D00,
     >  1.39999997615814208984D00 /
      DATA(A2(tmp0), tmp0 = 1, 5, 1) / 2.3D+01, 2.0D+01, 1.7D+01,
     >  1.4D+01, 7.90000009536743164062D00 /
      DATA(RFAC(tmp0), tmp0 = 1, 5, 1) / 5.79999983310699462891D-01,
     >  6.20000004768371582031D-01, 6.70000016689300537109D-01,
     >  7.69999980926513671875D-01, 7.79999971389770507812D-01 /
C
C     **** Statements ****
C
      t__922 = IMAX
      t__924 = MAX(t__922, 0_w2f__i8)
      JWTYPE = 2
      doloop_ub = IMAX
      DO I = 1, doloop_ub, 1
        FACZ = SWDK(I) * FACT
        IF(FACZ .LT.(-2.0D+02)) THEN
          SWDK(I) = 0.0
        ELSE
          SWDK(I) = (RFAC(JWTYPE) * EXP(FACZ / A1(JWTYPE)) + EXP(FACZ /
     >  A2(JWTYPE)) *(1.0D00 - RFAC(JWTYPE)))
        ENDIF
      END DO
      RETURN
      RETURN
      END SUBROUTINE
