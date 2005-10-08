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
