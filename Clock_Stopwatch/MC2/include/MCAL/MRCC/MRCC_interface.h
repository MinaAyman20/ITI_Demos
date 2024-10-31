/******************************************************************************
*
* Module: RCC Driver.
*
* File Name: RCC_interface.h
*
* Description: Driver's APIs' prototypes and typedefs' declaration.
*
* Author: Shaher Shah Abdalla Kamal
*
* Date:	07-02-2024
*
*******************************************************************************/

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

/****************************************************************************************/
/*										Includes										*/
/****************************************************************************************/
/* ِIncluding the .h file that contains typedefs for the primitive data types */
#include <LIB/std_types.h>


/****************************************************************************************/
/*									Macros Declaration									*/
/****************************************************************************************/


/*=========================================================*/
/*=========================================================*/
/* PLease Supply me with these data to run correctly */

/* The value of the external HSE Oscillator
 * CAUTION:	Its value MUST be between 4 and 26 MHz */
#define HSE_CRYSTAL_VALUE				(25000000UL)
/*=========================================================*/
/*=========================================================*/








/* Main PLL(PLL) and audio PLL (PLLI2S) entry clock source options */

/* Select HSI as the PLLs clock source */
#define PLLSRC_HSI						(0x00000000UL)	/* 	Mask for HSI in PLLSRC bit	*/
/* Select HSE as the PLLs clock source */
#define PLLSRC_HSE						(0x00400000UL)	/* 	Mask for HSE in PLLSRC bit	*/
/**************************************************************************************/

/* PLLM options */
#define PLLM_2  						(2UL)	/*(0x00000002UL)	 	Mask for PLLM bits	*/
#define PLLM_3  						(3UL) 	/*(0x00000003UL)	 	Mask for PLLM bits	*/
#define PLLM_4 						 	(4UL) 	/*(0x00000004UL)	 	Mask for PLLM bits	*/
#define PLLM_5  						(5UL) 	/*(0x00000005UL)	 	Mask for PLLM bits	*/
#define PLLM_6  						(6UL)	/*(0x00000006UL)	 	Mask for PLLM bits	*/
#define PLLM_7  						(7UL)	/*(0x00000007UL)	 	Mask for PLLM bits	*/
#define PLLM_8  						(8UL)	/*(0x00000008UL)	 	Mask for PLLM bits	*/
#define PLLM_9  						(9UL)	/*(0x00000009UL)	 	Mask for PLLM bits	*/
#define PLLM_10  						(10UL)	/*(0x0000000AUL)	 	Mask for PLLM bits	*/
#define PLLM_11  						(11UL)	/*(0x0000000BUL)	 	Mask for PLLM bits	*/
#define PLLM_12  						(12UL)	/*(0x0000000CUL)	 	Mask for PLLM bits	*/
#define PLLM_13							(13UL)	/*(0x0000000DUL)	 	Mask for PLLM bits	*/
#define PLLM_14  						(14UL)	/*(0x0000000EUL)	 	Mask for PLLM bits	*/
#define PLLM_15  						(15UL)	/*(0x0000000FUL)	 	Mask for PLLM bits	*/
#define PLLM_16  						(16UL)	/*(0x00000010UL)	 	Mask for PLLM bits	*/
#define PLLM_17  						(17UL)	/*(0x00000011UL)	 	Mask for PLLM bits	*/
#define PLLM_18  						(18UL)	/*(0x00000012UL)	 	Mask for PLLM bits	*/
#define PLLM_19  						(19UL)	/*(0x00000013UL)	 	Mask for PLLM bits	*/
#define PLLM_20  						(20UL)	/*(0x00000014UL)	 	Mask for PLLM bits	*/
#define PLLM_21  						(21UL)	/*(0x00000015UL)	 	Mask for PLLM bits	*/
#define PLLM_22  						(22UL)	/*(0x00000016UL)	 	Mask for PLLM bits	*/
#define PLLM_23  						(23UL)	/*(0x00000017UL)	 	Mask for PLLM bits	*/
#define PLLM_24  						(24UL)	/*(0x00000018UL)	 	Mask for PLLM bits	*/
#define PLLM_25  						(25UL)	/*(0x00000019UL)	 	Mask for PLLM bits	*/
#define PLLM_26  						(26UL)	/*(0x0000001AUL)	 	Mask for PLLM bits	*/
#define PLLM_27  						(27UL)	/*(0x0000001BUL)	 	Mask for PLLM bits	*/
#define PLLM_28  						(28UL)	/*(0x0000001CUL)	 	Mask for PLLM bits	*/
#define PLLM_29  						(29UL)	/*(0x0000001DUL)	 	Mask for PLLM bits	*/
#define PLLM_30  						(30UL)	/*(0x0000001EUL)	 	Mask for PLLM bits	*/
#define PLLM_31  						(31UL)	/*(0x0000001FUL)	 	Mask for PLLM bits	*/
#define PLLM_32  						(32UL)	/*(0x00000020UL)	 	Mask for PLLM bits	*/
#define PLLM_33  						(33UL)	/*(0x00000021UL)	 	Mask for PLLM bits	*/
#define PLLM_34  						(34UL)	/*(0x00000022UL)	 	Mask for PLLM bits	*/
#define PLLM_35  						(35UL)	/*(0x00000023UL)	 	Mask for PLLM bits	*/
#define PLLM_36  						(36UL)	/*(0x00000024UL)	 	Mask for PLLM bits	*/
#define PLLM_37  						(37UL)	/*(0x00000025UL)	 	Mask for PLLM bits	*/
#define PLLM_38  						(38UL)	/*(0x00000026UL)	 	Mask for PLLM bits	*/
#define PLLM_39  						(39UL)	/*(0x00000027UL)	 	Mask for PLLM bits	*/
#define PLLM_40  						(40UL)	/*(0x00000028UL)	 	Mask for PLLM bits	*/
#define PLLM_41  						(41UL)	/*(0x00000029UL)	 	Mask for PLLM bits	*/
#define PLLM_42  						(42UL)	/*(0x0000002AUL)	 	Mask for PLLM bits	*/
#define PLLM_43  						(43UL)	/*(0x0000002BUL)	 	Mask for PLLM bits	*/
#define PLLM_44  						(44UL)	/*(0x0000002CUL)	 	Mask for PLLM bits	*/
#define PLLM_45  						(45UL)	/*(0x0000002DUL)	 	Mask for PLLM bits	*/
#define PLLM_46  						(46UL)	/*(0x0000002EUL)	 	Mask for PLLM bits	*/
#define PLLM_47 						(47UL)	/*(0x0000002FUL)	 	Mask for PLLM bits	*/
#define PLLM_48 						(48UL)	/*(0x00000030UL)	 	Mask for PLLM bits	*/
#define PLLM_49  						(49UL)	/*(0x00000031UL)	 	Mask for PLLM bits	*/
#define PLLM_50  						(50UL)	/*(0x00000032UL)	 	Mask for PLLM bits	*/
#define PLLM_51  						(51UL)	/*(0x00000033UL)	 	Mask for PLLM bits	*/
#define PLLM_52  						(52UL)	/*(0x00000034UL)	 	Mask for PLLM bits	*/
#define PLLM_53  						(53UL)	/*(0x00000035UL)	 	Mask for PLLM bits	*/
#define PLLM_54  						(54UL)	/*(0x00000036UL)	 	Mask for PLLM bits	*/
#define PLLM_55  						(55UL)	/*(0x00000037UL)	 	Mask for PLLM bits	*/
#define PLLM_56  						(56UL)	/*(0x00000038UL)	 	Mask for PLLM bits	*/
#define PLLM_57  						(57UL)	/*(0x00000039UL)	 	Mask for PLLM bits	*/
#define PLLM_58  						(58UL)	/*(0x0000003AUL)	 	Mask for PLLM bits	*/
#define PLLM_59  						(59UL)	/*(0x0000003BUL)	 	Mask for PLLM bits	*/
#define PLLM_60  						(60UL)	/*(0x0000003CUL)	 	Mask for PLLM bits	*/
#define PLLM_61  						(61UL)	/*(0x0000003DUL)	 	Mask for PLLM bits	*/
#define PLLM_62 						(62UL)	/*(0x0000003EUL)	 	Mask for PLLM bits	*/
#define PLLM_63  						(63UL)	/*(0x0000003FUL)	 	Mask for PLLM bits	*/
/**************************************************************************************/

/* PLLN options */
#define PLLN_192   						(192UL)	/*(0x00003000UL)	 	Mask for PLLN bits	*/
#define PLLN_193   						(193UL)
#define PLLN_194   						(194UL)
#define PLLN_195   						(195UL)
#define PLLN_196   						(196UL)
#define PLLN_197   						(197UL)
#define PLLN_198   						(198UL)
#define PLLN_199   						(199UL)
#define PLLN_200   						(200UL)
#define PLLN_201   						(201UL)
#define PLLN_202   						(202UL)
#define PLLN_203   						(203UL)
#define PLLN_204   						(204UL)
#define PLLN_205   						(205UL)
#define PLLN_206   						(206UL)
#define PLLN_207   						(207UL)
#define PLLN_208   						(208UL)
#define PLLN_209   						(209UL)
#define PLLN_210   						(210UL)
#define PLLN_211   						(211UL)
#define PLLN_212   						(212UL)
#define PLLN_213   						(213UL)
#define PLLN_214  					 	(214UL)
#define PLLN_215   						(215UL)
#define PLLN_216   						(216UL)
#define PLLN_217   						(217UL)
#define PLLN_218   						(218UL)
#define PLLN_219   						(219UL)
#define PLLN_220   						(220UL)
#define PLLN_221  						(221UL)
#define PLLN_222   						(222UL)
#define PLLN_223   						(223UL)
#define PLLN_224   						(224UL)
#define PLLN_225   						(225UL)
#define PLLN_226   						(226UL)
#define PLLN_227   						(227UL)
#define PLLN_228   						(228UL)
#define PLLN_229   						(229UL)
#define PLLN_230   						(230UL)
#define PLLN_231   						(231UL)
#define PLLN_232   						(232UL)
#define PLLN_233   						(233UL)
#define PLLN_234   						(234UL)
#define PLLN_235   						(235UL)
#define PLLN_236   						(236UL)
#define PLLN_237   						(237UL)
#define PLLN_238   						(238UL)
#define PLLN_239   						(239UL)
#define PLLN_240   						(240UL)
#define PLLN_241   						(241UL)
#define PLLN_242   						(242UL)
#define PLLN_243   						(243UL)
#define PLLN_244   						(244UL)
#define PLLN_245   						(245UL)
#define PLLN_246   						(246UL)
#define PLLN_247   						(247UL)
#define PLLN_248   						(248UL)
#define PLLN_249   						(249UL)
#define PLLN_250   						(250UL)
#define PLLN_251   						(251UL)
#define PLLN_252   						(252UL)
#define PLLN_253   						(253UL)
#define PLLN_254   						(254UL)
#define PLLN_255   						(255UL)
#define PLLN_256   						(256UL)
#define PLLN_257   						(257UL)
#define PLLN_258   						(258UL)
#define PLLN_259   						(259UL)
#define PLLN_260   						(260UL)
#define PLLN_261   						(261UL)
#define PLLN_262   						(262UL)
#define PLLN_263   						(263UL)
#define PLLN_264   						(264UL)
#define PLLN_265   						(265UL)
#define PLLN_266   						(266UL)
#define PLLN_267   						(267UL)
#define PLLN_268  						(268UL)
#define PLLN_269   						(269UL)
#define PLLN_270   						(270UL)
#define PLLN_271   						(271UL)
#define PLLN_272   						(272UL)
#define PLLN_273   						(273UL)
#define PLLN_274   						(274UL)
#define PLLN_275   						(275UL)
#define PLLN_276   						(276UL)
#define PLLN_277   						(277UL)
#define PLLN_278   						(278UL)
#define PLLN_279   						(279UL)
#define PLLN_280   						(280UL)
#define PLLN_281   						(281UL)
#define PLLN_282   						(282UL)
#define PLLN_283   						(283UL)
#define PLLN_284   						(284UL)
#define PLLN_285   						(285UL)
#define PLLN_286   						(286UL)
#define PLLN_287   						(287UL)
#define PLLN_288   						(288UL)
#define PLLN_289   						(289UL)
#define PLLN_290   						(290UL)
#define PLLN_291   						(291UL)
#define PLLN_292   						(292UL)
#define PLLN_293   						(293UL)
#define PLLN_294   						(294UL)
#define PLLN_295   						(295UL)
#define PLLN_296   						(296UL)
#define PLLN_297  						(297UL)
#define PLLN_298   						(298UL)
#define PLLN_299   						(299UL)
#define PLLN_300   						(300UL)
#define PLLN_301   						(301UL)
#define PLLN_302   						(302UL)
#define PLLN_303   						(303UL)
#define PLLN_304   						(304UL)
#define PLLN_305   						(305UL)
#define PLLN_306   						(306UL)
#define PLLN_307   						(307UL)
#define PLLN_308   						(308UL)
#define PLLN_309   						(309UL)
#define PLLN_310   						(310UL)
#define PLLN_311   						(311UL)
#define PLLN_312   						(312UL)
#define PLLN_313   						(313UL)
#define PLLN_314   						(314UL)
#define PLLN_315   						(315UL)
#define PLLN_316   						(316UL)
#define PLLN_317   						(317UL)
#define PLLN_318   						(318UL)
#define PLLN_319   						(319UL)
#define PLLN_320   						(320UL)
#define PLLN_321   						(321UL)
#define PLLN_322   						(322UL)
#define PLLN_323   						(323UL)
#define PLLN_324   						(324UL)
#define PLLN_325   						(325UL)
#define PLLN_326   						(326UL)
#define PLLN_327   						(327UL)
#define PLLN_328   						(328UL)
#define PLLN_329   						(329UL)
#define PLLN_330   						(330UL)
#define PLLN_331   						(331UL)
#define PLLN_332   						(332UL)
#define PLLN_333   						(333UL)
#define PLLN_334   						(334UL)
#define PLLN_335   						(335UL)
#define PLLN_336   						(336UL)
#define PLLN_337   						(337UL)
#define PLLN_338   						(338UL)
#define PLLN_339   						(339UL)
#define PLLN_340   						(340UL)
#define PLLN_341   						(341UL)
#define PLLN_342   						(342UL)
#define PLLN_343   						(343UL)
#define PLLN_344   						(344UL)
#define PLLN_345   						(345UL)
#define PLLN_346   						(346UL)
#define PLLN_347   						(347UL)
#define PLLN_348   						(348UL)
#define PLLN_349   						(349UL)
#define PLLN_350   						(350UL)
#define PLLN_351   						(351UL)
#define PLLN_352   						(352UL)
#define PLLN_353   						(353UL)
#define PLLN_354   						(354UL)
#define PLLN_355   						(355UL)
#define PLLN_356   						(356UL)
#define PLLN_357   						(357UL)
#define PLLN_358   						(358UL)
#define PLLN_359   						(359UL)
#define PLLN_360   						(360UL)
#define PLLN_361   						(361UL)
#define PLLN_362   						(362UL)
#define PLLN_363   						(363UL)
#define PLLN_364   						(364UL)
#define PLLN_365   						(365UL)
#define PLLN_366   						(366UL)
#define PLLN_367   						(367UL)
#define PLLN_368   						(368UL)
#define PLLN_369   						(369UL)
#define PLLN_370   						(370UL)
#define PLLN_371   						(371UL)
#define PLLN_372   						(372UL)
#define PLLN_373   						(373UL)
#define PLLN_374   						(374UL)
#define PLLN_375   						(375UL)
#define PLLN_376   						(376UL)
#define PLLN_377   						(377UL)
#define PLLN_378   						(378UL)
#define PLLN_379   						(379UL)
#define PLLN_380   						(380UL)
#define PLLN_381   						(381UL)
#define PLLN_382   						(382UL)
#define PLLN_383   						(383UL)
#define PLLN_384   						(384UL)
#define PLLN_385   						(385UL)
#define PLLN_386   						(386UL)
#define PLLN_387   						(387UL)
#define PLLN_388   						(388UL)
#define PLLN_389   						(389UL)
#define PLLN_390   						(390UL)
#define PLLN_391   						(391UL)
#define PLLN_392   						(392UL)
#define PLLN_393   						(393UL)
#define PLLN_394   						(394UL)
#define PLLN_395   						(395UL)
#define PLLN_396   						(396UL)
#define PLLN_397   						(397UL)
#define PLLN_398  						(398UL)
#define PLLN_399   						(399UL)
#define PLLN_400   						(400UL)
#define PLLN_401   						(401UL)
#define PLLN_402   						(402UL)
#define PLLN_403   						(403UL)
#define PLLN_404   						(404UL)
#define PLLN_405   						(405UL)
#define PLLN_406   						(406UL)
#define PLLN_407   						(407UL)
#define PLLN_408   						(408UL)
#define PLLN_409   						(409UL)
#define PLLN_410   						(410UL)
#define PLLN_411   						(411UL)
#define PLLN_412   						(412UL)
#define PLLN_413  						(413UL)
#define PLLN_414   						(414UL)
#define PLLN_415   						(415UL)
#define PLLN_416   						(416UL)
#define PLLN_417   						(417UL)
#define PLLN_418   						(418UL)
#define PLLN_419   						(419UL)
#define PLLN_420   						(420UL)
#define PLLN_421   						(421UL)
#define PLLN_422   						(422UL)
#define PLLN_423   						(423UL)
#define PLLN_424   						(424UL)
#define PLLN_425   						(425UL)
#define PLLN_426  						(426UL)
#define PLLN_427   						(427UL)
#define PLLN_428   						(428UL)
#define PLLN_429   						(429UL)	/*(0x00006B40UL)	 	Mask for PLLN bits	*/
#define PLLN_430   						(430UL)	/*(0x00006B80UL)	 	Mask for PLLN bits	*/
#define PLLN_431   						(431UL)	/*(0x00006BC0UL)	 	Mask for PLLN bits	*/
#define PLLN_432   						(432UL)	/*(0x00006C00UL)	 	Mask for PLLN bits	*/
/**************************************************************************************/

/* PLLP options */
#define PLLP_2 							(0UL)	/*(0x00000000UL)	 	Mask for PLLP bits	*/
#define PLLP_4 							(1UL)	/*(0x00010000UL)	 	Mask for PLLP bits	*/
#define PLLP_6 							(2UL)	/*(0x00020000UL)	 	Mask for PLLP bits	*/
#define PLLP_8							(3UL)	/*(0x00030000UL)	 	Mask for PLLP bits	*/
/**************************************************************************************/

/* PLLQ options */
#define PLLQ_2  						(2UL)	/*(0x02000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_3  						(3UL)	/*(0x03000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_4 						 	(4UL)	/*(0x04000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_5  						(5UL)	/*(0x05000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_6  						(6UL)	/*(0x06000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_7  						(7UL)	/*(0x07000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_8  						(8UL)	/*(0x08000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_9  						(9UL)	/*(0x09000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_10  						(10UL)	/*(0x0A000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_11  						(11UL)	/*(0x0B000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_12  						(12UL)	/*(0x0C000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_13							(13UL)	/*(0x0D000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_14  						(14UL)	/*(0x0E000000UL)	 	Mask for PLLQ bits	*/
#define PLLQ_15  						(15UL)	/*(0x0F000000UL)	 	Mask for PLLQ bits	*/
/**************************************************************************************/

/* PLLI2SN options */
#define PLLI2SN_192   					(192UL)	/*(0x00003000UL)	 	Mask for PLLN bits	*/
#define PLLI2SN_193   					(193UL)
#define PLLI2SN_194   					(194UL)
#define PLLI2SN_195   					(195UL)
#define PLLI2SN_196   					(196UL)
#define PLLI2SN_197   					(197UL)
#define PLLI2SN_198   					(198UL)
#define PLLI2SN_199   					(199UL)
#define PLLI2SN_200   					(200UL)
#define PLLI2SN_201   					(201UL)
#define PLLI2SN_202   					(202UL)
#define PLLI2SN_203   					(203UL)
#define PLLI2SN_204   					(204UL)
#define PLLI2SN_205   					(205UL)
#define PLLI2SN_206   					(206UL)
#define PLLI2SN_207   					(207UL)
#define PLLI2SN_208   					(208UL)
#define PLLI2SN_209   					(209UL)
#define PLLI2SN_210   					(210UL)
#define PLLI2SN_211   					(211UL)
#define PLLI2SN_212   					(212UL)
#define PLLI2SN_213   					(213UL)
#define PLLI2SN_214  				 	(214UL)
#define PLLI2SN_215   					(215UL)
#define PLLI2SN_216   					(216UL)
#define PLLI2SN_217   					(217UL)
#define PLLI2SN_218   					(218UL)
#define PLLI2SN_219   					(219UL)
#define PLLI2SN_220   					(220UL)
#define PLLI2SN_221  					(221UL)
#define PLLI2SN_222   					(222UL)
#define PLLI2SN_223   					(223UL)
#define PLLI2SN_224   					(224UL)
#define PLLI2SN_225   					(225UL)
#define PLLI2SN_226   					(226UL)
#define PLLI2SN_227   					(227UL)
#define PLLI2SN_228  					(228UL)
#define PLLI2SN_229   					(229UL)
#define PLLI2SN_230   					(230UL)
#define PLLI2SN_231   					(231UL)
#define PLLI2SN_232   					(232UL)
#define PLLI2SN_233   					(233UL)
#define PLLI2SN_234   					(234UL)
#define PLLI2SN_235   					(235UL)
#define PLLI2SN_236   					(236UL)
#define PLLI2SN_237   					(237UL)
#define PLLI2SN_238   					(238UL)
#define PLLI2SN_239   					(239UL)
#define PLLI2SN_240   					(240UL)
#define PLLI2SN_241   					(241UL)
#define PLLI2SN_242   					(242UL)
#define PLLI2SN_243   					(243UL)
#define PLLI2SN_244   					(244UL)
#define PLLI2SN_245   					(245UL)
#define PLLI2SN_246   					(246UL)
#define PLLI2SN_247   					(247UL)
#define PLLI2SN_248   					(248UL)
#define PLLI2SN_249   					(249UL)
#define PLLI2SN_250   					(250UL)
#define PLLI2SN_251   					(251UL)
#define PLLI2SN_252   					(252UL)
#define PLLI2SN_253   					(253UL)
#define PLLI2SN_254   					(254UL)
#define PLLI2SN_255   					(255UL)
#define PLLI2SN_256   					(256UL)
#define PLLI2SN_257   					(257UL)
#define PLLI2SN_258   					(258UL)
#define PLLI2SN_259   					(259UL)
#define PLLI2SN_260   					(260UL)
#define PLLI2SN_261   					(261UL)
#define PLLI2SN_262   					(262UL)
#define PLLI2SN_263   					(263UL)
#define PLLI2SN_264   					(264UL)
#define PLLI2SN_265   					(265UL)
#define PLLI2SN_266   					(266UL)
#define PLLI2SN_267   					(267UL)
#define PLLI2SN_268  					(268UL)
#define PLLI2SN_269   					(269UL)
#define PLLI2SN_270   					(270UL)
#define PLLI2SN_271   					(271UL)
#define PLLI2SN_272   					(272UL)
#define PLLI2SN_273   					(273UL)
#define PLLI2SN_274   					(274UL)
#define PLLI2SN_275   					(275UL)
#define PLLI2SN_276   					(276UL)
#define PLLI2SN_277   					(277UL)
#define PLLI2SN_278   					(278UL)
#define PLLI2SN_279   					(279UL)
#define PLLI2SN_280   					(280UL)
#define PLLI2SN_281   					(281UL)
#define PLLI2SN_282   					(282UL)
#define PLLI2SN_283   					(283UL)
#define PLLI2SN_284   					(284UL)
#define PLLI2SN_285   					(285UL)
#define PLLI2SN_286   					(286UL)
#define PLLI2SN_287   					(287UL)
#define PLLI2SN_288   					(288UL)
#define PLLI2SN_289   					(289UL)
#define PLLI2SN_290   					(290UL)
#define PLLI2SN_291   					(291UL)
#define PLLI2SN_292   					(292UL)
#define PLLI2SN_293   					(293UL)
#define PLLI2SN_294   					(294UL)
#define PLLI2SN_295   					(295UL)
#define PLLI2SN_296   					(296UL)
#define PLLI2SN_297  					(297UL)
#define PLLI2SN_298   					(298UL)
#define PLLI2SN_299   					(299UL)
#define PLLI2SN_300   					(300UL)
#define PLLI2SN_301   					(301UL)
#define PLLI2SN_302   					(302UL)
#define PLLI2SN_303   					(303UL)
#define PLLI2SN_304   					(304UL)
#define PLLI2SN_305   					(305UL)
#define PLLI2SN_306   					(306UL)
#define PLLI2SN_307   					(307UL)
#define PLLI2SN_308   					(308UL)
#define PLLI2SN_309   					(309UL)
#define PLLI2SN_310   					(310UL)
#define PLLI2SN_311   					(311UL)
#define PLLI2SN_312   					(312UL)
#define PLLI2SN_313   					(313UL)
#define PLLI2SN_314   					(314UL)
#define PLLI2SN_315   					(315UL)
#define PLLI2SN_316   					(316UL)
#define PLLI2SN_317   					(317UL)
#define PLLI2SN_318   					(318UL)
#define PLLI2SN_319   					(319UL)
#define PLLI2SN_320   					(320UL)
#define PLLI2SN_321   					(321UL)
#define PLLI2SN_322   					(322UL)
#define PLLI2SN_323   					(323UL)
#define PLLI2SN_324   					(324UL)
#define PLLI2SN_325   					(325UL)
#define PLLI2SN_326   					(326UL)
#define PLLI2SN_327   					(327UL)
#define PLLI2SN_328   					(328UL)
#define PLLI2SN_329   					(329UL)
#define PLLI2SN_330  					(330UL)
#define PLLI2SN_331   					(331UL)
#define PLLI2SN_332   					(332UL)
#define PLLI2SN_333   					(333UL)
#define PLLI2SN_334   					(334UL)
#define PLLI2SN_335   					(335UL)
#define PLLI2SN_336   					(336UL)
#define PLLI2SN_337   					(337UL)
#define PLLI2SN_338   					(338UL)
#define PLLI2SN_339   					(339UL)
#define PLLI2SN_340   					(340UL)
#define PLLI2SN_341   					(341UL)
#define PLLI2SN_342   					(342UL)
#define PLLI2SN_343   					(343UL)
#define PLLI2SN_344   					(344UL)
#define PLLI2SN_345   					(345UL)
#define PLLI2SN_346   					(346UL)
#define PLLI2SN_347   					(347UL)
#define PLLI2SN_348   					(348UL)
#define PLLI2SN_349   					(349UL)
#define PLLI2SN_350   					(350UL)
#define PLLI2SN_351   					(351UL)
#define PLLI2SN_352   					(352UL)
#define PLLI2SN_353   					(353UL)
#define PLLI2SN_354   					(354UL)
#define PLLI2SN_355   					(355UL)
#define PLLI2SN_356   					(356UL)
#define PLLI2SN_357   					(357UL)
#define PLLI2SN_358   					(358UL)
#define PLLI2SN_359   					(359UL)
#define PLLI2SN_360   					(360UL)
#define PLLI2SN_361   					(361UL)
#define PLLI2SN_362   					(362UL)
#define PLLI2SN_363   					(363UL)
#define PLLI2SN_364   					(364UL)
#define PLLI2SN_365   					(365UL)
#define PLLI2SN_366   					(366UL)
#define PLLI2SN_367   					(367UL)
#define PLLI2SN_368   					(368UL)
#define PLLI2SN_369   					(369UL)
#define PLLI2SN_370   					(370UL)
#define PLLI2SN_371   					(371UL)
#define PLLI2SN_372   					(372UL)
#define PLLI2SN_373   					(373UL)
#define PLLI2SN_374   					(374UL)
#define PLLI2SN_375   					(375UL)
#define PLLI2SN_376   					(376UL)
#define PLLI2SN_377   					(377UL)
#define PLLI2SN_378   					(378UL)
#define PLLI2SN_379   					(379UL)
#define PLLI2SN_380   					(380UL)
#define PLLI2SN_381   					(381UL)
#define PLLI2SN_382   					(382UL)
#define PLLI2SN_383   					(383UL)
#define PLLI2SN_384   					(384UL)
#define PLLI2SN_385   					(385UL)
#define PLLI2SN_386   					(386UL)
#define PLLI2SN_387   					(387UL)
#define PLLI2SN_388   					(388UL)
#define PLLI2SN_389   					(389UL)
#define PLLI2SN_390   					(390UL)
#define PLLI2SN_391   					(391UL)
#define PLLI2SN_392   					(392UL)
#define PLLI2SN_393   					(393UL)
#define PLLI2SN_394   					(394UL)
#define PLLI2SN_395   					(395UL)
#define PLLI2SN_396   					(396UL)
#define PLLI2SN_397   					(397UL)
#define PLLI2SN_398  					(398UL)
#define PLLI2SN_399   					(399UL)
#define PLLI2SN_400   					(400UL)
#define PLLI2SN_401   					(401UL)
#define PLLI2SN_402   					(402UL)
#define PLLI2SN_403   					(403UL)
#define PLLI2SN_404   					(404UL)
#define PLLI2SN_405   					(405UL)
#define PLLI2SN_406   					(406UL)
#define PLLI2SN_407   					(407UL)
#define PLLI2SN_408   					(408UL)
#define PLLI2SN_409   					(409UL)
#define PLLI2SN_410   					(410UL)
#define PLLI2SN_411   					(411UL)
#define PLLI2SN_412   					(412UL)
#define PLLI2SN_413  					(413UL)
#define PLLI2SN_414   					(414UL)
#define PLLI2SN_415   					(415UL)
#define PLLI2SN_416   					(416UL)
#define PLLI2SN_417   					(417UL)
#define PLLI2SN_418   					(418UL)
#define PLLI2SN_419   					(419UL)
#define PLLI2SN_420   					(420UL)
#define PLLI2SN_421   					(421UL)
#define PLLI2SN_422   					(422UL)
#define PLLI2SN_423   					(423UL)
#define PLLI2SN_424   					(424UL)
#define PLLI2SN_425   					(425UL)
#define PLLI2SN_426  					(426UL)
#define PLLI2SN_427   					(427UL)
#define PLLI2SN_428   					(428UL)
#define PLLI2SN_429   					(429UL)	/*(0x00006B40UL)	 	Mask for PLLN bits	*/
#define PLLI2SN_430   					(430UL)	/*(0x00006B80UL)	 	Mask for PLLN bits	*/
#define PLLI2SN_431   					(431UL)	/*(0x00006BC0UL)	 	Mask for PLLN bits	*/
#define PLLI2SN_432   					(432UL)	/*(0x00006C00UL)	 	Mask for PLLN bits	*/
/**************************************************************************************/

/* PLLI2SR options */

/* Division Factor PLLI2SR = 2 */
#define PLLI2SR_2						(2UL)	/*(0x20000000UL)	 	Mask for PLLI2SR bits	*/
/* Division Factor PLLI2SR = 3 */
#define PLLI2SR_3						(3UL)	/*(0x30000000UL)	 	Mask for PLLI2SR bits	*/
/* Division Factor PLLI2SR = 4 */
#define PLLI2SR_4						(4UL)	/*(0x40000000UL)	 	Mask for PLLI2SR bits	*/
/* Division Factor PLLI2SR = 5 */
#define PLLI2SR_5						(5UL)	/*(0x50000000UL)	 	Mask for PLLI2SR bits	*/
/* Division Factor PLLI2SR = 6 */
#define PLLI2SR_6						(6UL)	/*(0x60000000UL)	 	Mask for PLLI2SR bits	*/
/* Division Factor PLLI2SR = 7 */
#define PLLI2SR_7						(7UL)	/*(0x70000000UL)	 	Mask for PLLI2SR bits	*/
/**************************************************************************************/

/* System Clock Source select options */

/* Select HSI as the system clock */
#define SYSCLK_HSI						(0x00000000UL)	/* 	Mask for HSI in SW bit			*/
/* Select HSE as the system clock */
#define SYSCLK_HSE						(0x00000001UL)	/* 	Mask for HSE in SW bit			*/
/* Select Main PLL as the system clock */
#define SYSCLK_PLL						(0x00000002UL)	/* 	Mask for PLL in SW bit			*/
/**************************************************************************************/

/* AHB1 Peripherals */
#define AHB1_GPIOA						(0x00000001UL)	/* 	Mask for GPIOAEN bit 			*/
#define AHB1_GPIOB						(0x00000002UL)	/* 	Mask for GPIOBEN bit 			*/
#define AHB1_GPIOC						(0x00000004UL)	/* 	Mask for GPIOCEN bit 			*/
#define AHB1_GPIOD						(0x00000008UL)	/* 	Mask for GPIODEN bit 			*/
#define AHB1_GPIOE						(0x00000010UL)	/* 	Mask for GPIOEEN bit 			*/
#define AHB1_GPIOH						(0x00000080UL)	/* 	Mask for GPIOHEN bit 			*/
#define AHB1_CRC						(0x00001000UL)	/* 	Mask for CRCEN bit 				*/
#define AHB1_DMA1						(0x00200000UL)	/* 	Mask for DMA1EN bit 			*/
#define AHB1_DMA2						(0x00400000UL)	/* 	Mask for DMA2EN bit 			*/
/**************************************************************************************/

/* AHB2 Peripherals */
#define AHB2_USBOTGFS					(0x00000080UL)	/* 	Mask for OTGFSEN bit 			*/
/**************************************************************************************/

/* APB1 Peripherals */
#define APB1_TIM2						(0x00000001UL)	/* 	Mask for TIM2EN bit 			*/
#define APB1_TIM3						(0x00000002UL)	/* 	Mask for TIM3EN bit 			*/
#define APB1_TIM4						(0x00000004UL)	/* 	Mask for TIM4EN bit 			*/
#define APB1_TIM5						(0x00000008UL)	/* 	Mask for TIM5EN bit 			*/
#define APB1_WWDG						(0x00000800UL)	/* 	Mask for WWDGEN bit 			*/
#define APB1_SPI2						(0x00004000UL)	/* 	Mask for SPI2EN bit 			*/
#define APB1_SPI3						(0x00008000UL)	/* 	Mask for SPI3EN bit 			*/
#define APB1_USART2						(0x00020000UL)	/* 	Mask for USART2EN bit			*/
#define APB1_I2C1						(0x00200000UL)	/* 	Mask for I2C1EN bit 			*/
#define APB1_I2C2						(0x00400000UL)	/* 	Mask for I2C2EN bit 			*/
#define APB1_I2C3						(0x00800000UL)	/* 	Mask for I2C3EN bit 			*/
#define APB1_PWR						(0x10000000UL)	/* 	Mask for PWREN bit 				*/
/**************************************************************************************/

/* APB2 Peripherals */
#define APB2_TIM1						(0x00000001UL)	/* 	Mask for TIM1EN bit 			*/
#define APB2_USART1						(0x00000010UL)	/* 	Mask for USART1EN bit 			*/
#define APB2_USART6						(0x00000020UL)	/* 	Mask for USART6EN bit 			*/
#define APB2_ADC1						(0x00000100UL)	/* 	Mask for ADC1EN bit 			*/
#define APB2_SDIO						(0x00000800UL)	/* 	Mask for SDIOEN bit 			*/
#define APB2_SPI1						(0x00001000UL)	/* 	Mask for SPI1EN bit 			*/
#define APB2_SPI4						(0x00002000UL)	/* 	Mask for SPI4EN bit 			*/
#define APB2_SYSCFG						(0x00004000UL)	/* 	Mask for SYSCFGEN bit 			*/
#define APB2_TIM9						(0x00010000UL)	/* 	Mask for TIM9EN bit 			*/
#define APB2_TIM10						(0x00020000UL)	/* 	Mask for TIM10EN bit 			*/
#define APB2_TIM11						(0x00040000UL)	/* 	Mask for TIM11EN bit 			*/
/**************************************************************************************/

/* AHB Pre-scaler options */

/*	system clock not divided	*/
#define AHBPRES_1						(0x00000000UL)	/*	Mask for AHBPRES_1				*/
/*	system clock divided by 2	*/
#define AHBPRES_2						(0x00000080UL)	/*	Mask for AHBPRES_2				*/
/*	system clock divided by 4	*/
#define AHBPRES_4						(0x00000090UL)	/*	Mask for AHBPRES_4				*/
/*	system clock divided by 8	*/
#define AHBPRES_8						(0x000000A0UL)	/*	Mask for AHBPRES_8				*/
/*	system clock divided by 16	*/
#define AHBPRES_16						(0x000000B0UL)	/*	Mask for AHBPRES_16				*/
/*	system clock divided by 64	*/
#define AHBPRES_64						(0x000000C0UL)	/*	Mask for AHBPRES_64				*/
/*	system clock divided by 128	*/
#define AHBPRES_128						(0x000000D0UL)	/*	Mask for AHBPRES_128			*/
/*	system clock divided by 256	*/
#define AHBPRES_256						(0x000000E0UL)	/*	Mask for AHBPRES_256			*/
/*	system clock divided by 512	*/
#define AHBPRES_512						(0x000000F0UL)	/*	Mask for AHBPRES_512			*/
/**************************************************************************************/

/* APB1 Pre-scaler options */

/*	AHB clock not divided	*/
#define APB1PRES_1						(0x00000000UL)	/*	Mask for APB1PRES_1				*/
/*	AHB clock divided by 2	*/
#define APB1PRES_2						(0x00001000UL)	/*	Mask for APB1PRES_2				*/
/*	AHB clock divided by 4	*/
#define APB1PRES_4						(0x00001400UL)	/*	Mask for APB1PRES_4				*/
/*	AHB clock divided by 8	*/
#define APB1PRES_8						(0x00001800UL)	/*	Mask for APB1PRES_8				*/
/*	AHB clock divided by 16	*/
#define APB1PRES_16						(0x00001C00UL)	/*	Mask for APB1PRES_16			*/
/**************************************************************************************/

/* APB2 Pre-scaler options */

/*	AHB clock not divided	*/
#define APB2PRES_1						(0x00000000UL)	/*	Mask for APB2PRES_1				*/
/*	AHB clock divided by 2	*/
#define APB2PRES_2						(0x00008000UL)	/*	Mask for APB2PRES_2				*/
/*	AHB clock divided by 4	*/
#define APB2PRES_4						(0x0000A000UL)	/*	Mask for APB2PRES_4				*/
/*	AHB clock divided by 8	*/
#define APB2PRES_8						(0x0000C000UL)	/*	Mask for APB2PRES_8				*/
/*	AHB clock divided by 16	*/
#define APB2PRES_16						(0x0000E000UL)	/*	Mask for APB2PRES_16			*/
/**************************************************************************************/

/* Timers' Frequency pre-scaler */

/* 	If the APB prescaler (PPRE1, PPRE2 in the RCC_CFGR register) is configured to a
	division factor of 1, TIMxCLK = HCKL . Otherwise, the timer clock frequencies are set to
	twice to the frequency of the APB domain to which the timers are connected:
	TIMxCLK = 2xPCLKx. */
#define TIMPRE_0						(0x00000000UL)	/* 	Mask for TIMPRE clear  			*/
/* 	If the APB prescaler ( PPRE1, PPRE2 in the RCC_CFGR register) is configured to a
	division factor of 1 or 2, TIMxCLK = HCKL. Otherwise, the timer clock frequencies are set to
	four times to the frequency of the APB domain to which the timers are connected:
	TIMxCLK = 4xPCLKx. */
#define TIMPRE_1						(0x01000000UL)	/*	Mask for TIMPRE set				*/


/****************************************************************************************/
/*								User-defined types Declaration							*/
/****************************************************************************************/


/**
 *@brief : The Error List Type
 */
typedef enum
{
	/**
	 *@brief : Everything OK, function had Performed Correctly.
	 */
	RCC_enuOk = 0,
	/**
	 *@brief : Something went wrong in the function.
	 */
	RCC_enuNotOk,
	/**
	 *@brief : Null pointer is passed to a function as an argument.
	 */
	RCC_enuNullPointer
}RCC_enuErrorStatus_t;







/********************************************************************************************/
/*									Functions' Declaration									*/
/********************************************************************************************/


/**
 *@brief : Function to Set the HSI clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableHSI(void);


/**
 *@brief : Function to Set the HSI clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableHSI(void);


/**
 *@brief : Function to Set the HSE crystal clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableHSECrystal(void);


/**
 *@brief : Function to Set the HSE crystal clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableHSECrystal(void);


/**
 *@brief : Function to Set the HSE Bypass clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableHSEBYP(void);


/**
 *@brief : Function to Set the HSE Bypass clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableHSEBYP(void);


/**
 *@brief : Function to Set the Main PLL clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableMainPLL(void);


/**
 *@brief : Function to Set the Main PLL clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableMainPLL(void);


/**
 *@brief : Function to Set the PLLI2S clock ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnablePLLI2S(void);


/**
 *@brief : Function to Set the PLLI2S clock OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisablePLLI2S(void);


/**
 *@brief : Function to Set the Clock security system ON.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableCSS(void);


/**
 *@brief : Function to Set the Clock security system OFF.
 *@param : void.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableCSS(void);
/**************************************************************************************/


/**
 *@brief : Function to Set the PLLs clock source.
 *@param : PLLSRC_HSI	or	PLLSRC_HSE.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuSelectPLLsSrc(u32 Copy_u32PLLSrc);


/**
 *@brief : Function to Get the PLLs clock source, will be used in calculations.
 *@param : Address of a variable in which the current PLLs clock source will be returned.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuGetPLLsSrc(u32* Add_u32PLLSrc);


/**
 *@brief : Function to Configure The Main PLL.
 *@param : Values of PLLM, PLLN, PLLP, PLLQ respectively.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigMainPLL(u32 Copy_u32PLLM, u32 Copy_u32PLLN, u32 Copy_u32PLLP, u32 Copy_u32PLLQ);


///**
// *@brief : Function to Configure The division Factor PLLM of the PLLs.
// *@param : PLLM.
// *@return: Error status.
// */
//RCC_enuErrorStatus_t RCC_enuConfigPLLM(u32 Copy_u32PLLM);
//
//
///**
// *@brief : Function to Configure The multiplication Factor PLLN of the Main PLL.
// *@param : PLLN.
// *@return: Error status.
// */
//RCC_enuErrorStatus_t RCC_enuConfigPLLN(u32 Copy_u32PLLN);
//
//
///**
// *@brief : Function to Configure The division Factor PLLP of the Main PLL.
// *@param : PLLP.
// *@return: Error status.
// */
//RCC_enuErrorStatus_t RCC_enuConfigPLLP(u32 Copy_u32PLLP);
//
//
///**
// *@brief : Function to Configure The division Factor PLLQ of the Main PLL.
// *@param : PLLQ.
// *@return: Error status.
// */
//RCC_enuErrorStatus_t RCC_enuConfigPLLQ(u32 Copy_u32PLLQ);


/**
 *@brief : Function to Configure The PLLI2S clock.
 *@param : Values of PLLM, PLLI2SN, PLLI2SR respectively.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigPLLI2SN(u32 Copy_u32PLLM, u32 Copy_u32PLLI2SN, u32 Copy_u32PLLI2SR);


///**
// *@brief : Function to Configure The multiplication Factor PLLI2SN of the PLLI2S.
// *@param : PLLI2SN.
// *@return: Error status.
// */
//RCC_enuErrorStatus_t RCC_enuConfigPLLI2SN(u32 Copy_u32PLLI2SN);
//
//
///**
// *@brief : Function to Configure The division Factor PLLI2SR of the PLLI2S.
// *@param : PLLI2SR.
// *@return: Error status.
// */
//RCC_enuErrorStatus_t RCC_enuConfigPLLI2SR(u32 Copy_u32PLLI2SR);
/**************************************************************************************/


/**
 *@brief : Function to Select the System clock source.
 *@param : Copy_u32SysClk. Options: HSI or HSE or PLL.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuSelectSysClk(u32 Copy_u32SysClk);


/**
 *@brief : Function to Know the System clock source, will be used inside other functions.
 *@param : Add_u32SysClk, Address of a variable in which the current System clock source will be returned.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuGetSysClk(u32* Add_u32SysClk);
/**************************************************************************************/


/**
 *@brief : Function to Enable one of the peripherals connected to AHB1 bus.
 *@param : Copy_u32AHB1Peripheral. Options: AHB1_GPIOA ~ AHB1_GPIOH, AHB1_CRC, AHB1_DMA1 and AHB1_DMA2.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableAHB1Peripheral(u32 Copy_u32AHB1Peripheral);


/**
 *@brief : Function to Disable one of the peripherals connected to AHB1 bus.
 *@param : Copy_u32AHB1Peripheral. Options: AHB1_GPIOA ~ AHB1_GPIOH, AHB1_CRC, AHB1_DMA1 and AHB1_DMA2.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableAHB1Peripheral(u32 Copy_u32AHB1Peripheral);


/**
 *@brief : Function to Enable one of the peripherals connected to AHB2 bus.
 *@param : Copy_u32AHB2Peripheral. Options: AHB2_USBOTGFS.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableAHB2Peripheral(u32 Copy_u32AHB2Peripheral);


/**
 *@brief : Function to Disable one of the peripherals connected to AHB2 bus.
 *@param : Copy_u32AHB2Peripheral. Options: AHB2_USBOTGFS.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableAHB2Peripheral(u32 Copy_u32AHB2Peripheral);


/**
 *@brief : Function to Enable one of the peripherals connected to APB1 bus.
 *@param : Copy_u32APB1Peripheral. Options: 	APB1_TIM2 ~ APB1_TIM5, APB1_WWDG, APB1_SPI2, APB1_SPI3,
 *											APB1_USART2, APB1_I2C1 ~ APB1_I2C3 and APB1_PWR.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableAPB1Peripheral(u32 Copy_u32APB1Peripheral);


/**
 *@brief : Function to Disable one of the peripherals connected to APB1 bus.
 *@param : Copy_u32APB1Peripheral. Options: 	APB1_TIM2 ~ APB1_TIM5, APB1_WWDG, APB1_SPI2, APB1_SPI3,
 *											APB1_USART2, APB1_I2C1 ~ APB1_I2C3 and APB1_PWR.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableAPB1Peripheral(u32 Copy_u32APB1Peripheral);


/**
 *@brief : Function to Enable one of the peripherals connected to APB2 bus.
 *@param : Copy_u32APB2Peripherl. Options: 	APB2_TIM1, APB2_USART1, APB2_USART6, APB2_ADC1,
 *											APB2_SDIO, APB2_SPI1, APB2_SPI4, APB2_SYSCFG,
 *											APB2_TIM9 ~ APB2_TIM11.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuEnableAPB2Peripheral(u32 Copy_u32APB2Peripheral);


/**
 *@brief : Function to Disable one of the peripherals connected to APB2 bus.
 *@param : Copy_u32APB2Peripheral. Options: 	APB2_TIM1, APB2_USART1, APB2_USART6, APB2_ADC1,
 *											APB2_SDIO, APB2_SPI1, APB2_SPI4, APB2_SYSCFG,
 *											APB2_TIM9 ~ APB2_TIM11.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuDisableAPB2Peripheral(u32 Copy_u32APB2Peripheral);
/**************************************************************************************/


/**
 *@brief : Function to Configure the pre-scaler of the AHB clock source.
 *@param : Copy_u32AHBPRES. Options: 	AHBPRES_1, AHBPRES_2, AHBPRES_4,
 *										AHBPRES_8, AHBPRES_16, AHBPRES_64,
 *										AHBPRES_128, AHBPRES_256, AHBPRES_512.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigAHBPRES(u32 Copy_u32AHBPRES);


/**
 *@brief : Function to Configure the pre-scaler of the APB1 clock source.
 *@param : Copy_u32APB1PRES. Options: 	APB1PRES_1, APB1PRES_2, APB1PRES_4,
 *										APB1PRES_8, APB1PRES_16.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigAPB1PRES(u32 Copy_u32APB1PRES);


/**
 *@brief : Function to Configure the pre-scaler of the APB2 clock source.
 *@param : Copy_u32APB2PRES. Options: 	APB2PRES_1, APB2PRES_2, APB2PRES_4,
 *										APB2PRES_8, APB2PRES_16.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigAPB2PRES(u32 Copy_u32APB2PRES);


/**
 *@brief : Function to Control the clock frequency of all the timers connected to APB1 and APB2 domain..
 *@param : Copy_u32TIMsPRES. Options: 	TIMPRE_0, TIMPRE_1.
 *@return: Error status.
 */
RCC_enuErrorStatus_t RCC_enuConfigTimersPRES(u32 Copy_u32TIMsPRES);




#endif /* RCC_INTERFACE_H_ */
