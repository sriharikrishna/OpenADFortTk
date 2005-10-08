      MODULE SIZE_mod
      INTEGER sNx
      INTEGER sNy
      INTEGER OLx
      INTEGER OLy
      INTEGER nSx
      INTEGER nSy
      INTEGER nPx
      INTEGER nPy
      INTEGER Nx
      INTEGER Ny
      INTEGER Nr
      PARAMETER (
     &           sNx =  90,
     &           sNy =  40,
     &           OLx =   3,
     &           OLy =   3,
     &           nSx =   1,
     &           nSy =   1,
     &           nPx =   1,
     &           nPy =   1,
     &           Nx  = sNx*nSx*nPx,
     &           Ny  = sNy*nSy*nPy,
     &           Nr  =  15)
      INTEGER MAX_OLX
      INTEGER MAX_OLY
      PARAMETER ( MAX_OLX = OLx,
     &            MAX_OLY = OLy )
      integer     nobcs
      parameter ( nobcs = 4 )
      END MODULE SIZE_mod
      MODULE EEPARAMS_mod
      use SIZE_mod
      INTEGER MAX_LEN_MBUF
      PARAMETER ( MAX_LEN_MBUF = 512 )
      INTEGER MAX_LEN_FNAM
      PARAMETER ( MAX_LEN_FNAM = 512 )
      INTEGER MAX_LEN_PREC
      PARAMETER ( MAX_LEN_PREC = 200 )
      CHARACTER*(*) SQUEEZE_RIGHT
      PARAMETER ( SQUEEZE_RIGHT = 'R' )
      CHARACTER*(*) SQUEEZE_LEFT
      PARAMETER ( SQUEEZE_LEFT = 'L' )
      CHARACTER*(*) SQUEEZE_BOTH
      PARAMETER ( SQUEEZE_BOTH = 'B' )
      CHARACTER*(*) PRINT_MAP_XY
      PARAMETER ( PRINT_MAP_XY = 'XY' )
      CHARACTER*(*) PRINT_MAP_XZ
      PARAMETER ( PRINT_MAP_XZ = 'XZ' )
      CHARACTER*(*) PRINT_MAP_YZ
      PARAMETER ( PRINT_MAP_YZ = 'YZ' )
      CHARACTER*(*) commentCharacter
      PARAMETER ( commentCharacter = '#' )
      INTEGER INDEX_I
      INTEGER INDEX_J
      INTEGER INDEX_K   
      INTEGER INDEX_NONE
      PARAMETER ( INDEX_I    = 1,
     &            INDEX_J    = 2,
     &            INDEX_K    = 3,
     &            INDEX_NONE = 4 )
      INTEGER EXCH_IGNORE_CORNERS
      INTEGER EXCH_UPDATE_CORNERS
      PARAMETER ( EXCH_IGNORE_CORNERS = 0,
     &            EXCH_UPDATE_CORNERS = 1 )
      INTEGER FORWARD_SIMULATION
      INTEGER REVERSE_SIMULATION
      INTEGER TANGENT_SIMULATION
      PARAMETER ( FORWARD_SIMULATION = 0,
     &            REVERSE_SIMULATION = 1,
     &            TANGENT_SIMULATION = 2 )
      INTEGER cacheLineSize
      INTEGER lShare1
      INTEGER lShare4
      INTEGER lShare8
      PARAMETER ( cacheLineSize = 256 )
      PARAMETER ( lShare1 =  cacheLineSize )
      PARAMETER ( lShare4 =  cacheLineSize/4 )
      PARAMETER ( lShare8 =  cacheLineSize/8 )
      INTEGER MAX_NO_THREADS
      PARAMETER ( MAX_NO_THREADS =   32 )
      INTEGER MAX_NO_PROCS
      PARAMETER ( MAX_NO_PROCS   =  2048 )
      INTEGER MAX_NO_BARRIERS
      PARAMETER ( MAX_NO_BARRIERS = 1 )
      LOGICAL eeBootError
      LOGICAL eeEndError
      LOGICAL fatalError
      LOGICAL useCubedSphereExchange
      LOGICAL useCoupler
      INTEGER eeDataUnit
      INTEGER errorMessageUnit
      INTEGER ioErrorCount(MAX_NO_THREADS)
      INTEGER modelDataUnit
      INTEGER myBxLo(MAX_NO_THREADS)
      INTEGER myBxHi(MAX_NO_THREADS)
      INTEGER myByLo(MAX_NO_THREADS)
      INTEGER myByHi(MAX_NO_THREADS)
      INTEGER myProcId
      INTEGER myPx
      INTEGER myPy
      INTEGER myXGlobalLo
      INTEGER myYGlobalLo
      INTEGER nThreads
      INTEGER nTx
      INTEGER nTy
      INTEGER numberOfProcs
      INTEGER pidIO
      INTEGER scrUnit1
      INTEGER scrUnit2
      INTEGER standardMessageUnit
      END MODULE EEPARAMS_mod
      MODULE PARAMS_mod
      use SIZE_mod
      use EEPARAMS_mod
      Real*8 PI
      PARAMETER ( PI    = 3.14159265358979323844d0   )
      Real*8 deg2rad
      PARAMETER ( deg2rad = 2.d0*PI/360.d0           )
      INTEGER precFloat32
      PARAMETER ( precFloat32 = 32 )
      INTEGER precFloat64
      PARAMETER ( precFloat64 = 64 )
      Real*8 UNSET_FLOAT8
      PARAMETER ( UNSET_FLOAT8 = 1.234567D5 )
      Real*4 UNSET_FLOAT4
      PARAMETER ( UNSET_FLOAT4 = 1.234567E5 )
      Real*8    UNSET_RL    
      PARAMETER ( UNSET_RL     = 1.234567D5 )
      Real*8    UNSET_RS     
      PARAMETER ( UNSET_RS     = 1.234567E5 )
      INTEGER UNSET_I
      PARAMETER ( UNSET_I      = 123456789  )
      INTEGER maxNoChkptLev
      PARAMETER ( maxNoChkptLev = 2 )
      CHARACTER*(5) checkPtSuff(maxNoChkptLev)
      CHARACTER*(MAX_LEN_FNAM) delXFile
      CHARACTER*(MAX_LEN_FNAM) delYFile
      CHARACTER*(MAX_LEN_FNAM) horizGridFile
      CHARACTER*(MAX_LEN_FNAM) bathyFile, topoFile
      CHARACTER*(MAX_LEN_FNAM) hydrogThetaFile
      CHARACTER*(MAX_LEN_FNAM) hydrogSaltFile
      CHARACTER*(MAX_LEN_FNAM) zonalWindFile
      CHARACTER*(MAX_LEN_FNAM) meridWindFile
      CHARACTER*(MAX_LEN_FNAM) thetaClimFile
      CHARACTER*(MAX_LEN_FNAM) saltClimFile
      CHARACTER*(MAX_LEN_FNAM) surfQfile
      CHARACTER*(MAX_LEN_FNAM) surfQnetFile
      CHARACTER*(MAX_LEN_FNAM) surfQswFile
      CHARACTER*(MAX_LEN_FNAM) EmPmRfile
      CHARACTER*(MAX_LEN_FNAM) saltFluxFile
      CHARACTER*(MAX_LEN_FNAM) buoyancyRelation
      CHARACTER*(MAX_LEN_FNAM) uVelInitFile
      CHARACTER*(MAX_LEN_FNAM) vVelInitFile
      CHARACTER*(MAX_LEN_FNAM) pSurfInitFile
      CHARACTER*(MAX_LEN_FNAM) dQdTfile
      CHARACTER*(MAX_LEN_FNAM) ploadFile
      CHARACTER*(MAX_LEN_FNAM) eddyTauxFile
      CHARACTER*(MAX_LEN_FNAM) eddyTauyFile
      CHARACTER*(MAX_LEN_FNAM) lambdaThetaFile
      CHARACTER*(MAX_LEN_FNAM) lambdaSaltFile
      CHARACTER*(MAX_LEN_FNAM) mdsioLocalDir
      CHARACTER*(MAX_LEN_FNAM) the_run_name
      CHARACTER*(6) eosType
      CHARACTER*(10) pickupSuff
      INTEGER cg2dMaxIters
      INTEGER cg2dChkResFreq
      INTEGER cg2dPreCondFreq
      INTEGER cg3dMaxIters
      INTEGER cg3dChkResFreq
      INTEGER nIter0
      INTEGER nTimeSteps
      INTEGER nEndIter
      INTEGER numStepsPerPickup
      INTEGER writeStatePrec
      INTEGER writeBinaryPrec
      INTEGER readBinaryPrec
      INTEGER nCheckLev
      INTEGER nonlinFreeSurf
      INTEGER select_rStar
      INTEGER tempAdvScheme, tempVertAdvScheme
      INTEGER saltAdvScheme, saltVertAdvScheme
      INTEGER debugLevel
      INTEGER debLevZero
      PARAMETER(debLevZero=0)
      INTEGER debLevA
      PARAMETER(debLevA=1)
      INTEGER debLevB
      PARAMETER(debLevB=2)
      LOGICAL usingCartesianGrid
      LOGICAL usingSphericalPolarGrid
      LOGICAL usingCylindricalGrid
      LOGICAL usingCurvilinearGrid
      LOGICAL usingSphericalPolarMTerms
      LOGICAL useNHMTerms
      LOGICAL no_slip_sides
      LOGICAL no_slip_bottom
      LOGICAL staggerTimeStep
      LOGICAL momViscosity
      LOGICAL momAdvection
      LOGICAL momForcing
      LOGICAL momPressureForcing
      LOGICAL useCoriolis
      LOGICAL vectorInvariantMomentum
      LOGICAL tempAdvection
      LOGICAL tempForcing
      LOGICAL saltAdvection
      LOGICAL saltForcing
      LOGICAL useRealFreshWaterFlux
      LOGICAL useFullLeith, useAnisotropicViscAGridMax
      LOGICAL rigidLid
      LOGICAL implicitFreeSurface
      LOGICAL exactConserv
      LOGICAL uniformLin_PhiSurf
      LOGICAL momStepping
      LOGICAL tempStepping
      LOGICAL saltStepping
      LOGICAL metricTerms
      LOGICAL useConstantF
      LOGICAL useBetaPlaneF
      LOGICAL useSphereF
      LOGICAL useCDscheme
      LOGICAL useEnergyConservingCoriolis
      LOGICAL useJamartWetPoints
      LOGICAL useJamartMomAdv
      LOGICAL SadournyCoriolis
      LOGICAL upwindVorticity
      LOGICAL highOrderVorticity
      LOGICAL useAbsVorticity
      LOGICAL upwindShear
      LOGICAL implicitDiffusion
      LOGICAL implicitViscosity
      LOGICAL tempImplVertAdv 
      LOGICAL saltImplVertAdv 
      LOGICAL momImplVertAdv
      LOGICAL multiDimAdvection
      LOGICAL useMultiDimAdvec
      LOGICAL forcing_In_AB
      LOGICAL doThetaClimRelax
      LOGICAL doSaltClimRelax
      LOGICAL doTr1ClimRelax
      LOGICAL periodicExternalForcing
      LOGICAL fluidIsAir
      LOGICAL fluidIsWater
      LOGICAL usingPCoords
      LOGICAL usingZCoords
      LOGICAL useDynP_inEos_Zc
      LOGICAL setCenterDr
      LOGICAL nonHydrostatic
      LOGICAL quasiHydrostatic
      LOGICAL globalFiles
      LOGICAL useSingleCpuIO
      LOGICAL allowFreezing
      LOGICAL useOldFreezing
      LOGICAL usePickupBeforeC35
      LOGICAL usePickupBeforeC54
      LOGICAL startFromPickupAB2
      LOGICAL dumpInitAndLast
      LOGICAL debugMode
      LOGICAL pickup_read_mdsio, pickup_write_mdsio
      LOGICAL pickup_write_immed
      LOGICAL timeave_mdsio, snapshot_mdsio, monitor_stdio
      LOGICAL outputTypesInclusive
      LOGICAL inAdMode, inAdTrue, inAdFalse, inAdExact
      LOGICAL calendarDumps
      Real*8 nh_Am2
      Real*8 cg2dTargetResidual
      Real*8 cg2dTargetResWunit
      Real*8 cg3dTargetResidual
      Real*8 cg2dpcOffDFac
      Real*8 delR(Nr)
      Real*8 delRc(Nr+1)
      Real*8 delX(Nx)
      Real*8 delY(Ny)
      Real*8 deltaT
      Real*8 deltaTClock
      Real*8 deltaTmom
      Real*8 dTtracerLev(Nr)
      Real*8 deltaTfreesurf
      Real*8 abEps, alph_AB, beta_AB
      Real*8 phiMin
      Real*8 thetaMin
      Real*8 rSphere
      Real*8 recip_RSphere
      Real*8 f0
      Real*8 freeSurfFac
      Real*8 implicSurfPress
      Real*8 implicDiv2Dflow
      Real*8 hFacMin
      Real*8 hFacMinDz
      Real*8 hFacMinDp
      Real*8 hFacMinDr
      Real*8 hFacInf
      Real*8 hFacSup
      Real*8 beta
      Real*8 viscAh
      Real*8 viscAhW
      Real*8 viscAhD
      Real*8 viscAhZ
      Real*8 viscAhMax
      Real*8 viscAhGrid
      Real*8 viscAhGridMax
      Real*8 viscAhGridMin
      Real*8 viscC2leith
      Real*8 viscC2leithD
      Real*8 viscC2smag
      Real*8 viscAstrain
      Real*8 viscAtension
      Real*8 viscAr
      Real*8 viscA4 
      Real*8 viscA4W
      Real*8 viscA4D
      Real*8 viscA4Z
      Real*8 viscA4Max
      Real*8 viscA4Grid, viscA4GridMax, viscA4GridMin
      Real*8 viscC4leith
      Real*8 viscC4leithD
      Real*8 diffKhT 
      Real*8 diffKrNrT(Nr)
      Real*8 diffK4T 
      Real*8 diffKhS 
      Real*8 diffKrNrS(Nr)
      Real*8 diffK4S 
      Real*8 diffKrBL79surf
      Real*8 diffKrBL79deep
      Real*8 diffKrBL79scl
      Real*8 diffKrBL79Ho
      Real*8 delt
      Real*8 tauCD
      Real*8 rCD
      Real*8 gravity
      Real*8 recip_gravity
      Real*8 gBaro
      Real*8 rhonil
      Real*8 recip_rhonil
      Real*8 rhoConst
      Real*8 recip_rhoConst
      Real*8 rhoConstFresh
      Real*8 convertEmP2rUnit
      Real*8 tRef(Nr)
      Real*8 sRef(Nr)
      Real*8 baseTime
      Real*8 startTime
      Real*8 endTime
      Real*8 chkPtFreq
      Real*8 pChkPtFreq
      Real*8 dumpFreq
      Real*8 adjDumpFreq
      Real*8 diagFreq
      Real*8 taveFreq
      Real*8 tave_lastIter
      Real*8 monitorFreq
      Real*8 adjMonitorFreq
      Real*8 afFacMom
      Real*8 vfFacMom
      Real*8 pfFacMom
      Real*8 cfFacMom
      Real*8 foFacMom
      Real*8 mTFacMom
      Real*8 cosPower
      Real*8 cAdjFreq
      Real*8 omega
      Real*8 rotationPeriod
      Real*8 tauThetaClimRelax
      Real*8 tauSaltClimRelax
      Real*8 tauTr1ClimRelax
      Real*8 lambdaTr1ClimRelax
      Real*8 latBandClimRelax
      Real*8 externForcingCycle
      Real*8 externForcingPeriod
      Real*8 convertFW2Salt
      Real*8 temp_EvPrRn
      Real*8 salt_EvPrRn
      Real*8 horiVertRatio
      Real*8 recip_horiVertRatio
      Real*8 ivdc_kappa
      Real*8 Ro_SeaLevel
      Real*8 bottomDragLinear
      Real*8 bottomDragQuadratic
      Real*8 tCylIn
      Real*8 tCylOut
      Real*8 HeatCapacity_Cp
      Real*8 recip_Cp
      Real*8 celsius2K
      Real*8 atm_Po, atm_Cp, atm_Rd, atm_kappa, atm_Rq
      INTEGER integr_GeoPot, selectFindRoSurf
      LOGICAL useOPPS
      LOGICAL usePP81
      LOGICAL useMY82
      LOGICAL useGGL90
      LOGICAL useKPP
      LOGICAL useGMRedi
      LOGICAL useOBCS
      LOGICAL useAIM
      LOGICAL useLand
      LOGICAL useGrdchk
      LOGICAL useECCO
      LOGICAL useSHAP_FILT
      LOGICAL useZONAL_FILT
      LOGICAL useFLT
      LOGICAL usePTRACERS
      LOGICAL useGCHEM
      LOGICAL useSBO
      LOGICAL useSEAICE
      LOGICAL useBulkForce
      LOGICAL useThSIce
      LOGICAL usefizhi
      LOGICAL usegridalt
      LOGICAL usediagnostics
      LOGICAL useEBM
      LOGICAL useMNC
      LOGICAL useMATRIX
      LOGICAL useRunClock
      END MODULE PARAMS_mod
      MODULE BAR2_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      INTEGER BAR2_level(cacheLineSize/4,MAX_NO_THREADS)
      INTEGER BAR2_barrierCount(cacheLineSize/4,MAX_NO_THREADS)
      INTEGER BAR2_spinsCount(cacheLineSize/4,MAX_NO_THREADS)
      INTEGER BAR2_spinsMax(cacheLineSize/4,MAX_NO_THREADS)
      INTEGER BAR2_spinsMin(cacheLineSize/4,MAX_NO_THREADS)
      LOGICAL bar2CollectStatistics
      END MODULE BAR2_mod
      MODULE BARRIER_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      INTEGER key1(lShare4,MAX_NO_THREADS)
      INTEGER key2(lShare4,MAX_NO_THREADS)
      INTEGER key3(lShare4,MAX_NO_THREADS)
      INTEGER door1
      INTEGER door2
      INTEGER door3
      INTEGER VALID
      PARAMETER ( VALID = 1 )
      INTEGER INVALID
      PARAMETER ( INVALID = 0 )
      INTEGER OPEN
      PARAMETER ( OPEN = 1 )
      INTEGER SHUT
      PARAMETER ( SHUT = 0 )
      END MODULE BARRIER_mod
      MODULE CD_CODE_VARS_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  uVeld (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  vVeld (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  etaNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  uNm1  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  vNm1  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      END MODULE CD_CODE_VARS_mod
      MODULE CG2D_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      LOGICAL cg2dNormaliseRHS
      Real*8  aW2d (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  aS2d (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  pW   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  pS   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  pC   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  cg2dNorm, cg2dTolerance
      Real*8  cg2d_q(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  cg2d_r(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  cg2d_s(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE CG2D_mod
      MODULE CG3D_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE CG3D_mod
      MODULE DFILE_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE DFILE_mod
      MODULE DYNVARS_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  etaN  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  etaH  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  uVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  vVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  wVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  theta(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  salt (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gT(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gS(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  guNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gvNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gtNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gsNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  diffKr (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  phiHydLow(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  totPhiHyd(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  IVDConvCount(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      END MODULE DYNVARS_mod
      MODULE EEIO_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE EEIO_mod
      MODULE EESUPPORT_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      CHARACTER*(*) ERROR_HEADER
      PARAMETER ( ERROR_HEADER = ' *** ERROR ***' )
      CHARACTER*(*) PROCESS_HEADER
      PARAMETER ( PROCESS_HEADER = 'PID.TID' )
      INTEGER MAX_NUM_COMM_MODES
      PARAMETER ( MAX_NUM_COMM_MODES = 4 )
      INTEGER COMM_NONE
      PARAMETER ( COMM_NONE   =   1 )
      INTEGER COMM_MSG
      PARAMETER ( COMM_MSG    =   2 )
      INTEGER COMM_PUT
      PARAMETER ( COMM_PUT    =   3 )
      INTEGER COMM_GET
      PARAMETER ( COMM_GET    =   4 )
      CHARACTER*10 commName(MAX_NUM_COMM_MODES)
      INTEGER NULL_TILE
      PARAMETER ( NULL_TILE = -1 )
      CHARACTER*128 myProcessStr
      LOGICAL thError(MAX_NO_THREADS)
      LOGICAL threadIsRunning(MAX_NO_THREADS)
      LOGICAL threadIsComplete(MAX_NO_THREADS)
      LOGICAL allMyEdgesAreSharedMemory(MAX_NO_THREADS)
      LOGICAL usingMPI
      LOGICAL usingSyncMessages
      LOGICAL notUsingXPeriodicity
      LOGICAL notUsingYPeriodicity
      LOGICAL printMapIncludesZeros
      INTEGER myPid
      INTEGER nProcs
      INTEGER pidW
      INTEGER pidE
      INTEGER pidN
      INTEGER pidS
      INTEGER tileCommModeW ( nSx, nSy )
      INTEGER tileCommModeE ( nSx, nSy )
      INTEGER tileCommModeN ( nSx, nSy )
      INTEGER tileCommModeS ( nSx, nSy )
      INTEGER tileNo( nSx, nSy )
      INTEGER tileNoW( nSx, nSy )
      INTEGER tileNoE( nSx, nSy )
      INTEGER tileNoN( nSx, nSy )
      INTEGER tileNoS( nSx, nSy )
      INTEGER tilePidW( nSx, nSy )
      INTEGER tilePidE( nSx, nSy )
      INTEGER tilePidN( nSx, nSy )
      INTEGER tilePidS( nSx, nSy )
      INTEGER tileBiW( nSx, nSy )
      INTEGER tileBiE( nSx, nSy )
      INTEGER tileBiN( nSx, nSy )
      INTEGER tileBiS( nSx, nSy )
      INTEGER tileBjW( nSx, nSy )
      INTEGER tileBjE( nSx, nSy )
      INTEGER tileBjN( nSx, nSy )
      INTEGER tileBjS( nSx, nSy )
      INTEGER tileTagSendW( nSx, nSy )
      INTEGER tileTagSendE( nSx, nSy )
      INTEGER tileTagSendN( nSx, nSy )
      INTEGER tileTagSendS( nSx, nSy )
      INTEGER tileTagRecvW( nSx, nSy )
      INTEGER tileTagRecvE( nSx, nSy )
      INTEGER tileTagRecvN( nSx, nSy )
      INTEGER tileTagRecvS( nSx, nSy )
      END MODULE EESUPPORT_mod
      MODULE EOS_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 SItoBar, SItodBar
      PARAMETER ( SItoBar  = 1.D-05 )
      PARAMETER ( SItodBar = 1.D-04 )
      Real*8 tAlpha
      Real*8 sBeta
      character*(6) equationOfState
      Real*8 eosC(9,Nr+1),eosSig0(Nr+1),eosRefT(Nr+1),eosRefS(Nr+1)
      Real*8 eosJMDCFw(6), eosJMDCSw(9)
      Real*8 eosJMDCKFw(5), eosJMDCKSw(7), eosJMDCKP(14)
      Real*8 eosMDJWFnum(0:11), eosMDJWFden(0:12)
      END MODULE EOS_mod
      MODULE EXCH_JAM_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 exchBuf1(((sNx+2*OLx)*OLy)*Nr)
      Real*8 exchBuf2(((sNx+2*OLx)*OLy)*Nr)
      END MODULE EXCH_JAM_mod
      MODULE EXCH_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
       INTEGER MAX_OLX_EXCH
       PARAMETER ( MAX_OLX_EXCH = MAX_OLX )
       INTEGER MAX_OLY_EXCH
       PARAMETER ( MAX_OLY_EXCH = MAX_OLY )
       INTEGER MAX_NR_EXCH
       PARAMETER ( MAX_NR_EXCH  = nR + 1 )
       INTEGER NUMBER_OF_BUFFER_LEVELS
       PARAMETER ( NUMBER_OF_BUFFER_LEVELS = 1 )
       INTEGER EXCH_SPIN_LIMIT
       PARAMETER ( EXCH_SPIN_LIMIT = 100000000 )
       INTEGER L_BUFFERX
       PARAMETER ( L_BUFFERX = 
     &  (sNy+2*MAX_OLY_EXCH)*MAX_OLX_EXCH*MAX_NR_EXCH )
       INTEGER L_BUFFERY
       PARAMETER ( L_BUFFERY = 
     &  (sNx+2*MAX_OLX_EXCH)*MAX_OLY_EXCH*MAX_NR_EXCH )
       INTEGER L_WBUFFER
       INTEGER L_EBUFFER
       INTEGER L_SBUFFER
       INTEGER L_NBUFFER
       PARAMETER ( L_WBUFFER = L_BUFFERX,
     &             L_EBUFFER = L_BUFFERX,
     &             L_SBUFFER = L_BUFFERY,
     &             L_NBUFFER = L_BUFFERY )
       COMMON / EXCH_L / exchNeedsMemSync, exchUsesBarrier,
     &                   exchCollectStatistics
       LOGICAL exchNeedsMemSync
       LOGICAL exchUsesBarrier
       LOGICAL exchCollectStatistics
       COMMON / EXCH_R /
     &  westSendBuf_RL, eastSendBuf_RL, 
     &  southSendBuf_RL, northSendBuf_RL,
     &  westRecvBuf_RL, eastRecvBuf_RL, 
     &  southRecvBuf_RL, northRecvBuf_RL,
     &  westSendBuf_RS, eastSendBuf_RS, 
     &  southSendBuf_RS, northSendBuf_RS,
     &  westRecvBuf_RS, eastRecvBuf_RS, 
     &  southRecvBuf_RS, northRecvBuf_RS,
     &  westSendBuf_R8, eastSendBuf_R8, 
     &  southSendBuf_R8, northSendBuf_R8,
     &  westRecvBuf_R8, eastRecvBuf_R8, 
     &  southRecvBuf_R8, northRecvBuf_R8,
     &  westSendBuf_R4, eastSendBuf_R4, 
     &  southSendBuf_R4, northSendBuf_R4,
     &  westRecvBuf_R4, eastRecvBuf_R4, 
     &  southRecvBuf_R4, northRecvBuf_R4
       Real*8   westSendBuf_RL( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastSendBuf_RL( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southSendBuf_RL( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northSendBuf_RL( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westRecvBuf_RL( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastRecvBuf_RL( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southRecvBuf_RL( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northRecvBuf_RL( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westSendBuf_RS( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastSendBuf_RS( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southSendBuf_RS( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northSendBuf_RS( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westRecvBuf_RS( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastRecvBuf_RS( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southRecvBuf_RS( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northRecvBuf_RS( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westSendBuf_R8( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastSendBuf_R8( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southSendBuf_R8( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northSendBuf_R8( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westRecvBuf_R8( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastRecvBuf_R8( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southRecvBuf_R8( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northRecvBuf_R8( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4   westSendBuf_R4( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4   eastSendBuf_R4( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4  southSendBuf_R4( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4  northSendBuf_R4( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4   westRecvBuf_R4( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4   eastRecvBuf_R4( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4  southRecvBuf_R4( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4  northRecvBuf_R4( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       COMMON / EXCH_I /
     &  westSendAck, eastSendAck, southSendAck, northSendAck,
     &  westRecvAck, eastRecvAck, southRecvAck, northRecvAck,
     &  exchangeBufLevel,
     &  exchNReqsX, exchNReqsY, exchReqIdX, exchReqIdY,
     &  exchRecvXSpinCount, exchRecvXSpinMax, exchRecvXSpinMin,
     &  exchRecvXExchCount,
     &  exchRecvYSpinCount, exchRecvYSpinMax, exchRecvYSpinMin,
     &  exchRecvYExchCount
       INTEGER  westSendAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER  eastSendAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER southSendAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER northSendAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER  westRecvAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER  eastRecvAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER southRecvAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER northRecvAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER exchangeBufLevel(  cacheLineSize/4, nSx, nSy )
       INTEGER exchNReqsX(cacheLineSize/4,nSx,nSy)
       INTEGER exchNReqsY(cacheLineSize/4,nSx,nSy)
       INTEGER exchReqIdX(2*nSx+2*nSy,cacheLineSize/4,nSx,nSy)
       INTEGER exchReqIdY(2*nSx+2*nSy,cacheLineSize/4,nSx,nSy)
       INTEGER exchRecvXSpinCount(cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvXExchCount(cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvXSpinMax  (cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvXSpinMin  (cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvYSpinCount(cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvYExchCount(cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvYSpinMax  (cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvYSpinMin  (cacheLineSize/4, nSx, nSy)
      END MODULE EXCH_mod
      MODULE FC_NAMEMANGLE_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE FC_NAMEMANGLE_mod
      MODULE FFIELDS_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  fu       (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  fv       (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  Qnet     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  Qsw      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  dQdT     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  EmPmR    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  saltFlux (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SST      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SSS      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 lambdaThetaClimRelax(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 lambdaSaltClimRelax(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  taux0    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  tauy0    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  Qnet0    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  EmPmR0   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  saltFlux0(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SST0     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SSS0     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  taux1    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  tauy1    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  Qnet1    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  EmPmR1   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  saltFlux1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SST1     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SSS1     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingU   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingV   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingT   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingS   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingTice(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE FFIELDS_mod
      MODULE GAD_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      INTEGER ENUM_CENTERED_2ND
      PARAMETER(ENUM_CENTERED_2ND=2)
      INTEGER ENUM_UPWIND_3RD
      PARAMETER(ENUM_UPWIND_3RD=3)
      INTEGER ENUM_CENTERED_4TH
      PARAMETER(ENUM_CENTERED_4TH=4)
      INTEGER ENUM_FLUX_LIMIT
      PARAMETER(ENUM_FLUX_LIMIT=77)
      INTEGER ENUM_DST3
      PARAMETER(ENUM_DST3=30)
      INTEGER ENUM_DST3_FLUX_LIMIT
      PARAMETER(ENUM_DST3_FLUX_LIMIT=33)
      Real*8 oneSixth
      PARAMETER(oneSixth=1.d0/6.d0)
      INTEGER GAD_TEMPERATURE
      PARAMETER(GAD_TEMPERATURE=1)
      INTEGER GAD_SALINITY
      PARAMETER(GAD_SALINITY=2)
      INTEGER GAD_TR1
      PARAMETER(GAD_TR1=3)
      LOGICAL tempMultiDimAdvec
      LOGICAL saltMultiDimAdvec
      LOGICAL tr1_MultiDimAdvec
      LOGICAL tempAdamsBashforth
      LOGICAL saltAdamsBashforth
      LOGICAL tr1_AdamsBashforth
      END MODULE GAD_mod
      MODULE GLOBAL_MAX_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  phiGMRL(lShare8, MAX_NO_THREADS )
      Real*4  phiGMRS(lShare4, MAX_NO_THREADS )
      INTEGER phiGMI (lShare4, MAX_NO_THREADS )
      END MODULE GLOBAL_MAX_mod
      MODULE GLOBAL_SUM_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  phiGSRL(lShare8, MAX_NO_THREADS )
      Real*4  phiGSRS(lShare4, MAX_NO_THREADS )
      INTEGER phiGSI (lShare4, MAX_NO_THREADS )
      END MODULE GLOBAL_SUM_mod
      MODULE GRID_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      INTEGER klowC (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 cosfacU(1-Oly:sNy+Oly,nSx,nSy)
      Real*8 cosfacV(1-Oly:sNy+Oly,nSx,nSy)
      Real*8 sqcosfacU(1-Oly:sNy+Oly,nSx,nSy)
      Real*8 sqcosfacV(1-Oly:sNy+Oly,nSx,nSy)
      Real*8 gravitySign
      Real*8 rkSign
      Real*8 globalArea
      Real*8 dxC            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dxF            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dxG            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dxV            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dyC            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dyF            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dyG            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dyU            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 R_low          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 Ro_surf        (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 hFacC          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 hFacW          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 hFacS          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 recip_dxC      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dxF      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dxG      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dxV      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dyC      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dyF      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dyG      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dyU      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_Rcol     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_hFacC    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 recip_hFacW    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 recip_hFacS    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 xC             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 xG             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 yC             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 yG             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 rA             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 rAw            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 rAs            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 rAz            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_rA       (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_rAw      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_rAs      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_rAz      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 maskH          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 maskC          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 maskW          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 maskS          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 tanPhiAtU      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 tanPhiAtV      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 angleCosC      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 angleSinC      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 drC            (1:Nr)
      Real*8 drF            (1:Nr)
      Real*8 recip_drC      (1:Nr)
      Real*8 recip_drF      (1:Nr)
      Real*8 saFac          (1:Nr)
      Real*8 rC             (1:Nr)
      Real*8 rF             (1:Nr+1)
      Real*8 xC0
      Real*8 yC0
      Real*8 fCori(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 fCoriG(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 fCoriCos(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE GRID_mod
      MODULE GW_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE GW_mod
      MODULE MPI_INFO_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
       COMMON /MPI_INFO/
     &  mpi_pid,     mpi_np,
     &  mpi_northId, mpi_southId
       INTEGER mpi_pid
       INTEGER mpi_np
       INTEGER mpi_northId
       INTEGER mpi_southId
      END MODULE MPI_INFO_mod
      MODULE SOLVE_FOR_PRESSURE3D_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE SOLVE_FOR_PRESSURE3D_mod
      MODULE SOLVE_FOR_PRESSURE_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 cg2d_x(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 cg2d_b(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE SOLVE_FOR_PRESSURE_mod
      MODULE SURFACE_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  Bo_surf (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  recip_Bo(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  topoZ   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  phi0surf(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER ksurfC(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER ksurfW(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER ksurfS(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE SURFACE_mod
      MODULE tamc_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      integer nyears_chkpt
      integer nmonths_chkpt
      integer ndays_chkpt
      integer ngeom_chkpt
      integer ncheck_chkpt
      integer nthreads_chkpt
      parameter (nyears_chkpt   =          1 )
      parameter (nmonths_chkpt  =         12 )
      parameter (ndays_chkpt    =         31 )
      parameter (ngeom_chkpt    = nr*nsx*nsy )
      parameter (ncheck_chkpt   =          6 )
      parameter ( nthreads_chkpt = 1 )
      integer    nchklev_1
      parameter( nchklev_1      =     2 )
      integer    nchklev_2
      parameter( nchklev_2      =   240 )
      integer    nchklev_3
      parameter( nchklev_3      =    60 )
      integer ikey_dynamics
      integer ikey_yearly
      integer ikey_daily_1
      integer ikey_daily_2
      integer iloop_daily
      INTEGER    isbyte
      PARAMETER( isbyte      = 8 )
      INTEGER    maximpl
      PARAMETER( maximpl     = 6 )
      INTEGER    maxpass
      PARAMETER( maxpass     = 2 )
      INTEGER    maxcube
      PARAMETER( maxcube     = 1 )
      INTEGER act0, act1, act2, act3, act4
      INTEGER max0, max1, max2, max3
      INTEGER iikey, kkey, passkey, igadkey, 
     &        itdkey, idynkey, igmkey, ikppkey, iptrkey
      END MODULE tamc_mod
      MODULE tamc_keys_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      integer           key, ikey
      END MODULE tamc_keys_mod
      MODULE cost_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  fc
      Real*8  objf_atl  (nsx,nsy)
      Real*8  objf_test (nsx,nsy)
      Real*8  objf_tracer (nsx,nsy)
      Real*8  objf_entropy (nsx,nsy)
      Real*8  objf_t_misfit (nsx,nsy)
      Real*8  objf_eflux (nsx,nsy)
      Real*8 lastinterval
      Real*8  mult_atl
      Real*8  mult_test
      Real*8  mult_tracer
      Real*8  mult_entropy
      Real*8  mult_t_misfit
      Real*8  mult_eflux
      Real*8 cMeanTheta(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 cMeanUVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 cMeanVVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      END MODULE cost_mod
      MODULE g_cost_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  g_fc
      END MODULE g_cost_mod
      MODULE ctrl_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      integer     maxcvars
      parameter ( maxcvars = 40 )
      integer     ctrlprec
      parameter ( ctrlprec = 64 )
      logical doInitXX
      logical doAdmTlm
      logical doPackDiag
      logical doZscaleUnpack
      logical doZscalePack
      integer nvartype
      integer nvarlength
      integer ncvarindex    ( maxcvars )
      integer ncvarrecs     ( maxcvars )
      integer ncvarrecstart ( maxcvars )
      integer ncvarrecsend  ( maxcvars )
      integer ncvarxmax     ( maxcvars )
      integer ncvarymax     ( maxcvars )
      integer ncvarnrmax    ( maxcvars )
      integer nwetctile     ( nsx,nsy,nr )
      integer nwetstile     ( nsx,nsy,nr )
      integer nwetwtile     ( nsx,nsy,nr )
      integer nwetvtile     ( nsx,nsy,nr )
      integer nwetcglobal     ( nr )
      integer nwetsglobal     ( nr )
      integer nwetwglobal     ( nr )
      integer nwetvglobal     ( nr )
      integer nbuffglobal
      character*(1) ncvargrd(maxcvars)
      character*(2) yadprefix
      integer        filenvartype
      integer        filenvarlength
      integer        fileOptimCycle
      integer        filencbuffindex
      integer        fileIg
      integer        fileJg
      integer        fileI
      integer        fileJ
      integer        filensx
      integer        filensy
      integer        filek
      integer        filenWetcGlobal(nr)
      integer        filenWetsGlobal(nr)
      integer        filenWetwGlobal(nr)
      integer        filenWetvGlobal(nr)
      integer        filencvarindex(maxcvars)
      integer        filencvarrecs(maxcvars)
      integer        filencvarxmax(maxcvars)
      integer        filencvarymax(maxcvars)
      integer        filencvarnrmax(maxcvars)
      Real*8            filefc
      character*(10) fileYctrlid
      character*( 1) filencvargrd(maxcvars)
      Real*8 wunit   ( nr,nsx,nsy )
      Real*8 tmpfld2d 
     &    (1-olx:snx+olx,1-oly:sny+oly,nsx,nsy)
      Real*8 tmpfld3d 
     &    (1-olx:snx+olx,1-oly:sny+oly,nr,nsx,nsy)
      character*(MAX_LEN_FNAM) xx_theta_file
      character*(MAX_LEN_FNAM) xx_salt_file
      character*(MAX_LEN_FNAM) xx_hflux_file
      character*(MAX_LEN_FNAM) xx_sflux_file
      character*(MAX_LEN_FNAM) xx_tauu_file
      character*(MAX_LEN_FNAM) xx_tauv_file
      character*(MAX_LEN_FNAM) xx_atemp_file
      character*(MAX_LEN_FNAM) xx_aqh_file
      character*(MAX_LEN_FNAM) xx_precip_file
      character*(MAX_LEN_FNAM) xx_swflux_file
      character*(MAX_LEN_FNAM) xx_swdown_file
      character*(MAX_LEN_FNAM) xx_uwind_file
      character*(MAX_LEN_FNAM) xx_vwind_file
      character*(MAX_LEN_FNAM) xx_obcsn_file
      character*(MAX_LEN_FNAM) xx_obcss_file
      character*(MAX_LEN_FNAM) xx_obcsw_file
      character*(MAX_LEN_FNAM) xx_obcse_file
      character*(MAX_LEN_FNAM) xx_diffkr_file
      character*(MAX_LEN_FNAM) xx_kapgm_file
      character*(MAX_LEN_FNAM) xx_tr1_file
      character*(MAX_LEN_FNAM) xx_sst_file
      character*(MAX_LEN_FNAM) xx_sss_file
      character*(MAX_LEN_FNAM) xx_hfacc_file
      character*(MAX_LEN_FNAM) xx_efluxy_file
      character*(MAX_LEN_FNAM) xx_efluxp_file
      character*(MAX_LEN_FNAM) xx_bottomdrag_file
      character*(MAX_LEN_FNAM) xx_edtaux_file
      character*(MAX_LEN_FNAM) xx_edtauy_file
      character*(MAX_LEN_FNAM) xx_uvel_file
      character*(MAX_LEN_FNAM) xx_vvel_file
      character*(MAX_LEN_FNAM) xx_etan_file
      character*(MAX_LEN_FNAM) xx_relaxsst_file
      character*(MAX_LEN_FNAM) xx_relaxsss_file
      character*(MAX_LEN_FNAM) xx_theta_ini_fin_file
      character*(MAX_LEN_FNAM) xx_salt_ini_fin_file
      character*2 yadmark
      character*9 ctrlname
      character*9 costname
      character*9 scalname
      character*9 maskname
      character*9 metaname
      character*10 yctrlid
      character*4 yctrlposunpack
      character*4 yctrlpospack
      Real*8     xx_hfluxperiod
      Real*8     xx_sfluxperiod
      Real*8     xx_tauuperiod
      Real*8     xx_tauvperiod
      Real*8     xx_atempperiod
      Real*8     xx_aqhperiod
      Real*8     xx_precipperiod
      Real*8     xx_swfluxperiod
      Real*8     xx_swdownperiod
      Real*8     xx_uwindperiod
      Real*8     xx_vwindperiod
      Real*8     xx_obcsnperiod
      Real*8     xx_obcssperiod
      Real*8     xx_obcswperiod
      Real*8     xx_obcseperiod
      integer xx_hfluxstartdate1
      integer xx_hfluxstartdate2
      integer xx_sfluxstartdate1
      integer xx_sfluxstartdate2
      integer xx_tauustartdate1
      integer xx_tauustartdate2
      integer xx_tauvstartdate1
      integer xx_tauvstartdate2
      integer xx_atempstartdate1
      integer xx_atempstartdate2
      integer xx_aqhstartdate1
      integer xx_aqhstartdate2
      integer xx_precipstartdate1
      integer xx_precipstartdate2
      integer xx_swfluxstartdate1
      integer xx_swfluxstartdate2
      integer xx_swdownstartdate1
      integer xx_swdownstartdate2
      integer xx_uwindstartdate1
      integer xx_uwindstartdate2
      integer xx_vwindstartdate1
      integer xx_vwindstartdate2
      integer xx_obcsnstartdate1
      integer xx_obcsnstartdate2
      integer xx_obcssstartdate1
      integer xx_obcssstartdate2
      integer xx_obcswstartdate1
      integer xx_obcswstartdate2
      integer xx_obcsestartdate1
      integer xx_obcsestartdate2
      integer xx_hfluxstartdate(4)
      integer xx_sfluxstartdate(4)
      integer xx_tauustartdate(4)
      integer xx_tauvstartdate(4)
      integer xx_atempstartdate(4)
      integer xx_aqhstartdate(4)
      integer xx_precipstartdate(4)
      integer xx_swfluxstartdate(4)
      integer xx_swdownstartdate(4)
      integer xx_uwindstartdate(4)
      integer xx_vwindstartdate(4)
      integer xx_obcsnstartdate(4)
      integer xx_obcssstartdate(4)
      integer xx_obcswstartdate(4)
      integer xx_obcsestartdate(4)
      character*( 80)   fname_theta(2)
      character*( 80)   fname_salt(2)
      character*( 80)   fname_hflux(2)
      character*( 80)   fname_sflux(2)
      character*( 80)   fname_tauu(2)
      character*( 80)   fname_tauv(2)
      character*( 80)   fname_atemp(2)
      character*( 80)   fname_aqh(2)
      character*( 80)   fname_precip(2)
      character*( 80)   fname_swflux(2)
      character*( 80)   fname_swdown(2)
      character*( 80)   fname_uwind(2)
      character*( 80)   fname_vwind(2)
      character*( 80)   fname_obcsn(2)
      character*( 80)   fname_obcss(2)
      character*( 80)   fname_obcsw(2)
      character*( 80)   fname_obcse(2)
      character*( 80)   fname_diffkr(2)
      character*( 80)   fname_kapgm(2)
      character*( 80)   fname_tr1(2)
      character*( 80)   fname_sst(2)
      character*( 80)   fname_sss(2)
      character*( 80)   fname_hfacc(2)
      character*( 80)   fname_efluxy(2)
      character*( 80)   fname_efluxp(2)
      character*( 80)   fname_bottomdrag(2)
      character*( 80)   fname_edtaux(2)
      character*( 80)   fname_edtauy(2)
      character*( 80)   fname_uvel(2)
      character*( 80)   fname_vvel(2)
      character*( 80)   fname_etan(2)
      character*( 80)   fname_relaxsst(2)
      character*( 80)   fname_relaxsss(2)
      END MODULE ctrl_mod
      MODULE ctrl_dummy_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 xx_theta_dummy
      Real*8 xx_salt_dummy
      Real*8 xx_hflux_dummy
      Real*8 xx_sflux_dummy
      Real*8 xx_tauu_dummy
      Real*8 xx_tauv_dummy
      Real*8 xx_atemp_dummy
      Real*8 xx_aqh_dummy
      Real*8 xx_precip_dummy
      Real*8 xx_swflux_dummy
      Real*8 xx_swdown_dummy
      Real*8 xx_uwind_dummy
      Real*8 xx_vwind_dummy
      Real*8 xx_obcsn_dummy
      Real*8 xx_obcss_dummy
      Real*8 xx_obcsw_dummy
      Real*8 xx_obcse_dummy
      Real*8 xx_diffkr_dummy
      Real*8 xx_kapgm_dummy
      Real*8 xx_tr1_dummy
      Real*8 xx_sst_dummy
      Real*8 xx_sss_dummy
      Real*8 xx_hfacc_dummy
      Real*8 xx_efluxy_dummy
      Real*8 xx_efluxp_dummy
      Real*8 xx_bottomdrag_dummy
      Real*8 xx_edtaux_dummy
      Real*8 xx_edtauy_dummy
      Real*8 xx_uvel_dummy
      Real*8 xx_vvel_dummy
      Real*8 xx_etan_dummy
      Real*8 xx_relaxsst_dummy
      Real*8 xx_relaxsss_dummy
      Real*8 xx_tbar_mean_dummy
      Real*8 xx_sbar_mean_dummy
      Real*8 xx_ubar_mean_dummy
      Real*8 xx_vbar_mean_dummy
      Real*8 xx_wbar_mean_dummy
      Real*8 xx_psbar_mean_dummy
      Real*8 xx_hflux_mean_dummy
      Real*8 xx_sflux_mean_dummy
      Real*8 xx_taux_mean_dummy
      Real*8 xx_tauy_mean_dummy
      Real*8 xx_atemp_mean_dummy
      Real*8 xx_aqh_mean_dummy
      Real*8 xx_precip_mean_dummy
      Real*8 xx_swflux_mean_dummy
      Real*8 xx_swdown_mean_dummy
      Real*8 xx_uwind_mean_dummy
      Real*8 xx_vwind_mean_dummy
      Real*8 xx_theta_ini_fin_dummy
      Real*8 xx_salt_ini_fin_dummy
      END MODULE ctrl_dummy_mod
      MODULE ctrl_weights_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 wtheta   ( nr,nsx,nsy )
      Real*8 wsalt    ( nr,nsx,nsy )
      END MODULE ctrl_weights_mod
      MODULE optim_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      character*(5)  lsoptversion
      parameter    ( lsoptversion = '2.1.0' )
      character*(5)  offlineversion
      parameter    ( offlineversion = '0.1.1' )
      integer optimcycle
      integer nvars
      integer numiter
      integer nfunc
      integer iprint
      integer nupdate
      Real*8 epsf
      Real*8 epsx
      Real*8 fmin
      Real*8 epsg
      Real*8 eps
      logical nondimcontrol
      character*( 3) copt
      END MODULE optim_mod
      MODULE grdchk_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      integer     maxgrdchecks
      parameter ( maxgrdchecks = 4000 )
      Real*8     grdchk_eps
      logical useCentralDiff
      integer nbeg
      integer nend
      integer nstep
      integer grdchkvarindex
      integer grdchkwhichproc
      integer iGloPos
      integer jGloPos
      integer kGloPos
      integer obcsglo
      integer recglo
      Real*8 fcrmem      ( maxgrdchecks )
      Real*8 fcppmem     ( maxgrdchecks )
      Real*8 fcpmmem     ( maxgrdchecks )
      Real*8 xxmemref    ( maxgrdchecks )
      Real*8 xxmempert   ( maxgrdchecks )
      Real*8 gfdmem      ( maxgrdchecks )
      Real*8 adxxmem     ( maxgrdchecks )
      Real*8 ftlxxmem    ( maxgrdchecks )
      Real*8 ratioadmem  ( maxgrdchecks )
      Real*8 ratioftlmem ( maxgrdchecks )
      integer ncvarcomp
      integer maxncvarcomps
      integer nwettile( nsx,nsy,nr,nobcs )
      integer irecmem ( maxgrdchecks )
      integer bjmem   ( maxgrdchecks )
      integer bimem   ( maxgrdchecks )
      integer klocmem ( maxgrdchecks )
      integer iobcsmem( maxgrdchecks )
      integer jlocmem ( maxgrdchecks )
      integer ilocmem ( maxgrdchecks )
      integer ichkmem ( maxgrdchecks )
      integer icompmem( maxgrdchecks )
      integer itestmem( maxgrdchecks )
      integer ierrmem ( maxgrdchecks )
      END MODULE grdchk_mod
      MODULE SIZE_mod
      INTEGER sNx
      INTEGER sNy
      INTEGER OLx
      INTEGER OLy
      INTEGER nSx
      INTEGER nSy
      INTEGER nPx
      INTEGER nPy
      INTEGER Nx
      INTEGER Ny
      INTEGER Nr
      PARAMETER (
     &           sNx =  90,
     &           sNy =  40,
     &           OLx =   3,
     &           OLy =   3,
     &           nSx =   1,
     &           nSy =   1,
     &           nPx =   1,
     &           nPy =   1,
     &           Nx  = sNx*nSx*nPx,
     &           Ny  = sNy*nSy*nPy,
     &           Nr  =  15)
      INTEGER MAX_OLX
      INTEGER MAX_OLY
      PARAMETER ( MAX_OLX = OLx,
     &            MAX_OLY = OLy )
      integer     nobcs
      parameter ( nobcs = 4 )
      END MODULE SIZE_mod
      MODULE EEPARAMS_mod
      use SIZE_mod
      INTEGER MAX_LEN_MBUF
      PARAMETER ( MAX_LEN_MBUF = 512 )
      INTEGER MAX_LEN_FNAM
      PARAMETER ( MAX_LEN_FNAM = 512 )
      INTEGER MAX_LEN_PREC
      PARAMETER ( MAX_LEN_PREC = 200 )
      CHARACTER*(*) SQUEEZE_RIGHT
      PARAMETER ( SQUEEZE_RIGHT = 'R' )
      CHARACTER*(*) SQUEEZE_LEFT
      PARAMETER ( SQUEEZE_LEFT = 'L' )
      CHARACTER*(*) SQUEEZE_BOTH
      PARAMETER ( SQUEEZE_BOTH = 'B' )
      CHARACTER*(*) PRINT_MAP_XY
      PARAMETER ( PRINT_MAP_XY = 'XY' )
      CHARACTER*(*) PRINT_MAP_XZ
      PARAMETER ( PRINT_MAP_XZ = 'XZ' )
      CHARACTER*(*) PRINT_MAP_YZ
      PARAMETER ( PRINT_MAP_YZ = 'YZ' )
      CHARACTER*(*) commentCharacter
      PARAMETER ( commentCharacter = '#' )
      INTEGER INDEX_I
      INTEGER INDEX_J
      INTEGER INDEX_K   
      INTEGER INDEX_NONE
      PARAMETER ( INDEX_I    = 1,
     &            INDEX_J    = 2,
     &            INDEX_K    = 3,
     &            INDEX_NONE = 4 )
      INTEGER EXCH_IGNORE_CORNERS
      INTEGER EXCH_UPDATE_CORNERS
      PARAMETER ( EXCH_IGNORE_CORNERS = 0,
     &            EXCH_UPDATE_CORNERS = 1 )
      INTEGER FORWARD_SIMULATION
      INTEGER REVERSE_SIMULATION
      INTEGER TANGENT_SIMULATION
      PARAMETER ( FORWARD_SIMULATION = 0,
     &            REVERSE_SIMULATION = 1,
     &            TANGENT_SIMULATION = 2 )
      INTEGER cacheLineSize
      INTEGER lShare1
      INTEGER lShare4
      INTEGER lShare8
      PARAMETER ( cacheLineSize = 256 )
      PARAMETER ( lShare1 =  cacheLineSize )
      PARAMETER ( lShare4 =  cacheLineSize/4 )
      PARAMETER ( lShare8 =  cacheLineSize/8 )
      INTEGER MAX_NO_THREADS
      PARAMETER ( MAX_NO_THREADS =   32 )
      INTEGER MAX_NO_PROCS
      PARAMETER ( MAX_NO_PROCS   =  2048 )
      INTEGER MAX_NO_BARRIERS
      PARAMETER ( MAX_NO_BARRIERS = 1 )
      LOGICAL eeBootError
      LOGICAL eeEndError
      LOGICAL fatalError
      LOGICAL useCubedSphereExchange
      LOGICAL useCoupler
      INTEGER eeDataUnit
      INTEGER errorMessageUnit
      INTEGER ioErrorCount(MAX_NO_THREADS)
      INTEGER modelDataUnit
      INTEGER myBxLo(MAX_NO_THREADS)
      INTEGER myBxHi(MAX_NO_THREADS)
      INTEGER myByLo(MAX_NO_THREADS)
      INTEGER myByHi(MAX_NO_THREADS)
      INTEGER myProcId
      INTEGER myPx
      INTEGER myPy
      INTEGER myXGlobalLo
      INTEGER myYGlobalLo
      INTEGER nThreads
      INTEGER nTx
      INTEGER nTy
      INTEGER numberOfProcs
      INTEGER pidIO
      INTEGER scrUnit1
      INTEGER scrUnit2
      INTEGER standardMessageUnit
      END MODULE EEPARAMS_mod
      MODULE PARAMS_mod
      use SIZE_mod
      use EEPARAMS_mod
      Real*8 PI
      PARAMETER ( PI    = 3.14159265358979323844d0   )
      Real*8 deg2rad
      PARAMETER ( deg2rad = 2.d0*PI/360.d0           )
      INTEGER precFloat32
      PARAMETER ( precFloat32 = 32 )
      INTEGER precFloat64
      PARAMETER ( precFloat64 = 64 )
      Real*8 UNSET_FLOAT8
      PARAMETER ( UNSET_FLOAT8 = 1.234567D5 )
      Real*4 UNSET_FLOAT4
      PARAMETER ( UNSET_FLOAT4 = 1.234567E5 )
      Real*8    UNSET_RL    
      PARAMETER ( UNSET_RL     = 1.234567D5 )
      Real*8    UNSET_RS     
      PARAMETER ( UNSET_RS     = 1.234567E5 )
      INTEGER UNSET_I
      PARAMETER ( UNSET_I      = 123456789  )
      INTEGER maxNoChkptLev
      PARAMETER ( maxNoChkptLev = 2 )
      CHARACTER*(5) checkPtSuff(maxNoChkptLev)
      CHARACTER*(MAX_LEN_FNAM) delXFile
      CHARACTER*(MAX_LEN_FNAM) delYFile
      CHARACTER*(MAX_LEN_FNAM) horizGridFile
      CHARACTER*(MAX_LEN_FNAM) bathyFile, topoFile
      CHARACTER*(MAX_LEN_FNAM) hydrogThetaFile
      CHARACTER*(MAX_LEN_FNAM) hydrogSaltFile
      CHARACTER*(MAX_LEN_FNAM) zonalWindFile
      CHARACTER*(MAX_LEN_FNAM) meridWindFile
      CHARACTER*(MAX_LEN_FNAM) thetaClimFile
      CHARACTER*(MAX_LEN_FNAM) saltClimFile
      CHARACTER*(MAX_LEN_FNAM) surfQfile
      CHARACTER*(MAX_LEN_FNAM) surfQnetFile
      CHARACTER*(MAX_LEN_FNAM) surfQswFile
      CHARACTER*(MAX_LEN_FNAM) EmPmRfile
      CHARACTER*(MAX_LEN_FNAM) saltFluxFile
      CHARACTER*(MAX_LEN_FNAM) buoyancyRelation
      CHARACTER*(MAX_LEN_FNAM) uVelInitFile
      CHARACTER*(MAX_LEN_FNAM) vVelInitFile
      CHARACTER*(MAX_LEN_FNAM) pSurfInitFile
      CHARACTER*(MAX_LEN_FNAM) dQdTfile
      CHARACTER*(MAX_LEN_FNAM) ploadFile
      CHARACTER*(MAX_LEN_FNAM) eddyTauxFile
      CHARACTER*(MAX_LEN_FNAM) eddyTauyFile
      CHARACTER*(MAX_LEN_FNAM) lambdaThetaFile
      CHARACTER*(MAX_LEN_FNAM) lambdaSaltFile
      CHARACTER*(MAX_LEN_FNAM) mdsioLocalDir
      CHARACTER*(MAX_LEN_FNAM) the_run_name
      CHARACTER*(6) eosType
      CHARACTER*(10) pickupSuff
      INTEGER cg2dMaxIters
      INTEGER cg2dChkResFreq
      INTEGER cg2dPreCondFreq
      INTEGER cg3dMaxIters
      INTEGER cg3dChkResFreq
      INTEGER nIter0
      INTEGER nTimeSteps
      INTEGER nEndIter
      INTEGER numStepsPerPickup
      INTEGER writeStatePrec
      INTEGER writeBinaryPrec
      INTEGER readBinaryPrec
      INTEGER nCheckLev
      INTEGER nonlinFreeSurf
      INTEGER select_rStar
      INTEGER tempAdvScheme, tempVertAdvScheme
      INTEGER saltAdvScheme, saltVertAdvScheme
      INTEGER debugLevel
      INTEGER debLevZero
      PARAMETER(debLevZero=0)
      INTEGER debLevA
      PARAMETER(debLevA=1)
      INTEGER debLevB
      PARAMETER(debLevB=2)
      LOGICAL usingCartesianGrid
      LOGICAL usingSphericalPolarGrid
      LOGICAL usingCylindricalGrid
      LOGICAL usingCurvilinearGrid
      LOGICAL usingSphericalPolarMTerms
      LOGICAL useNHMTerms
      LOGICAL no_slip_sides
      LOGICAL no_slip_bottom
      LOGICAL staggerTimeStep
      LOGICAL momViscosity
      LOGICAL momAdvection
      LOGICAL momForcing
      LOGICAL momPressureForcing
      LOGICAL useCoriolis
      LOGICAL vectorInvariantMomentum
      LOGICAL tempAdvection
      LOGICAL tempForcing
      LOGICAL saltAdvection
      LOGICAL saltForcing
      LOGICAL useRealFreshWaterFlux
      LOGICAL useFullLeith, useAnisotropicViscAGridMax
      LOGICAL rigidLid
      LOGICAL implicitFreeSurface
      LOGICAL exactConserv
      LOGICAL uniformLin_PhiSurf
      LOGICAL momStepping
      LOGICAL tempStepping
      LOGICAL saltStepping
      LOGICAL metricTerms
      LOGICAL useConstantF
      LOGICAL useBetaPlaneF
      LOGICAL useSphereF
      LOGICAL useCDscheme
      LOGICAL useEnergyConservingCoriolis
      LOGICAL useJamartWetPoints
      LOGICAL useJamartMomAdv
      LOGICAL SadournyCoriolis
      LOGICAL upwindVorticity
      LOGICAL highOrderVorticity
      LOGICAL useAbsVorticity
      LOGICAL upwindShear
      LOGICAL implicitDiffusion
      LOGICAL implicitViscosity
      LOGICAL tempImplVertAdv 
      LOGICAL saltImplVertAdv 
      LOGICAL momImplVertAdv
      LOGICAL multiDimAdvection
      LOGICAL useMultiDimAdvec
      LOGICAL forcing_In_AB
      LOGICAL doThetaClimRelax
      LOGICAL doSaltClimRelax
      LOGICAL doTr1ClimRelax
      LOGICAL periodicExternalForcing
      LOGICAL fluidIsAir
      LOGICAL fluidIsWater
      LOGICAL usingPCoords
      LOGICAL usingZCoords
      LOGICAL useDynP_inEos_Zc
      LOGICAL setCenterDr
      LOGICAL nonHydrostatic
      LOGICAL quasiHydrostatic
      LOGICAL globalFiles
      LOGICAL useSingleCpuIO
      LOGICAL allowFreezing
      LOGICAL useOldFreezing
      LOGICAL usePickupBeforeC35
      LOGICAL usePickupBeforeC54
      LOGICAL startFromPickupAB2
      LOGICAL dumpInitAndLast
      LOGICAL debugMode
      LOGICAL pickup_read_mdsio, pickup_write_mdsio
      LOGICAL pickup_write_immed
      LOGICAL timeave_mdsio, snapshot_mdsio, monitor_stdio
      LOGICAL outputTypesInclusive
      LOGICAL inAdMode, inAdTrue, inAdFalse, inAdExact
      LOGICAL calendarDumps
      Real*8 nh_Am2
      Real*8 cg2dTargetResidual
      Real*8 cg2dTargetResWunit
      Real*8 cg3dTargetResidual
      Real*8 cg2dpcOffDFac
      Real*8 delR(Nr)
      Real*8 delRc(Nr+1)
      Real*8 delX(Nx)
      Real*8 delY(Ny)
      Real*8 deltaT
      Real*8 deltaTClock
      Real*8 deltaTmom
      Real*8 dTtracerLev(Nr)
      Real*8 deltaTfreesurf
      Real*8 abEps, alph_AB, beta_AB
      Real*8 phiMin
      Real*8 thetaMin
      Real*8 rSphere
      Real*8 recip_RSphere
      Real*8 f0
      Real*8 freeSurfFac
      Real*8 implicSurfPress
      Real*8 implicDiv2Dflow
      Real*8 hFacMin
      Real*8 hFacMinDz
      Real*8 hFacMinDp
      Real*8 hFacMinDr
      Real*8 hFacInf
      Real*8 hFacSup
      Real*8 beta
      Real*8 viscAh
      Real*8 viscAhW
      Real*8 viscAhD
      Real*8 viscAhZ
      Real*8 viscAhMax
      Real*8 viscAhGrid
      Real*8 viscAhGridMax
      Real*8 viscAhGridMin
      Real*8 viscC2leith
      Real*8 viscC2leithD
      Real*8 viscC2smag
      Real*8 viscAstrain
      Real*8 viscAtension
      Real*8 viscAr
      Real*8 viscA4 
      Real*8 viscA4W
      Real*8 viscA4D
      Real*8 viscA4Z
      Real*8 viscA4Max
      Real*8 viscA4Grid, viscA4GridMax, viscA4GridMin
      Real*8 viscC4leith
      Real*8 viscC4leithD
      Real*8 diffKhT 
      Real*8 diffKrNrT(Nr)
      Real*8 diffK4T 
      Real*8 diffKhS 
      Real*8 diffKrNrS(Nr)
      Real*8 diffK4S 
      Real*8 diffKrBL79surf
      Real*8 diffKrBL79deep
      Real*8 diffKrBL79scl
      Real*8 diffKrBL79Ho
      Real*8 delt
      Real*8 tauCD
      Real*8 rCD
      Real*8 gravity
      Real*8 recip_gravity
      Real*8 gBaro
      Real*8 rhonil
      Real*8 recip_rhonil
      Real*8 rhoConst
      Real*8 recip_rhoConst
      Real*8 rhoConstFresh
      Real*8 convertEmP2rUnit
      Real*8 tRef(Nr)
      Real*8 sRef(Nr)
      Real*8 baseTime
      Real*8 startTime
      Real*8 endTime
      Real*8 chkPtFreq
      Real*8 pChkPtFreq
      Real*8 dumpFreq
      Real*8 adjDumpFreq
      Real*8 diagFreq
      Real*8 taveFreq
      Real*8 tave_lastIter
      Real*8 monitorFreq
      Real*8 adjMonitorFreq
      Real*8 afFacMom
      Real*8 vfFacMom
      Real*8 pfFacMom
      Real*8 cfFacMom
      Real*8 foFacMom
      Real*8 mTFacMom
      Real*8 cosPower
      Real*8 cAdjFreq
      Real*8 omega
      Real*8 rotationPeriod
      Real*8 tauThetaClimRelax
      Real*8 tauSaltClimRelax
      Real*8 tauTr1ClimRelax
      Real*8 lambdaTr1ClimRelax
      Real*8 latBandClimRelax
      Real*8 externForcingCycle
      Real*8 externForcingPeriod
      Real*8 convertFW2Salt
      Real*8 temp_EvPrRn
      Real*8 salt_EvPrRn
      Real*8 horiVertRatio
      Real*8 recip_horiVertRatio
      Real*8 ivdc_kappa
      Real*8 Ro_SeaLevel
      Real*8 bottomDragLinear
      Real*8 bottomDragQuadratic
      Real*8 tCylIn
      Real*8 tCylOut
      Real*8 HeatCapacity_Cp
      Real*8 recip_Cp
      Real*8 celsius2K
      Real*8 atm_Po, atm_Cp, atm_Rd, atm_kappa, atm_Rq
      INTEGER integr_GeoPot, selectFindRoSurf
      LOGICAL useOPPS
      LOGICAL usePP81
      LOGICAL useMY82
      LOGICAL useGGL90
      LOGICAL useKPP
      LOGICAL useGMRedi
      LOGICAL useOBCS
      LOGICAL useAIM
      LOGICAL useLand
      LOGICAL useGrdchk
      LOGICAL useECCO
      LOGICAL useSHAP_FILT
      LOGICAL useZONAL_FILT
      LOGICAL useFLT
      LOGICAL usePTRACERS
      LOGICAL useGCHEM
      LOGICAL useSBO
      LOGICAL useSEAICE
      LOGICAL useBulkForce
      LOGICAL useThSIce
      LOGICAL usefizhi
      LOGICAL usegridalt
      LOGICAL usediagnostics
      LOGICAL useEBM
      LOGICAL useMNC
      LOGICAL useMATRIX
      LOGICAL useRunClock
      END MODULE PARAMS_mod
      MODULE BAR2_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      INTEGER BAR2_level(cacheLineSize/4,MAX_NO_THREADS)
      INTEGER BAR2_barrierCount(cacheLineSize/4,MAX_NO_THREADS)
      INTEGER BAR2_spinsCount(cacheLineSize/4,MAX_NO_THREADS)
      INTEGER BAR2_spinsMax(cacheLineSize/4,MAX_NO_THREADS)
      INTEGER BAR2_spinsMin(cacheLineSize/4,MAX_NO_THREADS)
      LOGICAL bar2CollectStatistics
      END MODULE BAR2_mod
      MODULE BARRIER_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      INTEGER key1(lShare4,MAX_NO_THREADS)
      INTEGER key2(lShare4,MAX_NO_THREADS)
      INTEGER key3(lShare4,MAX_NO_THREADS)
      INTEGER door1
      INTEGER door2
      INTEGER door3
      INTEGER VALID
      PARAMETER ( VALID = 1 )
      INTEGER INVALID
      PARAMETER ( INVALID = 0 )
      INTEGER OPEN
      PARAMETER ( OPEN = 1 )
      INTEGER SHUT
      PARAMETER ( SHUT = 0 )
      END MODULE BARRIER_mod
      MODULE CD_CODE_VARS_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  uVeld (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  vVeld (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  etaNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  uNm1  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  vNm1  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      END MODULE CD_CODE_VARS_mod
      MODULE CG2D_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      LOGICAL cg2dNormaliseRHS
      Real*8  aW2d (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  aS2d (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  pW   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  pS   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  pC   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  cg2dNorm, cg2dTolerance
      Real*8  cg2d_q(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  cg2d_r(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  cg2d_s(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE CG2D_mod
      MODULE CG3D_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE CG3D_mod
      MODULE cost_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  fc
      Real*8  objf_atl  (nsx,nsy)
      Real*8  objf_test (nsx,nsy)
      Real*8  objf_tracer (nsx,nsy)
      Real*8  objf_entropy (nsx,nsy)
      Real*8  objf_t_misfit (nsx,nsy)
      Real*8  objf_eflux (nsx,nsy)
      Real*8 lastinterval
      Real*8  mult_atl
      Real*8  mult_test
      Real*8  mult_tracer
      Real*8  mult_entropy
      Real*8  mult_t_misfit
      Real*8  mult_eflux
      Real*8 cMeanTheta(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 cMeanUVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 cMeanVVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      END MODULE cost_mod
      MODULE ctrl_dummy_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 xx_theta_dummy
      Real*8 xx_salt_dummy
      Real*8 xx_hflux_dummy
      Real*8 xx_sflux_dummy
      Real*8 xx_tauu_dummy
      Real*8 xx_tauv_dummy
      Real*8 xx_atemp_dummy
      Real*8 xx_aqh_dummy
      Real*8 xx_precip_dummy
      Real*8 xx_swflux_dummy
      Real*8 xx_swdown_dummy
      Real*8 xx_uwind_dummy
      Real*8 xx_vwind_dummy
      Real*8 xx_obcsn_dummy
      Real*8 xx_obcss_dummy
      Real*8 xx_obcsw_dummy
      Real*8 xx_obcse_dummy
      Real*8 xx_diffkr_dummy
      Real*8 xx_kapgm_dummy
      Real*8 xx_tr1_dummy
      Real*8 xx_sst_dummy
      Real*8 xx_sss_dummy
      Real*8 xx_hfacc_dummy
      Real*8 xx_efluxy_dummy
      Real*8 xx_efluxp_dummy
      Real*8 xx_bottomdrag_dummy
      Real*8 xx_edtaux_dummy
      Real*8 xx_edtauy_dummy
      Real*8 xx_uvel_dummy
      Real*8 xx_vvel_dummy
      Real*8 xx_etan_dummy
      Real*8 xx_relaxsst_dummy
      Real*8 xx_relaxsss_dummy
      Real*8 xx_tbar_mean_dummy
      Real*8 xx_sbar_mean_dummy
      Real*8 xx_ubar_mean_dummy
      Real*8 xx_vbar_mean_dummy
      Real*8 xx_wbar_mean_dummy
      Real*8 xx_psbar_mean_dummy
      Real*8 xx_hflux_mean_dummy
      Real*8 xx_sflux_mean_dummy
      Real*8 xx_taux_mean_dummy
      Real*8 xx_tauy_mean_dummy
      Real*8 xx_atemp_mean_dummy
      Real*8 xx_aqh_mean_dummy
      Real*8 xx_precip_mean_dummy
      Real*8 xx_swflux_mean_dummy
      Real*8 xx_swdown_mean_dummy
      Real*8 xx_uwind_mean_dummy
      Real*8 xx_vwind_mean_dummy
      Real*8 xx_theta_ini_fin_dummy
      Real*8 xx_salt_ini_fin_dummy
      END MODULE ctrl_dummy_mod
      MODULE ctrl_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      integer     maxcvars
      parameter ( maxcvars = 40 )
      integer     ctrlprec
      parameter ( ctrlprec = 64 )
      logical doInitXX
      logical doAdmTlm
      logical doPackDiag
      logical doZscaleUnpack
      logical doZscalePack
      integer nvartype
      integer nvarlength
      integer ncvarindex    ( maxcvars )
      integer ncvarrecs     ( maxcvars )
      integer ncvarrecstart ( maxcvars )
      integer ncvarrecsend  ( maxcvars )
      integer ncvarxmax     ( maxcvars )
      integer ncvarymax     ( maxcvars )
      integer ncvarnrmax    ( maxcvars )
      integer nwetctile     ( nsx,nsy,nr )
      integer nwetstile     ( nsx,nsy,nr )
      integer nwetwtile     ( nsx,nsy,nr )
      integer nwetvtile     ( nsx,nsy,nr )
      integer nwetcglobal     ( nr )
      integer nwetsglobal     ( nr )
      integer nwetwglobal     ( nr )
      integer nwetvglobal     ( nr )
      integer nbuffglobal
      character*(1) ncvargrd(maxcvars)
      character*(2) yadprefix
      integer        filenvartype
      integer        filenvarlength
      integer        fileOptimCycle
      integer        filencbuffindex
      integer        fileIg
      integer        fileJg
      integer        fileI
      integer        fileJ
      integer        filensx
      integer        filensy
      integer        filek
      integer        filenWetcGlobal(nr)
      integer        filenWetsGlobal(nr)
      integer        filenWetwGlobal(nr)
      integer        filenWetvGlobal(nr)
      integer        filencvarindex(maxcvars)
      integer        filencvarrecs(maxcvars)
      integer        filencvarxmax(maxcvars)
      integer        filencvarymax(maxcvars)
      integer        filencvarnrmax(maxcvars)
      Real*8            filefc
      character*(10) fileYctrlid
      character*( 1) filencvargrd(maxcvars)
      Real*8 wunit   ( nr,nsx,nsy )
      Real*8 tmpfld2d 
     &    (1-olx:snx+olx,1-oly:sny+oly,nsx,nsy)
      Real*8 tmpfld3d 
     &    (1-olx:snx+olx,1-oly:sny+oly,nr,nsx,nsy)
      character*(MAX_LEN_FNAM) xx_theta_file
      character*(MAX_LEN_FNAM) xx_salt_file
      character*(MAX_LEN_FNAM) xx_hflux_file
      character*(MAX_LEN_FNAM) xx_sflux_file
      character*(MAX_LEN_FNAM) xx_tauu_file
      character*(MAX_LEN_FNAM) xx_tauv_file
      character*(MAX_LEN_FNAM) xx_atemp_file
      character*(MAX_LEN_FNAM) xx_aqh_file
      character*(MAX_LEN_FNAM) xx_precip_file
      character*(MAX_LEN_FNAM) xx_swflux_file
      character*(MAX_LEN_FNAM) xx_swdown_file
      character*(MAX_LEN_FNAM) xx_uwind_file
      character*(MAX_LEN_FNAM) xx_vwind_file
      character*(MAX_LEN_FNAM) xx_obcsn_file
      character*(MAX_LEN_FNAM) xx_obcss_file
      character*(MAX_LEN_FNAM) xx_obcsw_file
      character*(MAX_LEN_FNAM) xx_obcse_file
      character*(MAX_LEN_FNAM) xx_diffkr_file
      character*(MAX_LEN_FNAM) xx_kapgm_file
      character*(MAX_LEN_FNAM) xx_tr1_file
      character*(MAX_LEN_FNAM) xx_sst_file
      character*(MAX_LEN_FNAM) xx_sss_file
      character*(MAX_LEN_FNAM) xx_hfacc_file
      character*(MAX_LEN_FNAM) xx_efluxy_file
      character*(MAX_LEN_FNAM) xx_efluxp_file
      character*(MAX_LEN_FNAM) xx_bottomdrag_file
      character*(MAX_LEN_FNAM) xx_edtaux_file
      character*(MAX_LEN_FNAM) xx_edtauy_file
      character*(MAX_LEN_FNAM) xx_uvel_file
      character*(MAX_LEN_FNAM) xx_vvel_file
      character*(MAX_LEN_FNAM) xx_etan_file
      character*(MAX_LEN_FNAM) xx_relaxsst_file
      character*(MAX_LEN_FNAM) xx_relaxsss_file
      character*(MAX_LEN_FNAM) xx_theta_ini_fin_file
      character*(MAX_LEN_FNAM) xx_salt_ini_fin_file
      character*2 yadmark
      character*9 ctrlname
      character*9 costname
      character*9 scalname
      character*9 maskname
      character*9 metaname
      character*10 yctrlid
      character*4 yctrlposunpack
      character*4 yctrlpospack
      Real*8     xx_hfluxperiod
      Real*8     xx_sfluxperiod
      Real*8     xx_tauuperiod
      Real*8     xx_tauvperiod
      Real*8     xx_atempperiod
      Real*8     xx_aqhperiod
      Real*8     xx_precipperiod
      Real*8     xx_swfluxperiod
      Real*8     xx_swdownperiod
      Real*8     xx_uwindperiod
      Real*8     xx_vwindperiod
      Real*8     xx_obcsnperiod
      Real*8     xx_obcssperiod
      Real*8     xx_obcswperiod
      Real*8     xx_obcseperiod
      integer xx_hfluxstartdate1
      integer xx_hfluxstartdate2
      integer xx_sfluxstartdate1
      integer xx_sfluxstartdate2
      integer xx_tauustartdate1
      integer xx_tauustartdate2
      integer xx_tauvstartdate1
      integer xx_tauvstartdate2
      integer xx_atempstartdate1
      integer xx_atempstartdate2
      integer xx_aqhstartdate1
      integer xx_aqhstartdate2
      integer xx_precipstartdate1
      integer xx_precipstartdate2
      integer xx_swfluxstartdate1
      integer xx_swfluxstartdate2
      integer xx_swdownstartdate1
      integer xx_swdownstartdate2
      integer xx_uwindstartdate1
      integer xx_uwindstartdate2
      integer xx_vwindstartdate1
      integer xx_vwindstartdate2
      integer xx_obcsnstartdate1
      integer xx_obcsnstartdate2
      integer xx_obcssstartdate1
      integer xx_obcssstartdate2
      integer xx_obcswstartdate1
      integer xx_obcswstartdate2
      integer xx_obcsestartdate1
      integer xx_obcsestartdate2
      integer xx_hfluxstartdate(4)
      integer xx_sfluxstartdate(4)
      integer xx_tauustartdate(4)
      integer xx_tauvstartdate(4)
      integer xx_atempstartdate(4)
      integer xx_aqhstartdate(4)
      integer xx_precipstartdate(4)
      integer xx_swfluxstartdate(4)
      integer xx_swdownstartdate(4)
      integer xx_uwindstartdate(4)
      integer xx_vwindstartdate(4)
      integer xx_obcsnstartdate(4)
      integer xx_obcssstartdate(4)
      integer xx_obcswstartdate(4)
      integer xx_obcsestartdate(4)
      character*( 80)   fname_theta(2)
      character*( 80)   fname_salt(2)
      character*( 80)   fname_hflux(2)
      character*( 80)   fname_sflux(2)
      character*( 80)   fname_tauu(2)
      character*( 80)   fname_tauv(2)
      character*( 80)   fname_atemp(2)
      character*( 80)   fname_aqh(2)
      character*( 80)   fname_precip(2)
      character*( 80)   fname_swflux(2)
      character*( 80)   fname_swdown(2)
      character*( 80)   fname_uwind(2)
      character*( 80)   fname_vwind(2)
      character*( 80)   fname_obcsn(2)
      character*( 80)   fname_obcss(2)
      character*( 80)   fname_obcsw(2)
      character*( 80)   fname_obcse(2)
      character*( 80)   fname_diffkr(2)
      character*( 80)   fname_kapgm(2)
      character*( 80)   fname_tr1(2)
      character*( 80)   fname_sst(2)
      character*( 80)   fname_sss(2)
      character*( 80)   fname_hfacc(2)
      character*( 80)   fname_efluxy(2)
      character*( 80)   fname_efluxp(2)
      character*( 80)   fname_bottomdrag(2)
      character*( 80)   fname_edtaux(2)
      character*( 80)   fname_edtauy(2)
      character*( 80)   fname_uvel(2)
      character*( 80)   fname_vvel(2)
      character*( 80)   fname_etan(2)
      character*( 80)   fname_relaxsst(2)
      character*( 80)   fname_relaxsss(2)
      END MODULE ctrl_mod
      MODULE ctrl_weights_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 wtheta   ( nr,nsx,nsy )
      Real*8 wsalt    ( nr,nsx,nsy )
      END MODULE ctrl_weights_mod
      MODULE DFILE_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE DFILE_mod
      MODULE DYNVARS_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  etaN  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  etaH  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  uVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  vVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  wVel (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  theta(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  salt (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gT(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gS(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  guNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gvNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gtNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gsNm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  diffKr (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  phiHydLow(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  totPhiHyd(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  IVDConvCount(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      END MODULE DYNVARS_mod
      MODULE EEIO_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE EEIO_mod
      MODULE EESUPPORT_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      CHARACTER*(*) ERROR_HEADER
      PARAMETER ( ERROR_HEADER = ' *** ERROR ***' )
      CHARACTER*(*) PROCESS_HEADER
      PARAMETER ( PROCESS_HEADER = 'PID.TID' )
      INTEGER MAX_NUM_COMM_MODES
      PARAMETER ( MAX_NUM_COMM_MODES = 4 )
      INTEGER COMM_NONE
      PARAMETER ( COMM_NONE   =   1 )
      INTEGER COMM_MSG
      PARAMETER ( COMM_MSG    =   2 )
      INTEGER COMM_PUT
      PARAMETER ( COMM_PUT    =   3 )
      INTEGER COMM_GET
      PARAMETER ( COMM_GET    =   4 )
      CHARACTER*10 commName(MAX_NUM_COMM_MODES)
      INTEGER NULL_TILE
      PARAMETER ( NULL_TILE = -1 )
      CHARACTER*128 myProcessStr
      LOGICAL thError(MAX_NO_THREADS)
      LOGICAL threadIsRunning(MAX_NO_THREADS)
      LOGICAL threadIsComplete(MAX_NO_THREADS)
      LOGICAL allMyEdgesAreSharedMemory(MAX_NO_THREADS)
      LOGICAL usingMPI
      LOGICAL usingSyncMessages
      LOGICAL notUsingXPeriodicity
      LOGICAL notUsingYPeriodicity
      LOGICAL printMapIncludesZeros
      INTEGER myPid
      INTEGER nProcs
      INTEGER pidW
      INTEGER pidE
      INTEGER pidN
      INTEGER pidS
      INTEGER tileCommModeW ( nSx, nSy )
      INTEGER tileCommModeE ( nSx, nSy )
      INTEGER tileCommModeN ( nSx, nSy )
      INTEGER tileCommModeS ( nSx, nSy )
      INTEGER tileNo( nSx, nSy )
      INTEGER tileNoW( nSx, nSy )
      INTEGER tileNoE( nSx, nSy )
      INTEGER tileNoN( nSx, nSy )
      INTEGER tileNoS( nSx, nSy )
      INTEGER tilePidW( nSx, nSy )
      INTEGER tilePidE( nSx, nSy )
      INTEGER tilePidN( nSx, nSy )
      INTEGER tilePidS( nSx, nSy )
      INTEGER tileBiW( nSx, nSy )
      INTEGER tileBiE( nSx, nSy )
      INTEGER tileBiN( nSx, nSy )
      INTEGER tileBiS( nSx, nSy )
      INTEGER tileBjW( nSx, nSy )
      INTEGER tileBjE( nSx, nSy )
      INTEGER tileBjN( nSx, nSy )
      INTEGER tileBjS( nSx, nSy )
      INTEGER tileTagSendW( nSx, nSy )
      INTEGER tileTagSendE( nSx, nSy )
      INTEGER tileTagSendN( nSx, nSy )
      INTEGER tileTagSendS( nSx, nSy )
      INTEGER tileTagRecvW( nSx, nSy )
      INTEGER tileTagRecvE( nSx, nSy )
      INTEGER tileTagRecvN( nSx, nSy )
      INTEGER tileTagRecvS( nSx, nSy )
      END MODULE EESUPPORT_mod
      MODULE EOS_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 SItoBar, SItodBar
      PARAMETER ( SItoBar  = 1.D-05 )
      PARAMETER ( SItodBar = 1.D-04 )
      Real*8 tAlpha
      Real*8 sBeta
      character*(6) equationOfState
      Real*8 eosC(9,Nr+1),eosSig0(Nr+1),eosRefT(Nr+1),eosRefS(Nr+1)
      Real*8 eosJMDCFw(6), eosJMDCSw(9)
      Real*8 eosJMDCKFw(5), eosJMDCKSw(7), eosJMDCKP(14)
      Real*8 eosMDJWFnum(0:11), eosMDJWFden(0:12)
      END MODULE EOS_mod
      MODULE EXCH_JAM_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 exchBuf1(((sNx+2*OLx)*OLy)*Nr)
      Real*8 exchBuf2(((sNx+2*OLx)*OLy)*Nr)
      END MODULE EXCH_JAM_mod
      MODULE EXCH_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
       INTEGER MAX_OLX_EXCH
       PARAMETER ( MAX_OLX_EXCH = MAX_OLX )
       INTEGER MAX_OLY_EXCH
       PARAMETER ( MAX_OLY_EXCH = MAX_OLY )
       INTEGER MAX_NR_EXCH
       PARAMETER ( MAX_NR_EXCH  = nR + 1 )
       INTEGER NUMBER_OF_BUFFER_LEVELS
       PARAMETER ( NUMBER_OF_BUFFER_LEVELS = 1 )
       INTEGER EXCH_SPIN_LIMIT
       PARAMETER ( EXCH_SPIN_LIMIT = 100000000 )
       INTEGER L_BUFFERX
       PARAMETER ( L_BUFFERX = 
     &  (sNy+2*MAX_OLY_EXCH)*MAX_OLX_EXCH*MAX_NR_EXCH )
       INTEGER L_BUFFERY
       PARAMETER ( L_BUFFERY = 
     &  (sNx+2*MAX_OLX_EXCH)*MAX_OLY_EXCH*MAX_NR_EXCH )
       INTEGER L_WBUFFER
       INTEGER L_EBUFFER
       INTEGER L_SBUFFER
       INTEGER L_NBUFFER
       PARAMETER ( L_WBUFFER = L_BUFFERX,
     &             L_EBUFFER = L_BUFFERX,
     &             L_SBUFFER = L_BUFFERY,
     &             L_NBUFFER = L_BUFFERY )
       COMMON / EXCH_L / exchNeedsMemSync, exchUsesBarrier,
     &                   exchCollectStatistics
       LOGICAL exchNeedsMemSync
       LOGICAL exchUsesBarrier
       LOGICAL exchCollectStatistics
       COMMON / EXCH_R /
     &  westSendBuf_RL, eastSendBuf_RL, 
     &  southSendBuf_RL, northSendBuf_RL,
     &  westRecvBuf_RL, eastRecvBuf_RL, 
     &  southRecvBuf_RL, northRecvBuf_RL,
     &  westSendBuf_RS, eastSendBuf_RS, 
     &  southSendBuf_RS, northSendBuf_RS,
     &  westRecvBuf_RS, eastRecvBuf_RS, 
     &  southRecvBuf_RS, northRecvBuf_RS,
     &  westSendBuf_R8, eastSendBuf_R8, 
     &  southSendBuf_R8, northSendBuf_R8,
     &  westRecvBuf_R8, eastRecvBuf_R8, 
     &  southRecvBuf_R8, northRecvBuf_R8,
     &  westSendBuf_R4, eastSendBuf_R4, 
     &  southSendBuf_R4, northSendBuf_R4,
     &  westRecvBuf_R4, eastRecvBuf_R4, 
     &  southRecvBuf_R4, northRecvBuf_R4
       Real*8   westSendBuf_RL( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastSendBuf_RL( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southSendBuf_RL( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northSendBuf_RL( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westRecvBuf_RL( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastRecvBuf_RL( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southRecvBuf_RL( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northRecvBuf_RL( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westSendBuf_RS( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastSendBuf_RS( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southSendBuf_RS( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northSendBuf_RS( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westRecvBuf_RS( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastRecvBuf_RS( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southRecvBuf_RS( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northRecvBuf_RS( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westSendBuf_R8( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastSendBuf_R8( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southSendBuf_R8( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northSendBuf_R8( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   westRecvBuf_R8( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8   eastRecvBuf_R8( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  southRecvBuf_R8( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*8  northRecvBuf_R8( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4   westSendBuf_R4( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4   eastSendBuf_R4( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4  southSendBuf_R4( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4  northSendBuf_R4( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4   westRecvBuf_R4( L_WBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4   eastRecvBuf_R4( L_EBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4  southRecvBuf_R4( L_SBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       Real*4  northRecvBuf_R4( L_NBUFFER, NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       COMMON / EXCH_I /
     &  westSendAck, eastSendAck, southSendAck, northSendAck,
     &  westRecvAck, eastRecvAck, southRecvAck, northRecvAck,
     &  exchangeBufLevel,
     &  exchNReqsX, exchNReqsY, exchReqIdX, exchReqIdY,
     &  exchRecvXSpinCount, exchRecvXSpinMax, exchRecvXSpinMin,
     &  exchRecvXExchCount,
     &  exchRecvYSpinCount, exchRecvYSpinMax, exchRecvYSpinMin,
     &  exchRecvYExchCount
       INTEGER  westSendAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER  eastSendAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER southSendAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER northSendAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER  westRecvAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER  eastRecvAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER southRecvAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER northRecvAck(            NUMBER_OF_BUFFER_LEVELS, 
     &                       nSx, nSy )
       INTEGER exchangeBufLevel(  cacheLineSize/4, nSx, nSy )
       INTEGER exchNReqsX(cacheLineSize/4,nSx,nSy)
       INTEGER exchNReqsY(cacheLineSize/4,nSx,nSy)
       INTEGER exchReqIdX(2*nSx+2*nSy,cacheLineSize/4,nSx,nSy)
       INTEGER exchReqIdY(2*nSx+2*nSy,cacheLineSize/4,nSx,nSy)
       INTEGER exchRecvXSpinCount(cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvXExchCount(cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvXSpinMax  (cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvXSpinMin  (cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvYSpinCount(cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvYExchCount(cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvYSpinMax  (cacheLineSize/4, nSx, nSy)
       INTEGER exchRecvYSpinMin  (cacheLineSize/4, nSx, nSy)
      END MODULE EXCH_mod
      MODULE FC_NAMEMANGLE_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE FC_NAMEMANGLE_mod
      MODULE FFIELDS_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  fu       (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  fv       (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  Qnet     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  Qsw      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  dQdT     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  EmPmR    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  saltFlux (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SST      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SSS      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 lambdaThetaClimRelax(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 lambdaSaltClimRelax(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  taux0    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  tauy0    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  Qnet0    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  EmPmR0   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  saltFlux0(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SST0     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SSS0     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  taux1    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  tauy1    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  Qnet1    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  EmPmR1   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  saltFlux1(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SST1     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  SSS1     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingU   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingV   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingT   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingS   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  surfaceForcingTice(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE FFIELDS_mod
      MODULE GAD_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      INTEGER ENUM_CENTERED_2ND
      PARAMETER(ENUM_CENTERED_2ND=2)
      INTEGER ENUM_UPWIND_3RD
      PARAMETER(ENUM_UPWIND_3RD=3)
      INTEGER ENUM_CENTERED_4TH
      PARAMETER(ENUM_CENTERED_4TH=4)
      INTEGER ENUM_FLUX_LIMIT
      PARAMETER(ENUM_FLUX_LIMIT=77)
      INTEGER ENUM_DST3
      PARAMETER(ENUM_DST3=30)
      INTEGER ENUM_DST3_FLUX_LIMIT
      PARAMETER(ENUM_DST3_FLUX_LIMIT=33)
      Real*8 oneSixth
      PARAMETER(oneSixth=1.d0/6.d0)
      INTEGER GAD_TEMPERATURE
      PARAMETER(GAD_TEMPERATURE=1)
      INTEGER GAD_SALINITY
      PARAMETER(GAD_SALINITY=2)
      INTEGER GAD_TR1
      PARAMETER(GAD_TR1=3)
      LOGICAL tempMultiDimAdvec
      LOGICAL saltMultiDimAdvec
      LOGICAL tr1_MultiDimAdvec
      LOGICAL tempAdamsBashforth
      LOGICAL saltAdamsBashforth
      LOGICAL tr1_AdamsBashforth
      END MODULE GAD_mod
      MODULE g_cost_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  g_fc
      END MODULE g_cost_mod
      MODULE GLOBAL_MAX_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  phiGMRL(lShare8, MAX_NO_THREADS )
      Real*4  phiGMRS(lShare4, MAX_NO_THREADS )
      INTEGER phiGMI (lShare4, MAX_NO_THREADS )
      END MODULE GLOBAL_MAX_mod
      MODULE GLOBAL_SUM_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  phiGSRL(lShare8, MAX_NO_THREADS )
      Real*4  phiGSRS(lShare4, MAX_NO_THREADS )
      INTEGER phiGSI (lShare4, MAX_NO_THREADS )
      END MODULE GLOBAL_SUM_mod
      MODULE grdchk_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      integer     maxgrdchecks
      parameter ( maxgrdchecks = 4000 )
      Real*8     grdchk_eps
      logical useCentralDiff
      integer nbeg
      integer nend
      integer nstep
      integer grdchkvarindex
      integer grdchkwhichproc
      integer iGloPos
      integer jGloPos
      integer kGloPos
      integer obcsglo
      integer recglo
      Real*8 fcrmem      ( maxgrdchecks )
      Real*8 fcppmem     ( maxgrdchecks )
      Real*8 fcpmmem     ( maxgrdchecks )
      Real*8 xxmemref    ( maxgrdchecks )
      Real*8 xxmempert   ( maxgrdchecks )
      Real*8 gfdmem      ( maxgrdchecks )
      Real*8 adxxmem     ( maxgrdchecks )
      Real*8 ftlxxmem    ( maxgrdchecks )
      Real*8 ratioadmem  ( maxgrdchecks )
      Real*8 ratioftlmem ( maxgrdchecks )
      integer ncvarcomp
      integer maxncvarcomps
      integer nwettile( nsx,nsy,nr,nobcs )
      integer irecmem ( maxgrdchecks )
      integer bjmem   ( maxgrdchecks )
      integer bimem   ( maxgrdchecks )
      integer klocmem ( maxgrdchecks )
      integer iobcsmem( maxgrdchecks )
      integer jlocmem ( maxgrdchecks )
      integer ilocmem ( maxgrdchecks )
      integer ichkmem ( maxgrdchecks )
      integer icompmem( maxgrdchecks )
      integer itestmem( maxgrdchecks )
      integer ierrmem ( maxgrdchecks )
      END MODULE grdchk_mod
      MODULE GRID_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      INTEGER klowC (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 cosfacU(1-Oly:sNy+Oly,nSx,nSy)
      Real*8 cosfacV(1-Oly:sNy+Oly,nSx,nSy)
      Real*8 sqcosfacU(1-Oly:sNy+Oly,nSx,nSy)
      Real*8 sqcosfacV(1-Oly:sNy+Oly,nSx,nSy)
      Real*8 gravitySign
      Real*8 rkSign
      Real*8 globalArea
      Real*8 dxC            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dxF            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dxG            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dxV            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dyC            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dyF            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dyG            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 dyU            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 R_low          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 Ro_surf        (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 hFacC          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 hFacW          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 hFacS          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 recip_dxC      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dxF      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dxG      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dxV      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dyC      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dyF      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dyG      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_dyU      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_Rcol     (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_hFacC    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 recip_hFacW    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 recip_hFacS    (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 xC             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 xG             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 yC             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 yG             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 rA             (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 rAw            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 rAs            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 rAz            (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_rA       (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_rAw      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_rAs      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 recip_rAz      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 maskH          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 maskC          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 maskW          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 maskS          (1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:Nr,nSx,nSy)
      Real*8 tanPhiAtU      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 tanPhiAtV      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 angleCosC      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 angleSinC      (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 drC            (1:Nr)
      Real*8 drF            (1:Nr)
      Real*8 recip_drC      (1:Nr)
      Real*8 recip_drF      (1:Nr)
      Real*8 saFac          (1:Nr)
      Real*8 rC             (1:Nr)
      Real*8 rF             (1:Nr+1)
      Real*8 xC0
      Real*8 yC0
      Real*8 fCori(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 fCoriG(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 fCoriCos(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE GRID_mod
      MODULE GW_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE GW_mod
      MODULE MPI_INFO_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
       COMMON /MPI_INFO/
     &  mpi_pid,     mpi_np,
     &  mpi_northId, mpi_southId
       INTEGER mpi_pid
       INTEGER mpi_np
       INTEGER mpi_northId
       INTEGER mpi_southId
      END MODULE MPI_INFO_mod
      MODULE optim_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      character*(5)  lsoptversion
      parameter    ( lsoptversion = '2.1.0' )
      character*(5)  offlineversion
      parameter    ( offlineversion = '0.1.1' )
      integer optimcycle
      integer nvars
      integer numiter
      integer nfunc
      integer iprint
      integer nupdate
      Real*8 epsf
      Real*8 epsx
      Real*8 fmin
      Real*8 epsg
      Real*8 eps
      logical nondimcontrol
      character*( 3) copt
      END MODULE optim_mod
      MODULE SOLVE_FOR_PRESSURE3D_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      END MODULE SOLVE_FOR_PRESSURE3D_mod
      MODULE SOLVE_FOR_PRESSURE_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8 cg2d_x(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 cg2d_b(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE SOLVE_FOR_PRESSURE_mod
      MODULE SURFACE_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      Real*8  Bo_surf (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  recip_Bo(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  topoZ   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8  phi0surf(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER ksurfC(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER ksurfW(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER ksurfS(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      END MODULE SURFACE_mod
      MODULE tamc_keys_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      integer           key, ikey
      END MODULE tamc_keys_mod
      MODULE tamc_mod
      use SIZE_mod
      use EEPARAMS_mod
      use PARAMS_mod
      integer nyears_chkpt
      integer nmonths_chkpt
      integer ndays_chkpt
      integer ngeom_chkpt
      integer ncheck_chkpt
      integer nthreads_chkpt
      parameter (nyears_chkpt   =          1 )
      parameter (nmonths_chkpt  =         12 )
      parameter (ndays_chkpt    =         31 )
      parameter (ngeom_chkpt    = nr*nsx*nsy )
      parameter (ncheck_chkpt   =          6 )
      parameter ( nthreads_chkpt = 1 )
      integer    nchklev_1
      parameter( nchklev_1      =     2 )
      integer    nchklev_2
      parameter( nchklev_2      =   240 )
      integer    nchklev_3
      parameter( nchklev_3      =    60 )
      integer ikey_dynamics
      integer ikey_yearly
      integer ikey_daily_1
      integer ikey_daily_2
      integer iloop_daily
      INTEGER    isbyte
      PARAMETER( isbyte      = 8 )
      INTEGER    maximpl
      PARAMETER( maximpl     = 6 )
      INTEGER    maxpass
      PARAMETER( maxpass     = 2 )
      INTEGER    maxcube
      PARAMETER( maxcube     = 1 )
      INTEGER act0, act1, act2, act3, act4
      INTEGER max0, max1, max2, max3
      INTEGER iikey, kkey, passkey, igadkey, 
     &        itdkey, idynkey, igmkey, ikppkey, iptrkey
      END MODULE tamc_mod
      SUBROUTINE CD_CODE_SCHEME( 
     I        bi,bj,k, dPhiHydX,dPhiHydY, guFld,gvFld,
     O        guCor,gvCor,
     I        myTime, myIter, myThid)
       USE SIZE_mod
       USE DYNVARS_mod
       USE CD_CODE_VARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER bi,bj,k
      Real*8 dPhiHydX(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 dPhiHydY(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8    guFld(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8    gvFld(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8    guCor(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8    gvCor(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8     myTime
      INTEGER myIter
      INTEGER myThid
      Real*8 pF(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vF(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 aF(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,iMin,iMax,jMin,jMax
      Real*8 ab15,ab05
      Real*8 phxFac, phyFac
      iMin=1-Olx+1
      iMax=sNx+Olx-1
      jMin=1-Oly+1
      jMax=sNy+Oly-1
      ab15   =  1.5 + abEps
      ab05   = -0.5 - abEps
      IF (staggerTimeStep) THEN
        phxFac = pfFacMom
        phyFac = pfFacMom
      ELSE
        phxFac = 0.
        phyFac = 0.
      ENDIF
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        pf(i,j) = 
     &   ab15*(  etaN(i,j,bi,bj)*Bo_surf(i,j,bi,bj) )
     &  +ab05*(etaNm1(i,j,bi,bj)*Bo_surf(i,j,bi,bj) )
       ENDDO
      ENDDO
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx,sNx+Olx
        af(i,j) =
     &        (  gvFld(i,j)
     &          -( recip_dyC(i,j,bi,bj)*(pf(i,j)-pf(i,j-1))
     &            +phyFac*dPhiHydY(i,j) )
     &        )*maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        vf(i,j) =      
     &    0.25*( af(i  ,j)+af(i  ,j+1)
     &          +af(i-1,j)+af(i-1,j+1)
     &         )*maskW(i,j,k,bi,bj)
     &   -0.5*(fCori(i,j,bi,bj)+
     &         fCori(i-1,j,bi,bj))
     &         *uVel(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        vVelD(i,j,k,bi,bj) = vVelD(i,j,k,bi,bj) + deltaTmom*vf(i,j)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
         vVelD(i,j,k,bi,bj) = ( rCD*vVelD(i,j,k,bi,bj)
     &   +(1. - rCD)*(
     &            ab15*( 
     &                vVel(i  ,j  ,k,bi,bj)+vVel(i  ,j+1,k,bi,bj)
     &               +vVel(i-1,j  ,k,bi,bj)+vVel(i-1,j+1,k,bi,bj)
     &                 )*0.25
     &           +ab05*( 
     &                vNM1(i  ,j  ,k,bi,bj)+vNM1(i  ,j+1,k,bi,bj)
     &               +vNM1(i-1,j  ,k,bi,bj)+vNM1(i-1,j+1,k,bi,bj)
     &                 )*0.25
     &               )        )*maskW(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        guCor(i,j) = 
     &    0.5*( fCori(i  ,j,bi,bj) + 
     &          fCori(i-1,j,bi,bj)  )
     &   *vVelD(i,j,k,bi,bj)*cfFacMom
       ENDDO
      ENDDO
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        af(i,j) =
     &        (  guFld(i,j)
     &          -( recip_dxC(i,j,bi,bj)*(pf(i,j)-pf(i-1,j))
     &            +phxFac*dPhiHydX(i,j) )
     &        )*maskW(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        vf(i,j) =
     &    0.25*( af(i  ,j)+af(i  ,j-1)
     &          +af(i+1,j)+af(i+1,j-1)
     &         )*maskS(i,j,k,bi,bj)
     &   +0.5*( fCori(i,j,bi,bj)
     &         +fCori(i,j-1,bi,bj))
     &         *vVel(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        uVelD(i,j,k,bi,bj) = uVelD(i,j,k,bi,bj) + deltaTmom*vf(i,j)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
         uVelD(i,j,k,bi,bj) = ( rCD*uVelD(i,j,k,bi,bj) 
     &   +(1. - rCD)*(
     &            ab15*( 
     &                uVel(i,j  ,k,bi,bj)+uVel(i+1,j  ,k,bi,bj)
     &               +uVel(i,j-1,k,bi,bj)+uVel(i+1,j-1,k,bi,bj)
     &                 )*0.25
     &           +ab05*( 
     &                uNM1(i,j  ,k,bi,bj)+uNM1(i+1,j  ,k,bi,bj)
     &               +uNM1(i,j-1,k,bi,bj)+uNM1(i+1,j-1,k,bi,bj)
     &                 )*0.25
     &               )        )*maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        gvCor(i,j) =
     &    -0.5*( fCori(i  ,j,bi,bj) 
     &          +fCori(i,j-1,bi,bj)  )
     &   *uVelD(i,j,k,bi,bj)*cfFacMom
       ENDDO
      ENDDO
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
         uNM1(i,j,k,bi,bj) =  uVel(i,j,k,bi,bj)
         vNM1(i,j,k,bi,bj) =  vVel(i,j,k,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CD_CODE_INI_VARS( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE CD_CODE_VARS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER  I,  J, K
      CHARACTER*(MAX_LEN_FNAM) fn
      CHARACTER*(10) suff
      INTEGER prec
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO K=1,Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           uNM1(I,J,K,bi,bj)=0.d0
           vNM1(I,J,K,bi,bj)=0.d0
           uVeld(I,J,K,bi,bj)=0.d0
           vVeld(I,J,K,bi,bj)=0.d0
          ENDDO
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          etaNm1(I,J,bi,bj)=0.d0
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF ( nIter0.NE.0 ) THEN
        CALL CD_CODE_READ_CHECKPOINT( nIter0, myThid )
      ENDIF
      RETURN
      END
      subroutine cost_accumulate_mean( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE cost_mod
      integer bi, bj
      integer myThid
      Real*8 thetaRef
      integer i, j, k
      integer ig, jg
      integer itlo,ithi
      integer jtlo,jthi
      jtlo = mybylo(mythid)
      jthi = mybyhi(mythid)
      itlo = mybxlo(mythid)
      ithi = mybxhi(mythid)
      do bj = jtlo,jthi
        do bi = itlo,ithi
          do k = 1, Nr
            do j=1,sNy
              do i=1,sNx
                cMeanTheta(i,j,k,bi,bj) = cMeanTheta(i,j,k,bi,bj)
     &                                    + theta(i,j,k,bi,bj)
     &                                    /lastinterval*deltaTClock
                cMeanUVel(i,j,k,bi,bj) = cMeanUVel(i,j,k,bi,bj)
     &                                    + uVel(i,j,k,bi,bj)
     &                                    /lastinterval*deltaTClock
                cMeanVVel(i,j,k,bi,bj) = cMeanVVel(i,j,k,bi,bj)
     &                                    + vVel(i,j,k,bi,bj)
     &                                    /lastinterval*deltaTClock
              end do
            end do
          end do
        end do
      end do
      END
      subroutine cost_final( mythid )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE PARAMS_mod
       USE cost_mod
       USE ctrl_mod
      integer mythid
      integer i,j,k
      integer bi,bj
      integer itlo,ithi
      integer jtlo,jthi
      jtlo = mybylo(mythid)
      jthi = mybyhi(mythid)
      itlo = mybxlo(mythid)
      ithi = mybxhi(mythid)
      CALL COST_ATLANTIC_HEAT (myThid)
      do bj = jtlo,jthi
        do bi = itlo,ithi
          write(standardmessageunit,'(A,D22.15)') 
     &          ' --> objf_test(bi,bj)   = ', objf_test(bi,bj)
          write(standardmessageunit,'(A,D22.15)') 
     &         ' --> objf_tracer(bi,bj) = ', objf_tracer(bi,bj)
          write(standardmessageunit,'(A,D22.15)') 
     &         ' --> objf_atl(bi,bj)    = ', objf_atl(bi,bj)
          fc = fc
     &            + mult_test   * objf_test(bi,bj)
     &            + mult_tracer * objf_tracer(bi,bj)
     &            + mult_atl    * objf_atl(bi,bj)
        enddo
      enddo
      write(standardmessageunit,'(A,D22.15)') '  local fc = ', fc
      CALL GLOBAL_SUM_R8 (  fc ,  myThid  )
      write(standardmessageunit,'(A,D22.15)') ' global fc = ', fc
      taveFreq    = 0.
      dumpFreq    = 0.
      pChkptFreq  = 0.
      monitorFreq = 0.
      return
      end
      subroutine cost_init_varia( mythid )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE cost_mod
      integer mythid
      integer i,j,k
      integer bi,bj
      integer itlo,ithi
      integer jtlo,jthi
      jtlo = mybylo(mythid)
      jthi = mybyhi(mythid)
      itlo = mybxlo(mythid)
      ithi = mybxhi(mythid)
      do bj = jtlo,jthi
        do bi = itlo,ithi
          objf_atl(bi,bj)  = 0.d0
          objf_test(bi,bj) = 0.d0
          objf_tracer(bi,bj) = 0.d0
          do k=1,nr
            do j=1,sNy
              do i=1,sNx
                cMeanTheta(i,j,k,bi,bj) = 0.d0
                cMeanUVel(i,j,k,bi,bj)  = 0.d0
                cMeanVVel(i,j,k,bi,bj)  = 0.d0
              end do
            end do
          end do
       enddo
      enddo
      IF (  mythid  .EQ. 1 ) THEN
        fc         = 0.d0
      ENDIF
      CALL BARRIER(myThid)
      return
      end
      subroutine cost_tile( mytime, myiter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE cost_mod
      Real*8 myTime
      integer myiter
      integer myThid
      integer bi, bj
      DO bj=myByLo(myThid),myByHi(myThid)
        DO bi=myBxLo(myThid),myBxHi(myThid)
           IF ( myTime .GT. (EndTime - lastinterval) )
     &          CALL COST_ACCUMULATE_MEAN (myThid)
        ENDDO
      ENDDO
      RETURN
      END
      subroutine cost_test( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE cost_mod
      integer bi, bj
      integer myThid
      END
      subroutine cost_tracer( bi, bj, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE cost_mod
      integer bi, bj
      integer myThid
      RETURN
      END
      subroutine cost_atlantic_heat( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE cost_mod
      integer myThid
      integer    isecbeg      , isecend      , jsec
      integer    jsecbeg      , jsecend      , isec
      integer    kmaxdepth
      integer i, j, k
      integer ig, jg
      integer bi, bj
      Real*8     locfc
      Real*8     uVel_bar(Nr), vVel_bar(Nr), theta_bar(Nr) 
      Real*8     countU(Nr), countV(Nr), countT(Nr)
      Real*8     petawatt
      Real*8     sum
      parameter( petawatt = 1.e+15 )
      parameter( isecbeg = 69, isecend = 87, jsec = 28 )
      parameter( jsecbeg = 10, jsecend = 27, isec = 59 )
      parameter ( kmaxdepth = 5 )
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        locfc = 0.0
        sum = 0.0
        do j=1,sNy
         jg = myYGlobalLo-1+(bj-1)*sNy+j
         if (jg .eq. jsec) then
          do k = 1, Nr
           vVel_bar(k) = 0.0
           theta_bar(k) = 0.0
           countT(k) = 0.0
           countV(k) = 0.0
           do i=1,sNx
            ig = myXGlobalLo-1+(bi-1)*sNx+i
            if ((ig .ge. isecbeg) .and. (ig .le. isecend)) then
             vVel_bar(k) = vVel_bar(k) 
     &                      + cMeanVVel(i,j,k,bi,bj)
     &                      *maskS(i,j,k,bi,bj)
     &                      *maskC(i,j,k,bi,bj)*maskC(i,j-1,k,bi,bj)
             theta_bar(k) = theta_bar(k) +
     &            0.5*( cMeanTheta(i,j,k,bi,bj)
     &                 +cMeanTheta(i,j-1,k,bi,bj) )
     &                 *maskS(i,j,k,bi,bj)*dxG(i,j,bi,bj)
     &                 *maskC(i,j,k,bi,bj)*maskC(i,j-1,k,bi,bj)
             countT(k) = countT(k) + maskS(i,j,k,bi,bj)
     &                      *maskC(i,j,k,bi,bj)*maskC(i,j-1,k,bi,bj)
             countV(k) = countV(k) + maskS(i,j,k,bi,bj)
     &                      *maskC(i,j,k,bi,bj)*maskC(i,j-1,k,bi,bj)
            end if
           enddo
          enddo
          do k = 1, Nr
           if ( k .LE. kmaxdepth .AND.
     &          countT(k) .NE. 0 .AND. countV(k) .NE. 0) then
            sum = sum
     &            + vVel_bar(k) * theta_bar(k) * drF(k) 
     &            / ( countT(k) * countV(k) )
           end if
          end do
         end if
        end do
        objf_atl(bi,bj) = 
     &     sum*HeatCapacity_Cp*rhoConst/petawatt
       end do
      end do
      end
      subroutine cost_vector( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE cost_mod
      integer myThid
      end
      subroutine cost_state_final( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE cost_mod
      integer myThid
      end
      subroutine ctrl_get_gen(
     I          xx_gen_file, xx_genstartdate, xx_genperiod,
     I          genmask, genfld, xx_gen0, xx_gen1, xx_gen_dummy, 
     I          mytime, myiter, mythid
     &                     )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE PARAMS_mod
       USE GRID_mod
       USE ctrl_mod
       USE ctrl_dummy_mod
       USE optim_mod
      character*(MAX_LEN_FNAM) xx_gen_file
      integer xx_genstartdate(4)
      Real*8     xx_genperiod
      Real*8     genmask(1-olx:snx+olx,1-oly:sny+oly,nr,nsx,nsy)
      Real*8     genfld(1-olx:snx+olx,1-oly:sny+oly,nsx,nsy)
      Real*8     xx_gen0(1-olx:snx+olx,1-oly:sny+oly,nsx,nsy)
      Real*8     xx_gen1(1-olx:snx+olx,1-oly:sny+oly,nsx,nsy)
      Real*8     xx_gen_dummy
      Real*8     mytime
      integer myiter
      integer mythid
      end
      subroutine ctrl_get_gen_rec(
     I                        xx_genstartdate,
     I                        xx_genperiod,
     O                        fac,
     O                        first,
     O                        changed,
     O                        count0,
     O                        count1,
     I                        mytime,
     I                        myiter,
     I                        mythid
     &                      )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE ctrl_mod
      integer xx_genstartdate(4)
      Real*8     xx_genperiod
      Real*8     fac
      logical first
      logical changed
      integer count0
      integer count1
      Real*8     mytime
      integer myiter
      integer mythid
      return
      end
      subroutine ctrl_init_variables( mythid )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE PARAMS_mod
       USE GRID_mod
       USE ctrl_mod
      integer mythid
      integer bi,bj
      integer i,j,k
      integer itlo,ithi
      integer jtlo,jthi
      integer jmin,jmax
      integer imin,imax
      integer ntmp
      integer ivarindex
      jtlo = mybylo(mythid)
      jthi = mybyhi(mythid)
      itlo = mybxlo(mythid)
      ithi = mybxhi(mythid)
      jmin = 1-oly
      jmax = sny+oly
      imin = 1-olx
      imax = snx+olx
      return
      end
      subroutine ctrl_map_ini( mythid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
       USE ctrl_mod
       USE ctrl_dummy_mod
       USE optim_mod
      integer mythid
      integer bi,bj
      integer i,j,k
      integer itlo,ithi
      integer jtlo,jthi
      integer jmin,jmax
      integer imin,imax
      integer il
      logical equal
      logical doglobalread
      logical ladinit
      character*( 80)   fnamegeneric
      Real*8     fac
      Real*8 tmptest
      integer  ilnblnk
      external ilnblnk
      jtlo = mybylo(mythid)
      jthi = mybyhi(mythid)
      itlo = mybxlo(mythid)
      ithi = mybxhi(mythid)
      jmin = 1
      jmax = sny
      imin = 1
      imax = snx
      doglobalread = .false.
      ladinit      = .false.
      equal = .true.
      if ( equal ) then
        fac = 1.d0
      else
        fac = 0.d0
      endif
      il=ilnblnk( xx_theta_file )
      write(fnamegeneric(1:80),'(2a,i10.10)')
     &     xx_theta_file(1:il),'.',optimcycle
      call active_read_xyz_loc( fnamegeneric, tmpfld3d, 1,
     &                      doglobalread, ladinit, optimcycle,
     &                      mythid, xx_theta_dummy )
      do bj = jtlo,jthi
        do bi = itlo,ithi
          do k = 1,nr
            do j = jmin,jmax
              do i = imin,imax
                theta(i,j,k,bi,bj) = theta(i,j,k,bi,bj) +
     &                               fac*tmpfld3d(i,j,k,bi,bj)
                if(theta(i,j,k,bi,bj).lt.-2.0) 
     &               theta(i,j,k,bi,bj)= -2.0 
              enddo
            enddo
          enddo
       enddo
      enddo
      il=ilnblnk( xx_salt_file )
      write(fnamegeneric(1:80),'(2a,i10.10)')
     &     xx_salt_file(1:il),'.',optimcycle
      call active_read_xyz_loc( fnamegeneric, tmpfld3d, 1,
     &                      doglobalread, ladinit, optimcycle,
     &                      mythid, xx_salt_dummy )
      do bj = jtlo,jthi
        do bi = itlo,ithi
          do k = 1,nr
            do j = jmin,jmax
              do i = imin,imax
                salt(i,j,k,bi,bj) = salt(i,j,k,bi,bj) +
     &                               fac*tmpfld3d(i,j,k,bi,bj)
              enddo
            enddo
          enddo
       enddo
      enddO
      il=ilnblnk( xx_diffkr_file )
      write(fnamegeneric(1:80),'(2a,i10.10)')
     &     xx_diffkr_file(1:il),'.',optimcycle
      call active_read_xyz_loc( fnamegeneric, tmpfld3d, 1,
     &                      doglobalread, ladinit, optimcycle,
     &                      mythid, xx_diffkr_dummy )
      do bj = jtlo,jthi
        do bi = itlo,ithi
          do k = 1,nr
            do j = jmin,jmax
              do i = imin,imax
                diffkr(i,j,k,bi,bj) = diffkr(i,j,k,bi,bj) +
     &                                tmpfld3d(i,j,k,bi,bj)
              enddo
            enddo
          enddo
       enddo
      enddo
      CALL EXCH_XYZ_RL (  theta,  mythid  )
      CALL EXCH_XYZ_RL (   salt,  mythid  )
      CALL EXCH_XYZ_RL (  diffkr,  mythid )
      return
      end
      subroutine ctrl_map_ini_ecco( mythid )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
       USE ctrl_mod
       USE ctrl_dummy_mod
       USE optim_mod
       USE tamc_mod
       USE tamc_keys_mod
      integer mythid
      return
      end
      SUBROUTINE CTRL_MAP_FORCING(myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE FFIELDS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE ctrl_mod
       USE ctrl_dummy_mod
       USE optim_mod
      INTEGER myThid
      integer bi,bj
      integer i,j,k
      integer itlo,ithi
      integer jtlo,jthi
      integer jmin,jmax
      integer imin,imax
      integer il
      logical equal
      logical doglobalread
      logical ladinit
      character*( 80)   fnametauu
      character*( 80)   fnametauv
      character*( 80)   fnamesflux
      character*( 80)   fnamehflux
      character*( 80)   fnamesss
      character*( 80)   fnamesst
      integer  ilnblnk
      external ilnblnk
      jtlo = mybylo(mythid)
      jthi = mybyhi(mythid)
      itlo = mybxlo(mythid)
      ithi = mybxhi(mythid)
      jmin = 1
      jmax = sny
      imin = 1
      imax = snx
      doglobalread = .false.
      ladinit      = .false.
      il=ilnblnk( xx_tauu_file )
      write(fnametauu(1:80),'(2a,i10.10)')
     &     xx_tauu_file(1:il),'.',optimcycle
      call active_read_xy_loc ( fnametauu, tmpfld2d, 1,
     &                      doglobalread, ladinit, optimcycle,
     &                      mythid, xx_tauu_dummy )
      do bj = jtlo,jthi
        do bi = itlo,ithi
          do j = jmin,jmax
            do i = imin,imax
              fu(i,j,bi,bj) = fu(i,j,bi,bj) + tmpfld2d(i,j,bi,bj)
            enddo
          enddo
        enddo
      enddo
      il=ilnblnk( xx_tauv_file )
      write(fnametauv(1:80),'(2a,i10.10)')
     &     xx_tauv_file(1:il),'.',optimcycle
      call active_read_xy_loc ( fnametauv, tmpfld2d, 1,
     &                      doglobalread, ladinit, optimcycle,
     &                      mythid, xx_tauv_dummy )
      do bj = jtlo,jthi
        do bi = itlo,ithi
          do j = jmin,jmax
            do i = imin,imax
              fv(i,j,bi,bj) = fv(i,j,bi,bj) + tmpfld2d(i,j,bi,bj)
            enddo
          enddo
        enddo
      enddo
      il=ilnblnk( xx_sflux_file )
      write(fnamesflux(1:80),'(2a,i10.10)')
     &     xx_sflux_file(1:il),'.',optimcycle
      call active_read_xy_loc ( fnamesflux, tmpfld2d, 1,
     &                      doglobalread, ladinit, optimcycle,
     &                      mythid, xx_sflux_dummy )
      do bj = jtlo,jthi
        do bi = itlo,ithi
          do j = jmin,jmax
            do i = imin,imax
              empmr(i,j,bi,bj) = empmr(i,j,bi,bj) + tmpfld2d(i,j,bi,bj)
            enddo
          enddo
        enddo
      enddo
      il=ilnblnk( xx_hflux_file )
      write(fnamehflux(1:80),'(2a,i10.10)')
     &     xx_hflux_file(1:il),'.',optimcycle
      call active_read_xy_loc ( fnamehflux, tmpfld2d, 1,
     &                      doglobalread, ladinit, optimcycle,
     &                      mythid, xx_hflux_dummy )
      do bj = jtlo,jthi
        do bi = itlo,ithi
          do j = jmin,jmax
            do i = imin,imax
              qnet(i,j,bi,bj) = qnet(i,j,bi,bj) + tmpfld2d(i,j,bi,bj)
            enddo
          enddo
        enddo
      enddo
       CALL EXCH_UV_XY_RS(fu,fv,.TRUE.,myThid)
       CALL EXCH_XY_RL ( EmPmR,  myThid  )
       CALL EXCH_XY_RL ( Qnet,   myThid  )
      END
      subroutine ctrl_smooth (
     U     fld ,mask)
       USE SIZE_mod
      integer k, bi, bj
      integer itlo,ithi
      integer jtlo,jthi
      Real*8 fld( 1-OLx:sNx+OLx, 1-OLy:sNy+OLy ,nSx,nSy)
      Real*8 mask( 1-OLx:sNx+OLx, 1-OLy:sNy+OLy,nr,nSx,nSy )
      integer i, j, im1, ip1, jm1, jp1
      Real*8 tempVar
      Real*8 fld_tmp( 1-OLx:sNx+OLx, 1-OLy:sNy+OLy )
      integer   imin      , imax          , jmin      , jmax
      parameter(imin=2-OLx, imax=sNx+OLx-1, jmin=2-OLy, jmax=sNy+OLy-1)
      Real*8        p0    , p5    , p25     , p125      , p0625
      parameter( p0=0.0, p5=0.5, p25=0.25, p125=0.125, p0625=0.0625 )
      jtlo = 1
      jthi = nsy
      itlo = 1
      ithi = nsx
      k=1
      do bj = jtlo,jthi
         do bi = itlo,ithi
            DO j = jmin, jmax
         jm1 = j-1
         jp1 = j+1
         DO i = imin, imax
            im1 = i-1
            ip1 = i+1
            tempVar =
     &           p25   *   mask(i  ,j  ,k,bi,bj)   +
     &           p125  * ( mask(im1,j  ,k,bi,bj)   +
     &                     mask(ip1,j  ,k,bi,bj)   +
     &                     mask(i  ,jm1,k,bi,bj)   +
     &                     mask(i  ,jp1,k,bi,bj) ) +
     &           p0625 * ( mask(im1,jm1,k,bi,bj)   +
     &                     mask(im1,jp1,k,bi,bj)   +
     &                     mask(ip1,jm1,k,bi,bj)   +
     &                     mask(ip1,jp1,k,bi,bj) )
            IF ( tempVar .GE. p25 ) THEN
               fld_tmp(i,j) = (
     &              p25  * fld(i  ,j,bi,bj  )*mask(i  ,j  ,k,bi,bj) +
     &              p125 *(fld(im1,j ,bi,bj )*mask(im1,j  ,k,bi,bj) +
     &                     fld(ip1,j ,bi,bj )*mask(ip1,j  ,k,bi,bj) +
     &                     fld(i  ,jm1,bi,bj)*mask(i  ,jm1,k,bi,bj) +
     &                     fld(i  ,jp1,bi,bj)*mask(i  ,jp1,k,bi,bj))+
     &              p0625*(fld(im1,jm1,bi,bj)*mask(im1,jm1,k,bi,bj) +
     &                     fld(im1,jp1,bi,bj)*mask(im1,jp1,k,bi,bj) +
     &                     fld(ip1,jm1,bi,bj)*mask(ip1,jm1,k,bi,bj) +
     &                     fld(ip1,jp1,bi,bj)*mask(ip1,jp1,k,bi,bj)))
     &              / tempVar
            ELSE
               fld_tmp(i,j) = fld(i,j,bi,bj)
            ENDIF
         ENDDO
      ENDDO
      DO j = jmin, jmax
         DO i = imin, imax
            fld(i,j,bi,bj) = fld_tmp(i,j)
         ENDDO
      ENDDO
         ENDDO
      ENDDO
      return
      end
      subroutine ctrl_getobcse(
     I                             mytime,
     I                             myiter,
     I                             mythid
     &                           )
      Real*8     mytime
      integer myiter
      integer mythid
      end
      subroutine ctrl_getobcsn(
     I                             mytime,
     I                             myiter,
     I                             mythid
     &                           )
      Real*8     mytime
      integer myiter
      integer mythid
      end
      subroutine ctrl_getobcss(
     I                             mytime,
     I                             myiter,
     I                             mythid
     &                           )
      Real*8     mytime
      integer myiter
      integer mythid
      end
      subroutine ctrl_getobcsw(
     I                             mytime,
     I                             myiter,
     I                             mythid
     &                           )
      Real*8     mytime
      integer myiter
      integer mythid
      end
      subroutine ctrl_obcsbal(
     I                       mytime,
     I                       myiter,
     I                       mythid
     &                     )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE ctrl_mod
       USE ctrl_dummy_mod
      integer myiter
      Real*8     mytime
      integer mythid
      return
      end
      subroutine ctrl_init_obcs_variables( mythid )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE PARAMS_mod
       USE GRID_mod
       USE ctrl_mod
      integer mythid
      integer bi,bj
      integer i,j,k
      integer itlo,ithi
      integer jtlo,jthi
      integer jmin,jmax
      integer imin,imax
      integer ntmp
      integer ivarindex
      integer iobcs
      jtlo = mybylo(mythid)
      jthi = mybyhi(mythid)
      itlo = mybxlo(mythid)
      ithi = mybxhi(mythid)
      jmin = 1-oly
      jmax = sny+oly
      imin = 1-olx
      imax = snx+olx
      return
      end
      subroutine ctrl_GetRec(
     I                        thefield,
     O                        fac,
     O                        first,
     O                        changed,
     O                        count0,
     O                        count1,
     I                        mytime,
     I                        myiter,
     I                        mythid
     &                      )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE ctrl_mod
      character*(*) thefield
      Real*8     fac
      logical first
      logical changed
      integer count0
      integer count1
      Real*8     mytime
      integer myiter
      integer mythid
      return
      end
      subroutine ctrl_volflux(
     I                       obcsncount,
     O                       sumarea,
     O                       sumflux, mythid
     &                     )
       USE EEPARAMS_mod
       USE SIZE_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE ctrl_mod
       USE ctrl_dummy_mod
       USE optim_mod
      integer obcsncount
      Real*8 sumflux
      Real*8 sumarea
      integer mythid
      return
      end
      SUBROUTINE GAD_ADVECTION(
     I     implicitAdvection, advectionScheme, vertAdvecScheme,
     I     tracerIdentity,
     I     uVel, vVel, wVel, tracer,
     O     gTracer,
     I     bi,bj, myTime,myIter,myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE GAD_mod
       USE tamc_mod
       USE tamc_keys_mod
      LOGICAL implicitAdvection
      INTEGER advectionScheme, vertAdvecScheme
      INTEGER tracerIdentity
      Real*8 uVel  (1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      Real*8 vVel  (1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      Real*8 wVel  (1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      Real*8 tracer(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      INTEGER bi,bj
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      Real*8 gTracer(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      Real*8 maskUp  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 maskLocW(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 maskLocS(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER iMin,iMax,jMin,jMax
      INTEGER iMinUpd,iMaxUpd,jMinUpd,jMaxUpd
      INTEGER i,j,k,kup,kDown
      Real*8 xA      (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 yA      (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uTrans  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vTrans  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTrans  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTransKp1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 af      (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 afx     (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 afy     (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fVerT   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 localTij(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 localTijk(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 kp1Msk
      LOGICAL calc_fluxes_X, calc_fluxes_Y, withSigns
      LOGICAL interiorOnly, overlapOnly
      INTEGER nipass,ipass
      INTEGER myTile, nCFace
      LOGICAL N_edge, S_edge, E_edge, W_edge
          act0 = tracerIdentity - 1
          max0 = maxpass
          act1 = bi - myBxLo(myThid)
          max1 = myBxHi(myThid) - myBxLo(myThid) + 1
          act2 = bj - myByLo(myThid)
          max2 = myByHi(myThid) - myByLo(myThid) + 1
          act3 = myThid - 1
          max3 = nTx*nTy
          act4 = ikey_dynamics - 1
          igadkey = (act0 + 1) 
     &                      + act1*max0
     &                      + act2*max0*max1
     &                      + act3*max0*max1*max2
     &                      + act4*max0*max1*max2*max3
          if (tracerIdentity.GT.maxpass) then
             print *, 'ph-pass gad_advection ', maxpass, tracerIdentity
             STOP 'maxpass seems smaller than tracerIdentity'
          endif
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        xA(i,j)      = 0.d0
        yA(i,j)      = 0.d0
        uTrans(i,j)  = 0.d0
        vTrans(i,j)  = 0.d0
        rTrans(i,j)  = 0.d0
        fVerT(i,j,1) = 0.d0
        fVerT(i,j,2) = 0.d0
        rTransKp1(i,j)= 0.d0
       ENDDO
      ENDDO
      IF (useCubedSphereExchange) THEN
       nipass=3
       IF ( nipass.GT.maxcube ) STOP 'maxcube needs to be = 3'
       nCFace = bi
       N_edge = .TRUE.
       S_edge = .TRUE.
       E_edge = .TRUE.
       W_edge = .TRUE.
      ELSE
       nipass=2
       N_edge = .FALSE.
       S_edge = .FALSE.
       E_edge = .FALSE.
       W_edge = .FALSE.
      ENDIF
      iMin = 1-OLx
      iMax = sNx+OLx
      jMin = 1-OLy
      jMax = sNy+OLy
      DO k=1,Nr
         kkey = (igadkey-1)*Nr + k
      CALL CALC_COMMON_FACTORS (
     I         bi,bj,iMin,iMax,jMin,jMax,k,
     O         xA,yA,uTrans,vTrans,rTrans,maskUp,
     I         myThid)
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
         localTij(i,j)=tracer(i,j,k,bi,bj)
         maskLocW(i,j)=maskW(i,j,k,bi,bj)
         maskLocS(i,j)=maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO ipass=1,nipass
         passkey = ipass + (k-1)      *maxcube
     &                   + (igadkey-1)*maxcube*Nr
         IF (nipass .GT. maxpass) THEN
          STOP 'GAD_ADVECTION: nipass > maxcube. check tamc.h'
         ENDIF
      interiorOnly = .FALSE.
      overlapOnly  = .FALSE.
      IF (useCubedSphereExchange) THEN
       IF (ipass.EQ.1) THEN
        overlapOnly  = MOD(nCFace,3).EQ.0
        interiorOnly = MOD(nCFace,3).NE.0
        calc_fluxes_X = nCFace.EQ.6 .OR. nCFace.EQ.1 .OR. nCFace.EQ.2
        calc_fluxes_Y = nCFace.EQ.3 .OR. nCFace.EQ.4 .OR. nCFace.EQ.5
       ELSEIF (ipass.EQ.2) THEN
        overlapOnly  = MOD(nCFace,3).EQ.2
        calc_fluxes_X = nCFace.EQ.2 .OR. nCFace.EQ.3 .OR. nCFace.EQ.4
        calc_fluxes_Y = nCFace.EQ.5 .OR. nCFace.EQ.6 .OR. nCFace.EQ.1
       ELSE
        calc_fluxes_X = nCFace.EQ.5 .OR. nCFace.EQ.6
        calc_fluxes_Y = nCFace.EQ.2 .OR. nCFace.EQ.3
       ENDIF
      ELSE
        calc_fluxes_X = MOD(ipass,2).EQ.1
        calc_fluxes_Y = .NOT.calc_fluxes_X
      ENDIF
      IF (calc_fluxes_X) THEN
       IF ( .NOT.overlapOnly .OR. N_edge .OR. S_edge ) THEN
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          af(i,j) = 0.
         ENDDO
        ENDDO
        IF (advectionScheme.EQ.ENUM_FLUX_LIMIT) THEN
          CALL GAD_FLUXLIMIT_ADV_X( bi,bj,k, dTtracerLev(k),
     I                              uTrans, uVel, maskLocW, localTij,
     O                              af, myThid )
        ELSEIF (advectionScheme.EQ.ENUM_DST3 ) THEN
          CALL GAD_DST3_ADV_X(      bi,bj,k, dTtracerLev(k),
     I                              uTrans, uVel, maskLocW, localTij,
     O                              af, myThid )
        ELSEIF (advectionScheme.EQ.ENUM_DST3_FLUX_LIMIT ) THEN
          CALL GAD_DST3FL_ADV_X(    bi,bj,k, dTtracerLev(k),
     I                              uTrans, uVel, maskLocW, localTij,
     O                              af, myThid )
        ELSE
         STOP 'GAD_ADVECTION: adv. scheme incompatibale with multi-dim'
        ENDIF
       ENDIF
       IF ( overlapOnly ) THEN
        iMinUpd = 1-Olx+1
        iMaxUpd = sNx+Olx-1
        IF ( W_edge ) iMinUpd = 1
        IF ( E_edge ) iMaxUpd = sNx
        IF ( S_edge ) THEN
         DO j=1-Oly,0
          DO i=iMinUpd,iMaxUpd
           localTij(i,j)=localTij(i,j)-dTtracerLev(k)*
     &       recip_hFacC(i,j,k,bi,bj)*recip_drF(k)
     &       *recip_rA(i,j,bi,bj)
     &       *( af(i+1,j)-af(i,j)
     &         -tracer(i,j,k,bi,bj)*(uTrans(i+1,j)-uTrans(i,j))
     &        )
          ENDDO
         ENDDO
        ENDIF
        IF ( N_edge ) THEN
         DO j=sNy+1,sNy+Oly
          DO i=iMinUpd,iMaxUpd
           localTij(i,j)=localTij(i,j)-dTtracerLev(k)*
     &       recip_hFacC(i,j,k,bi,bj)*recip_drF(k)
     &       *recip_rA(i,j,bi,bj)
     &       *( af(i+1,j)-af(i,j)
     &         -tracer(i,j,k,bi,bj)*(uTrans(i+1,j)-uTrans(i,j))
     &        )
          ENDDO
         ENDDO
        ENDIF
       ELSE
        jMinUpd = 1-Oly 
        jMaxUpd = sNy+Oly
        IF ( interiorOnly .AND. S_edge ) jMinUpd = 1
        IF ( interiorOnly .AND. N_edge ) jMaxUpd = sNy
        DO j=jMinUpd,jMaxUpd
         DO i=1-Olx+1,sNx+Olx-1
           localTij(i,j)=localTij(i,j)-dTtracerLev(k)*
     &       recip_hFacC(i,j,k,bi,bj)*recip_drF(k)
     &       *recip_rA(i,j,bi,bj)
     &       *( af(i+1,j)-af(i,j)
     &         -tracer(i,j,k,bi,bj)*(uTrans(i+1,j)-uTrans(i,j))
     &        )
         ENDDO
        ENDDO
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          afx(i,j) = af(i,j)
         ENDDO
        ENDDO
       ENDIF
      ENDIF
      IF (calc_fluxes_Y) THEN
       IF ( .NOT.overlapOnly .OR. E_edge .OR. W_edge ) THEN
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          af(i,j) = 0.
         ENDDO
        ENDDO
        IF (advectionScheme.EQ.ENUM_FLUX_LIMIT) THEN
          CALL GAD_FLUXLIMIT_ADV_Y( bi,bj,k, dTtracerLev(k),
     I                              vTrans, vVel, maskLocS, localTij,
     O                              af, myThid )
        ELSEIF (advectionScheme.EQ.ENUM_DST3 ) THEN
          CALL GAD_DST3_ADV_Y(      bi,bj,k, dTtracerLev(k),
     I                              vTrans, vVel, maskLocS, localTij,
     O                              af, myThid )
        ELSEIF (advectionScheme.EQ.ENUM_DST3_FLUX_LIMIT ) THEN
          CALL GAD_DST3FL_ADV_Y(    bi,bj,k, dTtracerLev(k),
     I                              vTrans, vVel, maskLocS, localTij,
     O                              af, myThid )
        ELSE
         STOP 'GAD_ADVECTION: adv. scheme incompatibale with mutli-dim'
        ENDIF
       ENDIF
       IF ( overlapOnly ) THEN
        jMinUpd = 1-Oly+1 
        jMaxUpd = sNy+Oly-1
        IF ( S_edge ) jMinUpd = 1
        IF ( N_edge ) jMaxUpd = sNy
        IF ( W_edge ) THEN
         DO j=jMinUpd,jMaxUpd
          DO i=1-Olx,0
           localTij(i,j)=localTij(i,j)-dTtracerLev(k)*
     &       recip_hFacC(i,j,k,bi,bj)*recip_drF(k)
     &       *recip_rA(i,j,bi,bj)
     &       *( af(i,j+1)-af(i,j)
     &         -tracer(i,j,k,bi,bj)*(vTrans(i,j+1)-vTrans(i,j))
     &        )
          ENDDO
         ENDDO
        ENDIF
        IF ( E_edge ) THEN
         DO j=jMinUpd,jMaxUpd
          DO i=sNx+1,sNx+Olx
           localTij(i,j)=localTij(i,j)-dTtracerLev(k)*
     &       recip_hFacC(i,j,k,bi,bj)*recip_drF(k)
     &       *recip_rA(i,j,bi,bj)
     &       *( af(i,j+1)-af(i,j)
     &         -tracer(i,j,k,bi,bj)*(vTrans(i,j+1)-vTrans(i,j))
     &        )
          ENDDO
         ENDDO
        ENDIF
       ELSE
        iMinUpd = 1-Olx
        iMaxUpd = sNx+Olx
        IF ( interiorOnly .AND. W_edge ) iMinUpd = 1
        IF ( interiorOnly .AND. E_edge ) iMaxUpd = sNx
        DO j=1-Oly+1,sNy+Oly-1
         DO i=iMinUpd,iMaxUpd
           localTij(i,j)=localTij(i,j)-dTtracerLev(k)*
     &       recip_hFacC(i,j,k,bi,bj)*recip_drF(k)
     &       *recip_rA(i,j,bi,bj)
     &       *( af(i,j+1)-af(i,j)
     &         -tracer(i,j,k,bi,bj)*(vTrans(i,j+1)-vTrans(i,j))
     &        )
         ENDDO
        ENDDO
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          afy(i,j) = af(i,j)
         ENDDO
        ENDDO
       ENDIF
      ENDIF
      ENDDO
      IF ( implicitAdvection ) THEN
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          gTracer(i,j,k,bi,bj)=
     &     (localTij(i,j)-tracer(i,j,k,bi,bj))/dTtracerLev(k)
         ENDDO
        ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         localTijk(i,j,k)=localTij(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF ( debugLevel .GE. debLevB
     &   .AND. tracerIdentity.EQ.GAD_TEMPERATURE
     &   .AND. k.LE.3 .AND. myIter.EQ.1+nIter0
     &   .AND. nPx.EQ.1 .AND. nPy.EQ.1
     &   .AND. useCubedSphereExchange ) THEN
        CALL DEBUG_CS_CORNER_UV( ' afx,afy from GAD_ADVECTION',
     &             afx,afy, k, standardMessageUnit,bi,bj,myThid )
      ENDIF
      ENDDO
      IF ( .NOT.implicitAdvection ) THEN
       DO k=Nr,1,-1
         kkey = (igadkey-1)*Nr + k
        kup  = 1+MOD(k+1,2)
        kDown= 1+MOD(k,2)
        kp1Msk=1.
        if (k.EQ.Nr) kp1Msk=0.
        IF ( k.EQ.1 ) THEN
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
           rTransKp1(i,j) = kp1Msk*rTrans(i,j)
           rTrans(i,j) = 0.
           fVerT(i,j,kUp) = 0.
          ENDDO
         ENDDO
        ELSE
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
           rTransKp1(i,j) = kp1Msk*rTrans(i,j)
           rTrans(i,j) = wVel(i,j,k,bi,bj)*rA(i,j,bi,bj)
     &                 *maskC(i,j,k-1,bi,bj)
           fVerT(i,j,kUp) = 0.
          ENDDO
         ENDDO
         IF (vertAdvecScheme.EQ.ENUM_FLUX_LIMIT) THEN
           CALL GAD_FLUXLIMIT_ADV_R( bi,bj,k, dTtracerLev(k),
     I                               rTrans, wVel, localTijk,
     O                               fVerT(1-Olx,1-Oly,kUp), myThid )
         ELSEIF (vertAdvecScheme.EQ.ENUM_DST3 ) THEN
           CALL GAD_DST3_ADV_R(      bi,bj,k, dTtracerLev(k),
     I                               rTrans, wVel, localTijk,
     O                               fVerT(1-Olx,1-Oly,kUp), myThid )
         ELSEIF (vertAdvecScheme.EQ.ENUM_DST3_FLUX_LIMIT ) THEN
           CALL GAD_DST3FL_ADV_R(    bi,bj,k, dTtracerLev(k),
     I                               rTrans, wVel, localTijk,
     O                               fVerT(1-Olx,1-Oly,kUp), myThid )
         ELSE
          STOP 'GAD_ADVECTION: adv. scheme incompatibale with mutli-dim'
         ENDIF
        ENDIF
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          localTij(i,j)=localTijk(i,j,k)-dTtracerLev(k)*
     &     recip_hFacC(i,j,k,bi,bj)*recip_drF(k)
     &     *recip_rA(i,j,bi,bj)
     &     *( fVerT(i,j,kDown)-fVerT(i,j,kUp)
     &       -tracer(i,j,k,bi,bj)*(rTransKp1(i,j)-rTrans(i,j))
     &      )*rkSign
          gTracer(i,j,k,bi,bj)=
     &     (localTij(i,j)-tracer(i,j,k,bi,bj))/dTtracerLev(k)
         ENDDO
        ENDDO
       ENDDO
      ENDIF 
      RETURN
      END
      SUBROUTINE GAD_BIHARM_X( 
     I           bi,bj,k,
     I           xA,del2T,diffK4,
     U           dfx,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 xA   (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2T(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 diffK4
      INTEGER myThid
      Real*8 dfx  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
         dfx(i,j) = dfx(i,j) + diffK4
     &    *xA(i,j)
     &    *(del2T(i,j)-del2T(i-1,j))*recip_dxC(i,j,bi,bj)
     &    *sqCosFacU(j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_BIHARM_Y( 
     I           bi,bj,k,
     I           yA,del2T,diffK4,
     O           dfy,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 yA   (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2T(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 diffK4
      INTEGER myThid
      Real*8 dfy  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx,sNx+Olx
         dfy(i,j) = dfy(i,j) + diffK4
     &    *yA(i,j)
     &    *(del2T(i,j)-del2T(i,j-1))*recip_dyC(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_C2_ADV_R( 
     I           bi,bj,k,
     I           rTrans,
     I           tracer,
     O           wT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      Real*8 wT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,km1
      km1=max(1,k-1)
      IF ( k.EQ.1 .OR. k.GT.Nr) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         wT(i,j) = 0.
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         wT(i,j) = maskC(i,j,kM1,bi,bj)*
     &     rTrans(i,j)*
     &        (Tracer(i,j,k,bi,bj)+Tracer(i,j,kM1,bi,bj))*0.5d0
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE GAD_C2_ADV_X( 
     I           bi,bj,k,
     I           uTrans,
     I           tracer,
     O           uT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 uT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Oly,sNy+Oly
       uT(1-Olx,j)=0.
       DO i=1-Olx+1,sNx+Olx
        uT(i,j) = 
     &   uTrans(i,j)*(Tracer(i,j)+Tracer(i-1,j))*0.5d0
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_C2_ADV_Y( 
     I           bi,bj,k,
     I           vTrans,
     I           tracer,
     O           vT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 vT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO i=1-Olx,sNx+Olx
       vT(i,1-Oly)=0.
      ENDDO
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx,sNx+Olx
        vT(i,j) = 
     &   vTrans(i,j)*(Tracer(i,j)+Tracer(i,j-1))*0.5d0
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_C4_ADV_R( 
     I           bi,bj,k,
     I           rTrans,
     I           tracer,
     O           wT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      Real*8 wT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,kp1,km1,km2
      Real*8 Rjm,Rj,Rjp,Rjjm,Rjjp
      Real*8 maskPM, maskBound
      km2=MAX(1,k-2)
      km1=MAX(1,k-1)
      kp1=MIN(Nr,k+1)
      maskPM = 1.
      IF (k.LE.2 .OR. k.GE.Nr) maskPM = 0.
      IF ( k.EQ.1 .OR. k.GT.Nr) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         wT(i,j) = 0.
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         maskBound = maskPM*maskC(i,j,km2,bi,bj)*maskC(i,j,kp1,bi,bj)
         Rjp=(tracer(i,j,kp1,bi,bj)-tracer(i,j,k,bi,bj))
     &        *maskC(i,j,kp1,bi,bj)
         Rj =(tracer(i,j,k,bi,bj)-tracer(i,j,km1,bi,bj))
         Rjm=(tracer(i,j,km1,bi,bj)-tracer(i,j,km2,bi,bj))
     &        *maskC(i,j,km1,bi,bj)
         Rjjp=(Rjp-Rj)
         Rjjm=(Rj-Rjm)
         wT(i,j) = maskC(i,j,km1,bi,bj)*(
     &     rTrans(i,j)*(
     &        (Tracer(i,j,k,bi,bj)+Tracer(i,j,km1,bi,bj))*0.5d0
     &        -oneSixth*(Rjjm+Rjjp)*0.5d0 )
     &    +ABS(rTrans(i,j))*
     &         oneSixth*(Rjjm-Rjjp)*0.5d0*(1.d0 - maskBound)
     &                                  )                      
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE GAD_C4_ADV_X( 
     I           bi,bj,k,
     I           uTrans,
     I           tracer,
     O           uT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 uT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      Real*8 Rjm,Rj,Rjp,Rjjm,Rjjp
      DO j=1-Oly,sNy+Oly
       uT(1-Olx,j)=0.
       uT(2-Olx,j)=0.
       uT(sNx+Olx,j)=0.
       DO i=1-Olx+2,sNx+Olx-1
        Rjp=(tracer(i+1,j)-tracer(i,j))
     &     *maskW(i+1,j,k,bi,bj)
        Rj =(tracer(i,j)-tracer(i-1,j))
     &     *maskW(i,j,k,bi,bj)
        Rjm=(tracer(i-1,j)-tracer(i-2,j))
     &     *maskW(i-1,j,k,bi,bj)
        Rjjp=(Rjp-Rj)
        Rjjm=(Rj-Rjm)
        uT(i,j) =
     &   uTrans(i,j)*(
     &     Tracer(i,j)+Tracer(i-1,j)-oneSixth*( Rjjp+Rjjm )
     &               )*0.5d0
     &  +ABS( uTrans(i,j) )*0.5d0*oneSixth*( Rjjp-Rjjm )
     &    *( 1.d0 - maskW(i-1,j,k,bi,bj)*maskW(i+1,j,k,bi,bj) )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_C4_ADV_Y( 
     I           bi,bj,k,
     I           vTrans,
     I           tracer,
     O           vT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 vT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      Real*8 Rjm,Rj,Rjp,Rjjm,Rjjp
      DO i=1-Olx,sNx+Olx
       vT(i,1-Oly)=0.
       vT(i,2-Oly)=0.
       vT(i,sNy+Oly)=0.
      ENDDO
      DO j=1-Oly+2,sNy+Oly-1
       DO i=1-Olx,sNx+Olx
        Rjp=(tracer(i,j+1)-tracer(i,j))
     &     *maskS(i,j+1,k,bi,bj)
        Rj =(tracer(i,j)-tracer(i,j-1))
     &     *maskS(i,j,k,bi,bj)
        Rjm=(tracer(i,j-1)-tracer(i,j-2))
     &     *maskS(i,j-1,k,bi,bj)
        Rjjp=(Rjp-Rj)
        Rjjm=(Rj-Rjm)
        vT(i,j) =
     &   vTrans(i,j)*(
     &     Tracer(i,j)+Tracer(i,j-1)-oneSixth*( Rjjp+Rjjm )
     &               )*0.5d0
     &  +ABS( vTrans(i,j) )*0.5d0*oneSixth*( Rjjp-Rjjm )
     &    *( 1.d0 - maskS(i,j-1,k,bi,bj)*maskS(i,j+1,k,bi,bj) )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_CALC_RHS( 
     I           bi,bj,iMin,iMax,jMin,jMax,k,kM1,kUp,kDown,
     I           xA,yA,uTrans,vTrans,rTrans,rTransKp1,maskUp,
     I           uVel, vVel, wVel,
     I           diffKh, diffK4, KappaR, Tracer,
     I           tracerIdentity, advectionScheme, vertAdvecScheme,
     I           calcAdvection, implicitAdvection,
     U           fVerT, gTracer,
     I           myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
       USE GAD_mod
       USE tamc_mod
       USE tamc_keys_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k,kUp,kDown,kM1
      Real*8 xA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 yA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTransKp1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 maskUp(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uVel  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 vVel  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 wVel  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 diffKh, diffK4
      Real*8 KappaR(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 Tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER tracerIdentity
      INTEGER advectionScheme, vertAdvecScheme
      LOGICAL calcAdvection
      LOGICAL implicitAdvection
      Real*8     myTime
      INTEGER myIter, myThid
      Real*8 gTracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 fVerT (1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      INTEGER i,j
      Real*8 df4   (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fZon  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fMer  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 af    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 df    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 localT(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 advFac, rAdvFac
      fVerT(1,1,kDown) = fVerT(1,1,kDown)
      advFac  = 0.d0
      IF (calcAdvection) advFac = 1.d0
      rAdvFac = rkSign*advFac
      IF (implicitAdvection) rAdvFac = 0.d0
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        fZon(i,j)      = 0.d0
        fMer(i,j)      = 0.d0
        fVerT(i,j,kUp) = 0.d0
        df(i,j)        = 0.d0
        df4(i,j)       = 0.d0
       ENDDO
      ENDDO
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        localT(i,j)=tracer(i,j,k,bi,bj)
       ENDDO
      ENDDO
      IF (diffK4 .NE. 0.) THEN
       CALL GAD_GRAD_X(bi,bj,k,xA,localT,fZon,myThid)
       CALL GAD_GRAD_Y(bi,bj,k,yA,localT,fMer,myThid)
       CALL GAD_DEL2(bi,bj,k,fZon,fMer,df4,myThid)
      ENDIF
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        fZon(i,j) = 0.d0
       ENDDO
      ENDDO
      IF (calcAdvection) THEN
        IF (advectionScheme.EQ.ENUM_CENTERED_2ND) THEN
          CALL GAD_C2_ADV_X(bi,bj,k,uTrans,localT,af,myThid)
        ELSEIF (advectionScheme.EQ.ENUM_FLUX_LIMIT) THEN
          CALL GAD_FLUXLIMIT_ADV_X( bi,bj,k, dTtracerLev(k),
     I            uTrans, uVel, maskW(1-Olx,1-Oly,k,bi,bj), localT,
     O            af, myThid )
        ELSEIF (advectionScheme.EQ.ENUM_UPWIND_3RD ) THEN
          CALL GAD_U3_ADV_X(bi,bj,k,uTrans,localT,af,myThid)
        ELSEIF (advectionScheme.EQ.ENUM_CENTERED_4TH) THEN
          CALL GAD_C4_ADV_X(bi,bj,k,uTrans,localT,af,myThid)
        ELSEIF (advectionScheme.EQ.ENUM_DST3 ) THEN
          CALL GAD_DST3_ADV_X( bi,bj,k, dTtracerLev(k),
     I            uTrans, uVel, maskW(1-Olx,1-Oly,k,bi,bj), localT,
     O            af, myThid )
        ELSEIF (advectionScheme.EQ.ENUM_DST3_FLUX_LIMIT ) THEN
         IF ( inAdMode ) THEN
          CALL GAD_DST3_ADV_X( bi,bj,k, dTtracerLev(k),
     I           uTrans, uVel, maskW(1-Olx,1-Oly,k,bi,bj), localT,
     O           af, myThid )
         ELSE
          CALL GAD_DST3FL_ADV_X( bi,bj,k, dTtracerLev(k),
     I           uTrans, uVel, maskW(1-Olx,1-Oly,k,bi,bj), localT,
     O           af, myThid )
         ENDIF
        ELSE
         STOP 'GAD_CALC_RHS: Bad advectionScheme (X)'
        ENDIF
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          fZon(i,j) = fZon(i,j) + af(i,j)
         ENDDO
        ENDDO
      ENDIF
      IF (diffKh.NE.0.) THEN
       CALL GAD_DIFF_X(bi,bj,k,xA,diffKh,localT,df,myThid)
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         df(i,j) = 0.d0
        ENDDO
       ENDDO
      ENDIF
      IF (diffK4 .NE. 0.) THEN
       CALL GAD_BIHARM_X(bi,bj,k,xA,df4,diffK4,df,myThid)
      ENDIF
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        fZon(i,j) = fZon(i,j) + df(i,j)
       ENDDO
      ENDDO
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        fMer(i,j) = 0.d0
       ENDDO
      ENDDO
      IF (calcAdvection) THEN
        IF (advectionScheme.EQ.ENUM_CENTERED_2ND) THEN
          CALL GAD_C2_ADV_Y(bi,bj,k,vTrans,localT,af,myThid)
        ELSEIF (advectionScheme.EQ.ENUM_FLUX_LIMIT) THEN
          CALL GAD_FLUXLIMIT_ADV_Y( bi,bj,k, dTtracerLev(k),
     I            vTrans, vVel, maskS(1-Olx,1-Oly,k,bi,bj), localT,
     O            af, myThid )
        ELSEIF (advectionScheme.EQ.ENUM_UPWIND_3RD ) THEN
          CALL GAD_U3_ADV_Y(bi,bj,k,vTrans,localT,af,myThid)
        ELSEIF (advectionScheme.EQ.ENUM_CENTERED_4TH) THEN
          CALL GAD_C4_ADV_Y(bi,bj,k,vTrans,localT,af,myThid)
        ELSEIF (advectionScheme.EQ.ENUM_DST3 ) THEN
          CALL GAD_DST3_ADV_Y( bi,bj,k, dTtracerLev(k),
     I            vTrans, vVel, maskS(1-Olx,1-Oly,k,bi,bj), localT,
     O            af, myThid )
        ELSEIF (advectionScheme.EQ.ENUM_DST3_FLUX_LIMIT ) THEN
         IF ( inAdMode ) THEN
          CALL GAD_DST3_ADV_Y( bi,bj,k, dTtracerLev(k),
     I           vTrans, vVel, maskS(1-Olx,1-Oly,k,bi,bj), localT,
     O           af, myThid )
         ELSE
          CALL GAD_DST3FL_ADV_Y( bi,bj,k, dTtracerLev(k),
     I           vTrans, vVel, maskS(1-Olx,1-Oly,k,bi,bj), localT,
     O           af, myThid )
         ENDIF
        ELSE
          STOP 'GAD_CALC_RHS: Bad advectionScheme (Y)'
        ENDIF
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          fMer(i,j) = fMer(i,j) + af(i,j)
         ENDDO
        ENDDO
      ENDIF
      IF (diffKh.NE.0.) THEN
       CALL GAD_DIFF_Y(bi,bj,k,yA,diffKh,localT,df,myThid)
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         df(i,j) = 0.d0
        ENDDO
       ENDDO
      ENDIF
      IF (diffK4 .NE. 0.) THEN
       CALL GAD_BIHARM_Y(bi,bj,k,yA,df4,diffK4,df,myThid)
      ENDIF
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        fMer(i,j) = fMer(i,j) + df(i,j)
       ENDDO
      ENDDO
      IF (calcAdvection .AND. .NOT.implicitAdvection .AND. K.GE.2) THEN
        IF (vertAdvecScheme.EQ.ENUM_CENTERED_2ND) THEN
          CALL GAD_C2_ADV_R(bi,bj,k,rTrans,tracer,af,myThid)
        ELSEIF (vertAdvecScheme.EQ.ENUM_FLUX_LIMIT) THEN
          CALL GAD_FLUXLIMIT_ADV_R(
     &         bi,bj,k,dTtracerLev(k),rTrans,wVel,tracer,af,myThid)
        ELSEIF (vertAdvecScheme.EQ.ENUM_UPWIND_3RD ) THEN
          CALL GAD_U3_ADV_R(bi,bj,k,rTrans,tracer,af,myThid)
        ELSEIF (vertAdvecScheme.EQ.ENUM_CENTERED_4TH) THEN
          CALL GAD_C4_ADV_R(bi,bj,k,rTrans,tracer,af,myThid)
        ELSEIF (vertAdvecScheme.EQ.ENUM_DST3 ) THEN
          CALL GAD_DST3_ADV_R(
     &         bi,bj,k,dTtracerLev(k),rTrans,wVel,tracer,af,myThid)
        ELSEIF (vertAdvecScheme.EQ.ENUM_DST3_FLUX_LIMIT ) THEN
          IF ( inAdMode ) THEN
           CALL GAD_DST3_ADV_R(
     &        bi,bj,k,dTtracerLev(k),rTrans,wVel,tracer,af,myThid)
          ELSE
           CALL GAD_DST3FL_ADV_R(
     &        bi,bj,k,dTtracerLev(k),rTrans,wVel,tracer,af,myThid)
          ENDIF
        ELSE
          STOP 'GAD_CALC_RHS: Bad vertAdvecScheme (R)'
        ENDIF
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          fVerT(i,j,kUp) = fVerT(i,j,kUp) + af(i,j)
         ENDDO
        ENDDO
      ENDIF
      IF (implicitDiffusion) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         df(i,j) = 0.d0
        ENDDO
       ENDDO
      ELSE
       CALL GAD_DIFF_R(bi,bj,k,KappaR,tracer,df,myThid)
      ENDIF
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        fVerT(i,j,kUp) = fVerT(i,j,kUp) + df(i,j)*maskUp(i,j)
       ENDDO
      ENDDO
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        gTracer(i,j,k,bi,bj)=gTracer(i,j,k,bi,bj)
     &   -recip_hFacC(i,j,k,bi,bj)*recip_drF(k)*recip_rA(i,j,bi,bj)
     &   *( (fZon(i+1,j)-fZon(i,j))
     &     +(fMer(i,j+1)-fMer(i,j))
     &     +(fVerT(i,j,kDown)-fVerT(i,j,kUp))*rkSign
     &     -localT(i,j)*( (uTrans(i+1,j)-uTrans(i,j))
     &                   +(vTrans(i,j+1)-vTrans(i,j))
     &                   +(rTransKp1(i,j)-rTrans(i,j))*rAdvFac
     &                  )*advFac
     &    )
       ENDDO
      ENDDO
      IF ( debugLevel .GE. debLevB
     &   .AND. tracerIdentity.EQ.GAD_TEMPERATURE
     &   .AND. k.EQ.2 .AND. myIter.EQ.1+nIter0
     &   .AND. nPx.EQ.1 .AND. nPy.EQ.1
     &   .AND. useCubedSphereExchange ) THEN
        CALL DEBUG_CS_CORNER_UV( ' fZon,fMer from GAD_CALC_RHS',
     &             fZon,fMer, k, standardMessageUnit,bi,bj,myThid )
      ENDIF
      RETURN
      END
      SUBROUTINE GAD_DEL2( 
     I           bi,bj,k,
     I           dTdx,dTdy,
     O           del2,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 dTdx(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dTdy(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 del2(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        del2(i,j)= 0.d0
       ENDDO
      ENDDO
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        del2(i,j)=recip_rA(i,j,bi,bj)
     &           *recip_drF(k)
     &           *recip_hFacC(i,j,k,bi,bj)
     &           *( ( dTdx(i+1,j)-dTdx(i,j) )
     &             +( dTdy(i,j+1)-dTdy(i,j) )
     &            )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_DIFF_R( 
     I           bi,bj,k,
     I           KappaR,
     I           tracer,
     O           dfr,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 KappaR(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      Real*8 dfr   (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,km1
      km1=max(1,k-1)
      IF (k.eq.1 .OR. k.gt.Nr) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         dfr(i,j) = 0.
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         dfr(i,j) =
     &    -rA(i,j,bi,bj)
     &     *KappaR(i,j)*recip_drC(k)
     &     *(Tracer(i,j,k,bi,bj)-Tracer(i,j,km1,bi,bj))*rkSign
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE GAD_DIFF_X( 
     I           bi,bj,k,
     I           xA, diffKh,
     I           tracer,
     O           dfx,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 xA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 diffKh
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 dfx   (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Oly,sNy+Oly
       dfx(1-Olx,j)=0.
       DO i=1-Olx+1,sNx+Olx
        dfx(i,j) = -diffKh*xA(i,j)
     &      *recip_dxC(i,j,bi,bj)
     &      *(Tracer(i,j)-Tracer(i-1,j))
     &      *CosFacU(j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_DIFF_Y( 
     I           bi,bj,k,
     I           yA, diffKh,
     I           tracer,
     O           dfy,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 yA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 diffKh
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 dfy   (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO i=1-Olx,sNx+Olx
       dfy(i,1-Oly)=0.
      ENDDO
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx,sNx+Olx
        dfy(i,j) = -diffKh*yA(i,j)
     &      *recip_dyC(i,j,bi,bj)
     &      *(Tracer(i,j)-Tracer(i,j-1))
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_DST3_ADV_X( 
     I           bi,bj,k,deltaTloc,
     I           uTrans, uVel,
     I           maskLocW, tracer,
     O           uT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 deltaTloc
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 maskLocW(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      Real*8 Rjm,Rj,Rjp,cfl,d0,d1
      Real*8 psiP,psiM,thetaP,thetaM
      Real*8 uFld
      Real*8 smallNo
      Real*8 Rjjm,Rjjp
      IF (inAdMode) THEN
       smallNo = 1.0D-20
      ELSE
       smallNo = 1.0D-20
      ENDIF
      DO j=1-Oly,sNy+Oly
       uT(1-Olx,j)=0.
       uT(2-Olx,j)=0.
       uT(sNx+Olx,j)=0.
       DO i=1-Olx+2,sNx+Olx-1
        Rjp=(tracer(i+1,j)-tracer( i ,j))*maskLocW(i+1,j)
        Rj =(tracer( i ,j)-tracer(i-1,j))*maskLocW( i ,j)
        Rjm=(tracer(i-1,j)-tracer(i-2,j))*maskLocW(i-1,j)
        uFld = uTrans(i,j)*recip_dyG(i,j,bi,bj)
     &       *recip_drF(k)*recip_hFacW(i,j,k,bi,bj)
        cfl=abs(uFld*deltaTloc*recip_dxC(i,j,bi,bj))
        d0=(2.-cfl)*(1.-cfl)*oneSixth
        d1=(1.-cfl*cfl)*oneSixth
        IF ( ABS(Rj).LT.smallNo .OR.
     &       ABS(Rjm).LT.smallNo ) THEN
         thetaP=0.
         psiP=0.
        ELSE
         thetaP=(Rjm+smallNo)/(smallNo+Rj)
         psiP=d0+d1*thetaP
        ENDIF
        IF ( ABS(Rj).LT.smallNo .OR.
     &       ABS(Rjp).LT.smallNo ) THEN
         thetaM=0.
         psiM=0.
        ELSE
         thetaM=(Rjp+smallNo)/(smallNo+Rj)
         psiM=d0+d1*thetaM
        ENDIF
        uT(i,j)=
     &   0.5*(uTrans(i,j)+abs(uTrans(i,j)))
     &      *( Tracer(i-1,j) + psiP*Rj )
     &  +0.5*(uTrans(i,j)-abs(uTrans(i,j)))
     &      *( Tracer( i ,j) - psiM*Rj )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_DST3_ADV_Y( 
     I           bi,bj,k,deltaTloc,
     I           vTrans, vVel,
     I           maskLocS, tracer,
     O           vT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 deltaTloc
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 maskLocS(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      Real*8 Rjm,Rj,Rjp,cfl,d0,d1
      Real*8 psiP,psiM,thetaP,thetaM
      Real*8 vFld
      Real*8 smallNo
      Real*8 Rjjm,Rjjp
      IF (inAdMode) THEN
       smallNo = 1.0D-20
      ELSE
       smallNo = 1.0D-20
      ENDIF
      DO i=1-Olx,sNx+Olx
       vT(i,1-Oly)=0.
       vT(i,2-Oly)=0.
       vT(i,sNy+Oly)=0.
      ENDDO
      DO j=1-Oly+2,sNy+Oly-1
       DO i=1-Olx,sNx+Olx
        Rjp=(tracer(i,j+1)-tracer(i, j ))*maskLocS(i,j+1)
        Rj =(tracer(i, j )-tracer(i,j-1))*maskLocS(i, j )
        Rjm=(tracer(i,j-1)-tracer(i,j-2))*maskLocS(i,j-1)
        vFld = vTrans(i,j)*recip_dxG(i,j,bi,bj)
     &       *recip_drF(k)*recip_hFacS(i,j,k,bi,bj)
        cfl=abs(vFld*deltaTloc*recip_dyC(i,j,bi,bj))
        d0=(2.-cfl)*(1.-cfl)*oneSixth
        d1=(1.-cfl*cfl)*oneSixth
        IF ( ABS(Rj).LT.smallNo .OR.
     &       ABS(Rjm).LT.smallNo ) THEN
         thetaP=0.
         psiP=0.
        ELSE   
         thetaP=(Rjm+smallNo)/(smallNo+Rj)
         psiP=d0+d1*thetaP
        ENDIF
        IF ( ABS(Rj).LT.smallNo .OR.
     &       ABS(Rjp).LT.smallNo ) THEN
         thetaM=0.
         psiM=0.
        ELSE
         thetaM=(Rjp+smallNo)/(smallNo+Rj)
         psiM=d0+d1*thetaM
        ENDIF
        vT(i,j)=
     &   0.5*(vTrans(i,j)+abs(vTrans(i,j)))
     &      *( Tracer(i,j-1) + psiP*Rj )
     &  +0.5*(vTrans(i,j)-abs(vTrans(i,j)))
     &      *( Tracer(i, j ) - psiM*Rj )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_DST3_ADV_R( 
     I           bi_arg,bj_arg,k,dTarg,
     I           rTrans, wVel,
     I           tracer,
     O           wT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GAD_mod
      INTEGER bi_arg,bj_arg,k
      Real*8 dTarg
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 wVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 wT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j,kp1,km1,km2,bi,bj
      Real*8 Rjm,Rj,Rjp,cfl,d0,d1
      Real*8 psiP,psiM,thetaP,thetaM
      Real*8 wFld
      Real*8 smallNo
      Real*8 Rjjm,Rjjp
      IF (.NOT. multiDimAdvection) THEN
       bi=bi_arg
       bj=bj_arg
      ELSE
       bi=1
       bj=1
      ENDIF
      IF (inAdMode) THEN
       smallNo = 1.0D-20
      ELSE
       smallNo = 1.0D-20
      ENDIF
      km2=MAX(1,k-2)
      km1=MAX(1,k-1)
      kp1=MIN(Nr,k+1)
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        Rjp=(tracer(i,j,k,bi,bj)-tracer(i,j,kp1,bi,bj))
     &         *maskC(i,j,kp1,bi_arg,bj_arg)
        Rj =(tracer(i,j,km1,bi,bj)-tracer(i,j,k,bi,bj))
     &         *maskC(i,j,k,bi_arg,bj_arg)*maskC(i,j,km1,bi_arg,bj_arg)
        Rjm=(tracer(i,j,km2,bi,bj)-tracer(i,j,km1,bi,bj))
     &         *maskC(i,j,km1,bi_arg,bj_arg)
        wFld = rTrans(i,j)*recip_rA(i,j,bi_arg,bj_arg)
        cfl=abs(wFld*dTarg*recip_drC(k))
        d0=(2.-cfl)*(1.-cfl)*oneSixth
        d1=(1.-cfl*cfl)*oneSixth
        IF ( ABS(Rj).LT.smallNo .OR.
     &       ABS(Rjm).LT.smallNo ) THEN
         thetaP=0.
         psiP=0.
        ELSE
         thetaP=(Rjm+smallNo)/(smallNo+Rj)
         psiP=d0+d1*thetaP
        ENDIF
        IF ( ABS(Rj).LT.smallNo .OR.
     &       ABS(Rjp).LT.smallNo ) THEN
         thetaM=0.
         psiM=0.
        ELSE
         thetaM=(Rjp+smallNo)/(smallNo+Rj)
         psiM=d0+d1*thetaM
        ENDIF
         wT(i,j)=
     &    0.5*(rTrans(i,j)+abs(rTrans(i,j)))
     &       *( Tracer(i,j, k ,bi,bj) + psiM*Rj )
     &   +0.5*(rTrans(i,j)-abs(rTrans(i,j)))
     &       *( Tracer(i,j,km1,bi,bj) - psiP*Rj )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_DST3FL_ADV_X( 
     I           bi,bj,k,deltaTloc,
     I           uTrans, uVel,
     I           maskLocW, tracer,
     O           uT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 deltaTloc
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 maskLocW(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      Real*8 Rjm,Rj,Rjp,cfl,d0,d1,psiP,psiM,thetaP,thetaM
      Real*8 uFld
      DO j=1-Oly,sNy+Oly
       uT(1-Olx,j)=0.d0
       uT(2-Olx,j)=0.d0
       uT(sNx+Olx,j)=0.d0
       DO i=1-Olx+2,sNx+Olx-1
        Rjp=(tracer(i+1,j)-tracer( i ,j))*maskLocW(i+1,j)
        Rj =(tracer( i ,j)-tracer(i-1,j))*maskLocW( i ,j)
        Rjm=(tracer(i-1,j)-tracer(i-2,j))*maskLocW(i-1,j)
        uFld = uTrans(i,j)*recip_dyG(i,j,bi,bj)
     &       *recip_drF(k)*recip_hFacW(i,j,k,bi,bj)
        cfl=abs(uFld*deltaTloc*recip_dxC(i,j,bi,bj))
        d0=(2.d0-cfl)*(1.d0-cfl)*oneSixth
        d1=(1.d0-cfl*cfl)*oneSixth
        thetaP=Rjm/(1.D-20+Rj)
        psiP=d0+d1*thetaP
        psiP=max(0.d0, min(min(1.d0,psiP),
     &       (1.d0-cfl)/(1.D-20+cfl)*thetaP))
        thetaM=Rjp/(1.D-20+Rj)
        psiM=d0+d1*thetaM
        psiM=max(0.d0, min(min(1.d0,psiM),
     &       (1.d0-cfl)/(1.D-20+cfl)*thetaM))
        uT(i,j)=
     &   0.5*(uTrans(i,j)+abs(uTrans(i,j)))
     &      *( Tracer(i-1,j) + psiP*Rj )
     &  +0.5*(uTrans(i,j)-abs(uTrans(i,j)))
     &      *( Tracer( i ,j) - psiM*Rj )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_DST3FL_ADV_Y( 
     I           bi,bj,k,deltaTloc,
     I           vTrans, vVel,
     I           maskLocS, tracer,
     O           vT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 deltaTloc
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 maskLocS(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      Real*8 Rjm,Rj,Rjp,cfl,d0,d1,psiP,psiM,thetaP,thetaM
      Real*8 vFld
      DO i=1-Olx,sNx+Olx
       vT(i,1-Oly)=0.d0
       vT(i,2-Oly)=0.d0
       vT(i,sNy+Oly)=0.d0
      ENDDO
      DO j=1-Oly+2,sNy+Oly-1
       DO i=1-Olx,sNx+Olx
        Rjp=(tracer(i,j+1)-tracer(i, j ))*maskLocS(i,j+1)
        Rj =(tracer(i, j )-tracer(i,j-1))*maskLocS(i, j )
        Rjm=(tracer(i,j-1)-tracer(i,j-2))*maskLocS(i,j-1)
        vFld = vTrans(i,j)*recip_dxG(i,j,bi,bj)
     &       *recip_drF(k)*recip_hFacS(i,j,k,bi,bj)
        cfl=abs(vFld*deltaTloc*recip_dyC(i,j,bi,bj))
        d0=(2.d0-cfl)*(1.d0-cfl)*oneSixth
        d1=(1.d0-cfl*cfl)*oneSixth
        thetaP=Rjm/(1.D-20+Rj)
        psiP=d0+d1*thetaP
        psiP=max(0.d0, min(min(1.d0,psiP),
     &       (1.d0-cfl)/(1.D-20+cfl)*thetaP))
        thetaM=Rjp/(1.D-20+Rj)
        psiM=d0+d1*thetaM
        psiM=max(0.d0, min(min(1.d0,psiM),
     &       (1.d0-cfl)/(1.D-20+cfl)*thetaM))
        vT(i,j)=
     &   0.5*(vTrans(i,j)+abs(vTrans(i,j)))
     &      *( Tracer(i,j-1) + psiP*Rj )
     &  +0.5*(vTrans(i,j)-abs(vTrans(i,j)))
     &      *( Tracer(i, j ) - psiM*Rj )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_DST3FL_ADV_R( 
     I           bi_arg,bj_arg,k,dTarg,
     I           rTrans, wVel,
     I           tracer,
     O           wT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GAD_mod
      INTEGER bi_arg,bj_arg,k
      Real*8 dTarg
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 wVel(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 wT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j,kp1,km1,km2,bi,bj
      Real*8 Rjm,Rj,Rjp,cfl,d0,d1
      Real*8 psiP,psiM,thetaP,thetaM
      Real*8 wFld
      IF (.NOT. multiDimAdvection) THEN
       bi=bi_arg
       bj=bj_arg
      ELSE
       bi=1
       bj=1
      ENDIF
      km2=MAX(1,k-2)
      km1=MAX(1,k-1)
      kp1=MIN(Nr,k+1)
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        Rjp=(tracer(i,j,k,bi,bj)-tracer(i,j,kp1,bi,bj))
     &         *maskC(i,j,kp1,bi_arg,bj_arg)
        Rj =(tracer(i,j,km1,bi,bj)-tracer(i,j,k,bi,bj))
     &         *maskC(i,j,k,bi_arg,bj_arg)*maskC(i,j,km1,bi_arg,bj_arg)
        Rjm=(tracer(i,j,km2,bi,bj)-tracer(i,j,km1,bi,bj))
     &         *maskC(i,j,km1,bi_arg,bj_arg)
        wFld = rTrans(i,j)*recip_rA(i,j,bi_arg,bj_arg)
        cfl=abs(wFld*dTarg*recip_drC(k))
        d0=(2.d0-cfl)*(1.-cfl)*oneSixth
        d1=(1.d0-cfl*cfl)*oneSixth
        thetaP=Rjm/(1.D-20+Rj)
        psiP=d0+d1*thetaP
        psiP=max(0.d0,min(min(1.d0,psiP),
     &       (1.d0-cfl)/(1.D-20+cfl)*thetaP))
        thetaM=Rjp/(1.D-20+Rj)
        psiM=d0+d1*thetaM
        psiM=max(0.d0,min(min(1.d0,psiM),
     &       (1.d0-cfl)/(1.D-20+cfl)*thetaM))
        wT(i,j)=
     &   0.5*(rTrans(i,j)+abs(rTrans(i,j)))
     &      *( Tracer(i,j, k ,bi,bj) + psiM*Rj )
     &  +0.5*(rTrans(i,j)-abs(rTrans(i,j)))
     &      *( Tracer(i,j,km1,bi,bj) - psiP*Rj )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_FLUXLIMIT_ADV_R( 
     I           bi_arg,bj_arg,k,dTarg,
     I           rTrans, wVel,
     I           tracer,
     O           wT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi_arg,bj_arg,k
      Real*8 dTarg
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 wVel  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      Real*8 wT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,kp1,km1,km2,bi,bj
      Real*8 Cr,Rjm,Rj,Rjp
      Real*8 wFld
      Real*8 Limiter
      Limiter(Cr)=max(0.d0,max(min(1.d0,2.d0*Cr),
     &                         min(2.d0,Cr))) 
      IF (.NOT. multiDimAdvection) THEN
       bi=bi_arg
       bj=bj_arg
      ELSE
       bi=1
       bj=1
      ENDIF
      km2=MAX(1,k-2)
      km1=MAX(1,k-1)
      kp1=MIN(Nr,k+1)
      IF ( k.GT.Nr) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         wT(i,j) = 0.
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         wFld = rTrans(i,j)*recip_rA(i,j,bi_arg,bj_arg)
         Rjp=(tracer(i,j,kp1,bi,bj)-tracer(i,j,k,bi,bj))
     &        *maskC(i,j,kp1,bi_arg,bj_arg)
         Rj=(tracer(i,j,k,bi,bj)-tracer(i,j,kM1,bi,bj))
         Rjm=(tracer(i,j,km1,bi,bj)-tracer(i,j,kM2,bi,bj))
     &        *maskC(i,j,km2,bi_arg,bj_arg)
         IF (Rj.NE.0.) THEN
          IF (rTrans(i,j).LT.0.) THEN
            Cr=Rjm/Rj
          ELSE
            Cr=Rjp/Rj
          ENDIF
         ELSE
          IF (rTrans(i,j).LT.0.) THEN
            Cr=Rjm*1.E20
          ELSE
            Cr=Rjp*1.E20
          ENDIF
         ENDIF
         Cr=Limiter(Cr)
         wT(i,j) = maskC(i,j,kM1,bi_arg,bj_arg)*(
     &     rTrans(i,j)*
     &        (Tracer(i,j,k,bi,bj)+Tracer(i,j,kM1,bi,bj))*0.5d0
     &    +(ABS(rTrans(i,j))*(1-Cr)
     &      +rTrans(i,j)*wFld*dTarg*recip_drC(k)
     &                  *Cr
     &     )*Rj*0.5d0                )
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE GAD_FLUXLIMIT_ADV_X( 
     I           bi,bj,k,deltaTloc,
     I           uTrans, uVel,
     I           maskLocW, tracer,
     O           uT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 deltaTloc
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uVel  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 maskLocW(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 uT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      Real*8 Cr,Rjm,Rj,Rjp
      Real*8 uFld
      Real*8 Limiter
      Limiter(Cr)=max(0.d0,max(min(1.d0,2.d0*Cr),
     &                         min(2.d0,Cr))) 
      DO j=1-Oly,sNy+Oly
       uT(1-Olx,j)=0.
       uT(2-Olx,j)=0.
       uT(sNx+Olx,j)=0.
       DO i=1-Olx+2,sNx+Olx-1
        uFld = uTrans(i,j)*recip_dyG(i,j,bi,bj)
     &       *recip_drF(k)*recip_hFacW(i,j,k,bi,bj)
        Rjp=(tracer(i+1,j)-tracer( i ,j))*maskLocW(i+1,j)
        Rj =(tracer( i ,j)-tracer(i-1,j))*maskLocW( i ,j)
        Rjm=(tracer(i-1,j)-tracer(i-2,j))*maskLocW(i-1,j)
        IF (Rj.NE.0.) THEN
         IF (uTrans(i,j).GT.0) THEN
           Cr=Rjm/Rj
         ELSE
           Cr=Rjp/Rj
         ENDIF
        ELSE
         IF (uTrans(i,j).GT.0) THEN
           Cr=Rjm*1.E20
         ELSE
           Cr=Rjp*1.E20
         ENDIF
        ENDIF
        Cr=Limiter(Cr)
        uT(i,j) = 
     &   uTrans(i,j)*(Tracer(i,j)+Tracer(i-1,j))*0.5d0
     &   -0.5*(
     &        (1-Cr)*ABS(uTrans(i,j))
     &        +uTrans(i,j)*uFld*deltaTloc
     &         *recip_dxC(i,j,bi,bj)*Cr
     &        )*Rj
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_FLUXLIMIT_ADV_Y( 
     I           bi,bj,k,deltaTloc,
     I           vTrans, vVel,
     I           maskLocS, tracer,
     O           vT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 deltaTloc
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vVel  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 maskLocS(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 vT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      Real*8 Cr,Rjm,Rj,Rjp
      Real*8 vFld
      Real*8 Limiter
      Limiter(Cr)=max(0.d0,max(min(1.d0,2.d0*Cr),
     &                         min(2.d0,Cr))) 
      DO i=1-Olx,sNx+Olx
       vT(i,1-Oly)=0.
       vT(i,2-Oly)=0.
       vT(i,sNy+Oly)=0.
      ENDDO
      DO j=1-Oly+2,sNy+Oly-1
       DO i=1-Olx,sNx+Olx
        vFld = vTrans(i,j)*recip_dxG(i,j,bi,bj)
     &       *recip_drF(k)*recip_hFacS(i,j,k,bi,bj)
        Rjp=(tracer(i,j+1)-tracer(i, j ))*maskLocS(i,j+1)
        Rj =(tracer(i, j )-tracer(i,j-1))*maskLocS(i, j )
        Rjm=(tracer(i,j-1)-tracer(i,j-2))*maskLocS(i,j-1)
        IF (Rj.NE.0.) THEN
         IF (vTrans(i,j).GT.0) THEN
           Cr=Rjm/Rj
         ELSE
           Cr=Rjp/Rj
         ENDIF
        ELSE
         IF (vTrans(i,j).GT.0) THEN
           Cr=Rjm*1.E20
         ELSE
           Cr=Rjp*1.E20
         ENDIF
        ENDIF
        Cr=Limiter(Cr)
        vT(i,j) = 
     &   vTrans(i,j)*(Tracer(i,j)+Tracer(i,j-1))*0.5d0
     &   -0.5*(
     &        (1-Cr)*ABS(vTrans(i,j))
     &        +vTrans(i,j)*vFld*deltaTloc
     &         *recip_dyC(i,j,bi,bj)*Cr
     &        )*Rj
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_GRAD_X( 
     I           bi,bj,k,
     I           xA,
     U           tracer,
     O           dTdx,
     I           myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 xA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dTdx  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Oly,sNy+Oly
       dTdx(1-Olx,j)=0.
       DO i=1-Olx+1,sNx+Olx
        dTdx(i,j) = recip_dxC(i,j,bi,bj)*xA(i,j)
     &               *(tracer(i,j)-tracer(i-1,j))
     &               *sqCosFacU(j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_GRAD_Y( 
     I           bi,bj,k,
     I           yA,
     U           tracer,
     O           dTdy,
     I           myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 yA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dTdy  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO i=1-Olx,sNx+Olx
       dTdy(I,1-Oly)=0.
      ENDDO
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx,sNx+Olx
        dTdy(i,j) = recip_dyC(i,j,bi,bj)*yA(i,j)
     &               *(tracer(i,j)-tracer(i,j-1))
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_U3_ADV_R( 
     I           bi,bj,k,
     I           rTrans,
     I           tracer,
     O           wT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      Real*8 wT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,kp1,km1,km2
      Real*8 Rjm,Rj,Rjp,Rjjm,Rjjp
      km2=MAX(1,k-2)
      km1=MAX(1,k-1)
      kp1=MIN(Nr,k+1)
      IF ( k.EQ.1 .OR. k.GT.Nr ) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         wT(i,j) = 0.
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         Rjp=(tracer(i,j,kp1,bi,bj)-tracer(i,j,k,bi,bj))
     &        *maskC(i,j,kp1,bi,bj)
         Rj=(tracer(i,j,k,bi,bj)-tracer(i,j,km1,bi,bj))
         Rjm=(tracer(i,j,km1,bi,bj)-tracer(i,j,km2,bi,bj))
     &        *maskC(i,j,km2,bi,bj)
         Rjjp=Rjp-Rj
         Rjjm=Rj-Rjm
         wT(i,j) = maskC(i,j,km1,bi,bj)*(
     &     rTrans(i,j)*(
     &        (Tracer(i,j,k,bi,bj)+Tracer(i,j,km1,bi,bj))*0.5d0
     &        -oneSixth*(Rjjm+Rjjp)*0.5d0  )
     &    +ABS(rTrans(i,j))*
     &         oneSixth*(Rjjm-Rjjp)*0.5d0
     &                                  )
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE GAD_U3_ADV_X( 
     I           bi,bj,k,
     I           uTrans,
     I           tracer,
     O           uT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 uT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      Real*8 Rjm,Rj,Rjp,Rjjm,Rjjp
      DO j=1-Oly,sNy+Oly
       uT(1-Olx,j)=0.
       uT(2-Olx,j)=0.
       uT(sNx+Olx,j)=0.
       DO i=1-Olx+2,sNx+Olx-1
        Rjp=(tracer(i+1,j)-tracer(i,j))*maskW(i+1,j,k,bi,bj)
        Rj =(tracer(i,j)-tracer(i-1,j))*maskW(i,j,k,bi,bj)
        Rjm=(tracer(i-1,j)-tracer(i-2,j))*maskW(i-1,j,k,bi,bj)
        Rjjp=Rjp-Rj
        Rjjm=Rj-Rjm
        uT(i,j) = 
     &   uTrans(i,j)*(
     &     Tracer(i,j)+Tracer(i-1,j)-oneSixth*( Rjjp+Rjjm )
     &               )*0.5d0
     &  +ABS( uTrans(i,j) )*0.5d0*oneSixth*( Rjjp-Rjjm )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GAD_U3_ADV_Y( 
     I           bi,bj,k,
     I           vTrans,
     I           tracer,
     O           vT,
     I           myThid )
       USE SIZE_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,k
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 vT    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      Real*8 Rjm,Rj,Rjp,Rjjm,Rjjp
      DO i=1-Olx,sNx+Olx
       vT(i,1-Oly)=0.
       vT(i,2-Oly)=0.
       vT(i,sNy+Oly)=0.
      ENDDO
      DO j=1-Oly+2,sNy+Oly-1
       DO i=1-Olx,sNx+Olx
        Rjp=(tracer(i,j+1)-tracer(i,j))*maskS(i,j+1,k,bi,bj)
        Rj =(tracer(i,j)-tracer(i,j-1))*maskS(i,j,k,bi,bj)
        Rjm=(tracer(i,j-1)-tracer(i,j-2))*maskS(i,j-1,k,bi,bj)
        Rjjp=Rjp-Rj
        Rjjm=Rj-Rjm
        vT(i,j) = 
     &   vTrans(i,j)*(
     &     Tracer(i,j)+Tracer(i,j-1)-oneSixth*( Rjjp+Rjjm )
     &               )*0.5d0
     &  +ABS( vTrans(i,j) )*0.5d0*oneSixth*( Rjjp-Rjjm )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_CALC_RTRANS( 
     I                          k, bi, bj,
     O                          rTransU, rTransV,
     I                          myTime, myIter, myThid)
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER k, bi, bj, myIter, myThid
      Real*8 myTime
      Real*8 rTransU(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTransV(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
       IF ( k.GT.Nr ) THEN
        DO j=1-OLy+1,sNy+OLy
         DO i=1-OLx+1,sNx+OLx
          rTransU(i,j) = 0.
          rTransV(i,j) = 0.
         ENDDO
        ENDDO
      ELSE
        DO j=1-OLy+1,sNy+OLy
         DO i=1-OLx+1,sNx+OLx
          rTransU(i,j) =
     &      0.5d0*( wVel(i-1,j,k,bi,bj)*rA(i-1,j,bi,bj)
     &                +wVel( i ,j,k,bi,bj)*rA( i ,j,bi,bj) )
          rTransV(i,j) =
     &      0.5d0*( wVel(i,j-1,k,bi,bj)*rA(i,j-1,bi,bj)
     &                +wVel(i, j ,k,bi,bj)*rA(i, j ,bi,bj) )
         ENDDO
        ENDDO
      ENDIF           
      RETURN
      END
      SUBROUTINE MOM_FLUXFORM( 
     I        bi,bj,iMin,iMax,jMin,jMax,k,kUp,kDown,
     I        KappaRU, KappaRV,
     U        fVerU, fVerV,
     O        guDiss, gvDiss,
     I        myTime, myIter, myThid)
       USE SIZE_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k,kUp,kDown
      Real*8 KappaRU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 KappaRV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 fVerU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 fVerV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 guDiss(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 gvDiss(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8     myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER i,j
      Real*8 vF(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 v4F(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 cF(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 mT(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fZon(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fMer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fVrUp(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fVrDw(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8    hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  r_hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8      xA(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8      yA(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  rTransU(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  rTransV(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 KE(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 strain(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tension(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  uDudxFac
      Real*8  AhDudxFac
      Real*8  vDudyFac
      Real*8  AhDudyFac
      Real*8  rVelDudrFac
      Real*8  ArDudrFac
      Real*8  fuFac
      Real*8  mtFacU
      Real*8  uDvdxFac
      Real*8  AhDvdxFac
      Real*8  vDvdyFac
      Real*8  AhDvdyFac
      Real*8  rVelDvdrFac
      Real*8  ArDvdrFac
      Real*8  fvFac
      Real*8  mtFacV
      LOGICAL bottomDragTerms
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        vF(i,j)   = 0.
        v4F(i,j)  = 0.
        cF(i,j)   = 0.
        mT(i,j)   = 0.
        fZon(i,j) = 0.
        fMer(i,j) = 0.
        fVrUp(i,j)= 0.
        fVrDw(i,j)= 0.
        rTransU(i,j)= 0.
        rTransV(i,j)= 0.
        strain(i,j) = 0.
        tension(i,j)= 0.
        guDiss(i,j) = 0.
        gvDiss(i,j) = 0.
       ENDDO
      ENDDO
      uDudxFac     = afFacMom*1.
      AhDudxFac    = vfFacMom*1.
      vDudyFac     = afFacMom*1.
      AhDudyFac    = vfFacMom*1.
      rVelDudrFac  = afFacMom*1.
      ArDudrFac    = vfFacMom*1.
      mTFacU       = mtFacMom*1.
      fuFac        = cfFacMom*1.
      uDvdxFac     = afFacMom*1.
      AhDvdxFac    = vfFacMom*1.
      vDvdyFac     = afFacMom*1.
      AhDvdyFac    = vfFacMom*1.
      rVelDvdrFac  = afFacMom*1.
      ArDvdrFac    = vfFacMom*1.
      mTFacV       = mtFacMom*1.
      fvFac        = cfFacMom*1.
      IF (implicitViscosity) THEN
        ArDudrFac  = 0.
        ArDvdrFac  = 0.
      ENDIF
      IF (     no_slip_bottom
     &    .OR. bottomDragQuadratic.NE.0.
     &    .OR. bottomDragLinear.NE.0.) THEN
       bottomDragTerms=.TRUE.
      ELSE
       bottomDragTerms=.FALSE.
      ENDIF
      CALL MOM_CALC_HFACZ(bi,bj,k,hFacZ,r_hFacZ,myThid)
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        xA(i,j) = dyG(i,j,bi,bj)
     &   *drF(k)*hFacW(i,j,k,bi,bj)
        yA(i,j) = dxG(i,j,bi,bj)
     &   *drF(k)*hFacS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        uFld(i,j) = uVel(i,j,k,bi,bj)
        vFld(i,j) = vVel(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        uTrans(i,j) = uFld(i,j)*xA(i,j)
        vTrans(i,j) = vFld(i,j)*yA(i,j)
       ENDDO
      ENDDO
      IF (bottomDragTerms) THEN
        CALL MOM_CALC_KE(bi,bj,k,3,uFld,vFld,KE,myThid)
      ENDIF
      IF (viscAstrain.NE.0. .OR. viscAtension.NE.0.) THEN
         CALL MOM_CALC_TENSION(bi,bj,k,uFld,vFld,
     O                         tension,
     I                         myThid)
         CALL MOM_CALC_STRAIN(bi,bj,k,uFld,vFld,hFacZ,
     O                        strain,
     I                        myThid)
      ENDIF
      IF (momAdvection.AND.k.EQ.1) THEN
        CALL MOM_CALC_RTRANS( k, bi, bj,
     O                        rTransU, rTransV,
     I                        myTime, myIter, myThid)
        CALL MOM_U_ADV_WU( bi,bj,k,uVel,wVel,rTransU,
     O                     fVerU(1-OLx,1-OLy,kUp), myThid )
        CALL MOM_V_ADV_WV( bi,bj,k,vVel,wVel,rTransV,
     O                     fVerV(1-OLx,1-OLy,kUp), myThid )
      ENDIF
      IF (momAdvection) THEN
        CALL MOM_CALC_RTRANS( k+1, bi, bj,
     O                        rTransU, rTransV,
     I                        myTime, myIter, myThid)
      ENDIF
      IF (momAdvection) THEN
        CALL MOM_U_ADV_UU(bi,bj,k,uTrans,uFld,fZon,myThid)
        CALL MOM_U_ADV_VU(bi,bj,k,vTrans,uFld,fMer,myThid)
        CALL MOM_U_ADV_WU(
     I                     bi,bj,k+1,uVel,wVel,rTransU,
     O                     fVerU(1-OLx,1-OLy,kDown), myThid )
        DO j=jMin,jMax
         DO i=iMin,iMax
          gU(i,j,k,bi,bj) =
     &     -recip_hFacW(i,j,k,bi,bj)*recip_drF(k)
     &     *recip_rAw(i,j,bi,bj)
     &    *( ( fZon(i,j  )     - fZon(i-1,j) )*uDudxFac
     &      +( fMer(i,j+1)     - fMer(i,  j) )*vDudyFac
     &      +(fVerU(i,j,kDown) - fVerU(i,j,kUp))*rkSign*rVelDudrFac
     &     )
         ENDDO
        ENDDO
      ELSE
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
           gU(i,j,k,bi,bj) = 0.d0
         ENDDO
        ENDDO
      ENDIF
      IF (momViscosity) THEN
        IF ( viscA4.NE.0. ) 
     &  CALL MOM_U_DEL2U(bi,bj,k,uFld,hFacZ,v4f,myThid)
        CALL MOM_U_XVISCFLUX(bi,bj,k,uFld,v4F,fZon,myThid)
        CALL MOM_U_YVISCFLUX(bi,bj,k,uFld,v4F,hFacZ,fMer,myThid)
       IF (.NOT.implicitViscosity) THEN
        CALL MOM_U_RVISCFLUX(bi,bj, k, uVel,KappaRU,fVrUp,myThid)
        CALL MOM_U_RVISCFLUX(bi,bj,k+1,uVel,KappaRU,fVrDw,myThid)
       ENDIF
        DO j=jMin,jMax
         DO i=iMin,iMax
          guDiss(i,j) =
     &     -recip_hFacW(i,j,k,bi,bj)*recip_drF(k)
     &     *recip_rAw(i,j,bi,bj)
     &    *( ( fZon(i,j  ) - fZon(i-1,j) )*AhDudxFac
     &      +( fMer(i,j+1) - fMer(i,  j) )*AhDudyFac
     &      +( fVrDw(i,j)  - fVrUp(i,j) )*rkSign*ArDudrFac
     &     )
         ENDDO
        ENDDO
        IF (no_slip_sides) THEN
         CALL MOM_U_SIDEDRAG(bi,bj,k,uFld,v4F,hFacZ,vF,myThid)
         DO j=jMin,jMax
          DO i=iMin,iMax
           gUdiss(i,j) = gUdiss(i,j) + vF(i,j)
          ENDDO
         ENDDO
        ENDIF
        IF (bottomDragTerms) THEN
         CALL MOM_U_BOTTOMDRAG(bi,bj,k,uFld,KE,KappaRU,vF,myThid)
         DO j=jMin,jMax
          DO i=iMin,iMax
           gUdiss(i,j) = gUdiss(i,j) + vF(i,j)
          ENDDO
         ENDDO
        ENDIF
      ENDIF
      IF (useNHMTerms) THEN
       CALL MOM_U_METRIC_NH(bi,bj,k,uFld,wVel,mT,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)+mTFacU*mT(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF (usingSphericalPolarMTerms) THEN
       CALL MOM_U_METRIC_SPHERE(bi,bj,k,uFld,vFld,mT,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)+mTFacU*mT(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF (usingCylindricalGrid) THEN
         CALL MOM_U_METRIC_CYLINDER(bi,bj,k,uFld,vFld,mT,myThid)
         DO j=jMin,jMax
          DO i=iMin,iMax
             gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)+mTFacU*mT(i,j)
          ENDDO
       ENDDO
      ENDIF
      IF (momAdvection) THEN
        CALL MOM_V_ADV_UV(bi,bj,k,uTrans,vFld,fZon,myThid)
        CALL MOM_V_ADV_VV(bi,bj,k,vTrans,vFld,fMer,myThid)
        CALL MOM_V_ADV_WV(
     I                     bi,bj,k+1,vVel,wVel,rTransV,
     O                     fVerV(1-OLx,1-OLy,kDown), myThid )
        DO j=jMin,jMax
         DO i=iMin,iMax
          gV(i,j,k,bi,bj) =
     &     -recip_hFacS(i,j,k,bi,bj)*recip_drF(k)
     &      *recip_rAs(i,j,bi,bj)
     &    *( ( fZon(i+1,j)     - fZon(i,j  ) )*uDvdxFac
     &      +( fMer(i,  j)     - fMer(i,j-1) )*vDvdyFac
     &      +(fVerV(i,j,kDown) - fVerV(i,j,kUp))*rkSign*rVelDvdrFac
     &     )
       ENDDO
      ENDDO
      ELSE
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
           gV(i,j,k,bi,bj) = 0.d0
         ENDDO
        ENDDO
      ENDIF
      IF (momViscosity) THEN
        IF ( viscA4.NE.0. ) 
     &  CALL MOM_V_DEL2V(bi,bj,k,vFld,hFacZ,v4f,myThid)
        CALL MOM_V_XVISCFLUX(bi,bj,k,vFld,v4f,hFacZ,fZon,myThid)
        CALL MOM_V_YVISCFLUX(bi,bj,k,vFld,v4f,fMer,myThid)
       IF (.NOT.implicitViscosity) THEN
        CALL MOM_V_RVISCFLUX(bi,bj, k, vVel,KappaRV,fVrUp,myThid)
        CALL MOM_V_RVISCFLUX(bi,bj,k+1,vVel,KappaRV,fVrDw,myThid)
       ENDIF
        DO j=jMin,jMax
         DO i=iMin,iMax
          gvDiss(i,j) =
     &     -recip_hFacS(i,j,k,bi,bj)*recip_drF(k)
     &      *recip_rAs(i,j,bi,bj)
     &    *( ( fZon(i+1,j)  - fZon(i,j  ) )*AhDvdxFac
     &      +( fMer(i,  j)  - fMer(i,j-1) )*AhDvdyFac
     &      +( fVrDw(i,j)   - fVrUp(i,j) )*rkSign*ArDvdrFac
     &     )
         ENDDO
        ENDDO
      IF (no_slip_sides) THEN
         CALL MOM_V_SIDEDRAG(bi,bj,k,vFld,v4F,hFacZ,vF,myThid)
         DO j=jMin,jMax
          DO i=iMin,iMax
           gvDiss(i,j) = gvDiss(i,j) + vF(i,j)
          ENDDO
         ENDDO
        ENDIF
        IF (bottomDragTerms) THEN
         CALL MOM_V_BOTTOMDRAG(bi,bj,k,vFld,KE,KappaRV,vF,myThid)
         DO j=jMin,jMax
          DO i=iMin,iMax
           gvDiss(i,j) = gvDiss(i,j) + vF(i,j)
          ENDDO
         ENDDO
        ENDIF
      ENDIF
      IF (useNHMTerms) THEN
       CALL MOM_V_METRIC_NH(bi,bj,k,vFld,wVel,mT,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)+mTFacV*mT(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF (usingSphericalPolarMTerms) THEN
       CALL MOM_V_METRIC_SPHERE(bi,bj,k,uFld,mT,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)+mTFacV*mT(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF (usingCylindricalGrid) THEN
         CALL MOM_V_METRIC_CYLINDER(bi,bj,k,uFld,vFld,mT,myThid)
         DO j=jMin,jMax
            DO i=iMin,iMax
               gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)+mTFacV*mT(i,j)
            ENDDO
         ENDDO
      ENDIF
      IF (.NOT.useCDscheme) THEN
        CALL MOM_U_CORIOLIS(bi,bj,k,vFld,cf,myThid)
        DO j=jMin,jMax
         DO i=iMin,iMax
          gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)+fuFac*cf(i,j)
         ENDDO
        ENDDO
        CALL MOM_V_CORIOLIS(bi,bj,k,uFld,cf,myThid)
        DO j=jMin,jMax
         DO i=iMin,iMax
          gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)+fvFac*cf(i,j)
         ENDDO
        ENDDO
      ENDIF
      IF (nonHydrostatic.OR.quasiHydrostatic) THEN
       CALL MOM_U_CORIOLIS_NH(bi,bj,k,wVel,cf,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)+fuFac*cf(i,j)
        ENDDO
       ENDDO
      ENDIF
      DO j=jMin,jMax
       DO i=iMin,iMax
        gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)*maskW(i,j,k,bi,bj)
        guDiss(i,j)     = guDiss(i,j)    *maskW(i,j,k,bi,bj)
        gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)*maskS(i,j,k,bi,bj)
        gvDiss(i,j)     = gvDiss(i,j)    *maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_ADV_UU(
     I        bi,bj,k,
     I        uTrans, uFld,
     O        AdvectFluxUU,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 AdvectFluxUU(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        AdvectFluxUU(i,j) =
     &  0.25*( uTrans(i,j) + uTrans(i+1,j) )
     &      *(   uFld(i,j) +   uFld(i+1,j) )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_ADV_VU(
     I        bi,bj,k,
     I        vTrans, uFld,
     O        AdvectFluxVU,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 AdvectFluxVU(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        AdvectFluxVU(i,j) =
     &  0.25*( vTrans(i,j) + vTrans(i-1,j) )
     &      *( uFld(i,j) + uFld(i,j-1) )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_ADV_WU(
     I        bi,bj,k,
     I        uFld,wFld,rTrans,
     O        advectiveFluxWU,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 wFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 advectiveFluxWU(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 tmpFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      IF ( k.EQ.Nr+1 .AND.
     &     useRealFreshWaterFlux .AND. usingPCoords ) THEN
       DO j=1-Oly+1,sNy+Oly
        DO i=1-Olx+1,sNx+Olx
         advectiveFluxWU(i,j) = rTrans(i,j)*uFld(i,j,k-1,bi,bj) 
        ENDDO
       ENDDO
      ELSEIF ( k.GT.Nr .OR. (k.EQ.1.AND.rigidLid) ) THEN
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        advectiveFluxWU(i,j) = 0.
       ENDDO
      ENDDO
      ELSEIF (k.EQ.1) THEN
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        advectiveFluxWU(i,j) = rTrans(i,j)*uFld(i,j,k,bi,bj) 
       ENDDO
      ENDDO
      ELSE
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        advectiveFluxWU(i,j) = rTrans(i,j)*
     &   0.5d0*( uFld(i,j,k,bi,bj)+uFld(i,j,k-1,bi,bj) )
       ENDDO
      ENDDO
      IF ( select_rStar.EQ.0 .AND. .NOT.rigidLid ) THEN
        DO j=1-Oly+1,sNy+Oly
         DO i=1-Olx+1,sNx+Olx
          advectiveFluxWU(i,j) = advectiveFluxWU(i,j)
     &     +0.25*(
     &          wFld(i, j ,k,bi,bj)*rA(i, j ,bi,bj)*
     &          (maskC(i,j,k,bi,bj) - maskC(i,j,k-1,bi,bj))
     &         +wFld(i-1,j,k,bi,bj)*rA(i-1,j,bi,bj)*
     &          (maskC(i-1,j,k,bi,bj)-maskC(i-1,j,k-1,bi,bj))
     &           )*uFld(i,j,k,bi,bj)
         ENDDO
        ENDDO
      ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_U_CORIOLIS( 
     I        bi,bj,k,vFld,
     U        uCoriolisTerm,
     I        myThid)
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER bi,bj,K
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 uCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 one
      PARAMETER(one=1.d0)
      IF (useEnergyConservingCoriolis) THEN
       DO j=1-Oly,sNy+Oly-1
        DO i=1-Olx+1,sNx+Olx
         uCoriolisTerm(i,j) =
     &     0.5*( fCori( i ,j,bi,bj)
     &          *0.5*( vFld( i ,j)+vFld( i ,j+1) )
     &         + fCori(i-1,j,bi,bj)
     &          *0.5*( vFld(i-1,j)+vFld(i-1,j+1) ) )
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly-1
        DO i=1-Olx+1,sNx+Olx
         uCoriolisTerm(i,j) =
     &     0.5*( fCori( i ,j,bi,bj) +
     &           fCori(i-1,j,bi,bj)  )
     &   *0.25*(
     &     vFld( i ,j)+vFld( i ,j+1)
     &    +vFld(i-1,j)+vFld(i-1,j+1)
     &         )
        ENDDO
       ENDDO
      ENDIF
      IF (useJamartWetPoints) THEN
       DO j=1-Oly,sNy+Oly-1
        DO i=1-Olx+1,sNx+Olx
         uCoriolisTerm(i,j) = uCoriolisTerm(i,j)
     & *4.d0/max(one, maskS( i , j ,k,bi,bj)+maskS( i ,j+1,k,bi,bj)
     &               +maskS(i-1, j ,k,bi,bj)+maskS(i-1,j+1,k,bi,bj) )
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_U_CORIOLIS_NH( 
     I        bi,bj,k,wFld,
     U        uCoriolisTerm,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,K
      Real*8 wFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      Real*8 uCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,kp1
      Real*8 wMsk
      kp1=min(k+1,Nr)
      wMsk=1.
      IF (k.EQ.Nr) wMsk=0.
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx
        uCoriolisTerm(i,j) =
     &    0.5*( fCoriCos( i ,j,bi,bj)
     &         *0.5*( wFld( i ,j,k,bi,bj)+wFld( i ,j,kp1,bi,bj)*wMsk )
     &        + fCoriCos(i-1,j,bi,bj)
     &         *0.5*( wFld(i-1,j,k,bi,bj)+wFld(i-1,j,kp1,bi,bj)*wMsk ) )
     &    *gravitySign*recip_horiVertRatio
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_DEL2U(
     I        bi,bj,k,
     I        uFld, hFacZ,
     O        del2u,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 del2u(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 fZon(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fMer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZClosedS,hFacZClosedN
      DO j=1-Oly+1,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        fZon(i,j) = drF(k)*hFacC(i,j,k,bi,bj)
     &   *dyF(i,j,bi,bj)
     &   *recip_dxF(i,j,bi,bj)
     &   *(uFld(i+1,j)-uFld(i,j))
       ENDDO
      ENDDO
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx+1,sNx+Olx-1
        fMer(i,j) = drF(k)*hFacZ(i,j)
     &   *dxV(i,j,bi,bj)
     &   *recip_dyU(i,j,bi,bj)
     &   *(uFld(i,j)-uFld(i,j-1))
       ENDDO
      ENDDO
      DO j=1-Oly+1,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx-1
        del2u(i,j) =
     &  recip_drF(k)*recip_hFacW(i,j,k,bi,bj)
     &  *recip_rAw(i,j,bi,bj)
     &  *( fZon(i,j  )    - fZon(i-1,j)
     &    +fMer(i,j+1)    - fMer(i  ,j)
     &   )*maskW(i,j,k,bi,bj)
       ENDDO
      ENDDO
      IF (no_slip_sides) THEN
      DO j=1-Oly+1,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx-1
        hFacZClosedS = hFacW(i,j,k,bi,bj) - hFacZ(i,j)
        hFacZClosedN = hFacW(i,j,k,bi,bj) - hFacZ(i,j+1)
        del2u(i,j) = del2u(i,j)
     &  - recip_hFacW(i,j,k,bi,bj)*recip_drF(k)
     &   *recip_rAw(i,j,bi,bj)
     &   *( hFacZClosedS*dxV(i, j ,bi,bj)
     &     *recip_dyU(i, j ,bi,bj)
     &     +hFacZClosedN*dxV(i,j+1,bi,bj)
     &     *recip_dyU(i,j+1,bi,bj)
     &    )*drF(k)*2.*uFld(i,j)
     &     *maskW(i,j,k,bi,bj)
       ENDDO
      ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_U_METRIC_CYLINDER(
     I        bi,bj,k,
     I        uFld, vFld,
     O        uMetricTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 uMetricTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      Real*8 radius
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx
          radius = (yG(i,j,bi,bj)+yG(i,j+1,bi,bj))*0.5d0
          IF ( radius.GT.0. ) THEN
             uMetricTerms(i,j) = 
     &            uFld(i,j)
     &            *0.25*(vFld(i,j) + vFld(i-1,j) +
     &                   vFld(i,j+1)+vFld(i-1,j+1))/radius
          ELSE
             uMetricTerms(i,j) = 0.
          ENDIF
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_METRIC_NH(
     I        bi,bj,k,
     I        uFld, wFld,
     O        uMetricTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 wFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      Real*8 uMetricTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,Kp1
      Real*8 wVelBottomOverride
      Kp1=min(k+1,Nr)
      wVelBottomOverride=1.
      IF (k.EQ.Nr) wVelBottomOverride=0.
      DO j=1-Olx,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
         uMetricTerms(i,j) = uFld(i,j)*recip_RSphere
     &    *0.25*(wVelBottomOverride*
     &            (wFld(i-1,j,kp1,bi,bj)+wFld(i,j,kp1,bi,bj))
     &            +wFld(i-1,j, k ,bi,bj)+wFld(i,j, k ,bi,bj)
     &          )*recip_horiVertRatio*gravitySign
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_METRIC_SPHERE(
     I        bi,bj,k,
     I        uFld, vFld,
     O        uMetricTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 uMetricTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Olx,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx
         uMetricTerms(i,j) = 
     &    uFld(i,j)*recip_RSphere
     &    *0.25*( vFld(i,j  )+vFld(i-1,j  )
     &           +vFld(i,j+1)+vFld(i-1,j+1)
     &          )*tanPhiAtU(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_XVISCFLUX(
     I        bi,bj,k,
     I        uFld, del2u,
     O        xViscFluxU,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2u(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 xViscFluxU(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        xViscFluxU(i,j) =
     &    dyF(i,j,bi,bj)*drF(k)*hFacC(i,j,k,bi,bj)
     &     *(
     &       -viscAh*(uFld(i+1,j)-uFld(i,j))
     &       *cosFacU(J,bi,bj)
     &       +viscA4*(del2u(i+1,j)       -del2u(i,j)       )
     &       *cosFacU(J,bi,bj)
     &      )*recip_dxF(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_YVISCFLUX(
     I        bi,bj,k,
     I        uFld, del2u, hFacZ,
     O        yViscFluxU,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2u(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 yViscFluxU(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx,sNx+Olx
        yViscFluxU(i,j) =
     &     dxV(i,j,bi,bj)*drF(k)*hFacZ(i,j)
     &     *(
     &       -viscAh*(uFld(i,j)-uFld(i,j-1))
     &       +viscA4*(del2u(i,j)       -del2u(i,j-1)       )
     &      )*recip_dyU(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_ADV_UV(
     I        bi,bj,k,
     I        uTrans, vFld,
     O        AdvectFluxUV,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 AdvectFluxUV(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        AdvectFluxUV(i,j) =
     &  0.25*( uTrans(i,j) + uTrans(i,j-1) )
     &      *(   vFld(i,j) +   vFld(i-1,j) )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_ADV_VV(
     I        bi,bj,k,
     I        vTrans, vFld,
     O        AdvectFluxVV,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 AdvectFluxVV(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        AdvectFluxVV(i,j) =
     &  0.25*( vTrans(i,j) + vTrans(i,j+1) )
     &      *(   vFld(i,j) +   vFld(i,j+1) )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_ADV_WV(
     I        bi,bj,k,
     I        vFld,wFld,rTrans,
     O        advectiveFluxWV,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 wFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 advectiveFluxWV(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 tmpFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      IF ( k.EQ.Nr+1 .AND.
     &     useRealFreshWaterFlux .AND. usingPCoords ) THEN
       DO j=1-Oly+1,sNy+Oly
        DO i=1-Olx+1,sNx+Olx
         advectiveFluxWV(i,j) = rTrans(i,j)*vFld(i,j,k-1,bi,bj)
        ENDDO
       ENDDO
      ELSEIF ( k.GT.Nr .OR. (k.EQ.1.AND.rigidLid) ) THEN
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        advectiveFluxWV(i,j) = 0.
       ENDDO
      ENDDO
      ELSEIF (k.EQ.1) THEN
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        advectiveFluxWV(i,j) = rTrans(i,j)*vFld(i,j,k,bi,bj)
       ENDDO
      ENDDO
      ELSE
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        advectiveFluxWV(i,j) = rTrans(i,j)*
     &   0.5d0*( vFld(i,j,k,bi,bj)+vFld(i,j,k-1,bi,bj) ) 
       ENDDO
      ENDDO
      IF ( select_rStar.EQ.0 .AND. .NOT.rigidLid ) THEN
        DO j=1-Oly+1,sNy+Oly
         DO i=1-Olx+1,sNx+Olx
          advectiveFluxWV(i,j) = advectiveFluxWV(i,j)
     &     +0.25*(
     &          wFld(i, j ,k,bi,bj)*rA(i, j ,bi,bj)*
     &          (maskC(i,j,k,bi,bj) - maskC(i,j,k-1,bi,bj))
     &         +wFld(i,j-1,k,bi,bj)*rA(i,j-1,bi,bj)*
     &          (maskC(i,j-1,k,bi,bj)-maskC(i,j-1,k-1,bi,bj))
     &           )*vFld(i,j,k,bi,bj)
         ENDDO
        ENDDO
      ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_V_CORIOLIS( 
     I        bi,bj,k,uFld,
     U        vCoriolisTerm,
     I        myThid)
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER bi,bj,K
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 vCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 one
      PARAMETER(one=1.d0)
      IF (useEnergyConservingCoriolis) THEN
       DO j=1-Oly+1,sNy+Oly
        DO i=1-Olx,sNx+Olx-1
         vCoriolisTerm(i,j) =
     &    -0.5*( fCori(i, j ,bi,bj)
     &          *0.5*( uFld( i , j )+uFld(i+1, j ) )
     &         + fCori(i,j-1,bi,bj)
     &          *0.5*( uFld( i ,j-1)+uFld(i+1,j-1) ) )
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly+1,sNy+Oly
        DO i=1-Olx,sNx+Olx-1
        vCoriolisTerm(i,j) =
     &    -0.5*(fCori(i, j ,bi,bj)+fCori(i,j-1,bi,bj))
     &   *0.25*( uFld(i, j )+uFld(i+1, j )
     &          +uFld(i,j-1)+uFld(i+1,j-1)
     &         )
        ENDDO
       ENDDO
      ENDIF
      IF (useJamartWetPoints) THEN
       DO j=1-Oly+1,sNy+Oly
        DO i=1-Olx,sNx+Olx-1
         vCoriolisTerm(i,j) = vCoriolisTerm(i,j)
     & *4.d0/max(one, maskW( i , j ,k,bi,bj)+maskW(i+1, j ,k,bi,bj)
     &               +maskW( i ,j-1,k,bi,bj)+maskW(i+1,j-1,k,bi,bj) )
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_V_DEL2V(
     I        bi,bj,k,
     I        vFld, hFacZ,
     O        del2v,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 del2v(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 fZon(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fMer(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZClosedE,hFacZClosedW
      DO j=1-Oly+1,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx
        fZon(i,j) = drF(k)*hFacZ(i,j)
     &   *dyU(i,j,bi,bj)
     &   *recip_dxV(i,j,bi,bj)
     &   *(vFld(i,j)-vFld(i-1,j))
       ENDDO
      ENDDO
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx-1
        fMer(i,j) = drF(k)*hFacC(i,j,k,bi,bj)
     &   *dxF(i,j,bi,bj)
     &   *recip_dyF(i,j,bi,bj)
     &   *(vFld(i,j+1)-vFld(i,j))
       ENDDO
      ENDDO
      DO j=1-Oly+1,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx-1
        del2v(i,j) = recip_drF(k)*recip_hFacS(i,j,k,bi,bj)
     &  *recip_rAs(i,j,bi,bj)
     &  *( fZon(i+1,j)    - fZon(i, j )
     &    +fMer( i ,j)    - fMer(i,j-1)
     &   )*maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      IF (no_slip_sides) THEN
      DO j=1-Oly+1,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx-1
        hFacZClosedW = hFacS(i,j,k,bi,bj) - hFacZ(i,j)
        hFacZClosedE = hFacS(i,j,k,bi,bj) - hFacZ(i+1,j)
        del2v(i,j) = del2v(i,j)
     &  -recip_hFacS(i,j,k,bi,bj)*recip_drF(k)
     &  *recip_rAs(i,j,bi,bj)
     &   *( hFacZClosedW*dyU( i ,j,bi,bj)
     &      *recip_dxV( i ,j,bi,bj)
     &     +hFacZClosedE*dyU(i+1,j,bi,bj)
     &      *recip_dxV(i+1,j,bi,bj)
     &    )*drF(k)*2.*vFld(i,j)
     &      *maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_V_METRIC_CYLINDER(
     I        bi,bj,k,
     I        uFld, vFld,
     O        vMetricTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 vMetricTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      Real*8 radius
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx,sNx+Olx-1
          radius = (yG(i,j,bi,bj)+yG(i+1,j,bi,bj))*0.5d0
          IF ( radius.GT.0. ) THEN 
             vMetricTerms(i,j) = 
     &           -0.25*(uFld(i,j) + uFld(i+1,j) +
     &                  uFld(i,j-1)+uFld(i+1,j-1)) 
     &           *0.25*(uFld(i,j) + uFld(i+1,j) +
     &                  uFld(i,j-1)+uFld(i+1,j-1))/radius
          ELSE
             vMetricTerms(i,j) = 0.
          ENDIF
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_METRIC_NH(
     I        bi,bj,k,
     I        vFld,wFld,
     O        vMetricTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 wFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      Real*8 vMetricTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,Kp1
      Real*8 wVelBottomOverride
      Kp1=min(k+1,Nr)
      wVelBottomOverride=1.
      IF (k.EQ.Nr) wVelBottomOverride=0.
      DO j=1-Olx+1,sNy+Oly
       DO i=1-Olx,sNx+Olx
         vMetricTerms(i,j) = vFld(i,j)*recip_RSphere
     &    *0.25*(wVelBottomOverride*
     &           (wFld(i,j,kp1,bi,bj)+wFld(i,j-1,kp1,bi,bj))
     &           +wFld(i,j, k ,bi,bj)+wFld(i,j-1, k ,bi,bj)
     &          )*recip_horiVertRatio*gravitySign
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_METRIC_SPHERE(
     I        bi,bj,k,
     I        uFld,
     O        vMetricTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 vMetricTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Olx+1,sNy+Oly
       DO i=1-Olx,sNx+Olx-1
         vMetricTerms(i,j) = -recip_RSphere
     &    *0.25*( uFld(i,j  )+uFld(i+1,j  )
     &           +uFld(i,j-1)+uFld(i+1,j-1)
     &          )
     &    *0.25*( uFld(i,j  )+uFld(i+1,j  )
     &           +uFld(i,j-1)+uFld(i+1,j-1)
     &          )
     &    *tanPhiAtV(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_XVISCFLUX(
     I        bi,bj,k,
     I        vFld, del2v, hFacZ,
     O        xViscFluxV,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2v(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 xViscFluxV(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        xViscFluxV(i,j) =
     &     dyU(i,j,bi,bj)*drF(k)*hFacZ(i,j)
     &     *(
     &       -viscAh*(vFld(i,j)-vFld(i-1,j))
     &       *cosFacV(J,bi,bj)
     &       +viscA4*(del2v(i,j)       -del2v(i-1,j)       )
     &      *cosFacV(J,bi,bj)
     &      )*recip_dxV(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_YVISCFLUX(
     I        bi,bj,k,
     I        vFld, del2v,
     O        yViscFluxV,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2v(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 yViscFluxV(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        yViscFluxV(i,j) =
     & dxF(i,j,bi,bj)*drF(k)*hFacC(i,j,k,bi,bj)
     &     *(
     &       -viscAh*(vFld(i,j+1)-vFld(i,j))
     &       +viscA4*(del2v(i,j+1)       -del2v(i,j)       )
     &      )*recip_dyF(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_VECINV( 
     I        bi,bj,iMin,iMax,jMin,jMax,k,kUp,kDown,
     I        KappaRU, KappaRV,
     U        fVerU, fVerV,
     O        guDiss, gvDiss,
     I        myTime, myIter, myThid)
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      Real*8 KappaRU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 KappaRV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 fVerU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 fVerV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 guDiss(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 gvDiss(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER kUp,kDown
      Real*8     myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      LOGICAL  DIFFERENT_MULTIPLE
      EXTERNAL DIFFERENT_MULTIPLE
      Real*8      vF (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8      vrF (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8      uCf (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8      vCf (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2u(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2v(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tension(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 strain(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 r_hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dStar(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 zStar(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j,k
      Real*8  ArDudrFac
      Real*8  ArDvdrFac
      LOGICAL bottomDragTerms
      LOGICAL writeDiag
      Real*8 KE(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 omega3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vort3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hDiv(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      fVerU(1,1,kUp) = fVerU(1,1,kUp)
      fVerV(1,1,kUp) = fVerV(1,1,kUp)
      writeDiag = DIFFERENT_MULTIPLE(diagFreq, myTime, deltaTClock)
      DO J=1-OLy,sNy+OLy
       DO I=1-OLx,sNx+OLx
        vF(i,j)    = 0.
        vrF(i,j)   = 0.
        uCf(i,j)   = 0.
        vCf(i,j)   = 0.
        del2u(i,j) = 0.
        del2v(i,j) = 0.
        dStar(i,j) = 0.
        zStar(i,j) = 0.
        guDiss(i,j)= 0.
        gvDiss(i,j)= 0.
        vort3(i,j) = 0.
        omega3(i,j)= 0.
        ke(i,j)    = 0.
        strain(i,j)  = 0.d0
        tension(i,j) = 0.d0
       ENDDO
      ENDDO
      ArDudrFac    = vfFacMom*1.
      ArDvdrFac    = vfFacMom*1.
      IF (     no_slip_bottom
     &    .OR. bottomDragQuadratic.NE.0.
     &    .OR. bottomDragLinear.NE.0.) THEN
       bottomDragTerms=.TRUE.
      ELSE
       bottomDragTerms=.FALSE.
      ENDIF
      CALL MOM_CALC_HFACZ(bi,bj,k,hFacZ,r_hFacZ,myThid)
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        uFld(i,j) = uVel(i,j,k,bi,bj)
        vFld(i,j) = vVel(i,j,k,bi,bj)
       ENDDO
      ENDDO
      CALL MOM_CALC_KE(bi,bj,k,2,uFld,vFld,KE,myThid)
      CALL MOM_CALC_HDIV(bi,bj,k,2,uFld,vFld,hDiv,myThid)
      CALL MOM_CALC_RELVORT3(bi,bj,k,uFld,vFld,hFacZ,vort3,myThid)
      IF (useAbsVorticity)
     & CALL MOM_CALC_ABSVORT3(bi,bj,k,vort3,omega3,myThid)
      IF (momViscosity) THEN
       IF ( (viscA4.NE.0. .AND. no_slip_sides)
     &     .OR. viscA4D.NE.0. .OR. viscA4Z.NE.0.
     &     .OR. viscA4Grid.NE.0.
     &     .OR. viscC4leith.NE.0.
     &     .OR. viscC4leithD.NE.0.
     &    ) THEN
         CALL MOM_VI_DEL2UV(bi,bj,k,hDiv,vort3,hFacZ,
     O                      del2u,del2v,
     &                      myThid)
         CALL MOM_CALC_HDIV(bi,bj,k,2,del2u,del2v,dStar,myThid)
         CALL MOM_CALC_RELVORT3(
     &                         bi,bj,k,del2u,del2v,hFacZ,zStar,myThid)
       ENDIF
       IF (    viscAhD.NE.0. .OR. viscAhZ.NE.0. 
     &    .OR. viscA4D.NE.0. .OR. viscA4Z.NE.0.
     &    .OR. viscAhGrid.NE.0. .OR. viscA4Grid.NE.0.
     &    .OR. viscC2leith.NE.0. .OR. viscC4leith.NE.0.
     &    .OR. viscC2leithD.NE.0. .OR. viscC4leithD.NE.0.
     &    ) THEN
         CALL MOM_VI_HDISSIP(bi,bj,k,hDiv,vort3,hFacZ,dStar,zStar,
     O                       guDiss,gvDiss,
     &                       myThid)
       ENDIF
       IF (viscAstrain.NE.0. .OR. viscAtension.NE.0.
     O      .OR. viscC2smag.ne.0) THEN
         CALL MOM_CALC_TENSION(bi,bj,k,uFld,vFld,
     O                         tension,
     I                         myThid)
         CALL MOM_CALC_STRAIN(bi,bj,k,uFld,vFld,hFacZ,
     O                        strain,
     I                        myThid)
         CALL MOM_HDISSIP(bi,bj,k,
     I                    tension,strain,hFacZ,viscAtension,viscAstrain,
     O                    guDiss,gvDiss,
     I                    myThid)
       ENDIF
      ENDIF
      IF (momViscosity.AND..NOT.implicitViscosity) THEN
       CALL MOM_U_RVISCFLUX(bi,bj,k+1,uVel,KappaRU,vrF,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         fVerU(i,j,kDown) = ArDudrFac*vrF(i,j)
        ENDDO
       ENDDO
       DO j=2-Oly,sNy+Oly-1
        DO i=2-Olx,sNx+Olx-1
         guDiss(i,j) = guDiss(i,j)
     &   -recip_hFacW(i,j,k,bi,bj)*recip_drF(k)
     &   *recip_rAw(i,j,bi,bj)
     &  *(
     &    fVerU(i,j,kDown) - fVerU(i,j,kUp)
     &   )*rkSign
        ENDDO
       ENDDO
      ENDIF
      IF (momViscosity.AND.no_slip_sides) THEN
       CALL MOM_U_SIDEDRAG(bi,bj,k,uFld,del2u,hFacZ,vF,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         guDiss(i,j) = guDiss(i,j)+vF(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF (momViscosity.AND.bottomDragTerms) THEN
       CALL MOM_U_BOTTOMDRAG(bi,bj,k,uFld,KE,KappaRU,vF,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         guDiss(i,j) = guDiss(i,j)+vF(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF (momViscosity.AND..NOT.implicitViscosity) THEN
       CALL MOM_V_RVISCFLUX(bi,bj,k+1,vVel,KappaRV,vrF,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         fVerV(i,j,kDown) = ArDvdrFac*vrF(i,j)
        ENDDO
       ENDDO
       DO j=jMin,jMax
        DO i=iMin,iMax
         gvDiss(i,j) = gvDiss(i,j)
     &   -recip_hFacS(i,j,k,bi,bj)*recip_drF(k)
     &    *recip_rAs(i,j,bi,bj)
     &  *(
     &    fVerV(i,j,kDown) - fVerV(i,j,kUp)
     &   )*rkSign
        ENDDO
       ENDDO
      ENDIF
      IF (momViscosity.AND.no_slip_sides) THEN
       CALL MOM_V_SIDEDRAG(bi,bj,k,vFld,del2v,hFacZ,vF,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gvDiss(i,j) = gvDiss(i,j)+vF(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF (momViscosity.AND.bottomDragTerms) THEN
       CALL MOM_V_BOTTOMDRAG(bi,bj,k,vFld,KE,KappaRV,vF,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gvDiss(i,j) = gvDiss(i,j)+vF(i,j)
        ENDDO
       ENDDO
      ENDIF
      IF ( useCoriolis .AND. 
     &     .NOT.( useCDscheme .OR. useAbsVorticity.AND.momAdvection )
     &   ) THEN
       IF (useAbsVorticity) THEN
        CALL MOM_VI_U_CORIOLIS(bi,bj,K,vFld,omega3,hFacZ,r_hFacZ,
     &                         uCf,myThid)
        CALL MOM_VI_V_CORIOLIS(bi,bj,K,uFld,omega3,hFacZ,r_hFacZ,
     &                         vCf,myThid)
       ELSE
        CALL MOM_VI_CORIOLIS(bi,bj,k,uFld,vFld,hFacZ,r_hFacZ,
     &                       uCf,vCf,myThid)
       ENDIF
       DO j=jMin,jMax
        DO i=iMin,iMax
         gU(i,j,k,bi,bj) = uCf(i,j)
         gV(i,j,k,bi,bj) = vCf(i,j)
        ENDDO
       ENDDO
       IF ( writeDiag ) THEN
         IF (snapshot_mdsio) THEN
           CALL WRITE_LOCAL_RL('fV','I10',1,uCf,bi,bj,k,myIter,myThid)
           CALL WRITE_LOCAL_RL('fU','I10',1,vCf,bi,bj,k,myIter,myThid)
         ENDIF
       ENDIF
      ELSE
       DO j=jMin,jMax
        DO i=iMin,iMax
         gU(i,j,k,bi,bj) = 0.d0
         gV(i,j,k,bi,bj) = 0.d0
        ENDDO
       ENDDO
      ENDIF
      IF (momAdvection) THEN
       IF (highOrderVorticity.AND.useAbsVorticity) THEN
        CALL MOM_VI_U_CORIOLIS_C4(bi,bj,k,vFld,omega3,r_hFacZ,
     &                         uCf,myThid)
       ELSEIF (highOrderVorticity) THEN
        CALL MOM_VI_U_CORIOLIS_C4(bi,bj,k,vFld,vort3, r_hFacZ,
     &                         uCf,myThid)
       ELSEIF (useAbsVorticity) THEN
        CALL MOM_VI_U_CORIOLIS(bi,bj,K,vFld,omega3,hFacZ,r_hFacZ,
     &                         uCf,myThid)
       ELSE
        CALL MOM_VI_U_CORIOLIS(bi,bj,k,vFld,vort3, hFacZ,r_hFacZ,
     &                         uCf,myThid)
       ENDIF
       DO j=jMin,jMax
        DO i=iMin,iMax
         gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)+uCf(i,j)
        ENDDO
       ENDDO
       IF (highOrderVorticity.AND.useAbsVorticity) THEN
        CALL MOM_VI_V_CORIOLIS_C4(bi,bj,K,uFld,omega3,r_hFacZ,
     &                         vCf,myThid)
       ELSEIF (highOrderVorticity) THEN
        CALL MOM_VI_V_CORIOLIS_C4(bi,bj,K,uFld,vort3, r_hFacZ,
     &                         vCf,myThid)
       ELSEIF (useAbsVorticity) THEN
        CALL MOM_VI_V_CORIOLIS(bi,bj,K,uFld,omega3,hFacZ,r_hFacZ,
     &                         vCf,myThid)
       ELSE
        CALL MOM_VI_V_CORIOLIS(bi,bj,k,uFld,vort3, hFacZ,r_hFacZ,
     &                         vCf,myThid)
       ENDIF
       DO j=jMin,jMax
        DO i=iMin,iMax
         gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)+vCf(i,j)
        ENDDO
       ENDDO
       IF ( writeDiag ) THEN
         IF (snapshot_mdsio) THEN
           CALL WRITE_LOCAL_RL('zV','I10',1,uCf,bi,bj,k,myIter,myThid)
           CALL WRITE_LOCAL_RL('zU','I10',1,vCf,bi,bj,k,myIter,myThid)
         ENDIF
       ENDIF
       IF ( .NOT. momImplVertAdv ) THEN
        CALL MOM_VI_U_VERTSHEAR(bi,bj,K,uVel,wVel,uCf,myThid)
        DO j=jMin,jMax
         DO i=iMin,iMax
          gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)+uCf(i,j)
         ENDDO
        ENDDO
        CALL MOM_VI_V_VERTSHEAR(bi,bj,K,vVel,wVel,vCf,myThid)
        DO j=jMin,jMax
         DO i=iMin,iMax
          gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)+vCf(i,j)
         ENDDO
        ENDDO
       ENDIF
       CALL MOM_VI_U_GRAD_KE(bi,bj,K,KE,uCf,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)+uCf(i,j)
        ENDDO
       ENDDO
       CALL MOM_VI_V_GRAD_KE(bi,bj,K,KE,vCf,myThid)
       DO j=jMin,jMax
        DO i=iMin,iMax
         gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)+vCf(i,j)
        ENDDO
       ENDDO
       IF ( writeDiag ) THEN
         IF (snapshot_mdsio) THEN
           CALL WRITE_LOCAL_RL('KEx','I10',1,uCf,bi,bj,k,myIter,myThid)
           CALL WRITE_LOCAL_RL('KEy','I10',1,vCf,bi,bj,k,myIter,myThid)
         ENDIF
       ENDIF
      ENDIF
      DO j=jMin,jMax
       DO i=iMin,iMax
        gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj)*maskW(i,j,k,bi,bj)
        gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj)*maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      IF ( debugLevel .GE. debLevB
     &   .AND. k.EQ.4 .AND. myIter.EQ.nIter0
     &   .AND. nPx.EQ.1 .AND. nPy.EQ.1
     &   .AND. useCubedSphereExchange ) THEN
        CALL DEBUG_CS_CORNER_UV( ' uDiss,vDiss from MOM_VECINV',
     &             guDiss,gvDiss, k, standardMessageUnit,bi,bj,myThid )
      ENDIF
      IF ( writeDiag ) THEN
        IF (snapshot_mdsio) THEN
          CALL WRITE_LOCAL_RL('Ds','I10',1,strain,bi,bj,k,myIter,myThid)
          CALL WRITE_LOCAL_RL('Dt','I10',1,tension,bi,bj,k,myIter,
     &         myThid)
          CALL WRITE_LOCAL_RL('Du','I10',1,guDiss,bi,bj,k,myIter,myThid)
          CALL WRITE_LOCAL_RL('Dv','I10',1,gvDiss,bi,bj,k,myIter,myThid)
          CALL WRITE_LOCAL_RL('Z3','I10',1,vort3,bi,bj,k,myIter,myThid)
          CALL WRITE_LOCAL_RL('W3','I10',1,omega3,bi,bj,k,myIter,myThid)
          CALL WRITE_LOCAL_RL('KE','I10',1,KE,bi,bj,k,myIter,myThid)
          CALL WRITE_LOCAL_RL('D','I10',1,hdiv,bi,bj,k,myIter,myThid)
        ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_VI_CORIOLIS( 
     I        bi,bj,K,
     I        uFld,vFld,hFacZ,r_hFacZ,
     O        uCoriolisTerm,vCoriolisTerm,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
       USE PARAMS_mod
      INTEGER bi,bj,K
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 r_hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER I,J
      Real*8 vBarXY,uBarXY,vort3u,vort3v
      Real*8 epsil
      epsil = 1.D-9
      IF (useJamartWetPoints) THEN
       DO J=1-Oly,sNy+Oly-1
        DO I=2-Olx,sNx+Olx
         vBarXY=(
     &       vFld( i , j )*dxG( i , j ,bi,bj)*hFacS( i , j ,k,bi,bj)
     &      +vFld( i ,j+1)*dxG( i ,j+1,bi,bj)*hFacS( i ,j+1,k,bi,bj)
     &      +vFld(i-1, j )*dxG(i-1, j ,bi,bj)*hFacS(i-1, j ,k,bi,bj)
     &      +vFld(i-1,j+1)*dxG(i-1,j+1,bi,bj)*hFacS(i-1,j+1,k,bi,bj) )
     &   / MAX( epsil, hFacS( i , j ,k,bi,bj)+hFacS(i-1, j ,k,bi,bj)
     &                +hFacS( i ,j+1,k,bi,bj)+hFacS(i-1,j+1,k,bi,bj) )
         uCoriolisTerm(i,j)=
     &    +0.5*( fCoriG(i,j,bi,bj)+fCoriG(i,j+1,bi,bj)
     &         )*vBarXY*recip_dxC(i,j,bi,bj)*maskW(I,J,K,bi,bj)
        ENDDO
       ENDDO
      ELSE
       DO J=1-Oly,sNy+Oly-1
        DO I=2-Olx,sNx+Olx
         vBarXY=0.25*(
     &       vFld( i , j )*dxG( i , j ,bi,bj)
     &      +vFld( i ,j+1)*dxG( i ,j+1,bi,bj)
     &      +vFld(i-1, j )*dxG(i-1, j ,bi,bj)
     &      +vFld(i-1,j+1)*dxG(i-1,j+1,bi,bj) )
         uCoriolisTerm(i,j)=
     &    +0.5*( fCoriG(i,j,bi,bj)+fCoriG(i,j+1,bi,bj)
     &         )*vBarXY*recip_dxC(i,j,bi,bj)*maskW(I,J,K,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      IF (useJamartWetPoints) THEN
       DO J=2-Oly,sNy+Oly
        DO I=1-Olx,sNx+Olx-1
         uBarXY=(
     &       uFld( i , j )*dyG( i , j ,bi,bj)*hFacW( i , j ,k,bi,bj)
     &      +uFld( i ,j-1)*dyG( i ,j-1,bi,bj)*hFacW( i ,j-1,k,bi,bj)
     &      +uFld(i+1, j )*dyG(i+1, j ,bi,bj)*hFacW(i+1, j ,k,bi,bj)
     &      +uFld(i+1,j-1)*dyG(i+1,j-1,bi,bj)*hFacW(i+1,j-1,k,bi,bj) )
     &   / MAX( epsil, hFacW( i , j ,k,bi,bj)+hFacW( i ,j-1,k,bi,bj)
     &                +hFacW(i+1, j ,k,bi,bj)+hFacW(i+1,j-1,k,bi,bj) )
         vCoriolisTerm(i,j)=
     &    -0.5*( fCoriG(i,j,bi,bj)+fCoriG(i+1,j,bi,bj)
     &         )*uBarXY*recip_dyC(i,j,bi,bj)*maskS(I,J,K,bi,bj)
        ENDDO
       ENDDO
      ELSE
       DO J=2-Oly,sNy+Oly
        DO I=1-Olx,sNx+Olx-1
         uBarXY=0.25*(
     &       uFld( i , j )*dyG( i , j ,bi,bj)
     &      +uFld( i ,j-1)*dyG( i ,j-1,bi,bj)
     &      +uFld(i+1, j )*dyG(i+1, j ,bi,bj)
     &      +uFld(i+1,j-1)*dyG(i+1,j-1,bi,bj) )
         vCoriolisTerm(i,j)=
     &    -0.5*( fCoriG(i,j,bi,bj)+fCoriG(i+1,j,bi,bj)
     &         )*uBarXY*recip_dyC(i,j,bi,bj)*maskS(I,J,K,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_VI_DEL2UV(
     I        bi,bj,k,
     I        hDiv,vort3,hFacZ,
     O        del2u,del2v,
     I        myThid)
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
      INTEGER bi,bj,k
      Real*8 hDiv(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vort3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2u(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2v(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER I,J
      Real*8 Zip,Zij,Zpj,Dim,Dij,Dmj,uDij
      LOGICAL northWestCorner, northEastCorner,
     &        southWestCorner, southEastCorner
      IF (useCubedSphereExchange) THEN
         southWestCorner = .TRUE.
         southEastCorner = .TRUE.
         northWestCorner = .TRUE.
         northEastCorner = .TRUE.
      ENDIF
      DO j=2-Oly,sNy+Oly-1
       DO i=2-Olx,sNx+Olx-1
        Dim=                                          hDiv( i ,j-1)
        Dij=                                          hDiv( i , j )
        Dmj=                                          hDiv(i-1, j )
        Zip=                   hFacZ( i ,j+1)*vort3( i ,j+1)
        Zij=                   hFacZ( i , j )*vort3( i , j )
        Zpj=                   hFacZ(i+1, j )*vort3(i+1, j )
        uDij=Dij
        IF (useCubedSphereExchange) THEN
         if(southWestCorner.and.i.eq.1.and.j.eq.0) Dmj=hDiv(0,1)
         if(southWestCorner.and.i.eq.0.and.j.eq.1) Dim=hDiv(1,0)
         if(northWestCorner.and.i.eq.1.and.j.eq.sNy+1) Dmj=hDiv(0,sNy)
         if(northWestCorner.and.i.eq.0.and.j.eq.sNy+1) Dij=hDiv(1,sNy+1)
         if(southEastCorner.and.i.eq.sNx+1.and.j.eq.0)uDij=hDiv(sNx+1,1)
         if(southEastCorner.and.i.eq.sNx+1.and.j.eq.1) Dim=hDiv(sNx,0)
         if (northEastCorner.and.i.eq.sNx+1 .and. j.eq.sNy+1) then
          uDij=hDiv(sNx+1,sNy)
          Dij=hDiv(sNx,sNy+1)
         endif
        ENDIF
        del2u(i,j) =
     &   +                         ( uDij-Dmj )*recip_DXC(i,j,bi,bj)
     &   -recip_hFacW(i,j,k,bi,bj)*( Zip-Zij )*recip_DYG(i,j,bi,bj)
        del2v(i,j) =
     &    recip_hFacS(i,j,k,bi,bj)*( Zpj-Zij )*recip_DXG(i,j,bi,bj)
     &   +                         ( Dij-Dim )*recip_DYC(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_VI_HDISSIP(
     I        bi,bj,k,
     I        hDiv,vort3,hFacZ,dStar,zStar,
     O        uDissip,vDissip,
     I        myThid)
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 hDiv(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vort3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dStar(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 zStar(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uDissip(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vDissip(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 viscAh_Z(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 viscAh_D(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 viscA4_Z(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 viscA4_D(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 Zip,Zij,Zpj,Dim,Dij,Dmj,uD2,vD2,uD4,vD4
      Real*8 Alin,AlinMin,AlinMax,Alth2,Alth4,grdVrt,grdDiv
      Real*8 vg2,vg2Min,vg2Max,vg4,vg4Min,vg4Max
      Real*8 recip_dt,L2,L3,L4,L5,L2rdt,L4rdt
      LOGICAL useVariableViscosity
      useVariableViscosity=
     &      (viscAhGrid.NE.0.)
     &  .OR.(viscA4Grid.NE.0.)
     &  .OR.(viscC2leith.NE.0.)
     &  .OR.(viscC2leithD.NE.0.)
     &  .OR.(viscC4leith.NE.0.)
     &  .OR.(viscC4leithD.NE.0.)
      IF (deltaTmom.NE.0.) THEN
       recip_dt=1./deltaTmom
      ELSE
       recip_dt=0.
      ENDIF
      vg2=viscAhGrid*recip_dt
      vg2Min=viscAhGridMin*recip_dt
      vg2Max=viscAhGridMax*recip_dt
      vg4=viscA4Grid*recip_dt
      vg4Min=viscA4GridMin*recip_dt
      vg4Max=viscA4GridMax*recip_dt
      IF (useVariableViscosity) THEN
       DO j=2-Oly,sNy+Oly-1
        DO i=2-Olx,sNx+Olx-1
         L2=rA(i,j,bi,bj)
         L3=(L2**1.5)
         L4=(L2**2)
         L5=0.125*(L2**2.5)
         IF (useAnisotropicViscAGridMax) THEN
         L2rdt=recip_dt/( 2.*(recip_DXF(I,J,bi,bj)**2
     &                       +recip_DYF(I,J,bi,bj)**2) )
         L4rdt=recip_dt/( 6.*(recip_DXF(I,J,bi,bj)**4
     &                       +recip_DYF(I,J,bi,bj)**4)
     &                   +8.*((recip_DXF(I,J,bi,bj)
     &                        *recip_DYF(I,J,bi,bj))**2) )
         ENDIF
         IF (useFullLeith) THEN
          grdVrt=0.25*(
     &     ((vort3(i+1,j)-vort3(i,j))*recip_DXG(i,j,bi,bj))**2
     &     +((vort3(i,j+1)-vort3(i,j))*recip_DYG(i,j,bi,bj))**2
     &     +((vort3(i+1,j+1)-vort3(i,j+1))*recip_DXG(i,j+1,bi,bj))**2
     &     +((vort3(i+1,j+1)-vort3(i+1,j))*recip_DYG(i+1,j,bi,bj))**2)
           grdDiv=0.25*(
     &      ((hDiv(i+1,j)-hDiv(i,j))*recip_DXG(i,j,bi,bj))**2
     &      +((hDiv(i,j+1)-hDiv(i,j))*recip_DYG(i,j,bi,bj))**2
     &      +((hDiv(i-1,j)-hDiv(i,j))*recip_DXG(i-1,j,bi,bj))**2
     &      +((hDiv(i,j-1)-hDiv(i,j))*recip_DYG(i,j-1,bi,bj))**2)
           IF ( (viscC2leith**2*grdVrt+viscC2leithD**2*grdDiv)
     &          .NE. 0. ) THEN
            Alth2=sqrt(viscC2leith**2*grdVrt+viscC2leithD**2*grdDiv)*L3
           ELSE
            Alth2=0.d0
           ENDIF
           IF ( (viscC4leith**2*grdVrt+viscC4leithD**2*grdDiv)
     &          .NE. 0. ) THEN
            Alth4=sqrt(viscC4leith**2*grdVrt+viscC4leithD**2*grdDiv)*L5
           ELSE
            Alth4=0.d0
           ENDIF
         ELSE
           grdVrt=abs((vort3(i+1,j)-vort3(i,j))*recip_DXG(i,j,bi,bj))
           grdVrt=max(grdVrt,
     &      abs((vort3(i,j+1)-vort3(i,j))*recip_DYG(i,j,bi,bj)))
           grdVrt=max(grdVrt,
     &      abs((vort3(i+1,j+1)-vort3(i,j+1))*recip_DXG(i,j+1,bi,bj)))
           grdVrt=max(grdVrt,
     &      abs((vort3(i+1,j+1)-vort3(i+1,j))*recip_DYG(i+1,j,bi,bj)))
           grdDiv=abs((hDiv(i+1,j)-hDiv(i,j))*recip_DXG(i,j,bi,bj))
           grdDiv=max(grdDiv,
     &      abs((hDiv(i,j+1)-hDiv(i,j))*recip_DYG(i,j,bi,bj)))
           grdDiv=max(grdDiv,
     &      abs((hDiv(i-1,j)-hDiv(i,j))*recip_DXG(i-1,j,bi,bj)))
           grdDiv=max(grdDiv,
     &      abs((hDiv(i,j-1)-hDiv(i,j))*recip_DYG(i,j-1,bi,bj)))
           Alth2=(viscC2leith*grdVrt+(viscC2leithD*grdDiv))*L3
           Alth4=(viscC4leith*grdVrt+(viscC4leithD*grdDiv))*L5
         ENDIF
         Alin=viscAhD+vg2*L2+Alth2
         viscAh_D(i,j)=min(viscAhMax,Alin)
         IF (useAnisotropicViscAGridMax) THEN
            AlinMax=viscAhGridMax*L2rdt
            viscAh_D(i,j)=min(AlinMax,viscAh_D(i,j))
         ELSE
         IF (vg2Max.GT.0.) THEN
            AlinMax=vg2Max*L2
            viscAh_D(i,j)=min(AlinMax,viscAh_D(i,j))
         ENDIF
         ENDIF
         AlinMin=vg2Min*L2
         viscAh_D(i,j)=max(AlinMin,viscAh_D(i,j))
         Alin=viscA4D+vg4*L4+Alth4
         viscA4_D(i,j)=min(viscA4Max,Alin)
         IF (useAnisotropicViscAGridMax) THEN
            AlinMax=viscA4GridMax*L4rdt
            viscA4_D(i,j)=min(AlinMax,viscA4_D(i,j))
         ELSE
         IF (vg4Max.GT.0.) THEN
            AlinMax=vg4Max*L4
            viscA4_D(i,j)=min(AlinMax,viscA4_D(i,j))
         ENDIF
         ENDIF
         AlinMin=vg4Min*L4
         viscA4_D(i,j)=max(AlinMin,viscA4_D(i,j))
         L2=rAz(i,j,bi,bj)
         L3=(L2**1.5)
         L4=(L2**2)
         L5=0.125*(L2**2.5)
         IF (useAnisotropicViscAGridMax) THEN
         L2rdt=recip_dt/( 2.*(recip_DXV(I,J,bi,bj)**2
     &                       +recip_DYU(I,J,bi,bj)**2) )
         L4rdt=recip_dt/( 6.*(recip_DXV(I,J,bi,bj)**4
     &                       +recip_DYU(I,J,bi,bj)**4)
     &                   +8.*((recip_DXV(I,J,bi,bj)
     &                        *recip_DYU(I,J,bi,bj))**2) )
         ENDIF
         IF (useFullLeith) THEN
           grdVrt=0.25*(
     &      ((vort3(i+1,j)-vort3(i,j))*recip_DXG(i,j,bi,bj))**2
     &      +((vort3(i,j+1)-vort3(i,j))*recip_DYG(i,j,bi,bj))**2
     &      +((vort3(i-1,j)-vort3(i,j))*recip_DXG(i-1,j,bi,bj))**2
     &      +((vort3(i,j-1)-vort3(i,j))*recip_DYG(i,j-1,bi,bj))**2)
           grdDiv=0.25*(
     &       ((hDiv(i+1,j)-hDiv(i,j))*recip_DXG(i,j,bi,bj))**2
     &      +((hDiv(i,j+1)-hDiv(i,j))*recip_DYG(i,j,bi,bj))**2
     &      +((hDiv(i+1,j+1)-hDiv(i,j+1))*recip_DXG(i,j+1,bi,bj))**2
     &      +((hDiv(i+1,j+1)-hDiv(i+1,j))*recip_DYG(i+1,j,bi,bj))**2)
           IF ( (viscC2leith**2*grdVrt+viscC2leithD**2*grdDiv)
     &          .NE. 0. ) THEN
            Alth2=sqrt(viscC2leith**2*grdVrt+viscC2leithD**2*grdDiv)*L3
           ELSE
            Alth2=0.d0
           ENDIF
           IF ( (viscC4leith**2*grdVrt+viscC4leithD**2*grdDiv)
     &          .NE. 0. ) THEN
            Alth4=sqrt(viscC4leith**2*grdVrt+viscC4leithD**2*grdDiv)*L5
           ELSE
            Alth4=0.d0
           ENDIF
         ELSE
           grdVrt=abs((vort3(i+1,j)-vort3(i,j))*recip_DXG(i,j,bi,bj))
           grdVrt=max(grdVrt,
     &       abs((vort3(i,j+1)-vort3(i,j))*recip_DYG(i,j,bi,bj)))
           grdVrt=max(grdVrt,
     &       abs((vort3(i-1,j)-vort3(i,j))*recip_DXG(i-1,j,bi,bj)))
           grdVrt=max(grdVrt,
     &       abs((vort3(i,j-1)-vort3(i,j))*recip_DYG(i,j-1,bi,bj)))
           grdDiv=abs((hDiv(i+1,j)-hDiv(i,j))*recip_DXG(i,j,bi,bj))
           grdDiv=max(grdDiv,
     &      abs((hDiv(i,j+1)-hDiv(i,j))*recip_DYG(i,j,bi,bj)))
           grdDiv=max(grdDiv,
     &      abs((hDiv(i+1,j+1)-hDiv(i,j+1))*recip_DXG(i-1,j,bi,bj)))
           grdDiv=max(grdDiv,
     &      abs((hDiv(i+1,j+1)-hDiv(i+1,j))*recip_DYG(i,j-1,bi,bj)))
           Alth2=(viscC2leith*grdVrt+(viscC2leithD*grdDiv))*L3
           Alth4=(viscC4leith*grdVrt+(viscC4leithD*grdDiv))*L5
         ENDIF
         Alin=viscAhZ+vg2*L2+Alth2
         viscAh_Z(i,j)=min(viscAhMax,Alin)
         IF (useAnisotropicViscAGridMax) THEN
            AlinMax=viscAhGridMax*L2rdt
            viscAh_Z(i,j)=min(AlinMax,viscAh_Z(i,j))
         ELSE
         IF (vg2Max.GT.0.) THEN
            AlinMax=vg2Max*L2
            viscAh_Z(i,j)=min(AlinMax,viscAh_Z(i,j))
         ENDIF
         ENDIF
         AlinMin=vg2Min*L2
         viscAh_Z(i,j)=max(AlinMin,viscAh_Z(i,j))
         Alin=viscA4Z+vg4*L4+Alth4
         viscA4_Z(i,j)=min(viscA4Max,Alin)
         IF (useAnisotropicViscAGridMax) THEN
            AlinMax=viscA4GridMax*L4rdt
            viscA4_Z(i,j)=min(AlinMax,viscA4_Z(i,j))
         ELSE
         IF (vg4Max.GT.0.) THEN
            AlinMax=vg4Max*L4
            viscA4_Z(i,j)=min(AlinMax,viscA4_Z(i,j))
         ENDIF
         ENDIF
         AlinMin=vg4Min*L4
         viscA4_Z(i,j)=max(AlinMin,viscA4_Z(i,j))
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         viscAh_D(i,j)=viscAhD
         viscAh_Z(i,j)=viscAhZ
         viscA4_D(i,j)=viscA4D
         viscA4_Z(i,j)=viscA4Z
        ENDDO
       ENDDO
      ENDIF
      IF ( viscC2leith.NE.0. .OR. viscAhGrid.NE.0.
     &    .OR. viscAhD.NE.0. .OR. viscAhZ.NE.0. ) THEN
       DO j=2-Oly,sNy+Oly-1
        DO i=2-Olx,sNx+Olx-1
         Dim=hDiv( i ,j-1)
         Dij=hDiv( i , j )
         Dmj=hDiv(i-1, j )
         Zip=hFacZ( i ,j+1)*vort3( i ,j+1)
         Zij=hFacZ( i , j )*vort3( i , j )
         Zpj=hFacZ(i+1, j )*vort3(i+1, j )
         IF (useVariableViscosity) THEN
          Dij=Dij*viscAh_D(i,j)
          Dim=Dim*viscAh_D(i,j-1)
          Dmj=Dmj*viscAh_D(i-1,j)
          Zij=Zij*viscAh_Z(i,j)
          Zip=Zip*viscAh_Z(i,j+1)
          Zpj=Zpj*viscAh_Z(i+1,j)
          uD2 = (
     &               cosFacU(j,bi,bj)*( Dij-Dmj )*recip_DXC(i,j,bi,bj)
     &      -recip_hFacW(i,j,k,bi,bj)*( Zip-Zij )*recip_DYG(i,j,bi,bj) )
          vD2 = (
     &       recip_hFacS(i,j,k,bi,bj)*( Zpj-Zij )*recip_DXG(i,j,bi,bj)
     &                                           *cosFacV(j,bi,bj)
     &                               +( Dij-Dim )*recip_DYC(i,j,bi,bj) )
         ELSE
          uD2 = viscAhD*
     &               cosFacU(j,bi,bj)*( Dij-Dmj )*recip_DXC(i,j,bi,bj)
     &        - viscAhZ*recip_hFacW(i,j,k,bi,bj)*
     &                                ( Zip-Zij )*recip_DYG(i,j,bi,bj)
          vD2 = viscAhZ*recip_hFacS(i,j,k,bi,bj)*
     &               cosFacV(j,bi,bj)*( Zpj-Zij )*recip_DXG(i,j,bi,bj)
     &        + viscAhD*              ( Dij-Dim )*recip_DYC(i,j,bi,bj)
         ENDIF
         uDissip(i,j) = uD2
         vDissip(i,j) = vD2
        ENDDO
       ENDDO
      ELSE
       DO j=2-Oly,sNy+Oly-1
        DO i=2-Olx,sNx+Olx-1
         uDissip(i,j) = 0.
         vDissip(i,j) = 0.
        ENDDO
       ENDDO
      ENDIF
      IF ( viscC4leith.NE.0. .OR. viscA4Grid.NE.0.
     &    .OR. viscA4D.NE.0. .OR. viscA4Z.NE.0. ) THEN
       DO j=2-Oly,sNy+Oly-1
        DO i=2-Olx,sNx+Olx-1
         Dim=dStar( i ,j-1)
         Dij=dStar( i , j )
         Dmj=dStar(i-1, j )
         Zip=hFacZ( i ,j+1)*zStar( i ,j+1)
         Zij=hFacZ( i , j )*zStar( i , j )
         Zpj=hFacZ(i+1, j )*zStar(i+1, j )
         IF (useVariableViscosity) THEN
          Dij=Dij*viscA4_D(i,j)
          Dim=Dim*viscA4_D(i,j-1)
          Dmj=Dmj*viscA4_D(i-1,j)
          Zij=Zij*viscA4_Z(i,j)
          Zip=Zip*viscA4_Z(i,j+1)
          Zpj=Zpj*viscA4_Z(i+1,j)
          uD4 = (
     &               cosFacU(j,bi,bj)*( Dij-Dmj )*recip_DXC(i,j,bi,bj)
     &      -recip_hFacW(i,j,k,bi,bj)*( Zip-Zij )*recip_DYG(i,j,bi,bj) )
          vD4 = (
     &       recip_hFacS(i,j,k,bi,bj)*( Zpj-Zij )*recip_DXG(i,j,bi,bj)
     &                                           *cosFacV(j,bi,bj)
     &                               +( Dij-Dim )*recip_DYC(i,j,bi,bj) )
         ELSE
          uD4 = viscA4D*
     &               cosFacU(j,bi,bj)*( Dij-Dmj )*recip_DXC(i,j,bi,bj)
     &        - viscA4Z*recip_hFacW(i,j,k,bi,bj)*
     &                                ( Zip-Zij )*recip_DYG(i,j,bi,bj)
          vD4 = viscA4Z*recip_hFacS(i,j,k,bi,bj)*
     &               cosFacV(j,bi,bj)*( Zpj-Zij )*recip_DXG(i,j,bi,bj)
     &        + viscA4D*              ( Dij-Dim )*recip_DYC(i,j,bi,bj)
         ENDIF
         uDissip(i,j) = uDissip(i,j) - uD4
         vDissip(i,j) = vDissip(i,j) - vD4
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_VI_U_CORIOLIS( 
     I        bi,bj,k,
     I        vFld,omega3,hFacZ,r_hFacZ,
     O        uCoriolisTerm,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
       USE PARAMS_mod
      INTEGER bi,bj,K
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 omega3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 r_hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      LOGICAL use_original_hFac
      INTEGER I,J
      Real*8 vBarXY,vort3u,Zp,Zm
      Real*8 epsil
      PARAMETER ( use_original_hFac=.FALSE. )
      epsil = 1.D-9 
      DO J=1-Oly,sNy+Oly-1
       DO I=2-Olx,sNx+Olx
        IF ( use_original_hFac ) THEN
         vBarXY=0.25*(
     &       vFld( i , j )*dxG( i , j ,bi,bj)*hFacS( i , j ,k,bi,bj)
     &      +vFld( i ,j+1)*dxG( i ,j+1,bi,bj)*hFacS( i ,j+1,k,bi,bj)
     &      +vFld(i-1, j )*dxG(i-1, j ,bi,bj)*hFacS(i-1, j ,k,bi,bj)
     &      +vFld(i-1,j+1)*dxG(i-1,j+1,bi,bj)*hFacS(i-1,j+1,k,bi,bj))
         IF (upwindVorticity) THEN
          IF (vBarXY.GT.0.) THEN
           vort3u=omega3(I,J)*r_hFacZ(i,j)
          ELSE
           vort3u=omega3(I,J+1)*r_hFacZ(i,j+1)
          ENDIF
         ELSE
           vort3u=0.5*(omega3(i,j)*r_hFacZ(i,j)
     &                +omega3(i,j+1)*r_hFacZ(i,j+1))
         ENDIF
        ELSEIF ( SadournyCoriolis ) THEN
         Zm=0.5*(
     &       vFld( i , j )*dxG( i , j ,bi,bj)*hFacS( i , j ,k,bi,bj)
     &      +vFld(i-1, j )*dxG(i-1, j ,bi,bj)*hFacS(i-1, j ,k,bi,bj) )
         Zp=0.5*(
     &       vFld( i ,j+1)*dxG( i ,j+1,bi,bj)*hFacS( i ,j+1,k,bi,bj)
     &      +vFld(i-1,j+1)*dxG(i-1,j+1,bi,bj)*hFacS(i-1,j+1,k,bi,bj) )
         IF (upwindVorticity) THEN
          IF ( (Zm+Zp) .GT.0.) THEN
           vort3u=Zm*r_hFacZ(i, j )*omega3(i, j )
          ELSE
           vort3u=Zp*r_hFacZ(i,j+1)*omega3(i,j+1)
          ENDIF
         ELSE
          Zm=Zm*r_hFacZ(i, j )*omega3(i, j )
          Zp=Zp*r_hFacZ(i,j+1)*omega3(i,j+1)
          vort3u=0.5*( Zm + Zp )
         ENDIF
         vBarXY=1.
        ELSE
         vBarXY=0.5*(
     &       vFld( i , j )*dxG( i , j ,bi,bj)*hFacZ(i,j)
     &      +vFld(i-1, j )*dxG(i-1, j ,bi,bj)*hFacZ(i,j)
     &      +vFld( i ,j+1)*dxG( i ,j+1,bi,bj)*hFacZ(i,j+1)
     &      +vFld(i-1,j+1)*dxG(i-1,j+1,bi,bj)*hFacZ(i,j+1)
     &              )/MAX( epsil, hFacZ(i,j)+hFacZ(i,j+1) ) 
         IF (upwindVorticity) THEN
          IF (vBarXY.GT.0.) THEN
           vort3u=omega3(i,j)
          ELSE
           vort3u=omega3(i,j+1)
          ENDIF
         ELSE
           vort3u=0.5*(omega3(i,j)+omega3(i,j+1)) 
         ENDIF
        ENDIF
        IF (useJamartMomAdv)
     &   vBarXY = vBarXY * 4.d0 * hFacW(i,j,k,bi,bj)
     &   / MAX( epsil, hFacS( i , j ,k,bi,bj)+hFacS(i-1, j ,k,bi,bj)
     &                +hFacS( j ,i+1,k,bi,bj)+hFacS(i-1,j+1,k,bi,bj) )
        uCoriolisTerm(i,j)=
     &   +vort3u*vBarXY*recip_dxC(i,j,bi,bj)*maskW(i,j,k,bi,bj) 
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_VI_U_CORIOLIS_C4(
     I        bi,bj,k,
     I        vFld,omega3,r_hFacZ,
     O        uCoriolisTerm,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 omega3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 r_hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      Real*8 vBarXY,vort3u,Rjp,Rjm
      Real*8 vBarXm,vBarXp,oneSixth
      LOGICAL upwindVort3
      LOGICAL fourthVort3
      PARAMETER(oneSixth=1.d0/6.d0)
      PARAMETER(upwindVort3=.FALSE.)
      PARAMETER(fourthVort3=.TRUE. )
      DO j=1,sNy
       DO i=1,sNx+1
        IF ( SadournyCoriolis ) THEN
         vBarXY=1.
         vBarXm=0.5*(
     &       vFld( i , j )*dxG( i , j ,bi,bj)*hFacS( i , j ,k,bi,bj)
     &      +vFld(i-1, j )*dxG(i-1, j ,bi,bj)*hFacS(i-1, j ,k,bi,bj) )
         vBarXp=0.5*(
     &       vFld( i ,j+1)*dxG( i ,j+1,bi,bj)*hFacS( i ,j+1,k,bi,bj)
     &      +vFld(i-1,j+1)*dxG(i-1,j+1,bi,bj)*hFacS(i-1,j+1,k,bi,bj) )
         IF (upwindVorticity) THEN
          IF ( (vBarXm+vBarXp) .GT.0.) THEN
           vort3u=vBarXm*r_hFacZ(i, j )*omega3(i, j )
          ELSE
           vort3u=vBarXp*r_hFacZ(i,j+1)*omega3(i,j+1)
          ENDIF
         ELSEIF (fourthVort3) THEN
          Rjp = omega3(i,j+1)*r_hFacZ(i,j+1)
     &         -oneSixth*( omega3(i,j+2)*r_hFacZ(i,j+2)
     &                    -omega3(i, j )*r_hFacZ(i, j ) )
          Rjm = omega3(i,j)*r_hFacZ(i,j)
     &         +oneSixth*( omega3(i,j+1)*r_hFacZ(i,j+1)
     &                    -omega3(i,j-1)*r_hFacZ(i,j-1) )
          vort3u=0.5*( vBarXm*Rjm + vBarXp*Rjp )
         ELSE
          vort3u=0.5*( vBarXm*r_hFacZ(i, j )*omega3(i, j )
     &               + vBarXp*r_hFacZ(i,j+1)*omega3(i,j+1) )
         ENDIF
        ELSE
         vBarXY=0.25*(
     &       vFld( i , j )*dxG( i , j ,bi,bj)*hFacS( i , j ,k,bi,bj)
     &      +vFld( i ,j+1)*dxG( i ,j+1,bi,bj)*hFacS( i ,j+1,k,bi,bj)
     &      +vFld(i-1, j )*dxG(i-1, j ,bi,bj)*hFacS(i-1, j ,k,bi,bj)
     &      +vFld(i-1,j+1)*dxG(i-1,j+1,bi,bj)*hFacS(i-1,j+1,k,bi,bj))
         IF (upwindVort3) THEN
          IF (vBarXY.GT.0.) THEN
           vort3u=omega3(i,j)*r_hFacZ(i,j)
          ELSE
           vort3u=omega3(i,j+1)*r_hFacZ(i,j+1)
          ENDIF
         ELSEIF (fourthVort3) THEN
          Rjp=omega3(i,j+2)*r_hFacZ(i,j+2)
     &       -omega3(i,j+1)*r_hFacZ(i,j+1)
          Rjm=omega3(i,j)*r_hFacZ(i,j)
     &       -omega3(i,j-1)*r_hFacZ(i,j-1)
          vort3u=0.5*(omega3(i,j)*r_hFacZ(i,j)
     &               +omega3(i,j+1)*r_hFacZ(i,j+1)
     &               -1./12.*(Rjp-Rjm)
     &               )
         ELSE
          vort3u=0.5*(omega3(i,j)*r_hFacZ(i,j)
     &               +omega3(i,j+1)*r_hFacZ(i,j+1))
         ENDIF
        ENDIF
        uCoriolisTerm(i,j)=
     &    vort3u*vBarXY*recip_dxC(i,j,bi,bj)
     &                 * maskW(i,j,k,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_VI_U_GRAD_KE( 
     I        bi,bj,K,
     I        KE,
     O        dKEdx,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,K
      Real*8 KE(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dKEdx(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER I,J
       DO J=1-Oly,sNy+Oly
        DO I=2-Olx,sNx+Olx
         dKEdx(I,J)=-recip_dxC(i,j,bi,bj)*(KE(i,j)-KE(i-1,j))
     &       *maskW(i,j,k,BI,BJ)
        ENDDO
       ENDDO
      RETURN
      END
      SUBROUTINE MOM_VI_U_VERTSHEAR(
     I        bi,bj,K,
     I        uFld,wFld,
     U        uShearTerm,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
       USE PARAMS_mod
      INTEGER bi,bj,K
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 wFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 uShearTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER I,J,Kp1,Km1
      Real*8  mask_Kp1,mask_Km1,wBarXm,wBarXp
      Real*8  uZm,uZp
      Kp1=min(K+1,Nr)
      mask_Kp1=1.
      IF (K.EQ.Nr) mask_Kp1=0.
      Km1=max(K-1,1)
      mask_Km1=1.
      IF (K.EQ.1) mask_Km1=0.
      DO J=1-Oly,sNy+Oly
       DO I=2-Olx,sNx+Olx
        wBarXm=0.5*(
     &    wFld(I,J,K,bi,bj)*rA(i,j,bi,bj)*maskC(I,J,Km1,bi,bj)
     &   +wFld(I-1,J,K,bi,bj)*rA(i-1,j,bi,bj)*maskC(I-1,J,Km1,bi,bj)
     &             )*mask_Km1
        wBarXp=0.5*(
     &    wFld(I,J,Kp1,bi,bj)*rA(i,j,bi,bj)
     &   +wFld(I-1,J,Kp1,bi,bj)*rA(i-1,j,bi,bj)
     &             )*mask_Kp1
        uZm=(uFld(I,J,K,bi,bj)-mask_Km1*uFld(I,J,Km1,bi,bj))*rkSign
        uZp=(mask_Kp1*uFld(I,J,Kp1,bi,bj)-uFld(I,J,K,bi,bj))*rkSign
        IF (upwindShear) THEN
          uShearTerm(I,J)=-0.5*
     &                   (     (wBarXp*uZp+wBarXm*uZm)
     &                        +(ABS(wBarXp)*uZp-ABS(wBarXm)*uZm)
     &                   )*recip_rAw(i,j,bi,bj)
     &                    *recip_hFacW(i,j,k,bi,bj)
     &                    *recip_drF(K)
        ELSE
          uShearTerm(I,J)=-0.5*(wBarXp*uZp+wBarXm*uZm)
     &                    *recip_rAw(i,j,bi,bj)
     &                    *recip_hFacW(i,j,k,bi,bj)
     &                    *recip_drF(K)
        ENDIF
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_VI_V_CORIOLIS( 
     I        bi,bj,k,
     I        uFld,omega3,hFacZ,r_hFacZ,
     O        vCoriolisTerm,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 omega3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 r_hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      LOGICAL use_original_hFac
      INTEGER I,J
      Real*8 uBarXY,vort3v,Zp,Zm
      Real*8 epsil
      PARAMETER ( use_original_hFac=.FALSE. )
      epsil = 1.D-9
      DO J=2-Oly,sNy+Oly
       DO I=1-Olx,sNx+Olx-1
        IF ( use_original_hFac ) THEN
         uBarXY=0.25*(
     &       uFld( i , j )*dyG( i , j ,bi,bj)*hFacW( i , j ,k,bi,bj)
     &      +uFld(i+1, j )*dyG(i+1, j ,bi,bj)*hFacW(i+1, j ,k,bi,bj)
     &      +uFld( i ,j-1)*dyG( i ,j-1,bi,bj)*hFacW( i ,j-1,k,bi,bj)
     &      +uFld(i+1,j-1)*dyG(i+1,j-1,bi,bj)*hFacW(i+1,j-1,k,bi,bj))
         IF (upwindVorticity) THEN
          IF (uBarXY.GT.0.) THEN
           vort3v=omega3(i,j)*r_hFacZ(i,j)
          ELSE
           vort3v=omega3(i+1,j)*r_hFacZ(i+1,j)
          ENDIF
         ELSE
           vort3v=0.5*(omega3(i,j)*r_hFacZ(i,j)
     &                +omega3(i+1,j)*r_hFacZ(i+1,j))
         ENDIF
        ELSEIF ( SadournyCoriolis ) THEN
         Zm=0.5*(
     &       uFld( i , j )*dyG( i , j ,bi,bj)*hFacW( i , j ,k,bi,bj)
     &      +uFld( i ,j-1)*dyG( i ,j-1,bi,bj)*hFacW( i ,j-1,k,bi,bj) )
         Zp=0.5*(
     &       uFld(i+1, j )*dyG(i+1, j ,bi,bj)*hFacW(i+1, j ,k,bi,bj)
     &      +uFld(i+1,j-1)*dyG(i+1,j-1,bi,bj)*hFacW(i+1,j-1,k,bi,bj) )
         IF (upwindVorticity) THEN
          IF ( (Zm+Zp) .GT.0.) THEN
           vort3v=Zm*r_hFacZ( i ,j)*omega3( i ,j)
          ELSE
           vort3v=Zp*r_hFacZ(i+1,j)*omega3(i+1,j)
          ENDIF
         ELSE
          Zm=Zm*r_hFacZ( i ,j)*omega3( i ,j)
          Zp=Zp*r_hFacZ(i+1,j)*omega3(i+1,j)
          vort3v=0.5*( Zm + Zp )
         ENDIF
         uBarXY=1.
        ELSE
         uBarXY=0.5*(
     &       uFld( i , j )*dyG( i , j ,bi,bj)*hFacZ(i,j)
     &      +uFld( i ,j-1)*dyG( i ,j-1,bi,bj)*hFacZ(i,j)
     &      +uFld(i+1, j )*dyG(i+1, j ,bi,bj)*hFacZ(i+1,j)
     &      +uFld(i+1,j-1)*dyG(i+1,j-1,bi,bj)*hFacZ(i+1,j)
     &              )/MAX( epsil, hFacZ(i,j)+hFacZ(i+1,j) )
         IF (upwindVorticity) THEN
          IF (uBarXY.GT.0.) THEN
           vort3v=omega3(i,j)
          ELSE
           vort3v=omega3(i+1,j)
          ENDIF
         ELSE
           vort3v=0.5*(omega3(i,j)+omega3(i+1,j))
         ENDIF
        ENDIF
        IF (useJamartMomAdv)
     &   uBarXY = uBarXY * 4.d0 * hFacS(i,j,k,bi,bj)
     &   / MAX( epsil, hFacW( i , j ,k,bi,bj)+hFacW( i ,j-1,k,bi,bj)
     &                +hFacW(i+1, j ,k,bi,bj)+hFacW(i+1,j-1,k,bi,bj) )
        vCoriolisTerm(i,j)=
     &   -vort3v*uBarXY*recip_dyC(i,j,bi,bj)*maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_VI_V_CORIOLIS_C4(
     I        bi,bj,k,
     I        uFld,omega3,r_hFacZ,
     O        vCoriolisTerm,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 omega3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 r_hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vCoriolisTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      Real*8 uBarXY,vort3v,Rjp,Rjm
      Real*8 uBarYm,uBarYp,oneSixth
      LOGICAL upwindVort3
      LOGICAL fourthVort3
      PARAMETER(oneSixth=1.d0/6.d0)
      PARAMETER(upwindVort3=.FALSE.)
      PARAMETER(fourthVort3=.TRUE. )
      DO j=1,sNy+1
       DO i=1,sNx
        IF ( SadournyCoriolis ) THEN
         uBarXY=1.
         uBarYm=0.5*(
     &       uFld( i , j )*dyG( i , j ,bi,bj)*hFacW( i , j ,k,bi,bj)
     &      +uFld( i ,j-1)*dyG( i ,j-1,bi,bj)*hFacW( i ,j-1,k,bi,bj) )
         uBarYp=0.5*(
     &       uFld(i+1, j )*dyG(i+1, j ,bi,bj)*hFacW(i+1, j ,k,bi,bj)
     &      +uFld(i+1,j-1)*dyG(i+1,j-1,bi,bj)*hFacW(i+1,j-1,k,bi,bj) )
         IF (upwindVorticity) THEN
          IF ( (uBarYm+uBarYp) .GT.0.) THEN
           vort3v=uBarYm*r_hFacZ( i ,j)*omega3( i ,j)
          ELSE
           vort3v=uBarYp*r_hFacZ(i+1,j)*omega3(i+1,j)
          ENDIF
         ELSEIF (fourthVort3) THEN
          Rjp = omega3(i+1,j)*r_hFacZ(i+1,j)
     &         -oneSixth*( omega3(i+2,j)*r_hFacZ(i+2,j)
     &                    -omega3( i ,j)*r_hFacZ( i ,j) )
          Rjm = omega3(i,j)*r_hFacZ(i,j)
     &         +oneSixth*( omega3(i+1,j)*r_hFacZ(i+1,j)
     &                    -omega3(i-1,j)*r_hFacZ(i-1,j) )
          vort3v=0.5*( uBarYm*Rjm + uBarYp*Rjp )
         ELSE
          vort3v=0.5*( uBarYm*r_hFacZ( i ,j)*omega3( i ,j)
     &                +uBarYp*r_hFacZ(i+1,j)*omega3(i+1,j) )
         ENDIF
        ELSE
         uBarXY=0.25*(
     &       uFld( i , j )*dyG( i , j ,bi,bj)*hFacW( i , j ,k,bi,bj)
     &      +uFld(i+1, j )*dyG(i+1, j ,bi,bj)*hFacW(i+1, j ,k,bi,bj)
     &      +uFld( i ,j-1)*dyG( i ,j-1,bi,bj)*hFacW( i ,j-1,k,bi,bj)
     &      +uFld(i+1,j-1)*dyG(i+1,j-1,bi,bj)*hFacW(i+1,j-1,k,bi,bj))
         IF (upwindVort3) THEN
          IF (uBarXY.GT.0.) THEN
           vort3v=omega3(i,j)*r_hFacZ(i,j)
          ELSE
           vort3v=omega3(i+1,j)*r_hFacZ(i+1,j)
          ENDIF
         ELSEIF (fourthVort3) THEN
          Rjp=omega3(i+2,j)*r_hFacZ(i+2,j)
     &       -omega3(i+1,j)*r_hFacZ(i+1,j)
          Rjm=omega3(i,j)*r_hFacZ(i,j)
     &       -omega3(i-1,j)*r_hFacZ(i-1,j)
          vort3v=0.5*(omega3(i,j)*r_hFacZ(i,j)
     &               +omega3(i+1,j)*r_hFacZ(i+1,j)
     &               -1./12.*(Rjp-Rjm)
     &               )
         ELSE
          vort3v=0.5*(omega3(i,j)*r_hFacZ(i,j)
     &               +omega3(i+1,j)*r_hFacZ(i+1,j))
         ENDIF
        ENDIF
        vCoriolisTerm(i,j)=
     &   -vort3v*uBarXY*recip_dyC(i,j,bi,bj)
     &                 * maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_VI_V_GRAD_KE( 
     I        bi,bj,K,
     I        KE,
     O        dKEdy,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,K
      Real*8 KE(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dKEdy(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER I,J
       DO J=2-Oly,sNy+Oly
        DO I=1-Olx,sNx+Olx
         dKEdy(I,J)=-recip_dyC(i,j,bi,bj)*(KE(i,j)-KE(i,j-1))
     &       *maskS(i,j,k,BI,BJ)
        ENDDO
       ENDDO
      RETURN
      END
      SUBROUTINE MOM_VI_V_VERTSHEAR( 
     I        bi,bj,K,
     I        vFld,wFld,
     U        vShearTerm,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
       USE PARAMS_mod
      INTEGER bi,bj,K
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 wFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 vShearTerm(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER I,J,Kp1,Km1
      Real*8 mask_Kp1,mask_Km1,wBarYm,wBarYp
      Real*8 vZm,vZp
      Kp1=min(K+1,Nr)
      mask_Kp1=1.
      IF (K.EQ.Nr) mask_Kp1=0.
      Km1=max(K-1,1)
      mask_Km1=1.
      IF (K.EQ.1) mask_Km1=0.
      DO J=2-Oly,sNy+Oly
       DO I=1-Olx,sNx+Olx
        wBarYm=0.5*(
     &    wFld(I,J,K,bi,bj)*rA(i,j,bi,bj)*maskC(i,j,Km1,bi,bj)
     &   +wFld(I,J-1,K,bi,bj)*rA(i,j-1,bi,bj)*maskC(i,j-1,Km1,bi,bj)
     &             )*mask_Km1
        wBarYp=0.5*(
     &    wFld(I,J,Kp1,bi,bj)*rA(i,j,bi,bj)
     &   +wFld(I,J-1,Kp1,bi,bj)*rA(i,j-1,bi,bj)
     &             )*mask_Kp1
        vZm=(vFld(I,J,K,bi,bj)-mask_Km1*vFld(I,J,Km1,bi,bj))*rkSign
        vZp=(mask_Kp1*vFld(I,J,Kp1,bi,bj)-vFld(I,J,K,bi,bj))*rkSign
        IF (upwindShear) THEN
          vShearTerm(I,J)=-0.5*
     &                   (     (wBarYp*vZp+wBarYm*vZm)
     &                        +(ABS(wBarYp)*vZp-ABS(wBarYm)*vZm)
     &                   )*recip_rAs(i,j,bi,bj)
     &                    *recip_hFacS(i,j,k,bi,bj)
     &                    *recip_drF(K)
        ELSE
          vShearTerm(I,J)=-0.5*(wBarYp*vZp+wBarYm*vZm)
     &                    *recip_rAs(i,j,bi,bj)
     &                    *recip_hFacS(i,j,k,bi,bj)
     &                    *recip_drF(K)
        ENDIF
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_CALC_ABSVORT3( 
     I        bi,bj,k,
     I        vort3,
     O        omega3,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vort3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 omega3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      Real*8 nonLinFac,useCoriolisFac
      IF (momAdvection) THEN
        nonLinFac=1.
      ELSE
        nonLinFac=0.
      ENDIF
      IF (useCoriolis) THEN
        useCoriolisFac=1.
      ELSE
        useCoriolisFac=0.
      ENDIF
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        omega3(I,J)=
     &      fCoriG(i,j,bi,bj)*useCoriolisFac
     &     +vort3(i,j)*nonLinFac
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_CALC_HDIV( 
     I        bi,bj,k, hDivScheme,
     I        uFld, vFld,
     O        hDiv,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k,hDivScheme
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hDiv(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      IF (hDivScheme.EQ.1) THEN
       DO J=1-Oly,sNy+Oly-1
        DO I=1-Olx,sNx+Olx-1
         hDiv(I,J)=(
     &       uFld(i+1, j )*dyg(i+1, j ,bi,bj)
     &      -uFld( i , j )*dyg( i , j ,bi,bj)
     &      +vFld( i ,j+1)*dxg( i ,j+1,bi,bj)
     &      -vFld( i , j )*dxg( i , j ,bi,bj)
     &             )*recip_rA(I,J,bi,bj)
        ENDDO
       ENDDO
      ELSEIF (hDivScheme.EQ.2) THEN
       DO J=1-Oly,sNy+Oly-1
        DO I=1-Olx,sNx+Olx-1
         hDiv(I,J)= 
     &    (  uFld(i+1, j )*dyg(i+1, j ,bi,bj)*hFacW(i+1, j ,K,bi,bj)
     &      -uFld( i , j )*dyg( i , j ,bi,bj)*hFacW( i , j ,K,bi,bj)
     &      +vFld( i ,j+1)*dxg( i ,j+1,bi,bj)*hFacS( i ,j+1,K,bi,bj)
     &      -vFld( i , j )*dxg( i , j ,bi,bj)*hFacS( i , j ,K,bi,bj)
     &    )*recip_rA(I,J,bi,bj)
     &     *recip_hFacC(i,j,k,bi,bj)
        ENDDO
       ENDDO
      ELSE
       STOP 'S/R MOM_CALC_HDIV: We should never reach this point!'
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_CALC_HFACZ(
     I        bi,bj,k,
     O        hFacZ,r_hFacZ,
     I        myThid)
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      INTEGER myThid
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 r_hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 hFacZOpen
      DO i=1-Olx,sNx+Olx
       hFacZ(i,1-Oly)=0.
       r_hFacZ(i,1-Oly)=0.
      ENDDO
      DO j=2-Oly,sNy+Oly
       hFacZ(1-Olx,j)=0.
       r_hFacZ(1-Olx,j)=0.
       DO i=2-Olx,sNx+Olx
        hFacZOpen=min(hFacW(i,j,k,bi,bj),
     &                hFacW(i,j-1,k,bi,bj))
        hFacZOpen=min(hFacS(i,j,k,bi,bj),hFacZOpen)
        hFacZOpen=min(hFacS(i-1,j,k,bi,bj),hFacZOpen)
        hFacZ(i,j)=hFacZOpen
        IF (hFacZ(i,j).EQ.0.) THEN
         r_hFacZ(i,j)=0.
        ELSE
         r_hFacZ(i,j)=1./hFacZ(i,j)
        ENDIF
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_CALC_KE(
     I        bi,bj,k,KEscheme,
     I        uFld, vFld,
     O        KE,
     I        myThid)
       USE SIZE_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER KEscheme
      INTEGER myThid
      Real*8 KE(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      IF (KEscheme.EQ.1) THEN
       DO J=1-OLy,sNy+OLy-1
        DO I=1-OLx,sNx+OLx-1
         KE(i,j) = 0.125*(
     &             ( uFld(i,j)+uFld(i+1, j ) )**2
     &            +( vFld(i,j)+vFld( i ,j+1) )**2 )
       ENDDO
      ENDDO
      ELSEIF (KEscheme.EQ.2) THEN
       DO J=1-OLy,sNy+OLy-1
        DO I=1-OLx,sNx+OLx-1
         KE(i,j) = 0.25*(
     &             uFld( i , j )*uFld( i , j )
     &            +uFld(i+1, j )*uFld(i+1, j )
     &            +vFld( i , j )*vFld( i , j )
     &            +vFld( i ,j+1)*vFld( i ,j+1) )
        ENDDO
       ENDDO
      ELSEIF (KEscheme.EQ.3) THEN
       DO J=1-OLy,sNy+OLy-1
        DO I=1-OLx,sNx+OLx-1
         KE(i,j) = 0.25*(
     &             uFld( i , j )*uFld( i , j )*hFacW(i,j,k,bi,bj)
     &            +uFld(i+1, j )*uFld(i+1, j )*hFacW(i+1,j,k,bi,bj)
     &            +vFld( i , j )*vFld( i , j )*hFacS(i,j,k,bi,bj)
     &            +vFld( i ,j+1)*vFld( i ,j+1)*hFacS(i,j+1,k,bi,bj)
     &            )*recip_hFacC(i,j,k,bi,bj)
        ENDDO
       ENDDO
      ELSEIF (KEscheme.EQ.4) THEN
       DO J=1-OLy,sNy+OLy-1
        DO I=1-OLx,sNx+OLx-1
         KE(i,j) = 0.25*(
     &    uFld(i, j )*uFld(i, j )*hFacW(i ,j, k,bi,bj)*rAw(i ,j, bi,bj)
     &   +uFld(i+1,j)*uFld(i+1,j)*hFacW(i+1,j,k,bi,bj)*rAw(i+1,j,bi,bj)
     &   +vFld(i, j )*vFld(i, j )*hFacS(i, j, k,bi,bj)*rAs(i ,j, bi,bj)
     &   +vFld(i,j+1)*vFld(i,j+1)*hFacS(i,j+1,k,bi,bj)*rAs(i,j+1,bi,bj)
     &                  )*recip_hFacC(i,j,k,bi,bj)*recip_rA(i,j,bi,bj)
        ENDDO
       ENDDO
      ELSE
       STOP 'S/R MOM_CALC_KE: We should never reach this point!'
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_CALC_RELVORT3(
     I        bi,bj,k,
     I        uFld, vFld, hFacZ,
     O        vort3,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vort3(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      LOGICAL northWestCorner, northEastCorner,
     &        southWestCorner, southEastCorner
      DO J=1-Oly,sNy+Oly
       DO I=1-Olx,sNx+Olx
        vort3(I,J) = 0.d0
       ENDDO
      ENDDO
      DO J=2-Oly,sNy+Oly
       DO I=2-Olx,sNx+Olx
        vort3(I,J)=
     &      recip_rAz(I,J,bi,bj)*(
     &      vFld(I,J)*dyc(I,J,bi,bj)
     &     -vFld(I-1,J)*dyc(I-1,J,bi,bj)
     &     -uFld(I,J)*dxc(I,J,bi,bj)
     &     +uFld(I,J-1)*dxc(I,J-1,bi,bj)
     &                           )
        IF (hFacZ(i,j).NE.0.) THEN
        ELSE
         vort3(I,J)=0.
        ENDIF
       ENDDO
      ENDDO
      IF (useCubedSphereExchange) THEN
       southWestCorner = .FALSE.
       southEastCorner = .FALSE.
       northWestCorner = .FALSE.
       northEastCorner = .FALSE.
       southWestCorner = .TRUE.
       southEastCorner = .TRUE.
       northWestCorner = .TRUE.
       northEastCorner = .TRUE.
       IF ( southWestCorner ) THEN
         I=1
         J=1
         vort3(I,J)=
     &     +recip_rAz(I,J,bi,bj)*(
     &      vFld(I,J)*dyc(I,J,bi,bj)
     &     -uFld(I,J)*dxc(I,J,bi,bj)
     &     +uFld(I,J-1)*dxc(I,J-1,bi,bj)
     &     )
        IF (hFacZ(i,j).EQ.0.d0) vort3(i,j) = 0.d0
        vort3(I-1,J)=
     &      recip_rAz(I-1,J,bi,bj)*(
     &      vFld(I-1,J)*dyc(I-1,J,bi,bj)
     &     -vFld(I-2,J)*dyc(I-2,J,bi,bj)
     &     -uFld(I-1,J)*dxc(I-1,J,bi,bj)
     &     +vFld(I+0,J-1)*dyc(I+0,J-1,bi,bj)
     &                             )
     &     *maskS(i-1,j,k,bi,bj)*maskS(i-2,j,k,bi,bj)
     &     *maskW(i-1,j,k,bi,bj)*maskS(i,j-1,k,bi,bj)
        vort3(I,J-1)=vort3(I-1,J)
       ENDIF
       IF ( southEastCorner ) THEN
         I=sNx+1
         J=1
         vort3(I,J)=
     &     +recip_rAz(I,J,bi,bj)*(
     &     -vFld(I-1,J)*dyc(I-1,J,bi,bj)
     &     -uFld(I,J)*dxc(I,J,bi,bj)
     &     +uFld(I,J-1)*dxc(I,J-1,bi,bj)
     &     )
        IF (hFacZ(i,j).EQ.0.d0) vort3(i,j) = 0.d0
        vort3(I+1,J)=
     &      recip_rAz(I+1,J,bi,bj)*(
     &      vFld(I+1,J)*dyc(I+1,J,bi,bj)
     &     -vFld(I-0,J)*dyc(I-0,J,bi,bj)
     &     -uFld(I+1,J)*dxc(I+1,J,bi,bj)
     &     -vFld(I-1,J-1)*dyc(I-1,J-1,bi,bj)
     &                           )
     &     *maskS(i+1,j,k,bi,bj)*maskS(i-0,j,k,bi,bj)
     &     *maskW(i+1,j,k,bi,bj)*maskS(i-1,j-1,k,bi,bj)
        vort3(I,J-1)=vort3(I+1,J)
       ENDIF
       IF ( northWestCorner ) THEN
         I=1
         J=sNy+1
         vort3(I,J)=
     &     +recip_rAz(I,J,bi,bj)*(
     &      vFld(I,J)*dyc(I,J,bi,bj)
     &     -uFld(I,J)*dxc(I,J,bi,bj)
     &     +uFld(I,J-1)*dxc(I,J-1,bi,bj)
     &     )
        IF (hFacZ(i,j).EQ.0.d0) vort3(i,j) = 0.d0
        vort3(I-1,J)=
     &      recip_rAz(I-1,J,bi,bj)*(
     &      vFld(I-1,J)*dyc(I-1,J,bi,bj)
     &     -vFld(I-2,J)*dyc(I-2,J,bi,bj)
     &     +vFld(I-0,J+1)*dyc(I-0,J+1,bi,bj)
     &     +uFld(I-1,J-1)*dxc(I-1,J-1,bi,bj)
     &                           )
     &     *maskS(i-1,j,k,bi,bj)*maskS(i-2,j,k,bi,bj)
     &     *maskS(i,j+1,k,bi,bj)*maskW(i-1,j-1,k,bi,bj)
        vort3(I,J+1)=vort3(I-1,J)
       ENDIF
       IF ( northEastCorner ) THEN
         I=sNx+1
         J=sNy+1
         vort3(I,J)=
     &     +recip_rAz(I,J,bi,bj)*(
     &     -vFld(I-1,J)*dyc(I-1,J,bi,bj)
     &     -uFld(I,J)*dxc(I,J,bi,bj)
     &     +uFld(I,J-1)*dxc(I,J-1,bi,bj)
     &     )
        IF (hFacZ(i,j).EQ.0.d0) vort3(i,j) = 0.d0
        vort3(I+1,J)=
     &      recip_rAz(I+1,J,bi,bj)*(
     &      vFld(I+1,J)*dyc(I+1,J,bi,bj)
     &     -vFld(I-0,J)*dyc(I-0,J,bi,bj)
     &     -vFld(I-1,J+1)*dyc(I-1,J+1,bi,bj)
     &     +uFld(I+1,J-1)*dxc(I+1,J-1,bi,bj)
     &                           )
     &     *maskS(i+1,j,k,bi,bj)*maskS(i-0,j,k,bi,bj)
     &     *maskS(i-1,j+1,k,bi,bj)*maskW(i+1,j-1,k,bi,bj)
        vort3(I,J+1)=vort3(I+1,J)
       ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_CALC_STRAIN( 
     I        bi,bj,k,
     I        uFld, vFld, hFacZ,
     O        strain,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 strain(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO J=2-Oly,sNy+Oly
       DO I=2-Olx,sNx+Olx
        strain(I,J)=
     &    ( dyc( i , j ,bi,bj)*vFld( i , j )
     &     -dyc(i-1, j ,bi,bj)*vFld(i-1, j )
     &     +dxc( i , j ,bi,bj)*uFld( i , j )
     &     -dxc( i ,j-1,bi,bj)*uFld( i ,j-1) )*recip_rAz(i,j,bi,bj)
        IF (hFacZ(i,j).EQ.0.) THEN
         strain(I,J)=0.
        ENDIF
       ENDDO
      ENDDO
      IF (useCubedSphereExchange) THEN
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_CALC_TENSION( 
     I        bi,bj,k,
     I        uFld, vFld,
     O        tension,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 tension(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        tension(i,j)= 
     &    ( dyg(i+1, j ,bi,bj)*uFld(i+1, j )
     &     -dyg( i , j ,bi,bj)*uFld( i , j )
     &     -dxg( i ,j+1,bi,bj)*vFld( i ,j+1)
     &     +dxg( i , j ,bi,bj)*vFld( i , j ) )*recip_rA(i,j,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_HDISSIP(
     I        bi,bj,k,
     I        tension,strain,hFacZ,viscAt,viscAs,
     O        uDissip,vDissip,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE GRID_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 tension(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 strain(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 viscAt
      Real*8 viscAs
      Real*8 uDissip(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vDissip(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER I,J
      Real*8 viscA_t(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 viscA_s(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 ASmag, smagfac
      Real*8 vg2Min, vg2Max, AlinMax, AlinMin
      Real*8 lenA2, lenAz2
      IF (deltaTmom.NE.0.) THEN
       vg2Min=viscAhGridMin/deltaTmom
       vg2Max=viscAhGridMax/deltaTmom
      ELSE
       vg2Min=0.
       vg2Max=0.
      ENDIF
      smagfac=(viscC2smag/pi)**2
      DO j=2-Oly,sNy+Oly-1
       DO i=2-Olx,sNx+Olx-1
        IF (viscC2smag.NE.0.) THEN
         lenA2=(2*rA(i,j,bi,bj)/
     &	    (dxF(I,J,bi,bj)+dyF(I,J,bi,bj)))**2
         Asmag=smagfac*lenA2
     &    *sqrt(tension(i,j)**2
     &          +0.25*(strain(i+1, j )**2+strain( i ,j+1)**2
     &                +strain(i-1, j )**2+strain( i ,j-1)**2))
         viscA_t(i,j)=min(viscAhMax,max(viscAt,Asmag))
         IF (vg2Max.GT.0.) THEN
            AlinMax=vg2Max*lenA2
            viscA_t(i,j)=min(AlinMax,viscA_t(i,j))
         ENDIF
         AlinMin=vg2Min*lenA2
         viscA_t(i,j)=max(AlinMin,viscA_t(i,j))
         lenAz2=(2*rAz(i,j,bi,bj)/
     &       (dxV(I,J,bi,bj)+dyU(I,J,bi,bj)))**2
         Asmag=smagfac*lenAz2
     &    *sqrt(strain(i,j)**2
     &          +0.25*(tension( i , j )**2+tension( i ,j+1)**2
     &                +tension(i+1, j )**2+tension(i+1,j+1)**2))
         viscA_s(i,j)=min(viscAhMax,max(viscAs,Asmag))
         IF (vg2Max.GT.0.) THEN
            AlinMax=vg2Max*lenAz2
            viscA_s(i,j)=min(AlinMax,viscA_s(i,j))
         ENDIF
         AlinMin=vg2Min*lenAz2
         viscA_s(i,j)=max(AlinMin,viscA_s(i,j))
        ELSE
         viscA_t(i,j)=viscAt
         viscA_s(i,j)=viscAs
        ENDIF
       ENDDO
      ENDDO
      DO j=2-Oly,sNy+Oly-1
       DO i=2-Olx,sNx+Olx-1
        uDissip(i,j) = 
     &   recip_dyg(i,j,bi,bj)*recip_dyg(i,j,bi,bj)
     &   *recip_dxc(i,j,bi,bj)
     &   *(
     &      dyf( i , j ,bi,bj)*dyf( i , j ,bi,bj)
     &        *viscA_t( i , j )*tension( i , j )
     &     -dyf(i-1, j ,bi,bj)*dyf(i-1, j ,bi,bj)
     &        *viscA_t(i-1, j )*tension(i-1, j )
     &    )
     &   +recip_dxc(i,j,bi,bj)*recip_dxc(i,j,bi,bj)
     &   *recip_dyg(i,j,bi,bj)
     &   *(
     &      dxv( i ,j+1,bi,bj)*dxv( i ,j+1,bi,bj)
     &        *viscA_s(i,j+1)*strain( i ,j+1)
     &     -dxv( i , j ,bi,bj)*dxv( i , j ,bi,bj)
     &        *viscA_s(i, j )*strain( i , j )
     &    )
        vDissip(i,j) = 
     &   recip_dyc(i,j,bi,bj)*recip_dyc(i,j,bi,bj)
     &   *recip_dxg(i,j,bi,bj)
     &   *(
     &      dyu(i+1, j ,bi,bj)*dyu(i+1, j ,bi,bj)
     &        *viscA_s(i+1,j)*strain(i+1,j)
     &     -dyu( i , j ,bi,bj)*dyu( i , j ,bi,bj)
     &        *viscA_s( i ,j)*strain( i ,j)
     &    )
     &   -recip_dxg(i,j,bi,bj)*recip_dxg(i,j,bi,bj)
     &   *recip_dyc(i,j,bi,bj)
     &   *(
     &      dxf( i , j ,bi,bj)*dxf( i , j ,bi,bj)
     &        *viscA_t(i, j )*tension(i, j )
     &     -dxf( i ,j-1,bi,bj)*dxf( i ,j-1,bi,bj)
     &        *viscA_t(i,j-1)*tension(i,j-1)
     &    )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_BOTTOMDRAG(
     I        bi,bj,k,
     I        uFld, KE, KappaRU,
     O        uDragTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 KE(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 KappaRU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      INTEGER myThid
      Real*8 uDragTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J,kDown,kDownC,kBottom
      Real*8 viscFac
      Real*8 rdrckp1,maskDown
      IF ( usingZCoords ) THEN
       kBottom = Nr
       kDown   = min(k+1,kBottom)
       kDownC  = kDown
      ELSE
       kBottom = 1
       kDown   = max(k-1,kBottom)
       kDownC  = k
      ENDIF	
      rdrckp1=recip_drC(kDownC)
      IF (k.EQ.kBottom) rdrckp1=recip_drF(k)
      viscFac=0.
      IF (no_slip_bottom) viscFac=1.
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx+1,sNx+Olx-1
        maskDown=maskW(i,j,kDown,bi,bj)
        IF (k.EQ.kBottom) maskDown=0.
        uDragTerms(i,j)=
     &   -recip_hFacW(i,j,k,bi,bj)*recip_drF(k)
     &   *( 
     &      2.*KappaRU(i,j,kDownC)*rdrckp1*viscFac
     &     + bottomDragLinear
     &    )*(1.-maskDown)*uFld(i,j)
        IF ( (KE(i,j)+KE(i-1,j)) .NE. 0. ) THEN
         uDragTerms(i,j)=uDragTerms(i,j)
     &    -recip_hFacW(i,j,k,bi,bj)*recip_drF(k)
     &    *bottomDragQuadratic*sqrt(KE(i,j)+KE(i-1,j))
     &    *(1.-maskDown)*uFld(i,j)
        ENDIF
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_U_RVISCFLUX(
     I        bi,bj,k,
     I        uFld, KappaRU,
     O        rViscFluxU,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 KappaRU(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      INTEGER myThid
      Real*8 rViscFluxU(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      IF ( k.LE.1 .OR. k.GT.Nr ) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
          rViscFluxU(i,j) = 0.d0
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly-1
        DO i=1-Olx,sNx+Olx-1
          rViscFluxU(i,j) =
     &      -KappaRU(i,j,k)
     &      *rAw(i,j,bi,bj)
     &      *( uFld(i,j,k,bi,bj)-uFld(i,j,k-1,bi,bj)
     &       )*rkSign*recip_drC(k)
     &      *maskW(i,j,k,bi,bj)
     &      *maskW(i,j,k-1,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_U_SIDEDRAG(
     I        bi,bj,k,
     I        uFld, del2u, hFacZ,
     O        uDragTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 uFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2u(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 uDragTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 hFacZClosedS,hFacZClosedN
      Real*8 Ahtmp,A4tmp
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        hFacZClosedS = hFacW(i,j,k,bi,bj) - hFacZ(i,j)
        hFacZClosedN = hFacW(i,j,k,bi,bj) - hFacZ(i,j+1)
        Ahtmp=min(viscAh+viscAhGrid*rAw(i,j,bi,bj)/deltaTmom,
     &            viscAhMax)
        A4tmp=min(viscA4+viscA4Grid*(rAw(i,j,bi,bj)**2)/deltaTmom,
     &            viscA4Max)
        A4tmp=min(A4tmp,viscA4GridMax*(rAw(i,j,bi,bj)**2)/deltaTmom)
        A4tmp=max(A4tmp,viscA4GridMin*(rAw(i,j,bi,bj)**2)/deltaTmom)
        uDragTerms(i,j) =
     &   -recip_hFacW(i,j,k,bi,bj)
     &   *recip_drF(k)*recip_rAw(i,j,bi,bj)
     &   *( hFacZClosedS*dxV(i, j ,bi,bj)
     &      *recip_dyU(i, j ,bi,bj)
     &     +hFacZClosedN*dxV(i,j+1,bi,bj)
     &      *recip_dyU(i,j+1,bi,bj) )
     &   *drF(k)*2.*(
     &                Ahtmp*uFld(i,j)
     &               -A4tmp*del2u(i,j)
     &              )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_BOTTOMDRAG(
     I        bi,bj,k,
     I        vFld, KE, KappaRV,
     O        vDragTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 KE(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 KappaRV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 viscFac
      INTEGER myThid
      Real*8 vDragTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J,kDown,kDownC,kBottom
      Real*8 rdrckp1,maskDown
      IF ( usingZCoords ) THEN
       kBottom = Nr
       kDown   = min(k+1,kBottom)
       kDownC  = kDown
      ELSE
       kBottom = 1
       kDown   = max(k-1,kBottom)
       kDownC  = k
      ENDIF
      rdrckp1=recip_drC(kDownC)
      viscFac=0.
      IF (no_slip_bottom) viscFac=1.
      IF (k.EQ.kBottom) rdrckp1=recip_drF(k)
      DO j=1-Oly+1,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        maskDown=maskS(i,j,kdown,bi,bj)
        IF (k.EQ.kBottom) maskDown=0.
        vDragTerms(i,j)=
     &   -recip_hFacS(i,j,k,bi,bj)*recip_drF(k)
     &   *( 
     &      2.*KappaRV(i,j,kDownC)*rdrckp1*viscFac
     &     + bottomDragLinear
     &    )*(1.-maskDown)*vFld(i,j)
        IF ( (KE(i,j)+KE(i,j-1)) .NE. 0. ) THEN
         vDragTerms(i,j)=vDragTerms(i,j)
     &    -recip_hFacS(i,j,k,bi,bj)*recip_drF(k)
     &    *bottomDragQuadratic*sqrt(KE(i,j)+KE(i,j-1))
     &    *(1.-maskDown)*vFld(i,j)
        ENDIF
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE MOM_V_RVISCFLUX(
     I        bi,bj,k,
     I        vFld, KappaRV,
     O        rViscFluxV,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 KappaRV(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      INTEGER myThid
      Real*8 rViscFluxV(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER i,j
      IF ( k.LE.1 .OR. k.GT.Nr ) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
          rViscFluxV(i,j) = 0.d0
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly-1
        DO i=1-Olx,sNx+Olx-1
          rViscFluxV(i,j) =
     &     -KappaRV(i,j,k)
     &     *rAs(i,j,bi,bj)
     &     *( vFld(i,j,k,bi,bj)-vFld(i,j,k-1,bi,bj)
     &      )*rkSign*recip_drC(k)
     &     *maskS(i,j,k,bi,bj)
     &     *maskS(i,j,k-1,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE MOM_V_SIDEDRAG(
     I        bi,bj,k,
     I        vFld, del2v, hFacZ,
     O        vDragTerms,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 vFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 del2v(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 hFacZ(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      Real*8 vDragTerms(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER I,J
      Real*8 hFacZClosedE,hFacZClosedW
      Real*8 Ahtmp,A4tmp
      DO j=1-Oly,sNy+Oly-1
       DO i=1-Olx,sNx+Olx-1
        hFacZClosedW = hFacS(i,j,k,bi,bj) - hFacZ(i,j)
        hFacZClosedE = hFacS(i,j,k,bi,bj) - hFacZ(i+1,j)
        Ahtmp=min(viscAh+viscAhGrid*rAs(i,j,bi,bj)/deltaTmom,
     &            viscAhMax)
        A4tmp=min(viscA4+viscA4Grid*(rAs(i,j,bi,bj)**2)/deltaTmom,
     &            viscA4Max)
        IF (viscA4GridMax.GT.0.) THEN
           A4tmp=min(A4tmp,viscA4GridMax*(rAw(i,j,bi,bj)**2)/deltaTmom)
        ENDIF
        A4tmp=max(A4tmp,viscA4GridMin*(rAw(i,j,bi,bj)**2)/deltaTmom)
        vDragTerms(i,j) =
     &   -recip_hFacS(i,j,k,bi,bj)
     &   *recip_drF(k)*recip_rAs(i,j,bi,bj)
     &   *( hFacZClosedW*dyU( i ,j,bi,bj)
     &      *recip_dxV( i ,j,bi,bj)
     &     +hFacZClosedE*dyU(i+1,j,bi,bj)
     &      *recip_dxV(i+1,j,bi,bj) )
     &   *drF(k)*2.*(
     &                Ahtmp*vFld(i,j)*cosFacV(J,bi,bj)
     &               -A4tmp*del2v(i,j)*cosFacV(J,bi,bj)
     &               -viscA4*del2v(i,j)*cosFacV(J,bi,bj)
     &              )
       ENDDO
      ENDDO
      RETURN
      END
      LOGICAL FUNCTION DIFFERENT_MULTIPLE( freq, val1, step )
      IMPLICIT NONE
      Real*8  freq, val1, step
      Real*8  v1, v2, v3, v4, d1, d2, d3
      DIFFERENT_MULTIPLE = .FALSE.
      IF ( freq .NE. 0. ) THEN
        IF ( ABS(step) .GT. freq ) THEN
         DIFFERENT_MULTIPLE = .TRUE.
        ELSE
          v1 = val1
          v2 = val1 - step
          v3 = val1 + step
          v4 = NINT(v1/freq)*freq
          d1 = v1-v4
          d2 = v2-v4
          d3 = v3-v4
          IF ( ABS(d1) .LE. ABS(d2) .AND. ABS(d1) .LE. ABS(d3) )
     &        DIFFERENT_MULTIPLE = .TRUE.
        ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE ADAMS_BASHFORTH2(
     I                     bi, bj, k,
     U                     gTracer, gTrNm1,
     I                     myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8  gTracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gTrNm1 (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myIter, myThid
      INTEGER i,j
      Real*8 ab15,ab05
      Real*8 gTrtmp
      IF ( myIter.EQ.0 ) THEN
       ab15=1.0
       ab05=0.0
      ELSE
       ab15=1.5+abEps
       ab05=-(0.5+abEps)
      ENDIF
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        gTrtmp = ab15*gTracer(i,j,k,bi,bj) 
     &         + ab05*gTrNm1(i,j,k,bi,bj)
        gTrNm1(i,j,k,bi,bj) = gTracer(i,j,k,bi,bj)
        gTracer(i,j,k,bi,bj) = gTrtmp
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CALC_3D_DIFFUSIVITY( 
     I        bi,bj,iMin,iMax,jMin,jMax,
     I        trIdentity, trUseGMRedi, trUseKPP,
     O        KappaRTr,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE GAD_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER trIdentity
      LOGICAL trUseGMRedi, trUseKPP
      Real*8 KappaRTr(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      INTEGER myThid
      INTEGER i,j,k
      INTEGER iTr
      Real*8 KbryanLewis79
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      IF ( trIdentity.EQ.GAD_TEMPERATURE) THEN
       DO k = 1,Nr
        KbryanLewis79=diffKrBL79surf+(diffKrBL79deep-diffKrBL79surf)
     &  *( atan( -( rF(k)-diffKrBL79Ho )/diffKrBL79scl )/PI+0.5d0)
        DO j = 1-Oly,sNy+Oly
         DO i = 1-Olx,sNx+Olx
          KappaRTr(i,j,k) =
     &         IVDConvCount(i,j,k,bi,bj)*ivdc_kappa
     &       + diffKr(i,j,k,bi,bj)
     &       + KbryanLewis79
         ENDDO
        ENDDO
       ENDDO
      ELSEIF ( trIdentity.EQ.GAD_SALINITY) THEN
       DO k = 1,Nr
        KbryanLewis79=diffKrBL79surf+(diffKrBL79deep-diffKrBL79surf)
     &  *( atan( -( rF(k)-diffKrBL79Ho )/diffKrBL79scl )/PI+0.5d0)
        DO j = 1-Oly, sNy+Oly
         DO i = 1-Olx, sNx+Olx
          KappaRTr(i,j,k) =
     &         IVDConvCount(i,j,k,bi,bj)*ivdc_kappa
     &       + diffKr(i,j,k,bi,bj)
     &       + KbryanLewis79
         ENDDO
        ENDDO
       ENDDO
      ELSE
        WRITE(msgBuf,'(A,I4)')
     &      ' CALC_3D_DIFFUSIVITY: Invalid tracer Id: ',trIdentity
        CALL PRINT_ERROR(msgBuf, myThid)
        STOP 'ABNORMAL END: S/R CALC_3D_DIFFUSIVITY'
      ENDIF
      RETURN
      END
      SUBROUTINE CALC_BUOYANCY(
     I      bi, bj, iMin, iMax, jMin, jMax,  k, rhoLoc,
     O      buoy,
     I      myThid )
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k			
      Real*8 rhoLoc(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 buoy  (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      IF    ( buoyancyRelation .eq. 'ATMOSPHERIC'  ) THEN
       DO j=jMin,jMax
        DO i=iMin,iMax
         buoy(i,j)=(theta(i,j,k,bi,bj)-tRef(K))/tRef(K)
        ENDDO
       ENDDO
      ELSEIF ( buoyancyRelation .eq. 'OCEANIC' ) THEN
       DO j=jMin,jMax
        DO i=iMin,iMax
         buoy(i,j)=-Gravity*recip_rhoConst*rholoc(i,j)
        ENDDO
       ENDDO
      ELSEIF ( buoyancyRelation .eq. 'OCEANICP' ) THEN
       DO j=jMin,jMax
        DO i=iMin,iMax
         if ( rholoc(i,j) .ne. 0. ) then
          rholoc(i,j) = 1./rholoc(i,j)
          buoy(i,j)=rholoc(i,j)
         endif
        ENDDO
       ENDDO
      ELSE
       STOP 
     &'CALC_BUOANCY: variable "buoyancyRelation" has an illegal value'
      ENDIF
      RETURN
      END
      SUBROUTINE CALC_COMMON_FACTORS( 
     I        bi,bj,iMin,iMax,jMin,jMax,k,
     O        xA,yA,uTrans,vTrans,rTrans,maskUp,
     I        myThid)
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax,k
      Real*8 xA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 yA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 maskUp(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER i,j
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        xA(i,j)      = 0.d0
        yA(i,j)      = 0.d0
        uTrans(i,j)  = 0.d0
        vTrans(i,j)  = 0.d0
        rTrans(i,j)  = 0.d0
       ENDDO
      ENDDO      
      IF (K .EQ. 1) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
          maskUp(i,j) = 0.
         ENDDO
        ENDDO
      ELSE
        DO j=jMin,jMax
         DO i=iMin,iMax
          maskUp(i,j) = maskC(i,j,k-1,bi,bj)*maskC(i,j,k,bi,bj)
         ENDDO
        ENDDO
      ENDIF
      DO j=jMin,jMax
       DO i=iMin,iMax
        xA(i,j) = dyG(i,j,bi,bj)
     &   *drF(k)*hFacW(i,j,k,bi,bj)
        yA(i,j) = dxG(i,j,bi,bj)
     &   *drF(k)*hFacS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        uTrans(i,j) = uVel(i,j,k,bi,bj)*xA(i,j)
        vTrans(i,j) = vVel(i,j,k,bi,bj)*yA(i,j)
       ENDDO
      ENDDO
      DO j=jMin,jMax
        DO i=iMin,iMax
          rTrans(i,j) = wVel(i,j,k,bi,bj)*rA(i,j,bi,bj)*maskUp(i,j)
        ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CALC_DIFFUSIVITY( 
     I        bi,bj,iMin,iMax,jMin,jMax,k,
     I        maskUp,
     O        KappaRT,KappaRS,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax,K
      Real*8 maskUp(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 KappaRT(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 KappaRS(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      Real*8 KbryanLewis79
      KbryanLewis79=diffKrBL79surf+(diffKrBL79deep-diffKrBL79surf)
     & *( atan( -( rF(k)-diffKrBL79Ho )/diffKrBL79scl )/PI+0.5d0)
      DO j = 1-Oly, sNy+Oly
       DO i = 1-Olx, sNx+Olx
        KappaRT(i,j) =
     &         IVDConvCount(i,j,k,bi,bj)*ivdc_kappa
     &       + diffKr(i,j,k,bi,bj)
     &       + KbryanLewis79
       ENDDO
      ENDDO
      DO j = 1-Oly, sNy+Oly
       DO i = 1-Olx, sNx+Olx
        KappaRS(i,j) =
     &         IVDConvCount(i,j,k,bi,bj)*ivdc_kappa
     &       + diffKr(i,j,k,bi,bj)
     &       + KbryanLewis79
       ENDDO
      ENDDO
      DO j = 1-Oly, sNy+Oly
       DO i = 1-Olx, sNx+Olx
        KappaRT(i,j) = maskUp(i,j)*KappaRT(i,j)
        KappaRS(i,j) = maskUp(i,j)*KappaRS(i,j)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CALC_DIV_GHAT(
     I        bi,bj,iMin,iMax,jMin,jMax,K,
     I        xA,yA,
     U        cg2d_b,
     I        myThid)
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SOLVE_FOR_PRESSURE3D_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER K
      Real*8 xA (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 yA (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 cg2d_b(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER myThid
      INTEGER i,j
      Real*8 pf (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      IF (implicDiv2Dflow.EQ.1.) THEN
        DO j=1,sNy
         DO i=1,sNx+1
          pf(i,j) = xA(i,j)*gU(i,j,k,bi,bj) / deltaTmom
         ENDDO
        ENDDO
      ELSEIF (exactConserv) THEN
        DO j=1,sNy
         DO i=1,sNx+1
          pf(i,j) = implicDiv2Dflow 
     &             *xA(i,j)*gU(i,j,k,bi,bj) / deltaTmom
         ENDDO
        ENDDO
      ELSE
        DO j=1,sNy
         DO i=1,sNx+1
          pf(i,j) = ( implicDiv2Dflow * gU(i,j,k,bi,bj)
     &          + (1.-implicDiv2Dflow) * uVel(i,j,k,bi,bj)
     &               ) * xA(i,j) / deltaTmom
         ENDDO
        ENDDO
      ENDIF
      DO j=1,sNy
       DO i=1,sNx
        cg2d_b(i,j,bi,bj) = cg2d_b(i,j,bi,bj) +
     &   pf(i+1,j)-pf(i,j)
       ENDDO
      ENDDO
      IF (implicDiv2Dflow.EQ.1.) THEN
        DO j=1,sNy+1
         DO i=1,sNx
          pf(i,j) = yA(i,j)*gV(i,j,k,bi,bj) / deltatmom
         ENDDO
        ENDDO
      ELSEIF (exactConserv) THEN
        DO j=1,sNy+1
         DO i=1,sNx
          pf(i,j) = implicDiv2Dflow
     &             *yA(i,j)*gV(i,j,k,bi,bj) / deltatmom
         ENDDO
        ENDDO
      ELSE
        DO j=1,sNy+1
         DO i=1,sNx
          pf(i,j) = ( implicDiv2Dflow * gV(i,j,k,bi,bj)
     &          + (1.-implicDiv2Dflow) * vVel(i,j,k,bi,bj)
     &               ) * yA(i,j) / deltaTmom
         ENDDO
        ENDDO
      ENDIF
      DO j=1,sNy
       DO i=1,sNx
        cg2d_b(i,j,bi,bj) = cg2d_b(i,j,bi,bj) +
     &   pf(i,j+1)-pf(i,j)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CALC_GRAD_PHI_HYD( 
     I                       k, bi, bj, iMin,iMax, jMin,jMax,
     I                       phiHydC, alphRho, tFld, sFld,
     O                       dPhiHydX, dPhiHydY,
     I                       myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
       USE DYNVARS_mod
      INTEGER k, bi,bj, iMin,iMax, jMin,jMax
      Real*8 phiHydC(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 alphRho(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 dPhiHydX(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 dPhiHydY(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 myTime
      INTEGER myIter, myThid
      INTEGER i,j
      Real*8 varLoc(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 factorZ, factorP, conv_theta2T
      Real*8 factPI
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      IF (.TRUE.) THEN
       DO j=jMin-1,jMax
        DO i=iMin-1,iMax
         varLoc(i,j) = phiHydC(i,j)+phi0surf(i,j,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      DO j=jMin,jMax
       DO i=iMin,iMax
        dPhiHydX(i,j) = recip_dxC(i,j,bi,bj)
     &                *( varLoc(i,j)-varLoc(i-1,j) )
        dPhiHydY(i,j) = recip_dyC(i,j,bi,bj)
     &                *( varLoc(i,j)-varLoc(i,j-1) )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CALC_GRAD_PHI_SURF( bi, bj, iMin, iMax, jMin, jMax,
     I                       etaFld,
     O                       phiSurfX, phiSurfY,
     I                       myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      Real*8 etaFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 phiSurfX(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 phiSurfY(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      DO j=jMin,jMax
       DO i=iMin,iMax
        phiSurfX(i,j)=recip_dxC(i,j,bi,bj)*
     &   ( Bo_surf(i,j,bi,bj)*etaFld(i,j,bi,bj)
     &   - Bo_surf(i-1,j,bi,bj)*etaFld(i-1,j,bi,bj) )      
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        phiSurfY(i,j)=recip_dyC(i,j,bi,bj)*
     &   ( Bo_surf(i,j,bi,bj)*etaFld(i,j,bi,bj)
     &   - Bo_surf(i,j-1,bi,bj)*etaFld(i,j-1,bi,bj) ) 
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CALC_GS( 
     I           bi,bj,iMin,iMax,jMin,jMax,k,kM1,kUp,kDown,
     I           xA,yA,uTrans,vTrans,rTrans,rTransKp1,maskUp,
     I           KappaRS,
     U           fVerS,
     I           myTime,myIter,myThid )
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GAD_mod
      Real*8 fVerS (1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 xA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 yA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTransKp1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 maskUp(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 KappaRS(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER k,kUp,kDown,kM1
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      Real*8     myTime
      INTEGER myIter
      INTEGER myThid
      LOGICAL calcAdvection
      INTEGER iterNb
      fVerS(1,1,kDown) = fVerS(1,1,kDown)
      calcAdvection = saltAdvection .AND. .NOT.saltMultiDimAdvec
      CALL GAD_CALC_RHS(
     I           bi,bj,iMin,iMax,jMin,jMax,k,kM1,kUp,kDown,
     I           xA,yA,uTrans,vTrans,rTrans,rTransKp1,maskUp,
     I           uVel, vVel, wVel,
     I           diffKhS, diffK4S, KappaRS, Salt,
     I           GAD_SALINITY, saltAdvScheme, saltVertAdvScheme,
     I           calcAdvection, saltImplVertAdv,
     U           fVerS, gS,
     I           myTime, myIter, myThid )
      IF ( saltForcing .AND. forcing_In_AB )
     & CALL EXTERNAL_FORCING_S(
     I     iMin,iMax,jMin,jMax,bi,bj,k,
     I     myTime,myThid)
      IF ( saltAdamsBashforth ) THEN
        iterNb = myIter
        IF (staggerTimeStep) iterNb = myIter - 1
        CALL ADAMS_BASHFORTH2(
     I                        bi, bj, k,
     U                        gS, gsNm1,
     I                        iterNb, myThid )
      ENDIF
      IF ( saltForcing .AND. .NOT.forcing_In_AB )
     & CALL EXTERNAL_FORCING_S(
     I     iMin,iMax,jMin,jMax,bi,bj,k,
     I     myTime,myThid)
      RETURN
      END
      SUBROUTINE CALC_GT( 
     I           bi,bj,iMin,iMax,jMin,jMax,k,kM1,kUp,kDown,
     I           xA,yA,uTrans,vTrans,rTrans,rTransKp1,maskUp,
     I           KappaRT,
     U           fVerT,
     I           myTime,myIter,myThid )
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GAD_mod
      Real*8 fVerT (1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 xA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 yA    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTransKp1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 maskUp(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 KappaRT(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER k,kUp,kDown,kM1
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      Real*8     myTime
      INTEGER myIter
      INTEGER myThid
      LOGICAL calcAdvection
      INTEGER iterNb
      fVerT(1,1,kDown) = fVerT(1,1,kDown)
      calcAdvection = tempAdvection .AND. .NOT.tempMultiDimAdvec
      CALL GAD_CALC_RHS(
     I           bi,bj,iMin,iMax,jMin,jMax,k,kM1,kUp,kDown,
     I           xA,yA,uTrans,vTrans,rTrans,rTransKp1,maskUp,
     I           uVel, vVel, wVel,
     I           diffKhT, diffK4T, KappaRT, theta,
     I           GAD_TEMPERATURE, tempAdvScheme, tempVertAdvScheme,
     I           calcAdvection, tempImplVertAdv,
     U           fVerT, gT,
     I           myTime, myIter, myThid )
      IF ( tempForcing .AND. forcing_In_AB )
     & CALL EXTERNAL_FORCING_T(
     I     iMin,iMax,jMin,jMax,bi,bj,k,
     I     myTime,myThid)
      IF ( tempAdamsBashforth ) THEN
        iterNb = myIter
        IF (staggerTimeStep) iterNb = myIter - 1
        CALL ADAMS_BASHFORTH2(
     I                        bi, bj, k,
     U                        gT, gtNm1,
     I                        iterNb, myThid )
      ENDIF
      IF ( tempForcing .AND. .NOT.forcing_In_AB )
     & CALL EXTERNAL_FORCING_T(
     I     iMin,iMax,jMin,jMax,bi,bj,k,
     I     myTime,myThid)
      RETURN
      END
      SUBROUTINE CALC_IVDC( 
     I       bi, bj, iMin, iMax, jMin, jMax, K,
     I       rhoKm1, rhoKp1,
     I       myTime,myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax,K
      Real*8 rhoKm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rhoKp1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER i,j
       DO j=jMin,jmax
        DO i=iMin,imax
         IF ( hFacC(i,j,k,bi,bj) .GT. 0. .AND.
     &        (rhokm1(i,j)-rhokp1(i,j))*rkSign*gravitySign.GT.0. ) THEN
          IVDConvCount(i,j,k,bi,bj) = 1.d0
         ELSE
          IVDConvCount(i,j,k,bi,bj) = 0.d0
         ENDIF
        ENDDO
       ENDDO
      RETURN
      END
      SUBROUTINE CALC_PHI_HYD(
     I                         bi, bj, iMin, iMax, jMin, jMax, k,
     I                         tFld, sFld,
     U                         phiHydF,
     O                         phiHydC, dPhiHydX, dPhiHydY,
     I                         myTime, myIter, myThid)
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE tamc_mod
       USE tamc_keys_mod
       USE SURFACE_mod
       USE DYNVARS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax,k
      Real*8 tFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 phiHydF(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 phiHydC(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dPhiHydX(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 dPhiHydY(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 myTime
      INTEGER myIter, myThid
      INTEGER i,j
      Real*8 zero, one, half
      Real*8 alphaRho(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dRlocM,dRlocP, ddRloc, locAlpha
      Real*8 ddPIm, ddPIp, rec_dRm, rec_dRp
      Real*8 surfPhiFac
      INTEGER iMnLoc,jMnLoc
      PARAMETER ( zero= 0.d0 , one= 1.d0 , half= .5d0 )
      LOGICAL useDiagPhiRlow, addSurfPhiAnom
      useDiagPhiRlow = .TRUE.
      addSurfPhiAnom = select_rStar.EQ.0 .AND. nonlinFreeSurf.GT.3
      surfPhiFac = 0.
      IF (addSurfPhiAnom) surfPhiFac = 1.
          act1 = bi - myBxLo(myThid)
          max1 = myBxHi(myThid) - myBxLo(myThid) + 1
          act2 = bj - myByLo(myThid)
          max2 = myByHi(myThid) - myByLo(myThid) + 1
          act3 = myThid - 1
          max3 = nTx*nTy
          act4 = ikey_dynamics - 1
          ikey = (act1 + 1) + act2*max1
     &                      + act3*max1*max2
     &                      + act4*max1*max2*max3
      IF (k.EQ.1) THEN
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
           phiHydF(i,j) = 0.
         ENDDO
        ENDDO
      ENDIF
      IF ( buoyancyRelation .EQ. 'OCEANIC' ) THEN
        kkey = (ikey-1)*Nr + k
        CALL FIND_RHO( bi, bj, iMin, iMax, jMin, jMax, k, k,
     &                 tFld, sFld,
     &                 alphaRho, myThid)
        IF (quasiHydrostatic) THEN
         CALL QUASIHYDROSTATICTERMS(bi,bj,k,alphaRho,myThid)
        ENDIF
       IF (integr_GeoPot.EQ.1) THEN
         DO j=jMin,jMax
          DO i=iMin,iMax
           phiHydC(i,j)=phiHydF(i,j)
     &       + half*drF(k)*gravity*alphaRho(i,j)*recip_rhoConst
           phiHydF(i,j)=phiHydF(i,j)
     &            + drF(k)*gravity*alphaRho(i,j)*recip_rhoConst
          ENDDO
         ENDDO
       ELSE
         dRlocM=half*drC(k)
         IF (k.EQ.1) dRlocM=rF(k)-rC(k)
         IF (k.EQ.Nr) THEN
           dRlocP=rC(k)-rF(k+1)
         ELSE
           dRlocP=half*drC(k+1)
         ENDIF
         DO j=jMin,jMax
          DO i=iMin,iMax
            phiHydC(i,j)=phiHydF(i,j)
     &        +dRlocM*gravity*alphaRho(i,j)*recip_rhoConst
            phiHydF(i,j)=phiHydC(i,j)
     &        +dRlocP*gravity*alphaRho(i,j)*recip_rhoConst
          ENDDO
         ENDDO
       ENDIF
      ELSEIF ( buoyancyRelation .EQ. 'OCEANICP' ) THEN
            kkey = (ikey-1)*Nr + k
        CALL FIND_RHO( bi, bj, iMin, iMax, jMin, jMax, k, k,
     &                 tFld, sFld,
     &                 alphaRho, myThid)
        DO j=jMin,jMax
          DO i=iMin,iMax
            locAlpha=alphaRho(i,j)+rhoConst
            alphaRho(i,j)=maskC(i,j,k,bi,bj)*
     &              (one/locAlpha - recip_rhoConst)
          ENDDO
        ENDDO
       IF (integr_GeoPot.EQ.1) THEN
         DO j=jMin,jMax
          DO i=iMin,iMax
           IF (k.EQ.ksurfC(i,j,bi,bj)) THEN
             ddRloc = Ro_surf(i,j,bi,bj)-rC(k)
             phiHydC(i,j) = ddRloc*alphaRho(i,j)
           ELSE
             phiHydC(i,j) = phiHydF(i,j) + half*drF(k)*alphaRho(i,j)
           ENDIF
             phiHydF(i,j) = phiHydC(i,j) + half*drF(k)*alphaRho(i,j)
          ENDDO
         ENDDO
       ELSE
         dRlocM=half*drC(k)
         IF (k.EQ.1) dRlocM=rF(k)-rC(k)
         IF (k.EQ.Nr) THEN
           dRlocP=rC(k)-rF(k+1)
         ELSE
           dRlocP=half*drC(k+1)
         ENDIF
         rec_dRm = one/(rF(k)-rC(k))
         rec_dRp = one/(rC(k)-rF(k+1))
         DO j=jMin,jMax
          DO i=iMin,iMax
           IF (k.EQ.ksurfC(i,j,bi,bj)) THEN
             ddRloc = Ro_surf(i,j,bi,bj)-rC(k)
             phiHydC(i,j) =( MAX(zero,ddRloc)*rec_dRm*dRlocM
     &                      +MIN(zero,ddRloc)*rec_dRp*dRlocP
     &                     )*alphaRho(i,j)
           ELSE
             phiHydC(i,j) = phiHydF(i,j) + dRlocM*alphaRho(i,j)
           ENDIF
             phiHydF(i,j) = phiHydC(i,j) + dRlocP*alphaRho(i,j)
          ENDDO
         ENDDO
       ENDIF
      ELSEIF ( buoyancyRelation .EQ. 'ATMOSPHERIC' ) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
          alphaRho(i,j)=maskC(i,j,k,bi,bj)
     &             *( tFld(i,j,k,bi,bj)*(sFld(i,j,k,bi,bj)*atm_Rq+one) 
     &               -tRef(k) )
         ENDDO
        ENDDO
       IF (integr_GeoPot.EQ.0) THEN
         IF (k.EQ.1) THEN
           ddPIm=atm_Cp*( ((rF( k )/atm_Po)**atm_kappa)
     &                   -((rC( k )/atm_Po)**atm_kappa) )
         ELSE
           ddPIm=atm_Cp*( ((rC(k-1)/atm_Po)**atm_kappa)
     &                   -((rC( k )/atm_Po)**atm_kappa) )*half
         ENDIF
         IF (k.EQ.Nr) THEN
           ddPIp=atm_Cp*( ((rC( k )/atm_Po)**atm_kappa)
     &                   -((rF(k+1)/atm_Po)**atm_kappa) )
         ELSE
           ddPIp=atm_Cp*( ((rC( k )/atm_Po)**atm_kappa)
     &                   -((rC(k+1)/atm_Po)**atm_kappa) )*half 
         ENDIF
         DO j=jMin,jMax
          DO i=iMin,iMax
             phiHydC(i,j) = phiHydF(i,j) +ddPIm*alphaRho(i,j)
             phiHydF(i,j) = phiHydC(i,j) +ddPIp*alphaRho(i,j)
          ENDDO
         ENDDO
       ELSEIF (integr_GeoPot.EQ.1) THEN
           ddPIm=atm_Cp*( ((rF( k )/atm_Po)**atm_kappa)
     &                   -((rC( k )/atm_Po)**atm_kappa) )
           ddPIp=atm_Cp*( ((rC( k )/atm_Po)**atm_kappa)
     &                   -((rF(k+1)/atm_Po)**atm_kappa) )
         DO j=jMin,jMax
          DO i=iMin,iMax
           IF (k.EQ.ksurfC(i,j,bi,bj)) THEN
             ddRloc = Ro_surf(i,j,bi,bj)-rC(k)
             phiHydC(i,j) = ddRloc*recip_drF(k)*2.d0
     &          *ddPIm*alphaRho(i,j)
           ELSE
             phiHydC(i,j) = phiHydF(i,j) +ddPIm*alphaRho(i,j)
           ENDIF
             phiHydF(i,j) = phiHydC(i,j) +ddPIp*alphaRho(i,j)
          ENDDO
         ENDDO
       ELSEIF ( integr_GeoPot.EQ.2
     &     .OR. integr_GeoPot.EQ.3 ) THEN
         IF (k.EQ.1) THEN
           ddPIm=atm_Cp*( ((rF( k )/atm_Po)**atm_kappa)
     &                   -((rC( k )/atm_Po)**atm_kappa) )
         ELSE
           ddPIm=atm_Cp*( ((rC(k-1)/atm_Po)**atm_kappa)
     &                   -((rC( k )/atm_Po)**atm_kappa) )*half
         ENDIF
         IF (k.EQ.Nr) THEN
           ddPIp=atm_Cp*( ((rC( k )/atm_Po)**atm_kappa)
     &                   -((rF(k+1)/atm_Po)**atm_kappa) )
         ELSE
           ddPIp=atm_Cp*( ((rC( k )/atm_Po)**atm_kappa)
     &                   -((rC(k+1)/atm_Po)**atm_kappa) )*half 
         ENDIF
         rec_dRm = one/(rF(k)-rC(k))
         rec_dRp = one/(rC(k)-rF(k+1))
         DO j=jMin,jMax
          DO i=iMin,iMax
           IF (k.EQ.ksurfC(i,j,bi,bj)) THEN
             ddRloc = Ro_surf(i,j,bi,bj)-rC(k)
             phiHydC(i,j) =( MAX(zero,ddRloc)*rec_dRm*ddPIm
     &                      +MIN(zero,ddRloc)*rec_dRp*ddPIp )
     &                    *alphaRho(i,j)
           ELSE
             phiHydC(i,j) = phiHydF(i,j) +ddPIm*alphaRho(i,j)
           ENDIF
             phiHydF(i,j) = phiHydC(i,j) +ddPIp*alphaRho(i,j)
          ENDDO
         ENDDO
       ELSE
         STOP 'CALC_PHI_HYD: Bad integr_GeoPot option !'
       ENDIF
      ELSE
        STOP 'CALC_PHI_HYD: Bad value of buoyancyRelation !'
      ENDIF
      IF (useDiagPhiRlow) THEN
        CALL DIAGS_PHI_RLOW(
     I                      k, bi, bj, iMin,iMax, jMin,jMax,
     I                      phiHydF, phiHydC, alphaRho, tFld, sFld,
     I                      myTime, myIter, myThid)  
      ENDIF
        CALL DIAGS_PHI_HYD(
     I                      k, bi, bj, iMin,iMax, jMin,jMax,
     I                      phiHydC,
     I                      myTime, myIter, myThid)
      IF (momPressureForcing) THEN 
        iMnLoc = MAX(1-Olx+1,iMin)
        jMnLoc = MAX(1-Oly+1,jMin)
        CALL CALC_GRAD_PHI_HYD(
     I                         k, bi, bj, iMnLoc,iMax, jMnLoc,jMax,
     I                         phiHydC, alphaRho, tFld, sFld,
     O                         dPhiHydX, dPhiHydY,
     I                         myTime, myIter, myThid)  
      ENDIF
      RETURN
      END
      SUBROUTINE CALC_VISCOSITY( 
     I        bi,bj,iMin,iMax,jMin,jMax,K,
     O        KappaRU,KappaRV,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax,K
      Real*8 KappaRU(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 KappaRV(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      INTEGER myThid
      INTEGER i,j
      DO j = 1-Oly, sNy+Oly
       DO i = 1-Olx, sNx+Olx
        KappaRU(i,j,k) = viscAr
       ENDDO
      ENDDO
      DO j = 1-Oly, sNy+Oly
       DO i = 1-Olx, sNx+Olx
        KappaRV(i,j,k) = viscAr
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CONVECT( bi, bj, iMin, iMax, jMin, jMax, K,
     &       rhoKm1, rhoKp1, ConvectCount,
     &       myTime,myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
      EXTERNAL DIFFERENT_MULTIPLE
      LOGICAL  DIFFERENT_MULTIPLE
      INTEGER bi,bj,iMin,iMax,jMin,jMax,K
      Real*8 rhoKm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rhoKp1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 ConvectCount(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER i,j
      Real*8 tMix(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 sMix(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dSum(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      IF ( DIFFERENT_MULTIPLE(cAdjFreq,myTime,deltaTClock)
     &   ) THEN
       DO j=jMin,jmax
        DO i=iMin,imax
         tMix(i,j) = theta(i,j,k-1,bi,bj)
     &               *hFacC(i,j,k-1,bi,bj)*drF(k-1)
     &              +theta(i,j,k,bi,bj)
     &               *hFacC(i,j,k,bi,bj)*drF(k)
         sMix(i,j) = salt (i,j,k-1,bi,bj)
     &               *hFacC(i,j,k-1,bi,bj)*drF(k-1)
     &              +salt (i,j,k,bi,bj)
     &               *hFacC(i,j,k,bi,bj)*drF(k)
         dSum(i,j) = hFacC(i,j,k-1,bi,bj)*drF(k-1)
     &              +hFacC(i,j,k,bi,bj)*drF(k)
        ENDDO
       ENDDO
       DO j=jMin,jmax
        DO i=iMin,imax
         IF ( hFacC(i,j,k,bi,bj) .GT. 0. .AND.
     &        (rhokm1(i,j)-rhokp1(i,j))*rkSign*gravitySign .GT. 0. 
     &        ) THEN
          theta(i,j,k-1,bi,bj) = tMix(i,j)/dSum(i,j)
          theta(i,j,k  ,bi,bj) = tMix(i,j)/dSum(i,j)
          salt(i,j,k-1,bi,bj)  = sMix(i,j)/dSum(i,j)
          salt(i,j,k  ,bi,bj)  = sMix(i,j)/dSum(i,j)
          ConvectCount(i,j,k) = ConvectCount(i,j,k) + 1.
         ENDIF
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE CONVECTIVE_ADJUSTMENT(
     I       bi, bj, iMin, iMax, jMin, jMax,
     I       myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE tamc_mod
       USE tamc_keys_mod
      EXTERNAL DIFFERENT_MULTIPLE
      LOGICAL  DIFFERENT_MULTIPLE
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER i, j, K, kTop, kBottom, kDir, deltaK
      Real*8 rhoKm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rhoK  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 ConvectCount(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 weightA(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 weightB(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      IF ( DIFFERENT_MULTIPLE(cAdjFreq,myTime,deltaTClock)
     &   ) THEN
        kTop    = 0
        kBottom = 0
        kDir    = 0
        deltaK  = 0
        DO K=1,Nr
         DO j=1-OLy,sNy+OLy
          DO i=1-OLx,sNx+OLx
           ConvectCount(i,j,k) = 0.
          ENDDO
         ENDDO
        ENDDO
          act1 = bi - myBxLo(myThid)
          max1 = myBxHi(myThid) - myBxLo(myThid) + 1
          act2 = bj - myByLo(myThid)
          max2 = myByHi(myThid) - myByLo(myThid) + 1
          act3 = myThid - 1
          max3 = nTx*nTy
          act4 = ikey_dynamics - 1
          ikey = (act1 + 1) + act2*max1
     &                      + act3*max1*max2
     &                      + act4*max1*max2*max3
         IF ( rkSign*gravitySign .GT. 0. ) THEN
          kTop    =  2
          kBottom = Nr
          kDir    =  1
          deltaK  = -1
         ELSE
          kTop    = Nr
          kBottom =  2
          kDir    = -1
          deltaK  =  0
         ENDIF
          DO K=kTop,kBottom,kDir
            kkey = (ikey-1)*Nr + k
            CALL FIND_RHO(
     I           bi,bj,iMin,iMax,jMin,jMax,K-1,K+deltaK,
     I           theta,salt,
     O           rhoKm1,
     I           myThid )
            CALL FIND_RHO(
     I           bi,bj,iMin,iMax,jMin,jMax,K,K+deltaK,
     I           theta,salt,
     O           rhoK,
     I           myThid )
            CALL CONVECTIVE_WEIGHTS(
     I           bi,bj,K,rhoKm1,rhoK,
     O           weightA,weightB,ConvectCount,
     I           myThid)
            CALL CONVECTIVELY_MIXTRACER(
     I                              bi,bj,k,weightA,weightB,
     U                              theta,
     I                              myThid)
            CALL CONVECTIVELY_MIXTRACER(
     I                              bi,bj,k,weightA,weightB,
     U                              salt,
     I                              myThid)
          ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE CONVECTIVE_ADJUSTMENT_INI(
     I       bi, bj, iMin, iMax, jMin, jMax,
     I       myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE tamc_mod
       USE tamc_keys_mod
      EXTERNAL DIFFERENT_MULTIPLE
      LOGICAL  DIFFERENT_MULTIPLE
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER i, j, K, kTop, kBottom, kDir, deltaK
      Real*8 rhoKm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rhoK  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 ConvectCount(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 weightA(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 weightB(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      IF ( DIFFERENT_MULTIPLE(cAdjFreq,myTime,deltaTClock)
     &   ) THEN
        kTop    = 0
        kBottom = 0
        kDir    = 0
        deltaK  = 0
        DO K=1,Nr
         DO j=1-OLy,sNy+OLy
          DO i=1-OLx,sNx+OLx
           ConvectCount(i,j,k) = 0.
          ENDDO
         ENDDO
        ENDDO
          act1 = bi - myBxLo(myThid)
          max1 = myBxHi(myThid) - myBxLo(myThid) + 1
          act2 = bj - myByLo(myThid)
          max2 = myByHi(myThid) - myByLo(myThid) + 1
          act3 = myThid - 1
          max3 = nTx*nTy
          act4 = 0
          ikey = (act1 + 1) + act2*max1
     &                      + act3*max1*max2
     &                      + act4*max1*max2*max3
         IF ( rkSign*gravitySign .GT. 0. ) THEN
          kTop    =  2
          kBottom = Nr
          kDir    =  1
          deltaK  = -1
         ELSE
          kTop    = Nr
          kBottom =  2
          kDir    = -1
          deltaK  =  0
         ENDIF	
          DO K=kTop,kBottom,kDir
            kkey = (ikey-1)*Nr + k
            CALL FIND_RHO(
     I           bi,bj,iMin,iMax,jMin,jMax,K-1,K+deltaK,
     I           theta,salt,
     O           rhoKm1,
     I           myThid )
            CALL FIND_RHO(
     I           bi,bj,iMin,iMax,jMin,jMax,K,K+deltaK,
     I           theta,salt,
     O           rhoK,
     I           myThid )
            CALL CONVECTIVE_WEIGHTS(
     I           bi,bj,K,rhoKm1,rhoK,
     O           weightA,weightB,ConvectCount,
     I           myThid)
            CALL CONVECTIVELY_MIXTRACER(
     I                              bi,bj,k,weightA,weightB,
     U                              theta,
     I                              myThid)
            CALL CONVECTIVELY_MIXTRACER(
     I                              bi,bj,k,weightA,weightB,
     U                              salt,
     I                              myThid)
          ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE CONVECTIVE_WEIGHTS(
     I                              bi,bj,k,rhoKm1,rhoK,
     O                              weightA,weightB,ConvectCount,
     I                              myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,k
      Real*8 rhoKm1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rhoK(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 weightA(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 weightB(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 ConvectCount(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      INTEGER myThid
      INTEGER i,j
      Real*8 dS,d1,d2
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
         IF ( hFacC(i,j,k-1,bi,bj)
     &       *hFacC(i,j,k,bi,bj) .GT. 0.
     &  .AND. (rhokm1(i,j)-rhok(i,j))*rkSign*gravitySign .GT. 0.
     &      ) THEN
          d1 = hFacC(i,j,k-1,bi,bj)*drF(k-1)
          d2 = hFacC(i,j, k ,bi,bj)*drF( k )
          dS = d1+d2
          weightA(i,j) = d2/dS
          weightB(i,j) = d1/dS
          ConvectCount(i,j,k) = ConvectCount(i,j,k) + 1.
         ELSE
          weightA(i,j) = 0.
          weightB(i,j) = 0.
         ENDIF
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CONVECTIVELY_MIXTRACER(
     I                              bi,bj,k,weightA,weightB,
     U                              Tracer,
     I                              myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
      INTEGER bi,bj,k
      Real*8 weightA(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 weightB(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 Tracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      INTEGER i,j
      Real*8 delTrac
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        delTrac=Tracer(i,j,k,bi,bj)-Tracer(i,j,k-1,bi,bj)
        Tracer(i,j,k-1,bi,bj)=Tracer(i,j,k-1,bi,bj)
     &                       +weightA(i,j)*delTrac
        Tracer(i,j,k,bi,bj)=Tracer(i,j,k,bi,bj)
     &                       -weightB(i,j)*delTrac
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CORRECTION_STEP( bi, bj, iMin, iMax, jMin, jMax,
     I                       K, phiSurfX, phiSurfY,
     I                       myCurrentTime, myThid )
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      Real*8  phiSurfX(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8  phiSurfY(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER K
      INTEGER myThid
      Real*8 myCurrentTime
      INTEGER i,j
      Real*8 hxFac,hyFac
      Real*8 hx3dFac,hy3dFac
      hxFac = pfFacMom
      hyFac = pfFacMom
      IF ( nonHydrostatic ) THEN
        hx3dFac = pfFacMom
        hy3dFac = pfFacMom
      ELSE
        hx3dFac = 0.
        hy3dFac = 0.
      ENDIF
      DO j=jMin,jMax
       DO i=iMin,iMax
        uVel(i,j,k,bi,bj)=( gU(i,j,k,bi,bj)
     &       -deltaTmom*hxFac*implicSurfPress*phiSurfX(i,j)
     &                    )*maskW(i,j,k,bi,bj)
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
        vVel(i,j,k,bi,bj)=( gV(i,j,k,bi,bj)
     &       -deltaTmom*hyFac*implicSurfPress*phiSurfY(i,j)
     &                    )*maskS(i,j,k,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE CYCLE_TRACER(
     I                   bi, bj, k,
     U                   tracer, gTracer,
     I                   myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,k
      Real*8 tracer (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 gTracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 myTime
      INTEGER myIter, myThid
      INTEGER i,j
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        tracer(i,j,k,bi,bj)=gTracer(i,j,k,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE DIAGS_PHI_HYD( 
     I                       k, bi, bj, iMin,iMax, jMin,jMax,
     I                       phiHydC,
     I                       myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
       USE DYNVARS_mod
      INTEGER k, bi,bj, iMin,iMax, jMin,jMax
      Real*8 phiHydC(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 myTime
      INTEGER myIter, myThid
      INTEGER i,j
        DO j=jMin,jMax
         DO i=iMin,iMax
           totPhiHyd(i,j,k,bi,bj) = phiHydC(i,j)
     &            + Bo_surf(i,j,bi,bj)*etaN(i,j,bi,bj)
     &            + phi0surf(i,j,bi,bj) 
         ENDDO
        ENDDO
      RETURN
      END
      SUBROUTINE DIAGS_PHI_RLOW( 
     I                       k, bi, bj, iMin,iMax, jMin,jMax,
     I                       phiHydF, phiHydC, alphRho, tFld, sFld,
     I                       myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
       USE DYNVARS_mod
      INTEGER k, bi,bj, iMin,iMax, jMin,jMax
      Real*8 phiHydF(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 phiHydC(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 alphRho(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 tFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 myTime
      INTEGER myIter, myThid
      INTEGER i,j
      Real*8 zero, one, half
      Real*8 ddRloc, ratioRm, ratioRp
      PARAMETER ( zero= 0.d0 , one= 1.d0 , half= .5d0 )
      IF ( buoyancyRelation .EQ. 'OCEANIC' ) THEN
       IF (integr_GeoPot.EQ.1) THEN
         DO j=jMin,jMax
          DO i=iMin,iMax
           IF ( k .EQ. kLowC(i,j,bi,bj) ) THEN
             ddRloc = rC(k)-R_low(i,j,bi,bj)
             phiHydLow(i,j,bi,bj) = phiHydC(i,j)
     &            + ddRloc*gravity*alphRho(i,j)*recip_rhoConst
           ENDIF
          ENDDO
         ENDDO
       ELSE
         ratioRm = one
         ratioRp = one
         IF (k.GT.1 ) ratioRm = half*drC(k)/(rF(k)-rC(k))
         IF (k.LT.Nr) ratioRp = half*drC(k+1)/(rC(k)-rF(k+1))
         DO j=jMin,jMax
          DO i=iMin,iMax
           IF ( k .EQ. kLowC(i,j,bi,bj) ) THEN
             ddRloc = rC(k)-R_low(i,j,bi,bj)
             phiHydLow(i,j,bi,bj) = phiHydC(i,j)
     &                  +( MIN(zero,ddRloc)*ratioRm
     &                    +MAX(zero,ddRloc)*ratioRp
     &                   )*gravity*alphRho(i,j)*recip_rhoConst
           ENDIF
          ENDDO
         ENDDO
       ENDIF
      ENDIF
      IF (k.EQ.Nr) THEN
       IF ( buoyancyRelation .EQ. 'OCEANICP' .OR.
     &      buoyancyRelation .EQ. 'ATMOSPHERIC' ) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
           phiHydLow(i,j,bi,bj) = phiHydF(i,j)
         ENDDO
        ENDDO
       ENDIF
        DO j=jMin,jMax
         DO i=iMin,iMax
           phiHydLow(i,j,bi,bj) = phiHydLow(i,j,bi,bj)
     &            + Bo_surf(i,j,bi,bj)*etaN(i,j,bi,bj)
     &            + phi0surf(i,j,bi,bj) 
         ENDDO
        ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE DO_ATMOSPHERIC_PHYS(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER bi, bj
      IF ( debugLevel .GE. debLevB ) 
     &   CALL DEBUG_ENTER('DO_ATMOSPHERIC_PHYS',myThid)
      IF ( debugLevel .GE. debLevB ) 
     &  CALL DEBUG_LEAVE('DO_ATMOSPHERIC_PHYS',myThid)
      RETURN
      END
      SUBROUTINE DO_FIELDS_BLOCKING_EXCHANGES(myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE CD_CODE_VARS_mod
      INTEGER myThid
      IF ( .NOT.staggerTimeStep .OR. .NOT.useMultiDimAdvec ) THEN
       CALL EXCH_UV_XYZ_RL(uVel,vVel,.TRUE.,myThid)
       CALL EXCH_XYZ_RL (  wVel ,  myThid  )
      ENDIF
      CALL EXCH_XYZ_RL (  theta,  myThid  )
      CALL EXCH_XYZ_RL (  salt ,  myThid  )
      CALL EXCH_XYZ_RL (  uVelD ,  myThid  )
      CALL EXCH_XYZ_RL (  vVelD ,  myThid  )
      IF ( useDynP_inEos_Zc )
     & CALL EXCH_XYZ_RL (  totPhiHyd ,  myThid  )
      RETURN
      END
      SUBROUTINE DO_OCEANIC_PHYS(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE tamc_mod
       USE tamc_keys_mod
       USE FFIELDS_mod
       USE EOS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      Real*8 rhokm1  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rhok    (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 sigmaX  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 sigmaY  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      Real*8 sigmaR  (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr)
      INTEGER iMin, iMax
      INTEGER jMin, jMax
      INTEGER bi, bj
      INTEGER i, j, k
      INTEGER doDiagsRho
      itdkey = 1
      IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_ENTER('DO_OCEANIC_PHYS',myThid)
      doDiagsRho = 0
      IF ( allowFreezing
     &                   .AND. .NOT. useSEAICE
     &                   .AND. .NOT. useThSIce ) THEN
        CALL FREEZE_SURFACE(  myTime, myIter, myThid )
      ENDIF
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
          act1 = bi - myBxLo(myThid)
          max1 = myBxHi(myThid) - myBxLo(myThid) + 1
          act2 = bj - myByLo(myThid)
          max2 = myByHi(myThid) - myByLo(myThid) + 1
          act3 = myThid - 1
          max3 = nTx*nTy
          act4 = ikey_dynamics - 1
          itdkey = (act1 + 1) + act2*max1
     &                      + act3*max1*max2
     &                      + act4*max1*max2*max3
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          rhok   (i,j)   = 0.d0
          rhoKM1 (i,j)   = 0.d0
         ENDDO
        ENDDO
        DO k=1,Nr
         DO j=1-OLy,sNy+OLy
          DO i=1-OLx,sNx+OLx
           sigmaX(i,j,k) = 0.d0
           sigmaY(i,j,k) = 0.d0
           sigmaR(i,j,k) = 0.d0
           IVDConvCount(i,j,k,bi,bj) = 0.
          ENDDO
         ENDDO
        ENDDO
        iMin = 1-OLx
        iMax = sNx+OLx
        jMin = 1-OLy
        jMax = sNy+OLy
        IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_MSG('ENTERING UPWARD K LOOP',myThid)
        DO k=Nr,1,-1
         kkey = (itdkey-1)*Nr + k
          IF ( useGMRedi .OR. (k.GT.1 .AND. ivdc_kappa.NE.0.)
     &                   .OR. doDiagsRho.GE.1 ) THEN
            IF ( debugLevel .GE. debLevB ) 
     &       CALL DEBUG_CALL('FIND_RHO',myThid)
            CALL FIND_RHO(
     I        bi, bj, iMin, iMax, jMin, jMax, k, k,
     I        theta, salt,
     O        rhoK,
     I        myThid )
            IF (k.GT.1) THEN
             CALL FIND_RHO(
     I        bi, bj, iMin, iMax, jMin, jMax, k-1, k,
     I        theta, salt,
     O        rhoKm1,
     I        myThid )
            ENDIF
            IF ( debugLevel .GE. debLevB ) 
     &       CALL DEBUG_CALL('GRAD_SIGMA',myThid)
            CALL GRAD_SIGMA(
     I             bi, bj, iMin, iMax, jMin, jMax, k,
     I             rhoK, rhoKm1, rhoK,
     O             sigmaX, sigmaY, sigmaR,
     I             myThid )
          ENDIF
          IF (k.GT.1 .AND. ivdc_kappa.NE.0.) THEN
            IF ( debugLevel .GE. debLevB ) 
     &       CALL DEBUG_CALL('CALC_IVDC',myThid)
            CALL CALC_IVDC(
     I        bi, bj, iMin, iMax, jMin, jMax, k,
     I        rhoKm1, rhoK,
     I        myTime, myIter, myThid)
          ENDIF
        ENDDO
        IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_CALL('EXTERNAL_FORCING_SURF',myThid)
         CALL EXTERNAL_FORCING_SURF(
     I             bi, bj, iMin, iMax, jMin, jMax,
     I             myTime, myIter, myThid )
       ENDDO
      ENDDO
         IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_LEAVE('DO_OCEANIC_PHYS',myThid)
      RETURN
      END
      SUBROUTINE DO_STAGGER_FIELDS_EXCHANGES(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid   
      IF ( staggerTimeStep .AND. useMultiDimAdvec) THEN
        CALL EXCH_UV_XYZ_RL(uVel,vVel,.TRUE.,myThid)
        CALL EXCH_XYZ_RL (  wVel ,  myThid  )
      ENDIF
      RETURN
      END
      SUBROUTINE DYNAMICS(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE CD_CODE_VARS_mod
       USE GRID_mod
       USE tamc_mod
       USE tamc_keys_mod
       USE FFIELDS_mod
       USE EOS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      Real*8 fVerU   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 fVerV   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 phiHydF (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 phiHydC (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 dPhiHydX(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 dPhiHydY(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 phiSurfX(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 phiSurfY(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 guDissip(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 gvDissip(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 KappaRU (1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 KappaRV (1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      INTEGER iMin, iMax
      INTEGER jMin, jMax
      INTEGER bi, bj
      INTEGER i, j
      INTEGER k, km1, kp1, kup, kDown
      IF ( debugLevel .GE. debLevB )
     &   CALL DEBUG_ENTER( 'DYNAMICS', myThid )
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
          act1 = bi - myBxLo(myThid)
          max1 = myBxHi(myThid) - myBxLo(myThid) + 1
          act2 = bj - myByLo(myThid)
          max2 = myByHi(myThid) - myByLo(myThid) + 1
          act3 = myThid - 1
          max3 = nTx*nTy
          act4 = ikey_dynamics - 1
          idynkey = (act1 + 1) + act2*max1
     &                      + act3*max1*max2
     &                      + act4*max1*max2*max3
        DO k=1,Nr
         DO j=1-OLy,sNy+OLy
          DO i=1-OLx,sNx+OLx
           KappaRU(i,j,k) = 0.d0
           KappaRV(i,j,k) = 0.d0
           gU(i,j,k,bi,bj) = 0.d0
           gV(i,j,k,bi,bj) = 0.d0
          ENDDO
         ENDDO
        ENDDO
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          fVerU  (i,j,1) = 0.d0
          fVerU  (i,j,2) = 0.d0
          fVerV  (i,j,1) = 0.d0
          fVerV  (i,j,2) = 0.d0
          phiHydF (i,j)  = 0.d0 
          phiHydC (i,j)  = 0.d0 
          dPhiHydX(i,j)  = 0.d0
          dPhiHydY(i,j)  = 0.d0 
          phiSurfX(i,j)  = 0.d0
          phiSurfY(i,j)  = 0.d0
          guDissip(i,j)  = 0.d0
          gvDissip(i,j)  = 0.d0
         ENDDO
        ENDDO
        iMin = 0
        iMax = sNx+1
        jMin = 0
        jMax = sNy+1
        IF (implicSurfPress.NE.1.) THEN
          CALL CALC_GRAD_PHI_SURF(
     I         bi,bj,iMin,iMax,jMin,jMax,
     I         etaN,
     O         phiSurfX,phiSurfY,
     I         myThid )                         
        ENDIF
        DO k=1,Nr
         CALL CALC_VISCOSITY(
     I        bi,bj,iMin,iMax,jMin,jMax,k,
     O        KappaRU,KappaRV,
     I        myThid)
       ENDDO
        DO k=1,Nr
          km1  = MAX(1,k-1)
          kp1  = MIN(k+1,Nr)
          kup  = 1+MOD(k+1,2)
          kDown= 1+MOD(k,2)
         kkey = (idynkey-1)*Nr + k
         CALL CALC_PHI_HYD(
     I        bi,bj,iMin,iMax,jMin,jMax,k,
     I        theta, salt,
     U        phiHydF,
     O        phiHydC, dPhiHydX, dPhiHydY,
     I        myTime, myIter, myThid )
         IF ( momStepping ) THEN
           IF (.NOT. vectorInvariantMomentum) CALL MOM_FLUXFORM(
     I         bi,bj,iMin,iMax,jMin,jMax,k,kup,kDown,
     I         KappaRU, KappaRV,
     U         fVerU, fVerV,
     O         guDissip, gvDissip,
     I         myTime, myIter, myThid)
           IF (vectorInvariantMomentum) CALL MOM_VECINV(
     I         bi,bj,iMin,iMax,jMin,jMax,k,kup,kDown,
     I         KappaRU, KappaRV,
     U         fVerU, fVerV,
     O         guDissip, gvDissip,
     I         myTime, myIter, myThid)
           CALL TIMESTEP(
     I         bi,bj,iMin,iMax,jMin,jMax,k,
     I         dPhiHydX,dPhiHydY, phiSurfX, phiSurfY,
     I         guDissip, gvDissip,
     I         myTime, myIter, myThid)
         ENDIF
        ENDDO
        IF     ( implicitViscosity ) THEN
          CALL IMPLDIFF(
     I         bi, bj, iMin, iMax, jMin, jMax,
     I         0, KappaRU,recip_HFacW,
     U         gU,
     I         myThid )
          CALL IMPLDIFF(
     I         bi, bj, iMin, iMax, jMin, jMax,
     I         0, KappaRV,recip_HFacS,
     U         gV,
     I         myThid )
        ENDIF
        IF (implicitViscosity.AND.useCDscheme) THEN
          CALL IMPLDIFF(
     I         bi, bj, iMin, iMax, jMin, jMax,
     I         0, KappaRU,recip_HFacW,
     U         vVelD,
     I         myThid )
          CALL IMPLDIFF(
     I         bi, bj, iMin, iMax, jMin, jMax,
     I         0, KappaRV,recip_HFacS,
     U         uVelD,
     I         myThid )
        ENDIF
       ENDDO
      ENDDO
      If ( debugLevel .GE. debLevB ) THEN
       CALL DEBUG_STATS_RL(1,EtaN,'EtaN (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,uVel,'Uvel (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,vVel,'Vvel (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,wVel,'Wvel (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,theta,'Theta (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,salt,'Salt (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gU,'Gu (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gV,'Gv (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gT,'Gt (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gS,'Gs (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,guNm1,'GuNm1 (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gvNm1,'GvNm1 (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gtNm1,'GtNm1 (DYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gsNm1,'GsNm1 (DYNAMICS)',myThid)
      ENDIF
      IF ( debugLevel .GE. debLevB )
     &   CALL DEBUG_LEAVE( 'DYNAMICS', myThid )
      RETURN
      END
      SUBROUTINE EXTERNAL_FIELDS_LOAD( myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE FFIELDS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      Real*8     myTime
      INTEGER myIter
      INTEGER bi,bj,i,j,intime0,intime1
      Real*8 aWght,bWght,rdt
      Real*8 tmp1Wght, tmp2Wght
      INTEGER nForcingPeriods,Imytm,Ifprd,Ifcyc,Iftm
      IF ( periodicExternalForcing ) THEN
      rdt = 1.d0 / deltaTclock
      nForcingPeriods = NINT(externForcingCycle/externForcingPeriod)
      Imytm = NINT(myTime*rdt)
      Ifprd = NINT(externForcingPeriod*rdt)
      Ifcyc = NINT(externForcingCycle*rdt)
      Iftm  = MOD( Imytm+Ifcyc-Ifprd/2, Ifcyc)
      intime0 = 1 + INT(Iftm/Ifprd)
      intime1 = 1 + MOD(intime0,nForcingPeriods)
      tmp1Wght = FLOAT( Iftm-Ifprd*(intime0 - 1) )
      tmp2Wght = FLOAT( Ifprd )
      aWght =  tmp1Wght / tmp2Wght
      bWght = 1.d0 - aWght
      IF (
     &  Iftm-Ifprd*(intime0-1) .EQ. 0
     &  .OR. myIter .EQ. nIter0
     & ) THEN
       IF ( myThid .EQ. 1 ) THEN
       WRITE(standardMessageUnit,'(A,2I5,I10,1P1E20.12)')
     &  'S/R EXTERNAL_FIELDS_LOAD: Reading new data:',
     &  intime0, intime1, myIter, myTime
      IF ( zonalWindFile .NE. ' '  ) THEN
       CALL MDSREADFIELD ( zonalWindFile, readBinaryPrec,
     &        'RS', 1, taux0, intime0, myThid )
       CALL MDSREADFIELD ( zonalWindFile, readBinaryPrec,
     &        'RS', 1, taux1, intime1, myThid )
      ENDIF
      IF ( meridWindFile .NE. ' '  ) THEN
       CALL MDSREADFIELD ( meridWindFile, readBinaryPrec,
     &        'RS', 1, tauy0, intime0, myThid )
       CALL MDSREADFIELD ( meridWindFile, readBinaryPrec,
     &        'RS', 1, tauy1, intime1, myThid )
      ENDIF
      IF ( surfQFile .NE. ' '  ) THEN
       CALL MDSREADFIELD ( surfQFile, readBinaryPrec,
     &        'RS', 1, Qnet0, intime0, myThid )
       CALL MDSREADFIELD ( surfQFile, readBinaryPrec,
     &        'RS', 1, Qnet1, intime1, myThid )
      ELSEIF ( surfQnetFile .NE. ' '  ) THEN
       CALL MDSREADFIELD ( surfQnetFile, readBinaryPrec,
     &        'RS', 1, Qnet0, intime0, myThid )
       CALL MDSREADFIELD ( surfQnetFile, readBinaryPrec,
     &        'RS', 1, Qnet1, intime1, myThid )
      ENDIF
      IF ( EmPmRfile .NE. ' '  ) THEN
       CALL MDSREADFIELD ( EmPmRfile, readBinaryPrec,
     &        'RS', 1, EmPmR0, intime0, myThid )
       CALL MDSREADFIELD ( EmPmRfile, readBinaryPrec,
     &        'RS', 1, EmPmR1, intime1, myThid )
      ENDIF
      IF ( saltFluxFile .NE. ' '  ) THEN
       CALL MDSREADFIELD ( saltFluxFile, readBinaryPrec,
     &        'RS', 1, saltFlux0, intime0, myThid )
       CALL MDSREADFIELD ( saltFluxFile, readBinaryPrec,
     &        'RS', 1, saltFlux1, intime1, myThid )
      ENDIF
      IF ( thetaClimFile .NE. ' '  ) THEN
       CALL MDSREADFIELD ( thetaClimFile, readBinaryPrec,
     &        'RS', 1, SST0, intime0, myThid )
       CALL MDSREADFIELD ( thetaClimFile, readBinaryPrec,
     &        'RS', 1, SST1, intime1, myThid )
      ENDIF
      IF ( saltClimFile .NE. ' '  ) THEN
       CALL MDSREADFIELD ( saltClimFile, readBinaryPrec,
     &        'RS', 1, SSS0, intime0, myThid )
       CALL MDSREADFIELD ( saltClimFile, readBinaryPrec,
     &        'RS', 1, SSS1, intime1, myThid )
      ENDIF
       ENDIF
       CALL EXCH_XY_RL ( SST0  ,  myThid  )
       CALL EXCH_XY_RL ( SST1  ,  myThid  )
       CALL EXCH_XY_RL ( SSS0  ,  myThid  )
       CALL EXCH_XY_RL ( SSS1  ,  myThid  )
       CALL EXCH_UV_XY_RS(taux0,tauy0,.TRUE.,myThid)
       CALL EXCH_UV_XY_RS(taux1,tauy1,.TRUE.,myThid)
       CALL EXCH_XY_RL ( Qnet0,  myThid  )
       CALL EXCH_XY_RL ( Qnet1,  myThid  )
       CALL EXCH_XY_RL ( EmPmR0,  myThid  )
       CALL EXCH_XY_RL ( EmPmR1,  myThid  )
       CALL EXCH_XY_RL ( saltFlux0,  myThid  )
       CALL EXCH_XY_RL ( saltFlux1,  myThid  )
      ENDIF
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          SST(i,j,bi,bj)   = bWght*SST0(i,j,bi,bj)  
     &                       +aWght*SST1(i,j,bi,bj)
          SSS(i,j,bi,bj)   = bWght*SSS0(i,j,bi,bj)  
     &                       +aWght*SSS1(i,j,bi,bj)
          fu(i,j,bi,bj)    = bWght*taux0(i,j,bi,bj) 
     &                       +aWght*taux1(i,j,bi,bj)
          fv(i,j,bi,bj)    = bWght*tauy0(i,j,bi,bj) 
     &                       +aWght*tauy1(i,j,bi,bj)
          Qnet(i,j,bi,bj)  = bWght*Qnet0(i,j,bi,bj)
     &                       +aWght*Qnet1(i,j,bi,bj)
          EmPmR(i,j,bi,bj) = bWght*EmPmR0(i,j,bi,bj)
     &                       +aWght*EmPmR1(i,j,bi,bj)
          saltFlux(i,j,bi,bj) = bWght*saltFlux0(i,j,bi,bj)
     &                        + aWght*saltFlux1(i,j,bi,bj)
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF ( debugLevel.GE.debLevA  .AND. myTime.LT.62208000.) THEN
        IF (  myThid  .EQ. 1 ) THEN
        WRITE(standardMessageUnit,'(a,1p7e12.4,2i6,2e12.4)')
     &   'time,SST,SSS,fu,fv,Q,E-P,i0,i1,a,b = ',
     &   myTime,
     &   SST(1,sNy,1,1),SSS(1,sNy,1,1),
     &   fu(1,sNy,1,1),fv(1,sNy,1,1),
     &   Qnet(1,sNy,1,1),EmPmR(1,sNy,1,1),
     &   intime0,intime1,aWght,bWght
        WRITE(standardMessageUnit,'(a,1p4e12.4,2E23.15)')
     &   'time,fu0,fu1,fu = ',
     &   myTime,
     &   taux0(1,sNy,1,1),taux1(1,sNy,1,1),fu(1,sNy,1,1),
     &   aWght,bWght
        ENDIF
      ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE LEF_ZERO( arr ,myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
      Real*8  arr (1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER myThid
      INTEGER i,j,bi,bj
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          arr(i,j,bi,bj)=0.
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE EXTERNAL_FORCING_U(
     I           iMin,iMax, jMin,jMax, bi,bj, kLev,
     I           myTime, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
      INTEGER iMin, iMax, jMin, jMax, kLev, bi, bj
      Real*8 myTime
      INTEGER myThid
      INTEGER i, j
      INTEGER kSurface
      IF ( fluidIsAir ) THEN
       kSurface = 0
      ELSEIF ( usingPCoords ) THEN
       kSurface = Nr
      ELSE
       kSurface = 1
      ENDIF
      IF ( kLev .EQ. kSurface ) THEN
       DO j=0,sNy+1
        DO i=1,sNx+1
         gU(i,j,kLev,bi,bj) = gU(i,j,kLev,bi,bj)
     &   +foFacMom*surfaceForcingU(i,j,bi,bj)
     &   *recip_drF(kLev)*recip_hFacW(i,j,kLev,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE EXTERNAL_FORCING_V(
     I           iMin,iMax, jMin,jMax, bi,bj, kLev,
     I           myTime, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
      INTEGER iMin, iMax, jMin, jMax, kLev, bi, bj
      Real*8 myTime
      INTEGER myThid
      INTEGER i, j
      INTEGER kSurface
      IF ( fluidIsAir ) THEN
       kSurface = 0
      ELSEIF ( usingPCoords ) THEN
       kSurface = Nr
      ELSE
       kSurface = 1
      ENDIF
      IF ( kLev .EQ. kSurface ) THEN
       DO j=1,sNy+1
        DO i=0,sNx+1
         gV(i,j,kLev,bi,bj) = gV(i,j,kLev,bi,bj)
     &   +foFacMom*surfaceForcingV(i,j,bi,bj)
     &   *recip_drF(kLev)*recip_hFacS(i,j,kLev,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE EXTERNAL_FORCING_T(
     I           iMin,iMax, jMin,jMax, bi,bj, kLev,
     I           myTime, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
      INTEGER iMin, iMax, jMin, jMax, kLev, bi, bj
      Real*8 myTime
      INTEGER myThid
      INTEGER i, j
      INTEGER kSurface
      IF ( fluidIsAir ) THEN
       kSurface = 0
      ELSEIF ( usingPCoords ) THEN
       kSurface = Nr
      ELSE
       kSurface = 1
      ENDIF
      IF ( kLev .EQ. kSurface ) THEN
       DO j=1,sNy
        DO i=1,sNx
         gT(i,j,kLev,bi,bj)=gT(i,j,kLev,bi,bj)
     &     +surfaceForcingT(i,j,bi,bj)
     &     *recip_drF(kLev)*recip_hFacC(i,j,kLev,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE EXTERNAL_FORCING_S(
     I           iMin,iMax, jMin,jMax, bi,bj, kLev,
     I           myTime, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
      INTEGER iMin, iMax, jMin, jMax, kLev, bi, bj
      Real*8 myTime
      INTEGER myThid
      INTEGER i, j
      INTEGER kSurface
      IF ( fluidIsAir ) THEN
       kSurface = 0
      ELSEIF ( usingPCoords ) THEN
       kSurface = Nr
      ELSE
       kSurface = 1
      ENDIF
      IF ( kLev .EQ. kSurface ) THEN
       DO j=1,sNy
        DO i=1,sNx
         gS(i,j,kLev,bi,bj)=gS(i,j,kLev,bi,bj)
     &     +surfaceForcingS(i,j,bi,bj)
     &     *recip_drF(kLev)*recip_hFacC(i,j,kLev,bi,bj)
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE EXTERNAL_FORCING_SURF( 
     I             bi, bj, iMin, iMax, jMin, jMax,
     I             myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE FFIELDS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE SURFACE_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER bi,bj
      INTEGER iMin, iMax
      INTEGER jMin, jMax
      INTEGER i,j
      INTEGER ks
      IF ( usingPCoords ) THEN
       ks        = Nr 
      ELSE
       ks        = 1
      ENDIF
      IF ( doThetaClimRelax .OR. doSaltClimRelax ) THEN
       DO j = jMin, jMax
        DO i = iMin, iMax
          surfaceForcingT(i,j,bi,bj) = 
     &      -lambdaThetaClimRelax(i,j,bi,bj)
     &         *(theta(i,j,ks,bi,bj)-SST(i,j,bi,bj))
     &         *drF(ks)*hFacC(i,j,ks,bi,bj)
          surfaceForcingS(i,j,bi,bj) =
     &      -lambdaSaltClimRelax(i,j,bi,bj)
     &         *(salt(i,j,ks,bi,bj)-SSS(i,j,bi,bj))
     &         *drF(ks)*hFacC(i,j,ks,bi,bj)
        ENDDO
       ENDDO
      ELSE
       DO j = jMin, jMax
        DO i = iMin, iMax
          surfaceForcingT(i,j,bi,bj) = 0.d0
          surfaceForcingS(i,j,bi,bj) = 0.d0
        ENDDO
       ENDDO
      ENDIF
      DO j = jMin, jMax
         DO i = iMin, iMax
          surfaceForcingU(i,j,bi,bj) = 
     &      fu(i,j,bi,bj)*horiVertRatio*recip_rhoConst
          surfaceForcingV(i,j,bi,bj) = 
     &      fv(i,j,bi,bj)*horiVertRatio*recip_rhoConst
          surfaceForcingT(i,j,bi,bj) = surfaceForcingT(i,j,bi,bj)
     &       - ( Qnet(i,j,bi,bj)
     &         ) *recip_Cp*horiVertRatio*recip_rhoConst
          surfaceForcingS(i,j,bi,bj) = surfaceForcingS(i,j,bi,bj)
     &      -saltFlux(i,j,bi,bj)*horiVertRatio*recip_rhoConst
         ENDDO
      ENDDO
      IF (.TRUE.) THEN
       IF (convertFW2Salt .EQ. -1.) THEN
        DO j = jMin, jMax
         DO i = iMin, iMax
          surfaceForcingS(i,j,bi,bj) = surfaceForcingS(i,j,bi,bj)
     &      + EmPmR(i,j,bi,bj)*salt(i,j,ks,bi,bj)
     &         *convertEmP2rUnit
         ENDDO
        ENDDO
       ELSE 
        DO j = jMin, jMax
         DO i = iMin, iMax
          surfaceForcingS(i,j,bi,bj) = surfaceForcingS(i,j,bi,bj)
     &      + EmPmR(i,j,bi,bj)*convertFW2Salt
     &         *convertEmP2rUnit
         ENDDO
        ENDDO
       ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE FIND_ALPHA (
     I     bi, bj, iMin, iMax, jMin, jMax,  k, kRef, 
     O     alphaloc )
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
       USE GRID_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k
      INTEGER kRef
      Real*8 alphaloc(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER i,j
      Real*8 refTemp,refSalt,tP,sP
      Real*8 t1, t2, t3, s1, s3o2, p1, p2, sp5, p1t1
      Real*8 drhoP0dtheta, drhoP0dthetaFresh, drhoP0dthetaSalt
      Real*8 dKdtheta, dKdthetaFresh, dKdthetaSalt, dKdthetaPres
      Real*8 locPres(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 rhoP0  (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 bulkMod(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 dnum_dtheta, dden_dtheta
      Real*8 rhoDen (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 rhoLoc (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      IF (equationOfState.EQ.'LINEAR') THEN
         DO j=jMin,jMax
            DO i=iMin,iMax
               alphaloc(i,j) = -rhonil * tAlpha
            ENDDO
         ENDDO
      ELSEIF (equationOfState.EQ.'POLY3') THEN
         refTemp=eosRefT(kRef)
         refSalt=eosRefS(kRef)
         DO j=jMin,jMax
            DO i=iMin,iMax
               tP=theta(i,j,k,bi,bj)-refTemp
               sP=salt(i,j,k,bi,bj)-refSalt
               alphaloc(i,j) =
     &     ( eosC(6,kRef)
     &         *tP*3.
     &        +(eosC(7,kRef)*sP + eosC(3,kRef))*2.
     &       )*tP
     &      +(eosC(8,kRef)*sP + eosC(4,kRef) )*sP + eosC(1,kRef)
     &     
            ENDDO
         ENDDO
      ELSEIF ( equationOfState(1:5).EQ.'JMD95'
     &        .OR. equationOfState.EQ.'UNESCO' ) THEN
         CALL PRESSURE_FOR_EOS(
     I        bi, bj, iMin, iMax, jMin, jMax,  kRef,
     O        locPres,
     I        myThid ) 
         CALL FIND_RHOP0(
     I        bi, bj, iMin, iMax, jMin, jMax, k,
     I        theta, salt,
     O        rhoP0,
     I        myThid )
         CALL FIND_BULKMOD(
     I        bi, bj, iMin, iMax, jMin, jMax,  k,
     I        locPres, theta, salt,
     O        bulkMod,
     I        myThid )
         DO j=jMin,jMax
            DO i=iMin,iMax
               t1 = theta(i,j,k,bi,bj) 
               t2 = t1*t1
               t3 = t2*t1
               s1  = salt(i,j,k,bi,bj)
              IF ( s1 .GT. 0.d0 ) THEN
               s3o2 = SQRT(s1*s1*s1)
              ELSE
               s1   = 0.d0
               s3o2 = 0.d0
              ENDIF
               p1  = locPres(i,j)*SItoBar
               p2 = p1*p1
               drhoP0dthetaFresh = 
     &                eosJMDCFw(2)
     &           + 2.*eosJMDCFw(3)*t1
     &           + 3.*eosJMDCFw(4)*t2
     &           + 4.*eosJMDCFw(5)*t3
     &           + 5.*eosJMDCFw(6)*t3*t1
               drhoP0dthetaSalt = 
     &        s1*(
     &                eosJMDCSw(2)
     &           + 2.*eosJMDCSw(3)*t1
     &           + 3.*eosJMDCSw(4)*t2
     &           + 4.*eosJMDCSw(5)*t3
     &           )
     &       + s3o2*(
     &           +    eosJMDCSw(7)
     &           + 2.*eosJMDCSw(8)*t1
     &           )
               dKdthetaFresh = 
     &                eosJMDCKFw(2)
     &           + 2.*eosJMDCKFw(3)*t1
     &           + 3.*eosJMDCKFw(4)*t2
     &           + 4.*eosJMDCKFw(5)*t3
               dKdthetaSalt =
     &        s1*(    eosJMDCKSw(2)
     &           + 2.*eosJMDCKSw(3)*t1
     &           + 3.*eosJMDCKSw(4)*t2
     &           )
     &    + s3o2*(    eosJMDCKSw(6)
     &           + 2.*eosJMDCKSw(7)*t1
     &           )
               dKdthetaPres =
     &        p1*(    eosJMDCKP(2)
     &           + 2.*eosJMDCKP(3)*t1
     &           + 3.*eosJMDCKP(4)*t2
     &           )
     &   + p1*s1*(    eosJMDCKP(6)
     &           + 2.*eosJMDCKP(7)*t1
     &           )
     &      + p2*(    eosJMDCKP(10)
     &           + 2.*eosJMDCKP(11)*t1
     &           )
     &   + p2*s1*(    eosJMDCKP(13)
     &           + 2.*eosJMDCKP(14)*t1
     &           )
               drhoP0dtheta  = drhoP0dthetaFresh 
     &                       + drhoP0dthetaSalt
               dKdtheta      = dKdthetaFresh 
     &                       + dKdthetaSalt 
     &                       + dKdthetaPres
               alphaloc(i,j) = 
     &              ( bulkmod(i,j)**2*drhoP0dtheta
     &              - bulkmod(i,j)*p1*drhoP0dtheta
     &              - rhoP0(i,j)*p1*dKdtheta )
     &              /( bulkmod(i,j) - p1 )**2
            ENDDO
         ENDDO
      ELSEIF ( equationOfState.EQ.'MDJWF' ) THEN
         CALL PRESSURE_FOR_EOS(
     I        bi, bj, iMin, iMax, jMin, jMax,  kRef,
     O        locPres,
     I        myThid ) 
         CALL FIND_RHONUM( bi, bj, iMin, iMax, jMin, jMax, k,
     &      locPres, theta, salt, rhoLoc, myThid )
         CALL FIND_RHODEN( bi, bj, iMin, iMax, jMin, jMax, k,
     &        locPres, theta, salt, rhoDen, myThid )
         DO j=jMin,jMax
            DO i=iMin,iMax
               t1  = theta(i,j,k,bi,bj)
               t2  = t1*t1
               s1  = salt(i,j,k,bi,bj)
              IF ( s1 .GT. 0.d0 ) THEN
               sp5 = SQRT(s1) 
              ELSE
               s1  = 0.d0
               sp5 = 0.d0
              ENDIF
               p1   = locPres(i,j)*SItodBar
               p1t1 = p1*t1
               dnum_dtheta = eosMDJWFnum(1)
     &              + t1*(2.*eosMDJWFnum(2) + 3.*eosMDJWFnum(3)*t1) 
     &              + eosMDJWFnum(5)*s1                                 
     &              + p1t1*(2.*eosMDJWFnum(8) + 2.*eosMDJWFnum(11)*p1)
               dden_dtheta = eosMDJWFden(1) 
     &              + t1*(2.*eosMDJWFden(2) 
     &              +     t1*(3.*eosMDJWFden(3) 
     &              +         4.*eosMDJWFden(4)*t1 ) )
     &              + s1*(eosMDJWFden(6) 
     &              +     t1*(3.*eosMDJWFden(7)*t1 
     &              +         2.*eosMDJWFden(9)*sp5 ) )
     &              + p1*p1*(3.*eosMDJWFden(11)*t2 + eosMDJWFden(12)*p1)
               alphaLoc(i,j)    = rhoDen(i,j)*(dnum_dtheta 
     &              - (rhoLoc(i,j)*rhoDen(i,j))*dden_dtheta)
         ENDDO
      ENDDO
      ELSE
         WRITE(*,*) 'FIND_ALPHA: equationOfState = ',equationOfState
         STOP 'FIND_ALPHA: "equationOfState" has illegal value'
      ENDIF
      RETURN 
      END
      SUBROUTINE FIND_BETA (
     I     bi, bj, iMin, iMax, jMin, jMax,  k, kRef,
     O     betaloc )
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
       USE GRID_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k
      INTEGER kRef
      Real*8 betaloc(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER i,j
      Real*8 refTemp,refSalt,tP,sP
      Real*8 t1, t2, t3, s1, s3o2, p1, sp5, p1t1
      Real*8 drhoP0dS
      Real*8 dKdS, dKdSSalt, dKdSPres
      Real*8 locPres(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 rhoP0  (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 bulkMod(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 dnum_dsalt, dden_dsalt
      Real*8 rhoDen (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 rhoLoc (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      IF (equationOfState.EQ.'LINEAR') THEN
         DO j=jMin,jMax
            DO i=iMin,iMax
               betaloc(i,j) = rhonil * sBeta
            ENDDO
         ENDDO
      ELSEIF (equationOfState.EQ.'POLY3') THEN
         refTemp=eosRefT(kRef)
         refSalt=eosRefS(kRef)
         DO j=jMin,jMax
            DO i=iMin,iMax
               tP=theta(i,j,k,bi,bj)-refTemp
               sP=salt(i,j,k,bi,bj)-refSalt
               betaloc(i,j) =
     &    ( eosC(9,kRef)*sP*3. + eosC(5,kRef)*2. )*sP + eosC(2,kRef)
     &   + ( eosC(7,kRef)*tP
     &      +eosC(8,kRef)*sP*2. + eosC(4,kRef)
     &     )*tP
            ENDDO
         ENDDO
      ELSEIF ( equationOfState(1:5).EQ.'JMD95'
     &        .OR. equationOfState.EQ.'UNESCO' ) THEN
         CALL PRESSURE_FOR_EOS(
     I        bi, bj, iMin, iMax, jMin, jMax,  kRef,
     O        locPres,
     I        myThid ) 
         CALL FIND_RHOP0(
     I        bi, bj, iMin, iMax, jMin, jMax, k,
     I        theta, salt,
     O        rhoP0,
     I        myThid )
         CALL FIND_BULKMOD(
     I        bi, bj, iMin, iMax, jMin, jMax,  k,
     I        locPres, theta, salt,
     O        bulkMod,
     I        myThid )
         DO j=jMin,jMax
            DO i=iMin,iMax
               t1 = theta(i,j,k,bi,bj) 
               t2 = t1*t1
               t3 = t2*t1
               s1  = salt(i,j,k,bi,bj)
              IF ( s1 .GT. 0.d0 ) THEN
               s3o2 = 1.5*SQRT(s1)
              ELSE
               s1   = 0.d0
               s3o2 = 0.d0
              ENDIF
               p1  = locPres(i,j)*SItoBar
               drhoP0dS = 0.d0
               drhoP0dS = drhoP0dS
     &              + eosJMDCSw(1)
     &              + eosJMDCSw(2)*t1
     &              + eosJMDCSw(3)*t2
     &              + eosJMDCSw(4)*t3
     &              + eosJMDCSw(5)*t3*t1
     &       + s3o2*(
     &                eosJMDCSw(6)
     &              + eosJMDCSw(7)*t1
     &              + eosJMDCSw(8)*t2
     &              )
     &              + 2*eosJMDCSw(9)*s1
               dKdS = 0.d0
               dKdSSalt =
     &                eosJMDCKSw(1)
     &              + eosJMDCKSw(2)*t1
     &              + eosJMDCKSw(3)*t2
     &              + eosJMDCKSw(4)*t3
     &       + s3o2*( eosJMDCKSw(5)
     &              + eosJMDCKSw(6)*t1
     &              + eosJMDCKSw(7)*t2
     &              )
               dKdSPres = 
     &           p1*( eosJMDCKP(5)
     &              + eosJMDCKP(6)*t1
     &              + eosJMDCKP(7)*t2
     &              )
     &        + s3o2*p1*eosJMDCKP(8)
     &      + p1*p1*( eosJMDCKP(12)
     &              + eosJMDCKP(13)*t1
     &              + eosJMDCKP(14)*t2
     &              )
               dKdS = dKdSSalt + dKdSPres
               betaloc(i,j) = 
     &              ( bulkmod(i,j)**2*drhoP0dS
     &              - bulkmod(i,j)*p1*drhoP0dS
     &              - rhoP0(i,j)*p1*dKdS )
     &              /( bulkmod(i,j) - p1 )**2
            ENDDO
         ENDDO
      ELSEIF ( equationOfState.EQ.'MDJWF' ) THEN
         CALL PRESSURE_FOR_EOS(
     I        bi, bj, iMin, iMax, jMin, jMax,  kRef,
     O        locPres,
     I        myThid ) 
         CALL FIND_RHONUM( bi, bj, iMin, iMax, jMin, jMax, k,
     &      locPres, theta, salt, rhoLoc, myThid )
         CALL FIND_RHODEN( bi, bj, iMin, iMax, jMin, jMax, k,
     &        locPres, theta, salt, rhoDen, myThid )
         DO j=jMin,jMax
            DO i=iMin,iMax
               t1  = theta(i,j,k,bi,bj)
               t2  = t1*t1
               s1  = salt(i,j,k,bi,bj)
              IF ( s1 .GT. 0.d0 ) THEN
               sp5 = SQRT(s1) 
              ELSE
               s1  = 0.d0
               sp5 = 0.d0
              ENDIF
               p1   = locPres(i,j)*SItodBar
               p1t1 = p1*t1
               dnum_dsalt = eosMDJWFnum(4) 
     &              + eosMDJWFnum(5)*t1
     &              + 2.*eosMDJWFnum(6)*s1 + eosMDJWFnum(9)*p1
               dden_dsalt = eosMDJWFden(5) 
     &              + t1*( eosMDJWFden(6) + eosMDJWFden(7)*t2 ) 
     &              + 1.5*sp5*(eosMDJWFden(8) + eosMDJWFden(9)*t2)
               betaLoc(i,j) = rhoDen(i,j)*( dnum_dsalt 
     &              - (rhoLoc(i,j)*rhoDen(i,j))*dden_dsalt )
            ENDDO
         ENDDO
      ELSE
         WRITE(*,*) 'FIND_BETA: equationOfState = ',equationOfState
         STOP 'FIND_BETA: "equationOfState" has illegal value'
      ENDIF
      RETURN 
      END
      SUBROUTINE FIND_RHO(
     I      bi, bj, iMin, iMax, jMin, jMax,  k, kRef,
     I      tFld, sFld,
     O      rholoc,
     I      myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
       USE GRID_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k
      INTEGER kRef
      Real*8 tFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 rholoc(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      Real*8 refTemp,refSalt,sigRef,tP,sP,deltaSig,dRho
      Real*8 locPres(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 rhoP0  (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 bulkMod(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 rhoNum (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 rhoDen (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      CHARACTER*(MAX_LEN_MBUF) msgbuf
      DO j=1-OLy,sNy+OLy
       DO i=1-OLx,sNx+OLx
        rholoc(i,j)  = 0.d0
        rhoP0(i,j)   = 0.d0
        bulkMod(i,j) = 0.d0
       ENDDO
      ENDDO
      IF (equationOfState.EQ.'LINEAR') THEN
       refTemp=tRef(kRef)
       refSalt=sRef(kRef)
       dRho = rhoNil-rhoConst
       DO j=jMin,jMax
        DO i=iMin,iMax
         rholoc(i,j)=rhoNil*(
     &     sBeta*(sFld(i,j,k,bi,bj)-refSalt)
     &   -tAlpha*(tFld(i,j,k,bi,bj)-refTemp) )
     &        + dRho
        ENDDO
       ENDDO
      ELSEIF (equationOfState.EQ.'POLY3') THEN
       refTemp=eosRefT(kRef)
       refSalt=eosRefS(kRef)
       sigRef=eosSig0(kRef) + (1000.-rhoConst)
       DO j=jMin,jMax
        DO i=iMin,iMax
         tP=tFld(i,j,k,bi,bj)-refTemp
         sP=sFld(i,j,k,bi,bj)-refSalt
         deltaSig=
     &    (( eosC(9,kRef)*sP + eosC(5,kRef) )*sP + eosC(2,kRef) )*sP
     &   + ( ( eosC(6,kRef)
     &         *tP
     &        +eosC(7,kRef)*sP + eosC(3,kRef)
     &       )*tP
     &      +(eosC(8,kRef)*sP + eosC(4,kRef) )*sP + eosC(1,kRef)
     &     )*tP
         rholoc(i,j)=sigRef+deltaSig
        ENDDO
       ENDDO
      ELSEIF ( equationOfState(1:5).EQ.'JMD95'
     &      .OR. equationOfState.EQ.'UNESCO' ) THEN
         CALL PRESSURE_FOR_EOS(
     I        bi, bj, iMin, iMax, jMin, jMax,  kRef,
     O        locPres,
     I        myThid )
         CALL FIND_RHOP0(
     I        bi, bj, iMin, iMax, jMin, jMax, k,
     I        tFld, sFld,
     O        rhoP0,
     I        myThid )
         CALL FIND_BULKMOD(
     I        bi, bj, iMin, iMax, jMin, jMax,  k,
     I        locPres, tFld, sFld,
     O        bulkMod,
     I        myThid )
         DO j=jMin,jMax
            DO i=iMin,iMax
               rholoc(i,j) = rhoP0(i,j)
     &              /(1.d0 - 
     &              locPres(i,j)*SItoBar/bulkMod(i,j))
     &              - rhoConst
            ENDDO
         ENDDO
      ELSEIF ( equationOfState.EQ.'MDJWF' ) THEN
         CALL PRESSURE_FOR_EOS(
     I        bi, bj, iMin, iMax, jMin, jMax,  kRef,
     O        locPres,
     I        myThid )
         CALL FIND_RHONUM( bi, bj, iMin, iMax, jMin, jMax, k,
     &      locPres, tFld, sFld, rhoNum, myThid )
         CALL FIND_RHODEN( bi, bj, iMin, iMax, jMin, jMax, k,
     &      locPres, tFld, sFld, rhoDen, myThid )
         DO j=jMin,jMax
            DO i=iMin,iMax
               rholoc(i,j) = rhoNum(i,j)*rhoDen(i,j) - rhoConst
            ENDDO
         ENDDO
      ELSEIF( equationOfState .EQ. 'IDEALG' ) THEN
      ELSE
       WRITE(msgbuf,'(3a)')
     &        ' FIND_RHO: equationOfState = "',equationOfState,'"'
       CALL print_error( msgbuf, mythid )
       STOP 'ABNORMAL END: S/R FIND_RHO'
      ENDIF
      RETURN 
      END
      SUBROUTINE FIND_RHOP0(
     I      bi, bj, iMin, iMax, jMin, jMax, k,
     I      tFld, sFld,
     O      rhoP0,
     I      myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k	
      Real*8 tFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 rhoP0(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      Real*8 rfresh, rsalt
      Real*8 t, t2, t3, t4, s, s3o2
      DO j=jMin,jMax
         DO i=iMin,iMax
            t  = tFld(i,j,k,bi,bj) 
            t2 = t*t
            t3 = t2*t
            t4 = t3*t
            s  = sFld(i,j,k,bi,bj)
           IF ( s .GT. 0.d0 ) THEN
            s3o2 = s*SQRT(s)
           ELSE
            s    = 0.d0
            s3o2 = 0.d0
           ENDIF
            rfresh = 
     &             eosJMDCFw(1) 
     &           + eosJMDCFw(2)*t
     &           + eosJMDCFw(3)*t2
     &           + eosJMDCFw(4)*t3
     &           + eosJMDCFw(5)*t4
     &           + eosJMDCFw(6)*t4*t
            rsalt = 
     &         s*(
     &             eosJMDCSw(1)
     &           + eosJMDCSw(2)*t
     &           + eosJMDCSw(3)*t2
     &           + eosJMDCSw(4)*t3
     &           + eosJMDCSw(5)*t4
     &           )
     &       + s3o2*(
     &             eosJMDCSw(6)
     &           + eosJMDCSw(7)*t
     &           + eosJMDCSw(8)*t2
     &           )
     &           + eosJMDCSw(9)*s*s
            rhoP0(i,j) = rfresh + rsalt
         ENDDO
      ENDDO
      RETURN 
      END
      SUBROUTINE FIND_BULKMOD(
     I      bi, bj, iMin, iMax, jMin, jMax,  k,
     I      locPres, tFld, sFld,
     O      bulkMod,
     I      myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k	
      Real*8 locPres(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 tFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 bulkMod(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      Real*8 bMfresh, bMsalt, bMpres
      Real*8 t, t2, t3, t4, s, s3o2, p, p2
      DO j=jMin,jMax
         DO i=iMin,iMax
            t  = tFld(i,j,k,bi,bj) 
            t2 = t*t
            t3 = t2*t
            t4 = t3*t
            s  = sFld(i,j,k,bi,bj)
          IF ( s .GT. 0.d0 ) THEN
            s3o2 = s*SQRT(s)
          ELSE
            s    = 0.d0
            s3o2 = 0.d0
          ENDIF
            p = locPres(i,j)*SItoBar
            p2 = p*p
            bMfresh = 
     &             eosJMDCKFw(1)
     &           + eosJMDCKFw(2)*t
     &           + eosJMDCKFw(3)*t2
     &           + eosJMDCKFw(4)*t3
     &           + eosJMDCKFw(5)*t4
            bMsalt =
     &         s*( eosJMDCKSw(1)
     &           + eosJMDCKSw(2)*t
     &           + eosJMDCKSw(3)*t2
     &           + eosJMDCKSw(4)*t3
     &           )
     &    + s3o2*( eosJMDCKSw(5)
     &           + eosJMDCKSw(6)*t
     &           + eosJMDCKSw(7)*t2
     &           )
            bMpres = 
     &         p*( eosJMDCKP(1)
     &           + eosJMDCKP(2)*t
     &           + eosJMDCKP(3)*t2
     &           + eosJMDCKP(4)*t3
     &           )
     &     + p*s*( eosJMDCKP(5)
     &           + eosJMDCKP(6)*t
     &           + eosJMDCKP(7)*t2
     &           )
     &      + p*s3o2*eosJMDCKP(8)
     &      + p2*( eosJMDCKP(9)
     &           + eosJMDCKP(10)*t
     &           + eosJMDCKP(11)*t2
     &           )
     &    + p2*s*( eosJMDCKP(12)
     &           + eosJMDCKP(13)*t
     &           + eosJMDCKP(14)*t2
     &           )
            bulkMod(i,j) = bMfresh + bMsalt + bMpres
         ENDDO
      ENDDO
      RETURN 
      END
      SUBROUTINE FIND_RHONUM(
     I      bi, bj, iMin, iMax, jMin, jMax, k,
     I      locPres, tFld, sFld,
     O      rhoNum,
     I      myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k
      Real*8 locPres(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 tFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 rhoNum(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      Real*8 t1, t2, s1, p1
      DO j=jMin,jMax
         DO i=iMin,iMax
            t1  = tFld(i,j,k,bi,bj) 
            t2 = t1*t1
            s1  = sFld(i,j,k,bi,bj)
            p1   = locPres(i,j)*SItodBar
            rhoNum(i,j) = eosMDJWFnum(0)
     &           + t1*(eosMDJWFnum(1) 
     &           +     t1*(eosMDJWFnum(2) + eosMDJWFnum(3)*t1) )  
     &           + s1*(eosMDJWFnum(4)
     &           +     eosMDJWFnum(5)*t1  + eosMDJWFnum(6)*s1)      
     &           + p1*(eosMDJWFnum(7) + eosMDJWFnum(8)*t2 
     &           +     eosMDJWFnum(9)*s1 
     &           +     p1*(eosMDJWFnum(10) + eosMDJWFnum(11)*t2) )
         ENDDO
      ENDDO
      RETURN 
      end 
      SUBROUTINE FIND_RHODEN(
     I      bi, bj, iMin, iMax, jMin, jMax, k,
     I      locPres, tFld, sFld,
     O      rhoDen,
     I      myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k	
      Real*8 locPres(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 tFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8 rhoDen(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      Real*8 t1, t2, s1, sp5, p1, p1t1
      Real*8 den, epsln
      parameter ( epsln = 0.d0 )
      DO j=jMin,jMax
         DO i=iMin,iMax
            t1  = tFld(i,j,k,bi,bj) 
            t2 = t1*t1
            s1  = sFld(i,j,k,bi,bj)
           IF ( s1 .GT. 0.d0 ) THEN
            sp5 = SQRT(s1) 
           ELSE
            s1  = 0.d0
            sp5 = 0.d0
           ENDIF
            p1   = locPres(i,j)*SItodBar
            p1t1 = p1*t1
            den = eosMDJWFden(0)
     &           + t1*(eosMDJWFden(1)
     &           +     t1*(eosMDJWFden(2)
     &           +         t1*(eosMDJWFden(3) + t1*eosMDJWFden(4) ) ) )
     &           + s1*(eosMDJWFden(5)
     &           +     t1*(eosMDJWFden(6) 
     &           +         eosMDJWFden(7)*t2) 
     &           +     sp5*(eosMDJWFden(8) + eosMDJWFden(9)*t2) ) 
     &           + p1*(eosMDJWFden(10)
     &           +     p1t1*(eosMDJWFden(11)*t2 + eosMDJWFden(12)*p1) )
            rhoDen(i,j) = 1.0/(epsln+den) 
         ENDDO
      ENDDO
      RETURN 
      end 
      SUBROUTINE find_rho_scalar( 
     I     tLoc, sLoc, pLoc,
     O     rhoLoc,
     I     myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
      Real*8 sLoc, tLoc, pLoc
      Real*8 rhoLoc
      INTEGER myThid
      Real*8 t1, t2, t3, t4, s1, s3o2, p1, p2, sp5, p1t1
      Real*8 rfresh, rsalt, rhoP0
      Real*8 bMfresh, bMsalt, bMpres, BulkMod
      Real*8 rhoNum, rhoDen, den, epsln
      parameter ( epsln = 0.d0 )
      character*(max_len_mbuf) msgbuf
      rhoLoc  = 0.d0
      rhoP0   = 0.d0
      bulkMod = 0.d0
      rfresh  = 0.d0
      rsalt   = 0.d0
      bMfresh = 0.d0
      bMsalt  = 0.d0
      bMpres  = 0.d0
      rhoNum  = 0.d0
      rhoDen  = 0.d0
      den     = 0.d0
      t1 = tLoc
      t2 = t1*t1
      t3 = t2*t1
      t4 = t3*t1
      s1  = sLoc
      IF ( s1 .LT. 0.d0 ) THEN
         WRITE(*,'(a,i3,a,i3,a,i3,a,e13.5)') 
     &        ' FIND_RHO_SCALAR:   WARNING, salinity = ', s1
         s1 = 0.d0
      ENDIF
      IF (equationOfState.EQ.'LINEAR') THEN
         rhoLoc = 0.d0
      ELSEIF (equationOfState.EQ.'POLY3') THEN
         WRITE(*,'(a)') 
     &        ' FIND_RHO_SCALAR: for POLY3, the density is not'
         WRITE(*,'(a)') 
     &         '                 computed correctly in this routine'
         rhoLoc = 0.d0
      ELSEIF ( equationOfState(1:5).EQ.'JMD95'
     &      .OR. equationOfState.EQ.'UNESCO' ) THEN
         s3o2 = s1*SQRT(s1)
         p1 = pLoc*SItoBar
         p2 = p1*p1
         rfresh = 
     &          eosJMDCFw(1) 
     &        + eosJMDCFw(2)*t1
     &        + eosJMDCFw(3)*t2
     &        + eosJMDCFw(4)*t3
     &        + eosJMDCFw(5)*t4
     &        + eosJMDCFw(6)*t4*t1
         rsalt = 
     &        s1*(
     &             eosJMDCSw(1)
     &           + eosJMDCSw(2)*t1
     &           + eosJMDCSw(3)*t2
     &           + eosJMDCSw(4)*t3
     &           + eosJMDCSw(5)*t4
     &           )
     &        + s3o2*(
     &             eosJMDCSw(6)
     &           + eosJMDCSw(7)*t1
     &           + eosJMDCSw(8)*t2
     &           )
     &           + eosJMDCSw(9)*s1*s1
         rhoP0 = rfresh + rsalt
         bMfresh = 
     &             eosJMDCKFw(1)
     &           + eosJMDCKFw(2)*t1
     &           + eosJMDCKFw(3)*t2
     &           + eosJMDCKFw(4)*t3
     &           + eosJMDCKFw(5)*t4
         bMsalt =
     &        s1*( eosJMDCKSw(1)
     &           + eosJMDCKSw(2)*t1
     &           + eosJMDCKSw(3)*t2
     &           + eosJMDCKSw(4)*t3
     &           )
     &    + s3o2*( eosJMDCKSw(5)
     &           + eosJMDCKSw(6)*t1
     &           + eosJMDCKSw(7)*t2
     &           )
         bMpres = 
     &        p1*( eosJMDCKP(1)
     &           + eosJMDCKP(2)*t1
     &           + eosJMDCKP(3)*t2
     &           + eosJMDCKP(4)*t3
     &           )
     &   + p1*s1*( eosJMDCKP(5)
     &           + eosJMDCKP(6)*t1
     &           + eosJMDCKP(7)*t2
     &           )
     &      + p1*s3o2*eosJMDCKP(8)
     &      + p2*( eosJMDCKP(9)
     &           + eosJMDCKP(10)*t1
     &           + eosJMDCKP(11)*t2
     &           )
     &    + p2*s1*( eosJMDCKP(12)
     &           + eosJMDCKP(13)*t1
     &           + eosJMDCKP(14)*t2
     &           )
         bulkMod = bMfresh + bMsalt + bMpres
         rhoLoc = rhoP0/(1.d0 - p1/bulkMod) - rhoConst
      ELSEIF ( equationOfState.EQ.'MDJWF' ) THEN
         sp5 = SQRT(s1) 
         p1   = pLoc*SItodBar
         p1t1 = p1*t1
         rhoNum = eosMDJWFnum(0)
     &        + t1*(eosMDJWFnum(1) 
     &        +     t1*(eosMDJWFnum(2) + eosMDJWFnum(3)*t1) )  
     &        + s1*(eosMDJWFnum(4)
     &        +     eosMDJWFnum(5)*t1  + eosMDJWFnum(6)*s1)      
     &        + p1*(eosMDJWFnum(7) + eosMDJWFnum(8)*t2 
     &        +     eosMDJWFnum(9)*s1 
     &        +     p1*(eosMDJWFnum(10) + eosMDJWFnum(11)*t2) )
         den = eosMDJWFden(0)
     &        + t1*(eosMDJWFden(1)
     &        +     t1*(eosMDJWFden(2)
     &        +         t1*(eosMDJWFden(3) + t1*eosMDJWFden(4) ) ) )
     &        + s1*(eosMDJWFden(5)
     &        +     t1*(eosMDJWFden(6) 
     &        +         eosMDJWFden(7)*t2) 
     &        +     sp5*(eosMDJWFden(8) + eosMDJWFden(9)*t2) ) 
     &        + p1*(eosMDJWFden(10)
     &        +     p1t1*(eosMDJWFden(11)*t2 + eosMDJWFden(12)*p1) )
         rhoDen = 1.0/(epsln+den) 
         rhoLoc = rhoNum*rhoDen - rhoConst
      ELSEIF( equationOfState .EQ. 'IDEALG' ) THEN
      ELSE
       WRITE(msgbuf,'(3A)')
     &        ' FIND_RHO_SCALAR : equationOfState = "',
     &        equationOfState,'"'
       CALL PRINT_ERROR( msgbuf, mythid )
       STOP 'ABNORMAL END: S/R FIND_RHO_SCALAR'
      ENDIF
      RETURN 
      END
      SUBROUTINE LOOK_FOR_NEG_SALINITY(
     I     bi, bj, iMin, iMax, jMin, jMax,  k, 
     I     sFld,
     I     myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k
      Real*8 sFld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      INTEGER i,j, localWarning
      character*(max_len_mbuf) msgbuf
      localWarning = 0
      DO j=jMin,jMax
       DO i=iMin,iMax
        IF ( sFld(i,j,k,bi,bj) .LT. 0.d0 ) THEN
         localWarning = localWarning + 1
         sFld(i,j,k,bi,bj) = 0.d0
        ENDIF
       ENDDO
      ENDDO
      IF ( localWarning .GT. 0 ) THEN
       WRITE(standardMessageUnit,'(A,A)') 
     &      'S/R LOOK_FOR_NEG_SALINITY: found negative salinity',
     &      'values and reset them to zero.'
       WRITE(standardMessageUnit,'(A,I3)') 
     &      'S/R LOOK_FOR_NEG_SALINITY: current level is k = ', k
      ENDIF
      RETURN 
      END
      SUBROUTINE FORWARD_STEP( iloop, myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
       USE tamc_mod
       USE ctrl_mod
       USE ctrl_dummy_mod
       USE cost_mod
       USE EOS_mod
       USE CD_CODE_VARS_mod
      INTEGER iloop
      INTEGER myThid 
      INTEGER myIter
      Real*8     myTime
      INTEGER myItP1
      IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_ENTER('FORWARD_STEP',myThid)
      myIter = nIter0 + (iloop-1)
      myTime = startTime + float(iloop-1)*deltaTclock
      IF ( usediagnostics ) THEN
        CALL TIMER_START('DO_STATEVARS_DIAGS  [FORWARD_STEP]',myThid)
        CALL DO_STATEVARS_DIAGS( myTime, 0, myIter, myThid )
        CALL TIMER_STOP ('DO_STATEVARS_DIAGS  [FORWARD_STEP]',myThid)
      ENDIF
       IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_CALL('EXTERNAL_FIELDS_LOAD',myThid)
       CALL TIMER_START('EXTERNAL_FIELDS_LOAD[FORWARD_STEP]',mythid)
       CALL EXTERNAL_FIELDS_LOAD( mytime, myiter, mythid )
       CALL TIMER_STOP ('EXTERNAL_FIELDS_LOAD[FORWARD_STEP]',mythid)
      if ( myiter .EQ. nIter0 )
     &     CALL CTRL_MAP_FORCING (mythid)
       IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_CALL('DO_ATMOSPHERIC_PHYS',myThid)
       CALL TIMER_START('DO_ATMOSPHERIC_PHYS [FORWARD_STEP]',mythid)
       CALL DO_ATMOSPHERIC_PHYS( myTime, myIter, myThid )
       CALL TIMER_STOP ('DO_ATMOSPHERIC_PHYS [FORWARD_STEP]',mythid)
       IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_CALL('DO_OCEANIC_PHYS',myThid)
       CALL TIMER_START('DO_OCEANIC_PHYS     [FORWARD_STEP]',mythid)
       CALL DO_OCEANIC_PHYS( myTime, myIter, myThid )
       CALL TIMER_STOP ('DO_OCEANIC_PHYS     [FORWARD_STEP]',mythid)
      IF ( .NOT.staggerTimeStep ) THEN
        IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_CALL('THERMODYNAMICS',myThid)
        CALL TIMER_START('THERMODYNAMICS      [FORWARD_STEP]',mythid)
        CALL THERMODYNAMICS( myTime, myIter, myThid )
        CALL TIMER_STOP ('THERMODYNAMICS      [FORWARD_STEP]',mythid)
      ENDIF
        IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_CALL('DYNAMICS',myThid)
        CALL TIMER_START('DYNAMICS            [FORWARD_STEP]',mythid)
        CALL DYNAMICS( myTime, myIter, myThid )
        CALL TIMER_STOP ('DYNAMICS            [FORWARD_STEP]',mythid)
      myIter = nIter0 + iLoop
      myTime = startTime + deltaTClock * float(iLoop)
      IF ( momStepping ) THEN
        CALL TIMER_START('SOLVE_FOR_PRESSURE  [FORWARD_STEP]',myThid)
        CALL SOLVE_FOR_PRESSURE(myTime, myIter, myThid)
        CALL TIMER_STOP ('SOLVE_FOR_PRESSURE  [FORWARD_STEP]',myThid)
      ENDIF
        CALL TIMER_START('UV_CORRECTION_STEP  [FORWARD_STEP]',myThid)
        CALL MOMENTUM_CORRECTION_STEP(myTime, myIter, myThid)
        CALL TIMER_STOP ('UV_CORRECTION_STEP  [FORWARD_STEP]',myThid)
      IF ( staggerTimeStep ) THEN
        IF ( debugLevel .GE. debLevB )
     &    CALL DEBUG_CALL('DO_STAGGER_FIELDS_EXCH.',myThid)
        CALL TIMER_START('BLOCKING_EXCHANGES  [FORWARD_STEP]',myThid)
        CALL DO_STAGGER_FIELDS_EXCHANGES( myTime, myIter, myThid )
        CALL TIMER_STOP ('BLOCKING_EXCHANGES  [FORWARD_STEP]',myThid)
       IF ( usediagnostics ) THEN
        CALL TIMER_START('DO_STATEVARS_DIAGS  [FORWARD_STEP]',myThid)
        CALL DO_STATEVARS_DIAGS( myTime, 1, myIter, myThid )
        CALL TIMER_STOP ('DO_STATEVARS_DIAGS  [FORWARD_STEP]',myThid)
       ENDIF
        IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_CALL('THERMODYNAMICS',myThid)
        CALL TIMER_START('THERMODYNAMICS      [FORWARD_STEP]',mythid)
        CALL THERMODYNAMICS( myTime, myIter, myThid )
        CALL TIMER_STOP ('THERMODYNAMICS      [FORWARD_STEP]',mythid)
      ENDIF
        CALL TIMER_START('TS_CORRECTION_STEP  [FORWARD_STEP]',myThid)
        CALL TRACERS_CORRECTION_STEP(myTime, myIter, myThid)
        CALL TIMER_STOP ('TS_CORRECTION_STEP  [FORWARD_STEP]',myThid)
      CALL TIMER_START('BLOCKING_EXCHANGES  [FORWARD_STEP]',myThid)
      CALL DO_FIELDS_BLOCKING_EXCHANGES( myThid )
      CALL TIMER_STOP ('BLOCKING_EXCHANGES  [FORWARD_STEP]',myThid)
      CALL TIMER_START('DO_STATEVARS_TAVE   [FORWARD_STEP]',myThid)
      CALL DO_STATEVARS_TAVE( myTime, myIter, myThid )
      CALL TIMER_STOP ('DO_STATEVARS_TAVE   [FORWARD_STEP]',myThid)
      CALL TIMER_START('COST_TILE           [FORWARD_STEP]',myThid)
      CALL COST_TILE  ( mytime, myiter, myThid )
      CALL TIMER_STOP ('COST_TILE           [FORWARD_STEP]',myThid)
      CALL TIMER_START('DO_THE_MODEL_IO     [FORWARD_STEP]',myThid)
      CALL DO_THE_MODEL_IO( myTime, myIter, myThid )
      CALL TIMER_STOP ('DO_THE_MODEL_IO     [FORWARD_STEP]',myThid)
      CALL TIMER_START('WRITE_CHECKPOINT    [FORWARD_STEP]',myThid)
      CALL PACKAGES_WRITE_PICKUP(
     I               .FALSE., myTime, myIter, myThid )
      CALL WRITE_CHECKPOINT(
     I               .FALSE., myTime, myIter, myThid )   
      CALL TIMER_STOP ('WRITE_CHECKPOINT    [FORWARD_STEP]',myThid)
      IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_LEAVE('FORWARD_STEP',myThid)
      RETURN
      END
      SUBROUTINE FREEZE( bi, bj, iMin, iMax, jMin, jMax,
     I                     K,
     I                     myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER K
      INTEGER myThid
      INTEGER i,j
      Real*8 Tfreezing
      Tfreezing=-1.9d0
       DO j=jMin,jMax
        DO i=iMin,iMax
         IF (gT(i,j,k,bi,bj) .LT. Tfreezing) THEN
          gT(i,j,k,bi,bj)=Tfreezing
         ENDIF
        ENDDO
       ENDDO
      RETURN
      END
      SUBROUTINE FREEZE_SURFACE( myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE FFIELDS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER bi,bj,i,j,k
      Real*8 Tfreezing
      IF ( usingPCoords ) THEN
        k = Nr
      ELSE
        k = 1
      ENDIF
      Tfreezing = -1.9d0
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          IF (theta(i,j,k,bi,bj) .LT. Tfreezing) THEN
             surfaceForcingTice(i,j,bi,bj) =
     &            ( Tfreezing - theta(i,j,k,bi,bj) )
     &                    *drF(k)*hFacC(i,j,k,bi,bj) / dTtracerLev(k)
             theta(i,j,k,bi,bj) = Tfreezing
          ELSE
             surfaceForcingTice(i,j,bi,bj) = 0.d0
          ENDIF
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE GRAD_SIGMA(
     I             bi, bj, iMin, iMax, jMin, jMax, K,
     I             rhoK, sigKm1, sigKp1,
     O             sigmaX, sigmaY, sigmaR,
     I             myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax,K
      Real*8 rhoK(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 sigKm1(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 sigKp1(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 sigmaX(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 sigmaY(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 sigmaR(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      INTEGER myThid
      INTEGER i,j
      Real*8 rhoLoc(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        rhoLoc(i,j) = rhoK(i,j)
       ENDDO
      ENDDO
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx+1,sNx+Olx
        sigmaX(i,j,k)=maskW(i,j,k,bi,bj)
     &        *recip_dxC(i,j,bi,bj)
     &        *(rhoLoc(i,j)-rhoLoc(i-1,j))
       ENDDO
      ENDDO
      DO j=1-Oly+1,sNy+Oly
       DO i=1-Olx,sNx+Olx
        sigmaY(i,j,k)=maskS(i,j,k,bi,bj)
     &        *recip_dyC(i,j,bi,bj)
     &        *(rhoLoc(i,j)-rhoLoc(i,j-1))
       ENDDO
      ENDDO
      IF (K.EQ.1) THEN
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         sigmaR(i,j,k)=0.
        ENDDO
       ENDDO
      ELSE
       DO j=1-Oly,sNy+Oly
        DO i=1-Olx,sNx+Olx
         sigmaR(i,j,k)= maskC(i,j,k,bi,bj)
     &                *recip_drC(k)*rkSign
     &                *(sigKp1(i,j)-sigKm1(i,j))
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE IMPLDIFF( bi, bj, iMin, iMax, jMin, jMax,
     I                     tracerId, KappaRX, recip_hFac,
     U                     gXNm1,
     I                     myThid )
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE tamc_keys_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER tracerId
      Real*8 KappaRX(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 recip_hFac(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      Real*8 gXnm1(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      INTEGER myThid
      INTEGER i,j,k
      Real*8 deltaTX(Nr)
      Real*8 gYnm1(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      Real*8 a(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 b(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 c(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 bet(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 gam(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      IF ( tracerId.GE.1 ) THEN
        DO k=1,Nr
         deltaTX(k) = dTtracerLev(k)
        ENDDO
      ELSE
        DO k=1,Nr
         deltaTX(k) = deltaTmom
        ENDDO
      ENDIF
      DO k=1,Nr
       DO j=jMin,jMax
        DO i=iMin,iMax
         gYNm1(i,j,k,bi,bj) = 0.d0
        ENDDO
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
         a(i,j,1) = 0.d0 
       ENDDO
      ENDDO
      DO k=2,Nr
       DO j=jMin,jMax
        DO i=iMin,iMax
          a(i,j,k) = -deltaTX(k)*recip_hFac(i,j,k,bi,bj)*recip_drF(k)
     &               *KappaRX(i,j, k )*recip_drC( k )
          IF (recip_hFac(i,j,k-1,bi,bj).EQ.0.) a(i,j,k)=0.
        ENDDO
       ENDDO
      ENDDO
      DO k=1,Nr-1
       DO j=jMin,jMax
        DO i=iMin,iMax
          c(i,j,k) = -deltaTX(k)*recip_hFac(i,j,k,bi,bj)*recip_drF(k)
     &               *KappaRX(i,j,k+1)*recip_drC(k+1)
          IF (recip_hFac(i,j,k+1,bi,bj).EQ.0.) c(i,j,k)=0.
        ENDDO
       ENDDO
      ENDDO
      DO j=jMin,jMax
       DO i=iMin,iMax
         c(i,j,Nr) = 0.d0
       ENDDO
      ENDDO
      DO k=1,Nr
       DO j=jMin,jMax
        DO i=iMin,iMax
          b(i,j,k) = 1.d0 - c(i,j,k) - a(i,j,k)
        ENDDO
       ENDDO
      ENDDO
      DO k=1,Nr
       DO j=jMin,jMax
        DO i=iMin,iMax
          bet(i,j,k) = 1.d0
          gam(i,j,k) = 0.d0
        ENDDO
       ENDDO
      ENDDO
      IF (Nr.GT.1) THEN
       k = 1
       DO j=jMin,jMax
        DO i=iMin,iMax
         IF (b(i,j,1).NE.0.) bet(i,j,1) = 1.d0 / b(i,j,1)
        ENDDO
       ENDDO
      ENDIF
      IF (Nr.GE.2) THEN
       DO k=2,Nr
        DO j=jMin,jMax
         DO i=iMin,iMax
          gam(i,j,k) = c(i,j,k-1)*bet(i,j,k-1)
          IF ( ( b(i,j,k) - a(i,j,k)*gam(i,j,k) ) .NE. 0.) 
     &        bet(i,j,k) = 1.d0 / ( b(i,j,k) - a(i,j,k)*gam(i,j,k) )
         ENDDO
        ENDDO
       ENDDO
      ENDIF
      DO j=jMin,jMax
       DO i=iMin,iMax
        gYNm1(i,j,1,bi,bj) = gXNm1(i,j,1,bi,bj)*bet(i,j,1)
       ENDDO
      ENDDO
      DO k=2,Nr
       DO j=jMin,jMax
        DO i=iMin,iMax
         gYnm1(i,j,k,bi,bj) = bet(i,j,k)*
     &        (gXnm1(i,j,k,bi,bj) - a(i,j,k)*gYnm1(i,j,k-1,bi,bj))
        ENDDO
       ENDDO
      ENDDO
       DO k=Nr-1,1,-1
        DO j=jMin,jMax
         DO i=iMin,iMax
          gYnm1(i,j,k,bi,bj)=gYnm1(i,j,k,bi,bj)
     &              -gam(i,j,k+1)*gYnm1(i,j,k+1,bi,bj)
         ENDDO
        ENDDO
       ENDDO
       DO k=1,Nr
        DO j=jMin,jMax
         DO i=iMin,iMax
          gXnm1(i,j,k,bi,bj)=gYnm1(i,j,k,bi,bj)
         ENDDO
        ENDDO
       ENDDO
      RETURN
      END
      SUBROUTINE INI_AUTODIFF( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE FFIELDS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER  I, J, K
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO K=1,Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
          ENDDO
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      END
      SUBROUTINE INI_CARTESIAN_GRID( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER myThid
      INTEGER iG, jG, bi, bj, I,  J
      Real*8 xG0, yG0
      Real*8 xGloc(1-Olx:sNx+Olx+1,1-Oly:sNy+Oly+1)
      Real*8 yGloc(1-Olx:sNx+Olx+1,1-Oly:sNy+Oly+1)
      INTEGER iGl,jGl
      iGl(I,bi) = 1+mod(myXGlobalLo-1+(bi-1)*sNx+I+Olx*Nx-1,Nx)
      jGl(J,bj) = 1+mod(myYGlobalLo-1+(bj-1)*sNy+J+Oly*Ny-1,Ny)
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        jG = myYGlobalLo + (bj-1)*sNy
        iG = myXGlobalLo + (bi-1)*sNx
        xG0 = 0.
        DO i=1, iG-1
         xG0 = xG0 + delX(i)
        ENDDO
        DO i=1, Olx
         xG0 = xG0 - delX( 1+mod(Olx*Nx-1+iG-i,Nx) )
        ENDDO
        yG0 = 0.
        DO j=1, jG-1
         yG0 = yG0 + delY(j)
        ENDDO
        DO j=1, Oly
         yG0 = yG0 - delY( 1+mod(Oly*Ny-1+jG-j,Ny) )
        ENDDO
        DO J=1-Oly,sNy+Oly +1
         xGloc(1-Olx,J) = xG0
         DO I=1-Olx,sNx+Olx
          xGloc(I+1,J) = xGloc(I,J) + delX( iGl(I,bi) )
         ENDDO
        ENDDO
        DO I=1-Olx,sNx+Olx +1
         yGloc(I,1-Oly) = yG0
         DO J=1-Oly,sNy+Oly
          yGloc(I,J+1) = yGloc(I,J) + delY( jGl(J,bj) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          xG(I,J,bi,bj) = xGloc(I,J)
          yG(I,J,bi,bj) = yGloc(I,J)
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          xC(I,J,bi,bj) = 0.25*(
     &     xGloc(I,J)+xGloc(I+1,J)+xGloc(I,J+1)+xGloc(I+1,J+1) )
          yC(I,J,bi,bj) = 0.25*(
     &     yGloc(I,J)+yGloc(I+1,J)+yGloc(I,J+1)+yGloc(I+1,J+1) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          dXF(I,J,bi,bj) = delX( iGl(I,bi) )
          dYF(I,J,bi,bj) = delY( jGl(J,bj) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          dXG(I,J,bi,bj) = delX( iGl(I,bi) )
          dYG(I,J,bi,bj) = delY( jGl(J,bj) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          dXC(I,J,bi,bj) = 0.
          dYC(I,J,bi,bj) = 0.
          dXV(I,J,bi,bj) = 0.
          dYU(I,J,bi,bj) = 0.
          rAw(I,J,bi,bj) = 0.
          rAs(I,J,bi,bj) = 0.
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx+1,sNx+Olx ! NOTE range
          dXC(I,J,bi,bj) = 0.5d0*(dXF(I,J,bi,bj)+dXF(I-1,J,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly+1,sNy+Oly ! NOTE range
         DO I=1-Olx,sNx+Olx
          dYC(I,J,bi,bj) = 0.5*(dYF(I,J,bi,bj)+dYF(I,J-1,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly+1,sNy+Oly ! NOTE range
         DO I=1-Olx+1,sNx+Olx ! NOTE range
          dXV(I,J,bi,bj) = 0.5*(dXG(I,J,bi,bj)+dXG(I-1,J,bi,bj))
          dYU(I,J,bi,bj) = 0.5*(dYG(I,J,bi,bj)+dYG(I,J-1,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          rA (I,J,bi,bj) = dxF(I,J,bi,bj)*dyF(I,J,bi,bj)
          rAw(I,J,bi,bj) = dxC(I,J,bi,bj)*dyG(I,J,bi,bj)
          rAs(I,J,bi,bj) = dxG(I,J,bi,bj)*dyC(I,J,bi,bj)
          rAz(I,J,bi,bj) = dxV(I,J,bi,bj)*dyU(I,J,bi,bj)
          tanPhiAtU(I,J,bi,bj) = 0.
          tanPhiAtV(I,J,bi,bj) = 0.
          angleCosC(I,J,bi,bj) = 1.
          angleSinC(I,J,bi,bj) = 0.
         ENDDO
        ENDDO
        DO J=1-OLy,sNy+OLy
         cosFacU(J,bi,bj)=1.
         cosFacV(J,bi,bj)=1.
         sqcosFacU(J,bi,bj)=1.
         sqcosFacV(J,bi,bj)=1.
        ENDDO
       ENDDO ! bi
      ENDDO ! bj
      IF ( latBandClimRelax.EQ.UNSET_RL ) THEN
        IF ( myThid .EQ. 1 ) THEN
        latBandClimRelax = 0.
        DO j=1,Ny
          latBandClimRelax = latBandClimRelax + delY(j)
        ENDDO
        latBandClimRelax = latBandClimRelax*3.d0
        ENDIF
      ENDIF 
      RETURN
      END
      SUBROUTINE INI_CG2D( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
       USE CG2D_mod
      INTEGER myThid
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      INTEGER bi, bj
      INTEGER I,  J, K
      Real*8     faceArea
      Real*8     myNorm
      Real*8     aC, aCw, aCs
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO J=1-OLy,sNy+OLy
         DO I=1-OLx,sNx+OLx
          aW2d(I,J,bi,bj) = 0.d0
          aS2d(I,J,bi,bj) = 0.d0
          pW(I,J,bi,bj) = 0.d0
          pS(I,J,bi,bj) = 0.d0
          pC(I,J,bi,bj) = 0.d0
          cg2d_q(I,J,bi,bj) = 0.d0
         ENDDO
        ENDDO
        DO J=1-1,sNy+1
         DO I=1-1,sNx+1
          cg2d_r(I,J,bi,bj) = 0.d0
          cg2d_s(I,J,bi,bj) = 0.d0
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      myNorm = 0.d0
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO J=1,sNy
         DO I=1,sNx
          aW2d(I,J,bi,bj) = 0.d0
          aS2d(I,J,bi,bj) = 0.d0
         ENDDO
        ENDDO
        DO K=1,Nr
         DO J=1,sNy
          DO I=1,sNx
           faceArea = dyG(I,J,bi,bj)*drF(K)
     &               *hFacW(I,J,K,bi,bj)
           aW2d(I,J,bi,bj) = aW2d(I,J,bi,bj) + 
     &      implicSurfPress*implicDiv2DFlow
     &           *faceArea*recip_dxC(I,J,bi,bj)
           faceArea = dxG(I,J,bi,bj)*drF(K)
     &               *hFacS(I,J,K,bi,bj)
           aS2d(I,J,bi,bj) = aS2d(I,J,bi,bj) + 
     &      implicSurfPress*implicDiv2DFlow
     &           *faceArea*recip_dyC(I,J,bi,bj)
          ENDDO
         ENDDO
        ENDDO
        DO J=1,sNy
         DO I=1,sNx
          myNorm = MAX(ABS(aW2d(I,J,bi,bj)),myNorm)
          myNorm = MAX(ABS(aS2d(I,J,bi,bj)),myNorm)
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      CALL GLOBAL_MAX_R8 (  myNorm,  myThid  )
      IF ( myNorm .NE. 0.d0 ) THEN
       myNorm = 1.d0/myNorm
      ELSE
       myNorm = 1.d0
      ENDIF
       cg2dNorm = myNorm
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO J=1,sNy
         DO I=1,sNx
          aW2d(I,J,bi,bj) = aW2d(I,J,bi,bj)*myNorm
          aS2d(I,J,bi,bj) = aS2d(I,J,bi,bj)*myNorm
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      CALL EXCH_UV_XY_RS(aW2d,aS2d,.FALSE.,myThid)
      cg2dNormaliseRHS = cg2dTargetResWunit.LE.0.
      IF (cg2dNormaliseRHS) THEN
        cg2dTolerance = cg2dTargetResidual
      ELSE
        cg2dTolerance = cg2dNorm * cg2dTargetResWunit
     &                           * globalArea / deltaTmom
      ENDIF
      IF (  myThid  .EQ. 1 ) THEN
       WRITE(msgBuf,'(2A,1PE23.16)') 'INI_CG2D: ',
     &      'CG2D normalisation factor = ', cg2dNorm
       CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
       IF (.NOT.cg2dNormaliseRHS) THEN
        WRITE(msgBuf,'(2A,1PE22.15,A,1PE16.10,A)') 'INI_CG2D: ',
     &      'cg2dTolerance =', cg2dTolerance, ' (Area=',globalArea,')'
        CALL PRINT_MESSAGE(msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
       ENDIF
       WRITE(msgBuf,*) ' '
       CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      ENDIF
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO J=1,sNy
         DO I=1,sNx
          pC(I,J,bi,bj) = 1.d0
          aC = -(
     &     aW2d(I,J,bi,bj) + aW2d(I+1,J  ,bi,bj)
     &    +aS2d(I,J,bi,bj) + aS2d(I  ,J+1,bi,bj)
     &    +freeSurfFac*myNorm*recip_Bo(I,J,bi,bj)* 
     &     rA(I,J,bi,bj)/deltaTMom/deltaTfreesurf
     &    )
          aCs = -(
     &     aW2d(I,J-1,bi,bj) + aW2d(I+1,J-1,bi,bj)
     &    +aS2d(I,J-1,bi,bj) + aS2d(I  ,J  ,bi,bj)
     &    +freeSurfFac*myNorm*recip_Bo(I,J-1,bi,bj)* 
     &     rA(I,J-1,bi,bj)/deltaTMom/deltaTfreesurf
     &    )
          aCw = -(
     &     aW2d(I-1,J,bi,bj) + aW2d(I  ,J  ,bi,bj)
     &    +aS2d(I-1,J,bi,bj) + aS2d(I-1,J+1,bi,bj)
     &    +freeSurfFac*myNorm*recip_Bo(I-1,J,bi,bj)* 
     &     rA(I-1,J,bi,bj)/deltaTMom/deltaTfreesurf
     &    )
          IF ( aC .EQ. 0. ) THEN
            pC(I,J,bi,bj) = 1.d0
          ELSE
           pC(I,J,bi,bj) =  1.d0 / aC
          ENDIF
          IF ( aC + aCw .EQ. 0. ) THEN
           pW(I,J,bi,bj) = 0.
          ELSE
           pW(I,J,bi,bj) = 
     &     -aW2d(I  ,J  ,bi,bj)/((cg2dpcOffDFac *(aCw+aC))**2 )
          ENDIF
          IF ( aC + aCs .EQ. 0. ) THEN
           pS(I,J,bi,bj) = 0.
          ELSE
           pS(I,J,bi,bj) =
     &     -aS2d(I  ,J  ,bi,bj)/((cg2dpcOffDFac *(aCs+aC))**2 )
          ENDIF
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      CALL EXCH_XY_RL ( pC,  myThid )
      CALL EXCH_UV_XY_RS(pW,pS,.FALSE.,myThid)
      RETURN
      END
      SUBROUTINE INI_CORI( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER  I,  J, K
      Real*8 facGrid
      IF     ( useConstantF ) THEN
        DO bj = myByLo(myThid), myByHi(myThid)
          DO bi = myBxLo(myThid), myBxHi(myThid)
              DO J=1-Oly,sNy+Oly
                DO I=1-Olx,sNx+Olx
                  fCori(i,j,bi,bj)=f0
                  fCoriG(i,j,bi,bj)=f0
                  fCoriCos(i,j,bi,bj)=0.
                ENDDO
              ENDDO
          ENDDO
        ENDDO
      ELSEIF ( useBetaPlaneF ) THEN
        facGrid = 1.d0
        IF ( usingSphericalPolarGrid ) facGrid = deg2rad*rSphere
        DO bj = myByLo(myThid), myByHi(myThid)
          DO bi = myBxLo(myThid), myBxHi(myThid)
              DO J=1-Oly,sNy+Oly
                DO I=1-Olx,sNx+Olx
                  fCori(i,j,bi,bj)=f0+beta*yC(i,j,bi,bj)*facGrid
                  fCoriG(i,j,bi,bj)=f0+beta*yG(i,j,bi,bj)*facGrid
                  fCoriCos(i,j,bi,bj)=0.
                ENDDO
              ENDDO
          ENDDO
        ENDDO
      ELSEIF ( useSphereF ) THEN
        DO bj = myByLo(myThid), myByHi(myThid)
          DO bi = myBxLo(myThid), myBxHi(myThid)
              DO J=1-Oly,sNy+Oly
                DO I=1-Olx,sNx+Olx
                  fCori(i,j,bi,bj)=
     &                 2.d0*omega*sin(yC(i,j,bi,bj)*deg2rad)
                  fCoriG(i,j,bi,bj)=
     &                 2.d0*omega*sin(yG(i,j,bi,bj)*deg2rad)
                  fCoriCos(i,j,bi,bj)=
     &                 2.d0*omega*cos(yC(i,j,bi,bj)*deg2rad)
                ENDDO
              ENDDO
          ENDDO
        ENDDO
      ELSE
        DO bj = myByLo(myThid), myByHi(myThid)
          DO bi = myBxLo(myThid), myBxHi(myThid)
              DO J=1-Oly,sNy+Oly
                DO I=1-Olx,sNx+Olx
                  fCori(i,j,bi,bj)=0.
                  fCoriG(i,j,bi,bj)=0.
                  fCoriCos(i,j,bi,bj)=0.
                ENDDO
              ENDDO
          ENDDO
        ENDDO
        CALL READ_REC_XY_RS( 'fCoriC.bin', fCori,   1, 0, myThid )
        CALL READ_REC_XY_RS( 'fCoriG.bin', fCoriG,  1, 0, myThid )
        CALL READ_REC_XY_RS( 'fCorCs.bin', fCoriCos,1, 0, myThid )
        IF ( useCubedSphereExchange ) THEN
         DO bj = myByLo(myThid), myByHi(myThid)
          DO bi = myBxLo(myThid), myBxHi(myThid)
           IF (bi.LE.3 .OR. bi.GE.5) THEN
             fCoriG(sNx+1,1,bi,bj) = fCoriG(1,1,bi,bj)
           ELSE
             fCoriG(sNx+1,1,bi,bj) = -fCoriG(1,1,bi,bj)
           ENDIF
           IF (bi.GE.3) THEN
             fCoriG(1,sNy+1,bi,bj) = fCoriG(1,1,bi,bj)
             fCoriG(sNx+1,sNy+1,bi,bj) = fCoriG(sNx+1,1,bi,bj)
           ELSE
             fCoriG(1,sNy+1,bi,bj) = -fCoriG(1,1,bi,bj)
             fCoriG(sNx+1,sNy+1,bi,bj) = -fCoriG(sNx+1,1,bi,bj)
           ENDIF
          ENDDO
         ENDDO
        ENDIF
        CALL EXCH_XY_RL ( fCori, myThid )
        CALL EXCH_Z_XY_RS(fCoriG,myThid)
        CALL EXCH_XY_RL ( fCoriCos, myThid )
      ENDIF
      RETURN
      END
      SUBROUTINE INI_CURVILINEAR_GRID( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER myThid
      INTEGER bi,bj, myIter
      INTEGER I,J
      CHARACTER*(MAX_LEN_FNAM) fName
      Real*8 buf(sNx+1,sNy+1)
      INTEGER iG, iL, iLen
      CHARACTER*(MAX_LEN_MBUF) msgBuf, tmpBuf
      INTEGER  ILNBLNK
      EXTERNAL ILNBLNK
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          XC(i,j,bi,bj)=0.
          YC(i,j,bi,bj)=0.
          XG(i,j,bi,bj)=0.
          YG(i,j,bi,bj)=0.
          DXC(i,j,bi,bj)=0.
          DYC(i,j,bi,bj)=0.
          DXG(i,j,bi,bj)=0.
          DYG(i,j,bi,bj)=0.
          DXF(i,j,bi,bj)=0.
          DYF(i,j,bi,bj)=0.
          DXV(i,j,bi,bj)=0.
          DYU(i,j,bi,bj)=0.
          RA(i,j,bi,bj)=0.
          RAZ(i,j,bi,bj)=0.
          RAW(i,j,bi,bj)=0.
          RAS(i,j,bi,bj)=0.
          tanPhiAtU(i,j,bi,bj)=0.
          tanPhiAtV(i,j,bi,bj)=0.
          angleCosC(i,j,bi,bj)=1.
          angleSinC(i,j,bi,bj)=0.
          cosFacU(J,bi,bj)=1.
          cosFacV(J,bi,bj)=1.
          sqcosFacU(J,bi,bj)=1.
          sqcosFacV(J,bi,bj)=1.
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      CALL MDSREADFIELD('LONC.bin',readBinaryPrec,'RS',1,XC,  1,myThid)
      CALL MDSREADFIELD('LATC.bin',readBinaryPrec,'RS',1,YC,  1,myThid)
      CALL EXCH_XY_RL ( XC, myThid )
      CALL EXCH_XY_RL ( YC, myThid )
      CALL MDSREADFIELD('DXF.bin',readBinaryPrec,'RS',1,DXF,  1,myThid)
      CALL MDSREADFIELD('DYF.bin',readBinaryPrec,'RS',1,DYF,  1,myThid)
      CALL EXCH_XY_RL ( DXF, myThid )
      CALL EXCH_XY_RL ( DYF, myThid )
      IF (useCubedSphereExchange) THEN
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1,sNy
         DO i=1,Olx
          DXF(1-i,j,bi,bj)=DXF(i,j,bi,bj)
          DXF(sNx+i,j,bi,bj)=DXF(sNx+1-i,j,bi,bj)
          DYF(1-i,j,bi,bj)=DYF(i,j,bi,bj)
          DYF(sNx+i,j,bi,bj)=DYF(sNx+1-i,j,bi,bj)
         ENDDO
        ENDDO
        DO j=1,Oly
         DO i=1,sNx
          DXF(i,1-j,bi,bj)=DXF(i,j,bi,bj)
          DXF(i,sNy+j,bi,bj)=DXF(i,sNy+1-j,bi,bj)
          DYF(i,1-j,bi,bj)=DYF(i,j,bi,bj)
          DYF(i,sNy+j,bi,bj)=DYF(i,sNy+1-j,bi,bj)
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      ENDIF
      CALL MDSREADFIELD('RA.bin',readBinaryPrec,'RS',1,RA,  1,myThid)
      CALL EXCH_XY_RL ( RA, myThid  )
      CALL MDSREADFIELD('LONG.bin',readBinaryPrec,'RS',1,XG,  1,myThid)
      CALL MDSREADFIELD('LATG.bin',readBinaryPrec,'RS',1,YG,  1,myThid)
      IF (useCubedSphereExchange) THEN
      bi=3
      bj=1
      YG(1,sNy+1,bj,1)=YG(1,1,bi,1)
      bj=bj+2
      YG(1,sNy+1,bj,1)=YG(1,1,bi,1)
      bj=bj+2
      YG(1,sNy+1,bj,1)=YG(1,1,bi,1)
      bi=6
      bj=2
      YG(sNx+1,1,bj,1)=YG(1,1,bi,1)
      bj=bj+2
      YG(sNx+1,1,bj,1)=YG(1,1,bi,1)
      bj=bj+2
      YG(sNx+1,1,bj,1)=YG(1,1,bi,1)
      ENDIF
      CALL EXCH_Z_XY_RS(XG,myThid)
      CALL EXCH_Z_XY_RS(YG,myThid)
      CALL MDSREADFIELD('DXV.bin',readBinaryPrec,'RS',1,DXV,  1,myThid)
      CALL MDSREADFIELD('DYU.bin',readBinaryPrec,'RS',1,DYU,  1,myThid)
      IF (.NOT.useCubedSphereExchange) THEN
      CALL EXCH_Z_XY_RS(DXV,myThid)
      CALL EXCH_Z_XY_RS(DYU,myThid)
      ELSE
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1,sNy
         DO i=1,Olx
          DXV(1-i,j,bi,bj)=DXV(1+i,j,bi,bj)
          DXV(sNx+i,j,bi,bj)=DXV(i,j,bi,bj)
          DYU(1-i,j,bi,bj)=DYU(1+i,j,bi,bj)
          DYU(sNx+i,j,bi,bj)=DYU(i,j,bi,bj)
         ENDDO
        ENDDO
        DO j=1,Oly
         DO i=1-Olx,sNx+Olx
          DXV(i,1-j,bi,bj)=DXV(i,1+j,bi,bj)
          DXV(i,sNy+j,bi,bj)=DXV(i,j,bi,bj)
          DYU(i,1-j,bi,bj)=DYU(i,1+j,bi,bj)
          DYU(i,sNy+j,bi,bj)=DYU(i,j,bi,bj)
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      ENDIF
      CALL MDSREADFIELD('RAZ.bin',readBinaryPrec,'RS',1,RAZ,  1,myThid)
      IF (useCubedSphereExchange) THEN
      CALL EXCH_Z_XY_RS(RAZ , myThid )
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        RAZ(sNx+1,1,bi,bj)=RAZ(1,1,bi,bj)
        RAZ(1,sNy+1,bi,bj)=RAZ(1,1,bi,bj)
       ENDDO
      ENDDO
      ENDIF
      CALL EXCH_Z_XY_RS(RAZ,myThid)
      CALL MDSREADFIELD('DXC.bin',readBinaryPrec,'RS',1,DXC,  1,myThid)
      CALL MDSREADFIELD('DYC.bin',readBinaryPrec,'RS',1,DYC,  1,myThid)
      CALL EXCH_UV_XY_RS(DXC,DYC,.FALSE.,myThid)
      CALL MDSREADFIELD('RAW.bin',readBinaryPrec,'RS',1,RAW,  1,myThid)
      CALL MDSREADFIELD('RAS.bin',readBinaryPrec,'RS',1,RAS,  1,myThid)
      IF (useCubedSphereExchange) THEN
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO J = 1,sNy
        ENDDO
       ENDDO
      ENDDO
      ENDIF
      CALL EXCH_UV_XY_RS(RAW,RAS,.FALSE.,myThid)
      CALL MDSREADFIELD('DXG.bin',readBinaryPrec,'RS',1,DXG,  1,myThid)
      CALL MDSREADFIELD('DYG.bin',readBinaryPrec,'RS',1,DYG,  1,myThid)
      IF (useCubedSphereExchange) THEN
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO J = 1,sNy
        ENDDO
       ENDDO
      ENDDO
      ENDIF
      CALL EXCH_UV_XY_RS(DYG,DXG,.FALSE.,myThid)
      CALL EXCH_UV_AGRID_XY_RS(angleSinC,angleCosC,.TRUE.,myThid)
      IF ( debugLevel .GE. debLevB ) THEN
         myIter = 1
         CALL PLOT_FIELD_XYRL( XC      , 'Current XC      ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( YC      , 'Current YC      ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( DXF     , 'Current DXF     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( XC      , 'Current XC      ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( DYF     , 'Current DYF     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( RA      , 'Current RA      ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( XG      , 'Current XG      ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( YG      , 'Current YG      ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( DXV     , 'Current DXV     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( DYU     , 'Current DYU     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( RAZ     , 'Current RAZ     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( DXC     , 'Current DXC     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( DYC     , 'Current DYC     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( RAW     , 'Current RAW     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( RAS     , 'Current RAS     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( DXG     , 'Current DXG     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL( DYG     , 'Current DYG     ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL(angleCosC, 'Current AngleCS ' ,
     &        myIter, myThid )
         CALL PLOT_FIELD_XYRL(angleSinC, 'Current AngleSN ' ,
     &        myIter, myThid )
      ENDIF
      RETURN
      END
      SUBROUTINE READSYMTILE_RS(fName,irec,array,bi,bj,buf,myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
      CHARACTER*(*) fName
      INTEGER irec
      Real*8 array(1-Olx:sNx+Olx,1-Oly:sNy+Oly,nSx,nSy)
      INTEGER bi,bj,myThid
      Real*8 buf(1:sNx+1,1:sNy+1)
      INTEGER I,J,dUnit, iLen
      INTEGER length_of_rec
      INTEGER MDS_RECLEN
      INTEGER  ILNBLNK
      EXTERNAL ILNBLNK
      iLen = ILNBLNK(fName)
      CALL MDSFINDUNIT( dUnit, myThid )
      length_of_rec=MDS_RECLEN( 64, (sNx+1)*(sNy+1), myThid )
      OPEN( dUnit, file=fName(1:iLen), status='old',
     &             access='direct', recl=length_of_rec )
      READ(dUnit,rec=irec) buf
      CLOSE( dUnit )
      DO J=1,sNy+1
       DO I=1,sNx+1
        array(I,J,bi,bj)=buf(I,J)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE INI_CYLINDER_GRID( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER myThid
      INTEGER iG, jG
      INTEGER bi, bj
      INTEGER  I,  J
      Real*8 dtheta, thisRad, xG0, yG0
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      Real*8 xGloc(1-Olx:sNx+Olx+1,1-Oly:sNy+Oly+1)
      Real*8 yGloc(1-Olx:sNx+Olx+1,1-Oly:sNy+Oly+1)
      INTEGER iGl,jGl
      iGl(I,bi) = 1+mod(myXGlobalLo-1+(bi-1)*sNx+I+Olx*Nx-1,Nx)
      jGl(J,bj) = 1+mod(myYGlobalLo-1+(bj-1)*sNy+J+Oly*Ny-1,Ny)
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        jG = myYGlobalLo + (bj-1)*sNy
        iG = myXGlobalLo + (bi-1)*sNx
        xG0 = thetaMin
        DO i=1, iG-1
         xG0 = xG0 + delX(i)
        ENDDO
        DO i=1, Olx
         xG0 = xG0 - delX( 1+mod(Olx*Nx-1+iG-i,Nx) )
        ENDDO
        yG0 = 0
        DO j=1, jG-1
         yG0 = yG0 + delY(j)
        ENDDO
        DO j=1, Oly
         yG0 = yG0 - delY( 1+mod(Oly*Ny-1+jG-j,Ny) )
        ENDDO
        DO J=1-Oly,sNy+Oly +1
         xGloc(1-Olx,J) = xG0
         DO I=1-Olx,sNx+Olx
          xGloc(I+1,J) = xGloc(I,J) + delX( iGl(I,bi) )
         ENDDO
        ENDDO
        DO I=1-Olx,sNx+Olx +1
         yGloc(I,1-Oly) = yG0
         DO J=1-Oly,sNy+Oly
          yGloc(I,J+1) = yGloc(I,J) + delY( jGl(J,bj) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          xG(I,J,bi,bj) = xGloc(I,J)
          yG(I,J,bi,bj) = yGloc(I,J)
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          xC(I,J,bi,bj) = 0.25*( 
     &     xGloc(I,J)+xGloc(I+1,J)+xGloc(I,J+1)+xGloc(I+1,J+1) )
          yC(I,J,bi,bj) = 0.25*( 
     &     yGloc(I,J)+yGloc(I+1,J)+yGloc(I,J+1)+yGloc(I+1,J+1) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          thisRad = yC(I,J,bi,bj)
          dtheta = delX( iGl(I,bi) )
          dXF(I,J,bi,bj) = thisRad*dtheta*deg2rad
          dYF(I,J,bi,bj) = delY( jGl(J,bj) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          thisRad = 0.5*(yGloc(I,J)+yGloc(I+1,J))
          dtheta = delX( iGl(I,bi) )
          dXG(I,J,bi,bj) = thisRad*dtheta*deg2rad
          dYG(I,J,bi,bj) = delY( jGl(J,bj) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          dXC(I,J,bi,bj) = 0.
          dYC(I,J,bi,bj) = 0.
          dXV(I,J,bi,bj) = 0.
          dYU(I,J,bi,bj) = 0.
          rAw(I,J,bi,bj) = 0.
          rAs(I,J,bi,bj) = 0.
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx+1,sNx+Olx ! NOTE range
          dXC(I,J,bi,bj) = 0.5d0*(dXF(I,J,bi,bj)+dXF(I-1,J,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly+1,sNy+Oly ! NOTE range
         DO I=1-Olx,sNx+Olx
          dYC(I,J,bi,bj) = 0.5*(dYF(I,J,bi,bj)+dYF(I,J-1,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly+1,sNy+Oly ! NOTE range
         DO I=1-Olx+1,sNx+Olx ! NOTE range
          dXV(I,J,bi,bj) = 0.5*(dXG(I,J,bi,bj)+dXG(I-1,J,bi,bj))
          dYU(I,J,bi,bj) = 0.5*(dYG(I,J,bi,bj)+dYG(I,J-1,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          rA (I,J,bi,bj) = dxF(I,J,bi,bj)*dyF(I,J,bi,bj)
          rAw(I,J,bi,bj) = dxC(I,J,bi,bj)*dyG(I,J,bi,bj)
          rAs(I,J,bi,bj) = dxG(I,J,bi,bj)*dyC(I,J,bi,bj)
          rAz(I,J,bi,bj) = dxV(I,J,bi,bj)*dyU(I,J,bi,bj)
          tanPhiAtU(I,J,bi,bj) = 0.
          tanPhiAtV(I,J,bi,bj) = 0.
          angleCosC(I,J,bi,bj) = 1.
          angleSinC(I,J,bi,bj) = 0.
         ENDDO
        ENDDO
        DO J=1-OLy,sNy+OLy
         cosFacU(J,bi,bj)=1.
         cosFacV(J,bi,bj)=1.
         sqcosFacU(J,bi,bj)=1.
         sqcosFacV(J,bi,bj)=1.
        ENDDO
       ENDDO ! bi
      ENDDO ! bj
      IF ( latBandClimRelax.EQ.UNSET_RL ) THEN
        IF ( myThid .EQ. 1 ) THEN
        latBandClimRelax = 0.
        DO j=1,Ny
          latBandClimRelax = latBandClimRelax + delY(j)
        ENDDO
        latBandClimRelax = latBandClimRelax*3.d0
        ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE INI_DEPTHS( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER myThid
      INTEGER iG, jG
      INTEGER bi, bj
      INTEGER  I, J
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      IF (usingPCoords .AND. bathyFile .NE. ' '
     &                 .AND. topoFile  .NE. ' ' ) THEN
       WRITE(msgBuf,'(A,A)')
     &  'S/R INI_DEPTHS: both bathyFile & topoFile are specified:',
     &  ' select the right one !'
       CALL PRINT_ERROR( msgBuf , myThid)
       STOP 'ABNORMAL END: S/R INI_DEPTHS'
      ENDIF
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          R_low(i,j,bi,bj) = 0.
          Ro_surf(i,j,bi,bj) = 0.
          topoZ(i,j,bi,bj) = 0.
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF (usingPCoords .OR. bathyFile .EQ. ' ') THEN
       DO bj = myByLo(myThid), myByHi(myThid)
        DO bi = myBxLo(myThid), myBxHi(myThid)
         DO j=1,sNy
          DO i=1,sNx
           R_low(i,j,bi,bj) = rF(Nr+1)
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ELSE
        IF (  myThid  .EQ. 1 ) THEN
        CALL READ_REC_XY_RS( bathyFile, R_low, 1, 0, myThid )
        ENDIF
      ENDIF
      CALL EXCH_XY_RL ( R_low,  myThid  )
      IF ( usingPCoords .AND. bathyFile.NE.' ' ) THEN
        IF (  myThid  .EQ. 1 ) THEN
        CALL READ_REC_XY_RS( bathyFile, Ro_surf, 1, 0, myThid )
        ENDIF
        CALL BARRIER(myThid)
      ELSEIF ( topoFile.EQ.' ' ) THEN
        DO bj = myByLo(myThid), myByHi(myThid)
         DO bi = myBxLo(myThid), myBxHi(myThid)
          DO j=1,sNy
           DO i=1,sNx
            Ro_surf(i,j,bi,bj) = Ro_SeaLevel
           ENDDO
          ENDDO
         ENDDO
        ENDDO
      ELSE
        IF (  myThid  .EQ. 1 ) THEN
        CALL READ_REC_XY_RS( topoFile, topoZ, 1, 0, myThid )
        ENDIF
        CALL BARRIER(myThid)
        IF (buoyancyRelation .EQ. 'ATMOSPHERIC') THEN
          CALL INI_P_GROUND( 2, topoZ,
     O                       Ro_surf,
     I                       myThid )
          CALL BARRIER(myThid)
        ELSE
          DO bj = myByLo(myThid), myByHi(myThid)
           DO bi = myBxLo(myThid), myBxHi(myThid)
            DO j=1,sNy
             DO i=1,sNx
              Ro_surf(i,j,bi,bj) = topoZ(i,j,bi,bj)
             ENDDO
            ENDDO
           ENDDO
          ENDDO
        ENDIF
      ENDIF
      CALL EXCH_XY_RL ( Ro_surf,  myThid  )
      IF (usingPCoords) THEN
       DO bj = myByLo(myThid), myByHi(myThid)
        DO bi = myBxLo(myThid), myBxHi(myThid)
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
           iG = myXGlobalLo-1+(bi-1)*sNx+I
           jG = myYGlobalLo-1+(bj-1)*sNy+J
           IF (usingSphericalPolarGrid .AND. abs(yC(I,J,bi,bj)).GE.90. )
     &       Ro_surf(I,J,bi,bj) = rF(Nr+1)
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ELSE
       DO bj = myByLo(myThid), myByHi(myThid)
        DO bi = myBxLo(myThid), myBxHi(myThid)
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
           iG = myXGlobalLo-1+(bi-1)*sNx+I
           jG = myYGlobalLo-1+(bj-1)*sNy+J
           IF (usingSphericalPolarGrid .AND. abs(yC(I,J,bi,bj)).GE.90. )
     &       R_low(I,J,bi,bj) = Ro_SeaLevel
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE INI_FIELDS( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER myThid
      IF ( startTime .EQ. baseTime .AND.  nIter0 .EQ. 0
     &     .AND. pickupSuff .EQ. ' ' ) THEN
        CALL INI_VEL( myThid )
        CALL INI_THETA( myThid )
        CALL INI_SALT( myThid )
        CALL INI_PSURF( myThid )
        CALL INI_PRESSURE( myThid )
        IF (nonHydrostatic) CALL INI_PNH( myThid )
      ELSE
        CALL READ_CHECKPOINT( nIter0, myThid )
      ENDIF
      RETURN
      END
      SUBROUTINE INI_FORCING( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE FFIELDS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER  I,  J
      CALL BARRIER(myThid)
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          fu              (i,j,bi,bj) = 0.d0
          fv              (i,j,bi,bj) = 0.d0
          Qnet            (i,j,bi,bj) = 0.d0
          EmPmR           (i,j,bi,bj) = 0.d0
          saltFlux        (i,j,bi,bj) = 0.d0
          SST             (i,j,bi,bj) = 0.d0
          SSS             (i,j,bi,bj) = 0.d0
          Qsw             (i,j,bi,bj) = 0.d0
          surfaceForcingU(i,j,bi,bj) = 0.d0
          surfaceForcingV(i,j,bi,bj) = 0.d0
          surfaceForcingT(i,j,bi,bj) = 0.d0
          surfaceForcingS(i,j,bi,bj) = 0.d0
          surfaceForcingTice(i,j,bi,bj) = 0.d0
          taux0           (i,j,bi,bj) = 0.d0
          taux1           (i,j,bi,bj) = 0.d0
          tauy0           (i,j,bi,bj) = 0.d0
          tauy1           (i,j,bi,bj) = 0.d0
          Qnet0           (i,j,bi,bj) = 0.d0
          Qnet1           (i,j,bi,bj) = 0.d0
          EmPmR0          (i,j,bi,bj) = 0.d0
          EmPmR1          (i,j,bi,bj) = 0.d0
          saltFlux0       (i,j,bi,bj) = 0.d0
          saltFlux1       (i,j,bi,bj) = 0.d0
          SST0            (i,j,bi,bj) = 0.d0
          SST1            (i,j,bi,bj) = 0.d0
          SSS0            (i,j,bi,bj) = 0.d0
          SSS1            (i,j,bi,bj) = 0.d0
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          IF ( doThetaClimRelax .AND. 
     &         abs(yC(i,j,bi,bj)).LE.latBandClimRelax ) THEN
           lambdaThetaClimRelax(I,J,bi,bj) = 1./tauThetaClimRelax
          ELSE
           lambdaThetaClimRelax(I,J,bi,bj) = 0.d0
          ENDIF
          IF ( doSaltClimRelax .AND.
     &         abs(yC(i,j,bi,bj)).LE.latBandClimRelax ) THEN
           lambdaSaltClimRelax(I,J,bi,bj) = 1./tauSaltClimRelax
          ELSE
           lambdaSaltClimRelax(I,J,bi,bj) = 0.d0
          ENDIF
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF ( myThid .EQ. 1 ) THEN
      IF ( zonalWindFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( zonalWindFile, ' ', fu, 0, myThid )
      ENDIF
      IF ( meridWindFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( meridWindFile, ' ', fv, 0, myThid )
      ENDIF
      IF ( surfQFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( surfQFile, ' ', Qnet, 0, myThid )
      ELSEIF ( surfQnetFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( surfQnetFile, ' ', Qnet, 0, myThid )
      ENDIF
      IF ( EmPmRfile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( EmPmRfile, ' ', EmPmR, 0, myThid )
      ENDIF
      IF ( saltFluxFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( saltFluxFile, ' ', saltFlux, 0, myThid )
      ENDIF
      IF ( thetaClimFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( thetaClimFile, ' ', SST, 0, myThid )
      ENDIF
      IF ( saltClimFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( saltClimFile, ' ', SSS, 0, myThid )
      ENDIF
      IF ( lambdaThetaFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( lambdaThetaFile, ' ', 
     &  lambdaThetaClimRelax, 0, myThid )
      ENDIF
      IF ( lambdaSaltFile .NE. ' '  ) THEN
       CALL READ_FLD_XY_RS( lambdaSaltFile, ' ', 
     &  lambdaSaltClimRelax, 0, myThid )
      ENDIF
      ENDIF
      CALL EXCH_XY_RL ( fu   ,  myThid  )
      CALL EXCH_XY_RL ( fv   ,  myThid  )
      CALL EXCH_XY_RL ( Qnet ,  myThid  )
      CALL EXCH_XY_RL ( EmPmR,  myThid  )
      CALL EXCH_XY_RL (  saltFlux,  myThid  )
      CALL EXCH_XY_RL ( SST  ,  myThid  )
      CALL EXCH_XY_RL ( SSS  ,  myThid  )
      CALL EXCH_XY_RL ( lambdaThetaClimRelax ,  myThid  )
      CALL EXCH_XY_RL ( lambdaSaltClimRelax ,  myThid  )
      RETURN
      END
      SUBROUTINE INI_GRID( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER myThid
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      INTEGER i
      CALL LOAD_GRID_SPACING( myThid )
      CALL INI_VERTICAL_GRID( myThid )
      IF ( usingCartesianGrid ) THEN
        CALL INI_CARTESIAN_GRID( myThid )
      ELSEIF ( usingSphericalPolarGrid ) THEN
        CALL INI_SPHERICAL_POLAR_GRID( myThid )
      ELSEIF ( usingCurvilinearGrid ) THEN
        CALL INI_CURVILINEAR_GRID( myThid )
      ELSEIF ( usingCylindricalGrid ) THEN
        CALL INI_CYLINDER_GRID( myThid )
      ELSE
        IF ( myThid .EQ. 1 ) THEN
        WRITE(msgBuf,'(2A)') 'S/R INI_GRID: ',
     &       'No grid coordinate system has been selected'
        CALL PRINT_ERROR( msgBuf , myThid)
        STOP 'ABNORMAL END: S/R INI_GRID'
        ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE INI_LINEAR_PHISURF( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER myThid
      COMMON / LOCAL_INI_PHISURF / topoHloc
      Real*8 topoHloc(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)   
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      INTEGER bi, bj
      INTEGER I, J, K
      Real*8     rhoLoc
      Real*8     dPIdp
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
           Bo_surf(I,J,bi,bj)  = 0.d0
           recip_Bo(I,J,bi,bj) = 0.d0
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF ( buoyancyRelation .eq. 'OCEANIC' ) THEN
        DO bj=myByLo(myThid),myByHi(myThid)
         DO bi=myBxLo(myThid),myBxHi(myThid)
          DO J=1-Oly,sNy+Oly
           DO I=1-Olx,sNx+Olx
             Bo_surf(I,J,bi,bj) = gBaro
             recip_Bo(I,J,bi,bj) = 1.d0 / gBaro
           ENDDO
          ENDDO
         ENDDO
        ENDDO
      ELSEIF ( uniformLin_PhiSurf ) THEN
        DO bj=myByLo(myThid),myByHi(myThid)
         DO bi=myBxLo(myThid),myBxHi(myThid)
          DO J=1-Oly,sNy+Oly
           DO I=1-Olx,sNx+Olx
             Bo_surf(I,J,bi,bj) = recip_rhoConst
             recip_Bo(I,J,bi,bj) = rhoConst
           ENDDO
          ENDDO
         ENDDO
        ENDDO
      ELSEIF ( buoyancyRelation .eq. 'OCEANICP' ) THEN
        DO bj=myByLo(myThid),myByHi(myThid)
         DO bi=myBxLo(myThid),myBxHi(myThid)
          DO J=1-Oly,sNy+Oly
           DO I=1-Olx,sNx+Olx
            IF ( Ro_surf(I,J,bi,bj).GT.0.d0 
     &          .AND. ksurfC(I,J,bi,bj).LE.Nr ) THEN
             k = ksurfC(I,J,bi,bj)
             CALL FIND_RHO_SCALAR( 
     &            tRef(k), sRef(k), Ro_surf(I,J,bi,bj),
     &            rhoLoc, myThid )
             rhoLoc = rhoLoc + rhoConst
             if ( rhoLoc .eq. 0.d0 ) then
              Bo_surf(I,J,bi,bj) = 0.d0
             else
              Bo_surf(I,J,bi,bj) = 1./rhoLoc
             endif
             recip_Bo(I,J,bi,bj) =  rhoLoc
            ELSE
              Bo_surf(I,J,bi,bj)  = 0.d0
              recip_Bo(I,J,bi,bj) = 0.d0
            ENDIF
           ENDDO
          ENDDO
         ENDDO
        ENDDO
      ELSEIF ( buoyancyRelation .eq. 'ATMOSPHERIC' ) THEN
        DO bj=myByLo(myThid),myByHi(myThid)
         DO bi=myBxLo(myThid),myBxHi(myThid)
          DO J=1-Oly,sNy+Oly
           DO I=1-Olx,sNx+Olx
            IF ( Ro_surf(I,J,bi,bj).GT.0.d0 
     &          .AND. ksurfC(I,J,bi,bj).LE.Nr ) THEN
              dPIdp = (atm_Cp*atm_kappa/atm_Po)*
     &         (Ro_surf(I,J,bi,bj)/atm_Po)**(atm_kappa-1.d0)
              Bo_surf(I,J,bi,bj) = dPIdp*tRef(ksurfC(I,J,bi,bj))
              recip_Bo(I,J,bi,bj) = 1.d0 / Bo_surf(I,J,bi,bj)
            ELSE
              Bo_surf(I,J,bi,bj) = 0.
              recip_Bo(I,J,bi,bj) = 0.
            ENDIF
           ENDDO
          ENDDO
         ENDDO
        ENDDO
      ELSE
        STOP 'INI_LINEAR_PHISURF: We should never reach this point!'
      ENDIF
      CALL EXCH_XY_RL ( Bo_surf,  myThid )
      CALL EXCH_XY_RL ( recip_Bo,  myThid )
      IF ( ( buoyancyRelation .eq. 'ATMOSPHERIC' .OR. 
     &       buoyancyRelation .eq. 'OCEANICP'         ) 
     &       .AND. .NOT.uniformLin_PhiSurf              ) THEN
        IF (  myThid  .EQ. 1 ) THEN 
        CALL WRITE_FLD_XY_RL( 'Bo_surf',' ',Bo_surf,0,myThid) 
        ENDIF
      ENDIF
        DO bj=myByLo(myThid),myByHi(myThid)
         DO bi=myBxLo(myThid),myBxHi(myThid)
          DO J=1-Oly,sNy+Oly
           DO I=1-Olx,sNx+Olx
             phi0surf(I,J,bi,bj) = 0.
           ENDDO
          ENDDO
         ENDDO
        ENDDO
      IF ( buoyancyRelation .eq. 'ATMOSPHERIC'
     &                   .AND. topoFile.NE.' ' ) THEN
         STOP 'CANNOT PRESENTLY USE THIS OPTION WITH ADJOINT'
      ENDIF
      RETURN
      END
      SUBROUTINE INI_MASKS_ETC( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER myThid
      COMMON / LOCAL_INI_MASKS_ETC / tmpfld
      Real*8 tmpfld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER bi, bj
      INTEGER  I, J, K
      Real*8 hFacCtmp
      Real*8 hFacMnSz
      Real*8 tileArea
      DO bj=myByLo(myThid), myByHi(myThid)
       DO bi=myBxLo(myThid), myBxHi(myThid)
        DO K=1, Nr
         hFacMnSz=max( hFacMin, min(hFacMinDr*recip_drF(k),1.d0) )
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           hFacCtmp = (rF(K)-R_low(I,J,bi,bj))*recip_drF(K)
           hFacCtmp=min( max( hFacCtmp, 0.d0) , 1.d0)
           IF (hFacCtmp.LT.hFacMnSz) THEN
            IF (hFacCtmp.LT.hFacMnSz*0.5) THEN
             hFacC(I,J,K,bi,bj)=0.
            ELSE
             hFacC(I,J,K,bi,bj)=hFacMnSz
            ENDIF
           ELSE
             hFacC(I,J,K,bi,bj)=hFacCtmp
           ENDIF
          ENDDO
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          R_low(I,J,bi,bj) = rF(1)
          DO K=Nr,1,-1
           R_low(I,J,bi,bj) = R_low(I,J,bi,bj)
     &                      - drF(k)*hFacC(I,J,K,bi,bj)
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      DO bj=myByLo(myThid), myByHi(myThid)
       DO bi=myBxLo(myThid), myBxHi(myThid)
        DO K=1, Nr
         hFacMnSz=max( hFacMin, min(hFacMinDr*recip_drF(k),1.d0) )
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           hFacCtmp = (rF(k)-Ro_surf(I,J,bi,bj))*recip_drF(K)
           hFacCtmp = hFacC(I,J,K,bi,bj) - max( hFacCtmp, 0.d0)
           hFacCtmp = max( hFacCtmp, 0.d0)
           IF (hFacCtmp.LT.hFacMnSz) THEN
            IF (hFacCtmp.LT.hFacMnSz*0.5) THEN
             hFacC(I,J,K,bi,bj)=0.
            ELSE
             hFacC(I,J,K,bi,bj)=hFacMnSz
            ENDIF
           ELSE
             hFacC(I,J,K,bi,bj)=hFacCtmp
           ENDIF
          ENDDO
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          tmpfld(I,J,bi,bj) = 0.
          ksurfC(I,J,bi,bj) = Nr+1
          maskH(i,j,bi,bj) = 0.
          Ro_surf(I,J,bi,bj) = R_low(I,J,bi,bj)
          DO K=Nr,1,-1
           Ro_surf(I,J,bi,bj) = Ro_surf(I,J,bi,bj)
     &                        + drF(k)*hFacC(I,J,K,bi,bj)
           IF (hFacC(I,J,K,bi,bj).NE.0.) THEN
            ksurfC(I,J,bi,bj) = k
            maskH(i,j,bi,bj) = 1.
            tmpfld(i,j,bi,bj) = tmpfld(i,j,bi,bj) + 1.
           ENDIF
          ENDDO
          kLowC(I,J,bi,bj) = 0
          DO K= 1, Nr
           IF (hFacC(I,J,K,bi,bj).NE.0) THEN
              kLowC(I,J,bi,bj) = K
           ENDIF
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      CALL PLOT_FIELD_XYRS(R_low, 
     &         'Model R_low (ini_masks_etc)', 1, myThid)
      CALL PLOT_FIELD_XYRS(Ro_surf, 
     &         'Model Ro_surf (ini_masks_etc)', 1, myThid)
      globalArea = 0.d0
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1-Oly,sNy+Oly
         DO i=1-Olx,sNx+Olx
          tmpfld(i,j,bi,bj) = Ro_surf(i,j,bi,bj) - R_low(i,j,bi,bj)
          IF ( tmpfld(i,j,bi,bj) .LE. 0. ) THEN
           recip_Rcol(i,j,bi,bj) = 0.
          ELSE
           recip_Rcol(i,j,bi,bj) = 1. / tmpfld(i,j,bi,bj)
          ENDIF
         ENDDO
        ENDDO
        tileArea = 0.d0
        DO j=1,sNy
         DO i=1,sNx
          tileArea = tileArea + rA(i,j,bi,bj)*maskH(i,j,bi,bj)
         ENDDO
        ENDDO
        globalArea = globalArea + tileArea
       ENDDO
      ENDDO
      CALL GLOBAL_SUM_R8 (  globalArea,  myThid  )
      DO bj=myByLo(myThid), myByHi(myThid)
       DO bi=myBxLo(myThid), myBxHi(myThid)
        DO K=1, Nr
         DO J=1-Oly,sNy+Oly
          DO I=2-Olx,sNx+Olx
           hFacW(I,J,K,bi,bj)=
     &       MIN(hFacC(I,J,K,bi,bj),hFacC(I-1,J,K,bi,bj))
          ENDDO
         ENDDO
         DO J=2-Oly,sNy+oly
          DO I=1-Olx,sNx+Olx
           hFacS(I,J,K,bi,bj)=
     &       MIN(hFacC(I,J,K,bi,bj),hFacC(I,J-1,K,bi,bj))
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      CALL EXCH_UV_XYZ_RS(hFacW,hFacS,.FALSE.,myThid)
      DO bj=myByLo(myThid), myByHi(myThid)
       DO bi=myBxLo(myThid), myBxHi(myThid)
        DO K=1, Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           IF (DYG(I,J,bi,bj).EQ.0.) hFacW(I,J,K,bi,bj)=0.
           IF (DXG(I,J,bi,bj).EQ.0.) hFacS(I,J,K,bi,bj)=0.
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      CALL BARRIER(myThid)
      CALL PLOT_FIELD_XYZRS( hFacC, 'hFacC' , Nr, 1, myThid )
      CALL PLOT_FIELD_XYZRS( hFacW, 'hFacW' , Nr, 1, myThid )
      CALL PLOT_FIELD_XYZRS( hFacS, 'hFacS' , Nr, 1, myThid )
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO K=1,Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           IF (HFacC(I,J,K,bi,bj) .NE. 0. ) THEN
            recip_HFacC(I,J,K,bi,bj) = 1. / HFacC(I,J,K,bi,bj)
            maskC(I,J,K,bi,bj) = 1.
           ELSE
            recip_HFacC(I,J,K,bi,bj) = 0.
            maskC(I,J,K,bi,bj) = 0.
           ENDIF
           IF (HFacW(I,J,K,bi,bj) .NE. 0. ) THEN
            recip_HFacW(I,J,K,bi,bj) = 1. / HFacW(I,J,K,bi,bj)
            maskW(I,J,K,bi,bj) = 1.
           ELSE
            recip_HFacW(I,J,K,bi,bj) = 0.
            maskW(I,J,K,bi,bj) = 0.
           ENDIF
           IF (HFacS(I,J,K,bi,bj) .NE. 0. ) THEN
            recip_HFacS(I,J,K,bi,bj) = 1. / HFacS(I,J,K,bi,bj)
            maskS(I,J,K,bi,bj) = 1.
           ELSE
            recip_HFacS(I,J,K,bi,bj) = 0.
            maskS(I,J,K,bi,bj) = 0.
           ENDIF
          ENDDO
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          ksurfW(I,J,bi,bj) = Nr+1
          ksurfS(I,J,bi,bj) = Nr+1
          DO k=Nr,1,-1
           IF (hFacW(I,J,K,bi,bj).NE.0.) ksurfW(I,J,bi,bj) = k
           IF (hFacS(I,J,K,bi,bj).NE.0.) ksurfS(I,J,bi,bj) = k
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          IF ( dxG(I,J,bi,bj) .NE. 0. )
     &    recip_dxG(I,J,bi,bj)=1.d0/dxG(I,J,bi,bj)
          IF ( dyG(I,J,bi,bj) .NE. 0. )
     &    recip_dyG(I,J,bi,bj)=1.d0/dyG(I,J,bi,bj)
          IF ( dxC(I,J,bi,bj) .NE. 0. )
     &    recip_dxC(I,J,bi,bj)=1.d0/dxC(I,J,bi,bj)
          IF ( dyC(I,J,bi,bj) .NE. 0. )
     &    recip_dyC(I,J,bi,bj)=1.d0/dyC(I,J,bi,bj)
          IF ( dxF(I,J,bi,bj) .NE. 0. )
     &    recip_dxF(I,J,bi,bj)=1.d0/dxF(I,J,bi,bj)
          IF ( dyF(I,J,bi,bj) .NE. 0. )
     &    recip_dyF(I,J,bi,bj)=1.d0/dyF(I,J,bi,bj)
          IF ( dxV(I,J,bi,bj) .NE. 0. )
     &    recip_dxV(I,J,bi,bj)=1.d0/dxV(I,J,bi,bj)
          IF ( dyU(I,J,bi,bj) .NE. 0. )
     &    recip_dyU(I,J,bi,bj)=1.d0/dyU(I,J,bi,bj)
          IF ( rA(I,J,bi,bj) .NE. 0. )
     &    recip_rA(I,J,bi,bj)=1.d0/rA(I,J,bi,bj)
          IF ( rAs(I,J,bi,bj) .NE. 0. )
     &    recip_rAs(I,J,bi,bj)=1.d0/rAs(I,J,bi,bj)
          IF ( rAw(I,J,bi,bj) .NE. 0. )
     &    recip_rAw(I,J,bi,bj)=1.d0/rAw(I,J,bi,bj)
          IF ( rAz(I,J,bi,bj) .NE. 0. )
     &    recip_rAz(I,J,bi,bj)=1.d0/rAz(I,J,bi,bj)
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE INI_MIXING( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER i, j, k
       DO bj = myByLo(myThid), myByHi(myThid)
        DO bi = myBxLo(myThid), myBxHi(myThid)
         DO k=1,Nr
          DO j=1,sNy
           DO i=1,sNx
            diffKr(i,j,k,bi,bj) = diffKrNrS(k)
           ENDDO
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      CALL EXCH_XYZ_RL ( diffKr ,  myThid  )
      RETURN
      END
      SUBROUTINE INI_P_GROUND(selectMode, 
     &                        Hfld, Pfld, 
     I                        myThid )
       USE SIZE_mod
       USE GRID_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE SURFACE_mod
      INTEGER selectMode
      Real*8 Hfld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      Real*8 Pfld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      INTEGER myThid
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      INTEGER bi,bj,i,j,K, Ks
      Real*8 ddPI, Po_surf
      Real*8 phiRef(2*Nr+1), rHalf(2*Nr+1)
      LOGICAL findPoSurf
      INTEGER nLevHvR
      PARAMETER ( nLevHvR = 60 )
      Real*8 plowHvR, dpHvR, pLevHvR(nLevHvR+1), pMidHvR(nLevHvR)
      Real*8 thetaHvR(nLevHvR), PiHvR(nLevHvR+1), dPiHvR(nLevHvR)
      Real*8 recip_kappa, PiLoc, zLoc, dzLoc, yLatLoc, phiLoc
      Real*8  psNorm, rMidKp1 
      Real*8 ratioRm(Nr), ratioRp(Nr)
      INTEGER kLev
      IF ( selectFindRoSurf.LT.0 .OR. selectFindRoSurf.GT.1 ) THEN
        WRITE(msgBuf,'(A,I2,A)')
     &   'INI_P_GROUND: selectFindRoSurf =', selectFindRoSurf,
     &        ' <== bad value !'
        CALL PRINT_ERROR( msgBuf , myThid)
        STOP 'INI_P_GROUND' 
      ENDIF
      DO K=1,Nr
        rHalf(2*K-1) = rF(K)
        rHalf(2*K)   = rC(K)
      ENDDO
       rHalf(2*Nr+1) = rF(Nr+1)
      IF (selectMode*selectFindRoSurf .LE. 0) THEN
      phiRef(1) = 0. 
      IF (integr_GeoPot.EQ.1) THEN
        DO K=1,2*Nr
          Ks = (K+1)/2
          ddPI=atm_Cp*( ((rHalf( K )/atm_Po)**atm_kappa)
     &                 -((rHalf(K+1)/atm_Po)**atm_kappa) ) 
          phiRef(K+1) = phiRef(K)+ddPI*tRef(Ks)
        ENDDO
      ELSE
        K = 1
          ddPI=atm_Cp*( ((rF(K)/atm_Po)**atm_kappa)
     &                 -((rC(K)/atm_Po)**atm_kappa) ) 
          phiRef(2*K)   = phiRef(1) + ddPI*tRef(K) 
        DO K=1,Nr-1
          ddPI=atm_Cp*( ((rC( K )/atm_Po)**atm_kappa)
     &                 -((rC(K+1)/atm_Po)**atm_kappa) ) 
          phiRef(2*K+1) = phiRef(2*K) + ddPI*0.5*tRef(K)
          phiRef(2*K+2) = phiRef(2*K)
     &                  + ddPI*0.5*(tRef(K)+tRef(K+1)) 
        ENDDO
        K = Nr
          ddPI=atm_Cp*( ((rC( K )/atm_Po)**atm_kappa)
     &                 -((rF(K+1)/atm_Po)**atm_kappa) ) 
          phiRef(2*K+1) = phiRef(2*K) + ddPI*tRef(K)
       ENDIF
      DO K=1,2*Nr+1
        phiRef(K) = phiRef(K)*recip_gravity
      ENDDO
      IF (  myThid  .EQ. 1 ) THEN
      WRITE(standardMessageUnit,'(2A)') 
     &  'INI_P_GROUND: PhiRef/g [m] at Center (integer) ',
     &  'and Interface (half-int.) levels:'
      DO K=1,2*Nr+1
        WRITE(standardMessageUnit,'(A,F5.1,A,F10.1,A,F12.3)')
     &    '  K=',K*0.5,'  ;  r=',rHalf(K),'  ;  phiRef/g=', phiRef(K)
      ENDDO
      ENDIF
      ENDIF
      IF (selectFindRoSurf.EQ.0 .AND. selectMode .GT. 0 ) THEN
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1,sNy
         DO i=1,sNx
           Ks = 1
           DO K=1,2*Nr
             IF (Hfld(i,j,bi,bj).GE.phiRef(K)) Ks = K 
           ENDDO
           Po_surf = rHalf(Ks) + (rHalf(Ks+1)-rHalf(Ks))*
     &       (Hfld(i,j,bi,bj)-phiRef(Ks))/(phiRef(Ks+1)-phiRef(Ks))
           Pfld(i,j,bi,bj) = Po_surf
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      ENDIF
      IF ( selectFindRoSurf.EQ.1 ) THEN
      recip_kappa = 1.d0 / atm_kappa
      plowHvR = 0.4d0
      dpHvR = nLevHvR
      dpHvR = (1. - plowHvR) / dpHvR
        pLevHvR(1)= Ro_SeaLevel/atm_Po
        PiHvR(1) = atm_Cp*(pLevHvR(1)**atm_kappa)
      DO k=1,nLevHvR
        pLevHvR(k+1)= pLevHvR(1) - float(k)*dpHvR
        PiHvR(k+1)  = atm_Cp*(pLevHvR(k+1)**atm_kappa)
        pMidHvR(k)= (pLevHvR(k)+pLevHvR(k+1))*0.5d0 
        dPiHvR(k) = PiHvR(k) - PiHvR(k+1)
      ENDDO
      DO k=1,Nr
         ratioRm(k) = 1.d0
         ratioRp(k) = 1.d0
         IF (k.GT.1 ) ratioRm(k) = 0.5d0*drC(k)/(rF(k)-rC(k))
         IF (k.LT.Nr) ratioRp(k) = 0.5d0*drC(k+1)/(rC(k)-rF(k+1)) 
      ENDDO
      ENDIF
      IF ( selectFindRoSurf*selectMode .GT. 0) THEN
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1,sNy
         DO i=1,sNx
          IF ( Hfld(i,j,bi,bj) .LE. 0.d0) THEN
           Pfld(i,j,bi,bj) = Ro_SeaLevel
          ELSE
           yLatLoc  = yC(i,j,bi,bj)
           CALL ANALYLIC_THETA( yLatLoc , pMidHvR,
     &                       thetaHvR, nLevHvR, mythid)
           zLoc = 0.
           DO k=1,nLevHvR 
            IF (zLoc.GE.0.) THEN
             dzLoc = dPiHvR(k)*thetaHvR(k)*recip_gravity 
             IF ( Hfld(i,j,bi,bj) .LE. zLoc+dzLoc ) THEN
               PiLoc = PiHvR(k) 
     &               - gravity*(Hfld(i,j,bi,bj)-zLoc)/thetaHvR(k)
               psNorm = (PiLoc/atm_Cp)**recip_kappa 
               zLoc = -1.
             ELSE
               zLoc = zLoc + dzLoc 
             ENDIF
            ENDIF
           ENDDO
           IF (zLoc.GE.0.) THEN
             WRITE(msgBuf,'(2A)')
     &        'INI_P_GROUND: FAIL in trying to find Pfld:',
     &        ' selectMode,i,j,bi,bj=',selectMode,i,j,bi,bj
             CALL PRINT_ERROR( msgBuf , myThid)
             WRITE(msgBuf,'(A,F7.1,2A,F6.4,A,F8.0)')
     &        'INI_P_GROUND: Hfld=', Hfld(i,j,bi,bj), ' exceeds',
     &        ' Zloc(lowest P=', pLevHvR(1+nLevHvR),' )=',zLoc
             CALL PRINT_ERROR( msgBuf , myThid)
             STOP 'ABNORMAL END: S/R INI_P_GROUND'  
           ELSE
             Pfld(i,j,bi,bj) = psNorm*atm_Po
           ENDIF
          ENDIF
         ENDDO
        ENDDO
        IF (selectMode.EQ.2 .AND. integr_GeoPot.NE.1) THEN
          DO j=1,sNy
           DO i=1,sNx
             Po_surf = Pfld(i,j,bi,bj)
              IF ( Po_surf.LT.rC(1) .AND. Po_surf.GT.rC(Nr) ) THEN
                findPoSurf = .TRUE.
                DO k=1,Nr
                  IF ( findPoSurf .AND. Po_surf.GE.rC(k) ) THEN
                    Po_surf = rC(k) + (Po_surf-rC(k))/ratioRm(k)
                    findPoSurf = .FALSE.
                  ENDIF
                  rMidKp1 = rF(k+1)
                  IF (k.LT.Nr) rMidKp1 = (rC(k)+rC(k+1))*0.5d0 
                  IF ( findPoSurf .AND. Po_surf.GE.rMidKp1 ) THEN
                    Po_surf = rC(k) + (Po_surf-rC(k))/ratioRp(k)
                    findPoSurf = .FALSE.
                  ENDIF
                ENDDO
                IF ( findPoSurf ) 
     &               STOP 'S/R INI_P_GROUND: Pb with selectMode=2'
              ENDIF 
             Pfld(i,j,bi,bj) = Po_surf
           ENDDO
          ENDDO
        ENDIF
       ENDDO
      ENDDO
      ENDIF
      IF (selectMode .LT. 0) THEN
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO j=1,sNy
         DO i=1,sNx
          ks = ksurfC(i,j,bi,bj)
          IF (ks.LE.Nr) THEN
           IF ( Pfld(i,j,bi,bj).GE.rC(ks) ) THEN
            phiLoc = phiRef(2*ks)
     &       + (phiRef(2*ks-1)-phiRef(2*ks))
     &        *(Pfld(i,j,bi,bj)-rC(ks))/(rHalf(2*ks-1)-rHalf(2*ks))
           ELSE
            phiLoc = phiRef(2*ks)
     &       + (phiRef(2*ks+1)-phiRef(2*ks))
     &        *(Pfld(i,j,bi,bj)-rC(ks))/(rHalf(2*ks+1)-rHalf(2*ks))
           ENDIF
           Hfld(i,j,bi,bj) = phiLoc
          ELSE
           Hfld(i,j,bi,bj) = 0.
          ENDIF
         ENDDO
        ENDDO
        IF (selectFindRoSurf.EQ.1) THEN
         DO j=1,sNy
          DO i=1,sNx
           zLoc = 0.
           IF ( Pfld(i,j,bi,bj) .LT. Ro_SeaLevel) THEN
            Po_surf = Pfld(i,j,bi,bj)
             IF (selectMode.EQ.-2 .AND. integr_GeoPot.NE.1) THEN
              IF ( Po_surf.LT.rC(1) .AND. Po_surf.GT.rC(Nr) ) THEN
                findPoSurf = .TRUE.
                DO k=1,Nr
                  IF ( findPoSurf .AND. Po_surf.GE.rC(k) ) THEN
                    Po_surf = rC(k) + (Po_surf-rC(k))*ratioRm(k)
                    findPoSurf = .FALSE.
                  ENDIF
                  IF ( findPoSurf .AND. Po_surf.GE.rF(k+1) ) THEN
                    Po_surf = rC(k) + (Po_surf-rC(k))*ratioRp(k)
                    findPoSurf = .FALSE.
                  ENDIF
                ENDDO
              ENDIF 
             ENDIF 
            psNorm = Po_surf/atm_Po
            kLev = 1 + INT( (pLevHvR(1)-psNorm)/dpHvR )
            yLatLoc  = yC(i,j,bi,bj)
            CALL ANALYLIC_THETA( yLatLoc , pMidHvR,
     &                        thetaHvR, kLev, mythid)
            DO k=1,kLev-1
              dzLoc = dPiHvR(k)*thetaHvR(k)*recip_gravity 
              zLoc = zLoc + dzLoc
            ENDDO
            dzLoc = ( PiHvR(kLev)-atm_Cp*(psNorm**atm_kappa) )
     &            * thetaHvR(kLev)*recip_gravity 
            zLoc = zLoc + dzLoc
           ENDIF
           phi0surf(i,j,bi,bj) = gravity*(zLoc - Hfld(i,j,bi,bj))
           Hfld(i,j,bi,bj) = zLoc
          ENDDO
         ENDDO
        ENDIF
       ENDDO
      ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE ANALYLIC_THETA( yLat, pNlev,
     O                           thetaLev,
     I                           kSize,myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER kSize
      Real*8  yLat
      Real*8  pNlev  (kSize)
      Real*8  thetaLev(kSize)
      INTEGER myThid
      INTEGER k
      Real*8  yyA, yyB, yyC, yyAd, yyBd, yyCd
      Real*8  cAtmp, cBtmp, ttdC
      Real*8  ppN0, ppN1, ppN2, ppN3a, ppN3b, ppN4 
      Real*8  ttp1, ttp2, ttp3, ttp4, ttp5
      Real*8  yAtmp, yBtmp, yCtmp, yDtmp
      Real*8  ttp2y, ttp4y, a1tmp 
      Real*8  ppl, ppm, pph, ppr
      DATA yyA ,    yyB ,     yyC ,     yyAd ,   yyBd ,   yyCd
     &  / 45.d0, 65.d0, 65.d0, .9d0, .9d0, 10.d0 /
      DATA  cAtmp ,   cBtmp ,   ttdC
     &   /  2.6d0, 1.5d0, 3.3d0 /
      DATA  ppN0  ,   ppN1  ,  ppN2  ,  ppN3a ,  ppN3b ,  ppN4 
     &   / .1d0, .19d0, .3d0, .9d0, .7d0, .925d0 /
      DATA ttp1 ,     ttp2 ,     ttp3 ,     ttp4 ,     ttp5
     &   / 350.d0, 342.d0, 307.d0, 301.d0, 257.d0 /
       yAtmp = ABS(yLat) - yyA
       yAtmp = yyA + MIN(0.d0,yAtmp/yyAd) + MAX(yAtmp, 0.d0)
       yAtmp = COS( deg2rad*MAX(yAtmp, 0.d0) )
       yBtmp = ABS(yLat) - yyB
       yBtmp = yyB + yBtmp/yyBd
       yBtmp = COS( deg2rad*MAX( 0.d0, MIN(yBtmp,90.d0) ) )
       yCtmp = ABS(yLat) - yyC
       yCtmp = MAX( 0.d0, 1.d0 - (yCtmp/yyCd)**2 )
       yDtmp = ppN3a +(ppN3b - ppN3a)*yCtmp
       ttp2y = ttp3 + (ttp2-ttp3)*yAtmp**cAtmp
       ttp4y = ttp5 + (ttp4-ttp5)*yBtmp**cBtmp
       a1tmp = (ttp1-ttp2y)*ppN1*ppN2/(ppN2-ppN1)
      DO k=1,kSize
       ppl = MIN(pNlev(k),ppN1)
       ppm = MIN(MAX(pNlev(k),ppN1),ppN2)
       pph = MAX(pNlev(k),ppN2)
       ppr =( ppN0 + ABS(ppl-ppN0) - ppN1 )/(ppN2-ppN1)
       thetaLev(k) = 
     &       ( (1.d0 -ppr)*ttp1*ppN1**atm_kappa
     &        + ppr*ttp2y*ppN2**atm_kappa
     &       )*ppl**(-atm_kappa)
     &     + a1tmp*(1.d0 /ppm - 1.d0/ppN1)
     &     + (ttp4y-ttp2y)*(pph-ppN2)/(ppN4-ppN2) 
     &     + (ttdC+yCtmp)*MAX(0.d0,pNlev(k)-yDtmp)/(1-yDtmp)
      ENDDO
      RETURN
      END
      SUBROUTINE INI_PRESSURE( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE EOS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER  I,  J, K
      INTEGER  iMin, iMax, jMin, jMax, npiter
      Real*8 PhiHydF (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 PhiHydC (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 dPhiHydX(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 dPhiHydY(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 oldPhi  (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 count, rmspp, rmsppold 
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      iMin = 1-OLx
      iMax = sNx+OLx
      jMin = 1-OLy
      jMax = sNy+OLy
      WRITE(msgBuf,'(a)')
     &     'Start initial hydrostatic pressure computation'
      CALL PRINT_MESSAGE( msgBuf, standardMessageUnit, 
     &     SQUEEZE_RIGHT , 1)
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO k = 1,Nr
         DO j=1-OLy,sNy+OLy
          DO i=1-OLx,sNx+OLx
           totPhiHyd(i,j,k,bi,bj) = 0.d0
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF ( useDynP_inEos_Zc ) THEN
      ELSE
       WRITE(msgBuf,'(A,A)')
     &        'Pressure is predetermined for buoyancyRelation ',
     &        buoyancyRelation(1:11)
       CALL PRINT_MESSAGE( msgBuf, standardMessageUnit, 
     &      SQUEEZE_RIGHT , 1)
      ENDIF
      WRITE(msgBuf,'(A)') ' '
      CALL PRINT_MESSAGE( msgBuf, standardMessageUnit, 
     &     SQUEEZE_RIGHT , 1)
      RETURN 
      END
      SUBROUTINE INI_PNH( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      INTEGER bi,bj,I,J,K
      RETURN
      END
      SUBROUTINE INI_PSURF( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE SURFACE_mod
       USE CD_CODE_VARS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER  I,  J
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          etaN(I,J,bi,bj) = 0.d0
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF (pSurfInitFile .NE. ' ') THEN
       IF (  myThid  .EQ. 1 ) THEN
       CALL READ_FLD_XY_RL( pSurfInitFile, ' ', etaN, 0, myThid )
       ENDIF
      ENDIF
      CALL EXCH_XY_RL ( etaN,  myThid )
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          etaNm1(I,J,bi,bj) = etaN(I,J,bi,bj)
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE INI_SALT ( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER I, J, K, localWarnings
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO K=1,Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           salt(I,J,K,bi,bj) = sRef(K)
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF ( hydrogSaltFile .NE. ' ' ) THEN
       IF (  myThid  .EQ. 1 ) THEN
       CALL READ_FLD_XYZ_RL( hydrogSaltFile, ' ', salt, 0, myThid )
       ENDIF
       CALL EXCH_XYZ_RL ( salt  ,  myThid  )
      ENDIF
      localWarnings=0
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO K=1,Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           IF (maskC(I,J,K,bi,bj).EQ.0.) salt(I,J,K,bi,bj) = 0.
          ENDDO
         ENDDO
         IF ( sRef(k).NE.0. ) THEN
          DO J=1,sNy
           DO I=1,sNx
            IF ( maskC(I,J,K,bi,bj).NE.0.
     &      .AND. salt(I,J,K,bi,bj).EQ.0. ) THEN
              localWarnings=localWarnings+1
            ENDIF
           ENDDO
          ENDDO
         ENDIF
        ENDDO
       ENDDO
      ENDDO
      IF (localWarnings.NE.0) THEN
       WRITE(msgBuf,'(A,A)')
     &  'S/R INI_SALT: salt = 0 identically. If this is intentional',
     &  'you will need to edit ini_salt.F to avoid this safety check'
       CALL PRINT_ERROR( msgBuf , myThid)
       STOP 'ABNORMAL END: S/R INI_SALT'
      ENDIF
      CALL PLOT_FIELD_XYZRL( salt, 'Initial Salinity' , Nr, 1, myThid )
      RETURN
      END
      SUBROUTINE INI_SPHERICAL_POLAR_GRID( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER myThid
      INTEGER iG, jG
      INTEGER bi, bj
      INTEGER  I,  J
      Real*8 lat, dlat, dlon, xG0, yG0
      Real*8 xGloc(1-Olx:sNx+Olx+1,1-Oly:sNy+Oly+1)
      Real*8 yGloc(1-Olx:sNx+Olx+1,1-Oly:sNy+Oly+1)
      INTEGER iGl,jGl
      iGl(I,bi) = 1+mod(myXGlobalLo-1+(bi-1)*sNx+I+Olx*Nx-1,Nx)
      jGl(J,bj) = 1+mod(myYGlobalLo-1+(bj-1)*sNy+J+Oly*Ny-1,Ny)
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        jG = myYGlobalLo + (bj-1)*sNy
        iG = myXGlobalLo + (bi-1)*sNx
        xG0 = thetaMin
        DO i=1, iG-1
         xG0 = xG0 + delX(i)
        ENDDO
        DO i=1, Olx
         xG0 = xG0 - delX( 1+mod(Olx*Nx-1+iG-i,Nx) )
        ENDDO
        yG0 = phiMin
        DO j=1, jG-1
         yG0 = yG0 + delY(j)
        ENDDO
        DO j=1, Oly
         yG0 = yG0 - delY( 1+mod(Oly*Ny-1+jG-j,Ny) )
        ENDDO
        DO J=1-Oly,sNy+Oly +1
         xGloc(1-Olx,J) = xG0
         DO I=1-Olx,sNx+Olx
          xGloc(I+1,J) = xGloc(I,J) + delX( iGl(I,bi) )
         ENDDO
        ENDDO
        DO I=1-Olx,sNx+Olx +1
         yGloc(I,1-Oly) = yG0
         DO J=1-Oly,sNy+Oly
          yGloc(I,J+1) = yGloc(I,J) + delY( jGl(J,bj) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          xG(I,J,bi,bj) = xGloc(I,J)
          yG(I,J,bi,bj) = yGloc(I,J)
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          xC(I,J,bi,bj) = 0.25*( 
     &     xGloc(I,J)+xGloc(I+1,J)+xGloc(I,J+1)+xGloc(I+1,J+1) )
          yC(I,J,bi,bj) = 0.25*( 
     &     yGloc(I,J)+yGloc(I+1,J)+yGloc(I,J+1)+yGloc(I+1,J+1) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          lat = yC(I,J,bi,bj)
          dlon = delX( iGl(I,bi) )
          dlat = delY( jGl(J,bj) )
          dXF(I,J,bi,bj) = rSphere*COS(deg2rad*lat)*dlon*deg2rad
          dYF(I,J,bi,bj) = rSphere*dlat*deg2rad
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          lat = 0.5*(yGloc(I,J)+yGloc(I+1,J))
          dlon = delX( iGl(I,bi) )
          dlat = delY( jGl(J,bj) )
          dXG(I,J,bi,bj) = rSphere*COS(deg2rad*lat)*dlon*deg2rad
          if (dXG(I,J,bi,bj).LT.1.) dXG(I,J,bi,bj)=0.
          dYG(I,J,bi,bj) = rSphere*dlat*deg2rad
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          dXC(I,J,bi,bj) = 0.
          dYC(I,J,bi,bj) = 0.
          dXV(I,J,bi,bj) = 0.
          dYU(I,J,bi,bj) = 0.
          rAw(I,J,bi,bj) = 0.
          rAs(I,J,bi,bj) = 0.
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx+1,sNx+Olx ! NOTE range
          dXC(I,J,bi,bj) = 0.5d0*(dXF(I,J,bi,bj)+dXF(I-1,J,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly+1,sNy+Oly ! NOTE range
         DO I=1-Olx,sNx+Olx
          dYC(I,J,bi,bj) = 0.5*(dYF(I,J,bi,bj)+dYF(I,J-1,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly+1,sNy+Oly ! NOTE range
         DO I=1-Olx+1,sNx+Olx ! NOTE range
          dXV(I,J,bi,bj) = 0.5*(dXG(I,J,bi,bj)+dXG(I-1,J,bi,bj))
          dYU(I,J,bi,bj) = 0.5*(dYG(I,J,bi,bj)+dYG(I,J-1,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          lat=0.5*(yGloc(I,J)+yGloc(I+1,J))
          dlon=delX( iGl(I,bi) )
          dlat=delY( jGl(J,bj) )
          rA(I,J,bi,bj) = rSphere*rSphere*dlon*deg2rad
     &        *abs( sin((lat+dlat)*deg2rad)-sin(lat*deg2rad) )
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx+1,sNx+Olx ! NOTE range
          rAw(I,J,bi,bj) = 0.5*(rA(I,J,bi,bj)+rA(I-1,J,bi,bj))
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          lat=yC(I,J,bi,bj)
          dlon=delX( iGl(I,bi) )
          dlat=0.5*( delY( jGl(J,bj) ) + delY( jGl(J-1,bj) ) )
          rAs(I,J,bi,bj) = rSphere*rSphere*dlon*deg2rad
     &        *abs( sin(lat*deg2rad)-sin((lat-dlat)*deg2rad) )
          IF (abs(lat).GT.90..OR.abs(lat-dlat).GT.90.) rAs(I,J,bi,bj)=0.
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          lat =0.5d0*(yGloc(I,J)+yGloc(I,J+1))
          dlon=0.5d0*( delX( iGl(I,bi) ) + delX( iGl(I-1,bi) ) )
          dlat=0.5d0*( delY( jGl(J,bj) ) + delY( jGl(J-1,bj) ) )
          rAz(I,J,bi,bj) = rSphere*rSphere*dlon*deg2rad
     &     *abs( sin(lat*deg2rad)-sin((lat-dlat)*deg2rad) )
          IF (abs(lat).GT.90..OR.abs(lat-dlat).GT.90.) rAz(I,J,bi,bj)=0.
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          lat=0.5*(yGloc(I,J)+yGloc(I,J+1))
          tanPhiAtU(I,J,bi,bj)=tan(lat*deg2rad)
          lat=0.5*(yGloc(I,J)+yGloc(I+1,J))
          tanPhiAtV(I,J,bi,bj)=tan(lat*deg2rad)
          angleCosC(I,J,bi,bj) = 1.
          angleSinC(I,J,bi,bj) = 0.
         ENDDO
        ENDDO
        DO J=1-OLy,sNy+OLy
         jG = myYGlobalLo + (bj-1)*sNy + J-1
         jG = min(max(1,jG),Ny)
         IF (cosPower.NE.0.) THEN
          cosFacU(J,bi,bj)=COS(yC(1,J,bi,bj)*deg2rad)
     &                    **cosPower
          cosFacV(J,bi,bj)=COS((yC(1,J,bi,bj)-0.5*delY(jG))*deg2rad)
     &                    **cosPower
          cosFacU(J,bi,bj)=ABS(cosFacU(J,bi,bj))
          cosFacV(J,bi,bj)=ABS(cosFacV(J,bi,bj))
          sqcosFacU(J,bi,bj)=sqrt(cosFacU(J,bi,bj))
          sqcosFacV(J,bi,bj)=sqrt(cosFacV(J,bi,bj))
         ELSE
          cosFacU(J,bi,bj)=1.
          cosFacV(J,bi,bj)=1.
          sqcosFacU(J,bi,bj)=1.
          sqcosFacV(J,bi,bj)=1.
         ENDIF
        ENDDO
       ENDDO ! bi
      ENDDO ! bj
      RETURN
      END
      SUBROUTINE INI_THETA( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER I, J, K, localWarnings
      Real*8     Tfreezing
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO K=1,Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           theta(I,J,K,bi,bj) = tRef(K)
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF ( hydrogThetaFile .NE. ' ' ) THEN
       IF (  myThid  .EQ. 1 ) THEN
       CALL READ_FLD_XYZ_RL( hydrogThetaFile, ' ', theta, 0, myThid )
       ENDIF
       CALL EXCH_XYZ_RL ( theta, myThid )
      ENDIF
      localWarnings=0
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO K=1,Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           IF (maskC(I,J,K,bi,bj).EQ.0.) theta(I,J,K,bi,bj) = 0.
          ENDDO
         ENDDO
         IF ( tRef(k).NE.0. ) THEN
          DO J=1,sNy
           DO I=1,sNx
            IF (  maskC(I,J,K,bi,bj).NE.0.
     &      .AND. theta(I,J,K,bi,bj).EQ.0. ) THEN
              localWarnings=localWarnings+1
            ENDIF
           ENDDO
          ENDDO
         ENDIF
        ENDDO
       ENDDO
      ENDDO
      IF (localWarnings.NE.0) THEN
       WRITE(msgBuf,'(A,A)')
     &  'S/R INI_THETA: theta = 0 identically. If this is intentional',
     &  'you will need to edit ini_theta.F to avoid this safety check'
       CALL PRINT_ERROR( msgBuf , myThid)
       STOP 'ABNORMAL END: S/R INI_THETA'
      ENDIF
      Tfreezing=-1.9d0
      IF ( allowFreezing ) THEN
       DO bj = myByLo(myThid), myByHi(myThid)
        DO bi = myBxLo(myThid), myBxHi(myThid)
         DO K=1,Nr
          DO J=1-Oly,sNy+Oly
           DO I=1-Olx,sNx+Olx
            IF (theta(I,J,k,bi,bj) .LT. Tfreezing) THEN
               theta(I,J,K,bi,bj) = Tfreezing
            ENDIF
           ENDDO
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDIF
      CALL PLOT_FIELD_XYZRL( theta, 'Initial Temperature' ,
     &                       Nr, 1, myThid )
      RETURN
      END
      SUBROUTINE INI_DYNVARS( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
      INTEGER myThid
      INTEGER bi, bj
      INTEGER  I,  J, K
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO K=1,Nr
         DO J=1-Oly,sNy+Oly
          DO I=1-Olx,sNx+Olx
           uVel(I,J,K,bi,bj)=0.d0
           vVel(I,J,K,bi,bj)=0.d0
           wVel(I,J,K,bi,bj)=0.d0
           theta(I,J,K,bi,bj)=0.d0
           salt(I,J,K,bi,bj)=0.d0
           gU(I,J,K,bi,bj)=0.d0
           gV(I,J,K,bi,bj)=0.d0
           gT(I,J,K,bi,bj)=0.d0
           gS(I,J,K,bi,bj)=0.d0
           guNm1(I,J,K,bi,bj) =0.d0
           gvNm1(I,J,K,bi,bj) =0.d0
           gtNm1(I,J,K,bi,bj) =0.d0
           gsNm1(I,J,K,bi,bj) =0.d0
           totPhiHyd(I,J,K,bi,bj)=0.d0
           IVDConvCount(i,j,k,bi,bj) = 0.d0
          ENDDO
         ENDDO
        ENDDO
        DO J=1-Oly,sNy+Oly
         DO I=1-Olx,sNx+Olx
          etaN(I,J,bi,bj)=0.d0
          etaH(I,J,bi,bj)=0.d0
          phiHydLow(I,J,bi,bj)=0.d0
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE INI_VEL( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      INTEGER bi,bj,i,j,k
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO k=1,Nr
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
           uVel(i,j,k,bi,bj)=0.d0
           vVel(i,j,k,bi,bj)=0.d0
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      IF (uVelInitFile .NE. ' ') THEN
       IF (  myThid  .EQ. 1 ) THEN
       CALL READ_FLD_XYZ_RL( uVelInitFile, ' ', uVel, 0, myThid )
       ENDIF
      ENDIF
      IF (vVelInitFile .NE. ' ') THEN
       IF (  myThid  .EQ. 1 ) THEN
       CALL READ_FLD_XYZ_RL( vVelInitFile, ' ', vVel, 0, myThid )
       ENDIF
      ENDIF
       CALL EXCH_UV_XYZ_RL(uVel,vVel,.TRUE.,myThid)
      DO bj = myByLo(myThid), myByHi(myThid)
       DO bi = myBxLo(myThid), myBxHi(myThid)
        DO k=1,Nr
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
           uVel(i,j,k,bi,bj)=uVel(i,j,k,bi,bj)*maskW(i,j,k,bi,bj)
           vVel(i,j,k,bi,bj)=vVel(i,j,k,bi,bj)*maskS(i,j,k,bi,bj)
          ENDDO
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE INI_VERTICAL_GRID( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER myThid
      INTEGER K
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      IF (setCenterDr) THEN
       DO K=1,Nr+1
        IF (delRc(K).LE.0.) THEN
         WRITE(msgBuf,'(A,I4,A,E16.8)')
     &  'S/R INI_VERTICAL_GRID: delRc(K=',K,' )=',delRc(K)
         CALL PRINT_ERROR( msgBuf , 1)
         WRITE(msgBuf,'(A)')
     &  'S/R INI_VERTICAL_GRID: Vert. grid spacing MUST BE > 0'
         CALL PRINT_ERROR( msgBuf , 1)
         STOP 'ABNORMAL END: S/R INI_VERTICAL_GRID'
        ENDIF
       ENDDO
        rF(1)  = Ro_SeaLevel
        rC(1)  = rF(1) + rkSign*delRc(1)
        drC(1) = delRc(1)
        drF(1) = delRc(1)
       DO K=2,Nr
        drC(K)   = delRc(K)
        drF(K-1) =  drF(K-1) + 0.5d0*delRc(K)
        drF(K)   = 0.5d0*delRc(K)
        rC(K)    = rC(K-1) + rkSign*drC(K)
        rF(K)    = rF(K-1) + rkSign*drF(K-1)
       ENDDO
        drF(Nr)  = drF(Nr) + delRc(Nr+1)
        rF(Nr+1) = rF(Nr) + rkSign*drF(Nr)
      ELSE
       DO K=1,Nr
        IF (delR(K).LE.0.) THEN
         WRITE(msgBuf,'(A,I4,A,E16.8)')
     &  'S/R INI_VERTICAL_GRID: delR(K=',K,' )=',delR(K)
         CALL PRINT_ERROR( msgBuf , 1)
         WRITE(msgBuf,'(A)')
     &  'S/R INI_VERTICAL_GRID: Vert. grid spacing MUST BE > 0'
         CALL PRINT_ERROR( msgBuf , 1)
         STOP 'ABNORMAL END: S/R INI_VERTICAL_GRID'
        ENDIF
       ENDDO
      rF(1) = Ro_SeaLevel
      DO K=1,Nr
       drF(K)     = delR(K)
       rF(K+1) = rF(K) + rkSign*delR(K)
      ENDDO
      drC(1)      = delR(1) * 0.5d0
      rC(1)       = rf(1) + rkSign*delR(1) * 0.5d0
      DO K=2,Nr
       drC(K)     = 0.5d0 *(delR(K-1)+delR(K))
       rC(K)      = rC(K-1) + rkSign*drC(K)
      ENDDO
      ENDIF
      DO K=1,Nr
       saFac(K)  = 1.d0
       recip_drC(K)   = 1.d0/drC(K)
       recip_drF(K)   = 1.d0/drF(K)
      ENDDO
      RETURN
      END
      SUBROUTINE INITIALISE_VARIA(myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE SURFACE_mod
      INTEGER myThid
      INTEGER bi,bj,K,iMin,iMax,jMin,jMax
      IF (debugMode) CALL DEBUG_ENTER('INITIALISE_VARIA',myThid)
      nIter0 = NINT( (startTime-baseTime)/deltaTClock )
      IF (debugMode) CALL DEBUG_CALL('INI_LINEAR_PHISURF',myThid)
      CALL INI_LINEAR_PHISURF( myThid )
      IF (debugMode) CALL DEBUG_CALL('INI_CORI',myThid)
      CALL INI_CORI( myThid )
      IF (debugMode) CALL DEBUG_CALL('INI_CG2D',myThid)
      CALL INI_CG2D( myThid )
      CALL BARRIER(myThid)
      IF (debugMode) CALL DEBUG_CALL('INI_MIXING',myThid)
      CALL INI_MIXING( myThid )
      CALL BARRIER(myThid)
      IF (debugMode) CALL DEBUG_CALL('INI_DYNVARS',myThid)
      CALL INI_DYNVARS( myThid )
      IF (debugMode) CALL DEBUG_CALL('INI_FIELDS',myThid)
      CALL INI_FIELDS( myThid )
      CALL BARRIER(myThid)
      CALL INI_AUTODIFF( myThid )
      CALL BARRIER(myThid)
      IF (debugMode) CALL DEBUG_CALL('PACKAGES_INIT_VARIABLES',myThid)
      CALL PACKAGES_INIT_VARIABLES( myThid )
      IF ( startTime .EQ. baseTime .AND. cAdjFreq .NE. 0. ) THEN
      IF (debugMode) CALL DEBUG_CALL('CONVECTIVE_ADJUSTMENT_INI',myThid)
        DO bj = myByLo(myThid), myByHi(myThid)
         DO bi = myBxLo(myThid), myBxHi(myThid)
           iMin=1-Olx
           iMax=sNx+Olx
           jMin=1-Oly
           jMax=sNy+Oly
           CALL CONVECTIVE_ADJUSTMENT_INI(
     I       bi, bj, iMin, iMax, jMin, jMax,
     I       startTime, nIter0, myThid )
         ENDDO
        ENDDO
        CALL BARRIER(myThid)
      END IF
      IF (debugMode) CALL DEBUG_CALL('INTEGR_CONTINUITY',myThid)
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        CALL INTEGR_CONTINUITY( bi, bj, uVel, vVel,
     I                          startTime, nIter0, myThid )
       ENDDO
      ENDDO
      CALL EXCH_XYZ_RL ( wVel, myThid ) 
      IF (debugMode) CALL DEBUG_CALL('STATE_SUMMARY',myThid)
      CALL STATE_SUMMARY( myThid )
      IF (debugMode) CALL DEBUG_LEAVE('INITIALISE_VARIA',myThid)
      RETURN
      END
      SUBROUTINE INTEGRATE_FOR_W( 
     I        bi,bj,k,uFld,vFld,
     O        wFld,
     I        myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER bi,bj,k
      Real*8  uFld (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  vFld (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  wFld (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myThid
      INTEGER i,j
      Real*8 uTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vTrans(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      DO j=1,sNy+1
        DO i=1,sNx+1
          uTrans(i,j) = uFld(i,j,k,bi,bj)*
     &     dyG(i,j,bi,bj)
     &     *drF(k)*hFacW(i,j,k,bi,bj)
          vTrans(i,j) = vFld(i,j,k,bi,bj)*
     &     dxG(i,j,bi,bj)
     &     *drF(k)*hFacS(i,j,k,bi,bj)
        ENDDO
      ENDDO
      IF (rigidLid) THEN
        IF (k.eq.1) THEN
          DO j=1,sNy
           DO i=1,sNx
             wFld(i,j,k,bi,bj) = 0.
           ENDDO
          ENDDO
        ELSEIF (k.eq.Nr) THEN
          DO j=1,sNy
           DO i=1,sNx
             wFld(i,j,k,bi,bj) = 
     &                -( uTrans(i+1,j)-uTrans(i,j)
     &                  +vTrans(i,j+1)-vTrans(i,j)
     &                 )*recip_rA(i,j,bi,bj) 
     &          *maskC(i,j,k,bi,bj)*maskC(i,j,k-1,bi,bj)
           ENDDO
          ENDDO
        ELSE
          DO j=1,sNy
           DO i=1,sNx
             wFld(i,j,k,bi,bj) = 
     &        ( wFld(i,j,k+1,bi,bj)
     &                -( uTrans(i+1,j)-uTrans(i,j)
     &                  +vTrans(i,j+1)-vTrans(i,j)
     &                 )*recip_rA(i,j,bi,bj) 
     &         )*maskC(i,j,k,bi,bj)*maskC(i,j,k-1,bi,bj)
           ENDDO
          ENDDO
        ENDIF
      ELSE
        IF (k.eq.Nr) THEN
          DO j=1,sNy
           DO i=1,sNx
             wFld(i,j,k,bi,bj) = 
     &                -( uTrans(i+1,j)-uTrans(i,j)
     &                  +vTrans(i,j+1)-vTrans(i,j)
     &                 )*recip_rA(i,j,bi,bj) 
     &          *maskC(i,j,k,bi,bj)
           ENDDO
          ENDDO
        ELSE
          DO j=1,sNy
           DO i=1,sNx
             wFld(i,j,k,bi,bj) = 
     &        ( wFld(i,j,k+1,bi,bj)
     &                -( uTrans(i+1,j)-uTrans(i,j)
     &                  +vTrans(i,j+1)-vTrans(i,j)
     &                 )*recip_rA(i,j,bi,bj) 
     &         )*maskC(i,j,k,bi,bj)
           ENDDO
          ENDDO
        ENDIF
      ENDIF
      RETURN
      END
      SUBROUTINE INTEGR_CONTINUITY(
     I                             bi, bj, uFld, vFld,
     I                             myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE SURFACE_mod
       USE FFIELDS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER bi,bj
      LOGICAL UpdateEtaN_EtaH
      Real*8 uFld(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy)
      Real*8 vFld(1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr,nSx,nSy) 
      INTEGER i,j,k
      Real*8 uTrans(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 vTrans(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 hDivFlow(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 wSurf, facEmP
      DO k=Nr,1,-1
       CALL INTEGRATE_FOR_W(
     I                       bi, bj, k, uFld, vFld,
     O                       wVel,
     I                       myThid )
      ENDDO
      RETURN
      END
      SUBROUTINE LOAD_GRID_SPACING( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
      INTEGER myThid
      REAL*4 tmp4delX(Nx), tmp4delY(Ny)
      REAL*8 tmp8delX(Nx), tmp8delY(Ny)
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      INTEGER i, j, iLen, iUnit
      INTEGER  ILNBLNK
      EXTERNAL ILNBLNK
      IF ( delXFile .NE. ' ' ) THEN
        IF (  myThid  .EQ. 1 ) THEN
        CALL MDSFINDUNIT( iUnit, myThid )
        iLen = ILNBLNK(delXFile)
        IF (readBinaryPrec.EQ.precFloat32) THEN
         OPEN(iUnit, FILE=delXFile(1:iLen), STATUS='OLD',
     &        FORM='UNFORMATTED',ACCESS='DIRECT',RECL=4*Nx)
         READ(iUnit,rec=1) tmp4delX
         CLOSE(iUnit)
         DO i=1,Nx
           delX(i) = tmp4delX(i)
         ENDDO
        ELSEIF (readBinaryPrec.EQ.precFloat64) THEN
         OPEN(iUnit, FILE=delXFile(1:iLen), STATUS='OLD',
     &        FORM='UNFORMATTED',ACCESS='DIRECT',RECL=4*2*Nx)
         READ(iUnit,rec=1) tmp8delX
         CLOSE(iUnit)
         DO i=1,Nx
           delX(i) = tmp8delX(i)
         ENDDO
        ENDIF
        WRITE(msgBuf,'(3A)') 'S/R LOAD_GRID_SPACING:',
     &    ' delX loaded from file: ', delXFile(1:iLen)
        CALL PRINT_MESSAGE( msgBuf, standardMessageUnit,
     &                      SQUEEZE_RIGHT , myThid)
        ENDIF
      ENDIF
      IF ( delYFile .NE. ' ' ) THEN
        IF (  myThid  .EQ. 1 ) THEN
        CALL MDSFINDUNIT( iUnit, myThid )
        iLen = ILNBLNK(delYFile)
        IF (readBinaryPrec.EQ.precFloat32) THEN
         OPEN(iUnit, FILE=delYFile(1:iLen), STATUS='OLD',
     &        FORM='UNFORMATTED',ACCESS='DIRECT',RECL=4*Ny)
         READ(iUnit,rec=1) tmp4delY
         CLOSE(iUnit)
         DO j=1,Ny
           delY(j) = tmp4delY(j)
         ENDDO
        ELSEIF (readBinaryPrec.EQ.precFloat64) THEN
         OPEN(iUnit, FILE=delYFile(1:iLen), STATUS='OLD',
     &        FORM='UNFORMATTED',ACCESS='DIRECT',RECL=4*2*Ny)
         READ(iUnit,rec=1) tmp8delY
         CLOSE(iUnit)
         DO j=1,Ny
           delY(j) = tmp8delY(j)
         ENDDO
        ENDIF
        WRITE(msgBuf,'(3A)') 'S/R LOAD_GRID_SPACING:',
     &    ' delY loaded from file: ', delYFile(1:iLen)
        CALL PRINT_MESSAGE( msgBuf, standardMessageUnit,
     &                      SQUEEZE_RIGHT , myThid)
        ENDIF
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE MODELDATA_EXAMPLE( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER myThid
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      WRITE(msgBuf,'(A)') '// Shown below is an example "data" file.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '// To use this example copy and paste the  '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '// ">" lines. Then remove the text up to' 
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1) 
      WRITE(msgBuf,'(A)') '// and including the ">".'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># Example "data" file'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># Lines beginning "#" are comments'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># o Continuous equation parameters'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   gravity - Accel due to gravity (m.s^2)'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   rhonil  - Reference density (kg/m^3)'   
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   tAlpha  - Thermal expansion coefficient (1/oC)'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   sBeta   - Haline contraction coefficient (1/ppt)'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   f0      - Reference coriolis parameter ( 1/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#             ( South edge f on beta plane.)'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   beta    - df/dy ( s^-1.m^-1 ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   viscAh  - Horizontal eddy viscosity coefficient '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^2/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   viscAz  - Vertical eddy viscosity coefficient '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^2/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   viscA4  - Biharmonic eddy viscosity coefficient '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^4/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   diffKhT - Horizontal temperature diffusivity '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^2/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   diffKzT - Vertical temperature diffusivity '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^2/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   diffK4T - Biharmonic temperature diffusivity '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^4/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   diffKhS - Horizontal salt diffusivity '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^2/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   diffKzS - Vertical salt diffusivity '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^2/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   diffK4S - Biharmonic salt diffusivity '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#             ( m^4/s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   momStepping - On/Off flag for momentum'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  equation.          '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   momViscosity - On/Off flag for momentum'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  mixing.                 '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   momAdvection - On/Off flag for momentum'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  self transport.         '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   momPressureForcing - On/Off flag for momentum'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#                        pressure terms.         '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   useCoriolis  - On/Off flag for momentum'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  equation coriolis term. '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   tempStepping - On/Off flag for temperature'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  eqaution.         '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   tempDiffusion- On/Off flag for temperature'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  mixing.                 '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   tempAdvection- On/Off flag for temperature'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  transport.         '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   tempForcing  - On/Off flag for temperature'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  forcing.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   saltDiffusion- On/Off flag for salt'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  mixing.                 '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   saltAdvection- On/Off flag for salt'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  transport.         '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   saltForcing  - On/Off flag for salt'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  forcing.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   tRef         - Reference vertical pot. temp'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   sRef         - Reference vertical salinity'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>&PARM01'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> gravity=9.81,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> rhonil=999.8,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> tAlpha=2.e-4,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> sBeta=7e-4'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> f0=1.e-4'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> viscAh=1.e3'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> viscAz=1.e-5'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> viscA4=0.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> diffKhT=1.e3'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> diffKzT=1.e-5'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> diffK4T=0.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> diffKhS=1.e3'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> diffKzS=1.e-5'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> diffK4S=0.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> momStepping=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> momViscosity=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> momAdvection=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> momPressureForcing=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> momForcing=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> useCoriolis=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> tempStepping=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> tempDiffusion=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> tempAdvection=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> tempForcing=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> saltDiffusion=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> saltAdvection=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> saltForcing=.TRUE.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> tRef=20.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> sRef=35.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> implicitFreeSurface=.TRUE.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> rigidLid=.FALSE.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> GMmaxSlope=1.d-2,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> GMlength=200.d3,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> GMalpha=200.d3,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> GMdepth=1000.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> GMkBackground=0.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>/                     '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># o Elliptic solver parameters'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   cg2dMaxIters - Maximum number of 2d '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                  solver iterations.   '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   cg2dChkReqFreq - Frequency solver tests '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                    convergence.       '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   cg2dTargetResidual - Solver target'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#                        residual.    '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>&PARM02'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> cg2dMaxIters=200,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> cg2dChkResFreq=5,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> cg2dTargetResidual=1.e-7,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>/                     '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># o Timestepping parameters'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   nIter0 - Start timestep index'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   nTimeSteps - Number of timesteps in run.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   delT - Timestep ( s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   deltaTtracer - Tracer timestep ( s ).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   abEps - Adams-Bashforth stabilising '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#           factor.                     '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   tauCD - CD scheme coupling timescale (s)'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   startTime - Integration starting time (s)'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   endTime - Integration ending time (s)'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   cAdjFreq - Convective adjustment period (s)'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   chkPtFreq - Frequency at which check  '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#               pointing is done ( s ).   '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   dumpFreq - Frequency at which model  '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#              state is stored ( s ).     '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>&PARM03'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> nIter0=0'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> nTimeSteps=5000'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> delT=3600.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> deltaTtracer=3600.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> abEps=0.1'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> tauCD=345600.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> startTime=0.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> endTime=31104000.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> chkPtFreq=864000.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> dumpFreq=2592000.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> cAdjFreq=86400.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>/                     '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># o Gridding parameters'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   l - Global domain grid-points in X'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   m - Global domain grid-points in Y'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   n - Grid-points in Z'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#   usingSphericalPolarGrid - On/Off flag for'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#       selecting spherical polar coordinates'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   usingCartesianGrid - On/Off flag for'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#        selecting cartesian coordinates'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   delX - Zonal grid spacing. Degrees'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#          for spherical polar and m for'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#          cartesian. A value for each point'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#          in X can be specified.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   delY - Meridional grid spacing. Degrees'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#          for spherical polar and m for'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') 
     & '>#          cartesian. A value for each point'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#          in Y can be specified.'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   delZ - Vertical grid spacing (m).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   delP - Vertical grid spacing (Pa).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   phiMin - Southern boundary latitude'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#            (spherical polar grid).   '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#   rSphere- Radius of globe           '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>#            (spherical polar grid).   '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>&PARM04'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> n=20,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> l=122,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> m=86,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> usingSphericalPolarGrid=.TRUE.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> usingCartesianGrid=.FALSE.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> delx=1.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> dely=1.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> delz=  100.,  100.,  100.,  100.,  100.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>        100.,  100.,  100.,  100.,  100.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>        100.,  100.,  100.,  100.,  100.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>        100.,  100.,  100.,  100.,  100.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> phiMin=-80.,'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '> rSphere=6430.E3'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '>/                     '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># Note: Some systems use & as the '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># namelist terminator. Other systems'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') '># use a / character (as shown here).'
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      WRITE(msgBuf,'(A)') ' '
      CALL PRINT_MESSAGE( msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
      RETURN
      END
      SUBROUTINE MOMENTUM_CORRECTION_STEP(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      Real*8 phiSurfX(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 phiSurfY(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER iMin,iMax
      INTEGER jMin,jMax
      INTEGER bi,bj
      INTEGER k,i,j
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          phiSurfX(i,j)=0.
          phiSurfY(i,j)=0.
         ENDDO
        ENDDO
        iMin = 1-OLx+1
        iMax = sNx+OLx
        jMin = 1-OLy+1
        jMax = sNy+OLy
        CALL CALC_GRAD_PHI_SURF(
     I       bi,bj,iMin,iMax,jMin,jMax,
     I       etaN,
     O       phiSurfX,phiSurfY,
     I       myThid )
        DO K=1,Nr
          IF (momStepping)
     &      CALL CORRECTION_STEP(
     I         bi,bj,iMin,iMax,jMin,jMax,K,
     I         phiSurfX,phiSurfY,myTime,myThid )
        ENDDO
       ENDDO
      ENDDO
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        CALL INTEGR_CONTINUITY( bi, bj, uVel, vVel,
     I                          myTime, myIter, myThid )
       ENDDO
      ENDDO
      IF ( exactConserv .AND. implicDiv2Dflow .NE. 0.d0)
     & CALL EXCH_XY_RL (  etaN ,  myThid  )
      RETURN
      END
      SUBROUTINE PACKAGES_INIT_VARIABLES( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE tamc_mod
       USE tamc_keys_mod
      INTEGER myThid
      IF (debugMode) 
     &     CALL DEBUG_ENTER('PACKAGES_INIT_VARIABLES',myThid)
      IF (debugMode) CALL DEBUG_CALL('CD_CODE_INI',myThid)
      IF (useCDscheme) CALL CD_CODE_INI_VARS( myThid )
      CALL CTRL_INIT_VARIABLES ( mythid )
      CALL CTRL_MAP_INI( mythid )
      CALL BARRIER(myThid)
      IF (debugMode) CALL DEBUG_CALL('INI_FORCING',myThid)
      CALL INI_FORCING( mythid )
      CALL COST_INIT_VARIA( mythid )
      CALL BARRIER(myThid)
      IF (debugMode) 
     &     CALL DEBUG_LEAVE('PACKAGES_INIT_VARIABLES',myThid)
      RETURN
      END
      SUBROUTINE PLOT_FIELD_XYRS( 
     I                            fld, fldNam , myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      Real*8 fld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      CHARACTER*(*) fldNam
      INTEGER myThid
      INTEGER myIter
      CHARACTER*(MAX_LEN_MBUF) fldTitle
      INTEGER iStart, iEnd, iStride
      INTEGER jStart, jEnd, jStride
      INTEGER kStart, kEnd, kStride
      INTEGER biStart, biEnd, biStride
      INTEGER bjStart, bjEnd, bjStride
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
       IF ( myIter .GE. 0 ) THEN
        WRITE(fldTitle,'(A,A,A,I10)') 
     &  '// Field ', fldNam, ' at iteration ',
     &  myIter
       ELSE
        WRITE(fldTitle,'(A,A)') '// Field ', fldNam
       ENDIF
       iStart   =  1-OLx
       iEnd     =  sNx+OLx
       iStride  =  1
       jStart   =  sNy+OLy
       jEnd     =  1-OLy
       jStride  = -1
       kStart   =  1
       kEnd     =  1
       kStride  =  1
       biStart  =  1
       biEnd    =  nSx
       biStride =  1
       bjStart  =  nSy
       bjEnd    =  1    
       bjStride = -1
       CALL PRINT_MAPRS(
     I        fld, fldTitle, PRINT_MAP_XY,
     I         1-OLx,sNx+OLx,1-OLy,sNy+OLy,1,1,  nSx,  nSy,
     I         iStart,   iEnd,  iStride,
     I         jStart,   jEnd,  jStride,
     I         kStart,   kEnd,  kStride,
     I        biStart,  biEnd, biStride,
     I        bjStart,  bjEnd, bjStride )
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE PLOT_FIELD_XYRL( 
     I                            fld, fldNam , myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      Real*8 fld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,nSx,nSy)
      CHARACTER*(*) fldNam
      INTEGER myThid
      INTEGER myIter
      CHARACTER*(MAX_LEN_MBUF) fldTitle
      INTEGER iStart, iEnd, iStride
      INTEGER jStart, jEnd, jStride
      INTEGER kStart, kEnd, kStride
      INTEGER biStart, biEnd, biStride
      INTEGER bjStart, bjEnd, bjStride
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
       IF ( myIter .GE. 0 ) THEN
        WRITE(fldTitle,'(A,A,A,I10)') 
     &  '// Field ', fldNam, ' at iteration ',
     &  myIter
       ELSE
        WRITE(fldTitle,'(A,A)') '// Field ', fldNam
       ENDIF
       iStart   =  1-OLx
       iEnd     =  sNx+OLx
       iStride  =  1
       jStart   =  sNy+OLy
       jEnd     =  1-OLy
       jStride  = -1
       kStart   =  1
       kEnd     =  1
       kStride  =  1
       biStart  =  1
       biEnd    =  nSx
       biStride =  1
       bjStart  =  nSy
       bjEnd    =  1    
       bjStride = -1
       CALL PRINT_MAPRL(
     I        fld, fldTitle, PRINT_MAP_XY,
     I         1-OLx,sNx+OLx,1-OLy,sNy+OLy,1,1,  nSx,  nSy,
     I         iStart,   iEnd,  iStride,
     I         jStart,   jEnd,  jStride,
     I         kStart,   kEnd,  kStride,
     I        biStart,  biEnd, biStride,
     I        bjStart,  bjEnd, bjStride )
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE PLOT_FIELD_XYZRS( 
     I                            fld, fldNam , fldNz, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER fldNz
      Real*8 fld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:fldNz,nSx,nSy)
      CHARACTER*(*) fldNam
      INTEGER myThid
      INTEGER myIter
      CHARACTER*(MAX_LEN_MBUF) fldTitle
      INTEGER iStart, iEnd, iStride
      INTEGER jStart, jEnd, jStride
      INTEGER kStart, kEnd, kStride
      INTEGER biStart, biEnd, biStride
      INTEGER bjStart, bjEnd, bjStride
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
       IF ( myIter .GE. 0 ) THEN
        WRITE(fldTitle,'(A,A,A,I10)') 
     &  '// Field ', fldNam, ' at iteration ',
     &  myIter
       ELSE
        WRITE(fldTitle,'(A,A)') '// Field ', fldNam
       ENDIF
       iStart   =  1-OLx
       iEnd     =  sNx+OLx
       iStride  =  1
       jStart   =  sNy+OLy
       jEnd     =  1-OLy
       jStride  = -1
       kStart   =  1
       kEnd     =  1
       kStride  =  1
       biStart  =  1
       biEnd    =  nSx
       biStride =  1
       bjStart  =  nSy
       bjEnd    =  1    
       bjStride = -1
       CALL PRINT_MAPRS(
     I        fld, fldTitle, PRINT_MAP_XY,
     I         1-OLx,sNx+OLx,1-OLy,sNy+OLy,1,fldNz,  nSx,  nSy,
     I         iStart,   iEnd,  iStride,
     I         jStart,   jEnd,  jStride,
     I         kStart,   kEnd,  kStride,
     I        biStart,  biEnd, biStride,
     I        bjStart,  bjEnd, bjStride )
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE PLOT_FIELD_XYZRL( 
     I                            fld, fldNam , fldNz, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER fldNz
      Real*8 fld(1-OLx:sNx+OLx,1-OLy:sNy+OLy,1:fldNz,nSx,nSy)
      CHARACTER*(*) fldNam
      INTEGER myThid
      INTEGER myIter
      CHARACTER*(MAX_LEN_MBUF) fldTitle
      INTEGER iStart, iEnd, iStride
      INTEGER jStart, jEnd, jStride
      INTEGER kStart, kEnd, kStride
      INTEGER biStart, biEnd, biStride
      INTEGER bjStart, bjEnd, bjStride
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
       IF ( myIter .GE. 0 ) THEN
        WRITE(fldTitle,'(A,A,A,I10)') 
     &  '// Field ', fldNam, ' at iteration ',
     &  myIter
       ELSE
        WRITE(fldTitle,'(A,A)') '// Field ', fldNam
       ENDIF
       iStart   =  1-OLx
       iEnd     =  sNx+OLx
       iStart   =  1
       iEnd     =  sNx
       iStride  =  1
       jStart   =  sNy+OLy
       jEnd     =  1-OLy
       jStart   =  sNy
       jEnd     =  1
       jStride  = -1
       kStart   =  1
       kEnd     =  fldNz
       kEnd     =  1
       kStride  =  1
       biStart  =  1
       biEnd    =  nSx
       biStride =  1
       bjStart  =  nSy
       bjEnd    =  1    
       bjStride = -1
       CALL PRINT_MAPRL(
     I        fld, fldTitle, PRINT_MAP_XY,
     I         1-OLx,sNx+OLx,1-OLy,sNy+OLy,1,fldNz,  nSx,  nSy,
     I         iStart,   iEnd,  iStride,
     I         jStart,   jEnd,  jStride,
     I         kStart,   kEnd,  kStride,
     I        biStart,  biEnd, biStride,
     I        bjStart,  bjEnd, bjStride )
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE PLOT_FIELD_XZRS( 
     I                            fld, fldNam , fldNz, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER fldNz
      Real*8 fld(1-OLx:sNx+OLx,1:fldNz,nSx,nSy)
      CHARACTER*(*) fldNam
      INTEGER myThid
      INTEGER myIter
      CHARACTER*(MAX_LEN_MBUF) fldTitle
      INTEGER iStart, iEnd, iStride
      INTEGER jStart, jEnd, jStride
      INTEGER kStart, kEnd, kStride
      INTEGER biStart, biEnd, biStride
      INTEGER bjStart, bjEnd, bjStride
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
       IF ( myIter .GE. 0 ) THEN
        WRITE(fldTitle,'(A,A,A,I10)') 
     &  '// Field ', fldNam, ' at iteration ',
     &  myIter
       ELSE
        WRITE(fldTitle,'(A,A)') '// Field ', fldNam
       ENDIF
       iStart   =  1
       iEnd     =  sNx
       iStride  =  1
       jStart   =  1
       jEnd     =  1
       jStride  =  1
       kStart   =  1
       kEnd     =  fldNz
       kStride  =  1
       biStart  =  1
       biEnd    =  nSx
       biStride =  1
       bjStart  =  nSy 
       bjEnd    =  1    
       bjStride = -1
       CALL PRINT_MAPRS(
     I        fld, fldTitle, PRINT_MAP_XZ,
     I         1-OLx,sNx+OLx,1,fldNz,1,1,  nSx,  nSy,
     I         iStart,   iEnd,  iStride,
     I         jStart,   jEnd,  jStride,
     I         kStart,   kEnd,  kStride,
     I        biStart,  biEnd, biStride,
     I        bjStart,  bjEnd, bjStride )
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE PLOT_FIELD_XZRL( 
     I                            fld, fldNam , fldNz, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER fldNz
      Real*8 fld(1-OLx:sNx+OLx,1:fldNz,nSx,nSy)
      CHARACTER*(*) fldNam
      INTEGER myThid
      INTEGER myIter
      CHARACTER*(MAX_LEN_MBUF) fldTitle
      INTEGER iStart, iEnd, iStride
      INTEGER jStart, jEnd, jStride
      INTEGER kStart, kEnd, kStride
      INTEGER biStart, biEnd, biStride
      INTEGER bjStart, bjEnd, bjStride
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
       IF ( myIter .GE. 0 ) THEN
        WRITE(fldTitle,'(A,A,A,I10)') 
     &  '// Field ', fldNam, ' at iteration ',
     &  myIter
       ELSE
        WRITE(fldTitle,'(A,A)') '// Field ', fldNam
       ENDIF
       iStart   =  1
       iEnd     =  sNx
       iStride  =  1
       jStart   =  1
       jEnd     =  1
       jStride  = -1
       kStart   =  1
       kEnd     =  fldNz
       kStride  =  1
       biStart  =  1
       biEnd    =  nSx
       biStride =  1
       bjStart  =  nSy
       bjEnd    =  1    
       bjStride = -1
       CALL PRINT_MAPRL(
     I        fld, fldTitle, PRINT_MAP_XZ,
     I         1-OLx,sNx+OLx,1,1,1,fldNz,  nSx,  nSy,
     I         iStart,   iEnd,  iStride,
     I         jStart,   jEnd,  jStride,
     I         kStart,   kEnd,  kStride,
     I        biStart,  biEnd, biStride,
     I        bjStart,  bjEnd, bjStride )
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE PLOT_FIELD_YZRS( 
     I                            fld, fldNam , fldNz, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER fldNz
      Real*8 fld(1-OLy:sNy+OLy,1:fldNz,nSx,nSy)
      CHARACTER*(*) fldNam
      INTEGER myThid
      INTEGER myIter
      CHARACTER*(MAX_LEN_MBUF) fldTitle
      INTEGER iStart, iEnd, iStride
      INTEGER jStart, jEnd, jStride
      INTEGER kStart, kEnd, kStride
      INTEGER biStart, biEnd, biStride
      INTEGER bjStart, bjEnd, bjStride
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
       IF ( myIter .GE. 0 ) THEN
        WRITE(fldTitle,'(A,A,A,I10)') 
     &  '// Field ', fldNam, ' at iteration ',
     &  myIter
       ELSE
        WRITE(fldTitle,'(A,A)') '// Field ', fldNam
       ENDIF
       iStart   =  1
       iEnd     =  1
       iStride  =  1
       jStart   =  sNy
       jEnd     =  1
       jStride  = -1
       kStart   =  1
       kEnd     =  fldNz
       kStride  =  1
       biStart  =  1
       biEnd    =  nSx 
       biStride =  1
       bjStart  =  nSy
       bjEnd    =  1    
       bjStride = -1
       CALL PRINT_MAPRS(
     I        fld, fldTitle, PRINT_MAP_YZ,
     I         1,1,1-OLy,sNy+OLy,1,fldNz,  nSx,  nSy,
     I         iStart,   iEnd,  iStride,
     I         jStart,   jEnd,  jStride,
     I         kStart,   kEnd,  kStride,
     I        biStart,  biEnd, biStride,
     I        bjStart,  bjEnd, bjStride )
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE PLOT_FIELD_YZRL( 
     I                            fld, fldNam , fldNz, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER fldNz
      Real*8 fld(1-OLy:sNy+OLy,1:fldNz,nSx,nSy)
      CHARACTER*(*) fldNam
      INTEGER myThid
      INTEGER myIter
      CHARACTER*(MAX_LEN_MBUF) fldTitle
      INTEGER iStart, iEnd, iStride
      INTEGER jStart, jEnd, jStride
      INTEGER kStart, kEnd, kStride
      INTEGER biStart, biEnd, biStride
      INTEGER bjStart, bjEnd, bjStride
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
       IF ( myIter .GE. 0 ) THEN
        WRITE(fldTitle,'(A,A,A,I10)') 
     &  '// Field ', fldNam, ' at iteration ',
     &  myIter
       ELSE
        WRITE(fldTitle,'(A,A)') '// Field ', fldNam
       ENDIF
       iStart   =  1
       iEnd     =  1
       iStride  =  1
       jStart   =  sNy
       jEnd     =  1
       jStride  = -1
       kStart   =  1
       kEnd     =  fldNz
       kStride  =  1
       biStart  =  1
       biEnd    =  nSx 
       biStride =  1
       bjStart  =  nSy
       bjEnd    =  1    
       bjStride = -1
       CALL PRINT_MAPRL(
     I        fld, fldTitle, PRINT_MAP_YZ,
     I         1,1,1-OLy,sNy+OLy,1,fldNz,  nSx,  nSy,
     I         iStart,   iEnd,  iStride,
     I         jStart,   jEnd,  jStride,
     I         kStart,   kEnd,  kStride,
     I        biStart,  biEnd, biStride,
     I        bjStart,  bjEnd, bjStride )
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE PRESSURE_FOR_EOS( 
     I        bi, bj, iMin, iMax, jMin, jMax,  k,
     O        locPres,
     I        myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE SURFACE_mod
      INTEGER bi, bj, k
      INTEGER iMin,iMax,jMin,jMax
      Real*8 locPres(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER myThid
      INTEGER  i,j
      IF ( usingZCoords ) THEN
        IF ( useDynP_inEos_Zc ) THEN  
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
            locPres(i,j) = rhoConst*(
     &                   totPhiHyd(i,j,k,bi,bj)
     &                  -rC(k)*gravity 
     &                            )*maskC(i,j,k,bi,bj)
          ENDDO
         ENDDO
       ELSE
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
            locPres(i,j) = -rhoConst*rC(k)*gravity 
     &                              *maskC(i,j,k,bi,bj)
          ENDDO
         ENDDO
       ENDIF
      ELSEIF ( usingPCoords ) THEN
         DO j=1-Oly,sNy+Oly
          DO i=1-Olx,sNx+Olx
            locPres(i,j) = rC(k)
     &                   * maskC(i,j,k,bi,bj)
          ENDDO
         ENDDO
      ENDIF
      RETURN 
      END
      SUBROUTINE QUASIHYDROSTATICTERMS(
     I      bi,bj,k,
     O      effectiveBuoy,
     I      myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER bi,bj,k
      Real*8 effectiveBuoy(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      INTEGER myThid
      INTEGER i,j
      Real*8 scalingFactor
      scalingFactor=rhoConst/gravity
      scalingFactor=1./gravity
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx-1
        effectiveBuoy(i,j)=effectiveBuoy(i,j)
     &    -scalingFactor*
     &     fCoriCos(i,j,bi,bj)*
     &     0.5*( uVel(i,j,k,bi,bj)+uVel(i+1,j,k,bi,bj) )
       ENDDO
      ENDDO
      IF (useNHMTerms) THEN
       DO j=1-Oly,sNy+Oly-1
        DO i=1-Olx,sNx+Olx-1
         effectiveBuoy(i,j)=effectiveBuoy(i,j)
     &    -scalingFactor*
     &     (
     &       0.5*( uVel(i,j,k,bi,bj)**2+uVel(i+1,j,k,bi,bj)**2 )
     &      +0.5*( vVel(i,j,k,bi,bj)**2+vVel(i,j+1,k,bi,bj)**2 )
     &     )*recip_RSphere
        ENDDO
       ENDDO
      ENDIF
      RETURN
      END
      SUBROUTINE SOLVE_FOR_PRESSURE(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE CD_CODE_VARS_mod
       USE GRID_mod
       USE SURFACE_mod
       USE FFIELDS_mod
       USE SOLVE_FOR_PRESSURE_mod
      LOGICAL  DIFFERENT_MULTIPLE
      EXTERNAL DIFFERENT_MULTIPLE
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER i,j,k,bi,bj
      Real*8 uf(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 vf(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 firstResidual,lastResidual
      Real*8 tmpFac
      Real*8 sumEmP, tileEmP
      LOGICAL putPmEinXvector
      INTEGER numIters
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      putPmEinXvector = .FALSE.
      sumEmP = 0.
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          etaNm1(i,j,bi,bj) = etaN(i,j,bi,bj)
          cg2d_x(i,j,bi,bj) = Bo_surf(i,j,bi,bj)*etaN(i,j,bi,bj)
          cg2d_b(i,j,bi,bj) = 0.
         ENDDO
        ENDDO
        IF (useRealFreshWaterFlux) THEN
         tmpFac = freeSurfFac*convertEmP2rUnit
         IF (exactConserv) 
     &        tmpFac = freeSurfFac*convertEmP2rUnit*implicDiv2DFlow
         DO j=1,sNy
          DO i=1,sNx
           cg2d_b(i,j,bi,bj) = 
     &       tmpFac*rA(i,j,bi,bj)*EmPmR(i,j,bi,bj)/deltaTMom
          ENDDO
         ENDDO
        ENDIF
        IF ( putPmEinXvector ) THEN
         tileEmP = 0.
         DO j=1,sNy
          DO i=1,sNx
            tileEmP = tileEmP + rA(i,j,bi,bj)*EmPmR(i,j,bi,bj)
     &                                       *maskH(i,j,bi,bj)
          ENDDO
         ENDDO
         sumEmP = sumEmP + tileEmP
        ENDIF
       ENDDO
      ENDDO
      IF ( putPmEinXvector ) THEN
        CALL GLOBAL_SUM_R8 (  sumEmP,  myThid  )
      ENDIF
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        IF ( putPmEinXvector ) THEN
          tmpFac = 0.
          IF (globalArea.GT.0.) tmpFac = freeSurfFac*deltaTfreesurf
     &                          *convertEmP2rUnit*sumEmP/globalArea
          DO j=1,sNy
           DO i=1,sNx
            cg2d_x(i,j,bi,bj) = cg2d_x(i,j,bi,bj)
     &                        - tmpFac*Bo_surf(i,j,bi,bj)
           ENDDO
          ENDDO
        ENDIF
        DO K=Nr,1,-1
         DO j=1,sNy+1
          DO i=1,sNx+1
           uf(i,j) = dyG(i,j,bi,bj)
     &      *drF(k)*hFacW(i,j,k,bi,bj)
           vf(i,j) = dxG(i,j,bi,bj)
     &      *drF(k)*hFacS(i,j,k,bi,bj)
          ENDDO
         ENDDO
         CALL CALC_DIV_GHAT(
     I       bi,bj,1,sNx,1,sNy,K,
     I       uf,vf,
     U       cg2d_b,
     I       myThid)
        ENDDO
       ENDDO
      ENDDO
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        IF ( exactConserv ) THEN
         DO j=1,sNy
          DO i=1,sNx
           cg2d_b(i,j,bi,bj) = cg2d_b(i,j,bi,bj)
     &       -freeSurfFac*rA(i,j,bi,bj)/deltaTMom/deltaTfreesurf
     &         * etaH(i,j,bi,bj)
          ENDDO
         ENDDO
        ELSE
         DO j=1,sNy
          DO i=1,sNx
           cg2d_b(i,j,bi,bj) = cg2d_b(i,j,bi,bj)
     &       -freeSurfFac*rA(i,j,bi,bj)/deltaTMom/deltaTfreesurf
     &         * etaN(i,j,bi,bj)
          ENDDO
         ENDDO
        ENDIF
       ENDDO
      ENDDO
      IF ( debugLevel .GE. debLevB ) THEN
       CALL DEBUG_STATS_RL(1,cg2d_b,'cg2d_b (SOLVE_FOR_PRESSURE)',
     &                        myThid)
      ENDIF
      firstResidual=0.
      lastResidual=0.
      numIters=cg2dMaxIters
      CALL CG2D(
     U           cg2d_b,
     U           cg2d_x,
     O           firstResidual,
     O           lastResidual,
     U           numIters,
     I           myThid )
      CALL EXCH_XY_RL ( cg2d_x,  myThid  )
      IF ( debugLevel .GE. debLevB ) THEN
       CALL DEBUG_STATS_RL(1,cg2d_x,'cg2d_x (SOLVE_FOR_PRESSURE)',
     &                        myThid)
      ENDIF
      IF ( DIFFERENT_MULTIPLE(monitorFreq,myTime,deltaTClock)
     &   ) THEN
       IF ( debugLevel .GE. debLevA ) THEN
        IF (  myThid  .EQ. 1 ) THEN
        WRITE(msgBuf,'(A34,1PE24.14)') 'cg2d_init_res =',firstResidual
        CALL PRINT_MESSAGE(msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
        WRITE(msgBuf,'(A34,I6)') 'cg2d_iters =',numIters
        CALL PRINT_MESSAGE(msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
        WRITE(msgBuf,'(A34,1PE24.14)') 'cg2d_res =',lastResidual
        CALL PRINT_MESSAGE(msgBuf,standardMessageUnit,SQUEEZE_RIGHT,1)
        ENDIF
       ENDIF
      ENDIF
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          etaN(i,j,bi,bj) = recip_Bo(i,j,bi,bj)*cg2d_x(i,j,bi,bj)
         ENDDO
        ENDDO
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE STATE_SUMMARY( myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
      INTEGER myThid
      CHARACTER*(MAX_LEN_MBUF) msgBuf
      CALL BARRIER(myThid)
      IF ( myThid .EQ. 1 ) THEN
      WRITE(msgBuf,'(A)')
     &'// ======================================================='
      CALL PRINT_MESSAGE( msgBuf, standardMessageUnit, 
     &                    SQUEEZE_RIGHT , 1)
      WRITE(msgBuf,'(A)') '// Model current state'
      CALL PRINT_MESSAGE( msgBuf, standardMessageUnit, 
     &                    SQUEEZE_RIGHT , 1)
      WRITE(msgBuf,'(A)')
     &'// ======================================================='
      CALL PRINT_MESSAGE( msgBuf, standardMessageUnit,
     &  SQUEEZE_RIGHT , 1)
      WRITE(msgBuf,'(A)') ' '
      CALL PRINT_MESSAGE( msgBuf, standardMessageUnit,
     &  SQUEEZE_RIGHT , 1)
      ENDIF
      CALL BARRIER(myThid)
      RETURN
      END
      SUBROUTINE TIMESTEP( bi, bj, iMin, iMax, jMin, jMax, k,
     I                     dPhiHydX,dPhiHydY, phiSurfX, phiSurfY,
     I                     guDissip, gvDissip,
     I                     myTime, myIter, myThid )
       USE SIZE_mod
       USE DYNVARS_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE SURFACE_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax
      INTEGER k
      Real*8     dPhiHydX(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8     dPhiHydY(1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8     phiSurfX(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8     phiSurfY(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8     guDissip(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8     gvDissip(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8     myTime
      INTEGER myIter, myThid
      LOGICAL momForcing_In_AB
      LOGICAL momDissip_In_AB
      INTEGER i,j
      Real*8 ab15,ab05
      Real*8 phxFac,phyFac, psFac
      Real*8     gUtmp(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8     gVtmp(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8     guCor(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8     gvCor(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      IF (myIter .EQ. 0) THEN
       ab15=1.0
       ab05=0.0
      ELSE
       ab15=1.5+abeps
       ab05=-0.5-abeps
      ENDIF
      psFac = pfFacMom*(1.d0 - implicSurfPress)
      phxFac = pfFacMom
      phyFac = pfFacMom
      momForcing_In_AB = forcing_In_AB
      momForcing_In_AB = .TRUE.
      momDissip_In_AB  = .TRUE.
      DO j=1-Oly,sNy+Oly
       DO i=1-Olx,sNx+Olx
        gUtmp(i,j) = 0.d0
        gVtmp(i,j) = 0.d0
        guCor(i,j) = 0.d0
        gvCor(i,j) = 0.d0
       ENDDO
      ENDDO
      IF ( .NOT.staggerTimeStep ) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
          gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj) - phxFac*dPhiHydX(i,j)
          gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj) - phyFac*dPhiHydY(i,j)
         ENDDO
        ENDDO
        phxFac = 0.
        phyFac = 0.
      ENDIF 
      IF ( momViscosity .AND. momDissip_In_AB) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
          gU(i,j,k,bi,bj) = gU(i,j,k,bi,bj) + guDissip(i,j)
          gV(i,j,k,bi,bj) = gV(i,j,k,bi,bj) + gvDissip(i,j)
         ENDDO
        ENDDO
      ENDIF
      IF (momForcing .AND. momForcing_In_AB) THEN
        CALL EXTERNAL_FORCING_U(
     I     iMin,iMax,jMin,jMax,bi,bj,k,
     I     myTime,myThid)
        CALL EXTERNAL_FORCING_V(
     I     iMin,iMax,jMin,jMax,bi,bj,k,
     I     myTime,myThid)
      ENDIF
      IF (useCDscheme) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
          gUtmp(i,j) = gU(i,j,k,bi,bj)
          gVtmp(i,j) = gV(i,j,k,bi,bj)
         ENDDO
        ENDDO
      ENDIF
      CALL ADAMS_BASHFORTH2(
     I                        bi, bj, k,
     U                        gU, guNm1,
     I                        myIter, myThid )
      CALL ADAMS_BASHFORTH2(
     I                        bi, bj, k,
     U                        gV, gvNm1,
     I                        myIter, myThid )
      IF (momForcing .AND. .NOT.momForcing_In_AB) THEN
       IF (useCDscheme) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
          gUtmp(i,j) = gUtmp(i,j) - gU(i,j,k,bi,bj)
          gVtmp(i,j) = gVtmp(i,j) - gV(i,j,k,bi,bj)
         ENDDO
        ENDDO
       ENDIF
        CALL EXTERNAL_FORCING_U(
     I     iMin,iMax,jMin,jMax,bi,bj,k,
     I     myTime,myThid)
        CALL EXTERNAL_FORCING_V(
     I     iMin,iMax,jMin,jMax,bi,bj,k,
     I     myTime,myThid)
       IF (useCDscheme) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
          gUtmp(i,j) = gUtmp(i,j) + gU(i,j,k,bi,bj)
          gVtmp(i,j) = gVtmp(i,j) + gV(i,j,k,bi,bj)
         ENDDO
        ENDDO
       ENDIF
      ENDIF
      IF (useCDscheme) THEN
        CALL CD_CODE_SCHEME(
     I                  bi,bj,k, dPhiHydX,dPhiHydY, gUtmp,gVtmp,
     O                  guCor,gvCor,
     I                  myTime, myIter, myThid)
        DO j=jMin,jMax
         DO i=iMin,iMax
          gUtmp(i,j) = gU(i,j,k,bi,bj)
     &               + guCor(i,j)
          gVtmp(i,j) = gV(i,j,k,bi,bj)
     &               + gvCor(i,j)
         ENDDO
        ENDDO
      ELSE
        DO j=jMin,jMax
         DO i=iMin,iMax
          gUtmp(i,j) = gU(i,j,k,bi,bj)
          gVtmp(i,j) = gV(i,j,k,bi,bj)
         ENDDO
        ENDDO
      ENDIF
      IF ( momViscosity .AND. .NOT.momDissip_In_AB ) THEN
        DO j=jMin,jMax
         DO i=iMin,iMax
          gUtmp(i,j) = gUtmp(i,j) + guDissip(i,j)
          gVtmp(i,j) = gVtmp(i,j) + gvDissip(i,j)
         ENDDO
        ENDDO
      ENDIF
      DO j=jMin,jMax
        DO i=iMin,iMax
          gU(i,j,k,bi,bj) = uVel(i,j,k,bi,bj) 
     &     +deltaTmom*( 
     &         gUtmp(i,j)
     &       - psFac*phiSurfX(i,j)
     &       - phxFac*dPhiHydX(i,j)
     &        )*maskW(i,j,k,bi,bj)
        ENDDO
      ENDDO
      DO j=jMin,jMax
        DO i=iMin,iMax
          gV(i,j,k,bi,bj) = vVel(i,j,k,bi,bj)
     &     +deltaTmom*(
     &         gVtmp(i,j)
     &       - psFac*phiSurfY(i,j)
     &       - phyFac*dPhiHydY(i,j)
     &        )*maskS(i,j,k,bi,bj)
        ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE THE_CORRECTION_STEP(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      Real*8 phiSurfX(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 phiSurfY(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      INTEGER iMin,iMax
      INTEGER jMin,jMax
      INTEGER bi,bj
      INTEGER k,i,j
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          phiSurfX(i,j)=0.
          phiSurfY(i,j)=0.
         ENDDO
        ENDDO
        iMin = 1-OLx+1
        iMax = sNx+OLx
        jMin = 1-OLy+1
        jMax = sNy+OLy
        CALL CALC_GRAD_PHI_SURF(
     I       bi,bj,iMin,iMax,jMin,jMax,
     I       etaN,
     O       phiSurfX,phiSurfY,
     I       myThid )
        DO K=1,Nr
          IF (momStepping)
     &      CALL CORRECTION_STEP(
     I         bi,bj,iMin,iMax,jMin,jMax,K,
     I         phiSurfX,phiSurfY,myTime,myThid )
          IF (tempStepping)
     &      CALL CYCLE_TRACER(
     I           bi,bj,K,
     U           theta,gT,
     I           myTime,myIter,myThid )
          IF (saltStepping)
     &      CALL CYCLE_TRACER(
     I           bi,bj,K,
     U           salt,gS,
     I           myTime,myIter,myThid )
        ENDDO
        iMin = 1
        iMax = sNx
        jMin = 1
        jMax = sNy
         CALL CONVECTIVE_ADJUSTMENT(
     I        bi, bj, iMin, iMax, jMin, jMax,
     I        myTime, myIter, myThid )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE THE_MAIN_LOOP( myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE GRID_mod
       USE DYNVARS_mod
       USE FFIELDS_mod
       USE EOS_mod
       USE GAD_mod
       USE CD_CODE_VARS_mod
       USE tamc_mod
       USE ctrl_mod
       USE ctrl_dummy_mod
       USE cost_mod
      INTEGER myThid 
      INTEGER myIter
      Real*8     myTime
      LOGICAL RUNCLOCK_CONTINUE
      LOGICAL RC_CONT
      integer iloop
      integer ilev_1
      integer ilev_2
      integer ilev_3
      integer ilev_4
      integer max_lev2
      integer max_lev3
      integer max_lev4
      IF (debugMode) CALL DEBUG_ENTER('THE_MAIN_LOOP',myThid)
      nIter0 = NINT( (startTime-baseTime)/deltaTClock )
      ikey_dynamics = 1
      CALL TIMER_START('ADJOINT SPIN-UP', mythid)
      IF (debugMode) CALL DEBUG_CALL('INITIALISE_VARIA',myThid)
      CALL TIMER_START('INITIALISE_VARIA    [THE_MAIN_LOOP]', mythid)
      CALL INITIALISE_VARIA( mythid )
      CALL TIMER_STOP ('INITIALISE_VARIA    [THE_MAIN_LOOP]', mythid)
      IF (debugMode) CALL DEBUG_CALL('DO_THE_MODEL_IO',myThid)
      CALL TIMER_START('DO_THE_MODEL_IO     [THE_MAIN_LOOP]', mythid)
      CALL DO_THE_MODEL_IO( myTime, myIter, mythid )
      CALL TIMER_STOP ('DO_THE_MODEL_IO     [THE_MAIN_LOOP]', mythid)
      CALL TIMER_STOP ('ADJOINT SPIN-UP', mythid)
      CALL BARRIER(myThid)
      CALL TIMER_START('MAIN LOOP           [THE_MAIN_LOOP]', mythid)
      max_lev4=nTimeSteps/(nchklev_1*nchklev_2*nchklev_3)+1
      max_lev3=nTimeSteps/(nchklev_1*nchklev_2)+1
      max_lev2=nTimeSteps/nchklev_1+1
      do ilev_3 = 1,nchklev_3
         if(ilev_3.le.max_lev3) then
        do ilev_2 = 1,nchklev_2
         if(ilev_2.le.max_lev2) then
          do ilev_1 = 1,nchklev_1
            iloop = (ilev_2 - 1)*nchklev_1                     + ilev_1
     &            + (ilev_3 - 1)*nchklev_2*nchklev_1
            if ( iloop .le. nTimeSteps ) then
        nIter0 = NINT( (startTime-baseTime)/deltaTClock )
        ikey_dynamics = ilev_1
        CALL AUTODIFF_INADMODE_UNSET( myThid )
        CALL AUTODIFF_INADMODE_UNSET( myThid )
      IF (debugMode) CALL DEBUG_CALL('FORWARD_STEP',myThid)
        CALL TIMER_START('FORWARD_STEP        [THE_MAIN_LOOP]',mythid)
        CALL FORWARD_STEP( iloop, mytime, myiter, mythid )
        CALL TIMER_STOP ('FORWARD_STEP        [THE_MAIN_LOOP]',mythid)
        CALL AUTODIFF_INADMODE_SET( myThid )
        CALL AUTODIFF_INADMODE_SET( myThid )
            endif
          enddo
          endif
        enddo
        endif
      enddo
      call TIMER_START('COST_FINAL         [ADJOINT SPIN-DOWN]', mythid)
      call COST_FINAL ( mythid )
      call TIMER_STOP ('COST_FINAL         [ADJOINT SPIN-DOWN]', mythid)
      CALL BARRIER(myThid)
      CALL TIMER_STOP ('MAIN LOOP           [THE_MAIN_LOOP]', mythid)
      IF (debugMode) CALL DEBUG_LEAVE('THE_MAIN_LOOP',myThid)
      END
      SUBROUTINE THERMODYNAMICS(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE GAD_mod
       USE tamc_mod
       USE tamc_keys_mod
       USE FFIELDS_mod
       USE EOS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      Real*8 xA      (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 yA      (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 uTrans  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 vTrans  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTrans  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 rTransKp1(1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 maskUp  (1-OLx:sNx+OLx,1-OLy:sNy+OLy)
      Real*8 fVerT   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 fVerS   (1-OLx:sNx+OLx,1-OLy:sNy+OLy,2)
      Real*8 kappaRT (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 kappaRS (1-Olx:sNx+Olx,1-Oly:sNy+Oly)
      Real*8 kappaRk (1-Olx:sNx+Olx,1-Oly:sNy+Oly,Nr)
      Real*8 kp1Msk
      LOGICAL useVariableK
      INTEGER iMin, iMax
      INTEGER jMin, jMax
      INTEGER bi, bj
      INTEGER i, j
      INTEGER k, km1, kup, kDown
      INTEGER iTracer, ip
         IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_ENTER('THERMODYNAMICS',myThid)
      ikey = 1
      itdkey = 1
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
          act1 = bi - myBxLo(myThid)
          max1 = myBxHi(myThid) - myBxLo(myThid) + 1
          act2 = bj - myByLo(myThid)
          max2 = myByHi(myThid) - myByLo(myThid) + 1
          act3 = myThid - 1
          max3 = nTx*nTy
          act4 = ikey_dynamics - 1
          itdkey = (act1 + 1) + act2*max1
     &                      + act3*max1*max2
     &                      + act4*max1*max2*max3
        DO j=1-OLy,sNy+OLy
         DO i=1-OLx,sNx+OLx
          xA(i,j)        = 0.d0
          yA(i,j)        = 0.d0
          uTrans(i,j)    = 0.d0
          vTrans(i,j)    = 0.d0
          rTrans (i,j)   = 0.d0
          rTransKp1(i,j) = 0.d0
          fVerT  (i,j,1) = 0.d0
          fVerT  (i,j,2) = 0.d0
          fVerS  (i,j,1) = 0.d0
          fVerS  (i,j,2) = 0.d0
          kappaRT(i,j)   = 0.d0
          kappaRS(i,j)   = 0.d0
         ENDDO
        ENDDO
        DO k=1,Nr
         DO j=1-OLy,sNy+OLy
          DO i=1-OLx,sNx+OLx
           kappaRk(i,j,k)    = 0.d0
           gT(i,j,k,bi,bj)   = 0.d0
           gS(i,j,k,bi,bj)   = 0.d0
          ENDDO
         ENDDO
        ENDDO
        IF (tempMultiDimAdvec) THEN
          IF ( debugLevel .GE. debLevB ) 
     &     CALL DEBUG_CALL('GAD_ADVECTION',myThid)
          CALL GAD_ADVECTION(
     I             tempImplVertAdv, tempAdvScheme, tempVertAdvScheme,
     I             GAD_TEMPERATURE,
     I             uVel, vVel, wVel, theta,
     O             gT,
     I             bi,bj,myTime,myIter,myThid)
        ENDIF
        IF (saltMultiDimAdvec) THEN
          IF ( debugLevel .GE. debLevB ) 
     &     CALL DEBUG_CALL('GAD_ADVECTION',myThid)
          CALL GAD_ADVECTION(
     I             saltImplVertAdv, saltAdvScheme, saltVertAdvScheme,
     I             GAD_SALINITY,
     I             uVel, vVel, wVel, salt,
     O             gS,
     I             bi,bj,myTime,myIter,myThid)
        ENDIF
        IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_MSG('ENTERING DOWNWARD K LOOP',myThid)
        DO k=Nr,1,-1
         kkey = (itdkey-1)*Nr + k
          km1  = MAX(1,k-1)
          kup  = 1+MOD(k+1,2)
          kDown= 1+MOD(k,2)
          iMin = 1-OLx
          iMax = sNx+OLx
          jMin = 1-OLy
          jMax = sNy+OLy
          kp1Msk=1.
          IF (k.EQ.Nr) kp1Msk=0.
           DO j=1-Oly,sNy+Oly
            DO i=1-Olx,sNx+Olx
             rTransKp1(i,j) = kp1Msk*rTrans(i,j)
            ENDDO
           ENDDO
          CALL CALC_COMMON_FACTORS (
     I         bi,bj,iMin,iMax,jMin,jMax,k,
     O         xA,yA,uTrans,vTrans,rTrans,maskUp,
     I         myThid)
          IF (k.EQ.1) THEN
           DO j=1-Oly,sNy+Oly
            DO i=1-Olx,sNx+Olx
             rTrans(i,j) = 0.
            ENDDO
           ENDDO
          ELSE
           DO j=1-Oly,sNy+Oly
            DO i=1-Olx,sNx+Olx
             rTrans(i,j) = rTrans(i,j)*maskC(i,j,k-1,bi,bj)
            ENDDO
           ENDDO
          ENDIF
          IF ( .NOT.implicitDiffusion ) THEN
            CALL CALC_DIFFUSIVITY(
     I          bi,bj,iMin,iMax,jMin,jMax,k,
     I          maskUp,
     O          kappaRT,kappaRS,
     I          myThid)
          ENDIF
          iMin = 1-OLx+2
          iMax = sNx+OLx-1
          jMin = 1-OLy+2
          jMax = sNy+OLy-1
         IF ( tempStepping ) THEN
           CALL CALC_GT(
     I         bi,bj,iMin,iMax,jMin,jMax, k,km1,kup,kDown,
     I         xA,yA,uTrans,vTrans,rTrans,rTransKp1,maskUp,
     I         kappaRT,
     U         fVerT,
     I         myTime,myIter,myThid)
           CALL TIMESTEP_TRACER(
     I         bi,bj,iMin,iMax,jMin,jMax,k,tempAdvScheme,
     I         theta, gT,
     I         myIter, myThid)
         ENDIF
         IF ( saltStepping ) THEN
           CALL CALC_GS(
     I         bi,bj,iMin,iMax,jMin,jMax, k,km1,kup,kDown,
     I         xA,yA,uTrans,vTrans,rTrans,rTransKp1,maskUp,
     I         kappaRS,
     U         fVerS,
     I         myTime,myIter,myThid)
           CALL TIMESTEP_TRACER(
     I         bi,bj,iMin,iMax,jMin,jMax,k,saltAdvScheme,
     I         salt, gS,
     I         myIter, myThid)
         ENDIF
         IF ( useOldFreezing .AND. .NOT. useSEAICE
     &       .AND. .NOT.(useThSIce.AND.k.EQ.1) ) THEN
            CALL FREEZE( bi, bj, iMin, iMax, jMin, jMax, k, myThid )
         ENDIF
        ENDDO
        iMin = 1
        iMax = sNx
        jMin = 1
        jMax = sNy
        IF ( tempStepping .AND. implicitDiffusion ) THEN
          CALL CALC_3D_DIFFUSIVITY(
     I         bi,bj,iMin,iMax,jMin,jMax,
     I         GAD_TEMPERATURE, useGMredi, useKPP,
     O         kappaRk,
     I         myThid)
        ENDIF
        IF     ( tempStepping .AND. implicitDiffusion ) THEN
          CALL IMPLDIFF(
     I         bi, bj, iMin, iMax, jMin, jMax,
     I         GAD_TEMPERATURE, kappaRk, recip_hFacC,
     U         gT,
     I         myThid )
        ENDIF
        IF ( saltStepping .AND. implicitDiffusion ) THEN
          CALL CALC_3D_DIFFUSIVITY(
     I         bi,bj,iMin,iMax,jMin,jMax,
     I         GAD_SALINITY, useGMredi, useKPP,
     O         kappaRk,
     I         myThid)
        ENDIF
        IF     ( saltStepping .AND. implicitDiffusion ) THEN
          CALL IMPLDIFF(
     I         bi, bj, iMin, iMax, jMin, jMax,
     I         GAD_SALINITY, kappaRk, recip_hFacC,
     U         gS,
     I         myThid )
        ENDIF
       ENDDO
      ENDDO
      If (debugMode) THEN
       CALL DEBUG_STATS_RL(Nr,uVel,'Uvel (THERMODYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,vVel,'Vvel (THERMODYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,wVel,'Wvel (THERMODYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,theta,'Theta (THERMODYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,salt,'Salt (THERMODYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gT,'Gt (THERMODYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gS,'Gs (THERMODYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gtNm1,'GtNm1 (THERMODYNAMICS)',myThid)
       CALL DEBUG_STATS_RL(Nr,gsNm1,'GsNm1 (THERMODYNAMICS)',myThid)
      ENDIF
         IF ( debugLevel .GE. debLevB ) 
     &    CALL DEBUG_LEAVE('THERMODYNAMICS',myThid)
      RETURN
      END
      SUBROUTINE TIMESTEP_TRACER(
     I                     bi, bj, iMin, iMax, jMin, jMax, K,
     I                     advection_scheme,
     I                     tracer, gTracer,
     I                     myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
      INTEGER bi,bj,iMin,iMax,jMin,jMax,K
      INTEGER advection_scheme
      Real*8  tracer (1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      Real*8  gTracer(1-OLx:sNx+OLx,1-OLy:sNy+OLy,Nr,nSx,nSy)
      INTEGER myIter, myThid
      INTEGER i,j
      DO j=jMin,jMax
       DO i=iMin,iMax
         gTracer(i,j,k,bi,bj)=tracer(i,j,k,bi,bj)
     &            +dTtracerLev(k)*gTracer(i,j,k,bi,bj)
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE TRACERS_CORRECTION_STEP(myTime, myIter, myThid)
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      INTEGER iMin,iMax
      INTEGER jMin,jMax
      INTEGER bi,bj
      INTEGER k,i,j
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        DO K=1,Nr
          IF (tempStepping)
     &      CALL CYCLE_TRACER(
     I           bi,bj,K,
     U           theta,gT,
     I           myTime,myIter,myThid )
          IF (saltStepping)
     &      CALL CYCLE_TRACER(
     I           bi,bj,k,
     U           salt,gS,
     I           myTime,myIter,myThid )
        ENDDO
       ENDDO
      ENDDO
      DO bj=myByLo(myThid),myByHi(myThid)
       DO bi=myBxLo(myThid),myBxHi(myThid)
        iMin = 1
        iMax = sNx
        jMin = 1
        jMax = sNy
         CALL CONVECTIVE_ADJUSTMENT(
     I        bi, bj, iMin, iMax, jMin, jMax,
     I        myTime, myIter, myThid )
       ENDDO
      ENDDO
      RETURN
      END
      SUBROUTINE UPDATE_ETAH( myTime, myIter, myThid )
       USE SIZE_mod
       USE EEPARAMS_mod
       USE PARAMS_mod
       USE DYNVARS_mod
       USE GRID_mod
       USE SURFACE_mod
       USE FFIELDS_mod
      Real*8 myTime
      INTEGER myIter
      INTEGER myThid
      RETURN
      END
      SUBROUTINE SWFRAC(
     I     imax, fact,
     I     mytime, mythid,
     U     swdk )
      IMPLICIT NONE
      INTEGER imax
      Real*8     fact
      Real*8     mytime
      integer mythid
      Real*8     swdk(imax)
      integer   nwtype  , jwtype
      PARAMETER(nwtype=5)
      Real*8 facz
      Real*8 rfac(nwtype),a1(nwtype),a2(nwtype)
      INTEGER i
      DATA rfac         /  0.58 ,  0.62 ,  0.67 ,  0.77 ,  0.78 /
      DATA a1           /  0.35 ,  0.6  ,  1.0  ,  1.5  ,  1.4  /
      DATA a2           / 23.0  , 20.0  , 17.0  , 14.0  ,  7.9  /
      jwtype=2
      DO i = 1,imax
         facz = fact*swdk(i)
         IF (facz .LT. (-200.)) THEN
            swdk(i) = 0.
         ELSE
            swdk(i) =       rfac(jwtype)  * exp(facz/a1(jwtype))
     $                + (1.-rfac(jwtype)) * exp(facz/a2(jwtype))
         ENDIF
      ENDDO
      RETURN
      END
