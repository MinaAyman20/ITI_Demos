#ifndef BIT_MATH_H_
#define BIT_MATH_H_

// Set bit BIT in REG
#define SET_BIT(REG,BIT)                      (REG) |=(1 << (BIT))                                   //han3ml set 3ady hanwdy 1 f mkan al bit aly 3ayzino w b3den n3ml or 3m al rkm b3d al shift
// Clear bit BIT in REG                                                                             
#define CLR_BIT(REG,BIT)                      (REG )&=  (~(1 << (BIT)))                              //han3ml shift b 1 fil mkan w b3den n2lb al rkn kolo 3ashan 3ayzen n3ml and asln m3 zero mash 1 f haykon al rkm kolo wa7ayd m3ada aly h3mlo and m3ah b zero
// Toggle bit BIT in REG                                                                            
#define TGL_BIT(REG,BIT)                      ( REG) ^= (1 << (BIT))                                 //ast5dmna ^ m3 al 1 3ashan ay 7aga shbh b3d batkon 0 f law 1 m3 1 hy2lbha zero w law 1m3 zero hat2lb 1  
// Get bit BIT in REG                                                                               
#define GET_BIT(REG,BIT)                      ( (REG >> BIT) & (0x01))                              //hangebha 3la al tarf al awl w b3den n3mlha & m3 al 1 3ashan law kant 1 tagily 1 w law kant 0 tagily 0
																					             
// Set high nibble in REG                                                                           
#define SET_HIGH_NIB(REG)                     ((REG) |=  (0xF0))                                    //n3mlha | m3 0x11110000  (m3 al or al 1 howa al mo2aser)
// Clear high nibble in REG                                                                         
#define CLR_HIGH_NIB(REG)                     ((REG) &=  (0x0F))                                    //n3mlha & m3 0x00001111  (m3 al and al 0 howa al mo2aser)
// Get high nibble in REG                                                                           
#define GET_HIGH_NIB(REG)                     (((REG) >>4) & (0x0F))                                //a3mlha shift b 4 3ashan agibha 3la al tarf w b3den n3mlha & m3 al 00001111 3ashan al wa7d mash mo2sr 
// Toggle high nibble in REG                                                                        
#define TGL_HIGH_NIB(REG)                     ((REG) ^=  (0xF0))                                    //n3mlha ^ m3 0x11110000
// Set low nibble in REG                                                                            
#define SET_LOW_NIB(REG)                      ((REG) |=  (0x0f) )                                   //n3mlha | m3 0x00001111
// Clear low nibble in REG                                                                          
#define CLR_LOW_NIB(REG)                      ((REG) &=  (0xf0) )                                   //n3mlha & m3 0x111 10000
// Get low nibble in REG                                                                            
#define GET_LOW_NIB(REG)                      ((REG) & (0x0F))                                      //mash han3mlha shift b 4 3ashan hya 3la al tarf asln bs n3mlha & m3 al 00001111 n7afz 3la al goz2 aly 3ayzino w n3ml mask lal high 3ashn mayt2srsh  
// Toggle low nibble in REG                                                                         
#define TGL_LOW_NIB(REG)                      ((REG) ^  (0x0f) )                                    //n3mlha ^ m3 0x00001111
																					             
// Assign VALUE to REG                                                                              
#define ASSIGN_REG(REG,VALUE)                 ((REG) =(VALUE))                                      // 7ot al value fil regester
// Assign VALUE to high nibble REG                                                                  
#define ASSIGN_HIGH_NIB(REG,VALUE)            ((REG & 0x0F)  | (((VALUE) & (0xF0))<< 4))            //al reg lazm nsfr goz2 al aly h3mlo set w a7afz 3la al adim f h3ml & m3 00001111 w al value bardo ashil mnha goz2 al low bt3ha f a3ml & m3 11110000 w nashftha b 4 w n3ml or
// Assign VALUE to low nibble REG                                                                   
#define ASSIGN_LOW_NIB(REG,VALUE)             ((REG & 0xF0)  | ((VALUE & 0x0F) ))                   //al reg lazm nsfr al goz2 aly han3mlo set w n7afz 3la al adim f han3ml and m3 11110000 w al value aly gya mash mohem goz2 al high bansbaly f h3mlo and m3 00001111 3ashan yakon 3andy al value bs b3den n3ml or
// Right shift by NO in REG                                                                         
#define RSHFT_REG(REG, NUM)                   ((REG) >>= (NUM))                                     //shaftha ymin b rkm
// Left shift by NO in REG                                                                          
#define LSHFT_REG(REG, NUM)                   ((REG) <<= (NUM))                                     //shaftha shmal b rkm
// Circular right shift by NO in REG
#define CRSHFT_REG(REG, NUM)           REG =  ( (REG >> NUM) | (REG << (8 - (NUM))) )               //banshft al awl bel size - al num 3ashan yaro7o f awl kam mkan w b3den al reg al asly ashfto left b mkdar al num 3ashan yanzlo b3d aly a7na shaftnahom right b3den or 3ashan alz2hom f b3d
// Circular left shift by NO in REG
#define CLSHFT_REG(REG,NUM)            REG =  ( (REG << NUM) | (REG << (8 - (NUM))) )               //banshft al awl bel size - al num 3ashan yaro7o f awl kam mkan w b3den al reg al asly ashfto right b mkdar al num 3ashan yanzlo b3d aly a7na shaftnahom left b3den or 3ashan alz2hom f b3d
// Circular left shift by NO in REG


#endif    