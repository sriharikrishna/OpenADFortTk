use FindBin qw($RealBin);
use lib "$RealBin/../Lib";
use lib "$RealBin/../Lib/FT";
use Test::More qw(no_plan);

use Ffile;
use FTscan;
use FTpat;
use ADxaif;
use ADinline;
use ADtemplate;

use PPsetup;

setup();

is($ff->rewrite_sem(\&xaifpp)->to_string(),$w2f1_pp,'xaif pp ok');

teardown();

sub setup{
    $w2f1 = <<'W2F1';
      use w2f__types
      IMPLICIT NONE
C
C     **** Global Variables ****
C
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
      REAL(w2f__8) SymbolTable_0x84b9ed0_10
      REAL(w2f__8) SymbolTable_0x84b9ed0_11
      REAL(w2f__8) SymbolTable_0x84b9ed0_12
      REAL(w2f__8) SymbolTable_0x84b9ed0_13
      REAL(w2f__8) SymbolTable_0x84b9ed0_14
      REAL(w2f__8) SymbolTable_0x84b9ed0_15
      REAL(w2f__8) SymbolTable_0x84b9ed0_20
      REAL(w2f__8) SymbolTable_0x84b9ed0_16
      REAL(w2f__8) SymbolTable_0x84b9ed0_21
      REAL(w2f__8) SymbolTable_0x84b9ed0_17
      REAL(w2f__8) SymbolTable_0x84b9ed0_22
      REAL(w2f__8) SymbolTable_0x84b9ed0_18
      REAL(w2f__8) SymbolTable_0x84b9ed0_23
      REAL(w2f__8) SymbolTable_0x84b9ed0_19
      REAL(w2f__8) SymbolTable_0x84b9ed0_24
      REAL(w2f__8) SymbolTable_0x84b9ed0_26
      REAL(w2f__8) SymbolTable_0x84b9ed0_31
      REAL(w2f__8) SymbolTable_0x84b9ed0_27
      REAL(w2f__8) SymbolTable_0x84b9ed0_32
      REAL(w2f__8) SymbolTable_0x84b9ed0_29
      REAL(w2f__8) SymbolTable_0x84b9ed0_34
      REAL(w2f__8) SymbolTable_0x84b9ed0_35
      REAL(w2f__8) SymbolTable_0x84b9ed0_40
      REAL(w2f__8) SymbolTable_0x84b9ed0_41
      REAL(w2f__8) SymbolTable_0x84b9ed0_37
      REAL(w2f__8) SymbolTable_0x84b9ed0_42
      REAL(w2f__8) SymbolTable_0x84b9ed0_38
      REAL(w2f__8) SymbolTable_0x84b9ed0_43
      REAL(w2f__8) SymbolTable_0x84b9ed0_44
      REAL(w2f__8) SymbolTable_0x84b9ed0_45
      REAL(w2f__8) SymbolTable_0x84b9ed0_50
      REAL(w2f__8) SymbolTable_0x84b9ed0_47
      REAL(w2f__8) SymbolTable_0x84b9ed0_52
      REAL(w2f__8) SymbolTable_0x84b9ed0_48
      REAL(w2f__8) SymbolTable_0x84b9ed0_49
      REAL(w2f__8) SymbolTable_0x84b9ed0_54
      REAL(w2f__8) SymbolTable_0x84b9ed0_60
      REAL(w2f__8) SymbolTable_0x84b9ed0_56
      REAL(w2f__8) SymbolTable_0x84b9ed0_62
      REAL(w2f__8) SymbolTable_0x84b9ed0_58
      REAL(w2f__8) SymbolTable_0x84b9ed0_64
      REAL(w2f__8) SymbolTable_0x84b9ed0_70
      REAL(w2f__8) SymbolTable_0x84b9ed0_66
      REAL(w2f__8) SymbolTable_0x84b9ed0_71
      REAL(w2f__8) SymbolTable_0x84b9ed0_72
      REAL(w2f__8) SymbolTable_0x84b9ed0_68
      REAL(w2f__8) SymbolTable_0x84b9ed0_73
      REAL(w2f__8) SymbolTable_0x84b9ed0_69
      REAL(w2f__8) SymbolTable_0x84b9ed0_75
      REAL(w2f__8) SymbolTable_0x84b9ed0_80
      REAL(w2f__8) SymbolTable_0x84b9ed0_76
      REAL(w2f__8) SymbolTable_0x84b9ed0_81
      REAL(w2f__8) SymbolTable_0x84b9ed0_77
      REAL(w2f__8) SymbolTable_0x84b9ed0_82
      REAL(w2f__8) SymbolTable_0x84b9ed0_78
      REAL(w2f__8) SymbolTable_0x84b9ed0_83
      REAL(w2f__8) SymbolTable_0x84b9ed0_79
      REAL(w2f__8) SymbolTable_0x84b9ed0_85
      REAL(w2f__8) SymbolTable_0x84b9ed0_90
      REAL(w2f__8) SymbolTable_0x84b9ed0_86
      REAL(w2f__8) SymbolTable_0x84b9ed0_91
      REAL(w2f__8) SymbolTable_0x84b9ed0_87
      REAL(w2f__8) SymbolTable_0x84b9ed0_92
      REAL(w2f__8) SymbolTable_0x84b9ed0_88
      REAL(w2f__8) SymbolTable_0x84b9ed0_93
      REAL(w2f__8) SymbolTable_0x84b9ed0_89
      REAL(w2f__8) SymbolTable_0x84b9ed0_94
      REAL(w2f__8) SymbolTable_0x84b9ed0_95
      REAL(w2f__8) SymbolTable_0x84b9ed0_96
      REAL(w2f__8) SymbolTable_0x84b9ed0_97
      REAL(w2f__8) SymbolTable_0x84b9ed0_98
      REAL(w2f__8) SymbolTable_0x84b9ed0_99
      REAL(w2f__8) SymbolTable_0x84b9ed0_100
      REAL(w2f__8) SymbolTable_0x84b9ed0_300
      REAL(w2f__8) SymbolTable_0x84b9ed0_301
      REAL(w2f__8) SymbolTable_0x84b9ed0_302
      REAL(w2f__8) SymbolTable_0x84b9ed0_303
      REAL(w2f__8) SymbolTable_0x84b9ed0_304
      REAL(w2f__8) SymbolTable_0x84b9ed0_310
      REAL(w2f__8) SymbolTable_0x84b9ed0_305
      REAL(w2f__8) SymbolTable_0x84b9ed0_311
      REAL(w2f__8) SymbolTable_0x84b9ed0_306
      REAL(w2f__8) SymbolTable_0x84b9ed0_312
      REAL(w2f__8) SymbolTable_0x84b9ed0_307
      REAL(w2f__8) SymbolTable_0x84b9ed0_313
      REAL(w2f__8) SymbolTable_0x84b9ed0_308
      REAL(w2f__8) SymbolTable_0x84b9ed0_314
      REAL(w2f__8) SymbolTable_0x84b9ed0_309
      REAL(w2f__8) SymbolTable_0x84b9ed0_320
      REAL(w2f__8) SymbolTable_0x84b9ed0_315
      REAL(w2f__8) SymbolTable_0x84b9ed0_321
      REAL(w2f__8) SymbolTable_0x84b9ed0_316
      REAL(w2f__8) SymbolTable_0x84b9ed0_322
      REAL(w2f__8) SymbolTable_0x84b9ed0_317
      REAL(w2f__8) SymbolTable_0x84b9ed0_272
      REAL(w2f__8) SymbolTable_0x84b9ed0_323
      REAL(w2f__8) SymbolTable_0x84b9ed0_318
      REAL(w2f__8) SymbolTable_0x84b9ed0_273
      REAL(w2f__8) SymbolTable_0x84b9ed0_324
      REAL(w2f__8) SymbolTable_0x84b9ed0_319
      REAL(w2f__8) SymbolTable_0x84b9ed0_274
      REAL(w2f__8) SymbolTable_0x84b9ed0_330
      REAL(w2f__8) SymbolTable_0x84b9ed0_325
      REAL(w2f__8) SymbolTable_0x84b9ed0_275
      REAL(w2f__8) SymbolTable_0x84b9ed0_280
      REAL(w2f__8) SymbolTable_0x84b9ed0_331
      REAL(w2f__8) SymbolTable_0x84b9ed0_326
      REAL(w2f__8) SymbolTable_0x84b9ed0_276
      REAL(w2f__8) SymbolTable_0x84b9ed0_281
      REAL(w2f__8) SymbolTable_0x84b9ed0_332
      REAL(w2f__8) SymbolTable_0x84b9ed0_327
      REAL(w2f__8) SymbolTable_0x84b9ed0_277
      REAL(w2f__8) SymbolTable_0x84b9ed0_282
      REAL(w2f__8) SymbolTable_0x84b9ed0_333
      REAL(w2f__8) SymbolTable_0x84b9ed0_328
      REAL(w2f__8) SymbolTable_0x84b9ed0_278
      REAL(w2f__8) SymbolTable_0x84b9ed0_283
      REAL(w2f__8) SymbolTable_0x84b9ed0_334
      REAL(w2f__8) SymbolTable_0x84b9ed0_329
      REAL(w2f__8) SymbolTable_0x84b9ed0_279
      REAL(w2f__8) SymbolTable_0x84b9ed0_284
      REAL(w2f__8) SymbolTable_0x84b9ed0_340
      REAL(w2f__8) SymbolTable_0x84b9ed0_335
      REAL(w2f__8) SymbolTable_0x84b9ed0_285
      REAL(w2f__8) SymbolTable_0x84b9ed0_290
      REAL(w2f__8) SymbolTable_0x84b9ed0_341
      REAL(w2f__8) SymbolTable_0x84b9ed0_336
      REAL(w2f__8) SymbolTable_0x84b9ed0_286
      REAL(w2f__8) SymbolTable_0x84b9ed0_291
      REAL(w2f__8) SymbolTable_0x84b9ed0_342
      REAL(w2f__8) SymbolTable_0x84b9ed0_337
      REAL(w2f__8) SymbolTable_0x84b9ed0_287
      REAL(w2f__8) SymbolTable_0x84b9ed0_292
      REAL(w2f__8) SymbolTable_0x84b9ed0_343
      REAL(w2f__8) SymbolTable_0x84b9ed0_338
      REAL(w2f__8) SymbolTable_0x84b9ed0_288
      REAL(w2f__8) SymbolTable_0x84b9ed0_293
      REAL(w2f__8) SymbolTable_0x84b9ed0_344
      REAL(w2f__8) SymbolTable_0x84b9ed0_339
      REAL(w2f__8) SymbolTable_0x84b9ed0_289
      REAL(w2f__8) SymbolTable_0x84b9ed0_294
      REAL(w2f__8) SymbolTable_0x84b9ed0_350
      REAL(w2f__8) SymbolTable_0x84b9ed0_345
      REAL(w2f__8) SymbolTable_0x84b9ed0_295
      REAL(w2f__8) SymbolTable_0x84b9ed0_351
      REAL(w2f__8) SymbolTable_0x84b9ed0_346
      REAL(w2f__8) SymbolTable_0x84b9ed0_296
      REAL(w2f__8) SymbolTable_0x84b9ed0_352
      REAL(w2f__8) SymbolTable_0x84b9ed0_347
      REAL(w2f__8) SymbolTable_0x84b9ed0_297
      REAL(w2f__8) SymbolTable_0x84b9ed0_353
      REAL(w2f__8) SymbolTable_0x84b9ed0_348
      REAL(w2f__8) SymbolTable_0x84b9ed0_298
      REAL(w2f__8) SymbolTable_0x84b9ed0_354
      REAL(w2f__8) SymbolTable_0x84b9ed0_349
      REAL(w2f__8) SymbolTable_0x84b9ed0_299
      REAL(w2f__8) SymbolTable_0x84b9ed0_360
      REAL(w2f__8) SymbolTable_0x84b9ed0_355
      REAL(w2f__8) SymbolTable_0x84b9ed0_361
      REAL(w2f__8) SymbolTable_0x84b9ed0_356
      REAL(w2f__8) SymbolTable_0x84b9ed0_362
      REAL(w2f__8) SymbolTable_0x84b9ed0_357
      REAL(w2f__8) SymbolTable_0x84b9ed0_363
      REAL(w2f__8) SymbolTable_0x84b9ed0_358
      REAL(w2f__8) SymbolTable_0x84b9ed0_364
      REAL(w2f__8) SymbolTable_0x84b9ed0_359
      REAL(w2f__8) SymbolTable_0x84b9ed0_370
      REAL(w2f__8) SymbolTable_0x84b9ed0_365
      REAL(w2f__8) SymbolTable_0x84b9ed0_371
      REAL(w2f__8) SymbolTable_0x84b9ed0_366
      REAL(w2f__8) SymbolTable_0x84b9ed0_372
      REAL(w2f__8) SymbolTable_0x84b9ed0_367
      REAL(w2f__8) SymbolTable_0x84b9ed0_373
      REAL(w2f__8) SymbolTable_0x84b9ed0_368
      REAL(w2f__8) SymbolTable_0x84b9ed0_374
      REAL(w2f__8) SymbolTable_0x84b9ed0_369
      REAL(w2f__8) SymbolTable_0x84b9ed0_380
      REAL(w2f__8) SymbolTable_0x84b9ed0_375
      REAL(w2f__8) SymbolTable_0x84b9ed0_376
      REAL(w2f__8) SymbolTable_0x84b9ed0_377
      REAL(w2f__8) SymbolTable_0x84b9ed0_378
      REAL(w2f__8) SymbolTable_0x84b9ed0_379
      REAL(w2f__8) SymbolTable_0x84b9ed0_0
      REAL(w2f__8) SymbolTable_0x84b9ed0_1
      REAL(w2f__8) SymbolTable_0x84b9ed0_2
      REAL(w2f__8) SymbolTable_0x84b9ed0_3
      REAL(w2f__8) SymbolTable_0x84b9ed0_4
      REAL(w2f__8) SymbolTable_0x84b9ed0_5
      REAL(w2f__8) SymbolTable_0x84b9ed0_6
      REAL(w2f__8) SymbolTable_0x84b9ed0_7
      REAL(w2f__8) SymbolTable_0x84b9ed0_8
      REAL(w2f__8) SymbolTable_0x84b9ed0_9
C
C     **** Local Variables and functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) L
C
C     **** statements ****
C
      VERBMODE = 0
      BLENGTH(1) = 5.0D+08
      BLENGTH(2) = 1.0D+08
      __value__(BLENGTH(3)) = __value__(BLENGTH(1))
      CALL sax_a_a(1.0D00, __deriv__(BLENGTH(1)), __deriv__(BLENGTH(3))
     > )
      BHEIGHT(1) = 1.0D+05
      BHEIGHT(3) = 4.0D+05
      __value__(SymbolTable_0x84b9ed0_273) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x84b9ed0_275) = __value__(BHEIGHT(3))
      __value__(BHEIGHT(2)) = (__value__(BHEIGHT(1)) + __value__(
     > BHEIGHT(3)))
      __value__(SymbolTable_0x84b9ed0_0) = 1.0D00
      __value__(SymbolTable_0x84b9ed0_1) = 1.0D00
      __value__(SymbolTable_0x84b9ed0_272) = __value__(
     > SymbolTable_0x84b9ed0_0)
      __value__(SymbolTable_0x84b9ed0_274) = __value__(
     > SymbolTable_0x84b9ed0_1)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_272), __deriv__(
     > SymbolTable_0x84b9ed0_273), __deriv__(BHEIGHT(2)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_274), __deriv__(
     > SymbolTable_0x84b9ed0_275), __deriv__(BHEIGHT(2)))
      __value__(SymbolTable_0x84b9ed0_277) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x84b9ed0_279) = __value__(BHEIGHT(3))
      __value__(SymbolTable_0x84b9ed0_281) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x84b9ed0_2) = (__value__(BHEIGHT(1)) +
     >  __value__(BHEIGHT(3)))
      __value__(SymbolTable_0x84b9ed0_7) = (__value__(BHEIGHT(1)) /
     >  __value__(SymbolTable_0x84b9ed0_2))
      __value__(SymbolTable_0x84b9ed0_3) = (1D00 / __value__(
     > SymbolTable_0x84b9ed0_2))
      __value__(SymbolTable_0x84b9ed0_5) = 1.0D00
      __value__(SymbolTable_0x84b9ed0_6) = 1.0D00
      __value__(SymbolTable_0x84b9ed0_4) = (-(__value__(BHEIGHT(1)) /
     >  SQRT(__value__(BHEIGHT(1)))))
      __value__(DELTA) = __value__(SymbolTable_0x84b9ed0_7)
      __value__(SymbolTable_0x84b9ed0_276) = (__value__(
     > SymbolTable_0x84b9ed0_5) * __value__(SymbolTable_0x84b9ed0_4))
      __value__(SymbolTable_0x84b9ed0_278) = (__value__(
     > SymbolTable_0x84b9ed0_6) * __value__(SymbolTable_0x84b9ed0_4))
      __value__(SymbolTable_0x84b9ed0_280) = __value__(
     > SymbolTable_0x84b9ed0_3)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_276), __deriv__(
     > SymbolTable_0x84b9ed0_277), __deriv__(DELTA))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_278), __deriv__(
     > SymbolTable_0x84b9ed0_279), __deriv__(DELTA))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_280), __deriv__(
     > SymbolTable_0x84b9ed0_281), __deriv__(DELTA))
      BWIDTH = 4.0D+08
      __value__(SymbolTable_0x84b9ed0_283) = __value__(BLENGTH(1))
      __value__(SymbolTable_0x84b9ed0_285) = __value__(BWIDTH)
      __value__(AREA(1)) = (__value__(BLENGTH(1)) * __value__(BWIDTH))
      __value__(SymbolTable_0x84b9ed0_8) = __value__(BWIDTH)
      __value__(SymbolTable_0x84b9ed0_9) = __value__(BLENGTH(1))
      __value__(SymbolTable_0x84b9ed0_282) = __value__(
     > SymbolTable_0x84b9ed0_8)
      __value__(SymbolTable_0x84b9ed0_284) = __value__(
     > SymbolTable_0x84b9ed0_9)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_282), __deriv__(
     > SymbolTable_0x84b9ed0_283), __deriv__(AREA(1)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_284), __deriv__(
     > SymbolTable_0x84b9ed0_285), __deriv__(AREA(1)))
      __value__(SymbolTable_0x84b9ed0_287) = __value__(BLENGTH(2))
      __value__(SymbolTable_0x84b9ed0_289) = __value__(BWIDTH)
      __value__(AREA(2)) = (__value__(BLENGTH(2)) * __value__(BWIDTH))
      __value__(SymbolTable_0x84b9ed0_10) = __value__(BWIDTH)
      __value__(SymbolTable_0x84b9ed0_11) = __value__(BLENGTH(2))
      __value__(SymbolTable_0x84b9ed0_286) = __value__(
     > SymbolTable_0x84b9ed0_10)
      __value__(SymbolTable_0x84b9ed0_288) = __value__(
     > SymbolTable_0x84b9ed0_11)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_286), __deriv__(
     > SymbolTable_0x84b9ed0_287), __deriv__(AREA(2)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_288), __deriv__(
     > SymbolTable_0x84b9ed0_289), __deriv__(AREA(2)))
      __value__(SymbolTable_0x84b9ed0_291) = __value__(BLENGTH(3))
      __value__(SymbolTable_0x84b9ed0_293) = __value__(BWIDTH)
      __value__(AREA(3)) = (__value__(BLENGTH(3)) * __value__(BWIDTH))
      __value__(SymbolTable_0x84b9ed0_12) = __value__(BWIDTH)
      __value__(SymbolTable_0x84b9ed0_13) = __value__(BLENGTH(3))
      __value__(SymbolTable_0x84b9ed0_290) = __value__(
     > SymbolTable_0x84b9ed0_12)
      __value__(SymbolTable_0x84b9ed0_292) = __value__(
     > SymbolTable_0x84b9ed0_13)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_290), __deriv__(
     > SymbolTable_0x84b9ed0_291), __deriv__(AREA(3)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_292), __deriv__(
     > SymbolTable_0x84b9ed0_293), __deriv__(AREA(3)))
      __value__(SymbolTable_0x84b9ed0_295) = __value__(AREA(1))
      __value__(SymbolTable_0x84b9ed0_297) = __value__(BHEIGHT(1))
      __value__(VOL(1)) = (__value__(AREA(1)) * __value__(BHEIGHT(1)))
      __value__(SymbolTable_0x84b9ed0_14) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x84b9ed0_15) = __value__(AREA(1))
      __value__(SymbolTable_0x84b9ed0_294) = __value__(
     > SymbolTable_0x84b9ed0_14)
      __value__(SymbolTable_0x84b9ed0_296) = __value__(
     > SymbolTable_0x84b9ed0_15)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_294), __deriv__(
     > SymbolTable_0x84b9ed0_295), __deriv__(VOL(1)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_296), __deriv__(
     > SymbolTable_0x84b9ed0_297), __deriv__(VOL(1)))
      __value__(SymbolTable_0x84b9ed0_299) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x84b9ed0_301) = __value__(BHEIGHT(3))
      __value__(SymbolTable_0x84b9ed0_303) = __value__(AREA(2))
      __value__(SymbolTable_0x84b9ed0_16) = (__value__(BHEIGHT(1)) +
     >  __value__(BHEIGHT(3)))
      __value__(SymbolTable_0x84b9ed0_21) = (__value__(AREA(2)) *
     >  __value__(SymbolTable_0x84b9ed0_16))
      __value__(SymbolTable_0x84b9ed0_17) = __value__(
     > SymbolTable_0x84b9ed0_16)
      __value__(SymbolTable_0x84b9ed0_19) = 1.0D00
      __value__(SymbolTable_0x84b9ed0_20) = 1.0D00
      __value__(SymbolTable_0x84b9ed0_18) = __value__(AREA(2))
      __value__(VOL(2)) = __value__(SymbolTable_0x84b9ed0_21)
      __value__(SymbolTable_0x84b9ed0_298) = (__value__(
     > SymbolTable_0x84b9ed0_19) * __value__(SymbolTable_0x84b9ed0_18))
      __value__(SymbolTable_0x84b9ed0_300) = (__value__(
     > SymbolTable_0x84b9ed0_20) * __value__(SymbolTable_0x84b9ed0_18))
      __value__(SymbolTable_0x84b9ed0_302) = __value__(
     > SymbolTable_0x84b9ed0_17)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_298), __deriv__(
     > SymbolTable_0x84b9ed0_299), __deriv__(VOL(2)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_300), __deriv__(
     > SymbolTable_0x84b9ed0_301), __deriv__(VOL(2)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_302), __deriv__(
     > SymbolTable_0x84b9ed0_303), __deriv__(VOL(2)))
      __value__(SymbolTable_0x84b9ed0_305) = __value__(AREA(3))
      __value__(SymbolTable_0x84b9ed0_307) = __value__(BHEIGHT(3))
      __value__(VOL(3)) = (__value__(AREA(3)) * __value__(BHEIGHT(3)))
      __value__(SymbolTable_0x84b9ed0_22) = __value__(BHEIGHT(3))
      __value__(SymbolTable_0x84b9ed0_23) = __value__(AREA(3))
      __value__(SymbolTable_0x84b9ed0_304) = __value__(
     > SymbolTable_0x84b9ed0_22)
      __value__(SymbolTable_0x84b9ed0_306) = __value__(
     > SymbolTable_0x84b9ed0_23)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_304), __deriv__(
     > SymbolTable_0x84b9ed0_305), __deriv__(VOL(3)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_306), __deriv__(
     > SymbolTable_0x84b9ed0_307), __deriv__(VOL(3)))
      ROBERT_FILTER_COEFF = 2.5D-01
      HUNDRED = 1.0D+02
      THOUSAND = 1.0D+03
      DAY = 8.64D+04
      __value__(SymbolTable_0x84b9ed0_309) = __value__(DAY)
      __value__(YEAR) = (__value__(DAY) * 3.65D+02)
      __value__(SymbolTable_0x84b9ed0_24) = 3.65D+02
      __value__(SymbolTable_0x84b9ed0_308) = __value__(
     > SymbolTable_0x84b9ed0_24)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_308), __deriv__(
     > SymbolTable_0x84b9ed0_309), __deriv__(YEAR))
      SV = 1.0D+12
      __value__(SymbolTable_0x84b9ed0_311) = __value__(SV)
      __value__(SymbolTable_0x84b9ed0_26) = (__value__(SV) * 1.6D+01)
      __value__(SymbolTable_0x84b9ed0_31) = (__value__(
     > SymbolTable_0x84b9ed0_26) / 4.00000000000000019169D-04)
      __value__(SymbolTable_0x84b9ed0_29) = 1.6D+01
      __value__(SymbolTable_0x84b9ed0_27) = 2.5D+03
      __value__(U0) = __value__(SymbolTable_0x84b9ed0_31)
      __value__(SymbolTable_0x84b9ed0_310) = (__value__(
     > SymbolTable_0x84b9ed0_29) * __value__(SymbolTable_0x84b9ed0_27))
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_310), __deriv__(
     > SymbolTable_0x84b9ed0_311), __deriv__(U0))
      ALPHA = 1.6679999999999998864D-04
      BETA = 7.81000000000000010186D-04
      DAYS_PER_50M_MIXED_LAYER = 5.0D+01
      __value__(SymbolTable_0x84b9ed0_313) = __value__(DAY)
      __value__(SymbolTable_0x84b9ed0_32) = (__value__(DAY) * 3.0D+02)
      __value__(SymbolTable_0x84b9ed0_37) = (1D00 / __value__(
     > SymbolTable_0x84b9ed0_32))
      __value__(SymbolTable_0x84b9ed0_35) = 3.0D+02
      __value__(SymbolTable_0x84b9ed0_34) = (-1.0D00)
      __value__(GAMMA_T) = __value__(SymbolTable_0x84b9ed0_37)
      __value__(SymbolTable_0x84b9ed0_312) = (__value__(
     > SymbolTable_0x84b9ed0_35) * __value__(SymbolTable_0x84b9ed0_34))
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_312), __deriv__(
     > SymbolTable_0x84b9ed0_313), __deriv__(GAMMA_T))
      __value__(SymbolTable_0x84b9ed0_317) = __value__(DAY)
      __value__(SymbolTable_0x84b9ed0_319) = __value__(
     > DAYS_PER_50M_MIXED_LAYER)
      __value__(SymbolTable_0x84b9ed0_321) = __value__(BHEIGHT(1))
      __value__(SymbolTable_0x84b9ed0_41) = (__value__(BHEIGHT(1)) /
     >  5.0D+03)
      __value__(SymbolTable_0x84b9ed0_42) = (__value__(DAY) * __value__
     > (DAYS_PER_50M_MIXED_LAYER))
      __value__(SymbolTable_0x84b9ed0_38) = (__value__(
     > SymbolTable_0x84b9ed0_41) * __value__(SymbolTable_0x84b9ed0_42))
      __value__(SymbolTable_0x84b9ed0_49) = (0.0D00 / __value__(
     > SymbolTable_0x84b9ed0_38))
      __value__(SymbolTable_0x84b9ed0_45) = 2.00000000000000009584D-04
      __value__(SymbolTable_0x84b9ed0_43) = __value__(
     > SymbolTable_0x84b9ed0_42)
      __value__(SymbolTable_0x84b9ed0_47) = __value__(
     > DAYS_PER_50M_MIXED_LAYER)
      __value__(SymbolTable_0x84b9ed0_48) = __value__(DAY)
      __value__(SymbolTable_0x84b9ed0_44) = __value__(
     > SymbolTable_0x84b9ed0_41)
      __value__(SymbolTable_0x84b9ed0_40) = (0.0D00 / -0.0D00)
      __value__(GAMMA_S) = __value__(SymbolTable_0x84b9ed0_49)
      __value__(SymbolTable_0x84b9ed0_314) = (__value__(
     > SymbolTable_0x84b9ed0_43) * __value__(SymbolTable_0x84b9ed0_40))
      __value__(SymbolTable_0x84b9ed0_315) = (__value__(
     > SymbolTable_0x84b9ed0_44) * __value__(SymbolTable_0x84b9ed0_40))
      __value__(SymbolTable_0x84b9ed0_316) = (__value__(
     > SymbolTable_0x84b9ed0_47) * __value__(SymbolTable_0x84b9ed0_315)
     > )
      __value__(SymbolTable_0x84b9ed0_318) = (__value__(
     > SymbolTable_0x84b9ed0_48) * __value__(SymbolTable_0x84b9ed0_315)
     > )
      __value__(SymbolTable_0x84b9ed0_320) = (__value__(
     > SymbolTable_0x84b9ed0_45) * __value__(SymbolTable_0x84b9ed0_314)
     > )
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_316), __deriv__(
     > SymbolTable_0x84b9ed0_317), __deriv__(GAMMA_S))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_318), __deriv__(
     > SymbolTable_0x84b9ed0_319), __deriv__(GAMMA_S))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_320), __deriv__(
     > SymbolTable_0x84b9ed0_321), __deriv__(GAMMA_S))
      EPSILON_IC = (-1.00000000000000004792D-04)
      __value__(SymbolTable_0x84b9ed0_323) = __value__(DAY)
      __value__(NOISE_CORRELATION_TIME) = (__value__(DAY) * 1.5D+01)
      __value__(SymbolTable_0x84b9ed0_50) = 1.5D+01
      __value__(SymbolTable_0x84b9ed0_322) = __value__(
     > SymbolTable_0x84b9ed0_50)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_322), __deriv__(
     > SymbolTable_0x84b9ed0_323), __deriv__(NOISE_CORRELATION_TIME))
      __value__(SymbolTable_0x84b9ed0_325) = __value__(DAY)
      __value__(DELTA_T) = (__value__(DAY) * 5.0D00)
      __value__(SymbolTable_0x84b9ed0_52) = 5.0D00
      __value__(SymbolTable_0x84b9ed0_324) = __value__(
     > SymbolTable_0x84b9ed0_52)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_324), __deriv__(
     > SymbolTable_0x84b9ed0_325), __deriv__(DELTA_T))
      WRITE(*, *) 'delta_t = ', __value__(DELTA_T)
      __value__(SymbolTable_0x84b9ed0_327) = __value__(YEAR)
      __value__(INTEGRATION_TIME) = (__value__(YEAR) * 5.0D+01)
      __value__(SymbolTable_0x84b9ed0_54) = 5.0D+01
      __value__(SymbolTable_0x84b9ed0_326) = __value__(
     > SymbolTable_0x84b9ed0_54)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_326), __deriv__(
     > SymbolTable_0x84b9ed0_327), __deriv__(INTEGRATION_TIME))
      WRITE(*, *) 'integration_time = ', __value__(INTEGRATION_TIME)
      N_MAX = JIDINT((INTEGRATION_TIME / DELTA_T))
      WRITE(*, *) 'n_max = ', N_MAX
      FDEPS = 9.99999999999999954748D-07
      __value__(SymbolTable_0x84b9ed0_329) = __value__(THOUSAND)
      __value__(Y(1)) = (__value__(THOUSAND) /
     >  3.2680000000000000715D-02)
      __value__(SymbolTable_0x84b9ed0_56) = 3.05997552019583842764D+01
      __value__(SymbolTable_0x84b9ed0_328) = __value__(
     > SymbolTable_0x84b9ed0_56)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_328), __deriv__(
     > SymbolTable_0x84b9ed0_329), __deriv__(Y(1)))
      __value__(SymbolTable_0x84b9ed0_331) = __value__(THOUSAND)
      __value__(Y(2)) = (__value__(THOUSAND) /
     >  7.9399999999999991418D-03)
      __value__(SymbolTable_0x84b9ed0_58) = 1.25944584382871553885D+02
      __value__(SymbolTable_0x84b9ed0_330) = __value__(
     > SymbolTable_0x84b9ed0_58)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_330), __deriv__(
     > SymbolTable_0x84b9ed0_331), __deriv__(Y(2)))
      __value__(SymbolTable_0x84b9ed0_333) = __value__(THOUSAND)
      __value__(Y(3)) = (__value__(THOUSAND) /
     >  1.39999999999999998578D-03)
      __value__(SymbolTable_0x84b9ed0_60) = 7.14285714285714334437D+02
      __value__(SymbolTable_0x84b9ed0_332) = __value__(
     > SymbolTable_0x84b9ed0_60)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_332), __deriv__(
     > SymbolTable_0x84b9ed0_333), __deriv__(Y(3)))
      __value__(SymbolTable_0x84b9ed0_335) = __value__(THOUSAND)
      __value__(Y(4)) = (__value__(THOUSAND) /
     >  1.41699999999999992628D-01)
      __value__(SymbolTable_0x84b9ed0_62) = 7.0571630204657731511D00
      __value__(SymbolTable_0x84b9ed0_334) = __value__(
     > SymbolTable_0x84b9ed0_62)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_334), __deriv__(
     > SymbolTable_0x84b9ed0_335), __deriv__(Y(4)))
      __value__(SymbolTable_0x84b9ed0_337) = __value__(THOUSAND)
      __value__(Y(5)) = (__value__(THOUSAND) /
     >  1.28599999999999992095D-01)
      __value__(SymbolTable_0x84b9ed0_64) = 7.77604976671850778303D00
      __value__(SymbolTable_0x84b9ed0_336) = __value__(
     > SymbolTable_0x84b9ed0_64)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_336), __deriv__(
     > SymbolTable_0x84b9ed0_337), __deriv__(Y(5)))
      __value__(SymbolTable_0x84b9ed0_339) = __value__(THOUSAND)
      __value__(Y(6)) = (__value__(THOUSAND) /
     >  8.7800000000000003042D-02)
      __value__(SymbolTable_0x84b9ed0_66) = 1.1389521640091116339D+01
      __value__(SymbolTable_0x84b9ed0_338) = __value__(
     > SymbolTable_0x84b9ed0_66)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_338), __deriv__(
     > SymbolTable_0x84b9ed0_339), __deriv__(Y(6)))
      __value__(SymbolTable_0x84b9ed0_341) = __value__(ALPHA)
      __value__(SymbolTable_0x84b9ed0_343) = __value__(DELTA)
      __value__(R(1)) = (__value__(ALPHA) * __value__(DELTA))
      __value__(SymbolTable_0x84b9ed0_68) = __value__(DELTA)
      __value__(SymbolTable_0x84b9ed0_69) = __value__(ALPHA)
      __value__(SymbolTable_0x84b9ed0_340) = __value__(
     > SymbolTable_0x84b9ed0_68)
      __value__(SymbolTable_0x84b9ed0_342) = __value__(
     > SymbolTable_0x84b9ed0_69)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_340), __deriv__(
     > SymbolTable_0x84b9ed0_341), __deriv__(R(1)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_342), __deriv__(
     > SymbolTable_0x84b9ed0_343), __deriv__(R(1)))
      __value__(SymbolTable_0x84b9ed0_345) = __value__(ALPHA)
      __value__(R(2)) = (- __value__(ALPHA))
      __value__(SymbolTable_0x84b9ed0_70) = 4.294967295D+09
      __value__(SymbolTable_0x84b9ed0_344) = __value__(
     > SymbolTable_0x84b9ed0_70)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_344), __deriv__(
     > SymbolTable_0x84b9ed0_345), __deriv__(R(2)))
      __value__(SymbolTable_0x84b9ed0_347) = __value__(DELTA)
      __value__(SymbolTable_0x84b9ed0_349) = __value__(ALPHA)
      __value__(SymbolTable_0x84b9ed0_71) = (1.0D00 - __value__(DELTA))
      __value__(SymbolTable_0x84b9ed0_76) = (__value__(ALPHA) *
     >  __value__(SymbolTable_0x84b9ed0_71))
      __value__(SymbolTable_0x84b9ed0_72) = __value__(
     > SymbolTable_0x84b9ed0_71)
      __value__(SymbolTable_0x84b9ed0_75) = 4.294967295D+09
      __value__(SymbolTable_0x84b9ed0_73) = __value__(ALPHA)
      __value__(R(3)) = __value__(SymbolTable_0x84b9ed0_76)
      __value__(SymbolTable_0x84b9ed0_346) = (__value__(
     > SymbolTable_0x84b9ed0_75) * __value__(SymbolTable_0x84b9ed0_73))
      __value__(SymbolTable_0x84b9ed0_348) = __value__(
     > SymbolTable_0x84b9ed0_72)
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_346), __deriv__(
     > SymbolTable_0x84b9ed0_347), __deriv__(R(3)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_348), __deriv__(
     > SymbolTable_0x84b9ed0_349), __deriv__(R(3)))
      __value__(SymbolTable_0x84b9ed0_351) = __value__(BETA)
      __value__(SymbolTable_0x84b9ed0_353) = __value__(DELTA)
      __value__(R(4)) = (-(__value__(BETA) * __value__(DELTA)))
      __value__(SymbolTable_0x84b9ed0_78) = __value__(DELTA)
      __value__(SymbolTable_0x84b9ed0_79) = __value__(BETA)
      __value__(SymbolTable_0x84b9ed0_77) = 4.294967295D+09
      __value__(SymbolTable_0x84b9ed0_350) = (__value__(
     > SymbolTable_0x84b9ed0_78) * __value__(SymbolTable_0x84b9ed0_77))
      __value__(SymbolTable_0x84b9ed0_352) = (__value__(
     > SymbolTable_0x84b9ed0_79) * __value__(SymbolTable_0x84b9ed0_77))
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_350), __deriv__(
     > SymbolTable_0x84b9ed0_351), __deriv__(R(4)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_352), __deriv__(
     > SymbolTable_0x84b9ed0_353), __deriv__(R(4)))
      __value__(R(5)) = __value__(BETA)
      CALL sax_a_a(1.0D00, __deriv__(BETA), __deriv__(R(5)))
      __value__(SymbolTable_0x84b9ed0_356) = __value__(BETA)
      __value__(SymbolTable_0x84b9ed0_358) = __value__(DELTA)
      __value__(SymbolTable_0x84b9ed0_81) = (1.0D00 - __value__(DELTA))
      __value__(SymbolTable_0x84b9ed0_86) = (-(__value__(BETA) *
     >  __value__(SymbolTable_0x84b9ed0_81)))
      __value__(SymbolTable_0x84b9ed0_82) = __value__(
     > SymbolTable_0x84b9ed0_81)
      __value__(SymbolTable_0x84b9ed0_85) = 4.294967295D+09
      __value__(SymbolTable_0x84b9ed0_83) = __value__(BETA)
      __value__(SymbolTable_0x84b9ed0_80) = 4.294967295D+09
      __value__(R(6)) = __value__(SymbolTable_0x84b9ed0_86)
      __value__(SymbolTable_0x84b9ed0_354) = (__value__(
     > SymbolTable_0x84b9ed0_85) * __value__(SymbolTable_0x84b9ed0_83))
      __value__(SymbolTable_0x84b9ed0_355) = (__value__(
     > SymbolTable_0x84b9ed0_82) * __value__(SymbolTable_0x84b9ed0_80))
      __value__(SymbolTable_0x84b9ed0_357) = (__value__(
     > SymbolTable_0x84b9ed0_354) * __value__(SymbolTable_0x84b9ed0_80)
     > )
      CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_355), __deriv__(
     > SymbolTable_0x84b9ed0_356), __deriv__(R(6)))
      CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_357), __deriv__(
     > SymbolTable_0x84b9ed0_358), __deriv__(R(6)))
      DO L = 1, 6, 1
        __value__(SymbolTable_0x84b9ed0_360) = __value__(R(L))
        __value__(SymbolTable_0x84b9ed0_362) = __value__(U0)
        __value__(SymbolTable_0x84b9ed0_364) = __value__(SV)
        __value__(SymbolTable_0x84b9ed0_87) = (__value__(R(L)) *
     >  __value__(U0))
        __value__(SymbolTable_0x84b9ed0_92) = (__value__(
     > SymbolTable_0x84b9ed0_87) / __value__(SV))
        __value__(SymbolTable_0x84b9ed0_90) = __value__(U0)
        __value__(SymbolTable_0x84b9ed0_91) = __value__(R(L))
        __value__(SymbolTable_0x84b9ed0_88) = (1D00 / __value__(SV))
        __value__(SymbolTable_0x84b9ed0_89) = (-(__value__(
     > SymbolTable_0x84b9ed0_87) / SQRT(__value__(
     > SymbolTable_0x84b9ed0_87))))
        __value__(R(L)) = __value__(SymbolTable_0x84b9ed0_92)
        __value__(SymbolTable_0x84b9ed0_359) = (__value__(
     > SymbolTable_0x84b9ed0_90) * __value__(SymbolTable_0x84b9ed0_88))
        __value__(SymbolTable_0x84b9ed0_361) = (__value__(
     > SymbolTable_0x84b9ed0_91) * __value__(SymbolTable_0x84b9ed0_88))
        __value__(SymbolTable_0x84b9ed0_363) = __value__(
     > SymbolTable_0x84b9ed0_89)
        CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_359), __deriv__(
     > SymbolTable_0x84b9ed0_360), __deriv__(R(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_361), __deriv__(
     > SymbolTable_0x84b9ed0_362), __deriv__(R(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_363), __deriv__(
     > SymbolTable_0x84b9ed0_364), __deriv__(R(L)))
      END DO
      DO L = 1, 6, 1
        IF(L .LE. 3) THEN
          PROJ_T(L) = 1.0D00
          PROJ_S(L) = 0.0D00
        ELSE
          PROJ_T(L) = 0.0D00
          PROJ_S(L) = 1.0D00
        ENDIF
      END DO
      DO L = 1, 6, 1
        __value__(SymbolTable_0x84b9ed0_366) = __value__(PROJ_T(L))
        __value__(SymbolTable_0x84b9ed0_368) = __value__(R(L))
        __value__(R_T(L)) = (__value__(PROJ_T(L)) * __value__(R(L)))
        __value__(SymbolTable_0x84b9ed0_93) = __value__(R(L))
        __value__(SymbolTable_0x84b9ed0_94) = __value__(PROJ_T(L))
        __value__(SymbolTable_0x84b9ed0_365) = __value__(
     > SymbolTable_0x84b9ed0_93)
        __value__(SymbolTable_0x84b9ed0_367) = __value__(
     > SymbolTable_0x84b9ed0_94)
        CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_365), __deriv__(
     > SymbolTable_0x84b9ed0_366), __deriv__(R_T(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_367), __deriv__(
     > SymbolTable_0x84b9ed0_368), __deriv__(R_T(L)))
        __value__(SymbolTable_0x84b9ed0_370) = __value__(PROJ_S(L))
        __value__(SymbolTable_0x84b9ed0_372) = __value__(R(L))
        __value__(R_S(L)) = (__value__(PROJ_S(L)) * __value__(R(L)))
        __value__(SymbolTable_0x84b9ed0_95) = __value__(R(L))
        __value__(SymbolTable_0x84b9ed0_96) = __value__(PROJ_S(L))
        __value__(SymbolTable_0x84b9ed0_369) = __value__(
     > SymbolTable_0x84b9ed0_95)
        __value__(SymbolTable_0x84b9ed0_371) = __value__(
     > SymbolTable_0x84b9ed0_96)
        CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_369), __deriv__(
     > SymbolTable_0x84b9ed0_370), __deriv__(R_S(L)))
        CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_371), __deriv__(
     > SymbolTable_0x84b9ed0_372), __deriv__(R_S(L)))
      END DO
      R1(1) = 1.0D00
      R1(2) = (-1.0D00)
      R1(3) = 0.0D00
      R1(4) = 0.0D00
      R1(5) = 0.0D00
      R1(6) = 0.0D00
      DO J = 1, 6, 1
        DO I = 1, 6, 1
          __value__(SymbolTable_0x84b9ed0_374) = __value__(R(I))
          __value__(SymbolTable_0x84b9ed0_376) = __value__(R(J))
          __value__(X(I, J)) = (__value__(R(I)) * __value__(R(J)))
          __value__(SymbolTable_0x84b9ed0_97) = __value__(R(J))
          __value__(SymbolTable_0x84b9ed0_98) = __value__(R(I))
          __value__(SymbolTable_0x84b9ed0_373) = __value__(
     > SymbolTable_0x84b9ed0_97)
          __value__(SymbolTable_0x84b9ed0_375) = __value__(
     > SymbolTable_0x84b9ed0_98)
          CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_373), __deriv__(
     > SymbolTable_0x84b9ed0_374), __deriv__(X(I, J)))
          CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_375),
     >  __deriv__(SymbolTable_0x84b9ed0_376), __deriv__(X(I, J)))
        END DO
      END DO
      EPSILON_REGULARIZE = 1.00000000000000002092D-08
      DO J = 1, 6, 1
        DO I = 1, 6, 1
          __value__(SymbolTable_0x84b9ed0_378) = __value__(X(I, J))
          __value__(SymbolTable_0x84b9ed0_380) = __value__(
     > EPSILON_REGULARIZE)
          __value__(X(I, J)) = (__value__(X(I, J)) + __value__(
     > EPSILON_REGULARIZE))
          __value__(SymbolTable_0x84b9ed0_99) = 1.0D00
          __value__(SymbolTable_0x84b9ed0_100) = 1.0D00
          __value__(SymbolTable_0x84b9ed0_377) = __value__(
     > SymbolTable_0x84b9ed0_99)
          __value__(SymbolTable_0x84b9ed0_379) = __value__(
     > SymbolTable_0x84b9ed0_100)
          CALL sax_a_a(__value__(SymbolTable_0x84b9ed0_377), __deriv__(
     > SymbolTable_0x84b9ed0_378), __deriv__(X(I, J)))
          CALL saxpy_a_a(__value__(SymbolTable_0x84b9ed0_379),
     >  __deriv__(SymbolTable_0x84b9ed0_380), __deriv__(X(I, J)))
        END DO
      END DO
      RETURN
      END SUBROUTINE
W2F1
    $w2f1_pp = <<'W2F1PP';
      use w2f__types
      use active_module
      IMPLICIT NONE
C
C     **** Global Variables ****
C
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
      type(active) :: SymbolTable_0x84b9ed0_10
      type(active) :: SymbolTable_0x84b9ed0_11
      type(active) :: SymbolTable_0x84b9ed0_12
      type(active) :: SymbolTable_0x84b9ed0_13
      type(active) :: SymbolTable_0x84b9ed0_14
      type(active) :: SymbolTable_0x84b9ed0_15
      type(active) :: SymbolTable_0x84b9ed0_20
      type(active) :: SymbolTable_0x84b9ed0_16
      type(active) :: SymbolTable_0x84b9ed0_21
      type(active) :: SymbolTable_0x84b9ed0_17
      type(active) :: SymbolTable_0x84b9ed0_22
      type(active) :: SymbolTable_0x84b9ed0_18
      type(active) :: SymbolTable_0x84b9ed0_23
      type(active) :: SymbolTable_0x84b9ed0_19
      type(active) :: SymbolTable_0x84b9ed0_24
      type(active) :: SymbolTable_0x84b9ed0_26
      type(active) :: SymbolTable_0x84b9ed0_31
      type(active) :: SymbolTable_0x84b9ed0_27
      type(active) :: SymbolTable_0x84b9ed0_32
      type(active) :: SymbolTable_0x84b9ed0_29
      type(active) :: SymbolTable_0x84b9ed0_34
      type(active) :: SymbolTable_0x84b9ed0_35
      type(active) :: SymbolTable_0x84b9ed0_40
      type(active) :: SymbolTable_0x84b9ed0_41
      type(active) :: SymbolTable_0x84b9ed0_37
      type(active) :: SymbolTable_0x84b9ed0_42
      type(active) :: SymbolTable_0x84b9ed0_38
      type(active) :: SymbolTable_0x84b9ed0_43
      type(active) :: SymbolTable_0x84b9ed0_44
      type(active) :: SymbolTable_0x84b9ed0_45
      type(active) :: SymbolTable_0x84b9ed0_50
      type(active) :: SymbolTable_0x84b9ed0_47
      type(active) :: SymbolTable_0x84b9ed0_52
      type(active) :: SymbolTable_0x84b9ed0_48
      type(active) :: SymbolTable_0x84b9ed0_49
      type(active) :: SymbolTable_0x84b9ed0_54
      type(active) :: SymbolTable_0x84b9ed0_60
      type(active) :: SymbolTable_0x84b9ed0_56
      type(active) :: SymbolTable_0x84b9ed0_62
      type(active) :: SymbolTable_0x84b9ed0_58
      type(active) :: SymbolTable_0x84b9ed0_64
      type(active) :: SymbolTable_0x84b9ed0_70
      type(active) :: SymbolTable_0x84b9ed0_66
      type(active) :: SymbolTable_0x84b9ed0_71
      type(active) :: SymbolTable_0x84b9ed0_72
      type(active) :: SymbolTable_0x84b9ed0_68
      type(active) :: SymbolTable_0x84b9ed0_73
      type(active) :: SymbolTable_0x84b9ed0_69
      type(active) :: SymbolTable_0x84b9ed0_75
      type(active) :: SymbolTable_0x84b9ed0_80
      type(active) :: SymbolTable_0x84b9ed0_76
      type(active) :: SymbolTable_0x84b9ed0_81
      type(active) :: SymbolTable_0x84b9ed0_77
      type(active) :: SymbolTable_0x84b9ed0_82
      type(active) :: SymbolTable_0x84b9ed0_78
      type(active) :: SymbolTable_0x84b9ed0_83
      type(active) :: SymbolTable_0x84b9ed0_79
      type(active) :: SymbolTable_0x84b9ed0_85
      type(active) :: SymbolTable_0x84b9ed0_90
      type(active) :: SymbolTable_0x84b9ed0_86
      type(active) :: SymbolTable_0x84b9ed0_91
      type(active) :: SymbolTable_0x84b9ed0_87
      type(active) :: SymbolTable_0x84b9ed0_92
      type(active) :: SymbolTable_0x84b9ed0_88
      type(active) :: SymbolTable_0x84b9ed0_93
      type(active) :: SymbolTable_0x84b9ed0_89
      type(active) :: SymbolTable_0x84b9ed0_94
      type(active) :: SymbolTable_0x84b9ed0_95
      type(active) :: SymbolTable_0x84b9ed0_96
      type(active) :: SymbolTable_0x84b9ed0_97
      type(active) :: SymbolTable_0x84b9ed0_98
      type(active) :: SymbolTable_0x84b9ed0_99
      type(active) :: SymbolTable_0x84b9ed0_100
      type(active) :: SymbolTable_0x84b9ed0_300
      type(active) :: SymbolTable_0x84b9ed0_301
      type(active) :: SymbolTable_0x84b9ed0_302
      type(active) :: SymbolTable_0x84b9ed0_303
      type(active) :: SymbolTable_0x84b9ed0_304
      type(active) :: SymbolTable_0x84b9ed0_310
      type(active) :: SymbolTable_0x84b9ed0_305
      type(active) :: SymbolTable_0x84b9ed0_311
      type(active) :: SymbolTable_0x84b9ed0_306
      type(active) :: SymbolTable_0x84b9ed0_312
      type(active) :: SymbolTable_0x84b9ed0_307
      type(active) :: SymbolTable_0x84b9ed0_313
      type(active) :: SymbolTable_0x84b9ed0_308
      type(active) :: SymbolTable_0x84b9ed0_314
      type(active) :: SymbolTable_0x84b9ed0_309
      type(active) :: SymbolTable_0x84b9ed0_320
      type(active) :: SymbolTable_0x84b9ed0_315
      type(active) :: SymbolTable_0x84b9ed0_321
      type(active) :: SymbolTable_0x84b9ed0_316
      type(active) :: SymbolTable_0x84b9ed0_322
      type(active) :: SymbolTable_0x84b9ed0_317
      type(active) :: SymbolTable_0x84b9ed0_272
      type(active) :: SymbolTable_0x84b9ed0_323
      type(active) :: SymbolTable_0x84b9ed0_318
      type(active) :: SymbolTable_0x84b9ed0_273
      type(active) :: SymbolTable_0x84b9ed0_324
      type(active) :: SymbolTable_0x84b9ed0_319
      type(active) :: SymbolTable_0x84b9ed0_274
      type(active) :: SymbolTable_0x84b9ed0_330
      type(active) :: SymbolTable_0x84b9ed0_325
      type(active) :: SymbolTable_0x84b9ed0_275
      type(active) :: SymbolTable_0x84b9ed0_280
      type(active) :: SymbolTable_0x84b9ed0_331
      type(active) :: SymbolTable_0x84b9ed0_326
      type(active) :: SymbolTable_0x84b9ed0_276
      type(active) :: SymbolTable_0x84b9ed0_281
      type(active) :: SymbolTable_0x84b9ed0_332
      type(active) :: SymbolTable_0x84b9ed0_327
      type(active) :: SymbolTable_0x84b9ed0_277
      type(active) :: SymbolTable_0x84b9ed0_282
      type(active) :: SymbolTable_0x84b9ed0_333
      type(active) :: SymbolTable_0x84b9ed0_328
      type(active) :: SymbolTable_0x84b9ed0_278
      type(active) :: SymbolTable_0x84b9ed0_283
      type(active) :: SymbolTable_0x84b9ed0_334
      type(active) :: SymbolTable_0x84b9ed0_329
      type(active) :: SymbolTable_0x84b9ed0_279
      type(active) :: SymbolTable_0x84b9ed0_284
      type(active) :: SymbolTable_0x84b9ed0_340
      type(active) :: SymbolTable_0x84b9ed0_335
      type(active) :: SymbolTable_0x84b9ed0_285
      type(active) :: SymbolTable_0x84b9ed0_290
      type(active) :: SymbolTable_0x84b9ed0_341
      type(active) :: SymbolTable_0x84b9ed0_336
      type(active) :: SymbolTable_0x84b9ed0_286
      type(active) :: SymbolTable_0x84b9ed0_291
      type(active) :: SymbolTable_0x84b9ed0_342
      type(active) :: SymbolTable_0x84b9ed0_337
      type(active) :: SymbolTable_0x84b9ed0_287
      type(active) :: SymbolTable_0x84b9ed0_292
      type(active) :: SymbolTable_0x84b9ed0_343
      type(active) :: SymbolTable_0x84b9ed0_338
      type(active) :: SymbolTable_0x84b9ed0_288
      type(active) :: SymbolTable_0x84b9ed0_293
      type(active) :: SymbolTable_0x84b9ed0_344
      type(active) :: SymbolTable_0x84b9ed0_339
      type(active) :: SymbolTable_0x84b9ed0_289
      type(active) :: SymbolTable_0x84b9ed0_294
      type(active) :: SymbolTable_0x84b9ed0_350
      type(active) :: SymbolTable_0x84b9ed0_345
      type(active) :: SymbolTable_0x84b9ed0_295
      type(active) :: SymbolTable_0x84b9ed0_351
      type(active) :: SymbolTable_0x84b9ed0_346
      type(active) :: SymbolTable_0x84b9ed0_296
      type(active) :: SymbolTable_0x84b9ed0_352
      type(active) :: SymbolTable_0x84b9ed0_347
      type(active) :: SymbolTable_0x84b9ed0_297
      type(active) :: SymbolTable_0x84b9ed0_353
      type(active) :: SymbolTable_0x84b9ed0_348
      type(active) :: SymbolTable_0x84b9ed0_298
      type(active) :: SymbolTable_0x84b9ed0_354
      type(active) :: SymbolTable_0x84b9ed0_349
      type(active) :: SymbolTable_0x84b9ed0_299
      type(active) :: SymbolTable_0x84b9ed0_360
      type(active) :: SymbolTable_0x84b9ed0_355
      type(active) :: SymbolTable_0x84b9ed0_361
      type(active) :: SymbolTable_0x84b9ed0_356
      type(active) :: SymbolTable_0x84b9ed0_362
      type(active) :: SymbolTable_0x84b9ed0_357
      type(active) :: SymbolTable_0x84b9ed0_363
      type(active) :: SymbolTable_0x84b9ed0_358
      type(active) :: SymbolTable_0x84b9ed0_364
      type(active) :: SymbolTable_0x84b9ed0_359
      type(active) :: SymbolTable_0x84b9ed0_370
      type(active) :: SymbolTable_0x84b9ed0_365
      type(active) :: SymbolTable_0x84b9ed0_371
      type(active) :: SymbolTable_0x84b9ed0_366
      type(active) :: SymbolTable_0x84b9ed0_372
      type(active) :: SymbolTable_0x84b9ed0_367
      type(active) :: SymbolTable_0x84b9ed0_373
      type(active) :: SymbolTable_0x84b9ed0_368
      type(active) :: SymbolTable_0x84b9ed0_374
      type(active) :: SymbolTable_0x84b9ed0_369
      type(active) :: SymbolTable_0x84b9ed0_380
      type(active) :: SymbolTable_0x84b9ed0_375
      type(active) :: SymbolTable_0x84b9ed0_376
      type(active) :: SymbolTable_0x84b9ed0_377
      type(active) :: SymbolTable_0x84b9ed0_378
      type(active) :: SymbolTable_0x84b9ed0_379
      type(active) :: SymbolTable_0x84b9ed0_0
      type(active) :: SymbolTable_0x84b9ed0_1
      type(active) :: SymbolTable_0x84b9ed0_2
      type(active) :: SymbolTable_0x84b9ed0_3
      type(active) :: SymbolTable_0x84b9ed0_4
      type(active) :: SymbolTable_0x84b9ed0_5
      type(active) :: SymbolTable_0x84b9ed0_6
      type(active) :: SymbolTable_0x84b9ed0_7
      type(active) :: SymbolTable_0x84b9ed0_8
      type(active) :: SymbolTable_0x84b9ed0_9
C
C     **** Local Variables and functions ****
C
      INTEGER(w2f__i4) I
      INTEGER(w2f__i4) J
      INTEGER(w2f__i4) L
C
C     **** statements ****
C
      VERBMODE = 0
      BLENGTH(1) = 5.0D+08
      BLENGTH(2) = 1.0D+08
      BLENGTH(3)%v = BLENGTH(1)%v
      CALL sax_a_a(1.0D00,BLENGTH(1),BLENGTH(3))
      BHEIGHT(1) = 1.0D+05
      BHEIGHT(3) = 4.0D+05
      SymbolTable_0x84b9ed0_273%v = BHEIGHT(1)%v
      SymbolTable_0x84b9ed0_275%v = BHEIGHT(3)%v
      BHEIGHT(2)%v = (BHEIGHT(1)%v+BHEIGHT(3)%v)
      SymbolTable_0x84b9ed0_0%v = 1.0D00
      SymbolTable_0x84b9ed0_1%v = 1.0D00
      SymbolTable_0x84b9ed0_272%v = SymbolTable_0x84b9ed0_0%v
      SymbolTable_0x84b9ed0_274%v = SymbolTable_0x84b9ed0_1%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_272%v,SymbolTable_0x84b9ed0_273
     +,BHEIGHT(2))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_274%v,SymbolTable_0x84b9ed0_2
     +75,BHEIGHT(2))
      SymbolTable_0x84b9ed0_277%v = BHEIGHT(1)%v
      SymbolTable_0x84b9ed0_279%v = BHEIGHT(3)%v
      SymbolTable_0x84b9ed0_281%v = BHEIGHT(1)%v
      SymbolTable_0x84b9ed0_2%v = (BHEIGHT(1)%v+BHEIGHT(3)%v)
      SymbolTable_0x84b9ed0_7%v = (BHEIGHT(1)%v/SymbolTable_0x84b9ed0_2%
     +v)
      SymbolTable_0x84b9ed0_3%v = (1D00/SymbolTable_0x84b9ed0_2%v)
      SymbolTable_0x84b9ed0_5%v = 1.0D00
      SymbolTable_0x84b9ed0_6%v = 1.0D00
      SymbolTable_0x84b9ed0_4%v = (-(BHEIGHT(1)%v/SQRT(BHEIGHT(1)%v)))
      DELTA%v = SymbolTable_0x84b9ed0_7%v
      SymbolTable_0x84b9ed0_276%v = (SymbolTable_0x84b9ed0_5%v*SymbolTab
     +le_0x84b9ed0_4%v)
      SymbolTable_0x84b9ed0_278%v = (SymbolTable_0x84b9ed0_6%v*SymbolTab
     +le_0x84b9ed0_4%v)
      SymbolTable_0x84b9ed0_280%v = SymbolTable_0x84b9ed0_3%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_276%v,SymbolTable_0x84b9ed0_277
     +,DELTA)
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_278%v,SymbolTable_0x84b9ed0_2
     +79,DELTA)
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_280%v,SymbolTable_0x84b9ed0_2
     +81,DELTA)
      BWIDTH = 4.0D+08
      SymbolTable_0x84b9ed0_283%v = BLENGTH(1)%v
      SymbolTable_0x84b9ed0_285%v = BWIDTH%v
      AREA(1)%v = (BLENGTH(1)%v*BWIDTH%v)
      SymbolTable_0x84b9ed0_8%v = BWIDTH%v
      SymbolTable_0x84b9ed0_9%v = BLENGTH(1)%v
      SymbolTable_0x84b9ed0_282%v = SymbolTable_0x84b9ed0_8%v
      SymbolTable_0x84b9ed0_284%v = SymbolTable_0x84b9ed0_9%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_282%v,SymbolTable_0x84b9ed0_283
     +,AREA(1))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_284%v,SymbolTable_0x84b9ed0_2
     +85,AREA(1))
      SymbolTable_0x84b9ed0_287%v = BLENGTH(2)%v
      SymbolTable_0x84b9ed0_289%v = BWIDTH%v
      AREA(2)%v = (BLENGTH(2)%v*BWIDTH%v)
      SymbolTable_0x84b9ed0_10%v = BWIDTH%v
      SymbolTable_0x84b9ed0_11%v = BLENGTH(2)%v
      SymbolTable_0x84b9ed0_286%v = SymbolTable_0x84b9ed0_10%v
      SymbolTable_0x84b9ed0_288%v = SymbolTable_0x84b9ed0_11%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_286%v,SymbolTable_0x84b9ed0_287
     +,AREA(2))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_288%v,SymbolTable_0x84b9ed0_2
     +89,AREA(2))
      SymbolTable_0x84b9ed0_291%v = BLENGTH(3)%v
      SymbolTable_0x84b9ed0_293%v = BWIDTH%v
      AREA(3)%v = (BLENGTH(3)%v*BWIDTH%v)
      SymbolTable_0x84b9ed0_12%v = BWIDTH%v
      SymbolTable_0x84b9ed0_13%v = BLENGTH(3)%v
      SymbolTable_0x84b9ed0_290%v = SymbolTable_0x84b9ed0_12%v
      SymbolTable_0x84b9ed0_292%v = SymbolTable_0x84b9ed0_13%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_290%v,SymbolTable_0x84b9ed0_291
     +,AREA(3))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_292%v,SymbolTable_0x84b9ed0_2
     +93,AREA(3))
      SymbolTable_0x84b9ed0_295%v = AREA(1)%v
      SymbolTable_0x84b9ed0_297%v = BHEIGHT(1)%v
      VOL(1)%v = (AREA(1)%v*BHEIGHT(1)%v)
      SymbolTable_0x84b9ed0_14%v = BHEIGHT(1)%v
      SymbolTable_0x84b9ed0_15%v = AREA(1)%v
      SymbolTable_0x84b9ed0_294%v = SymbolTable_0x84b9ed0_14%v
      SymbolTable_0x84b9ed0_296%v = SymbolTable_0x84b9ed0_15%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_294%v,SymbolTable_0x84b9ed0_295
     +,VOL(1))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_296%v,SymbolTable_0x84b9ed0_2
     +97,VOL(1))
      SymbolTable_0x84b9ed0_299%v = BHEIGHT(1)%v
      SymbolTable_0x84b9ed0_301%v = BHEIGHT(3)%v
      SymbolTable_0x84b9ed0_303%v = AREA(2)%v
      SymbolTable_0x84b9ed0_16%v = (BHEIGHT(1)%v+BHEIGHT(3)%v)
      SymbolTable_0x84b9ed0_21%v = (AREA(2)%v*SymbolTable_0x84b9ed0_16%v
     +)
      SymbolTable_0x84b9ed0_17%v = SymbolTable_0x84b9ed0_16%v
      SymbolTable_0x84b9ed0_19%v = 1.0D00
      SymbolTable_0x84b9ed0_20%v = 1.0D00
      SymbolTable_0x84b9ed0_18%v = AREA(2)%v
      VOL(2)%v = SymbolTable_0x84b9ed0_21%v
      SymbolTable_0x84b9ed0_298%v = (SymbolTable_0x84b9ed0_19%v*SymbolTa
     +ble_0x84b9ed0_18%v)
      SymbolTable_0x84b9ed0_300%v = (SymbolTable_0x84b9ed0_20%v*SymbolTa
     +ble_0x84b9ed0_18%v)
      SymbolTable_0x84b9ed0_302%v = SymbolTable_0x84b9ed0_17%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_298%v,SymbolTable_0x84b9ed0_299
     +,VOL(2))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_300%v,SymbolTable_0x84b9ed0_3
     +01,VOL(2))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_302%v,SymbolTable_0x84b9ed0_3
     +03,VOL(2))
      SymbolTable_0x84b9ed0_305%v = AREA(3)%v
      SymbolTable_0x84b9ed0_307%v = BHEIGHT(3)%v
      VOL(3)%v = (AREA(3)%v*BHEIGHT(3)%v)
      SymbolTable_0x84b9ed0_22%v = BHEIGHT(3)%v
      SymbolTable_0x84b9ed0_23%v = AREA(3)%v
      SymbolTable_0x84b9ed0_304%v = SymbolTable_0x84b9ed0_22%v
      SymbolTable_0x84b9ed0_306%v = SymbolTable_0x84b9ed0_23%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_304%v,SymbolTable_0x84b9ed0_305
     +,VOL(3))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_306%v,SymbolTable_0x84b9ed0_3
     +07,VOL(3))
      ROBERT_FILTER_COEFF = 2.5D-01
      HUNDRED = 1.0D+02
      THOUSAND = 1.0D+03
      DAY = 8.64D+04
      SymbolTable_0x84b9ed0_309%v = DAY%v
      YEAR%v = (DAY%v*3.65D+02)
      SymbolTable_0x84b9ed0_24%v = 3.65D+02
      SymbolTable_0x84b9ed0_308%v = SymbolTable_0x84b9ed0_24%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_308%v,SymbolTable_0x84b9ed0_309
     +,YEAR)
      SV = 1.0D+12
      SymbolTable_0x84b9ed0_311%v = SV%v
      SymbolTable_0x84b9ed0_26%v = (SV%v*1.6D+01)
      SymbolTable_0x84b9ed0_31%v = (SymbolTable_0x84b9ed0_26%v/4.0000000
     +0000000019169D-04)
      SymbolTable_0x84b9ed0_29%v = 1.6D+01
      SymbolTable_0x84b9ed0_27%v = 2.5D+03
      U0%v = SymbolTable_0x84b9ed0_31%v
      SymbolTable_0x84b9ed0_310%v = (SymbolTable_0x84b9ed0_29%v*SymbolTa
     +ble_0x84b9ed0_27%v)
      CALL sax_a_a(SymbolTable_0x84b9ed0_310%v,SymbolTable_0x84b9ed0_311
     +,U0)
      ALPHA = 1.6679999999999998864D-04
      BETA = 7.81000000000000010186D-04
      DAYS_PER_50M_MIXED_LAYER = 5.0D+01
      SymbolTable_0x84b9ed0_313%v = DAY%v
      SymbolTable_0x84b9ed0_32%v = (DAY%v*3.0D+02)
      SymbolTable_0x84b9ed0_37%v = (1D00/SymbolTable_0x84b9ed0_32%v)
      SymbolTable_0x84b9ed0_35%v = 3.0D+02
      SymbolTable_0x84b9ed0_34%v = (-1.0D00)
      GAMMA_T%v = SymbolTable_0x84b9ed0_37%v
      SymbolTable_0x84b9ed0_312%v = (SymbolTable_0x84b9ed0_35%v*SymbolTa
     +ble_0x84b9ed0_34%v)
      CALL sax_a_a(SymbolTable_0x84b9ed0_312%v,SymbolTable_0x84b9ed0_313
     +,GAMMA_T)
      SymbolTable_0x84b9ed0_317%v = DAY%v
      SymbolTable_0x84b9ed0_319%v = DAYS_PER_50M_MIXED_LAYER%v
      SymbolTable_0x84b9ed0_321%v = BHEIGHT(1)%v
      SymbolTable_0x84b9ed0_41%v = (BHEIGHT(1)%v/5.0D+03)
      SymbolTable_0x84b9ed0_42%v = (DAY%v*DAYS_PER_50M_MIXED_LAYER%v)
      SymbolTable_0x84b9ed0_38%v = (SymbolTable_0x84b9ed0_41%v*SymbolTab
     +le_0x84b9ed0_42%v)
      SymbolTable_0x84b9ed0_49%v = (0.0D00/SymbolTable_0x84b9ed0_38%v)
      SymbolTable_0x84b9ed0_45%v = 2.00000000000000009584D-04
      SymbolTable_0x84b9ed0_43%v = SymbolTable_0x84b9ed0_42%v
      SymbolTable_0x84b9ed0_47%v = DAYS_PER_50M_MIXED_LAYER%v
      SymbolTable_0x84b9ed0_48%v = DAY%v
      SymbolTable_0x84b9ed0_44%v = SymbolTable_0x84b9ed0_41%v
      SymbolTable_0x84b9ed0_40%v = (0.0D00/-0.0D00)
      GAMMA_S%v = SymbolTable_0x84b9ed0_49%v
      SymbolTable_0x84b9ed0_314%v = (SymbolTable_0x84b9ed0_43%v*SymbolTa
     +ble_0x84b9ed0_40%v)
      SymbolTable_0x84b9ed0_315%v = (SymbolTable_0x84b9ed0_44%v*SymbolTa
     +ble_0x84b9ed0_40%v)
      SymbolTable_0x84b9ed0_316%v = (SymbolTable_0x84b9ed0_47%v*SymbolTa
     +ble_0x84b9ed0_315%v)
      SymbolTable_0x84b9ed0_318%v = (SymbolTable_0x84b9ed0_48%v*SymbolTa
     +ble_0x84b9ed0_315%v)
      SymbolTable_0x84b9ed0_320%v = (SymbolTable_0x84b9ed0_45%v*SymbolTa
     +ble_0x84b9ed0_314%v)
      CALL sax_a_a(SymbolTable_0x84b9ed0_316%v,SymbolTable_0x84b9ed0_317
     +,GAMMA_S)
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_318%v,SymbolTable_0x84b9ed0_3
     +19,GAMMA_S)
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_320%v,SymbolTable_0x84b9ed0_3
     +21,GAMMA_S)
      EPSILON_IC = (-1.00000000000000004792D-04)
      SymbolTable_0x84b9ed0_323%v = DAY%v
      NOISE_CORRELATION_TIME%v = (DAY%v*1.5D+01)
      SymbolTable_0x84b9ed0_50%v = 1.5D+01
      SymbolTable_0x84b9ed0_322%v = SymbolTable_0x84b9ed0_50%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_322%v,SymbolTable_0x84b9ed0_323
     +,NOISE_CORRELATION_TIME)
      SymbolTable_0x84b9ed0_325%v = DAY%v
      DELTA_T%v = (DAY%v*5.0D00)
      SymbolTable_0x84b9ed0_52%v = 5.0D00
      SymbolTable_0x84b9ed0_324%v = SymbolTable_0x84b9ed0_52%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_324%v,SymbolTable_0x84b9ed0_325
     +,DELTA_T)
      WRITE(*,*)'delta_t = ',DELTA_T%v
      SymbolTable_0x84b9ed0_327%v = YEAR%v
      INTEGRATION_TIME%v = (YEAR%v*5.0D+01)
      SymbolTable_0x84b9ed0_54%v = 5.0D+01
      SymbolTable_0x84b9ed0_326%v = SymbolTable_0x84b9ed0_54%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_326%v,SymbolTable_0x84b9ed0_327
     +,INTEGRATION_TIME)
      WRITE(*,*)'integration_time = ',INTEGRATION_TIME%v
      N_MAX = JIDINT((INTEGRATION_TIME / DELTA_T))
      WRITE(*, *) 'n_max = ', N_MAX
      FDEPS = 9.99999999999999954748D-07
      SymbolTable_0x84b9ed0_329%v = THOUSAND%v
      Y(1)%v = (THOUSAND%v/3.2680000000000000715D-02)
      SymbolTable_0x84b9ed0_56%v = 3.05997552019583842764D+01
      SymbolTable_0x84b9ed0_328%v = SymbolTable_0x84b9ed0_56%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_328%v,SymbolTable_0x84b9ed0_329
     +,Y(1))
      SymbolTable_0x84b9ed0_331%v = THOUSAND%v
      Y(2)%v = (THOUSAND%v/7.9399999999999991418D-03)
      SymbolTable_0x84b9ed0_58%v = 1.25944584382871553885D+02
      SymbolTable_0x84b9ed0_330%v = SymbolTable_0x84b9ed0_58%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_330%v,SymbolTable_0x84b9ed0_331
     +,Y(2))
      SymbolTable_0x84b9ed0_333%v = THOUSAND%v
      Y(3)%v = (THOUSAND%v/1.39999999999999998578D-03)
      SymbolTable_0x84b9ed0_60%v = 7.14285714285714334437D+02
      SymbolTable_0x84b9ed0_332%v = SymbolTable_0x84b9ed0_60%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_332%v,SymbolTable_0x84b9ed0_333
     +,Y(3))
      SymbolTable_0x84b9ed0_335%v = THOUSAND%v
      Y(4)%v = (THOUSAND%v/1.41699999999999992628D-01)
      SymbolTable_0x84b9ed0_62%v = 7.0571630204657731511D00
      SymbolTable_0x84b9ed0_334%v = SymbolTable_0x84b9ed0_62%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_334%v,SymbolTable_0x84b9ed0_335
     +,Y(4))
      SymbolTable_0x84b9ed0_337%v = THOUSAND%v
      Y(5)%v = (THOUSAND%v/1.28599999999999992095D-01)
      SymbolTable_0x84b9ed0_64%v = 7.77604976671850778303D00
      SymbolTable_0x84b9ed0_336%v = SymbolTable_0x84b9ed0_64%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_336%v,SymbolTable_0x84b9ed0_337
     +,Y(5))
      SymbolTable_0x84b9ed0_339%v = THOUSAND%v
      Y(6)%v = (THOUSAND%v/8.7800000000000003042D-02)
      SymbolTable_0x84b9ed0_66%v = 1.1389521640091116339D+01
      SymbolTable_0x84b9ed0_338%v = SymbolTable_0x84b9ed0_66%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_338%v,SymbolTable_0x84b9ed0_339
     +,Y(6))
      SymbolTable_0x84b9ed0_341%v = ALPHA%v
      SymbolTable_0x84b9ed0_343%v = DELTA%v
      R(1)%v = (ALPHA%v*DELTA%v)
      SymbolTable_0x84b9ed0_68%v = DELTA%v
      SymbolTable_0x84b9ed0_69%v = ALPHA%v
      SymbolTable_0x84b9ed0_340%v = SymbolTable_0x84b9ed0_68%v
      SymbolTable_0x84b9ed0_342%v = SymbolTable_0x84b9ed0_69%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_340%v,SymbolTable_0x84b9ed0_341
     +,R(1))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_342%v,SymbolTable_0x84b9ed0_3
     +43,R(1))
      SymbolTable_0x84b9ed0_345%v = ALPHA%v
      R(2)%v = (-ALPHA%v)
      SymbolTable_0x84b9ed0_70%v = 4.294967295D+09
      SymbolTable_0x84b9ed0_344%v = SymbolTable_0x84b9ed0_70%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_344%v,SymbolTable_0x84b9ed0_345
     +,R(2))
      SymbolTable_0x84b9ed0_347%v = DELTA%v
      SymbolTable_0x84b9ed0_349%v = ALPHA%v
      SymbolTable_0x84b9ed0_71%v = (1.0D00-DELTA%v)
      SymbolTable_0x84b9ed0_76%v = (ALPHA%v*SymbolTable_0x84b9ed0_71%v)
      SymbolTable_0x84b9ed0_72%v = SymbolTable_0x84b9ed0_71%v
      SymbolTable_0x84b9ed0_75%v = 4.294967295D+09
      SymbolTable_0x84b9ed0_73%v = ALPHA%v
      R(3)%v = SymbolTable_0x84b9ed0_76%v
      SymbolTable_0x84b9ed0_346%v = (SymbolTable_0x84b9ed0_75%v*SymbolTa
     +ble_0x84b9ed0_73%v)
      SymbolTable_0x84b9ed0_348%v = SymbolTable_0x84b9ed0_72%v
      CALL sax_a_a(SymbolTable_0x84b9ed0_346%v,SymbolTable_0x84b9ed0_347
     +,R(3))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_348%v,SymbolTable_0x84b9ed0_3
     +49,R(3))
      SymbolTable_0x84b9ed0_351%v = BETA%v
      SymbolTable_0x84b9ed0_353%v = DELTA%v
      R(4)%v = (-(BETA%v*DELTA%v))
      SymbolTable_0x84b9ed0_78%v = DELTA%v
      SymbolTable_0x84b9ed0_79%v = BETA%v
      SymbolTable_0x84b9ed0_77%v = 4.294967295D+09
      SymbolTable_0x84b9ed0_350%v = (SymbolTable_0x84b9ed0_78%v*SymbolTa
     +ble_0x84b9ed0_77%v)
      SymbolTable_0x84b9ed0_352%v = (SymbolTable_0x84b9ed0_79%v*SymbolTa
     +ble_0x84b9ed0_77%v)
      CALL sax_a_a(SymbolTable_0x84b9ed0_350%v,SymbolTable_0x84b9ed0_351
     +,R(4))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_352%v,SymbolTable_0x84b9ed0_3
     +53,R(4))
      R(5)%v = BETA%v
      CALL sax_a_a(1.0D00,BETA,R(5))
      SymbolTable_0x84b9ed0_356%v = BETA%v
      SymbolTable_0x84b9ed0_358%v = DELTA%v
      SymbolTable_0x84b9ed0_81%v = (1.0D00-DELTA%v)
      SymbolTable_0x84b9ed0_86%v = (-(BETA%v*SymbolTable_0x84b9ed0_81%v)
     +)
      SymbolTable_0x84b9ed0_82%v = SymbolTable_0x84b9ed0_81%v
      SymbolTable_0x84b9ed0_85%v = 4.294967295D+09
      SymbolTable_0x84b9ed0_83%v = BETA%v
      SymbolTable_0x84b9ed0_80%v = 4.294967295D+09
      R(6)%v = SymbolTable_0x84b9ed0_86%v
      SymbolTable_0x84b9ed0_354%v = (SymbolTable_0x84b9ed0_85%v*SymbolTa
     +ble_0x84b9ed0_83%v)
      SymbolTable_0x84b9ed0_355%v = (SymbolTable_0x84b9ed0_82%v*SymbolTa
     +ble_0x84b9ed0_80%v)
      SymbolTable_0x84b9ed0_357%v = (SymbolTable_0x84b9ed0_354%v*SymbolT
     +able_0x84b9ed0_80%v)
      CALL sax_a_a(SymbolTable_0x84b9ed0_355%v,SymbolTable_0x84b9ed0_356
     +,R(6))
      CALL saxpy_a_a(SymbolTable_0x84b9ed0_357%v,SymbolTable_0x84b9ed0_3
     +58,R(6))
      DO L = 1, 6, 1
        SymbolTable_0x84b9ed0_360%v = R(L)%v
        SymbolTable_0x84b9ed0_362%v = U0%v
        SymbolTable_0x84b9ed0_364%v = SV%v
        SymbolTable_0x84b9ed0_87%v = (R(L)%v*U0%v)
        SymbolTable_0x84b9ed0_92%v = (SymbolTable_0x84b9ed0_87%v/SV%v)
        SymbolTable_0x84b9ed0_90%v = U0%v
        SymbolTable_0x84b9ed0_91%v = R(L)%v
        SymbolTable_0x84b9ed0_88%v = (1D00/SV%v)
        SymbolTable_0x84b9ed0_89%v = (-(SymbolTable_0x84b9ed0_87%v/SQRT(
     +SymbolTable_0x84b9ed0_87%v)))
        R(L)%v = SymbolTable_0x84b9ed0_92%v
        SymbolTable_0x84b9ed0_359%v = (SymbolTable_0x84b9ed0_90%v*Symbol
     +Table_0x84b9ed0_88%v)
        SymbolTable_0x84b9ed0_361%v = (SymbolTable_0x84b9ed0_91%v*Symbol
     +Table_0x84b9ed0_88%v)
        SymbolTable_0x84b9ed0_363%v = SymbolTable_0x84b9ed0_89%v
        CALL sax_a_a(SymbolTable_0x84b9ed0_359%v,SymbolTable_0x84b9ed0_3
     +60,R(L))
        CALL saxpy_a_a(SymbolTable_0x84b9ed0_361%v,SymbolTable_0x84b9ed0
     +_362,R(L))
        CALL saxpy_a_a(SymbolTable_0x84b9ed0_363%v,SymbolTable_0x84b9ed0
     +_364,R(L))
      END DO
      DO L = 1, 6, 1
        IF(L .LE. 3) THEN
          PROJ_T(L) = 1.0D00
          PROJ_S(L) = 0.0D00
        ELSE
          PROJ_T(L) = 0.0D00
          PROJ_S(L) = 1.0D00
        ENDIF
      END DO
      DO L = 1, 6, 1
        SymbolTable_0x84b9ed0_366%v = PROJ_T(L)%v
        SymbolTable_0x84b9ed0_368%v = R(L)%v
        R_T(L)%v = (PROJ_T(L)%v*R(L)%v)
        SymbolTable_0x84b9ed0_93%v = R(L)%v
        SymbolTable_0x84b9ed0_94%v = PROJ_T(L)%v
        SymbolTable_0x84b9ed0_365%v = SymbolTable_0x84b9ed0_93%v
        SymbolTable_0x84b9ed0_367%v = SymbolTable_0x84b9ed0_94%v
        CALL sax_a_a(SymbolTable_0x84b9ed0_365%v,SymbolTable_0x84b9ed0_3
     +66,R_T(L))
        CALL saxpy_a_a(SymbolTable_0x84b9ed0_367%v,SymbolTable_0x84b9ed0
     +_368,R_T(L))
        SymbolTable_0x84b9ed0_370%v = PROJ_S(L)%v
        SymbolTable_0x84b9ed0_372%v = R(L)%v
        R_S(L)%v = (PROJ_S(L)%v*R(L)%v)
        SymbolTable_0x84b9ed0_95%v = R(L)%v
        SymbolTable_0x84b9ed0_96%v = PROJ_S(L)%v
        SymbolTable_0x84b9ed0_369%v = SymbolTable_0x84b9ed0_95%v
        SymbolTable_0x84b9ed0_371%v = SymbolTable_0x84b9ed0_96%v
        CALL sax_a_a(SymbolTable_0x84b9ed0_369%v,SymbolTable_0x84b9ed0_3
     +70,R_S(L))
        CALL saxpy_a_a(SymbolTable_0x84b9ed0_371%v,SymbolTable_0x84b9ed0
     +_372,R_S(L))
      END DO
      R1(1) = 1.0D00
      R1(2) = (-1.0D00)
      R1(3) = 0.0D00
      R1(4) = 0.0D00
      R1(5) = 0.0D00
      R1(6) = 0.0D00
      DO J = 1, 6, 1
        DO I = 1, 6, 1
          SymbolTable_0x84b9ed0_374%v = R(I)%v
          SymbolTable_0x84b9ed0_376%v = R(J)%v
          X(I,J)%v = (R(I)%v*R(J)%v)
          SymbolTable_0x84b9ed0_97%v = R(J)%v
          SymbolTable_0x84b9ed0_98%v = R(I)%v
          SymbolTable_0x84b9ed0_373%v = SymbolTable_0x84b9ed0_97%v
          SymbolTable_0x84b9ed0_375%v = SymbolTable_0x84b9ed0_98%v
          CALL sax_a_a(SymbolTable_0x84b9ed0_373%v,SymbolTable_0x84b9ed0
     +_374,X(I,J))
          CALL saxpy_a_a(SymbolTable_0x84b9ed0_375%v,SymbolTable_0x84b9e
     +d0_376,X(I,J))
        END DO
      END DO
      EPSILON_REGULARIZE = 1.00000000000000002092D-08
      DO J = 1, 6, 1
        DO I = 1, 6, 1
          SymbolTable_0x84b9ed0_378%v = X(I,J)%v
          SymbolTable_0x84b9ed0_380%v = EPSILON_REGULARIZE%v
          X(I,J)%v = (X(I,J)%v+EPSILON_REGULARIZE%v)
          SymbolTable_0x84b9ed0_99%v = 1.0D00
          SymbolTable_0x84b9ed0_100%v = 1.0D00
          SymbolTable_0x84b9ed0_377%v = SymbolTable_0x84b9ed0_99%v
          SymbolTable_0x84b9ed0_379%v = SymbolTable_0x84b9ed0_100%v
          CALL sax_a_a(SymbolTable_0x84b9ed0_377%v,SymbolTable_0x84b9ed0
     +_378,X(I,J))
          CALL saxpy_a_a(SymbolTable_0x84b9ed0_379%v,SymbolTable_0x84b9e
     +d0_380,X(I,J))
        END DO
      END DO
      RETURN
      END SUBROUTINE
W2F1PP
    $ff = Ffile->new_from_heredoc($w2f1);
}

sub teardown{
    ;
}

