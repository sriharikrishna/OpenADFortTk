use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTscan;
use FTpat;

use PPsetup;

setup();

is($ff->rewrite_sem(\&x2wp)->to_string(),$w2f1_pp,'xaif pp ok');

teardown();

sub setup{
    $w2f1 = <<'W2F1';
C ***********************************************************
C Fortran file translated from WHIRL Wed Sep 17 12:31:15 2003
C ***********************************************************
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

      SUBROUTINE box_ini_params()
      use w2f__types
      IMPLICIT NONE
C
C     **** Variables and functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) L
      COMMON /pa_density_r/ ALPHA, BETA
      REAL(w2f__8) ALPHA
      REAL(w2f__8) BETA
      COMMON /pa_geometry_r/ BLENGTH, BHEIGHT, BWIDTH, AREA, VOL
      REAL(w2f__8) BLENGTH(1 : 3)
      REAL(w2f__8) BHEIGHT(1 : 3)
      REAL(w2f__8) BWIDTH
      REAL(w2f__8) AREA(1 : 3)
      REAL(w2f__8) VOL(1 : 3)
      COMMON /pa_parameters_r/ HUNDRED, THOUSAND, DAY, YEAR, SV,
     >  DAYS_PER_50M_MIXED_LAYER, GAMMA_T, GAMMA_S, EPSILON_IC,
     >  NOISE_CORRELATION_TIME, INTEGRATION_TIME, EPSILON_REGULARIZE,
     >  FDEPS
      REAL(w2f__8) HUNDRED
      REAL(w2f__8) THOUSAND
      REAL(w2f__8) DAY
      REAL(w2f__8) YEAR
      REAL(w2f__8) SV
      REAL(w2f__8) DAYS_PER_50M_MIXED_LAYER
      REAL(w2f__8) GAMMA_T
      REAL(w2f__8) GAMMA_S
      REAL(w2f__8) EPSILON_IC
      REAL(w2f__8) NOISE_CORRELATION_TIME
      REAL(w2f__8) INTEGRATION_TIME
      REAL(w2f__8) EPSILON_REGULARIZE
      REAL(w2f__8) FDEPS
      COMMON /pa_transport_r/ U0, DELTA
      REAL(w2f__8) U0
      REAL(w2f__8) DELTA
      COMMON /pa_timestep_r/ DELTA_T
      REAL(w2f__8) DELTA_T
      COMMON /pa_numbers_i/ N_MAX
      INTEGER(w2f__i4) N_MAX
      COMMON /pa_algebra_r/ Y, R, R1, R_T, R_S, PROJ_T, PROJ_S, X
      REAL(w2f__8) Y(1 : 6)
      REAL(w2f__8) R(1 : 6)
      REAL(w2f__8) R1(1 : 6)
      REAL(w2f__8) R_T(1 : 6)
      REAL(w2f__8) R_S(1 : 6)
      REAL(w2f__8) PROJ_T(1 : 6)
      REAL(w2f__8) PROJ_S(1 : 6)
      REAL(w2f__8) X(1 : 6, 1 : 6)
      COMMON /pa_robert_filter_r/ ROBERT_FILTER_COEFF
      REAL(w2f__8) ROBERT_FILTER_COEFF
      COMMON /pa_switches_l/ VERBMODE
      LOGICAL(w2f__i4) VERBMODE
      REAL(w2f__8) SymbolTable_0x81ed9a0_100
      REAL(w2f__8) SymbolTable_0x81ed9a0_101
      REAL(w2f__8) SymbolTable_0x81ed9a0_102
      REAL(w2f__8) SymbolTable_0x81ed9a0_0
      REAL(w2f__8) SymbolTable_0x81ed9a0_300
      REAL(w2f__8) SymbolTable_0x81ed9a0_1
      REAL(w2f__8) SymbolTable_0x81ed9a0_301
      REAL(w2f__8) SymbolTable_0x81ed9a0_2
      REAL(w2f__8) SymbolTable_0x81ed9a0_302
      REAL(w2f__8) SymbolTable_0x81ed9a0_3
      REAL(w2f__8) SymbolTable_0x81ed9a0_303
      REAL(w2f__8) SymbolTable_0x81ed9a0_4
      REAL(w2f__8) SymbolTable_0x81ed9a0_304
      REAL(w2f__8) SymbolTable_0x81ed9a0_5
      REAL(w2f__8) SymbolTable_0x81ed9a0_310
      REAL(w2f__8) SymbolTable_0x81ed9a0_305
      REAL(w2f__8) SymbolTable_0x81ed9a0_6
      REAL(w2f__8) SymbolTable_0x81ed9a0_311
      REAL(w2f__8) SymbolTable_0x81ed9a0_306
      REAL(w2f__8) SymbolTable_0x81ed9a0_7
      REAL(w2f__8) SymbolTable_0x81ed9a0_312
      REAL(w2f__8) SymbolTable_0x81ed9a0_307
      REAL(w2f__8) SymbolTable_0x81ed9a0_8
      REAL(w2f__8) SymbolTable_0x81ed9a0_313
      REAL(w2f__8) SymbolTable_0x81ed9a0_308
      REAL(w2f__8) SymbolTable_0x81ed9a0_9
      REAL(w2f__8) SymbolTable_0x81ed9a0_314
      REAL(w2f__8) SymbolTable_0x81ed9a0_309
      REAL(w2f__8) SymbolTable_0x81ed9a0_320
      REAL(w2f__8) SymbolTable_0x81ed9a0_315
      REAL(w2f__8) SymbolTable_0x81ed9a0_321
      REAL(w2f__8) SymbolTable_0x81ed9a0_316
      REAL(w2f__8) SymbolTable_0x81ed9a0_322
      REAL(w2f__8) SymbolTable_0x81ed9a0_317
      REAL(w2f__8) SymbolTable_0x81ed9a0_323
      REAL(w2f__8) SymbolTable_0x81ed9a0_318
      REAL(w2f__8) SymbolTable_0x81ed9a0_324
      REAL(w2f__8) SymbolTable_0x81ed9a0_319
      REAL(w2f__8) SymbolTable_0x81ed9a0_274
      REAL(w2f__8) SymbolTable_0x81ed9a0_330
      REAL(w2f__8) SymbolTable_0x81ed9a0_325
      REAL(w2f__8) SymbolTable_0x81ed9a0_275
      REAL(w2f__8) SymbolTable_0x81ed9a0_280
      REAL(w2f__8) SymbolTable_0x81ed9a0_331
      REAL(w2f__8) SymbolTable_0x81ed9a0_326
      REAL(w2f__8) SymbolTable_0x81ed9a0_276
      REAL(w2f__8) SymbolTable_0x81ed9a0_281
      REAL(w2f__8) SymbolTable_0x81ed9a0_332
      REAL(w2f__8) SymbolTable_0x81ed9a0_327
      REAL(w2f__8) SymbolTable_0x81ed9a0_277
      REAL(w2f__8) SymbolTable_0x81ed9a0_282
      REAL(w2f__8) SymbolTable_0x81ed9a0_333
      REAL(w2f__8) SymbolTable_0x81ed9a0_328
      REAL(w2f__8) SymbolTable_0x81ed9a0_278
      REAL(w2f__8) SymbolTable_0x81ed9a0_283
      REAL(w2f__8) SymbolTable_0x81ed9a0_334
      REAL(w2f__8) SymbolTable_0x81ed9a0_329
      REAL(w2f__8) SymbolTable_0x81ed9a0_279
      REAL(w2f__8) SymbolTable_0x81ed9a0_284
      REAL(w2f__8) SymbolTable_0x81ed9a0_340
      REAL(w2f__8) SymbolTable_0x81ed9a0_335
      REAL(w2f__8) SymbolTable_0x81ed9a0_285
      REAL(w2f__8) SymbolTable_0x81ed9a0_290
      REAL(w2f__8) SymbolTable_0x81ed9a0_341
      REAL(w2f__8) SymbolTable_0x81ed9a0_336
      REAL(w2f__8) SymbolTable_0x81ed9a0_286
      REAL(w2f__8) SymbolTable_0x81ed9a0_291
      REAL(w2f__8) SymbolTable_0x81ed9a0_342
      REAL(w2f__8) SymbolTable_0x81ed9a0_337
      REAL(w2f__8) SymbolTable_0x81ed9a0_287
      REAL(w2f__8) SymbolTable_0x81ed9a0_292
      REAL(w2f__8) SymbolTable_0x81ed9a0_343
      REAL(w2f__8) SymbolTable_0x81ed9a0_338
      REAL(w2f__8) SymbolTable_0x81ed9a0_288
      REAL(w2f__8) SymbolTable_0x81ed9a0_293
      REAL(w2f__8) SymbolTable_0x81ed9a0_344
      REAL(w2f__8) SymbolTable_0x81ed9a0_339
      REAL(w2f__8) SymbolTable_0x81ed9a0_289
      REAL(w2f__8) SymbolTable_0x81ed9a0_294
      REAL(w2f__8) SymbolTable_0x81ed9a0_350
      REAL(w2f__8) SymbolTable_0x81ed9a0_345
      REAL(w2f__8) SymbolTable_0x81ed9a0_295
      REAL(w2f__8) SymbolTable_0x81ed9a0_351
      REAL(w2f__8) SymbolTable_0x81ed9a0_346
      REAL(w2f__8) SymbolTable_0x81ed9a0_296
      REAL(w2f__8) SymbolTable_0x81ed9a0_352
      REAL(w2f__8) SymbolTable_0x81ed9a0_347
      REAL(w2f__8) SymbolTable_0x81ed9a0_297
      REAL(w2f__8) SymbolTable_0x81ed9a0_353
      REAL(w2f__8) SymbolTable_0x81ed9a0_348
      REAL(w2f__8) SymbolTable_0x81ed9a0_298
      REAL(w2f__8) SymbolTable_0x81ed9a0_354
      REAL(w2f__8) SymbolTable_0x81ed9a0_349
      REAL(w2f__8) SymbolTable_0x81ed9a0_299
      REAL(w2f__8) SymbolTable_0x81ed9a0_360
      REAL(w2f__8) SymbolTable_0x81ed9a0_355
      REAL(w2f__8) SymbolTable_0x81ed9a0_361
      REAL(w2f__8) SymbolTable_0x81ed9a0_356
      REAL(w2f__8) SymbolTable_0x81ed9a0_362
      REAL(w2f__8) SymbolTable_0x81ed9a0_357
      REAL(w2f__8) SymbolTable_0x81ed9a0_363
      REAL(w2f__8) SymbolTable_0x81ed9a0_358
      REAL(w2f__8) SymbolTable_0x81ed9a0_364
      REAL(w2f__8) SymbolTable_0x81ed9a0_359
      REAL(w2f__8) SymbolTable_0x81ed9a0_370
      REAL(w2f__8) SymbolTable_0x81ed9a0_365
      REAL(w2f__8) SymbolTable_0x81ed9a0_371
      REAL(w2f__8) SymbolTable_0x81ed9a0_366
      REAL(w2f__8) SymbolTable_0x81ed9a0_372
      REAL(w2f__8) SymbolTable_0x81ed9a0_367
      REAL(w2f__8) SymbolTable_0x81ed9a0_373
      REAL(w2f__8) SymbolTable_0x81ed9a0_368
      REAL(w2f__8) SymbolTable_0x81ed9a0_374
      REAL(w2f__8) SymbolTable_0x81ed9a0_369
      REAL(w2f__8) SymbolTable_0x81ed9a0_380
      REAL(w2f__8) SymbolTable_0x81ed9a0_375
      REAL(w2f__8) SymbolTable_0x81ed9a0_381
      REAL(w2f__8) SymbolTable_0x81ed9a0_376
      REAL(w2f__8) SymbolTable_0x81ed9a0_382
      REAL(w2f__8) SymbolTable_0x81ed9a0_377
      REAL(w2f__8) SymbolTable_0x81ed9a0_383
      REAL(w2f__8) SymbolTable_0x81ed9a0_378
      REAL(w2f__8) SymbolTable_0x81ed9a0_384
      REAL(w2f__8) SymbolTable_0x81ed9a0_379
      REAL(w2f__8) SymbolTable_0x81ed9a0_385
      REAL(w2f__8) SymbolTable_0x81ed9a0_386
      REAL(w2f__8) SymbolTable_0x81ed9a0_10
      REAL(w2f__8) SymbolTable_0x81ed9a0_11
      REAL(w2f__8) SymbolTable_0x81ed9a0_12
      REAL(w2f__8) SymbolTable_0x81ed9a0_13
      REAL(w2f__8) SymbolTable_0x81ed9a0_14
      REAL(w2f__8) SymbolTable_0x81ed9a0_15
      REAL(w2f__8) SymbolTable_0x81ed9a0_20
      REAL(w2f__8) SymbolTable_0x81ed9a0_16
      REAL(w2f__8) SymbolTable_0x81ed9a0_21
      REAL(w2f__8) SymbolTable_0x81ed9a0_17
      REAL(w2f__8) SymbolTable_0x81ed9a0_22
      REAL(w2f__8) SymbolTable_0x81ed9a0_18
      REAL(w2f__8) SymbolTable_0x81ed9a0_23
      REAL(w2f__8) SymbolTable_0x81ed9a0_19
      REAL(w2f__8) SymbolTable_0x81ed9a0_24
      REAL(w2f__8) SymbolTable_0x81ed9a0_26
      REAL(w2f__8) SymbolTable_0x81ed9a0_31
      REAL(w2f__8) SymbolTable_0x81ed9a0_27
      REAL(w2f__8) SymbolTable_0x81ed9a0_32
      REAL(w2f__8) SymbolTable_0x81ed9a0_29
      REAL(w2f__8) SymbolTable_0x81ed9a0_34
      REAL(w2f__8) SymbolTable_0x81ed9a0_35
      REAL(w2f__8) SymbolTable_0x81ed9a0_40
      REAL(w2f__8) SymbolTable_0x81ed9a0_41
      REAL(w2f__8) SymbolTable_0x81ed9a0_37
      REAL(w2f__8) SymbolTable_0x81ed9a0_42
      REAL(w2f__8) SymbolTable_0x81ed9a0_38
      REAL(w2f__8) SymbolTable_0x81ed9a0_43
      REAL(w2f__8) SymbolTable_0x81ed9a0_44
      REAL(w2f__8) SymbolTable_0x81ed9a0_45
      REAL(w2f__8) SymbolTable_0x81ed9a0_50
      REAL(w2f__8) SymbolTable_0x81ed9a0_47
      REAL(w2f__8) SymbolTable_0x81ed9a0_52
      REAL(w2f__8) SymbolTable_0x81ed9a0_48
      REAL(w2f__8) SymbolTable_0x81ed9a0_49
      REAL(w2f__8) SymbolTable_0x81ed9a0_54
      REAL(w2f__8) SymbolTable_0x81ed9a0_60
      REAL(w2f__8) SymbolTable_0x81ed9a0_56
      REAL(w2f__8) SymbolTable_0x81ed9a0_57
      REAL(w2f__8) SymbolTable_0x81ed9a0_62
      REAL(w2f__8) SymbolTable_0x81ed9a0_58
      REAL(w2f__8) SymbolTable_0x81ed9a0_64
      REAL(w2f__8) SymbolTable_0x81ed9a0_70
      REAL(w2f__8) SymbolTable_0x81ed9a0_66
      REAL(w2f__8) SymbolTable_0x81ed9a0_71
      REAL(w2f__8) SymbolTable_0x81ed9a0_72
      REAL(w2f__8) SymbolTable_0x81ed9a0_68
      REAL(w2f__8) SymbolTable_0x81ed9a0_73
      REAL(w2f__8) SymbolTable_0x81ed9a0_74
      REAL(w2f__8) SymbolTable_0x81ed9a0_75
      REAL(w2f__8) SymbolTable_0x81ed9a0_80
      REAL(w2f__8) SymbolTable_0x81ed9a0_81
      REAL(w2f__8) SymbolTable_0x81ed9a0_77
      REAL(w2f__8) SymbolTable_0x81ed9a0_82
      REAL(w2f__8) SymbolTable_0x81ed9a0_78
      REAL(w2f__8) SymbolTable_0x81ed9a0_83
      REAL(w2f__8) SymbolTable_0x81ed9a0_79
      REAL(w2f__8) SymbolTable_0x81ed9a0_84
      REAL(w2f__8) SymbolTable_0x81ed9a0_85
      REAL(w2f__8) SymbolTable_0x81ed9a0_90
      REAL(w2f__8) SymbolTable_0x81ed9a0_91
      REAL(w2f__8) SymbolTable_0x81ed9a0_87
      REAL(w2f__8) SymbolTable_0x81ed9a0_92
      REAL(w2f__8) SymbolTable_0x81ed9a0_88
      REAL(w2f__8) SymbolTable_0x81ed9a0_93
      REAL(w2f__8) SymbolTable_0x81ed9a0_89
      REAL(w2f__8) SymbolTable_0x81ed9a0_94
      REAL(w2f__8) SymbolTable_0x81ed9a0_95
      REAL(w2f__8) SymbolTable_0x81ed9a0_96
      REAL(w2f__8) SymbolTable_0x81ed9a0_97
      REAL(w2f__8) SymbolTable_0x81ed9a0_98
      REAL(w2f__8) SymbolTable_0x81ed9a0_99
C
C     **** statements ****
C
      __value__(VERBMODE) = 0.0D00
      __value__(BLENGTH(1)) = 5.0D00
      __value__(BLENGTH(2)) = 1.0D00
      __value__(BLENGTH(3)) = __value__(BLENGTH(1))
      CALL sax_a_a(1.0D00, __value__(BLENGTH(1)), __value__(BLENGTH(3))
     > )
      __value__(BHEIGHT(1)) = 1.0D00
      __value__(BHEIGHT(3)) = 4.0D00
      __value__(SymbolTable_0x81ed9a0_275) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x81ed9a0_277) = __value__(BHEIGHT(3))
      __value__(BHEIGHT(2)) = (__value__(BHEIGHT(1)) + __value__(
     > BHEIGHT(3)))
      __value__(SymbolTable_0x81ed9a0_0) = 1.0D00
      __value__(SymbolTable_0x81ed9a0_1) = 1.0D00
      __value__(SymbolTable_0x81ed9a0_274) = __value__(
     > SymbolTable_0x81ed9a0_0)
      __value__(SymbolTable_0x81ed9a0_276) = __value__(
     > SymbolTable_0x81ed9a0_1)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_274), __value__(
     > SymbolTable_0x81ed9a0_275), __value__(BHEIGHT(2)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_276), __value__(
     > SymbolTable_0x81ed9a0_277), __value__(BHEIGHT(2)))
      __value__(SymbolTable_0x81ed9a0_279) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x81ed9a0_281) = __value__(BHEIGHT(3))
      __value__(SymbolTable_0x81ed9a0_283) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x81ed9a0_2) = (__value__(BHEIGHT(1)) +
     >  __value__(BHEIGHT(3)))
      __value__(SymbolTable_0x81ed9a0_7) = (__value__(BHEIGHT(1)) /
     >  __value__(SymbolTable_0x81ed9a0_2))
      __value__(SymbolTable_0x81ed9a0_3) = (1D00 / __value__(
     > SymbolTable_0x81ed9a0_2))
      __value__(SymbolTable_0x81ed9a0_5) = 1.0D00
      __value__(SymbolTable_0x81ed9a0_6) = 1.0D00
      __value__(SymbolTable_0x81ed9a0_4) = (-(__value__(BHEIGHT(1)) /
     >  SQRT(__value__(BHEIGHT(1)))))
      __value__(DELTA) = __value__(SymbolTable_0x81ed9a0_7)
      __value__(SymbolTable_0x81ed9a0_278) = (__value__(
     > SymbolTable_0x81ed9a0_5) * __value__(SymbolTable_0x81ed9a0_4))
      __value__(SymbolTable_0x81ed9a0_280) = (__value__(
     > SymbolTable_0x81ed9a0_6) * __value__(SymbolTable_0x81ed9a0_4))
      __value__(SymbolTable_0x81ed9a0_282) = __value__(
     > SymbolTable_0x81ed9a0_3)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_278), __value__(
     > SymbolTable_0x81ed9a0_279), __value__(DELTA))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_280), __value__(
     > SymbolTable_0x81ed9a0_281), __value__(DELTA))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_282), __value__(
     > SymbolTable_0x81ed9a0_283), __value__(DELTA))
      __value__(BWIDTH) = 4.0D00
      __value__(SymbolTable_0x81ed9a0_285) = __value__(BLENGTH(1))
      __value__(SymbolTable_0x81ed9a0_287) = __value__(BWIDTH)
      __value__(AREA(1)) = (__value__(BLENGTH(1)) * __value__(BWIDTH))
      __value__(SymbolTable_0x81ed9a0_8) = __value__(BWIDTH)
      __value__(SymbolTable_0x81ed9a0_9) = __value__(BLENGTH(1))
      __value__(SymbolTable_0x81ed9a0_284) = __value__(
     > SymbolTable_0x81ed9a0_8)
      __value__(SymbolTable_0x81ed9a0_286) = __value__(
     > SymbolTable_0x81ed9a0_9)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_284), __value__(
     > SymbolTable_0x81ed9a0_285), __value__(AREA(1)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_286), __value__(
     > SymbolTable_0x81ed9a0_287), __value__(AREA(1)))
      __value__(SymbolTable_0x81ed9a0_289) = __value__(BLENGTH(2))
      __value__(SymbolTable_0x81ed9a0_291) = __value__(BWIDTH)
      __value__(AREA(2)) = (__value__(BLENGTH(2)) * __value__(BWIDTH))
      __value__(SymbolTable_0x81ed9a0_10) = __value__(BWIDTH)
      __value__(SymbolTable_0x81ed9a0_11) = __value__(BLENGTH(2))
      __value__(SymbolTable_0x81ed9a0_288) = __value__(
     > SymbolTable_0x81ed9a0_10)
      __value__(SymbolTable_0x81ed9a0_290) = __value__(
     > SymbolTable_0x81ed9a0_11)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_288), __value__(
     > SymbolTable_0x81ed9a0_289), __value__(AREA(2)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_290), __value__(
     > SymbolTable_0x81ed9a0_291), __value__(AREA(2)))
      __value__(SymbolTable_0x81ed9a0_293) = __value__(BLENGTH(3))
      __value__(SymbolTable_0x81ed9a0_295) = __value__(BWIDTH)
      __value__(AREA(3)) = (__value__(BLENGTH(3)) * __value__(BWIDTH))
      __value__(SymbolTable_0x81ed9a0_12) = __value__(BWIDTH)
      __value__(SymbolTable_0x81ed9a0_13) = __value__(BLENGTH(3))
      __value__(SymbolTable_0x81ed9a0_292) = __value__(
     > SymbolTable_0x81ed9a0_12)
      __value__(SymbolTable_0x81ed9a0_294) = __value__(
     > SymbolTable_0x81ed9a0_13)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_292), __value__(
     > SymbolTable_0x81ed9a0_293), __value__(AREA(3)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_294), __value__(
     > SymbolTable_0x81ed9a0_295), __value__(AREA(3)))
      __value__(SymbolTable_0x81ed9a0_297) = __value__(AREA(1))
      __value__(SymbolTable_0x81ed9a0_299) = __value__(BHEIGHT(1))
      __value__(VOL(1)) = (__value__(AREA(1)) * __value__(BHEIGHT(1)))
      __value__(SymbolTable_0x81ed9a0_14) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x81ed9a0_15) = __value__(AREA(1))
      __value__(SymbolTable_0x81ed9a0_296) = __value__(
     > SymbolTable_0x81ed9a0_14)
      __value__(SymbolTable_0x81ed9a0_298) = __value__(
     > SymbolTable_0x81ed9a0_15)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_296), __value__(
     > SymbolTable_0x81ed9a0_297), __value__(VOL(1)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_298), __value__(
     > SymbolTable_0x81ed9a0_299), __value__(VOL(1)))
      __value__(SymbolTable_0x81ed9a0_301) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x81ed9a0_303) = __value__(BHEIGHT(3))
      __value__(SymbolTable_0x81ed9a0_305) = __value__(AREA(2))
      __value__(SymbolTable_0x81ed9a0_16) = (__value__(BHEIGHT(1)) +
     >  __value__(BHEIGHT(3)))
      __value__(SymbolTable_0x81ed9a0_21) = (__value__(AREA(2)) *
     >  __value__(SymbolTable_0x81ed9a0_16))
      __value__(SymbolTable_0x81ed9a0_17) = __value__(
     > SymbolTable_0x81ed9a0_16)
      __value__(SymbolTable_0x81ed9a0_19) = 1.0D00
      __value__(SymbolTable_0x81ed9a0_20) = 1.0D00
      __value__(SymbolTable_0x81ed9a0_18) = __value__(AREA(2))
      __value__(VOL(2)) = __value__(SymbolTable_0x81ed9a0_21)
      __value__(SymbolTable_0x81ed9a0_300) = (__value__(
     > SymbolTable_0x81ed9a0_19) * __value__(SymbolTable_0x81ed9a0_18))
      __value__(SymbolTable_0x81ed9a0_302) = (__value__(
     > SymbolTable_0x81ed9a0_20) * __value__(SymbolTable_0x81ed9a0_18))
      __value__(SymbolTable_0x81ed9a0_304) = __value__(
     > SymbolTable_0x81ed9a0_17)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_300), __value__(
     > SymbolTable_0x81ed9a0_301), __value__(VOL(2)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_302), __value__(
     > SymbolTable_0x81ed9a0_303), __value__(VOL(2)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_304), __value__(
     > SymbolTable_0x81ed9a0_305), __value__(VOL(2)))
      __value__(SymbolTable_0x81ed9a0_307) = __value__(AREA(3))
      __value__(SymbolTable_0x81ed9a0_309) = __value__(BHEIGHT(3))
      __value__(VOL(3)) = (__value__(AREA(3)) * __value__(BHEIGHT(3)))
      __value__(SymbolTable_0x81ed9a0_22) = __value__(BHEIGHT(3))
      __value__(SymbolTable_0x81ed9a0_23) = __value__(AREA(3))
      __value__(SymbolTable_0x81ed9a0_306) = __value__(
     > SymbolTable_0x81ed9a0_22)
      __value__(SymbolTable_0x81ed9a0_308) = __value__(
     > SymbolTable_0x81ed9a0_23)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_306), __value__(
     > SymbolTable_0x81ed9a0_307), __value__(VOL(3)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_308), __value__(
     > SymbolTable_0x81ed9a0_309), __value__(VOL(3)))
      __value__(ROBERT_FILTER_COEFF) = 2.5D00
      __value__(HUNDRED) = 1.0D00
      __value__(THOUSAND) = 1.0D00
      __value__(DAY) = 8.64000000000000056843D00
      __value__(SymbolTable_0x81ed9a0_311) = __value__(DAY)
      __value__(YEAR) = (__value__(DAY) * 3.64999999999999991118D00)
      __value__(SymbolTable_0x81ed9a0_24) = 3.64999999999999991118D00
      __value__(SymbolTable_0x81ed9a0_310) = __value__(
     > SymbolTable_0x81ed9a0_24)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_310), __value__(
     > SymbolTable_0x81ed9a0_311), __value__(YEAR))
      __value__(SV) = 1.0D00
      __value__(SymbolTable_0x81ed9a0_313) = __value__(SV)
      __value__(SymbolTable_0x81ed9a0_26) = (__value__(SV) *
     >  1.60000000000000008882D00)
      __value__(SymbolTable_0x81ed9a0_31) = (__value__(
     > SymbolTable_0x81ed9a0_26) * 2.5D-01)
      __value__(SymbolTable_0x81ed9a0_29) = 1.60000000000000008882D00
      __value__(SymbolTable_0x81ed9a0_27) = 2.5D-01
      __value__(U0) = __value__(SymbolTable_0x81ed9a0_31)
      __value__(SymbolTable_0x81ed9a0_312) = (__value__(
     > SymbolTable_0x81ed9a0_29) * __value__(SymbolTable_0x81ed9a0_27))
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_312), __value__(
     > SymbolTable_0x81ed9a0_313), __value__(U0))
      __value__(ALPHA) = 1.66799999999999992717D00
      __value__(BETA) = 7.8099999999999996092D00
      __value__(DAYS_PER_50M_MIXED_LAYER) = 5.0D00
      __value__(SymbolTable_0x81ed9a0_315) = __value__(DAY)
      __value__(SymbolTable_0x81ed9a0_32) = (__value__(DAY) * 3.0D00)
      __value__(SymbolTable_0x81ed9a0_37) = (1D00 / __value__(
     > SymbolTable_0x81ed9a0_32))
      __value__(SymbolTable_0x81ed9a0_35) = 3.0D00
      __value__(SymbolTable_0x81ed9a0_34) = (-1.0D00)
      __value__(GAMMA_T) = __value__(SymbolTable_0x81ed9a0_37)
      __value__(SymbolTable_0x81ed9a0_314) = (__value__(
     > SymbolTable_0x81ed9a0_35) * __value__(SymbolTable_0x81ed9a0_34))
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_314), __value__(
     > SymbolTable_0x81ed9a0_315), __value__(GAMMA_T))
      __value__(SymbolTable_0x81ed9a0_319) = __value__(DAY)
      __value__(SymbolTable_0x81ed9a0_321) = __value__(
     > DAYS_PER_50M_MIXED_LAYER)
      __value__(SymbolTable_0x81ed9a0_323) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x81ed9a0_41) = (__value__(BHEIGHT(1)) /
     >  5.0D00)
      __value__(SymbolTable_0x81ed9a0_42) = (__value__(DAY) * __value__
     > (DAYS_PER_50M_MIXED_LAYER))
      __value__(SymbolTable_0x81ed9a0_38) = (__value__(
     > SymbolTable_0x81ed9a0_41) * __value__(SymbolTable_0x81ed9a0_42))
      __value__(SymbolTable_0x81ed9a0_49) = (0.0D00 / __value__(
     > SymbolTable_0x81ed9a0_38))
      __value__(SymbolTable_0x81ed9a0_45) = 2.00000000000000011102D-01
      __value__(SymbolTable_0x81ed9a0_43) = __value__(
     > SymbolTable_0x81ed9a0_42)
      __value__(SymbolTable_0x81ed9a0_47) = __value__(
     > DAYS_PER_50M_MIXED_LAYER)
      __value__(SymbolTable_0x81ed9a0_48) = __value__(DAY)
      __value__(SymbolTable_0x81ed9a0_44) = __value__(
     > SymbolTable_0x81ed9a0_41)
      __value__(SymbolTable_0x81ed9a0_40) = (0.0D00 / -0.0D00)
      __value__(GAMMA_S) = __value__(SymbolTable_0x81ed9a0_49)
      __value__(SymbolTable_0x81ed9a0_316) = (__value__(
     > SymbolTable_0x81ed9a0_43) * __value__(SymbolTable_0x81ed9a0_40))
      __value__(SymbolTable_0x81ed9a0_317) = (__value__(
     > SymbolTable_0x81ed9a0_44) * __value__(SymbolTable_0x81ed9a0_40))
      __value__(SymbolTable_0x81ed9a0_318) = (__value__(
     > SymbolTable_0x81ed9a0_47) * __value__(SymbolTable_0x81ed9a0_317)
     > )
      __value__(SymbolTable_0x81ed9a0_320) = (__value__(
     > SymbolTable_0x81ed9a0_48) * __value__(SymbolTable_0x81ed9a0_317)
     > )
      __value__(SymbolTable_0x81ed9a0_322) = (__value__(
     > SymbolTable_0x81ed9a0_45) * __value__(SymbolTable_0x81ed9a0_316)
     > )
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_318), __value__(
     > SymbolTable_0x81ed9a0_319), __value__(GAMMA_S))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_320), __value__(
     > SymbolTable_0x81ed9a0_321), __value__(GAMMA_S))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_322), __value__(
     > SymbolTable_0x81ed9a0_323), __value__(GAMMA_S))
      __value__(EPSILON_IC) = (-1.0D00)
      __value__(SymbolTable_0x81ed9a0_325) = __value__(DAY)
      __value__(NOISE_CORRELATION_TIME) = (__value__(DAY) * 1.5D00)
      __value__(SymbolTable_0x81ed9a0_50) = 1.5D00
      __value__(SymbolTable_0x81ed9a0_324) = __value__(
     > SymbolTable_0x81ed9a0_50)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_324), __value__(
     > SymbolTable_0x81ed9a0_325), __value__(NOISE_CORRELATION_TIME))
      __value__(SymbolTable_0x81ed9a0_327) = __value__(DAY)
      __value__(DELTA_T) = (__value__(DAY) * 5.0D00)
      __value__(SymbolTable_0x81ed9a0_52) = 5.0D00
      __value__(SymbolTable_0x81ed9a0_326) = __value__(
     > SymbolTable_0x81ed9a0_52)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_326), __value__(
     > SymbolTable_0x81ed9a0_327), __value__(DELTA_T))
      WRITE(*, *) 'delta_t = ', __value__(DELTA_T)
      __value__(SymbolTable_0x81ed9a0_329) = __value__(YEAR)
      __value__(INTEGRATION_TIME) = (__value__(YEAR) * 5.0D00)
      __value__(SymbolTable_0x81ed9a0_54) = 5.0D00
      __value__(SymbolTable_0x81ed9a0_328) = __value__(
     > SymbolTable_0x81ed9a0_54)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_328), __value__(
     > SymbolTable_0x81ed9a0_329), __value__(INTEGRATION_TIME))
      WRITE(*, *) 'integration_time = ', __value__(INTEGRATION_TIME)
      __value__(SymbolTable_0x81ed9a0_331) = __value__(INTEGRATION_TIME
     > )
      __value__(SymbolTable_0x81ed9a0_333) = __value__(DELTA_T)
      __value__(N_MAX) = (__value__(INTEGRATION_TIME) / __value__(
     > DELTA_T))
      __value__(SymbolTable_0x81ed9a0_56) = (1D00 / __value__(DELTA_T))
      __value__(SymbolTable_0x81ed9a0_57) = (-(__value__(
     > INTEGRATION_TIME) / SQRT(__value__(INTEGRATION_TIME))))
      __value__(SymbolTable_0x81ed9a0_330) = __value__(
     > SymbolTable_0x81ed9a0_56)
      __value__(SymbolTable_0x81ed9a0_332) = __value__(
     > SymbolTable_0x81ed9a0_57)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_330), __value__(
     > SymbolTable_0x81ed9a0_331), __value__(N_MAX))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_332), __value__(
     > SymbolTable_0x81ed9a0_333), __value__(N_MAX))
      WRITE(*, *) 'n_max = ', N_MAX
      __value__(FDEPS) = 1.0D+01
      __value__(SymbolTable_0x81ed9a0_335) = __value__(THOUSAND)
      __value__(Y(1)) = (__value__(THOUSAND) /
     >  3.26799999999999979394D00)
      __value__(SymbolTable_0x81ed9a0_58) = 3.05997552019583840544D-01
      __value__(SymbolTable_0x81ed9a0_334) = __value__(
     > SymbolTable_0x81ed9a0_58)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_334), __value__(
     > SymbolTable_0x81ed9a0_335), __value__(Y(1)))
      __value__(SymbolTable_0x81ed9a0_337) = __value__(THOUSAND)
      __value__(Y(2)) = (__value__(THOUSAND) / 7.9400000000000003908D00
     > )
      __value__(SymbolTable_0x81ed9a0_60) = 1.25944584382871538342D-01
      __value__(SymbolTable_0x81ed9a0_336) = __value__(
     > SymbolTable_0x81ed9a0_60)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_336), __value__(
     > SymbolTable_0x81ed9a0_337), __value__(Y(2)))
      __value__(SymbolTable_0x81ed9a0_339) = __value__(THOUSAND)
      __value__(Y(3)) = (__value__(THOUSAND) /
     >  1.39999999999999991118D00)
      __value__(SymbolTable_0x81ed9a0_62) = 7.14285714285714301575D-01
      __value__(SymbolTable_0x81ed9a0_338) = __value__(
     > SymbolTable_0x81ed9a0_62)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_338), __value__(
     > SymbolTable_0x81ed9a0_339), __value__(Y(3)))
      __value__(SymbolTable_0x81ed9a0_341) = __value__(THOUSAND)
      __value__(Y(4)) = (__value__(THOUSAND) / 1.4170000000000000373D00
     > )
      __value__(SymbolTable_0x81ed9a0_64) = 7.05716302046577204088D-01
      __value__(SymbolTable_0x81ed9a0_340) = __value__(
     > SymbolTable_0x81ed9a0_64)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_340), __value__(
     > SymbolTable_0x81ed9a0_341), __value__(Y(4)))
      __value__(SymbolTable_0x81ed9a0_343) = __value__(THOUSAND)
      __value__(Y(5)) = (__value__(THOUSAND) /
     >  1.28600000000000003197D00)
      __value__(SymbolTable_0x81ed9a0_66) = 7.77604976671850689485D-01
      __value__(SymbolTable_0x81ed9a0_342) = __value__(
     > SymbolTable_0x81ed9a0_66)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_342), __value__(
     > SymbolTable_0x81ed9a0_343), __value__(Y(5)))
      __value__(SymbolTable_0x81ed9a0_345) = __value__(THOUSAND)
      __value__(Y(6)) = (__value__(THOUSAND) /
     >  8.77999999999999936051D00)
      __value__(SymbolTable_0x81ed9a0_68) = 1.13895216400911172827D-01
      __value__(SymbolTable_0x81ed9a0_344) = __value__(
     > SymbolTable_0x81ed9a0_68)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_344), __value__(
     > SymbolTable_0x81ed9a0_345), __value__(Y(6)))
      __value__(SymbolTable_0x81ed9a0_347) = __value__(ALPHA)
      __value__(SymbolTable_0x81ed9a0_349) = __value__(DELTA)
      __value__(R(1)) = (__value__(ALPHA) * __value__(DELTA))
      __value__(SymbolTable_0x81ed9a0_70) = __value__(DELTA)
      __value__(SymbolTable_0x81ed9a0_71) = __value__(ALPHA)
      __value__(SymbolTable_0x81ed9a0_346) = __value__(
     > SymbolTable_0x81ed9a0_70)
      __value__(SymbolTable_0x81ed9a0_348) = __value__(
     > SymbolTable_0x81ed9a0_71)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_346), __value__(
     > SymbolTable_0x81ed9a0_347), __value__(R(1)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_348), __value__(
     > SymbolTable_0x81ed9a0_349), __value__(R(1)))
      __value__(SymbolTable_0x81ed9a0_351) = __value__(ALPHA)
      __value__(R(2)) = (- __value__(ALPHA))
      __value__(SymbolTable_0x81ed9a0_72) = 4.294967295D+09
      __value__(SymbolTable_0x81ed9a0_350) = __value__(
     > SymbolTable_0x81ed9a0_72)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_350), __value__(
     > SymbolTable_0x81ed9a0_351), __value__(R(2)))
      __value__(SymbolTable_0x81ed9a0_353) = __value__(DELTA)
      __value__(SymbolTable_0x81ed9a0_355) = __value__(ALPHA)
      __value__(SymbolTable_0x81ed9a0_73) = (1.0D00 - __value__(DELTA))
      __value__(SymbolTable_0x81ed9a0_78) = (__value__(ALPHA) *
     >  __value__(SymbolTable_0x81ed9a0_73))
      __value__(SymbolTable_0x81ed9a0_74) = __value__(
     > SymbolTable_0x81ed9a0_73)
      __value__(SymbolTable_0x81ed9a0_77) = 4.294967295D+09
      __value__(SymbolTable_0x81ed9a0_75) = __value__(ALPHA)
      __value__(R(3)) = __value__(SymbolTable_0x81ed9a0_78)
      __value__(SymbolTable_0x81ed9a0_352) = (__value__(
     > SymbolTable_0x81ed9a0_77) * __value__(SymbolTable_0x81ed9a0_75))
      __value__(SymbolTable_0x81ed9a0_354) = __value__(
     > SymbolTable_0x81ed9a0_74)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_352), __value__(
     > SymbolTable_0x81ed9a0_353), __value__(R(3)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_354), __value__(
     > SymbolTable_0x81ed9a0_355), __value__(R(3)))
      __value__(SymbolTable_0x81ed9a0_357) = __value__(BETA)
      __value__(SymbolTable_0x81ed9a0_359) = __value__(DELTA)
      __value__(R(4)) = (-(__value__(BETA) * __value__(DELTA)))
      __value__(SymbolTable_0x81ed9a0_80) = __value__(DELTA)
      __value__(SymbolTable_0x81ed9a0_81) = __value__(BETA)
      __value__(SymbolTable_0x81ed9a0_79) = 4.294967295D+09
      __value__(SymbolTable_0x81ed9a0_356) = (__value__(
     > SymbolTable_0x81ed9a0_80) * __value__(SymbolTable_0x81ed9a0_79))
      __value__(SymbolTable_0x81ed9a0_358) = (__value__(
     > SymbolTable_0x81ed9a0_81) * __value__(SymbolTable_0x81ed9a0_79))
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_356), __value__(
     > SymbolTable_0x81ed9a0_357), __value__(R(4)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_358), __value__(
     > SymbolTable_0x81ed9a0_359), __value__(R(4)))
      __value__(R(5)) = __value__(BETA)
      CALL sax_a_a(1.0D00, __value__(BETA), __value__(R(5)))
      __value__(SymbolTable_0x81ed9a0_362) = __value__(BETA)
      __value__(SymbolTable_0x81ed9a0_364) = __value__(DELTA)
      __value__(SymbolTable_0x81ed9a0_83) = (1.0D00 - __value__(DELTA))
      __value__(SymbolTable_0x81ed9a0_88) = (-(__value__(BETA) *
     >  __value__(SymbolTable_0x81ed9a0_83)))
      __value__(SymbolTable_0x81ed9a0_84) = __value__(
     > SymbolTable_0x81ed9a0_83)
      __value__(SymbolTable_0x81ed9a0_87) = 4.294967295D+09
      __value__(SymbolTable_0x81ed9a0_85) = __value__(BETA)
      __value__(SymbolTable_0x81ed9a0_82) = 4.294967295D+09
      __value__(R(6)) = __value__(SymbolTable_0x81ed9a0_88)
      __value__(SymbolTable_0x81ed9a0_360) = (__value__(
     > SymbolTable_0x81ed9a0_87) * __value__(SymbolTable_0x81ed9a0_85))
      __value__(SymbolTable_0x81ed9a0_361) = (__value__(
     > SymbolTable_0x81ed9a0_84) * __value__(SymbolTable_0x81ed9a0_82))
      __value__(SymbolTable_0x81ed9a0_363) = (__value__(
     > SymbolTable_0x81ed9a0_360) * __value__(SymbolTable_0x81ed9a0_82)
     > )
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_361), __value__(
     > SymbolTable_0x81ed9a0_362), __value__(R(6)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_363), __value__(
     > SymbolTable_0x81ed9a0_364), __value__(R(6)))
      DO L = 1, 6, 1
        __value__(SymbolTable_0x81ed9a0_366) = __value__(R(L))
        __value__(SymbolTable_0x81ed9a0_368) = __value__(U0)
        __value__(SymbolTable_0x81ed9a0_370) = __value__(SV)
        __value__(SymbolTable_0x81ed9a0_89) = (__value__(R(L)) *
     >  __value__(U0))
        __value__(SymbolTable_0x81ed9a0_94) = (__value__(
     > SymbolTable_0x81ed9a0_89) / __value__(SV))
        __value__(SymbolTable_0x81ed9a0_92) = __value__(U0)
        __value__(SymbolTable_0x81ed9a0_93) = __value__(R(L))
        __value__(SymbolTable_0x81ed9a0_90) = (1D00 / __value__(SV))
        __value__(SymbolTable_0x81ed9a0_91) = (-(__value__(
     > SymbolTable_0x81ed9a0_89) / SQRT(__value__(
     > SymbolTable_0x81ed9a0_89))))
        __value__(R(L)) = __value__(SymbolTable_0x81ed9a0_94)
        __value__(SymbolTable_0x81ed9a0_365) = (__value__(
     > SymbolTable_0x81ed9a0_92) * __value__(SymbolTable_0x81ed9a0_90))
        __value__(SymbolTable_0x81ed9a0_367) = (__value__(
     > SymbolTable_0x81ed9a0_93) * __value__(SymbolTable_0x81ed9a0_90))
        __value__(SymbolTable_0x81ed9a0_369) = __value__(
     > SymbolTable_0x81ed9a0_91)
        CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_365), __value__(
     > SymbolTable_0x81ed9a0_366), __value__(R(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_367), __value__(
     > SymbolTable_0x81ed9a0_368), __value__(R(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_369), __value__(
     > SymbolTable_0x81ed9a0_370), __value__(R(L)))
      END DO
      DO L = 1, 6, 1
        IF(L .LE. 3) THEN
          __value__(PROJ_T(L)) = 1.0D00
          __value__(PROJ_S(L)) = 0.0D00
        ELSE
          __value__(PROJ_T(L)) = 0.0D00
          __value__(PROJ_S(L)) = 1.0D00
        ENDIF
      END DO
      DO L = 1, 6, 1
        __value__(SymbolTable_0x81ed9a0_372) = __value__(PROJ_T(L))
        __value__(SymbolTable_0x81ed9a0_374) = __value__(R(L))
        __value__(R_T(L)) = (__value__(PROJ_T(L)) * __value__(R(L)))
        __value__(SymbolTable_0x81ed9a0_95) = __value__(R(L))
        __value__(SymbolTable_0x81ed9a0_96) = __value__(PROJ_T(L))
        __value__(SymbolTable_0x81ed9a0_371) = __value__(
     > SymbolTable_0x81ed9a0_95)
        __value__(SymbolTable_0x81ed9a0_373) = __value__(
     > SymbolTable_0x81ed9a0_96)
        CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_371), __value__(
     > SymbolTable_0x81ed9a0_372), __value__(R_T(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_373), __value__(
     > SymbolTable_0x81ed9a0_374), __value__(R_T(L)))
        __value__(SymbolTable_0x81ed9a0_376) = __value__(PROJ_S(L))
        __value__(SymbolTable_0x81ed9a0_378) = __value__(R(L))
        __value__(R_S(L)) = (__value__(PROJ_S(L)) * __value__(R(L)))
        __value__(SymbolTable_0x81ed9a0_97) = __value__(R(L))
        __value__(SymbolTable_0x81ed9a0_98) = __value__(PROJ_S(L))
        __value__(SymbolTable_0x81ed9a0_375) = __value__(
     > SymbolTable_0x81ed9a0_97)
        __value__(SymbolTable_0x81ed9a0_377) = __value__(
     > SymbolTable_0x81ed9a0_98)
        CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_375), __value__(
     > SymbolTable_0x81ed9a0_376), __value__(R_S(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_377), __value__(
     > SymbolTable_0x81ed9a0_378), __value__(R_S(L)))
      END DO
      __value__(R1(1)) = 1.0D00
      __value__(R1(2)) = (-1.0D00)
      __value__(R1(3)) = 0.0D00
      __value__(R1(4)) = 0.0D00
      __value__(R1(5)) = 0.0D00
      __value__(R1(6)) = 0.0D00
      DO J = 1, 6, 1
        DO I = 1, 6, 1
          __value__(SymbolTable_0x81ed9a0_380) = __value__(R(I))
          __value__(SymbolTable_0x81ed9a0_382) = __value__(R(J))
          __value__(X(J, I)) = (__value__(R(I)) * __value__(R(J)))
          __value__(SymbolTable_0x81ed9a0_99) = __value__(R(J))
          __value__(SymbolTable_0x81ed9a0_100) = __value__(R(I))
          __value__(SymbolTable_0x81ed9a0_379) = __value__(
     > SymbolTable_0x81ed9a0_99)
          __value__(SymbolTable_0x81ed9a0_381) = __value__(
     > SymbolTable_0x81ed9a0_100)
          CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_379), __value__(
     > SymbolTable_0x81ed9a0_380), __value__(X(J, I)))
          CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_381),
     >  __value__(SymbolTable_0x81ed9a0_382), __value__(X(J, I)))
        END DO
      END DO
      __value__(EPSILON_REGULARIZE) = 1.0D00
      DO J = 1, 6, 1
        DO I = 1, 6, 1
          __value__(SymbolTable_0x81ed9a0_384) = __value__(X(J, I))
          __value__(SymbolTable_0x81ed9a0_386) = __value__(
     > EPSILON_REGULARIZE)
          __value__(X(J, I)) = (__value__(X(J, I)) + __value__(
     > EPSILON_REGULARIZE))
          __value__(SymbolTable_0x81ed9a0_101) = 1.0D00
          __value__(SymbolTable_0x81ed9a0_102) = 1.0D00
          __value__(SymbolTable_0x81ed9a0_383) = __value__(
     > SymbolTable_0x81ed9a0_101)
          __value__(SymbolTable_0x81ed9a0_385) = __value__(
     > SymbolTable_0x81ed9a0_102)
          CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_383), __value__(
     > SymbolTable_0x81ed9a0_384), __value__(X(J, I)))
          CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_385),
     >  __value__(SymbolTable_0x81ed9a0_386), __value__(X(J, I)))
        END DO
      END DO
      RETURN
      END SUBROUTINE

      SUBROUTINE box_ini_fields()
      use w2f__types
      IMPLICIT NONE
C
C     **** Variables and functions ****
C
      INTEGER(w2f__i4) L
      COMMON /pa_geometry_r/ BLENGTH, BHEIGHT, BWIDTH, AREA, VOL
      REAL(w2f__8) BLENGTH(1 : 3)
      REAL(w2f__8) BHEIGHT(1 : 3)
      REAL(w2f__8) BWIDTH
      REAL(w2f__8) AREA(1 : 3)
      REAL(w2f__8) VOL(1 : 3)
      COMMON /pa_parameters_r/ HUNDRED, THOUSAND, DAY, YEAR, SV,
     >  DAYS_PER_50M_MIXED_LAYER, GAMMA_T, GAMMA_S, EPSILON_IC,
     >  NOISE_CORRELATION_TIME, INTEGRATION_TIME, EPSILON_REGULARIZE,
     >  FDEPS
      REAL(w2f__8) HUNDRED
      REAL(w2f__8) THOUSAND
      REAL(w2f__8) DAY
      REAL(w2f__8) YEAR
      REAL(w2f__8) SV
      REAL(w2f__8) DAYS_PER_50M_MIXED_LAYER
      REAL(w2f__8) GAMMA_T
      REAL(w2f__8) GAMMA_S
      REAL(w2f__8) EPSILON_IC
      REAL(w2f__8) NOISE_CORRELATION_TIME
      REAL(w2f__8) INTEGRATION_TIME
      REAL(w2f__8) EPSILON_REGULARIZE
      REAL(w2f__8) FDEPS
      COMMON /fi_forcing_params_r/ NULLFORCE, FW, TSTAR, SSTAR
      REAL(w2f__8) NULLFORCE(1 : 2)
      REAL(w2f__8) FW(1 : 2)
      REAL(w2f__8) TSTAR(1 : 2)
      REAL(w2f__8) SSTAR(1 : 2)
      COMMON /fi_metric_r/ METRIC
      REAL(w2f__8) METRIC
      COMMON /fi_metric_aux_r/ METRIC1, METRIC2
      REAL(w2f__8) METRIC1
      REAL(w2f__8) METRIC2
      COMMON /fi_ini_r/ UBAR, T, S
      REAL(w2f__8) UBAR
      REAL(w2f__8) T(1 : 3)
      REAL(w2f__8) S(1 : 3)
      COMMON /fi_state_r/ TOLD, TNOW, TNEW, SOLD, SNOW, SNEW
      REAL(w2f__8) TOLD(1 : 3)
      REAL(w2f__8) TNOW(1 : 3)
      REAL(w2f__8) TNEW(1 : 3)
      REAL(w2f__8) SOLD(1 : 3)
      REAL(w2f__8) SNOW(1 : 3)
      REAL(w2f__8) SNEW(1 : 3)
      COMMON /fi_thc_r/ THC_TOT, THC_T, THC_S
      REAL(w2f__8) THC_TOT
      REAL(w2f__8) THC_T
      REAL(w2f__8) THC_S
      COMMON /fi_final_state_r/ TSVEC
      REAL(w2f__8) TSVEC(1 : 6)
      COMMON /fi_velocity_r/ UVEL
      REAL(w2f__8) UVEL
      COMMON /fi_controls_r/ XX
      REAL(w2f__8) XX(1 : 6)
      REAL(w2f__8) SymbolTable_0x81ed9a0_103
      REAL(w2f__8) SymbolTable_0x81ed9a0_104
      REAL(w2f__8) SymbolTable_0x81ed9a0_105
      REAL(w2f__8) SymbolTable_0x81ed9a0_110
      REAL(w2f__8) SymbolTable_0x81ed9a0_106
      REAL(w2f__8) SymbolTable_0x81ed9a0_111
      REAL(w2f__8) SymbolTable_0x81ed9a0_107
      REAL(w2f__8) SymbolTable_0x81ed9a0_112
      REAL(w2f__8) SymbolTable_0x81ed9a0_113
      REAL(w2f__8) SymbolTable_0x81ed9a0_109
      REAL(w2f__8) SymbolTable_0x81ed9a0_115
      REAL(w2f__8) SymbolTable_0x81ed9a0_116
      REAL(w2f__8) SymbolTable_0x81ed9a0_117
      REAL(w2f__8) SymbolTable_0x81ed9a0_118
      REAL(w2f__8) SymbolTable_0x81ed9a0_400
      REAL(w2f__8) SymbolTable_0x81ed9a0_401
      REAL(w2f__8) SymbolTable_0x81ed9a0_402
      REAL(w2f__8) SymbolTable_0x81ed9a0_403
      REAL(w2f__8) SymbolTable_0x81ed9a0_404
      REAL(w2f__8) SymbolTable_0x81ed9a0_405
      REAL(w2f__8) SymbolTable_0x81ed9a0_390
      REAL(w2f__8) SymbolTable_0x81ed9a0_391
      REAL(w2f__8) SymbolTable_0x81ed9a0_392
      REAL(w2f__8) SymbolTable_0x81ed9a0_387
      REAL(w2f__8) SymbolTable_0x81ed9a0_393
      REAL(w2f__8) SymbolTable_0x81ed9a0_388
      REAL(w2f__8) SymbolTable_0x81ed9a0_394
      REAL(w2f__8) SymbolTable_0x81ed9a0_389
      REAL(w2f__8) SymbolTable_0x81ed9a0_395
      REAL(w2f__8) SymbolTable_0x81ed9a0_396
      REAL(w2f__8) SymbolTable_0x81ed9a0_397
      REAL(w2f__8) SymbolTable_0x81ed9a0_398
      REAL(w2f__8) SymbolTable_0x81ed9a0_399
C
C     **** statements ****
C
      __value__(THC_TOT) = 0.0D00
      __value__(THC_T) = 0.0D00
      __value__(THC_S) = 0.0D00
      __value__(METRIC1) = 0.0D00
      __value__(METRIC2) = 0.0D00
      __value__(METRIC) = 0.0D00
      __value__(NULLFORCE(1)) = 0.0D00
      __value__(NULLFORCE(2)) = 0.0D00
      __value__(SymbolTable_0x81ed9a0_389) = __value__(HUNDRED)
      __value__(SymbolTable_0x81ed9a0_391) = __value__(YEAR)
      __value__(SymbolTable_0x81ed9a0_393) = __value__(AREA(1))
      __value__(SymbolTable_0x81ed9a0_106) = (__value__(HUNDRED) /
     >  __value__(YEAR))
      __value__(SymbolTable_0x81ed9a0_103) = (__value__(
     > SymbolTable_0x81ed9a0_106) * 3.5D00)
      __value__(SymbolTable_0x81ed9a0_111) = (__value__(AREA(1)) *
     >  __value__(SymbolTable_0x81ed9a0_103))
      __value__(SymbolTable_0x81ed9a0_104) = __value__(
     > SymbolTable_0x81ed9a0_103)
      __value__(SymbolTable_0x81ed9a0_109) = (1D00 / __value__(YEAR))
      __value__(SymbolTable_0x81ed9a0_110) = (-(__value__(HUNDRED) /
     >  SQRT(__value__(HUNDRED))))
      __value__(SymbolTable_0x81ed9a0_107) = 3.5D00
      __value__(SymbolTable_0x81ed9a0_105) = __value__(AREA(1))
      __value__(FW(1)) = __value__(SymbolTable_0x81ed9a0_111)
      __value__(SymbolTable_0x81ed9a0_387) = (__value__(
     > SymbolTable_0x81ed9a0_107) * __value__(SymbolTable_0x81ed9a0_105
     > ))
      __value__(SymbolTable_0x81ed9a0_388) = (__value__(
     > SymbolTable_0x81ed9a0_109) * __value__(SymbolTable_0x81ed9a0_387
     > ))
      __value__(SymbolTable_0x81ed9a0_390) = (__value__(
     > SymbolTable_0x81ed9a0_110) * __value__(SymbolTable_0x81ed9a0_387
     > ))
      __value__(SymbolTable_0x81ed9a0_392) = __value__(
     > SymbolTable_0x81ed9a0_104)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_388), __value__(
     > SymbolTable_0x81ed9a0_389), __value__(FW(1)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_390), __value__(
     > SymbolTable_0x81ed9a0_391), __value__(FW(1)))
      CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_392), __value__(
     > SymbolTable_0x81ed9a0_393), __value__(FW(1)))
      __value__(SymbolTable_0x81ed9a0_395) = __value__(FW(1))
      __value__(FW(2)) = (- __value__(FW(1)))
      __value__(SymbolTable_0x81ed9a0_112) = 4.294967295D+09
      __value__(SymbolTable_0x81ed9a0_394) = __value__(
     > SymbolTable_0x81ed9a0_112)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_394), __value__(
     > SymbolTable_0x81ed9a0_395), __value__(FW(2)))
      __value__(TSTAR(1)) = 2.20000000000000017764D00
      __value__(TSTAR(2)) = 0.0D00
      __value__(SSTAR(1)) = 3.60000000000000008882D00
      __value__(SSTAR(2)) = 3.39999999999999991118D00
      __value__(SymbolTable_0x81ed9a0_397) = __value__(SV)
      __value__(UBAR) = (__value__(SV) * 2.0D00)
      __value__(SymbolTable_0x81ed9a0_113) = 2.0D00
      __value__(SymbolTable_0x81ed9a0_396) = __value__(
     > SymbolTable_0x81ed9a0_113)
      CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_396), __value__(
     > SymbolTable_0x81ed9a0_397), __value__(UBAR))
      __value__(T(1)) = 2.0D00
      __value__(T(2)) = 1.0D00
      __value__(T(3)) = 1.0D00
      __value__(S(1)) = 3.54999999999999982236D00
      __value__(S(2)) = 3.45000000000000017764D00
      __value__(S(3)) = 3.45000000000000017764D00
      DO L = 1, 6, 1
        __value__(TSVEC(L)) = 0.0D00
      END DO
      DO L = 1, 3, 1
        __value__(SymbolTable_0x81ed9a0_399) = __value__(T(L))
        __value__(SymbolTable_0x81ed9a0_401) = __value__(XX(L))
        __value__(T(L)) = (__value__(T(L)) + __value__(XX(L)))
        __value__(SymbolTable_0x81ed9a0_115) = 1.0D00
        __value__(SymbolTable_0x81ed9a0_116) = 1.0D00
        __value__(SymbolTable_0x81ed9a0_398) = __value__(
     > SymbolTable_0x81ed9a0_115)
        __value__(SymbolTable_0x81ed9a0_400) = __value__(
     > SymbolTable_0x81ed9a0_116)
        CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_398), __value__(
     > SymbolTable_0x81ed9a0_399), __value__(T(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_400), __value__(
     > SymbolTable_0x81ed9a0_401), __value__(T(L)))
        __value__(SymbolTable_0x81ed9a0_403) = __value__(S(L))
        __value__(SymbolTable_0x81ed9a0_405) = __value__(XX(L + 3.0D00)
     > )
        __value__(S(L)) = (__value__(S(L)) + __value__(XX(L + 3.0D00)))
        __value__(SymbolTable_0x81ed9a0_117) = 1.0D00
        __value__(SymbolTable_0x81ed9a0_118) = 1.0D00
        __value__(SymbolTable_0x81ed9a0_402) = __value__(
     > SymbolTable_0x81ed9a0_117)
        __value__(SymbolTable_0x81ed9a0_404) = __value__(
     > SymbolTable_0x81ed9a0_118)
        CALL sax_a_a(__value__(SymbolTable_0x81ed9a0_402), __value__(
     > SymbolTable_0x81ed9a0_403), __value__(S(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x81ed9a0_404), __value__(
     > SymbolTable_0x81ed9a0_405), __value__(S(L)))
      END DO
      DO L = 1, 3, 1
        __value__(TNEW(L)) = __value__(T(L))
        CALL sax_a_a(1.0D00, __value__(T(L)), __value__(TNEW(L)))
        __value__(SNEW(L)) = __value__(S(L))
        CALL sax_a_a(1.0D00, __value__(S(L)), __value__(SNEW(L)))
        __value__(TOLD(L)) = __value__(T(L))
        CALL sax_a_a(1.0D00, __value__(T(L)), __value__(TOLD(L)))
        __value__(SOLD(L)) = __value__(S(L))
        CALL sax_a_a(1.0D00, __value__(S(L)), __value__(SOLD(L)))
        __value__(TNOW(L)) = __value__(T(L))
        CALL sax_a_a(1.0D00, __value__(T(L)), __value__(TNOW(L)))
        __value__(SNOW(L)) = __value__(S(L))
        CALL sax_a_a(1.0D00, __value__(S(L)), __value__(SNOW(L)))
      END DO
      __value__(UVEL) = __value__(UBAR)
      CALL sax_a_a(1.0D00, __value__(UBAR), __value__(UVEL))
      RETURN
      END SUBROUTINE
W2F1
    $w2f1_pp = <<'W2F1PP';
C ***********************************************************
C Fortran file translated from WHIRL Wed Sep 17 12:31:15 2003
C ***********************************************************
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

      SUBROUTINE box_ini_params()
      use w2f__types
      use active_module
      IMPLICIT NONE
C
C     **** Variables and functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) L
      COMMON /pa_density_r/ ALPHA, BETA
      type(active) :: ALPHA
      type(active) :: BETA
      COMMON /pa_geometry_r/ BLENGTH, BHEIGHT, BWIDTH, AREA, VOL
      type(active) :: BLENGTH(1 : 3)
      type(active) :: BHEIGHT(1 : 3)
      type(active) :: BWIDTH
      type(active) :: AREA(1 : 3)
      type(active) :: VOL(1 : 3)
      COMMON /pa_parameters_r/ HUNDRED, THOUSAND, DAY, YEAR, SV,
     >  DAYS_PER_50M_MIXED_LAYER, GAMMA_T, GAMMA_S, EPSILON_IC,
     >  NOISE_CORRELATION_TIME, INTEGRATION_TIME, EPSILON_REGULARIZE,
     >  FDEPS
      type(active) :: HUNDRED
      type(active) :: THOUSAND
      type(active) :: DAY
      type(active) :: YEAR
      type(active) :: SV
      type(active) :: DAYS_PER_50M_MIXED_LAYER
      type(active) :: GAMMA_T
      type(active) :: GAMMA_S
      type(active) :: EPSILON_IC
      type(active) :: NOISE_CORRELATION_TIME
      type(active) :: INTEGRATION_TIME
      type(active) :: EPSILON_REGULARIZE
      type(active) :: FDEPS
      COMMON /pa_transport_r/ U0, DELTA
      type(active) :: U0
      type(active) :: DELTA
      COMMON /pa_timestep_r/ DELTA_T
      type(active) :: DELTA_T
      COMMON /pa_numbers_i/ N_MAX
      INTEGER(w2f__i4) N_MAX
      COMMON /pa_algebra_r/ Y, R, R1, R_T, R_S, PROJ_T, PROJ_S, X
      type(active) :: Y(1 : 6)
      type(active) :: R(1 : 6)
      type(active) :: R1(1 : 6)
      type(active) :: R_T(1 : 6)
      type(active) :: R_S(1 : 6)
      type(active) :: PROJ_T(1 : 6)
      type(active) :: PROJ_S(1 : 6)
      type(active) :: X(1 : 6, 1 : 6)
      COMMON /pa_robert_filter_r/ ROBERT_FILTER_COEFF
      type(active) :: ROBERT_FILTER_COEFF
      COMMON /pa_switches_l/ VERBMODE
      LOGICAL(w2f__i4) VERBMODE
      type(active) :: SymbolTable_0x81ed9a0_100
      type(active) :: SymbolTable_0x81ed9a0_101
      type(active) :: SymbolTable_0x81ed9a0_102
      type(active) :: SymbolTable_0x81ed9a0_0
      type(active) :: SymbolTable_0x81ed9a0_300
      type(active) :: SymbolTable_0x81ed9a0_1
      type(active) :: SymbolTable_0x81ed9a0_301
      type(active) :: SymbolTable_0x81ed9a0_2
      type(active) :: SymbolTable_0x81ed9a0_302
      type(active) :: SymbolTable_0x81ed9a0_3
      type(active) :: SymbolTable_0x81ed9a0_303
      type(active) :: SymbolTable_0x81ed9a0_4
      type(active) :: SymbolTable_0x81ed9a0_304
      type(active) :: SymbolTable_0x81ed9a0_5
      type(active) :: SymbolTable_0x81ed9a0_310
      type(active) :: SymbolTable_0x81ed9a0_305
      type(active) :: SymbolTable_0x81ed9a0_6
      type(active) :: SymbolTable_0x81ed9a0_311
      type(active) :: SymbolTable_0x81ed9a0_306
      type(active) :: SymbolTable_0x81ed9a0_7
      type(active) :: SymbolTable_0x81ed9a0_312
      type(active) :: SymbolTable_0x81ed9a0_307
      type(active) :: SymbolTable_0x81ed9a0_8
      type(active) :: SymbolTable_0x81ed9a0_313
      type(active) :: SymbolTable_0x81ed9a0_308
      type(active) :: SymbolTable_0x81ed9a0_9
      type(active) :: SymbolTable_0x81ed9a0_314
      type(active) :: SymbolTable_0x81ed9a0_309
      type(active) :: SymbolTable_0x81ed9a0_320
      type(active) :: SymbolTable_0x81ed9a0_315
      type(active) :: SymbolTable_0x81ed9a0_321
      type(active) :: SymbolTable_0x81ed9a0_316
      type(active) :: SymbolTable_0x81ed9a0_322
      type(active) :: SymbolTable_0x81ed9a0_317
      type(active) :: SymbolTable_0x81ed9a0_323
      type(active) :: SymbolTable_0x81ed9a0_318
      type(active) :: SymbolTable_0x81ed9a0_324
      type(active) :: SymbolTable_0x81ed9a0_319
      type(active) :: SymbolTable_0x81ed9a0_274
      type(active) :: SymbolTable_0x81ed9a0_330
      type(active) :: SymbolTable_0x81ed9a0_325
      type(active) :: SymbolTable_0x81ed9a0_275
      type(active) :: SymbolTable_0x81ed9a0_280
      type(active) :: SymbolTable_0x81ed9a0_331
      type(active) :: SymbolTable_0x81ed9a0_326
      type(active) :: SymbolTable_0x81ed9a0_276
      type(active) :: SymbolTable_0x81ed9a0_281
      type(active) :: SymbolTable_0x81ed9a0_332
      type(active) :: SymbolTable_0x81ed9a0_327
      type(active) :: SymbolTable_0x81ed9a0_277
      type(active) :: SymbolTable_0x81ed9a0_282
      type(active) :: SymbolTable_0x81ed9a0_333
      type(active) :: SymbolTable_0x81ed9a0_328
      type(active) :: SymbolTable_0x81ed9a0_278
      type(active) :: SymbolTable_0x81ed9a0_283
      type(active) :: SymbolTable_0x81ed9a0_334
      type(active) :: SymbolTable_0x81ed9a0_329
      type(active) :: SymbolTable_0x81ed9a0_279
      type(active) :: SymbolTable_0x81ed9a0_284
      type(active) :: SymbolTable_0x81ed9a0_340
      type(active) :: SymbolTable_0x81ed9a0_335
      type(active) :: SymbolTable_0x81ed9a0_285
      type(active) :: SymbolTable_0x81ed9a0_290
      type(active) :: SymbolTable_0x81ed9a0_341
      type(active) :: SymbolTable_0x81ed9a0_336
      type(active) :: SymbolTable_0x81ed9a0_286
      type(active) :: SymbolTable_0x81ed9a0_291
      type(active) :: SymbolTable_0x81ed9a0_342
      type(active) :: SymbolTable_0x81ed9a0_337
      type(active) :: SymbolTable_0x81ed9a0_287
      type(active) :: SymbolTable_0x81ed9a0_292
      type(active) :: SymbolTable_0x81ed9a0_343
      type(active) :: SymbolTable_0x81ed9a0_338
      type(active) :: SymbolTable_0x81ed9a0_288
      type(active) :: SymbolTable_0x81ed9a0_293
      type(active) :: SymbolTable_0x81ed9a0_344
      type(active) :: SymbolTable_0x81ed9a0_339
      type(active) :: SymbolTable_0x81ed9a0_289
      type(active) :: SymbolTable_0x81ed9a0_294
      type(active) :: SymbolTable_0x81ed9a0_350
      type(active) :: SymbolTable_0x81ed9a0_345
      type(active) :: SymbolTable_0x81ed9a0_295
      type(active) :: SymbolTable_0x81ed9a0_351
      type(active) :: SymbolTable_0x81ed9a0_346
      type(active) :: SymbolTable_0x81ed9a0_296
      type(active) :: SymbolTable_0x81ed9a0_352
      type(active) :: SymbolTable_0x81ed9a0_347
      type(active) :: SymbolTable_0x81ed9a0_297
      type(active) :: SymbolTable_0x81ed9a0_353
      type(active) :: SymbolTable_0x81ed9a0_348
      type(active) :: SymbolTable_0x81ed9a0_298
      type(active) :: SymbolTable_0x81ed9a0_354
      type(active) :: SymbolTable_0x81ed9a0_349
      type(active) :: SymbolTable_0x81ed9a0_299
      type(active) :: SymbolTable_0x81ed9a0_360
      type(active) :: SymbolTable_0x81ed9a0_355
      type(active) :: SymbolTable_0x81ed9a0_361
      type(active) :: SymbolTable_0x81ed9a0_356
      type(active) :: SymbolTable_0x81ed9a0_362
      type(active) :: SymbolTable_0x81ed9a0_357
      type(active) :: SymbolTable_0x81ed9a0_363
      type(active) :: SymbolTable_0x81ed9a0_358
      type(active) :: SymbolTable_0x81ed9a0_364
      type(active) :: SymbolTable_0x81ed9a0_359
      type(active) :: SymbolTable_0x81ed9a0_370
      type(active) :: SymbolTable_0x81ed9a0_365
      type(active) :: SymbolTable_0x81ed9a0_371
      type(active) :: SymbolTable_0x81ed9a0_366
      type(active) :: SymbolTable_0x81ed9a0_372
      type(active) :: SymbolTable_0x81ed9a0_367
      type(active) :: SymbolTable_0x81ed9a0_373
      type(active) :: SymbolTable_0x81ed9a0_368
      type(active) :: SymbolTable_0x81ed9a0_374
      type(active) :: SymbolTable_0x81ed9a0_369
      type(active) :: SymbolTable_0x81ed9a0_380
      type(active) :: SymbolTable_0x81ed9a0_375
      type(active) :: SymbolTable_0x81ed9a0_381
      type(active) :: SymbolTable_0x81ed9a0_376
      type(active) :: SymbolTable_0x81ed9a0_382
      type(active) :: SymbolTable_0x81ed9a0_377
      type(active) :: SymbolTable_0x81ed9a0_383
      type(active) :: SymbolTable_0x81ed9a0_378
      type(active) :: SymbolTable_0x81ed9a0_384
      type(active) :: SymbolTable_0x81ed9a0_379
      type(active) :: SymbolTable_0x81ed9a0_385
      type(active) :: SymbolTable_0x81ed9a0_386
      type(active) :: SymbolTable_0x81ed9a0_10
      type(active) :: SymbolTable_0x81ed9a0_11
      type(active) :: SymbolTable_0x81ed9a0_12
      type(active) :: SymbolTable_0x81ed9a0_13
      type(active) :: SymbolTable_0x81ed9a0_14
      type(active) :: SymbolTable_0x81ed9a0_15
      type(active) :: SymbolTable_0x81ed9a0_20
      type(active) :: SymbolTable_0x81ed9a0_16
      type(active) :: SymbolTable_0x81ed9a0_21
      type(active) :: SymbolTable_0x81ed9a0_17
      type(active) :: SymbolTable_0x81ed9a0_22
      type(active) :: SymbolTable_0x81ed9a0_18
      type(active) :: SymbolTable_0x81ed9a0_23
      type(active) :: SymbolTable_0x81ed9a0_19
      type(active) :: SymbolTable_0x81ed9a0_24
      type(active) :: SymbolTable_0x81ed9a0_26
      type(active) :: SymbolTable_0x81ed9a0_31
      type(active) :: SymbolTable_0x81ed9a0_27
      type(active) :: SymbolTable_0x81ed9a0_32
      type(active) :: SymbolTable_0x81ed9a0_29
      type(active) :: SymbolTable_0x81ed9a0_34
      type(active) :: SymbolTable_0x81ed9a0_35
      type(active) :: SymbolTable_0x81ed9a0_40
      type(active) :: SymbolTable_0x81ed9a0_41
      type(active) :: SymbolTable_0x81ed9a0_37
      type(active) :: SymbolTable_0x81ed9a0_42
      type(active) :: SymbolTable_0x81ed9a0_38
      type(active) :: SymbolTable_0x81ed9a0_43
      type(active) :: SymbolTable_0x81ed9a0_44
      type(active) :: SymbolTable_0x81ed9a0_45
      type(active) :: SymbolTable_0x81ed9a0_50
      type(active) :: SymbolTable_0x81ed9a0_47
      type(active) :: SymbolTable_0x81ed9a0_52
      type(active) :: SymbolTable_0x81ed9a0_48
      type(active) :: SymbolTable_0x81ed9a0_49
      type(active) :: SymbolTable_0x81ed9a0_54
      type(active) :: SymbolTable_0x81ed9a0_60
      type(active) :: SymbolTable_0x81ed9a0_56
      type(active) :: SymbolTable_0x81ed9a0_57
      type(active) :: SymbolTable_0x81ed9a0_62
      type(active) :: SymbolTable_0x81ed9a0_58
      type(active) :: SymbolTable_0x81ed9a0_64
      type(active) :: SymbolTable_0x81ed9a0_70
      type(active) :: SymbolTable_0x81ed9a0_66
      type(active) :: SymbolTable_0x81ed9a0_71
      type(active) :: SymbolTable_0x81ed9a0_72
      type(active) :: SymbolTable_0x81ed9a0_68
      type(active) :: SymbolTable_0x81ed9a0_73
      type(active) :: SymbolTable_0x81ed9a0_74
      type(active) :: SymbolTable_0x81ed9a0_75
      type(active) :: SymbolTable_0x81ed9a0_80
      type(active) :: SymbolTable_0x81ed9a0_81
      type(active) :: SymbolTable_0x81ed9a0_77
      type(active) :: SymbolTable_0x81ed9a0_82
      type(active) :: SymbolTable_0x81ed9a0_78
      type(active) :: SymbolTable_0x81ed9a0_83
      type(active) :: SymbolTable_0x81ed9a0_79
      type(active) :: SymbolTable_0x81ed9a0_84
      type(active) :: SymbolTable_0x81ed9a0_85
      type(active) :: SymbolTable_0x81ed9a0_90
      type(active) :: SymbolTable_0x81ed9a0_91
      type(active) :: SymbolTable_0x81ed9a0_87
      type(active) :: SymbolTable_0x81ed9a0_92
      type(active) :: SymbolTable_0x81ed9a0_88
      type(active) :: SymbolTable_0x81ed9a0_93
      type(active) :: SymbolTable_0x81ed9a0_89
      type(active) :: SymbolTable_0x81ed9a0_94
      type(active) :: SymbolTable_0x81ed9a0_95
      type(active) :: SymbolTable_0x81ed9a0_96
      type(active) :: SymbolTable_0x81ed9a0_97
      type(active) :: SymbolTable_0x81ed9a0_98
      type(active) :: SymbolTable_0x81ed9a0_99
C
C     **** statements ****
C
      VERBMODE%v = 0.0D00
      BLENGTH(1)%v = 5.0D00
      BLENGTH(2)%v = 1.0D00
      BLENGTH(3)%v = BLENGTH(1)%v
      CALL sax_a_a(1.0D00,BLENGTH(1)%v,BLENGTH(3)%v)
      BHEIGHT(1)%v = 1.0D00
      BHEIGHT(3)%v = 4.0D00
      SymbolTable_0x81ed9a0_275%v = BHEIGHT(1)%v
      SymbolTable_0x81ed9a0_277%v = BHEIGHT(3)%v
      BHEIGHT(2)%v = (BHEIGHT(1)%v+BHEIGHT(3)%v)
      SymbolTable_0x81ed9a0_0%v = 1.0D00
      SymbolTable_0x81ed9a0_1%v = 1.0D00
      SymbolTable_0x81ed9a0_274%v = SymbolTable_0x81ed9a0_0%v
      SymbolTable_0x81ed9a0_276%v = SymbolTable_0x81ed9a0_1%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_274%v,SymbolTable_0x81ed9a0_275
     +%v,BHEIGHT(2)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_276%v,SymbolTable_0x81ed9a0_2
     +77%v,BHEIGHT(2)%v)
      SymbolTable_0x81ed9a0_279%v = BHEIGHT(1)%v
      SymbolTable_0x81ed9a0_281%v = BHEIGHT(3)%v
      SymbolTable_0x81ed9a0_283%v = BHEIGHT(1)%v
      SymbolTable_0x81ed9a0_2%v = (BHEIGHT(1)%v+BHEIGHT(3)%v)
      SymbolTable_0x81ed9a0_7%v = (BHEIGHT(1)%v/SymbolTable_0x81ed9a0_2%
     +v)
      SymbolTable_0x81ed9a0_3%v = (1D00/SymbolTable_0x81ed9a0_2%v)
      SymbolTable_0x81ed9a0_5%v = 1.0D00
      SymbolTable_0x81ed9a0_6%v = 1.0D00
      SymbolTable_0x81ed9a0_4%v = (-(BHEIGHT(1)%v/SQRT(BHEIGHT(1)%v)))
      DELTA%v = SymbolTable_0x81ed9a0_7%v
      SymbolTable_0x81ed9a0_278%v = (SymbolTable_0x81ed9a0_5%v*SymbolTab
     +le_0x81ed9a0_4%v)
      SymbolTable_0x81ed9a0_280%v = (SymbolTable_0x81ed9a0_6%v*SymbolTab
     +le_0x81ed9a0_4%v)
      SymbolTable_0x81ed9a0_282%v = SymbolTable_0x81ed9a0_3%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_278%v,SymbolTable_0x81ed9a0_279
     +%v,DELTA%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_280%v,SymbolTable_0x81ed9a0_2
     +81%v,DELTA%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_282%v,SymbolTable_0x81ed9a0_2
     +83%v,DELTA%v)
      BWIDTH%v = 4.0D00
      SymbolTable_0x81ed9a0_285%v = BLENGTH(1)%v
      SymbolTable_0x81ed9a0_287%v = BWIDTH%v
      AREA(1)%v = (BLENGTH(1)%v*BWIDTH%v)
      SymbolTable_0x81ed9a0_8%v = BWIDTH%v
      SymbolTable_0x81ed9a0_9%v = BLENGTH(1)%v
      SymbolTable_0x81ed9a0_284%v = SymbolTable_0x81ed9a0_8%v
      SymbolTable_0x81ed9a0_286%v = SymbolTable_0x81ed9a0_9%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_284%v,SymbolTable_0x81ed9a0_285
     +%v,AREA(1)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_286%v,SymbolTable_0x81ed9a0_2
     +87%v,AREA(1)%v)
      SymbolTable_0x81ed9a0_289%v = BLENGTH(2)%v
      SymbolTable_0x81ed9a0_291%v = BWIDTH%v
      AREA(2)%v = (BLENGTH(2)%v*BWIDTH%v)
      SymbolTable_0x81ed9a0_10%v = BWIDTH%v
      SymbolTable_0x81ed9a0_11%v = BLENGTH(2)%v
      SymbolTable_0x81ed9a0_288%v = SymbolTable_0x81ed9a0_10%v
      SymbolTable_0x81ed9a0_290%v = SymbolTable_0x81ed9a0_11%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_288%v,SymbolTable_0x81ed9a0_289
     +%v,AREA(2)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_290%v,SymbolTable_0x81ed9a0_2
     +91%v,AREA(2)%v)
      SymbolTable_0x81ed9a0_293%v = BLENGTH(3)%v
      SymbolTable_0x81ed9a0_295%v = BWIDTH%v
      AREA(3)%v = (BLENGTH(3)%v*BWIDTH%v)
      SymbolTable_0x81ed9a0_12%v = BWIDTH%v
      SymbolTable_0x81ed9a0_13%v = BLENGTH(3)%v
      SymbolTable_0x81ed9a0_292%v = SymbolTable_0x81ed9a0_12%v
      SymbolTable_0x81ed9a0_294%v = SymbolTable_0x81ed9a0_13%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_292%v,SymbolTable_0x81ed9a0_293
     +%v,AREA(3)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_294%v,SymbolTable_0x81ed9a0_2
     +95%v,AREA(3)%v)
      SymbolTable_0x81ed9a0_297%v = AREA(1)%v
      SymbolTable_0x81ed9a0_299%v = BHEIGHT(1)%v
      VOL(1)%v = (AREA(1)%v*BHEIGHT(1)%v)
      SymbolTable_0x81ed9a0_14%v = BHEIGHT(1)%v
      SymbolTable_0x81ed9a0_15%v = AREA(1)%v
      SymbolTable_0x81ed9a0_296%v = SymbolTable_0x81ed9a0_14%v
      SymbolTable_0x81ed9a0_298%v = SymbolTable_0x81ed9a0_15%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_296%v,SymbolTable_0x81ed9a0_297
     +%v,VOL(1)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_298%v,SymbolTable_0x81ed9a0_2
     +99%v,VOL(1)%v)
      SymbolTable_0x81ed9a0_301%v = BHEIGHT(1)%v
      SymbolTable_0x81ed9a0_303%v = BHEIGHT(3)%v
      SymbolTable_0x81ed9a0_305%v = AREA(2)%v
      SymbolTable_0x81ed9a0_16%v = (BHEIGHT(1)%v+BHEIGHT(3)%v)
      SymbolTable_0x81ed9a0_21%v = (AREA(2)%v*SymbolTable_0x81ed9a0_16%v
     +)
      SymbolTable_0x81ed9a0_17%v = SymbolTable_0x81ed9a0_16%v
      SymbolTable_0x81ed9a0_19%v = 1.0D00
      SymbolTable_0x81ed9a0_20%v = 1.0D00
      SymbolTable_0x81ed9a0_18%v = AREA(2)%v
      VOL(2)%v = SymbolTable_0x81ed9a0_21%v
      SymbolTable_0x81ed9a0_300%v = (SymbolTable_0x81ed9a0_19%v*SymbolTa
     +ble_0x81ed9a0_18%v)
      SymbolTable_0x81ed9a0_302%v = (SymbolTable_0x81ed9a0_20%v*SymbolTa
     +ble_0x81ed9a0_18%v)
      SymbolTable_0x81ed9a0_304%v = SymbolTable_0x81ed9a0_17%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_300%v,SymbolTable_0x81ed9a0_301
     +%v,VOL(2)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_302%v,SymbolTable_0x81ed9a0_3
     +03%v,VOL(2)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_304%v,SymbolTable_0x81ed9a0_3
     +05%v,VOL(2)%v)
      SymbolTable_0x81ed9a0_307%v = AREA(3)%v
      SymbolTable_0x81ed9a0_309%v = BHEIGHT(3)%v
      VOL(3)%v = (AREA(3)%v*BHEIGHT(3)%v)
      SymbolTable_0x81ed9a0_22%v = BHEIGHT(3)%v
      SymbolTable_0x81ed9a0_23%v = AREA(3)%v
      SymbolTable_0x81ed9a0_306%v = SymbolTable_0x81ed9a0_22%v
      SymbolTable_0x81ed9a0_308%v = SymbolTable_0x81ed9a0_23%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_306%v,SymbolTable_0x81ed9a0_307
     +%v,VOL(3)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_308%v,SymbolTable_0x81ed9a0_3
     +09%v,VOL(3)%v)
      ROBERT_FILTER_COEFF%v = 2.5D00
      HUNDRED%v = 1.0D00
      THOUSAND%v = 1.0D00
      DAY%v = 8.64000000000000056843D00
      SymbolTable_0x81ed9a0_311%v = DAY%v
      YEAR%v = (DAY%v*3.64999999999999991118D00)
      SymbolTable_0x81ed9a0_24%v = 3.64999999999999991118D00
      SymbolTable_0x81ed9a0_310%v = SymbolTable_0x81ed9a0_24%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_310%v,SymbolTable_0x81ed9a0_311
     +%v,YEAR%v)
      SV%v = 1.0D00
      SymbolTable_0x81ed9a0_313%v = SV%v
      SymbolTable_0x81ed9a0_26%v = (SV%v*1.60000000000000008882D00)
      SymbolTable_0x81ed9a0_31%v = (SymbolTable_0x81ed9a0_26%v*2.5D-01)
      SymbolTable_0x81ed9a0_29%v = 1.60000000000000008882D00
      SymbolTable_0x81ed9a0_27%v = 2.5D-01
      U0%v = SymbolTable_0x81ed9a0_31%v
      SymbolTable_0x81ed9a0_312%v = (SymbolTable_0x81ed9a0_29%v*SymbolTa
     +ble_0x81ed9a0_27%v)
      CALL sax_a_a(SymbolTable_0x81ed9a0_312%v,SymbolTable_0x81ed9a0_313
     +%v,U0%v)
      ALPHA%v = 1.66799999999999992717D00
      BETA%v = 7.8099999999999996092D00
      DAYS_PER_50M_MIXED_LAYER%v = 5.0D00
      SymbolTable_0x81ed9a0_315%v = DAY%v
      SymbolTable_0x81ed9a0_32%v = (DAY%v*3.0D00)
      SymbolTable_0x81ed9a0_37%v = (1D00/SymbolTable_0x81ed9a0_32%v)
      SymbolTable_0x81ed9a0_35%v = 3.0D00
      SymbolTable_0x81ed9a0_34%v = (-1.0D00)
      GAMMA_T%v = SymbolTable_0x81ed9a0_37%v
      SymbolTable_0x81ed9a0_314%v = (SymbolTable_0x81ed9a0_35%v*SymbolTa
     +ble_0x81ed9a0_34%v)
      CALL sax_a_a(SymbolTable_0x81ed9a0_314%v,SymbolTable_0x81ed9a0_315
     +%v,GAMMA_T%v)
      SymbolTable_0x81ed9a0_319%v = DAY%v
      SymbolTable_0x81ed9a0_321%v = DAYS_PER_50M_MIXED_LAYER%v
      SymbolTable_0x81ed9a0_323%v = BHEIGHT(1)%v
      SymbolTable_0x81ed9a0_41%v = (BHEIGHT(1)%v/5.0D00)
      SymbolTable_0x81ed9a0_42%v = (DAY%v*DAYS_PER_50M_MIXED_LAYER%v)
      SymbolTable_0x81ed9a0_38%v = (SymbolTable_0x81ed9a0_41%v*SymbolTab
     +le_0x81ed9a0_42%v)
      SymbolTable_0x81ed9a0_49%v = (0.0D00/SymbolTable_0x81ed9a0_38%v)
      SymbolTable_0x81ed9a0_45%v = 2.00000000000000011102D-01
      SymbolTable_0x81ed9a0_43%v = SymbolTable_0x81ed9a0_42%v
      SymbolTable_0x81ed9a0_47%v = DAYS_PER_50M_MIXED_LAYER%v
      SymbolTable_0x81ed9a0_48%v = DAY%v
      SymbolTable_0x81ed9a0_44%v = SymbolTable_0x81ed9a0_41%v
      SymbolTable_0x81ed9a0_40%v = (0.0D00/-0.0D00)
      GAMMA_S%v = SymbolTable_0x81ed9a0_49%v
      SymbolTable_0x81ed9a0_316%v = (SymbolTable_0x81ed9a0_43%v*SymbolTa
     +ble_0x81ed9a0_40%v)
      SymbolTable_0x81ed9a0_317%v = (SymbolTable_0x81ed9a0_44%v*SymbolTa
     +ble_0x81ed9a0_40%v)
      SymbolTable_0x81ed9a0_318%v = (SymbolTable_0x81ed9a0_47%v*SymbolTa
     +ble_0x81ed9a0_317%v)
      SymbolTable_0x81ed9a0_320%v = (SymbolTable_0x81ed9a0_48%v*SymbolTa
     +ble_0x81ed9a0_317%v)
      SymbolTable_0x81ed9a0_322%v = (SymbolTable_0x81ed9a0_45%v*SymbolTa
     +ble_0x81ed9a0_316%v)
      CALL sax_a_a(SymbolTable_0x81ed9a0_318%v,SymbolTable_0x81ed9a0_319
     +%v,GAMMA_S%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_320%v,SymbolTable_0x81ed9a0_3
     +21%v,GAMMA_S%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_322%v,SymbolTable_0x81ed9a0_3
     +23%v,GAMMA_S%v)
      EPSILON_IC%v = (-1.0D00)
      SymbolTable_0x81ed9a0_325%v = DAY%v
      NOISE_CORRELATION_TIME%v = (DAY%v*1.5D00)
      SymbolTable_0x81ed9a0_50%v = 1.5D00
      SymbolTable_0x81ed9a0_324%v = SymbolTable_0x81ed9a0_50%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_324%v,SymbolTable_0x81ed9a0_325
     +%v,NOISE_CORRELATION_TIME%v)
      SymbolTable_0x81ed9a0_327%v = DAY%v
      DELTA_T%v = (DAY%v*5.0D00)
      SymbolTable_0x81ed9a0_52%v = 5.0D00
      SymbolTable_0x81ed9a0_326%v = SymbolTable_0x81ed9a0_52%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_326%v,SymbolTable_0x81ed9a0_327
     +%v,DELTA_T%v)
      WRITE(*,*)'delta_t = ',DELTA_T%v
      SymbolTable_0x81ed9a0_329%v = YEAR%v
      INTEGRATION_TIME%v = (YEAR%v*5.0D00)
      SymbolTable_0x81ed9a0_54%v = 5.0D00
      SymbolTable_0x81ed9a0_328%v = SymbolTable_0x81ed9a0_54%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_328%v,SymbolTable_0x81ed9a0_329
     +%v,INTEGRATION_TIME%v)
      WRITE(*,*)'integration_time = ',INTEGRATION_TIME%v
      SymbolTable_0x81ed9a0_331%v = INTEGRATION_TIME%v
      SymbolTable_0x81ed9a0_333%v = DELTA_T%v
      N_MAX%v = (INTEGRATION_TIME%v/DELTA_T%v)
      SymbolTable_0x81ed9a0_56%v = (1D00/DELTA_T%v)
      SymbolTable_0x81ed9a0_57%v = (-(INTEGRATION_TIME%v/SQRT(INTEGRATIO
     +N_TIME%v)))
      SymbolTable_0x81ed9a0_330%v = SymbolTable_0x81ed9a0_56%v
      SymbolTable_0x81ed9a0_332%v = SymbolTable_0x81ed9a0_57%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_330%v,SymbolTable_0x81ed9a0_331
     +%v,N_MAX%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_332%v,SymbolTable_0x81ed9a0_3
     +33%v,N_MAX%v)
      WRITE(*, *) 'n_max = ', N_MAX
      FDEPS%v = 1.0D+01
      SymbolTable_0x81ed9a0_335%v = THOUSAND%v
      Y(1)%v = (THOUSAND%v/3.26799999999999979394D00)
      SymbolTable_0x81ed9a0_58%v = 3.05997552019583840544D-01
      SymbolTable_0x81ed9a0_334%v = SymbolTable_0x81ed9a0_58%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_334%v,SymbolTable_0x81ed9a0_335
     +%v,Y(1)%v)
      SymbolTable_0x81ed9a0_337%v = THOUSAND%v
      Y(2)%v = (THOUSAND%v/7.9400000000000003908D00)
      SymbolTable_0x81ed9a0_60%v = 1.25944584382871538342D-01
      SymbolTable_0x81ed9a0_336%v = SymbolTable_0x81ed9a0_60%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_336%v,SymbolTable_0x81ed9a0_337
     +%v,Y(2)%v)
      SymbolTable_0x81ed9a0_339%v = THOUSAND%v
      Y(3)%v = (THOUSAND%v/1.39999999999999991118D00)
      SymbolTable_0x81ed9a0_62%v = 7.14285714285714301575D-01
      SymbolTable_0x81ed9a0_338%v = SymbolTable_0x81ed9a0_62%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_338%v,SymbolTable_0x81ed9a0_339
     +%v,Y(3)%v)
      SymbolTable_0x81ed9a0_341%v = THOUSAND%v
      Y(4)%v = (THOUSAND%v/1.4170000000000000373D00)
      SymbolTable_0x81ed9a0_64%v = 7.05716302046577204088D-01
      SymbolTable_0x81ed9a0_340%v = SymbolTable_0x81ed9a0_64%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_340%v,SymbolTable_0x81ed9a0_341
     +%v,Y(4)%v)
      SymbolTable_0x81ed9a0_343%v = THOUSAND%v
      Y(5)%v = (THOUSAND%v/1.28600000000000003197D00)
      SymbolTable_0x81ed9a0_66%v = 7.77604976671850689485D-01
      SymbolTable_0x81ed9a0_342%v = SymbolTable_0x81ed9a0_66%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_342%v,SymbolTable_0x81ed9a0_343
     +%v,Y(5)%v)
      SymbolTable_0x81ed9a0_345%v = THOUSAND%v
      Y(6)%v = (THOUSAND%v/8.77999999999999936051D00)
      SymbolTable_0x81ed9a0_68%v = 1.13895216400911172827D-01
      SymbolTable_0x81ed9a0_344%v = SymbolTable_0x81ed9a0_68%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_344%v,SymbolTable_0x81ed9a0_345
     +%v,Y(6)%v)
      SymbolTable_0x81ed9a0_347%v = ALPHA%v
      SymbolTable_0x81ed9a0_349%v = DELTA%v
      R(1)%v = (ALPHA%v*DELTA%v)
      SymbolTable_0x81ed9a0_70%v = DELTA%v
      SymbolTable_0x81ed9a0_71%v = ALPHA%v
      SymbolTable_0x81ed9a0_346%v = SymbolTable_0x81ed9a0_70%v
      SymbolTable_0x81ed9a0_348%v = SymbolTable_0x81ed9a0_71%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_346%v,SymbolTable_0x81ed9a0_347
     +%v,R(1)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_348%v,SymbolTable_0x81ed9a0_3
     +49%v,R(1)%v)
      SymbolTable_0x81ed9a0_351%v = ALPHA%v
      R(2)%v = (-ALPHA%v)
      SymbolTable_0x81ed9a0_72%v = 4.294967295D+09
      SymbolTable_0x81ed9a0_350%v = SymbolTable_0x81ed9a0_72%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_350%v,SymbolTable_0x81ed9a0_351
     +%v,R(2)%v)
      SymbolTable_0x81ed9a0_353%v = DELTA%v
      SymbolTable_0x81ed9a0_355%v = ALPHA%v
      SymbolTable_0x81ed9a0_73%v = (1.0D00-DELTA%v)
      SymbolTable_0x81ed9a0_78%v = (ALPHA%v*SymbolTable_0x81ed9a0_73%v)
      SymbolTable_0x81ed9a0_74%v = SymbolTable_0x81ed9a0_73%v
      SymbolTable_0x81ed9a0_77%v = 4.294967295D+09
      SymbolTable_0x81ed9a0_75%v = ALPHA%v
      R(3)%v = SymbolTable_0x81ed9a0_78%v
      SymbolTable_0x81ed9a0_352%v = (SymbolTable_0x81ed9a0_77%v*SymbolTa
     +ble_0x81ed9a0_75%v)
      SymbolTable_0x81ed9a0_354%v = SymbolTable_0x81ed9a0_74%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_352%v,SymbolTable_0x81ed9a0_353
     +%v,R(3)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_354%v,SymbolTable_0x81ed9a0_3
     +55%v,R(3)%v)
      SymbolTable_0x81ed9a0_357%v = BETA%v
      SymbolTable_0x81ed9a0_359%v = DELTA%v
      R(4)%v = (-(BETA%v*DELTA%v))
      SymbolTable_0x81ed9a0_80%v = DELTA%v
      SymbolTable_0x81ed9a0_81%v = BETA%v
      SymbolTable_0x81ed9a0_79%v = 4.294967295D+09
      SymbolTable_0x81ed9a0_356%v = (SymbolTable_0x81ed9a0_80%v*SymbolTa
     +ble_0x81ed9a0_79%v)
      SymbolTable_0x81ed9a0_358%v = (SymbolTable_0x81ed9a0_81%v*SymbolTa
     +ble_0x81ed9a0_79%v)
      CALL sax_a_a(SymbolTable_0x81ed9a0_356%v,SymbolTable_0x81ed9a0_357
     +%v,R(4)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_358%v,SymbolTable_0x81ed9a0_3
     +59%v,R(4)%v)
      R(5)%v = BETA%v
      CALL sax_a_a(1.0D00,BETA%v,R(5)%v)
      SymbolTable_0x81ed9a0_362%v = BETA%v
      SymbolTable_0x81ed9a0_364%v = DELTA%v
      SymbolTable_0x81ed9a0_83%v = (1.0D00-DELTA%v)
      SymbolTable_0x81ed9a0_88%v = (-(BETA%v*SymbolTable_0x81ed9a0_83%v)
     +)
      SymbolTable_0x81ed9a0_84%v = SymbolTable_0x81ed9a0_83%v
      SymbolTable_0x81ed9a0_87%v = 4.294967295D+09
      SymbolTable_0x81ed9a0_85%v = BETA%v
      SymbolTable_0x81ed9a0_82%v = 4.294967295D+09
      R(6)%v = SymbolTable_0x81ed9a0_88%v
      SymbolTable_0x81ed9a0_360%v = (SymbolTable_0x81ed9a0_87%v*SymbolTa
     +ble_0x81ed9a0_85%v)
      SymbolTable_0x81ed9a0_361%v = (SymbolTable_0x81ed9a0_84%v*SymbolTa
     +ble_0x81ed9a0_82%v)
      SymbolTable_0x81ed9a0_363%v = (SymbolTable_0x81ed9a0_360%v*SymbolT
     +able_0x81ed9a0_82%v)
      CALL sax_a_a(SymbolTable_0x81ed9a0_361%v,SymbolTable_0x81ed9a0_362
     +%v,R(6)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_363%v,SymbolTable_0x81ed9a0_3
     +64%v,R(6)%v)
      DO L = 1, 6, 1
        SymbolTable_0x81ed9a0_366%v = R(L)%v
        SymbolTable_0x81ed9a0_368%v = U0%v
        SymbolTable_0x81ed9a0_370%v = SV%v
        SymbolTable_0x81ed9a0_89%v = (R(L)%v*U0%v)
        SymbolTable_0x81ed9a0_94%v = (SymbolTable_0x81ed9a0_89%v/SV%v)
        SymbolTable_0x81ed9a0_92%v = U0%v
        SymbolTable_0x81ed9a0_93%v = R(L)%v
        SymbolTable_0x81ed9a0_90%v = (1D00/SV%v)
        SymbolTable_0x81ed9a0_91%v = (-(SymbolTable_0x81ed9a0_89%v/SQRT(
     +SymbolTable_0x81ed9a0_89%v)))
        R(L)%v = SymbolTable_0x81ed9a0_94%v
        SymbolTable_0x81ed9a0_365%v = (SymbolTable_0x81ed9a0_92%v*Symbol
     +Table_0x81ed9a0_90%v)
        SymbolTable_0x81ed9a0_367%v = (SymbolTable_0x81ed9a0_93%v*Symbol
     +Table_0x81ed9a0_90%v)
        SymbolTable_0x81ed9a0_369%v = SymbolTable_0x81ed9a0_91%v
        CALL sax_a_a(SymbolTable_0x81ed9a0_365%v,SymbolTable_0x81ed9a0_3
     +66%v,R(L)%v)
        CALL saxpy_a_a(SymbolTable_0x81ed9a0_367%v,SymbolTable_0x81ed9a0
     +_368%v,R(L)%v)
        CALL saxpy_a_a(SymbolTable_0x81ed9a0_369%v,SymbolTable_0x81ed9a0
     +_370%v,R(L)%v)
      END DO
      DO L = 1, 6, 1
        IF(L .LE. 3) THEN
          PROJ_T(L)%v = 1.0D00
          PROJ_S(L)%v = 0.0D00
        ELSE
          PROJ_T(L)%v = 0.0D00
          PROJ_S(L)%v = 1.0D00
        ENDIF
      END DO
      DO L = 1, 6, 1
        SymbolTable_0x81ed9a0_372%v = PROJ_T(L)%v
        SymbolTable_0x81ed9a0_374%v = R(L)%v
        R_T(L)%v = (PROJ_T(L)%v*R(L)%v)
        SymbolTable_0x81ed9a0_95%v = R(L)%v
        SymbolTable_0x81ed9a0_96%v = PROJ_T(L)%v
        SymbolTable_0x81ed9a0_371%v = SymbolTable_0x81ed9a0_95%v
        SymbolTable_0x81ed9a0_373%v = SymbolTable_0x81ed9a0_96%v
        CALL sax_a_a(SymbolTable_0x81ed9a0_371%v,SymbolTable_0x81ed9a0_3
     +72%v,R_T(L)%v)
        CALL saxpy_a_a(SymbolTable_0x81ed9a0_373%v,SymbolTable_0x81ed9a0
     +_374%v,R_T(L)%v)
        SymbolTable_0x81ed9a0_376%v = PROJ_S(L)%v
        SymbolTable_0x81ed9a0_378%v = R(L)%v
        R_S(L)%v = (PROJ_S(L)%v*R(L)%v)
        SymbolTable_0x81ed9a0_97%v = R(L)%v
        SymbolTable_0x81ed9a0_98%v = PROJ_S(L)%v
        SymbolTable_0x81ed9a0_375%v = SymbolTable_0x81ed9a0_97%v
        SymbolTable_0x81ed9a0_377%v = SymbolTable_0x81ed9a0_98%v
        CALL sax_a_a(SymbolTable_0x81ed9a0_375%v,SymbolTable_0x81ed9a0_3
     +76%v,R_S(L)%v)
        CALL saxpy_a_a(SymbolTable_0x81ed9a0_377%v,SymbolTable_0x81ed9a0
     +_378%v,R_S(L)%v)
      END DO
      R1(1)%v = 1.0D00
      R1(2)%v = (-1.0D00)
      R1(3)%v = 0.0D00
      R1(4)%v = 0.0D00
      R1(5)%v = 0.0D00
      R1(6)%v = 0.0D00
      DO J = 1, 6, 1
        DO I = 1, 6, 1
          SymbolTable_0x81ed9a0_380%v = R(I)%v
          SymbolTable_0x81ed9a0_382%v = R(J)%v
          X(J,I)%v = (R(I)%v*R(J)%v)
          SymbolTable_0x81ed9a0_99%v = R(J)%v
          SymbolTable_0x81ed9a0_100%v = R(I)%v
          SymbolTable_0x81ed9a0_379%v = SymbolTable_0x81ed9a0_99%v
          SymbolTable_0x81ed9a0_381%v = SymbolTable_0x81ed9a0_100%v
          CALL sax_a_a(SymbolTable_0x81ed9a0_379%v,SymbolTable_0x81ed9a0
     +_380%v,X(J,I)%v)
          CALL saxpy_a_a(SymbolTable_0x81ed9a0_381%v,SymbolTable_0x81ed9
     +a0_382%v,X(J,I)%v)
        END DO
      END DO
      EPSILON_REGULARIZE%v = 1.0D00
      DO J = 1, 6, 1
        DO I = 1, 6, 1
          SymbolTable_0x81ed9a0_384%v = X(J,I)%v
          SymbolTable_0x81ed9a0_386%v = EPSILON_REGULARIZE%v
          X(J,I)%v = (X(J,I)%v+EPSILON_REGULARIZE%v)
          SymbolTable_0x81ed9a0_101%v = 1.0D00
          SymbolTable_0x81ed9a0_102%v = 1.0D00
          SymbolTable_0x81ed9a0_383%v = SymbolTable_0x81ed9a0_101%v
          SymbolTable_0x81ed9a0_385%v = SymbolTable_0x81ed9a0_102%v
          CALL sax_a_a(SymbolTable_0x81ed9a0_383%v,SymbolTable_0x81ed9a0
     +_384%v,X(J,I)%v)
          CALL saxpy_a_a(SymbolTable_0x81ed9a0_385%v,SymbolTable_0x81ed9
     +a0_386%v,X(J,I)%v)
        END DO
      END DO
      RETURN
      END SUBROUTINE

      SUBROUTINE box_ini_fields()
      use w2f__types
      use active_module
      IMPLICIT NONE
C
C     **** Variables and functions ****
C
      INTEGER(w2f__i4) L
      COMMON /pa_geometry_r/ BLENGTH, BHEIGHT, BWIDTH, AREA, VOL
      type(active) :: BLENGTH(1 : 3)
      type(active) :: BHEIGHT(1 : 3)
      type(active) :: BWIDTH
      type(active) :: AREA(1 : 3)
      type(active) :: VOL(1 : 3)
      COMMON /pa_parameters_r/ HUNDRED, THOUSAND, DAY, YEAR, SV,
     >  DAYS_PER_50M_MIXED_LAYER, GAMMA_T, GAMMA_S, EPSILON_IC,
     >  NOISE_CORRELATION_TIME, INTEGRATION_TIME, EPSILON_REGULARIZE,
     >  FDEPS
      type(active) :: HUNDRED
      type(active) :: THOUSAND
      type(active) :: DAY
      type(active) :: YEAR
      type(active) :: SV
      type(active) :: DAYS_PER_50M_MIXED_LAYER
      type(active) :: GAMMA_T
      type(active) :: GAMMA_S
      type(active) :: EPSILON_IC
      type(active) :: NOISE_CORRELATION_TIME
      type(active) :: INTEGRATION_TIME
      type(active) :: EPSILON_REGULARIZE
      type(active) :: FDEPS
      COMMON /fi_forcing_params_r/ NULLFORCE, FW, TSTAR, SSTAR
      type(active) :: NULLFORCE(1 : 2)
      type(active) :: FW(1 : 2)
      type(active) :: TSTAR(1 : 2)
      type(active) :: SSTAR(1 : 2)
      COMMON /fi_metric_r/ METRIC
      type(active) :: METRIC
      COMMON /fi_metric_aux_r/ METRIC1, METRIC2
      type(active) :: METRIC1
      type(active) :: METRIC2
      COMMON /fi_ini_r/ UBAR, T, S
      type(active) :: UBAR
      type(active) :: T(1 : 3)
      type(active) :: S(1 : 3)
      COMMON /fi_state_r/ TOLD, TNOW, TNEW, SOLD, SNOW, SNEW
      type(active) :: TOLD(1 : 3)
      type(active) :: TNOW(1 : 3)
      type(active) :: TNEW(1 : 3)
      type(active) :: SOLD(1 : 3)
      type(active) :: SNOW(1 : 3)
      type(active) :: SNEW(1 : 3)
      COMMON /fi_thc_r/ THC_TOT, THC_T, THC_S
      type(active) :: THC_TOT
      type(active) :: THC_T
      type(active) :: THC_S
      COMMON /fi_final_state_r/ TSVEC
      type(active) :: TSVEC(1 : 6)
      COMMON /fi_velocity_r/ UVEL
      type(active) :: UVEL
      COMMON /fi_controls_r/ XX
      type(active) :: XX(1 : 6)
      type(active) :: SymbolTable_0x81ed9a0_103
      type(active) :: SymbolTable_0x81ed9a0_104
      type(active) :: SymbolTable_0x81ed9a0_105
      type(active) :: SymbolTable_0x81ed9a0_110
      type(active) :: SymbolTable_0x81ed9a0_106
      type(active) :: SymbolTable_0x81ed9a0_111
      type(active) :: SymbolTable_0x81ed9a0_107
      type(active) :: SymbolTable_0x81ed9a0_112
      type(active) :: SymbolTable_0x81ed9a0_113
      type(active) :: SymbolTable_0x81ed9a0_109
      type(active) :: SymbolTable_0x81ed9a0_115
      type(active) :: SymbolTable_0x81ed9a0_116
      type(active) :: SymbolTable_0x81ed9a0_117
      type(active) :: SymbolTable_0x81ed9a0_118
      type(active) :: SymbolTable_0x81ed9a0_400
      type(active) :: SymbolTable_0x81ed9a0_401
      type(active) :: SymbolTable_0x81ed9a0_402
      type(active) :: SymbolTable_0x81ed9a0_403
      type(active) :: SymbolTable_0x81ed9a0_404
      type(active) :: SymbolTable_0x81ed9a0_405
      type(active) :: SymbolTable_0x81ed9a0_390
      type(active) :: SymbolTable_0x81ed9a0_391
      type(active) :: SymbolTable_0x81ed9a0_392
      type(active) :: SymbolTable_0x81ed9a0_387
      type(active) :: SymbolTable_0x81ed9a0_393
      type(active) :: SymbolTable_0x81ed9a0_388
      type(active) :: SymbolTable_0x81ed9a0_394
      type(active) :: SymbolTable_0x81ed9a0_389
      type(active) :: SymbolTable_0x81ed9a0_395
      type(active) :: SymbolTable_0x81ed9a0_396
      type(active) :: SymbolTable_0x81ed9a0_397
      type(active) :: SymbolTable_0x81ed9a0_398
      type(active) :: SymbolTable_0x81ed9a0_399
C
C     **** statements ****
C
      THC_TOT%v = 0.0D00
      THC_T%v = 0.0D00
      THC_S%v = 0.0D00
      METRIC1%v = 0.0D00
      METRIC2%v = 0.0D00
      METRIC%v = 0.0D00
      NULLFORCE(1)%v = 0.0D00
      NULLFORCE(2)%v = 0.0D00
      SymbolTable_0x81ed9a0_389%v = HUNDRED%v
      SymbolTable_0x81ed9a0_391%v = YEAR%v
      SymbolTable_0x81ed9a0_393%v = AREA(1)%v
      SymbolTable_0x81ed9a0_106%v = (HUNDRED%v/YEAR%v)
      SymbolTable_0x81ed9a0_103%v = (SymbolTable_0x81ed9a0_106%v*3.5D00)
      SymbolTable_0x81ed9a0_111%v = (AREA(1)%v*SymbolTable_0x81ed9a0_103
     +%v)
      SymbolTable_0x81ed9a0_104%v = SymbolTable_0x81ed9a0_103%v
      SymbolTable_0x81ed9a0_109%v = (1D00/YEAR%v)
      SymbolTable_0x81ed9a0_110%v = (-(HUNDRED%v/SQRT(HUNDRED%v)))
      SymbolTable_0x81ed9a0_107%v = 3.5D00
      SymbolTable_0x81ed9a0_105%v = AREA(1)%v
      FW(1)%v = SymbolTable_0x81ed9a0_111%v
      SymbolTable_0x81ed9a0_387%v = (SymbolTable_0x81ed9a0_107%v*SymbolT
     +able_0x81ed9a0_105%v)
      SymbolTable_0x81ed9a0_388%v = (SymbolTable_0x81ed9a0_109%v*SymbolT
     +able_0x81ed9a0_387%v)
      SymbolTable_0x81ed9a0_390%v = (SymbolTable_0x81ed9a0_110%v*SymbolT
     +able_0x81ed9a0_387%v)
      SymbolTable_0x81ed9a0_392%v = SymbolTable_0x81ed9a0_104%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_388%v,SymbolTable_0x81ed9a0_389
     +%v,FW(1)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_390%v,SymbolTable_0x81ed9a0_3
     +91%v,FW(1)%v)
      CALL saxpy_a_a(SymbolTable_0x81ed9a0_392%v,SymbolTable_0x81ed9a0_3
     +93%v,FW(1)%v)
      SymbolTable_0x81ed9a0_395%v = FW(1)%v
      FW(2)%v = (-FW(1)%v)
      SymbolTable_0x81ed9a0_112%v = 4.294967295D+09
      SymbolTable_0x81ed9a0_394%v = SymbolTable_0x81ed9a0_112%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_394%v,SymbolTable_0x81ed9a0_395
     +%v,FW(2)%v)
      TSTAR(1)%v = 2.20000000000000017764D00
      TSTAR(2)%v = 0.0D00
      SSTAR(1)%v = 3.60000000000000008882D00
      SSTAR(2)%v = 3.39999999999999991118D00
      SymbolTable_0x81ed9a0_397%v = SV%v
      UBAR%v = (SV%v*2.0D00)
      SymbolTable_0x81ed9a0_113%v = 2.0D00
      SymbolTable_0x81ed9a0_396%v = SymbolTable_0x81ed9a0_113%v
      CALL sax_a_a(SymbolTable_0x81ed9a0_396%v,SymbolTable_0x81ed9a0_397
     +%v,UBAR%v)
      T(1)%v = 2.0D00
      T(2)%v = 1.0D00
      T(3)%v = 1.0D00
      S(1)%v = 3.54999999999999982236D00
      S(2)%v = 3.45000000000000017764D00
      S(3)%v = 3.45000000000000017764D00
      DO L = 1, 6, 1
        TSVEC(L)%v = 0.0D00
      END DO
      DO L = 1, 3, 1
        SymbolTable_0x81ed9a0_399%v = T(L)%v
        SymbolTable_0x81ed9a0_401%v = XX(L)%v
        T(L)%v = (T(L)%v+XX(L)%v)
        SymbolTable_0x81ed9a0_115%v = 1.0D00
        SymbolTable_0x81ed9a0_116%v = 1.0D00
        SymbolTable_0x81ed9a0_398%v = SymbolTable_0x81ed9a0_115%v
        SymbolTable_0x81ed9a0_400%v = SymbolTable_0x81ed9a0_116%v
        CALL sax_a_a(SymbolTable_0x81ed9a0_398%v,SymbolTable_0x81ed9a0_3
     +99%v,T(L)%v)
        CALL saxpy_a_a(SymbolTable_0x81ed9a0_400%v,SymbolTable_0x81ed9a0
     +_401%v,T(L)%v)
        SymbolTable_0x81ed9a0_403%v = S(L)%v
        SymbolTable_0x81ed9a0_405%v = XX(L+3.0D00)%v
        S(L)%v = (S(L)%v+XX(L+3.0D00)%v)
        SymbolTable_0x81ed9a0_117%v = 1.0D00
        SymbolTable_0x81ed9a0_118%v = 1.0D00
        SymbolTable_0x81ed9a0_402%v = SymbolTable_0x81ed9a0_117%v
        SymbolTable_0x81ed9a0_404%v = SymbolTable_0x81ed9a0_118%v
        CALL sax_a_a(SymbolTable_0x81ed9a0_402%v,SymbolTable_0x81ed9a0_4
     +03%v,S(L)%v)
        CALL saxpy_a_a(SymbolTable_0x81ed9a0_404%v,SymbolTable_0x81ed9a0
     +_405%v,S(L)%v)
      END DO
      DO L = 1, 3, 1
        TNEW(L)%v = T(L)%v
        CALL sax_a_a(1.0D00,T(L)%v,TNEW(L)%v)
        SNEW(L)%v = S(L)%v
        CALL sax_a_a(1.0D00,S(L)%v,SNEW(L)%v)
        TOLD(L)%v = T(L)%v
        CALL sax_a_a(1.0D00,T(L)%v,TOLD(L)%v)
        SOLD(L)%v = S(L)%v
        CALL sax_a_a(1.0D00,S(L)%v,SOLD(L)%v)
        TNOW(L)%v = T(L)%v
        CALL sax_a_a(1.0D00,T(L)%v,TNOW(L)%v)
        SNOW(L)%v = S(L)%v
        CALL sax_a_a(1.0D00,S(L)%v,SNOW(L)%v)
      END DO
      UVEL%v = UBAR%v
      CALL sax_a_a(1.0D00,UBAR%v,UVEL%v)
      RETURN
      END SUBROUTINE
W2F1PP
    $ff = Ffile->new_from_heredoc($w2f1);
}

sub x2wp {
    my($line) = @_;
    my($scn) = FTscan->new($line);
    if ($scn->match(qr/use $TB w2f__types $TBE /x)){
	return($line,<<'U');
      use active_module
U
    }
    if($line =~ /^\s+real\(w2f__8\)\s+/i) {
	$line =~s/real\(w2f__8\)/type(active) ::/i;
	return $line;
    }
    if($scn->match(qr/ __value__ $TB \( $TB/x)){
	return ($scn->grterm(qr/__value__/,\&xaif_t)->lstring());
    }
    return($UNCHANGED);
}

sub xaif_t {
    my($v) = $_[0]->copy();
    my(@tl) = $v->tl();
    $v->set_tl(@tl[2 .. $#tl-1]); # pick up arg tokens
    my($s) = $v->str();

    return FTscan->new("$s%v");
}

sub teardown{
}
